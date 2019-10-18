// # define EIGEN_NO_DEBUG // コード内のassertを無効化．
// # define EIGEN_MPL2_ONLY // LGPLライセンスのコードを使わない．

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
    template<typename T, typename FuncType> // (float, float) -> T
    static void calc_xy_mesh(eg::Matrix<T, eg::Dynamic, eg::Dynamic>& mat, const eg::VectorXf& range, const FuncType f) {

        for (int i=0; i<range.size(); ++i) {
            for (int j=0; j<range.size(); ++j) {
                mat(i, j) = f(range(i), range(j));
            }
        }
    }
    static std::complex<float> integral(float x_p, float y_p, const eg::MatrixXi& fxy, const eg::VectorXf& range, const float k, const float r) {
        
        std::complex<float> sum(0, 0);
        for (int i=0; i<range.size(); ++i) {
            for (int j=0; j<range.size(); ++j) {
                if (fxy(i, j) == 1)
                    sum += std::exp( I * k / r *(range(i)*x_p + range(j)*y_p) );
            }
        }
        return sum;
    }
    // xy -> fxy
    // u :ans
    template<typename FuncType> // (float, float) -> int
    void simulate(eg::MatrixXf& grr, const FuncType f, const eg::VectorXf& range0, const eg::VectorXf& range1, const float r, const float k) {
        
        eg::MatrixXi fxy = eg::MatrixXi::Zero(range0.size(), range0.size());        
        calc_xy_mesh(fxy, range0, [r, f](float x, float y){ return f(x, y, r); }); // f(x, y)

        eg::MatrixXcf u = eg::MatrixXcf::Zero(range1.size(), range1.size());
        // ここがn^4
        calc_xy_mesh(u, range1, [&fxy, &range1, k, r](float x, float y){ return integral(x, y, fxy, range1, k, r); });
        // u /= r;

        // 絶対値を求めるなら位相因子は不要
        // u = u * std::exp(I*k*r) / r;
        grr = u.unaryExpr([](std::complex<float> z){return std::norm(z);});
    }
    


    inline int circle(const float x, const float y, const float r0) {
        return x*x + y*y < r0*r0 ? 1 : 0;
    }


    
} // namespace simulation


