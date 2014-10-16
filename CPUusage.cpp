#include <iostream>
#include <fstream>
#include <unistd.h>
#include "CPUusage.h"

bool CPUusage::GetDataFromStat (const std::string& filename)
{
	std::ifstream infile(filename.c_str());
	
	if(!infile)
	{
		std::cerr 	<< "error: unable to open input file :"
				<< filename << std::endl;
		return false;
	}
	
	infile 	>> cpuname_ 
		>> user_time_
		>> nice_time_
		>> sys_time_
		>> idle_time_
		>> iowait_time_
		>> irq_time_
		>> sirq_time_
		>> steals_stolen_time_
		>> guest_time_;
	
	total_time_	= user_time_
			+ nice_time_
			+ sys_time_
			+ idle_time_
			+ iowait_time_
			+ irq_time_
			+ sirq_time_
			+ steals_stolen_time_
			+ guest_time_;

#ifdef __DEBUG__	
	std::cout 	<< cpuname_	<<' ' 
			<< user_time_	<<' '
			<< nice_time_	<<' '
			<< sys_time_	<<' '
			<< idle_time_	<<' '
			<< iowait_time_	<<' '
			<< irq_time_	<<' '
			<< sirq_time_	<<' '
			<< steals_stolen_time_	<<' '
			<< guest_time_ 	<< std::endl;
#endif

	infile.close();
	return true;
}
int CPUusage::CalCPUusage()
//calculate cpuusage
{

	const std::string filename="/proc/stat";
	int total_cputime_delta;
	int idle_time_delta;
	int cpu_used_perc = 0 ;

	bool b_got_t1 	= GetDataFromStat(filename);
	int total_time_t1= get_total_time();
	int idle_time_t1 = get_idle_time();
	if( b_got_t1 == false) 
	{
		return -1;
	}
	sleep(1);

	bool b_got_t2  	= GetDataFromStat(filename);
	int total_time_t2= get_total_time();
	int idle_time_t2 = get_idle_time();
	if( b_got_t2 == false)
	{
		return -1;
	}
	total_cputime_delta = total_time_t2 - total_time_t1;
	idle_time_delta =idle_time_t2 - idle_time_t1; 
	
	if(total_cputime_delta != 0)
	{
		cpu_used_perc= 100 * (total_cputime_delta - idle_time_delta) / total_cputime_delta;
	}
	return cpu_used_perc;
}

int CPUusage::get_total_time()
{
	return this-> total_time_;
}

int CPUusage::get_idle_time()
{
	return this-> idle_time_;
}

