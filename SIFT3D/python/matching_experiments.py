import glob
import os
import csv
import numpy as np
import collections

from sklearn.svm import SVC

from SIFT3D.python.settings import Constants
from SIFT3D.python.utils import infer_label
from SIFT3D.python.videoDescription import vocab_creation, descriptor_evaluation
import logging
logging.basicConfig(level=Constants.LOGGING_LEVEL)
def warn(*args, **kwargs):
    pass
import warnings
warnings.warn = warn
from sklearn import svm, neighbors
from sklearn.model_selection import train_test_split
from sklearn.decomposition import PCA
from sklearn.model_selection import GridSearchCV
from sklearn import preprocessing
from keras.models import Sequential
from keras.layers import Dense, Activation, Dropout, BatchNormalization, Merge
from keras.utils import np_utils
from keras.regularizers import l2
import matplotlib.pyplot as plt
import random
import xgboost as xgb

def load_samples_from_file(file_name, X, y):
    csvReader = csv.reader(open(file_name, "r"))
    xi = list(csvReader)
    # xi looks like this: [[0,1,2],[4,5,6],[7,8,9]] where [0,1,2] is data from the first descriptor
    # we don't want multiple list levels in X, so we do as follows
    for i in range(0, len(xi)):
        X.append(xi[i])
        # only take the top 200 descriptors; this can be changed in the settings file
        if Constants.TAKE_TOP_200 == True and i == 199:
            break
    yi = infer_label(file_name)
    if Constants.TAKE_TOP_200 == True:
        # if we want to only take the top 200 descriptors, we also must take care not to get out of bounds
        # on yi in the next for loop, as some short videos might have less than 200 descriptors
        times = min(len(xi), 200)
    else:
        # len(xi) is the number of descriptors we found in a file: they all have the same label
        times = len(xi)
    for i in range(0, times):
        y.append(yi)
    return X, y

def load_descriptors_and_features(des_file_name, feature_file_name, X, F, y):
    des_reader = csv.reader(open(des_file_name, "r"))
    feature_reader = csv.reader(open(feature_file_name, "r"))
    xi = list(des_reader)
    fi = list(feature_reader)
    # xi looks like this: [[0,1,2],[4,5,6],[7,8,9]] where [0,1,2] is data from the first descriptor
    # we don't want multiple list levels in X, so we do as follows
    for i in range(0, len(xi)):
        X.append(xi[i])
        F.append(fi[i])
        # only take the top 200 descriptors; this can be changed in the settings file
        if Constants.TAKE_TOP_200 == True and i == 199:
            break
    yi = infer_label(des_file_name)
    if Constants.TAKE_TOP_200 == True:
        # if we want to only take the top 200 descriptors, we also must take care not to get out of bounds
        # on yi in the next for loop, as some short videos might have less than 200 descriptors
        times = min(len(xi), 200)
    else:
        # len(xi) is the number of descriptors we found in a file: they all have the same label
        times = len(xi)
    for i in range(0, times):
        y.append(yi)
    return X, F, y

def load_samples_from_file_same_dim(file_name, feature_file_name, X, y, octave, scale):
    descriptor_reader = csv.reader(open(file_name, "r"))
    xi = list(descriptor_reader)
    feature_reader = csv.reader(open(feature_file_name, "r"))
    fi = list(feature_reader)
    # xi looks like this: [[0,1,2],[4,5,6],[7,8,9]] where [0,1,2] is data from the first descriptor
    # we don't want multiple list levels in X, so we do as follows
    for i in range(0, len(xi)):
        f = fi[i]
        # checking that the descriptor was extracted in a certain point in the scale space
        if int(f[0]) == octave and int(f[1]) == scale:
            X.append(xi[i])
    yi = infer_label(file_name)
    if Constants.TAKE_TOP_200 == True:
        # if we want to only take the top 200 descriptors, we also must take care not to get out of bounds
        # on yi in the next for loop, as some short videos might have less than 200 descriptors
        times = min(len(xi), 200)
    else:
        # len(xi) is the number of descriptors we found in a file: they all have the same label
        times = len(xi)
    for i in range(0, times):
        y.append(yi)
    return X, y

def pca_plot(X, y):
    pca = PCA(n_components=2)
    logging.info("pca_plot: Computing PCA.")
    X_pca = pca.fit_transform(X, y=y)
    print(X.shape)
    print(X_pca.shape)
    # use y to infer the color/labels
    colors = [int(i % 7) for i in y]
    plt.scatter(X_pca[:,0], X_pca[:,1], c=colors)
    plt.show()

def create_model(X, y):
    X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.1)
    logging.info("Training the model")
    #model = svm.SVC().fit(X_train, y_train)
    model = neighbors.KNeighborsClassifier(15).fit(X_train, y_train)
    #model = svm.LinearSVC(C=1e-06, max_iter=2000, verbose=1, tol=0.0000001).fit(X_train, y_train)
    accuracy = model.score(X_train, y_train)
    logging.info("Achieved " + str(accuracy) + " accuracy on the training set")
    accuracy = model.score(X_test, y_test)
    logging.info("Achieved " + str(accuracy) + " accuracy on the test set")
    return model

def xgb_experiment(X, y):
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
    #X = preprocessing.scale(X)
    X -= np.mean(X)
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
    X -= np.mean(X)
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

def majority_voting(model, test_videos):
    yeah = 0
    noes = 0
    # TODO: refactor this. Too similar to load_descriptors
    for file in test_videos:
        X = []
        y = []
        X, y_actual = load_samples_from_file(file, X, y)
        X = np.array(X).astype(np.float32)  # scikit-learn requires this
        y_actual = np.array(y).astype(np.int32)
        # can take just any one label: let's take the first
        actual_label = y_actual[0]
        y_predicted = model.predict(X)
        # the predicted label for the whole video
        # is the one that is predicted the most times for single descriptors from that video
        max_counts = max(np.bincount(y_predicted))
        # casting to list has to be done because numpy arrays and lists are handled differently
        predicted_label = list(np.bincount(y_predicted)).index(max_counts)
        if predicted_label == actual_label:
            yeah += 1
        else:
            noes += 1
    return yeah, noes


def split_train_test_videos(folder, num_testing_videos):
    test_videos = []
    train_videos = []
    for file in glob.glob(folder + "/*.csv"):
        train_videos.append(file)
    r = random.Random()
    for i in range(0, num_testing_videos):
        rand_video_id = r.randint(0, len(train_videos)-1)
        test_videos.append(train_videos[rand_video_id])
        del train_videos[rand_video_id]
    return train_videos, test_videos

def load_descriptors(video_list):
    # X: matrix of sample data. At this time, each row is a SIFT3D descriptor.
    X = []
    # y: matrix of labels. The .csv files don't have these, so we infer them from the file name.
    y = []
    for file in video_list:
        X, y = load_samples_from_file(file, X, y)
    X = np.array(X).astype(np.float32) # scikit-learn requires this
    y = np.array(y).astype(np.int32)
    logging.info("Loaded " + str(len(X)) + " descriptors.")
    # if this fails, then something went wrong with the loading and labeling
    assert len(X) == len(y)
    if Constants.SHOW_PLOTS == True:
        pca_plot(X, y)
    return X, y

def weissman_experiment():
    logging.info("Starting a matching experiment on the Weissman dataset.")
    train_videos, test_videos = split_train_test_videos(Constants.WEISSMAN_DATASET_DIR, 10)
    X_train, y_train = load_descriptors(train_videos)
    model = create_model(X_train, y_train)
    #model = xgb_experiment(X_train, y_train)
    yeah, noes = majority_voting(model, test_videos)
    logging.info("By majority voting: " + str(yeah) + " correct predictions, " + str(noes) + " wrong predictions.")
    return yeah, noes

def kth_experiment():
    logging.info("Starting a matching experiment on the KTH dataset.")
    train_videos, test_videos = split_train_test_videos(Constants.KTH_DATASET_DIR, 1)
    X_train, y_train = load_descriptors(train_videos)
    model = create_model(X_train, y_train)
    yeah, noes = majority_voting(model, test_videos)
    logging.info("By majority voting: " + str(yeah) + " correct predictions, " + str(noes) + " wrong predictions.")
    return yeah, noes

def estimate_hyperparameters(X, y):

    parameters = [
        {'C': np.logspace(-8, 5, num=14, base=10)},
        #{'n_neighbors' : range(1, 20)},
        #{'weights': ['uniform', 'distance']}
    ]

    param_grid = [
        {'C': np.logspace(-20, 2, num=23, base=10), 'kernel': ['linear']},
        {'C': np.logspace(-20, 2, num=23, base=10), 'gamma': [0.001, 0.0001], 'kernel': ['rbf']},
    ]

    #clf = GridSearchCV(svm.SVC(C=1, kernel='sigmoid', gamma=0.01), parameters, cv=5, scoring='accuracy', verbose=0)
    clf = GridSearchCV(svm.SVC(C=1), param_grid, cv=2, scoring='accuracy', verbose=0)
    #clf = GridSearchCV(neighbors.KNeighborsClassifier(n_neighbors=1, weights='uniform', n_jobs=-1, algorithm='ball_tree'),
    #                   parameters, cv=5, scoring='accuracy', verbose=2)
    clf.fit(X, y)
    print(clf.best_params_)
    return clf.best_params_

def weissman_experiment_multiple(times):
    total_yeahs = 0
    total_noes = 0
    for i in range(0, times):
        yeah, noes = weissman_experiment()
        total_yeahs += yeah
        total_noes += noes
    logging.info("After "+str(times)+" Weissman experiments:")
    logging.info(""+ str(total_yeahs) + " correct predictions")
    logging.info(""+ str(total_noes) + " wrong predictions")
    logging.info(""+ str(total_yeahs/times) + " accuracy")

def kth_experiment_multiple(times):
    total_yeahs = 0
    total_noes = 0
    for i in range(0, times):
        yeah, noes = kth_experiment()
        total_yeahs += yeah
        total_noes += noes
    logging.info("After " + str(times) + " Weissman experiments:")
    logging.info("" + str(total_yeahs) + "correct predictions")
    logging.info("" + str(total_noes) + " wrong predictions")
    logging.info("" + str(total_yeahs / times) + " accuracy")

def vocab_experiment(size, c=0.001):
    #dicts, y = vocabCreation.generate_vocabulary(Constants.DATA_DIR + '/descriptors/weissman-yash/', size)

    dicts, y = vocab_creation.load_vocab(Constants.DATA_DIR + 'vocabs/bbrister-2grams-window/',
                                         Constants.WEISSMAN_DATASET_DIR, size)

    #train_videos, test_videos = split_train_test_videos(Constants.DESCRIPTORS_DIR + '/bbrister/', 10)
    #X_train, y_train = load_descriptors(train_videos)

    X_train, X_test, y_train, y_test = train_test_split(dicts, y, test_size=0.1, stratify=y)

    scaler = preprocessing.StandardScaler().fit(X_train)
    scaler.transform(X_train)
    scaler.transform(X_test)

    #X_test, X_dev, y_test, y_dev = train_test_split(X_test, y_test, test_size=0.5, stratify=y_test)


    #best_params_dict = estimate_hyperparameters(X_dev, y_dev)

    #k = estimate_hyperparameters(X_train, y_train)

    model = svm.LinearSVC(C=1e-3)
    #model = svm.SVC(**best_params_dict)
    #model = neighbors.KNeighborsClassifier(n_neighbors=15)
    model.fit(X_train, y_train)
    logging.info("Done fitting.")

    #yeah, noes = majority_voting(model, test_videos)
    #logging.info("Done voting.")

    #model = xgb_model(dicts, y)
    accuracy = model.score(X_train, y_train)
    logging.info("Achieved " + str(accuracy) + " accuracy on the training set")
    #logging.info("By majority rule, " + str(yeah) + " successes and " + str(noes) + " failures")
    #logging.info("Good for " + str(yeah / (yeah + noes)) + " accuracy")
    accuracy = model.score(X_test, y_test)
    logging.info("Achieved " + str(accuracy) + " accuracy on the test set")
    return accuracy

def vocab_experiment_multiple_sizes(size_arr):
    accuracies = []
    for size in size_arr:
        logging.info('Trying size '+ str(size) + ':')
        accuracy = vocab_experiment(size)
        accuracies.append(accuracy)
    mean = sum(accuracies) / len(accuracies)
    logging.info('Achieved ' + str(mean) + ' accuracies over ' + str(len(accuracies)) + ' tries.')

def vocab_experiment_multiple(times, size=250, c=0.001):
    accuracies = []
    for i in range(0, times):
        accuracy = vocab_experiment(size, c=c)
        accuracies.append(accuracy)
    mean = sum(accuracies)/len(accuracies)
    logging.info('Achieved '+str(mean)+' accuracies over '+str(times)+' tries.')

def random_experiment(size):
    random_dataset_dir = Constants.DATA_DIR + '/weizmann/random/'
    dicts, y = vocab_creation.generate_vocabulary_with_pruning(random_dataset_dir, size, model=None)
    X_train, X_test, y_train, y_test = train_test_split(dicts, y, test_size=0.1, random_state=42)

    model = svm.LinearSVC(C=0.001)
    # model = neighbors.KNeighborsClassifier(15).fit(X_train, y_train)
    model.fit(X_train, y_train)

    # model = xgb_model(dicts, y)
    accuracy = model.score(X_train, y_train)
    logging.info("Achieved " + str(accuracy) + " accuracy on the training set")
    accuracy = model.score(X_test, y_test)
    logging.info("Achieved " + str(accuracy) + " accuracy on the test set")
    return accuracy

def random_experiment_multiple_sizes(size_arr):
    for size in size_arr:
        random_experiment(size)


def majority_voting_weighted(X_test, y_test, y_pred, X_test_tfidf):
    scores = [0 for i in range(0, Constants.WEISSMAN_LABEL_NUM)]
    for i in range(0, len(X_test)):
        xi = X_test[i]
        yi = y_pred[i]

        scores[yi] += 1 * X_test_tfidf[i]

    high_score = max(scores)
    final_pred = scores.index(high_score)

    print('Final prediction: ' + str(final_pred))
    print('Actual label: ' + str(y_test[0]))
    print(scores)

    if final_pred == y_test[0]:
        return 1
    else:
        return 0



if __name__ == "__main__":
    sizes = [100, 250, 500, 750, 1000, 1250, 1500]
    modes = ['threshold']

    #bigram_cluster_sizes = [7, 10, 16, 23, 27, 32, 36, 39, 45, 50]

    #trigram_cluster_sizes = [4, 5, 7, 8, 9, 10, 11, 12, 20]

    #for size in sizes:
    #    vocab_experiment_multiple(20, size=size)
    for size in sizes:
        #dicts, y = vocabCreation.generate_ngram_vocab(Constants.DATA_DIR + '/descriptors/bbrister-kth/',
        #                                             Constants.DATA_DIR + '/features/bbrister-kth/', size, n=2, ngram_strategy='window')
        dicts, y = vocab_creation.generate_vocabulary(Constants.DATA_DIR + '/descriptors/bbrister-kth/', size=size)
    #    print(dicts)

    # # tfidf experiments
    # times = 20
    # successes = 0
    # for mode in modes:
    #     for i in range(0, times):
    #         # split and load descriptors
    #         train_videos, test_videos = split_train_test_videos(Constants.DESCRIPTORS_DIR + '/bbrister/', 1)
    #         X_train, y_train = load_descriptors(train_videos)
    #         X_test, y_test = load_descriptors(test_videos)
    #
    #         # train the evaluation model
    #         vocab_size = 500
    #         #tfidf_evaluator = descriptorEvaluation.TFIDF_Evaluator(vocab_size, Constants.WEISSMAN_LABEL_NUM)
    #         #tfidf_evaluator.train(X_train, y_train)
    #         cluster_evaluator = descriptorEvaluation.contestedClusterEvaluator(vocab_size, Constants.WEISSMAN_LABEL_NUM)
    #         cluster_evaluator.train(X_train, y_train)
    #
    #         # train the k-neighbors model
    #         model = neighbors.KNeighborsClassifier(15)
    #         model.fit(X_train, y_train)
    #         y_pred = model.predict(X_test)
    #
    #         # get the weights for the test data and vote by majority
    #         #X_test_tfidf = tfidf_evaluator.get_evaluation(X_test, y_pred)
    #         X_test_cluster_goodness = cluster_evaluator.get_evaluation(X_test, mode=mode)
    #         #X_test_tfidf = [1 for xi in X_test]
    #         success = majority_voting_weighted(X_test, y_test, y_pred, X_test_cluster_goodness)
    #         logging.info('Experiment state was ' + str(success))
    #         successes += success
    #
    # logging.info('Average over ' + str(times) + ' tries : ' + str(successes / times))

    #weissman_experiment_multiple(2)
    #vocab_experiment_multiple_sizes(sizes)
    #for size in sizes:
    #    vocab_experiment_multiple(20, size=size)
    #vocab_experiment_multiple_sizes(sizes)
    #random_experiment_multiple_sizes(sizes)


    # experiments in directly recognizing descriptor classes
    '''
    train_videos, test_videos = split_train_test_videos(Constants.DESCRIPTORS_DIR + '/bbrister/', 10)
    X, y = load_descriptors(train_videos)
    mean_X = np.mean(X)
    X -= mean_X
    #y = np_utils.to_categorical(y, 10)
    #model = neural_net_model(X, y)
    model = svm.SVC()
    model.fit(X, y)
    #model.fit(X, y, verbose=1, nb_epoch=80)

    logging.info('Obtained '+ str(model.score(X, y)) + ' accuracy on the training set')
    X_test, y_test = load_descriptors(test_videos)
    X_test -= mean_X
    #y_test = np_utils.to_categorical(y_test, 10)
    score = model.score(X_test, y_test)
    #score = model.evaluate(X_test, y_test)
    print(score)
    model.save('mymodel-6.keras')
    #yeah, noes = majority_voting(model, test_videos)
    #logging.info('Obtained '+ str(yeah/yeah+noes) + ' accuracy on the test set')
    '''


    #weissman_experiment_multiple(5)