#include <string>

class Memusage
{
public:
	Memusage(): 	mem_total_(0),
			mem_free_(0),
			buffers_(0),
			cached_(0){}
	~Memusage(){}
	
	bool GetDataFromMeminfo (const std::string& filename);
	int CalMemusage();

private:
	//from /proc/meminfo
	int mem_total_;
	int mem_free_;
	int buffers_;
	int cached_;
};
