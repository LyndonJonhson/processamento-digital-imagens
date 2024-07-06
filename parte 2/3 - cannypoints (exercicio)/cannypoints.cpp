#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <opencv2/opencv.hpp>
#include <vector>
#include <chrono>
#include <random>

#define STEP 5
#define JITTER 3

cv::Mat image, points, border;

int width, height;
int x, y, gray;

int top_slider_canny = 10;
int top_slider_canny_max = 200;
int top_slider_point = 1;
int top_slider_point_max = 20;
int top_slider_point_border = 1;
int top_slider_point_border_max = 20;

char TrackbarNameCanny[50];
char TrackbarNamePoint[50];
char TrackbarNamePointBorder[50];

void pontilhismo() {
  std::srand(std::time(0));

  std::vector<int> yrange;
  std::vector<int> xrange;

  xrange.resize(height / STEP);
  yrange.resize(width / STEP);

  std::iota(xrange.begin(), xrange.end(), 0);
  std::iota(yrange.begin(), yrange.end(), 0);

  for(uint i = 0; i < xrange.size(); i++) {
    xrange[i] = xrange[i] * STEP + STEP / 2;
  }

  for(uint i = 0; i < yrange.size(); i++) {
    yrange[i] = yrange[i] * STEP + STEP / 2;
  }

  points = cv::Mat(height, width, CV_8U, cv::Scalar(255));

  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::shuffle(xrange.begin(), xrange.end(), std::default_random_engine(seed));

  for (auto i : xrange) {
  std::shuffle(yrange.begin(), yrange.end(), std::default_random_engine(seed));
    for (auto j : yrange) {
      x = i + std::rand() % (2 * JITTER) - JITTER + 1;
      y = j + std::rand() % (2 * JITTER) - JITTER + 1;
      gray = image.at<uchar>(x, y);
      cv::circle(
        points, 
        cv::Point(y, x), 
        top_slider_point, 
        CV_RGB(gray, gray, gray),
        cv::FILLED, 
        cv::LINE_AA
      );
    }
  }
}

void applyPointInBorders() {  
  for(x = 0; x < height; x++) {
    for(y = 0; y < width; y++) {
      if(border.at<uchar>(x, y) == 255) {
        gray = image.at<uchar>(x, y);
        circle(
          points,
          cv::Point(y, x),
          top_slider_point_border,
          CV_RGB(gray, gray, gray),
          cv::FILLED,
          cv::LINE_AA
        );
      }
    }
  }
}

void on_trackbar(int, void*){
  pontilhismo();
  cv::Canny(image, border, top_slider_canny, 3*top_slider_canny);
  applyPointInBorders();
  cv::imshow("Cannypoints", points);
}

int main(int argc, char** argv){
  image = cv::imread(argv[1], cv::IMREAD_GRAYSCALE);

  if (image.empty()) {
    std::cout << "Could not open or find the image" << std::endl;
    return -1;
  }

  sprintf(TrackbarNameCanny, "Canny", top_slider_canny_max);
  sprintf(TrackbarNamePoint, "Points Radius", top_slider_point_max);
  sprintf(TrackbarNamePointBorder, "Border Radius", top_slider_point_border_max);

  //altura e largura da imagem
  width = image.cols;
  height = image.rows;

  //prepara a janela para exibição da imagem
  cv::namedWindow("Cannypoints", 1);
  cv::createTrackbar(
    TrackbarNameCanny,
    "Cannypoints",
    &top_slider_canny,
    top_slider_canny_max,
    on_trackbar
  );
  cv::createTrackbar(
    TrackbarNamePoint,
    "Cannypoints",
    &top_slider_point,
    top_slider_point_max,
    on_trackbar
  );
  cv::createTrackbar(
    TrackbarNamePointBorder,
    "Cannypoints",
    &top_slider_point_border,
    top_slider_point_border_max,
    on_trackbar
  );

  cv::waitKey(0);
  return EXIT_SUCCESS;
}