#ifndef ARGUSMONITOR_H
#define ARGUSMONITOR_H
#include "ArgusServer.h"
using namespace argusserver;
class ArgusMonitor
{
public:
  ArgusMonitor (){};
  virtual ~ArgusMonitor (){};

  ThresholdAlarm(DataAl);
private:
  /* data */
};
#endif
