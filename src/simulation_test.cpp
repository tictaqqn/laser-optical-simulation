# include <iostream>
# include "Eigen/Dense"
# include "simulation.hpp"

namespace sim = simulation;
namespace eg = Eigen;

int main(int argc, char const *argv[])
{
    eg::VectorXd v(2);

    v << 0, 1;
    std::cout << v(0) << std::endl;

    return 0;
}
