#include <iostream>
#include <opencv2/opencv.hpp>

int main(int argc, char** argv){
  cv::Mat image;
  image = cv::imread("../biel.png",cv::IMREAD_GRAYSCALE);
  cv::imshow("image", image);
  cv::waitKey();
  return 0;
}
