#ifndef PIPELINE_ENTRY_H
#define PIPELINE_ENTRY_H

#include "PipelineStep.h"
#include "PipelineDataSet.h"

class PipelineEntry : public PipelineStep {
public:
  PipelineEntry();
  PipelineEntry(const PipelineDataSet* dataSet);
  const PipelineDataSet* getDataSet();
protected:
  const PipelineDataSet* dataSet;
};

#endif
