#include <stdio.h>
#include <string>
#include "../src/pfxbrick.h"

static void PrintUsage(void);

void PrintUsage (void)
{ printf ("Usage:  pfxtest [command]\n");
}

int main (int argc, char *argv[])
{ 
  std::vector<std::string> sn;
  
  sn = find_bricks(true);
  
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
    
    brick.refresh_file_dir();
    brick.filedir.Print();   
//     PFxAction a = PFxAction().set_motor_speed("A", 50, 3);
//     a.Print();
//
//     PFxAction a2 = PFxAction().light_on("1,4");
//     a2.Print();
// //    PFxAction a3 = PFxAction().combo_light_fx(EVT_COMBOFX_BARGRAPH, {EVT_PERIOD_1S, EVT_FADE_FACTOR_10});
// //    a3.Print();
//     PFxAction a4 = PFxAction().play_audio_file(2);
//     a4.Print();
//
//
//     printf("Closing...\n");
//     brick.close();
//   }
//     PFxAction a = PFxAction().set_motor_speed("A", 50, 3);
//     a.Print();
//
//     PFxAction a2 = PFxAction().light_on("1,4");
//     a2.Print();
//     std::vector<int> p(2);
//     p[0] = EVT_PERIOD_1S;
//     p[1] = EVT_FADE_FACTOR_10;
//     PFxAction a3 = PFxAction().combo_light_fx(EVT_COMBOFX_BARGRAPH, p);
//     a3.Print();
//     PFxAction a4 = PFxAction().play_audio_file(2);
//     a4.Print();
  }
  return 0;
}