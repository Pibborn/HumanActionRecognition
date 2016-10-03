import os
import logging

class Constants:
    # these values should be changed as you find useful
    DATA_DIR = os.path.expanduser("~/")
    VIDEO_DIR = DATA_DIR + "videos/"
    CSV_DIR = DATA_DIR + "csv/"
    LOGGING_LEVEL = logging.INFO