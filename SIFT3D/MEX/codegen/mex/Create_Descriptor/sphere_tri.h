/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * sphere_tri.h
 *
 * Code generation for function 'sphere_tri'
 *
 */

#ifndef __SPHERE_TRI_H__
#define __SPHERE_TRI_H__

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
extern void sphere_tri(const emlrtStack *sp, emxArray_real_T *FV_vertices,
  real_T FV_faces_data[], int32_T FV_faces_size[2], real_T FV_centers_data[],
  int32_T FV_centers_size[2]);

#endif

/* End of code generation (sphere_tri.h) */
