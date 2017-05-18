%%sift3D_bbrister: a function that uses the sift3D library from Blaine
%%Brister.
function [features, descriptors] =  sift3D_bbrister(video)

LoadParams;

% Intensity Video : Normalized 0-1 Video.
I = (video - min(video(:)))/...
    (max(video(:)) - min(video(:)));

% Detect keypoints
keys = detectSift3D(video);

save('keypoint-file.m', 'keys');
% Extract descriptors
[descriptors, features] = extractSift3D(keys);

% Obtain euler angles for each keypoint
phi_mat = [];
for i = 1 : size(keys)
    phi_x = atan2(keys(i).ori(3, 2), keys(i).ori(3, 3));
    phi_y = atan2(-keys(i).ori(3, 1), sqrt(keys(i).ori(3, 2) * keys(i).ori(3, 2) + keys(i).ori(3, 3) * keys(i).ori(3, 3)));
    phi_z = atan2(keys(i).ori(2, 1), keys(i).ori(1, 1));
    phi_mat = [phi_mat; phi_x phi_y phi_z];
end

% "Append" the euler angles matrix to the feature matrix, changing the
% number of columns
features = [features phi_mat];

csvwrite(outFeaturesPath,features);
csvwrite(outDescriptorsPath,descriptors);

