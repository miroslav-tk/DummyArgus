#include <iostream>
#include "CPUusage.h"
#include "Memusage.h"

int main(int argc, const char *argv[])
{
	CPUusage cpuusage;
	int cpuUsedPerc = cpuusage.calCPUusage();

	if(cpuUsedPerc == -1)
		std::cerr 	<< "function calCPUusage doesn't work !";
	else
	{
		std::cout 	<< "CPUusage: " 
				<< cpuUsedPerc 	<<"%"
				<< std::endl;
	}	


	Memusage memusage;
	int memUsedPerc = memusage.calMemusage();

	if(memUsedPerc == -1)
		std::cerr 	<< "function calMemusage doesn't work !";
	else
	{
		std::cout 	<< "Memusage: " 
				<< memUsedPerc 	<<"%"
				<< std::endl;
	}

	return 0;
}
