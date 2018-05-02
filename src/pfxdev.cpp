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