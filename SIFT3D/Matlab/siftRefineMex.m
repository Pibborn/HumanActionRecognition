function nidx = siftRefineMex(idx, I, threshold, r)
%% ANNOTATIONS
% f : Features
% x : Height of Frame (H)
% y : Wdith of Frame  (W)
% t : Frame Count     (T)
% s : Scale

nidx = [];
fCount       = size(idx, 1);
[X, Y, T, S] = size(I);
maxIteration = 5;
for f = 1 : fCount
    o = idx(f, 1); % octave
    s = idx(f, 2); % scale
    x = idx(f, 3); % height
    y = idx(f, 4); % width
    t = idx(f, 5); % frame/time
    pixelValue = I(x, y, t, s);
    
    dx = 0; dy = 0; dt = 0;
    iterator = 0;
    while iterator < maxIteration
        x = x + dx;
        y = y + dy;
        t = t + dt;
        
        Dx = 0.5*(I(x+1,y,t,s) - I(x-1,y,t,s));
        Dy = 0.5*(I(x,y+1,t,s) - I(x,y-1,t,s));
        Dt = 0.5*(I(x,y,t+1,s) - I(x,y,t-1,s));
        Ds = 0.5*(I(x,y,t,s+1) - I(x,y,t,s-1));
        
        Dxx = (I(x+1,y,t,s) + I(x-1,y,t,s)) - 2*pixelValue;
        Dyy = (I(x,y+1,t,s) + I(x,y-1,t,s)) - 2*pixelValue;
        Dtt = (I(x,y,t+1,s) + I(x,y,t-1,s)) - 2*pixelValue;
        Dss = (I(x,y,t,s+1) + I(x,y,t,s-1)) - 2*pixelValue;
        
        Dxy = 0.25*(I(x+1,y+1,t,s)+I(x-1,y-1,t,s)-I(x-1,y+1,t,s)-I(x+1,y-1,t,s));
        Dxt = 0.25*(I(x+1,y,t+1,s)+I(x-1,y,t-1,s)-I(x-1,y,t+1,s)-I(x+1,y,t-1,s));
        Dxs = 0.25*(I(x+1,y,t,s+1)+I(x-1,y,t,s-1)-I(x-1,y,t,s+1)-I(x+1,y,t,s-1));
        Dyt = 0.25*(I(x,y+1,t+1,s)+I(x,y-1,t-1,s)-I(x,y+1,t-1,s)-I(x,y-1,t+1,s));
        Dys = 0.25*(I(x,y+1,t,s+1)+I(x,y-1,t,s-1)-I(x,y+1,t,s-1)-I(x,y-1,t,s+1));
        Dts = 0.25*(I(x,y,t+1,s+1)+I(x,y,t-1,s-1)-I(x,y,t-1,s+1)-I(x,y,t+1,s-1));
        
        b = (-1)*[Dx, Dy, Dt, Ds];
        if b(1) > 0.6 && x < X-1
            dx = 1;
        else
            dx = 0;
        end
        if b(1) < -0.6 && x > 1
            dx = dx - 1;
        end
        if b(2) > 0.6 && y < Y-1
            dy = 1;
        else
            dy = 0;
        end
        if b(2) < -0.6 && y > 1
            dy = dy - 1;
        end
        if b(3) > 0.6 && t < T-1
            dt = 1;
        else
            dt = 0;
        end
        if b(3) < -0.6 && t > 1
            dt = dt - 1;
        end
        if dx == 0 && dy == 0 && dt == 0
            break;
        end
        iterator = iterator + 1;
    end
    
    Hessian = [Dxx Dxy Dxt Dxs;...
               Dxy Dyy Dyt Dys;...
               Dxt Dyt Dtt Dts;...
               Dxs Dys Dts Dss];
           
    val = pixelValue + 0.5*(Dx*b(1) + Dy*b(2) + Dt*b(3) + Ds*b(4));
    
    traceH = trace(Hessian(1:3,1:3));
    detH = det(Hessian(1:3,1:3));
    
    % score = traceH*traceH/detH;
    % ratio = (r+1)*(r+1)/r
    
    score = traceH*traceH*traceH/detH;
    ratio = power((2*r)+1,3)/power(r,2);
    
    xn = x + b(1);
    yn = y + b(2);
    tn = t + b(3);
    sn = s + b(4);
    b = abs(b);
    if abs(val) > threshold && ...
       score < ratio &&...
       score > 0 &&...
       b(1) < 1.5 && b(2) < 1.5 &&...
       b(3) < 1.5 && b(4) < 1.5 &&...
       xn >= 1 && xn <= X &&...
       yn >= 1 && yn <= Y &&...
       tn >= 1 && tn <= T &&...
       sn >= 1 && sn <= S
        % these are the features that will be printed
        nidx = [nidx; [o, ceil(sn), ceil(xn), ceil(yn), ceil(tn), idx(f,6), val, score]];
        % idx(f, 6): maximum or minimum
        % val: contrast
        % score: curvature ratio
    end
end

end