import glob
import random

from sklearn import svm
from sklearn.decomposition import PCA
from sklearn.model_selection import GridSearchCV
from SIFT3D.python.settings import Constants
import csv
import numpy as np
import logging
logging.basicConfig(level=Constants.LOGGING_LEVEL)

def load_samples_from_file(file_name, X, y):
    csvReader = csv.reader(open(file_name, "r"))
    xi = list(csvReader)
    # xi looks like this: [[0,1,2],[4,5,6],[7,8,9]] where [0,1,2] is data from the first descriptor
    # we don't want multiple list levels in X, so we do as follows
    for i in range(0, len(xi)):
        X.append(xi[i])
        # only take the top 200 descriptors; this can be changed in the settings file
        if Constants.TAKE_TOP_200 == True and i == 199:
            break
    yi = infer_label(file_name)
    if Constants.TAKE_TOP_200 == True:
        # if we want to only take the top 200 descriptors, we also must take care not to get out of bounds
        # on yi in the next for loop, as some short videos might have less than 200 descriptors
        times = min(len(xi), 200)
    else:
        # len(xi) is the number of descriptors we found in a file: they all have the same label
        times = len(xi)
    for i in range(0, times):
        y.append(yi)
    return X, y

def load_descriptors_and_features(des_file_name, feature_file_name, X, F, y):
    des_reader = csv.reader(open(des_file_name, "r"))
    feature_reader = csv.reader(open(feature_file_name, "r"))
    xi = list(des_reader)
    fi = list(feature_reader)
    # xi looks like this: [[0,1,2],[4,5,6],[7,8,9]] where [0,1,2] is data from the first descriptor
    # we don't want multiple list levels in X, so we do as follows
    for i in range(0, len(xi)):
        X.append(xi[i])
        F.append(fi[i])
        # only take the top 200 descriptors; this can be changed in the settings file
        if Constants.TAKE_TOP_200 == True and i == 199:
            break
    yi = infer_label(des_file_name)
    if Constants.TAKE_TOP_200 == True:
        # if we want to only take the top 200 descriptors, we also must take care not to get out of bounds
        # on yi in the next for loop, as some short videos might have less than 200 descriptors
        times = min(len(xi), 200)
    else:
        # len(xi) is the number of descriptors we found in a file: they all have the same label
        times = len(xi)
    for i in range(0, times):
        y.append(yi)
    return X, F, y

def load_samples_from_file_same_dim(file_name, feature_file_name, X, F, y, octave, scale, matchScale = False):
    descriptor_reader = csv.reader(open(file_name, "r"))
    xi = list(descriptor_reader)
    feature_reader = csv.reader(open(feature_file_name, "r"))
    fi = list(feature_reader)
    # xi looks like this: [[0,1,2],[4,5,6],[7,8,9]] where [0,1,2] is data from the first descriptor
    # we don't want multiple list levels in X, so we do as follows
    for i in range(0, len(xi)):
        f = fi[i]
        # checking that the descriptor was extracted in a certain point in the scale space
        if matchScale:
            if int(f[6]) == octave and float(f[7]) == scale:
                X.append(xi[i])
                F.append(fi[i])
        else:
            if int(f[6]) == octave:
                X.append(xi[i])
                F.append(fi[i])
    yi = infer_label(file_name)
    if Constants.TAKE_TOP_200 == True:
        # if we want to only take the top 200 descriptors, we also must take care not to get out of bounds
        # on yi in the next for loop, as some short videos might have less than 200 descriptors
        times = min(len(xi), 200)
    else:
        # len(xi) is the number of descriptors we found in a file: they all have the same label
        times = len(xi)
    for i in range(0, times):
        y.append(yi)
    return X, F, y

def split_train_test_videos(folder, num_testing_videos):
    test_videos = []
    train_videos = []
    for file in glob.glob(folder + "/*.csv"):
        train_videos.append(file)
    r = random.Random()
    for i in range(0, num_testing_videos):
        rand_video_id = r.randint(0, len(train_videos)-1)
        test_videos.append(train_videos[rand_video_id])
        del train_videos[rand_video_id]
    return train_videos, test_videos

def load_descriptors(video_list):
    # X: matrix of sample data. At this time, each row is a SIFT3D descriptor.
    X = []
    # y: matrix of labels. The .csv files don't have these, so we infer them from the file name.
    y = []
    for file in video_list:
        X, y = load_samples_from_file(file, X, y)
    X = np.array(X).astype(np.float32) # scikit-learn requires this
    y = np.array(y).astype(np.int32)
    logging.info("Loaded " + str(len(X)) + " descriptors.")
    # if this fails, then something went wrong with the loading and labeling
    assert len(X) == len(y)
    if Constants.SHOW_PLOTS == True:
        pca_plot(X, y)
    return X, y

def infer_label(file_name):
    file_name = file_name
    if "boxing" in file_name:
        return Constants.BOXING_LABEL
    if "running" in file_name:
        return Constants.RUNNING_LABEL
    if "jogging" in file_name:
        return Constants.JOGGING_LABEL
    if "walking" in file_name:
        return Constants.WALKING_LABEL
    if "handclapping" in file_name:
        return Constants.HANDCLAPPING_LABEL
    if "handwaving" in file_name:
        return Constants.HANDWAVING_LABEL
    if "bend" in file_name:
        return Constants.BEND_LABEL
    if "jack" in file_name:
        return Constants.JACK_LABEL
    # it is important that this check comes before the 'jump' one
    if "pjump" in file_name:
        return Constants.PJUMP_LABEL
    if "jump" in file_name:
        return Constants.JUMP_LABEL
    if "run" in file_name:
        return Constants.WEISSMAN_RUN_LABEL
    if "side" in file_name:
        return Constants.SIDE_LABEL
    if "skip" in file_name:
        return Constants.SKIP_LABEL
    if "walk" in file_name:
        return Constants.WEISSMAN_WALK_LABEL
    if "wave1" in file_name:
        return Constants.WEISSMAN_WAVE1_LABEL
    if "wave2" in file_name:
        return Constants.WEISSMAN_WAVE2_LABEL
    return -1

# TODO: This probably has to be moved somewhere else, but ATM is just a bad function
def estimate_hyperparameters(X, y):

    parameters = [
        {'C': np.logspace(-8, 5, num=14, base=10)},
        #{'n_neighbors' : range(1, 20)},
        #{'weights': ['uniform', 'distance']}
    ]

    param_grid = [
        {'C': np.logspace(-20, 2, num=23, base=10), 'kernel': ['linear']},
        {'C': np.logspace(-20, 2, num=23, base=10), 'gamma': [0.001, 0.0001], 'kernel': ['rbf']},
    ]

    #clf = GridSearchCV(svm.SVC(C=1, kernel='sigmoid', gamma=0.01), parameters, cv=5, scoring='accuracy', verbose=0)
    clf = GridSearchCV(svm.SVC(C=1), param_grid, cv=2, scoring='accuracy', verbose=0)
    #clf = GridSearchCV(neighbors.KNeighborsClassifier(n_neighbors=1, weights='uniform', n_jobs=-1, algorithm='ball_tree'),
    #                   parameters, cv=5, scoring='accuracy', verbose=2)
    clf.fit(X, y)
    print(clf.best_params_)
    return clf.best_params_

