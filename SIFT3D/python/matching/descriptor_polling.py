import xgboost as xgb
import numpy as np
from sklearn import neighbors
from sklearn.model_selection import train_test_split
from SIFT3D.python.settings import Constants
import logging
logging.basicConfig(level=Constants.LOGGING_LEVEL)
from SIFT3D.python.utils.utils import *
from keras.models import Sequential
from keras.layers import Dense, Activation, Dropout, BatchNormalization, Merge
from keras.regularizers import l2
from keras.utils.np_utils import to_categorical

# TODO: uniformare la signature dei modelli keras e di quelli scikit-learn. In questo momento
# bisogna modificare majority_voting per usare uno piuttosto che l'altro.

def xgb_experiment(X, y):
    """
    A function that tests the xgb_boost library to perform descriptor matching. This has a different signature
    than the other scikit-learn classifiers, so it is hard to include it in the majority_voting() workflow.
    """
    X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2)
    dtrain = xgb.DMatrix(X_train, label=y_train)
    dtest = xgb.DMatrix(X_test, label=y_test)

    param = {'optimizer': 'dart', 'max_depth': 5, 'eta': 0.001,
             'silent': 1, 'objective': 'multi:softmax', 'num_class': 10}
    watchlist = [(dtest, 'eval'), (dtrain, 'train')]
    num_round = 1000
    bst = xgb.train(param, dtrain, num_round, watchlist, verbose_eval=False)
    preds = bst.predict(dtest)
    labels = dtest.get_label()
    logging.info('error=%f' % (sum(1 for i in range(len(preds)) if int(preds[i] > 0.5) != labels[i]) / float(len(preds))))
    return bst

def neural_net_model(X, y):
    """
    Builds a multi-layer perceptron for the purpose of classifying descriptor classes. All
    layers are dense. Dropout, batch normalization and L2 weight regularization is included for
    generalization purposes (i.e. avoiding overfitting).
    :param X: np.ndarray
    :param y: np.ndarray
    :return: model: keras neural network
    """
    model = Sequential()
    model.add(Dense(260, input_dim=768, init='glorot_normal', W_regularizer=l2(1e-3)))
    model.add(BatchNormalization())
    model.add(Activation('relu'))
    model.add(Dropout(0.5))
    model.add(Dense(90, W_regularizer=l2(1e-3)))
    model.add(BatchNormalization())
    model.add(Activation('relu'))
    model.add(Dropout(0.5))
    model.add(Dense(30, W_regularizer=l2(1e-3)))
    model.add(BatchNormalization())
    model.add(Activation('relu'))
    model.add(Dropout(0.5))
    model.add(Dense(10))
    model.add(Activation('softmax'))

    model.compile(optimizer='adam',
                  loss='categorical_crossentropy',
                  metrics=['accuracy'])
    return model

def neural_net_model_quadrants(X, y):
    """
    Builds a multi-layer perceptron for the purpose of classifying descriptor classes. All
    layers are dense, but the input layer is tricky: it has different input paths for each "quadrant"
    around the center of the descriptor, so that each 3D sub-histogram is handled differently.
    Dropout, batch normalization and L2 weight regularization is included for
    generalization purposes (i.e. avoiding overfitting).
    :param X: np.ndarray
    :param y: np.ndarray
    :return: model: keras neural network
    """
    # check for correct X shape, or we won't be able to build the input layer
    assert np.shape(X)[1] % 8 == 0
    quadrant_size = np.shape(X)[1] / 8
    input_layers = []
    for i in range(0, 8):
        model = Sequential()
        model.add(Dense(60, input_dim = quadrant_size, W_regularizer=l2(1e-3)))
        model.add(Activation('relu'))
        input_layers.append(model)
    model = Sequential()
    model.add(Merge(input_layers, mode='max'))
    model.add(Dropout(0.2))
    model.add(Dense(30, W_regularizer=l2(1e-3)))
    model.add(BatchNormalization())
    model.add(Activation('relu'))
    model.add(Dense(10, W_regularizer=l2(1e-3)))
    model.add(Activation('softmax'))

    model.compile(optimizer='adagrad',
                  loss='categorical_crossentropy',
                  metrics=['accuracy'])
    return model

def train_descriptor_prediction_model(X, y, **kwargs):
    X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.1, stratify=y)
    X_train -= np.mean(X_train)
    X_test -= np.mean(X_test)
    # You can use any model you wish. Some examples are included. KNeighbors usually works best.
    # model = svm.SVC()
    # model = svm.LinearSVC(C=1e-06, max_iter=2000, verbose=1, tol=0.0000001)
    model = neural_net_model(X_train, y_train)
    # model = neighbors.KNeighborsClassifier(15)

    # handle the keras model case, which requires different labels (but with the same meaning)
    # and has a different fit() function signature
    if 'keras' in str(type(model)):
        y_train = to_categorical(y_train)
        y_test = to_categorical(y_test)
        model.fit(X_train, y_train, **kwargs)
        train_accuracy = model.evaluate(X_train, y_train)
        test_accuracy = model.evaluate(X_test, y_test)
    else:
        model.fit(X_train, y_train)
        train_accuracy = model.score(X_train, y_train)
        test_accuracy = model.evaluate(X_test, y_test)
    logging.info("Achieved " + str(train_accuracy) + " accuracy on the training set")
    logging.info("Achieved " + str(test_accuracy) + " accuracy on the test set")
    return model

def majority_voting(model, test_videos):
    yeah = 0
    noes = 0
    for file in test_videos:
        X = []
        y = []
        X, y_actual = load_samples_from_file(file, X, y)
        X = np.array(X).astype(np.float32)  # scikit-learn requires this
        X -= np.mean(X)
        y_actual = np.array(y).astype(np.int32)
        # can take just any one label: let's take the first
        actual_label = y_actual[0]
        y_predicted = model.predict(X)
        # the predicted label for the whole video
        # is the one that is predicted the most times for single descriptors from that video
        try:
            max_counts = max(np.bincount(y_predicted))
        # this happens when using a keras model, again because of the labels
        except ValueError:
            y_predicted = np.argmax(y_predicted, axis=1)
            max_counts = max(np.bincount(y_predicted))
        # casting to list has to be done because numpy arrays and lists are handled differently
        predicted_label = list(np.bincount(y_predicted)).index(max_counts)
        if predicted_label == actual_label:
            yeah += 1
        else:
            noes += 1
    return yeah, noes

def polling_experiment(dataset_id, **kwargs):
    """
    This is the main entry point for descriptor polling experiments.
    :type dataset_id: str
    :type **kwargs: keyword args. Keras uses a different model.fit() function that also asks for verbosity
    and number of epochs. Try this with verbosity=1 and nb_epoch=10.
    """
    if dataset_id not in Constants.DATASETS:
        logging.error('Unrecognized dataset for polling experiment. Possible datasets: ' + str(Constants.DATASETS))
        return
    else:
        dataset_path = Constants.DATASETS_DIRS[Constants.DATASETS.index(dataset_id)]
    logging.info("Starting a matching experiment on the "+ dataset_id + " dataset.")
    train_videos, test_videos = split_train_test_videos(dataset_path, 10)
    X_train, y_train = load_descriptors(train_videos)
    model = train_descriptor_prediction_model(X_train, y_train, **kwargs)
    yeah, noes = majority_voting(model, test_videos)
    logging.info("By majority voting: " + str(yeah) + " correct predictions, " + str(noes) + " wrong predictions.")
    return yeah, noes

def polling_experiment_multiple(dataset_id, times, **kwargs):
    """
    A simple function that executes polling_experiment(dataset_id) multiple times.
    :type dataset_id: str
    :type times: int
    :type **kwargs: keyword args. Keras uses a different model.fit() function that also asks for verbosity
    and number of epochs. Try this with verbosity=1 and nb_epoch=10.
    """
    total_yeahs = 0
    total_noes = 0
    for i in range(0, times):
        yeah, noes = polling_experiment(dataset_id, **kwargs)
        total_yeahs += yeah
        total_noes += noes
    logging.info("After "+str(times)+" "+ str(dataset_id) + " experiments:")
    logging.info(""+ str(total_yeahs) + " correct predictions")
    logging.info(""+ str(total_noes) + " wrong predictions")
    logging.info(""+ str(total_yeahs/(total_yeahs + total_noes)) + " accuracy")

# Suggestion: don't put complicated experiment scripts here. Instead, if you make some changes
# use this space to test that functionality.
if __name__ == "__main__":
    polling_experiment_multiple('bbrister', 1, nb_epoch=5, verbose=1)