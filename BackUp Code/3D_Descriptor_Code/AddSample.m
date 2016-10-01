function index = AddSample(index, k, pix, distsq, r, c, s, i_indx, j_indx, s_indx, fv)

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

if (r < 1  ||  r > size(pix,1)  ||  c < 1  ||  c > size(pix,2) || s < 1 || s > size(pix,3))
    return;
end

sigma = IndexSigma * 0.5 * IndexSize;
weight = exp(-double(distsq / (2.0 * sigma * sigma)));

[grad, vect] = GetGradOri_vector(pix,r,c,s);
mag = weight * grad;

index = PlaceInIndex(index, mag, vect, i_indx, j_indx, s_indx, fv);

end
 
