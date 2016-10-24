import glob
import os
import csv
import numpy as np
import collections
from SIFT3D.python.settings import Constants
import logging
logging.basicConfig(level=Constants.LOGGING_LEVEL)
from sklearn import svm, neighbors
from sklearn.model_selection import train_test_split
from sklearn.decomposition import PCA
import matplotlib.pyplot as plt

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
    if "wave" in file_name:
        return Constants.WEISSMAN_WAVE_LABEL
    return -1

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
        # as some short videos might have less than 200 descriptors
        times = min(len(xi), 200)
    else:
        # len(xi) is the number of descriptors we found in a file: they all have the same label
        times = len(xi)
    for i in range(0, times):
        y.append(yi)
    return X, y

def pca_plot(X, y):
    pca = PCA(n_components=2)
    logging.info("pca_plot: Computing PCA.")
    X_pca = pca.fit_transform(X, y=y)
    print(X.shape)
    print(X_pca.shape)
    # use y to infer the color/labels
    colors = [int(i % 7) for i in y]
    plt.scatter(X_pca[:,0], X_pca[:,1], c=colors)
    plt.show()


def create_model(X, y):
    X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2)
    logging.info("Training the model")
    #model = svm.SVC().fit(X_train, y_train)
    model = neighbors.KNeighborsClassifier(15).fit(X_train, y_train)
    accuracy = model.score(X_test, y_test)
    logging.info("Achieved " + str(accuracy) + " score.")
    return model

# TODO: refactor this
def majority_voting(model):
    os.chdir(Constants.DESCRIPTORS_DIR + "weissman-yash/test")
    yeah = 0
    noes = 0
    for file in glob.glob("*.csv"):
        X = []
        y = []
        X, y_actual = load_samples_from_file(file, X, y)
        X = np.array(X).astype(np.float32)  # scikit-learn requires this
        y_actual = np.array(y).astype(np.int32)
        # can take just any one label: let's take the first
        actual_label = y_actual[0]
        y_predicted = model.predict(X)
        # the predicted label for the whole video
        # is the one that is predicted the most times for single descriptors from that video
        max_counts = max(np.bincount(y_predicted))
        print(np.bincount(y_predicted))
        print(actual_label)
        # casting to list has to be done because numpy arrays and lists are handled differently
        predicted_label = list(np.bincount(y_predicted)).index(max_counts)
        if predicted_label == actual_label:
            yeah += 1
        else:
            noes += 1
    return yeah, noes

def descriptor_matching():
    logging.info("Loading descriptors from " + Constants.DESCRIPTORS_DIR)
    # X: matrix of sample data. At this time, each row is a SIFT3D descriptor.
    X = []
    # y: matrix of labels. The .csv files don't have these, so we infer them from the file name.
    y = []
    os.chdir(Constants.DESCRIPTORS_DIR + "weissman-yash/train/")
    for file in glob.glob("*.csv"):
        X, y = load_samples_from_file(file, X, y)
    X = np.array(X).astype(np.float32) # scikit-learn requires this
    y = np.array(y).astype(np.int32)
    logging.info("Loaded " + str(len(X)) + " descriptors.")
    # if this fails, then something went wrong with the loading and labeling
    print(X.shape)
    print(y.shape)
    assert len(X) == len(y)
    if Constants.SHOW_PLOTS == True:
        pca_plot(X, y)
    model = create_model(X, y)
    yeah, noes = majority_voting(model)
    logging.info("By majority voting: " +str(yeah)+ " correct predictions, "+str(noes)+" wrong predictions.")

if __name__ == "__main__":
    descriptor_matching()
