#include <string>
#include <vector>

#ifndef pfxhelpers_h
#define pfxhelpers_h

bool set_with_bit(unsigned char byte, unsigned char mask);

std::string on_off_str(bool on);
std::string status_str(int key);
std::string error_str(int key);
std::string status_led_str(int key);
std::string volume_beep_str(int key);
std::string power_save_str(int key);
std::string lockout_str(int key);
std::string ir_off_str(int key);
std::string ble_off_str(int key);
std::string ble_motor_str(int key);

std::string command_str(int key);
std::string motor_action_str(int key);
std::string ind_lightfx_str(int key);
std::string combo_lightfx_str(int key);
std::string evtid_str(int key);

std::string uint16_tover(unsigned char msb, unsigned char lsb);
std::string bytes_to_hexstr(int numBytes, unsigned char *bytes);
std::string bytes_to_str(int numBytes, unsigned char *bytes);
std::string wchar_to_str(const wchar_t *s);
void str_to_wchar(const std::string& str, wchar_t *ws);                      
bool is_in_list(std::string& s, std::vector<std::string>& slist);

#endif
