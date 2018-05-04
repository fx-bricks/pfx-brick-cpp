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
    std::vector<int> p(4);    
    p[0] = EVT_PERIOD_1S;
    p[1] = EVT_DUTYCY_10;
    p[2] = EVT_BURST_COUNT_2;
    p[3] = EVT_TRANSITION_TOGGLE;
    PFxAction a = PFxAction().light_fx("1,4", EVT_LIGHTFX_STROBE_P, p);
    brick.test_action(a);
    brick.close();
  }
}