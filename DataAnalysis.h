#ifndef DATAANALYSIS_H
#define DATAANALYSIS_H 
#include "Summary.h"

typedef struct{
  float val;
  std::string time;
}UsageValue;

typedef std::vector<UsageValue> UsageValueList;
typedef std::pair<std::string,UsageValueList> Usage;
typedef std::vector<Usage> UsageList;
typedef std::pair<std::string,UsageList> UsageOfHost;
typedef std::map<std::string,UsageOfHost> HostList;

class DataAnalysis
{
public:
  DataAnalysis (){}
  virtual ~DataAnalysis (){}

  void Collect(const SummaryInfo& suminfo);

private:
  SummaryInfo suminfo_;
};
#endif
