/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: getKeyPoints_emxutil.h
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 16-Nov-2016 14:57:30
 */

#ifndef __GETKEYPOINTS_EMXUTIL_H__
#define __GETKEYPOINTS_EMXUTIL_H__

/* Include Files */
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rtwtypes.h"
#include "getKeyPoints_types.h"

/* Function Declarations */
extern void emxEnsureCapacity(emxArray__common *emxArray, int oldNumel, int
  elementSize);
extern void emxFree_real_T(emxArray_real_T **pEmxArray);
extern void emxInit_real_T(emxArray_real_T **pEmxArray, int numDimensions);

#endif

/*
 * File trailer for getKeyPoints_emxutil.h
 *
 * [EOF]
 */
