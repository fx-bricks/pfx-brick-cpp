#include "pfx.h"

#ifndef pfxfiles_h
#define pfxfiles_h

class PFxFile
{
public:
  PFxFile();
  ~PFxFile();
  PFxFile (const PFxFile& withFile);
  PFxFile& operator=(const PFxFile& withFile);

  /* Methods */
  bool is_audio_file();
  void from_bytes(int msglen, unsigned char msg);

  /* Variables */  
  unsigned int id;
  unsigned long size;
  unsigned int firstSector;
  unsigned int attributes;
  unsigned long userData1;
  unsigned long userData2;
  unsigned long crc32;
  std::string name;
};

class PFxDir
{
public:
  PFxDir();
  ~PFxDir();
  PFxDir (const PFxDir& withDir);
  PFxDir& operator=(const PFxDir& withDir);
  
  /* Methods */
  PFxFile* get_file_dir_entry(int fid);

  /* Variables */  
  unsigned int numFiles;
  unsigned long bytesUsed;
  unsigned long bytesLeft;
  PFxFile *files;  
};

#endif
