#include <stdio.h>
#include <string>
#include "../src/pfxbrick.h"


int main (int argc, char *argv[])
{ 
  std::vector<std::string> sn;  
  sn = find_bricks(true);
  
  PFxBrick brick = PFxBrick();
  if (brick.open())
  {
    brick.get_icd_rev();
    printf("ICD rev : %s\n", brick.icd_rev.c_str());
    brick.get_status();
    brick.print_status();
    brick.get_config();
    brick.print_config();
    brick.close();
  }
  return 0;
}
