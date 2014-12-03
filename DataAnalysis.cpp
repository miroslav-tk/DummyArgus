#include <iostream>
#include "DataAnalysis.h"

void DataAnalysis::Collect(const SummaryInfo& suminfo)
{
  std::deque<float> cpuusage;
  cpuusage.push_back(suminfo.val);
  std::pair<std::string,std::deque<float> > cpu(suminfo.content,cpuusage);
  std::cout <<cpu.first <<" "<<cpu.second.front() << std::endl;
}

