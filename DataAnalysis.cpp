#include <iostream>
#include "DataAnalysis.h"

void DataAnalysis::Collect(const SummaryInfo& suminfo)
{
  UsageValue usage_value;
  usage_value.val = suminfo.val;
  usage_value.time = suminfo.time;

  UsageValueList usage_values;
  usage_values.push_back(usage_value);
  
  Usage usage;
  usage.first = suminfo.content;
  usage.second = usage_values;

  UsageList usage_list;
  usage_list.push_back(usage);

  UsageOfHost usage_of_host;
  usage_of_host.first = suminfo.hostname;
  usage_of_host.second = usage_list;

  HostList host_list;
  host_list.insert(std::map<std::string,UsageOfHost>::value_type(suminfo.hostname,
                                                                 usage_of_host));

}

