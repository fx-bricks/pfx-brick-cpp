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

#include "pfxbrick.h"

std::vector<std::string> find_bricks(bool show_list)
{
  std::vector<std::string> serials;
  int numBricks = 0;
  wchar_t wstr[64];
  
  if (hid_init())
  { printf ("Error initializing the USB HID API\n");
  }
  else
  {
    struct hid_device_info *devs, *currDev;
    devs = hid_enumerate(PFX_USB_VENDOR_ID, PFX_USB_PRODUCT_ID);
    currDev = devs;
    while (currDev)
    {
      if (currDev->usage_page == PFX_USB_USAGE_PAGE)
      {
        hid_device *brick = hid_open_path(currDev->path);
        if (brick)
        { hid_get_serial_number_string(brick, &wstr[0], 16);
          std::string brick_sn = wchar_to_str(&wstr[0]);
          hid_get_product_string(brick, &wstr[0], 32);
          std::string brick_desc = wchar_to_str(&wstr[0]);
          if (!is_in_list(brick_sn, serials))
          { numBricks++;
            serials.push_back(brick_sn);
            if (show_list)
            { printf("%d. %s, Serial No: %s\n", numBricks, brick_desc.c_str(), brick_sn.c_str());
            }
          }
          hid_close(brick);
        }
      }
      currDev = currDev->next;
    }
    hid_free_enumeration(devs);
    hid_exit();
  }
  return serials;    
}

PFxBrick::PFxBrick()
{
  product_id = "";
  serial_no = "";
  product_desc = "";
  firmware_ver = "";
  firmware_build = "";
  icd_rev = "";
  status = 0;
  error = 0;
  usb_vid = PFX_USB_VENDOR_ID;
  usb_pid = PFX_USB_PRODUCT_ID;
  usb_manu_str = "";
  usb_prod_str = "";
  usb_serno_str = "";
  is_open = false;
  name = "";
}

PFxBrick::~PFxBrick()
{
}

PFxBrick::PFxBrick (const PFxBrick& withBrick)
{
  dev = withBrick.dev;
  config = withBrick.config;
  filedir = withBrick.filedir;
  product_id = withBrick.product_id;
  serial_no = withBrick.serial_no;
  product_desc = withBrick.product_desc;
  firmware_ver = withBrick.firmware_ver;
  firmware_build = withBrick.firmware_build;
  icd_rev = withBrick.icd_rev;
  status = withBrick.status;
  error = withBrick.error;
  usb_vid = withBrick.usb_vid;
  usb_pid = withBrick.usb_pid;
  usb_manu_str = withBrick.usb_manu_str;
  usb_prod_str = withBrick.usb_prod_str;
  usb_serno_str = withBrick.usb_serno_str;
  is_open = withBrick.is_open;
  name = withBrick.name;
  
}

PFxBrick& PFxBrick::operator=(const PFxBrick& withBrick)
{
  if (this == &withBrick) return *this;
  dev = withBrick.dev;
  config = withBrick.config;
  filedir = withBrick.filedir;
  product_id = withBrick.product_id;
  serial_no = withBrick.serial_no;
  product_desc = withBrick.product_desc;
  firmware_ver = withBrick.firmware_ver;
  firmware_build = withBrick.firmware_build;
  icd_rev = withBrick.icd_rev;
  status = withBrick.status;
  error = withBrick.error;
  usb_vid = withBrick.usb_vid;
  usb_pid = withBrick.usb_pid;
  usb_manu_str = withBrick.usb_manu_str;
  usb_prod_str = withBrick.usb_prod_str;
  usb_serno_str = withBrick.usb_serno_str;
  is_open = withBrick.is_open;
  name = withBrick.name;
  return *this;
}

bool PFxBrick::open(std::string ser_no)
{
  wchar_t wstr[64];

  if (!is_open)
  { int numBricks = 0;
    std::vector<std::string> serials;

    serials = find_bricks(false);    
    numBricks = serials.size();
    if ((ser_no.length() > 0) && (!is_in_list(ser_no, serials)))
    { printf("The PFx Brick with serial number %s was not found.\n", ser_no.c_str());
    }
    else
    { if (hid_init())
      { printf ("Error initializing the USB HID API\n");
        return false;
      }

      if (numBricks == 0)
      { printf ("No PFx Bricks are currently connected.\n");
      }
      else if ((numBricks > 1) && (ser_no.length() == 0))
      { printf ("There are multiple PFx Bricks connected. Therefore a serial number is required to specify which PFx Brick to connect to.\n");
      }
      else
      { 
        std::string mySerNo;
        if ((numBricks == 1) && (ser_no.length() == 0))
        { mySerNo = serials[0];
        }
        else mySerNo = ser_no;
        str_to_wchar(mySerNo, &wstr[0]);    
        std::string wtest = wchar_to_str(&wstr[0]);
        dev.hdev = hid_open(PFX_USB_VENDOR_ID, PFX_USB_PRODUCT_ID, &wstr[0]);
        hid_get_manufacturer_string(dev.hdev, &wstr[0], 32);
        usb_manu_str = wchar_to_str(&wstr[0]);
        hid_get_product_string(dev.hdev, &wstr[0], 32);
        usb_prod_str = wchar_to_str(&wstr[0]);
        hid_get_serial_number_string(dev.hdev, &wstr[0], 32);
        usb_serno_str = wchar_to_str(&wstr[0]);
        hid_set_nonblocking(dev.hdev, 0);
        is_open = true;
      }
    }
  }
  return is_open;
}

void PFxBrick::close()
{
  if (is_open)
  { hid_close(dev.hdev);
    hid_exit();
    is_open = false;
  }
}

void PFxBrick::get_icd_rev(bool silent)
{ if (!is_open) return;
  int res = cmd_get_icd_rev(dev, silent);
  if (res)
  { icd_rev = uint16_tover(dev.rx[1], dev.rx[2]);
  }
}

void PFxBrick::get_status()
{ if (!is_open) return;
  int res = cmd_get_status(dev);
  if (res)
  { status = dev.rx[1];
    error = dev.rx[2];
    product_id = bytes_to_hexstr(2, &dev.rx[7]);
    serial_no = bytes_to_hexstr(4, &dev.rx[9]);
    product_desc = bytes_to_str(24, &dev.rx[13]);
    firmware_ver = uint16_tover(dev.rx[37], dev.rx[38]);
    firmware_build = bytes_to_hexstr(2, &dev.rx[39]);
  }
}

void PFxBrick::print_status()
{
  printf("USB vendor ID         : %04X\n", usb_vid);
  printf("USB product ID        : %04X\n", usb_pid);
  printf("USB product desc      : %s\n", usb_prod_str.c_str());
  printf("USB manufacturer      : %s\n", usb_manu_str.c_str());
  printf("PFx Brick product ID  : %s, %s\n", product_id.c_str(), product_desc.c_str());
  printf("Serial number         : %s\n", serial_no.c_str());
  printf("Firmware version      : %s build %s\n", firmware_ver.c_str(), firmware_build.c_str());
  printf("Status                : %02X %s\n", status, status_str(status).c_str());
  printf("Errors                : %02X %s\n", error, error_str(error).c_str());  
}

void PFxBrick::get_config()
{ if (!is_open) return;
  int res = cmd_get_config(dev);
  if (res) config.from_bytes(&dev.rx[0]);
}

void PFxBrick::print_config()
{
  config.Print();
}

void PFxBrick::set_config()
{ if (!is_open) return;
  int res = 0;
  unsigned char msg[64];
  config.to_bytes(&msg[0]);
  res = cmd_set_config(dev, &msg[0]);
}

void PFxBrick::get_name()
{ if (!is_open) return;
  int res = cmd_get_name(dev);
  if (res)
  { for (int i=0; i<PFX_NAME_MAX; i++) name[i] = dev.rx[1+i];
  }
}

void PFxBrick::set_name(std::string name)
{ if (!is_open) return;
  int res = cmd_set_name(dev, name);
}

PFxAction& PFxBrick::get_action_by_address(int address, PFxAction& action)
{ if (!is_open) return action;
  if (address > EVT_LUT_MAX)
  { printf("Requested action at address %02X is out of range\n", address);
    return action;
  }
  int evt = 0;
  int ch = 0;
  address_to_evtch(address, &evt, &ch);
  return (get_action(evt, ch, action));
}

PFxAction& PFxBrick::get_action(int evtID, int ch, PFxAction& action)
{ if (!is_open) return action;
  if ((ch > 3) || (evtID > EVT_ID_MAX))
  { printf("Requested action (id=%02X, ch=%02X) is out of range\n", evtID, ch);
  }
  else
  { int res = cmd_get_event_action(dev, evtID, ch);
    if (res)
    { action = PFxAction();
      action.from_bytes(&dev.rx[1]); 
    }
  }  
  return action;
}

void PFxBrick::set_action_by_address(int address, const PFxAction& action)
{ if (!is_open) return;
  if (address > EVT_LUT_MAX)
  { printf("Requested action at address %02X is out of range\n", address);
    return;
  }
  int evt = 0;
  int ch = 0;
  address_to_evtch(address, &evt, &ch);
  set_action(evt, ch, action);
}

void PFxBrick::set_action(int evtID, int ch, const PFxAction& action)
{ if (!is_open) return;
  if ((ch > 3) || (evtID > EVT_ID_MAX))
  { printf("Requested action (id=%02X, ch=%02X) is out of range\n", evtID, ch);
    return;
  }
  int res = cmd_set_event_action(dev, evtID, ch, action);
}

void PFxBrick::test_action(const PFxAction& action)
{
  cmd_test_action(dev, action);
}
      
void PFxBrick::refresh_file_dir()
{ if (!is_open) return;
  int res = 0;
  res = cmd_get_free_space(dev);
  if (res)
  { filedir.bytesLeft = bytes_to_uint32(&dev.rx[3]);
    unsigned long capacity = bytes_to_uint32(&dev.rx[7]);
    filedir.bytesUsed = capacity - filedir.bytesLeft;
  }
  res = cmd_get_num_files(dev);
  if (res)
  { filedir.Clear();
    int file_count = bytes_to_uint16(&dev.rx[3]);
    for (int i=0; i<64; i++)
    { res = cmd_get_dir_entry(dev, i+1);
      PFxFile d = PFxFile();
      d.from_bytes(&dev.rx[0]);
      if (d.id < 0xFF) filedir.InsertAtEnd(d);
    }
  }
}

void PFxBrick::put_file(int fileID, std::string fn, bool show_progress)
{
  fs_copy_file_to(dev, fileID, fn, show_progress);
}

void PFxBrick::get_file(int fileID, std::string fn, bool show_progress)
{
  refresh_file_dir();
  PFxFile *f = filedir.get_file_dir_entry(fileID);
  fs_copy_file_from(dev, *f, fn, show_progress);
}

void PFxBrick::remove_file(int fileID)
{
  fs_remove_file(dev, fileID);
}

void PFxBrick::format_fs(bool quick)
{
  fs_format(dev, quick);
}

void PFxBrick::reset_factory_config()
{
  cmd_set_factory_defaults(dev);
}


