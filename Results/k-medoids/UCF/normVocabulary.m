filePath = strcat(pwd,'\3D\Vocab\');

files = dir(strcat(filePath,'*.csv'));

nFiles = size(files,1);

for file = 1 : nFiles
    vocab = csvread(strcat(filePath,files(file).name));
    
    tValue = sum(vocab,2);
    
    nVocab = bsxfun(@rdivide,vocab,tValue);
    csvwrite(strcat(filePath,'Norm_',files(file).name),nVocab);
end