#include <string>
#include <unistd.h>
#include "Summary.h"


  SummaryInfo Summary::get_suminfo()
  {
    return suminfo_;
  }

  SummaryInfo& Summary::set_suminfo(const SummaryInfo& suminfo)
  {
    suminfo_.hostname = suminfo.hostname;
    suminfo_.content = suminfo.content;
    suminfo_.val = suminfo.val;
    suminfo_.time = suminfo.time;
    return suminfo_;
  }

struct tm* Summary::GetTime()
{
 time_t rawtime;
 struct tm* timeinfo;

 time(&rawtime);
 timeinfo = gmtime(&rawtime);
 //线程安全版本
 //timeinfo = gmtime_r(&rawtime,timeinfo);
 return timeinfo;
}

bool Summary::CreateSummaryInfo(const std::string& content,
                                const int& cpu_used_perc)
{
  SummaryInfo suminfo;
  char hname[20];
  gethostname(hname,20);
  suminfo.hostname = std::string(hname);
  suminfo.content = content;
  suminfo.val = cpu_used_perc;
  suminfo.time = asctime( GetTime());

  this->set_suminfo(suminfo);

  return true;
}
