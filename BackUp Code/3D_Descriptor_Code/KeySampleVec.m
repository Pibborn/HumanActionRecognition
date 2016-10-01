function vec = KeySampleVec(key, pix)
% LoadParams;
output = LoadParameters();

       TwoPeak_Flag = output( 1);
          IndexSize = output( 2);
       Display_flag = output( 3);
  Tessellation_flag = output( 4);
Tessellation_levels = output( 5);
             nFaces = output( 6);
        Smooth_Flag = output( 7);
         Smooth_Var = output( 8);
     IgnoreGradSign = output( 9);
         IndexSigma = output(10);
          MagFactor = output(11);
    UseHistogramOri = output(12);
      OriHistThresh = output(13);
           OriSigma = output(14);


% Method 1
index = KeySample(key, pix);
vec = index(:);

% % Method 2
% index = KeySample2D(key, grad, ori, scale, row, col);
% vec = index(:);

% % Method 3
% n = 0;
% orig_frame = key.frame;
% for t_offset=-4:4
%     key.frame = orig_frame + t_offset;
%     index = KeySample2D(key, grad, ori, scale, row, col);
%     vec_temp = index(:);
%     n = n + 1;
%     vec((n-1)*length(vec_temp)+1:n*length(vec_temp)) = vec_temp;
% end
% key.frame = orig_frame;
% vec = vec';

% % Method 4
% index = KeySample2D(key, grad, ori, scale, row, col);
% index = KeySample2Dxt(key, grad, ori, scale, row, col);
% index = KeySample2Dyt(key, grad, ori, scale, row, col);


end
