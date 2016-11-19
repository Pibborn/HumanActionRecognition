close all;
clear;
clc;

%% Loading Parameter
params;

%% DEFINING VIDEO PATH
videoPath = 'C:\Users\ygarg\Dropbox (ASU)\sift3D\Dataset\Weismann\';
videoName = 'daria_bend.avi';

%% READING VIDEO
fprintf('Reading Video %s.\n',videoName);
videoObj = VideoReader(strcat(videoPath, videoName));

height = videoObj.Height;
width  = videoObj.Width;
time   = ceil(videoObj.Duration*videoObj.FrameRate);

video = zeros(height, width, time);

frameCount = 0;

while hasFrame(videoObj)
    frameCount = frameCount + 1;
    fprintf('Reading Frame %d\n', frameCount);
    frame = readFrame(videoObj);
    grayFrame = rgb2gray(frame);
    video(:, :, frameCount) = grayFrame;
    
end


%% Creating Difference Video based on flag : videoDiffChk
if videoDiffChk == 1
    videoDiff = zeros(height, width, time-videoDiffStep);
    
    for frame = 1 : (frameCount - vidDiffStep)
        videoDiff(:,:,frame) = video(:,:,frame) - video(:,:,frame+videoDiffStep);
    end
    inputVideo = videoDiff;
else
    inputVideo = video;
end

%% Creating Features and Descriptors
% abs to make sure all the pixel values are positive.
[feature, descriptor, gss, dogss] = sift3D(abs(inputVideo));