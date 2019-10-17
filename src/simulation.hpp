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
                    eg::VectorXf range, const float r, const float k) {
        
        
        const eg::MatrixXf fxy = calc_xy_mesh(range, f); // f(x, y)

        u = calc_xy_mesh(range, [fxy, range, k, r](float x, float y){ return integral(x, y, fxy, range, k, r);});
        
        u = u * std::exp(I*k*r) / r;

        

    }
    
    static std::complex<float> integral(float x_p, float y_p, const eg::MatrixXf& fxy, const eg::VectorXf range, const float k, const float r) {
        
        std::complex<float> sum(0, 0);
        for (int i=0; i<range.col; ++i) {
            for (int j=0; j<range.col; ++j) {
                sum += fxy(i, j) * std::exp( I * k / r *(range(i)*x_p + range(j)*y_p) );
            }
        }
        return sum;
    }

    template<typename T, typename FuncType>
    static eg::Matrix<T, eg::Dynamic, eg::Dynamic> calc_xy_mesh(eg::VectorXf range, FuncType f) {

        eg::Matrix<T, eg::Dynamic, eg::Dynamic> mat;
        for (int i=0; i<range.col; ++i) {
            for (int i=0; i<range.col; ++i) {
                mat(i, j) = f(range(i), range(j));
            }
        }
        return mat;
    }

    
} // namespace simulation


