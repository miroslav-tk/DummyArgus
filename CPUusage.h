#include<string>

class CPUusage
{
public:
	CPUusage(): 	uTime(0),      
 	             	nTime(0),      
  	             	sTime(0),      
  	             	idleTime(0),   
                     	iowaitTime(0), 
                     	irqTime(0),    
  	             	sirqTime(0),   
                     	ssTime(0),     
  	             	guestTime(0),  
                     	totalTime(0){}

	~CPUusage(){}

	bool getDataFromStat(const std::string& filename);
	int calCPUusage();

	int getTotalTime();
	int getIdleTime();

private:
	int	uTime;		//user mode time
	int	nTime;		//nice mode time
	int	sTime;		//system mode time
	int	idleTime;	//idle time
	int	iowaitTime;	//iowait time
	int	irqTime;	//irq time
	int	sirqTime;	//softirq time
	int	ssTime;		//stealstolen time,
	int	guestTime;	//guest time
	int	totalTime;	//summary of all the time
	std::string 	cpuname; 	
};
