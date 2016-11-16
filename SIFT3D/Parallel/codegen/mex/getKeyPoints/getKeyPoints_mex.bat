@echo off
set MATLAB=C:\PROGRA~1\MATLAB\R2015b
set MATLAB_ARCH=win64
set MATLAB_BIN="C:\Program Files\MATLAB\R2015b\bin"
set ENTRYPOINT=mexFunction
set OUTDIR=.\
set LIB_NAME=getKeyPoints_mex
set MEX_NAME=getKeyPoints_mex
set MEX_EXT=.mexw64
call setEnv.bat
echo # Make settings for getKeyPoints > getKeyPoints_mex.mki
echo COMPILER=%COMPILER%>> getKeyPoints_mex.mki
echo COMPFLAGS=%COMPFLAGS%>> getKeyPoints_mex.mki
echo OPTIMFLAGS=%OPTIMFLAGS%>> getKeyPoints_mex.mki
echo DEBUGFLAGS=%DEBUGFLAGS%>> getKeyPoints_mex.mki
echo LINKER=%LINKER%>> getKeyPoints_mex.mki
echo LINKFLAGS=%LINKFLAGS%>> getKeyPoints_mex.mki
echo LINKOPTIMFLAGS=%LINKOPTIMFLAGS%>> getKeyPoints_mex.mki
echo LINKDEBUGFLAGS=%LINKDEBUGFLAGS%>> getKeyPoints_mex.mki
echo MATLAB_ARCH=%MATLAB_ARCH%>> getKeyPoints_mex.mki
echo BORLAND=%BORLAND%>> getKeyPoints_mex.mki
echo OMPFLAGS= >> getKeyPoints_mex.mki
echo OMPLINKFLAGS= >> getKeyPoints_mex.mki
echo EMC_COMPILER=mingw64>> getKeyPoints_mex.mki
echo EMC_CONFIG=optim>> getKeyPoints_mex.mki
"C:\Program Files\MATLAB\R2015b\bin\win64\gmake" -B -f getKeyPoints_mex.mk
