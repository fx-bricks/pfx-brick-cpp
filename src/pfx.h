/*******************************************************************************
 *******************************************************************************

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


 PFXBrick Top Level Definitions

  File Name:
    pfx.h

  Summary:
    Defines types and APIs associated with the PFx Brick.

  Description:
    Defines types and APIs associated with the PFx Brick.

  Copyright (c) 2017  Fx Bricks Inc.

  Jun 3, 2016

  Jun 8, 2016 : Added USB HID messages to support event table definition
                for EV3 IR remote beacon:
                  PFX_USB_CMD_GET_EVENT_CH1_EV3
                  PFX_USB_CMD_SET_EVENT_CH1_EV3
                  PFX_USB_CMD_GET_EVENT_CH2_EV3
                  PFX_USB_CMD_SET_EVENT_CH2_EV3
                  PFX_USB_CMD_GET_EVENT_CH3_EV3
                  PFX_USB_CMD_SET_EVENT_CH3_EV3
                  PFX_USB_CMD_GET_EVENT_CH4_EV3
                  PFX_USB_CMD_SET_EVENT_CH4_EV3
                Added a motor configuration parameter which enables low
                freq PWM at low speeds for torque compensation:
                  PFX_CFG_MOTOR_TRQCOMP
  
  Jul 28, 2016 : Added new parameters types.  Added new command messages.
 
  Aug 10, 2016 : Added error code defines

  Aug 12, 2016 : Major redesign based on future-proofing capacity
 
  Sep 23, 2016 : Added the PFX_USB_CMD_GET_ICD_REV message
                 Redefined the MOTOR_STOP and MOTOR_COAST definitions
                 Added the EVT_COMMAND_IR_LOCK_TOGGLE command
                 Added the PFX_CFG_AUDIO_DRC_MASK to the PFX settings config byte
  
  Oct 14, 2016 : Changed the PFX_USB_CMD_GET_STATUS message format
                 Changed the PFX_USB_CMD_GET_CONFIG message format
                 Other changes to reflect ICD v.3.0

  Oct 24, 2016 : Changed to reflect ICD v.3.14

  Nov 7, 2016  : Changed to reflect ICD v.3.15
 
  Nov 27, 2016 : Changed to reflect ICD v.3.16
  
  Dec 16, 2016 : Added new product descriptor for updated PCB

  Dec 18, 2016 : Changed to reflect ICD v.3.17
  
  Jan 25, 2017 : Changed to reflect ICD v.3.20
  
  Mar 25, 2017 : Added more constant defines shared between firmware and App
                 Changes to reflect ICD v.3.22
   
  May 15, 2017 : Added more product defines and masks
  
  Jul 4, 2017  : Updated product part number/descriptors

  Aug 31, 2017 : Updated to reflect ICD 3.30
  
  Oct 12, 2017 : Updated to reflect ICD 3.33

  Dec 12, 2017 : Updated to reflect ICD 3.36
 
*******************************************************************************
*******************************************************************************/


#ifndef _PFX_H_
#define _PFX_H_

#ifdef	__cplusplus
extern "C" {
#endif

/*******************************************************************************
 *******************************************************************************

 PFX Product Descriptors
  
*******************************************************************************
*******************************************************************************/

#define PFX_USB_VENDOR_ID             0x04D8   // Microchip Inc's registered VID
#define PFX_USB_PRODUCT_ID            0xEF74   // official USB PID for the PFx
#define PFX_USB_PRODUCT_ID_LEGACY     0x00F8   // unofficial/legacy USB PID for the PFx
#define PFX_USB_USAGE_PAGE            0xFF00
#define PFX_USB_USAGE_HID_1           0x0001
#define PFX_USB_USAGE_HID_2           0x0002
#define PFX_USB_USAGE_HID_3           0x0003
#define PFX_USB_USAGE_HID_4           0x0004

#define PFX_BLE_GATT_DEV_INFO_UUID    0x180A
#define PFX_BLE_GATT_UART_UUID        "49535343-FE7D-4AE5-8FA9-9FAFD205E455"
#define PFX_BLE_GATT_UART_RX_UUID     "49535343-1E4D-4BD9-BA61-23C647249616"
#define PFX_BLE_GATT_UART_TX_UUID     "49535343-8841-43F4-A8D4-ECBE34729BB3"
#define PFX_BLE_GATT_UART_TXRESP_UUID "49535343-A4C8-39B3-2F49-511CFF073B7E"
                                    
#define PFX_PFXBRICK_PROD_MASK        0x0F00
#define PFX_PFXBRICK_PROD             0x0200  
#define PFX_PFXBRICK_BT_MASK          0x8000
#define PFX_PFXBRICK_PRODUCTION_MASK  0x3F00
#define PFX_PFXBRICK_PRODUCTION_PN    0x2200
#define PFX_PFXBRICK_ALPHA_PN         0x1201
#define PFX_PFXBRICK_ALPHA_DESC       "PFx Brick alpha"
#define PFX_PFXBRICK_ALPHA_FLASH_SZ   0x80000
#define PFX_PFXBRICK_BETA_PN          0x1202
#define PFX_PFXBRICK_BETA_DESC        "PFx Brick beta"
#define PFX_PFXBRICK_BETA_FLASH_SZ    0x400000
#define PFX_PFXBRICK_GAMMA_PN         0x1203
#define PFX_PFXBRICK_GAMMA_DESC       "PFx Brick gamma"
#define PFX_PFXBRICK_GAMMA_FLASH_SZ   0x400000
#define PFX_PFXBRICK_DELTA_PN         0x1204
#define PFX_PFXBRICK_DELTA_DESC       "PFx Brick delta"
#define PFX_PFXBRICK_DELTA_FLASH_SZ   0x400000
#define PFX_PFXBRICK_DELTA_IR_PN      0x9204
#define PFX_PFXBRICK_DELTA_IR_DESC    "PFx Brick delta IR"
#define PFX_PFXBRICK_DELTA_IR_FLASH_SZ 0x400000
#define PFX_PFXBRICK_IR_4MB_PN        0x2204
#define PFX_PFXBRICK_IR_4MB_DESC      "PFx Brick IR 4 MB"
#define PFX_PFXBRICK_IR_4MB_FLASH_SZ  0x400000
#define PFX_PFXBRICK_IR_8MB_PN        0x2208
#define PFX_PFXBRICK_IR_8MB_DESC      "PFx Brick IR 8 MB"
#define PFX_PFXBRICK_IR_8MB_FLASH_SZ  0x800000
#define PFX_PFXBRICK_IR_16MB_PN       0x2216
#define PFX_PFXBRICK_IR_16MB_DESC     "PFx Brick IR 16 MB"
#define PFX_PFXBRICK_IR_16MB_FLASH_SZ 0x1000000
#define PFX_PFXBRICK_4MB_PN           0xA204
#define PFX_PFXBRICK_4MB_DESC         "PFx Brick 4 MB"
#define PFX_PFXBRICK_4MB_FLASH_SZ     0x400000
#define PFX_PFXBRICK_8MB_PN           0xA208
#define PFX_PFXBRICK_8MB_DESC         "PFx Brick 8 MB"
#define PFX_PFXBRICK_8MB_FLASH_SZ     0x800000
#define PFX_PFXBRICK_16MB_PN          0xA216
#define PFX_PFXBRICK_16MB_DESC        "PFx Brick 16 MB"
#define PFX_PFXBRICK_16MB_FLASH_SZ    0x1000000
#define PFX_PFXBRICK_GENERIC_PN       0x1200
#define PFX_PFXBRICK_GENERIC_DESC     "PFx Brick"
#define PFX_PFXBRICK_GENERIC_FLASH_SZ  0x400000

#define PFX_PFXLITE_PROD_MASK         0x0F00
#define PFX_PFXLITE_PROD              0x0700
#define PFX_PFXLITE_ALPHA_PN          0x1701
#define PFX_PFXLITE_ALPHA_DESC        "PFx Lite alpha"
#define PFX_PFXLITE_ALPHA_FLASH_SZ    0x80000
#define PFX_PFXLITE_PN                0x2701
#define PFX_PFXLITE_DESC              "PFx Lite"
#define PFX_PFXLITE_FLASH_SZ          0x80000

#define PFX_PFXBRICK_PRO_ALPHA_PN     0x1401
#define PFX_PFXBRICK_PRO_ALPHA_DESC   "PFx Brick Pro alpha"
#define PFX_PFXBRICK_PRO_ALPHA_FLASH_SZ 0x400000
#define PFX_PFXBRICK_PRO_4MB_PN       0xA404
#define PFX_PFXBRICK_PRO_4MB_DESC     "PFx Brick Pro 4 MB"
#define PFX_PFXBRICK_PRO_4MB_FLASH_SZ 0x400000
#define PFX_PFXBRICK_PRO_8MB_PN       0xA408
#define PFX_PFXBRICK_PRO_8MB_DESC     "PFx Brick Pro 8 MB"
#define PFX_PFXBRICK_PRO_8MB_FLASH_SZ 0x800000
#define PFX_PFXBRICK_PRO_16MB_PN      0xA416
#define PFX_PFXBRICK_PRO_16MB_DESC    "PFx Brick Pro 16 MB"
#define PFX_PFXBRICK_PRO_16MB_FLASH_SZ 0x1000000

#define PFX_PFXBRICK_DCC_ALPHA_PN     0x1301
#define PFX_PFXBRICK_DCC_ALPHA_DESC   "PFx Brick DCC alpha"
#define PFX_PFXBRICK_DCC_PN           0x2302
#define PFX_PFXBRICK_DCC_DESC         "PFx Brick DCC"

#define PFX_PFXBOT_ALPHA_PN           0x1501
#define PFX_PFXBOT_ALPHA_DESC         "PFx Bot alpha"
#define PFX_PFXBOT_PN                 0x2502
#define PFX_PFXBOT_DESC               "PFx Bot"
                                     
#define PFX_FLASH_SECTOR_SZ           0x1000
  
/*******************************************************************************
 *******************************************************************************

 Configuration Definitions
  
*******************************************************************************
*******************************************************************************/

#define PFX_NAME_MAX                  24
#define PFX_VER_MAJOR_MASK            0xFF00
#define PFX_VER_MINOR_MASK            0x00FF
                                      
#define PFX_CFG_AUDIO_DRC_MASK        0x40
#define PFX_CFG_LOCK_MODE_MASK        0x30
#define PFX_CFG_STATLED_MASK          0x01
#define PFX_CFG_VOLBEEP_MASK          0x02
#define PFX_CFG_POWERSAVE_MASK        0x0C
                                     
#define PFX_CFG_STATLED_OFF           0x01
#define PFX_CFG_STATLED_ON            0x00
#define PFX_CFG_VOLBEEP_ON            0x02
#define PFX_CFG_VOLBEEP_OFF           0x00
#define PFX_CFG_POWERSAVE_OFF         0x00
#define PFX_CFG_POWERSAVE_30M         0x04
#define PFX_CFG_POWERSAVE_60M         0x08
#define PFX_CFG_POWERSAVE_3HR         0x0C
#define PFX_CFG_POWERSAVE_MASK        0x0C
#define PFX_CFG_LOCKOUT_INH           0x00
#define PFX_CFG_LOCKOUT_CH1           0x10
#define PFX_CFG_LOCKOUT_ALLCH         0x20
#define PFX_CFG_AUDIO_DRC_ON          0x40
#define PFX_CFG_AUDIO_DRC_OFF         0x00

#define PFX_CFG_IRAUTO_OFF_NEVER      0x0
#define PFX_CFG_IRAUTO_OFF_1MIN       0x1
#define PFX_CFG_IRAUTO_OFF_5MIN       0x2
#define PFX_CFG_IRAUTO_OFF_IMMEDIATE  0x3

#define PFX_CFG_BLEAUTO_OFF_NEVER     0x0
#define PFX_CFG_BLEAUTO_OFF_1MIN      0x1
#define PFX_CFG_BLEAUTO_OFF_5MIN      0x2
#define PFX_CFG_BLEAUTO_OFF_IMMEDIATE 0x3

#define PFX_CFG_BLE_MOTOR_CONTINUE    0x0
#define PFX_CFG_BLE_MOTOR_STOP        0x1

#define PFX_CFG_BLE_TX_PWR_MAX        0x0
#define PFX_CFG_BLE_TX_PWR_MIN        0x5
  
#define PFX_CFG_MOTOR_INVERT          0x01
#define PFX_CFG_MOTOR_NORMAL          0x00
#define PFX_CFG_MOTOR_TRQCOMP         0x02
#define PFX_CFG_MOTOR_TLGMODE         0x04
                                  
#define PFX_AUDIO_FILES_MAX           60
#define PFX_AUDIO_FILENAME_MAX        32
#define PFX_AUDIO_CHANNELS            4
                                  
#define PFX_MOTOR_CHANNELS            2
#define PFX_MOTOR_CHANNELS_MAX        4
#define PFX_LIGHT_PORTS               8
#define PFX_LIGHT_CHANNELS            10
#define PFX_LIGHT_CHANNELS_MAX        12

/*******************************************************************************
 *******************************************************************************

 Default Value Definitions
  
*******************************************************************************
*******************************************************************************/

#define PFX_DEFAULT_NAME              "My PFx Brick"
#define PFX_DEFAULT_STATLED           PFX_CFG_STATLED_ON
#define PFX_DEFAULT_VOLBEEP           PFX_CFG_VOLBEEP_OFF
#define PFX_DEFAULT_POWERSAVE         PFX_CFG_POWERSAVE_OFF
#define PFX_DEFAULT_LOCKOUT           PFX_CFG_LOCKOUT_INH
#define PFX_DEFAULT_AUDIO_DRC         PFX_CFG_AUDIO_DRC_OFF
#define PFX_DEFAULT_AUDIO_BASS        0
#define PFX_DEFAULT_AUDIO_TREBLE      0
#define PFX_DEFAULT_BRIGHTNESS        0xC0
#define PFX_DEFAULT_VOLUME            0xA0
#define PFX_DEFAULT_IRAUTO_OFF        PFX_CFG_IRAUTO_OFF_NEVER
#define PFX_DEFAULT_BLEAUTO_OFF       PFX_CFG_BLEAUTO_OFF_NEVER
#define PFX_DEFAULT_BLE_MOTOR         PFX_CFG_BLE_MOTOR_CONTINUE
#define PFX_DEFAULT_BLE_ADV_TXPWR     PFX_CFG_BLE_TX_PWR_MAX
#define PFX_DEFAULT_BLE_SESS_TXPWR    PFX_CFG_BLE_TX_PWR_MAX

/*******************************************************************************
 *******************************************************************************

 Event Table Definitions
  
*******************************************************************************
*******************************************************************************/

#define EVT_LUT_MAX                   0x7F    // maximum number of LUT entries
                                      
#define EVT_ID_8879_TWO_BUTTONS       0x0
#define EVT_ID_8879_LEFT_BUTTON       0x1
#define EVT_ID_8879_RIGHT_BUTTON      0x2
#define EVT_ID_8879_LEFT_INC          0x3
#define EVT_ID_8879_LEFT_DEC          0x4
#define EVT_ID_8879_RIGHT_INC         0x5
#define EVT_ID_8879_RIGHT_DEC         0x6
#define EVT_ID_8885_LEFT_FWD          0x7
#define EVT_ID_8885_LEFT_REV          0x8
#define EVT_ID_8885_RIGHT_FWD         0x9
#define EVT_ID_8885_RIGHT_REV         0xA
#define EVT_ID_8885_LEFT_CTROFF       0xB
#define EVT_ID_8885_RIGHT_CTROFF      0xC
#define EVT_ID_EV3_BEACON             0xD
#define EVT_ID_TEST_EVENT             0xE
#define EVT_ID_STARTUP_EVENT          0xF
#define EVT_ID_STARTUP_EVENT2         0x10
#define EVT_ID_RCTRAIN_UP             0x14
#define EVT_ID_RCTRAIN_DOWN           0x15
#define EVT_ID_RCTRAIN_STOP           0x16
#define EVT_ID_RCTRAIN_HORN           0x17
                                      
#define EVT_ID_MAX                    0x20

/*******************************************************************************
 Convenient left-shifted versions of the event ID 
   The event ID occupies byte positions <5:2> 
   IR channel occupies byte positions <1:0>
   These event ID definitions can be logically OR-ed with the channel number
   for indexing into the event LUT. 
*******************************************************************************/
#define EVT_8879_TWO_BUTTONS          0x00
#define EVT_8879_LEFT_BUTTON          0x04
#define EVT_8879_RIGHT_BUTTON         0x08
#define EVT_8879_LEFT_INC             0x0C
#define EVT_8879_LEFT_DEC             0x10
#define EVT_8879_RIGHT_INC            0x14
#define EVT_8879_RIGHT_DEC            0x18
#define EVT_8885_LEFT_FWD             0x1C
#define EVT_8885_LEFT_REV             0x20
#define EVT_8885_RIGHT_FWD            0x24
#define EVT_8885_RIGHT_REV            0x28
#define EVT_8885_LEFT_CTROFF          0x2C
#define EVT_8885_RIGHT_CTROFF         0x30
#define EVT_EV3_BEACON                0x34
#define EVT_TEST_EVENT                0x38
#define EVT_DEFAULT_EVENT             0x3C
#define EVT_STARTUP_EVENT1            0x3C
#define EVT_STARTUP_EVENT2            0x3D
#define EVT_STARTUP_EVENT3            0x3E
#define EVT_STARTUP_EVENT4            0x3F
#define EVT_STARTUP_EVENT5            0x40
#define EVT_STARTUP_EVENT6            0x41
#define EVT_STARTUP_EVENT7            0x42
#define EVT_STARTUP_EVENT8            0x43
#define EVT_RCTRAIN_UP                0x50
#define EVT_RCTRAIN_DOWN              0x54
#define EVT_RCTRAIN_STOP              0x58
#define EVT_RCTRAIN_HORN              0x5C
#define EVT_SPARKFUN_POWER            0x60
#define EVT_SPARKFUN_A                0x61
#define EVT_SPARKFUN_B                0x62
#define EVT_SPARKFUN_C                0x63
#define EVT_SPARKFUN_UP               0x64
#define EVT_SPARKFUN_DOWN             0x65
#define EVT_SPARKFUN_LEFT             0x66
#define EVT_SPARKFUN_RIGHT            0x67
#define EVT_ADAFRUIT_VOLDOWN          0x68
#define EVT_ADAFRUIT_PLAY             0x69
#define EVT_ADAFRUIT_VOLUP            0x6A
#define EVT_ADAFRUIT_SETUP            0x6B
#define EVT_ADAFRUIT_STOP             0x6C
#define EVT_ADAFRUIT_UP               0x6D
#define EVT_ADAFRUIT_DOWN             0x6E
#define EVT_ADAFRUIT_LEFT             0x6F
#define EVT_ADAFRUIT_RIGHT            0x70
#define EVT_ADAFRUIT_ENTER            0x71
#define EVT_ADAFRUIT_REPEAT           0x72
#define EVT_ADAFRUIT_0                0x73
#define EVT_ADAFRUIT_1                0x74
#define EVT_ADAFRUIT_2                0x75
#define EVT_ADAFRUIT_3                0x76
#define EVT_ADAFRUIT_4                0x77
#define EVT_ADAFRUIT_5                0x78
#define EVT_ADAFRUIT_6                0x79
#define EVT_ADAFRUIT_7                0x7A
#define EVT_ADAFRUIT_8                0x7B
#define EVT_ADAFRUIT_9                0x7C
  
#define EVT_INVALID                   0xFF
#define EVT_EVENT_ID_MAX              0x20
#define EVT_EVENT_ID_MASK             0x7C
#define EVT_EVENT_CH_MASK             0x03

/*******************************************************************************
 Byte indexes
*******************************************************************************/
#define EVT_ACT_COMMAND               0x0
#define EVT_ACT_MOTOR_ACTION_ID       0x1
#define EVT_ACT_MOTOR_MASK            0x1
#define EVT_ACT_MOTOR_PARAM1          0x2
#define EVT_ACT_MOTOR_PARAM2          0x3
#define EVT_ACT_LIGHT_FX_ID           0x4
#define EVT_ACT_LIGHT_OUTPUT_MASK     0x5
#define EVT_ACT_LIGHT_PF_OUTPUT_MASK  0x6
#define EVT_ACT_LIGHT_PARAM1          0x7
#define EVT_ACT_LIGHT_PARAM2          0x8
#define EVT_ACT_LIGHT_PARAM3          0x9
#define EVT_ACT_LIGHT_PARAM4          0xA
#define EVT_ACT_LIGHT_PARAM5          0xB
#define EVT_ACT_SOUND_FX_ID           0xC
#define EVT_ACT_SOUND_FILE_ID         0xD
#define EVT_ACT_SOUND_PARAM1          0xE
#define EVT_ACT_SOUND_PARAM2          0xF

/*******************************************************************************
 Byte 0 - COMMAND
*******************************************************************************/
#define EVT_COMMAND_NONE              0x00
#define EVT_COMMAND_ALL_OFF           0x01
#define EVT_COMMAND_IR_LOCKOUT_ON     0x02
#define EVT_COMMAND_IR_LOCKOUT_OFF    0x03
#define EVT_COMMAND_IR_LOCK_TOGGLE    0x04
#define EVT_COMMAND_ALL_MOTORS_OFF    0x05
#define EVT_COMMAND_ALL_LIGHTS_OFF    0x06
#define EVT_COMMAND_ALL_AUDIO_OFF     0x07
#define EVT_COMMAND_RESTART           0x08

/*******************************************************************************
 Byte 1 - MOTOR_ACTION_ID / MOTOR_MASK
*******************************************************************************/
#define EVT_MOTOR_ACTION_ID_MASK      0xF0
#define EVT_MOTOR_OUTPUT_MASK         0x0F
                                      
#define EVT_MOTOR_ESTOP               0x00
#define EVT_MOTOR_STOP                0x10
#define EVT_MOTOR_INC_SPD             0x20
#define EVT_MOTOR_DEC_SPD             0x30
#define EVT_MOTOR_INC_SPD_BI          0x40
#define EVT_MOTOR_DEC_SPD_BI          0x50
#define EVT_MOTOR_CHANGE_DIR          0x60
#define EVT_MOTOR_SET_SPD             0x70
#define EVT_MOTOR_SET_SPD_TIMED       0x80
#define EVT_MOTOR_OSCILLATE           0x90
#define EVT_MOTOR_OSCILLATE_BIDIR     0xA0
#define EVT_MOTOR_OSCILLATE_BIDIR_WAIT 0xB0
#define EVT_MOTOR_WIPE                0x90
#define EVT_MOTOR_WIPE_BIDIR          0xA0
#define EVT_MOTOR_WIPE_BIDIR_WAIT     0xB0
#define EVT_MOTOR_RANDOM              0xC0
#define EVT_MOTOR_RANDOM_BIDIR        0xD0
#define EVT_MOTOR_SOUND_MODULATED     0xE0
                                     
#define EVT_MOTOR_OUTPUT_A            0x01
#define EVT_MOTOR_OUTPUT_B            0x02
#define EVT_MOTOR_OUTPUT_C            0x04
#define EVT_MOTOR_OUTPUT_D            0x08

/*******************************************************************************
 Byte 2 - MOTOR_PARAM1 
 Byte 3 - MOTOR_PARAM2 
*******************************************************************************/

// MOTOR_STEP Parameter
#define EVT_MOTOR_STEP_DEFAULT        0x0
#define EVT_MOTOR_STEP_1PCT           0x1
#define EVT_MOTOR_STEP_2PCT           0x2
#define EVT_MOTOR_STEP_3PCT           0x3
#define EVT_MOTOR_STEP_5PCT           0x4
#define EVT_MOTOR_STEP_6PCT           0x5
#define EVT_MOTOR_STEP_10PCT          0x6
#define EVT_MOTOR_STEP_20PCT          0x7
#define EVT_MOTOR_STEP_25PCT          0x8
#define EVT_MOTOR_STEP_33PCT          0x9
#define EVT_MOTOR_STEP_TLG7STEP       0xA
                                 
// MOTOR_SPEED Parameter               
#define EVT_MOTOR_SPEED_STOP          0x0
#define EVT_MOTOR_SPEED_FWD_10        0x1
#define EVT_MOTOR_SPEED_FWD_25        0x2
#define EVT_MOTOR_SPEED_FWD_33        0x3
#define EVT_MOTOR_SPEED_FWD_50        0x4
#define EVT_MOTOR_SPEED_FWD_67        0x5
#define EVT_MOTOR_SPEED_FWD_75        0x6
#define EVT_MOTOR_SPEED_FWD_100       0x7
#define EVT_MOTOR_SPEED_REV_STOP      0x8
#define EVT_MOTOR_SPEED_REV_10        0x9
#define EVT_MOTOR_SPEED_REV_25        0xA
#define EVT_MOTOR_SPEED_REV_33        0xB
#define EVT_MOTOR_SPEED_REV_50        0xC
#define EVT_MOTOR_SPEED_REV_67        0xD
#define EVT_MOTOR_SPEED_REV_75        0xE
#define EVT_MOTOR_SPEED_REV_100       0xF
#define EVT_MOTOR_SPEED_LO_MASK       0xF
#define EVT_MOTOR_SPEED_HIRES_MASK    0x3F
#define EVT_MOTOR_SPEED_HIRES         0x80
#define EVT_MOTOR_SPEED_HIRES_REV     0x40
#define EVT_MOTOR_SPEED_HIRES_FWD     0x80

// MOTOR_PERIOD Parameter
#define EVT_MOTOR_PERIOD_250MS        0x0
#define EVT_MOTOR_PERIOD_500MS        0x1
#define EVT_MOTOR_PERIOD_750MS        0x2
#define EVT_MOTOR_PERIOD_1S           0x3
#define EVT_MOTOR_PERIOD_1_25S        0x4
#define EVT_MOTOR_PERIOD_1_5S         0x5
#define EVT_MOTOR_PERIOD_2S           0x6
#define EVT_MOTOR_PERIOD_2_5S         0x7
#define EVT_MOTOR_PERIOD_3S           0x8
#define EVT_MOTOR_PERIOD_4S           0x9
#define EVT_MOTOR_PERIOD_5S           0xA
#define EVT_MOTOR_PERIOD_10S          0xB
#define EVT_MOTOR_PERIOD_15S          0xC
#define EVT_MOTOR_PERIOD_20S          0xD
#define EVT_MOTOR_PERIOD_30S          0xE
#define EVT_MOTOR_PERIOD_60S          0xF
#define EVT_MOTOR_PERIOD_ON_MASK     0x0F
#define EVT_MOTOR_PERIOD_OFF_MASK    0xF0

/*******************************************************************************
 Byte 4 - LIGHT_FX_ID
*******************************************************************************/
#define EVT_LIGHT_COMBO_MASK          0x80
#define EVT_LIGHT_ID_MASK             0x7F
                                      
#define EVT_LIGHTFX_NONE              0x00
#define EVT_LIGHTFX_ON_OFF_TOGGLE     0x01
#define EVT_LIGHTFX_INC_BRIGHT        0x02
#define EVT_LIGHTFX_DEC_BRIGHT        0x03
#define EVT_LIGHTFX_SET_BRIGHT        0x04
#define EVT_LIGHTFX_FLASH50_P         0x05
#define EVT_LIGHTFX_FLASH50_N         0x06
#define EVT_LIGHTFX_STROBE_P          0x07
#define EVT_LIGHTFX_STROBE_N          0x08
#define EVT_LIGHTFX_GYRALITE_P        0x09
#define EVT_LIGHTFX_GYRALITE_N        0x0A
#define EVT_LIGHTFX_FLICKER           0x0B
#define EVT_LIGHTFX_RAND_BLINK        0x0C
#define EVT_LIGHTFX_PHOTON_TORP       0x0D
#define EVT_LIGHTFX_LASER_PULSE       0x0E
#define EVT_LIGHTFX_ENGINE_GLOW       0x0F
#define EVT_LIGHTFX_LIGHTHOUSE        0x10
#define EVT_LIGHTFX_BROKEN_LIGHT      0x11
#define EVT_LIGHTFX_STATUS_IND        0x12
#define EVT_LIGHTFX_SOUND_MOD         0x13
#define EVT_LIGHTFX_MOTOR_MOD         0x14
                                      
#define EVT_COMBOFX_NONE              0x00
#define EVT_COMBOFX_LIN_SWEEP         0x01
#define EVT_COMBOFX_BARGRAPH          0x02
#define EVT_COMBOFX_KNIGHTRIDER       0x03
#define EVT_COMBOFX_EMCY_TWSONIC      0x04
#define EVT_COMBOFX_EMCY_WHELEN       0x05
#define EVT_COMBOFX_TIMES_SQ          0x06
#define EVT_COMBOFX_NOISE             0x07
#define EVT_COMBOFX_TWINKLE_STAR      0x08
#define EVT_COMBOFX_TRAFFIC_SIG       0x09
#define EVT_COMBOFX_SOUND_BAR         0x0A
#define EVT_COMBOFX_ALT_FLASH         0x0B
#define EVT_COMBOFX_LAVA_LAMP         0x0C
#define EVT_COMBOFX_LASER_CANNON      0x0D

/*******************************************************************************
 Byte 5 - LIGHT_OUTPUT_MASK
*******************************************************************************/
#define EVT_LIGHT_OUTPUT_1            0x01
#define EVT_LIGHT_OUTPUT_2            0x02
#define EVT_LIGHT_OUTPUT_3            0x04
#define EVT_LIGHT_OUTPUT_4            0x08
#define EVT_LIGHT_OUTPUT_5            0x10
#define EVT_LIGHT_OUTPUT_6            0x20
#define EVT_LIGHT_OUTPUT_7            0x40
#define EVT_LIGHT_OUTPUT_8            0x80

/*******************************************************************************
 Byte 6 - LIGHT_PF_OUTPUT_MASK
*******************************************************************************/
#define EVT_LIGHT_PF_OUTPUT_A         0x01
#define EVT_LIGHT_PF_OUTPUT_B         0x02
#define EVT_LIGHT_PF_OUTPUT_C         0x04
#define EVT_LIGHT_PF_OUTPUT_D         0x08

/*******************************************************************************
 Byte  7 - LIGHT_PARAM1
 Byte  8 - LIGHT_PARAM2
 Byte  9 - LIGHT_PARAM3
 Byte 10 - LIGHT_PARAM4
 Byte 11 - LIGHT_PARAM5
*******************************************************************************/

// DIR_OPTION Parameter
#define EVT_DIR_OPTION_NONE           0x00
#define EVT_DIR_OPTION_MOTORA_FWD     0x01
#define EVT_DIR_OPTION_MOTORA_REV     0x02
#define EVT_DIR_OPTION_MOTORB_FWD     0x03
#define EVT_DIR_OPTION_MOTORB_REV     0x04
#define EVT_DIR_OPTION_MOTORC_FWD     0x05
#define EVT_DIR_OPTION_MOTORC_REV     0x06
#define EVT_DIR_OPTION_MOTORD_FWD     0x07
#define EVT_DIR_OPTION_MOTORD_REV     0x08
#define EVT_DIR_OPTION_ODD_MOTORA_FWD 0x09
#define EVT_DIR_OPTION_ODD_MOTORB_FWD 0x0A
#define EVT_DIR_OPTION_ODD_MOTORC_FWD 0x0B
#define EVT_DIR_OPTION_ODD_MOTORD_FWD 0x0C
#define EVT_DIR_OPTION_ODD_MOTORA_REV 0x0D
#define EVT_DIR_OPTION_ODD_MOTORB_REV 0x0E 
#define EVT_DIR_OPTION_ODD_MOTORC_REV 0x0F
#define EVT_DIR_OPTION_ODD_MOTORD_REV 0x10 
  
// FADE TIME Parameter
#define EVT_FADE_TIME_NONE            0x0
#define EVT_FADE_TIME_50MS            0x1
#define EVT_FADE_TIME_100MS           0x2
#define EVT_FADE_TIME_200MS           0x3
#define EVT_FADE_TIME_400MS           0x4
#define EVT_FADE_TIME_500MS           0x5
#define EVT_FADE_TIME_600MS           0x6
#define EVT_FADE_TIME_800MS           0x7
#define EVT_FADE_TIME_1S              0x8
#define EVT_FADE_TIME_1_5S            0x9
#define EVT_FADE_TIME_2S              0xA
#define EVT_FADE_TIME_2_5S            0xB
#define EVT_FADE_TIME_3S              0xC
#define EVT_FADE_TIME_4S              0xD
#define EVT_FADE_TIME_5S              0xE
#define EVT_FADE_TIME_10S             0xF
#define EVT_FADE_TIME_MAX             0x10
#define EVT_FADE_TIME_MIN             0x1F

// FADE FACTOR Parameter
#define EVT_FADE_FACTOR_NONE          0x0
#define EVT_FADE_FACTOR_1             0x1
#define EVT_FADE_FACTOR_5             0x2
#define EVT_FADE_FACTOR_10            0x3
#define EVT_FADE_FACTOR_15            0x4
#define EVT_FADE_FACTOR_20            0x5
#define EVT_FADE_FACTOR_25            0x6
#define EVT_FADE_FACTOR_30            0x7
#define EVT_FADE_FACTOR_40            0x8
#define EVT_FADE_FACTOR_50            0x9
#define EVT_FADE_FACTOR_75            0xA
#define EVT_FADE_FACTOR_90            0xB
#define EVT_FADE_FACTOR_100           0xC
#define EVT_FADE_FACTOR_150           0xD
#define EVT_FADE_FACTOR_200           0xE
#define EVT_FADE_FACTOR_400           0xF
#define EVT_FADE_FACTOR_MAX           0x10
#define EVT_FADE_FACTOR_MIN           0x1F

// PERIOD Parameter
#define EVT_PERIOD_100MS              0x0
#define EVT_PERIOD_250MS              0x1
#define EVT_PERIOD_500MS              0x2
#define EVT_PERIOD_750MS              0x3
#define EVT_PERIOD_1S                 0x4
#define EVT_PERIOD_1_25S              0x5
#define EVT_PERIOD_1_5S               0x6
#define EVT_PERIOD_1_75S              0x7
#define EVT_PERIOD_2S                 0x8
#define EVT_PERIOD_2_5S               0x9
#define EVT_PERIOD_3S                 0xA
#define EVT_PERIOD_4S                 0xB
#define EVT_PERIOD_5S                 0xC
#define EVT_PERIOD_8S                 0xD
#define EVT_PERIOD_10S                0xE
#define EVT_PERIOD_20S                0xF
#define EVT_PERIOD_MAX                0x10
                                      
// PERIOD2 Parameter                  
#define EVT_PERIOD2_50MS              0x0
#define EVT_PERIOD2_100MS             0x1
#define EVT_PERIOD2_200MS             0x2
#define EVT_PERIOD2_300MS             0x3
#define EVT_PERIOD2_400MS             0x4
#define EVT_PERIOD2_500MS             0x5
#define EVT_PERIOD2_600MS             0x6
#define EVT_PERIOD2_700MS             0x7
#define EVT_PERIOD2_800MS             0x8
#define EVT_PERIOD2_900MS             0x9
#define EVT_PERIOD2_1S                0xA
#define EVT_PERIOD2_1_25S             0xB
#define EVT_PERIOD2_1_5S              0xC
#define EVT_PERIOD2_1_75S             0xD
#define EVT_PERIOD2_2S                0xE
#define EVT_PERIOD2_3S                0xF
#define EVT_PERIOD2_MAX               0x10
  
#define PFX_PERIOD_COUNT_MAX     EVT_PERIOD_MAX + EVT_PERIOD2_MAX 
  
// DUTY_CYCLE Parameter
#define EVT_DUTYCY_1                  0x0
#define EVT_DUTYCY_2                  0x1
#define EVT_DUTYCY_5                  0x2
#define EVT_DUTYCY_10                 0x3
#define EVT_DUTYCY_15                 0x4
#define EVT_DUTYCY_20                 0x5
#define EVT_DUTYCY_25                 0x6
#define EVT_DUTYCY_30                 0x7
#define EVT_DUTYCY_40                 0x8
#define EVT_DUTYCY_50                 0x9
#define EVT_DUTYCY_60                 0xA
#define EVT_DUTYCY_70                 0xB
#define EVT_DUTYCY_75                 0xC
#define EVT_DUTYCY_80                 0xD
#define EVT_DUTYCY_85                 0xE
#define EVT_DUTYCY_90                 0xF
#define EVT_DUTYCY_95                 0x10
#define EVT_DUTYCY_98                 0x11
#define EVT_DUTYCY_99                 0x12
#define EVT_DUTYCY_MAX                0x13
                                     
// BURST_COUNT Parameter             
#define EVT_BURST_COUNT_1             0x0
#define EVT_BURST_COUNT_2             0x1
#define EVT_BURST_COUNT_3             0x2
#define EVT_BURST_COUNT_4             0x3
#define EVT_BURST_COUNT_MAX           0x4
                                     
// SIZE Parameter                    
#define EVT_SIZE_8_LIGHTS             0x0
#define EVT_SIZE_7_LIGHTS             0x1
#define EVT_SIZE_6_LIGHTS             0x2
#define EVT_SIZE_5_LIGHTS             0x3
#define EVT_SIZE_4_LIGHTS             0x4
  
// BAR_STYLE parameter for sound bar
#define EVT_BAR_STYLE_NONE            0x0
#define EVT_BAR_STYLE_LEFTRIGHT       0x1
#define EVT_BAR_STYLE_RIGHTLEFT       0x2
#define EVT_BAR_STYLE_INOUT           0x3
#define EVT_BAR_STYLE_OUTIN           0x4
  
// SWEEP_STYLE parameter for bargraph and linear sweep
#define EVT_SWEEP_STYLE_LEFTRIGHT     0x0
#define EVT_SWEEP_STYLE_RIGHTLEFT     0x1
                                      
// TWINSONIC_STYLE parameter          
#define EVT_TWINSONIC_SINGLE          0x0
#define EVT_TWINSONIC_DUAL            0x1
#define EVT_TWINSONIC_AERO            0x2
#define EVT_TWINSONIC_COMBO           0x3
  
// WHELEN_STYLE parameter for emergency vehicle lightbars
#define EVT_WHELEN_SIGALERT           0x0
#define EVT_WHELEN_SIGALERT_STDY      0x1
#define EVT_WHELEN_COMET_FLASH        0x2
#define EVT_WHELEN_ACT_FLASH50        0x3
#define EVT_WHELEN_ACT_FLASH150       0x4
#define EVT_WHELEN_MODU_FLASH         0x5
#define EVT_WHELEN_SINGLE_FLASH       0x6
#define EVT_WHELEN_DOUBLE_FLASH       0x7
#define EVT_WHELEN_TRIPLE_FLASH       0x8
#define EVT_WHELEN_WARNING            0x9
#define EVT_WHELEN_RANDOM             0xA

// SEQ parameter for emergency flashers
#define EVT_SEQ_SOLID                 0x0
#define EVT_SEQ_LEFTRIGHT             0x1
#define EVT_SEQ_INOUT                 0x2

// FLASH_RATE parameter for emergency flashers
#define EVT_FLASH_RATE_SLOW           0x0
#define EVT_FLASH_RATE_MED            0x1
#define EVT_FLASH_RATE_FAST           0x2
#define EVT_FLASH_RATE_VERYFAST       0x3

// TRAFFIC_STYLE parameter for traffic light sequences
#define EVT_TRAFFIC_STD               0x0
#define EVT_TRAFFIC_STD_FLGRN         0x1
#define EVT_TRAFFIC_EUR               0x2
#define EVT_TRAFFIC_NS_FLRED          0x3
#define EVT_TRAFFIC_STD_PED           0x4
#define EVT_TRAFFIC_STD_FLGRN_PED     0x5
#define EVT_TRAFFIC_EUR_PED           0x6
#define EVT_TRAFFIC_EW_FLRED          0x7
#define EVT_TRAFFIC_EUR2              0x8
#define EVT_TRAFFIC_EUR2_PED          0x9
  
// SEQ_TIME parameter for traffic light sequence length
#define EVT_SEQ_TIME_SLOW             0x0
#define EVT_SEQ_TIME_MED              0x1
#define EVT_SEQ_TIME_FAST             0x2
#define EVT_SEQ_TIME_VERYFAST         0x3
  
// FAULT_RATE parameter for broken light
#define EVT_FAULT_RATE_RARE           0x0  
#define EVT_FAULT_RATE_OCCASIONAL     0x1  
#define EVT_FAULT_RATE_OFTEN          0x2  
#define EVT_FAULT_RATE_VERYOFTEN      0x3
#define EVT_FAULT_RATE_ALWAYS         0x4

// FAULT_INTENSITY parameter for broken light
#define EVT_FAULT_INT_SUBTLE          0x0
#define EVT_FAULT_INT_MODERATE        0x1
#define EVT_FAULT_INT_SERVERE         0x2
#define EVT_FAULT_INT_MAX             0x3
#define EVT_FAULT_INT_FLICKER_ON      0x4

// SOURCE1 parameter for status indicator
#define EVT_SOURCE1_USB_CONN          0x01
#define EVT_SOURCE1_USB_ACTIVITY      0x02
#define EVT_SOURCE1_IR_ACTIVITY       0x04
#define EVT_SOURCE1_IR_LOCKOUT        0x08
#define EVT_SOURCE1_AUDIO_PLAY        0x10
#define EVT_SOURCE1_BLE_CONN          0x20
#define EVT_SOURCE1_BLE_ACTIVITY      0x40
#define EVT_SOURCE1_FS_ACCESS         0x80

// SOURCE2 parameter for status indicator
#define EVT_SOURCE2_MOTORA_FWD        0x01
#define EVT_SOURCE2_MOTORA_REV        0x02
#define EVT_SOURCE2_MOTORB_FWD        0x04
#define EVT_SOURCE2_MOTORB_REV        0x08
#define EVT_SOURCE2_MOTORC_FWD        0x10
#define EVT_SOURCE2_MOTORC_REV        0x20
#define EVT_SOURCE2_MOTORD_FWD        0x40
#define EVT_SOURCE2_MOTORD_REV        0x80
#define EVT_SOURCE2_MOTORA_MASK       0xFC
#define EVT_SOURCE2_MOTORB_MASK       0xF3
#define EVT_SOURCE2_MOTORC_MASK       0xCF
#define EVT_SOURCE2_MOTORD_MASK       0x3F
  
// INVERT parameter for status indicator
#define EVT_INVERT_NORMAL             0x00
                                      
// TRANSITION parameter               
#define EVT_TRANSITION_TOGGLE         0x00
#define EVT_TRANSITION_ON             0x01
#define EVT_TRANSITION_OFF            0x02
#define EVT_TRANSITION_DURATION       0x03
#define EVT_TRANSITION_MASK           0x03

/*******************************************************************************
 Byte 12 - SOUND_FX_ID
*******************************************************************************/
#define EVT_SOUND_NONE                0x0
#define EVT_SOUND_INC_VOL             0x1
#define EVT_SOUND_DEC_VOL             0x2
#define EVT_SOUND_SET_VOL             0x3
#define EVT_SOUND_PLAY_ONCE           0x4
#define EVT_SOUND_PLAY_CONT           0x5
#define EVT_SOUND_PLAY_NTIMES         0x6
#define EVT_SOUND_PLAY_DUR            0x7
#define EVT_SOUND_PLAY_PITCH          0x8
#define EVT_SOUND_PLAY_GATED          0x9
#define EVT_SOUND_PLAY_AM             0xA
#define EVT_SOUND_STOP                0xB
#define EVT_SOUND_PLAY_IDX_MOTOR      0xC
#define EVT_SOUND_PLAY_RAND           0xD
#define EVT_SOUND_PLAY_PAUSE_FLAG     0x10

/*******************************************************************************
 Byte 14 - SOUND_PARAM1
 Byte 15 - SOUND_PARAM2
*******************************************************************************/

// DURATION Parameter
#define EVT_SOUND_DUR_500MS           0x0
#define EVT_SOUND_DUR_1S              0x1
#define EVT_SOUND_DUR_1_5S            0x2
#define EVT_SOUND_DUR_2S              0x3
#define EVT_SOUND_DUR_3S              0x4
#define EVT_SOUND_DUR_4S              0x5
#define EVT_SOUND_DUR_5S              0x6
#define EVT_SOUND_DUR_10S             0x7
#define EVT_SOUND_DUR_15S             0x8
#define EVT_SOUND_DUR_20S             0x9
#define EVT_SOUND_DUR_30S             0xA
#define EVT_SOUND_DUR_45S             0xB
#define EVT_SOUND_DUR_60S             0xC
#define EVT_SOUND_DUR_90S             0xD
#define EVT_SOUND_DUR_2M              0xE
#define EVT_SOUND_DUR_5M              0xF
                                      
#define EVT_SOUND_TOGGLE              0x0
#define EVT_SOUND_RESTART             0x1

// MOTOR_OUTPUT parameter for SOUND_PLAY_IDX_MOTOR sound Fx in SOUND_PARAM1
#define EVT_SOUND_IDX_MOTOR_MASK      0x03
#define EVT_SOUND_IDX_MOTOR_CURR_SPD  0x04
#define EVT_SOUND_IDX_MOTOR_TGT_SPD   0x00
  
// IDX_OPTIONS for SOUND_PLAY_IDX_MOTOR sound Fx in SOUND_PARAM2
#define EVT_SOUND_IDX_VOL_MOD_OFF     0x0
#define EVT_SOUND_IDX_VOL_MOD_LIGHT   0x1
#define EVT_SOUND_IDX_VOL_MOD_MED     0x2
#define EVT_SOUND_IDX_VOL_MOD_HEAVY   0x3
#define EVT_SOUND_IDX_VOL_MOD_MASK    0x3
#define EVT_SOUND_IDX_PLAY_STARTUP    0x4
#define EVT_SOUND_IDX_PLAY_START_OVR  0x8
  
// PROBABILITY parameter for random sounds in SOUND_PARAM1
#define EVT_SOUND_RAND_RARE           0x0  
#define EVT_SOUND_RAND_OCCASIONAL     0x1  
#define EVT_SOUND_RAND_OFTEN          0x2  
#define EVT_SOUND_RAND_VERYOFTEN      0x3
  
#define PFX_SOUND_IDX_MAX_NOTCHES     8
// SOUND_PLAY_IDX_MOTOR reserved file IDs for motor sound states
#define PFX_SOUND_IDX_STARTUP         0xE7
#define PFX_SOUND_IDX_SHUTDOWN        0xE8
#define PFX_SOUND_IDX_NOTCH1_LOOP     0xE9
#define PFX_SOUND_IDX_NOTCH2_LOOP     0xEA
#define PFX_SOUND_IDX_NOTCH3_LOOP     0xEB
#define PFX_SOUND_IDX_NOTCH4_LOOP     0xEC
#define PFX_SOUND_IDX_NOTCH5_LOOP     0xED
#define PFX_SOUND_IDX_NOTCH6_LOOP     0xEE
#define PFX_SOUND_IDX_NOTCH7_LOOP     0xEF
#define PFX_SOUND_IDX_NOTCH8_LOOP     0xF0
#define PFX_SOUND_IDX_ACCEL1          0xF1
#define PFX_SOUND_IDX_ACCEL2          0xF2
#define PFX_SOUND_IDX_ACCEL3          0xF3
#define PFX_SOUND_IDX_ACCEL4          0xF4
#define PFX_SOUND_IDX_ACCEL5          0xF5
#define PFX_SOUND_IDX_ACCEL6          0xF6
#define PFX_SOUND_IDX_ACCEL7          0xF7
#define PFX_SOUND_IDX_DECEL1          0xF8
#define PFX_SOUND_IDX_DECEL2          0xF9
#define PFX_SOUND_IDX_DECEL3          0xFA
#define PFX_SOUND_IDX_DECEL4          0xFB
#define PFX_SOUND_IDX_DECEL5          0xFC
#define PFX_SOUND_IDX_DECEL6          0xFD
#define PFX_SOUND_IDX_DECEL7          0xFE
  
/*******************************************************************************
 *******************************************************************************

 Interface Command Byte Definitions

*******************************************************************************
*******************************************************************************/

#define PFX_BLE_CMD_PRE_DELIMITER        0x5B
#define PFX_BLE_CMD_PRE_DELIMITER_LEN    3
#define PFX_BLE_CMD_POST_DELIMITER       0x5D
#define PFX_BLE_CMD_POST_DELIMITER_LEN   3

/*******************************************************************************
 Operation and Configuration Commands
*******************************************************************************/
#define PFX_USB_CMD_GET_ICD_REV          0x08
#define PFX_USB_CMD_GET_STATUS           0x01
#define PFX_USB_CMD_SET_FACTORY_DEFAULTS 0x02
#define PFX_USB_CMD_GET_CONFIG           0x03
#define PFX_USB_CMD_SET_CONFIG           0x04
#define PFX_USB_CMD_VERIFY_CONFIG        0x05 // deprecated as of v.3.36
#define PFX_USB_CMD_GET_CURRENT_STATE    0x06
#define PFX_USB_CMD_GET_NAME             0x07
#define PFX_USB_CMD_SET_NAME             0x09
// New synonymous defines without interface specific namespace
#define PFX_CMD_GET_ICD_REV              0x08
#define PFX_CMD_GET_STATUS               0x01
#define PFX_CMD_SET_FACTORY_DEFAULTS     0x02
#define PFX_CMD_GET_CONFIG               0x03
#define PFX_CMD_SET_CONFIG               0x04
#define PFX_CMD_VERIFY_CONFIG            0x05 // deprecated as of v.3.36
#define PFX_CMD_GET_CURRENT_STATE        0x06
#define PFX_CMD_GET_NAME                 0x07
#define PFX_CMD_SET_NAME                 0x09

/*******************************************************************************
 Event/Action LUT Commands
*******************************************************************************/
#define PFX_USB_CMD_VERIFY_EVENT_LUT     0x10 // deprecated as of v.3.36
#define PFX_USB_CMD_GET_EVENT_ACTION     0x11                                
#define PFX_USB_CMD_SET_EVENT_ACTION     0x12
#define PFX_USB_CMD_TEST_ACTION          0x13
#define PFX_USB_CMD_GET_LAST_IR_MSG      0x14 // deprecated as of v.3.36
// New synonymous defines without interface specific namespace
#define PFX_CMD_VERIFY_EVENT_LUT         0x10 // deprecated as of v.3.36
#define PFX_CMD_GET_EVENT_ACTION         0x11                                
#define PFX_CMD_SET_EVENT_ACTION         0x12
#define PFX_CMD_TEST_ACTION              0x13
#define PFX_CMD_GET_LAST_IR_MSG          0x14 // deprecated as of v.3.36
#define PFX_CMD_SEND_EVENT               0x15

/*******************************************************************************
 Audio Commands
*******************************************************************************/
#define PFX_USB_CMD_INC_VOLUME           0x20
#define PFX_USB_CMD_DEC_VOLUME           0x21
#define PFX_USB_CMD_GET_AUDIO_LUT_ENTRY  0x22 // deprecated
#define PFX_USB_CMD_GET_AUDIO_CAPACITY   0x23 // deprecated
#define PFX_USB_CMD_ERASE_AUDIO_LUT      0x24 // deprecated
#define PFX_USB_CMD_ADD_AUDIO_FILE       0x25 // deprecated
#define PFX_USB_CMD_ADD_AUDIO_DATA       0x26 // deprecated
#define PFX_USB_CMD_ADD_AUDIO_DONE       0x27 // deprecated
#define PFX_USB_CMD_GET_AUDIO_FILE       0x28 // deprecated
#define PFX_USB_CMD_GET_AUDIO_DATA       0x29 // deprecated
#define PFX_USB_CMD_SET_AUDIO_EQ         0x2A
// New synonymous defines without interface specific namespace
#define PFX_CMD_INC_VOLUME               0x20
#define PFX_CMD_DEC_VOLUME               0x21
#define PFX_CMD_SET_AUDIO_EQ             0x2A

/*******************************************************************************
 File Commands
*******************************************************************************/
#define PFX_USB_CMD_FILE_OPEN            0x40
#define PFX_USB_CMD_FILE_CLOSE           0x41
#define PFX_USB_CMD_FILE_READ            0x42
#define PFX_USB_CMD_FILE_WRITE           0x43
#define PFX_USB_CMD_FILE_SEEK            0x44
#define PFX_USB_CMD_FILE_DIR             0x45
#define PFX_USB_CMD_FILE_REMOVE          0x46
#define PFX_USB_CMD_FILE_FORMAT_FS       0x47
#define PFX_USB_CMD_FILE_GET_FS_STATE    0x48
#define PFX_USB_CMD_GET_FLASH_SECTORMAP  0x49
#define PFX_USB_CMD_GET_FLASH_DIR_ENTRY  0x4A
// New synonymous defines without interface specific namespace
#define PFX_CMD_FILE_OPEN                0x40
#define PFX_CMD_FILE_CLOSE               0x41
#define PFX_CMD_FILE_READ                0x42
#define PFX_CMD_FILE_WRITE               0x43
#define PFX_CMD_FILE_SEEK                0x44
#define PFX_CMD_FILE_DIR                 0x45
#define PFX_CMD_FILE_REMOVE              0x46
#define PFX_CMD_FILE_FORMAT_FS           0x47
#define PFX_CMD_FILE_GET_FS_STATE        0x48
#define PFX_CMD_GET_FLASH_SECTORMAP      0x49
#define PFX_CMD_GET_FLASH_DIR_ENTRY      0x4A

/*******************************************************************************
 Bluetooth Interface Commands
*******************************************************************************/
#define PFX_USB_CMD_GET_BT_STATUS        0x50
#define PFX_USB_CMD_SET_BT_POWER         0x51
#define PFX_USB_CMD_SEND_BT_UART         0x52
#define PFX_USB_CMD_RECEIVE_BT_UART      0x53
// New synonymous defines without interface specific namespace
#define PFX_CMD_GET_BT_STATUS            0x50
#define PFX_CMD_SET_BT_POWER             0x51
#define PFX_CMD_SEND_BT_UART             0x52
#define PFX_CMD_RECEIVE_BT_UART          0x53

/*******************************************************************************
 Notifications
*******************************************************************************/
#define PFX_CMD_SET_NOTIFICATIONS        0x60
#define PFX_MSG_NOTIFICATION             0x61

/*******************************************************************************
 Service Commands
*******************************************************************************/
#define PFX_USB_CMD_LOAD_FIRMWARE_FILE   0x30
#define PFX_USB_CMD_LOAD_FIRMWARE_DATA   0x31
#define PFX_USB_CMD_LOAD_FIRMWARE_DONE   0x32
#define PFX_USB_CMD_READ_NVRAM           0x33
#define PFX_USB_CMD_READ_BOOTCONFIG      0x34
#define PFX_USB_CMD_ERASE_NVRAM          0x35
#define PFX_USB_CMD_COMPUTE_CRC32        0x36
#define PFX_USB_CMD_REBOOT               0x37
#define PFX_USB_CMD_WRITE_SN             0x38
#define PFX_USB_CMD_READ_SN              0x39
// New synonymous defines without interface specific namespace
#define PFX_CMD_LOAD_FIRMWARE_FILE       0x30
#define PFX_CMD_LOAD_FIRMWARE_DATA       0x31
#define PFX_CMD_LOAD_FIRMWARE_DONE       0x32
#define PFX_CMD_READ_NVRAM               0x33
#define PFX_CMD_READ_BOOTCONFIG          0x34
#define PFX_CMD_ERASE_NVRAM              0x35
#define PFX_CMD_COMPUTE_CRC32            0x36
#define PFX_CMD_REBOOT                   0x37
#define PFX_CMD_WRITE_SN                 0x38
#define PFX_CMD_READ_SN                  0x39
  
/*******************************************************************************
 Low Level Test/Debug Commands
*******************************************************************************/
#define PFX_USB_CMD_STATUS_LED           0x70
#define PFX_USB_CMD_DIAG_LED             0x71  // deprecated
#define PFX_USB_CMD_WRITE_SPI            0x72
#define PFX_USB_CMD_READ_SPI             0x73
#define PFX_USB_CMD_WRITE_I2C            0x74
#define PFX_USB_CMD_READ_I2C             0x75
#define PFX_USB_CMD_READ_FLASH           0x76
#define PFX_USB_CMD_GET_IRRX_STATUS      0x77
// New synonymous defines without interface specific namespace
#define PFX_CMD_STATUS_LED               0x70
#define PFX_CMD_WRITE_SPI                0x72
#define PFX_CMD_READ_SPI                 0x73
#define PFX_CMD_WRITE_I2C                0x74
#define PFX_CMD_READ_I2C                 0x75
#define PFX_CMD_READ_FLASH               0x76
#define PFX_CMD_GET_IRRX_STATUS          0x77
  
/*******************************************************************************
 *******************************************************************************

 Interface convenient constant defines and codes

*******************************************************************************
*******************************************************************************/

//
// Security bytes to prevent inadvertent critical actions
//
#define PFX_RESET_BYTE0                  0xAA
#define PFX_RESET_BYTE1                  0x55
#define PFX_RESET_BYTE2                  0xDE
#define PFX_RESET_BYTE3                  0xAD
#define PFX_RESET_BYTE4                  0xBE
#define PFX_RESET_BYTE5                  0xEF
#define PFX_RESET_BYTE6                  0x02
                                        
#define PFX_STATUS_BYTE0                 0xA5
#define PFX_STATUS_BYTE1                 0x5A
#define PFX_STATUS_BYTE2                 0x6E
#define PFX_STATUS_BYTE3                 0x40
#define PFX_STATUS_BYTE4                 0x54
#define PFX_STATUS_BYTE5                 0xA4
#define PFX_STATUS_BYTE6                 0xE5

#define PFX_GET_ICD_BYTE0                0x60
#define PFX_GET_ICD_BYTE1                0x0D
#define PFX_GET_ICD_BYTE2                0x01
  
#define PFX_REBOOT_BYTE0                 0x5A
#define PFX_REBOOT_BYTE1                 0xA5
#define PFX_REBOOT_BYTE2                 0xD0
#define PFX_REBOOT_BYTE3                 0xBE
#define PFX_REBOOT_BYTE4                 0xB0
#define PFX_REBOOT_BYTE5                 0x04
#define PFX_REBOOT_BYTE6                 0x77
                                       
#define PFX_ERASE_NVRAM_BYTE0            0xEE
#define PFX_ERASE_NVRAM_BYTE1            0x4A
#define PFX_ERASE_NVRAM_BYTE2            0x5E
#define PFX_ERASE_NVRAM_BYTE3            0xEE
#define PFX_ERASE_NVRAM_BYTE4            0x4A
#define PFX_ERASE_NVRAM_BYTE5            0x5E
#define PFX_ERASE_NVRAM_BYTE6            0x35

#define PFX_WRITE_SN_BYTE0               0x5E
#define PFX_WRITE_SN_BYTE1               0x45
#define PFX_WRITE_SN_BYTE2               0x5E
#define PFX_WRITE_SN_BYTE3               0x41
#define PFX_WRITE_SN_BYTE4               0xA1
#define PFX_WRITE_SN_BYTE5               0x10
#define PFX_WRITE_SN_BYTE6               0x70

#define PFX_FORMAT_BYTE0                 0xEA
#define PFX_FORMAT_BYTE1                 0x5E
#define PFX_FORMAT_BYTE2                 0x88

// 
// File System specific defines
//
#define PFX_FILE_ACC_READ                0x01
#define PFX_FILE_ACC_WRITE               0x02
#define PFX_FILE_ACC_CREATE              0x04

#define PFX_DIR_REQ_GET_FILE_COUNT       0x00
#define PFX_DIR_REQ_GET_FREE_SPACE       0x01
#define PFX_DIR_REQ_GET_DIR_ENTRY_IDX    0x02
#define PFX_DIR_REQ_GET_DIR_ENTRY_ID     0x03
#define PFX_DIR_REQ_ADD_AUDIO_FILE_ID    0x04
#define PFX_DIR_REQ_RENAME_FILE_ID       0x05
#define PFX_DIR_REQ_SET_ATTR_ID          0x06
#define PFX_DIR_REQ_SET_USER_DATA1_ID    0x07
#define PFX_DIR_REQ_SET_USER_DATA2_ID    0x08
#define PFX_DIR_REQ_COMPUTE_CRC32_ID     0x09
#define PFX_DIR_REQ_SET_ATTR_MASKED_ID   0x0A
  
#define PFX_FILE_FMT_MASK                0xFF00
#define PFX_FILE_FMT_WAV                 0x0000
#define PFX_FILE_FMT_FLAC                0x0100
#define PFX_FILE_FMT_MP3                 0x0200
#define PFX_FILE_FMT_OGG                 0x0300
#define PFX_FILE_FMT_AU                  0x0400
#define PFX_FILE_FMT_GSM                 0x0500
#define PFX_FILE_FMT_TXT                 0x1000
#define PFX_FILE_FMT_HEX                 0x1100
#define PFX_FILE_FMT_ZIP                 0x2000
#define PFX_FILE_FMT_GZ                  0x2100
#define PFX_FILE_FMT_IMG                 0x5000

#define PFX_WAV_ATTR_SAMPLE_RATE_MASK    0x0001  
#define PFX_WAV_ATTR_SAMPLE_RATE_22K     0x0000  
#define PFX_WAV_ATTR_SAMPLE_RATE_11K     0x0001  
#define PFX_WAV_ATTR_QUANTIZATION_MASK   0x0002  
#define PFX_WAV_ATTR_QUANTIZATION_16     0x0000  
#define PFX_WAV_ATTR_QUANTIZATION_8      0x0002  

#define PFX_SOUND_ATTR_MOTOR_MASK        0x007C
#define PFX_SOUND_ATTR_MOTOR_LOOP_MASK   0x0060
#define PFX_SOUND_ATTR_MOTOR_LOOP_NOTCH  0x0020
#define PFX_SOUND_ATTR_MOTOR_LOOP_ACCEL  0x0040
#define PFX_SOUND_ATTR_MOTOR_LOOP_DECEL  0x0060
#define PFX_SOUND_ATTR_MOTOR_LOOP_IDX    0x001C
#define PFX_SOUND_ATTR_MOTOR_LOOP_IDX_SH 2
#define PFX_SOUND_ATTR_MOTOR_LOOP_N1     0x0020
#define PFX_SOUND_ATTR_MOTOR_LOOP_N2     0x0024
#define PFX_SOUND_ATTR_MOTOR_LOOP_N3     0x0028
#define PFX_SOUND_ATTR_MOTOR_LOOP_N4     0x002C
#define PFX_SOUND_ATTR_MOTOR_LOOP_N5     0x0030
#define PFX_SOUND_ATTR_MOTOR_LOOP_N6     0x0034
#define PFX_SOUND_ATTR_MOTOR_LOOP_N7     0x0038
#define PFX_SOUND_ATTR_MOTOR_LOOP_N8     0x003C
#define PFX_SOUND_ATTR_MOTOR_ACCEL12     0x0040
#define PFX_SOUND_ATTR_MOTOR_ACCEL23     0x0044
#define PFX_SOUND_ATTR_MOTOR_ACCEL34     0x0048
#define PFX_SOUND_ATTR_MOTOR_ACCEL45     0x004C
#define PFX_SOUND_ATTR_MOTOR_ACCEL56     0x0050
#define PFX_SOUND_ATTR_MOTOR_ACCEL67     0x0054
#define PFX_SOUND_ATTR_MOTOR_ACCEL78     0x0058
#define PFX_SOUND_ATTR_MOTOR_STARTUP     0x005C
#define PFX_SOUND_ATTR_MOTOR_DECEL21     0x0060
#define PFX_SOUND_ATTR_MOTOR_DECEL32     0x0064
#define PFX_SOUND_ATTR_MOTOR_DECEL43     0x0068
#define PFX_SOUND_ATTR_MOTOR_DECEL54     0x006C
#define PFX_SOUND_ATTR_MOTOR_DECEL65     0x0070
#define PFX_SOUND_ATTR_MOTOR_DECEL76     0x0074
#define PFX_SOUND_ATTR_MOTOR_DECEL87     0x0078
#define PFX_SOUND_ATTR_MOTOR_SHUTDOWN    0x007C
  
//
// Notification flags
//
#define PFX_NOTIFICATION_AUDIO_PLAY_DONE  0x01
#define PFX_NOTIFICATION_AUDIO_PLAY       0x02
#define PFX_NOTIFICATION_MOTORA_CURR_SPD  0x04
#define PFX_NOTIFICATION_MOTORA_STOP      0x08
#define PFX_NOTIFICATION_MOTORB_CURR_SPD  0x10
#define PFX_NOTIFICATION_MOTORB_STOP      0x20
#define PFX_NOTIFICATION_TO_USB           0x80
#define PFX_NOTIFICATION_TO_BLE           0x40
  
//
// Status message response codes
//  
#define PFX_STATUS_NORMAL                0x00
#define PFX_STATUS_NORMAL_PENDING        0x33
#define PFX_STATUS_SERVICE               0x55
#define PFX_STATUS_SERVICE_PENDING       0x53
#define PFX_STATUS_SERVICE_BUSY          0x5B
  
//
// Error response codes
//  
#define PFX_ERR_NONE                     0x00
#define PFX_ERR_VERIFY_PASS              0x00
#define PFX_ERR_VERIFY_FAIL              0x01
#define PFX_ERR_TRANSFER_REQUEST_OK      0x00
#define PFX_ERR_TRANSFER_FILE_EXISTS     0x02
#define PFX_ERR_TRANSFER_TOO_BIG         0x03
#define PFX_ERR_TRANSFER_INVALID         0x04
#define PFX_ERR_TRANSFER_FILE_NOT_FOUND  0x05
#define PFX_ERR_TRANSFER_ERROR           0xFF
#define PFX_ERR_TRANSFER_CRC_MISMATCH    0x06
#define PFX_ERR_TRANSFER_BUSY_WAIT       0x07
#define PFX_ERR_TRANSFER_LUT_FULL        0x08
#define PFX_ERR_TRANSFER_COMPLETE        0x09
#define PFX_ERR_UPGRADE_FAIL             0x80
  
#define PFX_ERR_FILE_SYSTEM_ERR          0xF0
#define PFX_ERR_FILE_INVALID             0xF1
#define PFX_ERR_FILE_OUT_OF_RANGE        0xF2
#define PFX_ERR_FILE_READ_ONLY           0xF3
#define PFX_ERR_FILE_TOO_BIG             0xF4
#define PFX_ERR_FILE_NOT_FOUND           0xF5
#define PFX_ERR_FILE_NOT_UNIQUE          0xF6
#define PFX_ERR_FILE_LOCKED_BUSY         0xF7
#define PFX_ERR_FILE_SYSTEM_FULL         0xF8
#define PFX_ERR_FILE_SYSTEM_TIMEOUT      0xF9
#define PFX_ERR_FILE_INVALID_ADDRESS     0xFA
#define PFX_ERR_FILE_NEXT_SECTOR         0xFB
#define PFX_ERR_FILE_ACCESS_DENIED       0xFC
#define PFX_ERR_FILE_EOF                 0xFF
  
#define PFX_ERR_BLE_FAULT                0x0B
#define PFX_ERR_SPKR_SHORTCIR_FAULT      0x04    
#define PFX_ERR_DAC_OVERTEMP_FAULT       0x08    
#define PFX_ERR_TRAP_BROWNOUT_RST        0x0A  
#define PFX_ERR_TRAP_CONFLICT            0x10
#define PFX_ERR_TRAP_ILLEGAL_OPCODE      0x20
#define PFX_ERR_TRAP_CONFIG_MISMATCH     0x40
  
#ifdef	__cplusplus
}
#endif

#endif /* end of include guard: _PFX_H_ */
