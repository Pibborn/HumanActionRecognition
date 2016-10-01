function index = PlaceInIndex(index, mag, vect, i, j, s, fv)

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

corr_array = fv.centers * vect';

[yy, ix] = sort(corr_array,'descend');

if (Smooth_Flag == 0)
    index(i,j,s,ix(1)) = index(i,j,s,ix(1)) + mag;
elseif (Smooth_Flag == 1)
    tmpsum = sum(yy(1:3).^Smooth_Var);
    for ii=1:3
        index(i,j,s,ix(ii)) = index(i,j,s,ix(ii)) + ( mag * ( yy(ii) .^ Smooth_Var ) / tmpsum );
    end
end
