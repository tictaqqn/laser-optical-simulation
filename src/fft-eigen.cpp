#include "fft-eigen.h"
#include "fft.h"

static void fft_eigen(const eg::VectorXf& input, eg::VectorXcf& output) {
    const std::vector< std::complex<float> > input_v(input.data(), input.data()+input.size());
    std::vector<int> ids;
    const int n_level = lc_fft_calc_ids(input.size(), &ids);
    std::vector< std::complex<float> > output_v;
    lc_fft(input_v, ids, n_level, &output_v);
    output = eg::Map<eg::VectorXcf>(output_v.data(), input.size(), 1);
}
static void ifft_eigen(const eg::VectorXf& input, eg::VectorXcf& output) {
    const std::vector< std::complex<float> > input_v(input.data(), input.data()+input.size());
    std::vector<int> ids;
    const int n_level = lc_fft_calc_ids(input.cols(), &ids);
    std::vector< std::complex<float> > output_v;
    lc_inverse_fft(input_v, ids, n_level, &output_v);
    output = eg::Map<eg::VectorXcf>(output_v.data(), input.size(), 1);
}
void fft2(const eg::MatrixXf& input, eg::MatrixXcf& output)
{
  
    eg::MatrixXcf tmp(input.rows(), input.cols());
  
    for (int i=0; i < input.cols(); ++i) {
      fft_eigen(input.col(i), tmp.row(i));
    }
    for (int i=0; i< input.cols(); ++i) {
      fft_eigen(tmp.row(i), output.row(i));
    }

}

void ifft2(const eg::MatrixXf& input, eg::MatrixXcf& output);


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