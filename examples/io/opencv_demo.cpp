#include "opencv2/core/core.hpp"
#include "opencv2/core/hal/interface.h"
#include "opencv2/core/matx.hpp"
#include <iostream>
#include <opencv2/core/base.hpp>
#include <opencv2/core/types.hpp>
#include <string>

using namespace std;
using namespace cv;
int main()
{
    cv::Mat mat = (cv::Mat_<int>(3, 3) << 1, 2, 3, 4, 5, 6, 7, 8, 9);
    mat.col(1) = -10;
    cout << mat << endl;
}
