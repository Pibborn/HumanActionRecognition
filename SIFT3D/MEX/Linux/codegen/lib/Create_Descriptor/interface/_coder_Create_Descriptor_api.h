/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: _coder_Create_Descriptor_api.h
 *
 * MATLAB Coder version            : 3.2
 * C/C++ source code generated on  : 18-Nov-2016 16:32:39
 */

#ifndef _CODER_CREATE_DESCRIPTOR_API_H
#define _CODER_CREATE_DESCRIPTOR_API_H

/* Include Files */
#include "tmwtypes.h"
#include "mex.h"
#include "emlrt.h"
#include <stddef.h>
#include <stdlib.h>
#include "_coder_Create_Descriptor_api.h"

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

#ifndef typedef_struct0_T
#define typedef_struct0_T

typedef struct {
  real_T x;
  real_T y;
  real_T z;
  real_T xyScale;
  real_T tScale;
  real_T ivec[640];
} struct0_T;

#endif                                 /*typedef_struct0_T*/

/* Variable Declarations */
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

/* Function Declarations */
extern void Create_Descriptor(emxArray_real_T *pix, real_T xyScale, real_T
  tScale, real_T x, real_T y, real_T z, struct0_T *keyPoint, real_T *reRun);
extern void Create_Descriptor_api(const mxArray *prhs[6], const mxArray *plhs[2]);
extern void Create_Descriptor_atexit(void);
extern void Create_Descriptor_initialize(void);
extern void Create_Descriptor_terminate(void);
extern void Create_Descriptor_xil_terminate(void);

#endif

/*
 * File trailer for _coder_Create_Descriptor_api.h
 *
 * [EOF]
 */
