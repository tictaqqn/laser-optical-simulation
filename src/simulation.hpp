# define EIGEN_NO_DEBUG // コード内のassertを無効化．
# define EIGEN_MPL2_ONLY // LGPLライセンスのコードを使わない．

# include <vector>
# include <complex>
# include <functional>
# include "Eigen/Dense"

namespace eg = Eigen;
constexpr std::complex<float> I(0, 1);

// template<typename T> // float, double などを想定。変更可能にした
// using MatrixX = eg::Matrix<T, eg::Dynamic, eg::Dynamic>;

namespace simulation
{
    // xy -> fxy
    // u :ans
    template<typename FuncType> // 本当は関数の部分型にしたいがコンパイル時にチェックさせれば大丈夫
    void simulate(eg::Matrix<std::vector<float>, eg::Dynamic, eg::Dynamic>& xys, eg::MatrixXcf& u, const FuncType f,
                    std::vector< float > range, const float r, const float k) {
        
        
        const eg::MatrixXf fxys = calc_xy_mesh(range, f); // f(x, y)

        u = calc_xy_mesh(range, [fxys, range, k, r](std::vector<float> xy){ return integral(xy[0], xy[1], fxys, range, k, r);});
        
        u = u * std::exp(I*k*r) / r;

        

    }
    
    static std::complex<float> integral(float x_p, float y_p, const eg::MatrixXf& fxy, std::vector< float > range, const float k, const float r) {
        
        std::complex<float> sum(0, 0);
        int i = 0, j = 0;
        for (const auto& x : range) {
            for (const auto& y : range) {
                sum += fxy(i, j) * std::exp( I * k / r *(x*x_p + y*y_p) );
                ++j;
            }
            ++i;
        }
        return sum;
    }

    template<typename T, typename FuncType>
    static eg::Matrix<T, eg::Dynamic, eg::Dynamic> calc_xy_mesh(std::vector<float> range, FuncType f) {

    }

    
} // namespace simulation


