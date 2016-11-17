/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: fprintf.c
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 16-Nov-2016 14:15:56
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "Create_Descriptor.h"
#include "fprintf.h"
#include "fileManager.h"
#include <stdio.h>

/* Function Definitions */

/*
 * Arguments    : void
 * Return Type  : double
 */
double b_fprintf(void)
{
  int nbytesint;
  FILE * b_NULL;
  boolean_T autoflush;
  FILE * filestar;
  static const char cfmt[20] = { 'r', 'e', 'p', 'l', 'i', 'c', 'a', 't', 'e',
    'd', ' ', 'v', 'e', 'r', 't', 'i', 'c', 'e', 's', '\x00' };

  nbytesint = 0;
  b_NULL = NULL;
  fileManager(&filestar, &autoflush);
  if (filestar == b_NULL) {
  } else {
    nbytesint = fprintf(filestar, cfmt);
    fflush(filestar);
  }

  return nbytesint;
}

/*
 * File trailer for fprintf.c
 *
 * [EOF]
 */
