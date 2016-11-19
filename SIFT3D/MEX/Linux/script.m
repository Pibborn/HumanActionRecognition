videoPath = 'C:\Users\ygarg\Dropbox (ASU)\KTH Results\sift3D\Dataset\Weismann\daria_bend.avi';

%% SIFT Paramters
nScales = 3;                  % Number of Scales
oMin = -1;                    % Starting Octave Index
nOctaves = 3;                 % Number of Octaves
iSigma = 1.6*2^(1/nScales);   % Initial Sigma of Gaussian Smoothening
nSigma = 0.5;
thresh = 0.04 / nScales / 2;  % Base Pixel Value and Contrast Threshold
threshP = 0.8;                % Base Pixel value Threshold Percentage
r = 10;                       % Curvature Ratio Threshold

video = VideoReader(strcat(videoPath,videoFileName));
fprintf('Reading Video:%s\n',videoFileName);

X = video.Height;                           % Height
Y = video.Width;                            % Width
T = ceil(video.Duration*video.FrameRate);   % Frames
inputVideo = zeros(X,Y,T);

frameCount = 1;
while hasFrame(video)
    inputVideo(:,:,frameCount) = rgb2gray(readFrame(video));
    frameCount = frameCount + 1;
end

fprintf('GSS\n');
gss = getGaussian(inputVideo, nSigma, nOctaves+1, nScales, oMin, -1, nScales+1, iSigma);
fprintf('DOG\n');
dogss = diffss(gss);

features = csvread(strcat(featurePath,videoFileName,'_feature.csv'),1,0);

nFeatures = size(features,1);

for feature = 1 : nFeatures
    o = features(feature,1);
    s = features(feature,2);
    x = features(feature,3);
    y = features(feature,4);
    t = features(feature,5);
    features(feature,13) = gss.octave{o}(x, y, t, s);
    features(feature,14) = dogss.octave{o}(x, y, t, s);
end

if size(features,1) <= 200
    candidateFeatures = features;
else
    candidateFeatures = features(1:200,:);
end

candidates = candidateFeatures(:,3:5);

featureCount = size(candidates,1);
finalFeatures = [];
descriptors = [];

for feature = 1 : featureCount
    o = candidateFeatures(feature,1);
    s = candidateFeatures(feature,2);
    x = candidates(feature,1);
    y = candidates(feature,2);
    t = candidates(feature,3);
    fprintf(1,'Feature : %d of %d, Location (%d, %d, %d)\n', feature, featureCount, x, y, t);
    
    [keys, reRun] = Create_Descriptor(gss.octave{o}(:, :, :, s),1, 1, x, y, t);
    
    if reRun == 0
        descriptors = [descriptors; keys.ivec];
        finalFeatures = [finalFeatures; candidateFeatures(feature,:)];
    end
end
csvwrite(strcat(resultPathFinal,videoFileName,'_features.csv'),finalFeatures);
csvwrite(strcat(resultPathFinal,videoFileName,'_descriptors.csv'),descriptors);
