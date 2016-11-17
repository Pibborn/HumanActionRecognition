% function [keyX, keyY, keyZ, keyXYScale, keyTScale, keyIvec] = MakeKeypoint(pix, xyScale, tScale, x, y, z)
function key = MakeKeypoint(pix, xyScale, tScale, x, y, z)
%     lData = load('LoadParams.mat');
% 
%     Display_flag = lData.Display_flag;
%     IgnoreGradSign = lData.IgnoreGradSign;
%     IndexSigma = lData.IndexSigma;
%     IndexSize = lData.IndexSize;
%     MagFactor = lData.MagFactor;
%     nFaces = lData.nFaces;
%     OriHistThresh = lData.OriHistThresh;
%     OriSigma = lData.OriSigma;
%     Smooth_Flag = lData.Smooth_Flag;
%     Smooth_Var = lData.Smooth_Var;
%     Tessellation_flag = lData.Tessellation_flag;
%     Tessellation_levels = lData.Tessellation_levels;
%     TwoPeak_Flag = lData.TwoPeak_Flag;
%     UseHistogramOri = lData.UseHistogramOri;
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
    ivec = zeros(1, (IndexSize*IndexSize*IndexSize*nFaces));
    
    k.x = x;
    k.y = y;
    k.z = z;
    k.xyScale = xyScale;
    k.tScale = tScale;
    k.ivec = ivec;
    key = MakeKeypointSample(k, pix);
    
%     keyX = key.x;
%     keyY = key.y;
%     keyZ = key.z;
%     keyXYScale = key.xyScale;
%     keyTScale = key.tScale;
%     keyIvec = key.ivec;
end


function key = MakeKeypointSample(key, pix)

% LoadParams;
% lData = load('LoadParams.mat');
% 
% Display_flag = lData.Display_flag;
% IgnoreGradSign = lData.IgnoreGradSign;
% IndexSigma = lData.IndexSigma;
% IndexSize = lData.IndexSize;
% MagFactor = lData.MagFactor;
% nFaces = lData.nFaces;
% OriHistThresh = lData.OriHistThresh;
% OriSigma = lData.OriSigma;
% Smooth_Flag = lData.Smooth_Flag;
% Smooth_Var = lData.Smooth_Var;
% Tessellation_flag = lData.Tessellation_flag;
% Tessellation_levels = lData.Tessellation_levels;
% TwoPeak_Flag = lData.TwoPeak_Flag;
% UseHistogramOri = lData.UseHistogramOri;
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

MaxIndexVal = 0.2;
changed = 0;

vec = KeySampleVec(key, pix);
VecLength = length(vec);

vec = NormalizeVec(vec, VecLength);

for i = 1:VecLength
    if (vec(i) > MaxIndexVal)
        vec(i) = MaxIndexVal;
        changed = 1;
    end
end
if (changed)
    vec = NormalizeVec(vec, VecLength);
end

for i = 1:VecLength
    intval = int16(512.0 * vec(i));
    if ~(intval >= 0)
        disp('Assertation failed in MakeKeypoint.m');
    end
    key.ivec(i) = uint8(min(255, intval));
end
end


