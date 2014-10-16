#include<string>

class CPUusage
{
public:
	CPUusage(): 	user_time_(0),      
 	             	nice_time_(0),      
  	             	sys_time_(0),      
  	             	idle_time_(0),   
                     	iowait_time_(0), 
                     	irq_time_(0),    
  	             	sirq_time_(0),   
                     	steals_stolen_time_(0),     
  	             	guest_time_(0),  
                     	total_time_(0){}

	~CPUusage(){}

	bool GetDataFromStat (const std::string& filename);
	int CalCPUusage();
	int get_total_time();
	int get_idle_time();

private:
	int	user_time_;		//user mode time
	int	nice_time_;		//nice mode time
	int	sys_time_;		//system mode time
	int	idle_time_;	//idle time
	int	iowait_time_;	//iowait time
	int	irq_time_;	//irq time
	int	sirq_time_;	//softirq time
	int	steals_stolen_time_;		//stealstolen time,
	int	guest_time_;	//guest time
	int	total_time_;	//summary of all the time
	std::string 	cpuname_; 	
};
