% function key = MakeKeypoint(pix, xyScale, tScale, x, y, z)
function k = MakeKeypoint(pix, xyScale, tScale, x, y, z)
    ktemp = struct('x',x,'y',y,'z',z,'xyScale',...
        xyScale,'tScale',tScale);
    k = struct('x',x,'y',y,'z',z,'xyScale',...
        xyScale,'tScale',tScale,'ivec',MakeKeypointSample(ktemp, pix));
    %{
    k.x = x;
    k.y = y;
    k.z = z;
    k.xyScale = xyScale;
    k.tScale = tScale;
    % key = MakeKeypointSample(k, pix);
    k.ivec = MakeKeypointSample(k, pix);
    %}
    return;
end


% function key = MakeKeypointSample(key, pix)
function ivec = MakeKeypointSample(key, pix)

% LoadParams;
% output = LoadParameters();
% 
%        TwoPeak_Flag = output( 1);
%           IndexSize = output( 2);
%        Display_flag = output( 3);
%   Tessellation_flag = output( 4);
% Tessellation_levels = output( 5);
%              nFaces = output( 6);
%         Smooth_Flag = output( 7);
%          Smooth_Var = output( 8);
%      IgnoreGradSign = output( 9);
%          IndexSigma = output(10);
%           MagFactor = output(11);
%     UseHistogramOri = output(12);
%       OriHistThresh = output(13);
%            OriSigma = output(14);

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
ivec = zeros(1,VecLength);
for i = 1:VecLength
    intval = int16(512.0 * vec(i));
    if ~(intval >= 0)
        disp('Assertation failed in MakeKeypoint.m');
    end
    ivec(i) = uint8(min(255, intval));
end
end