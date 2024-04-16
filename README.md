# Processamento digital de imagens

## 1. Primeira unidade

### 1.1. Manipulando pixels em uma imagem

**Atividade 1:** Utilizando o programa [pixels.cpp](https://github.com/LyndonJonhson/processamento-digital-imagens/blob/main/parte%201/2%20-%20pixels/pixels.cpp) como referência, implemente um programa regions.cpp. Esse programa deverá solicitar ao usuário as coordenadas de dois pontos P1 e P2 localizados dentro dos limites do tamanho da imagem e exibir que lhe for fornecida. Entretanto, a região definida pelo retângulo de vértices opostos definidos pelos pontos P1 e P2 será exibida com o negativo da imagem na região correspondente. O efeito é ilustrado na figura abaixo.
<div align="center">
  <img src="https://github.com/LyndonJonhson/processamento-digital-imagens/blob/main/parte%201/2%20-%20regions%20(exercicio)/fig_regions.png"
       alt="imagem exemplo para atividade 1"/>
</div>

- **Resposta:**
~~~cpp
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
~~~

No início do código é feita a leitura da imagem e logo em seguida solicita ao usuário dois pontos para definir a região da imagem que receberá o negativo. Após isso é feito o cálculo do negativo da região solicitada pelo usuário, para isso foi feito dois loops que percorrem a região definida e realiza o cálculo do negativo (255 - valor atual do pixel). A figura abaixo mostra o resultado do código para um entrada com P1(50,50) e P2(200,200).
<div align="center">
  <img src="https://github.com/LyndonJonhson/processamento-digital-imagens/blob/main/parte%201/2%20-%20regions%20(exercicio)/build/regions.png"
       alt="imagem resultado da atividade 1"/>
</div>

**Atividade 2:** Utilizando o programa [pixels.cpp](https://github.com/LyndonJonhson/processamento-digital-imagens/blob/main/parte%201/2%20-%20pixels/pixels.cpp) como referência, implemente um programa trocaregioes.cpp. Seu programa deverá trocar os quadrantes em diagonal na imagem. Explore o uso da classe cv::Mat e seus construtores para criar as regiões que serão trocadas. O efeito é ilustrado na figura abaixo. Assuma que a imagem de entrada tem dimensões múltiplas de 2 para facilitar a implementação do processo de troca.
<div align="center">
  <img src="https://github.com/LyndonJonhson/processamento-digital-imagens/blob/main/parte%201/2%20-%20trocaregioes%20(exercicio)/fig_trocaregioes.png"
       alt="imagem exemplo para atividade 2"/>
</div>

- **Resposta:**
~~~cpp
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
~~~
No inicio do código é feita a leitura da imagem, em seguida é criado quatro retângulos baseados nas dimensões da imagem e com eles faz-se 4 imagens referente aos quatro quadrantes da imagem original. É criado em seguida um cv::Mat com as mesmas dimensões da imagem original, e com as 4 imagens dos quadrantes da imagem original, é utilizada a função **copyTo** para colocar as imagens nos quadrantes trocados na imagem final, gerando por fim a mesma imagem exemplo da atividade.
