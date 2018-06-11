#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include "include/DCTStep.h"
#include "include/ImageData.h"
#include "include/EigenLab.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "include/stb_image_write.h"

using namespace std;
using namespace Eigen;
using namespace EigenLab;

RGBImageData* rgbsource;
MonoImageData* ysource;
RGBImageData* rgbfreq;
MonoImageData* yfreq;
MonoImageData* ydest;
RGBImageData* rgbdest;

int main(int argc, char** argv){
  DCTDataSet* dataSet;

  rgbsource = new RGBImageData("lena256color.jpg");
  ysource = new MonoImageData("lena256.jpg");
  yfreq = new MonoImageData(rgbsource->getWidth(), rgbsource->getHeight());
  rgbfreq = new RGBImageData(rgbsource->getWidth(), rgbsource->getHeight());
  ydest = new MonoImageData(rgbsource->getWidth(), rgbsource->getHeight());
  rgbdest = new RGBImageData(rgbsource->getWidth(), rgbsource->getHeight());


  int w = rgbdest->getWidth();
  int h = rgbdest->getHeight();
  stbi_write_png("rgbout.png", w, h, 3, rgbdest->getRawData(), w * 3);

  stbi_write_png("yout.png", w, h, 1, ydest->getRawData(), w);

  return 0;
}
