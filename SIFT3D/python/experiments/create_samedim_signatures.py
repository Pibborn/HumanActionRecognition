from SIFT3D.python.videodescription import vocab_creation
from SIFT3D.python.utils.utils import Constants
import os
import itertools
import logging

if __name__ == '__main__':
    word_sizes = [50, 100, 250, 500, 750, 1000, 1250, 1500, 1750, 2000]
    octaves = [0, 1, 2, 3]
    for word_size in word_sizes:
        for octave in octaves:
            logging.info('Extraction: word size ' + str(word_size) + ' octave ' + str(octave))
            vocab_creation.generate_vocabulary_with_pruning(Constants.BBRISTER_DATASET_DIR,
                        Constants.FEATURES_DIR + os.path.join('weissman-angles-2', ''), word_size, octave=octave)
