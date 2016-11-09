clear;
clc;

%% Initializing the Paths
dataPath = strcat(pwd,'\Weizmann\');
vocabPath = strcat(pwd,'\Weizmann\SIFT3DDesVocab\');
% vocabPath = 'C:\Users\ygarg\Dropbox (ASU)\sift3D\Results\Weizmann\Vocabulary\';
%% INITIALIZING THE VACABULARY
vocabs = [50, 100, 250, 500, 750, 1000, 1250, 1500];
nVocabs = length(vocabs);
vocabType = 'Multi_XYT_DES_';

%% INITIALIZING THE TRAINING AND TESTING DATA
trainInd = csvread(strcat(dataPath,'trainInd.csv'));
testInd  = csvread(strcat(dataPath,'testInd.csv'));
labels   = csvread(strcat(dataPath,'labels.csv'));

NumofClass = length(unique(labels));
nIterations = size(trainInd, 2);

accuracy = zeros(2,nVocabs);
for kernel = 1 : 2
    scores = zeros(nIterations, nVocabs);
    for v = 1 : nVocabs
        vocab = vocabs(v);
        data  = csvread(strcat(vocabPath,vocabType,num2str(vocab),'.csv'));
        % data  = csvread(strcat(vocabPath,num2str(vocab),'_SIFT3Des.csv'));
        fprintf('Vocab Size : %d\n', vocab);
        for i = 1 : nIterations
            fprintf('(Iteration : %d\n', i);
            trainData = data(trainInd(:,i),:); 
            testData = data(testInd(:,i),:);
            
            trainLbl = labels(trainInd(:,i));
            testLbl  = labels(testInd(:,i));
            
            model = cell(NumofClass,1);
            for k = 1:NumofClass
                if kernel == 1
                    % Linear Kernel
                    model{k} = svmtrain(double(trainLbl==k), trainData, '-t 0 -h 0 -b 1');
                else
                    % Polynomial with degree 2
                    model{k} = svmtrain(double(trainLbl==k), trainData, '-t 1 -d 2 -h 0 -b 1');
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
        end
    end
    accuracy(kernel,:) = mean(scores);
end
accuracy