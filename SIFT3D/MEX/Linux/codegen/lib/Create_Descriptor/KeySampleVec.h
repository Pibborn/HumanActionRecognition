/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: KeySampleVec.h
 *
 * MATLAB Coder version            : 3.2
 * C/C++ source code generated on  : 18-Nov-2016 16:32:39
 */

#ifndef KEYSAMPLEVEC_H
#define KEYSAMPLEVEC_H

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
extern void KeySampleVec(double key_x, double key_y, double key_z, double
  key_xyScale, double key_tScale, const emxArray_real_T *pix, double vec[640]);

#endif

/*
 * File trailer for KeySampleVec.h
 *
 * [EOF]
 */
