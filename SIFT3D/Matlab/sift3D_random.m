function [features, descriptors] = sift3D_random(video, height, width, time)

features = [];
descriptors = [];

%% Load Parameters
LoadParams;

% relevant parameters loaded: outFeaturesPath, outDescriptorsPath
%% Intensity Video : Normalized 0-1 Video.
I = (video - min(video(:)))/...
    (max(video(:)) - min(video(:)));

%% Creating Gaussian Scale-Space Representation.
[H, W, T] = size(I);

S        =  3;                                 % Number of Scale
omin     =  0;                                 % Minimum Scale
O        =  floor(log2(min([H, W, T]))) - omin - 4; % Up to 16x16 images
O        =  3; % Up to 16x16 images
k        =  2^(1/S);                           % Scale Multiplicative Step
sigma0   =  1.6 * k;                           % Initial Smoothing Sigma
sigman   =  0.5;                               % Nominal Smoothing
thresh   =  0.04 / S / 2;
pThresh  =  0.8;                               % Weak Point Threshold
neighbor =  0.97;                              % Percentage Extrema Neighborhood
r        = 20;                                 % Curvature Threshold
smin     = -1;                                 % Minimum Scale
smax     =  S + 1;                             % Maximum Scale

verb = 0;
if verb > 0
    fprintf('Computing Scale Space\n');
end

gss   = imgaussian(I, O, S, omin, smin, smax, sigma0, sigman, verb);

%% Random sampling of space-time-scale points
% Create 200x1 vectors of random values for each descriptor parameter (o, s, x, y, t)  
rng('shuffle');
random_octaves = randi(3, NumMaxFeatures, 1);
random_scales = randi(4, NumMaxFeatures, 1);
% for (x, y, t) we probably don't want to sample points that are close to
% the borders of the frame or video
random_xs = randi([floor(width/3), width-floor(width/3)], NumMaxFeatures, 1); % the first parameter is [min, max] in the uniform distribution
random_ys = randi([floor(height/3), height-floor(height/3)], NumMaxFeatures, 1);
random_times = randi([floor(time/3), time-floor(time/3)], NumMaxFeatures, 1);

features = [];
descriptors = [];

for i = 1 : NumMaxFeatures
    
    o = random_octaves(i);
    s = random_scales(i);
    x = random_xs(i);
    y = random_ys(i);
    t = random_times(i);
    
    [keys, reRun] = Create_Descriptor(gss.octave{o}(:, :, :, s),1, 1, x, y, t);
    if reRun == 0
        descriptors = [descriptors; keys.ivec];
        features = [features; o s x y t];
    end
end

csvwrite(outFeaturesPath,features);
csvwrite(outDescriptorsPath,descriptors);

end





