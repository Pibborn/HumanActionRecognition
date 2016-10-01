%% AUTHOR INFORMATION
% ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
% Yash Garg(Contact) ~ ygarg@asu.edu        ~ http://public.asu.edu/~ygarg/
% K. Selcuk Candan   ~ candan@asu.edu       ~ http://aria.asu.edu/candan/
% Maria-Luisa Sapino ~ mlsapino@di.unito.it ~ http://www.di.unito.it/~mlsapino/
% ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

%% Clearing the Workspace
close all;
clear;
clc;

% mex -setup C++

%% Paramters for 3D Feature Computation
%% SIFT Paramters
nScales = 3;                  % Number of Scales
oMin = -1;                    % Starting Octave Index
nOctaves = 3;                 % Number of Octaves
iSigma = 1.6*2^(1/nScales);   % Initial Sigma of Gaussian Smoothening
nSigma = 0.5;
thresh = 0.04 / nScales / 2;  % Base Pixel Value and Contrast Threshold
threshP = 0.8;                % Base Pixel value Threshold Percentage
r = 10;                       % Curvature Ratio Threshold

frameCount = 1;
verbose = 1;

videoFileName = 'C:\Users\ygarg\Dropbox (ASU)\KTH Results\sift3D\Dataset\Weismann\daria_bend.avi';

readerObj = VideoReader(videoFileName);

height = readerObj.height;
width  = readerObj.width;
nFrames = ceil(readerObj.Duration*readerObj.FrameRate);

inputFrame = uint8(zeros(height, width, nFrames));
frameCount = 1;

while hasFrame(readerObj)
    fprintf('Frame %d\n',frameCount);
    temp = readFrame(readerObj);
    tempGray = rgb2gray(temp);
    inputFrame(:,:,frameCount) = uint8(tempGray);
    frameCount = frameCount + 1;
end
fprintf('Gaussian Computation');
tic;
gss = getGaussian(inputFrame, nSigma, nOctaves+1, nScales, oMin, -1, nScales+1, iSigma);
dogss = diffss(gss);
toc;
features = [];
spaceTime = 0;
pruneTime = 0;
for octave = 2 : gss.O
    fprintf('Octave - %d\n',octave);
    
    tic;
    keyPoints = getKeyPoints(dogss.octave{octave},octave, threshP*thresh);
    spaceTime = spaceTime + toc;
    
    tic;
    % tFeatures = refineKeyPoints(keyPoints, dogss.octave{octave},dogss.smin,thresh, r);
    tFeatures = refineKeyPoints3DHessian(keyPoints, dogss.octave{octave},dogss.smin,thresh, r);
    pruneTime = pruneTime + toc;
    
    features = [features; tFeatures];
end

for feature = 1 : size(features,1)
    % Using in general case
    features(feature,13) = gss.octave{features(feature,1)}(features(feature,3),features(feature,4),features(feature,5),features(feature,2));
    features(feature,14) = dogss.octave{features(feature,1)}(features(feature,3),features(feature,4),features(feature,5),features(feature,2));
    
end

[~,I] = sort(features(:,14),'descend');
features = features(I,:);

if size(features, 1) <=200
    features = features;
else
    features = features(1:200,:);
end

featureCount = size(features,1);
finalFeatures = [];
descriptors = [];
descriptorTime = 0;
for feature = 1 : featureCount
    
    o = features(feature,1);
    s = features(feature,2);
    x = features(feature,3);
    y = features(feature,4);
    t = features(feature,5);
    fprintf(1,'Feature : %d of %d, Location (%d, %d, %d)\n', feature, featureCount, x, y, t);
    
    tic;
    % Create a 3DSIFT descriptor at the given location
    [keys, reRun] = Create_Descriptor(gss.octave{o}(:, :, :, s),1, 1, x, y, t);
    if reRun == 0
        descriptors = [descriptors; keys.ivec];
        finalFeatures = [finalFeatures; features(feature,:)];
    end
    descriptorTime = descriptorTime + toc;
end
