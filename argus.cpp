#include <iostream>
#include <fstream>
#include <unistd.h>
using namespace std;

typedef struct {
	int	uTime,		//user mode time
		nTime,		//nice mode time
		sTime,		//system mode time
		idleTime,	//idle time
		iowaitTime,	//iowait time
		irqTime,	//irq time
		sirqTime,	//softirq time
		ssTime,		//stealstolen time,
		guestTime,	//guest time
		totalTime;	//summary of all the time
	string 	cpuname; 	
} STATDATA;

int main()
{
	int getCPUusage();
	getCPUusage();
	return 0;
}
bool getDataFromStat(STATDATA& statData,string filename)
{
	ifstream infile(filename.c_str());
	
	if(!infile)
	{
		cerr 	<< "error: unable ro open input file :"
			<< infile << endl;
		return false;
	}
	
	infile 	>> statData. cpuname 
		>> statData. uTime
		>> statData. nTime
		>> statData. sTime
		>> statData. idleTime
		>> statData. iowaitTime
		>> statData. irqTime
		>> statData. sirqTime
		>> statData. ssTime
		>> statData. guestTime;
	
	statData.totalTime	= statData. uTime
				+ statData. nTime
				+ statData. sTime
				+ statData. idleTime
				+ statData. iowaitTime
				+ statData. irqTime
				+ statData. sirqTime
				+ statData. ssTime
				+ statData. guestTime;

#ifdef __DEBUG__	
	cout 	<< statData. cpuname	<<' ' 
		<< statData. uTime	<<' '
		<< statData. nTime	<<' '
		<< statData. sTime	<<' '
		<< statData. idleTime	<<' '
		<< statData. iowaitTime	<<' '
		<< statData. irqTime	<<' '
		<< statData. sirqTime	<<' '
		<< statData. ssTime	<<' '
		<< statData. guestTime 	<< endl;
#endif

	infile.close();
	return true;
}
int getCPUusage()
{

	string filename="/proc/stat";
	int totalCPUtime_delta;
	int idleTime_delta;
	int cpuusage = 0 ;
	STATDATA statData_t1,statData_t2;

	bool b_got_t1 = getDataFromStat(statData_t1,filename.c_str());
	if( b_got_t1 == false) return -1;

	sleep(1);

	bool b_got_t2 =  getDataFromStat(statData_t2,filename.c_str());
	if( b_got_t2 == false) return -1;
	
	totalCPUtime_delta = statData_t2.totalTime - statData_t1.totalTime ;
	idleTime_delta = statData_t2.idleTime - statData_t1.idleTime;
	
	if(totalCPUtime_delta != 0)
		cpuusage= 100 * (totalCPUtime_delta - idleTime_delta) / totalCPUtime_delta;
	
	cout << cpuusage << endl;
	
	return 0;
}
