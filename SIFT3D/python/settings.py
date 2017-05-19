import os.path
import logging
from SIFT3D.python.secrets import Secrets

class Constants:
    # these values should be changed as you find useful
    ROOT_DIR = Secrets.ROOT_DIR
    MATLAB_CODE_DIR = os.path.join(ROOT_DIR, 'SIFT3D', 'Matlab', '')
    PYTHON_CODE_DIR = os.path.join(ROOT_DIR, 'SIFT3D', 'python', '')
    DATA_DIR = os.path.join(ROOT_DIR, 'SIFT3D', 'data', '')
    VIDEO_DIR = os.path.join(DATA_DIR, 'videos', '')
    CSV_DIR = os.path.join(DATA_DIR, 'csv', '')
    FEATURES_DIR = os.path.join(DATA_DIR, 'features', '')
    DESCRIPTORS_DIR = os.path.join(DATA_DIR, 'descriptors', '')
    RESULT_DIR = os.path.join(DATA_DIR, 'results', '')
    LOGGING_LEVEL = logging.CRITICAL
    KTH_DATASET_DIR = os.path.join(DESCRIPTORS_DIR, 'kth-yash', '')
    BOXING_LABEL = 0
    RUNNING_LABEL = 1
    JOGGING_LABEL = 2
    WALKING_LABEL = 3
    HANDCLAPPING_LABEL = 4
    HANDWAVING_LABEL = 5
    SHOW_PLOTS = False
    TAKE_TOP_200 = False
    WEISSMAN_DATASET_DIR = os.path.join(DESCRIPTORS_DIR, 'weissman-yash', '')
    BBRISTER_DATASET_DIR = os.path.join(DESCRIPTORS_DIR, 'bbrister', '')
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
    WEISSMAN_LABEL_NUM = 10
    DATASETS = ['kth', 'weissman', 'bbrister']
    DATASETS_DIRS = [KTH_DATASET_DIR, WEISSMAN_DATASET_DIR, BBRISTER_DATASET_DIR]