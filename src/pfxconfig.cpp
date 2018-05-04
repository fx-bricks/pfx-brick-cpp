/*
  Copyright (C) 2018  Fx Bricks Inc.
  This file is part of the pfxbrick python module.
  Permission is hereby granted, free of charge, to any person
  obtaining a copy of this software and associated documentation
  files (the "Software"), to deal in the Software without restriction,
  including without limitation the rights to use, copy, modify, merge,
  publish, distribute, sublicense, and/or sell copies of the Software,
  and to permit persons to whom the Software is furnished to do so,
  subject to the following conditions:
  
  The above copyright notice and this permission notice shall be
  included in all copies or substantial portions of the Software.
  
  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
  OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
  IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
  CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
  TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
  SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include <stdio.h>
#include "pfxbrick.h"

PFxSettings::PFxSettings()
{
  statusLED = 0;
  volumeBeep = 0;
  autoPowerDown = 0;
  lockoutMode = 0;
  irAutoOff = 0;
  bleAutoOff = 0;
  bleMotorWhenDisconnect = 0;
  bleAdvertPower = 0;
  bleSessionPower = 0;
  notchCount = 0;
  memset(&notchBounds[0], 0, 8);  
}

PFxSettings::~PFxSettings()
{
}

PFxSettings::PFxSettings (const PFxSettings& withSettings)
{
  statusLED = withSettings.statusLED;
  volumeBeep = withSettings.volumeBeep;
  autoPowerDown = withSettings.autoPowerDown;
  lockoutMode = withSettings.lockoutMode;
  irAutoOff = withSettings.irAutoOff;
  bleAutoOff = withSettings.bleAutoOff;
  bleMotorWhenDisconnect = withSettings.bleMotorWhenDisconnect;
  bleAdvertPower = withSettings.bleAdvertPower;
  bleSessionPower = withSettings.bleSessionPower;
  notchCount = withSettings.notchCount;
  memcpy(&notchBounds[0], &withSettings.notchBounds[0], 8);
}

PFxSettings& PFxSettings::operator=(const PFxSettings& withSettings)
{
  if (this == &withSettings) return *this;
  statusLED = withSettings.statusLED;
  volumeBeep = withSettings.volumeBeep;
  autoPowerDown = withSettings.autoPowerDown;
  lockoutMode = withSettings.lockoutMode;
  irAutoOff = withSettings.irAutoOff;
  bleAutoOff = withSettings.bleAutoOff;
  bleMotorWhenDisconnect = withSettings.bleMotorWhenDisconnect;
  bleAdvertPower = withSettings.bleAdvertPower;
  bleSessionPower = withSettings.bleSessionPower;
  notchCount = withSettings.notchCount;
  memcpy(&notchBounds[0], &withSettings.notchBounds[0], 8);
  return *this;
}

void PFxSettings::Print()
{ 
  printf("Status LED            : %s\n", status_led_str(statusLED).c_str());
  printf("Volume Beep           : %s\n", volume_beep_str(volumeBeep).c_str());
  printf("Auto Power Down       : %s\n", power_save_str(autoPowerDown).c_str());
  printf("IR Lockout Mode       : %s\n", lockout_str(lockoutMode).c_str());
  printf("IR Auto Off           : %s\n", ir_off_str(irAutoOff).c_str());
  printf("BLE Auto Off          : %s\n", ble_off_str(bleAutoOff).c_str());
  printf("BLE Motor Disconnect  : %s\n", ble_motor_str(bleMotorWhenDisconnect).c_str());
  printf("BLE Advert Power      : %d\n", bleAdvertPower);
  printf("BLE Session Power     : %d\n", bleSessionPower);
  printf("Motor sound notches   : %d\n", notchCount);
  printf("Motor sound bounds    : ");
  for (int i=0; i<8; i++) printf("%02X ", notchBounds[i]);
  printf("\n");
}

/*
  PFxMotor Methods
*/

PFxMotor::PFxMotor()
{
  invert = false;
  torqueComp = false;
  tlgMode = false;
  accel = 0;
  decel = 0;
  vmin = 0;
  vmid = 128;
  vmax = 255;
}
PFxMotor::~PFxMotor()
{}
  
PFxMotor::PFxMotor (const PFxMotor& withMotor)
{
  invert = withMotor.invert;
  torqueComp = withMotor.torqueComp;
  tlgMode = withMotor.tlgMode;
  accel = withMotor.accel;
  decel = withMotor.decel;
  vmin = withMotor.vmin;
  vmid = withMotor.vmid;
  vmax = withMotor.vmax;
}

PFxMotor& PFxMotor::operator=(const PFxMotor& withMotor)
{
  if (this == &withMotor) return *this;
  invert = withMotor.invert;
  torqueComp = withMotor.torqueComp;
  tlgMode = withMotor.tlgMode;
  accel = withMotor.accel;
  decel = withMotor.decel;
  vmin = withMotor.vmin;
  vmid = withMotor.vmid;
  vmax = withMotor.vmax;
  return *this;
}

void PFxMotor::from_config_byte(unsigned char msg)
{
  invert = set_with_bit(msg, PFX_CFG_MOTOR_INVERT);
  torqueComp = set_with_bit(msg, PFX_CFG_MOTOR_TRQCOMP);
  tlgMode = set_with_bit(msg, PFX_CFG_MOTOR_TLGMODE);
}
  
void PFxMotor::from_speed_bytes(unsigned char *msg)
{
  vmin = (int)msg[0];
  vmid = (int)msg[1];
  vmax = (int)msg[2];
  accel = (int)msg[3];
  decel = (int)msg[4];
}

unsigned char PFxMotor::to_config_byte()
{ unsigned char v = 0;
  if (invert) v |= PFX_CFG_MOTOR_INVERT;
  if (torqueComp) v |= PFX_CFG_MOTOR_TRQCOMP;
  if (tlgMode) v |= PFX_CFG_MOTOR_TLGMODE;
  return v;
}

void PFxMotor::to_speed_bytes(unsigned char *msg)
{ 
  msg[0] = (unsigned char)vmin;
  msg[1] = (unsigned char)vmid;
  msg[2] = (unsigned char)vmax;
  msg[3] = (unsigned char)accel;
  msg[4] = (unsigned char)decel;
}

void PFxMotor::Print()
{ std::string istr = (invert) ? "ON" : "OFF";
  std::string tstr = (torqueComp) ? "ON" : "OFF";
  std::string pstr = (tlgMode) ? "ON" : "OFF";
  printf("  Invert : %s  Torque comp : %s  PF mode : %s\n", \
    on_off_str(invert).c_str(), on_off_str(torqueComp).c_str(), on_off_str(tlgMode).c_str());
  printf("  Accel  : %d  Decel : %d\n", accel, decel);
  printf("  vMin   : %d  vMid  : %d  vMax : %d\n", vmin, vmid, vmax);
}

/* 
  PFxLights Methods 
*/

PFxLights::PFxLights()
{
  defaultBrightness = 0;
  memset(&startupBrightness[0], 0, PFX_LIGHT_PORTS);
  pfBrightnessA = 0;
  pfBrightnessB = 0;
  pfBrightnessC = 0;
  pfBrightnessD = 0;
}

PFxLights::~PFxLights()
{}
  
PFxLights::PFxLights (const PFxLights& withLights)
{
  defaultBrightness = withLights.defaultBrightness;
  memcpy(&startupBrightness[0], &withLights.startupBrightness[0], PFX_LIGHT_PORTS);
  pfBrightnessA = withLights.pfBrightnessA;
  pfBrightnessB = withLights.pfBrightnessB;
  pfBrightnessC = withLights.pfBrightnessC;
  pfBrightnessD = withLights.pfBrightnessD;
}

PFxLights& PFxLights::operator=(const PFxLights& withLights)
{
  if (this == &withLights) return *this;
  
  defaultBrightness = withLights.defaultBrightness;
  memcpy(&startupBrightness[0], &withLights.startupBrightness[0], PFX_LIGHT_PORTS);
  pfBrightnessA = withLights.pfBrightnessA;
  pfBrightnessB = withLights.pfBrightnessB;
  pfBrightnessC = withLights.pfBrightnessC;
  pfBrightnessD = withLights.pfBrightnessD;
  return *this;  
}

void PFxLights::Print()
{
  printf("Default brightness    : %02X\n", defaultBrightness);
  printf("Startup brightness    : ");
  for (int i=0; i<PFX_LIGHT_PORTS; i++) printf("%02X ", startupBrightness[i]);
  printf("\n");
  printf("PF Output brightness  : %02X %02X %02X %02X\n", \
    pfBrightnessA, pfBrightnessB, pfBrightnessC, pfBrightnessD);
}

/*
  PFxAudio Methods
*/

PFxAudio::PFxAudio()
{
  audioDRC = false;
  bass = 0;
  treble = 0;
  defaultVolume = 0;
}

PFxAudio::~PFxAudio()
{}
  
PFxAudio::PFxAudio (const PFxAudio& withAudio)
{
  audioDRC = withAudio.audioDRC;
  bass = withAudio.bass;
  treble = withAudio.treble;
  defaultVolume = withAudio.defaultVolume;
}

PFxAudio& PFxAudio::operator=(const PFxAudio& withAudio)
{
  if (this == &withAudio) return *this;

  audioDRC = withAudio.audioDRC;
  bass = withAudio.bass;
  treble = withAudio.treble;
  defaultVolume = withAudio.defaultVolume;
  return *this;
}

void PFxAudio::Print()
{
  printf("Audio DRC: %s  Bass: %02X  Treble: %02X\n", on_off_str(audioDRC).c_str(), bass, treble);
}

/*
  PFxConfig
*/

PFxConfig::PFxConfig()
{
    
}

PFxConfig::~PFxConfig()
{
  
}

PFxConfig::PFxConfig (const PFxConfig& withConfig)
{
  settings = withConfig.settings;
  lights = withConfig.lights;
  audio = withConfig.audio;
  for (int i=0; i<PFX_MOTOR_CHANNELS_MAX; i++)
  { motors[i] = withConfig.motors[i];
  }
}

PFxConfig& PFxConfig::operator=(const PFxConfig& withConfig)
{
  if (this == &withConfig) return *this;
  
  settings = withConfig.settings;
  lights = withConfig.lights;
  audio = withConfig.audio;
  for (int i=0; i<PFX_MOTOR_CHANNELS_MAX; i++)
  { motors[i] = withConfig.motors[i];
  }
  return *this;  
}

void PFxConfig::from_bytes(unsigned char *msg)
{
  lights.startupBrightness[0] = msg[1];
  lights.startupBrightness[1] = msg[2];
  lights.startupBrightness[2] = msg[3];
  lights.startupBrightness[3] = msg[4];
  lights.startupBrightness[4] = msg[5];
  lights.startupBrightness[5] = msg[6];
  settings.notchCount = msg[7];    
  settings.notchBounds[0] = msg[8];
  settings.notchBounds[1] = msg[9];
  settings.notchBounds[2] = msg[10];
  settings.notchBounds[3] = msg[11];
  settings.notchBounds[4] = msg[12];
  settings.notchBounds[5] = msg[13];
  settings.notchBounds[6] = msg[14];
  settings.irAutoOff = msg[26];
  settings.bleAutoOff = msg[27];
  settings.bleMotorWhenDisconnect = msg[28];
  settings.bleAdvertPower = msg[29];
  settings.bleSessionPower = msg[30];
  lights.startupBrightness[6] = msg[31];
  lights.startupBrightness[7] = msg[32];
  lights.pfBrightnessA = msg[33];
  lights.pfBrightnessB = msg[34];
  audio.bass = msg[35];
  audio.treble = msg[36];
  settings.statusLED = (int)(msg[37] & PFX_CFG_STATLED_MASK);
  settings.volumeBeep = (int)(msg[37] & PFX_CFG_VOLBEEP_MASK);
  settings.autoPowerDown = (int)(msg[37] & PFX_CFG_POWERSAVE_MASK);
  settings.lockoutMode = (int)(msg[37] & PFX_CFG_LOCK_MODE_MASK);
  audio.audioDRC = (bool)(msg[37] & PFX_CFG_AUDIO_DRC_MASK);
  motors[0].from_config_byte(msg[38]);
  motors[0].from_speed_bytes(&msg[39]);
  motors[1].from_config_byte(msg[44]);
  motors[1].from_speed_bytes(&msg[45]);
  motors[2].from_config_byte(msg[50]);
  motors[2].from_speed_bytes(&msg[51]);
  motors[3].from_config_byte(msg[56]);
  motors[3].from_speed_bytes(&msg[57]);
  audio.defaultVolume = msg[62];
  lights.defaultBrightness = msg[63];
}

void PFxConfig::to_bytes(unsigned char *msg)
{ int i=0;
  msg[i++] = settings.notchCount;
  msg[i++] = settings.notchBounds[0];  
  msg[i++] = settings.notchBounds[1];  
  msg[i++] = settings.notchBounds[2];  
  msg[i++] = settings.notchBounds[3];  
  msg[i++] = settings.notchBounds[4];  
  msg[i++] = settings.notchBounds[5];  
  msg[i++] = settings.notchBounds[6];  
  for (int j=0; j<11; j++) msg[i++] = 0;
  msg[i++] = settings.irAutoOff;
  msg[i++] = settings.bleAutoOff;  
  msg[i++] = settings.bleMotorWhenDisconnect;
  msg[i++] = settings.bleAdvertPower;
  msg[i++] = settings.bleSessionPower;  
  msg[i++] = audio.bass;
  msg[i++] = audio.treble;
  unsigned char v = 0;
  if (settings.statusLED == PFX_CFG_STATLED_OFF) v |= PFX_CFG_STATLED_OFF;
  else v |= PFX_CFG_STATLED_ON;
  if (settings.volumeBeep == PFX_CFG_VOLBEEP_ON) v |= PFX_CFG_VOLBEEP_ON;
  else v |= PFX_CFG_VOLBEEP_OFF;
  v |= settings.autoPowerDown;
  v |= settings.lockoutMode;
  if (audio.audioDRC) v |= PFX_CFG_AUDIO_DRC_ON;
  else v |= PFX_CFG_AUDIO_DRC_OFF;
  msg[i++] = v;
  msg[i++] = motors[0].to_config_byte();
  motors[0].to_speed_bytes(&msg[i]); i += 5;
  msg[i++] = motors[1].to_config_byte();
  motors[1].to_speed_bytes(&msg[i]); i += 5;
  msg[i++] = motors[2].to_config_byte();
  motors[2].to_speed_bytes(&msg[i]); i += 5;
  msg[i++] = motors[3].to_config_byte();
  motors[3].to_speed_bytes(&msg[i]); i += 5;
  msg[i++] = audio.defaultVolume;
  msg[i++] = lights.defaultBrightness;
  msg[i++] = lights.startupBrightness[0];
  msg[i++] = lights.startupBrightness[1];
  msg[i++] = lights.startupBrightness[2];
  msg[i++] = lights.startupBrightness[3];
  msg[i++] = lights.startupBrightness[4];
  msg[i++] = lights.startupBrightness[5];
  msg[i++] = lights.startupBrightness[6];
  msg[i++] = lights.startupBrightness[7];
  msg[i++] = lights.pfBrightnessA;
  msg[i++] = lights.pfBrightnessB;
}

void PFxConfig::Print()
{
  settings.Print();
  lights.Print();
  audio.Print();
  for (int i=0; i<PFX_MOTOR_CHANNELS_MAX; i++)
  { printf ("Motor Channel %d\n", i);
    motors[i].Print();
  }
}
