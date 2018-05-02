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
