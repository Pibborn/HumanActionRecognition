/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: sort1.c
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 16-Nov-2016 14:15:56
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "Create_Descriptor.h"
#include "sort1.h"
#include "sortIdx.h"
#include <stdio.h>

/* Function Declarations */
static void b_sort(double x_data[], int dim, int idx_data[], int idx_size[1]);
static void d_sort(double x[80], int idx[80]);

/* Function Definitions */

/*
 * Arguments    : double x_data[]
 *                int dim
 *                int idx_data[]
 *                int idx_size[1]
 * Return Type  : void
 */
static void b_sort(double x_data[], int dim, int idx_data[], int idx_size[1])
{
  int i8;
  double vwork_data[80];
  int vwork_size[1];
  int vstride;
  int k;
  int j;
  int iidx_size[1];
  int iidx_data[80];
  if (dim <= 1) {
    i8 = 80;
  } else {
    i8 = 1;
  }

  vwork_size[0] = i8;
  idx_size[0] = 80;
  vstride = 1;
  k = 1;
  while (k <= dim - 1) {
    vstride *= 80;
    k = 2;
  }

  for (j = 0; j + 1 <= vstride; j++) {
    for (k = 0; k + 1 <= i8; k++) {
      vwork_data[k] = x_data[j + k * vstride];
    }

    sortIdx(vwork_data, vwork_size, iidx_data, iidx_size);
    for (k = 0; k + 1 <= i8; k++) {
      x_data[j + k * vstride] = vwork_data[k];
      idx_data[j + k * vstride] = iidx_data[k];
    }
  }
}

/*
 * Arguments    : double x[80]
 *                int idx[80]
 * Return Type  : void
 */
static void d_sort(double x[80], int idx[80])
{
  double x4[4];
  signed char idx4[4];
  int m;
  double xwork[80];
  int nNaNs;
  int ib;
  int k;
  int i2;
  int i3;
  int i4;
  signed char perm[4];
  int iwork[80];
  memset(&idx[0], 0, 80U * sizeof(int));
  for (m = 0; m < 4; m++) {
    x4[m] = 0.0;
    idx4[m] = 0;
  }

  memset(&xwork[0], 0, 80U * sizeof(double));
  nNaNs = -79;
  ib = 0;
  for (k = 0; k < 80; k++) {
    if (rtIsNaN(x[k])) {
      idx[-nNaNs] = k + 1;
      xwork[-nNaNs] = x[k];
      nNaNs++;
    } else {
      ib++;
      idx4[ib - 1] = (signed char)(k + 1);
      x4[ib - 1] = x[k];
      if (ib == 4) {
        ib = (k - nNaNs) - 82;
        if (x4[0] >= x4[1]) {
          m = 1;
          i2 = 2;
        } else {
          m = 2;
          i2 = 1;
        }

        if (x4[2] >= x4[3]) {
          i3 = 3;
          i4 = 4;
        } else {
          i3 = 4;
          i4 = 3;
        }

        if (x4[m - 1] >= x4[i3 - 1]) {
          if (x4[i2 - 1] >= x4[i3 - 1]) {
            perm[0] = (signed char)m;
            perm[1] = (signed char)i2;
            perm[2] = (signed char)i3;
            perm[3] = (signed char)i4;
          } else if (x4[i2 - 1] >= x4[i4 - 1]) {
            perm[0] = (signed char)m;
            perm[1] = (signed char)i3;
            perm[2] = (signed char)i2;
            perm[3] = (signed char)i4;
          } else {
            perm[0] = (signed char)m;
            perm[1] = (signed char)i3;
            perm[2] = (signed char)i4;
            perm[3] = (signed char)i2;
          }
        } else if (x4[m - 1] >= x4[i4 - 1]) {
          if (x4[i2 - 1] >= x4[i4 - 1]) {
            perm[0] = (signed char)i3;
            perm[1] = (signed char)m;
            perm[2] = (signed char)i2;
            perm[3] = (signed char)i4;
          } else {
            perm[0] = (signed char)i3;
            perm[1] = (signed char)m;
            perm[2] = (signed char)i4;
            perm[3] = (signed char)i2;
          }
        } else {
          perm[0] = (signed char)i3;
          perm[1] = (signed char)i4;
          perm[2] = (signed char)m;
          perm[3] = (signed char)i2;
        }

        idx[ib] = idx4[perm[0] - 1];
        idx[ib + 1] = idx4[perm[1] - 1];
        idx[ib + 2] = idx4[perm[2] - 1];
        idx[ib + 3] = idx4[perm[3] - 1];
        x[ib] = x4[perm[0] - 1];
        x[ib + 1] = x4[perm[1] - 1];
        x[ib + 2] = x4[perm[2] - 1];
        x[ib + 3] = x4[perm[3] - 1];
        ib = 0;
      }
    }
  }

  if (ib > 0) {
    for (m = 0; m < 4; m++) {
      perm[m] = 0;
    }

    if (ib == 1) {
      perm[0] = 1;
    } else if (ib == 2) {
      if (x4[0] >= x4[1]) {
        perm[0] = 1;
        perm[1] = 2;
      } else {
        perm[0] = 2;
        perm[1] = 1;
      }
    } else if (x4[0] >= x4[1]) {
      if (x4[1] >= x4[2]) {
        perm[0] = 1;
        perm[1] = 2;
        perm[2] = 3;
      } else if (x4[0] >= x4[2]) {
        perm[0] = 1;
        perm[1] = 3;
        perm[2] = 2;
      } else {
        perm[0] = 3;
        perm[1] = 1;
        perm[2] = 2;
      }
    } else if (x4[0] >= x4[2]) {
      perm[0] = 2;
      perm[1] = 1;
      perm[2] = 3;
    } else if (x4[1] >= x4[2]) {
      perm[0] = 2;
      perm[1] = 3;
      perm[2] = 1;
    } else {
      perm[0] = 3;
      perm[1] = 2;
      perm[2] = 1;
    }

    for (k = 1; k <= ib; k++) {
      idx[(k - nNaNs) - ib] = idx4[perm[k - 1] - 1];
      x[(k - nNaNs) - ib] = x4[perm[k - 1] - 1];
    }
  }

  m = (nNaNs + 79) >> 1;
  for (k = 1; k <= m; k++) {
    ib = (signed char)idx[k - nNaNs];
    idx[k - nNaNs] = (signed char)idx[80 - k];
    idx[80 - k] = ib;
    x[k - nNaNs] = xwork[80 - k];
    x[80 - k] = xwork[k - nNaNs];
  }

  if (((nNaNs + 79) & 1) != 0) {
    x[(m - nNaNs) + 1] = xwork[(m - nNaNs) + 1];
  }

  memset(&iwork[0], 0, 80U * sizeof(int));
  if (1 - nNaNs > 1) {
    b_merge_block(idx, x, 1 - nNaNs, iwork, xwork);
  }

  if ((nNaNs + 79 > 0) && (1 - nNaNs > 0)) {
    for (k = 1; k <= nNaNs + 79; k++) {
      xwork[k - 1] = x[k - nNaNs];
      iwork[k - 1] = idx[k - nNaNs];
    }

    for (k = -nNaNs; k + 1 > 0; k--) {
      x[(nNaNs + k) + 79] = x[k];
      idx[(nNaNs + k) + 79] = idx[k];
    }

    for (k = 0; k + 1 <= nNaNs + 79; k++) {
      x[k] = xwork[k];
      idx[k] = iwork[k];
    }
  }
}

/*
 * Arguments    : double x[80]
 *                int idx[80]
 * Return Type  : void
 */
void c_sort(double x[80], int idx[80])
{
  d_sort(x, idx);
}

/*
 * Arguments    : double x_data[]
 *                int idx_data[]
 *                int idx_size[1]
 * Return Type  : void
 */
void sort(double x_data[], int idx_data[], int idx_size[1])
{
  b_sort(x_data, 1, idx_data, idx_size);
}

/*
 * File trailer for sort1.c
 *
 * [EOF]
 */
