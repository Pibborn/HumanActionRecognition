from sklearn.svm import LinearSVC

from SIFT3D.python.matching import vocab_matching
from SIFT3D.python.videodescription import vocab_creation
from SIFT3D.python.utils.utils import Constants

import os

if __name__ == '__main__':
    bbrister_path = os.path.join(Constants.DESCRIPTORS_DIR, 'weissman-angles')
    vocab_2d_path = os.path.join(Constants.DATA_DIR, 'vocabs', 'bbrister-angles')

    model = LinearSVC()
    dicts, y = vocab_creation.load_vocab(os.path.join(Constants.DATA_DIR, 'vocabs', 'bbrister-angles', ''),
                                         Constants.WEISSMAN_DATASET_DIR, 250)

    vocab_matching.vocab_experiment_multiple_times(dicts, y, model, 90)

