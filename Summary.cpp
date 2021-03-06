#include <string>
#include <unistd.h>
#include "Summary.h"


SummaryInfo Summary::get_suminfo()
{
  return suminfo_;
}

//struct tm* Summary::GetTime()
//{
//time_t rawtime;
//struct tm* timeinfo;

//time(&rawtime);
//timeinfo = gmtime(&rawtime);
////线程安全版本
////timeinfo = gmtime_r(&rawtime,timeinfo);
//return timeinfo;
//}

bool Summary::CreateSummaryInfo(const std::string& content,
                                const float& val)
{
  char hname[20];
  gethostname(hname,20);
  suminfo_.hostname = std::string(hname);
  suminfo_.content = content;
  suminfo_.val = val;
  suminfo_.time = boost::posix_time::to_simple_string(boost::posix_time::second_clock::local_time()); 

  return true;
}
