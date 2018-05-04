#include <stdio.h>
#include <string>
#include "../src/pfxbrick.h"


int main (int argc, char *argv[])
{ 
  std::vector<std::string> sn;
  sn = find_bricks();
  
  PFxBrick brick = PFxBrick();
  if (brick.open())
  { 
    brick.refresh_file_dir();
    brick.filedir.Print();   
    brick.close();
  }
  return 0;
}
