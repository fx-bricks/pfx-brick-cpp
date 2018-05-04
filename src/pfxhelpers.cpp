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

#include <locale>
#include <sstream>
#include <string>
#include <stdlib.h>
#include <sys/stat.h>
#if defined(__APPLE__) || defined(__linux__)
  #include <sys/ioctl.h>
  #include <sys/time.h>
  #include <termios.h>
  #include <unistd.h>
#else
  #include <conio.h>
  #include <Windows.h>
#endif

#include "pfxhelpers.h"
#include "pfx.h"


bool set_with_bit(unsigned char byte, unsigned char mask)
{
  if ((byte & mask) == mask) return true;
  return false;
}

std::string on_off_str(bool on)
{ std::string s;
  
  if (on) s = "ON";
  else s = "OFF";
  return s;
}

std::string status_str(int key)
{ std::string s;
  switch (key)
  {
    case PFX_STATUS_NORMAL: s = "Normal"; break;
    case PFX_STATUS_NORMAL_PENDING: s = "Normal, upgrade pending"; break;
    case PFX_STATUS_SERVICE: s = "Service"; break;
    case PFX_STATUS_SERVICE_PENDING: s = "Service, upgrade pending"; break;
    case PFX_STATUS_SERVICE_BUSY: s = "Service, busy"; break;
    default: s = "Unknown"; break;
  }
  return s;
}

std::string error_str(int key)
{ std::string s;
  switch (key)
  {
    case PFX_ERR_VERIFY_FAIL: s = "Verify failed"; break;
    case PFX_ERR_TRANSFER_FILE_EXISTS: s = "File exists"; break;
    case PFX_ERR_TRANSFER_TOO_BIG: s = "File too big"; break;
    case PFX_ERR_TRANSFER_FILE_NOT_FOUND: s = "File not found"; break;
    case PFX_ERR_TRANSFER_ERROR: s = "Transfer error"; break;
    case PFX_ERR_TRANSFER_CRC_MISMATCH: s = "CRC mismatch"; break;
    case PFX_ERR_TRANSFER_BUSY_WAIT: s = "Busy, try again"; break;
    case PFX_ERR_TRANSFER_COMPLETE: s = "Transfer complete"; break;
    case PFX_ERR_UPGRADE_FAIL: s = "Upgrade failed"; break;
    case PFX_ERR_FILE_SYSTEM_ERR: s = "File system error"; break;
    case PFX_ERR_FILE_INVALID: s = "File is invalid"; break;
    case PFX_ERR_FILE_OUT_OF_RANGE: s = "File access is out of range"; break;
    case PFX_ERR_FILE_READ_ONLY: s = "File is read only"; break;
    case PFX_ERR_FILE_TOO_BIG: s = "File is too big"; break;
    case PFX_ERR_FILE_NOT_FOUND: s = "File not found"; break;
    case PFX_ERR_FILE_NOT_UNIQUE: s = "File ID is not unique"; break;
    case PFX_ERR_FILE_LOCKED_BUSY: s = "File system is locked or busy"; break;
    case PFX_ERR_FILE_SYSTEM_FULL: s = "File system is full"; break;
    case PFX_ERR_FILE_SYSTEM_TIMEOUT: s = "File system operation timed out"; break;
    case PFX_ERR_FILE_INVALID_ADDRESS: s = "File system accessed invalid address"; break;
    case PFX_ERR_FILE_NEXT_SECTOR: s = "File system error reading next sector"; break;
    case PFX_ERR_FILE_ACCESS_DENIED: s = "File system access denied"; break;
    case PFX_ERR_BLE_FAULT: s = "Bluetooth fault"; break;
    case PFX_ERR_SPKR_SHORTCIR_FAULT: s = "Short circuit on speaker output"; break;
    case PFX_ERR_DAC_OVERTEMP_FAULT: s = "Overtemperature reported by DAC"; break;
    case PFX_ERR_TRAP_BROWNOUT_RST: s = "Brown-out reset trap"; break;
    case PFX_ERR_TRAP_CONFLICT: s = "Reset trap conflict"; break;
    case PFX_ERR_TRAP_ILLEGAL_OPCODE: s = "Reset trap due to illegal OP code"; break;
    case PFX_ERR_TRAP_CONFIG_MISMATCH: s = "Reset trap due to configuration mismatch"; break;
    default: s = "Unknown"; break;
  }
  return s;
}

std::string status_led_str(int key)
{ std::string s;
  switch (key)
  {
    case PFX_CFG_STATLED_OFF: s ="Normally OFF, blink with activity"; break;
    case PFX_CFG_STATLED_ON: s = "Normally ON, blink with activity"; break;
    default: s = "Unknown"; break;
  }
  return s;
}

std::string volume_beep_str(int key)
{ std::string s;
  switch (key)
  {
    case PFX_CFG_VOLBEEP_ON: s ="ON"; break;
    case PFX_CFG_VOLBEEP_OFF: s = "OFF"; break;
    default: s = "Unknown"; break;
  }
  return s;
}

std::string power_save_str(int key)
{ std::string s;
  switch (key)
  {
    case PFX_CFG_POWERSAVE_OFF: s = "OFF"; break;
    case PFX_CFG_POWERSAVE_30M: s = "30 min"; break;
    case PFX_CFG_POWERSAVE_60M: s = "60 min"; break;
    case PFX_CFG_POWERSAVE_3HR: s = "3 hrs"; break;
    default: s = "Unknown"; break;
  }
  return s;
}

std::string lockout_str(int key)
{ std::string s;
  switch (key)
  {
    case PFX_CFG_LOCKOUT_INH: s = "Inhibit"; break;
    case PFX_CFG_LOCKOUT_CH1: s = "Toggle from ch 1"; break;
    case PFX_CFG_LOCKOUT_ALLCH: s = "Toggle from any ch"; break;
    default: s = "Unknown"; break;
  }
  return s;
}

std::string ir_off_str(int key)
{ std::string s;
  switch (key)
  {
    case PFX_CFG_IRAUTO_OFF_NEVER: s = "Never"; break;
    case PFX_CFG_IRAUTO_OFF_1MIN: s = "After 1 min"; break;
    case PFX_CFG_IRAUTO_OFF_5MIN: s = "After 5 min"; break;
    case PFX_CFG_IRAUTO_OFF_IMMEDIATE: s = "Immediately"; break;
    default: s = "Unknown"; break;
  }
  return s;
}

std::string ble_off_str(int key)
{ std::string s;
  switch (key)
  {
    case PFX_CFG_BLEAUTO_OFF_NEVER: s = "Never"; break;
    case PFX_CFG_BLEAUTO_OFF_1MIN: s = "After 1 min"; break;
    case PFX_CFG_BLEAUTO_OFF_5MIN: s = "After 5 min"; break;
    case PFX_CFG_BLEAUTO_OFF_IMMEDIATE: s = "Immediately"; break;
    default: s = "Unknown"; break;
  }
  return s;
}
  
std::string ble_motor_str(int key)
{ std::string s;
  switch (key)
  {
    case PFX_CFG_BLE_MOTOR_CONTINUE: s = "Continue operation"; break;
    case PFX_CFG_BLE_MOTOR_STOP: s = "Stop motors"; break;
    default: s = "Unknown"; break;
  }
  return s;
}

std::string command_str(int key)
{ std::string s;
  switch (key)
  {
    case EVT_COMMAND_NONE: s = "None"; break;
    case EVT_COMMAND_ALL_OFF: s = "All OFF"; break;
    case EVT_COMMAND_IR_LOCKOUT_ON: s = "IR Lockout ON"; break;
    case EVT_COMMAND_IR_LOCKOUT_OFF: s = "IR Lockout OFF"; break;
    case EVT_COMMAND_IR_LOCK_TOGGLE: s = "Toggle IR Lockout"; break;
    case EVT_COMMAND_ALL_MOTORS_OFF: s = "All Motors OFF"; break;
    case EVT_COMMAND_ALL_LIGHTS_OFF: s = "All Lights OFF"; break;
    case EVT_COMMAND_ALL_AUDIO_OFF: s = "All Audio OFF"; break;
    case EVT_COMMAND_RESTART: s = "Restart"; break;
    default: s = "Unknown"; break;
  }
  return s;
}

std::string motor_action_str(int key)
{ std::string s;
  switch (key & EVT_MOTOR_ACTION_ID_MASK)
  {
    case EVT_MOTOR_ESTOP: s = "Emergency Stop"; break;
    case EVT_MOTOR_STOP: s = "Stop"; break;
    case EVT_MOTOR_INC_SPD: s = "Increase Speed"; break;
    case EVT_MOTOR_DEC_SPD: s = "Decrease Speed"; break;
    case EVT_MOTOR_INC_SPD_BI: s = "Increase Speed (bi-dir)"; break;
    case EVT_MOTOR_DEC_SPD_BI: s = "Decrease Speed (bi-dir)"; break;
    case EVT_MOTOR_CHANGE_DIR: s = "Change Direction"; break;
    case EVT_MOTOR_SET_SPD: s = "Set Speed"; break;
    case EVT_MOTOR_SET_SPD_TIMED: s = "Set Speed with Duration"; break;
    case EVT_MOTOR_OSCILLATE: s = "Oscillate"; break;
    case EVT_MOTOR_OSCILLATE_BIDIR: s = "Oscillate (bi-dir)"; break;
    case EVT_MOTOR_OSCILLATE_BIDIR_WAIT: s = "Oscillate (bi-dir) with wait"; break;
    case EVT_MOTOR_RANDOM: s = "Random"; break;
    case EVT_MOTOR_RANDOM_BIDIR: s = "Random (bi-dir)"; break;
    case EVT_MOTOR_SOUND_MODULATED: s = "Sound Modulated"; break;
    default: s = "Unknown"; break;
  }
  return s;
}

std::string ind_lightfx_str(int key)
{ std::string s;
  switch (key)
  {
    case EVT_LIGHTFX_NONE: s = "None"; break;
    case EVT_LIGHTFX_ON_OFF_TOGGLE: s = "On/Off"; break;
    case EVT_LIGHTFX_INC_BRIGHT: s = "Increase Brightness"; break;
    case EVT_LIGHTFX_DEC_BRIGHT: s = "Decrease Brightness"; break;
    case EVT_LIGHTFX_SET_BRIGHT: s = "Set Brightness"; break;
    case EVT_LIGHTFX_FLASH50_P: s = "Flash 50%, positive"; break;
    case EVT_LIGHTFX_FLASH50_N: s = "Flash 50%, negative"; break;
    case EVT_LIGHTFX_STROBE_P: s = "Strobe Flasher, positive"; break;
    case EVT_LIGHTFX_STROBE_N: s = "Strobe Flasher, negative"; break;
    case EVT_LIGHTFX_GYRALITE_P: s = "Gyralite, postive"; break;
    case EVT_LIGHTFX_GYRALITE_N: s = "Gyralite, negative"; break;
    case EVT_LIGHTFX_FLICKER: s = "Flicker"; break;
    case EVT_LIGHTFX_RAND_BLINK: s = "Random Blink"; break;
    case EVT_LIGHTFX_PHOTON_TORP: s = "Photon Torpedo"; break;
    case EVT_LIGHTFX_LASER_PULSE: s = "Laser Pulse"; break;
    case EVT_LIGHTFX_ENGINE_GLOW: s = "Engine Glow"; break;
    case EVT_LIGHTFX_LIGHTHOUSE: s = "Light House"; break;
    case EVT_LIGHTFX_BROKEN_LIGHT: s = "Broken Light"; break;
    case EVT_LIGHTFX_STATUS_IND: s = "Status Indicator"; break;
    case EVT_LIGHTFX_SOUND_MOD: s = "Sound Modulated"; break;
    case EVT_LIGHTFX_MOTOR_MOD: s = "Motor Modulated"; break;
    default: s = "Unknown"; break;
  }
  return s;
}

std::string combo_lightfx_str(int key)
{ std::string s;
  switch (key)
  {
    case EVT_COMBOFX_NONE: s = "None"; break;
    case EVT_COMBOFX_LIN_SWEEP: s = "Linear Sweep"; break;
    case EVT_COMBOFX_BARGRAPH: s = "Bargraph"; break;
    case EVT_COMBOFX_KNIGHTRIDER: s = "Knight Rider"; break;
    case EVT_COMBOFX_EMCY_TWSONIC: s = "Twinsonic Style Flashers"; break;
    case EVT_COMBOFX_EMCY_WHELEN: s = "Strobe Style Flashers"; break;
    case EVT_COMBOFX_TIMES_SQ: s = "Times Square"; break;
    case EVT_COMBOFX_NOISE: s = "Noise"; break;
    case EVT_COMBOFX_TWINKLE_STAR: s = "Twinkling Stars"; break;
    case EVT_COMBOFX_TRAFFIC_SIG: s = "Traffic Lights"; break;
    case EVT_COMBOFX_SOUND_BAR: s = "Sound Bar"; break;
    case EVT_COMBOFX_ALT_FLASH: s = "Alternating Flashers"; break;
    case EVT_COMBOFX_LAVA_LAMP: s = "Lava Lamp"; break;
    case EVT_COMBOFX_LASER_CANNON: s = "Laser Cannon"; break;
    default: s = "Unknown"; break;
  }
  return s;
}

std::string evtid_str(int key)
{ std::string s;
  switch (key)
  {
    case EVT_ID_8879_TWO_BUTTONS: s = "Left + Right Button"; break;
    case EVT_ID_8879_LEFT_BUTTON: s = "Left Button"; break;
    case EVT_ID_8879_RIGHT_BUTTON: s = "Right Button"; break;
    case EVT_ID_8879_LEFT_INC: s = "Left Wheel Inc"; break;
    case EVT_ID_8879_LEFT_DEC: s = "Left Wheel Dec"; break;
    case EVT_ID_8879_RIGHT_INC: s = "Right Wheel Inc"; break;
    case EVT_ID_8879_RIGHT_DEC: s = "Rigth Wheel Dec"; break;
    case EVT_ID_8885_LEFT_FWD: s = "Left Joystick Fwd"; break;
    case EVT_ID_8885_LEFT_REV: s = "Left Joystick Rev"; break;
    case EVT_ID_8885_RIGHT_FWD: s = "Right Joystick Fwd"; break;
    case EVT_ID_8885_RIGHT_REV: s = "Right Joystick Rev"; break;
    case EVT_ID_8885_LEFT_CTROFF: s = "Left Joystick Centre"; break;
    case EVT_ID_8885_RIGHT_CTROFF: s = "Right Joystick Centre"; break;
    case EVT_ID_EV3_BEACON: s = "EV3 Beacon"; break;
    case EVT_ID_TEST_EVENT: s = "Test Event"; break;
    case EVT_ID_STARTUP_EVENT: s = "Startup Events 1-4"; break;
    case EVT_ID_STARTUP_EVENT2: s = "Startup Events 5-8"; break;
    case EVT_ID_RCTRAIN_UP: s = "RC Train Up"; break;
    case EVT_ID_RCTRAIN_DOWN: s = "RC Train Down"; break;
    case EVT_ID_RCTRAIN_STOP: s = "RC Train Stop"; break;
    case EVT_ID_RCTRAIN_HORN: s = "RC Train Horn"; break;
    default: s = "Unknown"; break;
  }
  return s;
}

void uint32_to_bytes(unsigned long v, unsigned char *bytes)
{
  bytes[0] = ((v >> 24) & 0xFF);
  bytes[1] = ((v >> 16) & 0xFF);
  bytes[2] = ((v >> 8) & 0xFF);
  bytes[3] = (v & 0xFF);
}

unsigned long bytes_to_uint32(unsigned char *bytes)
{ unsigned long v = 0;
  v  = (unsigned long)(bytes[0] & 0xFF) << 24;
  v |= (unsigned long)(bytes[1] & 0xFF) << 16;
  v |= (unsigned long)(bytes[2] & 0xFF) << 8;
  v |= (unsigned long)(bytes[3] & 0xFF);
  return v;
}

unsigned int bytes_to_uint16(unsigned char *bytes)
{ unsigned int v = 0;
  v  = (unsigned int)(bytes[0] & 0xFF) << 8;
  v |= (unsigned int)(bytes[1] & 0xFF);
  return v;
}

std::string uint16_tover(unsigned char msb, unsigned char lsb)
{ std::string s;
  char sc[16];
  sprintf(sc, "%02X.%02X", msb, lsb);
  s = sc;
  return s;
}

std::string bytes_to_hexstr(int numBytes, unsigned char *bytes)
{ std::string s;
  char sc[64];
  sc[0] = 0;
  for (int i=0; i<numBytes; i++)
  { sprintf(&sc[strlen(sc)], "%02X", bytes[i]);
  }
  s = sc;
  return s;
}

std::string bytes_to_str(int numBytes, unsigned char *bytes)
{ std::string s;
  char sc[64];
  sc[0] = 0;
  for (int i=0; i<numBytes; i++) sc[i] = bytes[i];
  s = sc;
  return s;
}

bool is_in_list(std::string& s, std::vector<std::string>& slist)
{ int listlen = slist.size();
  
  for (int i=0; i<listlen; i++)
  { if (s == slist[i]) return true; 
  }
  return false; 
}

std::string wchar_to_str(const wchar_t *s)
{ char dfault = '?';
  std::locale loc = std::locale();
  std::ostringstream stm;

  while( *s != L'\0' ) {
    stm << std::use_facet< std::ctype<wchar_t> >( loc ).narrow( *s++, dfault );
  }
  return stm.str();
}

void str_to_wchar(const std::string& str, wchar_t *ws)
{
  std::wstring widestr = std::wstring(str.begin(), str.end());
  const wchar_t* wcstr = widestr.c_str();
  int len = widestr.length();
  for (int i=0; i<len; i++) { *ws++ = *wcstr++; }
  *ws = 0;
}

unsigned long get_file_size(std::string filename)
{
  struct stat stat_buf;
  int rc = stat(filename.c_str(), &stat_buf);
  return rc == 0 ? (unsigned long)stat_buf.st_size : 0ul;
}

std::string get_file_basename(std::string filename)
{
  const size_t last_slash_idx = filename.find_last_of("\\/");
  if (std::string::npos != last_slash_idx)
  { filename.erase(0, last_slash_idx + 1);
  }
  // Remove extension if present.
  const size_t period_idx = filename.rfind('.');
  if (std::string::npos != period_idx)
  { filename.erase(period_idx);
  }
  return filename;
}

int ch_to_mask(std::string& s)
{ int mask = 0;
  int len = s.length();
  for (int i=0; i<len; i++)
  { std::string cs = s.substr(i, 1);
    if      ((cs == "1") || (cs == "A") || (cs == "a")) mask |= 0x01;
    else if ((cs == "2") || (cs == "B") || (cs == "b")) mask |= 0x02;
    else if ((cs == "3") || (cs == "C") || (cs == "c")) mask |= 0x04;
    else if ((cs == "4") || (cs == "D") || (cs == "d")) mask |= 0x08;
    else if (cs == "5") mask |= 0x10;
    else if (cs == "6") mask |= 0x20;
    else if (cs == "7") mask |= 0x40;
    else if (cs == "8") mask |= 0x80;
  }
  return mask;
}

std::string mask_to_ch(int mask)
{
  std::string s;
  if (mask & 0x01) s.append("1 ");
  if (mask & 0x02) s.append("2 ");
  if (mask & 0x04) s.append("3 ");
  if (mask & 0x08) s.append("4 ");
  if (mask & 0x10) s.append("5 ");
  if (mask & 0x20) s.append("6 ");
  if (mask & 0x40) s.append("7 ");
  if (mask & 0x80) s.append("8 ");
  return s;
}

int duration_to_fixed_value(double duration)
{
  if (duration < 1.0) return EVT_SOUND_DUR_500MS;
  else if (duration < 1.5)  return EVT_SOUND_DUR_1S;
  else if (duration < 2.0)  return EVT_SOUND_DUR_1_5S;
  else if (duration < 3.0)  return EVT_SOUND_DUR_2S;
  else if (duration < 4.0)  return EVT_SOUND_DUR_3S;
  else if (duration < 5.0)  return EVT_SOUND_DUR_4S;
  else if (duration < 10.0) return EVT_SOUND_DUR_5S;
  else if (duration < 15.0) return EVT_SOUND_DUR_10S;
  else if (duration < 20.0) return EVT_SOUND_DUR_15S;
  else if (duration < 30.0) return EVT_SOUND_DUR_20S;
  else if (duration < 45.0) return EVT_SOUND_DUR_30S;
  else if (duration < 60.0) return EVT_SOUND_DUR_45S;
  else if (duration < 90.0) return EVT_SOUND_DUR_60S;
  else if (duration < 120.0) return EVT_SOUND_DUR_90S;
  else if (duration < 300.0) return EVT_SOUND_DUR_2M;
  return EVT_SOUND_DUR_5M;
}

void address_to_evtch(int address, int *evt, int *ch)
{
  *evt = (address >> 2) & 0xFF;
  *ch = address & EVT_EVENT_CH_MASK;
}

static int xPrev = 0;
static int yPrev = 0;
static int xmody = 0;
static int xmodyPrev = 0;
static uint64_t tNow = 0;
static uint64_t tPrev = 0;
static uint64_t tDiff = 0;
static uint64_t tStart = 0;
static uint64_t tStop = 0;
static uint64_t tTotal = 0;

#if defined( OS_WINDOWS )
int gettimeofday( struct timeval * tp, struct timezone * tzp )
{
	// Note: some broken versions only have 8 trailing zero's, the correct epoch has 9 trailing zero's
	// This magic number is the number of 100 nanosecond intervals since January 1, 1601 (UTC)
	// until 00:00:00 January 1, 1970 
	static const uint64_t EPOCH = ( (uint64_t)116444736000000000ULL );

	SYSTEMTIME  system_time;
	FILETIME    file_time;
	uint64_t    time;

	GetSystemTime( &system_time );
	SystemTimeToFileTime( &system_time, &file_time );
	time = ( (uint64_t)file_time.dwLowDateTime );
	time += ( (uint64_t)file_time.dwHighDateTime ) << 32;

	tp->tv_sec = (long)( ( time - EPOCH ) / 10000000L );
	tp->tv_usec = (long)( system_time.wMilliseconds * 1000 );
	return 0;
}
#endif

uint64_t GetTimeStamp() {
    struct timeval tv;
    gettimeofday(&tv,NULL);
    return tv.tv_sec*(uint64_t)1000000+tv.tv_usec;
}

void print_progress (int x, int y)
{ double pctComplete, rate;
  int nIntervals, i;
  
  nIntervals = y / 50;
  xmody = (x % nIntervals);
  tPrev = tNow;
  
  if (nIntervals > 0)
  {
    if (xmody < xmodyPrev)
    {
      pctComplete = (double)x / (double)y * 50.0;
      printf ("\r[");
      for (i=0; i<50; i++)
      { if ((int)(pctComplete) >= i) printf (".");
        else printf (" ");
      }
      printf ("] %.0lf %%", pctComplete*2.0);
      
      if (y == yPrev)
      { tNow = GetTimeStamp();
        tDiff = tNow - tPrev;
        if (tDiff > 0)
        { rate = ((double)x - (double)xPrev) / ((double)tDiff) * 1e6;
          if (rate < 1e3) printf (" %.0lf B/s", rate);
          else printf (" %.2lf kB/s", rate/1e3);
        }
        xPrev = x;
      }
      if (pctComplete <= 2) tStart = GetTimeStamp();
      if (pctComplete >= 49.5)
      { tStop = GetTimeStamp();
        tTotal = tStop - tStart;
        printf (" %.2lf sec (%.2lf kB/s)\n", (double)tTotal * 1e-6, (double)y/(double)tTotal * 1e3);
      }
      fflush(stdout);
    }
    xmodyPrev = xmody;
    yPrev = y;
  }
}

