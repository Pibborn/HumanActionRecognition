%%sift3D_bbrister: a function that uses the sift3D library from Blaine
%%Brister.
function [features, descriptors] =  sift3D_bbrister(video)

LoadParams;

% Intensity Video : Normalized 0-1 Video.
I = (video - min(video(:)))/...
    (max(video(:)) - min(video(:)));

% Detect keypoints
keys = detectSift3D(video);

% Extract descriptors
[descriptors, features] = extractSift3D(keys);

csvwrite(outFeaturesPath,features);
csvwrite(outDescriptorsPath,descriptors);

