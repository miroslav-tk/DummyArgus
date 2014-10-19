#ifndef LOADAVERAGE_H
#define LOADAVERAGE_H

#include <string>
#include "Summary.h"
class LoadAverage
{
 public:
  LoadAverage ():
      sys_total_time_(0),
      sys_idle_time_(0){}
  ~LoadAverage (){}
  bool GetDataFromUptime();
  bool CalLoadAverage(SummaryInfo& suminfo);

 private:
  float sys_total_time_;
  float sys_idle_time_;
};

#endif
