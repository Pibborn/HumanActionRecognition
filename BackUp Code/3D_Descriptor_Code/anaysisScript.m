close all;
clear;
clc;

%% Paramters for 3D Feature Computation

nOctaves = 3;                   % Number of Octaves
nScales = 3;                    % Number of Scales
% initSigma = 0.5;               % Initial Sigma of Gaussian Smoothening
initSigma = 0.1;               % Initial Sigma of Gaussian Smoothening
keyPointThreshold = 0.99;       % Neighborhood Threshold between 0 and 1
conThreshold = 0.04/nScales/2;           % Stability Threshold
curThreshold = 10;              % Curvature Ratio threshold
% Frame Counter

basePath = strcat(pwd,'\');
dataPath = strcat(pwd,'\dataset\');
videoList = dir(dataPath);

nVideos = size(videoList,1);
nVideos = 3;
for video = 3 : nVideos
    timeArr = zeros(nVideos,2);
    frameCount = 1;
    
    %videoName = videoList(video).name;
    %videoPath = strcat(dataPath,videoName);
    videoPath = 'LR2RL.mp4';
    videoObj = VideoReader(videoPath);
    videoName = 'LR2RL.mp4';
    
    % inputFame = uint8(zeros(videoObj.Height,videoObj.Width,ceil(videoObj.Duration*videoObj.FrameRate)));
    inputFrame = uint8([]);
    
    fprintf('Reading Video : %s\n',videoName);
    
    while hasFrame(videoObj) && frameCount < 20
        rgbFrame = readFrame(videoObj);
        grayFrame = rgb2gray(rgbFrame);
        inputFrame(:,:,frameCount) = grayFrame;
        frameCount = frameCount + 1;
    end
    tic;
    fprintf('Generating Scale Space Represnetation\n');
    [gss, dog, allSigma] = getScaleSpace(inputFrame, nOctaves, nScales + 2, initSigma);
    
    % Feature Extraction
    fprintf('Calculating Features\n');
    [features, oMag, oTheta] = calcFeatures(gss, dog, nOctaves, nScales, keyPointThreshold);
    
    % Feature Curvature Computation and Pruning
    fprintf('Calculating the curvature, and Purinng features\n');
    [features] = curvaturePruning(gss, features, curThreshold, conThreshold);
    timeArr(video,1) = toc;
    tic;
    offset = 0;
    descriptor = zeros(size(features,1),640);
    for i=1:size(features,1)
        o = features(i,1); % octave
        s = features(i,2); % scale
        reRun = 1;
        while reRun == 1
            f = features(i + offset, 3); % t
            h = features(i + offset, 4); % x
            w = features(i + offset, 5); % y
            % loc = subs(i+offset,:);
            fprintf(1,'Calculating keypoint at location (%d, %d, %d)\n',[h w f]);
            % Create a 3DSIFT descriptor at the given location
            % [keys{i}, reRun] = Create_Descriptor(gss{o,s},1,1,loc(1),loc(2),loc(3));
            [keys{i}, reRun] = Create_Descriptor(gss{1,1}, 1, 1, h, w, f);
            if reRun == 1
                offset = offset + 1;
            end
        end
        descriptor(i,:) = keys{1,i}.ivec;
    end
    timeArr(video,2) = toc;
    save(strcat(dataPath,videoName,'_features.mat'));
end