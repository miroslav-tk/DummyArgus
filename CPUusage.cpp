
#include <iostream>
#include <fstream>
#include <unistd.h>
using namespace std;

class CPUusage
{
public:
	CPUusage();
	~CPUusage();

	bool getDataFromStat(string filename);
	int getCPUusage();

	int getTotalTime();
	int getIdleTime();

private:
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
};

CPUusage::CPUusage()
{
	this-> uTime  		= 0 ;		
	this-> nTime	 	= 0 ; 
	this-> sTime	 	= 0 ; 
	this-> idleTime	 	= 0 ;
	this-> iowaitTime	= 0 ;	
	this-> irqTime	 	= 0 ;
	this-> sirqTime	 	= 0 ;
	this-> ssTime	 	= 0 ; 
	this-> guestTime 	= 0 ;       
	this-> totalTime	= 0 ;	
}
CPUusage::~CPUusage() {}

bool CPUusage::getDataFromStat (string filename)
{
	ifstream infile(filename.c_str());
	
	if(!infile)
	{
		cerr 	<< "error: unable ro open input file :"
			<< infile << endl;
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
	cout 	<< cpuname	<<' ' 
		<< uTime	<<' '
		<< nTime	<<' '
		<< sTime	<<' '
		<< idleTime	<<' '
		<< iowaitTime	<<' '
		<< irqTime	<<' '
		<< sirqTime	<<' '
		<< ssTime	<<' '
		<< guestTime 	<< endl;
#endif

	infile.close();
	return true;
}
int CPUusage::getCPUusage()
{

	string filename="/proc/stat";
	int totalCPUtime_delta;
	int idleTime_delta;
	int cpuusage = 0 ;

	bool b_got_t1 	= this-> getDataFromStat(filename.c_str());
	int totalTime_t1= this-> getTotalTime();
	int idleTime_t1 = this-> getIdleTime();
	if( b_got_t1 == false) return -1;

	sleep(1);

	bool b_got_t2  = this-> getDataFromStat(filename.c_str());
	int totalTime_t2= this-> getTotalTime();
	int idleTime_t2 = this-> getIdleTime();
	if( b_got_t2 == false) return -1;
	
	totalCPUtime_delta = totalTime_t2 -totalTime_t1;
	idleTime_delta =idleTime_t2 - idleTime_t1; 
	
	if(totalCPUtime_delta != 0)
		cpuusage= 100 * (totalCPUtime_delta - idleTime_delta) / totalCPUtime_delta;
	
	return cpuusage;
}

int CPUusage::getTotalTime()
{
	return this-> totalTime;
}

int CPUusage::getIdleTime()
{
	return this-> idleTime;
}

int main(int argc, const char *argv[])
{
	CPUusage cpuusage;
	int cpu = cpuusage.getCPUusage();
	if(cpu == -1)
		cerr << "function getCPUusage doesn't work !";
	else
	{
		cout 	<< "CPUusage: " 
			<< cpu << endl;
		return 0;
	}	
}
