

#include <stdio.h>
#include <math.h>
#include <vector>

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
 
PFxAction& PFxAction::stop_motor(std::string ch)
{
  int m = ch_to_mask(ch) & EVT_MOTOR_OUTPUT_MASK;
  m |= EVT_MOTOR_ESTOP;
  motorActionId = m;
  return *this;
}

PFxAction& PFxAction::light_on(std::string ch)
{
  lightOutputMask = ch_to_mask(ch);
  lightFxId = EVT_LIGHTFX_ON_OFF_TOGGLE;
  lightParam4 = EVT_TRANSITION_ON;
  return *this;
}
  
PFxAction& PFxAction::light_off(std::string ch)
{
  lightOutputMask = ch_to_mask(ch);
  lightFxId = EVT_LIGHTFX_ON_OFF_TOGGLE;
  lightParam4 = EVT_TRANSITION_OFF;
  return *this;
}

PFxAction& PFxAction::light_toggle(std::string ch)
{
  lightOutputMask = ch_to_mask(ch);
  lightFxId = EVT_LIGHTFX_ON_OFF_TOGGLE;
  lightParam4 = EVT_TRANSITION_TOGGLE;
  return *this;
}
  
PFxAction& PFxAction::set_brightness(std::string ch, int brightness)
{
  int x = brightness;
  if (x > 255) x = 255;
  if (x < 0) x = 0;
  lightOutputMask = ch_to_mask(ch);
  lightFxId = EVT_LIGHTFX_SET_BRIGHT;
  lightParam1 = x;  
  return *this;
}
  
PFxAction& PFxAction::combo_light_fx(int fx, std::vector<int> param)
{
  return light_fx("", fx | EVT_LIGHT_COMBO_MASK, param);
}
  
PFxAction& PFxAction::light_fx(std::string ch, int fx, std::vector<int> param)
{
  lightOutputMask = ch_to_mask(ch);
  lightFxId = fx;
  for (int i=0; i<param.size(); i++)
  { switch (i)
    { case 0 : lightParam1 = param[0]; break;
      case 1 : lightParam2 = param[1]; break;
      case 2 : lightParam3 = param[2]; break;
      case 3 : lightParam4 = param[3]; break;
      case 4 : lightParam5 = param[4]; break;
    }
  }
  return *this;
}
  
PFxAction& PFxAction::sound_fx(int fx, std::vector<int> param, int fileID)
{
  soundFxId = fx;
  if ((fileID >= 0) && (fileID < 0xFF)) soundFileId = fileID;
  for (int i=0; i<param.size(); i++)
  { switch (i)
    { case 0 : soundParam1 = param[0]; break;
      case 1 : soundParam2 = param[1]; break;
    }
  }
  return *this;  
}
  
PFxAction& PFxAction::play_audio_file(int fileID)
{ std::vector<int> p(2);
  p[0] = EVT_SOUND_TOGGLE;
  p[1] = 0;
  return sound_fx(EVT_SOUND_PLAY_ONCE, p, fileID);
}
  
PFxAction& PFxAction::stop_audio_file(int fileID)
{ std::vector<int> p;
  return sound_fx(EVT_SOUND_STOP, p, fileID);
}
  
PFxAction& PFxAction::repeat_audio_file(int fileID)
{ std::vector<int> p;
  return sound_fx(EVT_SOUND_PLAY_CONT, p, fileID);
}
  
PFxAction& PFxAction::set_volume(int volume)
{ std::vector<int> p;
  double vf = (double)volume;
  if (vf > 100.0) vf = 100.0;
  if (vf < 0.0) vf = 0.0;
  vf = (vf / 100.0) * 255.0;
  int v = (int)vf;
  p[0] = 0;
  p[1] = v;
  return sound_fx(EVT_SOUND_SET_VOL, p, -1);
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