% function [features, oTheta, oMag] = get3DFeature(dogPrev, dogCurr, dogNext, nOctaves, nScales, threshold, conThreshold, curThreshold)
function [features, oTheta, oMag] = get3DFeature(dog, nOctaves, nScales, threshold, conThreshold, curThreshold)
features = [];
oTheta = cell(size(dog));
oMag = cell(size(dog));

featureCount = 1;
for o = 1 : nOctaves                                    % Number of Octaves
    [height, width, frame] = size(dog{o,1});            % Frame Block Dimensions
    for s = 2 : nScales - 1                             % Number of Scales
        for f = 2 : frame - 1                           % Frames from the Video
            fprintf('O - %d, S - %d, F - %d\n',o, s, f);
            for h = 2 : height - 1                      % Height of the Frame
                for w = 2 : width - 1                   % Width of the Frame
                    success = 0;                        % success : 0 Not a feature, : 1 Is a Feature
                    type = 1;                           % Type : 1. Maxima, : 2. Minima
                    trueValue = dog{o,s}(h,w,f);        % Get Current Pixel Value
                    df = dog{o,s}(h,w,f+1) - dog{o,s}(h,w,f-1);
                    dh = dog{o,s}(h+1,w,f) - dog{o,s}(h-1,w,f);
                    dw = dog{o,s}(h,w+1,f) - dog{o,s}(h,w-1,f);
                    
                    % Computing Magnitude of Orientation.
                    oMag{o,s}(h,w,f) = sqrt(power(dh,2) + power(dw,2) + power(df,2));
                    
                    % Computing Angle of the Orientation.
                    oTheta{o,s}(h,w,f) = atan(df/(sqrt(power(dh,2) + power(dw,2))));
                    
                    % pSet = dog{o,s-1}(h-1:h+1, w-1:w+1, f-1:f+1);
                    % cSet = dog{o,s}(h-1:h+1, w-1:w+1, f-1:f+1);
                    % nSet = dog{o,s+1}(h-1:h+1, w-1:w+1, f-1:f+1);
                    
                    % pSet = dog{o,s-1}(h-1:h+1, w-1:w+1, f);
                    % cSet = dog{o,s}(h-1:h+1, w-1:w+1, f);
                    % nSet = dog{o,s+1}(h-1:h+1, w-1:w+1, f);
                    % pfSet = dog{o,s}(h-1:h+1,w-1:w+1,f-1);
                    % nfSet = dog{o,s}(h-1:h+1,w-1:w+1,f+1);
                    
                    % tempSet = [pSet; cSet; nSet; pfSet; nfSet];
                    
                    prevScale = dog{o,s-1}(h-1:h+1,w-1:w+1,f-1:f+1);
                    nextScale = dog{o,s+1}(h-1:h+1,w-1:w+1,f-1:f+1);
                    currScaleNextFrame = dog{o,s}(h-1:h+1,w-1:w+1,f+1);
                    currScalePrevFrame = dog{o,s}(h-1:h+1,w-1:w+1,f-1);
                    currScaleCurrFrame = [dog{o,s}(h-1,w-1:w+1,f) dog{o,s}(h+1,w-1:w+1,f) dog{o,s}(h,w-1,f) dog{o,s}(h,w+1,f)];
                    
                    pSet = reshape(prevScale,[1,27]);
                    nSet = reshape(nextScale,[1,27]);
                    cnfSet = reshape(currScaleNextFrame,[1,9]);
                    cpfSet = reshape(currScalePrevFrame,[1,9]);
                    ccfSet = reshape(currScaleCurrFrame,[1,8]);
                    
                    tempSet = [pSet nSet cnfSet cpfSet ccfSet];
                    tempSet = sort(tempSet);
                    % [success, type] = minMaxCheck(tempSet, threshold, success, type, trueValue);
                    
                    maxCheck = find(tempSet < trueValue);
                    totalNeighbor = length(tempSet);
                    if length(maxCheck)/totalNeighbor > threshold
                        success = 1;
                    else
                        minCheck = find(tempSet > trueValue);
                        if length(minCheck)/totalNeighbor > threshold
                            success = 1;
                            type = 2;
                        end
                    end
                    
                    
                    if success == 1
                        % Translationcount : tCount = 5;
                        % Maximum number of iterations to attempt to localize
                        % the feature
                        tCount = 0;
                        dw = 0;
                        dh = 0;
                        df = 0;
                        
                        H = size(dog{o,1},1);
                        W = size(dog{o,1},2);
                        F = size(dog{o,1},3);
                        
                        th = h;
                        tw = w;
                        tff = f;
                        while tCount < 5
                            if th < H - 1
                                th = th + dh;
                            end
                            if tw < W - 1
                                tw = tw + dw;
                            end
                            if tff < F - 1
                                tff = tff + df;
                            end
                            
                            Dw = 0.5 * (dog{o, s}(th, tw + 1, tff) - dog{o, s}(th, tw - 1, tff));
                            Dh = 0.5 * (dog{o, s}(th + 1, tw, tff) - dog{o, s}(th - 1, tw, tff));
                            Df = 0.5 * (dog{o, s}(th, tw, tff + 1) - dog{o, s}(th, tw, tff - 1));
                            
                            bw = -Dw;
                            bh = -Dh;
                            bf = -Df;
                            
                            if bw > 0.6 && w < W - 2
                                dw = 1;
                            else
                                dw = 0;
                            end
                            
                            if bh > 0.6 && h < H - 2
                                dh = 1;
                            else
                                dh = 0;
                            end
                            
                            if bf > 0.6 && f < F - 2
                                df = 1;
                            else
                                df = 0;
                            end
                            
                            if dw == 0 && dh == 0 && df == 0
                                break;
                            end
                            tCount = tCount + 1;
                        end
                        [curvature, flag, contrast] = calculateCurvature(dog, o, s, tff, th, tw, conThreshold, curThreshold);
                        if flag == 1
                            %{
                            features(featureCount,1) = o;
                            features(featureCount,2) = s;
                            features(featureCount,3) = tff;
                            features(featureCount,4) = th;
                            features(featureCount,5) = tw;
                            features(featureCount,6) = curvature;
                            features(featureCount,7) = contrast;
                            features(featureCount,8) = type;
                            %}
                            features = [features; [o s tff th tw curvature contrast type]];
                            featureCount = featureCount + 1;
                        end
                        f = tff;
                        h = th;
                        w = tw;
                    end
                end
            end
        end
    end
end