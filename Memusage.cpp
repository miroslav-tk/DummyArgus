#include <iostream>
#include <fstream>
#include <unistd.h>
#include "Memusage.h"

bool Memusage::GetDataFromMeminfo (const std::string& filename)
{
	std::ifstream infile(filename.c_str());
	
	if(!infile)
	{
		std::cerr 	<< "error: unable ro open input file :"
				<< filename << std::endl;
		return false;
	}

	std::string name_temp,unit_temp;

	infile 	>>name_temp 	>>mem_total_ 	>>unit_temp
		>>name_temp 	>>mem_free_ 	>>unit_temp
		>>name_temp 	>>buffers_ 	>>unit_temp
		>>name_temp 	>>cached_ 	>>unit_temp;
	
#ifdef __DEBUG__	
	std::cout 	<<mem_total_ 	<<" "
			<<mem_free_ 	<<" "
			<<buffers_ 	<<" "
			<<cached_ 	<<" "
			<<std::endl;
#endif

	infile.close();
	return true;
}

int Memusage::CalMemusage()
{
	const std::string filename="/proc/meminfo";
	int mem_used_perc = 0;

	bool b_got = GetDataFromMeminfo(filename);
	if( b_got == false ) 
	{
		return -1;
	}

	if( mem_total_ != 0 )
	{
		mem_used_perc = 100 * (mem_total_ - mem_free_ -buffers_ -cached_ )/mem_total_;	
	}

	return mem_used_perc;
}
