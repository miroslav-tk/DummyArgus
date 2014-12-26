#include <iostream>
#include "DataAnalysis.h"
#include "Summary.h"

int main(int argc, char *argv[])
{  
  Summary summary;
  SummaryInfo suminfo[10];
  summary.CreateSummaryInfo("c1",1);
  suminfo[0]=summary.get_suminfo();
  summary.CreateSummaryInfo("c2",2);
  suminfo[1]=summary.get_suminfo();
  summary.CreateSummaryInfo("c3",3);
  suminfo[2]=summary.get_suminfo();
  summary.CreateSummaryInfo("c1",11);
  suminfo[3]=summary.get_suminfo();
  DataAnalysis analysis;
  analysis.Collect(suminfo[0]);
  analysis.Collect(suminfo[1]);
  analysis.Collect(suminfo[2]);
  analysis.Collect(suminfo[3]);

  analysis.get_host_list();

  return 0;
}
