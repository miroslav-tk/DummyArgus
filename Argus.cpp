#include <iostream>
#include "CPUusage.h"
#include "Memusage.h"
#include "Diskusage.h"

int main(int argc, const char *argv[])
{
  SummaryInfo suminfo;
  std::cout
      << "HOSTNAME "
      << "CONTENT "
      << "VALUE "
      << "TIME "
      << std::endl;

	CPUusage cpuusage;
	bool b_got_cpu = cpuusage.CalCPUusage(suminfo);
	if(!b_got_cpu)
	{
		std::cerr 	<< "function CalCPUusage doesn't work !"
				<< std::endl ;
	}
	else
	{
    std::cout
        << suminfo.hostname   <<" "
        << suminfo.content    <<" "
        << suminfo.val        <<" "
        << suminfo.time       <<" "
        << std::endl;
	}	


  Memusage memusage;
	bool b_got_mem = memusage.CalMemusage(suminfo);
	if(!b_got_mem)
  {
    std::cerr 	<< "function CalMemusage doesn't work !"
        << std::endl;
  }
  else
  {
    std::cout
        << suminfo.hostname   <<" "
        << suminfo.content    <<" "
        << suminfo.val        <<" "
        << suminfo.time       <<" "
        << std::endl;
  }

  Diskusage diskusage;
  std::string mount_point = "/home";
  bool b_got_disk= diskusage.CalDiskusage(mount_point,suminfo);

  if(!b_got_disk)
  {
    std::cerr 	<< "the path was not a mount point"
        << std::endl;
  }
  else
  {
    std::cout
        << suminfo.hostname   <<" "
        << suminfo.content    <<" "
        << suminfo.val        <<" "
        << suminfo.time       <<" "
        << std::endl;
  }
	return 0;
}
