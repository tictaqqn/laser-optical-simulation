#ifndef FFT_HPP
#define FFT_HPP
#include "Eigen/Dense"
#include <iostream>
#include <vector>
#include <complex>

namespace eg = Eigen;

// fft header
int lc_fft_calc_ids( const int N, std::vector< int >* pids );
template<typename T> // T: double or float
void lc_fft(
            const std::vector< std::complex<T> >& a,
            const std::vector< int >& ids, const int n_level,
            std::vector< std::complex< T > >* pout, bool is_inverse=false );
template<typename T>
void lc_inverse_fft(
                    const std::vector< std::complex<T> >& a,
                    const std::vector< int >& ids,const int n_level,
                    std::vector< std::complex< T > >* pout );


#endif