#include <iostream>
#include <sys/statfs.h>
#include <fstream>
#include <sstream>
#include <algorithm> 
#include "Diskusage.h"

bool Diskusage::getDataFromMounts(std::vector<MOUNT_INFO>& mountVec)
{

	std::ifstream infile("/proc/mounts");

	if(!infile)
	{
		std::cerr 	<< "error: unable ro open input file :"
				<< "/proc/mounts" 	<< std::endl;
		return false;
	}

	std::string mountsLines;
	//std::vector<MOUNT_INFO> mountVec;
	while( getline(infile,mountsLines))
	{

		std::string deviceName,mountPoint,fileSystem,parameters,dump,fsck;
		std::stringstream mystream(mountsLines);

		MOUNT_INFO mountInfo;
		mystream 	>> mountInfo.deviceName
				>> mountInfo.mountPoint
				>> mountInfo.fileSystem
				>> mountInfo.parameters
				>> mountInfo.dump
				>> mountInfo.fsck;

		mountVec.push_back(mountInfo);
	}
#ifdef __DEBUG__
	for (std::vector<MOUNT_INFO>::const_iterator i = mountVec.begin(); i != mountVec.end(); ++i)
	{
		std::cout << (*i).deviceName << " " << (*i).mountPoint <<std::endl;
	}
#endif
	if(mountVec.empty())
	{
		std::cerr 	<<"error: no mount point ";
		return false;
	}
	else 	
		return true;
}
bool Diskusage::find(std::vector<MOUNT_INFO>& mountVec,const std::string& mountPoint)
{
	std::vector<MOUNT_INFO>::iterator first = mountVec.begin();
	std::vector<MOUNT_INFO>::iterator end  = mountVec.end();
	while(first != end)
	{
		if((*first).mountPoint == mountPoint)
			return true;
		++first;
	}
	return false;
}
bool Diskusage::checkMountPoint(const std::string& mountPoint)
{
	std::vector<MOUNT_INFO> mountVec;
	bool b_got = getDataFromMounts(mountVec);
	if (b_got == false) 
		return false;
	bool b_find = find(mountVec,mountPoint);
	return b_find;
}
int Diskusage::calDiskusage(const std::string& mountPoint)
{
	struct statfs sfs = {0};
	bool b_checked = checkMountPoint(mountPoint);
	if(b_checked)
	{
		int s = statfs(mountPoint.c_str(),&sfs);
	}
	else return -1;
	int diskUsedPerc =100 * (sfs.f_blocks - sfs.f_bfree ) / (sfs.f_blocks -sfs.f_bfree + sfs.f_bavail) + 1;
	return diskUsedPerc;
}
