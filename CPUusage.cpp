#include <iostream>
#include <fstream>
#include <unistd.h>
#include "CPUusage.h"

bool CPUusage::getDataFromStat (const std::string& filename)
{
	std::ifstream infile(filename.c_str());
	
	if(!infile)
	{
		std::cerr 	<< "error: unable to open input file :"
				<< filename << std::endl;
		return false;
	}
	
	infile 	>> cpuname 
		>> uTime
		>> nTime
		>> sTime
		>> idleTime
		>> iowaitTime
		>> irqTime
		>> sirqTime
		>> ssTime
		>> guestTime;
	
	totalTime	= uTime
			+ nTime
			+ sTime
			+ idleTime
			+ iowaitTime
			+ irqTime
			+ sirqTime
			+ ssTime
			+ guestTime;

#ifdef __DEBUG__	
	std::cout 	<< cpuname	<<' ' 
			<< uTime	<<' '
			<< nTime	<<' '
			<< sTime	<<' '
			<< idleTime	<<' '
			<< iowaitTime	<<' '
			<< irqTime	<<' '
			<< sirqTime	<<' '
			<< ssTime	<<' '
			<< guestTime 	<< std::endl;
#endif

	infile.close();
	return true;
}
int CPUusage::calCPUusage()
//calculate cpuusage
{

	const std::string filename="/proc/stat";
	int totalCPUtime_delta;
	int idleTime_delta;
	int cpuUsedPerc = 0 ;

	bool b_got_t1 	= getDataFromStat(filename);
	int totalTime_t1= getTotalTime();
	int idleTime_t1 = getIdleTime();
	if( b_got_t1 == false) return -1;

	sleep(1);

	bool b_got_t2  	= getDataFromStat(filename);
	int totalTime_t2= getTotalTime();
	int idleTime_t2 = getIdleTime();
	if( b_got_t2 == false) return -1;
	
	totalCPUtime_delta = totalTime_t2 -totalTime_t1;
	idleTime_delta =idleTime_t2 - idleTime_t1; 
	
	if(totalCPUtime_delta != 0)
		cpuUsedPerc= 100 * (totalCPUtime_delta - idleTime_delta) / totalCPUtime_delta;
	
	return cpuUsedPerc;
}

int CPUusage::getTotalTime()
{
	return this-> totalTime;
}

int CPUusage::getIdleTime()
{
	return this-> idleTime;
}

