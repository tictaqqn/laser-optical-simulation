# define EIGEN_NO_DEBUG // コード内のassertを無効化．
// # define EIGEN_MPL2_ONLY // LGPLライセンスのコードを使わない．

# define _USE_MATH_DEFINES
# include <cmath>
# include <iostream>
# include <string>
# include <fstream>
// # include <bits/stdc++.h> // for M_PI
# include "Eigen/Dense"
# include "simulation.hpp"
# include "get_time_stamp.hpp"
using namespace simulation;
namespace eg = Eigen;

// コンパイルのオプションは-O3 -funroll-loops -fopenmp

int main(int argc, char const *argv[])
{
    /* 波長以外すべてmm単位 */
    constexpr float wavelength_nm = 632.8; // nm
    constexpr float k = 2 * M_PI / (wavelength_nm * 1e-6);
    // constexpr float r = 400; // スクリーンとの距離
    constexpr float r0 = 10; // 円の半径
    constexpr float screen_range = 0.1; // スクリーンの幅/2
    constexpr int n_flt = 100;
    constexpr int n_sc = 1000;
    constexpr int n_R = 20;
    constexpr float R_min = 300;
    constexpr float R_max = 500;
    const eg::VectorXf range_flt = eg::VectorXf::LinSpaced(n_flt, -r0, r0);
    const eg::VectorXf range_sc = eg::VectorXf::LinSpaced(n_sc, -screen_range, screen_range);
    const eg::VectorXf rs = eg::VectorXf::LinSpaced(n_R, R_min, R_max);

    std::string file_path("../results/circle/");
    std::stringstream ss;
    ss << "wavelength: " << wavelength_nm << " r0: " << r0 << " n_flt: " << n_flt 
        << " n_sc: " << n_sc << " n_R: " << n_R << " R_min: " << R_min 
        << " R_max: " << R_max;
    file_path += ss.str();
    file_path += "__";
    file_path += getTimeStamp(); // timestamp
    file_path += ".txt";
    std::ofstream writing_file(file_path, std::ios::out);

    // writing_file << ss.str() << std::endl;

    for (int i=0; i<rs.size(); ++i) {
        eg::MatrixXf grr;
        simulate(grr, circle, range_flt, range_sc, rs(i), k, r0);
        writing_file << grr << std::endl;
        std::cout << i << std::endl;
    }


    return 0;
}


