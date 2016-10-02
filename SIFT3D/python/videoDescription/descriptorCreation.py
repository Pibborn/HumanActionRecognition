import logging


class DescriptorCreator:

    def __init__(self, creationStrategy):
        if creationStrategy is not None:
            self.create = creationStrategy


    def create(self):
        logging.error('The default create() method was called. This should never happen.')


def siftDescriptorCreation(siftFeaturesPath):
    logging.error('siftDescriptorCreation: This function is not implemented yet.')

def surfDescriptorCreation(surfFeaturesPath):
    logging.error('surfDescriptorCreation: This function is not implemented yet.')