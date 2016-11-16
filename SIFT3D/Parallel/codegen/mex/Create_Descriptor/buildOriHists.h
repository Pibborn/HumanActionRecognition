/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * buildOriHists.h
 *
 * Code generation for function 'buildOriHists'
 *
 */

#ifndef __BUILDORIHISTS_H__
#define __BUILDORIHISTS_H__

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
extern void buildOriHists(const emlrtStack *sp, real_T x, real_T y, real_T z,
  int16_T radius, const emxArray_real_T *pix, const real_T fv_centers_data[],
  real_T myhist[80]);

#endif

/* End of code generation (buildOriHists.h) */
