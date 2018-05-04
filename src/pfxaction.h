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

#include "pfx.h"

#ifndef pfxaction_h
#define pfxaction_h

/**
    Action data structure class.
    
    This class reflects the 16 byte data structure used internally
    by the PFx Brick to execute a composite action of motor, lighting,
    and sound effects.
*/
class PFxAction
{
public:
  PFxAction();
  ~PFxAction();
  PFxAction (const PFxAction& withAction);
  PFxAction& operator=(const PFxAction& withAction);
  
  /* Methods */
  /**
    Prints the contents of this class in human readable form
    using formatted printf statements.
  */
  void Print();
  /**
    Populates an action to set the speed of specified motor channel(s).
    The motor speed is specified between -100% and +100% where negative
    values are in the reverse direction and positive values are in
    the forward direction.
    
    @param ch a list of motor channels as a string, e.g. "A", "1, 2", "AB" are all valid
    @param speed desired motor speed (-100 to +100)
    @param duration optional duration (in seconds) to run motor, runs indefinitely if set to 0
    @returns a PFxAction reference to this instance       
    
    If the duration value is specified, it represents the desired motor
    run time in seconds. Note that this value will be rounded to the 
    nearest fixed interval of the DURATION parameter as defined in the ICD
    ranging between 16 fixed values from 0.5 sec to 5 min.
  */
  PFxAction& set_motor_speed(std::string ch, int speed, double duration);
  /**
    Convenience wrapper for set_motor_speed with no duration value specified.
  */
  PFxAction& set_motor_speed(std::string ch, int speed) { return set_motor_speed(ch, speed, 0); }
  /**
    Populates an action to stop the specifed motor channel(s).

    @param ch a list of motor channels as a string, e.g. "A", "1, 2", "AB" are all valid
    @returns a PFxAction reference to this instance       
  */
  PFxAction& stop_motor(std::string ch);
  /**
    Populates an action to turn on selected light outputs.
    
    @param ch a list of light channels as a string, e.g. "1", "3, 6", "4567" are all valid
    @returns a PFxAction reference to this instance       
  */
  PFxAction& light_on(std::string ch);
  /**
    Populates an action to turn off selected light outputs.
  
    @param ch a list of light channels as a string, e.g. "1", "3, 6", "4567" are all valid
    @returns a PFxAction reference to this instance       
  */
  PFxAction& light_off(std::string ch);
  /**
    Populates an action to toggle the state of selected light outputs.
  
    @param ch a list of light channels as a string, e.g. "1", "3, 6", "4567" are all valid
    @returns a PFxAction reference to this instance       
  */
  PFxAction& light_toggle(std::string ch);
  /**
    Populates an action to set the brightness of selected light outputs.
    
    @param brightness desired brightness (0 - 255 max)
    @returns a PFxAction reference to this instance       
  */
  PFxAction& set_brightness(std::string ch, int brightness);
  /**
    Populates an action with a user specified combination light effect
    and associated parameters.
    
    @param fx desired light effect
    @param param a vector of up to 5 light parameters
    @returns a PFxAction reference to this instance       
  */
  PFxAction& combo_light_fx(int fx, std::vector<int> param);
  /**
    Populates an action with a user specified light effect and
    associated parameters.
    
    @param ch a list of light channels as a string, e.g. "1", "3, 6", "4567" are all valid
    @param fx desired light effect
    @param param a vector of up to 5 light parameters
    @returns a PFxAction reference to this instance       
    
    The details of specifying the light **fx** and **param** items
    is described in detail in the ICD document. The **pfx.h** 
    file contains convenient pre-defined constants for all of
    the light effect types and parameter values.
    
    An example of using this method is as follows::
  
        std::vector<int> p(4);    
        p[0] = EVT_PERIOD_1S;
        p[1] = EVT_DUTYCY_10;
        p[2] = EVT_BURST_COUNT_2;
        p[3] = EVT_TRANSITION_TOGGLE;
        PFxAction a = PFxAction().light_fx("1,4", EVT_LIGHTFX_STROBE_P, p);
    
    This specifies a strobe light effect on channels 1 and 4 with
    a 1 second period, 10% duty cycle, two light pulses and with
    a toggle activation.
  */
  PFxAction& light_fx(std::string ch, int fx, std::vector<int> param);
  /**
    Populates an action with a user specified sound effect and
    associated parameters.
    
    @param fx desired sound action
    @param param: a vector of up to 2 sound parameters
    @param fileID: file ID of an audio file in the file system
    @returns a PFxAction reference to this instance       
    
    The details of specifying the sound **fx** and **param** items
    is described in detail in the ICD document. The **pfx.h** 
    file contains convenient pre-defined constants for all of
    the sound effect types and parameter values.
    
    An example of using this method is as follows::
    
        std::vector<int> p(1);    
        p[0] = EVT_SOUND_DUR_10S;
        PFxAction a = PFxAction().sound_fx(EVT_SOUND_PLAY_DUR, p, 5);
    
    This specifies an action to playback an audio file with ID=5 
    for a fixed duration of 10 seconds.
  */
  PFxAction& sound_fx(int fx, std::vector<int> param, int fileID);
  /**
    Populates an action to play an audio file once.
    
    @param fileID file ID of an audio file in the file system
    @returns a PFxAction reference to this instance       
    
    This is a convenience wrapper for the sound_fx method.
  */
  PFxAction& play_audio_file(int fileID);
  /**
    Populates an action to stop playback of an audio file.
    
    @param fileID file ID of an audio file in the file system
    @returns a PFxAction reference to this instance       
    
    This is a convenience wrapper for the sound_fx method.
  */
  PFxAction& stop_audio_file(int fileID);
  /**
    Populates an action for repeated playback of an audio file.
  
    @param fileID file ID of an audio file in the file system
    @returns a PFxAction reference to this instance       
  
    This is a convenience wrapper for the sound_fx method.
  */
  PFxAction& repeat_audio_file(int fileID);
  /**
    Populates an action to set the audio volume.

    @param volume desired audio volume (0 - 100%)
    @returns a PFxAction reference to this instance       

    This is a convenience wrapper for the sound_fx method.
  */
  PFxAction& set_volume(int volume);
  
  /** 
    Converts the data members of this class to the message 
    string bytes which can be sent to the PFx Brick.

    @param msg pointer to message bytes array
  */
  void to_bytes (unsigned char *msg) const;
  
  /**
    Converts the message string bytes read from the PFx Brick into
    the corresponding data members of this class.
  */
  void from_bytes(unsigned char *msg);
  
  /* Variables */
  /** Command byte */
  int command;
  /** Motor action ID and motor channel mask byte */
  int motorActionId;
  /** Motor parameter 1 */
  int motorParam1;
  /** Motor parameter 2 */
  int motorParam2; 
  /** Light Fx ID byte */
  int lightFxId;
  /** Light channel output mask */
  int lightOutputMask;
  /** Light channel on PF output mask */
  int lightPFOutputMask;
  /** Lighting parameter 1 */
  int lightParam1;
  /** Lighting parameter 2 */
  int lightParam2;
  /** Lighting parameter 3 */
  int lightParam3;
  /** Lighting parameter 4 */
  int lightParam4; 
  /** Lighting parameter 5 */
  int lightParam5; 
  /** Sound Fx ID byte */
  int soundFxId;
  /** Sound file ID */
  int soundFileId; 
  /** Sound parameter 1 */
  int soundParam1;
  /** Sound parameter 2 */
  int soundParam2;

};

#endif
