labels = csvread('C:\Users\ygarg\Dropbox (ASU)\MPEG\code\sift3D\SIFT3D Results\labels.csv');
uniqueLbls = unique(labels);
numOfClass = length(uniqueLbls);
count = 10;
testFiles = zeros(10,count);
trainFiles = zeros(83,count);

for i = 1 : count;
    train = [];
    test = [];
    
    for k = 1 : numOfClass
        curLbl = uniqueLbls(k);
        
        curFiles = find(labels == curLbl);
        
        temp = rand(1,length(curFiles));
        [~,I] = sort(temp);
        
        test = [test; curFiles(I(1))];
        train = [train; curFiles(I(2:end))];
    end
    
    trainFiles(:,i) = train;
    testFiles(:,i) = test;
end