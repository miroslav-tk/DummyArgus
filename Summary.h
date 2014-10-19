#include <string>

#ifndef SUMMARY_H
#define SUMMARY_H
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

  struct tm* GetTime();
  bool CreateSummaryInfo(const std::string& content, const float& val);

  SummaryInfo get_suminfo();

private:
  SummaryInfo suminfo_;
};

#endif
