#include "pfx.h"

#ifndef pfxfiles_h
#define pfxfiles_h

/**
  File directory entry container class.
  
  This class contains directory entry data for a file on the PFx file system.
*/
class PFxFile
{
public:
  PFxFile();
  ~PFxFile();
  PFxFile (const PFxFile& withFile);
  PFxFile& operator=(const PFxFile& withFile);

  /* Methods */
  /**
  Checks the file attributes to see if this file is a valid audio WAV file.

  @returns True if it is valid audio WAV file
  */
  bool is_audio_file();
  /**
    Converts the message string bytes read from the PFx Brick into
    the corresponding data members of this class.
     
    @param msg pointer to message bytes array 
  */
  void from_bytes(unsigned char *msg);
  /**
    Prints the contents of this class in human readable form
    using formatted printf statements.
  */
  void Print();
  
  /* Variables */ 
  /** unique file ID */ 
  unsigned int id;
  /** size in bytes */ 
  unsigned long size;
  /** the first 4k sector index in flash memory */ 
  unsigned int firstSector;
  /** 16-bit attributes field */ 
  unsigned int attributes;
  /** 32-bit user defined data field */ 
  unsigned long userData1;
  /** 32-bit user defined data field */ 
  unsigned long userData2;
  /** CRC32 hash of the file (auto computed after write) */ 
  unsigned long crc32;
  /** UTF-8 filename up to 32 bytes */ 
  std::string name;
};

/**
  File directory container class.
  
  This class contains PFx file system directory.
*/
class PFxDir
{
public:
  PFxDir();
  ~PFxDir();
  PFxDir (const PFxDir& withDir);
  PFxDir& operator=(const PFxDir& withDir);
  
  /* Methods */
  /**
    Returns a file directory entry containined in a PFxFile class.
    
    @param fid the unique file ID of desired directory entry
    @returns a pointer to a PFxFile directory entry
  */
  PFxFile* get_file_dir_entry(int fid);
  /**
    Clear the file directory array PFxFile *files
  */
  void Clear();
  /**
    Reallocate the file directory array of PFxFile *files
  
    @param newLength the new size of the file directory
  */
  void Reallocate (int newLength);
  /**
    Resize the file directory array of PFxFile *files
  
    @param newLength the new size of the file directory
  */
  void Resize (int newLength);
  /**
    Insert a new PFxFile entry into the directory
  
    @param withFile a PFxFile entry to insert
    @param atIdx the index where the new entry is inserted
  */
  void InsertBefore  (PFxFile withFile, int atIdx);
  /**
    Remove the specified PFxFile entry from the directory
  
    @param atIdx the index of the PFxFile to remove
  */
  void Remove (int atIdx);
  /** 
    A convenient wrapper for InsertBefore to add a new PFxFile
    entry at the beginning of the directory
  
    @param withFile the PFxFile entry to insert
  */
  void InsertAtBeginning (PFxFile withFile) { InsertBefore (withFile, 0); }
  /** 
    A convenient wrapper for InsertBefore to add a new PFxFile
    entry at the end of the directory

    @param withFile the PFxFile entry to insert
  */
  void InsertAtEnd (PFxFile withFile) { InsertBefore (withFile, numFiles); }
  /**
    Prints the contents of this class in human readable form
    using formatted printf statements.
  */
  void Print();
  
  /* Variables */  
  /** number of files in the file system */
  unsigned int numFiles;
  /** bytes occupied by files */
  unsigned long bytesUsed;
  /** remaining space in bytes */
  unsigned long bytesLeft;
  /** a list of PFxFile objects corresponding to directory entries */
  PFxFile *files;  
};

/**
    Convenience error status lookup function used by other file system functions.
    
    @param res result status code byte returned by almost all file system ICD messages
    @returns **true** if there is an error, **false** on success
*/
bool fs_error_check(int res_code);

/**
  Sends an ICD message to format the PFx Brick file system.
  
  @param dev PFxDev reference containing the USB HID session handle
  @param quick: If **true**, only occupied sectors are erased. If **false**, every sector is erased, i.e. a complete format.
*/
void fs_format(PFxDev& dev, bool quick=false);

/**
  Sends an ICD message to remove a file from the PFx Brick file system.
  
  @param dev PFxDev reference containing the USB HID session handle
  @param fid the file ID of the file to remove
*/
void fs_remove_file(PFxDev& dev, int fid);

/**
  File copy handler to put a file on the PFx Brick.
  
  This function handles the process of opening and transferring
  file data from the host to the PFx Brick file system. A copy session
  may involve many message transactions with the PFx Brick and could
  be time consuming. Therefore, a progress bar can be optionally shown
  on the console to monitor the transfer.
  
  @param dev PFxDev reference containing the USB HID session handle
  @param fid a unique file ID to assign the copied file
  @param fn the host filename (optionally including path) to copy
  @param show_progress: a flag to show the progress bar indicator during transfer
*/
void fs_copy_file_to(PFxDev& dev, int fid, std::string fn, bool show_progress=true);

/**
  File copy handler to get a file from the PFx Brick.
  
  This function handles the process of opening and transferring
  file data from the PFx Brick file system to the host. A copy session
  may involve many message transactions with the PFx Brick and could
  be time consuming. Therefore, a progress bar can be optionally shown
  on the console to monitor the transfer.
  
  @param dev PFxDev reference containing the USB HID session handle
  @param file a PFxFile object specifying the file to copy
  @param fn optional name to override the filename of the host's copy
  @param show_progress a flag to show the progress bar indicator during transfer
*/
void fs_copy_file_from(PFxDev& dev, PFxFile& file, std::string fn="", bool show_progress=true);

#endif
