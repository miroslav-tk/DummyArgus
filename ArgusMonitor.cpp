#include "ArgusMonitor.h"
#include "ArgusServer.h"
#include <unistd.h>

void ArgusMonitor::ThresholdAlarm(const SummaryInfo& suminfo)
{
  if((suminfo.content.compare("cpuusage") == 0)
     && suminfo.val > kCpuusage_max)
  {
      std::cerr <<"["<<suminfo.hostname
                <<"]\t\t[CPUUSAGE]\t\t["
                <<  suminfo.time
                <<"][val= "
                <<  suminfo.val
                <<"]"<< std::endl;
  }
  if((suminfo.content.compare("Memusage") == 0)
     && suminfo.val > kMemusage_max)
  {
      std::cerr <<"["<<suminfo.hostname
                <<"]\t\t[MEMUSAGE]\t\t["
                <<  suminfo.time
                <<"][val= "
                <<  suminfo.val
                <<"]"<< std::endl;
  }
  if((suminfo.content.compare("Diskusage") == 0)
     && suminfo.val > kDiskusage_max)
  {
      std::cerr <<"["<<suminfo.hostname
                <<"]\t\t[DISKUSAGE]\t\t["
                <<  suminfo.time
                <<"][val= "
                <<  suminfo.val
                <<"]"<< std::endl;
  }
  if((suminfo.content.compare("LoadAverage") ==0)
     && suminfo.val > kLoadaverage_max)
  {
      std::cerr <<"["<<suminfo.hostname
                <<"]\t\t[LOADAVERAGE]\t\t["
                <<  suminfo.time
                <<"][val= "
                <<  suminfo.val
                <<"]"<< std::endl;
  }
}

void ArgusMonitor::Monitor(const HostList* host_list_ptr )
{
  std::string hostname,content,time;
  float val;
  //std::cout << "in Monitor, host_list_ptr="<<host_list_ptr << std::endl;
  while(1)
  {
    for (HostList::const_iterator h_it = (*host_list_ptr).begin();
         h_it != (*host_list_ptr).end(); 
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
    std::cout << "--------------------------------------------------------------------" << std::endl;
    sleep(3);
  }
}
