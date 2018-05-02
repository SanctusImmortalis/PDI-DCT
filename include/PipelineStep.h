#ifndef PIPELINE_STEP_H
#define PIPELINE_STEP_H

#include <cstdlib>
#include "PipelineDataSet.h"

class PipelineStep {
public:
  PipelineStep() {this->nextStep = NULL; this->isSetup = false;}
  PipelineStep(PipelineStep* nextStep) {this->nextStep = nextStep; this->isSetup = false;}
  void setup(PipelineDataSet* dataSet) {if(dataSet!=NULL) {this->dataSet = dataSet; if(this->nextStep!=NULL) {(this->nextStep)->setup(this->dataSet);} this->isSetup = true;} }
  virtual void run() = 0;
protected:
  virtual bool func(int x, int y, int z) = 0;
  bool isSetup;
  PipelineDataSet* dataSet;
  PipelineStep * nextStep;
};

#endif
