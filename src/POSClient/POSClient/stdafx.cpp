// stdafx.cpp : 只包括标准包含文件的源文件
// POSClient.pch 将作为预编译头
// stdafx.obj 将包含预编译类型信息

#include "stdafx.h"

#ifdef _DEBUG
#pragma comment(lib,"log4cplusUD.lib")
#pragma comment(lib,"LicenseLibD.lib")
#pragma comment(lib,"ZipArchiveD.lib")

#else
#pragma comment(lib,"log4cplusU.lib")
#pragma comment(lib,"LicenseLib.lib")
#pragma comment(lib,"ZipArchive.lib")
#endif

#pragma comment(lib,"odbc32.lib")
#pragma comment(lib,"version.lib")
#pragma comment(lib,"Imm32.lib")
#pragma comment(lib,"libcef.lib")
#pragma comment(lib,"libcef_dll_wrapper.lib")
//#pragma comment(lib,"Rockey3.lib")
#pragma comment (linker,"/NODEFAULTLIB:libc.lib")
