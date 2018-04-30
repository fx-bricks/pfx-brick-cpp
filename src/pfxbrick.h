#include <string>
#include <vector>
#include <iterator>
#include "hidapi.h"
#include "pfxconfig.h"
#include "pfxfiles.h"
#include "pfxhelpers.h"
#include "pfxaction.h"
#include "pfxmsg.h"

#ifndef pfxbrick_h
#define pfxbrick_h

#define EP_BUFF_LEN 64


class PFxDev
{
public:
  PFxDev();
  ~PFxDev();
  PFxDev (const PFxDev& withDev);
  PFxDev& operator=(const PFxDev& withDev);

  hid_device *hdev;
  unsigned char *tx;
  unsigned char *rx;
};


class PFxBrick
{
public:
  PFxBrick();
  ~PFxBrick();
  PFxBrick (const PFxBrick& withBrick);
  PFxBrick& operator=(const PFxBrick& withBrick);
  
  /* Methods */
  bool open(void) { return(open("")); }
  bool open(std::string ser_no);
  void close();
  void get_icd_rev() { return get_icd_rev(false); }
  void get_icd_rev(bool silent);
  void get_status();
  void print_status();
  void get_config();
  void print_config();
  void set_config();
  void get_name();
  void set_name();
  PFxAction& get_action_by_address(int address);
  PFxAction& get_action(int evtID, int ch);
  void set_action_by_address(int address, PFxAction& action);
  void set_action(int evtID, int ch, PFxAction& action);
  void test_action(PFxAction& action);
  void refresh_file_dir();
  void put_file(int fileID, char *fn) { put_file(fileID, fn, true); }
  void put_file(int fileID, char *fn, bool show_progress);
  void get_file(int fileID, char *fn, bool show_progress);
  void get_file(int fileID, char *fn) { get_file(fileID, fn, true); }
  void remove_file(int fileID);
  void format_fs(bool quick);
  void format_fs() { format_fs(false); }  
  void reset_factory_config();
  
  /* Variables */
  PFxDev dev;
  std::string product_id;
  std::string serial_no;
  std::string product_desc;
  std::string firmware_ver;
  std::string firmware_build;
  std::string icd_rev;
  int status;
  int error;
  int usb_vid;
  int usb_pid;
  std::string usb_manu_str;
  std::string usb_prod_str;
  std::string usb_serno_str;
  bool is_open;
  std::string name;
  
  PFxConfig config;
//  PFxDir filedir;
};

#endif