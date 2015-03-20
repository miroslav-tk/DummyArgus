#ifndef ARGUSMONITOR_H
#define ARGUSMONITOR_H
#include "DataAnalysis.h" 

const float kCpuusage_max=50;
const float kDiskusage_max=70;
const float kMemusage_max=70;
const float kLoadaverage_max=1;
class ArgusMonitor
{
public:
  ArgusMonitor (){};
  virtual ~ArgusMonitor (){};

  void Monitor(const HostList* host_list_ptr);
  void ThresholdAlarm(const SummaryInfo& suminfo);
private:
  /* data */
};
#endif
