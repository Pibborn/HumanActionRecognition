/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * buildOriHists.c
 *
 * Code generation for function 'buildOriHists'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "Create_Descriptor.h"
#include "buildOriHists.h"
#include "eml_int_forloop_overflow_check.h"
#include "sort1.h"
#include "GetGradOri_vector.h"
#include "Create_Descriptor_data.h"

/* Variable Definitions */
static emlrtRSInfo vb_emlrtRSI = { 54, "buildOriHists",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\buildOriHists.m" };

static emlrtRSInfo wb_emlrtRSI = { 55, "buildOriHists",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\buildOriHists.m" };

static emlrtRSInfo xb_emlrtRSI = { 56, "buildOriHists",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\buildOriHists.m" };

static emlrtRSInfo yb_emlrtRSI = { 59, "buildOriHists",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\buildOriHists.m" };

static emlrtRSInfo ac_emlrtRSI = { 61, "buildOriHists",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\buildOriHists.m" };

static emlrtRSInfo bc_emlrtRSI = { 64, "buildOriHists",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\buildOriHists.m" };

static emlrtBCInfo f_emlrtBCI = { 1, 80, 71, 33, "myhist", "buildOriHists",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\buildOriHists.m", 0 };

static emlrtBCInfo g_emlrtBCI = { 1, 80, 71, 17, "myhist", "buildOriHists",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\buildOriHists.m", 0 };

/* Function Definitions */
void buildOriHists(const emlrtStack *sp, real_T x, real_T y, real_T z, int16_T
                   radius, const emxArray_real_T *pix, const real_T
                   fv_centers_data[], real_T myhist[80])
{
  real_T alpha1;
  int16_T a;
  int16_T xi;
  int16_T yi;
  int16_T zi;
  int32_T i9;
  int16_T b;
  boolean_T b_a;
  int16_T r;
  int16_T b_b;
  boolean_T c_a;
  int16_T c;
  int16_T c_b;
  boolean_T d_a;
  int16_T s;
  real_T vect[3];
  real_T mag;
  real_T a_data[240];
  real_T d_b[3];
  real_T corr_array_data[80];
  real_T beta1;
  char_T TRANSB;
  char_T TRANSA;
  ptrdiff_t m_t;
  ptrdiff_t n_t;
  ptrdiff_t k_t;
  ptrdiff_t lda_t;
  ptrdiff_t ldb_t;
  ptrdiff_t ldc_t;
  real_T unusedU0_data[80];
  int32_T iidx_size[1];
  int32_T iidx_data[80];
  int32_T i10;
  emlrtStack st;
  emlrtStack b_st;
  st.prev = sp;
  st.tls = sp->tls;
  b_st.prev = &st;
  b_st.tls = st.tls;

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
  alpha1 = muDoubleScalarRound(x);
  if (alpha1 < 32768.0) {
    if (alpha1 >= -32768.0) {
      a = (int16_T)alpha1;
    } else {
      a = MIN_int16_T;
    }
  } else if (alpha1 >= 32768.0) {
    a = MAX_int16_T;
  } else {
    a = 0;
  }

  xi = a;
  alpha1 = muDoubleScalarRound(y);
  if (alpha1 < 32768.0) {
    if (alpha1 >= -32768.0) {
      a = (int16_T)alpha1;
    } else {
      a = MIN_int16_T;
    }
  } else if (alpha1 >= 32768.0) {
    a = MAX_int16_T;
  } else {
    a = 0;
  }

  yi = a;
  alpha1 = muDoubleScalarRound(z);
  if (alpha1 < 32768.0) {
    if (alpha1 >= -32768.0) {
      a = (int16_T)alpha1;
    } else {
      a = MIN_int16_T;
    }
  } else if (alpha1 >= 32768.0) {
    a = MAX_int16_T;
  } else {
    a = 0;
  }

  zi = a;
  memset(&myhist[0], 0, 80U * sizeof(real_T));
  i9 = xi - radius;
  if (i9 > 32767) {
    i9 = 32767;
  } else {
    if (i9 < -32768) {
      i9 = -32768;
    }
  }

  a = (int16_T)i9;
  i9 = xi + radius;
  if (i9 > 32767) {
    i9 = 32767;
  } else {
    if (i9 < -32768) {
      i9 = -32768;
    }
  }

  b = (int16_T)i9;
  st.site = &vb_emlrtRSI;
  if (a > b) {
    b_a = false;
  } else {
    b_a = (b > 32766);
  }

  if (b_a) {
    b_st.site = &t_emlrtRSI;
    b_check_forloop_overflow_error(&b_st);
  }

  r = a;
  while (r <= b) {
    i9 = yi - radius;
    if (i9 > 32767) {
      i9 = 32767;
    } else {
      if (i9 < -32768) {
        i9 = -32768;
      }
    }

    a = (int16_T)i9;
    i9 = yi + radius;
    if (i9 > 32767) {
      i9 = 32767;
    } else {
      if (i9 < -32768) {
        i9 = -32768;
      }
    }

    b_b = (int16_T)i9;
    st.site = &wb_emlrtRSI;
    if (a > b_b) {
      c_a = false;
    } else {
      c_a = (b_b > 32766);
    }

    if (c_a) {
      b_st.site = &t_emlrtRSI;
      b_check_forloop_overflow_error(&b_st);
    }

    c = a;
    while (c <= b_b) {
      i9 = zi - radius;
      if (i9 > 32767) {
        i9 = 32767;
      } else {
        if (i9 < -32768) {
          i9 = -32768;
        }
      }

      a = (int16_T)i9;
      i9 = zi + radius;
      if (i9 > 32767) {
        i9 = 32767;
      } else {
        if (i9 < -32768) {
          i9 = -32768;
        }
      }

      c_b = (int16_T)i9;
      st.site = &xb_emlrtRSI;
      if (a > c_b) {
        d_a = false;
      } else {
        d_a = (c_b > 32766);
      }

      if (d_a) {
        b_st.site = &t_emlrtRSI;
        b_check_forloop_overflow_error(&b_st);
      }

      s = a;
      while (s <= c_b) {
        /*           /$ Do not use last row or column, which are not valid. $/ */
        if ((r >= 1) && (c >= 1) && (r < pix->size[0] - 1) && (c < pix->size[1]
             - 1) && (s >= 1) && (s < pix->size[2] - 1)) {
          st.site = &yb_emlrtRSI;
          GetGradOri_vector(&st, pix, r, c, s, &mag, vect);
          st.site = &ac_emlrtRSI;
          memcpy(&a_data[0], &fv_centers_data[0], 240U * sizeof(real_T));
          for (i9 = 0; i9 < 3; i9++) {
            d_b[i9] = vect[i9];
          }

          memset(&corr_array_data[0], 0, 80U * sizeof(real_T));
          alpha1 = 1.0;
          beta1 = 0.0;
          TRANSB = 'N';
          TRANSA = 'N';
          m_t = (ptrdiff_t)80;
          n_t = (ptrdiff_t)1;
          k_t = (ptrdiff_t)3;
          lda_t = (ptrdiff_t)80;
          ldb_t = (ptrdiff_t)3;
          ldc_t = (ptrdiff_t)80;
          dgemm(&TRANSA, &TRANSB, &m_t, &n_t, &k_t, &alpha1, &a_data[0], &lda_t,
                &d_b[0], &ldb_t, &beta1, &corr_array_data[0], &ldc_t);

          /*  [yy, ix] = sort(corr_array,'descend'); */
          st.site = &bc_emlrtRSI;
          memcpy(&unusedU0_data[0], &corr_array_data[0], 80U * sizeof(real_T));
          b_st.site = &fc_emlrtRSI;
          sort(&b_st, unusedU0_data, iidx_data, iidx_size);
          for (i9 = 0; i9 < 80; i9++) {
            unusedU0_data[i9] = iidx_data[i9];
          }

          i9 = (int32_T)unusedU0_data[0];
          if (!((i9 >= 1) && (i9 <= 80))) {
            emlrtDynamicBoundsCheckR2012b(i9, 1, 80, &f_emlrtBCI, sp);
          }

          i10 = (int32_T)unusedU0_data[0];
          if (!((i10 >= 1) && (i10 <= 80))) {
            emlrtDynamicBoundsCheckR2012b(i10, 1, 80, &g_emlrtBCI, sp);
          }

          myhist[i10 - 1] = myhist[i9 - 1] + mag;
        }

        s++;
        if (*emlrtBreakCheckR2012bFlagVar != 0) {
          emlrtBreakCheckR2012b(sp);
        }
      }

      c++;
      if (*emlrtBreakCheckR2012bFlagVar != 0) {
        emlrtBreakCheckR2012b(sp);
      }
    }

    r++;
    if (*emlrtBreakCheckR2012bFlagVar != 0) {
      emlrtBreakCheckR2012b(sp);
    }
  }
}

/* End of code generation (buildOriHists.c) */
