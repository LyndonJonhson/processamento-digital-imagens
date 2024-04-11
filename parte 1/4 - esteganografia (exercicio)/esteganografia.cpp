
#include <iostream>
#include <opencv2/opencv.hpp>

int main(int argc, char**argv) {
  cv::Mat imagem, imagemEscondida;
  cv::Vec3b valImagem, valImagemEscondida;
  int nbits = 3;

  imagem = cv::imread("../desafio-esteganografia.png", cv::IMREAD_COLOR);

  if (imagem.empty()) {
    std::cout << "imagem nao carregou corretamente" << std::endl;
    return -1;
  }

  imagemEscondida = cv::Mat::zeros(imagem.rows, imagem.cols, CV_8UC3);

  for (int i = 0; i < imagem.rows; i++) {
    for (int j = 0; j < imagem.cols; j++) {
      valImagem = imagem.at<cv::Vec3b>(i, j);
      valImagemEscondida[0] = valImagem[0] << (8 - nbits);
      valImagemEscondida[1] = valImagem[1] << (8 - nbits);
      valImagemEscondida[2] = valImagem[2] << (8 - nbits);
      imagemEscondida.at<cv::Vec3b>(i, j) = valImagemEscondida;
    }
  }

  imwrite("imagem-escondidade.png", imagemEscondida);
  return 0;
}