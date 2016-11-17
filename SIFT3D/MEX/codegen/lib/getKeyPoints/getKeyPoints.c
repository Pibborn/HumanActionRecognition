/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: getKeyPoints.c
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 16-Nov-2016 14:57:30
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "getKeyPoints.h"
#include "getKeyPoints_emxutil.h"

/* Function Definitions */

/*
 * Arguments    : const emxArray_real_T *I
 *                double o
 *                double thresh
 *                emxArray_real_T *keyPoints
 * Return Type  : void
 */
void getKeyPoints(const emxArray_real_T *I, double o, double thresh,
                  emxArray_real_T *keyPoints)
{
  int k;
  int s;
  emxArray_real_T *b_keyPoints;
  int h;
  int w;
  int f;
  double currScaleCurrFrame[8];
  double pSet[27];
  double nSet[27];
  double cnfSet[9];
  double cpfSet[9];
  double ccfSet[8];
  double tempSet[80];
  double b_I;
  boolean_T check[80];
  int type;
  int loop_ub;
  int i0;
  k = keyPoints->size[0] * keyPoints->size[1];
  keyPoints->size[0] = 0;
  keyPoints->size[1] = 6;
  emxEnsureCapacity((emxArray__common *)keyPoints, k, (int)sizeof(double));
  s = 2;
  emxInit_real_T(&b_keyPoints, 2);
  while (s - 2 <= I->size[3] - 4) {
    for (h = 1; h - 1 <= I->size[0] - 5; h++) {
      for (w = 1; w - 1 <= I->size[1] - 5; w++) {
        for (f = 2; f - 2 <= I->size[2] - 5; f++) {
          if (I->data[(((h + I->size[0] * (w + 1)) + I->size[0] * I->size[1] * f)
                       + I->size[0] * I->size[1] * I->size[2] * s) + 1] > thresh)
          {
            for (k = 0; k < 3; k++) {
              currScaleCurrFrame[k] = I->data[((h + I->size[0] * (k + w)) +
                I->size[0] * I->size[1] * f) + I->size[0] * I->size[1] * I->
                size[2] * s];
            }

            for (k = 0; k < 3; k++) {
              currScaleCurrFrame[k + 3] = I->data[(((h + I->size[0] * (k + w)) +
                I->size[0] * I->size[1] * f) + I->size[0] * I->size[1] * I->
                size[2] * s) + 2];
            }

            currScaleCurrFrame[6] = I->data[(((h + I->size[0] * w) + I->size[0] *
              I->size[1] * f) + I->size[0] * I->size[1] * I->size[2] * s) + 1];
            currScaleCurrFrame[7] = I->data[(((h + I->size[0] * (2 + w)) +
              I->size[0] * I->size[1] * f) + I->size[0] * I->size[1] * I->size[2]
              * s) + 1];

            /*                     %% RESHAPING NEIGHBORHOOD ARRAYS TO ROW MATRICES */
            for (k = 0; k < 27; k++) {
              pSet[k] = I->data[(((k % 3 + h) + I->size[0] * (k / 3 % 3 + w)) +
                                 I->size[0] * I->size[1] * ((k / 9 + f) - 1)) +
                I->size[0] * I->size[1] * I->size[2] * (s - 1)];
            }

            for (k = 0; k < 27; k++) {
              nSet[k] = I->data[(((k % 3 + h) + I->size[0] * (k / 3 % 3 + w)) +
                                 I->size[0] * I->size[1] * ((k / 9 + f) - 1)) +
                I->size[0] * I->size[1] * I->size[2] * (s + 1)];
            }

            for (k = 0; k < 9; k++) {
              cnfSet[k] = I->data[(((k % 3 + h) + I->size[0] * (k / 3 + w)) +
                                   I->size[0] * I->size[1] * (f + 1)) + I->size
                [0] * I->size[1] * I->size[2] * s];
            }

            for (k = 0; k < 9; k++) {
              cpfSet[k] = I->data[(((k % 3 + h) + I->size[0] * (k / 3 + w)) +
                                   I->size[0] * I->size[1] * (f - 1)) + I->size
                [0] * I->size[1] * I->size[2] * s];
            }

            memcpy(&ccfSet[0], &currScaleCurrFrame[0], sizeof(double) << 3);

            /*                     %% CREATING NEIGHBORHOOD ARRAY */
            memcpy(&tempSet[0], &pSet[0], 27U * sizeof(double));
            memcpy(&tempSet[27], &nSet[0], 27U * sizeof(double));
            memcpy(&tempSet[54], &cnfSet[0], 9U * sizeof(double));
            memcpy(&tempSet[63], &cpfSet[0], 9U * sizeof(double));
            memcpy(&tempSet[72], &ccfSet[0], sizeof(double) << 3);

            /*  tempSet = sort(tempSet); */
            b_I = I->data[(((h + I->size[0] * (w + 1)) + I->size[0] * I->size[1]
                            * f) + I->size[0] * I->size[1] * I->size[2] * s) + 1];
            for (k = 0; k < 80; k++) {
              check[k] = (b_I > tempSet[k]);
            }

            type = 0;
            b_I = check[0];
            for (k = 0; k < 79; k++) {
              b_I += (double)check[k + 1];
            }

            if (b_I >= 77.6) {
              /*  fprintf('Maxima Detected\n'); */
              type = 1;
            } else {
              b_I = I->data[(((h + I->size[0] * (w + 1)) + I->size[0] * I->size
                              [1] * f) + I->size[0] * I->size[1] * I->size[2] *
                             s) + 1];
              for (k = 0; k < 80; k++) {
                check[k] = (b_I < tempSet[k]);
              }

              b_I = check[0];
              for (k = 0; k < 79; k++) {
                b_I += (double)check[k + 1];
              }

              if (b_I >= 77.6) {
                type = 2;
              }
            }

            if (type != 0) {
              k = b_keyPoints->size[0] * b_keyPoints->size[1];
              b_keyPoints->size[0] = keyPoints->size[0] + 1;
              b_keyPoints->size[1] = 6;
              emxEnsureCapacity((emxArray__common *)b_keyPoints, k, (int)sizeof
                                (double));
              for (k = 0; k < 6; k++) {
                loop_ub = keyPoints->size[0];
                for (i0 = 0; i0 < loop_ub; i0++) {
                  b_keyPoints->data[i0 + b_keyPoints->size[0] * k] =
                    keyPoints->data[i0 + keyPoints->size[0] * k];
                }
              }

              b_keyPoints->data[keyPoints->size[0]] = o;
              b_keyPoints->data[keyPoints->size[0] + b_keyPoints->size[0]] = 3.0
                + (double)(s - 2);
              b_keyPoints->data[keyPoints->size[0] + (b_keyPoints->size[0] << 1)]
                = 3.0 + (double)(h - 1);
              b_keyPoints->data[keyPoints->size[0] + b_keyPoints->size[0] * 3] =
                3.0 + (double)(w - 1);
              b_keyPoints->data[keyPoints->size[0] + (b_keyPoints->size[0] << 2)]
                = 3.0 + (double)(f - 2);
              b_keyPoints->data[keyPoints->size[0] + b_keyPoints->size[0] * 5] =
                type;
              k = keyPoints->size[0] * keyPoints->size[1];
              keyPoints->size[0] = b_keyPoints->size[0];
              keyPoints->size[1] = 6;
              emxEnsureCapacity((emxArray__common *)keyPoints, k, (int)sizeof
                                (double));
              for (k = 0; k < 6; k++) {
                loop_ub = b_keyPoints->size[0];
                for (i0 = 0; i0 < loop_ub; i0++) {
                  keyPoints->data[i0 + keyPoints->size[0] * k] =
                    b_keyPoints->data[i0 + b_keyPoints->size[0] * k];
                }
              }

              /*  disp([o,s,h,w,f, type]); */
            }
          } else {
            /*  Go to Next Pixel */
          }
        }
      }
    }

    s++;
  }

  emxFree_real_T(&b_keyPoints);
}

/*
 * File trailer for getKeyPoints.c
 *
 * [EOF]
 */
