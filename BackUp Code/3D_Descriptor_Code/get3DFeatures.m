function [features, oTheta, oMag] = get3DFeatures(dog, nOctaves, nScales, threshold, conThreshold, curThreshold)

oTheta = cell(size(dog));
oMag = cell(size(dog));

featureCount = 1;
for o = 1 : nOctaves                            % Number of Octaves
    [height, width, layer] = size(dog{o,1});    % Frame Block Dimensions
    for s = 2 : nScales - 1                     % Number of Scales
        for l = 2 : layer - 1                   % Frames from the Video
            for h = 2 : height - 1              % Height of the Frame
                for w = 2 : width - 1           % Width of the Frame
                    
                    % success : 0 Not a feature, : 1 Is a Feature
                    success = 0;
                    
                    % Type : 1. Maxima, : 2. Minima
                    type = 1;
                    
                    % Get Current Pixel Value
                    trueValue = dog{o,s}(h,w,l);
                    
                    fL = dog{o,s}(h,w,l+1) - dog{o,s}(h,w,l-1);
                    hL = dog{o,s}(h+1,w,l) - dog{o,s}(h-1,w,l);
                    wL = dog{o,s}(h,w+1,l) - dog{o,s}(h,w-1,l);
                    
                    % Computing Magnitude of Orientation.
                    oMag{o,s}(h,w,l) = sqrt(power(hL,2) + power(wL,2) + power(fL,2));
                    
                    % Computing Angle of the Orientation.
                    oTheta{o,s}(h,w,l) = atan(fL/(sqrt(power(hL,2) + power(wL,2))));
                    
                    if s == 1
                        if h == 1
                            if l == 1 && w == 1
                                cSet = dog{o,s}(h:h+1,w:w+1,l:l+1);
                                nSet = dog{o,s+1}(h:h+1,w:w+1,l:l+1);
                            end
                            if l == 1 && w ~= 1 && w ~= width
                                cSet = dog{o,s}(h:h+1, w-1:w+1, l:l+1);
                                nSet = dog{o,s+1}(h:h+1, w-1:w+1, l:l+1);
                            end
                            if l == 1 && w == width
                                cSet = dog{o,s}(h:h+1, w-1:w, l:l+1);
                                nSet = dog{o,s+1}(h:h+1, w-1:w, l:l+1);
                            end
                            if w == width && l ~= 1 && l ~= layer
                                cSet = dog{o,s}(h:h+1, w-1:w, l-1:l+1);
                                nSet = dog{o,s+1}(h:h+1, w-1:w, l-1:l+1);
                            end
                            if w == width && l == layer
                                cSet = dog{o,s}(h:h+1, w-1:w, l-1:l);
                                nSet = dog{o,s+1}(h:h+1, w-1:w, l-1:l);
                            end
                            if l == layer && w ~= 1 && w~= width
                                cSet = dog{o,s}(h:h+1, w-1:w+1, l-1:l);
                                nSet = dog{o,s+1}(h:h+1, w-1:w+1, l-1:l);
                            end
                            if l == layer && width == 1
                                cSet = dog{o,s}(h:h+1, w:w+1, l-1:l);
                                nSet = dog{o,s+1}(h:h+1, w:w+1, l-1:l);
                            end
                            if l ~= 1 && l~= layer && width == 1
                                cSet = dog{o,s}(h:h+1, w:w+1, l-1:l+1);
                                nSet = dog{o,s+1}(h:h+1, w:w+1, l-1:l+1);
                            end
                            if l ~= 1 && l ~= layer && w ~= width && w ~= 1
                                cSet = dog{o,s}(h:h+1, w-1:w+1, l-1:l+1);
                                nSet = dog{o,s+1}(h:h+1, w-1:w+1, l-1:l+1);
                            end
                        elseif h ~= 1 && h ~= height
                            if l == 1 && w == 1
                                cSet = dog{o,s}(h-1:h+1,w:w+1,l:l+1);
                                nSet = dog{o,s+1}(h-1:h+1,w:w+1,l:l+1);
                            end
                            
                            if l == 1 && w ~= 1 && w ~= width
                                cSet = dog{o,s}(h-1:h+1, w-1:w+1, l:l+1);
                                nSet = dog{o,s+1}(h-1:h+1, w-1:w+1, l:l+1);
                            end
                            if l == 1 && w == width
                                cSet = dog{o,s}(h-1:h+1, w-1:w, l:l+1);
                                nSet = dog{o,s+1}(h-1:h+1, w-1:w, l:l+1);
                            end
                            if w == width && l ~= 1 && l ~= layer
                                cSet = dog{o,s}(h-1:h+1, w-1:w, l-1:l+1);
                                nSet = dog{o,s+1}(h-1:h+1, w-1:w, l-1:l+1);
                            end
                            if w == width && l == layer
                                cSet = dog{o,s}(h-1:h+1, w-1:w, l-1:l);
                                nSet = dog{o,s+1}(h-1:h+1, w-1:w, l-1:l);
                            end
                            if l == layer && w ~= 1 && w~= width
                                cSet = dog{o,s}(h-1:h+1, w-1:w+1, l-1:l);
                                nSet = dog{o,s+1}(h-1:h+1, w-1:w+1, l-1:l);
                            end
                            if l == layer && width == 1
                                cSet = dog{o,s}(h-1:h+1, w:w+1, l-1:l);
                                nSet = dog{o,s+1}(h-1:h+1, w:w+1, l-1:l);
                            end
                            if l ~= 1 && l~= layer && width == 1
                                cSet = dog{o,s}(h-1:h+1, w:w+1, l-1:l+1);
                                nSet = dog{o,s+1}(h-1:h+1, w:w+1, l-1:l+1);
                            end
                            if l ~= 1 && l ~= layer && w ~= width && w ~= 1
                                cSet = dog{o,s}(h-1:h+1, w-1:w+1, l-1:l+1);
                                nSet = dog{o,s+1}(h-1:h+1, w-1:w+1, l-1:l+1);
                            end
                        else
                            if l == 1 && w == 1
                                cSet = dog{o,s}(h-1:h,w:w+1,l:l+1);
                                nSet = dog{o,s+1}(h-1:h,w:w+1,l:l+1);
                            end
                            
                            if l == 1 && w ~= 1 && w ~= width
                                cSet = dog{o,s}(h-1:h, w-1:w+1, l:l+1);
                                nSet = dog{o,s+1}(h-1:h, w-1:w+1, l:l+1);
                            end
                            if l == 1 && w == width
                                cSet = dog{o,s}(h-1:h, w-1:w, l:l+1);
                                nSet = dog{o,s+1}(h-1:h, w-1:w, l:l+1);
                            end
                            if w == width && l ~= 1 && l ~= layer
                                cSet = dog{o,s}(h-1:h, w-1:w, l-1:l+1);
                                nSet = dog{o,s+1}(h-1:h, w-1:w, l-1:l+1);
                            end
                            if w == width && l == layer
                                cSet = dog{o,s}(h-1:h, w-1:w, l-1:l);
                                nSet = dog{o,s+1}(h-1:h, w-1:w, l-1:l);
                            end
                            if l == layer && w ~= 1 && w~= width
                                cSet = dog{o,s}(h-1:h, w-1:w+1, l-1:l);
                                nSet = dog{o,s+1}(h-1:h, w-1:w+1, l-1:l);
                            end
                            if l == layer && width == 1
                                cSet = dog{o,s}(h-1:h, w:w+1, l-1:l);
                                nSet = dog{o,s+1}(h-1:h, w:w+1, l-1:l);
                            end
                            if l ~= 1 && l~= layer && width == 1
                                cSet = dog{o,s}(h-1:h, w:w+1, l-1:l+1);
                                nSet = dog{o,s+1}(h-1:h, w:w+1, l-1:l+1);
                            end
                            if l ~= 1 && l ~= layer && w ~= width && w ~= 1
                                cSet = dog{o,s}(h-1:h, w-1:w+1, l-1:l+1);
                                nSet = dog{o,s+1}(h-1:h, w-1:w+1, l-1:l+1);
                            end
                        end
                        tempSet = [cSet;nSet];
                    elseif s == nScales
                        if h == 1
                            if l == 1 && w == 1
                                cSet = dog{o,s}(h:h+1,w:w+1,l:l+1);
                                pSet = dog{o,s-1}(h:h+1,w:w+1,l:l+1);
                            end
                            if l == 1 && w ~= 1 && w ~= width
                                cSet = dog{o,s}(h:h+1, w-1:w+1, l:l+1);
                                pSet = dog{o,s-1}(h:h+1, w-1:w+1, l:l+1);
                            end
                            if l == 1 && w == width
                                cSet = dog{o,s}(h:h+1, w-1:w, l:l+1);
                                pSet = dog{o,s-1}(h:h+1, w-1:w, l:l+1);
                            end
                            if w == width && l ~= 1 && l ~= layer
                                cSet = dog{o,s}(h:h+1, w-1:w, l-1:l+1);
                                pSet = dog{o,s-1}(h:h+1, w-1:w, l-1:l+1);
                            end
                            if w == width && l == layer
                                cSet = dog{o,s}(h:h+1, w-1:w, l-1:l);
                                pSet = dog{o,s-1}(h:h+1, w-1:w, l-1:l);
                            end
                            if l == layer && w ~= 1 && w~= width
                                cSet = dog{o,s}(h:h+1, w-1:w+1, l-1:l);
                                pSet = dog{o,s-1}(h:h+1, w-1:w+1, l-1:l);
                            end
                            if l == layer && width == 1
                                cSet = dog{o,s}(h:h+1, w:w+1, l-1:l);
                                pSet = dog{o,s-1}(h:h+1, w:w+1, l-1:l);
                            end
                            if l ~= 1 && l~= layer && width == 1
                                cSet = dog{o,s}(h:h+1, w:w+1, l-1:l+1);
                                pSet = dog{o,s-1}(h:h+1, w:w+1, l-1:l+1);
                            end
                            if l ~= 1 && l ~= layer && w ~= width && w ~= 1
                                cSet = dog{o,s}(h:h+1, w-1:w+1, l-1:l+1);
                                pSet = dog{o,s-1}(h:h+1, w-1:w+1, l-1:l+1);
                            end
                        elseif h ~= 1 && h ~= height
                            if l == 1 && w == 1
                                cSet = dog{o,s}(h-1:h+1,w:w+1,l:l+1);
                                pSet = dog{o,s-1}(h-1:h+1,w:w+1,l:l+1);
                            end
                            if l == 1 && w ~= 1 && w ~= width
                                cSet = dog{o,s}(h-1:h+1, w-1:w+1, l:l+1);
                                pSet = dog{o,s-1}(h-1:h+1, w-1:w+1, l:l+1);
                            end
                            if l == 1 && w == width
                                cSet = dog{o,s}(h-1:h+1, w-1:w, l:l+1);
                                pSet = dog{o,s-1}(h-1:h+1, w-1:w, l:l+1);
                            end
                            if w == width && l ~= 1 && l ~= layer
                                cSet = dog{o,s}(h-1:h+1, w-1:w, l-1:l+1);
                                pSet = dog{o,s-1}(h-1:h+1, w-1:w, l-1:l+1);
                            end
                            if w == width && l == layer
                                cSet = dog{o,s}(h-1:h+1, w-1:w, l-1:l);
                                pSet = dog{o,s-1}(h-1:h+1, w-1:w, l-1:l);
                            end
                            if l == layer && w ~= 1 && w~= width
                                cSet = dog{o,s}(h-1:h+1, w-1:w+1, l-1:l);
                                pSet = dog{o,s-1}(h-1:h+1, w-1:w+1, l-1:l);
                            end
                            if l == layer && width == 1
                                cSet = dog{o,s}(h-1:h+1, w:w+1, l-1:l);
                                pSet = dog{o,s-1}(h-1:h+1, w:w+1, l-1:l);
                            end
                            if l ~= 1 && l~= layer && width == 1
                                cSet = dog{o,s}(h-1:h+1, w:w+1, l-1:l+1);
                                pSet = dog{o,s-1}(h-1:h+1, w:w+1, l-1:l+1);
                            end
                            if l ~= 1 && l ~= layer && w ~= width && w ~= 1
                                cSet = dog{o,s}(h-1:h+1, w-1:w+1, l-1:l+1);
                                pSet = dog{o,s-1}(h-1:h+1, w-1:w+1, l-1:l+1);
                            end
                        else
                            if l == 1 && w == 1
                                cSet = dog{o,s}(h-1:h,w:w+1,l:l+1);
                                pSet = dog{o,s-1}(h-1:h,w:w+1,l:l+1);
                            end
                            if l == 1 && w ~= 1 && w ~= width
                                cSet = dog{o,s}(h-1:h, w-1:w+1, l:l+1);
                                pSet = dog{o,s-1}(h-1:h, w-1:w+1, l:l+1);
                            end
                            if l == 1 && w == width
                                cSet = dog{o,s}(h-1:h, w-1:w, l:l+1);
                                pSet = dog{o,s-1}(h-1:h, w-1:w, l:l+1);
                            end
                            if w == width && l ~= 1 && l ~= layer
                                cSet = dog{o,s}(h-1:h, w-1:w, l-1:l+1);
                                pSet = dog{o,s-1}(h-1:h, w-1:w, l-1:l+1);
                            end
                            if w == width && l == layer
                                cSet = dog{o,s}(h-1:h, w-1:w, l-1:l);
                                pSet = dog{o,s-1}(h-1:h, w-1:w, l-1:l);
                            end
                            if l == layer && w ~= 1 && w~= width
                                cSet = dog{o,s}(h-1:h, w-1:w+1, l-1:l);
                                pSet = dog{o,s-1}(h-1:h, w-1:w+1, l-1:l);
                            end
                            if l == layer && width == 1
                                cSet = dog{o,s}(h-1:h, w:w+1, l-1:l);
                                pSet = dog{o,s-1}(h-1:h, w:w+1, l-1:l);
                            end
                            if l ~= 1 && l~= layer && width == 1
                                cSet = dog{o,s}(h-1:h, w:w+1, l-1:l+1);
                                pSet = dog{o,s-1}(h-1:h, w:w+1, l-1:l+1);
                            end
                            if l ~= 1 && l ~= layer && w ~= width && w ~= 1
                                cSet = dog{o,s}(h-1:h, w-1:w+1, l-1:l+1);
                                pSet = dog{o,s-1}(h-1:h, w-1:w+1, l-1:l+1);
                            end
                        end
                        tempSet = [cSet;pSet];
                    else
                        if h == 1
                            if l == 1 && w == 1
                                pSet = dog{o,s-1}(h:h+1,w:w+1,l:l+1);
                                cSet = dog{o,s}(h:h+1,w:w+1,l:l+1);
                                nSet = dog{o,s+1}(h:h+1,w:w+1,l:l+1);
                            end
                            
                            if l == 1 && w ~= 1 && w ~= width
                                pSet = dog{o,s-1}(h:h+1, w-1:w+1, l:l+1);
                                cSet = dog{o,s}(h:h+1, w-1:w+1, l:l+1);
                                nSet = dog{o,s+1}(h:h+1, w-1:w+1, l:l+1);
                            end
                            if l == 1 && w == width
                                pSet = dog{o,s-1}(h:h+1, w-1:w, l:l+1);
                                cSet = dog{o,s}(h:h+1, w-1:w, l:l+1);
                                nSet = dog{o,s+1}(h:h+1, w-1:w, l:l+1);
                            end
                            if w == width && l ~= 1 && l ~= layer
                                pSet = dog{o,s-1}(h:h+1, w-1:w, l-1:l+1);
                                cSet = dog{o,s}(h:h+1, w-1:w, l-1:l+1);
                                nSet = dog{o,s+1}(h:h+1, w-1:w, l-1:l+1);
                            end
                            if w == width && l == layer
                                pSet = dog{o,s-1}(h:h+1, w-1:w, l-1:l);
                                cSet = dog{o,s}(h:h+1, w-1:w, l-1:l);
                                nSet = dog{o,s+1}(h:h+1, w-1:w, l-1:l);
                            end
                            if l == layer && w ~= 1 && w~= width
                                pSet = dog{o,s-1}(h:h+1, w-1:w+1, l-1:l);
                                cSet = dog{o,s}(h:h+1, w-1:w+1, l-1:l);
                                nSet = dog{o,s+1}(h:h+1, w-1:w+1, l-1:l);
                            end
                            if l == layer && width == 1
                                pSet = dog{o,s-1}(h:h+1, w:w+1, l-1:l);
                                cSet = dog{o,s}(h:h+1, w:w+1, l-1:l);
                                nSet = dog{o,s+1}(h:h+1, w:w+1, l-1:l);
                            end
                            if l ~= 1 && l~= layer && width == 1
                                pSet = dog{o,s-1}(h:h+1, w:w+1, l-1:l+1);
                                cSet = dog{o,s}(h:h+1, w:w+1, l-1:l+1);
                                nSet = dog{o,s+1}(h:h+1, w:w+1, l-1:l+1);
                            end
                            if l ~= 1 && l ~= layer && w ~= width && w ~= 1
                                pSet = dog{o,s-1}(h:h+1, w-1:w+1, l-1:l+1);
                                cSet = dog{o,s}(h:h+1, w-1:w+1, l-1:l+1);
                                nSet = dog{o,s+1}(h:h+1, w-1:w+1, l-1:l+1);
                            end
                        elseif h ~= 1 && h ~= height
                            if l == 1 && w == 1
                                pSet = dog{o,s-1}(h-1:h+1,w:w+1,l:l+1);
                                cSet = dog{o,s}(h-1:h+1,w:w+1,l:l+1);
                                nSet = dog{o,s+1}(h-1:h+1,w:w+1,l:l+1);
                            end
                            
                            if l == 1 && w ~= 1 && w ~= width
                                pSet = dog{o,s-1}(h-1:h+1, w-1:w+1, l:l+1);
                                cSet = dog{o,s}(h-1:h+1, w-1:w+1, l:l+1);
                                nSet = dog{o,s+1}(h-1:h+1, w-1:w+1, l:l+1);
                            end
                            if l == 1 && w == width
                                pSet = dog{o,s-1}(h-1:h+1, w-1:w, l:l+1);
                                cSet = dog{o,s}(h-1:h+1, w-1:w, l:l+1);
                                nSet = dog{o,s+1}(h-1:h+1, w-1:w, l:l+1);
                            end
                            if w == width && l ~= 1 && l ~= layer
                                pSet = dog{o,s-1}(h-1:h+1, w-1:w, l-1:l+1);
                                cSet = dog{o,s}(h-1:h+1, w-1:w, l-1:l+1);
                                nSet = dog{o,s+1}(h-1:h+1, w-1:w, l-1:l+1);
                            end
                            if w == width && l == layer
                                pSet = dog{o,s-1}(h-1:h+1, w-1:w, l-1:l);
                                cSet = dog{o,s}(h-1:h+1, w-1:w, l-1:l);
                                nSet = dog{o,s+1}(h-1:h+1, w-1:w, l-1:l);
                            end
                            if l == layer && w ~= 1 && w~= width
                                pSet = dog{o,s-1}(h-1:h+1, w-1:w+1, l-1:l);
                                cSet = dog{o,s}(h-1:h+1, w-1:w+1, l-1:l);
                                nSet = dog{o,s+1}(h-1:h+1, w-1:w+1, l-1:l);
                            end
                            if l == layer && width == 1
                                pSet = dog{o,s-1}(h-1:h+1, w:w+1, l-1:l);
                                cSet = dog{o,s}(h-1:h+1, w:w+1, l-1:l);
                                nSet = dog{o,s+1}(h-1:h+1, w:w+1, l-1:l);
                            end
                            if l ~= 1 && l~= layer && width == 1
                                pSet = dog{o,s-1}(h-1:h+1, w:w+1, l-1:l+1);
                                cSet = dog{o,s}(h-1:h+1, w:w+1, l-1:l+1);
                                nSet = dog{o,s+1}(h-1:h+1, w:w+1, l-1:l+1);
                            end
                            if l ~= 1 && l ~= layer && w ~= width && w ~= 1
                                pSet = dog{o,s-1}(h-1:h+1, w-1:w+1, l-1:l+1);
                                cSet = dog{o,s}(h-1:h+1, w-1:w+1, l-1:l+1);
                                nSet = dog{o,s+1}(h-1:h+1, w-1:w+1, l-1:l+1);
                            end
                        else
                            if l == 1 && w == 1
                                pSet = dog{o,s-1}(h-1:h,w:w+1,l:l+1);
                                cSet = dog{o,s}(h-1:h,w:w+1,l:l+1);
                                nSet = dog{o,s+1}(h-1:h,w:w+1,l:l+1);
                            end
                            
                            if l == 1 && w ~= 1 && w ~= width
                                pSet = dog{o,s-1}(h-1:h, w-1:w+1, l:l+1);
                                cSet = dog{o,s}(h-1:h, w-1:w+1, l:l+1);
                                nSet = dog{o,s+1}(h-1:h, w-1:w+1, l:l+1);
                            end
                            if l == 1 && w == width
                                pSet = dog{o,s-1}(h-1:h, w-1:w, l:l+1);
                                cSet = dog{o,s}(h-1:h, w-1:w, l:l+1);
                                nSet = dog{o,s+1}(h-1:h, w-1:w, l:l+1);
                            end
                            if w == width && l ~= 1 && l ~= layer
                                pSet = dog{o,s-1}(h-1:h, w-1:w, l-1:l+1);
                                cSet = dog{o,s}(h-1:h, w-1:w, l-1:l+1);
                                nSet = dog{o,s+1}(h-1:h, w-1:w, l-1:l+1);
                            end
                            if w == width && l == layer
                                pSet = dog{o,s-1}(h-1:h, w-1:w, l-1:l);
                                cSet = dog{o,s}(h-1:h, w-1:w, l-1:l);
                                nSet = dog{o,s+1}(h-1:h, w-1:w, l-1:l);
                            end
                            if l == layer && w ~= 1 && w~= width
                                pSet = dog{o,s-1}(h-1:h, w-1:w+1, l-1:l);
                                cSet = dog{o,s}(h-1:h, w-1:w+1, l-1:l);
                                nSet = dog{o,s+1}(h-1:h, w-1:w+1, l-1:l);
                            end
                            if l == layer && width == 1
                                pSet = dog{o,s-1}(h-1:h, w:w+1, l-1:l);
                                cSet = dog{o,s}(h-1:h, w:w+1, l-1:l);
                                nSet = dog{o,s+1}(h-1:h, w:w+1, l-1:l);
                            end
                            if l ~= 1 && l~= layer && width == 1
                                pSet = dog{o,s-1}(h-1:h, w:w+1, l-1:l+1);
                                cSet = dog{o,s}(h-1:h, w:w+1, l-1:l+1);
                                nSet = dog{o,s+1}(h-1:h, w:w+1, l-1:l+1);
                            end
                            if l ~= 1 && l ~= layer && w ~= width && w ~= 1
                                pSet = dog{o,s-1}(h-1:h, w-1:w+1, l-1:l+1);
                                cSet = dog{o,s}(h-1:h, w-1:w+1, l-1:l+1);
                                nSet = dog{o,s+1}(h-1:h, w-1:w+1, l-1:l+1);
                            end
                        end
                        tempSet = [pSet;cSet;nSet];
                    end
                    
                    [success, type] = minMaxCheck(tempSet, threshold, success, type, trueValue);
                    
                    if success == 1
                    % Translationcount : tCount = 5;
                    % Maximum number of iterations to attempt to localize 
                    % the feature
                        tCount = 0;
                        dw = 0;
                        dh = 0;
                        dl = 0;
                        
                        H = size(dog{o,1},1);
                        W = size(dog{o,1},2);
                        L = size(dog{o,1},3);
                        
                        th = h;
                        tw = w;
                        tl = l;
                        while tCount < 5
                            if th < H - 1
                                th = th + dh;
                            end
                            if tw < W - 1
                                tw = tw + dw;
                            end
                            if tl < L - 1
                                tl = tl + dl;
                            end
                            
                            Dw = 0.5 * (dog{o, s}(th, tw + 1, l) - dog{o, s}(th, tw - 1, l));
                            Dh = 0.5 * (dog{o, s}(th + 1, tw, l) - dog{o, s}(th - 1, tw, l));
                            Dl = 0.5 * (dog{o, s}(th, tw, l + 1) - dog{o, s}(th, tw, l - 1));
                            
                            bw = -Dw;
                            bh = -Dh;
                            bl = -Dl;
                            
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
                            
                            if bl > 0.6 && l < L - 2
                                dl = 1;
                            else
                                dl = 0;
                            end
                            
                            if dw == 0 && dh == 0 && dl == 0
                                break;
                            end
                            tCount = tCount + 1;
                        end
                        [curvature, flag, contrast] = calculateCurvature(dog, o, s, tl, th, tw, conThreshold, curThreshold);
                        if flag == 1
                            features(featureCount,1) = o;
                            features(featureCount,2) = s;
                            features(featureCount,3) = tl;
                            features(featureCount,4) = th;
                            features(featureCount,5) = tw;
                            features(featureCount,6) = curvature;
                            features(featureCount,7) = contrast;
                            features(featureCount,8) = type;
                            featureCount = featureCount + 1;
                        end
                        % l = tl;
                        % h = th;
                        % w = tw;
                    end
                end
            end
        end
    end
end