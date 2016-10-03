from videoDescription.featureExtraction import *
from settings import Constants
import csv
import logging
logging.basicConfig(level=Constants.LOGGING_LEVEL)

def main(videoPath):
    myFirstExtractor = FeatureExtractor(siftExtraction)
    logging.info("Extracting sift features from " + videoPath)
    siftFeatures = myFirstExtractor.extract(videoPath)
    with open(Constants.CSV_DIR + videoName + "_siftfeatures.csv", 'wb') as csvFile:
        myFirstWriter = csv.writer(csvFile)
        for feature in siftFeatures:
            myFirstWriter.writerow(feature)

if __name__ == "__main__":
    videoName = 'daria_bend.avi'
    videoPath = Constants.VIDEO_DIR + videoName
    main(videoPath)