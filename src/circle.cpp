# define EIGEN_NO_DEBUG // コード内のassertを無効化．
# define EIGEN_MPL2_ONLY // LGPLライセンスのコードを使わない．

# include <bits/stdc++.h> // for M_PI
# include "Eigen/Dense"
# include "simulation.hpp"
using namespace simulation;
namespace eg = Eigen;

int main(int argc, char const *argv[])
{
    /* 波長以外すべてmm単位 */
    constexpr float wavelength_nm = 632.8; // nm
    constexpr float k = 2 * M_PI / (wavelength_nm * 1e-6);
    constexpr float r = 400; // スクリーンとの距離
    constexpr float r0 = 10; // 円の大きさ
    constexpr float screen_range = 50; // スクリーンの幅/2
    const eg::VectorXf range0 = eg::VectorXf::LinSpaced(100, -r0, r0);
    const eg::VectorXf range1 = eg::VectorXf::LinSpaced(100, -screen_range, screen_range);

    eg::MatrixXf grr;
    simulate(grr, circle, range0, range1, r, k);

    return 0;
}
