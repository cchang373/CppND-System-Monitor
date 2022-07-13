#ifndef PROCESSOR_H
#define PROCESSOR_H

class Processor {
 public:
  float Utilization();

 private:
  float PrevIdle = 0.0;
  float PrevTotal = 0.0;
};

#endif