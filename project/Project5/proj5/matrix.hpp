#pragma once

// #pragma GCC optimize(3, "Ofast", "inline")

#ifdef _OPENMP
#include <omp.h>
#endif

#ifdef WITH_AVX2
#include <immintrin.h>
#endif

#ifdef WITH_NEON
#include <arm_neon.h>
#endif

// #include <cblas.h>
#ifdef CBLAS_H //用于后面宏区别不同算法
#define BLAS 1
#else
#define BLAS 0
#endif

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath> 
#include <algorithm>
#include <chrono> 
#include <opencv2/opencv.hpp>
// #include <opencv2/core/simd_intrinsics.hpp>

#include "face_binary_cls.cpp"

class Matrix
{
private:
    size_t dimension;
    size_t channel;
    size_t height;
    size_t width;
    float* data; 

public:
    //构造器
    Matrix() :dimension(0), channel(0), height(0), width(0), data(nullptr) {};
    Matrix(size_t n, size_t c, size_t h, size_t w, const float* d) :dimension(n), channel(c), height(h), width(w) 
    {
        size_t len = n * c * h * w;
        data = new float[len]();
        if(!data) 
        {
            std::cerr << "Failed to allocate memory for Matrix data!" << '\n';
            exit(0);
        }
        memcpy(data, d, len * sizeof(float));
    }
    //拷贝构造
    Matrix(const Matrix& L) :dimension(L.dimension), channel(L.channel), height(L.height), width(L.width) 
    {
        size_t len = dimension * channel * height * width;
        data = new float[len]();
        memcpy(data, L.data, len * sizeof(float));
    }
    //析构
    ~Matrix()
    {
        if(!this->data) std::cerr << "Cannot delete data[] since it is null!" << '\n';
        else delete[] data;
        if(!this->data) std::cerr << "Fail to delete data[]!" << '\n';
    }

    //Override:取值 A(n,c,i,j) 第n个，第c层，第i行，第j列
    //由于在循环中调用太费时间，改成inline
    //不检查是否越界，因为在下方调用该inline函数保证不越界
    //return the address
    inline float& operator()(size_t n, size_t c, size_t i, size_t j) 
    {
        size_t index = n * height * width * channel + c * height * width + i * width + j;
        return data[index];
    }
    //return the value
    inline const float operator()(size_t n, size_t c, size_t i, size_t j) const 
    {
        size_t index = n * height * width * channel + c * height * width + i * width + j;
        return data[index];
    }
    //assignment operator
    Matrix& operator = (const Matrix& L) 
    {
        dimension = L.dimension;
        channel = L.channel;
        height = L.height;
        width = L.width;

        size_t len = dimension * channel * height * width;
        if (data) delete[] data;
        data = new float[len]();
        if(!data) 
        {
            std::cerr << "Failed to allocate memory for Matrix data!" << '\n';
            exit(0);
        }
        memcpy(data, L.data, len*sizeof(float));
    }

    //BGR->RGB
    friend float* BGR_to_RGB(cv::Mat& img);

    //卷积操作相关函数
    //卷积，包括padding+ReLU
    Matrix& conv(const Matrix & kernel, float * bias, size_t pad, size_t stride);
    //最大池化
    Matrix& maxpooling();
    //全连接
    void fullCon(float* out, float* weightgh, float* bias, size_t N);
};

/**
*cv::Mat中的通道是[b1, g1, r1, b2, g2, r2, b3, g3, r3...]这样的，
*需要改成[r1, r2, r3, ... g1, g2, g3, ... b1, b2, b3...]来适配weight
*/
float* BGR_to_RGB(cv::Mat& img)
{
    size_t row = img.rows;
    size_t col = img.cols;
    size_t channel = img.channels();

    size_t di = row * col;

    float* res = new float[row * col * channel];

    
    for (size_t i = 0; i < row; ++i) 
    {
        //第i行第一个数据
        uchar* p = img.ptr<uchar>(i);

        // #pragma omp parallel for

        for (size_t j = 0; j < col - 1; j +=4)
        {
            //一次性对每一层执行四个
            //R
            size_t l1 = i * col + j;
            res[l1] = (float)p[3 * j + 2] / 255;
			res[l1 + 1] = (float)p[3 * j + 5] / 255;
			res[l1 + 2] = (float)p[3 * j + 8] / 255;
			res[l1 + 3] = (float)p[3 * j + 11] / 255;

            //G
            size_t l2 = di + i * col + j;
			res[l2] = (float)p[3 * j + 1] / 255;
			res[l2 + 1] = (float)p[3 * j + 4] / 255;
			res[l2 + 2] = (float)p[3 * j + 7] / 255;
			res[l2 + 3] = (float)p[3 * j + 10] / 255;

            //B
            size_t l3 = 2 * di + i * col + j;
			res[l3] = (float)p[3 * j] / 255;
			res[l3 + 1] = (float)p[3 * j + 3] / 255;
			res[l3 + 2] = (float)p[3 * j + 6] / 255;
			res[l3 + 3] = (float)p[3 * j + 9] / 255;
        }
	}
    return res;
}

//conv
Matrix& Matrix::conv(const Matrix & kernel, float * bias, size_t pad, size_t stride)
{
    if(channel != kernel.channel)
    {
        std::cerr << "conv failed for channel don't match!" << '\n';
        exit(0);
    }
    else 
    {
        size_t out_channel = kernel.dimension;
        size_t out_height = (height + 2 * pad - kernel.height) / stride + 1;
        size_t out_width = (width + 2 * pad - kernel.width) / stride + 1;
        float * out_data = new float [1 * out_channel * out_height * out_width]();
        
        Matrix* tmp = new Matrix(1 , out_channel , out_height , out_width , out_data);

        //padding
        size_t h = height + 2 * pad, w = width + 2 * pad;//padding后输入矩阵的高=h，宽=w
        size_t hw = h * w;//padding后每一个channel的尺寸
        size_t HW = height * width;//padding前每一个channel的尺寸
        size_t kn = 0, kc = 0, ki = 0, kj = 0;
        size_t KN = 0, KC = 0, KI = 0, KJ = 0;
        float* inter = new float[dimension * channel * hw];

        for (size_t n = 0; n < dimension; n++) 
        {
            kn = n * channel * hw;
            KN = n * channel * HW;

        // #pragma omp parallel for

            for (size_t c = 0; c < channel; c++) 
            {
                kc = c * hw;
                KC = c * HW;
                for (size_t i = 0; i < height; i++)
                { 
                    ki = (i + pad) * w + pad;
                    KI = i * width;
                    kj = kn + kc + ki;
                    KJ = KN + KC + KI;

                    // #pragma omp parallel for

                    for (size_t j = 0; j < width; j++) {
                        inter[kj + j] = (*this).data[KJ + j];
                    }
                }
            }
        }

        float sum = 0, res = 0;
        size_t k_hw = kernel.height * kernel.width;
        size_t k_chw = kernel.channel * k_hw;
        size_t bc = 0, bi = 0, bj = 0, bik = 0, bck = 0, bjk = 0;//凡带k的，与kernel有关
        
    #if(BLAS)
        float * t_sum = new float[k_hw];
        size_t M = kernel.height, N = kernel.width, K = kernel.width;//MxK * KxN
        float alpha = 1.0f, beta = 0.0f;
        size_t lda = K, ldb = N, ldc = N;

        for(size_t c = 0; c < out_channel; ++c)//输出channel
        {
            for(size_t i = 0; i < out_height; ++i)//输出height
            {
                for(size_t j = 0; j < out_width; ++j)//输出width
                {
                    cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,
                                 M, N, K, alpha, inter, 
                                 lda, kernel.data, ldb, beta, t_sum, ldc);
                    for (size_t i = 0; i < k_hw; ++i)
                    {
                        sum += t_sum[i];
                    }
                    // ReLu
                    res = sum + bias[c];
                    (*tmp).data[c * out_height * out_width + i * out_width + j] = (res > 0.0f) ? res : 0.0f;
                    sum = 0;
                }
            }
        }
        delete[] t_sum;
    
    #else
        // #pragma omp parallel for
        for(size_t c = 0; c < out_channel; ++c)//输出channel
        {
            for(size_t i = 0; i < out_height; ++i)//输出height
            {
                for(size_t j = 0; j < out_width; ++j)//输出width
                {
                    //按着kernel的大小进行矩阵乘法，多用局部变量，减少计算量
                    for(size_t k_c = 0; k_c < kernel.channel; ++k_c)//kernel的channel
                    {
                        bc = k_c * hw;
                        bck = k_c * kernel.height * kernel.width;   
                        for(size_t k_i = 0; k_i < kernel.height; ++k_i)//kernel的height
                        {
                            //按stride移动kernel做不同的矩阵乘法
                            bj = bc + k_i * w + stride * (i * w + j);//对应的是输入矩阵
                            bjk = bck + k_i * kernel.width + c * k_chw;//对应的是kernel
                        #if(CV_SIMD)
                            cv::v_float32 v_sum = cv::vx_setzero_f32();//向量元素全部初始化为0
                            size_t step = sizeof(cv::v_float32)/sizeof(float);//计算每个向量可以存多少个float
                            for (size_t i = step; i < kernel.width; i+=step)
                            {
                                cv::v_float32 v1 = cv::vx_load(inter + bj + i);//从内存inter中装载bj+i个float到v1
                                cv::v_float32 v2 = cv::vx_load(kernel.data + bjk + i);//从内存kernel.data中装载bjk+i个float到v2
                                v_sum += v1 * v2;//通过库的内部重载的运算符，迅速算出
                            }
                            sum += cv::v_reduce_sum(v_sum);
                        #else
                            for(size_t k_j = 0; k_j < kernel.width; ++k_j)//kernel的width
                            {
                                sum += inter[bj + k_j] * kernel.data[bjk + k_j];
                            }
                        #endif
                        }
                    }
                    // ReLu
                    res = sum + bias[c];
                    (*tmp).data[c * out_height * out_width + i * out_width + j] = (res > 0.0f) ? res : 0.0f;
                    sum = 0;
                }
            }
        }
    #endif
        delete[] inter;
        return *tmp;
    }
}

//maxpooling
Matrix& Matrix::maxpooling()
{
    size_t N = dimension, C = channel, H = height / 2, W = width / 2;//四分矩阵
    float* inter = new float[N * C * H * W]();
    Matrix* res = new Matrix(N, C, H, W, inter);
    float max = 0;
    float tmp1 = 0, tmp2 = 0, tmp3 = 0;

    // #pragma omp parallel for
    for (size_t n = 0; n < N; ++n) 
    {
        for (size_t c = 0; c < C; ++c) 
        {
            for (size_t i = 0; i < H; ++i) 
            {
                for (size_t j = 0; j < W; ++j) 
                {
                    //取四个格中最大的
                    max = (*this)(n, c, 2 * i, 2 * j);
                    tmp1 = (*this)(n, c, 2 * i, 2 * j + 1);
                    tmp2 = (*this)(n, c, 2 * i + 1, 2 * j);
                    tmp3 = (*this)(n, c, 2 * i + 1, 2 * j + 1);

                    if (tmp1 > max) max = tmp1;
                    if (tmp2 > max) max = tmp2;
                    if (tmp3 > max) max = tmp3;

                    (*res)(n, c, i, j) = max;
                }
            }
        }
    }
    return *res;
}

//full connection
void Matrix::fullCon(float* out, float* weight, float* bias, size_t N)
{
    size_t L = dimension * channel * height * width;
    float sum;

    // #pragma omp parallel for
    for (size_t i = 0; i < N; ++i) 
    {
        sum = 0;
        size_t L1 = L / 4, L2 = L / 2, L3 = 3 * L / 4;
        for (size_t j = 0; j < L1; ++j) 
        {
            sum += weight[i * L + j] * data[j];
            sum += weight[i * L + L1 + j] * data[L1 + j];
            sum += weight[i * L + L2 + j] * data[L2 + j];
            sum += weight[i * L + L3 + j] * data[L3 + j];
        }
        out[i] = sum + bias[i];
    }
}