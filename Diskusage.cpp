#include <iostream>
#include <sys/statfs.h>
#include <fstream>
#include <sstream>
#include <algorithm> 
#include "Diskusage.h"

bool Diskusage::GetDataFromMounts(std::vector<MOUNT_INFO>& mount_vec)
{

	std::ifstream infile("/proc/mounts");

	if(!infile)
	{
		std::cerr 	<< "error: unable ro open input file :"
				<< "/proc/mounts" 	<< std::endl;
		return false;
	}

	std::string mount_input_lines;
	while( getline(infile,mount_input_lines))
	{
		std::stringstream inputline_stream(mount_input_lines);

		MOUNT_INFO mount_info;
		inputline_stream 	>> mount_info.device_name
					>> mount_info.mount_point
					>> mount_info.file_system
					>> mount_info.parameters
					>> mount_info.dump
					>> mount_info.fsck;

		mount_vec.push_back(mount_info);
	}
#ifdef __DEBUG__
	for (std::vector<MOUNT_INFO>::const_iterator i = mount_vec.begin(); i != mount_vec.end(); ++i)
	{
		std::cout << (*i).device_name << " " << (*i).mount_point <<std::endl;
	}
#endif
	if(mount_vec.empty())
	{
		std::cerr 	<<"error: no mount point ";
		return false;
	}
	else 	
	{
		return true;
	}
}
//bool Diskusage::find(const std::vector<MOUNT_INFO>& mount_vec,const std::string& mount_point)
//{
//	std::vector<MOUNT_INFO>::iterator first = mount_vec.begin();
//	std::vector<MOUNT_INFO>::iterator end  = mount_vec.end();
//	while(first != end)
//	{
//		if((*first).mount_point == mount_point)
//		{
//			return true;
//		}
//		++first;
//	}
//	return false;
//}
bool Diskusage::CheckMountPoint(const std::string& mount_point)
{
	std::vector<MOUNT_INFO> mount_vec;
	bool b_got = GetDataFromMounts(mount_vec);
	if (b_got == false) 
	{
		return false; 	  
	}
	std::vector<MOUNT_INFO>::iterator it = std::find_if(mount_vec.begin(),mount_vec.end(),Diskusage(mount_point));
	if (it == mount_vec.end())
	{
		return false;
	}
#ifdef __DEBUG__DISK
	std::cout <<"The specific mount point is : "<< (*it).mount_point << std::endl;
#endif
	return true;
}
bool Diskusage::CalDiskusage(const std::string& mount_point,
                            SummaryInfo& suminfo)
{
	struct statfs sfs = {0};
	bool b_checked = CheckMountPoint(mount_point);
	if(b_checked)
	{
		int s = statfs(mount_point.c_str(),&sfs);
	}
	else
	{
		return false;
	}
	int disk_used_perc =100 * (sfs.f_blocks - sfs.f_bfree ) / (sfs.f_blocks -sfs.f_bfree + sfs.f_bavail) + 1;

  Summary summary;
  summary.CreateSummaryInfo(std::string("Diskusage"), disk_used_perc);
  
  suminfo = summary.get_suminfo();
	return true;
}
