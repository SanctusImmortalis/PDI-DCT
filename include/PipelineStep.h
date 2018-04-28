#ifndef PIPELINE_STEP_H
#define PIPELINE_STEP_H

class PipelineInstanceID {
public:
  virtual PipelineInstanceID();
};

class PipelineStep {
public:
  virtual PipelineStep();
  virtual run();
protected:
  PipelineInstanceID id;
  const PipelineStep * entryPoint;
  const PipelineStep * nextStep;
};

#endif
