#ifndef IMAGE_DATA_H
#define IMAGE_DATA_H

#include "PipelineData.h"

class RGBImageData : public PipelineData<unsigned char*>{
using PipelineData<unsigned char*>::PipelineData;
public:
  RGBImageData(char const* filename);
protected:
  int width, height, nOfChannels;
};

class YImageData : public PipelineData<double*>{
using PipelineData<double*>::PipelineData;
public:
  YImageData(RGBImageData* rgbImage);
protected:
  int width, height;
};

#endif
