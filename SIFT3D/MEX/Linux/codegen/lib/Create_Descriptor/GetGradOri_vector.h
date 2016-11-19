/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: GetGradOri_vector.h
 *
 * MATLAB Coder version            : 3.2
 * C/C++ source code generated on  : 18-Nov-2016 16:32:39
 */

#ifndef GETGRADORI_VECTOR_H
#define GETGRADORI_VECTOR_H

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
extern void GetGradOri_vector(const emxArray_real_T *pix, short r, short c,
  short s, double *mag, double vect[3]);

#endif

/*
 * File trailer for GetGradOri_vector.h
 *
 * [EOF]
 */
