#include "matrix.hpp"

int main() 
{
    while(true)
    {
	    cv::Mat img;
        bool che = false;
        do{
            std::cout << "Please input the name of the image to be detected. Q to quit." << '\n';
            std::string img_name;
            std::cin >> img_name;
            if(img_name == "Q" || img_name == "q") 
            {
                che = true;
                break;
            }
            img_name = "./image/" + img_name;
            //图像读入 
            img = cv::imread(img_name);
            if(img.empty())
            {
                std::cout << "Cannot find or open the image! Please try again." << '\n';
            } else break;
        }while(true);
        if(che) break;
       
        //修正尺寸
        cv::Mat res;
	    cv::resize(img, res, cv::Size(128, 128));

        //BGR->RGB uchr->float
        size_t length = res.rows * res.cols * res.channels();
        float* arr_f = new float[length];
        arr_f = BGR_to_RGB(res);

        //计时开始
        auto start = std::chrono::steady_clock::now();

        //加入老师提供的kernel
        Matrix conv0_kernel(16, 3, 3, 3, conv0_weight);
        Matrix conv1_kernel(32, 16, 3, 3, conv1_weight);
        Matrix conv2_kernel(32, 32, 3, 3, conv2_weight);

        //卷积+最大池化
        Matrix conv0(1, 3, 128, 128, arr_f);
        Matrix conv1 = conv0.conv(conv0_kernel, conv0_bias, 1, 2).maxpooling();
        Matrix conv2 = conv1.conv(conv1_kernel, conv1_bias, 0, 1).maxpooling();
        Matrix result = conv2.conv(conv2_kernel, conv2_bias, 1, 2);

        //全连接
        float points[2];
        result.fullCon(points, fc0_weight, fc0_bias, 2);

        //Softmax
        double p01 = exp(points[0]);
        double p02 = exp(points[1]);
        double p1 = p01 / (p01 + p02);
        double p2 = p02 / (p01 + p02);

        //计时结束
        auto end = std::chrono::steady_clock::now();
        auto time = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

        std::cout << "-----------------------------------" << '\n';
        std::cout << " [ background = c0 , face = c1 ] " << '\n';
        std::cout << " [ "<< p1 << " , " << p2 << " ] "<< '\n';
        std::cout << " (time: " << time << " μs) " << '\n';
        std::cout << "-----------------------------------" << '\n';
    

        delete[] arr_f;
    }
    

	return 0;
}