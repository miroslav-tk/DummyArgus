#include <iostream>
#include <fstream>
using namespace std;

int main()
{

	int getCPUusage();
	getCPUusage();
	return 0;
}


int getCPUusage()
{
	string filename="/proc/stat";
	string 	cpuname, 	//
		uTime,		//user mode time
		nTime,		//nice mode time
		sTime,		//system mode time
		iTime;		//idle time
	ifstream infile("/proc/stat");
	
	if(!infile)
	{
		cerr 	<<"error: unable ro open input file :"
			<<infile <<endl;
		return -1;
	}
	infile 	>> cpuname 
		>> uTime
		>> nTime
		>> sTime
		>> iTime;
	cout 	<< cpuname <<' '
		<< uTime   <<' '
		<< nTime   <<' '
		<< sTime   <<' '
		<< iTime   <<endl;
	infile.close();
	return 0;
}
