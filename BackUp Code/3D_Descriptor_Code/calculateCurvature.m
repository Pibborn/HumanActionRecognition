function [score, flag, contrast] = calculateCurvature(gssP, gssC, gssN, f, h, w, c, r)

% includeScale = 0 : no scale , 1 : yes scale 
includeScale = 0;

% H = zeros(4,4);
flag = 0;

%% Computing Gradients
dw = 0.5 * (gssC(h,w+1,f) - gssC(h,w-1,f));
dh = 0.5 * (gssC(h+1,w,f) - gssC(h-1,w,f));
df = 0.5 * (gssC(h,w,f+1) - gssC(h,w,f-1));
ds = 0.5 * (gssN(h,w,f) - gssP(h,w,f));

%% Calculating Hessian Matrix Coefficients
% Second Degree COefficients
% Computing Diagonal of Hessian Matrix
dww = gssC(h,w+1,f) + gssC(h,w-1,f) - (2*gssC(h,w,f));
dhh = gssC(h+1,w,f) + gssC(h-1,w,f) - (2*gssC(h,w,f));
dff = gssC(h,w,f+1) + gssC(h,w,f-1) - (2*gssC(h,w,f));
dss = gssN(h,w,f) + gssP(h,w,f) - (2*gssC(h,w,f));

%% Computing Non-Diagonal Matrix Coefficients
dwh = gssC(h+1,w+1,f) + gssC(h-1,w-1,f) - ...
    (2*(gssC(h+1,w-1,f) + gssC(h-1,w+1,f)));
dhf = gssC(h+1,w,f+1) + gssC(h-1,w,f-1) - ...
    (2*(gssC(h-1,w,f+1) + gssC(h+1,w,f-1)));
dwf = gssC(h,w+1,f+1) + gssC(h,w-1,f-1) - ...
    (2*(gssC(h,w+1,f-1) + gssC(h,w-1,f+1)));
dhs = gssN(h+1,w,f) + gssP(h-1,w,f) - ...
    (2*(gssN(h-1,w,f) + gssP(h+1,w,f)));
dws = gssN(h,w+1,f) + gssP(h,w-1,f) - ...
    (2*(gssN(h,w-1,f) + gssP(h,w+1,f)));
dfs = gssN(h,w,f+1) + gssP(h,w,f-1) - ...
    (2*(gssN(h,w,f-1) + gssP(h,w,f+1)));

%% Computing Hessian Matrix
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

%% Determining Maximum and Minimum Eigen values
eMax = max(diag(H));
eMin = max(diag(H));

%% Different Threshold Techniques
% r = eMax/eMin;
% r = 10;

%% Computing the Curvature Ratio
traceH = trace(H);
detH = det(H);
score = power(traceH,1)/detH;

%% Computing the Contrast
if includeScale == 0
    contrast = abs(gssC(h,w,f) + (0.5*(dw*dw + dh*dh + df*df)));
else
    contrast = abs(gssC(h,w,f) + (0.5*(dw*dw + dh*dh + df*df + ds*ds)));
end

%% Threshold Check
if score < (power(r+1,1)/power(r,1)) && score > 0 && contrast > c
    flag = 1;
end
end