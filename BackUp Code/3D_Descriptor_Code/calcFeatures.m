function [features, oMag, oTheta ]= calcFeatures(gss, dog, nOctaves, nScales, threshold)

features = zeros(1,6);
% DIRECTION OF FEATURE
oTheta = cell(nOctaves,nScales);
% FEATURE MAGNITUDE
oMag = cell(nOctaves,nScales);                                              
for o = 1 : nOctaves                                                       % # OF OCTAVE IN SCALE-SPACE
    [height, width, frame] = size(dog{o,1});                               % GROUP-of-FRAMES[GoF] DIMENSIONS
    for s = 2 : nScales                                                    % # OF SCALES IN AN OCTAVE
        for f = 2 : frame - 1                                              % # OF FRAMES IN GoF(t)
            fprintf('Octave: %d, Scale : %d, Frame: %d\n',o,s,f);
            for h = 2 : height - 1                                         % FRAME HEIGHT(y)
                for w = 2 : width - 1                                      % FRAME WIDTH(x)
                    success = 0;                                           % success : 0 IS NOT A FEATURE, : 1 IS A FEATURE
                    type = 1;                                              % TYPE : 1. MAXIMA and 2. MINIMA
                    
                    %% EXTRACTING LOCAL PIXEL VALUES
                    trueValue = dog{o,s}(h,w,f);
                    
                    %% DETERMINING TEH NEIGHBORHOOD
                    prevScale = dog{o,s-1}(h-1:h+1,w-1:w+1,f-1:f+1);
                    nextScale = dog{o,s+1}(h-1:h+1,w-1:w+1,f-1:f+1);
                    currScaleNextFrame = dog{o,s}(h-1:h+1,w-1:w+1,f+1);
                    currScalePrevFrame = dog{o,s}(h-1:h+1,w-1:w+1,f-1);
                    currScaleCurrFrame = [dog{o,s}(h-1,w-1:w+1,f) dog{o,s}(h+1,w-1:w+1,f) dog{o,s}(h,w-1,f) dog{o,s}(h,w+1,f)];
                    
                    %% RESHAPING NEIGHBORHOOD ARRAYS TO ROW MATRICES
                    pSet = reshape(prevScale,[1,27]);
                    nSet = reshape(nextScale,[1,27]);
                    cnfSet = reshape(currScaleNextFrame,[1,9]);
                    cpfSet = reshape(currScalePrevFrame,[1,9]);
                    ccfSet = reshape(currScaleCurrFrame,[1,8]);
                    
                    %% CREATING NEIGHBORHOOD ARRAY
                    tempSet = [pSet nSet cnfSet cpfSet ccfSet];
                    tempSet = sort(tempSet);
                    
                    %% LOCAL MAXIMA CHECK
                    maxCheck = find(tempSet < trueValue);
                    totalNeighbor = length(tempSet);
                    if length(maxCheck)/totalNeighbor >= threshold
                        success = 1;
                    else
                        % LOCAL MINIMA CHECK
                        minCheck = find(tempSet > trueValue);
                        if length(minCheck)/totalNeighbor >= threshold
                            success = 1;
                            type = 2;
                        end
                    end
                    
                    %% COMPUTING FIRST DERIVATIVES
                    df = gss{o,s}(h,w,f+1) - gss{o,s}(h,w,f-1);
                    dh = gss{o,s}(h+1,w,f) - gss{o,s}(h-1,w,f);
                    dw = gss{o,s}(h,w+1,f) - gss{o,s}(h,w-1,f);

                    %% COMPUTING THE MAGNITUDE OF FEATURE
                    oMag{o,s}(h,w,f) = sqrt(power(dh,2) + power(dw,2) + power(df,2));
                    
                    %% COMPUTING THE FEATURE DIRECTION
                    oTheta{o,s}(h,w,f) = atand(df/(sqrt(power(dh,2) + power(dw,2))));
                    if success == 1
                        features = [features; [o s f h w type]];
                    end
                    
                end
            end
        end
    end
end
features( features(:, 1) == 0, :) = [];