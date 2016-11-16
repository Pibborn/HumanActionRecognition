/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: GetGradOri_vector.c
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 16-Nov-2016 14:15:56
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "Create_Descriptor.h"
#include "GetGradOri_vector.h"
#include <stdio.h>

/* Function Definitions */

/*
 * Arguments    : const emxArray_real_T *pix
 *                short r
 *                short c
 *                short s
 *                double *mag
 *                double vect[3]
 * Return Type  : void
 */
void GetGradOri_vector(const emxArray_real_T *pix, short r, short c, short s,
  double *mag, double vect[3])
{
  int i5;
  int i6;
  double xgrad;
  double ygrad;
  double zgrad;
  double b_xgrad[3];
  static const signed char iv1[3] = { 1, 0, 0 };

  if (r > pix->size[0]) {
    /*  r = rows; */
    r = (short)pix->size[0];
  }

  if (c > pix->size[1]) {
    /*  c = cols; */
    c = (short)pix->size[1];
  }

  if (s > pix->size[2]) {
    /*  s = slices; */
    s = (short)pix->size[2];
  }

  i5 = c + 1;
  if (i5 > 32767) {
    i5 = 32767;
  }

  i6 = c - 1;
  if (i6 < -32768) {
    i6 = -32768;
  }

  if (c == 1) {
    xgrad = 2.0 * (pix->data[((r + pix->size[0]) + pix->size[0] * pix->size[1] *
      (s - 1)) - 1] - pix->data[(r + pix->size[0] * pix->size[1] * (s - 1)) - 1]);
  } else if (c == pix->size[1]) {
    xgrad = 2.0 * (pix->data[((r + pix->size[0] * (c - 1)) + pix->size[0] *
      pix->size[1] * (s - 1)) - 1] - pix->data[((r + pix->size[0] * (c - 2)) +
      pix->size[0] * pix->size[1] * (s - 1)) - 1]);
  } else {
    xgrad = pix->data[((r + pix->size[0] * (i5 - 1)) + pix->size[0] * pix->size
                       [1] * (s - 1)) - 1] - pix->data[((r + pix->size[0] * (i6
      - 1)) + pix->size[0] * pix->size[1] * (s - 1)) - 1];
  }

  i5 = r + 1;
  if (i5 > 32767) {
    i5 = 32767;
  }

  if (r == 1) {
    ygrad = 2.0 * (pix->data[pix->size[0] * (c - 1) + pix->size[0] * pix->size[1]
                   * (s - 1)] - pix->data[(pix->size[0] * (c - 1) + pix->size[0]
      * pix->size[1] * (s - 1)) + 1]);
  } else if (r == pix->size[0]) {
    ygrad = 2.0 * (pix->data[((r + pix->size[0] * (c - 1)) + pix->size[0] *
      pix->size[1] * (s - 1)) - 2] - pix->data[((r + pix->size[0] * (c - 1)) +
      pix->size[0] * pix->size[1] * (s - 1)) - 1]);
  } else {
    ygrad = pix->data[((r + pix->size[0] * (c - 1)) + pix->size[0] * pix->size[1]
                       * (s - 1)) - 2] - pix->data[((i5 + pix->size[0] * (c - 1))
      + pix->size[0] * pix->size[1] * (s - 1)) - 1];
  }

  i5 = s + 1;
  if (i5 > 32767) {
    i5 = 32767;
  }

  if (s == 1) {
    zgrad = 2.0 * (pix->data[((r + pix->size[0] * (c - 1)) + pix->size[0] *
      pix->size[1]) - 1] - pix->data[(r + pix->size[0] * (c - 1)) - 1]);
  } else if (s == pix->size[2]) {
    zgrad = 2.0 * (pix->data[((r + pix->size[0] * (c - 1)) + pix->size[0] *
      pix->size[1] * (s - 1)) - 1] - pix->data[((r + pix->size[0] * (c - 1)) +
      pix->size[0] * pix->size[1] * (s - 2)) - 1]);
  } else {
    zgrad = pix->data[((r + pix->size[0] * (c - 1)) + pix->size[0] * pix->size[1]
                       * (i5 - 1)) - 1] - pix->data[((r + pix->size[0] * (c - 1))
      + pix->size[0] * pix->size[1] * (s - 2)) - 1];
  }

  *mag = sqrt((xgrad * xgrad + ygrad * ygrad) + zgrad * zgrad);
  if (*mag != 0.0) {
    b_xgrad[0] = xgrad;
    b_xgrad[1] = ygrad;
    b_xgrad[2] = zgrad;
    for (i5 = 0; i5 < 3; i5++) {
      vect[i5] = b_xgrad[i5] / *mag;
    }
  } else {
    for (i5 = 0; i5 < 3; i5++) {
      vect[i5] = iv1[i5];
    }
  }
}

/*
 * File trailer for GetGradOri_vector.c
 *
 * [EOF]
 */
