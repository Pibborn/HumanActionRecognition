close all;
clear;
clc;

%% DEFINING VIDEO PATH
videoPath = '~/videos/';
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
diffStep = 10;
videoDiff = zeros(height, width, time-diffStep);

for frame = 1 : (frameCount - diffStep)
    videoDiff(:,:,frame) = video(:,:,frame) - video(:,:,frame+diffStep);
end

[feature, descriptor, gss, dogss] = sift3D(video);

frame  = videoDiff(:,:,1);frame = uint8(abs(frame));imshow(frame);

frame = videoDiff(:,:,12);frame(85,60) = 255;imshow(uint8(frame));