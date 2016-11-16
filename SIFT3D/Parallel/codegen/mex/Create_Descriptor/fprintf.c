/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * fprintf.c
 *
 * Code generation for function 'fprintf'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "Create_Descriptor.h"
#include "fprintf.h"
#include "mesh_refine_tri4.h"
#include "Create_Descriptor_mexutil.h"

/* Variable Definitions */
static emlrtMCInfo c_emlrtMCI = { 71, 18, "fprintf",
  "C:\\Program Files\\MATLAB\\R2015b\\toolbox\\eml\\lib\\matlab\\iofun\\fprintf.m"
};

static emlrtRSInfo fe_emlrtRSI = { 71, "fprintf",
  "C:\\Program Files\\MATLAB\\R2015b\\toolbox\\eml\\lib\\matlab\\iofun\\fprintf.m"
};

/* Function Declarations */
static const mxArray *feval(const emlrtStack *sp, const mxArray *b, const
  mxArray *c, const mxArray *d, emlrtMCInfo *location);

/* Function Definitions */
static const mxArray *feval(const emlrtStack *sp, const mxArray *b, const
  mxArray *c, const mxArray *d, emlrtMCInfo *location)
{
  const mxArray *pArrays[3];
  const mxArray *m7;
  pArrays[0] = b;
  pArrays[1] = c;
  pArrays[2] = d;
  return emlrtCallMATLABR2012b(sp, 1, &m7, 3, pArrays, "feval", true, location);
}

real_T b_fprintf(const emlrtStack *sp)
{
  int32_T i3;
  static const char_T cv3[7] = { 'f', 'p', 'r', 'i', 'n', 't', 'f' };

  char_T u[7];
  const mxArray *y;
  static const int32_T iv5[2] = { 1, 7 };

  const mxArray *m2;
  static const char_T formatSpec[19] = { 'r', 'e', 'p', 'l', 'i', 'c', 'a', 't',
    'e', 'd', ' ', 'v', 'e', 'r', 't', 'i', 'c', 'e', 's' };

  char_T b_u[19];
  const mxArray *b_y;
  static const int32_T iv6[2] = { 1, 19 };

  emlrtStack st;
  st.prev = sp;
  st.tls = sp->tls;
  for (i3 = 0; i3 < 7; i3++) {
    u[i3] = cv3[i3];
  }

  y = NULL;
  m2 = emlrtCreateCharArray(2, iv5);
  emlrtInitCharArrayR2013a(sp, 7, m2, &u[0]);
  emlrtAssign(&y, m2);
  for (i3 = 0; i3 < 19; i3++) {
    b_u[i3] = formatSpec[i3];
  }

  b_y = NULL;
  m2 = emlrtCreateCharArray(2, iv6);
  emlrtInitCharArrayR2013a(sp, 19, m2, &b_u[0]);
  emlrtAssign(&b_y, m2);
  st.site = &fe_emlrtRSI;
  return emlrt_marshallIn(&st, feval(&st, y, emlrt_marshallOut(1.0), b_y,
    &c_emlrtMCI), "feval");
}

/* End of code generation (fprintf.c) */
