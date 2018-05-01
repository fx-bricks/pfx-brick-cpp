#include "pfxbrick.h"

PFxDev::PFxDev()
{
  hdev = NULL;
  tx = new unsigned char[EP_BUFF_LEN];
  rx = new unsigned char[EP_BUFF_LEN]; 
}

PFxDev::~PFxDev()
{
  delete[] tx;
  delete[] rx;
  tx = 0;
  rx = 0;
}

PFxDev::PFxDev (const PFxDev& withDev)
{
  hdev = withDev.hdev;
  tx = new unsigned char[EP_BUFF_LEN];
  for (int i=0; i<EP_BUFF_LEN; i++) tx[i] = withDev.tx[i];
  rx = new unsigned char[EP_BUFF_LEN];
  for (int i=0; i<EP_BUFF_LEN; i++) rx[i] = withDev.rx[i];
}

PFxDev& PFxDev::operator=(const PFxDev& withDev)
{
  if (this == &withDev) return *this;
  hdev = withDev.hdev;
  tx = new unsigned char[EP_BUFF_LEN];
  for (int i=0; i<EP_BUFF_LEN; i++) tx[i] = withDev.tx[i];
  rx = new unsigned char[EP_BUFF_LEN];
  for (int i=0; i<EP_BUFF_LEN; i++) rx[i] = withDev.rx[i];
  return *this;    
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
  if (!is_open)
  { int numBricks = 0;
    std::vector<std::string> serials;
    wchar_t wstr[64];
    
    if (hid_init())
    { printf ("Error initializing the USB HID API\n");
      return false;
    }
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
          if (!is_in_list(brick_sn, serials))
          { numBricks++;
            serials.push_back(brick_sn);
          }
          hid_close(brick);
        }
      }
      currDev = currDev->next;
    }
    hid_free_enumeration(devs);
    
    bool ser_no_in_serials = is_in_list(ser_no, serials);
    if ((ser_no.length() > 0) && (!ser_no_in_serials))
    { printf("The PFx Brick with serial number %s was not found.\n", ser_no.c_str());
    }
    else
    {
      if (numBricks == 0)
      { printf ("No PFx Bricks are currently connected.\n");
      }
      else if ((numBricks > 1) && (ser_no.length() == 0))
      { printf ("There are multiple PFx Bricks connected. Therefore a serial number is required to specify which PFx Brick to connect to.\n");
      }
      else
      { std::string mySerNo;
        if ((numBricks == 1) && (ser_no.length() == 0))
        { mySerNo = serials[0];
        }
        else mySerNo = ser_no;
        str_to_wchar(mySerNo, &wstr[0]);    
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
