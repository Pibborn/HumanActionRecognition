/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * sortIdx.c
 *
 * Code generation for function 'sortIdx'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "Create_Descriptor.h"
#include "sortIdx.h"
#include "eml_int_forloop_overflow_check.h"
#include "Create_Descriptor_mexutil.h"
#include "Create_Descriptor_data.h"

/* Variable Definitions */
static emlrtRSInfo tc_emlrtRSI = { 413, "sortIdx",
  "C:\\Program Files\\MATLAB\\R2015b\\toolbox\\eml\\eml\\+coder\\+internal\\sortIdx.m"
};

static emlrtRSInfo wc_emlrtRSI = { 520, "sortIdx",
  "C:\\Program Files\\MATLAB\\R2015b\\toolbox\\eml\\eml\\+coder\\+internal\\sortIdx.m"
};

static emlrtRSInfo yc_emlrtRSI = { 528, "sortIdx",
  "C:\\Program Files\\MATLAB\\R2015b\\toolbox\\eml\\eml\\+coder\\+internal\\sortIdx.m"
};

static emlrtRSInfo ad_emlrtRSI = { 535, "sortIdx",
  "C:\\Program Files\\MATLAB\\R2015b\\toolbox\\eml\\eml\\+coder\\+internal\\sortIdx.m"
};

static emlrtRSInfo bd_emlrtRSI = { 582, "sortIdx",
  "C:\\Program Files\\MATLAB\\R2015b\\toolbox\\eml\\eml\\+coder\\+internal\\sortIdx.m"
};

static emlrtRSInfo cd_emlrtRSI = { 551, "sortIdx",
  "C:\\Program Files\\MATLAB\\R2015b\\toolbox\\eml\\eml\\+coder\\+internal\\sortIdx.m"
};

/* Function Declarations */
static void b_merge(const emlrtStack *sp, int32_T idx[80], real_T x[80], int32_T
                    offset, int32_T np, int32_T nq, int32_T iwork[80], real_T
                    xwork[80]);
static void merge(const emlrtStack *sp, int32_T idx_data[], real_T x_data[],
                  int32_T offset, int32_T np, int32_T nq, int32_T iwork_data[],
                  real_T xwork_data[]);
static void merge_block(const emlrtStack *sp, int32_T idx_data[], real_T x_data[],
  int32_T n, int32_T iwork_data[], real_T xwork_data[]);

/* Function Definitions */
static void b_merge(const emlrtStack *sp, int32_T idx[80], real_T x[80], int32_T
                    offset, int32_T np, int32_T nq, int32_T iwork[80], real_T
                    xwork[80])
{
  int32_T n;
  boolean_T b6;
  int32_T qend;
  int32_T p;
  int32_T iout;
  int32_T exitg1;
  boolean_T b_p;
  emlrtStack st;
  emlrtStack b_st;
  st.prev = sp;
  st.tls = sp->tls;
  b_st.prev = &st;
  b_st.tls = st.tls;
  if (nq == 0) {
  } else {
    n = np + nq;
    st.site = &cd_emlrtRSI;
    if (1 > n) {
      b6 = false;
    } else {
      b6 = (n > 2147483646);
    }

    if (b6) {
      b_st.site = &t_emlrtRSI;
      check_forloop_overflow_error(&b_st);
    }

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
          st.site = &bd_emlrtRSI;
          if (p + 1 > np) {
            b_p = false;
          } else {
            b_p = (np > 2147483646);
          }

          if (b_p) {
            b_st.site = &t_emlrtRSI;
            check_forloop_overflow_error(&b_st);
          }

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

static void merge(const emlrtStack *sp, int32_T idx_data[], real_T x_data[],
                  int32_T offset, int32_T np, int32_T nq, int32_T iwork_data[],
                  real_T xwork_data[])
{
  int32_T n;
  boolean_T b5;
  int32_T qend;
  int32_T p;
  int32_T iout;
  int32_T exitg1;
  boolean_T b_p;
  emlrtStack st;
  emlrtStack b_st;
  st.prev = sp;
  st.tls = sp->tls;
  b_st.prev = &st;
  b_st.tls = st.tls;
  if (nq == 0) {
  } else {
    n = np + nq;
    st.site = &cd_emlrtRSI;
    if (1 > n) {
      b5 = false;
    } else {
      b5 = (n > 2147483646);
    }

    if (b5) {
      b_st.site = &t_emlrtRSI;
      check_forloop_overflow_error(&b_st);
    }

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
          st.site = &bd_emlrtRSI;
          if (p + 1 > np) {
            b_p = false;
          } else {
            b_p = (np > 2147483646);
          }

          if (b_p) {
            b_st.site = &t_emlrtRSI;
            check_forloop_overflow_error(&b_st);
          }

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

static void merge_block(const emlrtStack *sp, int32_T idx_data[], real_T x_data[],
  int32_T n, int32_T iwork_data[], real_T xwork_data[])
{
  int32_T nPairs;
  int32_T bLen;
  int32_T tailOffset;
  int32_T nTail;
  emlrtStack st;
  st.prev = sp;
  st.tls = sp->tls;
  nPairs = asr_s32(n, 2U);
  bLen = 4;
  while (nPairs > 1) {
    if ((nPairs & 1) != 0) {
      nPairs--;
      tailOffset = bLen * nPairs;
      nTail = n - tailOffset;
      if (nTail > bLen) {
        st.site = &wc_emlrtRSI;
        merge(&st, idx_data, x_data, tailOffset, bLen, nTail - bLen, iwork_data,
              xwork_data);
      }
    }

    tailOffset = bLen << 1;
    nPairs = asr_s32(nPairs, 1U);
    for (nTail = 1; nTail <= nPairs; nTail++) {
      st.site = &yc_emlrtRSI;
      merge(&st, idx_data, x_data, (nTail - 1) * tailOffset, bLen, bLen,
            iwork_data, xwork_data);
    }

    bLen = tailOffset;
  }

  if (n > bLen) {
    st.site = &ad_emlrtRSI;
    merge(&st, idx_data, x_data, 0, bLen, n - bLen, iwork_data, xwork_data);
  }
}

void b_merge_block(const emlrtStack *sp, int32_T idx[80], real_T x[80], int32_T
                   n, int32_T iwork[80], real_T xwork[80])
{
  int32_T nPairs;
  int32_T bLen;
  int32_T tailOffset;
  int32_T nTail;
  emlrtStack st;
  st.prev = sp;
  st.tls = sp->tls;
  nPairs = asr_s32(n, 2U);
  bLen = 4;
  while (nPairs > 1) {
    if ((nPairs & 1) != 0) {
      nPairs--;
      tailOffset = bLen * nPairs;
      nTail = n - tailOffset;
      if (nTail > bLen) {
        st.site = &wc_emlrtRSI;
        b_merge(&st, idx, x, tailOffset, bLen, nTail - bLen, iwork, xwork);
      }
    }

    tailOffset = bLen << 1;
    nPairs = asr_s32(nPairs, 1U);
    for (nTail = 1; nTail <= nPairs; nTail++) {
      st.site = &yc_emlrtRSI;
      b_merge(&st, idx, x, (nTail - 1) * tailOffset, bLen, bLen, iwork, xwork);
    }

    bLen = tailOffset;
  }

  if (n > bLen) {
    st.site = &ad_emlrtRSI;
    b_merge(&st, idx, x, 0, bLen, n - bLen, iwork, xwork);
  }
}

void sortIdx(const emlrtStack *sp, real_T x_data[], int32_T x_size[1], int32_T
             idx_data[], int32_T idx_size[1])
{
  int8_T unnamed_idx_0;
  int32_T x_size_idx_0;
  int32_T m;
  int32_T ib;
  real_T b_x_data[80];
  int32_T n;
  real_T x4[4];
  int8_T idx4[4];
  int32_T iwork_data[80];
  real_T xwork_data[80];
  int32_T nNaNs;
  int32_T k;
  int32_T wOffset;
  int32_T i3;
  int32_T i4;
  int8_T perm[4];
  emlrtStack st;
  emlrtStack b_st;
  emlrtStack c_st;
  emlrtStack d_st;
  st.prev = sp;
  st.tls = sp->tls;
  b_st.prev = &st;
  b_st.tls = st.tls;
  c_st.prev = &b_st;
  c_st.tls = b_st.tls;
  d_st.prev = &c_st;
  d_st.tls = c_st.tls;
  unnamed_idx_0 = (int8_T)x_size[0];
  st.site = &pc_emlrtRSI;
  b_st.site = &sc_emlrtRSI;
  x_size_idx_0 = x_size[0];
  m = x_size[0];
  for (ib = 0; ib < m; ib++) {
    b_x_data[ib] = x_data[ib];
  }

  idx_size[0] = unnamed_idx_0;
  m = unnamed_idx_0;
  for (ib = 0; ib < m; ib++) {
    idx_data[ib] = 0;
  }

  n = x_size[0];
  for (m = 0; m < 4; m++) {
    x4[m] = 0.0;
    idx4[m] = 0;
  }

  m = unnamed_idx_0;
  for (ib = 0; ib < m; ib++) {
    iwork_data[ib] = 0;
  }

  m = (int8_T)x_size[0];
  for (ib = 0; ib < m; ib++) {
    xwork_data[ib] = 0.0;
  }

  nNaNs = 0;
  ib = 0;
  c_st.site = &tc_emlrtRSI;
  for (k = 0; k + 1 <= n; k++) {
    if (muDoubleScalarIsNaN(b_x_data[k])) {
      idx_data[(n - nNaNs) - 1] = k + 1;
      xwork_data[(n - nNaNs) - 1] = b_x_data[k];
      nNaNs++;
    } else {
      ib++;
      idx4[ib - 1] = (int8_T)(k + 1);
      x4[ib - 1] = b_x_data[k];
      if (ib == 4) {
        ib = k - nNaNs;
        if (x4[0] >= x4[1]) {
          m = 1;
          wOffset = 2;
        } else {
          m = 2;
          wOffset = 1;
        }

        if (x4[2] >= x4[3]) {
          i3 = 3;
          i4 = 4;
        } else {
          i3 = 4;
          i4 = 3;
        }

        if (x4[m - 1] >= x4[i3 - 1]) {
          if (x4[wOffset - 1] >= x4[i3 - 1]) {
            perm[0] = (int8_T)m;
            perm[1] = (int8_T)wOffset;
            perm[2] = (int8_T)i3;
            perm[3] = (int8_T)i4;
          } else if (x4[wOffset - 1] >= x4[i4 - 1]) {
            perm[0] = (int8_T)m;
            perm[1] = (int8_T)i3;
            perm[2] = (int8_T)wOffset;
            perm[3] = (int8_T)i4;
          } else {
            perm[0] = (int8_T)m;
            perm[1] = (int8_T)i3;
            perm[2] = (int8_T)i4;
            perm[3] = (int8_T)wOffset;
          }
        } else if (x4[m - 1] >= x4[i4 - 1]) {
          if (x4[wOffset - 1] >= x4[i4 - 1]) {
            perm[0] = (int8_T)i3;
            perm[1] = (int8_T)m;
            perm[2] = (int8_T)wOffset;
            perm[3] = (int8_T)i4;
          } else {
            perm[0] = (int8_T)i3;
            perm[1] = (int8_T)m;
            perm[2] = (int8_T)i4;
            perm[3] = (int8_T)wOffset;
          }
        } else {
          perm[0] = (int8_T)i3;
          perm[1] = (int8_T)i4;
          perm[2] = (int8_T)m;
          perm[3] = (int8_T)wOffset;
        }

        idx_data[ib - 3] = idx4[perm[0] - 1];
        idx_data[ib - 2] = idx4[perm[1] - 1];
        idx_data[ib - 1] = idx4[perm[2] - 1];
        idx_data[ib] = idx4[perm[3] - 1];
        b_x_data[ib - 3] = x4[perm[0] - 1];
        b_x_data[ib - 2] = x4[perm[1] - 1];
        b_x_data[ib - 1] = x4[perm[2] - 1];
        b_x_data[ib] = x4[perm[3] - 1];
        ib = 0;
      }
    }
  }

  wOffset = (x_size[0] - nNaNs) - 1;
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

    c_st.site = &uc_emlrtRSI;
    if (ib > 2147483646) {
      d_st.site = &t_emlrtRSI;
      check_forloop_overflow_error(&d_st);
    }

    for (k = 1; k <= ib; k++) {
      idx_data[(wOffset - ib) + k] = idx4[perm[k - 1] - 1];
      b_x_data[(wOffset - ib) + k] = x4[perm[k - 1] - 1];
    }
  }

  m = asr_s32(nNaNs, 1U) + 1;
  c_st.site = &vc_emlrtRSI;
  for (k = 1; k < m; k++) {
    ib = idx_data[wOffset + k];
    idx_data[wOffset + k] = idx_data[n - k];
    idx_data[n - k] = ib;
    b_x_data[wOffset + k] = xwork_data[n - k];
    b_x_data[n - k] = xwork_data[wOffset + k];
  }

  if ((nNaNs & 1) != 0) {
    b_x_data[wOffset + m] = xwork_data[wOffset + m];
  }

  m = x_size[0] - nNaNs;
  if (m > 1) {
    b_st.site = &rc_emlrtRSI;
    merge_block(&b_st, idx_data, b_x_data, m, iwork_data, xwork_data);
  }

  if ((nNaNs > 0) && (m > 0)) {
    b_st.site = &qc_emlrtRSI;
    c_st.site = &dd_emlrtRSI;
    if (nNaNs > 2147483646) {
      d_st.site = &t_emlrtRSI;
      check_forloop_overflow_error(&d_st);
    }

    for (k = 0; k + 1 <= nNaNs; k++) {
      xwork_data[k] = b_x_data[m + k];
      iwork_data[k] = idx_data[m + k];
    }

    for (k = m - 1; k + 1 > 0; k--) {
      b_x_data[nNaNs + k] = b_x_data[k];
      idx_data[nNaNs + k] = idx_data[k];
    }

    c_st.site = &ed_emlrtRSI;
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

/* End of code generation (sortIdx.c) */
