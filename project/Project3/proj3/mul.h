//mul.h
#ifndef MUL_H
#define MUL_H

#include "matrix.h"

// #include <immintrin.h>
#include <cblas.h>

void mat_mul_simple(matp, const matp, const matp);

void mat_mul_simple_2(matp_2, const matp_2, const matp_2);

void mat_mul_divide(matp, const matp, const matp);

void mat_mul_divide_2(matp_2, const matp_2, const matp_2);

float **init_array(size_t);

void del_array(size_t, float **);

void mul(size_t, float **, float **, float **);

void add(size_t, float **, float **, float **);

void sub(size_t, float **, float **, float **);

void strassen(size_t, float **, float **, float **);

// float vec_dot(const float *, const float *, const size_t);

// void mat_dot(matp_2, const matp_2, const matp_2);

void blas(matp, const matp, const matp);

#endif //MUL_H
