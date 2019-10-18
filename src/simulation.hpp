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
    template<typename FuncType> // (float, float) -> bool
    void simulate(eg::MatrixXf& grr, const FuncType f, const eg::VectorXf range0, const eg::VectorXf range1, const float r, const float k) {
        
        
        const eg::MatrixXf fxy = calc_xy_mesh(range0, f); // f(x, y)

        eg::MatrixXcf u;
        // ここがn^4
        u = calc_xy_mesh(range1, [fxy, &range, k, r](float x, float y){ return integral(x, y, fxy, range1, k, r);});
        u /= r;

        // 絶対値を求めるなら位相因子は不要
        // u = u * std::exp(I*k*r) / r;
        grr = u.unaryExpr(std::norm);
    }
    
    static std::complex<float> integral(float x_p, float y_p, const eg::MatrixXf& fxy, const eg::VectorXf& range, const float k, const float r) {
        
        std::complex<float> sum(0, 0);
        for (int i=0; i<range.cols(); ++i) {
            for (int j=0; j<range.cols(); ++j) {
                if (fxy(i, j))
                    sum += std::exp( I * k / r *(range(i)*x_p + range(j)*y_p) );
            }
        }
        return sum;
    }

    template<typename FuncType> // (float, float) -> bool
    static eg::Matrix<bool, eg::Dynamic, eg::Dynamic> calc_xy_mesh(const eg::VectorXf& range, const FuncType f) {

        eg::Matrix<bool, eg::Dynamic, eg::Dynamic> mat;
        for (int i=0; i<range.cols(); ++i) {
            for (int j=0; j<range.cols(); ++j) {
                mat(i, j) = f(range(i), range(j));
            }
        }
        return mat;
    }


    inline bool circle(const float x, const float y, const float r0) {
        return x*x + y*y < r0*r0;
    }


    
} // namespace simulation


