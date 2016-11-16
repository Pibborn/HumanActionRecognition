/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * sort1.h
 *
 * Code generation for function 'sort1'
 *
 */

#ifndef __SORT1_H__
#define __SORT1_H__

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
extern void c_sort(const emlrtStack *sp, real_T x[80], int32_T idx[80]);
extern void sort(const emlrtStack *sp, real_T x_data[], int32_T idx_data[],
                 int32_T idx_size[1]);

#endif

/* End of code generation (sort1.h) */
