import logging


class FeatureExtractor:

    def __init__(self, extractionStrategy):
        if extractionStrategy is not None:
            self.extract = extractionStrategy


    def extract(self):
        logging.error("The default extract() method was called. This should never happen.")


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
