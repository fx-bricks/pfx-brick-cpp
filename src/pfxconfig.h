#include "pfx.h"

#ifndef pfxconfig_h
#define pfxconfig_h

class PFxSettings
{
public:  
  PFxSettings();
  ~PFxSettings();
  PFxSettings (const PFxSettings& withSettings);
  PFxSettings& operator=(const PFxSettings& withSettings);

  /* Methods */
  void Print();
  
  /* Variables */
  int statusLED;
  int volumeBeep;
  int autoPowerDown;
  int lockoutMode;
  int irAutoOff;
  int bleAutoOff;
  int bleMotorWhenDisconnect;
  int bleAdvertPower;
  int bleSessionPower;
  int notchCount;
  int notchBounds[8];
};

class PFxMotor
{
public:
  PFxMotor();
  ~PFxMotor();
  PFxMotor (const PFxMotor& withMotor);
  PFxMotor& operator=(const PFxMotor& withMotor);

  /* Methods */
  void from_config_byte(unsigned char msg);
  void from_speed_bytes(unsigned char *msg);
  unsigned char to_config_byte();
  void to_speed_bytes(unsigned char *msg);
  void Print();
  
  /* variables */
  bool invert;
  bool torqueComp;
  bool tlgMode;
  int accel;
  int decel;
  int vmin;
  int vmid;
  int vmax;    
};

class PFxLights
{
public:
  PFxLights();
  ~PFxLights();
  PFxLights (const PFxLights& withLights);
  PFxLights& operator=(const PFxLights& withLights);

  /* Methods */
  void Print();

  /* variables */
  int defaultBrightness;
  int startupBrightness[PFX_LIGHT_PORTS];
  int pfBrightnessA;
  int pfBrightnessB;
  int pfBrightnessC;
  int pfBrightnessD;
};

class PFxAudio
{
public:
  PFxAudio();
  ~PFxAudio();
  PFxAudio (const PFxAudio& withAudio);
  PFxAudio& operator=(const PFxAudio& withAudio);

  /* Methods */
  void Print();
  
  /* variables */
  bool audioDRC;
  int bass;
  int treble;
  int defaultVolume;
};

class PFxConfig
{
public:
  PFxConfig();
  ~PFxConfig();
  PFxConfig (const PFxConfig& withConfig);
  PFxConfig& operator=(const PFxConfig& withConfig);
  
  /* Methods */
  void from_bytes(unsigned char *msg);
  void to_bytes(unsigned char *msg);
  void Print();
  
  /* Variables */ 
  PFxSettings settings;
  PFxLights lights;
  PFxAudio audio;
  PFxMotor motors[PFX_MOTOR_CHANNELS_MAX];
};

#endif
