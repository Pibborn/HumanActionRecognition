/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * fprintf.h
 *
 * Code generation for function 'fprintf'
 *
 */

#ifndef __FPRINTF_H__
#define __FPRINTF_H__

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
extern real_T b_fprintf(const emlrtStack *sp);

#ifdef __WATCOMC__

#pragma aux b_fprintf value [8087];

#endif
#endif

/* End of code generation (fprintf.h) */
