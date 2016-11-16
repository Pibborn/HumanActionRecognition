/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * GetGradOri_vector.c
 *
 * Code generation for function 'GetGradOri_vector'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "Create_Descriptor.h"
#include "GetGradOri_vector.h"
#include "error.h"
#include "Create_Descriptor_data.h"

/* Variable Definitions */
static emlrtRSInfo cc_emlrtRSI = { 57, "GetGradOri_vector",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\GetGradOri_vector.m" };

static emlrtBCInfo h_emlrtBCI = { -1, -1, 32, 33, "pix", "GetGradOri_vector",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\GetGradOri_vector.m", 0 };

static emlrtBCInfo i_emlrtBCI = { -1, -1, 32, 56, "pix", "GetGradOri_vector",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\GetGradOri_vector.m", 0 };

static emlrtBCInfo j_emlrtBCI = { -1, -1, 39, 31, "pix", "GetGradOri_vector",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\GetGradOri_vector.m", 0 };

static emlrtBCInfo k_emlrtBCI = { -1, -1, 39, 52, "pix", "GetGradOri_vector",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\GetGradOri_vector.m", 0 };

static emlrtBCInfo l_emlrtBCI = { -1, -1, 46, 35, "pix", "GetGradOri_vector",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\GetGradOri_vector.m", 0 };

static emlrtBCInfo m_emlrtBCI = { -1, -1, 46, 58, "pix", "GetGradOri_vector",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\GetGradOri_vector.m", 0 };

static emlrtBCInfo n_emlrtBCI = { -1, -1, 36, 24, "pix", "GetGradOri_vector",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\GetGradOri_vector.m", 0 };

static emlrtBCInfo o_emlrtBCI = { -1, -1, 36, 26, "pix", "GetGradOri_vector",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\GetGradOri_vector.m", 0 };

static emlrtBCInfo p_emlrtBCI = { -1, -1, 36, 30, "pix", "GetGradOri_vector",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\GetGradOri_vector.m", 0 };

static emlrtBCInfo q_emlrtBCI = { -1, -1, 36, 47, "pix", "GetGradOri_vector",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\GetGradOri_vector.m", 0 };

static emlrtBCInfo r_emlrtBCI = { -1, -1, 36, 49, "pix", "GetGradOri_vector",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\GetGradOri_vector.m", 0 };

static emlrtBCInfo s_emlrtBCI = { -1, -1, 36, 53, "pix", "GetGradOri_vector",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\GetGradOri_vector.m", 0 };

static emlrtBCInfo t_emlrtBCI = { -1, -1, 34, 31, "pix", "GetGradOri_vector",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\GetGradOri_vector.m", 0 };

static emlrtBCInfo u_emlrtBCI = { -1, -1, 34, 33, "pix", "GetGradOri_vector",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\GetGradOri_vector.m", 0 };

static emlrtBCInfo v_emlrtBCI = { -1, -1, 34, 35, "pix", "GetGradOri_vector",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\GetGradOri_vector.m", 0 };

static emlrtBCInfo w_emlrtBCI = { -1, -1, 34, 52, "pix", "GetGradOri_vector",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\GetGradOri_vector.m", 0 };

static emlrtBCInfo x_emlrtBCI = { -1, -1, 34, 54, "pix", "GetGradOri_vector",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\GetGradOri_vector.m", 0 };

static emlrtBCInfo y_emlrtBCI = { -1, -1, 34, 58, "pix", "GetGradOri_vector",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\GetGradOri_vector.m", 0 };

static emlrtBCInfo ab_emlrtBCI = { -1, -1, 32, 31, "pix", "GetGradOri_vector",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\GetGradOri_vector.m", 0 };

static emlrtBCInfo bb_emlrtBCI = { -1, -1, 32, 37, "pix", "GetGradOri_vector",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\GetGradOri_vector.m", 0 };

static emlrtBCInfo cb_emlrtBCI = { -1, -1, 32, 54, "pix", "GetGradOri_vector",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\GetGradOri_vector.m", 0 };

static emlrtBCInfo db_emlrtBCI = { -1, -1, 32, 58, "pix", "GetGradOri_vector",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\GetGradOri_vector.m", 0 };

static emlrtBCInfo eb_emlrtBCI = { -1, -1, 43, 24, "pix", "GetGradOri_vector",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\GetGradOri_vector.m", 0 };

static emlrtBCInfo fb_emlrtBCI = { -1, -1, 43, 28, "pix", "GetGradOri_vector",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\GetGradOri_vector.m", 0 };

static emlrtBCInfo gb_emlrtBCI = { -1, -1, 43, 30, "pix", "GetGradOri_vector",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\GetGradOri_vector.m", 0 };

static emlrtBCInfo hb_emlrtBCI = { -1, -1, 43, 47, "pix", "GetGradOri_vector",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\GetGradOri_vector.m", 0 };

static emlrtBCInfo ib_emlrtBCI = { -1, -1, 43, 51, "pix", "GetGradOri_vector",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\GetGradOri_vector.m", 0 };

static emlrtBCInfo jb_emlrtBCI = { -1, -1, 43, 53, "pix", "GetGradOri_vector",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\GetGradOri_vector.m", 0 };

static emlrtBCInfo kb_emlrtBCI = { -1, -1, 41, 31, "pix", "GetGradOri_vector",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\GetGradOri_vector.m", 0 };

static emlrtBCInfo lb_emlrtBCI = { -1, -1, 41, 35, "pix", "GetGradOri_vector",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\GetGradOri_vector.m", 0 };

static emlrtBCInfo mb_emlrtBCI = { -1, -1, 41, 37, "pix", "GetGradOri_vector",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\GetGradOri_vector.m", 0 };

static emlrtBCInfo nb_emlrtBCI = { -1, -1, 41, 54, "pix", "GetGradOri_vector",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\GetGradOri_vector.m", 0 };

static emlrtBCInfo ob_emlrtBCI = { -1, -1, 41, 56, "pix", "GetGradOri_vector",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\GetGradOri_vector.m", 0 };

static emlrtBCInfo pb_emlrtBCI = { -1, -1, 41, 58, "pix", "GetGradOri_vector",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\GetGradOri_vector.m", 0 };

static emlrtBCInfo qb_emlrtBCI = { -1, -1, 39, 33, "pix", "GetGradOri_vector",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\GetGradOri_vector.m", 0 };

static emlrtBCInfo rb_emlrtBCI = { -1, -1, 39, 35, "pix", "GetGradOri_vector",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\GetGradOri_vector.m", 0 };

static emlrtBCInfo sb_emlrtBCI = { -1, -1, 39, 56, "pix", "GetGradOri_vector",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\GetGradOri_vector.m", 0 };

static emlrtBCInfo tb_emlrtBCI = { -1, -1, 39, 58, "pix", "GetGradOri_vector",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\GetGradOri_vector.m", 0 };

static emlrtBCInfo ub_emlrtBCI = { -1, -1, 50, 24, "pix", "GetGradOri_vector",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\GetGradOri_vector.m", 0 };

static emlrtBCInfo vb_emlrtBCI = { -1, -1, 50, 26, "pix", "GetGradOri_vector",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\GetGradOri_vector.m", 0 };

static emlrtBCInfo wb_emlrtBCI = { -1, -1, 50, 28, "pix", "GetGradOri_vector",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\GetGradOri_vector.m", 0 };

static emlrtBCInfo xb_emlrtBCI = { -1, -1, 50, 47, "pix", "GetGradOri_vector",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\GetGradOri_vector.m", 0 };

static emlrtBCInfo yb_emlrtBCI = { -1, -1, 50, 49, "pix", "GetGradOri_vector",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\GetGradOri_vector.m", 0 };

static emlrtBCInfo ac_emlrtBCI = { -1, -1, 50, 51, "pix", "GetGradOri_vector",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\GetGradOri_vector.m", 0 };

static emlrtBCInfo bc_emlrtBCI = { -1, -1, 48, 31, "pix", "GetGradOri_vector",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\GetGradOri_vector.m", 0 };

static emlrtBCInfo cc_emlrtBCI = { -1, -1, 48, 33, "pix", "GetGradOri_vector",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\GetGradOri_vector.m", 0 };

static emlrtBCInfo dc_emlrtBCI = { -1, -1, 48, 35, "pix", "GetGradOri_vector",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\GetGradOri_vector.m", 0 };

static emlrtBCInfo ec_emlrtBCI = { -1, -1, 48, 52, "pix", "GetGradOri_vector",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\GetGradOri_vector.m", 0 };

static emlrtBCInfo fc_emlrtBCI = { -1, -1, 48, 54, "pix", "GetGradOri_vector",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\GetGradOri_vector.m", 0 };

static emlrtBCInfo gc_emlrtBCI = { -1, -1, 48, 56, "pix", "GetGradOri_vector",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\GetGradOri_vector.m", 0 };

static emlrtBCInfo hc_emlrtBCI = { -1, -1, 46, 31, "pix", "GetGradOri_vector",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\GetGradOri_vector.m", 0 };

static emlrtBCInfo ic_emlrtBCI = { -1, -1, 46, 33, "pix", "GetGradOri_vector",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\GetGradOri_vector.m", 0 };

static emlrtBCInfo jc_emlrtBCI = { -1, -1, 46, 54, "pix", "GetGradOri_vector",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\GetGradOri_vector.m", 0 };

static emlrtBCInfo kc_emlrtBCI = { -1, -1, 46, 56, "pix", "GetGradOri_vector",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\GetGradOri_vector.m", 0 };

/* Function Definitions */
void GetGradOri_vector(const emlrtStack *sp, const emxArray_real_T *pix, int16_T
  r, int16_T c, int16_T s, real_T *mag, real_T vect[3])
{
  int32_T i11;
  int32_T i12;
  int32_T i13;
  int32_T i14;
  int32_T i15;
  real_T xgrad;
  int32_T i16;
  int32_T i17;
  real_T ygrad;
  real_T zgrad;
  real_T x;
  real_T b_xgrad[3];
  static const int8_T iv7[3] = { 1, 0, 0 };

  emlrtStack st;
  emlrtStack b_st;
  st.prev = sp;
  st.tls = sp->tls;
  b_st.prev = &st;
  b_st.tls = st.tls;
  if (r > pix->size[0]) {
    /*  r = rows; */
    r = (int16_T)pix->size[0];
  }

  if (c > pix->size[1]) {
    /*  c = cols; */
    c = (int16_T)pix->size[1];
  }

  if (s > pix->size[2]) {
    /*  s = slices; */
    s = (int16_T)pix->size[2];
  }

  if (c == 1) {
    i11 = pix->size[1];
    if (!(2 <= i11)) {
      emlrtDynamicBoundsCheckR2012b(2, 1, i11, &h_emlrtBCI, sp);
    }

    i11 = pix->size[1];
    if (!(1 <= i11)) {
      emlrtDynamicBoundsCheckR2012b(1, 1, i11, &i_emlrtBCI, sp);
    }

    i11 = pix->size[0];
    i12 = r;
    if (!((i12 >= 1) && (i12 <= i11))) {
      emlrtDynamicBoundsCheckR2012b(i12, 1, i11, &ab_emlrtBCI, sp);
    }

    i11 = pix->size[2];
    i13 = s;
    if (!((i13 >= 1) && (i13 <= i11))) {
      emlrtDynamicBoundsCheckR2012b(i13, 1, i11, &bb_emlrtBCI, sp);
    }

    i11 = pix->size[0];
    i14 = r;
    if (!((i14 >= 1) && (i14 <= i11))) {
      emlrtDynamicBoundsCheckR2012b(i14, 1, i11, &cb_emlrtBCI, sp);
    }

    i11 = pix->size[2];
    i15 = s;
    if (!((i15 >= 1) && (i15 <= i11))) {
      emlrtDynamicBoundsCheckR2012b(i15, 1, i11, &db_emlrtBCI, sp);
    }

    xgrad = 2.0 * (pix->data[((i12 + pix->size[0]) + pix->size[0] * pix->size[1]
      * (i13 - 1)) - 1] - pix->data[(i14 + pix->size[0] * pix->size[1] * (i15 -
      1)) - 1]);
  } else if (c == pix->size[1]) {
    i11 = pix->size[0];
    i12 = r;
    if (!((i12 >= 1) && (i12 <= i11))) {
      emlrtDynamicBoundsCheckR2012b(i12, 1, i11, &t_emlrtBCI, sp);
    }

    i11 = pix->size[1];
    i13 = c;
    if (!((i13 >= 1) && (i13 <= i11))) {
      emlrtDynamicBoundsCheckR2012b(i13, 1, i11, &u_emlrtBCI, sp);
    }

    i11 = pix->size[2];
    i14 = s;
    if (!((i14 >= 1) && (i14 <= i11))) {
      emlrtDynamicBoundsCheckR2012b(i14, 1, i11, &v_emlrtBCI, sp);
    }

    i11 = pix->size[0];
    i15 = r;
    if (!((i15 >= 1) && (i15 <= i11))) {
      emlrtDynamicBoundsCheckR2012b(i15, 1, i11, &w_emlrtBCI, sp);
    }

    i11 = pix->size[1];
    i16 = c - 1;
    if (!((i16 >= 1) && (i16 <= i11))) {
      emlrtDynamicBoundsCheckR2012b(i16, 1, i11, &x_emlrtBCI, sp);
    }

    i11 = pix->size[2];
    i17 = s;
    if (!((i17 >= 1) && (i17 <= i11))) {
      emlrtDynamicBoundsCheckR2012b(i17, 1, i11, &y_emlrtBCI, sp);
    }

    xgrad = 2.0 * (pix->data[((i12 + pix->size[0] * (i13 - 1)) + pix->size[0] *
      pix->size[1] * (i14 - 1)) - 1] - pix->data[((i15 + pix->size[0] * (i16 - 1))
      + pix->size[0] * pix->size[1] * (i17 - 1)) - 1]);
  } else {
    i11 = pix->size[0];
    i12 = r;
    if (!((i12 >= 1) && (i12 <= i11))) {
      emlrtDynamicBoundsCheckR2012b(i12, 1, i11, &n_emlrtBCI, sp);
    }

    i11 = pix->size[1];
    i13 = c + 1;
    if (i13 > 32767) {
      i13 = 32767;
    }

    if (!((i13 >= 1) && (i13 <= i11))) {
      emlrtDynamicBoundsCheckR2012b(i13, 1, i11, &o_emlrtBCI, sp);
    }

    i11 = pix->size[2];
    i14 = s;
    if (!((i14 >= 1) && (i14 <= i11))) {
      emlrtDynamicBoundsCheckR2012b(i14, 1, i11, &p_emlrtBCI, sp);
    }

    i11 = pix->size[0];
    i15 = r;
    if (!((i15 >= 1) && (i15 <= i11))) {
      emlrtDynamicBoundsCheckR2012b(i15, 1, i11, &q_emlrtBCI, sp);
    }

    i11 = pix->size[1];
    i16 = c - 1;
    if (i16 < -32768) {
      i16 = -32768;
    }

    if (!((i16 >= 1) && (i16 <= i11))) {
      emlrtDynamicBoundsCheckR2012b(i16, 1, i11, &r_emlrtBCI, sp);
    }

    i11 = pix->size[2];
    i17 = s;
    if (!((i17 >= 1) && (i17 <= i11))) {
      emlrtDynamicBoundsCheckR2012b(i17, 1, i11, &s_emlrtBCI, sp);
    }

    xgrad = pix->data[((i12 + pix->size[0] * (i13 - 1)) + pix->size[0] *
                       pix->size[1] * (i14 - 1)) - 1] - pix->data[((i15 +
      pix->size[0] * (i16 - 1)) + pix->size[0] * pix->size[1] * (i17 - 1)) - 1];
  }

  if (r == 1) {
    i11 = pix->size[0];
    if (!(1 <= i11)) {
      emlrtDynamicBoundsCheckR2012b(1, 1, i11, &j_emlrtBCI, sp);
    }

    i11 = pix->size[0];
    if (!(2 <= i11)) {
      emlrtDynamicBoundsCheckR2012b(2, 1, i11, &k_emlrtBCI, sp);
    }

    i11 = pix->size[1];
    i12 = c;
    if (!((i12 >= 1) && (i12 <= i11))) {
      emlrtDynamicBoundsCheckR2012b(i12, 1, i11, &qb_emlrtBCI, sp);
    }

    i11 = pix->size[2];
    i13 = s;
    if (!((i13 >= 1) && (i13 <= i11))) {
      emlrtDynamicBoundsCheckR2012b(i13, 1, i11, &rb_emlrtBCI, sp);
    }

    i11 = pix->size[1];
    i14 = c;
    if (!((i14 >= 1) && (i14 <= i11))) {
      emlrtDynamicBoundsCheckR2012b(i14, 1, i11, &sb_emlrtBCI, sp);
    }

    i11 = pix->size[2];
    i15 = s;
    if (!((i15 >= 1) && (i15 <= i11))) {
      emlrtDynamicBoundsCheckR2012b(i15, 1, i11, &tb_emlrtBCI, sp);
    }

    ygrad = 2.0 * (pix->data[pix->size[0] * (i12 - 1) + pix->size[0] * pix->
                   size[1] * (i13 - 1)] - pix->data[(pix->size[0] * (i14 - 1) +
      pix->size[0] * pix->size[1] * (i15 - 1)) + 1]);
  } else if (r == pix->size[0]) {
    i11 = pix->size[0];
    i12 = r - 1;
    if (!((i12 >= 1) && (i12 <= i11))) {
      emlrtDynamicBoundsCheckR2012b(i12, 1, i11, &kb_emlrtBCI, sp);
    }

    i11 = pix->size[1];
    i13 = c;
    if (!((i13 >= 1) && (i13 <= i11))) {
      emlrtDynamicBoundsCheckR2012b(i13, 1, i11, &lb_emlrtBCI, sp);
    }

    i11 = pix->size[2];
    i14 = s;
    if (!((i14 >= 1) && (i14 <= i11))) {
      emlrtDynamicBoundsCheckR2012b(i14, 1, i11, &mb_emlrtBCI, sp);
    }

    i11 = pix->size[0];
    i15 = r;
    if (!((i15 >= 1) && (i15 <= i11))) {
      emlrtDynamicBoundsCheckR2012b(i15, 1, i11, &nb_emlrtBCI, sp);
    }

    i11 = pix->size[1];
    i16 = c;
    if (!((i16 >= 1) && (i16 <= i11))) {
      emlrtDynamicBoundsCheckR2012b(i16, 1, i11, &ob_emlrtBCI, sp);
    }

    i11 = pix->size[2];
    i17 = s;
    if (!((i17 >= 1) && (i17 <= i11))) {
      emlrtDynamicBoundsCheckR2012b(i17, 1, i11, &pb_emlrtBCI, sp);
    }

    ygrad = 2.0 * (pix->data[((i12 + pix->size[0] * (i13 - 1)) + pix->size[0] *
      pix->size[1] * (i14 - 1)) - 1] - pix->data[((i15 + pix->size[0] * (i16 - 1))
      + pix->size[0] * pix->size[1] * (i17 - 1)) - 1]);
  } else {
    i11 = pix->size[0];
    i12 = r - 1;
    if (!((i12 >= 1) && (i12 <= i11))) {
      emlrtDynamicBoundsCheckR2012b(i12, 1, i11, &eb_emlrtBCI, sp);
    }

    i11 = pix->size[1];
    i13 = c;
    if (!((i13 >= 1) && (i13 <= i11))) {
      emlrtDynamicBoundsCheckR2012b(i13, 1, i11, &fb_emlrtBCI, sp);
    }

    i11 = pix->size[2];
    i14 = s;
    if (!((i14 >= 1) && (i14 <= i11))) {
      emlrtDynamicBoundsCheckR2012b(i14, 1, i11, &gb_emlrtBCI, sp);
    }

    i11 = pix->size[0];
    i15 = r + 1;
    if (i15 > 32767) {
      i15 = 32767;
    }

    if (!((i15 >= 1) && (i15 <= i11))) {
      emlrtDynamicBoundsCheckR2012b(i15, 1, i11, &hb_emlrtBCI, sp);
    }

    i11 = pix->size[1];
    i16 = c;
    if (!((i16 >= 1) && (i16 <= i11))) {
      emlrtDynamicBoundsCheckR2012b(i16, 1, i11, &ib_emlrtBCI, sp);
    }

    i11 = pix->size[2];
    i17 = s;
    if (!((i17 >= 1) && (i17 <= i11))) {
      emlrtDynamicBoundsCheckR2012b(i17, 1, i11, &jb_emlrtBCI, sp);
    }

    ygrad = pix->data[((i12 + pix->size[0] * (i13 - 1)) + pix->size[0] *
                       pix->size[1] * (i14 - 1)) - 1] - pix->data[((i15 +
      pix->size[0] * (i16 - 1)) + pix->size[0] * pix->size[1] * (i17 - 1)) - 1];
  }

  if (s == 1) {
    i11 = pix->size[2];
    if (!(2 <= i11)) {
      emlrtDynamicBoundsCheckR2012b(2, 1, i11, &l_emlrtBCI, sp);
    }

    i11 = pix->size[2];
    if (!(1 <= i11)) {
      emlrtDynamicBoundsCheckR2012b(1, 1, i11, &m_emlrtBCI, sp);
    }

    i11 = pix->size[0];
    i12 = r;
    if (!((i12 >= 1) && (i12 <= i11))) {
      emlrtDynamicBoundsCheckR2012b(i12, 1, i11, &hc_emlrtBCI, sp);
    }

    i11 = pix->size[1];
    i13 = c;
    if (!((i13 >= 1) && (i13 <= i11))) {
      emlrtDynamicBoundsCheckR2012b(i13, 1, i11, &ic_emlrtBCI, sp);
    }

    i11 = pix->size[0];
    i14 = r;
    if (!((i14 >= 1) && (i14 <= i11))) {
      emlrtDynamicBoundsCheckR2012b(i14, 1, i11, &jc_emlrtBCI, sp);
    }

    i11 = pix->size[1];
    i15 = c;
    if (!((i15 >= 1) && (i15 <= i11))) {
      emlrtDynamicBoundsCheckR2012b(i15, 1, i11, &kc_emlrtBCI, sp);
    }

    zgrad = 2.0 * (pix->data[((i12 + pix->size[0] * (i13 - 1)) + pix->size[0] *
      pix->size[1]) - 1] - pix->data[(i14 + pix->size[0] * (i15 - 1)) - 1]);
  } else if (s == pix->size[2]) {
    i11 = pix->size[0];
    i12 = r;
    if (!((i12 >= 1) && (i12 <= i11))) {
      emlrtDynamicBoundsCheckR2012b(i12, 1, i11, &bc_emlrtBCI, sp);
    }

    i11 = pix->size[1];
    i13 = c;
    if (!((i13 >= 1) && (i13 <= i11))) {
      emlrtDynamicBoundsCheckR2012b(i13, 1, i11, &cc_emlrtBCI, sp);
    }

    i11 = pix->size[2];
    i14 = s;
    if (!((i14 >= 1) && (i14 <= i11))) {
      emlrtDynamicBoundsCheckR2012b(i14, 1, i11, &dc_emlrtBCI, sp);
    }

    i11 = pix->size[0];
    i15 = r;
    if (!((i15 >= 1) && (i15 <= i11))) {
      emlrtDynamicBoundsCheckR2012b(i15, 1, i11, &ec_emlrtBCI, sp);
    }

    i11 = pix->size[1];
    i16 = c;
    if (!((i16 >= 1) && (i16 <= i11))) {
      emlrtDynamicBoundsCheckR2012b(i16, 1, i11, &fc_emlrtBCI, sp);
    }

    i11 = pix->size[2];
    i17 = s - 1;
    if (!((i17 >= 1) && (i17 <= i11))) {
      emlrtDynamicBoundsCheckR2012b(i17, 1, i11, &gc_emlrtBCI, sp);
    }

    zgrad = 2.0 * (pix->data[((i12 + pix->size[0] * (i13 - 1)) + pix->size[0] *
      pix->size[1] * (i14 - 1)) - 1] - pix->data[((i15 + pix->size[0] * (i16 - 1))
      + pix->size[0] * pix->size[1] * (i17 - 1)) - 1]);
  } else {
    i11 = pix->size[0];
    i12 = r;
    if (!((i12 >= 1) && (i12 <= i11))) {
      emlrtDynamicBoundsCheckR2012b(i12, 1, i11, &ub_emlrtBCI, sp);
    }

    i11 = pix->size[1];
    i13 = c;
    if (!((i13 >= 1) && (i13 <= i11))) {
      emlrtDynamicBoundsCheckR2012b(i13, 1, i11, &vb_emlrtBCI, sp);
    }

    i11 = pix->size[2];
    i14 = s + 1;
    if (i14 > 32767) {
      i14 = 32767;
    }

    if (!((i14 >= 1) && (i14 <= i11))) {
      emlrtDynamicBoundsCheckR2012b(i14, 1, i11, &wb_emlrtBCI, sp);
    }

    i11 = pix->size[0];
    i15 = r;
    if (!((i15 >= 1) && (i15 <= i11))) {
      emlrtDynamicBoundsCheckR2012b(i15, 1, i11, &xb_emlrtBCI, sp);
    }

    i11 = pix->size[1];
    i16 = c;
    if (!((i16 >= 1) && (i16 <= i11))) {
      emlrtDynamicBoundsCheckR2012b(i16, 1, i11, &yb_emlrtBCI, sp);
    }

    i11 = pix->size[2];
    i17 = s - 1;
    if (!((i17 >= 1) && (i17 <= i11))) {
      emlrtDynamicBoundsCheckR2012b(i17, 1, i11, &ac_emlrtBCI, sp);
    }

    zgrad = pix->data[((i12 + pix->size[0] * (i13 - 1)) + pix->size[0] *
                       pix->size[1] * (i14 - 1)) - 1] - pix->data[((i15 +
      pix->size[0] * (i16 - 1)) + pix->size[0] * pix->size[1] * (i17 - 1)) - 1];
  }

  st.site = &cc_emlrtRSI;
  x = (xgrad * xgrad + ygrad * ygrad) + zgrad * zgrad;
  if (x < 0.0) {
    b_st.site = &lb_emlrtRSI;
    error(&b_st);
  }

  *mag = muDoubleScalarSqrt(x);
  if (*mag != 0.0) {
    b_xgrad[0] = xgrad;
    b_xgrad[1] = ygrad;
    b_xgrad[2] = zgrad;
    for (i11 = 0; i11 < 3; i11++) {
      vect[i11] = b_xgrad[i11] / *mag;
    }
  } else {
    for (i11 = 0; i11 < 3; i11++) {
      vect[i11] = iv7[i11];
    }
  }
}

/* End of code generation (GetGradOri_vector.c) */
