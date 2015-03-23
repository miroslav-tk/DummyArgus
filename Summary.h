#ifndef SUMMARY_H
#define SUMMARY_H
#include <string>
#include <boost/date_time/posix_time/posix_time.hpp>

typedef struct{
  std::string hostname;
  std::string content;
  float  val;
  std::string time;
} SummaryInfo;

class Summary
{
public:
  Summary(){
    suminfo_.val = 0;
  }
  ~Summary(){}

  bool CreateSummaryInfo(const std::string& content, const float& val);

  SummaryInfo get_suminfo();

private:
  SummaryInfo suminfo_;
};

#endif
