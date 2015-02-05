#include <iostream>
#include "DataAnalysis.h"
#include "Summary.h"
#include "Diskusage.h"

int main(int argc, char *argv[])
{  
  Diskusage d;
  SummaryInfo msg; 
  d.CalDiskusage("/",msg);
  std::cout << msg.val << std::endl;
  return 0;
}
