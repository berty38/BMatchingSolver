/*!
 * BMatchingSolverMex
 * Bert Huang
 */

#include <iostream>
#include <math.h>
#include "mex.h"
#include "BMatchingLibrary.h"
#include "SparseMatrix.h"
#include "utils.h"

using namespace std;
using namespace bmatchingLibrary;

double ** getMatrix(const mxArray *pm) {
    double ** A;
    double * matrix = mxGetPr(pm);
    int m = mxGetM(pm);
    int n = mxGetN(pm);
   
    if (m == 0)
        return 0;
    
    A = new double*[m];
    
    for (int i = 0; i < m; i++)
        A[i] = new double[n];
    
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            A[i][j] = matrix[j*m+i];
    
    return A;
}

void deleteMatrix(double ** A, int size) {
    for (int i = 0; i < size; i++)
        delete[](A[i]);
    delete[](A);
}

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    int weightType = 0, d = 0, m = 0, n = 0, cacheSize = 0, 
            wsize = 0, xsize = 0, ysize = 0;
    double ** W = 0, ** X = 0, ** Y = 0;
    int * b, blen;
    bool matrix = true;
    bool verbose = false;
    
    
    //(W, b, X, Y, weightType, cacheSize)
    W = getMatrix(prhs[0]);
    
    m = mxGetM(prhs[0]);
    wsize = m;
    n = mxGetN(prhs[0]);
    double * bdouble = mxGetPr(prhs[1]);
    blen = mxGetM(prhs[1]) + mxGetN(prhs[1]) - 1;
    b = new int[blen];
    for (int i = 0; i < blen; i++)
        b[i] = round(bdouble[i]);
    
    if (nrhs > 2) {
        X = getMatrix(prhs[2]);

        xsize = mxGetM(prhs[2]);
        
        if (xsize > 0) {
            m = mxGetM(prhs[2]);
            d = mxGetN(prhs[2]);
            matrix = false;
            weightType = 1; // default weight type
            if (nrhs > 3) {
                Y = getMatrix(prhs[3]);
                n = mxGetM(prhs[3]);
                ysize = n;
            } else
                n = 0;
        } else 
            X = 0;
    }
    
    if (nrhs > 4 && mxGetM(prhs[4]) > 0)
        weightType = round(mxGetScalar(prhs[4]));
    if (nrhs > 5 && mxGetM(prhs[4]) > 0)
        cacheSize = round(mxGetScalar(prhs[5]));
    else
        cacheSize = round(2 * sqrt(m + n));
    
    if (nrhs > 6)
        verbose = mxGetScalar(prhs[6]) > 0;
    
    SparseMatrix<bool> * solution;
    
    // By default, perform no more than 100*(m+n) iterations
    int maxIter = 100*(m+n);
   
    if (blen == m) {
        // unipartite
        if (matrix)
            solution = bMatchMatrixCache(m, W, b, cacheSize, maxIter, verbose);
        else if (weightType == 1)
            solution = bMatchEuclideanCache(m, d, X, b, cacheSize, maxIter, verbose);
        else if (weightType == 2)
            solution = bMatchInnerProductCache(m, d, X, b, cacheSize, maxIter, verbose);
        else
            mexErrMsgTxt("Unrecognized weight type");
    } else {
        // bipartite
        if (matrix)
            solution = bMatchBipartiteMatrixCache(m, n, W, b, b+m,
                    cacheSize, maxIter, verbose);
        else if (weightType == 1)
            solution = bMatchBipartiteEuclideanCache(m, n, d, X, Y, b,
                    b+m, cacheSize, maxIter, verbose);
        else if (weightType == 2)
            solution = bMatchBipartiteInnerProductCache(m, n, d, X, Y, b,
                    b+m, cacheSize, maxIter, verbose);
        else
            mexErrMsgTxt("Unrecognized weight type");
    }
    
    if (wsize > 0)
        deleteMatrix(W, wsize);
    if (xsize > 0)
        deleteMatrix(X, xsize);
    if (ysize > 0)
        deleteMatrix(Y, ysize);
    
    delete[](b);
    
    
    int nnz = solution->getNNz();
    
    mxArray * I = mxCreateDoubleMatrix(nnz, 1, mxREAL);
    mxArray * J = mxCreateDoubleMatrix(nnz, 1, mxREAL);
    mxArray * V = mxCreateDoubleMatrix(nnz, 1, mxREAL);
    
    double * rows = new double[nnz];
    double * cols = new double[nnz];
    double * vals = new double[nnz];
   
    for (int i=0; i < nnz; i++) {
        rows[i] = solution->getRows()[i]+1;
        cols[i] = solution->getCols()[i]+1;
        vals[i] = 1.0;
    }
    
    delete(solution);
 
    memcpy(mxGetPr(I), rows, nnz*sizeof(double));
    memcpy(mxGetPr(J), cols, nnz*sizeof(double));
    memcpy(mxGetPr(V), vals, nnz*sizeof(double));

    delete[](rows);
    delete[](cols);
    delete[](vals);
   
    mxArray * rhs[5];
    
    rhs[0] = I;
    rhs[1] = J;
    rhs[2] = V;
    rhs[3] = mxCreateDoubleScalar(blen);
    rhs[4] = mxCreateDoubleScalar(blen);
    
    mexCallMATLAB(1, plhs, 5, rhs, "sparse");
    
    for (int i = 0; i < 5; i++)
        mxDestroyArray(rhs[i]);
   
    
    
    return;
}
