#include <string>
#include <vector>

typedef struct {
	std::string deviceName;
	std::string mountPoint;
	std::string fileSystem;
	std::string parameters;
	std::string dump;
	std::string fsck;
} MOUNT_INFO;

class Diskusage
{
public:
	Diskusage(){}
	Diskusage(std::string strval):myMountPoint(strval){}
	~Diskusage(){}
	bool operator()(const MOUNT_INFO& mount_info)
	{
		return (mount_info.mountPoint == myMountPoint );
	}
	bool getDataFromMounts(std::vector<MOUNT_INFO>& mountVec);
	//bool find(std::vector<MOUNT_INFO>& mountVec,const std::string& mountPoint);
	bool checkMountPoint(const std::string& mountPoint);
	int calDiskusage(const std::string& mountPoint);
	

private:
	std::string myMountPoint;
};

