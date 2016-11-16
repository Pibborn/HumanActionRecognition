/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * sortIdx.h
 *
 * Code generation for function 'sortIdx'
 *
 */

#ifndef __SORTIDX_H__
#define __SORTIDX_H__

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
extern void b_merge_block(const emlrtStack *sp, int32_T idx[80], real_T x[80],
  int32_T n, int32_T iwork[80], real_T xwork[80]);
extern void sortIdx(const emlrtStack *sp, real_T x_data[], int32_T x_size[1],
                    int32_T idx_data[], int32_T idx_size[1]);

#endif

/* End of code generation (sortIdx.h) */
