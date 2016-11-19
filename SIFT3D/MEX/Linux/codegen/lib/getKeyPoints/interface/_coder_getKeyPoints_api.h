/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: _coder_getKeyPoints_api.h
 *
 * MATLAB Coder version            : 3.2
 * C/C++ source code generated on  : 18-Nov-2016 16:35:03
 */

#ifndef _CODER_GETKEYPOINTS_API_H
#define _CODER_GETKEYPOINTS_API_H

/* Include Files */
#include "tmwtypes.h"
#include "mex.h"
#include "emlrt.h"
#include <stddef.h>
#include <stdlib.h>
#include "_coder_getKeyPoints_api.h"

/* Type Definitions */
#ifndef struct_emxArray_real_T
#define struct_emxArray_real_T

struct emxArray_real_T
{
  real_T *data;
  int32_T *size;
  int32_T allocatedSize;
  int32_T numDimensions;
  boolean_T canFreeData;
};

#endif                                 /*struct_emxArray_real_T*/

#ifndef typedef_emxArray_real_T
#define typedef_emxArray_real_T

typedef struct emxArray_real_T emxArray_real_T;

#endif                                 /*typedef_emxArray_real_T*/

/* Variable Declarations */
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

/* Function Declarations */
extern void getKeyPoints(emxArray_real_T *I, real_T o, real_T thresh,
  emxArray_real_T *keyPoints);
extern void getKeyPoints_api(const mxArray *prhs[3], const mxArray *plhs[1]);
extern void getKeyPoints_atexit(void);
extern void getKeyPoints_initialize(void);
extern void getKeyPoints_terminate(void);
extern void getKeyPoints_xil_terminate(void);

#endif

/*
 * File trailer for _coder_getKeyPoints_api.h
 *
 * [EOF]
 */
