/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: sort1.h
 *
 * MATLAB Coder version            : 3.2
 * C/C++ source code generated on  : 18-Nov-2016 16:32:39
 */

#ifndef SORT1_H
#define SORT1_H

/* Include Files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_defines.h"
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "omp.h"
#include "Create_Descriptor_types.h"

/* Function Declarations */
extern void c_sort(double x[80], int idx[80]);
extern void sort(double x_data[], int idx_data[], int idx_size[1]);

#endif

/*
 * File trailer for sort1.h
 *
 * [EOF]
 */
