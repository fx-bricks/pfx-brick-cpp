#include "pfx.h"

#ifndef pfxaction_h
#define pfxaction_h

class PFxAction
{
public:
  PFxAction();
  ~PFxAction();
  PFxAction (const PFxAction& withAction);
  PFxAction& operator=(const PFxAction& withAction);
  
  /* Methods */
  void Print();
  PFxAction& set_motor_speed(std::string ch, int speed, double duration);
  PFxAction& set_motor_speed(std::string ch, int speed) { return set_motor_speed(ch, speed, 0); }
  PFxAction& stop_motor(std::string ch);
  PFxAction& light_on(std::string ch);
  PFxAction& light_off(std::string ch);
  PFxAction& light_toggle(std::string ch);
  PFxAction& set_brightness(std::string ch, int brightness);
  PFxAction& combo_light_fx(int fx, std::vector<int> param);
  PFxAction& light_fx(std::string ch, int fx, std::vector<int> param);
  PFxAction& sound_fx(int fx, std::vector<int> param, int fileID);
  PFxAction& play_audio_file(int fileID);
  PFxAction& stop_audio_file(int fileID);
  PFxAction& repeat_audio_file(int fileID);
  PFxAction& set_volume(int volume);
  
  /* Variables */
  int command;
  int motorActionId;
  int motorParam1;
  int motorParam2; 
  int lightFxId;
  int lightOutputMask;
  int lightPFOutputMask;
  int lightParam1;
  int lightParam2;
  int lightParam3;
  int lightParam4; 
  int lightParam5; 
  int soundFxId;
  int soundFileId; 
  int soundParam1;
  int soundParam2;

};

#endif
