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

videoFileName = 'daria_pjump.avi';

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
toc;
fprintf('Difference of Gaussian Computation');
tic;
dogss = diffss(gss);
toc;
features = [];
spaceTime = 0;
pruneTime = 0;
parfor octave = 2 : gss.O
    fprintf('Octave - %d\n',octave);
    fprintf('In GetKeypoints\n');
    tic;
    keyPoints = getKeyPoints(dogss.octave{octave},octave, threshP*thresh);
    spaceTime = spaceTime + toc;
    fprintf('In refineKeyPoints\n');
    tic;
    % tFeatures = refineKeyPoints3DHessian(keyPoints, dogss.octave{octave},dogss.smin,thresh, r);
    tFeatures = refineKeyPoints(keyPoints, dogss.octave{octave},dogss.smin,thresh, r);
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

descriptors = zeros(featureCount,640);
tic;
parfor feature = 1 : featureCount
    
    o = features(feature,1);
    s = features(feature,2);
    x = features(feature,3);
    y = features(feature,4);
    t = features(feature,5);
    
    fprintf('Feature : %d of %d, Location (%d, %d, %d)\n', feature, featureCount, x, y, t);
    % Create a 3DSIFT descriptor at the given location
    I = squeeze(gss.octave{o}(:, :, :, s));
    [keys, reRun] = Create_Descriptor(I, 1, 1, x, y, t);
    if reRun == 0
        descriptors(feature,:) = keys.ivec;
    end
end
% fpringf('Descriptor Computation Time');
toc;
%% Removing features for which descriptor is not generated.

rmIndex = all(descriptors==0,2);
descriptors(rmIndex,:) = [];
features(rmIndex,:) = [];
