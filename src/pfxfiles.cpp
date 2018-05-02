#include <stdio.h>
#include <math.h>
#include <vector>
#include <string>

#include "pfxbrick.h"


PFxFile::PFxFile()
{
  id = 0;
  size = 0;
  firstSector = 0;
  attributes = 0;
  userData1 = 0;
  userData2 = 0;
  crc32 = 0;
  name = "";
}

PFxFile::~PFxFile()
{  
}

PFxFile::PFxFile (const PFxFile& withFile)
{
  id = withFile.id;
  size = withFile.size;
  firstSector = withFile.firstSector;
  attributes = withFile.attributes;
  userData1 = withFile.userData1;
  userData2 = withFile.userData2;
  crc32 = withFile.crc32;
  name = withFile.name;  
}

PFxFile& PFxFile::operator=(const PFxFile& withFile)
{
  if (this == &withFile) return *this;  
  id = withFile.id;
  size = withFile.size;
  firstSector = withFile.firstSector;
  attributes = withFile.attributes;
  userData1 = withFile.userData1;
  userData2 = withFile.userData2;
  crc32 = withFile.crc32;
  name = withFile.name;  
  return *this;
}

void PFxFile::Print()
{
  printf("%3d %-24s %6.1lf kB %04X %08lX %08lX %08lX\n", id, name.c_str(), (double)size/1000.0, attributes, userData1, userData2, crc32); 
}

void PFxFile::from_bytes(unsigned char *msg)
{
  id = msg[3];
  size = bytes_to_uint32(&msg[4]);
  firstSector = bytes_to_uint16(&msg[8]);
  attributes = bytes_to_uint16(&msg[10]);
  userData1 = bytes_to_uint32(&msg[12]);
  userData2 = bytes_to_uint32(&msg[16]);
  crc32 = bytes_to_uint32(&msg[20]);
  char sn[64];
  for (int i=0; i<32; i++) sn[i] = msg[24+i];
  sn[32] = 0;
  name = sn;
}

PFxDir::PFxDir()
{
  numFiles = 0;
  bytesUsed = 0;
  bytesLeft = 0;
  files = 0;    
}

PFxDir::~PFxDir()
{
  if (files) 
  { delete [] files;
    files = 0;    
  }
}

PFxDir::PFxDir (const PFxDir& withDir)
{
  numFiles = withDir.numFiles;
  bytesUsed = withDir.bytesUsed;
  bytesLeft = withDir.bytesLeft;
  if (numFiles > 0)
  { files = new PFxFile[numFiles];
    for (int i=0; i<numFiles; i++) files[i] = withDir.files[i];
  }
}

PFxDir& PFxDir::operator=(const PFxDir& withDir)
{
  if (this == &withDir) return *this;
  numFiles = withDir.numFiles;
  bytesUsed = withDir.bytesUsed;
  bytesLeft = withDir.bytesLeft;
  if (files) { delete [] files; files = 0; }
  if (numFiles > 0)
  { files = new PFxFile[numFiles];
    for (int i=0; i<numFiles; i++) files[i] = withDir.files[i];
  }
  return *this;
}

PFxFile* PFxDir::get_file_dir_entry(int fid)
{
  for (int i=0; i<numFiles; i++)
  { if (fid == files[i].id)
    { return &files[i];
    }    
  }
  return 0;
}

void PFxDir::Clear()
{
  if (files) { delete [] files; files = 0; }
  numFiles = 0;
}

void PFxDir::Reallocate (int newLength)
{
  Clear();
  if (newLength <= 0) return;
  numFiles = newLength;
  files = new PFxFile[numFiles];
}

void PFxDir::Resize (int newLength)
{
  if (newLength <= 0 )
  { numFiles = 0;
    Clear ();
    return;
  }
  PFxFile *newFiles = new PFxFile[newLength];
  if (numFiles > 0)
  {
    int numToCopy = (newLength > numFiles) ? numFiles : newLength;
    for (int i=0; i<numToCopy; i++) newFiles[i] = files[i];
  }
  delete[] files;
  files = newFiles;
  numFiles = newLength;
}

void PFxDir::InsertBefore(const PFxFile& withFile, int atIdx)
{ int i;
  
  if (atIdx < 0) return;
  if (atIdx > numFiles) return;

  PFxFile *newFiles = new PFxFile[numFiles + 1];
  
  for (i=0; i<atIdx; i++) newFiles[i] = files[i];
  newFiles[atIdx] = withFile;
  for (i=atIdx; i<numFiles; i++) newFiles[i+1] = files[i];
  
  if (numFiles) { delete[] files; files = 0; }
  files = newFiles;
  numFiles += 1;
}

void PFxDir::Remove(int atIdx)
{ int i;
  
  if (atIdx < 0) return;
  if (atIdx > numFiles) return;
  
  i = numFiles - 1;
  
  if (i > 0)
  {
    PFxFile *newFiles = new PFxFile[numFiles - 1];
    
    for (i=0; i<atIdx; i++) newFiles[i] = files[i];
    for (i=atIdx+1; i<numFiles; i++) newFiles[i-1] = files[i];
        
    delete[] files;
    files = newFiles;
  }
  else { delete [] files; files = 0; }
  
  numFiles -= 1;
}

void PFxDir::Print()
{
  printf("%3s %-24s %6s    %4s %8s %8s %8s\n", "ID", "Name", "Size", "Attr", "User1", "User2", "CRC32");
  for (int i=0; i<numFiles; i++) files[i].Print();
  printf("%d files, %.1lf kB used, %.1lf kB remaining\n", numFiles, (double)bytesUsed/1000.0, (double)bytesLeft/1000.0);
}

bool fs_error_check(int res_code)
{
  if (res_code > 62)
  { printf("File system error: [%02X] %s\n", res_code, error_str(res_code).c_str());
    return true;
  }  
  return false;
}

void fs_format(PFxDev& dev, bool quick)
{
  dev.tx[0] = PFX_CMD_FILE_FORMAT_FS;
  dev.tx[1] = PFX_FORMAT_BYTE0;
  dev.tx[2] = PFX_FORMAT_BYTE1;
  dev.tx[3] = PFX_FORMAT_BYTE2;
  if (quick) dev.tx[4] = 0;
  else       dev.tx[4] = 1;
  int res = usb_transaction(dev);
  fs_error_check(dev.rx[1]);
}

void fs_remove_file(PFxDev& dev, int fid)
{
  dev.tx[0] = PFX_CMD_FILE_REMOVE;
  dev.tx[1] = (unsigned char)(fid & 0xFF);
  int res = usb_transaction(dev);
  fs_error_check(dev.rx[1]);
}

void fs_copy_file_to(PFxDev& dev, int fid, std::string fn, bool show_progress)
{ int res = 0;
  unsigned long nBytes = get_file_size(fn);
  if (nBytes > 0)
  { dev.tx[0] = PFX_CMD_FILE_OPEN;
    dev.tx[1] = (unsigned char)(fid & 0xFF);
    dev.tx[2] = 0x06; // CREATE | WRITE mode
    uint32_to_bytes(nBytes, &dev.tx[3]);
    std::string name = get_file_basename(fn);
    int fnlen = name.length();
    if (fnlen > 32) fnlen = 32;
    for (int i=0; i<fnlen; i++) dev.tx[7+i] = (unsigned char)name[i];
    for (int i=fnlen; i<32; i++) dev.tx[7+i] = 0;
    res = usb_transaction(dev);
    if (res)
    {
      if (!fs_error_check(dev.rx[1]))      
      {
        FILE *fp;
        fp = fopen(fn.c_str(), "rb");
        unsigned long nCount = 0;
        unsigned long nRead = 0;
        unsigned char buf[64];
        bool err = false;
        while ((nCount < nBytes) && !err)
        { nRead = fread(&buf[0], 1, 61, fp);
          nCount += nRead;
          if (nRead > 0)
          {
            dev.tx[0] = PFX_CMD_FILE_WRITE;
            dev.tx[1] = (unsigned char)(fid & 0xFF);
            dev.tx[2] = (unsigned char)(nRead & 0xFF);
            for (int i=0; i<nRead; i++) dev.tx[3+i] = buf[i];
            res = usb_transaction(dev);
            err = fs_error_check(dev.rx[1]);
          }
        }
        fclose(fp);
        dev.tx[0] = PFX_CMD_FILE_CLOSE;
        dev.tx[1] = (unsigned char)(fid & 0xFF);
        res = usb_transaction(dev);
        err = fs_error_check(dev.rx[1]);
      }
    }
  }
}

void fs_copy_file_from(PFxDev& dev, const PFxFile& file, std::string fn, bool show_progress)
{ int res = 0;
  dev.tx[0] = PFX_CMD_FILE_OPEN;
  dev.tx[1] = (unsigned char)(file.id & 0xFF);
  res = usb_transaction(dev);
  if (res)
  {
    if (!fs_error_check(dev.rx[1]))      
    { FILE *fp;
      std::string nf;
      if (fn.length() > 0) nf = fn;
      else nf = file.name;
      fp = fopen(nf.c_str(), "wb");
      unsigned long nCount = 0;
      unsigned long nToRead = 0;
      bool err = false;
      while ((nCount < file.size) && !err)
      {
        dev.tx[0] = PFX_CMD_FILE_READ;
        dev.tx[1] = (unsigned char)(file.id & 0xFF);
        nToRead = file.size - nCount;
        if (nToRead > 62) nToRead = 62;
        dev.tx[2] = (unsigned char)nToRead;
        res = usb_transaction(dev);
        err = fs_error_check(dev.rx[1]);
        if (!err)
        { 
          nCount += dev.rx[1];
          fwrite(&dev.rx[2], 1, dev.rx[1], fp);
        }
      }
      fclose(fp);
      dev.tx[0] = PFX_CMD_FILE_CLOSE;
      dev.tx[1] = (unsigned char)(file.id & 0xFF);
      res = usb_transaction(dev);
      err = fs_error_check(dev.rx[1]);
    }      
  }  
}
