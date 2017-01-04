close all;
clear;
clc;

filePath   = strcat(pwd,'/KTH/data/features/');
resultPath = strcat(pwd,'/KTH/data/vocab/');

files = dir(strcat(filePath,'*.csv'));
nFiles = ceil(size(files,1)/2);

descriptors = cell(nFiles,1);
features = cell(nFiles,1);

allDescriptors = [];
allFeatures    = [];

for file = 1 : nFiles
    fprintf('Reading descriptor file: %s\n', files((file*2) - 1).name);
    descriptors{file} = csvread(strcat(filePath,files((file*2) - 1).name));
    allDescriptors = [allDescriptors; descriptors{file}];
    
    fprintf('Reading feature file: %s\n', files(file*2).name);
    features{file} = csvread(strcat(filePath,files(file*2).name));
    allFeatures = [allFeatures; features{file}];
end

% octave, scale, x, y and t are the first 5 elements in features csv files
inputFeatures = [allFeatures(:,1:5) allDescriptors];
% inputFeatures = allDescriptors;

%wordSizes = [50, 100, 250, 500, 750, 1000, 1250, 1500];
wordSizes = [50];

for word = 1 : length(wordSizes)
    fprintf('Vocabulary size - %d\n',wordSizes(word));
    tic;
    [idx, C] = kmedoids(inputFeatures, wordSizes(word), 'Distance', 'mahalanobis');
    fprintf('Clustering is done.')
    
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
    fName = 'KMedoids_Mahalanobis_osxyt_';
    signatureFileName = strcat(fName,num2str(wordSizes(word)),'.csv');
    signaturePath = strcat(resultPath,signatureFileName);
    
    csvwrite(signaturePath,vidSignature);
    csvwrite(strcat(resultPath, 'Codebook_', fName, num2str(wordSizes(word)),'.csv'), C);
end