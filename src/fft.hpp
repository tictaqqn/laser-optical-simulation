#ifndef FFT_HPP
#define FFT_HPP
#include "Eigen/Dense"
#include <iostream>
#include <vector>
#include <complex>

namespace eg = Eigen;

// fft header
int lc_fft_calc_ids( const int N, std::vector< int >* pids );
void lc_fft(
            const std::vector< std::complex<double> >& a,
            const std::vector< int >& ids, const int n_level,
            std::vector< std::complex< double > >* pout, bool is_inverse=0 );
void lc_inverse_fft(
                    const std::vector< std::complex<double> >& a,
                    const std::vector< int >& ids,const int n_level,
                    std::vector< std::complex< double > >* pout );


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
#endif