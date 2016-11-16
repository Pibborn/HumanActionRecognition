/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * MakeKeypoint.c
 *
 * Code generation for function 'MakeKeypoint'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "Create_Descriptor.h"
#include "MakeKeypoint.h"
#include "mpower.h"
#include "Create_Descriptor_emxutil.h"
#include "eml_int_forloop_overflow_check.h"
#include "PlaceInIndex.h"
#include "GetGradOri_vector.h"
#include "NormalizeVec.h"
#include "sphere_tri.h"
#include "Create_Descriptor_mexutil.h"
#include "Create_Descriptor_data.h"

/* Variable Definitions */
static emlrtRSInfo hd_emlrtRSI = { 109, "MakeKeypoint",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\MakeKeypoint.m" };

static emlrtRSInfo id_emlrtRSI = { 112, "MakeKeypoint",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\MakeKeypoint.m" };

static emlrtRSInfo jd_emlrtRSI = { 121, "MakeKeypoint",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\MakeKeypoint.m" };

static emlrtRSInfo kd_emlrtRSI = { 45, "KeySampleVec",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\KeySampleVec.m" };

static emlrtRSInfo ld_emlrtRSI = { 45, "KeySample",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\KeySample.m" };

static emlrtRSInfo md_emlrtRSI = { 62, "KeySample",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\KeySample.m" };

static emlrtRSInfo nd_emlrtRSI = { 63, "KeySample",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\KeySample.m" };

static emlrtRSInfo od_emlrtRSI = { 64, "KeySample",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\KeySample.m" };

static emlrtRSInfo pd_emlrtRSI = { 72, "KeySample",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\KeySample.m" };

static emlrtRSInfo qd_emlrtRSI = { 102, "KeySample",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\KeySample.m" };

static emlrtRSInfo sd_emlrtRSI = { 52, "AddSample",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\AddSample.m" };

static emlrtRSInfo td_emlrtRSI = { 55, "AddSample",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\AddSample.m" };

static emlrtMCInfo e_emlrtMCI = { 127, 9, "MakeKeypoint",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\MakeKeypoint.m" };

static emlrtMCInfo f_emlrtMCI = { 94, 17, "KeySample",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\KeySample.m" };

static emlrtRSInfo ae_emlrtRSI = { 94, "KeySample",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\KeySample.m" };

static emlrtRSInfo be_emlrtRSI = { 127, "MakeKeypoint",
  "C:\\Users\\ygarg\\Dropbox (ASU)\\sift3D\\Parallel\\MakeKeypoint.m" };

/* Function Definitions */
void MakeKeypointSample(const emlrtStack *sp, struct0_T *key, const
  emxArray_real_T *pix)
{
  emxArray_real_T *expl_temp;
  int32_T changed;
  int32_T fv_centers_size[2];
  real_T fv_centers_data[240];
  int32_T expl_temp_size[2];
  real_T expl_temp_data[240];
  real_T d1;
  int16_T a;
  int16_T irow;
  int16_T icol;
  int16_T islice;
  int16_T xyiradius;
  int16_T tiradius;
  real_T b_index[640];
  int32_T i19;
  boolean_T b_a;
  int16_T i;
  boolean_T c_a;
  int16_T j;
  boolean_T d_a;
  int16_T s;
  real_T distsq;
  int32_T i20;
  int16_T i_indx;
  int16_T j_indx;
  int16_T s_indx;
  static const char_T cv5[44] = { 'S', 'o', 'm', 'e', 't', 'h', 'i', 'n', 'g',
    ' ', 'w', 'r', 'o', 'n', 'g', ' ', 'w', 'i', 't', 'h', ' ', 't', 'h', 'e',
    ' ', 's', 'u', 'b', '-', 'h', 'i', 's', 't', 'o', 'g', 'r', 'a', 'm', ' ',
    'i', 'n', 'd', 'e', 'x' };

  char_T u[44];
  const mxArray *y;
  static const int32_T iv10[2] = { 1, 44 };

  const mxArray *m8;
  int16_T r;
  int16_T c;
  int16_T t;
  real_T vect[3];
  real_T grad;
  real_T vec[640];
  int32_T b_i;
  int16_T intval;
  static const char_T cv6[36] = { 'A', 's', 's', 'e', 'r', 't', 'a', 't', 'i',
    'o', 'n', ' ', 'f', 'a', 'i', 'l', 'e', 'd', ' ', 'i', 'n', ' ', 'M', 'a',
    'k', 'e', 'K', 'e', 'y', 'p', 'o', 'i', 'n', 't', '.', 'm' };

  char_T b_u[36];
  const mxArray *b_y;
  static const int32_T iv11[2] = { 1, 36 };

  emlrtStack st;
  emlrtStack b_st;
  emlrtStack c_st;
  emlrtStack d_st;
  st.prev = sp;
  st.tls = sp->tls;
  b_st.prev = &st;
  b_st.tls = st.tls;
  c_st.prev = &b_st;
  c_st.tls = b_st.tls;
  d_st.prev = &c_st;
  d_st.tls = c_st.tls;
  emlrtHeapReferenceStackEnterFcnR2012b(sp);
  emxInit_real_T(sp, &expl_temp, 2, &emlrtRTEI, true);

  /*  LoadParams; */
  /*  lData = load('LoadParams.mat'); */
  /*   */
  /*  Display_flag = lData.Display_flag; */
  /*  IgnoreGradSign = lData.IgnoreGradSign; */
  /*  IndexSigma = lData.IndexSigma; */
  /*  IndexSize = lData.IndexSize; */
  /*  MagFactor = lData.MagFactor; */
  /*  nFaces = lData.nFaces; */
  /*  OriHistThresh = lData.OriHistThresh; */
  /*  OriSigma = lData.OriSigma; */
  /*  Smooth_Flag = lData.Smooth_Flag; */
  /*  Smooth_Var = lData.Smooth_Var; */
  /*  Tessellation_flag = lData.Tessellation_flag; */
  /*  Tessellation_levels = lData.Tessellation_levels; */
  /*  TwoPeak_Flag = lData.TwoPeak_Flag; */
  /*  UseHistogramOri = lData.UseHistogramOri; */
  /*  Allow 3DSIFT to throw out points, Default: 1 */
  /*  Min: 1  Default: 2  */
  /*  Display a sphere which can be rotated (Rotate 3D button) to view gradient directions */
  /*  Keep this as 1 */
  /*  Min: zero  Default: 1 */
  /*  Number of faces in the tessellation, not a parameter */
  /*  Adds gradient data to surrounding bins in final histogram */
  /*  Determines amount of smoothing, Default: 20 */
  /*  The rest of the variables are not modified often, but are included here */
  /*  for completeness sake */
  changed = 0;
  st.site = &hd_emlrtRSI;

  /*  LoadParams; */
  /*  lData = load('LoadParams.mat'); */
  /*   */
  /*  Display_flag = lData.Display_flag; */
  /*  IgnoreGradSign = lData.IgnoreGradSign; */
  /*  IndexSigma = lData.IndexSigma; */
  /*  IndexSize = lData.IndexSize; */
  /*  MagFactor = lData.MagFactor; */
  /*  nFaces = lData.nFaces; */
  /*  OriHistThresh = lData.OriHistThresh; */
  /*  OriSigma = lData.OriSigma; */
  /*  Smooth_Flag = lData.Smooth_Flag; */
  /*  Smooth_Var = lData.Smooth_Var; */
  /*  Tessellation_flag = lData.Tessellation_flag; */
  /*  Tessellation_levels = lData.Tessellation_levels; */
  /*  TwoPeak_Flags = lData.TwoPeak_Flag; */
  /*  UseHistogramOri = lData.UseHistogramOri; */
  /*  Allow 3DSIFT to throw out points, Default: 1 */
  /*  Min: 1  Default: 2  */
  /*  Display a sphere which can be rotated (Rotate 3D button) to view gradient directions */
  /*  Keep this as 1 */
  /*  Min: zero  Default: 1 */
  /*  Number of faces in the tessellation, not a parameter */
  /*  Adds gradient data to surrounding bins in final histogram */
  /*  Determines amount of smoothing, Default: 20 */
  /*  The rest of the variables are not modified often, but are included here */
  /*  for completeness sake */
  /*  Method 1 */
  b_st.site = &kd_emlrtRSI;

  /*  LoadParams; */
  /*  lData = load('LoadParams.mat'); */
  /*   */
  /*  Display_flag = lData.Display_flag; */
  /*  IgnoreGradSign = lData.IgnoreGradSign; */
  /*  IndexSigma = lData.IndexSigma; */
  /*  IndexSize = lData.IndexSize; */
  /*  MagFactor = lData.MagFactor; */
  /*  nFaces = lData.nFaces; */
  /*  OriHistThresh = lData.OriHistThresh; */
  /*  OriSigma = lData.OriSigma; */
  /*  Smooth_Flag = lData.Smooth_Flag; */
  /*  Smooth_Var = lData.Smooth_Var; */
  /*  Tessellation_flag = lData.Tessellation_flag; */
  /*  Tessellation_levels = lData.Tessellation_levels; */
  /*  TwoPeak_Flags = lData.TwoPeak_Flag; */
  /*  UseHistogramOri = lData.UseHistogramOri; */
  /*  Allow 3DSIFT to throw out points, Default: 1 */
  /*  Min: 1  Default: 2  */
  /*  Display a sphere which can be rotated (Rotate 3D button) to view gradient directions */
  /*  Keep this as 1 */
  /*  Min: zero  Default: 1 */
  /*  Number of faces in the tessellation, not a parameter */
  /*  Adds gradient data to surrounding bins in final histogram */
  /*  Determines amount of smoothing, Default: 20 */
  /*  The rest of the variables are not modified often, but are included here */
  /*  for completeness sake */
  c_st.site = &ld_emlrtRSI;
  sphere_tri(&c_st, expl_temp, expl_temp_data, expl_temp_size, fv_centers_data,
             fv_centers_size);
  d1 = muDoubleScalarRound(key->x);
  if (d1 < 32768.0) {
    if (d1 >= -32768.0) {
      a = (int16_T)d1;
    } else {
      a = MIN_int16_T;
    }
  } else if (d1 >= 32768.0) {
    a = MAX_int16_T;
  } else {
    a = 0;
  }

  irow = a;

  /*  x */
  d1 = muDoubleScalarRound(key->y);
  if (d1 < 32768.0) {
    if (d1 >= -32768.0) {
      a = (int16_T)d1;
    } else {
      a = MIN_int16_T;
    }
  } else if (d1 >= 32768.0) {
    a = MAX_int16_T;
  } else {
    a = 0;
  }

  icol = a;

  /*  y */
  d1 = muDoubleScalarRound(key->z);
  if (d1 < 32768.0) {
    if (d1 >= -32768.0) {
      a = (int16_T)d1;
    } else {
      a = MIN_int16_T;
    }
  } else if (d1 >= 32768.0) {
    a = MAX_int16_T;
  } else {
    a = 0;
  }

  islice = a;

  /*  t */
  d1 = muDoubleScalarRound(1.414 * (key->xyScale * 3.0) * 3.0 / 2.0);
  if (d1 < 32768.0) {
    if (d1 >= -32768.0) {
      a = (int16_T)d1;
    } else {
      a = MIN_int16_T;
    }
  } else if (d1 >= 32768.0) {
    a = MAX_int16_T;
  } else {
    a = 0;
  }

  xyiradius = a;
  d1 = muDoubleScalarRound(1.414 * (key->tScale * 3.0) * 3.0 / 2.0);
  if (d1 < 32768.0) {
    if (d1 >= -32768.0) {
      a = (int16_T)d1;
    } else {
      a = MIN_int16_T;
    }
  } else if (d1 >= 32768.0) {
    a = MAX_int16_T;
  } else {
    a = 0;
  }

  tiradius = a;
  emxFree_real_T(&expl_temp);
  memset(&b_index[0], 0, 640U * sizeof(real_T));
  i19 = -xyiradius;
  if (i19 > 32767) {
    i19 = 32767;
  }

  a = (int16_T)i19;
  c_st.site = &md_emlrtRSI;
  if (a > xyiradius) {
    b_a = false;
  } else {
    b_a = (xyiradius > 32766);
  }

  if (b_a) {
    d_st.site = &t_emlrtRSI;
    b_check_forloop_overflow_error(&d_st);
  }

  i = a;
  while (i <= xyiradius) {
    i19 = -xyiradius;
    if (i19 > 32767) {
      i19 = 32767;
    }

    a = (int16_T)i19;
    c_st.site = &nd_emlrtRSI;
    if (a > xyiradius) {
      c_a = false;
    } else {
      c_a = (xyiradius > 32766);
    }

    if (c_a) {
      d_st.site = &t_emlrtRSI;
      b_check_forloop_overflow_error(&d_st);
    }

    j = a;
    while (j <= xyiradius) {
      i19 = -tiradius;
      if (i19 > 32767) {
        i19 = 32767;
      }

      a = (int16_T)i19;
      c_st.site = &od_emlrtRSI;
      if (a > tiradius) {
        d_a = false;
      } else {
        d_a = (tiradius > 32766);
      }

      if (d_a) {
        d_st.site = &t_emlrtRSI;
        b_check_forloop_overflow_error(&d_st);
      }

      s = a;
      while (s <= tiradius) {
        /*  This is redundant and probably slows down the code, but at */
        /*  some point this solved a major overflow headache, so leaving */
        /*  as-is for now */
        c_st.site = &pd_emlrtRSI;
        distsq = (mpower(i) + mpower(j)) + mpower(s);
        i19 = i + xyiradius;
        if (i19 > 32767) {
          i19 = 32767;
        } else {
          if (i19 < -32768) {
            i19 = -32768;
          }
        }

        a = xyiradius;
        if (a > 16383) {
          a = MAX_int16_T;
        } else if (a <= -16384) {
          a = MIN_int16_T;
        } else {
          a <<= 1;
        }

        i20 = (int32_T)muDoubleScalarRound((real_T)a / 2.0);
        a = (int16_T)i20;
        d1 = muDoubleScalarRound(muDoubleScalarFloor((real_T)i19 / (real_T)a));
        if (d1 < 32768.0) {
          if (d1 >= -32768.0) {
            a = (int16_T)d1;
          } else {
            a = MIN_int16_T;
          }
        } else if (d1 >= 32768.0) {
          a = MAX_int16_T;
        } else {
          a = 0;
        }

        i19 = a + 1;
        if (i19 > 32767) {
          i19 = 32767;
        }

        i_indx = (int16_T)i19;
        i19 = j + xyiradius;
        if (i19 > 32767) {
          i19 = 32767;
        } else {
          if (i19 < -32768) {
            i19 = -32768;
          }
        }

        a = xyiradius;
        if (a > 16383) {
          a = MAX_int16_T;
        } else if (a <= -16384) {
          a = MIN_int16_T;
        } else {
          a <<= 1;
        }

        i20 = (int32_T)muDoubleScalarRound((real_T)a / 2.0);
        a = (int16_T)i20;
        d1 = muDoubleScalarRound(muDoubleScalarFloor((real_T)i19 / (real_T)a));
        if (d1 < 32768.0) {
          if (d1 >= -32768.0) {
            a = (int16_T)d1;
          } else {
            a = MIN_int16_T;
          }
        } else if (d1 >= 32768.0) {
          a = MAX_int16_T;
        } else {
          a = 0;
        }

        i19 = a + 1;
        if (i19 > 32767) {
          i19 = 32767;
        }

        j_indx = (int16_T)i19;
        i19 = s + tiradius;
        if (i19 > 32767) {
          i19 = 32767;
        } else {
          if (i19 < -32768) {
            i19 = -32768;
          }
        }

        a = tiradius;
        if (a > 16383) {
          a = MAX_int16_T;
        } else if (a <= -16384) {
          a = MIN_int16_T;
        } else {
          a <<= 1;
        }

        i20 = (int32_T)muDoubleScalarRound((real_T)a / 2.0);
        a = (int16_T)i20;
        d1 = muDoubleScalarRound(muDoubleScalarFloor((real_T)i19 / (real_T)a));
        if (d1 < 32768.0) {
          if (d1 >= -32768.0) {
            a = (int16_T)d1;
          } else {
            a = MIN_int16_T;
          }
        } else if (d1 >= 32768.0) {
          a = MAX_int16_T;
        } else {
          a = 0;
        }

        i19 = a + 1;
        if (i19 > 32767) {
          i19 = 32767;
        }

        s_indx = (int16_T)i19;
        if (i_indx > 2) {
          /*  i_indx = IndexSize; */
          i_indx = 2;
        }

        if (j_indx > 2) {
          /*  j_indx = IndexSize; */
          j_indx = 2;
        }

        if (s_indx > 2) {
          /* s_indx = IndexSize; */
          s_indx = 2;
        }

        if ((i_indx < 1) || (j_indx < 1) || (s_indx < 1)) {
          for (i19 = 0; i19 < 44; i19++) {
            u[i19] = cv5[i19];
          }

          y = NULL;
          m8 = emlrtCreateCharArray(2, iv10);
          emlrtInitCharArrayR2013a(&b_st, 44, m8, &u[0]);
          emlrtAssign(&y, m8);
          c_st.site = &ae_emlrtRSI;
          disp(&c_st, y, &f_emlrtMCI);
        }

        i19 = irow + i;
        if (i19 > 32767) {
          i19 = 32767;
        } else {
          if (i19 < -32768) {
            i19 = -32768;
          }
        }

        r = (int16_T)i19;
        i19 = icol + j;
        if (i19 > 32767) {
          i19 = 32767;
        } else {
          if (i19 < -32768) {
            i19 = -32768;
          }
        }

        c = (int16_T)i19;
        i19 = islice + s;
        if (i19 > 32767) {
          i19 = 32767;
        } else {
          if (i19 < -32768) {
            i19 = -32768;
          }
        }

        t = (int16_T)i19;
        c_st.site = &qd_emlrtRSI;

        /*  LoadParams; */
        /*  lData = load('LoadParams.mat'); */
        /*   */
        /*  Display_flag = lData.Display_flag; */
        /*  IgnoreGradSign = lData.IgnoreGradSign; */
        /*  IndexSigma = lData.IndexSigma; */
        /*  IndexSize = lData.IndexSize; */
        /*  MagFactor = lData.MagFactor; */
        /*  nFaces = lData.nFaces; */
        /*  OriHistThresh = lData.OriHistThresh; */
        /*  OriSigma = lData.OriSigma; */
        /*  Smooth_Flag = lData.Smooth_Flag; */
        /*  Smooth_Var = lData.Smooth_Var; */
        /*  Tessellation_flag = lData.Tessellation_flag; */
        /*  Tessellation_levels = lData.Tessellation_levels; */
        /*  TwoPeak_Flags = lData.TwoPeak_Flag; */
        /*  UseHistogramOri = lData.UseHistogramOri; */
        /*  Allow 3DSIFT to throw out points, Default: 1 */
        /*  Min: 1  Default: 2  */
        /*  Display a sphere which can be rotated (Rotate 3D button) to view gradient directions */
        /*  Keep this as 1 */
        /*  Min: zero  Default: 1 */
        /*  Number of faces in the tessellation, not a parameter */
        /*  Adds gradient data to surrounding bins in final histogram */
        /*  Determines amount of smoothing, Default: 20 */
        /*  The rest of the variables are not modified often, but are included here */
        /*  for completeness sake */
        if ((r < 1) || (r > pix->size[0]) || (c < 1) || (c > pix->size[1]) || (t
             < 1) || (t > pix->size[2])) {
        } else {
          d_st.site = &sd_emlrtRSI;
          GetGradOri_vector(&d_st, pix, r, c, t, &grad, vect);
          d_st.site = &td_emlrtRSI;
          PlaceInIndex(&d_st, b_index, muDoubleScalarExp(-(distsq / 50.0)) *
                       grad, vect, i_indx, j_indx, s_indx, fv_centers_data);
        }

        s++;
        if (*emlrtBreakCheckR2012bFlagVar != 0) {
          emlrtBreakCheckR2012b(&b_st);
        }
      }

      j++;
      if (*emlrtBreakCheckR2012bFlagVar != 0) {
        emlrtBreakCheckR2012b(&b_st);
      }
    }

    i++;
    if (*emlrtBreakCheckR2012bFlagVar != 0) {
      emlrtBreakCheckR2012b(&b_st);
    }
  }

  /*  % Method 2 */
  /*  index = KeySample2D(key, grad, ori, scale, row, col); */
  /*  vec = index(:); */
  /*  % Method 3 */
  /*  n = 0; */
  /*  orig_frame = key.frame; */
  /*  for t_offset=-4:4 */
  /*      key.frame = orig_frame + t_offset; */
  /*      index = KeySample2D(key, grad, ori, scale, row, col); */
  /*      vec_temp = index(:); */
  /*      n = n + 1; */
  /*      vec((n-1)*length(vec_temp)+1:n*length(vec_temp)) = vec_temp; */
  /*  end */
  /*  key.frame = orig_frame; */
  /*  vec = vec'; */
  /*  % Method 4 */
  /*  index = KeySample2D(key, grad, ori, scale, row, col); */
  /*  index = KeySample2Dxt(key, grad, ori, scale, row, col); */
  /*  index = KeySample2Dyt(key, grad, ori, scale, row, col); */
  memcpy(&vec[0], &b_index[0], 640U * sizeof(real_T));
  st.site = &id_emlrtRSI;
  NormalizeVec(&st, vec);
  b_i = 0;
  while (b_i < 640) {
    if (vec[b_i] > 0.2) {
      vec[b_i] = 0.2;
      changed = 1;
    }

    b_i++;
    if (*emlrtBreakCheckR2012bFlagVar != 0) {
      emlrtBreakCheckR2012b(sp);
    }
  }

  if (changed != 0) {
    st.site = &jd_emlrtRSI;
    NormalizeVec(&st, vec);
  }

  b_i = 0;
  while (b_i < 640) {
    d1 = muDoubleScalarRound(512.0 * vec[b_i]);
    if (d1 < 32768.0) {
      if (d1 >= -32768.0) {
        a = (int16_T)d1;
      } else {
        a = MIN_int16_T;
      }
    } else if (d1 >= 32768.0) {
      a = MAX_int16_T;
    } else {
      a = 0;
    }

    intval = a;
    if (!(intval >= 0)) {
      for (i19 = 0; i19 < 36; i19++) {
        b_u[i19] = cv6[i19];
      }

      b_y = NULL;
      m8 = emlrtCreateCharArray(2, iv11);
      emlrtInitCharArrayR2013a(sp, 36, m8, &b_u[0]);
      emlrtAssign(&b_y, m8);
      st.site = &be_emlrtRSI;
      disp(&st, b_y, &e_emlrtMCI);
    }

    if (255 > intval) {
      a = intval;
    } else {
      a = 255;
    }

    if (a < 0) {
      a = 0;
    } else {
      if (a > 255) {
        a = 255;
      }
    }

    key->ivec[b_i] = a;
    b_i++;
    if (*emlrtBreakCheckR2012bFlagVar != 0) {
      emlrtBreakCheckR2012b(sp);
    }
  }

  emlrtHeapReferenceStackLeaveFcnR2012b(sp);
}

/* End of code generation (MakeKeypoint.c) */
