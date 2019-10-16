# include <vector>
# include <complex>
# include <functional>

template<typename T> // float, double などを想定。変更可能にした
using Vect2 = std::vector< std::vector<T> >;
namespace simulation
{
    template<typename T>
    void map_f(Vect2<T>& xy_array, const std::function<T(T)> f) {
        // xy_arrayは別途メモリ確保せず、fを各成分に作用させる
        for (auto& arr : xy_array) {
            for (auto& value : arr) {
                value = f(value);
            }
        }
    }
    template<typename T>
    void simulate(const Vect2<T>& xy_array, Vect2< std::complex<T> >& gr, const std::function<T(T)> f,
                const float mu_x, const float mu_y) {
        // gr -> 求めるべきもの
        // xy_arrayはfを各成分に作用させたもの
        
        
        

    }
} // namespace simulation


