#include <iostream>
#include <fstream>
#include "LoadAverage.h"

bool LoadAverage::GetDataFromUptime()
{

	std::ifstream infile("/proc/uptime");

	if(!infile)
	{
		std::cerr 	<< "error: unable ro open input file :"
				<< "/proc/uptime" 	<< std::endl;
		return false;
	}
  infile >> sys_total_time_ >> sys_idle_time_ ;
  return true;
}

bool LoadAverage::CalLoadAverage(SummaryInfo& suminfo)
{
  bool b_got = GetDataFromUptime();
  if(!b_got)
  {
    return false;
  }
  float load = sys_idle_time_  / (sys_total_time_ * 4 );
  Summary summary;
  summary.CreateSummaryInfo(std::string("LoadAverage"), load);
  
  suminfo = summary.get_suminfo();
	return true;
}
