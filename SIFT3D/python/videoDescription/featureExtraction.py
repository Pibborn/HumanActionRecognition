import logging
from pymatbridge import Matlab
from settings import Constants


class FeatureExtractor:

    def __init__(self, extractionStrategy):
        if extractionStrategy is not None:
            self.extract = extractionStrategy


    def extract(self):
        logging.error("The default extract() method was called. This should never happen.")

def startMatlab():
    logging.info("startMatlab: was called")
    mlab = Matlab(executable=Constants.MATLAB_EXECUTABLE)
    mlab.start()
    return mlab

def siftMatlabExtraction(videoPath, videoName, mlab):
    logging.info("siftMatlabExtraction: was called for video at path " + videoPath + videoName)
    logging.info("siftMatlabExtraction: running " + Constants.MATLAB_CODE_DIR + "start.m")
    result = mlab.run_func(Constants.MATLAB_CODE_DIR +'start.m', videoPath, videoName)
    logging.info("siftMatlabExtraction: result is " + str(result))

def parallelSiftMatlabExtraction(videoList, mlab):
    logging.info("parallelSiftMatlabExtraction: was called for a list of videos " + str(len(videoList)) + " long")
    logging.info("parallelSiftMatlabExtraction: running " + Constants.MATLAB_CODE_DIR + "start_parallel.m")
    result = mlab.run_func(Constants.MATLAB_CODE_DIR + 'start_parallel.m', videoList)
    logging.info("parallelSiftMatlabExtraction: result is " + str(result))

def stopMatlab(mlab):
    mlab.stop()


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
