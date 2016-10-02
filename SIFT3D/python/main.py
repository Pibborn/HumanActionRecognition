from videoDescription.featureExtraction import *
from settings import Constants

def main():
    myFirstExtractor = FeatureExtractor(siftExtraction)
    videoPath = Constants.VIDEO_DIR + 'daria_bend.avi'
    myFirstExtractor.extract(videoPath)

main()