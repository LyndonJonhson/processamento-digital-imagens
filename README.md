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

### 1.2. Serialização de dados em ponto flutuante via FileStorage

**Atividade 1:** Utilizando o programa-exemplo [filestorage.cpp](https://github.com/LyndonJonhson/processamento-digital-imagens/blob/main/parte%201/3%20-%20filestorage/filestorage.cpp) como base, crie um programa que gere uma imagem de dimensões 256x256 pixels contendo uma senóide de 4 períodos com amplitude igual 127 desenhada na horizontal, semelhante àquela apresentada na figura abaixo. Grave a imagem no formato YML e também exporte no formato PNG, como faz o programa-exemplo. Compare os arquivos gerados, extraindo uma linha correspondente de cada imagem gravada e comparando a diferença entre elas. Trace um gráfico da diferença calculada ao longo da linha correspondente extraída nas imagens. O que você observa? Por que isso acontece?
<div align="center">
  <img src="https://github.com/LyndonJonhson/processamento-digital-imagens/blob/main/parte%201/3%20-%20filestorage/build/senoide-256.png"
       alt="imagem exemplo para atividade 2"/>
</div>

- **Resposta:**
~~~cpp
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
~~~
Para gerar a imagem da senóide com 4 períodos foi basicamente repetir o código existente para a senóide de período 8. Após criar a senóide de 4 períodos, foi feito uma imagem que é resultado da subtração das duas imagens das senóides. Foi identificado na imagem resultante, que nos locais em que os pixels são brancos ou pretos nas duas imagens, o resultado é a cor preta. Nos locais em que uma das imagens tem pixels pretos e a outra tem pixels brancos, o resultado é a cor branca. E nos locais em que há transição das cores, a imagem resultante ficou cinza. Segue abaixo as imagens.
<div align="center">
  <img src="https://github.com/LyndonJonhson/processamento-digital-imagens/blob/main/parte%201/3%20-%20filestorage%20(exercicio)/build/senoide1-256.png"
       alt="senoide 8 periodos"/><br>
  <img src="https://github.com/LyndonJonhson/processamento-digital-imagens/blob/main/parte%201/3%20-%20filestorage%20(exercicio)/build/senoide2-256.png"
       alt="senoide 4 periodos"/><br>
  <img src="https://github.com/LyndonJonhson/processamento-digital-imagens/blob/main/parte%201/3%20-%20filestorage%20(exercicio)/build/result.png"
       alt="resultado da subtração entre as imagens"/>
</div>
