#include "include/DCTStep.h"
#include <cmath>
#define PI 3.14f

double ck(int k){
  if(!k) return sqrt(0.5f);
  else return 1;
}

void DCTStep1::run(){
  DCTDataSet* ds = (DCTDataSet*) this->dataSet;
  if(ds!=NULL && this->isSetup && ds->rgbsource->getWidth() == ds->ysource->getWidth() && ds->rgbsource->getHeight() == ds->ysource->getHeight()){
    for(int i=0;i<ds->rgbsource->getHeight();i++){
      for(int j=0;j<ds->rgbsource->getWidth();j++){
        this->func(i, j, ds->rgbsource->getWidth());
      }
    }
    this->nextStep->run();
  }
}

bool DCTStep1::func(int x, int y, int z){
  DCTDataSet* ds = (DCTDataSet*) this->dataSet;
  RGBPixel pix;
  pix.r = 0;
  pix.g = 0;
  pix.b = 0;
  int pix2 = 0;
  for(int i=0;i<ds->rgbsource->getWidth();i++){
    pix.r += (ds->rgbsource->getPixel(i, y)).r * cos((2*PI*x*i)/(2 * z) + (x*PI)/(2*z));
    pix.g += (ds->rgbsource->getPixel(i, y)).g * cos((2*PI*x*i)/(2 * z) + (x*PI)/(2*z));
    pix.b += (ds->rgbsource->getPixel(i, y)).b * cos((2*PI*x*i)/(2 * z) + (x*PI)/(2*z));
    pix2 += (ds->ydest->getPixel(i, y)) * cos((2*PI*x*i)/(2 * z) + (x*PI)/(2*z));
  }
  pix.r *= sqrt(2.0f/z) * ck(x);
  pix.g *= sqrt(2.0f/z) * ck(x);
  pix.b *= sqrt(2.0f/z) * ck(x);
  pix2 *= sqrt(2.0f/z) * ck(x);

  ds->rgbaux->setPixel(pix, x, y);
  ds->yaux->setPixel(pix2, x, y);
  return true;
}

void DCTStep2::run(){
  DCTDataSet* ds = (DCTDataSet*) this->dataSet;
  if(ds!=NULL && this->isSetup && ds->rgbsource->getWidth() == ds->ysource->getWidth() && ds->rgbsource->getHeight() == ds->ysource->getHeight()){
    for(int i=0;i<ds->rgbsource->getWidth();i++){
      for(int j=0;j<ds->rgbsource->getHeight();j++){
        this->func(i, j, ds->rgbsource->getHeight());
      }
    }
  }
}

bool DCTStep2::func(int x, int y, int z){
  DCTDataSet* ds = (DCTDataSet*) this->dataSet;
  RGBPixel pix;
  pix.r = 0;
  pix.g = 0;
  pix.b = 0;
  int pix2 = 0;
  for(int i=0;i<ds->rgbaux->getWidth();i++){
    pix.r += (ds->rgbaux->getPixel(x, i)).r * cos((2*PI*y*i)/(2 * z) + (y*PI)/(2*z));
    pix.g += (ds->rgbaux->getPixel(x, i)).g * cos((2*PI*y*i)/(2 * z) + (y*PI)/(2*z));
    pix.b += (ds->rgbaux->getPixel(x, i)).b * cos((2*PI*y*i)/(2 * z) + (y*PI)/(2*z));
    pix2 += (ds->yaux->getPixel(x, i)) * cos((2*PI*y*i)/(2 * z) + (y*PI)/(2*z));
  }
  pix.r *= sqrt(2.0f/z) * ck(y);
  pix.g *= sqrt(2.0f/z) * ck(y);
  pix.b *= sqrt(2.0f/z) * ck(y);
  pix2 *= sqrt(2.0f/z) * ck(y);

  ds->rgbaux2->setPixel(pix, x, y);
  ds->yaux2->setPixel(pix2, x, y);
  return true;
}

void IDCTStep1::run(){
  DCTDataSet* ds = (DCTDataSet*) this->dataSet;
  if(ds!=NULL && this->isSetup && ds->rgbsource->getWidth() == ds->ysource->getWidth() && ds->rgbsource->getHeight() == ds->ysource->getHeight()){
    for(int i=0;i<ds->rgbsource->getHeight();i++){
      for(int j=0;j<ds->rgbsource->getWidth();j++){
        this->func(i, j, ds->rgbsource->getWidth());
      }
    }
    this->nextStep->run();
  }
}

bool IDCTStep1::func(int x, int y, int z){
  DCTDataSet* ds = (DCTDataSet*) this->dataSet;
  RGBPixel pix;
  pix.r = 0;
  pix.g = 0;
  pix.b = 0;
  int pix2 = 0;
  for(int i=0;i<ds->rgbdest->getWidth();i++){
    pix.r +=  ds->rmask->getPixel(i, y) * ck(x) * (ds->rgbaux2->getPixel(i, y)).r * cos((2*PI*x*i)/(2 * z) + (x*PI)/(2*z));
    pix.g += ds->gmask->getPixel(i, y) * ck(x) * (ds->rgbaux2->getPixel(i, y)).g * cos((2*PI*x*i)/(2 * z) + (x*PI)/(2*z));
    pix.b += ds->bmask->getPixel(i, y) * ck(x) * (ds->rgbaux2->getPixel(i, y)).b * cos((2*PI*x*i)/(2 * z) + (x*PI)/(2*z));
    pix2 += ds->monomask->getPixel(i, y) * ck(x) * ds->yaux2->getPixel(i, y) * cos((2*PI*x*i)/(2 * z) + (x*PI)/(2*z));
  }
  pix.r *= sqrt(2.0f/z);
  pix.g *= sqrt(2.0f/z);
  pix.b *= sqrt(2.0f/z);
  pix2 *= sqrt(2.0f/z);

  ds->rgbaux->setPixel(pix, x, y);
  ds->yaux->setPixel(pix2, x, y);
  return true;
}

void IDCTStep2::run(){
  DCTDataSet* ds = (DCTDataSet*) this->dataSet;
  if(ds!=NULL && this->isSetup && ds->rgbsource->getWidth() == ds->ysource->getWidth() && ds->rgbsource->getHeight() == ds->ysource->getHeight()){
    for(int i=0;i<ds->rgbsource->getWidth();i++){
      for(int j=0;j<ds->rgbsource->getHeight();j++){
        this->func(i, j, ds->rgbsource->getHeight());
      }
    }
  }
}

bool IDCTStep2::func(int x, int y, int z){
  DCTDataSet* ds = (DCTDataSet*) this->dataSet;
  RGBPixel pix;
  pix.r = 0;
  pix.g = 0;
  pix.b = 0;
  int pix2 = 0;
  for(int i=0;i<ds->rgbaux->getWidth();i++){
    pix.r += ck(y) * (ds->rgbaux->getPixel(x, i)).r * cos((2*PI*y*i)/(2 * z) + (y*PI)/(2*z));
    pix.g += ck(y) * (ds->rgbaux->getPixel(x, i)).g * cos((2*PI*y*i)/(2 * z) + (y*PI)/(2*z));
    pix.b += ck(y) * (ds->rgbaux->getPixel(x, i)).b * cos((2*PI*y*i)/(2 * z) + (y*PI)/(2*z));
    pix2 += ck(y) * ds->yaux->getPixel(x, i) * cos((2*PI*y*i)/(2 * z) + (y*PI)/(2*z));
  }
  pix.r *= sqrt(2.0f/z);
  pix.g *= sqrt(2.0f/z);
  pix.b *= sqrt(2.0f/z);
  pix2 *= sqrt(2.0f/z);

  ds->rgbdest->setPixel(pix, x, y);
  ds->ydest->setPixel(pix2, x, y);
  return true;
}

void SelectionStep::run(){
  DCTDataSet* ds = (DCTDataSet*) this->dataSet;
  if(ds!=NULL && this->isSetup && ds->rgbsource->getWidth() == ds->ysource->getWidth() && ds->rgbsource->getHeight() == ds->ysource->getHeight()){
    for(int i=0;i<ds->rgbsource->getWidth();i++){
      for(int j=0;j<ds->rgbsource->getHeight();j++){

      }
    }
  }
}

bool SelectionStep::func(int x, int y, int z){
  return true;
}
