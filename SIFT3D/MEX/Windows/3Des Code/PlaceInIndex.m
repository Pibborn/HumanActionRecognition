function index = PlaceInIndex(index, mag, vect, i, j, s, fv)

% LoadParams;
% lData = load('LoadParams');
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
corr_array = fv.centers * vect';

[yy, ix] = sort(corr_array,'descend');

if (Smooth_Flag == 0)
    index(i,j,s,ix(1)) = index(i,j,s,ix(1)) + mag;
elseif (Smooth_Flag == 1)
    tmpsum = sum(yy(1:3).^Smooth_Var);
    for ii=1:3
        index(i,j,s,ix(ii)) = index(i,j,s,ix(ii)) + ( mag * ( yy(ii) .^ Smooth_Var ) / tmpsum );
    end
end
