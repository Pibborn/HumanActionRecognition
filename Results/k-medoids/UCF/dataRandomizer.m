labels = csvread(strcat(pwd,'/3P/labels.csv'));

uniqueLbls = unique(labels);
numOfClass = length(uniqueLbls);

nIterations = 10;

testFiles = zeros(numOfClass, nIterations);
trainFiles = zeros(size(labels,1) - numOfClass, nIterations);


for i = 1 : nIterations
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

csvwrite(strcat(pwd,'/3P/trainInd.csv'),trainFiles);
csvwrite(strcat(pwd,'/3P/testInd.csv'),testFiles);