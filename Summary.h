#include <string>

#ifndef SUMMARY_H
#define SUMMARY_H
typedef struct{
  std::string hostname;
  std::string content;
  int val;
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
  bool CreateSummaryInfo(const std::string& content, const int& cpu_used_perc);

  SummaryInfo get_suminfo();
  SummaryInfo& set_suminfo(const SummaryInfo& suminfo);

private:
  SummaryInfo suminfo_;
};

#endif
