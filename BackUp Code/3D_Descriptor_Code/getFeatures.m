% function features = getFeatures(dogPrev, dogCurr, dogNext, o, s, threshold, conThreshold, curThreshold, nOrientBins, nOrientNeighbors)
function features = getFeatures(dog, nOctaves, nScales, keyPointThreshold, conThreshold, curThreshold)
% function [features, oTheta, oMag] = getFeatures(dogPrev, dogCurr, dogNext, o, s, threshold, conThreshold, curThreshold, nOrientBins, nOrientNeighbors)
% function [features, oTheta, oMag] = get3DFeature(dog, nOctaves, nScales, threshold, conThreshold, curThreshold)
features = zeros(1,8);
descriptors = zeros(1,256);
[height, width, frame] = size(dogCurr);                                         % Frame Block Dimensions
oTheta = zeros(height, width, frame);                                           % Angle of Orientation
oMag = zeros(height, width, frame);                                             % Length of Orientation/Magnitude
for f = 2 : frame - 1  
    disp(f);
    for h = 2 : height - 1    
        parfor w = 2 : width - 1                                                   % Width of the Frame
            
            success = 0;                                                        % success : 0 Not a feature, : 1 Is a Feature
            type = 1;                                                           % Type : 1. Maxima, : 2. Minima
            
            %% Extracting Current Pixel value
            trueValue = dogCurr(h,w,f);                                         
            
            %% Computing First Derivatives
            df = dogCurr(h,w,f+1) - dogCurr(h,w,f-1);
            dh = dogCurr(h+1,w,f) - dogCurr(h-1,w,f);
            dw = dogCurr(h,w+1,f) - dogCurr(h,w-1,f);
            
            %% Computing Magnitude of Orientation.
            oMag(h,w,f) = sqrt(power(dh,2) + power(dw,2) + power(df,2));
             
            %% Computing Angle of the Orientation.
            oTheta(h,w,f) = atand(df/(sqrt(power(dh,2) + power(dw,2))));
            
            %% Determing the neighborhood
            prevScale = dogPrev(h-1:h+1,w-1:w+1,f-1:f+1);
            nextScale = dogNext(h-1:h+1,w-1:w+1,f-1:f+1);
            currScaleNextFrame = dogCurr(h-1:h+1,w-1:w+1,f+1);
            currScalePrevFrame = dogCurr(h-1:h+1,w-1:w+1,f-1);
            currScaleCurrFrame = [dogCurr(h-1,w-1:w+1,f) dogCurr(h+1,w-1:w+1,f) dogCurr(h,w-1,f) dogCurr(h,w+1,f)];
            
            %% Reshaping the neighborhood matrices
            pSet = reshape(prevScale,[1,27]);
            nSet = reshape(nextScale,[1,27]);
            cnfSet = reshape(currScaleNextFrame,[1,9]);
            cpfSet = reshape(currScalePrevFrame,[1,9]);
            ccfSet = reshape(currScaleCurrFrame,[1,8]);
            
            %% Creating Neighborhood Array
            tempSet = [pSet nSet cnfSet cpfSet ccfSet];
            tempSet = sort(tempSet);
            
            %% Local Maxima Check
            maxCheck = find(tempSet < trueValue);
            totalNeighbor = length(tempSet);
            if length(maxCheck)/totalNeighbor >= threshold
                success = 1;
            else
                % Local Minima Check
                minCheck = find(tempSet > trueValue);
                if length(minCheck)/totalNeighbor >= threshold
                    success = 1;
                    type = 2;
                end
            end
            
            if success == 1
                %% Translationcount : tCount = 5;
                % Maximum number of iterations to attempt to localize the feature
                tCount = 0;
                dw = 0;
                dh = 0;
                df = 0;
                
                [H, W, F] = size(dogCurr);
                
                ht = h;
                wt = w;
                ft = f;
                %% Feature Localization
                while tCount < 5
                    if ht < H - 1
                        ht = ht + dh;
                    end
                    if wt < W - 1
                        wt = wt + dw;
                    end
                    if ft < F - 1
                        ft = ft + df;
                    end
                    
                    Dw = 0.5 * (dogCurr(ht, wt + 1, ft) - dogCurr(ht, wt - 1, ft));
                    Dh = 0.5 * (dogCurr(ht + 1, wt, ft) - dogCurr(ht - 1, wt, ft));
                    Df = 0.5 * (dogCurr(ht, wt, ft + 1) - dogCurr(ht, wt, ft - 1));
                    
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
                
                %% Calculating Curvature Ratio
                [curvature, flag, contrast] = calculateCurvature(dogPrev, dogCurr, dogNext, ft, ht, wt, conThreshold, curThreshold);
                
                %% Appending Feature to Feature Arrat
                if flag == 1
                    features = [features; [o s ft ht wt curvature contrast type]];
                    
                    %{
                    nTheta = zeros(nOrientNeighbors);
                    nMag = zeros(nOrientNeighbors);
                    
                    if 
                    %}

                    % descriptors = [descriptors; computeDescriptor(dogPrev, dogCurr, dogNext, ft, ht, wt)];
                end
                %{
                f = ft;
                h = ht;
                w = wt;
                %}
            end
        end
    end
end