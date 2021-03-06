/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: KeySampleVec.c
 *
 * MATLAB Coder version            : 3.2
 * C/C++ source code generated on  : 18-Nov-2016 16:32:39
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "Create_Descriptor.h"
#include "KeySampleVec.h"
#include "sort1.h"
#include "GetGradOri_vector.h"
#include "MakeKeypoint.h"
#include "Create_Descriptor_emxutil.h"
#include "sphere_tri.h"
#include "Create_Descriptor_rtwutil.h"

/* Function Declarations */
static double rt_powd_snf(double u0, double u1);

/* Function Definitions */

/*
 * Arguments    : double u0
 *                double u1
 * Return Type  : double
 */
static double rt_powd_snf(double u0, double u1)
{
  double y;
  double d0;
  double d1;
  if (rtIsNaN(u0) || rtIsNaN(u1)) {
    y = rtNaN;
  } else {
    d0 = fabs(u0);
    d1 = fabs(u1);
    if (rtIsInf(u1)) {
      if (d0 == 1.0) {
        y = rtNaN;
      } else if (d0 > 1.0) {
        if (u1 > 0.0) {
          y = rtInf;
        } else {
          y = 0.0;
        }
      } else if (u1 > 0.0) {
        y = 0.0;
      } else {
        y = rtInf;
      }
    } else if (d1 == 0.0) {
      y = 1.0;
    } else if (d1 == 1.0) {
      if (u1 > 0.0) {
        y = u0;
      } else {
        y = 1.0 / u0;
      }
    } else if (u1 == 2.0) {
      y = u0 * u0;
    } else if ((u1 == 0.5) && (u0 >= 0.0)) {
      y = sqrt(u0);
    } else if ((u0 < 0.0) && (u1 > floor(u1))) {
      y = rtNaN;
    } else {
      y = pow(u0, u1);
    }
  }

  return y;
}

/*
 * LoadParams;
 *  lData = load('LoadParams.mat');
 *
 *  Display_flag = lData.Display_flag;
 *  IgnoreGradSign = lData.IgnoreGradSign;
 *  IndexSigma = lData.IndexSigma;
 *  IndexSize = lData.IndexSize;
 *  MagFactor = lData.MagFactor;
 *  nFaces = lData.nFaces;
 *  OriHistThresh = lData.OriHistThresh;
 *  OriSigma = lData.OriSigma;
 *  Smooth_Flag = lData.Smooth_Flag;
 *  Smooth_Var = lData.Smooth_Var;
 *  Tessellation_flag = lData.Tessellation_flag;
 *  Tessellation_levels = lData.Tessellation_levels;
 *  TwoPeak_Flags = lData.TwoPeak_Flag;
 *  UseHistogramOri = lData.UseHistogramOri;
 * Arguments    : double key_x
 *                double key_y
 *                double key_z
 *                double key_xyScale
 *                double key_tScale
 *                const emxArray_real_T *pix
 *                double vec[640]
 * Return Type  : void
 */
void KeySampleVec(double key_x, double key_y, double key_z, double key_xyScale,
                  double key_tScale, const emxArray_real_T *pix, double vec[640])
{
  emxArray_real_T *expl_temp;
  double expl_temp_data[240];
  int expl_temp_size[2];
  double fv_centers_data[240];
  int fv_centers_size[2];
  double mag;
  short irow;
  short icol;
  short islice;
  short xyiradius;
  short tiradius;
  double b_index[640];
  int ic;
  short i;
  short j;
  short s;
  short s_indx;
  int ar;
  short i_indx;
  short j_indx;
  short r;
  short c;
  short t;
  double v0[3];
  double corr_array_data[80];
  int ib;
  double yy_data[80];
  int ia;
  int iidx_data[80];
  int iidx_size[1];
  int ix_data[80];
  double tmpsum;
  emxInit_real_T(&expl_temp, 2);

  /*  Allow 3DSIFT to throw out points, Default: 1 */
  /*  Min: 1  Default: 2  */
  /*  Display a sphere which can be rotated (Rotate 3D button) to view gradient directions */
  /*  Keep this as 1 */
  /*  Min: zero  Default: 1 */
  /*  Number of faces in the tessellation, not a parameter */
  /*  Adds gradient data to surrounding bins in final histogram */
  /*  Determines amount of smoothing, Default: 20 */
  /*  The rest of the variables are not modified often, but are included here */
  /*  for completeness sake */
  /*  Method 1 */
  /*  LoadParams; */
  /*  lData = load('LoadParams.mat'); */
  /*   */
  /*  Display_flag = lData.Display_flag; */
  /*  IgnoreGradSign = lData.IgnoreGradSign; */
  /*  IndexSigma = lData.IndexSigma; */
  /*  IndexSize = lData.IndexSize; */
  /*  MagFactor = lData.MagFactor; */
  /*  nFaces = lData.nFaces; */
  /*  OriHistThresh = lData.OriHistThresh; */
  /*  OriSigma = lData.OriSigma; */
  /*  Smooth_Flag = lData.Smooth_Flag; */
  /*  Smooth_Var = lData.Smooth_Var; */
  /*  Tessellation_flag = lData.Tessellation_flag; */
  /*  Tessellation_levels = lData.Tessellation_levels; */
  /*  TwoPeak_Flags = lData.TwoPeak_Flag; */
  /*  UseHistogramOri = lData.UseHistogramOri; */
  /*  Allow 3DSIFT to throw out points, Default: 1 */
  /*  Min: 1  Default: 2  */
  /*  Display a sphere which can be rotated (Rotate 3D button) to view gradient directions */
  /*  Keep this as 1 */
  /*  Min: zero  Default: 1 */
  /*  Number of faces in the tessellation, not a parameter */
  /*  Adds gradient data to surrounding bins in final histogram */
  /*  Determines amount of smoothing, Default: 20 */
  /*  The rest of the variables are not modified often, but are included here */
  /*  for completeness sake */
  sphere_tri(expl_temp, expl_temp_data, expl_temp_size, fv_centers_data,
             fv_centers_size);
  mag = rt_roundd_snf(key_x);
  if (mag < 32768.0) {
    if (mag >= -32768.0) {
      irow = (short)mag;
    } else {
      irow = MIN_int16_T;
    }
  } else if (mag >= 32768.0) {
    irow = MAX_int16_T;
  } else {
    irow = 0;
  }

  /*  x */
  mag = rt_roundd_snf(key_y);
  if (mag < 32768.0) {
    if (mag >= -32768.0) {
      icol = (short)mag;
    } else {
      icol = MIN_int16_T;
    }
  } else if (mag >= 32768.0) {
    icol = MAX_int16_T;
  } else {
    icol = 0;
  }

  /*  y */
  mag = rt_roundd_snf(key_z);
  if (mag < 32768.0) {
    if (mag >= -32768.0) {
      islice = (short)mag;
    } else {
      islice = MIN_int16_T;
    }
  } else if (mag >= 32768.0) {
    islice = MAX_int16_T;
  } else {
    islice = 0;
  }

  /*  t */
  mag = rt_roundd_snf(1.414 * (key_xyScale * 3.0) * 3.0 / 2.0);
  if (mag < 32768.0) {
    if (mag >= -32768.0) {
      xyiradius = (short)mag;
    } else {
      xyiradius = MIN_int16_T;
    }
  } else if (mag >= 32768.0) {
    xyiradius = MAX_int16_T;
  } else {
    xyiradius = 0;
  }

  mag = rt_roundd_snf(1.414 * (key_tScale * 3.0) * 3.0 / 2.0);
  if (mag < 32768.0) {
    if (mag >= -32768.0) {
      tiradius = (short)mag;
    } else {
      tiradius = MIN_int16_T;
    }
  } else if (mag >= 32768.0) {
    tiradius = MAX_int16_T;
  } else {
    tiradius = 0;
  }

  emxFree_real_T(&expl_temp);
  memset(&b_index[0], 0, 640U * sizeof(double));
  ic = -xyiradius;
  if (ic > 32767) {
    ic = 32767;
  }

  for (i = (short)ic; i <= xyiradius; i++) {
    ic = -xyiradius;
    if (ic > 32767) {
      ic = 32767;
    }

    for (j = (short)ic; j <= xyiradius; j++) {
      ic = -tiradius;
      if (ic > 32767) {
        ic = 32767;
      }

      for (s = (short)ic; s <= tiradius; s++) {
        /*  This is redundant and probably slows down the code, but at */
        /*  some point this solved a major overflow headache, so leaving */
        /*  as-is for now */
        ic = i + xyiradius;
        if (ic > 32767) {
          ic = 32767;
        } else {
          if (ic < -32768) {
            ic = -32768;
          }
        }

        if (xyiradius > 16383) {
          s_indx = MAX_int16_T;
        } else if (xyiradius <= -16384) {
          s_indx = MIN_int16_T;
        } else {
          s_indx = (short)(xyiradius << 1);
        }

        ar = (int)rt_roundd_snf((double)s_indx / 2.0);
        s_indx = (short)ar;
        mag = rt_roundd_snf(floor((double)ic / (double)s_indx));
        if (mag < 32768.0) {
          if (mag >= -32768.0) {
            s_indx = (short)mag;
          } else {
            s_indx = MIN_int16_T;
          }
        } else if (mag >= 32768.0) {
          s_indx = MAX_int16_T;
        } else {
          s_indx = 0;
        }

        ic = s_indx + 1;
        if (ic > 32767) {
          ic = 32767;
        }

        i_indx = (short)ic;
        ic = j + xyiradius;
        if (ic > 32767) {
          ic = 32767;
        } else {
          if (ic < -32768) {
            ic = -32768;
          }
        }

        if (xyiradius > 16383) {
          s_indx = MAX_int16_T;
        } else if (xyiradius <= -16384) {
          s_indx = MIN_int16_T;
        } else {
          s_indx = (short)(xyiradius << 1);
        }

        ar = (int)rt_roundd_snf((double)s_indx / 2.0);
        s_indx = (short)ar;
        mag = rt_roundd_snf(floor((double)ic / (double)s_indx));
        if (mag < 32768.0) {
          if (mag >= -32768.0) {
            s_indx = (short)mag;
          } else {
            s_indx = MIN_int16_T;
          }
        } else if (mag >= 32768.0) {
          s_indx = MAX_int16_T;
        } else {
          s_indx = 0;
        }

        ic = s_indx + 1;
        if (ic > 32767) {
          ic = 32767;
        }

        j_indx = (short)ic;
        ic = s + tiradius;
        if (ic > 32767) {
          ic = 32767;
        } else {
          if (ic < -32768) {
            ic = -32768;
          }
        }

        if (tiradius > 16383) {
          s_indx = MAX_int16_T;
        } else if (tiradius <= -16384) {
          s_indx = MIN_int16_T;
        } else {
          s_indx = (short)(tiradius << 1);
        }

        ar = (int)rt_roundd_snf((double)s_indx / 2.0);
        s_indx = (short)ar;
        mag = rt_roundd_snf(floor((double)ic / (double)s_indx));
        if (mag < 32768.0) {
          if (mag >= -32768.0) {
            s_indx = (short)mag;
          } else {
            s_indx = MIN_int16_T;
          }
        } else if (mag >= 32768.0) {
          s_indx = MAX_int16_T;
        } else {
          s_indx = 0;
        }

        ic = s_indx + 1;
        if (ic > 32767) {
          ic = 32767;
        }

        s_indx = (short)ic;
        if (i_indx > 2) {
          /*  i_indx = IndexSize; */
          i_indx = 2;
        }

        if (j_indx > 2) {
          /*  j_indx = IndexSize; */
          j_indx = 2;
        }

        if (s_indx > 2) {
          /* s_indx = IndexSize; */
          s_indx = 2;
        }

        ic = (int)rt_roundd_snf(irow + i);
        if (ic < 32768) {
          if (ic >= -32768) {
            r = (short)ic;
          } else {
            r = MIN_int16_T;
          }
        } else {
          r = MAX_int16_T;
        }

        ic = (int)rt_roundd_snf(icol + j);
        if (ic < 32768) {
          if (ic >= -32768) {
            c = (short)ic;
          } else {
            c = MIN_int16_T;
          }
        } else {
          c = MAX_int16_T;
        }

        ic = (int)rt_roundd_snf(islice + s);
        if (ic < 32768) {
          if (ic >= -32768) {
            t = (short)ic;
          } else {
            t = MIN_int16_T;
          }
        } else {
          t = MAX_int16_T;
        }

        /*  LoadParams; */
        /*  lData = load('LoadParams.mat'); */
        /*   */
        /*  Display_flag = lData.Display_flag; */
        /*  IgnoreGradSign = lData.IgnoreGradSign; */
        /*  IndexSigma = lData.IndexSigma; */
        /*  IndexSize = lData.IndexSize; */
        /*  MagFactor = lData.MagFactor; */
        /*  nFaces = lData.nFaces; */
        /*  OriHistThresh = lData.OriHistThresh; */
        /*  OriSigma = lData.OriSigma; */
        /*  Smooth_Flag = lData.Smooth_Flag; */
        /*  Smooth_Var = lData.Smooth_Var; */
        /*  Tessellation_flag = lData.Tessellation_flag; */
        /*  Tessellation_levels = lData.Tessellation_levels; */
        /*  TwoPeak_Flags = lData.TwoPeak_Flag; */
        /*  UseHistogramOri = lData.UseHistogramOri; */
        /*  Allow 3DSIFT to throw out points, Default: 1 */
        /*  Min: 1  Default: 2  */
        /*  Display a sphere which can be rotated (Rotate 3D button) to view gradient directions */
        /*  Keep this as 1 */
        /*  Min: zero  Default: 1 */
        /*  Number of faces in the tessellation, not a parameter */
        /*  Adds gradient data to surrounding bins in final histogram */
        /*  Determines amount of smoothing, Default: 20 */
        /*  The rest of the variables are not modified often, but are included here */
        /*  for completeness sake */
        if ((r < 1) || (r > pix->size[0]) || (c < 1) || (c > pix->size[1]) || (t
             < 1) || (t > pix->size[2])) {
        } else {
          GetGradOri_vector(pix, r, c, t, &mag, v0);
          mag *= exp(-((((double)(i * i) + (double)(j * j)) + (double)(s * s)) /
                       50.0));

          /*  LoadParams; */
          /*  lData = load('LoadParams'); */
          /*   */
          /*  Display_flag = lData.Display_flag; */
          /*  IgnoreGradSign = lData.IgnoreGradSign; */
          /*  IndexSigma = lData.IndexSigma; */
          /*  IndexSize = lData.IndexSize; */
          /*  MagFactor = lData.MagFactor; */
          /*  nFaces = lData.nFaces; */
          /*  OriHistThresh = lData.OriHistThresh; */
          /*  OriSigma = lData.OriSigma; */
          /*  Smooth_Flag = lData.Smooth_Flag; */
          /*  Smooth_Var = lData.Smooth_Var; */
          /*  Tessellation_flag = lData.Tessellation_flag; */
          /*  Tessellation_levels = lData.Tessellation_levels; */
          /*  TwoPeak_Flags = lData.TwoPeak_Flag; */
          /*  UseHistogramOri = lData.UseHistogramOri; */
          /*  Allow 3DSIFT to throw out points, Default: 1 */
          /*  Min: 1  Default: 2  */
          /*  Display a sphere which can be rotated (Rotate 3D button) to view gradient directions */
          /*  Keep this as 1 */
          /*  Min: zero  Default: 1 */
          /*  Number of faces in the tessellation, not a parameter */
          /*  Adds gradient data to surrounding bins in final histogram */
          /*  Determines amount of smoothing, Default: 20 */
          /*  The rest of the variables are not modified often, but are included here */
          /*  for completeness sake */
          memset(&corr_array_data[0], 0, 80U * sizeof(double));
          for (ic = 1; ic < 81; ic++) {
            corr_array_data[ic - 1] = 0.0;
          }

          ar = 0;
          for (ib = 0; ib + 1 < 4; ib++) {
            if (v0[ib] != 0.0) {
              ia = ar;
              for (ic = 0; ic + 1 < 81; ic++) {
                ia++;
                corr_array_data[ic] += v0[ib] * fv_centers_data[ia - 1];
              }
            }

            ar += 80;
          }

          memcpy(&yy_data[0], &corr_array_data[0], 80U * sizeof(double));
          sort(yy_data, iidx_data, iidx_size);
          memcpy(&ix_data[0], &iidx_data[0], 80U * sizeof(int));
          for (ic = 0; ic < 3; ic++) {
            v0[ic] = rt_powd_snf(yy_data[ic], 20.0);
          }

          tmpsum = v0[0];
          for (ic = 0; ic < 2; ic++) {
            tmpsum += v0[ic + 1];
          }

          for (ic = 0; ic < 3; ic++) {
            b_index[(((i_indx + ((j_indx - 1) << 1)) + ((s_indx - 1) << 2)) +
                     ((ix_data[ic] - 1) << 3)) - 1] += mag * rt_powd_snf
              (yy_data[ic], 20.0) / tmpsum;
          }
        }
      }
    }
  }

  memcpy(&vec[0], &b_index[0], 640U * sizeof(double));

  /*  % Method 2 */
  /*  index = KeySample2D(key, grad, ori, scale, row, col); */
  /*  vec = index(:); */
  /*  % Method 3 */
  /*  n = 0; */
  /*  orig_frame = key.frame; */
  /*  for t_offset=-4:4 */
  /*      key.frame = orig_frame + t_offset; */
  /*      index = KeySample2D(key, grad, ori, scale, row, col); */
  /*      vec_temp = index(:); */
  /*      n = n + 1; */
  /*      vec((n-1)*length(vec_temp)+1:n*length(vec_temp)) = vec_temp; */
  /*  end */
  /*  key.frame = orig_frame; */
  /*  vec = vec'; */
  /*  % Method 4 */
  /*  index = KeySample2D(key, grad, ori, scale, row, col); */
  /*  index = KeySample2Dxt(key, grad, ori, scale, row, col); */
  /*  index = KeySample2Dyt(key, grad, ori, scale, row, col); */
}

/*
 * File trailer for KeySampleVec.c
 *
 * [EOF]
 */
