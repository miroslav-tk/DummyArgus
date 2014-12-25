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
//typedef std::pair<std::string,UsageList> UsageOfHost;
typedef std::map<std::string,UsageList> HostList;

class DataAnalysis
{
public:
  DataAnalysis (){}
  virtual ~DataAnalysis (){}

  void Collect(const SummaryInfo& suminfo);
  void get_host_list();

private:
  UsageValue usage_value_;        
  UsageValueList usage_values_;
  Usage usage_;
  UsageList usage_list_;
  HostList host_list_;
  SummaryInfo suminfo_;
};
#endif
