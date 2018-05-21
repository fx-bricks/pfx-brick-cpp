.. _examples:

***************
Examples
***************

This page shows some examples of using the PFx Brick API.

Brick Enumeration, Connection, Info Query
-----------------------------------------

.. code-block:: cpp

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
        printf("ICD rev               : %s\n", brick.icd_rev.c_str());
        brick.get_name();
        printf("Brick name            : %s\n", brick.name.c_str());
        brick.get_status();
        brick.print_status();
        brick.get_config();
        brick.print_config();
        brick.close();
      }
      return 0;
    }

.. code-block:: shell
    
    $ ./getinfo
    1. PFx Brick 4 MB, Serial No: 890F3024
    ICD rev               : 03.36
    Brick name            : My PFx Brick
    USB vendor ID         : 04D8
    USB product ID        : EF74
    USB product desc      : PFx Brick 4 MB
    USB manufacturer      : Fx Bricks Inc
    PFx Brick product ID  : A204, PFx Brick 4 MB
    Serial number         : 890F3024
    Firmware version      : 01.38 build 0530
    Status                : 00 Normal
    Errors                : 00 Unknown
    Status LED            : Normally ON, blink with activity
    Volume Beep           : OFF
    Auto Power Down       : OFF
    IR Lockout Mode       : Inhibit
    IR Auto Off           : Never
    BLE Auto Off          : Never
    BLE Motor Disconnect  : Continue operation
    BLE Advert Power      : 0
    BLE Session Power     : 0
    Motor sound notches   : 8
    Motor sound bounds    : 20 40 60 80 A0 C0 E0 00
    Default brightness    : 00
    Startup brightness    : 84 84 E2 E2 B5 B5 B5 B5
    PF Output brightness  : B5 B5 00 00
    Audio DRC: OFF  Bass: 00  Treble: 00
    Motor Channel 0
      Invert : OFF  Torque comp : OFF  PF mode : OFF
      Accel  : 0  Decel : 0
      vMin   : 0  vMid  : 76  vMax : 250
    Motor Channel 1
      Invert : OFF  Torque comp : OFF  PF mode : OFF
      Accel  : 0  Decel : 0
      vMin   : 0  vMid  : 125  vMax : 250
    Motor Channel 2
      Invert : OFF  Torque comp : OFF  PF mode : OFF
      Accel  : 0  Decel : 0
      vMin   : 0  vMid  : 125  vMax : 250
    Motor Channel 3
      Invert : OFF  Torque comp : OFF  PF mode : OFF
      Accel  : 0  Decel : 0
      vMin   : 0  vMid  : 125  vMax : 250
    

Changing Configuration
----------------------

.. code-block:: cpp

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

Modifying the Event/Action LUT
------------------------------

.. code-block:: cpp

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
    
Copying Audio Files
-------------------

Copy file to PFx Brick specified by command line arguments:

.. code-block:: cpp

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

Copy a file from the PFx Brick:

.. code-block:: cpp

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

Show the file directory of the PFx Brick:

.. code-block:: cpp

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

.. code-block:: shell

    $ ./filedir
     ID Name                       Size    Attr    User1    User2    CRC32
      1 Bark1                      22.3 kB 0000 000056B0 00000046 9D26CE7C
      3 Hero                       55.5 kB 0000 0000D8BC 0000002C DC91BD91
      2 Sosumi                     27.1 kB 0000 000069C2 0000002C 997DD19B
      8 chicken.wav               291.2 kB 0000 00047164 0000002C B185E6FD
      5 Bark1.wav                  22.3 kB 0000 000056B0 00000046 9D26CE7C
      9 Chicken1                  291.2 kB 0000 00047164 0000002C B185E6FD
    6 files, 725.0 kB used, 3452.9 kB remaining

Scripting Actions
-----------------

A demonstration of toggling a lighting effect:

.. code-block:: cpp

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
