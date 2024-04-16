#include <iostream>
#include <opencv2/opencv.hpp>

int main(int, char**) {
  cv::Mat image;

  image = cv::imread("../biel.png", cv::IMREAD_COLOR);
  
  if (!image.data) {
    std::cout << "nao abriu biel.png" << std::endl;
    return -1;
  }

  cv::namedWindow("janela", cv::WINDOW_AUTOSIZE);

  int x1, y1, x2, y2;
  
  std::cout << "Digite as coordenadas do ponto P1(x1, y1):" << std::endl;
  std::cin >> x1 >> y1;

  std::cout << "Digite as coordenadas do ponto P2(x2, y2):" << std::endl;
  std::cin >> x2 >> y2;

  int minX = std::min(x1, x2);
  int maxX = std::max(x1, x2);
  int minY = std::min(y1, y2);
  int maxY = std::max(y1, y2);

  for (int i = minX; i < maxX; i++) {
    for (int j = minY; j < maxY; j++) {
      image.at<cv::Vec3b>(i, j)[0] = 255 - image.at<cv::Vec3b>(i, j)[0]; // negativo B
      image.at<cv::Vec3b>(i, j)[1] = 255 - image.at<cv::Vec3b>(i, j)[1]; // negativo G
      image.at<cv::Vec3b>(i, j)[2] = 255 - image.at<cv::Vec3b>(i, j)[2]; // negativo R
    }
  }

  cv::imwrite("regions.png", image);
  cv::imshow("janela", image);
  cv::waitKey();
  return 0;
}