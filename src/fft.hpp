# include "Eigen/Dense"
# include "unsupported/Eigen/FFT"

namespace eg = Eigen;

void fft2(const eg::MatrixXf& input, eg::MatrixXcf& output) 
{
  
    const eg::FFT<float> fft;
    eg::MatrixXcf tmp(input.rows(), input.cols());
  
    for (int i=0; i < input.cols(); ++i) {
      tmp.col(i).noalias() = fft.fwd(input.col(i));
    }
    for (int i=0; i< input.cols(); ++i) {
      output.row(i).noalias() = fft.fwd(tmp.row(i)).transpose();
    }

}

void ifft2(const eg::MatrixXcf& input, eg::MatrixXcf& output) 
{
  
    const eg::FFT<float> fft;
    eg::MatrixXcf tmp(input.rows(), input.cols());
  
    for (int i=0; i < input.cols(); ++i) {
      tmp.col(i).noalias() = fft.inv(input.col(i));
    }
    for (int i=0; i< input.cols(); ++i) {
      output.row(i).noalias() = fft.inv(tmp.row(i)).transpose();
    }

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