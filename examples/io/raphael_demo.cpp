
#include "opencv2/core/core.hpp"
#include <cmath>
#include <iostream>
#include <opencv2/core.hpp>

using namespace std;
using namespace cv;
typedef struct raphael_point3d_t {
    double x;
    double y;
    double z;
} raphael_point3d;

double rmsd(raphael_point3d_t *src, raphael_point3d_t *dst, int sz)
{
    double var = 0;
    for (int i = 0; i < sz; i++) {
        double dif = pow((src[i].x - dst[i].x), 2) + pow((src[i].y - dst[i].y), 2);
        var += dif;
    }
    return sqrt(var / sz);
}

int main()
{
    Mat mat = (Mat_<double>(4, 2) << 1, 2, 3, 4, 5, 6, 7, 8);
    Mat mat2 = (Mat_<double>(4, 2) << 0, 1, 2, 3, 4, 5, 6, 7);
    auto src = new raphael_point3d[4];
    auto dst = new raphael_point3d[4];
    for (int i = 0; i < mat.rows; i++) {
        src[i].x = mat.at<double>(i, 0);
        src[i].y = mat.at<double>(i, 1);
        src[i].z = 0;

        dst[i].x = mat2.at<double>(i, 0);
        dst[i].y = mat2.at<double>(i, 1);
        dst[i].z = 0;
    }
    cout << "rmsd: " << rmsd(src, dst, 4) << endl; // (差的) 平方和平均数 开根号
    cout << "norml2: " << norm(mat, mat2) << endl; // (差的)平方和开根号
    delete[] src;
    delete[] dst;
}
