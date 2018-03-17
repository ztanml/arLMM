/*
 * MATLAB Compiler: 6.5 (R2017b)
 * Date: Sat Mar 17 15:12:57 2018
 * Arguments:
 * "-B""macro_default""-W""lib:libarLMM""-T""link:lib""-d""/home/eric/src/arLMM/
 */

#ifndef __libarLMM_h
#define __libarLMM_h 1

#if defined(__cplusplus) && !defined(mclmcrrt_h) && defined(__linux__)
#  pragma implementation "mclmcrrt.h"
#endif
#include "mclmcrrt.h"
#ifdef __cplusplus
extern "C" {
#endif

/* This symbol is defined in shared libraries. Define it here
 * (to nothing) in case this isn't a shared library. 
 */
#ifndef LIB_libarLMM_C_API 
#define LIB_libarLMM_C_API /* No special import/export declaration */
#endif

/* GENERAL LIBRARY FUNCTIONS -- START */

extern LIB_libarLMM_C_API 
bool MW_CALL_CONV libarLMMInitializeWithHandlers(
       mclOutputHandlerFcn error_handler, 
       mclOutputHandlerFcn print_handler);

extern LIB_libarLMM_C_API 
bool MW_CALL_CONV libarLMMInitialize(void);

extern LIB_libarLMM_C_API 
void MW_CALL_CONV libarLMMTerminate(void);

extern LIB_libarLMM_C_API 
void MW_CALL_CONV libarLMMPrintStackTrace(void);

/* GENERAL LIBRARY FUNCTIONS -- END */

/* C INTERFACE -- MLX WRAPPERS FOR USER-DEFINED MATLAB FUNCTIONS -- START */

extern LIB_libarLMM_C_API 
bool MW_CALL_CONV mlxArLMM(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[]);

/* C INTERFACE -- MLX WRAPPERS FOR USER-DEFINED MATLAB FUNCTIONS -- END */

/* C INTERFACE -- MLF WRAPPERS FOR USER-DEFINED MATLAB FUNCTIONS -- START */

extern LIB_libarLMM_C_API bool MW_CALL_CONV mlfArLMM(int nargout, mxArray** Beta, mxArray** c, mxArray** Gamma, mxArray** H, mxArray** s2, mxArray** cr, mxArray* X, mxArray* y, mxArray* Z, mxArray* varargin);

#ifdef __cplusplus
}
#endif
/* C INTERFACE -- MLF WRAPPERS FOR USER-DEFINED MATLAB FUNCTIONS -- END */

#endif
