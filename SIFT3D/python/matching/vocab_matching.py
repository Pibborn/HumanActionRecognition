from SIFT3D.python.utils.utils import Constants
from SIFT3D.python.videodescription import vocab_creation, descriptor_evaluation
import logging
logging.basicConfig(level=Constants.LOGGING_LEVEL)
from sklearn import svm, neighbors
from sklearn.model_selection import train_test_split
from sklearn import preprocessing
import os

def vocab_experiment(dicts, y, model, preprocess=True, estimate_parameters=False):
    logging.info("Started a vocabulary matching experiment.")
    X_train, X_test, y_train, y_test = train_test_split(dicts, y, test_size=0.1, stratify=y)

    if preprocess == True:
        logging.debug("Preprocessing data...")
        scaler = preprocessing.StandardScaler().fit(X_train)
        scaler.transform(X_train)
        scaler.transform(X_test)

    if estimate_parameters == True:
        logging.debug("Estimating hyperparameters...")
        X_test, X_dev, y_test, y_dev = train_test_split(X_test, y_test, test_size=0.5, stratify=y_test)
        # TODO: reimplement this
        pass

    logging.debug("Fitting the model...")
    model.fit(X_train, y_train)
    logging.debug("Done fitting.")
    accuracy = model.score(X_train, y_train)
    logging.debug("Achieved " + str(accuracy) + " accuracy on the training set")
    accuracy = model.score(X_test, y_test)
    logging.info("Achieved " + str(accuracy) + " accuracy on the test set")
    return accuracy

def vocab_experiment_folds(X_train, y_train, X_test, y_test, model, preprocess=True, estimate_parameters=False):
    logging.info("Started a vocabulary matching experiment.")

    if preprocess == True:
        logging.debug("Preprocessing data...")
        scaler = preprocessing.StandardScaler().fit(X_train)
        scaler.transform(X_train)
        scaler.transform(X_test)

    if estimate_parameters == True:
        logging.debug("Estimating hyperparameters...")
        X_test, X_dev, y_test, y_dev = train_test_split(X_test, y_test, test_size=0.5, stratify=y_test)
        # TODO: reimplement this
        pass

    logging.info("Fitting the model...")
    model.fit(X_train, y_train)
    logging.debug("Done fitting.")
    accuracy = model.score(X_train, y_train)
    logging.debug("Achieved " + str(accuracy) + " accuracy on the training set")
    accuracy = model.score(X_test, y_test)
    logging.info("Achieved " + str(accuracy) + " accuracy on the test set")
    return accuracy

def vocab_experiment_multiple_sizes(model, vocab_path, dataset_path, size_arr):
    accuracies = []
    for size in size_arr:
        dicts, y = vocab_creation.load_vocab_from_size(vocab_path, dataset_path, size)
        logging.info('Trying size '+ str(size) + ':')
        accuracy = vocab_experiment(dicts, y, model)
        accuracies.append(accuracy)
    mean = sum(accuracies) / len(accuracies)
    logging.info('Achieved ' + str(mean) + ' mean accuracy over ' + str(len(accuracies)) + ' tries.')

def vocab_experiment_multiple_times(dicts, y, model, times):
    accuracies = []
    for i in range(0, times):
        accuracy = vocab_experiment(dicts, y, model)
        accuracies.append(accuracy)
    mean = sum(accuracies)/len(accuracies)
    logging.info('Achieved '+str(mean)+' mean accuracy over '+str(times)+' tries.')

if __name__ == "__main__":
    model = svm.LinearSVC(C=1e-3)
    # model = svm.SVC()
    # model = neighbors.KNeighborsClassifier(n_neighbors=15)
    dicts, y = vocab_creation.load_vocab_from_size(os.path.join(Constants.DATA_DIR, 'vocabs', 'bbrister-2grams-window'),
                                                   Constants.WEISSMAN_DATASET_DIR, 50)
    vocab_experiment(dicts, y, model)
    vocab_experiment_multiple_sizes(model, os.path.join(Constants.DATA_DIR, 'vocabs', 'bbrister-2'),
                                    Constants.WEISSMAN_DATASET_DIR, [250, 500, 1000])
    vocab_experiment_multiple_times(dicts, y, model, 5)
