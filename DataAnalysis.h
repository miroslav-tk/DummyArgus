#ifndef DATAANALYSIS_H
#define DATAANALYSIS_H 
#include "Summary.h"
#include <boost/shared_ptr.hpp>

typedef struct{
  float val;
  std::string time;
}UsageValue;

typedef std::vector<UsageValue> UsageValueList;
typedef boost::shared_ptr<UsageValueList> UsageValueListPtr;
typedef std::map<std::string,UsageValueList> UsageList;
//typedef std::pair<std::string,UsageList> UsageOfHost;
typedef std::map<std::string,UsageList> HostList;

class DataAnalysis
{
public:
  DataAnalysis (){}
  virtual ~DataAnalysis (){}

  void Collect(const SummaryInfo& suminfo);
  void GetUVListByContent();
  void PrintHostList();

private:
  UsageValue usage_value_;        
  HostList host_list_;
  SummaryInfo suminfo_;
};
#endif
