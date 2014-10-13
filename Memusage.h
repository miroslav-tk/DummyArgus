#include <string>

class Memusage
{
public:
	Memusage(): 	memTotal(0),
			memFree(0),
			buffers(0),
			cached(0){}
	~Memusage(){}
	
	bool getDataFromMeminfo (const std::string& filename);
	int calMemusage();

private:
	//from /proc/meminfo
	int memTotal;
	int memFree;
	int buffers;
	int cached;
};
