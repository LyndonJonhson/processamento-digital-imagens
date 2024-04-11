#include <iostream>
#include <opencv2/opencv.hpp>

int main(int argc, char** argv) {
  cv::Mat image;
  int width, height;
  int nBolhasSemBuracos, nBolhasComBuracos;

  cv::Point p;
  image = cv::imread("../bolhas.png", cv::IMREAD_GRAYSCALE);

  if (!image.data) {
    std::cout << "imagem nao carregou corretamente\n";
    return (-1);
  }

  width = image.cols;
  height = image.rows;
  std::cout << width << "x" << height << std::endl;

  p.x = 0;
  p.y = 0;

  // elimina bolhas que tocam bordas esquerda e direita
  for (int i = 0; i < height; i++) {
    if (image.at<uchar>(i, 0) == 255) {
      p.x = 0;
      p.y = i;
      cv::floodFill(image, p, 0);
    }
    if (image.at<uchar>(i, width - 1) == 255) {
      p.x = width - 1;
      p.y = i;
      cv::floodFill(image, p, 0);
    }
  }

  // elimina bolhas que tocam bordas superior e inferior
  for (int j = 0; j < width; j++) {
    if (image.at<uchar>(0, j) == 255) {
      p.x = j;
      p.y = 0;
      cv::floodFill(image, p, 0);
    }
    if (image.at<uchar>(height - 1, j) == 255) {
      p.x = j;
      p.y = height - 1;
      cv::floodFill(image, p, 0);
    }
  }

  cv::imwrite("bordas-limpas.png", image);

  // trocando cor de fundo da imagem
  p.x = 0;
  p.y = 0;
  cv::floodFill(image, p, 10);

  //busca bolhas com buracos
  nBolhasComBuracos = 0;
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      // achou um buraco
      if (image.at<uchar>(i, j) == 0) {
        // verifica se a bolha já foi contada pegando o pixel anterior
        if (image.at<uchar>(i - 1, j - 1) == 255) {
          nBolhasComBuracos++;
          p.x = j - 1;
          p.y = i - 1;
          cv::floodFill(image, p, 100);
        }
        p.x = j;
        p.y = i;
        cv::floodFill(image, p, 100);
      }
    }
  }

  // busca bolhas restantes
  nBolhasSemBuracos = 0;
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      // achou uma bolha
      if (image.at<uchar>(i, j) == 255) {
        nBolhasSemBuracos++;
        p.x = j;
        p.y = i;
        cv::floodFill(image, p, 200);
      }
    }
  }

  std::cout << "a figura tem " << nBolhasComBuracos + nBolhasSemBuracos << " bolhas\n";
  std::cout << nBolhasComBuracos << " bolhas com buracos\n";
  std::cout << nBolhasSemBuracos << " bolhas sem buracos\n";
  cv::imshow("image", image);
  cv::imwrite("labeling.png", image);
  cv::waitKey();
  return 0;
}