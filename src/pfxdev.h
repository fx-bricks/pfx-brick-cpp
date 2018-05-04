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

#include "hidapi.h"

#ifndef pfxdev_h
#define pfxdev_h

/**
  A container class for USB I/O session data.
  This class contains the device handle to the USB HID API library.
  It also contains 64 byte transmit and receive buffers to pass to
  the USB driver for the transmit and receive endpoints.
*/
class PFxDev
{
public:
  PFxDev();
  ~PFxDev();
  PFxDev (const PFxDev& withDev);
  PFxDev& operator=(const PFxDev& withDev);
  
  /** device handle to the USB HID API */
  hid_device *hdev;
  /** 64 byte transmit data buffer */
  unsigned char *tx;
  /** 64 byte receive data buffer */
  unsigned char *rx;
};

#endif
