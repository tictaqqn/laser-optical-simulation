# define EIGEN_NO_DEBUG // コード内のassertを無効化．
// # define EIGEN_MPL2_ONLY // LGPLライセンスのコードを使わない．

# include <bits/stdc++.h> // for M_PI
# include "Eigen/Dense"
# include "simulation.hpp"
using namespace simulation;
namespace eg = Eigen;

// コンパイルのオプションは-O3 -funroll-loops -fopenmp
int main(int argc, char const *argv[])
{
    /* 波長以外すべてmm単位 */
    constexpr float wavelength_nm = 632.8; // nm
    constexpr float k = 2 * M_PI / (wavelength_nm * 1e-6);
    constexpr float r = 400; // スクリーンとの距離
    constexpr float r0 = 10; // 円の半径
    constexpr float screen_range = 0.5; // スクリーンの幅/2
    constexpr int dense_flt = 100;
    constexpr int dense_sc = 1000;
    const eg::VectorXf range_flt = eg::VectorXf::LinSpaced(dense_flt, -r0, r0);
    const eg::VectorXf range_sc = eg::VectorXf::LinSpaced(dense_sc, -screen_range, screen_range);

    std::cout << "wavelength: " << wavelength_nm << " R: " << r << " r0: " << r0 << " dense_flt: " << dense_flt 
        << " dense_sc " << dense_sc << std::endl;

    eg::MatrixXf grr;
    simulate(grr, circle, range_flt, range_sc, r, k, r0);

    std::cout << grr << std::endl;

    return 0;
}
