#include <stdio.h>
#include <string>
#include "../src/pfxbrick.h"


int main (int argc, char *argv[])
{ 
  std::vector<std::string> sn;
  sn = find_bricks();
  
  PFxBrick brick = PFxBrick();
  if (brick.open())
  { PFxAction left_button_ch1;
    left_button_ch1 = brick.get_action(EVT_ID_8879_LEFT_BUTTON, 0, left_button_ch1);
    printf("Get action for Left Button Ch 1 on Speed Remote...\n");
    left_button_ch1.Print();
    
    printf("Add a light effect to this action...\n");
    PFxAction new_left_action;
    new_left_action = left_button_ch1;
    new_left_action.light_on("1,2,3,4");
    new_left_action.Print();

    printf("Save new action back to brick...\n");
    brick.set_action(EVT_ID_8879_LEFT_BUTTON, 0, new_left_action);
    PFxAction new_action;
    new_action = brick.get_action(EVT_ID_8879_LEFT_BUTTON, 0, new_action);
    new_action.Print();

    printf("Restore the original action without the change...\n");
    brick.set_action(EVT_ID_8879_LEFT_BUTTON, 0, left_button_ch1);
    new_action = brick.get_action(EVT_ID_8879_LEFT_BUTTON, 0, new_action);
    new_action.Print();

    brick.close();
  }
  return 0;
}
