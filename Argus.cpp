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
		std::cerr 	<< "function CalCPUusage doesn't work !"
				<< std::endl ;
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
		std::cerr 	<< "function CalMemusage doesn't work !"
				<< std::endl;
	}
	else
	{
		std::cout 	<< "Memusage: " 
				<< mem_used_perc 	<<"%"
				<< std::endl;
	}

	Diskusage diskusage;
	std::string mount_point = "/home";
	int disk_used_perc = diskusage.CalDiskusage(mount_point);

	if(disk_used_perc == -1)
	{
		std::cerr 	<< "the path was not a mount point"
				<< std::endl;
	}
	else
	{
		std::cout 	<< "Diskusage: " 
				<< disk_used_perc 	<<"%"
				<< std::endl;
	}

	return 0;
}
