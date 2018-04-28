#ifndef PIPELINE_STEP_H
#define PIPELINE_STEP_H

typedef struct{
 unsigned int x;
 unsigned int y;
 unsigned int z;
} PipelineInstanceID;

class PipelineStep {
public:
  PipelineStep(PipelineInstanceID id);
  virtual run();
protected:
  PipelineInstanceID id;
  const PipelineStep * entryPoint;
  const PipelineStep * nextStep;
};

#endif
