from sklearn.neighbors import KNeighborsClassifier
from sklearn.svm import LinearSVC, SVC
from sklearn.decomposition import PCA

from SIFT3D.python.matching import vocab_matching
from SIFT3D.python.videodescription import vocab_creation
from SIFT3D.python.utils.utils import Constants
import os
import logging
logging.basicConfig(level=Constants.LOGGING_LEVEL,
                    filename=os.path.join(Constants.ROOT_DIR, 'all_vocabs.log'), filemode='w')
import warnings
warnings.filterwarnings("ignore")
import os
import glob

if __name__ == '__main__':
    bbrister_path = os.path.join(Constants.DESCRIPTORS_DIR, 'weissman-angles', '')
    vocab_2d_path = os.path.join(Constants.DATA_DIR, 'vocabs', 'bbrister-3', '')

    vocab_file_list = glob.glob(vocab_2d_path + '*.csv')
    model = LinearSVC()
    #model = SVC(kernel='poly', gamma=1e-4)

    for vocab_file in vocab_file_list:

        dicts, y = vocab_creation.load_vocab_from_path(vocab_file,
                                                       Constants.WEISSMAN_DATASET_DIR)

        accuracies = []
        for i in range(0, len(dicts)):
            X_train = dicts[:i] + dicts[i+1:len(dicts)]
            y_train = y[:i] + y[i + 1:len(dicts)]
            X_test = dicts[i]
            y_test = [y[i]]
            accuracy = vocab_matching.vocab_experiment_folds(X_train, y_train, X_test, y_test, model, preprocess=True)
            accuracies.append(accuracy)


        mean_accuracy = sum(accuracies) / len(dicts)
        logging.critical('Achieved ' + str(mean_accuracy) + ' on a complete weissman experiment')
        logging.critical('On the vocab file: ' + str(vocab_file))

