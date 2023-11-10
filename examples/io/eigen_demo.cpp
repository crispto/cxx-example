#include <Eigen/LU>
#include <iostream>
#include <string>

#include "Eigen/src/Core/Matrix.h"
using namespace std;
using namespace Eigen;
int main()
{
    MatrixXd a = Matrix<double, 4, 4>();
    a << 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16;
    cout << a << endl;

    MatrixXd b = Matrix<double, 4, 4>::Zero();
    // cout << a.col(0) << endl;
    b << a.col(0), a.col(1), a.col(2), a.col(3);
    MatrixXd c = a - b + Matrix<double, 4, 4>::Ones();
    cout << c << endl;
    return 0;
}
