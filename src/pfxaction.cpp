

#include <stdio.h>
#include <math.h>

#include "pfxbrick.h"


PFxAction::PFxAction()
{
  command = 0;
  motorActionId = 0;
  motorParam1 = 0;
  motorParam2 = 0; 
  lightFxId = 0;
  lightOutputMask = 0;
  lightPFOutputMask = 0;
  lightParam1 = 0;
  lightParam2 = 0;
  lightParam3 = 0;
  lightParam4 = 0; 
  lightParam5 = 0; 
  soundFxId = 0;
  soundFileId = 0; 
  soundParam1 = 0;
  soundParam2 = 0;
}

PFxAction::~PFxAction()
{ 
}

PFxAction::PFxAction (const PFxAction& withAction)
{
  command = withAction.command;
  motorActionId = withAction.motorActionId;
  motorParam1 = withAction.motorParam1;
  motorParam2 = withAction.motorParam2; 
  lightFxId = withAction.lightFxId;
  lightOutputMask = withAction.lightOutputMask;
  lightPFOutputMask = withAction.lightPFOutputMask;
  lightParam1 = withAction.lightParam1;
  lightParam2 = withAction.lightParam2;
  lightParam3 = withAction.lightParam3;
  lightParam4 = withAction.lightParam4; 
  lightParam5 = withAction.lightParam5; 
  soundFxId = withAction.soundFxId;
  soundFileId = withAction.soundFileId; 
  soundParam1 = withAction.soundParam1;
  soundParam2 = withAction.soundParam2;
}

PFxAction& PFxAction::operator=(const PFxAction& withAction)
{
  if (this == &withAction) return *this;  
  command = withAction.command;
  motorActionId = withAction.motorActionId;
  motorParam1 = withAction.motorParam1;
  motorParam2 = withAction.motorParam2; 
  lightFxId = withAction.lightFxId;
  lightOutputMask = withAction.lightOutputMask;
  lightPFOutputMask = withAction.lightPFOutputMask;
  lightParam1 = withAction.lightParam1;
  lightParam2 = withAction.lightParam2;
  lightParam3 = withAction.lightParam3;
  lightParam4 = withAction.lightParam4; 
  lightParam5 = withAction.lightParam5; 
  soundFxId = withAction.soundFxId;
  soundFileId = withAction.soundFileId; 
  soundParam1 = withAction.soundParam1;
  soundParam2 = withAction.soundParam2;
  return *this;
}

PFxAction& PFxAction::set_motor_speed(std::string ch, int speed, double duration)
{
  double sf = (double)speed;
  if (sf > 100.0) sf = 100.0;
  if (sf < -100.0) sf = -100.0;
  sf = (sf / 100.0) * 63.0;

  int si = (int)(fabs(sf)) & EVT_MOTOR_SPEED_HIRES_MASK;
  si |= EVT_MOTOR_SPEED_HIRES;
  if (sf < 0.0) si |= EVT_MOTOR_SPEED_HIRES_REV;
  motorParam1 = si;

  int m = ch_to_mask(ch) & EVT_MOTOR_OUTPUT_MASK;
  if (duration > 0)
  { m |= EVT_MOTOR_SET_SPD_TIMED;
    motorParam2 = duration_to_fixed_value(duration);
  }
  else m |= EVT_MOTOR_SET_SPD;
  motorActionId = m;
  return *this;
}
  
void PFxAction::Print()
{
  printf("Command           : [%02X] %s\n", command, command_str(command).c_str());
  if ((motorActionId & EVT_MOTOR_OUTPUT_MASK) == 0)
  { printf("Motor Action ID   : [%02X] None\n", motorActionId);
  }
  else
  { printf("Motor Action ID   : [%02X] %s Ch %s\n", motorActionId, motor_action_str(motorActionId).c_str(), mask_to_ch(motorActionId & EVT_MOTOR_OUTPUT_MASK).c_str());
  }
  printf("Motor Param 1     : [%02X]\n", motorParam1);
  printf("Motor Param 2     : [%02X]\n", motorParam2);
  std::string sf;
  if (lightFxId & EVT_LIGHT_COMBO_MASK)
  { sf = combo_lightfx_str(lightFxId & EVT_LIGHT_ID_MASK); }
  else
  { sf = ind_lightfx_str(lightFxId & EVT_LIGHT_ID_MASK); }
  printf("Light Fx ID       : [%02X] %s\n", lightFxId, sf.c_str());
  printf("Light Output Mask : [%02X] %s\n", lightOutputMask, mask_to_ch(lightOutputMask).c_str());
  printf("Light PF Out Mask : [%02X]\n", lightPFOutputMask);
  printf("Light Param 1     : [%02X]\n", lightParam1);
  printf("Light Param 2     : [%02X]\n", lightParam2);
  printf("Light Param 3     : [%02X]\n", lightParam3);
  printf("Light Param 4     : [%02X]\n", lightParam4);
  printf("Light Param 5     : [%02X]\n", lightParam5);
  printf("Sound Fx ID       : [%02X]\n", soundFxId);
  printf("Sound File ID     : [%02X]\n", soundFileId);
  printf("Sound Param 1     : [%02X]\n", soundParam1);
  printf("Sound Param 2     : [%02X]\n", soundParam2);
}