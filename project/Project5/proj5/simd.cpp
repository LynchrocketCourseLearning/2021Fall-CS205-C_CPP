#include "matrix.hpp"
#include <opencv2/core/simd_intrinsics.hpp>

using namespace std;
using namespace cv;

float simd_dotproduct(cv::Mat& vec1, cv::Mat& vec2)
{
    float* pv1 = vec1.ptr<float>(0);
    float* pv2 = vec2.ptr<float>(0);
    size_t step = sizeof(cv::v_float32)/sizeof(float);

    cv::v_float32 v_sum = cv::vx_setzero_f32();
    for (size_t i = 0; i < vec1.cols; i+=step)
    {
        cv::v_float32 v1 = cv::vx_load(pv1 + i);
        cv::v_float32 v2 = cv::vx_load(pv2 + i);

        v_sum += v1 * v2;
    }
    float sum = cv::v_reduce_sum(v_sum);
    return sum;
}

int main()
{
    Mat vec1(1,16*1024*1024,CV_32FC1);
    Mat vec2(1,16*1024*1024,CV_32FC1);

    vec1.ptr<float>(0)[2]=3.3f;
    vec2.ptr<float>(0)[2]=2.0f;
    float sum = simd_dotproduct(vec1,vec2);
    cout<<sum<<endl;

    return 0;
}