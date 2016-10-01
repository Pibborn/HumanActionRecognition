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

dataPath = strcat('C:\Users\reeyash\Dropbox (ASU)\MPEG\code\sift3D\dataset\');
videoFiles = dir(dataPath);
nFiles = size(videoFiles,1);
for videoFile = 3 : nFiles
    
    %% Defining Video Reader Object
    videoFileName = videoFiles(videoFile).name;
    fprintf('Video %s\n', videoFileName);
    readerObj = VideoReader(strcat(dataPath,videoFileName));
    
    %% Iterating through each frame
    inputFrame = uint8(zeros(readerObj.height, readerObj.width, ceil(readerObj.Duration*readerObj.FrameRate)));

    gopSize = ceil(readerObj.Duration*readerObj.FrameRate);
    frames = cell(1,gopSize);
    descriptors = cell(1,gopSize);
    gss = cell(1,gopSize);
    dogss = cell(1,gopSize);
    features = [];
    descriptors = [];
    frameCount = 1;
    finalFrames = [];
    while hasFrame(readerObj)
        fprintf('Frame %d\n',frameCount);
        %% READING FRAME FROM VIDEO
        temp = readFrame(readerObj);
        tempGray = rgb2gray(temp);
        
        inputFrame(:,:,frameCount) = uint8(tempGray);
        
        [frames, descriptor{frameCount}, gss{frameCount}, dogss{frameCount}] = sift(uint8(tempGray),'Verbosity',0);
        frames(5,:) = frameCount;
        frameCount = frameCount + 1;
        finalFrames = [finalFrames;frames'];
    end
    %% Saving feature file to disk along with header row
    fileName = strcat('F:\SIFT2D\',videoFileName,'_feature.csv');
    fid = fopen(fileName,'w');
    fprintf(fid,'Octave,Scale,x,y,t,Curvature\n');
    fclose(fid);
    
    dlmwrite(fileName, finalFrames, '-append', 'precision', '%.6f', 'delimiter', ',');
    % save(strcat('F:\SIFT2D\',videoFileName,'_workspace.mat'),'descriptor','gss','dogss');
end
