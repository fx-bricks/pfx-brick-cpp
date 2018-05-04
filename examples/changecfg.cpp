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
    printf("PFx Brick Configuration\n");
    printf("=======================\n");
    brick.get_config();
    brick.print_config();

    printf("Change the volume beep setting...\n");
    if (brick.config.settings.volumeBeep == PFX_CFG_VOLBEEP_ON)
    { brick.config.settings.volumeBeep = PFX_CFG_VOLBEEP_OFF; }
    else
    { brick.config.settings.volumeBeep = PFX_CFG_VOLBEEP_ON; }
    brick.set_config();

    printf("PFx Brick Updated Configuration\n");
    printf("===============================\n");
    brick.get_config();
    brick.print_config();
    brick.close();
  }
  return 0;
}
