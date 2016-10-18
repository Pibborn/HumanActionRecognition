TwoPeak_Flag = 1;  % Allow 3DSIFT to throw out points, Default: 1
IndexSize = 2;  % Min: 1  Default: 2 

Display_flag = 0;  % Display a sphere which can be rotated (Rotate 3D button) to view gradient directions
Tessellation_flag = 1;  % Keep this as 1
Tessellation_levels = 1;  % Min: zero  Default: 1
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

%% Various path parameters. Change as needed to run on your machine.
% global videoName variable, setup from start.m arguments. This should not
% be changed, as it is needed to properly set the name of the .csv files
% below.
global videoName;

baseDataPath = '~/Documents/uni/tesi/ActionRecognition/SIFT3D/data/';

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
outFeaturesPath = strcat(baseDataPath, 'features/',videoName,'_finalFeatures.csv');
outDescriptorsPath = strcat(baseDataPath, 'descriptors/', videoName, '_finalDescriptors.csv');
outRefinedFeaturesPath = strcat(baseDataPath, 'features/',videoName,'_refinedFeatures.csv');