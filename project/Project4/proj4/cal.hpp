#pragma once

#include "matrix.hpp"
#include <immintrin.h>
#include <cblas.h>

template<typename T>
void simple(matrix<T> &des, const matrix<T> &ma, const matrix<T> &mb);

float vec_dot(const float *, const float *, const size_t);

void simd(matrix<float> &des, const matrix<float> &ma, const matrix<float> &mb);

template<typename T>
void blas(matrix<T> &des, const matrix<T> &ma, const matrix<T> &mb);

