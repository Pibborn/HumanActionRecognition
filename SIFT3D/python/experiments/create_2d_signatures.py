from SIFT3D.python.videodescription import vocab_creation
from SIFT3D.python.utils.utils import Constants
import os
import itertools
import logging

if __name__ == '__main__':
    angle_sizes = [5, 10, 20, 30, 40, 50]
    word_sizes = [5, 100, 250, 500]
    parameter_tuple_list = list(itertools.product(word_sizes, angle_sizes))
    logging.info('Extracting 2D video signatures with the following parameters:')
    logging.info(str(parameter_tuple_list))
    for parameter_tuple in parameter_tuple_list:
        word_size = parameter_tuple[0]
        angle_size = parameter_tuple[1]
        logging.info('Extraction: word size ' + str(word_size) + ' angle size ' + str(angle_size))
        vocab_creation.generate_vocabulary_2d(Constants.BBRISTER_DATASET_DIR,
           Constants.FEATURES_DIR + os.path.join('weissman-angles', ''), word_size, angle_size)