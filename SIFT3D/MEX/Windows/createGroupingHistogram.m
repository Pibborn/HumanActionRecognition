clear;
clc;

vocabPath = 'C:\Users\reeyash\Dropbox (ASU)\MPEG\code\sift3D\SIFT3D Results\vocab\';
vocabs = [50, 100, 250, 500, 750, 1000, 1250, 1500];

trainInd = csvread('C:\Users\reeyash\Dropbox (ASU)\MPEG\code\sift3D\SIFT3D Results\trainInd.csv');
testInd  = csvread('C:\Users\reeyash\Dropbox (ASU)\MPEG\code\sift3D\SIFT3D Results\testInd.csv');
labels   = csvread('C:\Users\reeyash\Dropbox (ASU)\MPEG\code\sift3D\SIFT3D Results\labels.csv');

NumofClass = 10;
fileName = '_Random3Des_5.csv';

scores = zeros(10, 8);
for v = 1 : 8
    vocab = vocabs(v);
    fprintf('Vocab Size : %d\n', vocab);
    
    signatures = csvread(strcat(vocabPath,num2str(vocab),fileName));
    N = vocabs(v);
    nFiles = size(signatures,1);
    wordCoOccureMat = zeros(N, N);
    fprintf('Calculatinf Word Occurance\n');
    for file = 1 : nFiles
        for w = 1 : N
            temp = zeros(1,N);
            temp(:) = signatures(file,w);
            wTemp = temp./signatures(file,:);
            wTemp(logical(wTemp == Inf)) = 0;
            wTemp(isnan(wTemp)) = 0;
            wordCoOccureMat(w,:) = wordCoOccureMat(w, :) + wTemp(1,:);
        end
    end
    
    fprintf('Calculating Word Correlation\n');
    wordCoRelMat = zeros(N, N);
    coOccure = {};
    coCount = 1;
    for w1 = 1 : vocab
        for w2 = 1 : vocab
            wordCoRelMat(w1,w2) = abs(corr(wordCoOccureMat(w1,:)', wordCoOccureMat(w2,:)'));
            if wordCoRelMat(w1, w2) >= 0.5
                if w1 ~= w2
                    coOccure{1,coCount} = [w1,w2];
                    coCount = coCount + 1;
                end
            end
        end
    end
    
    coCount = coCount - 1;
    
    coSignatures = zeros(nFiles, coCount);
    
    for c = 1 : coCount
        temp = signatures(:,coOccure{1,c});
        if size(temp,2) == 1
            coSignatures(:,c) = temp;
        else
            tempT = temp';
            tempT = sum(tempT);
            coSignatures(:,c) = tempT';
        end
    end
    csvwrite(strcat('C:\Users\reeyash\Dropbox (ASU)\MPEG\code\sift3D\SIFT3D Results\vocab_gHist\',num2str(vocab),fileName),coSignatures);
end