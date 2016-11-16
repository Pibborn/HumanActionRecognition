/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * mesh_refine_tri4.c
 *
 * Code generation for function 'mesh_refine_tri4'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "Create_Descriptor.h"
#include "mesh_refine_tri4.h"
#include "Create_Descriptor_emxutil.h"
#include "eml_int_forloop_overflow_check.h"
#include "fprintf.h"
#include "Create_Descriptor_mexutil.h"
#include "Create_Descriptor_data.h"

/* Variable Definitions */
static emlrtRSInfo m_emlrtRSI = { 160, "mesh_refine_tri4",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\mesh_refine_tri4.m" };

static emlrtRSInfo n_emlrtRSI = { 161, "mesh_refine_tri4",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\mesh_refine_tri4.m" };

static emlrtRSInfo o_emlrtRSI = { 169, "mesh_refine_tri4",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\mesh_refine_tri4.m" };

static emlrtRSInfo p_emlrtRSI = { 170, "mesh_refine_tri4",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\mesh_refine_tri4.m" };

static emlrtRSInfo q_emlrtRSI = { 117, "repmat",
  "C:\\Program Files\\MATLAB\\R2015b\\toolbox\\eml\\lib\\matlab\\elmat\\repmat.m"
};

static emlrtRSInfo r_emlrtRSI = { 114, "repmat",
  "C:\\Program Files\\MATLAB\\R2015b\\toolbox\\eml\\lib\\matlab\\elmat\\repmat.m"
};

static emlrtRSInfo s_emlrtRSI = { 18, "repmat",
  "C:\\Program Files\\MATLAB\\R2015b\\toolbox\\eml\\lib\\matlab\\elmat\\repmat.m"
};

static emlrtRSInfo u_emlrtRSI = { 44, "find",
  "C:\\Program Files\\MATLAB\\R2015b\\toolbox\\eml\\lib\\matlab\\elmat\\find.m"
};

static emlrtRSInfo v_emlrtRSI = { 253, "find",
  "C:\\Program Files\\MATLAB\\R2015b\\toolbox\\eml\\lib\\matlab\\elmat\\find.m"
};

static emlrtRSInfo w_emlrtRSI = { 234, "find",
  "C:\\Program Files\\MATLAB\\R2015b\\toolbox\\eml\\lib\\matlab\\elmat\\find.m"
};

static emlrtRSInfo y_emlrtRSI = { 32, "fprintf",
  "C:\\Program Files\\MATLAB\\R2015b\\toolbox\\eml\\lib\\matlab\\iofun\\fprintf.m"
};

static emlrtMCInfo b_emlrtMCI = { 37, 5, "repmat",
  "C:\\Program Files\\MATLAB\\R2015b\\toolbox\\eml\\lib\\matlab\\elmat\\repmat.m"
};

static emlrtMCInfo d_emlrtMCI = { 20, 5, "error",
  "C:\\Program Files\\MATLAB\\R2015b\\toolbox\\eml\\lib\\matlab\\lang\\error.m"
};

static emlrtRTEInfo f_emlrtRTEI = { 157, 26, "mesh_refine_tri4",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\mesh_refine_tri4.m" };

static emlrtRTEInfo g_emlrtRTEI = { 253, 13, "find",
  "C:\\Program Files\\MATLAB\\R2015b\\toolbox\\eml\\lib\\matlab\\elmat\\find.m"
};

static emlrtRTEInfo h_emlrtRTEI = { 160, 1, "mesh_refine_tri4",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\mesh_refine_tri4.m" };

static emlrtRTEInfo i_emlrtRTEI = { 161, 1, "mesh_refine_tri4",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\mesh_refine_tri4.m" };

static emlrtRTEInfo j_emlrtRTEI = { 36, 6, "find",
  "C:\\Program Files\\MATLAB\\R2015b\\toolbox\\eml\\lib\\matlab\\elmat\\find.m"
};

static emlrtECInfo h_emlrtECI = { -1, 161, 16, "mesh_refine_tri4",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\mesh_refine_tri4.m" };

static emlrtECInfo i_emlrtECI = { -1, 162, 16, "mesh_refine_tri4",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\mesh_refine_tri4.m" };

static emlrtECInfo j_emlrtECI = { -1, 163, 16, "mesh_refine_tri4",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\mesh_refine_tri4.m" };

static emlrtRTEInfo n_emlrtRTEI = { 243, 9, "find",
  "C:\\Program Files\\MATLAB\\R2015b\\toolbox\\eml\\lib\\matlab\\elmat\\find.m"
};

static emlrtRSInfo de_emlrtRSI = { 20, "error",
  "C:\\Program Files\\MATLAB\\R2015b\\toolbox\\eml\\lib\\matlab\\lang\\error.m"
};

static emlrtRSInfo ee_emlrtRSI = { 37, "repmat",
  "C:\\Program Files\\MATLAB\\R2015b\\toolbox\\eml\\lib\\matlab\\elmat\\repmat.m"
};

/* Function Declarations */
static void b_error(const emlrtStack *sp, const mxArray *b, emlrtMCInfo
                    *location);

/* Function Definitions */
static void b_error(const emlrtStack *sp, const mxArray *b, emlrtMCInfo
                    *location)
{
  const mxArray *pArray;
  pArray = b;
  emlrtCallMATLABR2012b(sp, 0, NULL, 1, &pArray, "error", true, location);
}

void mesh_find_vertex(const emlrtStack *sp, const emxArray_real_T *Vertices,
                      const real_T vertex_data[], const int32_T vertex_size[2],
                      emxArray_real_T *vertices, real_T N_data[], int32_T
                      N_size[1])
{
  int32_T Vertices_idx_0;
  int32_T ibmat;
  int32_T i2;
  static const char_T cv1[15] = { 'M', 'A', 'T', 'L', 'A', 'B', ':', 'p', 'm',
    'a', 'x', 's', 'i', 'z', 'e' };

  char_T u[15];
  const mxArray *y;
  static const int32_T iv4[2] = { 1, 15 };

  const mxArray *m1;
  emxArray_real_T *Va;
  int32_T nx;
  boolean_T b2;
  int32_T idx;
  emxArray_boolean_T *x;
  emxArray_boolean_T *r0;
  emxArray_int32_T *ii;
  boolean_T overflow;
  boolean_T exitg1;
  boolean_T guard1 = false;
  emxArray_real_T *Vexist;
  real_T msg;
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
  emlrtHeapReferenceStackEnterFcnR2012b(sp);

  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
  st.site = &m_emlrtRSI;
  b_st.site = &s_emlrtRSI;
  Vertices_idx_0 = Vertices->size[0];
  ibmat = Vertices->size[0];
  if (Vertices_idx_0 == ibmat) {
  } else {
    for (i2 = 0; i2 < 15; i2++) {
      u[i2] = cv1[i2];
    }

    y = NULL;
    m1 = emlrtCreateCharArray(2, iv4);
    emlrtInitCharArrayR2013a(&st, 15, m1, &u[0]);
    emlrtAssign(&y, m1);
    b_st.site = &ee_emlrtRSI;
    b_error(&b_st, y, &b_emlrtMCI);
  }

  emxInit_real_T(&st, &Va, 2, &h_emlrtRTEI, true);
  i2 = Va->size[0] * Va->size[1];
  Va->size[0] = Vertices_idx_0;
  Va->size[1] = 3;
  emxEnsureCapacity(&st, (emxArray__common *)Va, i2, (int32_T)sizeof(real_T),
                    &f_emlrtRTEI);
  Vertices_idx_0 = Vertices->size[0];
  b_st.site = &r_emlrtRSI;
  for (nx = 0; nx < 3; nx++) {
    ibmat = nx * Vertices_idx_0;
    b_st.site = &q_emlrtRSI;
    if (1 > Vertices_idx_0) {
      b2 = false;
    } else {
      b2 = (Vertices_idx_0 > 2147483646);
    }

    if (b2) {
      c_st.site = &t_emlrtRSI;
      check_forloop_overflow_error(&c_st);
    }

    for (idx = 1; idx <= Vertices_idx_0; idx++) {
      Va->data[(ibmat + idx) - 1] = vertex_data[nx];
    }
  }

  emxInit_boolean_T(&st, &x, 1, &f_emlrtRTEI, true);
  i2 = Vertices->size[0];
  ibmat = Va->size[0];
  if (i2 != ibmat) {
    emlrtSizeEqCheck1DR2012b(i2, ibmat, &h_emlrtECI, sp);
  }

  i2 = Vertices->size[0];
  ibmat = Va->size[0];
  if (i2 != ibmat) {
    emlrtSizeEqCheck1DR2012b(i2, ibmat, &i_emlrtECI, sp);
  }

  nx = Vertices->size[0];
  i2 = x->size[0];
  x->size[0] = nx;
  emxEnsureCapacity(sp, (emxArray__common *)x, i2, (int32_T)sizeof(boolean_T),
                    &f_emlrtRTEI);
  for (i2 = 0; i2 < nx; i2++) {
    x->data[i2] = (Vertices->data[i2] == Va->data[i2]);
  }

  emxInit_boolean_T(sp, &r0, 1, &f_emlrtRTEI, true);
  nx = Vertices->size[0];
  i2 = r0->size[0];
  r0->size[0] = nx;
  emxEnsureCapacity(sp, (emxArray__common *)r0, i2, (int32_T)sizeof(boolean_T),
                    &f_emlrtRTEI);
  for (i2 = 0; i2 < nx; i2++) {
    r0->data[i2] = (Vertices->data[i2 + Vertices->size[0]] == Va->data[i2 +
                    Va->size[0]]);
  }

  i2 = x->size[0];
  ibmat = r0->size[0];
  if (i2 != ibmat) {
    emlrtSizeEqCheck1DR2012b(i2, ibmat, &h_emlrtECI, sp);
  }

  i2 = Vertices->size[0];
  ibmat = Va->size[0];
  if (i2 != ibmat) {
    emlrtSizeEqCheck1DR2012b(i2, ibmat, &j_emlrtECI, sp);
  }

  i2 = x->size[0];
  emxEnsureCapacity(sp, (emxArray__common *)x, i2, (int32_T)sizeof(boolean_T),
                    &f_emlrtRTEI);
  nx = x->size[0];
  for (i2 = 0; i2 < nx; i2++) {
    x->data[i2] = (x->data[i2] && r0->data[i2]);
  }

  nx = Vertices->size[0];
  i2 = r0->size[0];
  r0->size[0] = nx;
  emxEnsureCapacity(sp, (emxArray__common *)r0, i2, (int32_T)sizeof(boolean_T),
                    &f_emlrtRTEI);
  for (i2 = 0; i2 < nx; i2++) {
    r0->data[i2] = (Vertices->data[i2 + (Vertices->size[0] << 1)] == Va->data[i2
                    + (Va->size[0] << 1)]);
  }

  emxFree_real_T(&Va);
  i2 = x->size[0];
  ibmat = r0->size[0];
  if (i2 != ibmat) {
    emlrtSizeEqCheck1DR2012b(i2, ibmat, &h_emlrtECI, sp);
  }

  st.site = &n_emlrtRSI;
  i2 = x->size[0];
  emxEnsureCapacity(&st, (emxArray__common *)x, i2, (int32_T)sizeof(boolean_T),
                    &f_emlrtRTEI);
  nx = x->size[0];
  for (i2 = 0; i2 < nx; i2++) {
    x->data[i2] = (x->data[i2] && r0->data[i2]);
  }

  emxFree_boolean_T(&r0);
  emxInit_int32_T(&st, &ii, 1, &j_emlrtRTEI, true);
  b_st.site = &u_emlrtRSI;
  nx = x->size[0];
  idx = 0;
  i2 = ii->size[0];
  ii->size[0] = x->size[0];
  emxEnsureCapacity(&b_st, (emxArray__common *)ii, i2, (int32_T)sizeof(int32_T),
                    &f_emlrtRTEI);
  c_st.site = &w_emlrtRSI;
  if (1 > x->size[0]) {
    overflow = false;
  } else {
    overflow = (x->size[0] > 2147483646);
  }

  if (overflow) {
    d_st.site = &t_emlrtRSI;
    check_forloop_overflow_error(&d_st);
  }

  ibmat = 1;
  exitg1 = false;
  while ((!exitg1) && (ibmat <= nx)) {
    guard1 = false;
    if (x->data[ibmat - 1]) {
      idx++;
      ii->data[idx - 1] = ibmat;
      if (idx >= nx) {
        exitg1 = true;
      } else {
        guard1 = true;
      }
    } else {
      guard1 = true;
    }

    if (guard1) {
      ibmat++;
    }
  }

  if (idx <= x->size[0]) {
  } else {
    emlrtErrorWithMessageIdR2012b(&b_st, &n_emlrtRTEI,
      "Coder:builtins:AssertionFailed", 0);
  }

  emxFree_boolean_T(&x);
  emxInit_real_T1(&b_st, &Vexist, 1, &i_emlrtRTEI, true);
  c_st.site = &v_emlrtRSI;
  i2 = ii->size[0];
  if (1 > idx) {
    ii->size[0] = 0;
  } else {
    ii->size[0] = idx;
  }

  emxEnsureCapacity(&b_st, (emxArray__common *)ii, i2, (int32_T)sizeof(int32_T),
                    &g_emlrtRTEI);
  i2 = Vexist->size[0];
  Vexist->size[0] = ii->size[0];
  emxEnsureCapacity(&st, (emxArray__common *)Vexist, i2, (int32_T)sizeof(real_T),
                    &f_emlrtRTEI);
  nx = ii->size[0];
  for (i2 = 0; i2 < nx; i2++) {
    Vexist->data[i2] = ii->data[i2];
  }

  emxFree_int32_T(&ii);
  if (Vexist->size[0] != 0) {
    if (Vexist->size[0] == 1) {
      N_size[0] = Vexist->size[0];
      nx = Vexist->size[0];
      for (i2 = 0; i2 < nx; i2++) {
        N_data[i2] = Vexist->data[i2];
      }

      i2 = vertices->size[0] * vertices->size[1];
      vertices->size[0] = Vertices->size[0];
      vertices->size[1] = 3;
      emxEnsureCapacity(sp, (emxArray__common *)vertices, i2, (int32_T)sizeof
                        (real_T), &f_emlrtRTEI);
      nx = Vertices->size[0] * Vertices->size[1];
      for (i2 = 0; i2 < nx; i2++) {
        vertices->data[i2] = Vertices->data[i2];
      }
    } else {
      st.site = &o_emlrtRSI;
      b_st.site = &y_emlrtRSI;
      msg = b_fprintf(&b_st);
      st.site = &p_emlrtRSI;
      b_st.site = &de_emlrtRSI;
      b_error(&b_st, emlrt_marshallOut(msg), &d_emlrtMCI);
    }
  } else {
    i2 = vertices->size[0] * vertices->size[1];
    vertices->size[0] = Vertices->size[0] + 1;
    vertices->size[1] = 3;
    emxEnsureCapacity(sp, (emxArray__common *)vertices, i2, (int32_T)sizeof
                      (real_T), &f_emlrtRTEI);
    for (i2 = 0; i2 < 3; i2++) {
      nx = Vertices->size[0];
      for (ibmat = 0; ibmat < nx; ibmat++) {
        vertices->data[ibmat + vertices->size[0] * i2] = Vertices->data[ibmat +
          Vertices->size[0] * i2];
      }
    }

    for (i2 = 0; i2 < 3; i2++) {
      vertices->data[Vertices->size[0] + vertices->size[0] * i2] =
        vertex_data[vertex_size[0] * i2];
    }

    /* vertices(end+1,:) = vertex; */
    N_size[0] = 1;
    N_data[0] = vertices->size[0];
  }

  emxFree_real_T(&Vexist);
  emlrtHeapReferenceStackLeaveFcnR2012b(sp);
}

/* End of code generation (mesh_refine_tri4.c) */
