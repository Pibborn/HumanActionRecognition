/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: sortIdx.c
 *
 * MATLAB Coder version            : 3.2
 * C/C++ source code generated on  : 18-Nov-2016 16:32:39
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "Create_Descriptor.h"
#include "sortIdx.h"

/* Function Declarations */
static void b_merge(int idx[80], double x[80], int offset, int np, int nq, int
                    iwork[80], double xwork[80]);
static void merge(int idx_data[], double x_data[], int offset, int np, int nq,
                  int iwork_data[], double xwork_data[]);
static void merge_block(int idx_data[], double x_data[], int n, int iwork_data[],
  double xwork_data[]);

/* Function Definitions */

/*
 * Arguments    : int idx[80]
 *                double x[80]
 *                int offset
 *                int np
 *                int nq
 *                int iwork[80]
 *                double xwork[80]
 * Return Type  : void
 */
static void b_merge(int idx[80], double x[80], int offset, int np, int nq, int
                    iwork[80], double xwork[80])
{
  int n;
  int qend;
  int p;
  int iout;
  int exitg1;
  if (nq != 0) {
    n = np + nq;
    for (qend = 0; qend + 1 <= n; qend++) {
      iwork[qend] = idx[offset + qend];
      xwork[qend] = x[offset + qend];
    }

    p = 0;
    n = np;
    qend = np + nq;
    iout = offset - 1;
    do {
      exitg1 = 0;
      iout++;
      if (xwork[p] >= xwork[n]) {
        idx[iout] = iwork[p];
        x[iout] = xwork[p];
        if (p + 1 < np) {
          p++;
        } else {
          exitg1 = 1;
        }
      } else {
        idx[iout] = iwork[n];
        x[iout] = xwork[n];
        if (n + 1 < qend) {
          n++;
        } else {
          n = (iout - p) + 1;
          while (p + 1 <= np) {
            idx[n + p] = iwork[p];
            x[n + p] = xwork[p];
            p++;
          }

          exitg1 = 1;
        }
      }
    } while (exitg1 == 0);
  }
}

/*
 * Arguments    : int idx_data[]
 *                double x_data[]
 *                int offset
 *                int np
 *                int nq
 *                int iwork_data[]
 *                double xwork_data[]
 * Return Type  : void
 */
static void merge(int idx_data[], double x_data[], int offset, int np, int nq,
                  int iwork_data[], double xwork_data[])
{
  int n;
  int qend;
  int p;
  int iout;
  int exitg1;
  if (nq != 0) {
    n = np + nq;
    for (qend = 0; qend + 1 <= n; qend++) {
      iwork_data[qend] = idx_data[offset + qend];
      xwork_data[qend] = x_data[offset + qend];
    }

    p = 0;
    n = np;
    qend = np + nq;
    iout = offset - 1;
    do {
      exitg1 = 0;
      iout++;
      if (xwork_data[p] >= xwork_data[n]) {
        idx_data[iout] = iwork_data[p];
        x_data[iout] = xwork_data[p];
        if (p + 1 < np) {
          p++;
        } else {
          exitg1 = 1;
        }
      } else {
        idx_data[iout] = iwork_data[n];
        x_data[iout] = xwork_data[n];
        if (n + 1 < qend) {
          n++;
        } else {
          n = (iout - p) + 1;
          while (p + 1 <= np) {
            idx_data[n + p] = iwork_data[p];
            x_data[n + p] = xwork_data[p];
            p++;
          }

          exitg1 = 1;
        }
      }
    } while (exitg1 == 0);
  }
}

/*
 * Arguments    : int idx_data[]
 *                double x_data[]
 *                int n
 *                int iwork_data[]
 *                double xwork_data[]
 * Return Type  : void
 */
static void merge_block(int idx_data[], double x_data[], int n, int iwork_data[],
  double xwork_data[])
{
  int nPairs;
  int bLen;
  int tailOffset;
  int nTail;
  nPairs = n >> 2;
  bLen = 4;
  while (nPairs > 1) {
    if ((nPairs & 1) != 0) {
      nPairs--;
      tailOffset = bLen * nPairs;
      nTail = n - tailOffset;
      if (nTail > bLen) {
        merge(idx_data, x_data, tailOffset, bLen, nTail - bLen, iwork_data,
              xwork_data);
      }
    }

    tailOffset = bLen << 1;
    nPairs >>= 1;
    for (nTail = 1; nTail <= nPairs; nTail++) {
      merge(idx_data, x_data, (nTail - 1) * tailOffset, bLen, bLen, iwork_data,
            xwork_data);
    }

    bLen = tailOffset;
  }

  if (n > bLen) {
    merge(idx_data, x_data, 0, bLen, n - bLen, iwork_data, xwork_data);
  }
}

/*
 * Arguments    : int idx[80]
 *                double x[80]
 *                int n
 *                int iwork[80]
 *                double xwork[80]
 * Return Type  : void
 */
void b_merge_block(int idx[80], double x[80], int n, int iwork[80], double
                   xwork[80])
{
  int nPairs;
  int bLen;
  int tailOffset;
  int nTail;
  nPairs = n >> 2;
  bLen = 4;
  while (nPairs > 1) {
    if ((nPairs & 1) != 0) {
      nPairs--;
      tailOffset = bLen * nPairs;
      nTail = n - tailOffset;
      if (nTail > bLen) {
        b_merge(idx, x, tailOffset, bLen, nTail - bLen, iwork, xwork);
      }
    }

    tailOffset = bLen << 1;
    nPairs >>= 1;
    for (nTail = 1; nTail <= nPairs; nTail++) {
      b_merge(idx, x, (nTail - 1) * tailOffset, bLen, bLen, iwork, xwork);
    }

    bLen = tailOffset;
  }

  if (n > bLen) {
    b_merge(idx, x, 0, bLen, n - bLen, iwork, xwork);
  }
}

/*
 * Arguments    : double x_data[]
 *                int x_size[1]
 *                int idx_data[]
 *                int idx_size[1]
 * Return Type  : void
 */
void sortIdx(double x_data[], int x_size[1], int idx_data[], int idx_size[1])
{
  signed char unnamed_idx_0;
  int x_size_idx_0;
  int i;
  int ib;
  double b_x_data[80];
  int n;
  double x4[4];
  signed char idx4[4];
  int iwork_data[80];
  int nNaNs;
  double xwork_data[80];
  int k;
  int wOffset;
  signed char perm[4];
  int i3;
  int i4;
  unnamed_idx_0 = (signed char)x_size[0];
  x_size_idx_0 = x_size[0];
  i = x_size[0];
  for (ib = 0; ib < i; ib++) {
    b_x_data[ib] = x_data[ib];
  }

  idx_size[0] = unnamed_idx_0;
  i = unnamed_idx_0;
  for (ib = 0; ib < i; ib++) {
    idx_data[ib] = 0;
  }

  n = x_size[0];
  for (i = 0; i < 4; i++) {
    x4[i] = 0.0;
    idx4[i] = 0;
  }

  i = unnamed_idx_0;
  for (ib = 0; ib < i; ib++) {
    iwork_data[ib] = 0;
  }

  i = (signed char)x_size[0];
  for (ib = 0; ib < i; ib++) {
    xwork_data[ib] = 0.0;
  }

  nNaNs = 0;
  ib = 0;
  for (k = 0; k + 1 <= n; k++) {
    if (rtIsNaN(b_x_data[k])) {
      idx_data[(n - nNaNs) - 1] = k + 1;
      xwork_data[(n - nNaNs) - 1] = b_x_data[k];
      nNaNs++;
    } else {
      ib++;
      idx4[ib - 1] = (signed char)(k + 1);
      x4[ib - 1] = b_x_data[k];
      if (ib == 4) {
        i = k - nNaNs;
        if (x4[0] >= x4[1]) {
          ib = 1;
          wOffset = 2;
        } else {
          ib = 2;
          wOffset = 1;
        }

        if (x4[2] >= x4[3]) {
          i3 = 3;
          i4 = 4;
        } else {
          i3 = 4;
          i4 = 3;
        }

        if (x4[ib - 1] >= x4[i3 - 1]) {
          if (x4[wOffset - 1] >= x4[i3 - 1]) {
            perm[0] = (signed char)ib;
            perm[1] = (signed char)wOffset;
            perm[2] = (signed char)i3;
            perm[3] = (signed char)i4;
          } else if (x4[wOffset - 1] >= x4[i4 - 1]) {
            perm[0] = (signed char)ib;
            perm[1] = (signed char)i3;
            perm[2] = (signed char)wOffset;
            perm[3] = (signed char)i4;
          } else {
            perm[0] = (signed char)ib;
            perm[1] = (signed char)i3;
            perm[2] = (signed char)i4;
            perm[3] = (signed char)wOffset;
          }
        } else if (x4[ib - 1] >= x4[i4 - 1]) {
          if (x4[wOffset - 1] >= x4[i4 - 1]) {
            perm[0] = (signed char)i3;
            perm[1] = (signed char)ib;
            perm[2] = (signed char)wOffset;
            perm[3] = (signed char)i4;
          } else {
            perm[0] = (signed char)i3;
            perm[1] = (signed char)ib;
            perm[2] = (signed char)i4;
            perm[3] = (signed char)wOffset;
          }
        } else {
          perm[0] = (signed char)i3;
          perm[1] = (signed char)i4;
          perm[2] = (signed char)ib;
          perm[3] = (signed char)wOffset;
        }

        idx_data[i - 3] = idx4[perm[0] - 1];
        idx_data[i - 2] = idx4[perm[1] - 1];
        idx_data[i - 1] = idx4[perm[2] - 1];
        idx_data[i] = idx4[perm[3] - 1];
        b_x_data[i - 3] = x4[perm[0] - 1];
        b_x_data[i - 2] = x4[perm[1] - 1];
        b_x_data[i - 1] = x4[perm[2] - 1];
        b_x_data[i] = x4[perm[3] - 1];
        ib = 0;
      }
    }
  }

  wOffset = (x_size[0] - nNaNs) - 1;
  if (ib > 0) {
    for (i = 0; i < 4; i++) {
      perm[i] = 0;
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
      idx_data[(wOffset - ib) + k] = idx4[perm[k - 1] - 1];
      b_x_data[(wOffset - ib) + k] = x4[perm[k - 1] - 1];
    }
  }

  i = nNaNs >> 1;
  for (k = 1; k <= i; k++) {
    ib = idx_data[wOffset + k];
    idx_data[wOffset + k] = idx_data[n - k];
    idx_data[n - k] = ib;
    b_x_data[wOffset + k] = xwork_data[n - k];
    b_x_data[n - k] = xwork_data[wOffset + k];
  }

  if ((nNaNs & 1) != 0) {
    b_x_data[(wOffset + i) + 1] = xwork_data[(wOffset + i) + 1];
  }

  i = x_size[0] - nNaNs;
  if (i > 1) {
    merge_block(idx_data, b_x_data, i, iwork_data, xwork_data);
  }

  if ((nNaNs > 0) && (i > 0)) {
    for (k = 0; k + 1 <= nNaNs; k++) {
      xwork_data[k] = b_x_data[i + k];
      iwork_data[k] = idx_data[i + k];
    }

    for (k = i - 1; k + 1 > 0; k--) {
      b_x_data[nNaNs + k] = b_x_data[k];
      idx_data[nNaNs + k] = idx_data[k];
    }

    for (k = 0; k + 1 <= nNaNs; k++) {
      b_x_data[k] = xwork_data[k];
      idx_data[k] = iwork_data[k];
    }
  }

  x_size[0] = x_size_idx_0;
  for (ib = 0; ib < x_size_idx_0; ib++) {
    x_data[ib] = b_x_data[ib];
  }
}

/*
 * File trailer for sortIdx.c
 *
 * [EOF]
 */
