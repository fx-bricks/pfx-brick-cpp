#include <stdio.h>
#include <string>
#include "../src/pfxbrick.h"

void PrintUsage()
{
  printf("Usage: ./filecopyto <filename> <id>\n");
  printf("       where <filename> is the local file to copy\n");
  printf("             <id> is the unique file ID to assign the file on the PFx Brick\n");
}


int main (int argc, char *argv[])
{ 
  if (argc < 3) { PrintUsage(); exit(0); }
  std::vector<std::string> sn;
  sn = find_bricks();
  
  PFxBrick brick = PFxBrick();
  if (brick.open())
  {
    int fid = atoi(argv[2]);
    std::string fn = argv[1];
    printf("Copying %s to brick with id %d...\n", fn.c_str(), fid);
    brick.put_file(fid, fn);
    brick.refresh_file_dir();
    brick.filedir.Print();
    brick.close();
  }
  return 0;
}
