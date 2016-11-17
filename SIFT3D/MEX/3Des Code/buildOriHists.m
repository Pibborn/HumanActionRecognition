function myhist = buildOriHists(x,y,z,radius,pix,fv)
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


xi = int16(x);
yi = int16(y);
zi = int16(z);
[rows, cols, slices] = size(pix);
myhist = zeros(1,nFaces);


for r = xi - radius:xi + radius
    for c = yi - radius:yi + radius
        for s = zi - radius:zi + radius
            %          /* Do not use last row or column, which are not valid. */
            if (r >= 1 && c >= 1 && r < rows - 1 && c < cols - 1 && s >= 1 && s < slices - 1)
                [mag, vect] = GetGradOri_vector(pix, r, c, s);
                
                corr_array = fv.centers * vect';

                % [yy, ix] = sort(corr_array,'descend');
                [~, ix] = sort(corr_array, 'descend');
                
                if (Display_flag ==1)
                    plot3(vect(1), vect(2), vect(3), 'k.')
                    plot3(fv.centers(ix(1), 1), fv.centers(ix(1), 2), fv.centers(ix(1), 3), 'b*')
                end
                
                myhist(ix(1)) = myhist(ix(1)) + mag;
            end
        end
    end
end