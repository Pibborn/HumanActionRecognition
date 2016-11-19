/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: NormalizeVec.c
 *
 * MATLAB Coder version            : 3.2
 * C/C++ source code generated on  : 18-Nov-2016 16:32:39
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "Create_Descriptor.h"
#include "NormalizeVec.h"

/* Function Definitions */

/*
 * Arguments    : double vec[640]
 * Return Type  : void
 */
void NormalizeVec(double vec[640])
{
  double sqlen;
  int k;
  sqlen = 0.0;
  for (k = 0; k < 640; k++) {
    sqlen += vec[k] * vec[k];
  }

  sqlen = 1.0 / sqrt(sqlen);
  for (k = 0; k < 640; k++) {
    vec[k] *= sqlen;
  }
}

/*
 * File trailer for NormalizeVec.c
 *
 * [EOF]
 */
