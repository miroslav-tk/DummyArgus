#include <iostream>
#include "CPUusage.h"
#include "Memusage.h"
#include "Diskusage.h"

int main(int argc, const char *argv[])
{
	CPUusage cpuusage;
	int cpu_used_perc = cpuusage.CalCPUusage();

	if(cpu_used_perc == -1)
	{
		std::cerr 	<< "function CalCPUusage doesn't work !";
	}
	else
	{
		std::cout 	<< "CPUusage: " 
				<< cpu_used_perc 	<<"%"
				<< std::endl;
	}	


	Memusage memusage;
	int mem_used_perc = memusage.CalMemusage();

	if(mem_used_perc == -1)
	{
		std::cerr 	<< "function CalMemusage doesn't work !";
	}
	else
	{
		std::cout 	<< "Memusage: " 
				<< mem_used_perc 	<<"%"
				<< std::endl;
	}

	Diskusage diskusage;
	std::string mountPoint = "/";
	int diskUsedPerc = diskusage.calDiskusage(mountPoint);

	if(diskUsedPerc == -1)
	{
		std::cerr 	<< "the path was not a mount point";
	}
	else
	{
		std::cout 	<< "Diskusage: " 
				<< diskUsedPerc 	<<"%"
				<< std::endl;
	}

	return 0;
}
