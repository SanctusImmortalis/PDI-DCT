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
  RGBConvolutionDataSet(RGBImageData* rgbsrc, YImageData* ysrc, YImageData* msk, YImageData* ydst, RGBImageData* rgbdst) {this->rgbsource = rgbsrc; this->ysource = ysrc; this->mask = msk; this->ydest = ydst; this->rgbdest = rgbdst;}
  RGBImageData* rgbsource;
  YImageData* ysource;
  YImageData* mask;
  YImageData* ydest;
  RGBImageData* rgbdest;
  int result;
};

class RGBtoYStep : public PipelineStep{
using PipelineStep::PipelineStep;
};

class ConvolutionStep : public PipelineStep{
using PipelineStep::PipelineStep;
};

#endif
