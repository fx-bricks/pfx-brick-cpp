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

#include "pfxdev.h"

#ifndef pfxmsg_h
#define pfxmsg_h


int usb_transaction(PFxDev& dev);

int cmd_get_icd_rev(PFxDev& dev, bool silent);
int cmd_get_status(PFxDev& dev);
int cmd_get_config(PFxDev& dev);
int cmd_set_config(PFxDev& dev, unsigned char *cfgbytes);
int cmd_get_name(PFxDev& dev);
int cmd_set_name(PFxDev& dev, std::string name);
int cmd_get_event_action(PFxDev& dev, int evtID, int ch);
int cmd_set_event_action(PFxDev& dev, int evtID, int ch, const PFxAction& action);
int cmd_test_action(PFxDev& dev, const PFxAction& action);
int cmd_get_dir_entry(PFxDev& dev, int idx);
int cmd_get_num_files(PFxDev& dev);
int cmd_get_free_space(PFxDev& dev);
int cmd_set_factory_defaults(PFxDev& dev);
    
#endif
