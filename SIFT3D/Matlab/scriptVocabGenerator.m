clear;
clc;

% point to the folder that has descriptors csv
descriptorPath = 'C:\Users\ygarg\Dropbox (ASU)\KTH Results\sift3D\Results\Weizmann\Descriptor\3H\Final\';
resultPath = 'C:\Users\ygarg\Dropbox (ASU)\KTH Results\sift3D\Results\Weizmann\Vocabulary\';
descriptorFiles = dir(strcat(descriptorPath,'\*.csv'));

nFiles = ceil(size(descriptorFiles,1)/2);

descriptors = cell(1,nFiles);
allDescriptors = [];
for file = 1 : nFiles
    fprintf('Reading %d\n', file);
    descriptors{file} = csvread(strcat(descriptorPath,descriptorFiles((file*2) - 1).name));
    allDescriptors = [allDescriptors; descriptors{file}];
end

wordSizes = [100, 250, 500, 750, 1000, 1250, 1500];

for word = 1 : length(wordSizes)
    fprintf('Vocabulary size - %d\n',wordSizes(word));
    tic;
    [idx, C] = kmeans(allDescriptors, wordSizes(word));
    
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
    signatureFileName = strcat(num2str(wordSizes(word)),'_H3.csv');
    signaturePath = strcat(resultPath,signatureFileName);
    
    csvwrite(signaturePath,vidSignature);
end
