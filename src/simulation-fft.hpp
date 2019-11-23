#ifndef SIMULATION_HPP
#define SIMULATION_HPP

# define EIGEN_NO_DEBUG // コード内のassertを無効化．
// # define EIGEN_MPL2_ONLY // LGPLライセンスのコードを使わない．

# include <vector>
# include <complex>
# include <functional>
# include <opencv4/opencv2/core/eigen.hpp>
# include "Eigen/Dense"
# include "fft.hpp"
// # define DEBUG

namespace eg = Eigen;
constexpr std::complex<float> I(0, 1);

// template<typename T> // float, double などを想定。変更可能にした
// using MatrixX = eg::Matrix<T, eg::Dynamic, eg::Dynamic>;

namespace simulation_fft
{
    template<typename T, typename FuncType> // (float, float) -> T
    static void calc_xy_mesh(eg::Matrix<T, eg::Dynamic, eg::Dynamic>& mat, const eg::VectorXf& range, const FuncType f) {

        for (int i=0; i<range.size(); ++i) {
            for (int j=0; j<range.size(); ++j) {
                mat(i, j) = f(range(i), range(j));
            }
        }
    }

    void calc_dist2_freq(eg::MatrixXcf& freq_G, const eg::VectorXf& range_flt) {
        eg::MatrixXf G = eg::MatrixXf::Zero(range_flt.size(), range_flt.size());        
        calc_xy_mesh(G, range_flt, [](float x, float y){ return x*x + y*y; }); // f(x, y)
        fft2(G, freq_G);
    }

    template<typename FuncType> // (float, float) -> int
    void simulate(eg::MatrixXf& grr, const FuncType f, const eg::VectorXf& range_flt, const eg::VectorXf& range_sc, const float r, const float k, const eg::MatrixXcf& freq_G) {
        
        eg::MatrixXf H = eg::MatrixXf::Zero(range_flt.size(), range_flt.size());        
        calc_xy_mesh(H, range_flt, [f](float x, float y){ return f(x, y); }); // f(x, y)
        eg::MatrixXcf freq_H = eg::MatrixXcf::Zero(range_flt.size(), range_flt.size());        
        fft2(H, freq_H);

        eg::MatrixXcf grr_complex = eg::MatrixXcf::Zero(range_flt.size(), range_flt.size());        
        ifft2(freq_G.cwiseProduct(freq_H), grr_complex);

        grr = grr_complex.unaryExpr([](std::complex<float> z){return std::real(z);});
    }
    


    inline int circle(const float x, const float y, const float r0) {
        return x*x + y*y < r0*r0 ? 1 : 0;
    }


    
} // namespace simulation_fft
#endif

