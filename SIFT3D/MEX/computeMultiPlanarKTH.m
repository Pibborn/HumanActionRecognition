clear;
clc;

videoPath   = 'C:\Users\emitlab\Dropbox (ASU)\KTH Results\sift3D\Dataset\';
featurePath = 'C:\Users\emitlab\Dropbox (ASU)\KTH Results\sift3D\KTH\SIFT3DDes\Initial\';
resultPath  = 'C:\Users\emitlab\Dropbox (ASU)\KTH Results\sift3D\KTH\';

% SIFT PARAMETERS
% Paramters for 3D Feature Computation
nScales = 3;
oMin = -1;
nOctaves = 3;
iSigma = 1.6*2^(1/nScales);
nSigma = 0.5;
thresh = 0.04 / nScales / 2;
threshP = 0.8;
r = 10;
NBP = 4 ;
NBO = 8 ;
magnif = 3.0 ;

randFile = csvread('C:\Users\emitlab\Dropbox (ASU)\KTH Results\randFiles.csv');
rFiles = randFile(:,1:6);

dataTypes = dir(videoPath);
for dType = 3 : 8
    videoFilePath = strcat(videoPath,dataTypes(dType).name,'\');
    videos = dir(strcat(videoFilePath,'*.avi'));
    
    for randV = 1 : 6
        
        videoName = videos(rFiles(dType-2,randV)).name;
        videoFileName = strcat(videoFilePath,videoName);
        
        fprintf('Video %s\n', videoName);
        
        video = VideoReader(videoFileName);
        
        height = video.Height;
        width = video.Width;
        frames = ceil(video.Duration*video.FrameRate);
        
        inputFrame = zeros(height,width,frames);
        frameCount = 1;
        
        while hasFrame(video)
            fprintf('Frame - %d\n',frameCount);
            inputFrame(:,:,frameCount) = rgb2gray(readFrame(video));
            frameCount = frameCount + 1;
        end
        
        % inputFrame = inputFrame(:,:,1:30);
        
        fprintf('Gaussian\n');
        gss = getGaussian(inputFrame, nSigma, nOctaves+1, nScales, oMin, -1, nScales+1, iSigma);
        fprintf('Difference-of-Gaussian\n');
        dogss = diffss(gss);
        fprintf('Reading Features\n');
        features = csvread(strcat(featurePath,videoName,'.csv'));
        [~,I] = sort(features(:,14),'descend');
        features = features(I,:);
        features = features(1:200,:);
        
        % XY Plane - 1
        oframesXY = [features(:,3)';features(:,4)';features(:,2)';];
        % XT Plane - 2
        oframesXT = [features(:,3)';features(:,5)';features(:,2)';];
        % YT Plane - 3
        oframesYT = [features(:,4)';features(:,5)';features(:,2)';];
        descriptors = [];
        
        for feature = 1 : size(features,1)
            fprintf('Descriptor Feature # %d \n', feature);
            % Compute the oritentations
            
            oframe = oframesXY(:,feature);
            inputData = squeeze(gss.octave{features(feature,1)}...
                (:,:,features(feature,5),:));
            oframes = siftormx(...
                oframe, ...
                inputData, ...
                gss.S, ...
                gss.smin, ...
                gss.sigma0) ;
            shXY = siftdescriptor(...
                inputData, ...
                oframes, ...
                gss.sigma0, ...
                gss.S, ...
                gss.smin, ...
                'Magnif', magnif, ...
                'NumSpatialBins', NBP, ...
                'NumOrientBins', NBO) ;
            
            oframe = oframesXT(:,feature);
            inputData = squeeze(gss.octave{features(feature,1)}(:,features(feature,4),:,:));
            oframes = siftormx(...
                oframe, ...
                inputData, ...
                gss.S, ...
                gss.smin, ...
                gss.sigma0) ;
            shXT = siftdescriptor(...
                inputData, ...
                oframes, ...
                gss.sigma0, ...
                gss.S, ...
                gss.smin, ...
                'Magnif', magnif, ...
                'NumSpatialBins', NBP, ...
                'NumOrientBins', NBO) ;
            
            oframe = oframesYT(:,feature);
            inputData = squeeze(gss.octave{features(feature,1)}(features(feature,3),:,:,:));
            oframes = siftormx(...
                oframe, ...
                inputData, ...
                gss.S, ...
                gss.smin, ...
                gss.sigma0) ;
            
            shYT = siftdescriptor(...
                inputData, ...
                oframes, ...
                gss.sigma0, ...
                gss.S, ...
                gss.smin, ...
                'Magnif', magnif, ...
                'NumSpatialBins', NBP, ...
                'NumOrientBins', NBO) ;
            if size(shXY,2) == 0
                shXY = zeros(128,1);
                % oframes = oframe;
            end
            if size(shXT,2) == 0
                shXT = zeros(128,1);
                % oframes = oframe;
            end
            if size(shYT,2) == 0
                shYT = zeros(128,1);
                % oframes = oframe;
            end
            if size(shXY,2) ~= 1
                shXY = shXY(:,1);
            end
            if size(shXT,2) ~= 1
                shXT = shXT(:,1);
            end
            if size(shYT,2) ~= 1
                shYT = shYT(:,1);
            end
            sh = [shXY' shXT' shYT'];
            descriptors = [descriptors;sh];
            
        end
        
        csvwrite(strcat(resultPath,'XYT\',videoName,'_features.csv'),features);
        csvwrite(strcat(resultPath,'XYT\',videoName,'_descriptors.csv'),descriptors);
    end
end