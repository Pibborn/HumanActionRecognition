@echo off
set MATLAB=C:\PROGRA~1\MATLAB\R2015b
set MATLAB_ARCH=win64
set MATLAB_BIN="C:\Program Files\MATLAB\R2015b\bin"
set ENTRYPOINT=mexFunction
set OUTDIR=.\
set LIB_NAME=Create_Descriptor_mex
set MEX_NAME=Create_Descriptor_mex
set MEX_EXT=.mexw64
call setEnv.bat
echo # Make settings for Create_Descriptor > Create_Descriptor_mex.mki
echo COMPILER=%COMPILER%>> Create_Descriptor_mex.mki
echo COMPFLAGS=%COMPFLAGS%>> Create_Descriptor_mex.mki
echo OPTIMFLAGS=%OPTIMFLAGS%>> Create_Descriptor_mex.mki
echo DEBUGFLAGS=%DEBUGFLAGS%>> Create_Descriptor_mex.mki
echo LINKER=%LINKER%>> Create_Descriptor_mex.mki
echo LINKFLAGS=%LINKFLAGS%>> Create_Descriptor_mex.mki
echo LINKOPTIMFLAGS=%LINKOPTIMFLAGS%>> Create_Descriptor_mex.mki
echo LINKDEBUGFLAGS=%LINKDEBUGFLAGS%>> Create_Descriptor_mex.mki
echo MATLAB_ARCH=%MATLAB_ARCH%>> Create_Descriptor_mex.mki
echo BORLAND=%BORLAND%>> Create_Descriptor_mex.mki
echo OMPFLAGS= >> Create_Descriptor_mex.mki
echo OMPLINKFLAGS= >> Create_Descriptor_mex.mki
echo EMC_COMPILER=mingw64>> Create_Descriptor_mex.mki
echo EMC_CONFIG=optim>> Create_Descriptor_mex.mki
"C:\Program Files\MATLAB\R2015b\bin\win64\gmake" -B -f Create_Descriptor_mex.mk
