/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * atan2.c
 *
 * Code generation for function 'atan2'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "Create_Descriptor.h"
#include "atan2.h"
#include "Create_Descriptor_emxutil.h"
#include "eml_int_forloop_overflow_check.h"
#include "scalexpAlloc.h"
#include "Create_Descriptor_data.h"

/* Variable Definitions */
static emlrtRSInfo fb_emlrtRSI = { 12, "atan2",
  "C:\\Program Files\\MATLAB\\R2015b\\toolbox\\eml\\lib\\matlab\\elfun\\atan2.m"
};

static emlrtRSInfo hb_emlrtRSI = { 179, "applyScalarFunction",
  "C:\\Program Files\\MATLAB\\R2015b\\toolbox\\eml\\eml\\+coder\\+internal\\applyScalarFunction.m"
};

/* Function Definitions */
void b_atan2(const emlrtStack *sp, const emxArray_real_T *y, const
             emxArray_real_T *x, emxArray_real_T *r)
{
  int32_T k;
  int32_T i4;
  boolean_T overflow;
  emlrtStack st;
  emlrtStack b_st;
  emlrtStack c_st;
  st.prev = sp;
  st.tls = sp->tls;
  st.site = &fb_emlrtRSI;
  b_st.prev = &st;
  b_st.tls = st.tls;
  c_st.prev = &b_st;
  c_st.tls = b_st.tls;
  b_st.site = &gb_emlrtRSI;
  if (y->size[0] <= x->size[0]) {
    k = y->size[0];
  } else {
    k = x->size[0];
  }

  i4 = r->size[0];
  r->size[0] = k;
  emxEnsureCapacity(&b_st, (emxArray__common *)r, i4, (int32_T)sizeof(real_T),
                    &k_emlrtRTEI);
  if (dimagree(r, y, x)) {
  } else {
    emlrtErrorWithMessageIdR2012b(&b_st, &p_emlrtRTEI, "MATLAB:dimagree", 0);
  }

  b_st.site = &hb_emlrtRSI;
  if (1 > y->size[0]) {
    overflow = false;
  } else {
    overflow = (y->size[0] > 2147483646);
  }

  if (overflow) {
    c_st.site = &t_emlrtRSI;
    check_forloop_overflow_error(&c_st);
  }

  for (k = 0; k + 1 <= y->size[0]; k++) {
    r->data[k] = muDoubleScalarAtan2(y->data[k], x->data[k]);
  }
}

/* End of code generation (atan2.c) */
