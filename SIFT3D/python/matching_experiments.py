import glob
import os
import csv
import numpy as np
import logging
from ..settings import Constants
logging.basicConfig(level=Constants.LOGGING_LEVEL)

def infer_label(csv_file):
    file_name = csv_file.name
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
    return -1

def descriptor_matching():
    os.chdir(Constants.DESCRIPTORS_DIR)
    # X: matrix of sample data. At this time, each row is a SIFT3D descriptor.
    X = []
    # y: matrix of labels. The .csv files don't have these, so we infer them from the file name.
    y = []
    for file in glob.glob("*.csv"):
        print(file.name)
        csvReader = csv.reader(open(file, "rb"))
        # questo è sbagliato: sto iterando sui file ma mi sto comportando come se stessi iterando sulle righe di uno solo
        xi = list(csvReader)
        yi = infer_label(file)
        X.append(xi)
        y.append(yi)
        print(len(xi))
    X = np.array(X).astype(np.float32) # scikit-learn requires this
    y = np.array(y).astype(np.int32)


if __name__ == "__main__":
    descriptor_matching()
