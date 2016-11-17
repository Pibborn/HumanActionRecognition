function keyPoints = getKeyPoints(I, o, thresh)
coder.varsize('keyPoints');
keyPoints = zeros(0,6);
[height, width, frames, scales] = size(I);
for s = 3 : scales - 1
    for h = 3 : height - 2
        for w = 3 : width - 2
            for f = 3 : frames - 2
                if I(h,w,f,s) > thresh
                    
                    prevScale = I(h-1:h+1,w-1:w+1,f-1:f+1,s-1);
                    nextScale = I(h-1:h+1,w-1:w+1,f-1:f+1,s+1);
                    currScaleNextFrame = I(h-1:h+1,w-1:w+1,f+1,s);
                    currScalePrevFrame = I(h-1:h+1,w-1:w+1,f-1,s);
                    currScaleCurrFrame = [I(h-1,w-1:w+1,f,s) I(h+1,w-1:w+1,f,s) I(h,w-1,f,s) I(h,w+1,f,s)];
                    
                    %% RESHAPING NEIGHBORHOOD ARRAYS TO ROW MATRICES
                    pSet = reshape(prevScale,[1,27]);
                    nSet = reshape(nextScale,[1,27]);
                    cnfSet = reshape(currScaleNextFrame,[1,9]);
                    cpfSet = reshape(currScalePrevFrame,[1,9]);
                    ccfSet = reshape(currScaleCurrFrame,[1,8]);
                    
                    %% CREATING NEIGHBORHOOD ARRAY
                    tempSet = [pSet nSet cnfSet cpfSet ccfSet];
                    % tempSet = sort(tempSet);
                    
                    check = I(h,w,f,s) > tempSet;
                    
                    type = 0;
                    
                    if sum(check) >= 0.97*80
                        % fprintf('Maxima Detected\n');
                        type = 1;
                    else
                        check = I(h,w,f,s) < tempSet;
                        if sum(check) >= 0.97*80
                            type = 2;
                        end
                    end
                    
                    if type ~= 0
                        keyPoints = [keyPoints; [o, s, h, w, f, type] ];
                        % disp([o,s,h,w,f, type]);
                    end
                else
                    % Go to Next Pixel
                end
            end
        end
    end
end
end