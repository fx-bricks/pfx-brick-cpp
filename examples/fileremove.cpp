#include <stdio.h>
#include <string>
#include "../src/pfxbrick.h"

void PrintUsage()
{
  printf("Usage: ./fileremove <id>\n");
  printf("       where <id> is the file ID of the file to remove\n");
}


int main (int argc, char *argv[])
{ 
  if (argc < 2) { PrintUsage(); exit(0); }
  std::vector<std::string> sn;
  sn = find_bricks();
  
  PFxBrick brick = PFxBrick();
  if (brick.open())
  {
    int fid = atoi(argv[1]);    
    printf("Removing file %d...\n", fid);
    brick.remove_file(fid);
    brick.refresh_file_dir();
    brick.filedir.Print();
    brick.close();
  }
  return 0;
}
