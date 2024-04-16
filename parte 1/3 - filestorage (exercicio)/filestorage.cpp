#include <iostream>
#include <opencv2/opencv.hpp>
#include <sstream>
#include <string>

int SIDE = 256;
int PERIODOS[2] = {8, 4};

int main(int argc, char** argv) {
  std::stringstream ss_img1, ss_yml1;
  std::stringstream ss_img2, ss_yml2;
  cv::Mat image1, image2, result;

  ss_yml1 << "senoide1-" << SIDE << ".yml";
  image1 = cv::Mat::zeros(SIDE, SIDE, CV_32FC1);

  ss_yml2 << "senoide2-" << SIDE << ".yml";
  image2 = cv::Mat::zeros(SIDE, SIDE, CV_32FC1);

  cv::FileStorage fs1(ss_yml1.str(), cv::FileStorage::WRITE);
  cv::FileStorage fs2(ss_yml2.str(), cv::FileStorage::WRITE);

  for (int i = 0; i < SIDE; i++) {
    for (int j = 0; j < SIDE; j++) {
      image1.at<float>(i, j) = 127 * sin(2 * M_PI * PERIODOS[0] * j / SIDE) + 128;
      image2.at<float>(i, j) = 127 * sin(2 * M_PI * PERIODOS[1] * j / SIDE) + 128;
    }
  }

  fs1 << "mat" << image1;
  fs1.release();

  fs2 << "mat" << image2;
  fs2.release();

  cv::normalize(image1, image1, 0, 255, cv::NORM_MINMAX);
  image1.convertTo(image1, CV_8U);
  ss_img1 << "senoide1-" << SIDE << ".png";
  cv::imwrite(ss_img1.str(), image1);

  cv::normalize(image2, image2, 0, 255, cv::NORM_MINMAX);
  image2.convertTo(image2, CV_8U);
  ss_img2 << "senoide2-" << SIDE << ".png";
  cv::imwrite(ss_img2.str(), image2);

  fs1.open(ss_yml1.str(), cv::FileStorage::READ);
  fs1["mat"] >> image1;

  fs2.open(ss_yml2.str(), cv::FileStorage::READ);
  fs2["mat"] >> image2;

  cv::normalize(image1, image1, 0, 255, cv::NORM_MINMAX);
  image1.convertTo(image1, CV_8U);

  cv::normalize(image2, image2, 0, 255, cv::NORM_MINMAX);
  image2.convertTo(image2, CV_8U);

  result = cv::Mat::zeros(SIDE, SIDE, CV_8U);
  
  for (int i = 0; i < SIDE; i++) {
    for (int j = 0; j < SIDE; j++) {
      if (image1.at<uchar>(i, j) > image2.at<uchar>(i, j)) {
        result.at<uchar>(i, j) = image1.at<uchar>(i, j) - image2.at<uchar>(i, j);
      } else {
        result.at<uchar>(i, j) = image2.at<uchar>(i, j) - image1.at<uchar>(i, j);
      }
    }
  }

  cv::imwrite("result.png", result);
  cv::imshow("image1", image1);
  cv::imshow("image2", image2);
  cv::imshow("result", result);
  cv::waitKey();

  return 0;
}