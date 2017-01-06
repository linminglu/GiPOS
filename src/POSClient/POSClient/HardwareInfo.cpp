#include "StdAfx.h"
#include "HardwareInfo.h"
#include "WMI_DeviceQuery.h"
#include <winioctl.h>

//  Required to ensure correct PhysicalDrive IOCTL structure setup
#pragma pack(4)
//
// IOCTL_STORAGE_QUERY_PROPERTY
//
// Input Buffer:
//      a STORAGE_PROPERTY_QUERY structure which describes what type of query
//      is being done, what property is being queried for, and any additional
//      parameters which a particular property query requires.
//
//  Output Buffer:
//      Contains a buffer to place the results of the query into.  Since all
//      property descriptors can be cast into a STORAGE_DESCRIPTOR_HEADER,
//      the IOCTL can be called once with a small buffer then again using
//      a buffer as large as the header reports is necessary.
//


//
// Types of queries
//

typedef enum _STORAGE_QUERY_TYPE {
    PropertyStandardQuery = 0,          // Retrieves the descriptor
    PropertyExistsQuery,                // Used to test whether the descriptor is supported
    PropertyMaskQuery,                  // Used to retrieve a mask of writeable fields in the descriptor
    PropertyQueryMaxDefined     // use to validate the value
} STORAGE_QUERY_TYPE, *PSTORAGE_QUERY_TYPE;

//
// define some initial property id's
//

typedef enum _STORAGE_PROPERTY_ID {
    StorageDeviceProperty = 0,
    StorageAdapterProperty
} STORAGE_PROPERTY_ID, *PSTORAGE_PROPERTY_ID;

//
// Query structure - additional parameters for specific queries can follow
// the header
//

typedef struct _STORAGE_PROPERTY_QUERY {

    //
    // ID of the property being retrieved
    //

    STORAGE_PROPERTY_ID PropertyId;

    //
    // Flags indicating the type of query being performed
    //

    STORAGE_QUERY_TYPE QueryType;

    //
    // Space for additional parameters if necessary
    //

    UCHAR AdditionalParameters[1];

} STORAGE_PROPERTY_QUERY, *PSTORAGE_PROPERTY_QUERY;


#define IOCTL_STORAGE_QUERY_PROPERTY   CTL_CODE(IOCTL_STORAGE_BASE, 0x0500, METHOD_BUFFERED, FILE_ANY_ACCESS)
//
// Device property descriptor - this is really just a rehash of the inquiry
// data retrieved from a scsi device
//
// This may only be retrieved from a target device.  Sending this to the bus
// will result in an error
//

#pragma pack(4)

typedef struct _STORAGE_DEVICE_DESCRIPTOR {

    //
    // Sizeof(STORAGE_DEVICE_DESCRIPTOR)
    //

    ULONG Version;

    //
    // Total size of the descriptor, including the space for additional
    // data and id strings
    //

    ULONG Size;

    //
    // The SCSI-2 device type
    //

    UCHAR DeviceType;

    //
    // The SCSI-2 device type modifier (if any) - this may be zero
    //

    UCHAR DeviceTypeModifier;

    //
    // Flag indicating whether the device's media (if any) is removable.  This
    // field should be ignored for media-less devices
    //

    BOOLEAN RemovableMedia;

    //
    // Flag indicating whether the device can support mulitple outstanding
    // commands.  The actual synchronization in this case is the responsibility
    // of the port driver.
    //

    BOOLEAN CommandQueueing;

    //
    // Byte offset to the zero-terminated ascii string containing the device's
    // vendor id string.  For devices with no such ID this will be zero
    //

    ULONG VendorIdOffset;

    //
    // Byte offset to the zero-terminated ascii string containing the device's
    // product id string.  For devices with no such ID this will be zero
    //

    ULONG ProductIdOffset;

    //
    // Byte offset to the zero-terminated ascii string containing the device's
    // product revision string.  For devices with no such string this will be
    // zero
    //

    ULONG ProductRevisionOffset;

    //
    // Byte offset to the zero-terminated ascii string containing the device's
    // serial number.  For devices with no serial number this will be zero
    //

    ULONG SerialNumberOffset;

    //
    // Contains the bus type (as defined above) of the device.  It should be
    // used to interpret the raw device properties at the end of this structure
    // (if any)
    //

    STORAGE_BUS_TYPE BusType;

    //
    // The number of bytes of bus-specific data which have been appended to
    // this descriptor
    //

    ULONG RawPropertiesLength;

    //
    // Place holder for the first byte of the bus specific property data
    //

    UCHAR RawDeviceProperties[1];

} STORAGE_DEVICE_DESCRIPTOR, *PSTORAGE_DEVICE_DESCRIPTOR;
//  function to decode the serial numbers of IDE hard drives
	//  using the IOCTL_STORAGE_QUERY_PROPERTY command 
char * flipAndCodeBytes (const char * str,
			 int pos,
			 int flip,
			 char * buf)
{
   int i;
   int j = 0;
   int k = 0;

   buf [0] = '\0';
   if (pos <= 0)
      return buf;

   if ( ! j)
   {
      char p = 0;

      // First try to gather all characters representing hex digits only.
      j = 1;
      k = 0;
      buf[k] = 0;
      for (i = pos; j && str[i] != '\0'; ++i)
      {
	 char c = tolower(str[i]);

	 if (isspace(c))
	    c = '0';

	 ++p;
	 buf[k] <<= 4;

	 if (c >= '0' && c <= '9')
	    buf[k] |= (unsigned char) (c - '0');
	 else if (c >= 'a' && c <= 'f')
	    buf[k] |= (unsigned char) (c - 'a' + 10);
	 else
	 {
	    j = 0;
	    break;
	 }

	 if (p == 2)
	 {
	    if (buf[k] != '\0' && ! isprint(buf[k]))
	    {
	       j = 0;
	       break;
	    }
	    ++k;
	    p = 0;
	    buf[k] = 0;
	 }

      }
   }

   if ( ! j)
   {
      // There are non-digit characters, gather them as is.
      j = 1;
      k = 0;
      for (i = pos; j && str[i] != '\0'; ++i)
      {
	     char c = str[i];

	     if ( ! isprint(c))
	     {
	        j = 0;
	        break;
	     }

	     buf[k++] = c;
      }
   }

   if ( ! j)
   {
      // The characters are not there or are not printable.
      k = 0;
   }

   buf[k] = '\0';

   if (flip)
      // Flip adjacent characters
      for (j = 0; j < k; j += 2)
      {
	     char t = buf[j];
	     buf[j] = buf[j + 1];
	     buf[j + 1] = t;
      }

   // Trim any beginning and end space
   i = j = -1;
   for (k = 0; buf[k] != '\0'; ++k)
   {
      if (! isspace(buf[k]))
      {
	     if (i < 0)
	        i = k;
	     j = k;
      }
   }

   if ((i >= 0) && (j >= 0))
   {
      for (k = i; (k <= j) && (buf[k] != '\0'); ++k)
         buf[k - i] = buf[k];
      buf[k - i] = '\0';
   }

   return buf;
}

#define IOCTL_DISK_GET_DRIVE_GEOMETRY_EX CTL_CODE(IOCTL_DISK_BASE, 0x0028, METHOD_BUFFERED, FILE_ANY_ACCESS)




HardwareInfo::HardwareInfo()
{
}
HardwareInfo::~HardwareInfo()
{
}

// Windows NT/2000/XP下读取硬盘序列号
BOOL HardwareInfo::ReadPhysicalDriveInNTWithZeroRights(char* serialNumber)
{
   BOOL bFlag = FALSE;
   int  drive = 0;
   TCHAR driveName [256];
   HANDLE hPhysicalDriveIOCTL = 0;    
      
   wsprintf(driveName, _T("\\\\.\\PhysicalDrive%d"), drive);
  //  Windows NT, Windows 2000, Windows XP - admin rights not required
   hPhysicalDriveIOCTL = CreateFile(driveName, 0,
                               FILE_SHARE_READ | FILE_SHARE_WRITE, NULL,
                               OPEN_EXISTING, 0, NULL);
   if (hPhysicalDriveIOCTL != INVALID_HANDLE_VALUE)
   {
		 STORAGE_PROPERTY_QUERY query;
         DWORD cbBytesReturned = 0;
		 char buffer [10000];

         memset ((void *) & query, 0, sizeof (query));
		 query.PropertyId = StorageDeviceProperty;
		 query.QueryType = PropertyStandardQuery;

		 memset (buffer, 0, sizeof (buffer));

         if ( DeviceIoControl (hPhysicalDriveIOCTL, IOCTL_STORAGE_QUERY_PROPERTY,
                   & query,
                   sizeof (query),
				   & buffer,
				   sizeof (buffer),
                   & cbBytesReturned, NULL) )
         {
			 STORAGE_DEVICE_DESCRIPTOR * descrip = (STORAGE_DEVICE_DESCRIPTOR *) & buffer;
	         flipAndCodeBytes (buffer,
			                   descrip -> SerialNumberOffset,
			                   1, serialNumber );
			bFlag=TRUE;
		}
		CloseHandle (hPhysicalDriveIOCTL);  // 关闭句柄
   }
   return bFlag;
}
//
// IDENTIFY data (from ATAPI driver source)
//

#pragma pack(1)

typedef struct _IDENTIFY_DATA {
    USHORT GeneralConfiguration;            // 00 00
    USHORT NumberOfCylinders;               // 02  1
    USHORT Reserved1;                       // 04  2
    USHORT NumberOfHeads;                   // 06  3
    USHORT UnformattedBytesPerTrack;        // 08  4
    USHORT UnformattedBytesPerSector;       // 0A  5
    USHORT SectorsPerTrack;                 // 0C  6
    USHORT VendorUnique1[3];                // 0E  7-9
    USHORT SerialNumber[10];                // 14  10-19
    USHORT BufferType;                      // 28  20
    USHORT BufferSectorSize;                // 2A  21
    USHORT NumberOfEccBytes;                // 2C  22
    USHORT FirmwareRevision[4];             // 2E  23-26
    USHORT ModelNumber[20];                 // 36  27-46
    UCHAR  MaximumBlockTransfer;            // 5E  47
    UCHAR  VendorUnique2;                   // 5F
    USHORT DoubleWordIo;                    // 60  48
    USHORT Capabilities;                    // 62  49
    USHORT Reserved2;                       // 64  50
    UCHAR  VendorUnique3;                   // 66  51
    UCHAR  PioCycleTimingMode;              // 67
    UCHAR  VendorUnique4;                   // 68  52
    UCHAR  DmaCycleTimingMode;              // 69
    USHORT TranslationFieldsValid:1;        // 6A  53
    USHORT Reserved3:15;
    USHORT NumberOfCurrentCylinders;        // 6C  54
    USHORT NumberOfCurrentHeads;            // 6E  55
    USHORT CurrentSectorsPerTrack;          // 70  56
    ULONG  CurrentSectorCapacity;           // 72  57-58
    USHORT CurrentMultiSectorSetting;       //     59
    ULONG  UserAddressableSectors;          //     60-61
    USHORT SingleWordDMASupport : 8;        //     62
    USHORT SingleWordDMAActive : 8;
    USHORT MultiWordDMASupport : 8;         //     63
    USHORT MultiWordDMAActive : 8;
    USHORT AdvancedPIOModes : 8;            //     64
    USHORT Reserved4 : 8;
    USHORT MinimumMWXferCycleTime;          //     65
    USHORT RecommendedMWXferCycleTime;      //     66
    USHORT MinimumPIOCycleTime;             //     67
    USHORT MinimumPIOCycleTimeIORDY;        //     68
    USHORT Reserved5[2];                    //     69-70
    USHORT ReleaseTimeOverlapped;           //     71
    USHORT ReleaseTimeServiceCommand;       //     72
    USHORT MajorRevision;                   //     73
    USHORT MinorRevision;                   //     74
    USHORT Reserved6[50];                   //     75-126
    USHORT SpecialFunctionsEnabled;         //     127
    USHORT Reserved7[128];                  //     128-255
} IDENTIFY_DATA, *PIDENTIFY_DATA;
char *ConvertToString (DWORD diskdata [256],
		       int firstIndex,
		       int lastIndex,
		       char* buf)
{
   int index = 0;
   int position = 0;

      //  each integer has two characters stored in it backwards
   for (index = firstIndex; index <= lastIndex; index++)
   {
         //  get high byte for 1st character
      buf [position++] = (char) (diskdata [index] / 256);

         //  get low byte for 2nd character
      buf [position++] = (char) (diskdata [index] % 256);
   }

      //  end the string 
   buf[position] = '\0';

      //  cut off the trailing blanks
   for (index = position - 1; index > 0 && isspace(buf [index]); index--)
      buf [index] = '\0';

   return buf;
}
int HardwareInfo::ReadPhysicalDriveInNTUsingSmart (char* serialNumber)
{
	int done = FALSE;
	int drive = 0;
	TCHAR driveName [256];
    HANDLE hPhysicalDriveIOCTL = 0;    
      
   wsprintf(driveName, _T("\\\\.\\PhysicalDrive%d"), drive);

	//  Windows NT, Windows 2000, Windows Server 2003, Vista
	hPhysicalDriveIOCTL = CreateFile(driveName,
		GENERIC_READ | GENERIC_WRITE, 
		FILE_SHARE_DELETE | FILE_SHARE_READ | FILE_SHARE_WRITE, 
		NULL, OPEN_EXISTING, 0, NULL);
	// if (hPhysicalDriveIOCTL == INVALID_HANDLE_VALUE)
	//    printf ("Unable to open physical drive %d, error code: 0x%lX\n",
	//            drive, GetLastError ());

	if (hPhysicalDriveIOCTL != INVALID_HANDLE_VALUE)
	{
		GETVERSIONINPARAMS GetVersionParams;
		DWORD cbBytesReturned = 0;

		// Get the version, etc of PhysicalDrive IOCTL
		memset ((void*) & GetVersionParams, 0, sizeof(GetVersionParams));

		if (DeviceIoControl (hPhysicalDriveIOCTL, SMART_GET_VERSION,
			NULL, 
			0,
			&GetVersionParams, sizeof (GETVERSIONINPARAMS),
			&cbBytesReturned, NULL) )
		{
			// Print the SMART version
			// PrintVersion (& GetVersionParams);
			// Allocate the command buffer
			ULONG CommandSize = sizeof(SENDCMDINPARAMS) + IDENTIFY_BUFFER_SIZE;
			PSENDCMDINPARAMS Command = (PSENDCMDINPARAMS) malloc (CommandSize);
			// Retrieve the IDENTIFY data
			// Prepare the command
#define ID_CMD          0xEC            // Returns ID sector for ATA
			Command -> irDriveRegs.bCommandReg = ID_CMD;
			DWORD BytesReturned = 0;
			if ( ! DeviceIoControl (hPhysicalDriveIOCTL, 
				SMART_RCV_DRIVE_DATA, Command, sizeof(SENDCMDINPARAMS),
				Command, CommandSize,
				&BytesReturned, NULL) )
			{
				// Print the error
				//PrintError ("SMART_RCV_DRIVE_DATA IOCTL", GetLastError());
			} 
			else
			{
				// Print the IDENTIFY data
				DWORD diskdata [256];
				USHORT *pIdSector = (USHORT *)
					(PIDENTIFY_DATA) ((PSENDCMDOUTPARAMS) Command) -> bBuffer;

				for (int ijk = 0; ijk < 256; ijk++)
					diskdata [ijk] = pIdSector [ijk];

				ConvertToString (diskdata, 10, 19, serialNumber);
				done = TRUE;
			}
			// Done
			CloseHandle (hPhysicalDriveIOCTL);
			free (Command);
		}
	}
	return done;
}

// 读取硬盘序列号函数
CString HardwareInfo::GetHDSerial()
{
	CString strResult=_T("");
	char serialNumber [512]={0};
	OSVERSIONINFO versionInfo;
	versionInfo.dwOSVersionInfoSize = sizeof (OSVERSIONINFO);
	if (::GetVersionEx(&versionInfo))
	{
		if (versionInfo.dwMajorVersion>=6)
		{//vista or later
			T_DEVICE_PROPERTY proper={0};
			int r=WMI_DeviceQuery(1,&proper,1);
			strResult.Format(_T("%s"),proper.szProperty);
			strResult.Remove(' ');
		}
	}
	if(strResult.IsEmpty())
	{
		//  this works under WinNT4 or Win2K or WinXP if you have any rights
		ReadPhysicalDriveInNTWithZeroRights(serialNumber);
		//  this works under WinNT4 or Win2K or WinXP or Windows Server 2003 or Vista if you have any rights
		if(serialNumber[0]==0)//try smart
			ReadPhysicalDriveInNTUsingSmart(serialNumber);
		strResult=serialNumber;	
		strResult.Remove(' ');
	}
	strResult=strResult.Right(8);//仅保留8位
	return strResult;
}
// Windows NT/2000/XP系统下，将双字类型（DWORD）的硬盘信息转换为字符类型（char）
TCHAR* HardwareInfo::DWORDToChar (DWORD diskdata [256], int firstIndex, int lastIndex)
{
   static TCHAR string [1024];
   int index = 0;
   int position = 0;

   // 按照高字节在前，低字节在后的顺序将双字中的低字存入到字符串string中 
   for (index = firstIndex; index <= lastIndex; index++)
   {
      // 存入低字中的高字节
      string [position] = (TCHAR) (diskdata [index] / 256);
      position++;
      // 存入低字中的低字节
      string [position] = (TCHAR) (diskdata [index] % 256);
      position++;
   }
   //  添加字符串结束标志
   string [position] = '\0';

   //  删除字符串中空格
   for (index = position - 1; index > 0 && ' ' == string [index]; index--)
      string [index] = '\0';
   return string;
}
CString HardwareInfo::GetMAC()
{
	CString strMac=L"";
	T_DEVICE_PROPERTY proper={0};
	WMI_DeviceQuery(0,&proper,1);
	strMac.Format(_T("%s"),proper.szProperty);
	return strMac;
}


CString HardwareInfo::GetCPUID()
{
 	CString   CPUID; 
	unsigned   long   s1,s2;   
	__asm{   
		mov   eax,01h   
		xor   edx,edx   
		cpuid   
		mov   s1,edx   
		mov   s2,eax   
	}   
	CPUID.Format(_T("%06X"),s2);
	return   CPUID;
}