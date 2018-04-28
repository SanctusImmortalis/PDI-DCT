#ifndef PIPELINE_DATA_H
#define PIPELINE_DATA_H

template <class T>
class PipelineData{
public:
  virtual PipelineData();
  virtual PipelineData(T rawData);
  virtual T getRawData();
private:
  T data;
};

#endif
