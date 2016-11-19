/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * getKeyPoints.h
 *
 * Code generation for function 'getKeyPoints'
 *
 */

#ifndef __GETKEYPOINTS_H__
#define __GETKEYPOINTS_H__

/* Include files */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tmwtypes.h"
#include "mex.h"
#include "emlrt.h"
#include "blas.h"
#include "rtwtypes.h"
#include "getKeyPoints_types.h"

/* Function Declarations */
extern void getKeyPoints(const emlrtStack *sp, const emxArray_real_T *I, real_T
  o, real_T thresh, emxArray_real_T *keyPoints);

#endif

/* End of code generation (getKeyPoints.h) */
