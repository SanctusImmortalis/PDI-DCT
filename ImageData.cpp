#include <cstdlib>
#include "include/ImageData.h"
#define STB_IMAGE_IMPLEMENTATION
#include "include/stb_image.h"

unsigned char clampRGB(int p){
  if(p<0) return (unsigned char) 0;
  else if(p>255) return (unsigned char) 255;
  else return (unsigned char) p;
}

double clampY(double p){
  if(p<0.0f) return 0.0f;
  else if(p>1.0f) return 1.0f;
  else return p;
}

RGBImageData::RGBImageData(char const* filename){
  this->rawData = stbi_load(filename, &(this->width), &(this->height), &(this->nOfChannels), 3);
  this->fromSTBI = true;
  this->fromCALLOC = false;
}

RGBImageData::RGBImageData(int x, int y){
  if(x>=0 && y>=0){
    this->width = x;
    this->height = y;
    this->nOfChannels = 3;
    this->rawData = (unsigned char*) calloc(3*x*y, sizeof(unsigned char));
    this->fromCALLOC = true;
  }else{
    this->width = -1;
    this->height = -1;
    this->nOfChannels = 0;
    this->rawData = NULL;
    this->fromCALLOC = false;
  }
  this->fromSTBI = false;
}

RGBImageData::~RGBImageData(){
  if(fromSTBI) stbi_image_free(this->rawData);
  else if(fromCALLOC) free(this->rawData);
}

RGBPixel RGBImageData::getPixel(int x, int y){
  RGBPixel pix;
  if(isOutOfBounds(x, y)){
    pix.r = pix.g = pix.b = 0;
  }else{
    int coord = (x + y*(this->width))*3;
    unsigned char* arr = this->rawData;
    pix.r = arr[coord];
    pix.g = arr[coord + 1];
    pix.b = arr[coord + 2];
  }
  return pix;
}

bool RGBImageData::setPixel(RGBPixel pixel, int x, int y){
  if(isOutOfBounds(x, y)){
    return false;
  }
  int coord = (x + y*(this->width))*3;
  unsigned char* arr = this->rawData;
  arr[coord] = clampRGB(pixel.r);
  arr[coord + 1] = clampRGB(pixel.g);
  arr[coord + 2] = clampRGB(pixel.b);
  return true;
}

YImageData::YImageData(int x, int y){
  if(x>=0 && y>=0){
    this->width = x;
    this->height = y;
    this->rawData = (double*) calloc(x*y, sizeof(double));
    this->fromCALLOC = true;
  }else{
    this->width = -1;
    this->height = -1;
    this->rawData = NULL;
    this->fromCALLOC = false;
  }
}

YImageData::~YImageData(){
  if(this->fromCALLOC) free(this->rawData);
}

double YImageData::getPixel(int x, int y){
  if(isOutOfBounds(x, y)){
    return 0.0f;
  }else{
    int coord = (x + y*(this->width));
    double* arr = this->rawData;
    return arr[coord];
  }
}

bool YImageData::setPixel(double pixel, int x, int y){
  if(isOutOfBounds(x, y)){
    return false;
  }
  int coord = (x + y*(this->width));
  double* arr = this->rawData;
  arr[coord] = pixel;
  return true;
}
