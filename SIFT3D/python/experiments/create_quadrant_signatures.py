from SIFT3D.python.videodescription import vocab_creation
from SIFT3D.python.utils.utils import Constants
import os
import itertools
import logging

if __name__ == '__main__':
    quadrants = ['x', 'y', 'z']
    for quadrant in quadrants:
        num_quadrants_list = [2, 8]
        word_sizes = [5, 50, 100, 250, 500, 750, 1000, 1250, 1500]
        parameter_tuple_list = list(itertools.product(word_sizes, num_quadrants_list))
        logging.info('Extracting 2D video signatures with the following parameters:')
        logging.info(str(parameter_tuple_list))
        for parameter_tuple in parameter_tuple_list:
            word_size = parameter_tuple[0]
            num_quadrants = parameter_tuple[1]
            logging.info('Extraction: word size ' + str(word_size) +
                         ' quadrant: ' + quadrant + ' num_quadrants ' + str(num_quadrants))
            vocab_creation.generate_vocabulary_2d_quadrants(Constants.BBRISTER_DATASET_DIR,
                                                  Constants.FEATURES_DIR + os.path.join('weissman-angles', ''),
                                                  word_size, num_quadrants, quadrant=quadrant)