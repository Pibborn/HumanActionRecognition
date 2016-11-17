/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * dot.h
 *
 * Code generation for function 'dot'
 *
 */

#ifndef __DOT_H__
#define __DOT_H__

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
extern real_T dot(const real_T a_data[], const real_T b_data[]);

#ifdef __WATCOMC__

#pragma aux dot value [8087];

#endif
#endif

/* End of code generation (dot.h) */
