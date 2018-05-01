#include <stdio.h>
#include <math.h>
#include <vector>

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

