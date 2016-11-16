clear;
clc;

basePath = 'C:\Users\ygarg\Dropbox (ASU)\KTH Results\sift3D\Results\Weizmann\';
vocabPath = 'C:\Users\ygarg\Dropbox (ASU)\KTH Results\sift3D\Results\Weizmann\Vocabulary\';
vocabs = [50, 100, 250, 500, 750, 1000, 1250, 1500];
vocabType = '_SIFT3Des.csv';

trainInd = csvread(strcat(basePath,'trainInd.csv'));
testInd  = csvread(strcat(basePath,'testInd.csv'));
labels   = csvread(strcat(basePath,'labels.csv'));

% labels   = csvread('C:\Users\reeyash\Dropbox (ASU)\MPEG\code\sift3D\SIFT3D Results\labels.csv');

NumofClass = 10;

scores = zeros(10, 8);
for v = 1 : 8
    vocab = vocabs(v);
    data = csvread(strcat(vocabPath,num2str(vocab),vocabType));
    fprintf('Vocab Size : %d\n', vocab);
    for i = 1 : 10
        fprintf('(Iteration : %d\n', i);
        trainData = data(trainInd(:,i),:);
        
        subTrainData = bsxfun(@minus,trainData,min(trainData));
        trainData = bsxfun(@rdivide,subTrainData,max(trainData)-min(trainData));
        
        testData = data(testInd(:,i),:);
        
        subTestData = bsxfun(@minus,testData,min(testData));
        testData = bsxfun(@rdivide,subTestData,max(testData)-min(testData));
        
        trainLbl = labels(trainInd(:,i));
        testLbl = labels(testInd(:,i));
        
        model = cell(NumofClass,1);
        for k = 1:NumofClass
            model{k} = svmtrain(double(trainLbl==k), trainData, '-t 0 -h 0 -b 1');
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
accuracy = mean(scores)