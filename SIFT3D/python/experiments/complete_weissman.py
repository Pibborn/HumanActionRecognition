from sklearn.neighbors import KNeighborsClassifier
from sklearn.svm import LinearSVC, SVC
from sklearn.decomposition import PCA

from SIFT3D.python.matching import vocab_matching
from SIFT3D.python.videodescription import vocab_creation
from SIFT3D.python.utils.utils import Constants

import logging
logging.basicConfig(level=Constants.LOGGING_LEVEL)

import os

if __name__ == '__main__':
    bbrister_path = os.path.join(Constants.DESCRIPTORS_DIR, 'weissman-angles')
    vocab_2d_path = os.path.join(Constants.DATA_DIR, 'vocabs', 'bbrister-angles')

    model = LinearSVC()
    dicts, y = vocab_creation.load_vocab(os.path.join(Constants.DATA_DIR, 'vocabs', 'bbrister-angles', ''),
                                         Constants.WEISSMAN_DATASET_DIR, 250)

    accuracies = []
    for i in range(0, len(dicts)):
        X_train = dicts[:i] + dicts[i+1:len(dicts)]
        y_train = y[:i] + y[i + 1:len(dicts)]
        X_test = dicts[i]
        y_test = [y[i]]
        accuracy = vocab_matching.vocab_experiment_folds(X_train, y_train, X_test, y_test, model, preprocess=False)
        accuracies.append(accuracy)

    mean_accuracy = sum(accuracies) / len(dicts)
    logging.info('Achieved ' + str(mean_accuracy) + ' on a complete weissman experiment')