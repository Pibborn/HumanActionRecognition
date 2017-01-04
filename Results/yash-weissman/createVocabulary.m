close all;
clear;
clc;

filePath   = strcat(pwd,'\Descriptors\Weizmann\Final\');
resultPath = strcat(pwd,'\Vocabulary\Weizmann\');

files = dir(strcat(filePath,'*.csv'));
nFiles = ceil(size(files,1)/2);

descriptors = cell(nFiles,1);
features = cell(nFiles,1);

allDescriptors = [];
allFeatures    = [];

for file = 1 : nFiles
    fprintf('Reading %d\n', file);
    descriptors{file} = csvread(strcat(filePath,files((file*2) - 1).name));
    allDescriptors = [allDescriptors; descriptors{file}];
    
    features{file} = csvread(strcat(filePath,files(file*2).name));
    allFeatures = [allFeatures; features{file}];
end

inputFeatures = [allFeatures(:,3:5) allDescriptors];

wordSizes = [50, 100, 250, 500, 750, 1000, 1250, 1500];

for word = 1 : length(wordSizes)
    fprintf('Vocabulary size - %d\n',wordSizes(word));
    tic;
    [idx, C] = kmeans(inputFeatures, wordSizes(word));
    
    vidSignature = zeros(nFiles, wordSizes(word));
    
    startIndex = 1;
    for file = 1 : nFiles
        endIndex = startIndex + size(descriptors{file},1) - 1;
        wordInd = idx(startIndex : endIndex);
        words = unique(wordInd);
        freq = [words,histc(wordInd(:),words)];
        vidSignature(file,freq(:,1)) = freq(:,2);
        startIndex = endIndex + 1;
    end
    toc;
    fName = '3D_XYT_DES_';
    signatureFileName = strcat(fName,num2str(wordSizes(word)),'.csv');
    signaturePath = strcat(resultPath,signatureFileName);
    
    csvwrite(signaturePath,vidSignature);
    csvwrite(strcat(resultPath, 'Codebook_', fName, num2str(wordSizes(word)),'.csv'), C);
end