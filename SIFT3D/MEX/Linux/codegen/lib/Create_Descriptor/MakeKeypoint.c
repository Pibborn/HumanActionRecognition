/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: MakeKeypoint.c
 *
 * MATLAB Coder version            : 3.2
 * C/C++ source code generated on  : 18-Nov-2016 16:32:39
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "Create_Descriptor.h"
#include "MakeKeypoint.h"
#include "NormalizeVec.h"
#include "KeySampleVec.h"
#include "Create_Descriptor_rtwutil.h"

/* Function Definitions */

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
 *  TwoPeak_Flag = lData.TwoPeak_Flag;
 *  UseHistogramOri = lData.UseHistogramOri;
 * Arguments    : struct0_T *key
 *                const emxArray_real_T *pix
 * Return Type  : void
 */
void MakeKeypointSample(struct0_T *key, const emxArray_real_T *pix)
{
  int changed;
  double vec[640];
  int i;
  double b_vec;
  short intval;

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
  changed = 0;
  KeySampleVec(key->x, key->y, key->z, key->xyScale, key->tScale, pix, vec);
  NormalizeVec(vec);
  for (i = 0; i < 640; i++) {
    b_vec = vec[i];
    if (vec[i] > 0.2) {
      b_vec = 0.2;
      changed = 1;
    }

    vec[i] = b_vec;
  }

  if (changed != 0) {
    NormalizeVec(vec);
  }

  for (i = 0; i < 640; i++) {
    b_vec = rt_roundd_snf(512.0 * vec[i]);
    if (b_vec < 32768.0) {
      if (b_vec >= -32768.0) {
        intval = (short)b_vec;
      } else {
        intval = MIN_int16_T;
      }
    } else if (b_vec >= 32768.0) {
      intval = MAX_int16_T;
    } else {
      intval = 0;
    }

    changed = intval;
    if (255 <= changed) {
      changed = 255;
    }

    intval = (short)changed;
    if (intval < 0) {
      intval = 0;
    }

    key->ivec[i] = intval;
  }
}

/*
 * File trailer for MakeKeypoint.c
 *
 * [EOF]
 */
