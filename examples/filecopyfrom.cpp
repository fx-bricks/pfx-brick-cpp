#include <stdio.h>
#include <string>
#include "../src/pfxbrick.h"

void PrintUsage()
{
  printf("Usage: ./filecopyfrom <id> [filename]\n");
  printf("       where <id> is the file ID to copy\n");
  printf("             [filenanme] optional override filename when copied\n");
}

int main (int argc, char *argv[])
{ 
  if (argc < 2) { PrintUsage(); exit(0); }
  std::vector<std::string> sn;
  sn = find_bricks();
  
  PFxBrick brick = PFxBrick();
  if (brick.open())
  { std::string fn;
    
    int fid = atoi(argv[1]);
    brick.refresh_file_dir();
    PFxFile *f = brick.filedir.get_file_dir_entry(fid);
    if (argc == 3) fn = argv[2];
    else fn = f->name;
    printf("Copying file id %d as %s from brick...\n", fid, fn.c_str());
    brick.get_file(fid, fn);
    brick.close();
  }
  return 0;
}
