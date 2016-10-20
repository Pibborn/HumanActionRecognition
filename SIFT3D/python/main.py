from videoDescription.featureExtraction import *
from settings import Constants
import csv
import sys
import logging
import glob
logging.basicConfig(level=Constants.LOGGING_LEVEL)

def parseArguments(args):
    videoList = []
    if len(args) == 1:
        # in this case, the script has not been ran from shell, so it has to be glob-bed.
        videoList = glob.glob(args[0])
    else:
        videoList = args
    return videoList

def testMatlab(fullVideoPath, mlabInstance):
    matlabExtractor = FeatureExtractor(siftMatlabExtraction)
    videoName = fullVideoPath.split('/')[-1:] # take the part of the string after the last /
    videoName = "".join(videoName) # make it a string again
    videoPath =  fullVideoPath.split('/')[:-1] # take the part of the string before the last /
    videoPath = "/".join(videoPath) + "/" # make it a string again, and take care in putting the /-s in again
    # the matlab side will concat the full path, but it requires them to be passed as separate arguments
    matlabExtractor.extract(videoPath, videoName, mlabInstance)

def main(videoPath):
    myFirstExtractor = FeatureExtractor(siftExtraction)
    logging.info("Extracting sift features from " + videoPath)
    siftFeatures = myFirstExtractor.extract(videoPath)
    with open(Constants.CSV_DIR + videoName + "_siftfeatures.csv", 'wb') as csvFile:
        myFirstWriter = csv.writer(csvFile)
        for feature in siftFeatures:
            myFirstWriter.writerow(feature)

if __name__ == "__main__":
    print(sys.argv[1:])
    videoList = parseArguments(sys.argv[1:])
    logging.info("List of videos features will be extracted from: " + str(videoList))
    mlabInstance = startMatlab()
    for videoPath in videoList:
        print(videoPath)
        try:
            testMatlab(videoPath, mlabInstance)
        except Exception:
            continue
    stopMatlab(mlabInstance)

