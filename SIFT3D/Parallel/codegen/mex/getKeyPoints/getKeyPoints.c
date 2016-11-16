/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * getKeyPoints.c
 *
 * Code generation for function 'getKeyPoints'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "getKeyPoints.h"
#include "getKeyPoints_emxutil.h"
#include "getKeyPoints_data.h"

/* Variable Definitions */
static emlrtRTEInfo emlrtRTEI = { 1, 22, "getKeyPoints",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\getKeyPoints.m" };

static emlrtBCInfo emlrtBCI = { -1, -1, 11, 59, "I", "getKeyPoints",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\getKeyPoints.m", 0 };

static emlrtBCInfo b_emlrtBCI = { -1, -1, 12, 59, "I", "getKeyPoints",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\getKeyPoints.m", 0 };

static emlrtBCInfo c_emlrtBCI = { -1, -1, 13, 60, "I", "getKeyPoints",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\getKeyPoints.m", 0 };

static emlrtBCInfo d_emlrtBCI = { -1, -1, 13, 64, "I", "getKeyPoints",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\getKeyPoints.m", 0 };

static emlrtBCInfo e_emlrtBCI = { -1, -1, 14, 60, "I", "getKeyPoints",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\getKeyPoints.m", 0 };

static emlrtBCInfo f_emlrtBCI = { -1, -1, 14, 64, "I", "getKeyPoints",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\getKeyPoints.m", 0 };

static emlrtBCInfo g_emlrtBCI = { -1, -1, 15, 45, "I", "getKeyPoints",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\getKeyPoints.m", 0 };

static emlrtBCInfo h_emlrtBCI = { -1, -1, 15, 57, "I", "getKeyPoints",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\getKeyPoints.m", 0 };

static emlrtBCInfo i_emlrtBCI = { -1, -1, 15, 59, "I", "getKeyPoints",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\getKeyPoints.m", 0 };

static emlrtBCInfo j_emlrtBCI = { -1, -1, 15, 64, "I", "getKeyPoints",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\getKeyPoints.m", 0 };

static emlrtBCInfo k_emlrtBCI = { -1, -1, 15, 76, "I", "getKeyPoints",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\getKeyPoints.m", 0 };

static emlrtBCInfo l_emlrtBCI = { -1, -1, 15, 78, "I", "getKeyPoints",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\getKeyPoints.m", 0 };

static emlrtBCInfo m_emlrtBCI = { -1, -1, 9, 22, "I", "getKeyPoints",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\getKeyPoints.m", 0 };

static emlrtBCInfo n_emlrtBCI = { -1, -1, 9, 24, "I", "getKeyPoints",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\getKeyPoints.m", 0 };

static emlrtBCInfo o_emlrtBCI = { -1, -1, 9, 26, "I", "getKeyPoints",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\getKeyPoints.m", 0 };

static emlrtBCInfo p_emlrtBCI = { -1, -1, 9, 28, "I", "getKeyPoints",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\getKeyPoints.m", 0 };

static emlrtBCInfo q_emlrtBCI = { -1, -1, 11, 35, "I", "getKeyPoints",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\getKeyPoints.m", 0 };

static emlrtBCInfo r_emlrtBCI = { -1, -1, 11, 43, "I", "getKeyPoints",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\getKeyPoints.m", 0 };

static emlrtBCInfo s_emlrtBCI = { -1, -1, 11, 51, "I", "getKeyPoints",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\getKeyPoints.m", 0 };

static emlrtBCInfo t_emlrtBCI = { -1, -1, 12, 35, "I", "getKeyPoints",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\getKeyPoints.m", 0 };

static emlrtBCInfo u_emlrtBCI = { -1, -1, 12, 43, "I", "getKeyPoints",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\getKeyPoints.m", 0 };

static emlrtBCInfo v_emlrtBCI = { -1, -1, 12, 51, "I", "getKeyPoints",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\getKeyPoints.m", 0 };

static emlrtBCInfo w_emlrtBCI = { -1, -1, 13, 44, "I", "getKeyPoints",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\getKeyPoints.m", 0 };

static emlrtBCInfo x_emlrtBCI = { -1, -1, 13, 52, "I", "getKeyPoints",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\getKeyPoints.m", 0 };

static emlrtBCInfo y_emlrtBCI = { -1, -1, 14, 44, "I", "getKeyPoints",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\getKeyPoints.m", 0 };

static emlrtBCInfo ab_emlrtBCI = { -1, -1, 14, 52, "I", "getKeyPoints",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\getKeyPoints.m", 0 };

static emlrtBCInfo bb_emlrtBCI = { -1, -1, 15, 49, "I", "getKeyPoints",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\getKeyPoints.m", 0 };

static emlrtBCInfo cb_emlrtBCI = { -1, -1, 15, 68, "I", "getKeyPoints",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\getKeyPoints.m", 0 };

static emlrtBCInfo db_emlrtBCI = { -1, -1, 15, 83, "I", "getKeyPoints",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\getKeyPoints.m", 0 };

static emlrtBCInfo eb_emlrtBCI = { -1, -1, 15, 85, "I", "getKeyPoints",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\getKeyPoints.m", 0 };

static emlrtBCInfo fb_emlrtBCI = { -1, -1, 15, 89, "I", "getKeyPoints",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\getKeyPoints.m", 0 };

static emlrtBCInfo gb_emlrtBCI = { -1, -1, 15, 91, "I", "getKeyPoints",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\getKeyPoints.m", 0 };

static emlrtBCInfo hb_emlrtBCI = { -1, -1, 15, 96, "I", "getKeyPoints",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\getKeyPoints.m", 0 };

static emlrtBCInfo ib_emlrtBCI = { -1, -1, 15, 98, "I", "getKeyPoints",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\getKeyPoints.m", 0 };

static emlrtBCInfo jb_emlrtBCI = { -1, -1, 15, 102, "I", "getKeyPoints",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\getKeyPoints.m", 0 };

static emlrtBCInfo kb_emlrtBCI = { -1, -1, 15, 104, "I", "getKeyPoints",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\getKeyPoints.m", 0 };

static emlrtBCInfo lb_emlrtBCI = { -1, -1, 28, 31, "I", "getKeyPoints",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\getKeyPoints.m", 0 };

static emlrtBCInfo mb_emlrtBCI = { -1, -1, 28, 33, "I", "getKeyPoints",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\getKeyPoints.m", 0 };

static emlrtBCInfo nb_emlrtBCI = { -1, -1, 28, 35, "I", "getKeyPoints",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\getKeyPoints.m", 0 };

static emlrtBCInfo ob_emlrtBCI = { -1, -1, 28, 37, "I", "getKeyPoints",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\getKeyPoints.m", 0 };

static emlrtBCInfo pb_emlrtBCI = { -1, -1, 36, 35, "I", "getKeyPoints",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\getKeyPoints.m", 0 };

static emlrtBCInfo qb_emlrtBCI = { -1, -1, 36, 37, "I", "getKeyPoints",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\getKeyPoints.m", 0 };

static emlrtBCInfo rb_emlrtBCI = { -1, -1, 36, 39, "I", "getKeyPoints",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\getKeyPoints.m", 0 };

static emlrtBCInfo sb_emlrtBCI = { -1, -1, 36, 41, "I", "getKeyPoints",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\getKeyPoints.m", 0 };

/* Function Declarations */
static int32_T div_nzp_s32_floor(int32_T numerator, int32_T denominator);

/* Function Definitions */
static int32_T div_nzp_s32_floor(int32_T numerator, int32_T denominator)
{
  int32_T quotient;
  uint32_T absNumerator;
  uint32_T absDenominator;
  boolean_T quotientNeedsNegation;
  uint32_T tempAbsQuotient;
  if (numerator >= 0) {
    absNumerator = (uint32_T)numerator;
  } else {
    absNumerator = (uint32_T)-numerator;
  }

  if (denominator >= 0) {
    absDenominator = (uint32_T)denominator;
  } else {
    absDenominator = (uint32_T)-denominator;
  }

  quotientNeedsNegation = ((numerator < 0) != (denominator < 0));
  tempAbsQuotient = absNumerator / absDenominator;
  if (quotientNeedsNegation) {
    absNumerator %= absDenominator;
    if (absNumerator > 0U) {
      tempAbsQuotient++;
    }
  }

  if (quotientNeedsNegation) {
    quotient = -(int32_T)tempAbsQuotient;
  } else {
    quotient = (int32_T)tempAbsQuotient;
  }

  return quotient;
}

void getKeyPoints(const emlrtStack *sp, const emxArray_real_T *I, real_T o,
                  real_T thresh, emxArray_real_T *keyPoints)
{
  int32_T i0;
  int32_T s;
  emxArray_real_T *b_keyPoints;
  int32_T h;
  int32_T w;
  int32_T f;
  int32_T i1;
  int32_T i2;
  int32_T k;
  int32_T b_I;
  int32_T i3;
  real_T currScaleCurrFrame[8];
  real_T pSet[27];
  real_T nSet[27];
  real_T cnfSet[9];
  real_T cpfSet[9];
  real_T ccfSet[8];
  real_T tempSet[80];
  real_T c_I;
  boolean_T check[80];
  int32_T type;
  emlrtHeapReferenceStackEnterFcnR2012b(sp);
  i0 = keyPoints->size[0] * keyPoints->size[1];
  keyPoints->size[0] = 0;
  keyPoints->size[1] = 6;
  emxEnsureCapacity(sp, (emxArray__common *)keyPoints, i0, (int32_T)sizeof
                    (real_T), &emlrtRTEI);
  s = 3;
  emxInit_real_T(sp, &b_keyPoints, 2, &emlrtRTEI, true);
  while (s - 3 <= I->size[3] - 4) {
    h = 0;
    while (h <= I->size[0] - 5) {
      w = 0;
      while (w <= I->size[1] - 5) {
        f = 3;
        while (f - 3 <= I->size[2] - 5) {
          i0 = I->size[0];
          i1 = 3 + h;
          if (!((i1 >= 1) && (i1 <= i0))) {
            emlrtDynamicBoundsCheckR2012b(i1, 1, i0, &m_emlrtBCI, sp);
          }

          i0 = I->size[1];
          i2 = 3 + w;
          if (!((i2 >= 1) && (i2 <= i0))) {
            emlrtDynamicBoundsCheckR2012b(i2, 1, i0, &n_emlrtBCI, sp);
          }

          i0 = I->size[2];
          if (!((f >= 1) && (f <= i0))) {
            emlrtDynamicBoundsCheckR2012b(f, 1, i0, &o_emlrtBCI, sp);
          }

          i0 = I->size[3];
          if (!((s >= 1) && (s <= i0))) {
            emlrtDynamicBoundsCheckR2012b(s, 1, i0, &p_emlrtBCI, sp);
          }

          if (I->data[(((i1 + I->size[0] * (i2 - 1)) + I->size[0] * I->size[1] *
                        (f - 1)) + I->size[0] * I->size[1] * I->size[2] * (s - 1))
              - 1] > thresh) {
            k = I->size[0];
            for (i0 = 0; i0 < 3; i0++) {
              i1 = (int32_T)((3.0 + (real_T)h) + (-1.0 + (real_T)i0));
              if (!((i1 >= 1) && (i1 <= k))) {
                emlrtDynamicBoundsCheckR2012b(i1, 1, k, &q_emlrtBCI, sp);
              }
            }

            k = I->size[1];
            for (i0 = 0; i0 < 3; i0++) {
              i1 = (int32_T)((3.0 + (real_T)w) + (-1.0 + (real_T)i0));
              if (!((i1 >= 1) && (i1 <= k))) {
                emlrtDynamicBoundsCheckR2012b(i1, 1, k, &r_emlrtBCI, sp);
              }
            }

            k = I->size[2];
            for (i0 = 0; i0 < 3; i0++) {
              i1 = (int32_T)((3.0 + (real_T)(f - 3)) + (-1.0 + (real_T)i0));
              if (!((i1 >= 1) && (i1 <= k))) {
                emlrtDynamicBoundsCheckR2012b(i1, 1, k, &s_emlrtBCI, sp);
              }
            }

            i0 = I->size[3];
            i1 = (int32_T)((3.0 + (real_T)(s - 3)) - 1.0);
            if (!((i1 >= 1) && (i1 <= i0))) {
              emlrtDynamicBoundsCheckR2012b(i1, 1, i0, &emlrtBCI, sp);
            }

            k = I->size[0];
            for (i0 = 0; i0 < 3; i0++) {
              i1 = (int32_T)((3.0 + (real_T)h) + (-1.0 + (real_T)i0));
              if (!((i1 >= 1) && (i1 <= k))) {
                emlrtDynamicBoundsCheckR2012b(i1, 1, k, &t_emlrtBCI, sp);
              }
            }

            k = I->size[1];
            for (i0 = 0; i0 < 3; i0++) {
              i1 = (int32_T)((3.0 + (real_T)w) + (-1.0 + (real_T)i0));
              if (!((i1 >= 1) && (i1 <= k))) {
                emlrtDynamicBoundsCheckR2012b(i1, 1, k, &u_emlrtBCI, sp);
              }
            }

            k = I->size[2];
            for (i0 = 0; i0 < 3; i0++) {
              i1 = (int32_T)((3.0 + (real_T)(f - 3)) + (-1.0 + (real_T)i0));
              if (!((i1 >= 1) && (i1 <= k))) {
                emlrtDynamicBoundsCheckR2012b(i1, 1, k, &v_emlrtBCI, sp);
              }
            }

            i0 = I->size[3];
            i1 = (int32_T)((3.0 + (real_T)(s - 3)) + 1.0);
            if (!((i1 >= 1) && (i1 <= i0))) {
              emlrtDynamicBoundsCheckR2012b(i1, 1, i0, &b_emlrtBCI, sp);
            }

            k = I->size[0];
            for (i0 = 0; i0 < 3; i0++) {
              i1 = (int32_T)((3.0 + (real_T)h) + (-1.0 + (real_T)i0));
              if (!((i1 >= 1) && (i1 <= k))) {
                emlrtDynamicBoundsCheckR2012b(i1, 1, k, &w_emlrtBCI, sp);
              }
            }

            k = I->size[1];
            for (i0 = 0; i0 < 3; i0++) {
              i1 = (int32_T)((3.0 + (real_T)w) + (-1.0 + (real_T)i0));
              if (!((i1 >= 1) && (i1 <= k))) {
                emlrtDynamicBoundsCheckR2012b(i1, 1, k, &x_emlrtBCI, sp);
              }
            }

            i0 = I->size[2];
            i1 = (int32_T)((3.0 + (real_T)(f - 3)) + 1.0);
            if (!((i1 >= 1) && (i1 <= i0))) {
              emlrtDynamicBoundsCheckR2012b(i1, 1, i0, &c_emlrtBCI, sp);
            }

            i0 = I->size[3];
            i1 = (int32_T)(3.0 + (real_T)(s - 3));
            if (!((i1 >= 1) && (i1 <= i0))) {
              emlrtDynamicBoundsCheckR2012b(i1, 1, i0, &d_emlrtBCI, sp);
            }

            k = I->size[0];
            for (i0 = 0; i0 < 3; i0++) {
              i1 = (int32_T)((3.0 + (real_T)h) + (-1.0 + (real_T)i0));
              if (!((i1 >= 1) && (i1 <= k))) {
                emlrtDynamicBoundsCheckR2012b(i1, 1, k, &y_emlrtBCI, sp);
              }
            }

            k = I->size[1];
            for (i0 = 0; i0 < 3; i0++) {
              i1 = (int32_T)((3.0 + (real_T)w) + (-1.0 + (real_T)i0));
              if (!((i1 >= 1) && (i1 <= k))) {
                emlrtDynamicBoundsCheckR2012b(i1, 1, k, &ab_emlrtBCI, sp);
              }
            }

            i0 = I->size[2];
            i1 = (int32_T)((3.0 + (real_T)(f - 3)) - 1.0);
            if (!((i1 >= 1) && (i1 <= i0))) {
              emlrtDynamicBoundsCheckR2012b(i1, 1, i0, &e_emlrtBCI, sp);
            }

            i0 = I->size[3];
            i1 = (int32_T)(3.0 + (real_T)(s - 3));
            if (!((i1 >= 1) && (i1 <= i0))) {
              emlrtDynamicBoundsCheckR2012b(i1, 1, i0, &f_emlrtBCI, sp);
            }

            k = I->size[1];
            i0 = I->size[3];
            if (!((s >= 1) && (s <= i0))) {
              emlrtDynamicBoundsCheckR2012b(s, 1, i0, &i_emlrtBCI, sp);
            }

            i0 = I->size[2];
            if (!((f >= 1) && (f <= i0))) {
              emlrtDynamicBoundsCheckR2012b(f, 1, i0, &h_emlrtBCI, sp);
            }

            i0 = I->size[0];
            i1 = 2 + h;
            if (!((i1 >= 1) && (i1 <= i0))) {
              emlrtDynamicBoundsCheckR2012b(i1, 1, i0, &g_emlrtBCI, sp);
            }

            b_I = I->size[1];
            i0 = I->size[3];
            if (!((s >= 1) && (s <= i0))) {
              emlrtDynamicBoundsCheckR2012b(s, 1, i0, &l_emlrtBCI, sp);
            }

            i0 = I->size[2];
            if (!((f >= 1) && (f <= i0))) {
              emlrtDynamicBoundsCheckR2012b(f, 1, i0, &k_emlrtBCI, sp);
            }

            i0 = I->size[0];
            i2 = 4 + h;
            if (!((i2 >= 1) && (i2 <= i0))) {
              emlrtDynamicBoundsCheckR2012b(i2, 1, i0, &j_emlrtBCI, sp);
            }

            for (i0 = 0; i0 < 3; i0++) {
              i3 = (i0 + w) + 2;
              if (!((i3 >= 1) && (i3 <= k))) {
                emlrtDynamicBoundsCheckR2012b(i3, 1, k, &bb_emlrtBCI, sp);
              }

              currScaleCurrFrame[i0] = I->data[(((i1 + I->size[0] * (i3 - 1)) +
                I->size[0] * I->size[1] * (f - 1)) + I->size[0] * I->size[1] *
                I->size[2] * (s - 1)) - 1];
            }

            for (i0 = 0; i0 < 3; i0++) {
              i1 = (i0 + w) + 2;
              if (!((i1 >= 1) && (i1 <= b_I))) {
                emlrtDynamicBoundsCheckR2012b(i1, 1, b_I, &cb_emlrtBCI, sp);
              }

              currScaleCurrFrame[i0 + 3] = I->data[(((i2 + I->size[0] * (i1 - 1))
                + I->size[0] * I->size[1] * (f - 1)) + I->size[0] * I->size[1] *
                I->size[2] * (s - 1)) - 1];
            }

            i0 = I->size[0];
            i1 = 3 + h;
            if (!((i1 >= 1) && (i1 <= i0))) {
              emlrtDynamicBoundsCheckR2012b(i1, 1, i0, &db_emlrtBCI, sp);
            }

            i0 = I->size[1];
            i2 = 2 + w;
            if (!((i2 >= 1) && (i2 <= i0))) {
              emlrtDynamicBoundsCheckR2012b(i2, 1, i0, &eb_emlrtBCI, sp);
            }

            i0 = I->size[2];
            if (!((f >= 1) && (f <= i0))) {
              emlrtDynamicBoundsCheckR2012b(f, 1, i0, &fb_emlrtBCI, sp);
            }

            i0 = I->size[3];
            if (!((s >= 1) && (s <= i0))) {
              emlrtDynamicBoundsCheckR2012b(s, 1, i0, &gb_emlrtBCI, sp);
            }

            currScaleCurrFrame[6] = I->data[(((i1 + I->size[0] * (i2 - 1)) +
              I->size[0] * I->size[1] * (f - 1)) + I->size[0] * I->size[1] *
              I->size[2] * (s - 1)) - 1];
            i0 = I->size[0];
            i1 = 3 + h;
            if (!((i1 >= 1) && (i1 <= i0))) {
              emlrtDynamicBoundsCheckR2012b(i1, 1, i0, &hb_emlrtBCI, sp);
            }

            i0 = I->size[1];
            i2 = 4 + w;
            if (!((i2 >= 1) && (i2 <= i0))) {
              emlrtDynamicBoundsCheckR2012b(i2, 1, i0, &ib_emlrtBCI, sp);
            }

            i0 = I->size[2];
            if (!((f >= 1) && (f <= i0))) {
              emlrtDynamicBoundsCheckR2012b(f, 1, i0, &jb_emlrtBCI, sp);
            }

            i0 = I->size[3];
            if (!((s >= 1) && (s <= i0))) {
              emlrtDynamicBoundsCheckR2012b(s, 1, i0, &kb_emlrtBCI, sp);
            }

            currScaleCurrFrame[7] = I->data[(((i1 + I->size[0] * (i2 - 1)) +
              I->size[0] * I->size[1] * (f - 1)) + I->size[0] * I->size[1] *
              I->size[2] * (s - 1)) - 1];

            /*                     %% RESHAPING NEIGHBORHOOD ARRAYS TO ROW MATRICES */
            for (k = 0; k < 27; k++) {
              pSet[k] = I->data[((((k % 3 + h) + I->size[0] *
                                   ((div_nzp_s32_floor(k, 3) % 3 + w) + 1)) +
                                  I->size[0] * I->size[1] * ((div_nzp_s32_floor
                (k, 9) + f) - 2)) + I->size[0] * I->size[1] * I->size[2] * (s -
                2)) + 1];
            }

            for (k = 0; k < 27; k++) {
              nSet[k] = I->data[((((k % 3 + h) + I->size[0] *
                                   ((div_nzp_s32_floor(k, 3) % 3 + w) + 1)) +
                                  I->size[0] * I->size[1] * ((div_nzp_s32_floor
                (k, 9) + f) - 2)) + I->size[0] * I->size[1] * I->size[2] * s) +
                1];
            }

            for (k = 0; k < 9; k++) {
              cnfSet[k] = I->data[((((k % 3 + h) + I->size[0] *
                ((div_nzp_s32_floor(k, 3) + w) + 1)) + I->size[0] * I->size[1] *
                                    f) + I->size[0] * I->size[1] * I->size[2] *
                                   (s - 1)) + 1];
            }

            for (k = 0; k < 9; k++) {
              cpfSet[k] = I->data[((((k % 3 + h) + I->size[0] *
                ((div_nzp_s32_floor(k, 3) + w) + 1)) + I->size[0] * I->size[1] *
                                    (f - 2)) + I->size[0] * I->size[1] * I->
                                   size[2] * (s - 1)) + 1];
            }

            memcpy(&ccfSet[0], &currScaleCurrFrame[0], sizeof(real_T) << 3);

            /*                     %% CREATING NEIGHBORHOOD ARRAY */
            memcpy(&tempSet[0], &pSet[0], 27U * sizeof(real_T));
            memcpy(&tempSet[27], &nSet[0], 27U * sizeof(real_T));
            memcpy(&tempSet[54], &cnfSet[0], 9U * sizeof(real_T));
            memcpy(&tempSet[63], &cpfSet[0], 9U * sizeof(real_T));
            memcpy(&tempSet[72], &ccfSet[0], sizeof(real_T) << 3);

            /*  tempSet = sort(tempSet); */
            i0 = I->size[0];
            i1 = 3 + h;
            if (!((i1 >= 1) && (i1 <= i0))) {
              emlrtDynamicBoundsCheckR2012b(i1, 1, i0, &lb_emlrtBCI, sp);
            }

            i0 = I->size[1];
            i2 = 3 + w;
            if (!((i2 >= 1) && (i2 <= i0))) {
              emlrtDynamicBoundsCheckR2012b(i2, 1, i0, &mb_emlrtBCI, sp);
            }

            i0 = I->size[2];
            if (!((f >= 1) && (f <= i0))) {
              emlrtDynamicBoundsCheckR2012b(f, 1, i0, &nb_emlrtBCI, sp);
            }

            i0 = I->size[3];
            if (!((s >= 1) && (s <= i0))) {
              emlrtDynamicBoundsCheckR2012b(s, 1, i0, &ob_emlrtBCI, sp);
            }

            c_I = I->data[(((i1 + I->size[0] * (i2 - 1)) + I->size[0] * I->size
                            [1] * (f - 1)) + I->size[0] * I->size[1] * I->size[2]
                           * (s - 1)) - 1];
            for (i0 = 0; i0 < 80; i0++) {
              check[i0] = (c_I > tempSet[i0]);
            }

            type = 0;
            c_I = check[0];
            for (k = 0; k < 79; k++) {
              c_I += (real_T)check[k + 1];
            }

            if (c_I >= 77.6) {
              /*  fprintf('Maxima Detected\n'); */
              type = 1;
            } else {
              i0 = I->size[0];
              i1 = 3 + h;
              if (!((i1 >= 1) && (i1 <= i0))) {
                emlrtDynamicBoundsCheckR2012b(i1, 1, i0, &pb_emlrtBCI, sp);
              }

              i0 = I->size[1];
              i2 = 3 + w;
              if (!((i2 >= 1) && (i2 <= i0))) {
                emlrtDynamicBoundsCheckR2012b(i2, 1, i0, &qb_emlrtBCI, sp);
              }

              i0 = I->size[2];
              if (!((f >= 1) && (f <= i0))) {
                emlrtDynamicBoundsCheckR2012b(f, 1, i0, &rb_emlrtBCI, sp);
              }

              i0 = I->size[3];
              if (!((s >= 1) && (s <= i0))) {
                emlrtDynamicBoundsCheckR2012b(s, 1, i0, &sb_emlrtBCI, sp);
              }

              c_I = I->data[(((i1 + I->size[0] * (i2 - 1)) + I->size[0] *
                              I->size[1] * (f - 1)) + I->size[0] * I->size[1] *
                             I->size[2] * (s - 1)) - 1];
              for (i0 = 0; i0 < 80; i0++) {
                check[i0] = (c_I < tempSet[i0]);
              }

              c_I = check[0];
              for (k = 0; k < 79; k++) {
                c_I += (real_T)check[k + 1];
              }

              if (c_I >= 77.6) {
                type = 2;
              }
            }

            if (type != 0) {
              i0 = b_keyPoints->size[0] * b_keyPoints->size[1];
              b_keyPoints->size[0] = keyPoints->size[0] + 1;
              b_keyPoints->size[1] = 6;
              emxEnsureCapacity(sp, (emxArray__common *)b_keyPoints, i0,
                                (int32_T)sizeof(real_T), &emlrtRTEI);
              for (i0 = 0; i0 < 6; i0++) {
                k = keyPoints->size[0];
                for (i1 = 0; i1 < k; i1++) {
                  b_keyPoints->data[i1 + b_keyPoints->size[0] * i0] =
                    keyPoints->data[i1 + keyPoints->size[0] * i0];
                }
              }

              b_keyPoints->data[keyPoints->size[0]] = o;
              b_keyPoints->data[keyPoints->size[0] + b_keyPoints->size[0]] = 3.0
                + (real_T)(s - 3);
              b_keyPoints->data[keyPoints->size[0] + (b_keyPoints->size[0] << 1)]
                = 3.0 + (real_T)h;
              b_keyPoints->data[keyPoints->size[0] + b_keyPoints->size[0] * 3] =
                3.0 + (real_T)w;
              b_keyPoints->data[keyPoints->size[0] + (b_keyPoints->size[0] << 2)]
                = 3.0 + (real_T)(f - 3);
              b_keyPoints->data[keyPoints->size[0] + b_keyPoints->size[0] * 5] =
                type;
              i0 = keyPoints->size[0] * keyPoints->size[1];
              keyPoints->size[0] = b_keyPoints->size[0];
              keyPoints->size[1] = 6;
              emxEnsureCapacity(sp, (emxArray__common *)keyPoints, i0, (int32_T)
                                sizeof(real_T), &emlrtRTEI);
              for (i0 = 0; i0 < 6; i0++) {
                k = b_keyPoints->size[0];
                for (i1 = 0; i1 < k; i1++) {
                  keyPoints->data[i1 + keyPoints->size[0] * i0] =
                    b_keyPoints->data[i1 + b_keyPoints->size[0] * i0];
                }
              }

              /*  disp([o,s,h,w,f, type]); */
            }
          } else {
            /*  Go to Next Pixel */
          }

          f++;
          if (*emlrtBreakCheckR2012bFlagVar != 0) {
            emlrtBreakCheckR2012b(sp);
          }
        }

        w++;
        if (*emlrtBreakCheckR2012bFlagVar != 0) {
          emlrtBreakCheckR2012b(sp);
        }
      }

      h++;
      if (*emlrtBreakCheckR2012bFlagVar != 0) {
        emlrtBreakCheckR2012b(sp);
      }
    }

    s++;
    if (*emlrtBreakCheckR2012bFlagVar != 0) {
      emlrtBreakCheckR2012b(sp);
    }
  }

  emxFree_real_T(&b_keyPoints);
  emlrtHeapReferenceStackLeaveFcnR2012b(sp);
}

/* End of code generation (getKeyPoints.c) */
