import os
import logging

class Constants:
    # these values should be changed as you find useful
    MATLAB_EXECUTABLE = '/Applications/MATLAB_R2016a.app/bin/matlab'
    ROOT_DIR = '/Users/mattia/Documents/uni/tesi/ActionRecognition/'
    MATLAB_CODE_DIR = ROOT_DIR + "SIFT3D/Matlab/"
    PYTHON_CODE_DIR = ROOT_DIR + "SIFT3D/python/"
    DATA_DIR = ROOT_DIR + "SIFT3D/data/"
    VIDEO_DIR = DATA_DIR + "videos/"
    CSV_DIR = DATA_DIR + "csv/"
    FEATURES_DIR = DATA_DIR + "features/"
    DESCRIPTORS_DIR = DATA_DIR + "descriptors/"
    RESULT_DIR = DATA_DIR + "results/"
    LOGGING_LEVEL = logging.INFO
    BOXING_LABEL = 0
    RUNNING_LABEL = 1
    JOGGING_LABEL = 2
    WALKING_LABEL = 3
    HANDCLAPPING_LABEL = 4
    HANDWAVING_LABEL = 5
    SHOW_PLOTS = True