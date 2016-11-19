/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: Create_Descriptor.h
 *
 * MATLAB Coder version            : 3.2
 * C/C++ source code generated on  : 18-Nov-2016 16:32:39
 */

#ifndef CREATE_DESCRIPTOR_H
#define CREATE_DESCRIPTOR_H

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
extern void Create_Descriptor(const emxArray_real_T *pix, double xyScale, double
  tScale, double x, double y, double z, struct0_T *keyPoint, double *reRun);

#endif

/*
 * File trailer for Create_Descriptor.h
 *
 * [EOF]
 */
