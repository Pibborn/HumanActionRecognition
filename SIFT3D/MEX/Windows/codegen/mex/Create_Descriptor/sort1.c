/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * sort1.c
 *
 * Code generation for function 'sort1'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "Create_Descriptor.h"
#include "sort1.h"
#include "eml_int_forloop_overflow_check.h"
#include "sortIdx.h"
#include "Create_Descriptor_mexutil.h"
#include "Create_Descriptor_data.h"

/* Variable Definitions */
static emlrtRSInfo gc_emlrtRSI = { 19, "sort",
  "C:\\Program Files\\MATLAB\\R2015b\\toolbox\\eml\\eml\\+coder\\+internal\\sort.m"
};

static emlrtRSInfo hc_emlrtRSI = { 48, "sort",
  "C:\\Program Files\\MATLAB\\R2015b\\toolbox\\eml\\eml\\+coder\\+internal\\sort.m"
};

static emlrtRSInfo ic_emlrtRSI = { 69, "sort",
  "C:\\Program Files\\MATLAB\\R2015b\\toolbox\\eml\\eml\\+coder\\+internal\\sort.m"
};

static emlrtRSInfo jc_emlrtRSI = { 72, "sort",
  "C:\\Program Files\\MATLAB\\R2015b\\toolbox\\eml\\eml\\+coder\\+internal\\sort.m"
};

static emlrtRSInfo kc_emlrtRSI = { 74, "sort",
  "C:\\Program Files\\MATLAB\\R2015b\\toolbox\\eml\\eml\\+coder\\+internal\\sort.m"
};

static emlrtRSInfo lc_emlrtRSI = { 77, "sort",
  "C:\\Program Files\\MATLAB\\R2015b\\toolbox\\eml\\eml\\+coder\\+internal\\sort.m"
};

static emlrtRSInfo mc_emlrtRSI = { 80, "sort",
  "C:\\Program Files\\MATLAB\\R2015b\\toolbox\\eml\\eml\\+coder\\+internal\\sort.m"
};

static emlrtRSInfo nc_emlrtRSI = { 82, "sort",
  "C:\\Program Files\\MATLAB\\R2015b\\toolbox\\eml\\eml\\+coder\\+internal\\sort.m"
};

static emlrtRSInfo oc_emlrtRSI = { 49, "prodsize",
  "C:\\Program Files\\MATLAB\\R2015b\\toolbox\\eml\\eml\\+coder\\+internal\\prodsize.m"
};

static emlrtRSInfo fd_emlrtRSI = { 66, "sort",
  "C:\\Program Files\\MATLAB\\R2015b\\toolbox\\eml\\eml\\+coder\\+internal\\sort.m"
};

/* Function Declarations */
static void b_sort(const emlrtStack *sp, real_T x_data[], int32_T dim, int32_T
                   idx_data[], int32_T idx_size[1]);
static void d_sort(const emlrtStack *sp, real_T x[80], int32_T idx[80]);

/* Function Definitions */
static void b_sort(const emlrtStack *sp, real_T x_data[], int32_T dim, int32_T
                   idx_data[], int32_T idx_size[1])
{
  int32_T i18;
  real_T vwork_data[80];
  int32_T vwork_size[1];
  int32_T vstride;
  boolean_T b3;
  int32_T k;
  boolean_T b4;
  int32_T j;
  int32_T iidx_size[1];
  int32_T iidx_data[80];
  emlrtStack st;
  emlrtStack b_st;
  emlrtStack c_st;
  st.prev = sp;
  st.tls = sp->tls;
  st.site = &hc_emlrtRSI;
  b_st.prev = &st;
  b_st.tls = st.tls;
  c_st.prev = &b_st;
  c_st.tls = b_st.tls;
  if (dim <= 1) {
    i18 = 80;
  } else {
    i18 = 1;
  }

  vwork_size[0] = i18;
  idx_size[0] = 80;
  st.site = &ic_emlrtRSI;
  vstride = 1;
  b_st.site = &oc_emlrtRSI;
  if (1 > dim - 1) {
    b3 = false;
  } else {
    b3 = (dim - 1 > 2147483646);
  }

  if (b3) {
    c_st.site = &t_emlrtRSI;
    check_forloop_overflow_error(&c_st);
  }

  k = 1;
  while (k <= dim - 1) {
    vstride *= 80;
    k = 2;
  }

  st.site = &jc_emlrtRSI;
  st.site = &kc_emlrtRSI;
  if (1 > vstride) {
    b4 = false;
  } else {
    b4 = (vstride > 2147483646);
  }

  if (b4) {
    b_st.site = &t_emlrtRSI;
    check_forloop_overflow_error(&b_st);
  }

  for (j = 0; j + 1 <= vstride; j++) {
    st.site = &lc_emlrtRSI;
    for (k = 0; k + 1 <= i18; k++) {
      vwork_data[k] = x_data[j + k * vstride];
    }

    st.site = &mc_emlrtRSI;
    sortIdx(&st, vwork_data, vwork_size, iidx_data, iidx_size);
    st.site = &nc_emlrtRSI;
    for (k = 0; k + 1 <= i18; k++) {
      x_data[j + k * vstride] = vwork_data[k];
      idx_data[j + k * vstride] = iidx_data[k];
    }
  }
}

static void d_sort(const emlrtStack *sp, real_T x[80], int32_T idx[80])
{
  real_T x4[4];
  int8_T idx4[4];
  int32_T m;
  real_T xwork[80];
  int32_T nNaNs;
  int32_T ib;
  int32_T k;
  int32_T i2;
  int32_T i3;
  int32_T i4;
  int8_T perm[4];
  int32_T iwork[80];
  emlrtStack st;
  emlrtStack b_st;
  emlrtStack c_st;
  emlrtStack d_st;
  emlrtStack e_st;
  st.prev = sp;
  st.tls = sp->tls;
  st.site = &fd_emlrtRSI;
  b_st.prev = &st;
  b_st.tls = st.tls;
  c_st.prev = &b_st;
  c_st.tls = b_st.tls;
  d_st.prev = &c_st;
  d_st.tls = c_st.tls;
  e_st.prev = &d_st;
  e_st.tls = d_st.tls;
  b_st.site = &pc_emlrtRSI;
  c_st.site = &sc_emlrtRSI;
  memset(&idx[0], 0, 80U * sizeof(int32_T));
  for (m = 0; m < 4; m++) {
    x4[m] = 0.0;
    idx4[m] = 0;
  }

  memset(&xwork[0], 0, 80U * sizeof(real_T));
  nNaNs = 0;
  ib = 0;
  for (k = 0; k < 80; k++) {
    if (muDoubleScalarIsNaN(x[k])) {
      idx[79 - nNaNs] = k + 1;
      xwork[79 - nNaNs] = x[k];
      nNaNs++;
    } else {
      ib++;
      idx4[ib - 1] = (int8_T)(k + 1);
      x4[ib - 1] = x[k];
      if (ib == 4) {
        ib = k - nNaNs;
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
            perm[0] = (int8_T)m;
            perm[1] = (int8_T)i2;
            perm[2] = (int8_T)i3;
            perm[3] = (int8_T)i4;
          } else if (x4[i2 - 1] >= x4[i4 - 1]) {
            perm[0] = (int8_T)m;
            perm[1] = (int8_T)i3;
            perm[2] = (int8_T)i2;
            perm[3] = (int8_T)i4;
          } else {
            perm[0] = (int8_T)m;
            perm[1] = (int8_T)i3;
            perm[2] = (int8_T)i4;
            perm[3] = (int8_T)i2;
          }
        } else if (x4[m - 1] >= x4[i4 - 1]) {
          if (x4[i2 - 1] >= x4[i4 - 1]) {
            perm[0] = (int8_T)i3;
            perm[1] = (int8_T)m;
            perm[2] = (int8_T)i2;
            perm[3] = (int8_T)i4;
          } else {
            perm[0] = (int8_T)i3;
            perm[1] = (int8_T)m;
            perm[2] = (int8_T)i4;
            perm[3] = (int8_T)i2;
          }
        } else {
          perm[0] = (int8_T)i3;
          perm[1] = (int8_T)i4;
          perm[2] = (int8_T)m;
          perm[3] = (int8_T)i2;
        }

        idx[ib - 3] = idx4[perm[0] - 1];
        idx[ib - 2] = idx4[perm[1] - 1];
        idx[ib - 1] = idx4[perm[2] - 1];
        idx[ib] = idx4[perm[3] - 1];
        x[ib - 3] = x4[perm[0] - 1];
        x[ib - 2] = x4[perm[1] - 1];
        x[ib - 1] = x4[perm[2] - 1];
        x[ib] = x4[perm[3] - 1];
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

    d_st.site = &uc_emlrtRSI;
    if (ib > 2147483646) {
      e_st.site = &t_emlrtRSI;
      check_forloop_overflow_error(&e_st);
    }

    for (k = 80; k - 79 <= ib; k++) {
      idx[(k - nNaNs) - ib] = idx4[perm[k - 80] - 1];
      x[(k - nNaNs) - ib] = x4[perm[k - 80] - 1];
    }
  }

  m = asr_s32(nNaNs, 1U);
  d_st.site = &vc_emlrtRSI;
  for (k = 1; k <= m; k++) {
    ib = (int8_T)idx[(k - nNaNs) + 79];
    idx[(k - nNaNs) + 79] = (int8_T)idx[80 - k];
    idx[80 - k] = ib;
    x[(k - nNaNs) + 79] = xwork[80 - k];
    x[80 - k] = xwork[(k - nNaNs) + 79];
  }

  if ((nNaNs & 1) != 0) {
    x[(m - nNaNs) + 80] = xwork[(m - nNaNs) + 80];
  }

  memset(&iwork[0], 0, 80U * sizeof(int32_T));
  if (80 - nNaNs > 1) {
    c_st.site = &rc_emlrtRSI;
    b_merge_block(&c_st, idx, x, 80 - nNaNs, iwork, xwork);
  }

  if ((nNaNs > 0) && (80 - nNaNs > 0)) {
    c_st.site = &qc_emlrtRSI;
    d_st.site = &dd_emlrtRSI;
    if (nNaNs > 2147483646) {
      e_st.site = &t_emlrtRSI;
      check_forloop_overflow_error(&e_st);
    }

    for (k = 80; k - 79 <= nNaNs; k++) {
      xwork[k - 80] = x[k - nNaNs];
      iwork[k - 80] = idx[k - nNaNs];
    }

    for (k = 79 - nNaNs; k + 1 > 0; k--) {
      x[nNaNs + k] = x[k];
      idx[nNaNs + k] = idx[k];
    }

    d_st.site = &ed_emlrtRSI;
    for (k = 0; k + 1 <= nNaNs; k++) {
      x[k] = xwork[k];
      idx[k] = iwork[k];
    }
  }
}

void c_sort(const emlrtStack *sp, real_T x[80], int32_T idx[80])
{
  emlrtStack st;
  st.prev = sp;
  st.tls = sp->tls;
  st.site = &gc_emlrtRSI;
  d_sort(&st, x, idx);
}

void sort(const emlrtStack *sp, real_T x_data[], int32_T idx_data[], int32_T
          idx_size[1])
{
  emlrtStack st;
  st.prev = sp;
  st.tls = sp->tls;
  st.site = &gc_emlrtRSI;
  b_sort(&st, x_data, 1, idx_data, idx_size);
}

/* End of code generation (sort1.c) */
