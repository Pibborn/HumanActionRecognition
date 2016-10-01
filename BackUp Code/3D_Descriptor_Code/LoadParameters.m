function output = LoadParameters()
output = zeros(14,1);
% TwoPeak_Flag = 1;  % Allow 3DSIFT to throw out points, Default: 1
output(1,1) = 1;

% IndexSize = 2;  % Min: 1  Default: 2 
output(2,1) = 2;

% Display_flag = 0;  % Display a sphere which can be rotated (Rotate 3D button) to view gradient directions
output(3,1) = 0;

% Tessellation_flag = 1;  % Keep this as 1
output(4,1) = 1;

%Tessellation_levels = 1;  % Min: zero  Default: 1
output(5,1) = 1;

% nFaces = 20 * ( 4 ^ Tessellation_levels );  % Number of faces in the tessellation, not a parameter
output(6,1) = 20 * ( 4 ^ output(5) );

% Smooth_Flag = 1;  % Adds gradient data to surrounding bins in final histogram
output(7,1) = 1;

% Smooth_Var = 20;  % Determines amount of smoothing, Default: 20
output(8,1) = 20;

% The rest of the variables are not modified often, but are included here
% for completeness sake

% IgnoreGradSign = 0;
output(9,1) = 0;

% IndexSigma = 5.0;
output(10,1) = 5.0;

% MagFactor = 3;
output(11,1) = 3;

% UseHistogramOri = 1;
output(12,1) = 1;

% OriHistThresh = 0.8;
output(13,1) = 0.8;

% if (UseHistogramOri)
if (output(13,1))
    OriSigma = 1.5;
else
    OriSigma = 1.0;
end

output(14,1) = OriSigma;
end
