import logging
from pymatbridge import Matlab
from SIFT3D.python.settings import Constants


class FeatureExtractor:

    def __init__(self, extractionStrategy):
        if extractionStrategy is not None:
            self.extract = extractionStrategy


    def extract(self):
        logging.error("The default extract() method was called. This should never happen.")

def siftMatlabExtraction(videoPath):
    logging.info("siftMatlabExtraction: was called")
    mlab = Matlab(executable=Constants.MATLAB_EXECUTABLE)
    mlab.start()
    logging.info("siftMatlabExtraction: running " + Constants.MATLAB_CODE_DIR + "start.m")
    result = mlab.run_func(Constants.MATLAB_CODE_DIR +'start.m', {'uniqueArg' : 0})
    logging.info("siftMatlabExtraction: result is " + str(result))

def siftExtraction(videoPath):
    scaleSpace = getScaleSpace(videoPath)
    keypointList = getKeypoints(scaleSpace)
    keypointList = pruneKeypoints(keypointList)
    return keypointList

def surfExtraction(videoPath):
    logging.error("surfExtraction: This function is not implemented yet.")

def getScaleSpace(videoPath):
    logging.error("getScaleSpace: This function is not implemented yet.")

def getKeypoints(scaleSpace):
    logging.error("getKeypoints: This function is not implemented yet.")

def pruneKeypoints(keypointList):
    logging.error("pruneKeypoints: This function is not implemented yet.")
    return []
