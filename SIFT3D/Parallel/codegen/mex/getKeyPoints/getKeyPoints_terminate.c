/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * getKeyPoints_terminate.c
 *
 * Code generation for function 'getKeyPoints_terminate'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "getKeyPoints.h"
#include "getKeyPoints_terminate.h"
#include "_coder_getKeyPoints_mex.h"
#include "getKeyPoints_data.h"

/* Function Definitions */
void getKeyPoints_atexit(void)
{
  emlrtStack st = { NULL, NULL, NULL };

  mexFunctionCreateRootTLS();
  st.tls = emlrtRootTLSGlobal;
  emlrtEnterRtStackR2012b(&st);
  emlrtLeaveRtStackR2012b(&st);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
}

void getKeyPoints_terminate(void)
{
  emlrtStack st = { NULL, NULL, NULL };

  st.tls = emlrtRootTLSGlobal;
  emlrtLeaveRtStackR2012b(&st);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
}

/* End of code generation (getKeyPoints_terminate.c) */
