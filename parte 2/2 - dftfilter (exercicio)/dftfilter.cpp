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