clear;
clc;

vocabPath = strcat(pwd, '/KTH/3D/Vocab/');
groupPath = strcat(pwd, '/KTH/3D/Group75N/');

if exist(groupPath,'dir') ~= 7
    mkdir(groupPath);
end

files = dir(strcat(vocabPath, '*.csv'));
nFiles = size(files, 1);

for file = 1 : nFiles
    fileName = files(file).name;
    fprintf('Reading File : %s\n', fileName);
    data = csvread(strcat(vocabPath, fileName));
    
    sumRow = sum(data,2);
    data = bsxfun(@rdivide,data,sumRow);
    
    fprintf('Creating Word Co-Occurance Matrix\n');
    [nActions, nVocabs] = size(data); 
    wordCoOccur = zeros(nVocabs);
    
    for action = 1 : nActions
        for word = 1 : nVocabs
            temp = zeros(1, nVocabs);
            temp(:) = data(action, word);
            wTemp = temp./data(action, :);
            wTemp(logical(wTemp == Inf)) = 0;
            wTemp(isnan(wTemp)) = 0;
            wordCoOccur(word, :) = wordCoOccur(word, :) + wTemp(1, :);
        end
    end
    
    fprintf('Calculating Word Correlation\n');
    wordCoRelMat = zeros(nVocabs);
    coOccure = {};
    coCount = 0;
    for w1 = 1 : nVocabs
        for w2 = 1 : nVocabs
            wordCoRelMat(w1, w2) = abs(corr(wordCoOccur(w1,:)', wordCoOccur(w2,:)'));
            if wordCoRelMat(w1, w2) >= 0.75
                coCount = coCount + 1;
                coOccure{1, coCount} = [w1, w2];
            end
        end
    end
    
    coSignatures = zeros(nActions, coCount);
    fprintf('Creating Grouping HIstogram\n');
    for c = 1 : coCount
        temp = data(:, coOccure{1, c});
        if size(temp, 2) == 1
            coSignatures(:, c) = temp;
        else
            tempT = temp';
            tempT = sum(tempT);
            coSignatures(:, c) = tempT';
        end
    end
    csvwrite(strcat(groupPath, fileName), coSignatures);
end