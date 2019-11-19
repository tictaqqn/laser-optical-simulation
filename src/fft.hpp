// # include <opencv4/opencv2/core/core.hpp>
# include "Eigen/Dense"
# include <opencv4/opencv2/opencv.hpp>
// # include <opencv4/opencv2/core.hpp>
// # include <opencv4/opencv2/core/eigen.hpp>
// # include "eigen/unsupported/Eigen/FFT"

namespace eg = Eigen;

void fft2(const eg::MatrixXf& input, eg::MatrixXcf& output) 
{
    cv::Mat input_m, output_m;
    cv::eigen2cv(input, input_m);
    cv::dft(input_m, output_m);
    cv::cv2eigen(output_m, output);
}

void ifft2(const eg::MatrixXcf& input, eg::MatrixXcf& output) 
{
    cv::Mat input_m, output_m;
    cv::eigen2cv(input, input_m);
    cv::idft(input_m, output_m);
    cv::cv2eigen(output_m, output);
}


// 表示用に結果をずらす
void shift(eg::MatrixXcf& freq)
{
    eg::MatrixXcf tmp(freq.rows(), freq.cols());
    
    const int cx = freq.cols() / 2;
    const int cy = freq.rows() / 2;// 追記:rowとcol逆
    tmp.block(0, 0, cx, cy) = freq.block(cx, cy, cx, cy);
    tmp.block(cx, cy, cx, cy) = freq.block(0, 0, cx, cy);
    tmp.block(cx, 0, cx, cy) = freq.block(0, cy, cx, cy);
    tmp.block(0, cy, cx, cy) = freq.block(cx, 0, cx, cy);
   
    freq = tmp;
}