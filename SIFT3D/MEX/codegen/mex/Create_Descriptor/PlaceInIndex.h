/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * PlaceInIndex.h
 *
 * Code generation for function 'PlaceInIndex'
 *
 */

#ifndef __PLACEININDEX_H__
#define __PLACEININDEX_H__

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
extern void PlaceInIndex(const emlrtStack *sp, real_T b_index[640], real_T mag,
  const real_T vect[3], int16_T i, int16_T j, int16_T s, const real_T
  fv_centers_data[]);

#endif

/* End of code generation (PlaceInIndex.h) */
