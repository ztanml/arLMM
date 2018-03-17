// Subsampled randomized Hadamard transform

#include <time.h>
#include "tran_srht.h"
#include "mex.h"

/* The gateway function */
void mexFunction( int nlhs, mxArray *plhs[],
                  int nrhs, const mxArray *prhs[] )
{
  size_t m, n, p, u;
  double *X, *rin;
  double *S, *rout, *idx;

    /* check for proper number of arguments */
    if(nrhs != 3) {
        mexErrMsgIdAndTxt("arLMM:srht:nrhs","Three inputs required.");
    }

    if(nlhs != 3) {
        mexErrMsgIdAndTxt("arLMM:srht:nlhs","Three output required.");
    }

    /* make sure the first input argument is a double matrix */
    if( !mxIsDouble(prhs[0]) ) {
      mexErrMsgIdAndTxt("arLMM:srht:notDouble","Data matrix must be a double matrix.");
    }

    /* check that number of rows in second input argument is 1 */
    n = mxGetM(prhs[0]);
    p = mxGetN(prhs[0]);
    if ( n & (n-1) ) {
        mexErrMsgIdAndTxt("arLMM:srht:PowerOfTwoRows",
			  "Data matrix must have a power-of-two number of rows.");
    }

    /* second input is either empty or double matrix with correct dimensions */
    if( mxGetNumberOfElements(prhs[1]) && (!mxIsDouble(prhs[1]) ||
	mxGetN(prhs[1]) != 1 ||
	mxGetM(prhs[1]) != n )) {
        mexErrMsgIdAndTxt("arLMM:srht:RademacherDim","Rademacher vector dimension error.");
    }
    
    /* make sure the third input argument is a scalar */
    if( !mxIsDouble(prhs[2]) ||
	mxGetNumberOfElements(prhs[2]) != 1) {
        mexErrMsgIdAndTxt("arLMM:srht:m","Subsampled row count type error.");
    }

    m = mxGetScalar(prhs[2]);
    if (m > n) {
        mexErrMsgIdAndTxt("arLMM:srht:m",
			  "Subsampled row count cannot exceed the total number of rows.");
    }
    
    /* create a pointer to the real data in the input matrix  */
    X = mxGetPr(prhs[0]);
    rin = mxGetNumberOfElements(prhs[1])? mxGetPr(prhs[1]): NULL;

    /* create the output matrix */
    plhs[0] = mxCreateDoubleMatrix(n, p, mxREAL);
    plhs[1] = mxCreateDoubleMatrix(n, 1, mxREAL);
    plhs[2] = mxCreateDoubleMatrix(n, 1, mxREAL);

    /* get a pointer to the real data in the output matrix */
    S    = mxGetPr(plhs[0]);
    rout = mxGetPr(plhs[1]);
    idx  = mxGetPr(plhs[2]);

    for (u = 0; u < n; ++u)
      idx[u] = u + 1;

    if (srht(X, rin, m, n, p, time(NULL), S, rout, idx))
      mexErrMsgIdAndTxt("arLMM:srht:Computation", "SRHT computation failed.");
}
