/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * power.c
 *
 * Code generation for function 'power'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "Create_Descriptor.h"
#include "power.h"
#include "Create_Descriptor_emxutil.h"
#include "eml_int_forloop_overflow_check.h"
#include "scalexpAlloc.h"
#include "Create_Descriptor_data.h"

/* Variable Definitions */
static emlrtRSInfo ib_emlrtRSI = { 49, "power",
  "C:\\Program Files\\MATLAB\\R2015b\\toolbox\\eml\\lib\\matlab\\ops\\power.m" };

static emlrtRSInfo jb_emlrtRSI = { 58, "power",
  "C:\\Program Files\\MATLAB\\R2015b\\toolbox\\eml\\lib\\matlab\\ops\\power.m" };

static emlrtRSInfo kb_emlrtRSI = { 132, "applyScalarFunction",
  "C:\\Program Files\\MATLAB\\R2015b\\toolbox\\eml\\eml\\+coder\\+internal\\applyScalarFunction.m"
};

/* Function Definitions */
void power(const emlrtStack *sp, const emxArray_real_T *a, emxArray_real_T *y)
{
  uint32_T a_idx_0;
  int32_T k;
  boolean_T overflow;
  emlrtStack st;
  emlrtStack b_st;
  emlrtStack c_st;
  emlrtStack d_st;
  st.prev = sp;
  st.tls = sp->tls;
  st.site = &ib_emlrtRSI;
  b_st.prev = &st;
  b_st.tls = st.tls;
  c_st.prev = &b_st;
  c_st.tls = b_st.tls;
  d_st.prev = &c_st;
  d_st.tls = c_st.tls;
  b_st.site = &jb_emlrtRSI;
  c_st.site = &gb_emlrtRSI;
  a_idx_0 = (uint32_T)a->size[0];
  k = y->size[0];
  y->size[0] = (int32_T)a_idx_0;
  emxEnsureCapacity(&c_st, (emxArray__common *)y, k, (int32_T)sizeof(real_T),
                    &k_emlrtRTEI);
  if (b_dimagree(y, a)) {
  } else {
    emlrtErrorWithMessageIdR2012b(&c_st, &p_emlrtRTEI, "MATLAB:dimagree", 0);
  }

  c_st.site = &kb_emlrtRSI;
  if (1 > a->size[0]) {
    overflow = false;
  } else {
    overflow = (a->size[0] > 2147483646);
  }

  if (overflow) {
    d_st.site = &t_emlrtRSI;
    check_forloop_overflow_error(&d_st);
  }

  for (k = 0; k + 1 <= a->size[0]; k++) {
    y->data[k] = a->data[k] * a->data[k];
  }
}

/* End of code generation (power.c) */
