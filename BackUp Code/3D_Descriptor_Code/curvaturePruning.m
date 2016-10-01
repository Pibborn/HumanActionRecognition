function [newFeatures] = curvaturePruning(gss, features, curThreshold, conThreshold)

newFeatures = [];
featureCount = 1;

for feature = 1 : size(features, 1)
    
    o = features(feature,1);
    s = features(feature,2);
    f = features(feature,3);
    h = features(feature,4);
    w = features(feature,5);
    
    % # OF ITERATIONS TO LOCALIZE FEATURE : tCount : 5
    tCount = 0;
    dw = 0;
    dh = 0;
    df = 0;
    
    [H, W, F] = size(gss{o,s});
    
    ht = h;
    wt = w;
    ft = f;
    % FEATURE LOCALIZATION
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
        
        Dw = 0.5 * (gss{o,s}(ht, wt + 1, ft) - gss{o,s}(ht, wt - 1, ft));
        Dh = 0.5 * (gss{o,s}(ht + 1, wt, ft) - gss{o,s}(ht - 1, wt, ft));
        Df = 0.5 * (gss{o,s}(ht, wt, ft + 1) - gss{o,s}(ht, wt, ft - 1));
        
        bw = -Dw;
        bh = -Dh;
        bf = -Df;
        
        if bw > 0.6 && w < W - 1
            dw = 1;
        else
            dw = 0;
        end
        
        if bh > 0.6 && h < H - 1
            dh = 1;
        else
            dh = 0;
        end
        
        if bf > 0.6 && f < F - 1
            df = 1;
        else
            df = 0;
        end
        
        if dw == 0 && dh == 0 && df == 0
            break;
        end
        tCount = tCount + 1;
    end
    
    % CALCULATING CURVATURE RATIO
    % [curvature, flag, contrast] = calculateCurvature(gss{o,s-1}, gss{o,s}, gss{o,s+1}, ft, ht, wt, conThreshold, curThreshold);

    r = curThreshold;
    c = conThreshold;
    
    % includeScale = 0 : no scale , 1 : yes scale
    includeScale = 0;
    
    %% COMPUTING GRADIENTS
    dw = 0.5 * (gss{o,s}(h,w+1,f) - gss{o,s}(h,w-1,f));
    dh = 0.5 * (gss{o,s}(h+1,w,f) - gss{o,s}(h-1,w,f));
    df = 0.5 * (gss{o,s}(h,w,f+1) - gss{o,s}(h,w,f-1));
    ds = 0.5 * (gss{o,s+1}(h,w,f) - gss{o,s-1}(h,w,f));
    
    %% CALCULATING HESSIAN COEFFICIENTS
    % SECOND-DEGREE COEFFICIENTS
    % COMPUTING DIAGONAL COEFFICIENTS OF HESSIAN MATRIX 
    dww = gss{o,s}(h,w+1,f) + gss{o,s}(h,w-1,f) - (2*gss{o,s}(h,w,f));
    dhh = gss{o,s}(h+1,w,f) + gss{o,s}(h-1,w,f) - (2*gss{o,s}(h,w,f));
    dff = gss{o,s}(h,w,f+1) + gss{o,s}(h,w,f-1) - (2*gss{o,s}(h,w,f));
    dss = gss{o,s+1}(h,w,f) + gss{o,s-1}(h,w,f) - (2*gss{o,s}(h,w,f));
    
    %% COMPUTING NON-DIAGONAL COEFFICIENT OF HESSIAN MATRIX
    dwh = gss{o,s}(h+1,w+1,f) + gss{o,s}(h-1,w-1,f) - ...
        (2*(gss{o,s}(h+1,w-1,f) + gss{o,s}(h-1,w+1,f)));
    dhf = gss{o,s}(h+1,w,f+1) + gss{o,s}(h-1,w,f-1) - ...
        (2*(gss{o,s}(h-1,w,f+1) + gss{o,s}(h+1,w,f-1)));
    dwf = gss{o,s}(h,w+1,f+1) + gss{o,s}(h,w-1,f-1) - ...
        (2*(gss{o,s}(h,w+1,f-1) + gss{o,s}(h,w-1,f+1)));
    dhs = gss{o,s+1}(h+1,w,f) + gss{o,s-1}(h-1,w,f) - ...
        (2*(gss{o,s+1}(h-1,w,f) + gss{o,s-1}(h+1,w,f)));
    dws = gss{o,s+1}(h,w+1,f) + gss{o,s-1}(h,w-1,f) - ...
        (2*(gss{o,s+1}(h,w-1,f) + gss{o,s-1}(h,w+1,f)));
    dfs = gss{o,s+1}(h,w,f+1) + gss{o,s-1}(h,w,f-1) - ...
        (2*(gss{o,s+1}(h,w,f-1) + gss{o,s-1}(h,w,f+1)));
    
    %% COMPUTING HESSIAN MATRIX
    if includeScale == 0
        H = [dww dwh dwf;...
            dwh dhh dhf;...
            dwf dhf dff];
    else
        H = [dww dwh dwf dws;...
            dwh dhh dhf dhs;...
            dwf dhf dff dfs;...
            dws dhs dfs dss];
    end
    
    %% EXTRACTING MINIMUM AND MAXIMUM EIGEN VALUE
    % eMax = max(diag(H));
    % eMin = max(diag(H));
    
    %% EIGENVALUE BASED CURVATURE RATIO
    % r = eMax/eMin;
    % r = 10;
    
    %% COMPUTING CURVATURE RATIO
    traceH = trace(H);
    detH = det(H);
    curvature = power(traceH,1)/detH;
    
    %% COMPUTING CONTRAST
    if includeScale == 0
        contrast = abs(gss{o,s}(h,w,f) + (0.5*(dw*dw + dh*dh + df*df)));
    else
        contrast = abs(gss{o,s}(h,w,f) + (0.5*(dw*dw + dh*dh + df*df + ds*ds)));
    end

    % APPENDING FEATURE TO FEATURE ARRAY
    % if flag == 1
    %     newFeatures(featureCount,:) = [features(feature) curvature contrast];
    %     featureCount = featureCount + 1;
    % end
    
    if curvature < (power(r+1,1)/power(r,1)) && curvature > 0 && contrast > c
        newFeatures(featureCount,:) = [features(feature,:) curvature contrast];
        featureCount = featureCount + 1;
    end
end

end