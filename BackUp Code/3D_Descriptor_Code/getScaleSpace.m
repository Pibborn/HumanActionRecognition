function [gaussRep, diffOfGauss, allSigma] = getScaleSpace(inputFrame, nOctaves, nScales, initSigma)

allSigma = zeros(nOctaves, nScales);
gaussRep = cell(nOctaves, nScales);
diffOfGauss = cell(nOctaves, nScales - 1);
% [M,N,C] = size(inputFrame);
% Default value required by smooth3
% SIZE = 3;
sigma = initSigma;

for octave = 1 : nOctaves
    for scale = 1 : nScales
        fprintf('Octave - %d and Scale - %d\n',octave, scale);
        % disp([octave scale]);
        if octave == 1
            if scale == 1
                SIZE = getSIZE(sigma);
                gaussRep{octave, scale} = smooth3(inputFrame, 'gaussian', SIZE, sigma);
            else
                sigma = sigma * sqrt(2);
                SIZE = getSIZE(sigma);
                gaussRep{octave, scale} = smooth3(gaussRep{octave, scale - 1}, 'gaussian', SIZE, sigma);
                diffOfGauss{octave, scale - 1} = gaussRep{octave, scale} - gaussRep{octave, scale-1};
            end
        else
            if scale == 1
                gaussRep{octave, scale} = subSample(gaussRep{octave - 1, nScales});
            else
                sigma = sigma * sqrt(2);
                SIZE = getSIZE(sigma);
                gaussRep{octave, scale} = smooth3(gaussRep{octave, scale - 1}, 'gaussian', SIZE, sigma);
                diffOfGauss{octave, scale-1} = gaussRep{octave, scale} - gaussRep{octave, scale - 1};
            end
        end
        allSigma(octave, scale) = sigma;
    end
end

end

function [newSIZE] = getSIZE(Sigma)
size = ceil(3*Sigma);
if mod(size,2) == 0
    newSIZE = size - 1;
else
    newSIZE = size;
end
end