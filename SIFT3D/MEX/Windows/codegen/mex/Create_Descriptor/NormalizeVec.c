/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * NormalizeVec.c
 *
 * Code generation for function 'NormalizeVec'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "Create_Descriptor.h"
#include "NormalizeVec.h"
#include "error.h"
#include "Create_Descriptor_data.h"

/* Variable Definitions */
static emlrtRSInfo yd_emlrtRSI = { 4, "NormalizeVec",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\NormalizeVec.m" };

/* Function Definitions */
void NormalizeVec(const emlrtStack *sp, real_T vec[640])
{
  ptrdiff_t n_t;
  ptrdiff_t incx_t;
  ptrdiff_t incy_t;
  real_T sqlen;
  real_T fac;
  int32_T i28;
  emlrtStack st;
  emlrtStack b_st;
  st.prev = sp;
  st.tls = sp->tls;
  b_st.prev = &st;
  b_st.tls = st.tls;
  n_t = (ptrdiff_t)640;
  incx_t = (ptrdiff_t)1;
  incy_t = (ptrdiff_t)1;
  sqlen = ddot(&n_t, &vec[0], &incx_t, &vec[0], &incy_t);
  st.site = &yd_emlrtRSI;
  if (sqlen < 0.0) {
    b_st.site = &lb_emlrtRSI;
    error(&b_st);
  }

  fac = 1.0 / muDoubleScalarSqrt(sqlen);
  for (i28 = 0; i28 < 640; i28++) {
    vec[i28] *= fac;
  }
}

/* End of code generation (NormalizeVec.c) */
