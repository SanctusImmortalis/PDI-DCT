#ifndef CONVOLUTION_STEP_H
#define CONVOLUTION_STEP_H

#define CONVOLUTION_SUCCESS 0
#define CONVOLUTION_FAIL 1
#define CONVERSION_FAIL 2

#include "PipelineStep.h"
#include "PipelineDataSet.h"
#include "ImageData.h"

class ConvolutionDataSet : public PipelineDataSet{
public:
  ConvolutionDataSet(RGBImageData* rgbsrc, YImageData* ysrc, YImageData* msk, YImageData* ydst, RGBImageData* rgbdst, int rgboffset, double yoffset) {this->rgbsource = rgbsrc; this->ysource = ysrc; this->mask = msk; this->ydest = ydst; this->rgbdest = rgbdst; this->result = CONVOLUTION_SUCCESS; this->rgboffset = rgboffset; this->yoffset = yoffset;}
  RGBImageData* rgbsource;
  YImageData* ysource;
  YImageData* mask;
  int midx, midy;
  YImageData* ydest;
  RGBImageData* rgbdest;
  int result;
  int rgboffset;
  double yoffset;
};

class RGBtoYStep : public PipelineStep{
using PipelineStep::PipelineStep;
public:
  void run();
protected:
  bool func(int x, int y, int z);
};

class ConvolutionStep : public PipelineStep{
using PipelineStep::PipelineStep;
public:
  void run();
protected:
  bool func(int x, int y, int z);
};

#endif
