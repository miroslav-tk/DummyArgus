#include <iostream>
#include <fstream>
#include <unistd.h>
#include "Memusage.h"

bool Memusage::getDataFromMeminfo (const std::string& filename)
{
	std::ifstream infile(filename.c_str());
	
	if(!infile)
	{
		std::cerr 	<< "error: unable ro open input file :"
				<< infile << std::endl;
		return false;
	}

	std::string nameTemp,unitTemp;

	infile 	>>nameTemp 	>>memTotal 	>>unitTemp
		>>nameTemp 	>>memFree 	>>unitTemp
		>>nameTemp 	>>buffers 	>>unitTemp
		>>nameTemp 	>>cached 	>>unitTemp;
	
#ifdef __DEBUG__	
	std::cout 	<<memTotal 	<<" "
			<<memFree 	<<" "
			<<buffers 	<<" "
			<<cached 	<<" "
			<<std::endl;
#endif

	infile.close();
	return true;
}

int Memusage::calMemusage()
{
	const std::string filename="/proc/meminfo";
	int memUsedPerc = 0;

	bool b_got = getDataFromMeminfo(filename);
	if( b_got == false ) return -1;

	if( memTotal != 0 )
		memUsedPerc = 100 * (memTotal - memFree -buffers -cached )/memTotal;	

	return memUsedPerc;
}
