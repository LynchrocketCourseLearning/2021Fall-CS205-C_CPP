#include "util.hpp"
#include "cal.hpp"

template<typename T>
void simple(matrix<T> &des, const matrix<T> &ma, const matrix<T> &mb) {
    TIMER;
    size_t ma_row, ma_col, mb_row, mb_col;
    ma_row = ma.get_row();
    ma_col = ma.get_col();
    mb_row = mb.get_row();
    mb_col = mb.get_col();
    for (size_t i = 0; i < ma_row; ++i) {
        for (size_t k = 0; k < mb_row; ++k) {
            T tmp = ma.val[i * ma_row + k];
            for (size_t j = 0; j < mb_col; ++j) {
                des.val[i * ma_col + j] += tmp * mb.val[k * mb_col + j];
            }
        }
    }
}

// float vec_dot(const float *v1, const float *v2, const size_t len) {
//     if (len % 8 != 0) {
//         std::cerr << "ERROR: Not power of 8!" << '\n';
//         throw std::invalid_argument("Not power of 8!");
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

// template<typename T>
// void simd(matrix<T> &des, const matrix<T> &ma, const matrix<T> &mb) {
//     TIMER;
//     for (size_t i = 0; i < ma.get_row(); ++i) {
//         for (size_t j = 0; j < mb.get_col(); ++j) {
//             float *v1 = aligned_alloc(256, max(ma.get_col() * sizeof(float), 256));
//             float *v2 = aligned_alloc(256, max(mb.get_row() * sizeof(float), 256));
//             memcpy(v1, ma.get_val()[i], ma.get_col() * sizeof(float));
//             for (size_t k = 0; k < mb.get_row(); ++k) v2[k] = mb.get_val()[k * mb.get_col() + j];
//             des.data_[i][j] = _mm_vec_dot(v1, v2, mb.get_row());
//             delete[] v2;
//         }
//     }
// }

template<typename T>
void blas(matrix<T> &des, const matrix<T> &ma, const matrix<T> &mb) {
    TIMER;
    int M = ma.get_row(), N = mb.get_col(), K = ma.get_col();
    float alpha = 1.0f, beta = 0.0f;
    int lda = K, ldb = N, ldc = N;
    cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, M, N, K, alpha, ma.val, lda, mb.val, ldb, beta, des.val,
                ldc);
}
