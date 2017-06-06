import csv
import glob
import itertools
import logging
import operator

import numpy as np
import sys
from sklearn.cluster import KMeans

from SIFT3D.python.matching import matching_experiments as match
from SIFT3D.python.utils.utils import Constants, infer_label, load_samples_from_file, load_descriptors_and_features, \
    load_samples_from_file_same_dim

DUMP_TO_FILE = True

def generate_vocabulary(dataset_path, size, model=None):
    # set up output variables
    y = []
    X = list()
    num_des_list = list() # list that mantains the number of descriptors in each video

    # set up clustering model
    if (model == None):
        model = KMeans(n_clusters=size, tol=1e-2)

    descriptor_file_list = glob.glob(dataset_path + '*descriptors.csv')
    logging.info('Loaded ' + str(len(descriptor_file_list)) + ' descriptors files for vocabulary generation.')

    _ = []
    for descriptor_file in descriptor_file_list:
        prev_X_len = len(X)
        X, _ = load_samples_from_file(descriptor_file, X, _)

        yi = infer_label(descriptor_file)
        y.append(yi)

        num_des_list.append(len(X) - prev_X_len)

    # cluster the data, and get labels
    labels = model.fit_predict(X)
    #labels = model.predict(X)
    logging.info('Done clustering.')

    num_labels = len(set(labels)) # figure out the number of unique labels
    video_dicts = [[]]
    video_dicts[0] = [0 for _ in range(0, num_labels)]
    k = 0 # iterates on the number of videos
    j = 0 # iterates on the number of descriptors

    for i in range(0, len(labels)):
        video_dicts[k][labels[i]] += 1

        if j == num_des_list[k]:
            j = 0
            k += 1
            video_dicts.append([0 for _ in range(0, num_labels)])

        j += 1

    if DUMP_TO_FILE == True:
        f = open(Constants.DATA_DIR + '/vocabs/scovanner/python/kmeans-eucl-py-yash-'+str(size)+'.csv', 'w')
        writer = csv.writer(f)
        for dict in video_dicts:
            writer.writerow(dict)

    return video_dicts, y

def generate_ngram_vocab(dataset_path, feature_path, size, model=None, n=2, ngram_strategy='naive', window_size=3):
    # set up output variables
    y = []
    X = list()
    num_des_list = list()  # list that mantains the number of descriptors in each video

    # set up clustering model
    if (model == None):
        model = KMeans(n_clusters=size, tol=1e-2)

    descriptor_file_list = glob.glob(dataset_path + '*descriptors.csv')
    feature_file_list = glob.glob(feature_path + '*features.csv')
    logging.info('Loaded ' + str(len(descriptor_file_list)) + ' files for vocab generation.')

    _ = []
    i = 0
    X_temp = []
    F_temp = []
    for descriptor_file in descriptor_file_list:
        feature_file = feature_file_list[i]
        prev_X_len = len(X)
        X_temp, F_temp, _ = load_descriptors_and_features(descriptor_file, feature_file, X_temp, F_temp, _)

        yi = infer_label(descriptor_file)
        y.append(yi)

        for j in range(0, len(X_temp)):
            F_temp[j].extend(X_temp[j])

        F_temp.sort(key = lambda f: int(f[2]))

        #for fi in F_temp:
        #   del fi[:3]

        X.extend(F_temp)

        num_des_list.append(len(X) - prev_X_len)
        i += 1
        X_temp = []
        F_temp = []

    num_des_list[-1] -= (n + 1)

    # cluster the data, and get labels
    labels = model.fit_predict([xi[:3] for xi in X])
    logging.info('Done clustering.')

    j = 0 # iterates on the number of descriptors in a video
    k = 0 # iterates on the number of videos
    ngram_index_string = ''
    video_dicts = []
    ngram_dict = init_ngram_dict(size, n)
    empty_ngram_dict = ngram_dict

    for des_i in range(0, len(labels) - n):
        xi = X[des_i]
        xi_t = int(xi[2])

        ngram_index_string = str(labels[des_i]) + '-'

        if ngram_strategy == 'naive':
            for ngram_i in range(1, n):
                ngram_index_string += str(labels[des_i + ngram_i]) + '-'

            if ngram_index_string in ngram_dict:
                ngram_dict[str(ngram_index_string)] += 1
            else:
                ngram_dict[str(ngram_index_string)] = 1

        if ngram_strategy == 'window':
            if n != 2:
                logging.error('Unsupported strategy for n > 2')
                return
            for w in range(des_i + 1, len(labels) - n):
                ngram_index_string = str(labels[des_i]) + '-'
                xw = X[w]
                xw_t = int(xw[2])
                if abs(xi_t - xw_t) > window_size:
                    break
                ngram_index_string += str(labels[w]) + '-'

                if ngram_index_string in ngram_dict:
                    ngram_dict[str(ngram_index_string)] += 1
                else:
                    ngram_dict[str(ngram_index_string)] = 1

        if j == num_des_list[k]:
            j = 0
            k += 1
            ngram_dict = sorted(ngram_dict.items(), key=operator.itemgetter(0))
            #print(ngram_dict)
            ngram_dict = [num_word_occurrences for (key, num_word_occurrences) in ngram_dict]
            if len(ngram_dict) < np.power(size, n):
                ngram_dict.extend([0 for i in range(0, np.power(size, n) - len(ngram_dict))])
            video_dicts.append(ngram_dict)
            ngram_dict = empty_ngram_dict.copy()

        j += 1

    if DUMP_TO_FILE == True:
         f = open(Constants.DATA_DIR + '/vocabs/bbrister-ngrams/bbrister-window-'+str(size)+'-ngram'+str(n)+'.csv', 'w')
         writer = csv.writer(f)
         for dict in video_dicts:
             writer.writerow(dict)

    return video_dicts, y

def init_ngram_dict(n_clusters, ngram_length):
    ngram_list =  list(itertools.product(range(n_clusters), repeat=ngram_length))
    ngram_dict = dict()
    for i in range(0, len(ngram_list)):
        ngram_key_string = ''
        for j in range(0, ngram_length):
            ngram_key_string += str(ngram_list[i][j]) + '-'
        ngram_dict[ngram_key_string] = 0
    return ngram_dict


def generate_vocabulary_with_pruning(dataset_path, features_path, size, model=None,
                                     scale=1.6, octave=0, same_scale=False):
    # set up output variables
    y = []
    X = list()
    num_des_list = list() # list that mantains the number of descriptors in each video

    # set up clustering model
    if (model == None):
        model = KMeans(n_clusters=size, tol=1e-2)

    descriptor_file_list = glob.glob(dataset_path + '*descriptors.csv')
    feature_file_list = glob.glob(features_path + '*features.csv')
    logging.info('Loaded ' + str(len(descriptor_file_list)) + ' descriptors files for vocabulary generation.')
    logging.info('Loaded ' + str(len(feature_file_list)) + ' features files for vocabulary generation.')

    i = 0
    F = []
    X = []
    y = []
    for descriptor_file in descriptor_file_list:
        feature_file = feature_file_list[i]
        prev_X_len = len(X)
        X, F, y = load_samples_from_file_same_dim(descriptor_file, feature_file, X, F, y, octave, scale)
        yi = infer_label(descriptor_file)
        y.append(yi)
        num_des_list.append(len(X) - prev_X_len)
        i += 1

    logging.info('Loaded ' + str(len(X)) + ' descriptors after octave/scale pruning')

    # cluster the data, and get labels
    model.fit(X)
    labels = model.predict(X)
    logging.info('Done clustering.')

    num_labels = len(set(labels)) # figure out the number of unique labels
    video_dicts = [[]]
    video_dicts[0] = [0 for _ in range(0, num_labels)]
    k = 0 # iterates on the number of videos
    j = 0 # iterates on the number of descriptors

    fi = open(Constants.DATA_DIR + '/vocabs/bbrister-samedim/bbrister-samedim-octave' +
             str(octave) + '-size-' + str(size) + '.csv',
             'w')
    writer = csv.writer(fi)

    for i in range(0, len(labels)):
        video_dicts[k][labels[i]] += 1

        if j == num_des_list[k] - 1:
            j = 0
            k += 1
            video_dicts.append([0 for _ in range(0, num_labels)])
            if DUMP_TO_FILE:
                writer.writerow(video_dicts[k-1])
        else:
            j += 1

    return video_dicts, y

def generate_vocabulary_2d(dataset_path, features_path, size_words, size_angles, model=None, vocabs_path=None):
    feature_file_list = glob.glob(features_path + '*features.csv')
    descriptor_file_list = glob.glob(dataset_path + '*descriptors.csv')
    logging.info('Loaded ' + str(len(descriptor_file_list)) + ' descriptors files for vocabulary generation.')
    logging.info('Loaded ' + str(len(feature_file_list)) + ' features files for vocabulary generation.')

    i = 0
    F = []
    X = []
    y = []
    num_des_list = []

    # load descriptors, features and true video labels
    for feature_file in feature_file_list:
        prev_X_len = len(X)
        descriptor_file = descriptor_file_list[i]
        X, F, y  = load_descriptors_and_features(descriptor_file, feature_file, X, F, y)
        yi = infer_label(descriptor_file)
        y.append(yi)
        num_des_list.append(len(X) - prev_X_len)
        i += 1

    assert len(X) == len(F)

    # perform clustering on descriptors
    logging.info('Clustering descriptors...')
    if model == None:
        model = KMeans(n_clusters=size_words)
    word_labels = model.fit_predict(X)

    # perform clustering on angles
    logging.info('Clustering angles...')
    F = np.array(F)
    model = KMeans(n_clusters=size_angles)
    # only take the angles' values
    angle_labels = model.fit_predict(F[:, 3:6])

    logging.info('Building 2d signatures...')
    video_2d_dict = np.zeros((size_words, size_angles), dtype=np.int)
    video_dicts = []
    f = open(Constants.DATA_DIR + '/vocabs/bbrister-angles/bbrister-angles-' +
            str(size_angles) + '-size-' + str(size_words) + '.csv',
             'w')
    writer = csv.writer(f)
    j = 0
    k = 0
    for i in range(0, len(word_labels)):
        video_2d_dict[word_labels[i]][angle_labels[i]] += 1

        if j == num_des_list[k] - 1:
            j = 0
            k += 1
            video_dicts.append(video_2d_dict)
            if DUMP_TO_FILE == True:
                writer.writerow(video_2d_dict.flatten())
            video_2d_dict = np.zeros((size_words, size_angles), dtype=np.int)
        else:
            j += 1

    return video_dicts, y


def get_angle_quadrant_label(x, y, z, size_angles, quadrant):
    angle_label = []
    if size_angles == 2:
        if quadrant == 'x':
            if x > 0:
                angle_label = 0
            else:
                angle_label = 1
        if quadrant == 'y':
            if y > 0:
                angle_label = 0
            else:
                angle_label = 1
        if quadrant == 'z':
            if z > 0:
                angle_label = 0
            else:
                angle_label = 1
    else:
        if size_angles == 8:
            if x > 0 and y > 0 and z > 0:
                angle_label = 0
            if x < 0 and y > 0 and z > 0:
                angle_label = 1
            if x > 0 and y < 0 and z > 0:
                angle_label = 2
            if x > 0 and y > 0 and z < 0:
                angle_label = 3
            if x < 0 and y < 0 and z > 0:
                angle_label = 4
            if x > 0 and y < 0 and z < 0:
                angle_label = 5
            if x < 0 and y > 0 and z < 0:
                angle_label = 6
            if x < 0 and y < 0 and z < 0:
                angle_label = 7
        else:
            logging.error('Unsupported size_angles parameter')
            sys.exit()
    return angle_label




def generate_vocabulary_2d_quadrants(dataset_path, features_path, size_words, size_angles,
                                     model=None, vocabs_path=None, quadrant='x'):
    # input checking
    if size_angles != 2 and size_angles != 8:
        logging.error('Unsupported number of quadrants')
        sys.exit()
    if size_angles == 2 and quadrant != 'x' and quadrant != 'y' and quadrant != 'z':
        logging.error('2 quadrants case: unsupported \'quadrant\' parameter')
        sys.exit()

    feature_file_list = glob.glob(features_path + '*features.csv')
    descriptor_file_list = glob.glob(dataset_path + '*descriptors.csv')
    logging.info('Loaded ' + str(len(descriptor_file_list)) + ' descriptors files for vocabulary generation.')
    logging.info('Loaded ' + str(len(feature_file_list)) + ' features files for vocabulary generation.')

    i = 0
    F = []
    X = []
    y = []
    num_des_list = []

    # load descriptors, features and true video labels
    for feature_file in feature_file_list:
        prev_X_len = len(X)
        descriptor_file = descriptor_file_list[i]
        X, F, y = load_descriptors_and_features(descriptor_file, feature_file, X, F, y)
        yi = infer_label(descriptor_file)
        y.append(yi)
        num_des_list.append(len(X) - prev_X_len)
        i += 1

    assert len(X) == len(F)

    # perform clustering on descriptors
    logging.info('Clustering descriptors...')
    if model == None:
        model = KMeans(n_clusters=size_words)
    word_labels = model.fit_predict(X)

    # perform quadrant checking on angles
    logging.info('Clustering angles...')
    F = np.array(F)[:, 3:6]
    angle_labels = []
    for angle_list in F:
        x = float(angle_list[0])
        y = float(angle_list[1])
        z = float(angle_list[2])
        angle_labels.append(get_angle_quadrant_label(x, y, z, size_angles, quadrant))

    logging.info('Building 2d signatures...')
    video_2d_dict = np.zeros((size_words, size_angles), dtype=np.int)
    video_dicts = []
    if size_angles == 2:
        f = open(Constants.DATA_DIR + '/vocabs/bbrister-quadrants/bbrister-quadrants-'
                 + str(quadrant) + '-' + str(size_angles) + '-size-' + str(size_words) + '.csv',
                 'w')
    if size_angles == 8:
        f = open(Constants.DATA_DIR + '/vocabs/bbrister-quadrants/bbrister-quadrants-'
                 + str(size_angles) + '-size-' + str(size_words) + '.csv',
                 'w')
    writer = csv.writer(f)
    j = 0
    k = 0
    for i in range(0, len(word_labels)):
        video_2d_dict[word_labels[i]][angle_labels[i]] += 1

        if j == num_des_list[k] - 1:
            j = 0
            k += 1
            video_dicts.append(video_2d_dict)
            if DUMP_TO_FILE == True:
                writer.writerow(video_2d_dict.flatten())
            video_2d_dict = np.zeros((size_words, size_angles), dtype=np.int)
        else:
            j += 1

    return video_dicts, y



# load a vocabulary from a file. also infers labels from dataset_path.
# the assumption is that video signatures appear in vocab files in the same
# order as the files appear in dataset_path.
def load_vocab_from_size(vocabs_path, dataset_path, size):
    # get the vocab depending on the size string
    basename = '*-' + str(size) + '*.csv'
    # there should only be a single hit
    vocab_file_list = glob.glob(str(vocabs_path) + '/' + basename)
    try:
        assert len(vocab_file_list) == 1
    except AssertionError:
        logging.error('Something is wrong. The dataset paths are probably wrong, or the basename in '
                      'load_vocab_from_size does not match any vocab .csv file.')
        logging.error('basename: ' + str(vocabs_path) + str(basename))
        logging.error('vocab_file_list: ' + str(vocab_file_list))
        exit()
    vocab_file = open(vocab_file_list[0], 'r')
    reader = csv.reader(vocab_file, delimiter=',')

    des_file_list = glob.glob(dataset_path + '/*descriptors.csv')
    # i will iterate on the files in des_file_list
    i = 0
    y = []
    X = []

    for xi in reader:
        xi = list(map(lambda x: float(x), xi))
        X.append(xi)
        y.append(float(infer_label(des_file_list[i])))
        #print(des_file_list[i])
        i += 1
        #print(xi)
        #print(infer_label(des_file_list[i]))

    #print(y)
    return X, y

def load_vocab_from_path(vocabs_file, dataset_path):
    # there should only be a single hit
    vocab_file_list = glob.glob(str(vocabs_file))
    try:
        assert len(vocab_file_list) == 1
    except AssertionError:
        logging.error('Something is wrong. The dataset paths are probably wrong, or the basename in '
                      'load_vocab_from_path does not match any vocab .csv file.')
        logging.error('basename: ' + str(vocabs_file))
        logging.error('vocab_file_list: ' + str(vocab_file_list))
        exit()
    vocab_file = open(vocab_file_list[0], 'r')
    reader = csv.reader(vocab_file, delimiter=',')

    des_file_list = glob.glob(dataset_path + '/*descriptors.csv')
    # i will iterate on the files in des_file_list
    i = 0
    y = []
    X = []

    for xi in reader:
        xi = list(map(lambda x: float(x), xi))
        X.append(xi)
        y.append(float(infer_label(des_file_list[i])))
        #print(des_file_list[i])
        i += 1
        #print(xi)
        #print(infer_label(des_file_list[i]))

    #print(y)
    return X, y

def load_signatures(signature_path, label_path):
    signature_reader = csv.reader(open(signature_path, 'r'))
    label_reader = csv.reader(open(label_path, 'r'))

    X = []
    y = []

    for xi in signature_reader:
        X.append(xi)

    for yi in label_reader:
        y.append(yi)

    #for i in range(0, len(X)):
    #   print(X[i])
    #    print(y[i])

    return X, y

if __name__ == '__main__':
    generate_vocabulary_2d(Constants.DESCRIPTORS_DIR + '/weissman-angles/', Constants.DATA_DIR + '/features/weissman-angles/',
                         250, 10)
