function descriptors = calcDescriptors(features, oMag, oTheta, regionSize, nBins)

%% FUNCTION DESCRIPTION
% THIS FUNCTION WILL COMPUTE THE DESCRIPTORS FOR THE FEATURE EXTRACTED 
% FROM THE VIDEO BLOCK USING THE FUNCTION CALCFEATURES

%% Possible Pixel Location
%  _ _ _ _ _ _ _ _
% |A B    C    D E|
% |F G    H    I J|
% |               |
% |K L    M    N O|
% |               |
% |P Q    R    S T|
% |U_V_ _ W _ _X_Y|

% COUNTING THE NUMBER OF FEATURES
nFeatures = size(features,1);

% INITIALIZING THE OUTPUT VARIABLE
descriptors = zeros(nFeatures,128);

% CREATING ORIENTATION BINS
% binRanges = 360/nBins : 360/nBins : 360;
step = 360/nBins;
binRanges = zeros(1,nBins + 1);
start = 0;
count = 1;
while start <=360
    binRanges(count) = start;
    start = start + step;
    count = count + 1;
end

%% GENERATING DESCRIPTORS
for feature = 1 : nFeatures
    o = features(feature,1);
    s = features(feature,2);
    [H,W,~] = size(oMag{o,s});   
    
    f = features(feature,3);
    h = features(feature,4);
    w = features(feature,5);
    
    centerReg = regionSize/2;
    
    magRegion = zeros(regionSize);
    thetaRegion = zeros(regionSize);
    
    magRegion(:,:) = oMag{o,s}(h,w,f);
    thetaRegion(:,:) = oTheta{o,s}(h,w,f);
    
    leftLimit = w - centerReg + 1;
    lL = 1;
    topLimit = h - centerReg + 1;
    tL = 1;
    rightLimit = w + centerReg;
    rL = regionSize;
    bottomLimit = h + centerReg;
    bL = regionSize;
    
    if leftLimit < 1
        leftLimit = 1;
        lL = centerReg - (w - 1);
    end
    if topLimit < 1
        topLimit = 1;
        tL = centerReg - (h - 1);
    end
    
    if rightLimit > W
        rL = centerReg + (centerReg - (rightLimit - W));
        rightLimit = W;
        % rL = centerReg - (W - w);
    end
    if bottomLimit > H
        bL = centerReg + (centerReg - (bottomLimit - H));
        bottomLimit = H;
        % bL = centerReg - (H - h);
    end

    magRegion(tL:bL,lL:rL) = oMag{o,s}(topLimit:bottomLimit,leftLimit:rightLimit);
    thetaRegion(tL:bL,lL:rL) = oTheta{o,s}(topLimit:bottomLimit,leftLimit:rightLimit);
    
    descriptor = zeros(1,128);
    descriptorLength = 1;
    for i = 1 : 4 : regionSize
        for j = 1 : 4 : regionSize
            % fprintf('Length : %d\n',descriptorLength);
            data = reshape(thetaRegion(i : i + 4 - 1, j : j + 4 - 1),1,regionSize);
            magnitude = reshape(magRegion(i : i + 4 - 1, j : j + 4 - 1), 1, regionSize);
            
            [hist,ind] = histc(data,binRanges);
            hist(nBins) = hist(nBins) + hist(nBins+1);
            ind(ind==nBins+1) = nBins;
            hist = hist(1:nBins);
            
            tempind = ind;
            tempind(tempind == 0) = [];
            uniqueBins = unique(tempind);

            magHist = zeros(size(hist));
            for ub = 1 : size(uniqueBins,2)
                magHist(uniqueBins(ub)) = sum(magnitude(ind == uniqueBins(ub)));
            end
            
            descriptor(1,descriptorLength:descriptorLength + nBins - 1) = magHist(1,:);
            descriptorLength = descriptorLength + nBins;
        end
    end
    descriptors(feature,:) = descriptor;
end
end