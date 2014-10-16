#include <string>
#include <vector>

typedef struct {
	std::string device_name;
	std::string mount_point;
	std::string file_system;
	std::string parameters;
	std::string dump;
	std::string fsck;
} MOUNT_INFO;

class Diskusage
{
public:
	Diskusage(){}
	Diskusage(std::string strval):specfic_mount_point_(strval){}
	~Diskusage(){}
	bool operator()(const MOUNT_INFO& mount_info)
	{
		return (mount_info.mount_point == specfic_mount_point_ );
	}
	bool GetDataFromMounts(std::vector<MOUNT_INFO>& mount_vec);
	//bool find(std::vector<MOUNT_INFO>& mount_vec,const std::string& mount_point);
	bool CheckMountPoint(const std::string& mount_point);
	int CalDiskusage(const std::string& mount_point);
	

private:
	std::string specfic_mount_point_;
};

