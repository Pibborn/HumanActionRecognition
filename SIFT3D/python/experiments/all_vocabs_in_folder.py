from sklearn.metrics import confusion_matrix
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
import matplotlib.pyplot as plt
import matplotlib.cm as cm
import pylab

if __name__ == '__main__':
    bbrister_path = os.path.join(Constants.DESCRIPTORS_DIR, 'weissman-angles', '')
    vocab_2d_path = os.path.join(Constants.DATA_DIR, 'vocabs', 'bbrister-samedim', '')

    vocab_file_list = glob.glob(vocab_2d_path + '*.csv')
    model = LinearSVC()
    #model = SVC(kernel='poly', gamma=1e-4)

    word_sizes = []
    angle_sizes = []
    mean_accuracies = []
    confusion_matrices = []

    for vocab_file in vocab_file_list:
        dicts, y = vocab_creation.load_vocab_from_path(vocab_file, Constants.WEISSMAN_DATASET_DIR)

        # try to infer the number of words and number of angles from the video file name
        # drop everything but what is after the last '/' (or '\' in windows)
        filename = vocab_file.split(os.sep)[-1:]
        # the regex means: look for numbers after hyphens (i.e. '-')
        numbers_in_path = re.findall('(?<=-)\d+', str(filename))

        word_size = 0
        angle_size = 0
        # in this case, the signatures are 1d, word clusters only
        if len(numbers_in_path) == 1:
            word_size = int(numbers_in_path[0])
        else:
            # 2d signature: angle size comes first
            if len(numbers_in_path) == 2:
                angle_size = int(numbers_in_path[0])
                word_size = int(numbers_in_path[1])
            else:
                logging.critical('Vocab file did not match word/angle size regex: ' + str(vocab_file))
                logging.critical('numbers_in_path: '+str(numbers_in_path))
                exit()

        accuracies = []
        y_true_list = []
        y_pred_list = []
        for i in range(0, len(dicts)):
            X_train = dicts[:i] + dicts[i+1:len(dicts)]
            y_train = y[:i] + y[i + 1:len(dicts)]
            X_test = dicts[i]
            y_test = [y[i]]
            accuracy, _, y_pred = vocab_matching.vocab_experiment_folds(X_train,
                                y_train, X_test, y_test, model, preprocess=True)
            y_true_list.append(y_test)
            y_pred_list.append(y_pred)
            accuracies.append(accuracy)

        confusion_matrices.append(confusion_matrix(y_true_list, y_pred_list))

        mean_accuracy = sum(accuracies) / len(dicts)
        logging.critical('Achieved ' + str(mean_accuracy) + ' on a complete weissman experiment')
        logging.critical('On the vocab file: ' + str(vocab_file))

        mean_accuracies.append(mean_accuracy)
        word_sizes.append(word_size)
        angle_sizes.append(angle_size)

    # plot the accuracies depending on the signature parameters
    fig, ax = plt.subplots()

    # 1d signatures: a line plot is fine
    if angle_sizes[0] == 0:
        mean_accuracies = [x for y, x in sorted(zip(word_sizes, mean_accuracies))]
        word_sizes.sort()
        plt.plot(word_sizes, mean_accuracies, linestyle='--', marker='o', color='b')
        plt.xticks(word_sizes)
        plt.grid()
        plt.show()
    # 2d signatures: checkerboard-like plot
    else:
        mean_accuracy_matrix = np.zeros((len(set(word_sizes)), len(set(angle_sizes))))
        word_idx_list = sorted(set(word_sizes))
        angle_idx_list = sorted(set(angle_sizes))
        for i in range(0, len(mean_accuracies)):
            # I am sorry
            mean_accuracy_matrix[word_idx_list.index(word_sizes[i])][angle_idx_list.index(angle_sizes[i])] = mean_accuracies[i]
        img = ax.imshow(mean_accuracy_matrix, cmap=cm.jet, interpolation='nearest')
        plt.xticks(range(len(angle_idx_list)), angle_idx_list, fontsize=14)
        plt.yticks(range(len(word_idx_list)), word_idx_list, fontsize=14)
        fig.colorbar(img)
        pylab.savefig(os.path.join('.', ))
        #plt.show()

    # plot the confusion matrices
    k = 0 # iterates on video_list
    for confusion_matrix in confusion_matrices:
        norm_confusion_matrix = []
        for i in confusion_matrix:
            a = 0
            tmp_arr = []
            a = sum(i, 0)
            for j in i:
                tmp_arr.append(float(j) / float(a))
            norm_confusion_matrix.append(tmp_arr)

        fig = plt.figure()
        plt.clf()
        ax = fig.add_subplot(111)
        ax.set_aspect(1)
        img = ax.imshow(np.array(norm_confusion_matrix), cmap=cm.jet,
                        interpolation='nearest')
        #plt.show()

        # put absolute values in the cells
        width, height = confusion_matrix.shape

        for x in range(width):
            for y in range(height):
                ax.annotate(str(confusion_matrix[x][y]), xy=(y, x),
                            horizontalalignment='center',
                            verticalalignment='center')

        # annotate the axes with the weissman labels
        cb = fig.colorbar(img)
        label_list = ['wave1', 'wave2', 'walk', 'skip', 'side', 'run', 'jump', 'pjump', 'jack', 'bend']
        plt.xticks(range(width), label_list)
        plt.yticks(range(height), label_list)

        # save the figure
        pylab.savefig(os.path.join('.', 'confusion_matrices',
                                   str(vocab_file_list[k].split(os.sep)[-1] + '.pdf')), format='pdf')
        k += 1




