#ifndef PIPELINE_DATA_H
#define PIPELINE_DATA_H

template <class T>
class PipelineData{
public:
  PipelineData();
  PipelineData(T rawData);
  T getRawData();
private:
  T data;
};

#endif
