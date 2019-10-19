# define EIGEN_NO_DEBUG // コード内のassertを無効化．
// # define EIGEN_MPL2_ONLY // LGPLライセンスのコードを使わない．

# include <vector>
# include <complex>
# include <functional>
# include "Eigen/Dense"
// # define DEBUG

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
    static std::complex<float> integral(float x_p, float y_p, const eg::MatrixXi& fxy, const eg::VectorXf& range_flt, const float k, const float r) {
        
        std::complex<float> sum(0, 0);
        constexpr int n_th = 8;
        # pragma omp declare reduction(+ : std::complex<float> : omp_out=omp_out+omp_in) //initializer(omp_priv = omp_orig)
        # pragma omp parallel 
        {
            # pragma omp for reduction(+:sum)
            for(int th=0; th<n_th; ++th) {
                for (int i=0; i<range_flt.size()/n_th; ++i) {
                    if(k==n_th-1 && i==range_flt.size()%n_th) break;
                    for (int j=0; j<range_flt.size(); ++j) {
                        if (fxy(i, j) == 1)
                            sum += std::exp( I * k / r *(range_flt(i)*x_p + range_flt(j)*y_p) );
                    }
                }
            }
                
        }
        
        return sum;
    }
    // xy -> fxy
    // u :ans
    template<typename FuncType> // (float, float) -> int
    void simulate(eg::MatrixXf& grr, const FuncType f, const eg::VectorXf& range_flt, const eg::VectorXf& range_sc, const float r, const float k, const float r0) {
        
        eg::MatrixXi fxy = eg::MatrixXi::Zero(range_flt.size(), range_flt.size());        
        calc_xy_mesh(fxy, range_flt, [r0, f](float x, float y){ return f(x, y, r0); }); // f(x, y)

        # ifdef DEBUG
        std::cout << fxy << std::endl;
        # endif

        eg::MatrixXcf u = eg::MatrixXcf::Zero(range_sc.size(), range_sc.size());
        // ここがn^4
        calc_xy_mesh(u, range_sc, [&fxy, &range_flt, k, r](float x_p, float y_p){ return integral(x_p, y_p, fxy, range_flt, k, r); });
        // u /= r;

        // 絶対値を求めるなら位相因子は不要
        // u = u * std::exp(I*k*r) / r;
        grr = u.unaryExpr([](std::complex<float> z){return std::norm(z);});
    }
    


    inline int circle(const float x, const float y, const float r0) {
        return x*x + y*y < r0*r0 ? 1 : 0;
    }


    
} // namespace simulation


