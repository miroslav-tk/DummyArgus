#include "ArgusMonitor.h"
#include "ArgusServer.h"
#include "DataAnalysis.h"


using namespace argusserver;

void ArgusMonitor::ThresholdAlarm(const DataAnalysisPtr& analysis_ptr)
{
  UsageValueListPtr usagevaluelist_ptr;
  analysis_ptr->PrintHostList();  
}
