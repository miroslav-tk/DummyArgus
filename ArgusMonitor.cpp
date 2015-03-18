#include "ArgusMonitor.h"
#include "ArgusServer.h"
#include "DataAnalysis.h"
#include <unistd.h>

void ArgusMonitor::ThresholdAlarm(const HostList& host_list )
{

  std::string hostname,content,time;
  float val;
  while(1)
  {
    for (HostList::const_iterator h_it = host_list.begin();
         h_it != host_list.end(); 
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
    std::cout << "-------------------------sleeping----------------------------" << std::endl;
    sleep(3);
  }
}
