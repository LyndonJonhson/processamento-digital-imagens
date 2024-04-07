#include <iostream>
#include <opencv2/opencv.hpp>

int main(int, char**) {
  // Carregar a imagem original
    cv::Mat image = cv::imread("../biel.png");

    if (image.empty()) {
        std::cout << "nao abriu biel.png" << std::endl;
        return -1;
    }

    // Obter as dimensões da imagem
    int width = image.cols;
    int height = image.rows;

    // Dividir a imagem em quatro partes iguais
    cv::Rect topLeftRect(0, 0, width / 2, height / 2);
    cv::Rect topRightRect(width / 2, 0, width / 2, height / 2);
    cv::Rect bottomLeftRect(0, height / 2, width / 2, height / 2);
    cv::Rect bottomRightRect(width / 2, height / 2, width / 2, height / 2);

    cv::Mat topLeft = image(topLeftRect);
    cv::Mat topRight = image(topRightRect);
    cv::Mat bottomLeft = image(bottomLeftRect);
    cv::Mat bottomRight = image(bottomRightRect);

    // Juntar as partes em quadrantes diferentes
    cv::Mat result(height, width, image.type());

    topLeft.copyTo(result(cv::Rect(width / 2, height / 2, width / 2, height / 2)));
    topRight.copyTo(result(cv::Rect(0, height / 2, width / 2, height / 2)));
    bottomLeft.copyTo(result(cv::Rect(width / 2, 0, width / 2, height / 2)));
    bottomRight.copyTo(result(cv::Rect(0, 0, width / 2, height / 2)));

    // Mostrar a imagem resultante
    cv::imshow("Result", result);
    cv::waitKey(0);

    return 0;
}