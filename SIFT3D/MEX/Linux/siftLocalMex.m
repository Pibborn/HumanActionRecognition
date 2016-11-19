function idx = siftLocalMex(I, o, threshold, neighbor)
idx = [];
[H, W, T, S] = size(I);

for s = 2 : (S - 1)
    for h = 2 : (H - 1)
        for w = 2 : (W - 1)
            for t = 2 : (T - 1)
                % Weak Point Elimination
                if I(h, w, t, s) > threshold
                    prevScale = I(h - 1 : h + 1,...
                                  w - 1 : w + 1,...
                                  t - 1 : t + 1,...
                                  s - 1);
                    nextScale = I(h - 1 : h + 1,...
                                  w - 1 : w + 1,...
                                  t - 1 : t + 1,...
                                  s + 1);
                    currScalePrevFrame = I(h - 1 : h + 1,...
                                          w - 1 : w + 1,...
                                          t - 1, s);
                    currScaleNextFrame = I(h - 1 : h + 1,...
                                          w - 1 : w + 1,...
                                          t + 1, s);
                    currScaleCurrFrame = [I(h - 1, w - 1 : w + 1, t, s)...
                                          I(h + 1, w - 1 : w + 1, t, s)...
                                          I(h, w - 1, t, s)...
                                          I(h, w + 1, t, s)];
                    
                    %% RESHAPING NEIGHBORHOOD ARRAYS TO ROW MATRICES
                    pSet = reshape(prevScale, [1, 27]);
                    nSet = reshape(nextScale, [1, 27]);
                    cnfSet = reshape(currScaleNextFrame, [1, 9]);
                    cpfSet = reshape(currScalePrevFrame, [1, 9]);
                    ccfSet = reshape(currScaleCurrFrame, [1, 8]);
                    
                    %% CREATING NEIGHBORHOOD ARRAY
                    tempSet = [pSet nSet cnfSet cpfSet ccfSet];
                    
                    check = I(h, w, t, s) > tempSet;
                    
                    type = 0;
                    
                    %% EXTREMA DETECTION
                    if sum(check) >= (neighbor * 80)
                        % Local Maxima Extrema
                        type = 1;
                    else
                        % Local Minima Extrema
                        check = I(h, w, t, s) < tempSet;
                        if sum(check) >= (neighbor * 80)
                            type = 2;
                        end
                    end
                    
                    if type ~= 0
                        idx = [idx; [o, s, h, w, t, type] ];
                    end
                end
            end
        end
    end
end

end
