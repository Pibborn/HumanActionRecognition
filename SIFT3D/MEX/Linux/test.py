from keras.models import Sequential
from keras.layers import Dense, Activation
import numpy as np
np.random.seed(0);

trainFile = 'C:\\Users\\ygarg\\Dropbox (ASU)\\MPEG\\code\\sift3D\\SIFT3D Results\\trainInd.csv'   
trainFiles = np.genfromtxt(trainFile, dtype=None, delimiter=',')

testFile  = 'C:\\Users\\ygarg\\Dropbox (ASU)\\MPEG\\code\\sift3D\\SIFT3D Results\\testInd.csv'
testFiles  = np.genfromtxt(testFile,  dtype=None, delimiter=',')

vocabs = [50, 100, 250, 500, 750, 1000, 1250, 1500]
scores = np.empty([8, 10]);

layerSize = 50;

for v in range(0, 8):
    vocab = vocabs[v]    
    # layerSize = vocab;
    print 'Vocab Size ' + str(vocab) 

    # Creating a Sequential Model
    model = Sequential()  
    model.add(Dense(layerSize, input_dim = vocab))
    model.add(Activation('relu'))
    model.add(Dense(layerSize))
    model.add(Activation('relu'))
    model.add(Dense(10))
    model.compile(optimizer='rmsprop', loss='categorical_crossentropy', metrics=['accuracy'])
    
    wordFile = 'C:\\Users\\ygarg\\Dropbox (ASU)\\MPEG\\code\\sift3D\\SIFT3D Results\\vocab\\'+ str(vocab) +'_SIFT3Des.csv'
    labelFile= 'C:\\Users\\ygarg\\Dropbox (ASU)\\MPEG\\code\\sift3D\\SIFT3D Results\\label.csv'
    data = np.genfromtxt(wordFile, dtype=float, delimiter=',')
    labels = np.genfromtxt(labelFile, dtype=float, delimiter=',')
    
    for i in range(0,10):
        print str(i) + 'th iteration.'
        
        trainData = data[trainFiles[:,i]-1,:]
        trainLabel = labels[trainFiles[:,i]-1,:]
        testData = data[testFiles[:,i]-1,]
        testLabel = labels[testFiles[:,i]-1,:]

        model.fit(trainData, trainLabel, nb_epoch=10, verbose=0)
        score = model.evaluate(testData, testLabel, verbose=0)
        scores[v][i] = score[1] 
    
print 'average' + str(np.mean(scores))
print 'All Scores' + str(scores)
print 'Average Axis=0' + str(np.mean(scores, axis=0))
print 'Average Axis=1' + str(np.mean(scores, axis=1))
    