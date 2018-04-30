
#ifndef pfxmsg_h
#define pfxmsg_h


class PFxDev;

int usb_transaction(PFxDev& dev, unsigned char *txmsg, unsigned char *rxmsg);

int cmd_get_icd_rev(PFxDev& dev, bool silent);
int cmd_get_status(PFxDev& dev);
int cmd_get_config(PFxDev& dev);
int cmd_set_config(PFxDev& dev, unsigned char *cfgbytes);
int cmd_get_name(PFxDev& dev);
int cmd_set_name(PFxDev& dev, std::string name);
int cmd_get_event_action(PFxDev& dev, int evtID, int ch);
int cmd_set_event_action(PFxDev& dev, int evtID, int ch, PFxAction& action);
int cmd_test_action(PFxDev& dev, PFxAction& action);
int cmd_get_dir_entry(PFxDev& dev, int idx);
int cmd_get_num_files(PFxDev& dev);
int cmd_get_free_space(PFxDev& dev);
int cmd_set_factory_defaults(PFxDev& dev);
    
#endif
