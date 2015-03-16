#ifndef ARGUSMONITOR_H
#define ARGUSMONITOR_H
#include "ArgusServer.h"
using namespace argusserver;
class ArgusMonitor
{
public:
  ArgusMonitor (){};
  virtual ~ArgusMonitor (){};

  void ThresholdAlarm(const DataAnalysisPtr& analysis_ptr);
private:
  /* data */
};
#endif
