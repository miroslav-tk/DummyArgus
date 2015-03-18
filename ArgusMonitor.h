#ifndef ARGUSMONITOR_H
#define ARGUSMONITOR_H
#include "DataAnalysis.h" 
class ArgusMonitor
{
public:
  ArgusMonitor (){};
  virtual ~ArgusMonitor (){};

  void ThresholdAlarm(const HostList& host_list);
private:
  /* data */
};
#endif
