/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * dot.c
 *
 * Code generation for function 'dot'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "Create_Descriptor.h"
#include "dot.h"

/* Function Definitions */
real_T dot(const real_T a_data[], const real_T b_data[])
{
  ptrdiff_t n_t;
  ptrdiff_t incx_t;
  ptrdiff_t incy_t;
  n_t = (ptrdiff_t)3;
  incx_t = (ptrdiff_t)1;
  incy_t = (ptrdiff_t)1;
  return ddot(&n_t, &a_data[0], &incx_t, &b_data[0], &incy_t);
}

/* End of code generation (dot.c) */
