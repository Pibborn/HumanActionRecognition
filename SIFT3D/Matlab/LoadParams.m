TwoPeak_Flag = 1;  % Allow 3DSIFT to throw out points, Default: 1
IndexSize = 2;  % Min: 1  Default: 2 

Display_flag = 0;  % Display a sphere which can be rotated (Rotate 3D button) to view gradient directions
Tessellation_flag = 1;  % Keep this as 1
Tessellation_levels = 0;  % Min: zero  Default: 1
nFaces = 20 * ( 4 ^ Tessellation_levels );  % Number of faces in the tessellation, not a parameter

Smooth_Flag = 1;  % Adds gradient data to surrounding bins in final histogram
Smooth_Var = 20;  % Determines amount of smoothing, Default: 20

% The rest of the variables are not modified often, but are included here
% for completeness sake
IgnoreGradSign = 0;
IndexSigma = 5.0;
MagFactor = 3;

UseHistogramOri = 1;
OriHistThresh = 0.8;
if (UseHistogramOri)
    OriSigma = 1.5;
else
    OriSigma = 1.0;
end

NumMaxFeatures = 1; % maximum number of features for a video
NumProcessors = 2; % number of processors available on your machine

%% Various path parameters. Change as needed to run on your machine.
% global videoName variable, setup from start.m arguments. This should not
% be changed, as it is needed to properly set the name of the .csv files
% below.
global videoName;

baseDataPath = '~/Documents/uni/tesi/ActionRecognition/SIFT3D/data/';
rootPath = '~/Documents/uni/tesi/ActionRecognition/';

% Relevant to scriptVocabGenerator.m
% the .csv files containing descriptors. all .csvs in this folder will be
% loaded.
descriptorPath = strcat(baseDataPath,'descriptors/yash-sample/');
% this is where the vocabulary generation will output its .csv files to.
resultPath = strcat(baseDataPath,'results/');

% Relevant to scriptSVMNew.m
% Should be the same as resultPath above.
vocabPath = strcat(baseDataPath, 'results/');

% Relevant to sift3D.m
% videoName is set from arguments in start.m
outFeaturesPath = strcat(baseDataPath, 'features/test/',videoName,'_testfeatures.csv');
outDescriptorsPath = strcat(baseDataPath, 'descriptors/test/', videoName, '_testdescriptors.csv');
outRefinedFeaturesPath = strcat(baseDataPath, 'features/',videoName,'_refinedFeatures.csv');

% Relevant to start_parallel.m
% Path of the videos you desire to extract features from
videoPath = strcat(baseDataPath, 'videos/test-daria/');

% External library folders path
% bbrister-SIFT3D
addpath(strcat(rootPath, 'SIFT3D/bbrister-SIFT3D/build/lib/wrappers/matlab/'));

