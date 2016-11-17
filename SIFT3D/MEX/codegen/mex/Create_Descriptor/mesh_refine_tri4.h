/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * mesh_refine_tri4.h
 *
 * Code generation for function 'mesh_refine_tri4'
 *
 */

#ifndef __MESH_REFINE_TRI4_H__
#define __MESH_REFINE_TRI4_H__

/* Include files */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mwmathutil.h"
#include "tmwtypes.h"
#include "mex.h"
#include "emlrt.h"
#include "blas.h"
#include "rtwtypes.h"
#include "Create_Descriptor_types.h"

/* Function Declarations */
extern void mesh_find_vertex(const emlrtStack *sp, const emxArray_real_T
  *Vertices, const real_T vertex_data[], const int32_T vertex_size[2],
  emxArray_real_T *vertices, real_T N_data[], int32_T N_size[1]);

#endif

/* End of code generation (mesh_refine_tri4.h) */
