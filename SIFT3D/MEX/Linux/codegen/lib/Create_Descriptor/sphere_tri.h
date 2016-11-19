/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: sphere_tri.h
 *
 * MATLAB Coder version            : 3.2
 * C/C++ source code generated on  : 18-Nov-2016 16:32:39
 */

#ifndef SPHERE_TRI_H
#define SPHERE_TRI_H

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
extern void sphere_tri(emxArray_real_T *FV_vertices, double FV_faces_data[], int
  FV_faces_size[2], double FV_centers_data[], int FV_centers_size[2]);

#endif

/*
 * File trailer for sphere_tri.h
 *
 * [EOF]
 */
