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
import re
import numpy as np

if __name__ == '__main__':
    bbrister_path = os.path.join(Constants.DESCRIPTORS_DIR, 'weissman-angles', '')
    vocab_2d_path = os.path.join(Constants.DATA_DIR, 'vocabs', 'bbrister-angles', '')

    vocab_file_list = glob.glob(vocab_2d_path + '*.csv')
    model = LinearSVC()
    #model = SVC(kernel='poly', gamma=1e-4)

    word_sizes = []
    angle_sizes = []
    mean_accuracies = []

    for vocab_file in vocab_file_list:
        dicts, y = vocab_creation.load_vocab_from_path(vocab_file,
                                                       Constants.WEISSMAN_DATASET_DIR)

        # try to infer the number of words and number of angles from the video file name
        # drop everything but what is after the last '/' (or '\' in windows)
        filename = vocab_file.split(os.sep)[-1:]
        # the regex means: look for numbers after hyphens (i.e. '-')
        numbers_in_path = re.findall('(?<=-)\d+', str(filename))

        word_size = 0
        angle_size = 0
        # in this case, the signatures are 1d, word clusters only
        if len(numbers_in_path) == 1:
            word_size = numbers_in_path[0]
        else:
            # 2d signature: angle size comes first
            if len(numbers_in_path) == 2:
                angle_size = numbers_in_path[0]
                word_size = numbers_in_path[1]
            else:
                logging.critical('Vocab file did not match word/angle size regex: ' + str(vocab_file))
                logging.critical('numbers_in_path: '+str(numbers_in_path))
                exit()
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

        mean_accuracies.append(mean_accuracy)
        word_sizes.append(word_size)
        angle_sizes.append(angle_size)



