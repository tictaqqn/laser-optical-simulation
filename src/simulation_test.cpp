# include <bits/stdc++.h> // for M_PI
# include "Eigen/Dense"
# include "simulation.hpp"

namespace sim = simulation;
namespace eg = Eigen;

int main(int argc, char const *argv[])
{
    /* 波長以外すべてmm単位 */
    constexpr float wavelength_nm = 632.8; // nm
    constexpr float k = 2 * M_PI / (wavelength_nm * 1e-6);
    constexpr float r = 400; // スクリーンとの距離
    constexpr float r0 = 10; // 円の半径
    constexpr float screen_range = 50; // スクリーンの幅/2
    const eg::VectorXf range_flt = eg::VectorXf::LinSpaced(100, -r0, r0);
    const eg::VectorXf range_sc = eg::VectorXf::LinSpaced(100, -screen_range, screen_range);

    std::cout << range_flt << std::endl;
    std::cout << range_sc << std::endl;
    

    return 0;
}
