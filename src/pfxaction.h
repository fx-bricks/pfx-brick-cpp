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
