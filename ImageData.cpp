#include <cstdlib>
#include "include/ImageData.h"
#define STB_IMAGE_IMPLEMENTATION
#include "include/stb_image.h"

RGBImageData::RGBImageData(char const* filename){
  this->rawData = stbi_load(filename, &(this->width), &(this->height), &(this->nOfChannels), 3);
}

RGBImageData::RGBImageData(int x, int y){
  if(x>=0 && y>=0){
    this->width = x;
    this->height = y;
    this->nOfChannels = 3;
    this->rawData = (unsigned char*) calloc(3*x*y, 1);
  }else{
    this->width = -1;
    this->height = -1;
    this->nOfChannels = 0;
    this->rawData = NULL;
  }
}

RGBImageData::~RGBImageData(){
  stbi_image_free(this->rawData);
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
  arr[coord] = pixel.r;
  arr[coord + 1] = pixel.g;
  arr[coord + 2] = pixel.b;
  return true;
}
