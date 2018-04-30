#include <stdio.h>
#include <string>
#include "../src/pfxbrick.h"

static void PrintUsage(void);

void PrintUsage (void)
{ printf ("Usage:  pfxtest [command]\n");
}

int main (int argc, char *argv[])
{ 
  PFxBrick brick = PFxBrick();
  printf("Opening...\n");
  if (brick.open())
  {
    brick.get_icd_rev();
    printf("ICD rev : %s\n", brick.icd_rev.c_str());
    brick.get_status();
    brick.print_status();
    brick.get_config();
    brick.print_config();
    printf("Closing...\n");
    brick.close();
  }
  return 0;
}