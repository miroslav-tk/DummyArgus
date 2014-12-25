#include <iostream>
#include "DataAnalysis.h"

void DataAnalysis::Collect(const SummaryInfo& suminfo)
{
  usage_value_.val = suminfo.val;
  usage_value_.time = suminfo.time;

  usage_values_.push_back(usage_value_);
  
  usage_.first = suminfo.content;
  usage_.second = usage_values_;

  usage_list_.push_back(usage_);

  host_list_.insert(HostList::value_type(suminfo.hostname,
                                         usage_list_));
}

void DataAnalysis::get_host_list()
{
  
  std::string hostname,content,time;
  float val;
  for (HostList::const_iterator h_it = host_list_.begin();
       h_it != host_list_.end(); 
       ++h_it) 
  {
    hostname = (*h_it).first;
    for (UsageList::const_iterator u_it =(*h_it).second.begin();
         u_it != (*h_it).second.end(); 
         ++u_it) 
    {
       content = (*u_it).first;
       for (UsageValueList::const_iterator uv_it = (*u_it).second.begin();
            uv_it != (*u_it).second.end();
            ++uv_it) 
       {
         val = (*uv_it).val;
         time = (*uv_it).time;

         std::cout << "[host:"<<hostname <<"]" << std::endl;
         std::cout << "\t<Content: "<<content<<">" << std::endl;
         std::cout << "\t\t"<<val<<"\t\t"<<time << std::endl;
       }
       
    }
    

  }
   
}
