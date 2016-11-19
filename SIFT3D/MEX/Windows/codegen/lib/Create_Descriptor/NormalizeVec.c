/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: NormalizeVec.c
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 16-Nov-2016 14:15:56
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "Create_Descriptor.h"
#include "NormalizeVec.h"
#include <stdio.h>

/* Function Definitions */

/*
 * Arguments    : double vec[640]
 * Return Type  : void
 */
void NormalizeVec(double vec[640])
{
  double sqlen;
  int k;
  double fac;
  sqlen = 0.0;
  for (k = 0; k < 640; k++) {
    sqlen += vec[k] * vec[k];
  }

  fac = 1.0 / sqrt(sqlen);
  for (k = 0; k < 640; k++) {
    vec[k] *= fac;
  }
}

/*
 * File trailer for NormalizeVec.c
 *
 * [EOF]
 */
