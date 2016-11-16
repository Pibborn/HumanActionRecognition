/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: sphere_tri.c
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 16-Nov-2016 14:15:56
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "Create_Descriptor.h"
#include "sphere_tri.h"
#include "mesh_refine_tri4.h"
#include "Create_Descriptor_emxutil.h"
#include "cos.h"
#include "sin.h"
#include "atan2.h"
#include "power.h"
#include <stdio.h>

/* Function Definitions */

/*
 * Arguments    : emxArray_real_T *FV_vertices
 *                double FV_faces_data[]
 *                int FV_faces_size[2]
 *                double FV_centers_data[]
 *                int FV_centers_size[2]
 * Return Type  : void
 */
void sphere_tri(emxArray_real_T *FV_vertices, double FV_faces_data[], int
                FV_faces_size[2], double FV_centers_data[], int FV_centers_size
                [2])
{
  double ico_v[36];
  int iy;
  static const double dv0[3] = { 0.8506508084, 0.5257311121, 0.0 };

  static const double dv1[3] = { -0.8506508084, 0.5257311121, 0.0 };

  static const double dv2[3] = { -0.8506508084, -0.5257311121, 0.0 };

  static const double dv3[3] = { 0.8506508084, -0.5257311121, 0.0 };

  static const double dv4[3] = { 0.5257311121, 0.0, 0.8506508084 };

  static const double dv5[3] = { 0.5257311121, 0.0, -0.8506508084 };

  static const double dv6[3] = { -0.5257311121, 0.0, -0.8506508084 };

  static const double dv7[3] = { -0.5257311121, 0.0, 0.8506508084 };

  static const double dv8[3] = { 0.0, 0.8506508084, 0.5257311121 };

  static const double dv9[3] = { 0.0, -0.8506508084, 0.5257311121 };

  static const double dv10[3] = { 0.0, -0.8506508084, -0.5257311121 };

  static const double dv11[3] = { 0.0, 0.8506508084, -0.5257311121 };

  signed char ico_f[60];
  static const signed char iv0[60] = { 5, 5, 6, 6, 1, 1, 3, 3, 9, 9, 10, 10, 9,
    12, 5, 6, 8, 7, 8, 7, 8, 10, 12, 7, 4, 6, 2, 7, 12, 2, 4, 11, 1, 6, 4, 11, 2,
    12, 10, 3, 9, 8, 7, 11, 5, 4, 8, 2, 1, 12, 11, 3, 5, 1, 10, 4, 9, 2, 3, 11 };

  emxArray_real_T *vertices;
  double F2_data[240];
  double B_data[3];
  double C_data[3];
  emxArray_real_T *b_vertices;
  emxArray_real_T *c_vertices;
  int f;
  double A_data[3];
  int A_size[2];
  double centers_data[3];
  int Na_size[1];
  double Na_data[1];
  int B_size[2];
  double Nb_data[1];
  int C_size[2];
  double Nc_data[1];
  double temp[3];
  int k;
  emxArray_real_T *X;
  emxArray_real_T *Y;
  emxArray_real_T *theta;
  emxArray_real_T *x;
  emxArray_real_T *d_vertices;
  int ixstart;
  int ix;
  double b_centers_data[240];
  int i;
  signed char b_A_size[2];
  int b_i;
  double s;

  /*  sphere_tri - generate a triangle mesh approximating a sphere */
  /*  */
  /*  Usage: FV = sphere_tri(shape,Nrecurse,r,winding) */
  /*  */
  /*    shape is a string, either of the following: */
  /*    'ico'   starts with icosahedron (most even, default) */
  /*    'oct'   starts with octahedron */
  /*    'tetra' starts with tetrahedron (least even) */
  /*  */
  /*    Nrecurse is int >= 0, setting the recursions (default 0) */
  /*  */
  /*    r is the radius of the sphere (default 1) */
  /*  */
  /*    winding is 0 for clockwise, 1 for counterclockwise (default 0).  The */
  /*    matlab patch command gives outward surface normals for clockwise */
  /*    order of vertices in the faces (viewed from outside the surface). */
  /*  */
  /*    FV has fields FV.vertices and FV.faces.  The vertices */
  /*    are listed in clockwise order in FV.faces, as viewed */
  /*    from the outside in a RHS coordinate system. */
  /*  */
  /*  The function uses recursive subdivision.  The first */
  /*  approximation is an platonic solid, either an  icosahedron, */
  /*  octahedron or a tetrahedron.  Each level of refinement */
  /*  subdivides each triangle face by a factor of 4 (see also */
  /*  mesh_refine).  At each refinement, the vertices are */
  /*  projected to the sphere surface (see sphere_project). */
  /*  */
  /*  A recursion level of 3 or 4 is a good sphere surface, if */
  /*  gouraud shading is used for rendering. */
  /*  */
  /*  The returned struct can be used in the patch command, eg: */
  /*  */
  /*  % create and plot, vertices: [2562x3] and faces: [5120x3] */
  /*  FV = sphere_tri('ico',4,1); */
  /*  lighting phong; shading interp; figure; */
  /*  patch('vertices',FV.vertices,'faces',FV.faces,... */
  /*        'facecolor',[1 0 0],'edgecolor',[.2 .2 .6]); */
  /*  axis off; camlight infinite; camproj('perspective'); */
  /*  */
  /*  See also: mesh_refine, sphere_project */
  /*  */
  /*  $Revision: 1.2 $ $Date: 2005/07/20 23:07:03 $ */
  /*  Licence:  GNU GPL, no implied or express warranties */
  /*  Jon Leech (leech @ cs.unc.edu) 3/24/89 */
  /*  icosahedral code added by Jim Buddenhagen (jb1556@daditz.sbc.com) 5/93 */
  /*  06/2002, adapted from c to matlab by Darren.Weber_at_radiology.ucsf.edu */
  /*  05/2004, reorder of the faces for the 'ico' surface so they are indeed */
  /*  clockwise!  Now the surface normals are directed outward.  Also reset the */
  /*  default recursions to zero, so we can get out just the platonic solids. */
  /*  */
  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
  /* eegversion = '$Revision: 1.2 $'; */
  /*  fprintf('SPHERE_TRI [v %s]\n',eegversion(11:15)); tic */
  /* { */
  /* if size(varargin,2) < 1 */
  /*     shape = 'ico'; */
  /*     maxlevel = 0; */
  /*     r = 1; */
  /*     winding = 0; */
  /* elseif size(varargin,2) < 2 */
  /*     maxlevel = 0; */
  /*     r = 1; */
  /*     winding = 0; */
  /* elseif size(varargin,2) < 3 */
  /*     r = 1; */
  /*     winding = 0; */
  /* else */
  /*     winding = 0; */
  /* end */
  /* } */
  /* { */
  /* if ~exist('shape','var') || isempty(shape), */
  /*     shape = 'ico'; */
  /* end */
  /*  fprintf('...creating sphere tesselation based on %s\n',shape); */
  /*  */
  /*  default maximum subdivision level */
  /* if ~exist('maxlevel','var') || isempty(maxlevel) || maxlevel < 0, */
  /*     maxlevel = 0; */
  /* end */
  /*  */
  /*  default radius */
  /* if ~exist('r','var') || isempty(r), */
  /*     r = 1; */
  /* end */
  /*  */
  /* if ~exist('winding','var') || isempty(winding), */
  /*     winding = 0; */
  /* end */
  /* } */
  /*  ----------------- */
  /*  define the starting shapes */
  /*  Twelve vertices of icosahedron on unit sphere */
  /*  t=(1+sqrt(5))/2, tau=t/sqrt(1+t^2) */
  /*  one=1/sqrt(1+t^2) , unit sphere */
  /*  ZA */
  /*  ZB */
  /*  ZC */
  /*  ZD */
  /*  YA */
  /*  YB */
  /*  YC */
  /*  YD */
  /*  XA */
  /*  XB */
  /*  XC */
  for (iy = 0; iy < 3; iy++) {
    ico_v[12 * iy] = dv0[iy];
    ico_v[1 + 12 * iy] = dv1[iy];
    ico_v[2 + 12 * iy] = dv2[iy];
    ico_v[3 + 12 * iy] = dv3[iy];
    ico_v[4 + 12 * iy] = dv4[iy];
    ico_v[5 + 12 * iy] = dv5[iy];
    ico_v[6 + 12 * iy] = dv6[iy];
    ico_v[7 + 12 * iy] = dv7[iy];
    ico_v[8 + 12 * iy] = dv8[iy];
    ico_v[9 + 12 * iy] = dv9[iy];
    ico_v[10 + 12 * iy] = dv10[iy];
    ico_v[11 + 12 * iy] = dv11[iy];
  }

  /*  XD */
  /*  Structure for unit icosahedron */
  for (iy = 0; iy < 60; iy++) {
    ico_f[iy] = iv0[iy];
  }

  emxInit_real_T(&vertices, 2);

  /*  ----------------- */
  /*  refine the starting shapes with subdivisions */
  /*  Subdivide each starting triangle (maxlevel) times */
  /*  Subdivide each triangle and normalize the new points thus */
  /*  generated to lie on the surface of a sphere radius r. */
  iy = vertices->size[0] * vertices->size[1];
  vertices->size[0] = 12;
  vertices->size[1] = 3;
  emxEnsureCapacity((emxArray__common *)vertices, iy, (int)sizeof(double));
  for (iy = 0; iy < 36; iy++) {
    vertices->data[iy] = ico_v[iy];
  }

  /*  mesh_refine_tri4 - creates 4 triangle from each triangle of a mesh */
  /*  */
  /*  [ FV ] = mesh_refine_tri4( FV ) */
  /*  */
  /*  FV.vertices   - mesh vertices (Nx3 matrix) */
  /*  FV.faces      - faces with indices into 3 rows */
  /*                  of FV.vertices (Mx3 matrix) */
  /*  */
  /*  For each face, 3 new vertices are created at the */
  /*  triangle edge midpoints.  Each face is divided into 4 */
  /*  faces and returned in FV. */
  /*  */
  /*         B */
  /*        /\ */
  /*       /  \ */
  /*     a/____\b       Construct new triangles */
  /*     /\    /\       [A,a,c] */
  /*    /  \  /  \      [a,B,b] */
  /*   /____\/____\     [c,b,C] */
  /*  A         c       C    [a,b,c] */
  /*  */
  /*  It is assumed that the vertices are listed in clockwise order in */
  /*  FV.faces (A,B,C above), as viewed from the outside in a RHS coordinate */
  /*  system. */
  /*  */
  /*  See also: mesh_refine, sphere_tri, sphere_project */
  /*  */
  /*  ---this method is not implemented, but the idea here remains... */
  /*  This can be done until some minimal distance (D) of the mean */
  /*  distance between vertices of all triangles is achieved.  If */
  /*  no D argument is given, the function refines the mesh once. */
  /*  Alternatively, it could be done until some minimum mean */
  /*  area of faces is achieved.  As is, it just refines once. */
  /*  $Revision: 1.1 $ $Date: 2004/11/12 01:32:35 $ */
  /*  Licence:  GNU GPL, no implied or express warranties */
  /*  History:  05/2002, Darren.Weber_at_radiology.ucsf.edu, created */
  /*  */
  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
  /*  tic; */
  /*  fprintf('...refining mesh (tri4)...') */
  /*  NOTE */
  /*  The centroid is located one third of the way from each vertex to */
  /*  the midpoint of the opposite side. Each median divides the triangle */
  /*  into two equal areas; all the medians together divide it into six */
  /*  equal parts, and the lines from the median point to the vertices */
  /*  divide the whole into three equivalent triangles. */
  /*  Each input triangle with vertices labelled [A,B,C] as shown */
  /*  below will be turned into four new triangles: */
  /*  */
  /*  Make new midpoints */
  /*  a = (A+B)/2 */
  /*  b = (B+C)/2 */
  /*  c = (C+A)/2 */
  /*  */
  /*         B */
  /*        /\ */
  /*       /  \ */
  /*     a/____\b       Construct new triangles */
  /*     /\    /\       [A,a,c] */
  /*    /  \  /  \      [a,B,b] */
  /*   /____\/____\     [c,b,C] */
  /*  A      c     C    [a,b,c] */
  /*  */
  /*  Initialise a new vertices and faces matrix */
  memset(&F2_data[0], 0, 240U * sizeof(double));
  emxInit_real_T(&b_vertices, 2);
  emxInit_real_T(&c_vertices, 2);
  for (f = 0; f < 20; f++) {
    /*  Get the triangle vertex indices */
    /*  Get the triangle vertex coordinates */
    for (iy = 0; iy < 3; iy++) {
      A_data[iy] = ico_v[(ico_f[f] + 12 * iy) - 1];
      B_data[iy] = ico_v[(ico_f[20 + f] + 12 * iy) - 1];
      C_data[iy] = ico_v[(ico_f[40 + f] + 12 * iy) - 1];
    }

    /*  Now find the midpoints between vertices */
    /*  Find the length of each median */
    /* A2blen = sqrt ( sum( (A - b).^2, 2 ) ); */
    /* B2clen = sqrt ( sum( (B - c).^2, 2 ) ); */
    /* C2alen = sqrt ( sum( (C - a).^2, 2 ) ); */
    /*  Store the midpoint vertices, while */
    /*  checking if midpoint vertex already exists */
    /* 5 Just a initialization */
    A_size[0] = 1;
    A_size[1] = 3;
    for (iy = 0; iy < 3; iy++) {
      centers_data[iy] = (A_data[iy] + B_data[iy]) / 2.0;
    }

    mesh_find_vertex(vertices, centers_data, A_size, b_vertices, Na_data,
                     Na_size);
    B_size[0] = 1;
    B_size[1] = 3;
    for (iy = 0; iy < 3; iy++) {
      centers_data[iy] = (B_data[iy] + C_data[iy]) / 2.0;
    }

    mesh_find_vertex(b_vertices, centers_data, B_size, c_vertices, Nb_data,
                     Na_size);
    C_size[0] = 1;
    C_size[1] = 3;
    for (iy = 0; iy < 3; iy++) {
      centers_data[iy] = (C_data[iy] + A_data[iy]) / 2.0;
    }

    mesh_find_vertex(c_vertices, centers_data, C_size, vertices, Nc_data,
                     Na_size);
    temp[0] = Na_data[0];
    temp[1] = Nb_data[0];
    temp[2] = Nc_data[0];

    /*  Create new faces with orig vertices plus midpoints */
    iy = ((1 + f) << 2) - 4;
    F2_data[iy] = ico_f[f];
    F2_data[iy + 80] = Na_data[0];
    F2_data[iy + 160] = Nc_data[0];
    iy = ((1 + f) << 2) - 3;
    F2_data[iy] = Na_data[0];
    F2_data[iy + 80] = ico_f[20 + f];
    F2_data[iy + 160] = Nb_data[0];
    iy = ((1 + f) << 2) - 2;
    F2_data[iy] = Nc_data[0];
    F2_data[iy + 80] = Na_data[0];
    F2_data[iy + 160] = ico_f[40 + f];
    iy = (1 + f) << 2;
    for (k = 0; k < 3; k++) {
      F2_data[(iy + 80 * k) - 1] = temp[k];
    }

    /*     %{ */
    /*     F2(f*4-3,1) = NA; */
    /*     F2(f*4-3,2) = Na; */
    /*     F2(f*4-3,3) = Nc; */
    /*      */
    /*     F2(f*4-2,1) = Na; */
    /*     F2(f*4-2,2) = NB; */
    /*     F2(f*4-2,3) = Nb; */
    /*      */
    /*     F2(f*4-1,1) = Nc; */
    /*     F2(f*4-1,2) = Nb; */
    /*     F2(f*4-1,3) = NC; */
    /*      */
    /*     F2(f*4-0,1) = Na; */
    /*     F2(f*4-0,2) = Nb; */
    /*     F2(f*4-0,3) = Nc; */
    /*     %} */
  }

  emxFree_real_T(&c_vertices);
  emxFree_real_T(&b_vertices);
  emxInit_real_T1(&X, 1);

  /*  Replace the faces matrix */
  /*  t=toc; fprintf('done (%5.2f sec)\n',t); */
  /*  FV.vertices = sphere_project(FV.vertices,r); */
  /*  sphere_project - project point X,Y,Z to the surface of sphere radius r */
  /*  */
  /*  V = sphere_project(v,r,c) */
  /*  */
  /*  Cartesian inputs: */
  /*  v is the vertex matrix, Nx3 (XYZ) */
  /*  r is the sphere radius, 1x1 (default 1) */
  /*  c is the sphere centroid, 1x3 (default 0,0,0) */
  /*  */
  /*  XYZ are converted to spherical coordinates and their radius is */
  /*  adjusted according to r, from c toward XYZ (defined with theta,phi) */
  /*  */
  /*  V is returned as Cartesian 3D coordinates */
  /*  */
  /*  $Revision: 1.1 $ $Date: 2004/11/12 01:32:36 $ */
  /*  Licence:  GNU GPL, no implied or express warranties */
  /*  History:  06/2002, Darren.Weber_at_radiology.ucsf.edu, created */
  /*  */
  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
  /* { */
  /* if ~exist('v','var'), */
  /*     msg = sprintf('SPHERE_PROJECT: No input vertices (X,Y,Z)\n'); */
  /*     error(msg); */
  /* end */
  /* } */
  k = vertices->size[0];
  iy = X->size[0];
  X->size[0] = k;
  emxEnsureCapacity((emxArray__common *)X, iy, (int)sizeof(double));
  for (iy = 0; iy < k; iy++) {
    X->data[iy] = vertices->data[iy];
  }

  emxInit_real_T1(&Y, 1);
  k = vertices->size[0];
  iy = Y->size[0];
  Y->size[0] = k;
  emxEnsureCapacity((emxArray__common *)Y, iy, (int)sizeof(double));
  for (iy = 0; iy < k; iy++) {
    Y->data[iy] = vertices->data[iy + vertices->size[0]];
  }

  emxInit_real_T1(&theta, 1);
  emxInit_real_T1(&x, 1);

  /* { */
  /* if ~exist('c','var'), */
  /*     xo = 0; */
  /*     yo = 0; */
  /*     zo = 0; */
  /* else */
  /*     xo = c(1); */
  /*     yo = c(2); */
  /*     zo = c(3); */
  /* end */
  /*  */
  /* if ~exist('r','var'), r = 1; end */
  /* } */
  /*  alternate method is to use unit vector of V */
  /*  [ n = 'magnitude(V)'; unitV = V ./ n; ] */
  /*  to change the radius, multiply the unitV */
  /*  by the radius required.  This avoids the */
  /*  use of arctan functions, which have branches. */
  /*  Convert Cartesian X,Y,Z to spherical (radians) */
  b_atan2(Y, X, theta);
  power(X, x);
  power(Y, X);
  iy = x->size[0];
  emxEnsureCapacity((emxArray__common *)x, iy, (int)sizeof(double));
  k = x->size[0];
  for (iy = 0; iy < k; iy++) {
    x->data[iy] += X->data[iy];
  }

  iy = X->size[0];
  X->size[0] = x->size[0];
  emxEnsureCapacity((emxArray__common *)X, iy, (int)sizeof(double));
  k = x->size[0];
  for (iy = 0; iy < k; iy++) {
    X->data[iy] = x->data[iy];
  }

  for (k = 0; k + 1 <= x->size[0]; k++) {
    X->data[k] = sqrt(X->data[k]);
  }

  emxInit_real_T1(&d_vertices, 1);
  k = vertices->size[0];
  iy = d_vertices->size[0];
  d_vertices->size[0] = k;
  emxEnsureCapacity((emxArray__common *)d_vertices, iy, (int)sizeof(double));
  for (iy = 0; iy < k; iy++) {
    d_vertices->data[iy] = vertices->data[iy + (vertices->size[0] << 1)];
  }

  b_atan2(X, d_vertices, Y);

  /*  do not calc: r = sqrt( (X-xo).^2 + (Y-yo).^2 + (Z-zo).^2); */
  /*    Recalculate X,Y,Z for constant r, given theta & phi. */
  iy = x->size[0];
  x->size[0] = Y->size[0];
  emxEnsureCapacity((emxArray__common *)x, iy, (int)sizeof(double));
  k = Y->size[0];
  emxFree_real_T(&d_vertices);
  for (iy = 0; iy < k; iy++) {
    x->data[iy] = Y->data[iy];
  }

  b_sin(x);
  iy = X->size[0];
  X->size[0] = theta->size[0];
  emxEnsureCapacity((emxArray__common *)X, iy, (int)sizeof(double));
  k = theta->size[0];
  for (iy = 0; iy < k; iy++) {
    X->data[iy] = theta->data[iy];
  }

  b_cos(X);
  iy = x->size[0];
  emxEnsureCapacity((emxArray__common *)x, iy, (int)sizeof(double));
  k = x->size[0];
  for (iy = 0; iy < k; iy++) {
    x->data[iy] *= X->data[iy];
  }

  iy = X->size[0];
  X->size[0] = Y->size[0];
  emxEnsureCapacity((emxArray__common *)X, iy, (int)sizeof(double));
  k = Y->size[0];
  for (iy = 0; iy < k; iy++) {
    X->data[iy] = Y->data[iy];
  }

  b_sin(X);
  b_sin(theta);
  iy = X->size[0];
  emxEnsureCapacity((emxArray__common *)X, iy, (int)sizeof(double));
  k = X->size[0];
  for (iy = 0; iy < k; iy++) {
    X->data[iy] *= theta->data[iy];
  }

  emxFree_real_T(&theta);
  b_cos(Y);
  iy = Y->size[0];
  emxEnsureCapacity((emxArray__common *)Y, iy, (int)sizeof(double));
  k = x->size[0];
  ixstart = X->size[0];
  ix = Y->size[0];
  iy = vertices->size[0] * vertices->size[1];
  vertices->size[0] = k;
  vertices->size[1] = 3;
  emxEnsureCapacity((emxArray__common *)vertices, iy, (int)sizeof(double));
  for (iy = 0; iy < k; iy++) {
    vertices->data[iy] = x->data[iy];
  }

  emxFree_real_T(&x);
  for (iy = 0; iy < ixstart; iy++) {
    vertices->data[iy + vertices->size[0]] = X->data[iy];
  }

  emxFree_real_T(&X);
  for (iy = 0; iy < ix; iy++) {
    vertices->data[iy + (vertices->size[0] << 1)] = Y->data[iy];
  }

  emxFree_real_T(&Y);

  /*  An alternative might be to define a min distance */
  /*  between vertices and recurse or use fminsearch */
  memset(&b_centers_data[0], 0, 240U * sizeof(double));
  for (i = 0; i < 80; i++) {
    for (iy = 0; iy < 2; iy++) {
      b_A_size[iy] = (signed char)(1 + (iy << 1));
    }

    ix = -1;
    iy = -1;
    for (b_i = 0; b_i < 3; b_i++) {
      ixstart = ix;
      ix++;
      s = vertices->data[((int)F2_data[i + 80 * ((ixstart + 1) % 3)] +
                          vertices->size[0] * ((ixstart + 1) / 3)) - 1];
      for (k = 0; k < 2; k++) {
        ix++;
        s += vertices->data[((int)F2_data[i + 80 * (ix % 3)] + vertices->size[0]
                             * (ix / 3)) - 1];
      }

      iy++;
      A_data[iy] = s;
    }

    for (iy = 0; iy < 3; iy++) {
      b_centers_data[i + 80 * iy] = A_data[b_A_size[0] * iy] / 3.0;
    }

    /*  Unit Normalization */
    s = 0.0;
    for (k = 0; k < 3; k++) {
      s += b_centers_data[i + 80 * k] * b_centers_data[i + 80 * k];
    }

    s = sqrt(s);
    for (iy = 0; iy < 3; iy++) {
      centers_data[iy] = b_centers_data[i + 80 * iy] / s;
    }

    for (iy = 0; iy < 3; iy++) {
      b_centers_data[i + 80 * iy] = centers_data[iy];
    }
  }

  /*      fprintf('...returning clockwise vertex order (viewed from outside)\n'); */
  /*  t=toc; fprintf('...done (%6.2f sec)\n\n',t); */
  iy = FV_vertices->size[0] * FV_vertices->size[1];
  FV_vertices->size[0] = vertices->size[0];
  FV_vertices->size[1] = 3;
  emxEnsureCapacity((emxArray__common *)FV_vertices, iy, (int)sizeof(double));
  k = vertices->size[0] * vertices->size[1];
  for (iy = 0; iy < k; iy++) {
    FV_vertices->data[iy] = vertices->data[iy];
  }

  emxFree_real_T(&vertices);
  FV_faces_size[0] = 80;
  FV_faces_size[1] = 3;
  for (iy = 0; iy < 240; iy++) {
    FV_faces_data[iy] = F2_data[iy];
  }

  FV_centers_size[0] = 80;
  FV_centers_size[1] = 3;
  for (iy = 0; iy < 240; iy++) {
    FV_centers_data[iy] = b_centers_data[iy];
  }
}

/*
 * File trailer for sphere_tri.c
 *
 * [EOF]
 */
