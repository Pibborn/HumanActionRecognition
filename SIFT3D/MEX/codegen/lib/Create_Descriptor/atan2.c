/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: atan2.c
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 16-Nov-2016 14:15:56
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "Create_Descriptor.h"
#include "atan2.h"
#include "Create_Descriptor_emxutil.h"
#include <stdio.h>

/* Function Declarations */
static double rt_atan2d_snf(double u0, double u1);

/* Function Definitions */

/*
 * Arguments    : double u0
 *                double u1
 * Return Type  : double
 */
static double rt_atan2d_snf(double u0, double u1)
{
  double y;
  int b_u0;
  int b_u1;
  if (rtIsNaN(u0) || rtIsNaN(u1)) {
    y = rtNaN;
  } else if (rtIsInf(u0) && rtIsInf(u1)) {
    if (u0 > 0.0) {
      b_u0 = 1;
    } else {
      b_u0 = -1;
    }

    if (u1 > 0.0) {
      b_u1 = 1;
    } else {
      b_u1 = -1;
    }

    y = atan2(b_u0, b_u1);
  } else if (u1 == 0.0) {
    if (u0 > 0.0) {
      y = RT_PI / 2.0;
    } else if (u0 < 0.0) {
      y = -(RT_PI / 2.0);
    } else {
      y = 0.0;
    }
  } else {
    y = atan2(u0, u1);
  }

  return y;
}

/*
 * Arguments    : const emxArray_real_T *y
 *                const emxArray_real_T *x
 *                emxArray_real_T *r
 * Return Type  : void
 */
void b_atan2(const emxArray_real_T *y, const emxArray_real_T *x, emxArray_real_T
             *r)
{
  int k;
  int i4;
  if (y->size[0] <= x->size[0]) {
    k = y->size[0];
  } else {
    k = x->size[0];
  }

  i4 = r->size[0];
  r->size[0] = k;
  emxEnsureCapacity((emxArray__common *)r, i4, (int)sizeof(double));
  for (k = 0; k + 1 <= y->size[0]; k++) {
    r->data[k] = rt_atan2d_snf(y->data[k], x->data[k]);
  }
}

/*
 * File trailer for atan2.c
 *
 * [EOF]
 */
