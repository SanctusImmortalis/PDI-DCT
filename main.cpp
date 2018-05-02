#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include "include/ConvolutionStep.h"
#include "include/ImageData.h"
#include "include/EigenLab.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "include/stb_image_write.h"

using namespace std;
using namespace Eigen;
using namespace EigenLab;

RGBImageData* rgbsource;
YImageData* ysource;
YImageData* mask;
YImageData* ydest;
RGBImageData* rgbdest;

ConvolutionDataSet* dataSet;

RGBtoYStep* step1;
ConvolutionStep* step2;

int main(int argc, char** argv){
  if(argc!=3) return -2;
  ifstream fileinput;
  stringstream stringinput;
  fileinput.open("mask.txt");
  stringinput << fileinput.rdbuf();
  fileinput.close();
  string expr;
  expr = stringinput.str();
  Parser<MatrixXd> parserXd;
  Value<MatrixXd> resultXd;
  resultXd = parserXd.eval(expr);
  MatrixXd mat = resultXd.matrix();
  cout << mat;
  mat.transposeInPlace();

  rgbsource = new RGBImageData("image.png");
  ysource = new YImageData(rgbsource->getWidth(), rgbsource->getHeight());
  mask = new YImageData(mat.rows(), mat.cols());
  ydest = new YImageData(rgbsource->getWidth(), rgbsource->getHeight());
  rgbdest = new RGBImageData(rgbsource->getWidth(), rgbsource->getHeight());

  for(int i=0;i<mat.rows();i++){
    for(int j=0;j<mat.cols();j++){
      mask->setPixel(mat(i, j), i, j);
    }
  }
  dataSet = new ConvolutionDataSet(rgbsource, ysource, mask, ydest, rgbdest, atoi(argv[1]),  atof(argv[2]));
  step2 = new ConvolutionStep(NULL);
  step1 = new RGBtoYStep(step2);

  step1->setup(dataSet);

  step1->run();

  int w = rgbdest->getWidth();
  int h = rgbdest->getHeight();
  stbi_write_png("rgbout.png", w, h, 3, rgbdest->getRawData(), w * 3);

  unsigned char yinbytes[w * h];

  for(int i=0;i<w*h;i++){
    yinbytes[i] = clampRGB((int)(ydest->getPixel(i%h, i/h) * 255.0f));
  }

  stbi_write_png("yout.png", w, h, 1, yinbytes, w);

  return 0;
}
