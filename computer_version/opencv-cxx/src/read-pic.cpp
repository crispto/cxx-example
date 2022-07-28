#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

int main() {
  cv::Mat image; // empty image
  image = cv::imread("../data/mv.jpeg");
  if (image.empty()){
    std::cout << "error " << std::endl;
    return -1;
  }
  std::cout << "width " << image.rows << " ,height: " << image.cols << std::endl;
  
  cv::imshow("mv", image);
  cv::waitKey(0);


}