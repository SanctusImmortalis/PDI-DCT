#ifndef PIPELINE_ENTRY_H
#define PIPELINE_ENTRY_H

#include "PipelineStep.h"
#include "PipelineDataSet.h"

class PipelineEntry : public PipelineStep {
public:
  PipelineEntry() {this->entryPoint = this;}
  PipelineEntry(const PipelineDataSet* dataSet) { this->entryPoint = this; this->dataSet = dataSet;}
  const PipelineDataSet* getDataSet() {return this->dataSet;}
protected:
  const PipelineDataSet* dataSet;
};

#endif
