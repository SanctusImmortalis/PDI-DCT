#ifndef PIPELINE_STEP_H
#define PIPELINE_STEP_H

typedef struct{
 unsigned int x;
 unsigned int y;
 unsigned int z;
} PipelineInstanceID;

class PipelineStep {
public:
  PipelineStep() {}
  PipelineStep(PipelineInstanceID id, PipelineStep* entryPoint, PipelineStep* nextStep) {this->id = id; this->entryPoint = entryPoint; this->nextStep = nextStep;}
  virtual run() = 0;
protected:
  PipelineInstanceID id;
  const PipelineStep * entryPoint;
  const PipelineStep * nextStep;
};

#endif
