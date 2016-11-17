function [keyPoint, reRun] = Create_Descriptor(pix, xyScale, tScale, x, y, z)

% Main function of 3DSIFT Program from http://www.cs.ucf.edu/~pscovann/
%
% Inputs:
% pix - a 3 dimensional matrix of uint8
% xyScale and tScale - affects both the scale and the resolution, these are
% usually set to 1 and scaling is done before calling this function
% x, y, and z - the location of the center of the keypoint where a descriptor is requested
%
% Outputs:
% keypoint - the descriptor, varies in size depending on values in LoadParams.m
% reRun - a flag (0 or 1) which is set if the data at (x,y,z) is not
% descriptive enough for a good keypoint
%
% Example:
% See Demo.m

% LoadParams is a .mat files. To modify the parameters, open
% LoadParamsBkp.m and change parameters.
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



ivec = zeros(1, (IndexSize*IndexSize*IndexSize*nFaces));

keyPoint = struct('x',x,'y',y, 'z', z,'xyScale', xyScale, 'tScale', tScale,'ivec', ivec);


reRun = 0;

radius = int16(xyScale * 3.0);

fv = sphere_tri('ico',Tessellation_levels,1,0);
myhist = buildOriHists(x,y,z,radius,pix,fv);

% [yy, ix] = sort(myhist,'descend');
[~, ix] = sort(myhist,'descend');
% Dom_Peak = ix(1);
% Sec_Peak = ix(2);

if (TwoPeak_Flag == 1 && dot(fv.centers(ix(1),:),fv.centers(ix(2),:)) > .9 && dot(fv.centers(ix(1),:),fv.centers(ix(3),:)) > .9)
    disp('MISS : Top 3 orientations within ~25 degree range : Returning with reRun flag set.');
    reRun = 1;
    return;
end
keyPoint = MakeKeypoint(pix, xyScale, tScale, x, y, z);
% [keyX, keyY, keyZ, keyXYScale, keyTScale, keyIvec] = MakeKeypoint(pix, xyScale, tScale, x, y, z);
% keypoint = struct('x', keyX,'y',keyY,'z',keyZ,'xyScale',keyXYScale,'tScale',keyTScale,'ivec',keyIvec);