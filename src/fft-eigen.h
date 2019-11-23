#ifndef FFT2D_H
#define FFT2D_H
#include <vector>
#include "Eigen/Dense"

namespace eg = Eigen;

void fft2(const eg::MatrixXf& input, eg::MatrixXcf& output);
void ifft2(const eg::MatrixXf& input, eg::MatrixXcf& output);
void shift(eg::MatrixXcf& freq);

#endif
