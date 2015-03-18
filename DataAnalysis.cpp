#include <iostream>
#include "DataAnalysis.h"

void DataAnalysis::Collect(const SummaryInfo& suminfo)
{
  usage_value_.val = suminfo.val;
  usage_value_.time = suminfo.time;

  host_list_[suminfo.hostname][suminfo.content].push_back(usage_value_);
}

void  DataAnalysis::get_host_list(HostList& host_list)
{
  host_list=host_list_;
}

void DataAnalysis::PrintHostList()
{
  
  std::string hostname,content,time;
  float val;
  for (HostList::const_iterator h_it = host_list_.begin();
       h_it != host_list_.end(); 
       ++h_it) 
  {
    hostname = (*h_it).first;
    std::cout << "[host:"<<hostname <<"]" << std::endl;
    for (UsageList::const_iterator u_it =(*h_it).second.begin();
         u_it != (*h_it).second.end(); 
         ++u_it) 
    {
       content = (*u_it).first;
       std::cout << "\t<Content: "<<content<<">" << std::endl;
       for (UsageValueList::const_iterator uv_it = (*u_it).second.begin();
            uv_it != (*u_it).second.end();
            ++uv_it) 
       {
         val = (*uv_it).val;
         time = (*uv_it).time;

         std::cout << "\t\t"<<val<<"\t\t"<<time << std::endl;
       }
       
    }
    

  }
   
}
