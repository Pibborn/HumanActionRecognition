/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * _coder_Create_Descriptor_api.c
 *
 * Code generation for function '_coder_Create_Descriptor_api'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "Create_Descriptor.h"
#include "_coder_Create_Descriptor_api.h"
#include "Create_Descriptor_emxutil.h"
#include "fprintf.h"
#include "mesh_refine_tri4.h"
#include "Create_Descriptor_mexutil.h"
#include "Create_Descriptor_data.h"

/* Variable Definitions */
static emlrtRTEInfo l_emlrtRTEI = { 1, 1, "_coder_Create_Descriptor_api", "" };

/* Function Declarations */
static void c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *pix, const
  char_T *identifier, emxArray_real_T *y);
static void d_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, emxArray_real_T *y);
static const mxArray *d_emlrt_marshallOut(const struct0_T *u);
static void f_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId, emxArray_real_T *ret);

/* Function Definitions */
static void c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *pix, const
  char_T *identifier, emxArray_real_T *y)
{
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  d_emlrt_marshallIn(sp, emlrtAlias(pix), &thisId, y);
  emlrtDestroyArray(&pix);
}

static void d_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, emxArray_real_T *y)
{
  f_emlrt_marshallIn(sp, emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

static const mxArray *d_emlrt_marshallOut(const struct0_T *u)
{
  const mxArray *y;
  const mxArray *b_y;
  static const int32_T iv8[2] = { 1, 640 };

  const mxArray *m6;
  real_T *pData;
  int32_T i;
  y = NULL;
  emlrtAssign(&y, emlrtCreateStructMatrix(1, 1, 0, NULL));
  emlrtAddField(y, emlrt_marshallOut(u->x), "x", 0);
  emlrtAddField(y, emlrt_marshallOut(u->y), "y", 0);
  emlrtAddField(y, emlrt_marshallOut(u->z), "z", 0);
  emlrtAddField(y, emlrt_marshallOut(u->xyScale), "xyScale", 0);
  emlrtAddField(y, emlrt_marshallOut(u->tScale), "tScale", 0);
  b_y = NULL;
  m6 = emlrtCreateNumericArray(2, iv8, mxDOUBLE_CLASS, mxREAL);
  pData = (real_T *)mxGetPr(m6);
  for (i = 0; i < 640; i++) {
    pData[i] = u->ivec[i];
  }

  emlrtAssign(&b_y, m6);
  emlrtAddField(y, b_y, "ivec", 0);
  return y;
}

static void f_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId, emxArray_real_T *ret)
{
  int32_T iv9[3];
  boolean_T bv0[3] = { true, true, true };

  static const int32_T dims[3] = { -1, -1, -1 };

  emlrtCheckVsBuiltInR2012b(sp, msgId, src, "double", false, 3U, dims, &bv0[0],
    iv9);
  ret->size[0] = iv9[0];
  ret->size[1] = iv9[1];
  ret->size[2] = iv9[2];
  ret->allocatedSize = ret->size[0] * ret->size[1] * ret->size[2];
  ret->data = (real_T *)mxGetData(src);
  ret->canFreeData = false;
  emlrtDestroyArray(&src);
}

void Create_Descriptor_api(const mxArray * const prhs[6], const mxArray *plhs[2])
{
  emxArray_real_T *pix;
  real_T xyScale;
  real_T tScale;
  real_T x;
  real_T y;
  real_T z;
  real_T reRun;
  struct0_T keyPoint;
  emlrtStack st = { NULL, NULL, NULL };

  st.tls = emlrtRootTLSGlobal;
  emlrtHeapReferenceStackEnterFcnR2012b(&st);
  emxInit_real_T2(&st, &pix, 3, &l_emlrtRTEI, true);

  /* Marshall function inputs */
  c_emlrt_marshallIn(&st, emlrtAlias(prhs[0]), "pix", pix);
  xyScale = emlrt_marshallIn(&st, emlrtAliasP(prhs[1]), "xyScale");
  tScale = emlrt_marshallIn(&st, emlrtAliasP(prhs[2]), "tScale");
  x = emlrt_marshallIn(&st, emlrtAliasP(prhs[3]), "x");
  y = emlrt_marshallIn(&st, emlrtAliasP(prhs[4]), "y");
  z = emlrt_marshallIn(&st, emlrtAliasP(prhs[5]), "z");

  /* Invoke the target function */
  Create_Descriptor(&st, pix, xyScale, tScale, x, y, z, &keyPoint, &reRun);

  /* Marshall function outputs */
  plhs[0] = d_emlrt_marshallOut(&keyPoint);
  plhs[1] = emlrt_marshallOut(reRun);
  pix->canFreeData = false;
  emxFree_real_T(&pix);
  emlrtHeapReferenceStackLeaveFcnR2012b(&st);
}

/* End of code generation (_coder_Create_Descriptor_api.c) */
