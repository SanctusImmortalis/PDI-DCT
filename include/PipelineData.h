#ifndef PIPELINE_DATA_H
#define PIPELINE_DATA_H

template <class T>
class PipelineData{
public:
  PipelineData() {}
  PipelineData(T rawData) {this->rawData = rawData;}
  T getRawData() {return this->rawData;}
protected:
  T rawData;
};

#endif
