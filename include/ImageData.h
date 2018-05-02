#ifndef IMAGE_DATA_H
#define IMAGE_DATA_H

#include "PipelineData.h"

typedef struct{
  int r;
  int g;
  int b;
} RGBPixel;

unsigned char clampRGB(int p);

double clampY(double p);

class RGBImageData : public PipelineData<unsigned char*>{
public:
  RGBImageData() {this->width = -1; this->height= -1; this->nOfChannels = 0; this->fromSTBI = false; this->fromCALLOC = false;}
  RGBImageData(unsigned char* rawData) {this->width = -1; this->height= -1; this->nOfChannels = 0; this->rawData = rawData; this->fromSTBI = false; this->fromCALLOC = false;}
  RGBImageData(char const* filename);
  RGBImageData(int x, int y);
  ~RGBImageData();
  unsigned char* getRawData() {return this->rawData;}
  RGBPixel getPixel(int x, int y);
  bool setPixel(RGBPixel pixel, int x, int y);
  int getWidth() {return this->width;}
  int getHeight() {return this->height;}
  bool isOutOfBounds(int x, int y) {return (x<0)||(y<0)||(x>=(this->width))||(y>=(this->height));}
protected:
  int width, height, nOfChannels;
  bool fromSTBI, fromCALLOC;
};

class YImageData : public PipelineData<double*>{
public:
  YImageData() {this->fromCALLOC = false;}
  YImageData(double* rawData) {this->rawData = rawData; this->fromCALLOC = false;}
  YImageData(int x, int y);
  ~YImageData();
  double* getRawData() {return this->rawData;}
  double getPixel(int x, int y);
  bool setPixel(double pixel, int x, int y);
  int getWidth() {return this->width;}
  int getHeight() {return this->height;}
  bool isOutOfBounds(int x, int y) {return (x<0)||(y<0)||(x>=(this->width))||(y>=(this->height));}
protected:
  int width, height;
  bool fromCALLOC;
};

#endif
