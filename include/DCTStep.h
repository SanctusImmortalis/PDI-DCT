#ifndef DCT_STEP_H
#define DCT_STEP_H

#include "ImageData.h"
#include "PipelineDataSet.h"
#include "PipelineStep.h"
#include <cstdlib>

typedef struct {
  int x;
  int y;
} ImageCoords;

class DCTDataSet : public PipelineDataSet{
public:
  DCTDataSet(RGBImageData* rgbsrc, MonoImageData* ysrc, MonoImageData* ydst, RGBImageData* rgbdst) { this->rgbsource = rgbsrc; this->ysource = ysrc; this->ydest = ydst; this->rgbdest = rgbdst; this->rgbfreq = new RGBImageData(rgbsrc->getWidth(), rgbsrc->getHeight()); this->yfreq = new MonoImageData(ysrc->getWidth(), ysrc->getHeight());
    this->rgbaux = new RGBImageData(rgbsrc->getWidth(), rgbsrc->getHeight()); this->yaux = new MonoImageData(ysrc->getWidth(), ysrc->getHeight()); this->rgbaux2 = new RGBImageData(rgbsrc->getWidth(), rgbsrc->getHeight()); this->yaux2 = new MonoImageData(ysrc->getWidth(), ysrc->getHeight());
    this->r = (ImageCoords*) calloc(rgbsrc->getWidth()* rgbsrc->getHeight(), sizeof(ImageCoords)); this->g =  (ImageCoords*) calloc(rgbsrc->getWidth()* rgbsrc->getHeight(), sizeof(ImageCoords)); this->b = (ImageCoords*) calloc(rgbsrc->getWidth()* rgbsrc->getHeight(), sizeof(ImageCoords));
    this->mono = (ImageCoords*) calloc(ysrc->getWidth()* ysrc->getHeight(), sizeof(ImageCoords)); this->nOfFreqs = 0;
    this->rmask = new MonoImageData(ysrc->getWidth(), ysrc->getHeight()); this->gmask = new MonoImageData(ysrc->getWidth(), ysrc->getHeight()); this->bmask = new MonoImageData(ysrc->getWidth(), ysrc->getHeight());
    this->monomask = new MonoImageData(ysrc->getWidth(), ysrc->getHeight());
  }
  RGBImageData* rgbsource;
  MonoImageData* ysource;
  RGBImageData* rgbfreq;
  MonoImageData* yfreq;
  RGBImageData* rgbaux;
  MonoImageData* yaux;
  RGBImageData* rgbaux2;
  MonoImageData* yaux2;
  MonoImageData* ydest;
  RGBImageData* rgbdest;
  ImageCoords* r;
  ImageCoords* g;
  ImageCoords* b;
  ImageCoords* mono;
  MonoImageData* rmask;
  MonoImageData* gmask;
  MonoImageData* bmask;
  MonoImageData* monomask;
  int nOfFreqs;
};

class DCTStep1 : public PipelineStep{
using PipelineStep::PipelineStep;
public:
  void run();
protected:
  bool func(int x, int y, int z);
};

class DCTStep2 : public PipelineStep{
using PipelineStep::PipelineStep;
public:
  void run();
protected:
  bool func(int x, int y, int z);
};

class SelectionStep : public PipelineStep{
using PipelineStep::PipelineStep;
public:
  void run();
protected:
  bool func(int x, int y, int z);
};

class IDCTStep1 : public PipelineStep{
using PipelineStep::PipelineStep;
public:
  void run();
protected:
  bool func(int x, int y, int z);
};

class IDCTStep2 : public PipelineStep{
using PipelineStep::PipelineStep;
public:
  void run();
protected:
  bool func(int x, int y, int z);
};

#endif
