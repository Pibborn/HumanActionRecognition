function SS = imgaussian(I, O, S, omin, smin, smax, sigma0, sigman, verb)

if(nargin < 1)
    error('At-least one argument is required.');
end

if ndims(I) > 3
    error('Video must be grayscale color model.');
end

if ~isreal(I)
    error('Video must be real');
end

%% Lowe's choices
k = 2^(1/S);

dsigma0 = sigma0*sqrt(1-1/k^2);

%% Scale Space Structure
SS.O        = O;
SS.S        = S;
SS.sigma0   = sigma0;
SS.omin     = omin;
SS.smin     = smin;
SS.smax     = smax;

%% Resizing Input Video
% omin < 0 : Double Size for More Features
% omin = 0 : Keep the Video of Same Size as Input
% omin > 0 : Half Size for Less Features

if omin < 0
    for o = 1 : -omin
        I = doubleSize(I);
    end
elseif omin > 0
    for o = 1 : omin
        I = halveSize(I);
    end
else
    % Keep the video of same size
end
%% Index Offset
so = -smin + 1;

[H, W, T] = size(I);
sigma = sqrt((sigma0*k^smin)^2  - (sigman/2^omin)^2);
if verb > 0
    fprintf('Creating Octave 1\n');
end

SS.octave{1} = zeros(H, W, T, smax - smin + 1);
SS.octave{1}(:, :, :, 1) = imgaussfilt3(squeeze(I), sigma);
SS.Sigma{1}(1) = sigma;
for s = smin+1 : smax
    dsigma = k^s*dsigma0;
    SS.octave{1}(:,:,:,s+so) = ...
        imgaussfilt3(squeeze(...
        SS.octave{1}(:, :, :, s - 1 + so)),...
        dsigma);
    SS.Sigma{1}(s+so) = dsigma;
end

for o = 2 : O
    if verb > 0
        fprintf('Creating Octave %d\n',o);
    end
    sbest = min(smin + S, smax) ;
    TMP = halveSize(squeeze(...
        SS.octave{o-1}(:, :, :, sbest + so)));
    target_sigma = sigma0 * k^smin ;
    prev_sigma = sigma0 * k^(sbest - S) ;
    
    if(target_sigma > prev_sigma)
        TMP = imgaussfilt3(TMP,...
            sqrt(target_sigma^2 - prev_sigma^2) ) ;
    end
    [H,W,T] = size(TMP) ;
    
    SS.octave{o} = zeros(H, W, T, smax - smin + 1) ;
    SS.octave{o}(:, :, :, 1) = TMP ;
    SS.Sigma{o}(1) = dsigma0;
    for s=smin+1:smax
        dsigma = k^s * dsigma0 ;
        SS.octave{o}(:, :, :, s + so) = ...
            imgaussfilt3(squeeze(...
            SS.octave{o}(:, :, :, s - 1 + so)...
            ), dsigma)  ;
        SS.Sigma{o}(s+so) = dsigma;
    end
end
end

function J = doubleSize(I)
J = interp3(I,'linear');
% J = interpn(I,'linear');
end

function J = halveSize(I)
J = I(1:2:end, 1:2:end);
end