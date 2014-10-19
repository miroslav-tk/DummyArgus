#ifndef MEMUSAGE_H
#define MEMUSAGE_H

#include <string>
#include "Summary.h"

class Memusage
{
public:
	Memusage(): 	mem_total_(0),
			mem_free_(0),
			buffers_(0),
			cached_(0){}
	~Memusage(){}
	
	bool GetDataFromMeminfo (const std::string& filename);
  bool CalMemusage(SummaryInfo& suminfo);

private:
	//from /proc/meminfo
	int mem_total_;
	int mem_free_;
	int buffers_;
	int cached_;
};

#endif
