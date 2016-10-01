function features = refineKeyPoints(keyPoints, I , smin, thresh, r)

fCount = 1;
features = [];
[H, W, F, S] = size(I);
% <o, s, h, w, f, type
for point = 1 : size(keyPoints,1)
    o = keyPoints(point, 1);
    s = keyPoints(point, 2);
    h = keyPoints(point, 3);
    w = keyPoints(point, 4);
    f = keyPoints(point, 5);
    type = keyPoints(point, 6);
    iterator = 0;
    
    pixelValue = I(h, w, f, s);
    dh = 0;
    dw = 0;
    df = 0;
    
    while iterator < 5
        
        h = h + dh;
        w = w + dw;
        f = f + df;
        
        % Computing Gradiants
        Dh = 0.5 * (I(h + 1, w, f, s) - I(h - 1, w, f, s));
        Dw = 0.5 * (I(h, w + 1, f, s) - I(h, w - 1, f, s));
        Df = 0.5 * (I(h, w, f + 1, s) - I(h, w, f - 1, s));
        Ds = 0.5 * (I(h, w, f, s + 1) - I(h, w, f, s - 1));
        
        % Computing Hessian Diagonal Coefficients
        Dhh = I(h+1,w,f,s) + I(h-1,w,f,s) - (2.0 * pixelValue);
        Dww = I(h,w+1,f,s) + I(h,w-1,f,s) - (2.0 * pixelValue);
        Dff = I(h,w,f+1,s) + I(h,w,f-1,s) - (2.0 * pixelValue);
        Dss = I(h,w,f,s+1) + I(h,w,f,s-1) - (2.0 * pixelValue);
        
        % Computing Hessian non-Diagonal Coefficients
        Dhw = 0.25 * (I(h+1,w+1,f,s) + I(h-1,w-1,f,s) - I(h-1,w+1,f,s) - I(h+1,w-1,f,s));
        Dhf = 0.25 * (I(h+1,w,f+1,s) + I(h-1,w,f-1,s) - I(h-1,w,f+1,s) - I(h+1,w,f-1,s));
        Dhs = 0.25 * (I(h+1,w,f,s+1) + I(h-1,w,f,s-1) - I(h-1,w,f,s+1) - I(h+1,w,f,s-1));
        Dwf = 0.25 * (I(h,w+1,f+1,s) + I(h,w-1,f-1,s) - I(h,w-1,f+1,s) - I(h,w+1,f-1,s));
        Dws = 0.25 * (I(h,w+1,f,s+1) + I(h,w-1,f,s-1) - I(h,w-1,f,s+1) - I(h,w+1,f,s-1));
        Dfs = 0.25 * (I(h,w,f+1,s+1) + I(h,w,f-1,s-1) - I(h,w,f-1,s+1) - I(h,w,f+1,s-1));
        
        % Hessian Matrix
        Hessian = ...
            [ Dhh Dhw Dhf Dhs;...
            Dhw Dww Dwf Dws;...
            Dhf Dwf Dff Dfs;...
            Dhs Dws Dfs Dss;];
        
        HessianWF = ...
            [ Dww Dwf;...
            Dwf Dff];
        
        HessianHF = ...
            [ Dhh Dhf;...
            Dhf Dff];
        
        HessianHW = ...
            [ Dhh Dhw;...
            Dhw Dww];
        
        b = [-Dh -Dw -Df -Ds];
        
        if b(1) > 0.6 && h < H - 1
            dh = 1;
        else
            dh = 0;
        end
        
        if b(1) < -0.6 && h > 2
            dh = dh - 1;
        else
            dh = dh + 0;
        end
        
        if b(2) > 0.6 && w < W - 1
            dw = 1;
        else
            dw = 0;
        end
        
        if b(2) < -0.6 && w > 2
            dw = dw - 1;
        else
            dw = dw + 0;
        end
        
        if b(3) > 0.6 && f < F - 1
            df = 1;
        else
            df = 0;
        end
        
        if b(3) < -0.6 && F > 2
            df = df - 1;
        else
            df = df + 0;
        end
        
        if dh == 0 && dw == 0 && df == 0
            break;
        end
        
        iterator = iterator + 1;
    end
    
    valHWF = pixelValue + 0.5 * (Dh*b(1) + Dw*b(2) + Df*b(3) + Ds*b(4));

    valHW  = pixelValue + 0.5 * (Dh*b(1) + Dw*b(2) + Ds*b(4));
    valHF  = pixelValue + 0.5 * (Dh*b(1) + Df*b(3) + Ds*b(4));
    valWF  = pixelValue + 0.5 * (Dw*b(2) + Df*b(3) + Ds*b(4));
   
    curHWF = power(trace(Hessian(1:3,1:3)),3)/det(Hessian(1:3,1:3));
    curHF  = power(trace(HessianHF),2)/det(HessianHF);
    curHW  = power(trace(HessianHW),2)/det(HessianHW);
    curWF  = power(trace(HessianWF),2)/det(HessianWF);
    curThresh = power(r+1,2)/r;
    
    hn = h + b(1);
    wn = w + b(2);
    fn = f + b(3);
    sn = s + b(4);
    
    % if abs(val) > thresh &&
    if (( curHF < curThresh && curHF >= 0 && abs(valHF) > thresh ) || ...
            ( curHW < curThresh && curHW >= 0 && abs(valHW) > thresh )  || ...
            ( curWF < curThresh && curWF >= 0 && abs(valWF) > thresh )) && ...
            abs(b(1)) < 1.5 && ...
            abs(b(2)) < 1.5 && ...
            abs(b(3)) < 1.5 && ...
            abs(b(4)) < 1.5 && ...
            hn >= 1 && ...
            hn <= H && ...
            wn >= 1 && ...
            wn <= W && ...
            fn >= 1 && ...
            fn <= F && ...
            sn >= 1 && ...
            sn <= S
        % features = [features; [o s h w f type curvature val]];
        features = [features; ... 
            [o s h w f type ...
            curHF valHF ...
            curHW valHW ... 
            curWF valWF ...
            curHWF valHWF]];
    end
    fCount = fCount + 1;
end