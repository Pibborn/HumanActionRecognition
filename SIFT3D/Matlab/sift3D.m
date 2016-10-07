function [features, descriptors, gss, dogss] = sift3D(video)

features = [];
descriptors = [];

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
NBP      =  4;
NBO      =  8;
magnif   =  3.0;

% Parese input
compute_descriptor      = 0;
discard_boundary_points = 1;
verb = 1;
if verb > 0
    fprintf('Computing Scale Space\n');
end
tic;
gss   = imgaussian(I, O, S, omin, smin, smax, sigma0, sigman, verb);
time = toc;
save('gss.mat','gss');
if verb > 0
    fprintf('Gaussian Computation Time: %d seconds\n', time);
end

if verb > 0
    fprintf('Computing Difference of Gaussian\n');
end
tic;
dogss = diffgss(gss);
time = toc;
save('dogss.mat','dogss');
if verb > 0
    fprintf('DoG Computation Time: %d seconds\n', time);
end
for o = 1 : gss.O
    if verb > 0
        if omin == 0
            fprintf('Feature in Octave : %d\n', o);
        else
            fprintf('Feature in Octave : %d\n', o - 1 + omin);
        end
    end
    tic;
    idx = siftLocalMex(dogss.octave{o}, o, pThresh*thresh, neighbor);
    time = toc;
    if verb > 1
        fprintf('Feature Extraction Time : %s',time );
    end
    tic;
    features = [features; siftRefineMex(idx, dogss.octave{o}, thresh, r)];
    time = toc;
    if verb > 1
        fprintf('Feature Pruning Time : %s',time );
    end
end
csvwrite('refinedFeatures.csv',features);
featureCount = size(features,1);
finalFeatures = [];
descriptors = [];
descriptorTime = 0;
for feature = 1 : featureCount
    
    o = features(feature,1);
    s = features(feature,2);
    x = features(feature,3);
    y = features(feature,4);
    t = features(feature,5);
    fprintf(1,'Feature : %d of %d, Location (%d, %d, %d)\n', feature, featureCount, x, y, t);
    
    tic;
    % Create a 3DSIFT descriptor at the given location
    [keys, reRun] = Create_Descriptor(gss.octave{o}(:, :, :, s),1, 1, x, y, t);
    if reRun == 0
        descriptors = [descriptors; keys.ivec];
        finalFeatures = [finalFeatures; features(feature,:)];
    end
    descriptorTime = descriptorTime + toc;
end
csvwrite('finalFeatures.csv',finalFeatures);
csvwrite('finalDescriptors.csv',descriptors);
end

function dss = diffgss(ss)

dss.smin   = ss.smin ;
dss.smax   = ss.smax-1 ;
dss.omin   = ss.omin ;
dss.O      = ss.O ;
dss.S      = ss.S ;
dss.sigma0 = ss.sigma0 ;

for o=1:dss.O
    % Can be done at once, but it turns out to be faster
    % this way
    [H, W, T, S] = size(ss.octave{o}) ;
    dss.octave{o} = zeros(H, W, T, S - 1) ;
    for s=1:S-1
        dss.octave{o}(:, :, :, s) = ...
            ss.octave{o}(:, :, :, s+1) - ...
            ss.octave{o}(:, :, :, s) ;
    end
end

end