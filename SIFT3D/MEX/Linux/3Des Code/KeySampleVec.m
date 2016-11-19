function vec = KeySampleVec(key, pix)
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
% TwoPeak_Flags = lData.TwoPeak_Flag;
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

% Method 1
index = KeySample(key, pix);
vec = index(:);

% % Method 2
% index = KeySample2D(key, grad, ori, scale, row, col);
% vec = index(:);

% % Method 3
% n = 0;
% orig_frame = key.frame;
% for t_offset=-4:4
%     key.frame = orig_frame + t_offset;
%     index = KeySample2D(key, grad, ori, scale, row, col);
%     vec_temp = index(:);
%     n = n + 1;
%     vec((n-1)*length(vec_temp)+1:n*length(vec_temp)) = vec_temp;
% end
% key.frame = orig_frame;
% vec = vec';

% % Method 4
% index = KeySample2D(key, grad, ori, scale, row, col);
% index = KeySample2Dxt(key, grad, ori, scale, row, col);
% index = KeySample2Dyt(key, grad, ori, scale, row, col);


end
