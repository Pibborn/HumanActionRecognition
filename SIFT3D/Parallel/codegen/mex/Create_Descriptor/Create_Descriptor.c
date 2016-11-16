/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Create_Descriptor.c
 *
 * Code generation for function 'Create_Descriptor'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "Create_Descriptor.h"
#include "dot.h"
#include "Create_Descriptor_emxutil.h"
#include "MakeKeypoint.h"
#include "sort1.h"
#include "buildOriHists.h"
#include "sphere_tri.h"
#include "Create_Descriptor_mexutil.h"
#include "Create_Descriptor_data.h"

/* Variable Definitions */
static emlrtRSInfo emlrtRSI = { 74, "Create_Descriptor",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\Create_Descriptor.m" };

static emlrtRSInfo b_emlrtRSI = { 75, "Create_Descriptor",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\Create_Descriptor.m" };

static emlrtRSInfo c_emlrtRSI = { 78, "Create_Descriptor",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\Create_Descriptor.m" };

static emlrtRSInfo d_emlrtRSI = { 82, "Create_Descriptor",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\Create_Descriptor.m" };

static emlrtRSInfo e_emlrtRSI = { 87, "Create_Descriptor",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\Create_Descriptor.m" };

static emlrtRSInfo gd_emlrtRSI = { 51, "MakeKeypoint",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\MakeKeypoint.m" };

static emlrtMCInfo emlrtMCI = { 83, 5, "Create_Descriptor",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\Create_Descriptor.m" };

static emlrtBCInfo emlrtBCI = { -1, -1, 82, 41, "fv.centers",
  "Create_Descriptor",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\Create_Descriptor.m", 0 };

static emlrtBCInfo b_emlrtBCI = { -1, -1, 82, 61, "fv.centers",
  "Create_Descriptor",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\Create_Descriptor.m", 0 };

static emlrtBCInfo c_emlrtBCI = { -1, -1, 82, 94, "fv.centers",
  "Create_Descriptor",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\Create_Descriptor.m", 0 };

static emlrtBCInfo d_emlrtBCI = { -1, -1, 82, 114, "fv.centers",
  "Create_Descriptor",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\Create_Descriptor.m", 0 };

static emlrtRSInfo ce_emlrtRSI = { 83, "Create_Descriptor",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\Create_Descriptor.m" };

/* Function Definitions */
void Create_Descriptor(const emlrtStack *sp, const emxArray_real_T *pix, real_T
  xyScale, real_T tScale, real_T x, real_T y, real_T z, struct0_T *keyPoint,
  real_T *reRun)
{
  int32_T i0;
  emxArray_real_T *expl_temp;
  int32_T fv_centers_size[2];
  real_T fv_centers_data[240];
  int32_T expl_temp_size[2];
  real_T expl_temp_data[240];
  real_T d0;
  int16_T i1;
  real_T myhist[80];
  int32_T iidx[80];
  real_T b_fv_centers_data[3];
  real_T c_fv_centers_data[3];
  boolean_T guard1 = false;
  static const char_T cv0[82] = { 'M', 'I', 'S', 'S', ' ', ':', ' ', 'T', 'o',
    'p', ' ', '3', ' ', 'o', 'r', 'i', 'e', 'n', 't', 'a', 't', 'i', 'o', 'n',
    's', ' ', 'w', 'i', 't', 'h', 'i', 'n', ' ', '~', '2', '5', ' ', 'd', 'e',
    'g', 'r', 'e', 'e', ' ', 'r', 'a', 'n', 'g', 'e', ' ', ':', ' ', 'R', 'e',
    't', 'u', 'r', 'n', 'i', 'n', 'g', ' ', 'w', 'i', 't', 'h', ' ', 'r', 'e',
    'R', 'u', 'n', ' ', 'f', 'l', 'a', 'g', ' ', 's', 'e', 't', '.' };

  char_T u[82];
  const mxArray *b_y;
  static const int32_T iv0[2] = { 1, 82 };

  const mxArray *m0;
  emlrtStack st;
  emlrtStack b_st;
  st.prev = sp;
  st.tls = sp->tls;
  b_st.prev = &st;
  b_st.tls = st.tls;
  emlrtHeapReferenceStackEnterFcnR2012b(sp);

  /*  Main function of 3DSIFT Program from http://www.cs.ucf.edu/~pscovann/ */
  /*  */
  /*  Inputs: */
  /*  pix - a 3 dimensional matrix of uint8 */
  /*  xyScale and tScale - affects both the scale and the resolution, these are */
  /*  usually set to 1 and scaling is done before calling this function */
  /*  x, y, and z - the location of the center of the keypoint where a descriptor is requested */
  /*  */
  /*  Outputs: */
  /*  keypoint - the descriptor, varies in size depending on values in LoadParams.m */
  /*  reRun - a flag (0 or 1) which is set if the data at (x,y,z) is not */
  /*  descriptive enough for a good keypoint */
  /*  */
  /*  Example: */
  /*  See Demo.m */
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
  for (i0 = 0; i0 < 640; i0++) {
    keyPoint->ivec[i0] = 0.0;
  }

  emxInit_real_T(sp, &expl_temp, 2, &emlrtRTEI, true);
  *reRun = 0.0;
  st.site = &emlrtRSI;
  sphere_tri(&st, expl_temp, expl_temp_data, expl_temp_size, fv_centers_data,
             fv_centers_size);
  d0 = muDoubleScalarRound(xyScale * 3.0);
  if (d0 < 32768.0) {
    if (d0 >= -32768.0) {
      i1 = (int16_T)d0;
    } else {
      i1 = MIN_int16_T;
    }
  } else if (d0 >= 32768.0) {
    i1 = MAX_int16_T;
  } else {
    i1 = 0;
  }

  st.site = &b_emlrtRSI;
  buildOriHists(&st, x, y, z, i1, pix, fv_centers_data, myhist);

  /*  [yy, ix] = sort(myhist,'descend'); */
  st.site = &c_emlrtRSI;
  b_st.site = &fc_emlrtRSI;
  c_sort(&b_st, myhist, iidx);
  emxFree_real_T(&expl_temp);
  for (i0 = 0; i0 < 80; i0++) {
    myhist[i0] = iidx[i0];
  }

  /*  Dom_Peak = ix(1); */
  /*  Sec_Peak = ix(2); */
  i0 = (int32_T)myhist[0];
  if (!((i0 >= 1) && (i0 <= 80))) {
    emlrtDynamicBoundsCheckR2012b(i0, 1, 80, &emlrtBCI, sp);
  }

  for (i0 = 0; i0 < 3; i0++) {
    b_fv_centers_data[i0] = fv_centers_data[((int32_T)myhist[0] +
      fv_centers_size[0] * i0) - 1];
  }

  i0 = (int32_T)myhist[1];
  if (!((i0 >= 1) && (i0 <= 80))) {
    emlrtDynamicBoundsCheckR2012b(i0, 1, 80, &b_emlrtBCI, sp);
  }

  for (i0 = 0; i0 < 3; i0++) {
    c_fv_centers_data[i0] = fv_centers_data[((int32_T)myhist[1] +
      fv_centers_size[0] * i0) - 1];
  }

  guard1 = false;
  st.site = &d_emlrtRSI;
  if (dot(b_fv_centers_data, c_fv_centers_data) > 0.9) {
    i0 = (int32_T)myhist[0];
    if (!((i0 >= 1) && (i0 <= 80))) {
      emlrtDynamicBoundsCheckR2012b(i0, 1, 80, &c_emlrtBCI, sp);
    }

    for (i0 = 0; i0 < 3; i0++) {
      b_fv_centers_data[i0] = fv_centers_data[((int32_T)myhist[0] +
        fv_centers_size[0] * i0) - 1];
    }

    i0 = (int32_T)myhist[2];
    if (!((i0 >= 1) && (i0 <= 80))) {
      emlrtDynamicBoundsCheckR2012b(i0, 1, 80, &d_emlrtBCI, sp);
    }

    for (i0 = 0; i0 < 3; i0++) {
      c_fv_centers_data[i0] = fv_centers_data[((int32_T)myhist[2] +
        fv_centers_size[0] * i0) - 1];
    }

    st.site = &d_emlrtRSI;
    if (dot(b_fv_centers_data, c_fv_centers_data) > 0.9) {
      memcpy(&u[0], &cv0[0], 82U * sizeof(char_T));
      b_y = NULL;
      m0 = emlrtCreateCharArray(2, iv0);
      emlrtInitCharArrayR2013a(sp, 82, m0, &u[0]);
      emlrtAssign(&b_y, m0);
      st.site = &ce_emlrtRSI;
      disp(&st, b_y, &emlrtMCI);
      *reRun = 1.0;
    } else {
      guard1 = true;
    }
  } else {
    guard1 = true;
  }

  if (guard1) {
    st.site = &e_emlrtRSI;

    /*  function [keyX, keyY, keyZ, keyXYScale, keyTScale, keyIvec] = MakeKeypoint(pix, xyScale, tScale, x, y, z) */
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
    for (i0 = 0; i0 < 640; i0++) {
      keyPoint->ivec[i0] = 0.0;
    }

    b_st.site = &gd_emlrtRSI;
    MakeKeypointSample(&b_st, keyPoint, pix);

    /*      keyX = key.x; */
    /*      keyY = key.y; */
    /*      keyZ = key.z; */
    /*      keyXYScale = key.xyScale; */
    /*      keyTScale = key.tScale; */
    /*      keyIvec = key.ivec; */
  }

  /*  [keyX, keyY, keyZ, keyXYScale, keyTScale, keyIvec] = MakeKeypoint(pix, xyScale, tScale, x, y, z); */
  /*  keypoint = struct('x', keyX,'y',keyY,'z',keyZ,'xyScale',keyXYScale,'tScale',keyTScale,'ivec',keyIvec); */
  emlrtHeapReferenceStackLeaveFcnR2012b(sp);
}

/* End of code generation (Create_Descriptor.c) */
