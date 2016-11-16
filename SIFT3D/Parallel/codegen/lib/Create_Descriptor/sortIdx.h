/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: sortIdx.h
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 16-Nov-2016 14:15:56
 */

#ifndef __SORTIDX_H__
#define __SORTIDX_H__

/* Include Files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_defines.h"
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "Create_Descriptor_types.h"

/* Function Declarations */
extern void b_merge_block(int idx[80], double x[80], int n, int iwork[80],
  double xwork[80]);
extern void sortIdx(double x_data[], int x_size[1], int idx_data[], int
                    idx_size[1]);

#endif

/*
 * File trailer for sortIdx.h
 *
 * [EOF]
 */
