#ifndef IMAGE_DATA_H
#define IMAGE_DATA_H

#include "PipelineData.h"

typedef struct{
  unsigned char r;
  unsigned char g;
  unsigned char b;
} RGBPixel;

class RGBImageData : public PipelineData<unsigned char*>{
using PipelineData<unsigned char*>::PipelineData;
public:
  RGBImageData(char const* filename);
  RGBImageData(int x, int y);
  ~RGBImageData();
  RGBPixel getPixel(int x, int y);
  bool setPixel(RGBPixel pixel, int x, int y);
  bool isOutOfBounds(int x, int y) {return (x<0)||(y<0)||(x>=(this->width))||(y>=(this->height));}
protected:
  int width, height, nOfChannels;
};

class YImageData : public PipelineData<double*>{
using PipelineData<double*>::PipelineData;
public:
  YImageData(RGBImageData* rgbImage);
  double getPixel(int x, int y);
  bool setPixel(double pixel, int x, int y);
  bool isOutOfBounds(int x, int y) {return (x<0)||(y<0)||(x>=(this->width))||(y>=(this->height));}
protected:
  int width, height;
};

#endif
