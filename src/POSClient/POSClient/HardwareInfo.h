#pragma once
#include <windows.h>
#include <stdio.h>

class HardwareInfo
{
private:
	TCHAR* DWORDToChar (DWORD diskdata [256], int firstIndex, int lastIndex);
	BOOL  ReadPhysicalDriveInNTWithZeroRights(char* serialNumber);
	BOOL  ReadPhysicalDriveInNTUsingSmart(char* serialNumber);
public:
	HardwareInfo(void);
	~HardwareInfo(void);
	CString GetHDSerial();
	CString GetMAC();
	CString GetCPUID();
};