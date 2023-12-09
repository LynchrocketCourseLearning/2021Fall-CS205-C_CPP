
#include "../inc/matrix.hpp"

flMatrix::flMatrix(int a, int b, int c, int d) : rowA(a), colA(b), rowB(c), colB(d) {}

flMatrix::~flMatrix() {
    delete[] matrixA;
    delete[] matrixB;
    delete[] matrixRes;
}

void flMatrix::flMul(float *matrixA, int rowA, int colA, float *matrixB, int rowB, int colB, float *mul) {
    for (int i = 0; i < rowA; i++) {
        for (int k = 0; k < colA; k++) {
            for (int j = 0; j < colB; j++) { 
                *(mul + i * rowA + j) += *(matrixA + i * rowA + k) * (*(matrixB + k * colA + j));
            }
        }
    }
}


doMatrix::doMatrix(int a, int b, int c, int d) : rowA(a), colA(b), rowB(c), colB(d) {}

doMatrix::~doMatrix() {
    delete[] matrixA;
    delete[] matrixB;
    delete[] matrixRes;
}

void doMatrix::doMul(double *matrixA, int rowA, int colA, double *matrixB, int rowB, int colB, double *mul) {
    for (int i = 0; i < rowA; i++) {
        for (int k = 0; k < colA; k++) {
            for (int j = 0; j < colB; j++) { 
                *(mul + i * rowA + j) += *(matrixA + i * rowA + k) * (*(matrixB + k * colA + j));
            }
        }
    }
}