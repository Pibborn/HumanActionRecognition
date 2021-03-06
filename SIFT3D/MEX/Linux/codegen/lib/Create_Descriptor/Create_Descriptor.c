/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: Create_Descriptor.c
 *
 * MATLAB Coder version            : 3.2
 * C/C++ source code generated on  : 18-Nov-2016 16:32:39
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "Create_Descriptor.h"
#include "sort1.h"
#include "GetGradOri_vector.h"
#include "MakeKeypoint.h"
#include "Create_Descriptor_emxutil.h"
#include "sphere_tri.h"
#include "Create_Descriptor_rtwutil.h"

/* Function Definitions */

/*
 * Main function of 3DSIFT Program from http://www.cs.ucf.edu/~pscovann/
 *
 *  Inputs:
 *  pix - a 3 dimensional matrix of uint8
 *  xyScale and tScale - affects both the scale and the resolution, these are
 *  usually set to 1 and scaling is done before calling this function
 *  x, y, and z - the location of the center of the keypoint where a descriptor is requested
 *
 *  Outputs:
 *  keypoint - the descriptor, varies in size depending on values in LoadParams.m
 *  reRun - a flag (0 or 1) which is set if the data at (x,y,z) is not
 *  descriptive enough for a good keypoint
 *
 *  Example:
 *  See Demo.m
 * Arguments    : const emxArray_real_T *pix
 *                double xyScale
 *                double tScale
 *                double x
 *                double y
 *                double z
 *                struct0_T *keyPoint
 *                double *reRun
 * Return Type  : void
 */
void Create_Descriptor(const emxArray_real_T *pix, double xyScale, double tScale,
  double x, double y, double z, struct0_T *keyPoint, double *reRun)
{
  emxArray_real_T *expl_temp;
  double c;
  short radius;
  double expl_temp_data[240];
  int expl_temp_size[2];
  double fv_centers_data[240];
  int fv_centers_size[2];
  short xi;
  short yi;
  short zi;
  double myhist[80];
  int k;
  short i0;
  int iidx[80];
  short i1;
  double a_data[3];
  short b_c;
  double b_data[3];
  boolean_T guard1 = false;
  short i2;
  short s;
  double vect[3];
  double corr_array_data[80];
  int ar;
  int ib;
  double unusedU0_data[80];
  int ia;
  int iidx_size[1];

  /*  LoadParams is a .mat files. To modify the parameters, open */
  /*  LoadParamsBkp.m and change parameters. */
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
  /*  TwoPeak_Flag = lData.TwoPeak_Flag; */
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
  keyPoint->x = x;
  keyPoint->y = y;
  keyPoint->z = z;
  keyPoint->xyScale = xyScale;
  keyPoint->tScale = tScale;
  memset(&keyPoint->ivec[0], 0, 640U * sizeof(double));
  emxInit_real_T(&expl_temp, 2);
  *reRun = 0.0;
  c = rt_roundd_snf(xyScale * 3.0);
  if (c < 32768.0) {
    if (c >= -32768.0) {
      radius = (short)c;
    } else {
      radius = MIN_int16_T;
    }
  } else if (c >= 32768.0) {
    radius = MAX_int16_T;
  } else {
    radius = 0;
  }

  sphere_tri(expl_temp, expl_temp_data, expl_temp_size, fv_centers_data,
             fv_centers_size);

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
  c = rt_roundd_snf(x);
  if (c < 32768.0) {
    if (c >= -32768.0) {
      xi = (short)c;
    } else {
      xi = MIN_int16_T;
    }
  } else if (c >= 32768.0) {
    xi = MAX_int16_T;
  } else {
    xi = 0;
  }

  c = rt_roundd_snf(y);
  if (c < 32768.0) {
    if (c >= -32768.0) {
      yi = (short)c;
    } else {
      yi = MIN_int16_T;
    }
  } else if (c >= 32768.0) {
    yi = MAX_int16_T;
  } else {
    yi = 0;
  }

  c = rt_roundd_snf(z);
  if (c < 32768.0) {
    if (c >= -32768.0) {
      zi = (short)c;
    } else {
      zi = MIN_int16_T;
    }
  } else if (c >= 32768.0) {
    zi = MAX_int16_T;
  } else {
    zi = 0;
  }

  emxFree_real_T(&expl_temp);
  memset(&myhist[0], 0, 80U * sizeof(double));
  k = xi + radius;
  if (k > 32767) {
    k = 32767;
  } else {
    if (k < -32768) {
      k = -32768;
    }
  }

  i0 = (short)k;
  k = xi - radius;
  if (k > 32767) {
    k = 32767;
  } else {
    if (k < -32768) {
      k = -32768;
    }
  }

  for (xi = (short)k; xi <= i0; xi++) {
    k = yi + radius;
    if (k > 32767) {
      k = 32767;
    } else {
      if (k < -32768) {
        k = -32768;
      }
    }

    i1 = (short)k;
    k = yi - radius;
    if (k > 32767) {
      k = 32767;
    } else {
      if (k < -32768) {
        k = -32768;
      }
    }

    for (b_c = (short)k; b_c <= i1; b_c++) {
      k = zi + radius;
      if (k > 32767) {
        k = 32767;
      } else {
        if (k < -32768) {
          k = -32768;
        }
      }

      i2 = (short)k;
      k = zi - radius;
      if (k > 32767) {
        k = 32767;
      } else {
        if (k < -32768) {
          k = -32768;
        }
      }

      for (s = (short)k; s <= i2; s++) {
        /*           /$ Do not use last row or column, which are not valid. $/ */
        if ((xi >= 1) && (b_c >= 1) && (xi < pix->size[0] - 1) && (b_c <
             pix->size[1] - 1) && (s >= 1) && (s < pix->size[2] - 1)) {
          GetGradOri_vector(pix, xi, b_c, s, &c, vect);
          memset(&corr_array_data[0], 0, 80U * sizeof(double));
          for (k = 1; k < 81; k++) {
            corr_array_data[k - 1] = 0.0;
          }

          ar = 0;
          for (ib = 0; ib + 1 < 4; ib++) {
            if (vect[ib] != 0.0) {
              ia = ar;
              for (k = 0; k + 1 < 81; k++) {
                ia++;
                corr_array_data[k] += vect[ib] * fv_centers_data[ia - 1];
              }
            }

            ar += 80;
          }

          /*  [yy, ix] = sort(corr_array,'descend'); */
          memcpy(&unusedU0_data[0], &corr_array_data[0], 80U * sizeof(double));
          sort(unusedU0_data, iidx, iidx_size);
          for (k = 0; k < 80; k++) {
            unusedU0_data[k] = iidx[k];
          }

          myhist[(int)unusedU0_data[0] - 1] += c;
        }
      }
    }
  }

  /*  [yy, ix] = sort(myhist,'descend'); */
  c_sort(myhist, iidx);
  for (k = 0; k < 80; k++) {
    myhist[k] = iidx[k];
  }

  /*  Dom_Peak = ix(1); */
  /*  Sec_Peak = ix(2); */
  for (k = 0; k < 3; k++) {
    a_data[k] = fv_centers_data[((int)myhist[0] + fv_centers_size[0] * k) - 1];
    b_data[k] = fv_centers_data[((int)myhist[1] + fv_centers_size[0] * k) - 1];
  }

  c = 0.0;
  for (k = 0; k < 3; k++) {
    c += a_data[k] * b_data[k];
  }

  guard1 = false;
  if (c > 0.9) {
    for (k = 0; k < 3; k++) {
      a_data[k] = fv_centers_data[((int)myhist[0] + fv_centers_size[0] * k) - 1];
      b_data[k] = fv_centers_data[((int)myhist[2] + fv_centers_size[0] * k) - 1];
    }

    c = 0.0;
    for (k = 0; k < 3; k++) {
      c += a_data[k] * b_data[k];
    }

    if (c > 0.9) {
      *reRun = 1.0;
    } else {
      guard1 = true;
    }
  } else {
    guard1 = true;
  }

  if (guard1) {
    /*      lData = load('LoadParams.mat'); */
    /*   */
    /*      Display_flag = lData.Display_flag; */
    /*      IgnoreGradSign = lData.IgnoreGradSign; */
    /*      IndexSigma = lData.IndexSigma; */
    /*      IndexSize = lData.IndexSize; */
    /*      MagFactor = lData.MagFactor; */
    /*      nFaces = lData.nFaces; */
    /*      OriHistThresh = lData.OriHistThresh; */
    /*      OriSigma = lData.OriSigma; */
    /*      Smooth_Flag = lData.Smooth_Flag; */
    /*      Smooth_Var = lData.Smooth_Var; */
    /*      Tessellation_flag = lData.Tessellation_flag; */
    /*      Tessellation_levels = lData.Tessellation_levels; */
    /*      TwoPeak_Flag = lData.TwoPeak_Flag; */
    /*      UseHistogramOri = lData.UseHistogramOri; */
    /*  function [keyX, keyY, keyZ, keyXYScale, keyTScale, keyIvec] = MakeKeypoint(pix, xyScale, tScale, x, y, z) */
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
    keyPoint->x = x;
    keyPoint->y = y;
    keyPoint->z = z;
    keyPoint->xyScale = xyScale;
    keyPoint->tScale = tScale;
    for (k = 0; k < 640; k++) {
      keyPoint->ivec[k] = 0.0;
    }

    MakeKeypointSample(keyPoint, pix);

    /*      keyX = key.x; */
    /*      keyY = key.y; */
    /*      keyZ = key.z; */
    /*      keyXYScale = key.xyScale; */
    /*      keyTScale = key.tScale; */
    /*      keyIvec = key.ivec; */
  }

  /*  [keyX, keyY, keyZ, keyXYScale, keyTScale, keyIvec] = MakeKeypoint(pix, xyScale, tScale, x, y, z); */
  /*  keypoint = struct('x', keyX,'y',keyY,'z',keyZ,'xyScale',keyXYScale,'tScale',keyTScale,'ivec',keyIvec); */
}

/*
 * File trailer for Create_Descriptor.c
 *
 * [EOF]
 */
