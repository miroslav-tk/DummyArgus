#include <iostream>
#include <fstream>
#include <unistd.h>
using namespace std;

typedef struct {
	string 	cpuname; 	
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
} STATDATA;

int main()
{
	int getCPUusage();
	getCPUusage();
	return 0;
}
STATDATA* getDataFromStat(string filename)
{
	ifstream infile(filename.c_str());
	
	if(!infile)
	{
		cerr 	<< "error: unable ro open input file :"
			<< infile << endl;
		return NULL;
	}
	
	STATDATA* statPtr = new STATDATA;
	infile 	>> statPtr-> cpuname 
		>> statPtr-> uTime
		>> statPtr-> nTime
		>> statPtr-> sTime
		>> statPtr-> idleTime
		>> statPtr-> iowaitTime
		>> statPtr-> irqTime
		>> statPtr-> sirqTime
		>> statPtr-> ssTime
		>> statPtr-> guestTime;
	
	statPtr->totalTime	= statPtr->uTime
				+ statPtr-> nTime
				+ statPtr-> sTime
				+ statPtr-> idleTime
				+ statPtr-> iowaitTime
				+ statPtr-> irqTime
				+ statPtr-> sirqTime
				+ statPtr-> ssTime
				+ statPtr-> guestTime;

	infile.close();
	return statPtr;
}
int getCPUusage()
{

	string filename="/proc/stat";
	int totalCPUtime_delta;
	int idleTime_delta;
	int cpuusage;
	STATDATA* statDataPtr_t1 = getDataFromStat(filename.c_str());
	if(statDataPtr_t1 == NULL) return -1;

	sleep(1);

	STATDATA* statDataPtr_t2 = getDataFromStat(filename.c_str());
	if(statDataPtr_t2 == NULL) return -1;
	
	totalCPUtime_delta = statDataPtr_t2->totalTime - statDataPtr_t1->totalTime ;
	idleTime_delta = statDataPtr_t2-> idleTime - statDataPtr_t1-> idleTime;
	
	if(totalCPUtime_delta != 0)
		cpuusage= 100 * (totalCPUtime_delta - idleTime_delta) / totalCPUtime_delta;
	cout << cpuusage << endl;

	
//	cout 	<< cpuname	<<' ' 
//		<< uTime        <<' '
//		<< nTime        <<' '
//		<< sTime        <<' '
//		<< idleTime     <<' '
//		<< iowaitTime   <<' '
//		<< irqTime      <<' '
//		<< sirqTime     <<' '
//		<< ssTime       <<' '
//		<< guestTime << endl;
	delete statDataPtr_t1,statDataPtr_t2;
	return 0;
}
