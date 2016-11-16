/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: mesh_refine_tri4.h
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 16-Nov-2016 14:15:56
 */

#ifndef __MESH_REFINE_TRI4_H__
#define __MESH_REFINE_TRI4_H__

/* Include Files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_defines.h"
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "Create_Descriptor_types.h"

/* Function Declarations */
extern void mesh_find_vertex(const emxArray_real_T *Vertices, const double
  vertex_data[], const int vertex_size[2], emxArray_real_T *vertices, double
  N_data[], int N_size[1]);

#endif

/*
 * File trailer for mesh_refine_tri4.h
 *
 * [EOF]
 */
