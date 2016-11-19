/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: mesh_refine_tri4.c
 *
 * MATLAB Coder version            : 3.2
 * C/C++ source code generated on  : 18-Nov-2016 16:32:39
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "Create_Descriptor.h"
#include "mesh_refine_tri4.h"
#include "Create_Descriptor_emxutil.h"
#include "fprintf.h"

/* Function Definitions */

/*
 * Arguments    : const emxArray_real_T *Vertices
 *                const double vertex_data[]
 *                emxArray_real_T *vertices
 *                double N_data[]
 *                int N_size[1]
 * Return Type  : void
 */
void mesh_find_vertex(const emxArray_real_T *Vertices, const double vertex_data[],
                      emxArray_real_T *vertices, double N_data[], int N_size[1])
{
  emxArray_real_T *Va;
  int Vertices_idx_0;
  int i3;
  emxArray_boolean_T *x;
  int jcol;
  int nx;
  int idx;
  emxArray_int32_T *ii;
  boolean_T exitg1;
  boolean_T guard1 = false;
  emxArray_int32_T *Vexist;
  emxInit_real_T(&Va, 2);

  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
  Vertices_idx_0 = Vertices->size[0];
  i3 = Va->size[0] * Va->size[1];
  Va->size[0] = Vertices_idx_0;
  Va->size[1] = 3;
  emxEnsureCapacity((emxArray__common *)Va, i3, (int)sizeof(double));
  if (!(Vertices_idx_0 == 0)) {
    Vertices_idx_0 = Vertices->size[0];
    for (jcol = 0; jcol < 3; jcol++) {
      nx = jcol * Vertices_idx_0;
      for (idx = 1; idx <= Vertices_idx_0; idx++) {
        Va->data[(nx + idx) - 1] = vertex_data[jcol];
      }
    }
  }

  emxInit_boolean_T(&x, 1);
  jcol = Vertices->size[0];
  i3 = x->size[0];
  x->size[0] = jcol;
  emxEnsureCapacity((emxArray__common *)x, i3, (int)sizeof(boolean_T));
  for (i3 = 0; i3 < jcol; i3++) {
    x->data[i3] = ((Vertices->data[i3] == Va->data[i3]) && (Vertices->data[i3 +
      Vertices->size[0]] == Va->data[i3 + Va->size[0]]) && (Vertices->data[i3 +
      (Vertices->size[0] << 1)] == Va->data[i3 + (Va->size[0] << 1)]));
  }

  emxFree_real_T(&Va);
  emxInit_int32_T(&ii, 1);
  nx = x->size[0];
  idx = 0;
  i3 = ii->size[0];
  ii->size[0] = x->size[0];
  emxEnsureCapacity((emxArray__common *)ii, i3, (int)sizeof(int));
  jcol = 1;
  exitg1 = false;
  while ((!exitg1) && (jcol <= nx)) {
    guard1 = false;
    if (x->data[jcol - 1]) {
      idx++;
      ii->data[idx - 1] = jcol;
      if (idx >= nx) {
        exitg1 = true;
      } else {
        guard1 = true;
      }
    } else {
      guard1 = true;
    }

    if (guard1) {
      jcol++;
    }
  }

  if (x->size[0] == 1) {
    if (idx == 0) {
      i3 = ii->size[0];
      ii->size[0] = 0;
      emxEnsureCapacity((emxArray__common *)ii, i3, (int)sizeof(int));
    }
  } else {
    i3 = ii->size[0];
    if (1 > idx) {
      ii->size[0] = 0;
    } else {
      ii->size[0] = idx;
    }

    emxEnsureCapacity((emxArray__common *)ii, i3, (int)sizeof(int));
  }

  emxFree_boolean_T(&x);
  emxInit_int32_T(&Vexist, 1);
  i3 = Vexist->size[0];
  Vexist->size[0] = ii->size[0];
  emxEnsureCapacity((emxArray__common *)Vexist, i3, (int)sizeof(int));
  jcol = ii->size[0];
  for (i3 = 0; i3 < jcol; i3++) {
    Vexist->data[i3] = ii->data[i3];
  }

  emxFree_int32_T(&ii);
  if (Vexist->size[0] != 0) {
    if (Vexist->size[0] == 1) {
      N_size[0] = Vexist->size[0];
      jcol = Vexist->size[0];
      for (i3 = 0; i3 < jcol; i3++) {
        N_data[i3] = Vexist->data[i3];
      }

      i3 = vertices->size[0] * vertices->size[1];
      vertices->size[0] = Vertices->size[0];
      vertices->size[1] = 3;
      emxEnsureCapacity((emxArray__common *)vertices, i3, (int)sizeof(double));
      jcol = Vertices->size[0] * Vertices->size[1];
      for (i3 = 0; i3 < jcol; i3++) {
        vertices->data[i3] = Vertices->data[i3];
      }
    } else {
      cfprintf();
    }
  } else {
    if (!(Vertices->size[0] == 0)) {
      jcol = Vertices->size[0];
    } else {
      jcol = 0;
    }

    i3 = vertices->size[0] * vertices->size[1];
    vertices->size[0] = jcol + 1;
    vertices->size[1] = 3;
    emxEnsureCapacity((emxArray__common *)vertices, i3, (int)sizeof(double));
    for (i3 = 0; i3 < 3; i3++) {
      for (nx = 0; nx < jcol; nx++) {
        vertices->data[nx + vertices->size[0] * i3] = Vertices->data[nx + jcol *
          i3];
      }
    }

    for (i3 = 0; i3 < 3; i3++) {
      for (nx = 0; nx < 1; nx++) {
        vertices->data[jcol + vertices->size[0] * i3] = vertex_data[i3];
      }
    }

    /* vertices(end+1,:) = vertex; */
    N_size[0] = 1;
    N_data[0] = vertices->size[0];
  }

  emxFree_int32_T(&Vexist);
}

/*
 * File trailer for mesh_refine_tri4.c
 *
 * [EOF]
 */
