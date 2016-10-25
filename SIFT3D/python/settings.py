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
    KTH_DATASET_DIR = DESCRIPTORS_DIR + "kth-yash/"
    BOXING_LABEL = 0
    RUNNING_LABEL = 1
    JOGGING_LABEL = 2
    WALKING_LABEL = 3
    HANDCLAPPING_LABEL = 4
    HANDWAVING_LABEL = 5
    SHOW_PLOTS = False
    TAKE_TOP_200 = True
    WEISSMAN_DATASET_DIR = DESCRIPTORS_DIR + "weissman-yash/"
    WEISSMAN_WAVE1_LABEL = 0
    WEISSMAN_WAVE2_LABEL = 1
    WEISSMAN_WALK_LABEL = 2
    SKIP_LABEL = 3
    SIDE_LABEL = 4
    WEISSMAN_RUN_LABEL = 5
    JUMP_LABEL = 6
    PJUMP_LABEL = 7
    JACK_LABEL = 8
    BEND_LABEL = 9