//mul.c
#include "mul.h"

clock_t start, end;

//朴素乘法
void mat_mul_simple(matp des, const matp l_mat, const matp r_mat) {
    START;
    size_t i, j, k;
    for (i = 0; i < l_mat->row; ++i) {
        for (j = 0; j < r_mat->col; ++j) {
            for (k = 0; k < l_mat->col; ++k) {
                *(des->val + i * l_mat->row + j) +=
                        *(l_mat->val + i * l_mat->row + k) * *(r_mat->val + k * l_mat->row + j);
            }
        }
    }
    END("mat_mul_simple");
}

//二维数组
void mat_mul_simple_2(matp_2 des, const matp_2 l_mat, const matp_2 r_mat) {
    START;
    size_t i, j, k;
    for (i = 0; i < l_mat->row; ++i) {
        for (j = 0; j < r_mat->col; ++j) {
            for (k = 0; k < l_mat->col; ++k) {
                des->val[i][j] += l_mat->val[i][k] * r_mat->val[k][j];
            }
        }
    }
    END("mat_mul_simple_2");
}

//ikj矩阵乘法,一维数组
void mat_mul_divide(matp des, const matp l_mat, const matp r_mat) {
    START;
    size_t i, j, k;
    for (i = 0; i < l_mat->row; ++i) {
        for (k = 0; k < r_mat->row; ++k) {
            float tmp = *(l_mat->val + i * l_mat->row + k);
            for (j = 0; j < r_mat->col; ++j) {
                *(des->val + i * l_mat->row + j) += tmp * *(r_mat->val + k * r_mat->row + j);
            }
        }
    }
    END("mat_mul_divide");
}

//二维数组实现
void mat_mul_divide_2(matp_2 des, const matp_2 l_mat, const matp_2 r_mat) {
    START;
    size_t i, j, k;
    for (i = 0; i < l_mat->row; ++i) {
        for (k = 0; k < r_mat->row; ++k) {
            float tmp = l_mat->val[i][k];
            for (j = 0; j < r_mat->col; ++j) {
                des->val[i][j] += tmp * r_mat->val[k][j];
            }
        }
    }
    END("mat_mul_divide_2");
}

//Strassen算法
//初始化二维动态数组
float **init_array(size_t n) {
    float **arr = (float **) malloc(n * n * sizeof(float *));
    for (size_t i = 0; i < n; ++i) {
        arr[i] = (float *) malloc(n * sizeof(float));
    }
    return arr;
}

//删除二维动态数组
void del_array(size_t n, float **arr) {
    for (int i = 0; i < n; ++i) {
        free(arr[i]);
    }
    free(arr);
}

//二阶矩阵相乘
void mul(size_t n, float **A, float **B, float **C) {
    size_t i, j, k;
    for (i = 0; i < n; ++i) {
        for (k = 0; k < n; ++k) {
            float tmp = A[i][k];
            for (j = 0; j < 2; ++j) {
                C[i][j] += tmp * B[k][j];
            }
        }
    }
}

//矩阵加法：
void add(size_t n, float **A, float **B, float **C) {
    size_t i, j;
    for (i = 0; i < n; ++i)
        for (j = 0; j < n; ++j)
            C[i][j] = A[i][j] + B[i][j];
}

//矩阵减法：
void sub(size_t n, float **A, float **B, float **C) {
    size_t i, j;
    for (i = 0; i < n; ++i)
        for (j = 0; j < n; ++j)
            C[i][j] = A[i][j] - B[i][j];
}

//strassen主体
void strassen(size_t n, float **A, float **B, float **C) {
    if (n <= 256) {
        mul(n, A, B, C);
    } else {
        n >>= 1;
        float **A11 = init_array(n);
        float **A12 = init_array(n);
        float **A21 = init_array(n);
        float **A22 = init_array(n);

        float **B11 = init_array(n);
        float **B12 = init_array(n);
        float **B21 = init_array(n);
        float **B22 = init_array(n);

        float **M1 = init_array(n);
        float **M2 = init_array(n);
        float **M3 = init_array(n);
        float **M4 = init_array(n);
        float **M5 = init_array(n);
        float **M6 = init_array(n);
        float **M7 = init_array(n);

        float **AA = init_array(n);
        float **BB = init_array(n);

        float **C11 = init_array(n);
        float **C12 = init_array(n);
        float **C21 = init_array(n);
        float **C22 = init_array(n);

        size_t i, j;
        for (i = 0; i < n; ++i) {
            for (j = 0; j < n; ++j) {
                A11[i][j] = A[i][j];
                A12[i][j] = A[i][j + n];
                A21[i][j] = A[i + n][j];
                A22[i][j] = A[i + n][j + n];

                B11[i][j] = B[i][j];
                B12[i][j] = B[i][j + n];
                B21[i][j] = B[i + n][j];
                B22[i][j] = B[i + n][j + n];
            }
        }

        sub(n, B12, B22, BB);
        strassen(n, A11, BB, M1);

        add(n, A11, A12, AA);
        strassen(n, AA, B22, M2);

        add(n, A21, A22, AA);
        strassen(n, AA, B11, M3);

        sub(n, B21, B11, BB);
        strassen(n, A22, BB, M4);

        add(n, A11, A22, AA);
        add(n, B11, B22, BB);
        strassen(n, AA, BB, M5);

        sub(n, A12, A22, AA);
        add(n, B21, B22, BB);
        strassen(n, AA, BB, M6);

        sub(n, A11, A21, AA);
        add(n, B11, B12, BB);
        strassen(n, AA, BB, M7);

        //C11 = M5 + M4 - M2 + M6
        add(n, M5, M4, AA);
        sub(n, M6, M2, BB);
        add(n, AA, BB, C11);

        //C12 = M1 + M2
        add(n, M1, M2, C12);

        //C21 = M3 + M4
        add(n, M3, M4, C21);

        //C22 = M5 + M1 - M3 - M7
        sub(n, M5, M3, AA);
        sub(n, M1, M7, BB);
        add(n, AA, BB, C22);

        for (i = 0; i < n; ++i) {
            for (j = 0; j < n; ++j) {
                C[i][j] = C11[i][j];
                C[i][j + n] = C12[i][j];
                C[i + n][j] = C21[i][j];
                C[i + n][j + n] = C22[i][j];
            }
        }
        del_array(n, A11);
        del_array(n, A12);
        del_array(n, A21);
        del_array(n, A22);

        del_array(n, B11);
        del_array(n, B12);
        del_array(n, B21);
        del_array(n, B22);

        del_array(n, M1);
        del_array(n, M2);
        del_array(n, M3);
        del_array(n, M4);
        del_array(n, M5);
        del_array(n, M6);
        del_array(n, M7);

        del_array(n, AA);
        del_array(n, BB);

        del_array(n, C11);
        del_array(n, C12);
        del_array(n, C21);
        del_array(n, C22);
    }
}

// //SIMD优化，基于intel的AVX指令集
// float vec_dot(const float *v1, const float *v2, const size_t len) {
//     if (len % 8 != 0) {
//         fprintf(stderr, "Error: The size must be power of 8.\n");
//         exit(EXIT_FAILURE);
//     }

//     float s[8] = {0};
//     __m256 a, b;
//     __m256 c = _mm256_setzero_ps();

//     for (size_t i = 0; i < len; i += 8) {
//         a = _mm256_load_ps(v1 + i);
//         b = _mm256_load_ps(v2 + i);
//         c = _mm256_add_ps(c, _mm256_mul_ps(a, b));
//     }
//     _mm256_store_ps(s, c);
//     return (s[0] + s[1] + s[2] + s[3] + s[4] + s[5] + s[6] + s[7]);
// }

// void mat_dot(matp_2 m3, const matp_2 l_mat, const matp_2 r_mat) {
//     START;
//     size_t i, j, k;
//     float *v1 = (float *) aligned_alloc(256, l_mat->row * sizeof(float));
//     float *v2 = (float *) aligned_alloc(256, r_mat->col * sizeof(float));
//     for (i = 0; i < l_mat->row; ++i) {
//         for (j = 0; j < r_mat->col; ++j) {
//             for (k = 0; k < l_mat->col; ++k) *(v1 + k) = l_mat->val[j][k];
//             for (k = 0; k < r_mat->row; ++k) *(v2 + k) = r_mat->val[k][j];
//             m3->val[i][j] = vec_dot(v1, v2, l_mat->row);
//         }
//     }
//     free(v1);
//     free(v2);
//     END("_mm_mat_dot");
// }

//OpenBLAS
void blas(matp m3, const matp m1, const matp m2) {
    START;
    int M = m1->row, N = m2->col, K = m1->col;
    float alpha = 1.0f, beta = 0.0f;
    int lda = K, ldb = N, ldc = N;
    cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, M, N, K, alpha, m1->val, lda, m2->val, ldb, beta, m3->val, ldc);
    END("blas");
}