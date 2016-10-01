function index = KeySample(key, pix)

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

fv = sphere_tri('ico',Tessellation_levels,1);


irow = int16(key.x);
icol = int16(key.y);
islice = int16(key.z);

xySpacing = key.xyScale * MagFactor;
tSpacing = key.tScale * MagFactor;

xyRadius = 1.414 * xySpacing * (IndexSize + 1) / 2.0;
tRadius = 1.414 * tSpacing * (IndexSize + 1) / 2.0;
xyiradius = int16(xyRadius);
tiradius = int16(tRadius);

index = zeros(IndexSize,IndexSize,IndexSize,nFaces);

for i = -xyiradius:xyiradius
    for j = -xyiradius:xyiradius
        for s = -tiradius:tiradius

            % This is redundant and probably slows down the code, but at
            % some point this solved a major overflow headache, so leaving
            % as-is for now
            i2 = double(i);
            j2 = double(j);
            s2 = double(s);
            distsq = double(i2^2 + j2^2 + s2^2);

            v0 = [i2; j2; s2];

            i_indx = int16(floor(double((i + xyiradius)) / double((2*xyiradius/IndexSize)))) + 1;
            j_indx = int16(floor(double((j + xyiradius)) / double((2*xyiradius/IndexSize)))) + 1;
            s_indx = int16(floor(double((s + tiradius)) / double((2*tiradius/IndexSize)))) + 1;
            
            if i_indx > IndexSize
                i_indx = int16(IndexSize);
            end
            if j_indx > IndexSize
                j_indx = int16(IndexSize);
            end
            if s_indx > IndexSize
                s_indx = int16(IndexSize);
            end

            if (i_indx < 1 || j_indx < 1 || s_indx < 1)
                disp('Something wrong with the sub-histogram index');
            end
            
           
            r = irow + v0(1);
            c = icol + v0(2);
            t = islice + v0(3);

            index = AddSample(index, key, pix, distsq, r, c, t, i_indx, j_indx, s_indx, fv);
            
        end
    end
end
