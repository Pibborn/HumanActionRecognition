/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Create_Descriptor.h
 *
 * Code generation for function 'Create_Descriptor'
 *
 */

#ifndef __CREATE_DESCRIPTOR_H__
#define __CREATE_DESCRIPTOR_H__

/* Include files */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mwmathutil.h"
#include "tmwtypes.h"
#include "mex.h"
#include "emlrt.h"
#include "blas.h"
#include "rtwtypes.h"
#include "Create_Descriptor_types.h"

/* Function Declarations */
extern void Create_Descriptor(const emlrtStack *sp, const emxArray_real_T *pix,
  real_T xyScale, real_T tScale, real_T x, real_T y, real_T z, struct0_T
  *keyPoint, real_T *reRun);

#endif

/* End of code generation (Create_Descriptor.h) */
