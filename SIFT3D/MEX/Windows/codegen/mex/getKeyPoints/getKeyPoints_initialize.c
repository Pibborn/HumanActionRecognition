/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * getKeyPoints_initialize.c
 *
 * Code generation for function 'getKeyPoints_initialize'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "getKeyPoints.h"
#include "getKeyPoints_initialize.h"
#include "_coder_getKeyPoints_mex.h"
#include "getKeyPoints_data.h"

/* Function Definitions */
void getKeyPoints_initialize(void)
{
  emlrtStack st = { NULL, NULL, NULL };

  mexFunctionCreateRootTLS();
  emlrtBreakCheckR2012bFlagVar = emlrtGetBreakCheckFlagAddressR2012b();
  st.tls = emlrtRootTLSGlobal;
  emlrtClearAllocCountR2012b(&st, false, 0U, 0);
  emlrtEnterRtStackR2012b(&st);
  emlrtFirstTimeR2012b(emlrtRootTLSGlobal);
}

/* End of code generation (getKeyPoints_initialize.c) */
