#pragma once

class flMatrix {
public:
    int rowA, colA, rowB, colB;
    float *matrixA = new float[rowA * colA]();
    float *matrixB = new float[rowB * colB]();
    float *matrixRes = new float[rowA * colB]();

    flMatrix(int a, int b, int c, int d);

    void flMul(float *matrixA, int rowA, int colA, float *matrixB, int rowB, int colB, float *mul);

    ~flMatrix();
};

class doMatrix {
public:
    int rowA, colA, rowB, colB;
    double *matrixA = new double[rowA * colA]();
    double *matrixB = new double[rowB * colB]();
    double *matrixRes = new double[rowA * colB]();

    doMatrix(int a, int b, int c, int d);

    void doMul(double *matrixA, int rowA, int colA, double *matrixB, int rowB, int colB, double *mul);

    ~doMatrix();
};


