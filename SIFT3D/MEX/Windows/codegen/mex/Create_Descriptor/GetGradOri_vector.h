/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * GetGradOri_vector.h
 *
 * Code generation for function 'GetGradOri_vector'
 *
 */

#ifndef __GETGRADORI_VECTOR_H__
#define __GETGRADORI_VECTOR_H__

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
extern void GetGradOri_vector(const emlrtStack *sp, const emxArray_real_T *pix,
  int16_T r, int16_T c, int16_T s, real_T *mag, real_T vect[3]);

#endif

/* End of code generation (GetGradOri_vector.h) */
