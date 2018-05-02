#include "pfxbrick.h"

int usb_transaction(PFxDev& dev)
{
  hid_write(dev.hdev, &dev.tx[0], EP_BUFF_LEN);
  int res = hid_read(dev.hdev, &dev.rx[0], EP_BUFF_LEN);
  if (res > 0)
  { if (dev.rx[0] == (dev.tx[0] | 0x80))
    { return res;
    }
    else
    { printf ("Error reading valid response from PFx Brick\n");
    }
  }
  return 0;
}

int cmd_get_icd_rev(PFxDev& dev, bool silent)
{
  dev.tx[0] = PFX_CMD_GET_ICD_REV;
  dev.tx[1] = PFX_GET_ICD_BYTE0;
  dev.tx[2] = PFX_GET_ICD_BYTE1;
  dev.tx[3] = PFX_GET_ICD_BYTE2;
  dev.tx[4] = (unsigned char)silent;
  return(usb_transaction(dev));
}
int cmd_get_status(PFxDev& dev)
{
  dev.tx[0] = PFX_CMD_GET_STATUS;
  dev.tx[1] = PFX_STATUS_BYTE0;
  dev.tx[2] = PFX_STATUS_BYTE1;
  dev.tx[3] = PFX_STATUS_BYTE2;
  dev.tx[4] = PFX_STATUS_BYTE3;
  dev.tx[5] = PFX_STATUS_BYTE4;
  dev.tx[6] = PFX_STATUS_BYTE5;
  dev.tx[7] = PFX_STATUS_BYTE6;
  return(usb_transaction(dev));
}

int cmd_get_config(PFxDev& dev)
{
  dev.tx[0] = PFX_CMD_GET_CONFIG;
  return(usb_transaction(dev));
}

int cmd_set_config(PFxDev& dev, unsigned char *cfgbytes)
{
  dev.tx[0] = PFX_CMD_SET_CONFIG;
  for (int i=0; i<63; i++) dev.tx[1+i] = cfgbytes[i];
  return(usb_transaction(dev));
}

int cmd_get_name(PFxDev& dev)
{
  dev.tx[0] = PFX_CMD_GET_NAME;
  return(usb_transaction(dev));
}
  
int cmd_set_name(PFxDev& dev, std::string name);
int cmd_get_event_action(PFxDev& dev, int evtID, int ch);
int cmd_set_event_action(PFxDev& dev, int evtID, int ch, PFxAction& action);
int cmd_test_action(PFxDev& dev, PFxAction& action)
{
  dev.tx[0] = PFX_CMD_TEST_ACTION;
  action.to_bytes(&dev.tx[1]);
  return(usb_transaction(dev));
}

int cmd_get_dir_entry(PFxDev& dev, int idx)
{
  dev.tx[0] = PFX_CMD_FILE_DIR;
  dev.tx[1] = PFX_DIR_REQ_GET_DIR_ENTRY_IDX;
  dev.tx[2] = (unsigned char)(idx & 0xFF);
  return(usb_transaction(dev));
}

int cmd_get_num_files(PFxDev& dev)
{
  dev.tx[0] = PFX_CMD_FILE_DIR;
  dev.tx[1] = PFX_DIR_REQ_GET_FILE_COUNT;
  return(usb_transaction(dev));
}

int cmd_get_free_space(PFxDev& dev)
{
  dev.tx[0] = PFX_CMD_FILE_DIR;
  dev.tx[1] = PFX_DIR_REQ_GET_FREE_SPACE;
  return(usb_transaction(dev));
}

int cmd_set_factory_defaults(PFxDev& dev)
{
  dev.tx[0] = PFX_CMD_SET_FACTORY_DEFAULTS;
  dev.tx[1] = PFX_RESET_BYTE0;
  dev.tx[2] = PFX_RESET_BYTE1;
  dev.tx[3] = PFX_RESET_BYTE2;
  dev.tx[4] = PFX_RESET_BYTE3;
  dev.tx[5] = PFX_RESET_BYTE4;
  dev.tx[6] = PFX_RESET_BYTE5;
  dev.tx[7] = PFX_RESET_BYTE6;
  return(usb_transaction(dev));
}