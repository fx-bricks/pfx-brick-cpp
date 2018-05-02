#include "pfx.h"

#ifndef pfxconfig_h
#define pfxconfig_h

/**
    General settings container class. A member of PFxConfig
    
    This class contains miscellaneous user preference settings such as 
    power saving modes.
*/
class PFxSettings
{
public:  
  PFxSettings();
  ~PFxSettings();
  PFxSettings (const PFxSettings& withSettings);
  PFxSettings& operator=(const PFxSettings& withSettings);

  /* Methods */
  /**
    Prints the contents of this class in human readable form
    using formatted printf statements.
  */
  void Print();
  
  /* Variables */
  /** status LED mode */
  int statusLED;
  /** volume beep mode */
  int volumeBeep;
  /** auto power down mode */
  int autoPowerDown;
  /** IR lockout activation mode */
  int lockoutMode;
  /** auto IR disable mode */
  int irAutoOff;
  /** auto BLE disable mode */
  int bleAutoOff;
  /** behaviour of motors on BLE disconnect */
  int bleMotorWhenDisconnect;
  /** BLE RF power during advertising */
  int bleAdvertPower;
  /** BLE RF power during connected session */
  int bleSessionPower;
  /** number of motor index speed notches */
  int notchCount;
  /** list of monotonic increasing speed notch boundaries */
  int notchBounds[8];
};

/**
  Motor settings container class.
  This class contains motor configuration data for one motor channel.
*/
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

  /**
    Prints the contents of this class in human readable form
    using formatted printf statements.
  */
  void Print();
  
  /* variables */
  /** invert the definition of forward/reverse */
  bool invert;
  /** activate low speed torque compensation with low frequency PWM */
  bool torqueComp;
  /** enable LEGO® Power Functions compatible PWM mode */
  bool tlgMode;
  /** acceleration factor (0 - 15 max) */
  int accel;
  /** deceleration factor (0 - 15 max) */
  int decel;
  /** speed curve minimum mapped speed (0 -> vmid-1) */
  int vmin;
  /** speed curve midpoint speed (vmin+1 -> vmax-1) */
  int vmid;
  /** speed curve maximum mapped speed (vmid+1 -> 255) */
  int vmax;    
};

/**
  Light settings container class.

  This class contains default startup brightness data for every light channel.
  All brightness values range from 0 (minimum) to 255 (maximum).
*/
class PFxLights
{
public:
  PFxLights();
  ~PFxLights();
  PFxLights (const PFxLights& withLights);
  PFxLights& operator=(const PFxLights& withLights);

  /* Methods */

  /**
    Prints the contents of this class in human readable form
    using formatted printf statements.
  */
  void Print();

  /* variables */
  /** default global brightness, if 0, then individual brightness is used */
  int defaultBrightness;
  /** list of 8 individual startup brightness values for each light output */
  int startupBrightness[PFX_LIGHT_PORTS];
  /**  startup brightness of PF channel A (when used for lights) */
  int pfBrightnessA;
  /** startup brightness of PF channel B */
  int pfBrightnessB;
  /** startup brightness of PF channel C */
  int pfBrightnessC;
  /** startup brightness of PF channel D */
  int pfBrightnessD;
};

/**
  Audio settings container class.

  This class contains audio configuration data such as default volume,
  bass, treble, etc.
*/
class PFxAudio
{
public:
  PFxAudio();
  ~PFxAudio();
  PFxAudio (const PFxAudio& withAudio);
  PFxAudio& operator=(const PFxAudio& withAudio);

  /* Methods */
  /**
    Prints the contents of this class in human readable form
    using formatted printf statements.
  */
  void Print();
  
  /* variables */
  /** enable auto Dynamic Range Control */
  bool audioDRC;
  /** startup bass EQ (-20 to 20 dB) */
  int bass;
  /** startup treble EQ (-20 to 20 dB) */
  int treble;
  /** startup volume (0 min - 255 max) */
  int defaultVolume;
};

/**
  Top level configuration data container class.
  
  This class contains catergorized container classes for groups of related settings.
  To change a configuration setting, simply access the setting value using 
  a dotted path type notation, e.g. config.lights.startupBrightness[2] = 100
*/
class PFxConfig
{
public:
  PFxConfig();
  ~PFxConfig();
  PFxConfig (const PFxConfig& withConfig);
  PFxConfig& operator=(const PFxConfig& withConfig);
  
  /* Methods */
  /**
    Converts the message string bytes read from the PFx Brick into
    the corresponding data members of this class.

    @param msg pointer to message bytes array
  */
  void from_bytes(unsigned char *msg);
  /** 
    Converts the data members of this class to the message 
    string bytes which can be sent to the PFx Brick.
  
    @param msg pointer to message bytes array
  */
  void to_bytes(unsigned char *msg);
  /**
    Prints the contents of this class in human readable form
    using formatted printf statements.
  */
  void Print();
  
  /* Variables */ 
  /** container for general settings */
  PFxSettings settings;
  /** container for default brightness settings */
  PFxLights lights;
  /** container for audio related settings */
  PFxAudio audio;
  /** an array of up to 4 containers for motor settings */
  PFxMotor motors[PFX_MOTOR_CHANNELS_MAX];
};

#endif
