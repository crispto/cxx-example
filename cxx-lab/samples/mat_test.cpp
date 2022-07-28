#include <Eigen/Core>
#include <Eigen/Dense>
#include <iostream>
typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> EigenMat;

void get_matrix(float in[16])
{
    EigenMat q(in);
    std::cout << q << std::endl;
}
int main()
{
    EigenMat x = EigenMat::Zero(3, 4);
    std::cout << x;
}
