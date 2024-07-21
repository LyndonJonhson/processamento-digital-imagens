#include <iostream>
#include <vector>
#include <cmath>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

double compareMoments(double m1[], double m2[]) {
	double value = 0;
	for (int i = 0; i < 7; i++) {
		value += abs(m1[i] - m2[i]);
	}
	return value;
}

int main(int argc, char* argv[]) {
	double erro = 999;
	double huMomentsPessoa[7];
	double huMomentsTrecho[7];
	int posicaoPessoa[2];
	int size;
	cv::Mat trechoImage;
	cv::Moments momentsTrecho;

	cv::Mat pessoa = cv::imread(argv[1], IMREAD_GRAYSCALE);
	cv::Mat multidao = cv::imread(argv[2], IMREAD_GRAYSCALE);

	// Verificar se as imagens foram carregadas corretamente
	if (pessoa.empty() || multidao.empty()) {
		cout << "Erro ao carregar as imagens" << endl;
		return -1;
	}

	cv::resize(pessoa, pessoa, Size(pessoa.cols / 6, pessoa.rows / 6), INTER_LINEAR);
	cv::resize(multidao, multidao, Size(multidao.cols / 6, multidao.rows / 6), INTER_LINEAR);

	cv::Moments momentsPessoa = cv::moments(pessoa, false);
	cv::HuMoments(momentsPessoa, huMomentsPessoa);

	for (int i = 0; i < 7; i++) {
    huMomentsPessoa[i] = -1 * std::copysign(1.0, huMomentsPessoa[i]) * log10(abs(huMomentsPessoa[i]));
  }

	size = pessoa.cols;

	for (int i = 0; i < (multidao.cols - size); i++) {
		for (int j = 0; j < (multidao.rows - size); j++) {
			cv::Rect rect(i, j, size, size);
			trechoImage = multidao(rect);
			momentsTrecho = cv::moments(trechoImage, false);
			cv::HuMoments(momentsTrecho, huMomentsTrecho);
			for (int k = 0; k < 7; k++) {
				huMomentsTrecho[k] = -1 * std::copysign(1.0, huMomentsTrecho[k]) * log10(abs(huMomentsTrecho[k]));
			}
			double result = compareMoments(huMomentsPessoa, huMomentsTrecho);
			if (result < erro) {
				erro = result;
				posicaoPessoa[0] = i;
				posicaoPessoa[1] = j;
			}
		}
	}

	for (int i = posicaoPessoa[0]; i < (posicaoPessoa[0] + size); i++) {
		for (int j = posicaoPessoa[1]; j < (posicaoPessoa[1] + size); j++) {
			if (i == posicaoPessoa[0] || i == posicaoPessoa[0] + size - 1) {
				multidao.at<uchar>(i, j) = 0;
			}
			if (j == posicaoPessoa[1] || j == posicaoPessoa[1] + size - 1) {
				multidao.at<uchar>(i, j) = 0;
			}
		}
	}

	std::cout << erro << " - x: " << posicaoPessoa[0] << ", y: " << posicaoPessoa[1] << std::endl;
	cv::imwrite("image.png", multidao);
	cv::imshow("janela", multidao);
	cv::waitKey(0);

	return 0;
}