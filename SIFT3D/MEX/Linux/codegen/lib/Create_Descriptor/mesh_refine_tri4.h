/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: mesh_refine_tri4.h
 *
 * MATLAB Coder version            : 3.2
 * C/C++ source code generated on  : 18-Nov-2016 16:32:39
 */

#ifndef MESH_REFINE_TRI4_H
#define MESH_REFINE_TRI4_H

/* Include Files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_defines.h"
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "omp.h"
#include "Create_Descriptor_types.h"

/* Function Declarations */
extern void mesh_find_vertex(const emxArray_real_T *Vertices, const double
  vertex_data[], emxArray_real_T *vertices, double N_data[], int N_size[1]);

#endif

/*
 * File trailer for mesh_refine_tri4.h
 *
 * [EOF]
 */
