from keras.models import Sequential
from keras.layers import Dense, Activation
from keras.optimizers import SGD
import numpy as np
# from keras.layers.core import Dropout

np.random.seed(0);
basePath = 'C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Results-New\\'
dataSet  = 'KTH\\'
desType  = '3D\\'
histType = 'Group75\\'
algoType = '3D_OSXYT_Des_'

if dataSet == 'UCF':
    trainFile = basePath + dataSet + desType + 'trainInd.csv'
    testFile  = basePath + dataSet + desType + 'testInd.csv'
else:
    trainFile = basePath + dataSet + 'trainInd.csv'
    testFile  = basePath + dataSet + 'testInd.csv'
    
trainFiles  = np.genfromtxt(trainFile, dtype = None, delimiter = ',')
testFiles   = np.genfromtxt(testFile,  dtype = None, delimiter = ',')

vocabs      = [50, 100, 250, 500, 750, 1000, 1250, 1500]
nVocabs     = np.shape(vocabs)[0]

nIterations = np.shape(testFiles)[1]
nLabels     = np.shape(testFiles)[0]

sgd = SGD(lr = 0.005, momentum = 0.9, decay = 1e-6, nesterov=True)

for level in range(1, 4):
    scores = np.empty([nVocabs, nIterations])
    for v in range(0, nVocabs):
        vocab = vocabs[v]
        wordFile  = basePath + dataSet + desType + histType + algoType + str(vocab) +'.csv'
        
        if dataSet == 'UCF':
            labelFile = basePath + dataSet + desType + 'label.csv'
        else:
            labelFile = basePath + dataSet + 'label.csv'
            
        data   = np.genfromtxt(wordFile, dtype = float, delimiter = ',')
        labels = np.genfromtxt(labelFile, dtype = float, delimiter = ',')
    
        inputDim = np.shape(data)[1]
        #layerSize = vocab
        layerSize = 50
    
        print '\nVocab Size ' + str(vocab) + " layer size " + str(layerSize)

        # Creating a Sequential Model
        model = Sequential()  
        model.add(Dense(layerSize, input_dim = inputDim, init = 'he_normal'))
        model.add(Activation('relu'))
        
        if level == 1:
            model.add(Dense(layerSize))
            model.add(Activation('relu'))
        if level == 2:
            model.add(Dense(layerSize))
            model.add(Activation('relu'))
        if level == 3:    
            model.add(Dense(layerSize))
            model.add(Activation('relu'))
        model.add(Dense(nLabels))
        model.add(Activation('softmax'))
        model.compile(optimizer = sgd, loss = 'categorical_crossentropy', metrics = ['accuracy'])
        
        for i in range(0,nIterations):
            print str(i) + 'th.',
        
            trainData = data[trainFiles[:, i] - 1, :]
            trainLabel = labels[trainFiles[:, i] - 1, :]
            testData = data[testFiles[:, i] - 1, :]
            testLabel = labels[testFiles[:, i] - 1, :]

            model.fit(trainData, trainLabel, nb_epoch = 30, verbose = 0)
            score = model.evaluate(testData, testLabel, verbose = 0)
            scores[v][i] = score[1] 
    #print 'Average performance for all vocab representation in a given iteration\n' + str(np.mean(scores, axis=0))
    print '\n Average performance of a given vocab representation for all iteration\n' + str(np.mean(scores, axis = 1) * 100)