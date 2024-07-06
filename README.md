# Processamento digital de imagens

Aqui irei mostrar as atividades desenvolvidas durante meu semestre na matéria de Processamento Digital de Imagens, matéria do curso de Engenharia da Computação da Universidade Federal do Rio Grande do Norte. O roteiro com as atividades propostas e explicações mais detalhadas sobre o funcionamento do opencv encontram-se no repositório do professor Agostinho neste [link](https://agostinhobritojr.github.io/tutorial/pdi/).

## 1. Primeira unidade

### 1.2. Manipulando pixels em uma imagem

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

### 1.3. Serialização de dados em ponto flutuante via FileStorage

**Atividade:** Utilizando o programa-exemplo [filestorage.cpp](https://github.com/LyndonJonhson/processamento-digital-imagens/blob/main/parte%201/3%20-%20filestorage/filestorage.cpp) como base, crie um programa que gere uma imagem de dimensões 256x256 pixels contendo uma senóide de 4 períodos com amplitude igual 127 desenhada na horizontal, semelhante àquela apresentada na figura abaixo. Grave a imagem no formato YML e também exporte no formato PNG, como faz o programa-exemplo. Compare os arquivos gerados, extraindo uma linha correspondente de cada imagem gravada e comparando a diferença entre elas. Trace um gráfico da diferença calculada ao longo da linha correspondente extraída nas imagens. O que você observa? Por que isso acontece?
<div align="center">
  <img src="https://github.com/LyndonJonhson/processamento-digital-imagens/blob/main/parte%201/3%20-%20filestorage/build/senoide-256.png"
       alt="imagem exemplo para atividade"/>
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
  <p>Senóide de 8 períodos</p>
  <img src="https://github.com/LyndonJonhson/processamento-digital-imagens/blob/main/parte%201/3%20-%20filestorage%20(exercicio)/build/senoide1-256.png"
       alt="senoide 8 periodos"/><br><br>
  
  <p>Senóide de 4 períodos</p>
  <img src="https://github.com/LyndonJonhson/processamento-digital-imagens/blob/main/parte%201/3%20-%20filestorage%20(exercicio)/build/senoide2-256.png"
       alt="senoide 4 periodos"/><br><br>
       
  <p>Resultado</p>
  <img src="https://github.com/LyndonJonhson/processamento-digital-imagens/blob/main/parte%201/3%20-%20filestorage%20(exercicio)/build/result.png"
       alt="resultado da subtração entre as imagens"/>
</div>

### 1.4. Decomposição de imagens em planos de bits

**Atividade:** Usando o programa [bitplanes.cpp](https://github.com/LyndonJonhson/processamento-digital-imagens/blob/main/parte%201/4%20-%20bitplanes/bitplanes.cpp) como referência para esteganografia, escreva um programa que recupere a imagem codificada de uma imagem resultante de esteganografia. Lembre-se que os bits menos significativos dos pixels da imagem fornecida deverão compor os bits mais significativos dos pixels da imagem recuperada. O programa deve receber como parâmetros de linha de comando o nome da imagem resultante da esteganografia. Teste a sua implementação com a imagem abaixo:
<div align="center">
  <img src="https://github.com/LyndonJonhson/processamento-digital-imagens/blob/main/parte%201/4%20-%20esteganografia%20(exercicio)/desafio-esteganografia.png"
       alt="imagem exemplo para atividade"/>
</div>

- **Resposta:**
~~~cpp

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
~~~
No código acima, primeiro é realizada a leitura da imagem utilizada para realização da atividade que contém uma imagem escondida. Em seguida crio uma imagem com pixels iguais a zero com as mesmas dimensões da imagem da atividade para colocar a imagem escondida nela. Foi criado um loop para percorrer toda a imagem, pegando cada pixel da imagem original, tornando seus 3 últimos bits os mais significativos e salvando no pixel da nova imagem. Com isso, a nova imagem recebe os 3 bits menos significativos da imagem original, porém na nova imagem eles são os bits mais significativos. Com isso, abaixo encontra-se a imagem descoberta que estava escondida na imagem original.
<div align="center">
  <img src="https://github.com/LyndonJonhson/processamento-digital-imagens/blob/main/parte%201/4%20-%20esteganografia%20(exercicio)/build/imagem-escondidade.png"
       alt="imagem resultado da esteganografia"/>
</div>

### 1.5. Preenchendo regiões

**Atividade 1:** Observando-se o programa [labeling.cpp](https://github.com/LyndonJonhson/processamento-digital-imagens/blob/main/parte%201/5%20-%20labeling/labeling.cpp) como exemplo, é possível verificar que caso existam mais de 255 objetos na cena, o processo de rotulação poderá ficar comprometido, visto que o tipo de dado usado para suportar imagens cinzentas permitem armazenar apenas um byte por pixel. Identifique a situação em que isso ocorre e proponha uma solução para este problema.

- **Resposta:** Ao usar a imagem com tons de cinza, o programa fica limitado a usar apenas 256 tons de cinza (0 a 255), e como o programa está pintando os objetos em cor de cinza se baseando na contagem de objetos na imagem, caso tenha mais de 255 objetos na imagem o programa estará comprometido. Para contornar isso, pode-se realizar a leitura da imagem de forma colorida (RGB) e com isso ter uma gama maior de valores para contagem.

**Atividade 2:** Aprimore o algoritmo de contagem apresentado para identificar regiões com ou sem buracos internos que existam na cena. Assuma que objetos com mais de um buraco podem existir. Inclua suporte no seu algoritmo para não contar bolhas que tocam as bordas da imagem. Não se pode presumir, a priori, que elas tenham buracos ou não.
<div align="center">
  <p>Imagem para atividade</p>
  <img src="https://github.com/LyndonJonhson/processamento-digital-imagens/blob/main/parte%201/5%20-%20labeling%20(exercicio)/bolhas.png"
       alt="imagem da atividade"/>
</div>

- **Resposta:**
~~~cpp
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
~~~
Explicando o código da resolução, primeiro foi realizada a leitura da imagem com as bolhas e realizada inicialmente a eliminação das bolhas que tocam as bordas da imagem, pois não dá pra presumir se elas tem buracos ou não. Em seguida veio a parte do código que mais quebrou cabeça, conseguir contar quais bolhas tem buracos, com a bolha podendo conter mais de um buraco. Para resolver isso, iniciei mudando a cor de fundo da imagem com o floodfill, fazendo com que o fundo da imagem e o buraco das bolhas tenham tons de cinza diferentes. Em seguida criei um loop para percorrer todos os pixels da imagem, procurando por pixels com a cor 0, quando encontrado um pixel dessa cor significa que encontramos um buraco, porém, verifico o pixel anterior também, caso o pixel anterior tenha cor 255 significa que a bolha ainda não foi contada, pois sempre modifico a cor da bolha ao contabilizá-la. Então, ao encontrar uma bolha que o pixel anterior tenha cor 0, contabilizo uma bolha com buraco e transformo a bolha e o buraco para a cor 100 usando floodfill. E nos casos em que o pixel anterior não tenha cor 255, significa que a bolha já foi contabilizada, sendo assim eu apenas modifico a cor do buraco para 100. E com isso dentro do loop contabilizando todas as bolhas com buracos da imagem. Por fim, é apenas necessário contar as bolhas que sobraram, só verificar pixels com a cor 255 e contabilizar as bolhas sem buracos. Segue abaixo a imagem resultado, com as bolhas com buraco pintadas totalmente (até os buracos) em cinza mais escuro e as bolhas sem buracos em um cinza mais claro.
<div align="center">
  <img src="https://github.com/LyndonJonhson/processamento-digital-imagens/blob/main/parte%201/5%20-%20labeling%20(exercicio)/saida-terminal.png"
       alt="imagem resultado"/>
</div>

### 1.7. Filtragem no domínio espacial I

**Atividade:** Utilizando o programa [convolucao.cpp](https://github.com/LyndonJonhson/processamento-digital-imagens/blob/main/parte%201/7%20-%20convolucao/convolucao.cpp) como referência, implemente um programa laplgauss.cpp. O programa deverá acrescentar mais uma funcionalidade ao exemplo fornecido, permitindo que seja calculado o laplaciano do gaussiano das imagens capturadas. Compare o resultado desse filtro com a simples aplicação do filtro laplaciano.

- **Resposta:**
~~~cpp
#include <iostream>
#include <opencv2/opencv.hpp>
#include "camera.hpp"

void printmask(cv::Mat &m) {
  for (int i = 0; i < m.size().height; i++) {
    for (int j = 0; j < m.size().width; j++) {
      std::cout << m.at<float>(i, j) << ",";
    }
    std::cout << std::endl;
  }
}

int main(int, char **) {
  cv::VideoCapture cap;
  int camera;
  float media[] = {0.1111, 0.1111, 0.1111, 0.1111, 0.1111,
                   0.1111, 0.1111, 0.1111, 0.1111};
  float gauss[] = {0.0625, 0.125,  0.0625, 0.125, 0.25,
                   0.125,  0.0625, 0.125,  0.0625};
  float horizontal[] = {-1, 0, 1, -2, 0, 2, -1, 0, 1};
  float vertical[] = {-1, -2, -1, 0, 0, 0, 1, 2, 1};
  float laplacian[] = {0, -1, 0, -1, 4, -1, 0, -1, 0};
  float laplacianGauss[] = {0, 0, 1, 0, 0,
                            0, 1, 2, 1, 0,
                            1, 2, -16, 2, 1,
                            0, 1, 2, 1, 0,
                            0, 0, 1, 0, 0};
  float boost[] = {0, -1, 0, -1, 5.2, -1, 0, -1, 0};

  cv::Mat frame, framegray, frame32f, frameFiltered;
  cv::Mat mask(3, 3, CV_32F);
  cv::Mat result;
  double width, height;
  int absolut;
  char key;

  camera = cameraEnumerator();
  cap.open(camera);

  if (!cap.isOpened()) 
    return -1;

  cap.set(cv::CAP_PROP_FRAME_WIDTH, 640);
  cap.set(cv::CAP_PROP_FRAME_HEIGHT, 480);

  cv::namedWindow("filtroespacial", cv::WINDOW_NORMAL);
  cv::namedWindow("original", cv::WINDOW_NORMAL);

  mask = cv::Mat(3, 3, CV_32F, media);

  absolut = 1;  // calcula absoluto da imagem

  for (;;) {
    cap >> frame;  // captura nova imagem da camera
    cv::cvtColor(frame, framegray, cv::COLOR_BGR2GRAY);
    cv::flip(framegray, framegray, 1);
    cv::imshow("original", framegray);
    framegray.convertTo(frame32f, CV_32F);
    cv::filter2D(frame32f, frameFiltered, frame32f.depth(), mask, cv::Point(1, 1), cv::BORDER_REPLICATE);
    if (absolut) {
      frameFiltered = cv::abs(frameFiltered);
    }

    frameFiltered.convertTo(result, CV_8U);

    cv::imshow("filtroespacial", result);

    key = (char)cv::waitKey(10);
    if (key == 27) break;  // tecla ESC pressionada!
    switch (key) {
      case 'a':
        absolut = !absolut;
        break;
      case 'm':
        mask = cv::Mat(3, 3, CV_32F, media);
        printmask(mask);
        break;
      case 'g':
        mask = cv::Mat(3, 3, CV_32F, gauss);
        printmask(mask);
        break;
      case 'h':
        mask = cv::Mat(3, 3, CV_32F, horizontal);
        printmask(mask);
        break;
      case 'v':
        mask = cv::Mat(3, 3, CV_32F, vertical);
        printmask(mask);
        break;
      case 'l':
        mask = cv::Mat(3, 3, CV_32F, laplacian);
        printmask(mask);
        break;
      case 'k':
        mask = cv::Mat(5, 5, CV_32F, laplacianGauss);
        printmask(mask);
        break;
      case 'b':
        mask = cv::Mat(3, 3, CV_32F, boost);
        break;
      default:
        break;
    }
  }
  return 0;
}
~~~
O código acima contém toda a base do programa [convolucao.cpp](https://github.com/LyndonJonhson/processamento-digital-imagens/blob/main/parte%201/7%20-%20convolucao/convolucao.cpp), sendo apenas adicionado a matriz do filtro laplaciano do gaussiano para ser utilizado nas imagens e também realizar a comparação com o filtro laplaciano. Abaixo estão as imagens obtidas no programa.
<div align="center">
  <p>Imagem com filtro laplaciano</p>
  <img src="https://github.com/LyndonJonhson/processamento-digital-imagens/blob/main/parte%201/7%20-%20convolucao%20(exercicio)/laplaciano.png"
       alt="laplaciano"/><br><br>

  <p>Imagem com filtro laplaciano do gaussiano</p>
  <img src="https://github.com/LyndonJonhson/processamento-digital-imagens/blob/main/parte%201/7%20-%20convolucao%20(exercicio)/laplaciano-gaussiano.png"
       alt="laplaciano do gaussiano"/>
</div>
Ao analisar as imagens, foi notado que com o filtro laplaciano do gaussiano as bordas estão bem mais evidentes do que quando foi usado o filtro laplaciano.

## 2. Segunda unidade

### 2.1. A transformada discreta de Fourier
**Atividade 1:** Utilizando os programas [dft.cpp](https://github.com/LyndonJonhson/processamento-digital-imagens/blob/main/parte%202/1%20-%20dft/dft.cpp), calcule e apresente o espectro de magnitude da imagem [senoide-256](https://github.com/LyndonJonhson/processamento-digital-imagens/blob/main/parte%202/1%20-%20dft%20(exercicio)/senoide.png).
<div align="center">
  <p>Imagem da senoide-256</p>
  <img src="https://github.com/LyndonJonhson/processamento-digital-imagens/blob/main/parte%202/1%20-%20dft%20(exercicio)/senoide.png"
       alt="senoide-256"/>
</div>

- **Resposta:**
~~~cpp
#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

void swapQuadrants(cv::Mat& image) {
  cv::Mat tmp, A, B, C, D;

  // se a imagem tiver tamanho impar, recorta a regiao para o maior
  // tamanho par possivel (-2 = 1111...1110)
  image = image(cv::Rect(0, 0, image.cols & -2, image.rows & -2));

  int centerX = image.cols / 2;
  int centerY = image.rows / 2;

  // rearranja os quadrantes da transformada de Fourier de forma que
  // a origem fique no centro da imagem
  // A B   ->  D C
  // C D       B A
  A = image(cv::Rect(0, 0, centerX, centerY));
  B = image(cv::Rect(centerX, 0, centerX, centerY));
  C = image(cv::Rect(0, centerY, centerX, centerY));
  D = image(cv::Rect(centerX, centerY, centerX, centerY));

  // swap quadrants (Top-Left with Bottom-Right)
  A.copyTo(tmp);
  D.copyTo(A);
  tmp.copyTo(D);

  // swap quadrant (Top-Right with Bottom-Left)
  C.copyTo(tmp);
  B.copyTo(C);
  tmp.copyTo(B);
}

int main(int argc, char** argv) {
  cv::Mat image, padded, complexImage;
  std::vector<cv::Mat> planos;

  image = imread(argv[1], cv::IMREAD_GRAYSCALE);
  if (image.empty()) {
    std::cout << "Erro abrindo imagem" << argv[1] << std::endl;
    return EXIT_FAILURE;
  }

  // expande a imagem de entrada para o melhor tamanho no qual a DFT pode ser
  // executada, preenchendo com zeros a lateral inferior direita.
  int dft_M = cv::getOptimalDFTSize(image.rows);
  int dft_N = cv::getOptimalDFTSize(image.cols);
  cv::copyMakeBorder(image, padded, 0, dft_M - image.rows, 0,
                     dft_N - image.cols, cv::BORDER_CONSTANT,
                     cv::Scalar::all(0));

  // prepara a matriz complexa para ser preenchida
  // primeiro a parte real, contendo a imagem de entrada
  planos.push_back(cv::Mat_<float>(padded));
  // depois a parte imaginaria com valores nulos
  planos.push_back(cv::Mat::zeros(padded.size(), CV_32F));

  // combina os planos em uma unica estrutura de dados complexa
  cv::merge(planos, complexImage);

  // calcula a DFT
  cv::dft(complexImage, complexImage);
  swapQuadrants(complexImage);

  // planos[0] : Re(DFT(image)
  // planos[1] : Im(DFT(image)
  cv::split(complexImage, planos);

  // calcula o espectro de magnitude e de fase (em radianos)
  cv::Mat magn, fase;
  cv::cartToPolar(planos[0], planos[1], magn, fase, false);
  cv::normalize(fase, fase, 0, 1, cv::NORM_MINMAX);

  // caso deseje apenas o espectro de magnitude da DFT, use:
  cv::magnitude(planos[0], planos[1], magn);

  // some uma constante para evitar log(0)
  // log(1 + sqrt(Re(DFT(image))^2 + Im(DFT(image))^2))
  magn += cv::Scalar::all(1);

  // calcula o logaritmo da magnitude para exibir
  // com compressao de faixa dinamica
  cv::log(magn, magn);
  cv::normalize(magn, magn, 0, 1, cv::NORM_MINMAX);

  // exibe as imagens processadas
  cv::imshow("Imagem", image);
  cv::imshow("Espectro de magnitude", magn);
  cv::imshow("Espectro de fase", fase);

  cv::waitKey();
  return EXIT_SUCCESS;
}
~~~
<div align="center">
  <p>Imagem do espectro de magnitude da imagem senoide-256</p>
  <img src="https://github.com/LyndonJonhson/processamento-digital-imagens/blob/main/parte%202/1%20-%20dft%20(exercicio)/build/magnitude-senoide-256.png"
       alt="espectro de magnitude da imagem senoide-256"/>
</div><br><br>

**Atividade 2:** Usando agora o [filestorage.cpp](https://github.com/LyndonJonhson/processamento-digital-imagens/blob/main/parte%201/3%20-%20filestorage/filestorage.cpp) como referência, adapte o programa [dft.cpp](https://github.com/LyndonJonhson/processamento-digital-imagens/blob/main/parte%202/1%20-%20dft/dft.cpp) para ler a imagem em ponto flutuante armazenada no arquivo YAML equivalente ([senoide-256.yml](https://github.com/LyndonJonhson/processamento-digital-imagens/blob/main/parte%201/3%20-%20filestorage/build/senoide-256.yml)).

- **Resposta:**
~~~cpp
#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

void swapQuadrants(cv::Mat& image) {
  cv::Mat tmp, A, B, C, D;

  // se a imagem tiver tamanho impar, recorta a regiao para o maior
  // tamanho par possivel (-2 = 1111...1110)
  image = image(cv::Rect(0, 0, image.cols & -2, image.rows & -2));

  int centerX = image.cols / 2;
  int centerY = image.rows / 2;

  // rearranja os quadrantes da transformada de Fourier de forma que
  // a origem fique no centro da imagem
  // A B   ->  D C
  // C D       B A
  A = image(cv::Rect(0, 0, centerX, centerY));
  B = image(cv::Rect(centerX, 0, centerX, centerY));
  C = image(cv::Rect(0, centerY, centerX, centerY));
  D = image(cv::Rect(centerX, centerY, centerX, centerY));

  // swap quadrants (Top-Left with Bottom-Right)
  A.copyTo(tmp);
  D.copyTo(A);
  tmp.copyTo(D);

  // swap quadrant (Top-Right with Bottom-Left)
  C.copyTo(tmp);
  B.copyTo(C);
  tmp.copyTo(B);
}

int main(int argc, char** argv) {
  cv::Mat image, imageGray, padded, complexImage;
  std::vector<cv::Mat> planos;
  cv::FileStorage fs;

  fs.open(argv[1], cv::FileStorage::READ);

  fs["mat"] >> image;

  cv::normalize(image, imageGray, 0, 255, cv::NORM_MINMAX);
  imageGray.convertTo(imageGray, CV_8U);
  
  if (image.empty()) {
    std::cout << "Erro abrindo imagem" << argv[1] << std::endl;
    return EXIT_FAILURE;
  }

  // expande a imagem de entrada para o melhor tamanho no qual a DFT pode ser
  // executada, preenchendo com zeros a lateral inferior direita.
  int dft_M = cv::getOptimalDFTSize(image.rows);
  int dft_N = cv::getOptimalDFTSize(image.cols);
  cv::copyMakeBorder(image, padded, 0, dft_M - image.rows, 0,
                     dft_N - image.cols, cv::BORDER_CONSTANT,
                     cv::Scalar::all(0));

  // prepara a matriz complexa para ser preenchida
  // primeiro a parte real, contendo a imagem de entrada
  planos.push_back(cv::Mat_<float>(padded));
  // depois a parte imaginaria com valores nulos
  planos.push_back(cv::Mat::zeros(padded.size(), CV_32F));

  // combina os planos em uma unica estrutura de dados complexa
  cv::merge(planos, complexImage);

  // calcula a DFT
  cv::dft(complexImage, complexImage);
  swapQuadrants(complexImage);

  // planos[0] : Re(DFT(image)
  // planos[1] : Im(DFT(image)
  cv::split(complexImage, planos);

  // calcula o espectro de magnitude e de fase (em radianos)
  cv::Mat magn, fase;
  cv::cartToPolar(planos[0], planos[1], magn, fase, false);
  cv::normalize(fase, fase, 0, 1, cv::NORM_MINMAX);

  // caso deseje apenas o espectro de magnitude da DFT, use:
  cv::magnitude(planos[0], planos[1], magn);

  // some uma constante para evitar log(0)
  // log(1 + sqrt(Re(DFT(image))^2 + Im(DFT(image))^2))
  magn += cv::Scalar::all(1);

  // calcula o logaritmo da magnitude para exibir
  // com compressao de faixa dinamica
  cv::log(magn, magn);
  cv::normalize(magn, magn, 0, 1, cv::NORM_MINMAX);

  // exibe as imagens processadas
  cv::imshow("Imagem", imageGray);
  cv::imshow("Espectro de magnitude", magn);
  cv::imshow("Espectro de fase", fase);

  cv::waitKey();
  return EXIT_SUCCESS;
}
~~~
<div align="center">
  <p>Imagem do espectro de magnitude da imagem senoide-256.yml</p>
  <img src="https://github.com/LyndonJonhson/processamento-digital-imagens/blob/main/parte%202/1%20-%20dft%20(exercicio)/build/magnitude-senoide-256-yml.png"
       alt="espectro de magnitude da imagem senoide-256.yml"/>
</div><br><br>

**Atividade 3:** Compare o novo espectro de magnitude gerado com o valor teórico da transformada de Fourier da senóide. O que mudou para que o espectro de magnitude gerado agora esteja mais próximo do valor teórico? Porque isso aconteceu?
- **Resposta:** A senoide-256.yml ficou mais próxima do valor teórico por causa das suas casas decimais extras após a vírgula, com isso tendo uma imagem mais próxima do real.

### 2.2. Filtragem no Domínio da Frequência

**Atividade:** Utilizando o programa [dftfilter.cpp](https://github.com/LyndonJonhson/processamento-digital-imagens/blob/main/parte%202/2%20-%20dftfilter/dftfilter.cpp) como referência, implemente o filtro homomórfico para melhorar imagens com iluminação irregular. Crie uma cena mal iluminada e ajuste os parâmetros do filtro homomórfico para corrigir a iluminação da melhor forma possível. Assuma que a imagem fornecida é em tons de cinza.

- **Resposta:**
~~~cpp
#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>

cv::Mat image, padded, complexImage, filter, result;
std::vector<cv::Mat> planos;
int dft_M, dft_N;
double gh, gl, d, c;
int gl_slider = 20;
int gl_slider_max = 50;
int gh_slider = 2;
int gh_slider_max = 10;
int c_slider = 1;
int c_slider_max = 100;
int d_slider = 5;
int d_slider_max = 200;

void swapQuadrants(cv::Mat& image) {
  cv::Mat tmp, A, B, C, D;

  // se a imagem tiver tamanho impar, recorta a regiao para o maior
  // tamanho par possivel (-2 = 1111...1110)
  image = image(cv::Rect(0, 0, image.cols & -2, image.rows & -2));

  int centerX = image.cols / 2;
  int centerY = image.rows / 2;

  // rearranja os quadrantes da transformada de Fourier de forma que 
  // a origem fique no centro da imagem
  // A B   ->  D C
  // C D       B A
  A = image(cv::Rect(0, 0, centerX, centerY));
  B = image(cv::Rect(centerX, 0, centerX, centerY));
  C = image(cv::Rect(0, centerY, centerX, centerY));
  D = image(cv::Rect(centerX, centerY, centerX, centerY));

  // swap quadrants (Top-Left with Bottom-Right)
  A.copyTo(tmp);
  D.copyTo(A);
  tmp.copyTo(D);

  // swap quadrant (Top-Right with Bottom-Left)
  C.copyTo(tmp);
  B.copyTo(C);
  tmp.copyTo(B);
}

void makeFilter(const cv::Mat &image, cv::Mat &filter){
  cv::Mat_<float> filter2D(image.rows, image.cols);

  for (int i = 0; i < image.rows; i++) {
    for (int j = 0; j < image.cols; j++) {
        filter2D.at<float>(i, j) = (gh - gl)*(1 - exp(-c*(( (i-dft_M/2)*(i-dft_M/2) + (j-dft_N/2)*(j-dft_N/2) ) / (d*d) ))) + gl;
    }
  }

  cv::Mat planes[] = {filter2D, filter2D};
  cv::merge(planes, 2, filter);
}

void applyFilter(){
  planos.clear();
  // prepara a matriz complexa para ser preenchida
  // primeiro a parte real, contendo a imagem de entrada
  planos.push_back(cv::Mat_<float>(padded)); 
  // depois a parte imaginaria com valores nulos
  planos.push_back(cv::Mat::zeros(padded.size(), CV_32F));

  // combina os planos em uma unica estrutura de dados complexa
  cv::merge(planos, complexImage);

  // calcula a DFT
  cv::dft(complexImage, complexImage); 
  swapQuadrants(complexImage);

  // cria o filtro ideal e aplica a filtragem de frequencia
  makeFilter(complexImage, filter);
  cv::mulSpectrums(complexImage, filter, complexImage, 0);

  // calcula a DFT inversa
  swapQuadrants(complexImage);
  cv::idft(complexImage, complexImage);

  // planos[0] : Re(DFT(image)
  // planos[1] : Im(DFT(image)
  cv::split(complexImage, planos);

  // recorta a imagem filtrada para o tamanho original
  // selecionando a regiao de interesse (roi)
  cv::Rect roi(0, 0, image.cols, image.rows);
  result = planos[0](roi);

  // normaliza a parte real para exibicao
  cv::normalize(result, result, 0, 1, cv::NORM_MINMAX);

  cv::imshow("Homomorphic", result);
  cv::imwrite("dft-filter.png", result * 255);
}

void on_trackbar(int, void*){
  gl = (double) gl_slider/10;
  gh = (double) gh_slider/10;
  c = (double) c_slider;
  d = (double) d_slider;
  applyFilter();
}

int main(int argc, char** argv) {

  image = imread(argv[1], cv::IMREAD_GRAYSCALE);

  if (image.empty()) {
    std::cout << "Erro abrindo imagem" << argv[1] << std::endl;
    return EXIT_FAILURE;
  }

  // expande a imagem de entrada para o melhor tamanho no qual a DFT pode ser
  // executada, preenchendo com zeros a lateral inferior direita.
  dft_M = cv::getOptimalDFTSize(image.rows);
  dft_N = cv::getOptimalDFTSize(image.cols); 
  cv::copyMakeBorder(image, padded, 0, dft_M - image.rows, 0, dft_N - image.cols, cv::BORDER_CONSTANT, cv::Scalar::all(0));
  
  cv::namedWindow("Homomorphic", 1);

  char TrackbarName[50];

  std::sprintf( TrackbarName, "gl x %d", gl_slider_max );
  cv::createTrackbar( TrackbarName, "Homomorphic", &gl_slider, gl_slider_max, on_trackbar);

  std::sprintf( TrackbarName, "gh x %d", gh_slider_max );
  cv::createTrackbar( TrackbarName, "Homomorphic", &gh_slider, gh_slider_max, on_trackbar);

  std::sprintf( TrackbarName, "c x %d", c_slider_max );
  cv::createTrackbar( TrackbarName, "Homomorphic", &c_slider, c_slider_max, on_trackbar);

  std::sprintf( TrackbarName, "d x %d", d_slider_max );
  cv::createTrackbar( TrackbarName, "Homomorphic", &d_slider, d_slider_max, on_trackbar);

  applyFilter();

  cv::waitKey(0);
  return EXIT_SUCCESS;
}
~~~
<div align="center">
  <p>Imagem de teclado em cena escura</p>
  <img src="https://github.com/LyndonJonhson/processamento-digital-imagens/blob/main/parte%202/2%20-%20dftfilter%20(exercicio)/teclado.png"
       alt="imagem de um teclado em uma cena escura"/><br><br>
  <p>Imagem de teclado com filtro aplicado</p>
  <img src="https://github.com/LyndonJonhson/processamento-digital-imagens/blob/main/parte%202/2%20-%20dftfilter%20(exercicio)/teclado-filtered.png"
       alt="imagem de um teclado com filtro aplicado"/>
</div>

### 2.3. Detecção de bordas com o algoritmo de Canny
**Atividade:** Utilizando os programas [canny.cpp](https://github.com/LyndonJonhson/processamento-digital-imagens/blob/main/parte%202/3%20-%20canny/canny.cpp) e [pontilhismo.cpp](https://github.com/LyndonJonhson/processamento-digital-imagens/blob/main/parte%202/3%20-%20pontilhismo/pontilhismo.cpp) como referência, implemente um programa cannypoints.cpp. A idéia é usar as bordas produzidas pelo algoritmo de Canny para melhorar a qualidade da imagem pontilhista gerada. A forma como a informação de borda será usada é livre. Entretanto, são apresentadas algumas sugestões de técnicas que poderiam ser utilizadas:

- **Resposta:**
~~~cpp
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
~~~
No código acima foi usado os códigos de canny e do pontilhismo para editar a imagem de entrada. Inicialmente foi aplicado o pontilhismo na imagem toda com raio = 1 inicialmente, após isso aplico canny para pegar as bordas e com elas aplicar também o pontilhismo, porém com raios diferentes. Então como é possível ver na imagem abaixo, é possível editar a detecção de bordas com canny e o tamanho do raio dos pontos na imagem toda e também nas bordas de forma separada.
<div align="center">
  <p>Imagem de saída do código cannypoints.cpp</p>
  <img src="https://github.com/LyndonJonhson/processamento-digital-imagens/blob/main/parte%202/3%20-%20cannypoints%20(exercicio)/image.png" />
</div>
