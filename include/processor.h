#ifndef PROCESSOR_H
#define PROCESSOR_H

class Processor {
 public:
  float Utilization();  

 private:
  long jiffiesStart{0};
  long jiffiesEnd{0};
  long activeJiffiesStart{0};
  long activeJiffiesEnd{0};
};

#endif