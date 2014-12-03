#ifndef DATAANALYSIS_H
#define DATAANALYSIS_H 
#include "Summary.h"

class DataAnalysis
{
public:
  DataAnalysis (){}
  virtual ~DataAnalysis (){}

  void Collect(const SummaryInfo& suminfo);

private:
  SummaryInfo suminfo_;
};
#endif
