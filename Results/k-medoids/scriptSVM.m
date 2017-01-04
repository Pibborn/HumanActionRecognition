% ----------------------------------------------------------------------- %
% STAR : Spatio-Temporal Action Recognition Framework                     
% ----------------------------------------------------------------------- %
% AUTHOR(S)           : CONTACT                                           
% ----------------------------------------------------------------------- %
% K. Selcuk Candan    : N.A.                                              
% Maria-Luisa Sapino  : N.A.                                              
% Mattia Cerrato      : mattia.cerrato@edu.unito.it                       
% Yash Garg           : ygarg@asu.edu                                     
% ----------------------------------------------------------------------- %
% EXPERIMENT TYPE     : SVM Classification                                
% ----------------------------------------------------------------------- %
% THEORY                                                                  
% ----------------------------------------------------------------------- %
% + SVM classification is implemented using one-vs-all classifiers
%   and trained and tested using Leave-One-Out strategy. 
% + To maintain the independence of experiment on the data, we creared a 
%   run of 10 iterations, by selecting 83 videos as training data and 10
%   videos (1 for each label) as test data.
% + SVM was trained separately for both, linear and polynomial kernel with 
%   degree 2.
% ----------------------------------------------------------------------- %
% INITIALINING FLAGS                                                      
% ----------------------------------------------------------------------- %
% Normalize the Histograms
% normChk : 0 : Do Not Normalize
% normChk : 1 : Do Normalize
% ----------------------------------------------------------------------- %
% INITIALINING PATHS                                                      
% ----------------------------------------------------------------------- %
% dataPath  : Points to the folder containing the trainInd, testInd and
%             labels files.
% trainInd  : Number of training files x Number of Iterations
% testInd   : Number of testing files  x Number of Iterations
% labels    : Number of files x 1 (numbers represents labels)
% vocabPath : Points to the folder containing the vocabulary based
%             representation of the videos based on k-means clustering 
% ----------------------------------------------------------------------- %
%% SCRIPT STARTS HERE
clear;
clc;

%% FLAGS
normChk = 1;

%% Initializing the Paths
dataPath = strcat(pwd,'\Weizmann\');
vocabPath = strcat(pwd,'\Weizmann\SIFT3DDesVocab\');
%% INITIALIZING THE VACABULARY
vocabs = [50, 100, 250, 500, 750, 1000, 1250, 1500];
nVocabs = length(vocabs);
vocabType = '3D_DES_';

%% INITIALIZING THE TRAINING AND TESTING DATA
trainInd = csvread(strcat(dataPath,'trainInd.csv'));
testInd  = csvread(strcat(dataPath,'testInd.csv'));
labels   = csvread(strcat(dataPath,'labels.csv'));

NumofClass = length(unique(labels));
nIterations = size(trainInd, 2);

accuracy = zeros(2,nVocabs);

% Variables to save intermediate results
probs    = zeros(2,nVocabs,NumofClass,nIterations);
probsMax = zeros(2,nVocabs,NumofClass,nIterations);
probsLbl = zeros(2,nVocabs,NumofClass,nIterations);

for kernel = 1 : 2
    scores = zeros(nIterations, nVocabs);
    for v = 1 : nVocabs
        vocab = vocabs(v);
        
        % Reading Vocabulary 
        data  = csvread(strcat(vocabPath,vocabType,num2str(vocab),'.csv'));

        % Normalizeing the vocabulary
        if normChk == 1
            dataSum = sum(data,2);
            data = bsxfun(@rdivide,data',dataSum');
            data = data';
        end

        fprintf('Vocab Size : %d\n', vocab);
        for i = 1 : nIterations
            fprintf('(Iteration : %d\n', i);
            
            % Iniitializing training and testing data
            trainData = data(trainInd(:,i),:); 
            testData = data(testInd(:,i),:);
            
            trainLbl = labels(trainInd(:,i));
            testLbl  = labels(testInd(:,i));
            
            % Training the models
            model = cell(NumofClass,1);
            for k = 1:NumofClass
                if kernel == 1
                    % Linear Kernel
                    model{k} = svmtrain(double(trainLbl==k), trainData, '-t 0 -b 1');
                else
                    % Polynomial with degree 2
                    model{k} = svmtrain(double(trainLbl==k), trainData, '-t 1 -d 2 -b 1');
                end
            end
            
            % calculate the probability of different labels
            pr = zeros(length(testLbl),NumofClass);
            for k = 1:NumofClass
                [~,~,p] = svmpredict(double(testLbl==k), testData, model{k}, '-b 1');
                pr(:,k) = p(:,model{k}.Label==1);    %# probability of class==k
            end
            [~,predictedLabel] = max(pr,[],2);
            scores(i, v) = (sum(logical((predictedLabel-testLbl)==0))/NumofClass)*100;
            
            % Saving intermediate results
            probs(kernel,v,:,i)    = pr(logical(eye(size(pr))));
            probsMax(kernel,v,:,i) = max(pr,[],2);
            probsLbl(kernel,v,:,i) = predictedLabel;
        end
    end
    accuracy(kernel,:) = mean(scores);
end
accuracy