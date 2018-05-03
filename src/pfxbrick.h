#include <string>
#include <vector>
#include <iterator>
#include "hidapi.h"
#include "pfxdev.h"
#include "pfxconfig.h"
#include "pfxfiles.h"
#include "pfxhelpers.h"
#include "pfxaction.h"
#include "pfxmsg.h"

#ifndef pfxbrick_h
#define pfxbrick_h

#define EP_BUFF_LEN 64

/**
  @brief PFx Brick top level class

  This class is used to initialize and maintain a communication session
  with a USB connected PFx Brick. Many convenient methods are provided
  to perform tasks such as changing configuration, accessing the file
  system, initiating actions, and more. 
*/
class PFxBrick
{
public:
  PFxBrick();
  ~PFxBrick();
  PFxBrick (const PFxBrick& withBrick);
  PFxBrick& operator=(const PFxBrick& withBrick);
  
  /* Methods */
/**
    @brief Open a session with a PFx Brick

    Opens a USB communication session with a PFx Brick. If multiple PFx Bricks are
    connected, then a serial number must be specified to connect to a unique PFx Brick.

    @param ser_no: optional serial number to specify a particular PFx Brick if multiple connected
    @returns boolean indicating open session result
*/
  bool open(std::string ser_no);

  /**
    Opens a USB communication session with a single PFx Brick.  This is a 
    convenience method for quickly connecting to the only PFx Brick that
    is currently connected to the host.

    @returns boolean indicating open session result
  */
  bool open(void) { return(open("")); }

  /**
      @brief Closes a session with a PFx Brick

      Closes a USB communication session with a PFx Brick.
  */
  void close();

  /**
      @brief Gets the revision number of ICD the PFx Brick supports

      Requests the version of Interface Control Document (ICD)
      the connected PFx Brick supports using the PFX_CMD_GET_ICD_REV
      ICD message.  The resulting version number is stored in
      this class and also returned.
  
      @param silent flag to optionally silence the status LED blink
  */
  void get_icd_rev(bool silent=false);

  /**
      @brief Gets identity and status info from the PFx Brick

      Requests the top level operational status of the PFx Brick
      using the PFX_CMD_GET_STATUS ICD message.  The resulting
      status data is stored in this class and can be queried
      with typical class member access methods or the print_status method.
  */
  void get_status();

  /**
      @brief Prints the status info retrieved by get_status

      Prints the top level operational status information retrieved
      by a previous call to the get_status method.
  */  
  void print_status();

  /**
      @brief Gets PFx Brick configuration

      Retrieves configuration settings from the PFx Brick using 
      the PFX_CMD_GET_CONFIG ICD message. The configuration data
      is stored in the \a PFxBrick.config class member variable.
  */
  void get_config();

  /**
      @brief Prints the configuration retrieved by get_config

      Prints a summary representation of the PFx Brick configuration
      settings which were retrieved by a previous call to get_config.
  */
  void print_config();

  /**
      @brief Writes new configuration to the PFx Brick
  
      Writes the contents of the PFxConfig data structure class to
      the PFx Brick using the PFX_CMD_SET_CONFIG ICD message.
    
      It is recommended that the configuration be read from the
      PFx Brick (using get_config) before any changes are made to
      the configuration and written back. This ensures that any
      configuration settings which are not desired to be changed
      are left in the same state.
  */  
  void set_config();

  /**
      @brief Gets the user defined name of the PFx Brick

      Retrieves the user defined name of the PFx Brick using 
      the PFX_CMD_GET_NAME ICD message. The name is stored in
      the name class variable as a UTF-8 string.
    
      @returns a string with the user defined name
  */
  void get_name();

  /**
      @brief Sets a new user define PFx Brick name

      Sets the user defined name of the PFx Brick using the
      PFX_CMD_SET_NAME ICD message.
  
      @param name new name to set (up to 24 character bytes, UTF-8)
  */
  void set_name(std::string name);

  /**
      @brief Gets an action data structure by address
  
      Retrieves a stored action indexed by address rather than a
      combination of eventID and IR channel.  The address is converted into a 
      [eventID, IR channel] pair and the get_action method is 
      called with this function as a convenient wrapper.
    
      @param address event/action LUT address (0 - 0x7F)
      @returns PFxAction class filled with retrieved LUT data
  */  
  PFxAction& get_action_by_address(int address);

  /**
    @brief Gets an action data structure by event ID

    Retrieves the stored action associated with a particular
    [eventID / IR channel] event. The eventID and channel value
    form a composite address pointer into the event/action LUT
    in the PFx Brick. The address to the LUT is formed as:
    
    Address[5:2] = event ID
    Address[1:0] = channel
    
    @param evtID event ID LUT address component (0 - 0x20)
    @param channel channel index LUT address component (0 - 3)
    @returns PFxAction class filled with retrieved LUT data
  */
  PFxAction& get_action(int evtID, int ch);

  /**
    @brief Sets an a new action in the event/action LUT by address
  
    Sets a new stored action in the event/action LUT at the
    address specified. The address is converted into a 
    [eventID, IR channel] pair and the set_action method is 
    called with this function as a convenient wrapper.
    
    @param address event/action LUT address (0 - 0x7F)
    @param action PFxAction action data structure class
  */
  void set_action_by_address(int address, const PFxAction& action);

  /**
    @brief Sets a new action in the event/action LUT by event ID

    Sets a new stored action associated with a particular
    [eventID / IR channel] event. The eventID and channel value
    form a composite address pointer into the event/action LUT
    in the PFx Brick. The address to the LUT is formed as:
    
    Address[5:2] = event ID
    Address[1:0] = channel
    
    @param evtID event ID LUT address component (0 - 0x20)
    @param ch channel index LUT address component (0 - 3)
    @param action PFxAction action data structure class
  */
  void set_action(int evtID, int ch, const PFxAction& action);

  /**
    @brief Executes a passed action data structure
  
    Executes a passed action data structure. This function is
    used to "test" actions to see how they behave. The passed
    action is not stored in the event/action LUT.
    
    @param action PFxAction action data structure class
  */
  void test_action(const PFxAction& action);
  
  /**
    @brief Reads the PFx Brick file system directory

    Reads the PFx Brick file system directory. This includes
    the total storage used as well as the remaining capacity.
    Individual file directory entries are stored in the
    PFxBrick.filedir.files class variable.
  */
  void refresh_file_dir();

  /**
    @brief Copies a file to the PFx Brick
  
    Copies a file from the host to the PFx Brick. 
    
    @param fileID the unique file ID to assign the copied file in the file system
    @param fn the filename (optionally including the path) of the file to copy
    @param show_progress a flag to show the progress bar indicator during transfer.
  */
  void put_file(int fileID, char *fn, bool show_progress=true);

  /**
    @brief Copies a file from the PFx Brick
  
    Copies a file from the PFx Brick to the host.
    
    @param fileID the file ID of the file to copy
    @param fn optional override for the filename when copied into the host 
    @param show_progress a flag to show the progress bar indicator during transfer.
  */
  void get_file(int fileID, char *fn, bool show_progress=true);

  /**
    @brief Deletes a file on the PFx Brick file system

    Removes a file from the PFx Brick file system.
    
    @param fileID the file ID of the file to remove
  */
  void remove_file(int fileID);
  
  /**
    @brief Format the PFx Brick file system

    Formats the PFx Brick file system, erasing all files.
    
    @param quick If True, only occupied sectors are erased. If False, every sector is erased, i.e. a complete format.
  */
  void format_fs(bool quick=false);
  
  /**
    @brief Reset PFx Brick to factory default configuration
  
    Resets the PFx Brick configuration settings to factory defaults.
  */
  void reset_factory_config();
  
  /* Variables */
  /** a child class to hold the device handle and data buffers */
  PFxDev dev;
  /** child class to store configuration and settings */
  PFxConfig config;
  /** child class to store the file system directory */
  PFxDir filedir;
  /** product ID code reported by the PFx Brick (e.g. 'A204') */
  std::string product_id;
  /** serial number reported by the PFx Brick, usually 8 digit hexadecimal */
  std::string serial_no;
  /** product descriptor reported by the PFx Brick */
  std::string product_desc;
  /** firmware version number reported
      4-digit hex BCD, e.g. '0134' represents v.1.34 */
  std::string firmware_ver;
  /** firmware build number reported, 4-digit hex BCD */
  std::string firmware_build;
  /** ICD revision number reported
      4-digit hex BCD, e.g. '0336' represents v.3.36 */
  std::string icd_rev;
  /** status code reported, distinguishes normal and service/recovery mode */
  int status;
  /** error code reported */
  int error;
  /** fixed to PFX_USB_VENDOR_ID representing the official USB VID assigned to the PFx Brick */
  int usb_vid;
  /** fixed to PFX_USB_PRODUCT_ID representing the official USB PID assigned to the PFx Brick */
  int usb_pid;
  /** the manufacturer string reported to the host USB interface */
  std::string usb_manu_str;
  /** the product descriptor string reported to the host USB interface */
  std::string usb_prod_str;
  /** the product serial number string reported to the host USB interface */
  std::string usb_serno_str;
  /** a flag indicating connected session status */
  bool is_open;
  /** user defined name of the PFx Brick */
  std::string name;
};

/**
  @brief Enumerates all attached PFx Bricks 

  This function finds all PFx Bricks attached to the current host's
  USB subsystem.  Since all PFx Bricks have unique serial number,
  this function returns a vector string array of the serial numbers
  of discovered PFx Bricks.

  @param show_list optionally specifies that a listing of found PFx Bricks be printed to the console
*/
std::vector<std::string> find_bricks(bool show_list=false);

#endif