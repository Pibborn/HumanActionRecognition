import os
import logging

class Constants:
    # these values should be changed as you find useful
    MATLAB_EXECUTABLE = '/Applications/MATLAB_R2016a.app/bin/matlab'
    ROOT_DIR = os.path.abspath("../../") + "/"
    MATLAB_CODE_DIR = ROOT_DIR + "SIFT3D/Matlab/"
    PYTHON_CODE_DIR = ROOT_DIR + "SIFT3D/python/"
    DATA_DIR = ROOT_DIR + os.path.expanduser("./SIFT3D/data/")
    VIDEO_DIR = DATA_DIR + "videos/"
    CSV_DIR = DATA_DIR + "csv/"
    FEATURES_DIR = DATA_DIR + "features/"
    DESCRIPTORS_DIR = DATA_DIR + "descriptors/"
    RESULT_DIR = DATA_DIR + "results/"
    LOGGING_LEVEL = logging.INFO