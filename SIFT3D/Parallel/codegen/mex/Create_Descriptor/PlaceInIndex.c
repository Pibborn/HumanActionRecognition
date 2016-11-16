/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * PlaceInIndex.c
 *
 * Code generation for function 'PlaceInIndex'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "Create_Descriptor.h"
#include "PlaceInIndex.h"
#include "sort1.h"
#include "Create_Descriptor_data.h"

/* Variable Definitions */
static emlrtRSInfo ud_emlrtRSI = { 44, "PlaceInIndex",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\PlaceInIndex.m" };

static emlrtRSInfo vd_emlrtRSI = { 46, "PlaceInIndex",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\PlaceInIndex.m" };

static emlrtRSInfo wd_emlrtRSI = { 51, "PlaceInIndex",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\PlaceInIndex.m" };

static emlrtRSInfo xd_emlrtRSI = { 53, "PlaceInIndex",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\PlaceInIndex.m" };

static emlrtBCInfo lc_emlrtBCI = { 1, 2, 53, 37, "index", "PlaceInIndex",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\PlaceInIndex.m", 0 };

static emlrtBCInfo mc_emlrtBCI = { 1, 2, 53, 39, "index", "PlaceInIndex",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\PlaceInIndex.m", 0 };

static emlrtBCInfo nc_emlrtBCI = { 1, 2, 53, 41, "index", "PlaceInIndex",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\PlaceInIndex.m", 0 };

static emlrtBCInfo oc_emlrtBCI = { 1, 80, 53, 43, "index", "PlaceInIndex",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\PlaceInIndex.m", 0 };

static emlrtBCInfo pc_emlrtBCI = { 1, 2, 53, 15, "index", "PlaceInIndex",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\PlaceInIndex.m", 0 };

static emlrtBCInfo qc_emlrtBCI = { 1, 2, 53, 17, "index", "PlaceInIndex",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\PlaceInIndex.m", 0 };

static emlrtBCInfo rc_emlrtBCI = { 1, 2, 53, 19, "index", "PlaceInIndex",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\PlaceInIndex.m", 0 };

static emlrtBCInfo sc_emlrtBCI = { 1, 80, 53, 21, "index", "PlaceInIndex",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\PlaceInIndex.m", 0 };

/* Function Definitions */
void PlaceInIndex(const emlrtStack *sp, real_T b_index[640], real_T mag, const
                  real_T vect[3], int16_T i, int16_T j, int16_T s, const real_T
                  fv_centers_data[])
{
  real_T a_data[240];
  real_T b[3];
  int32_T k;
  real_T corr_array_data[80];
  real_T alpha1;
  real_T beta1;
  char_T TRANSB;
  char_T TRANSA;
  ptrdiff_t m_t;
  ptrdiff_t n_t;
  ptrdiff_t k_t;
  ptrdiff_t lda_t;
  ptrdiff_t ldb_t;
  ptrdiff_t ldc_t;
  int32_T iidx_size[1];
  int32_T iidx_data[80];
  int32_T ix_data[80];
  real_T tmpsum;
  int32_T ii;
  int32_T i21;
  int32_T i22;
  int32_T i23;
  int32_T i24;
  int32_T i25;
  int32_T i26;
  int32_T i27;
  emlrtStack st;
  emlrtStack b_st;
  st.prev = sp;
  st.tls = sp->tls;
  b_st.prev = &st;
  b_st.tls = st.tls;

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
  st.site = &ud_emlrtRSI;
  memcpy(&a_data[0], &fv_centers_data[0], 240U * sizeof(real_T));
  for (k = 0; k < 3; k++) {
    b[k] = vect[k];
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
  dgemm(&TRANSA, &TRANSB, &m_t, &n_t, &k_t, &alpha1, &a_data[0], &lda_t, &b[0],
        &ldb_t, &beta1, &corr_array_data[0], &ldc_t);
  st.site = &vd_emlrtRSI;
  b_st.site = &fc_emlrtRSI;
  sort(&b_st, corr_array_data, iidx_data, iidx_size);
  for (k = 0; k < 80; k++) {
    ix_data[k] = iidx_data[k];
  }

  st.site = &wd_emlrtRSI;
  st.site = &wd_emlrtRSI;
  for (k = 0; k < 3; k++) {
    b[k] = muDoubleScalarPower(corr_array_data[k], 20.0);
  }

  tmpsum = b[0];
  for (k = 0; k < 2; k++) {
    tmpsum += b[k + 1];
  }

  ii = 0;
  while (ii < 3) {
    st.site = &xd_emlrtRSI;
    k = i;
    if (!((k >= 1) && (k <= 2))) {
      emlrtDynamicBoundsCheckR2012b(k, 1, 2, &lc_emlrtBCI, sp);
    }

    i21 = j;
    if (!((i21 >= 1) && (i21 <= 2))) {
      emlrtDynamicBoundsCheckR2012b(i21, 1, 2, &mc_emlrtBCI, sp);
    }

    i22 = s;
    if (!((i22 >= 1) && (i22 <= 2))) {
      emlrtDynamicBoundsCheckR2012b(i22, 1, 2, &nc_emlrtBCI, sp);
    }

    i23 = ix_data[ii];
    if (!((i23 >= 1) && (i23 <= 80))) {
      emlrtDynamicBoundsCheckR2012b(i23, 1, 80, &oc_emlrtBCI, sp);
    }

    i24 = i;
    if (!((i24 >= 1) && (i24 <= 2))) {
      emlrtDynamicBoundsCheckR2012b(i24, 1, 2, &pc_emlrtBCI, sp);
    }

    i25 = j;
    if (!((i25 >= 1) && (i25 <= 2))) {
      emlrtDynamicBoundsCheckR2012b(i25, 1, 2, &qc_emlrtBCI, sp);
    }

    i26 = s;
    if (!((i26 >= 1) && (i26 <= 2))) {
      emlrtDynamicBoundsCheckR2012b(i26, 1, 2, &rc_emlrtBCI, sp);
    }

    i27 = ix_data[ii];
    if (!((i27 >= 1) && (i27 <= 80))) {
      emlrtDynamicBoundsCheckR2012b(i27, 1, 80, &sc_emlrtBCI, sp);
    }

    b_index[(((i24 + ((i25 - 1) << 1)) + ((i26 - 1) << 2)) + ((i27 - 1) << 3)) -
      1] = b_index[(((k + ((i21 - 1) << 1)) + ((i22 - 1) << 2)) + ((i23 - 1) <<
      3)) - 1] + mag * muDoubleScalarPower(corr_array_data[ii], 20.0) / tmpsum;
    ii++;
    if (*emlrtBreakCheckR2012bFlagVar != 0) {
      emlrtBreakCheckR2012b(sp);
    }
  }
}

/* End of code generation (PlaceInIndex.c) */
