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

%% Defining Video Reader Object
videoFileName = 'LR2RL.mp4';
readerObj = VideoReader(videoFileName);

%% Paramters for 3D Feature Computation
gopSize = 100;                  % Group-of-picture Size
initSigma = 0.05;               % Initial Sigma of Gaussian Smoothening
nOctaves = 3;                   % Number of Octaves
nScales = 3;                    % Number of Scales
keyPointThreshold = 0.95;       % Neighborhood Threshold between 0 and 1
conThreshold = 0.01;           % Stability Threshold
curThreshold = 10;              % Curvature Ratio threshold
pixelLength = 300;              % Frame Size
frameCount = 1;                 % Frame Counter

% For Orientation Estimation
nOrientBins = 8;                % Number of Orientation Bins
nOrientNeighbors = 16;          % Orientation Neighborhood Size

% For Discriptor Estimation
regionSize = 16;
nBins = 8;


%% Iterating through each frame
% inputFrame = zeros(readerObj.height, readerObj.width, gopSize);
inputFrame = zeros(pixelLength, pixelLength, gopSize);
features = zeros(0,0);

% Features are not computed for 1st & last frame
while hasFrame(readerObj)
    
    if frameCount == gopSize + 1
        frameCount = 1;
    end
    
    %% READING FRAME FROM VIDEO
    temp = readFrame(readerObj);
    tempGray = rgb2gray(temp);
    
    fprintf('Frame - %d\n', frameCount);
    
    %% EXTRACTING SUBSET OF FRAME
    inputFrame(:, :, frameCount) = tempGray(1:pixelLength,1:pixelLength);
    
    frameCount = frameCount + 1;
    % if frameCount == 13
    if frameCount == gopSize + 1
        if keyPointThreshold < 0 || keyPointThreshold > 1
            error(' Invalid Key Point Neghborhood Threshold : Valid Range - [0,1]');
        end
        
        %% Group-of-Frame DIMENSIONS
        % imgF(t) : Number of frames
        % imgW(y) : Width of the Frames
        % imgH(x) : Height of the Frames
        [imgH, imgW, imgF] = size(inputFrame);
        
        %% Check if the Current Octaves can be created or not.
        
        if nOctaves >= log2(imgH) && nOctaves >= log2(imgW) && nOctaves >= log2(imgF)
            error('Invalid Dimensions');
        end
        
        % Minimum Execution Requirement Condition.
        if imgH < 3 || imgW < 3 || imgF < 3
            error('Invalid Dimensions');
        end
        
        if nOrientBins < 1
            error('Number of Orientation bins must be a Non-Zero, Non-Negative Number.');
        end
        
        if mod(nOrientNeighbors,4) ~= 0 || nOrientNeighbors < 4
            error('Orientation Neighborhood must be a multiple of four and positve integer, greater than or equal to 4.');
        end
        
        %% Getting Scale Space Representation.
        fprintf('Generating Scale Space Represnetation\n');
        [gss, dog, allSigma] = getScaleSpace(inputFrame, nOctaves, nScales + 2, initSigma);
        
        %% Getting Key Points.
        % Local Maxima/Minima Detection.
        % Number of Scale is reduced by 1 in Differece-Of-Gaussian (DOG).
        
        % Feature Extraction
        fprintf('Calculating Features\n');
        [features, oMag, oTheta] = calcFeatures(gss, dog, nOctaves, nScales, keyPointThreshold);
        
        % Feature Curvature Computation and Pruning
        fprintf('Calculating the curvature, and Purinng features\n');
        [features] = curvaturePruning(gss, features, curThreshold, conThreshold);
        
        % Descriptor Assignment
        % fprintf('Computing the Descriptors');
        % [descriptors] = calcDescriptors(features, oMag, oTheta, regionSize, nBins);
        
        %% Mapping the frames to original dimensions.
        % [tFeatures, tFrame ] = translateFeature(features, inputFrame);
        
        
        
        offset = 0;
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
        end
        
        
        %% Writing images to disk.
        for i = 1 : gopSize
            imwrite(tFrame(:,:,i),strcat(videoFileName,'_Frame_',num2str(i),'.png'));
        end
        
        %% Converting Current System Time to String.
        format shortg;
        c = clock;
        dateToday = '';
        for i = 1 : length(c)
            dateToday = strcat(dateToday,num2str(c(i)),'_');
        end
        
        %% Saving feature file to disk along with header row
        fileName = strcat(videoFileName,'_feature',dateToday,'.csv');
        fid = fopen(fileName,'w');
        fprintf(fid,'Octave,Scale,Frame,Height,Width,CurvatureRatio,Contrast,Type\n');
        fclose(fid);
        
        dlmwrite(fileName, tFeatures, '-append', 'precision', '%.6f', 'delimiter', ',');
        
    end
end
