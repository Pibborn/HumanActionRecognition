function index = KeySample(key, pix)

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

fv = sphere_tri('ico', Tessellation_levels, 1, 0);


irow = int16(key.x); % x
icol = int16(key.y); % y
islice = int16(key.z); % t

xySpacing = key.xyScale * MagFactor;
tSpacing = key.tScale * MagFactor;

xyRadius = 1.414 * xySpacing * (IndexSize + 1) / 2.0;
tRadius = 1.414 * tSpacing * (IndexSize + 1) / 2.0;
xyiradius = int16(xyRadius);
tiradius = int16(tRadius);

index = zeros(IndexSize,IndexSize,IndexSize,nFaces);

for i = -xyiradius : xyiradius
    for j = -xyiradius : xyiradius
        for s = -tiradius : tiradius

            % This is redundant and probably slows down the code, but at
            % some point this solved a major overflow headache, so leaving
            % as-is for now
            i2 = double(i);
            j2 = double(j);
            s2 = double(s);
            distsq = double(i2^2 + j2^2 + s2^2);

            v0 = [i2; j2; s2];

            i_indx = int16(floor(double((i + xyiradius)) / double((2*xyiradius/IndexSize)))) + 1;
            j_indx = int16(floor(double((j + xyiradius)) / double((2*xyiradius/IndexSize)))) + 1;
            s_indx = int16(floor(double((s + tiradius )) / double((2*tiradius/IndexSize )))) + 1;
            
            if i_indx > IndexSize
                % i_indx = IndexSize;
                i_indx = cast(IndexSize,'int16');
            end
            if j_indx > IndexSize
                % j_indx = IndexSize;
                j_indx = cast(IndexSize,'int16');
            end
            if s_indx > IndexSize
                %s_indx = IndexSize;
                s_indx = cast(IndexSize,'int16');
            end

            if (i_indx < 1 || j_indx < 1 || s_indx < 1)
                disp('Something wrong with the sub-histogram index');
            end
            
           
            r = irow + v0(1);
            c = icol + v0(2);
            t = islice + v0(3);
            
            index = AddSample(index, key, pix, distsq, r, c, t, i_indx, j_indx, s_indx, fv);
            
        end
    end
end
