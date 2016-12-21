
/*******************************************************************************
* Includes
******************************************************************************/
#include "stdafx.h"
#include "ESCPrinter.h"
#include "POSClient.h"
#include <atlimage.h>
#include <Winsock2.h>
#include <setupapi.h>
#include <devguid.h>
#pragma comment(lib,"Setupapi.lib")
/*******************************************************************************
* Methods
******************************************************************************/
ESCPrinter::ESCPrinter()
{
	m_logpix=180;
	g_hComm	= INVALID_HANDLE_VALUE;//端口句柄
	m_nPaperWidth=80;
	last_size=-1;
	last_style=-1;
	last_align=-1;
}

ESCPrinter::~ESCPrinter()
{
}

BOOL ESCPrinter::Print(LPCTSTR lpchText,PrintItemCfg& cfg)
{
	try{
		if (cfg.align!=last_align)
		{
			last_align=cfg.align;
			setAlign(cfg.align);
		}
		if(cfg.size!=last_size)
		{
			last_size=cfg.size;
			if (cfg.size==2)
			{//倍高宽
				setCharacterSize(BaseCodes::MAGNIFICATION_2X,BaseCodes::MAGNIFICATION_2X);
			}
			else if(cfg.size==3)
			{//倍高
				setCharacterSize(BaseCodes::MAGNIFICATION_1X,BaseCodes::MAGNIFICATION_2X);
			}else if (cfg.size==4)
			{//倍宽
				setCharacterSize(BaseCodes::MAGNIFICATION_2X,BaseCodes::MAGNIFICATION_1X);
			}else if(cfg.size>5)
			{//兼容绘图模式下的字体(9为标准，18为双倍)
				if(cfg.size<=14)
					setCharacterSize(BaseCodes::MAGNIFICATION_1X,BaseCodes::MAGNIFICATION_1X);
				else if(cfg.size>=18)//倍高宽
					setCharacterSize(BaseCodes::MAGNIFICATION_2X,BaseCodes::MAGNIFICATION_2X);
				else//倍高
					setCharacterSize(BaseCodes::MAGNIFICATION_1X,BaseCodes::MAGNIFICATION_2X);
			}
			else
			{//正常大小
				setCharacterSize(BaseCodes::MAGNIFICATION_1X,BaseCodes::MAGNIFICATION_1X);
			}
			
		}
		if(last_style!= cfg.style)
		{
			last_style= cfg.style;
			if(cfg.style==0)
			{
				setEmphasis(false);
				setUnderline(BaseCodes::UNDERLINE_OFF);
			}
			if(cfg.style&POS_FONT_STYLE_BOLD)
			{
				setEmphasis(true);
			}
			if(cfg.style&POS_FONT_STYLE_UNDERLINE)
			{
				setUnderline(BaseCodes::UNDERLINE_NORMAL);
			}
			
		}
		if(cfg.left>0)
			setAbusoluteLeft(cfg.left);
		return Print(UnicodeToANSI(lpchText));
	}catch(...)
	{
		LOG4CPLUS_ERROR(log_pos,"Catch Exception GetLastError="<<GetLastError());
	}
	return FALSE;
}
BOOL ESCPrinter::Print(char* data)
{
	DWORD iBytesLength;
	return WriteFile(g_hComm, data, (DWORD)strlen(data), &iBytesLength, NULL);
}
int ESCPrinter::OpenPrinterDev(LPCTSTR wPrinterName,int type,
								int nComBaudrate,int nComDataBits,
								int nComStopBits, int nComParity)
{
	USES_CONVERSION;
	try{
		BOOL bCheckStatus=TRUE;
		m_printType=type;
		if (type == PRINTER_TYPE_COM||type==PRINTER_TYPE_LPT)//并口\串口
		{
			g_hComm = CreateFile(wPrinterName, GENERIC_READ | GENERIC_WRITE,
				0, NULL, 
				OPEN_EXISTING,
				FILE_ATTRIBUTE_NORMAL, NULL );

			if (g_hComm == INVALID_HANDLE_VALUE)
			{
				LOG4CPLUS_ERROR(log_pos,"Open COM failed! GetLastError="<<GetLastError());
				return PRINT_ERROR_OPENFAIL;
			}

			SetupComm(g_hComm, 1024, 1024);//设置端口缓冲

			COMMTIMEOUTS TimeOuts;
			TimeOuts.ReadIntervalTimeout = MAXDWORD;
			TimeOuts.ReadTotalTimeoutMultiplier = 0;
			TimeOuts.ReadTotalTimeoutConstant = 500;
			TimeOuts.WriteTotalTimeoutMultiplier = 50;
			TimeOuts.WriteTotalTimeoutConstant = 2000;
			SetCommTimeouts(g_hComm, &TimeOuts);		//设置超时控制
			DCB dcb;
			GetCommState(g_hComm, &dcb);	//获得当前串口配置

			dcb.BaudRate = nComBaudrate;			//设置波特率
			dcb.Parity = nComParity;				//校验, 无
			dcb.ByteSize = nComDataBits;			//数据位, 8bit
			dcb.StopBits = nComStopBits;			//停止位, 1位

			SetCommState(g_hComm, &dcb);	//配置串口
			PurgeComm(g_hComm, PURGE_TXCLEAR);

		}
		else if(type == PRINTER_TYPE_USB)//USB
		{
			GUID USB_Device_GUID = { 0xA5DCBF10L, 0x6530, 0x11D2, { 0x90, 0x1F, 0x00, 0xC0, 0x4F, 0xB9, 0x51, 0xED } };
			SP_DEVICE_INTERFACE_DATA  DeviceInterfaceData;

			HDEVINFO hDevInfo = SetupDiGetClassDevs( &USB_Device_GUID, NULL, NULL, DIGCF_PRESENT | DIGCF_DEVICEINTERFACE );
			if( INVALID_HANDLE_VALUE == hDevInfo )
			{
				return PRINT_ERROR_OPENFAIL;
			}
			DeviceInterfaceData.cbSize=sizeof(SP_DEVICE_INTERFACE_DATA);
			DeviceInterfaceData.Flags = 0;
			ULONG requiredLength = 0;
			int iCount = 0;
			while (SetupDiEnumDeviceInterfaces(hDevInfo, NULL,&USB_Device_GUID, iCount, &DeviceInterfaceData) )
			{
				iCount++;
				SP_DEVINFO_DATA devinfo;
				SetupDiGetInterfaceDeviceDetail(hDevInfo, &DeviceInterfaceData, NULL, 0, &requiredLength, NULL);
				ULONG predictedLength=requiredLength;
				devinfo.cbSize = sizeof (SP_DEVINFO_DATA);
				PSP_DEVICE_INTERFACE_DETAIL_DATA DeviceInterfaceDetailData = (PSP_DEVICE_INTERFACE_DETAIL_DATA)malloc(requiredLength);
				DeviceInterfaceDetailData->cbSize = sizeof (SP_DEVICE_INTERFACE_DETAIL_DATA);
				if (!SetupDiGetInterfaceDeviceDetail(hDevInfo, &DeviceInterfaceData, DeviceInterfaceDetailData, predictedLength, 0, &devinfo))
				{
					free(DeviceInterfaceDetailData);
					SetupDiDestroyDeviceInfoList(hDevInfo);
					return PRINT_ERROR_OPENFAIL;
				}
				DWORD dataType;
				TCHAR serviceName[32]={0};
				if (!SetupDiGetDeviceRegistryProperty(hDevInfo, &devinfo, SPDRP_SERVICE, &dataType, (LPBYTE)serviceName, predictedLength, 0))
				{
					free(DeviceInterfaceDetailData);
					continue;
				}
				_wcslwr_s(serviceName);
				if (wcsstr(serviceName, _T("usbprint")) != NULL)
				{
					g_hComm = CreateFile(DeviceInterfaceDetailData->DevicePath, GENERIC_READ | GENERIC_WRITE,
						0, NULL,
						OPEN_EXISTING,
						FILE_ATTRIBUTE_NORMAL, NULL );
					free(DeviceInterfaceDetailData);
					if (g_hComm == INVALID_HANDLE_VALUE)
					{
						LOG4CPLUS_ERROR(log_pos,"Open USB failed! GetLastError="<<GetLastError());
						return PRINT_ERROR_OPENFAIL;
					}
					bCheckStatus=FALSE;//USB不检查状态
					break;
				}
				free(DeviceInterfaceDetailData);
			}
			SetupDiDestroyDeviceInfoList(hDevInfo);
		}
		else if(type == PRINTER_TYPE_IP)//网络接口:IP地址
		{
			SOCKET sock=WSASocket(AF_INET,SOCK_STREAM, 0, NULL, 0, 0);//socket(AF_INET,SOCK_STREAM,0); 
			SOCKADDR_IN   addrSrv; 
			addrSrv.sin_addr.S_un.S_addr=inet_addr(W2A(wPrinterName)); 
			addrSrv.sin_family=AF_INET;
			int port=nComBaudrate;
			if(port<=0)
				port=9100;
			addrSrv.sin_port=htons(port);
			if(connect(sock,(SOCKADDR*)&addrSrv,sizeof(SOCKADDR))!=0)
				return PRINT_ERROR_NETFAIL;
			g_hComm=(HANDLE)sock;
			bCheckStatus=FALSE;//58打印机不支持
		}
		else
		{//不支持
			return PRINT_ERROR_OTHER;
		}
		//检测状态
		if(bCheckStatus)
		{
			queryStatus(2);
			int nFailed=0;
			BYTE buffer=0;
			DWORD readed;
			ReadFile(g_hComm,&buffer,1,&readed,NULL);
			if(buffer==0)
			{//读取超时
				//nFailed=1;
			}else if((buffer&0x04)>0)
			{//上盖打开
				nFailed=PRINT_ERROR_COVEOPEN;
			}else if((buffer&0x20)>0)
			{// 缺纸
				nFailed=PRINT_ERROR_PAPEROUT;
			}else if((buffer&0x40)>0)
			{// 错误
				nFailed=PRINT_ERROR_ERRO;
			}
			if(nFailed>1){
				ClosePrinterDev();
				return nFailed;
			}
		}
		initialize();
		if(m_nPaperWidth==40)
			setLineSpacing(0);
		else if(m_nPaperWidth==76)
			setLineSpacing(20);
		else
			setLineSpacing(30);
		return 0;

	}catch(...)
	{
		LOG4CPLUS_ERROR(log_pos,"Catch Exception GetLastError="<<GetLastError());
	}
	return PRINT_ERROR_OTHER;
}
void ESCPrinter::CutPaper()
{
	cutPaper(BaseCodes::CUT_PARTIAL,1);
	//蜂鸣响，"ESC BEL"
	//char chQueryCode2[] = "\x1B\x42\x03\x01";
	//VC_POS_WriteFile(g_hComm, chQueryCode2, (DWORD)4L);
}
BOOL ESCPrinter::ClosePrinterDev()
{
	if(g_hComm != INVALID_HANDLE_VALUE)
	{
		try
		{
			if(m_printType==3)
			{
				closesocket((SOCKET)g_hComm);
			}
			else
			{
				if(!CloseHandle(g_hComm))
					return FALSE;
			}
			g_hComm = INVALID_HANDLE_VALUE;
		}
		catch (CException* e)
		{
			LOG4CPLUS_DEBUG(log_pos,"CloseHandle Exception");
		}
	}
	return TRUE;
}


std::size_t ESCPrinter::writeBytes(const byte* buffer, std::size_t size)
{
	//USB设备缺纸时会导致阻塞,但是并不影响
	DWORD iBytesLength;
	WriteFile(g_hComm, buffer, (DWORD)size, &iBytesLength, NULL);
	return iBytesLength;
}
/************************************************************************
物理单位(mm)转为逻辑的像素
************************************************************************/
int ESCPrinter::Phy2LogicPix(int phypix)
{
	return (phypix*m_logpix)/25.4;
}
// Gamma 2.2 lookup table
const unsigned char GAMMA_22[256] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x02, 0x02, 0x02,
	0x02, 0x02, 0x03, 0x03, 0x03, 0x03, 0x03, 0x04, 0x04, 0x04, 0x04, 0x05, 0x05, 0x05, 0x05, 0x06,
	0x06, 0x06, 0x07, 0x07, 0x07, 0x08, 0x08, 0x08, 0x09, 0x09, 0x09, 0x0a, 0x0a, 0x0a, 0x0b, 0x0b,
	0x0c, 0x0c, 0x0d, 0x0d, 0x0d, 0x0e, 0x0e, 0x0f, 0x0f, 0x10, 0x10, 0x11, 0x11, 0x12, 0x12, 0x13,
	0x13, 0x14, 0x15, 0x15, 0x16, 0x16, 0x17, 0x17, 0x18, 0x19, 0x19, 0x1a, 0x1b, 0x1b, 0x1c, 0x1d,
	0x1d, 0x1e, 0x1f, 0x1f, 0x20, 0x21, 0x21, 0x22, 0x23, 0x24, 0x24, 0x25, 0x26, 0x27, 0x28, 0x28,
	0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x2d, 0x2e, 0x2f, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37,
	0x37, 0x38, 0x39, 0x3a, 0x3b, 0x3c, 0x3d, 0x3e, 0x3f, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47,
	0x48, 0x49, 0x4a, 0x4b, 0x4d, 0x4e, 0x4f, 0x50, 0x51, 0x52, 0x54, 0x55, 0x56, 0x57, 0x58, 0x5a,
	0x5b, 0x5c, 0x5d, 0x5f, 0x60, 0x61, 0x63, 0x64, 0x65, 0x67, 0x68, 0x69, 0x6b, 0x6c, 0x6d, 0x6f,
	0x70, 0x72, 0x73, 0x75, 0x76, 0x77, 0x79, 0x7a, 0x7c, 0x7d, 0x7f, 0x80, 0x82, 0x83, 0x85, 0x87,
	0x88, 0x8a, 0x8b, 0x8d, 0x8e, 0x90, 0x92, 0x93, 0x95, 0x97, 0x98, 0x9a, 0x9c, 0x9d, 0x9f, 0xa1,
	0xa2, 0xa4, 0xa6, 0xa8, 0xa9, 0xab, 0xad, 0xaf, 0xb0, 0xb2, 0xb4, 0xb6, 0xb8, 0xba, 0xbb, 0xbd, 
	0xbf, 0xc1, 0xc3, 0xc5, 0xc7, 0xc9, 0xcb, 0xcd, 0xcf, 0xd1, 0xd3, 0xd5, 0xd7, 0xd9, 0xdb, 0xdd,
	0xdf, 0xe1, 0xe3, 0xe5, 0xe7, 0xe9, 0xeb, 0xed, 0xef, 0xf1, 0xf4, 0xf6, 0xf8, 0xfa, 0xfc, 0xff
};

// Lightness lookup table
const unsigned char LIGHTNESS[256] = {
	0x00, 0x05, 0x11, 0x1a, 0x21, 0x26, 0x2b, 0x30, 0x34, 0x38, 0x3b, 0x3e, 0x41, 0x44, 0x47, 0x4a,
	0x4c, 0x4f, 0x51, 0x53, 0x55, 0x57, 0x59, 0x5b, 0x5d, 0x5f, 0x61, 0x63, 0x64, 0x66, 0x68, 0x69,
	0x6b, 0x6c, 0x6e, 0x6f, 0x71, 0x72, 0x74, 0x75, 0x76, 0x78, 0x79, 0x7a, 0x7b, 0x7d, 0x7e, 0x7f,
	0x80, 0x81, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90,
	0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98, 0x99, 0x9a, 0x9b, 0x9b, 0x9c, 0x9d, 0x9e, 0x9f,
	0xa0, 0xa1, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xa9, 0xaa, 0xab, 0xac,
	0xac, 0xad, 0xae, 0xae, 0xaf, 0xb0, 0xb1, 0xb1, 0xb2, 0xb3, 0xb3, 0xb4, 0xb5, 0xb6, 0xb6, 0xb7,
	0xb8, 0xb8, 0xb9, 0xba, 0xba, 0xbb, 0xbb, 0xbc, 0xbd, 0xbd, 0xbe, 0xbf, 0xbf, 0xc0, 0xc1, 0xc1,
	0xc2, 0xc2, 0xc3, 0xc4, 0xc4, 0xc5, 0xc5, 0xc6, 0xc7, 0xc7, 0xc8, 0xc8, 0xc9, 0xc9, 0xca, 0xcb,
	0xcb, 0xcc, 0xcc, 0xcd, 0xcd, 0xce, 0xcf, 0xcf, 0xd0, 0xd0, 0xd1, 0xd1, 0xd2, 0xd2, 0xd3, 0xd3,
	0xd4, 0xd4, 0xd5, 0xd6, 0xd6, 0xd7, 0xd7, 0xd8, 0xd8, 0xd9, 0xd9, 0xda, 0xda, 0xdb, 0xdb, 0xdc,
	0xdc, 0xdd, 0xdd, 0xde, 0xde, 0xdf, 0xdf, 0xe0, 0xe0, 0xe0, 0xe1, 0xe1, 0xe2, 0xe2, 0xe3, 0xe3,
	0xe4, 0xe4, 0xe5, 0xe5, 0xe6, 0xe6, 0xe7, 0xe7, 0xe7, 0xe8, 0xe8, 0xe9, 0xe9, 0xea, 0xea, 0xeb,
	0xeb, 0xec, 0xec, 0xec, 0xed, 0xed, 0xee, 0xee, 0xef, 0xef, 0xef, 0xf0, 0xf0, 0xf1, 0xf1, 0xf2,
	0xf2, 0xf2, 0xf3, 0xf3, 0xf4, 0xf4, 0xf4, 0xf5, 0xf5, 0xf6, 0xf6, 0xf7, 0xf7, 0xf7, 0xf8, 0xf8,
	0xf9, 0xf9, 0xf9, 0xfa, 0xfa, 0xfb, 0xfb, 0xfb, 0xfc, 0xfc, 0xfd, 0xfd, 0xfd, 0xfe, 0xfe, 0xff
};
// keeps value in the <min; max> interval
inline int rebound(const int value, const int min, const int max) {
	int a = value;
	if (a > max) {
		a = max;
	}
	else if (a < min) {
		a = min;
	}
	return a;
}

void Img2BW(CImage& img,byte* img_grey,int& threshold)
{
	int img_w=img.GetWidth();
	int img_h=img.GetHeight();
	unsigned int histogram[256] = {0};
	// convert RGBA to greyscale
	const unsigned int img_grey_size = img_h * img_w;
	for(int x=0;x<img_w;x++)
	{
		for(int y=0;y<img_h;y++)
		{
			COLORREF dot=img.GetPixel(x,y);
			// RGB → R'G'B'
			const unsigned int r_ = GAMMA_22[GetRValue(dot)];
			const unsigned int g_ = GAMMA_22[GetGValue(dot)];
			const unsigned int b_ = GAMMA_22[GetBValue(dot)];
			// R'G'B' → luma Y' (!= luminance), ITU-R: BT.709
			const unsigned int y_ = (55 * r_ + 182 * g_ + 18 * b_) / 255;
			// Y' → lightness L*
			int i=x+y*img_h;
			img_grey[i] = LIGHTNESS[y_];
			// prepare a histogram for HEA
			++histogram[img_grey[i]];
		}
	}
	// Histogram Equalization Algorithm
	for (unsigned int i = 1; i != 256; ++i) {
		histogram[i] += histogram[i - 1];
	}
	for (unsigned int i = 0; i != img_grey_size; ++i) {
		img_grey[i] = 255 * histogram[img_grey[i]] / img_grey_size;
	}
	
	threshold = 255 * histogram[threshold] / img_grey_size;
	// http://www.tannerhelland.com/4660/dithering-eleven-algorithms-source-code/
	// Atkinson Dithering Algorithm
	#define DITHERING_MATRIX_SIZE 6
	const struct {
		int dx;
		int dy;
		// for simplicity of computation, all standard dithering formulas
		// push the error forward, never backward 
	} dithering_matrix[DITHERING_MATRIX_SIZE] = {
		{1,0},
		{2,0},
		{-1,1},
		{0,1},
		{1,1},
		{0,2}
	};
	for (unsigned int i = 0; i != img_grey_size; ++i) {
		const unsigned int o = img_grey[i];
		const unsigned int n = o <= threshold ? 0x00 : 0xff;
		// the residual quantization error 
		const int d = (int)(o - n) / 8;
		img_grey[i] = n;
		const unsigned int x = i % img_w;
		const unsigned int y = i / img_w;

		for (unsigned int j = 0; j != DITHERING_MATRIX_SIZE; ++j) {
			const int x0 = x + dithering_matrix[j].dx;
			const int y0 = y + dithering_matrix[j].dy;
			if (x0 >= img_w || x0 < 0 || y0 >= img_h) {
				continue;
			}
			img_grey[x0 + img_w * y0] = rebound(img_grey[x0 + img_w * y0] + d, 0x00, 0xff);
		}
	}
}
//图片缓存，重复打印同一张图片可以加快效率
CString LAST_IMG_PATH;
byte* LAST_IMG_CACHE=NULL;
int LAST_IMG_WIDTH;
int LAST_IMG_HEIGHT;
int LAST_IMG_THRESHOLD;
BOOL ESCPrinter::PrintBitmap(LPCTSTR path,PrintItemCfg& cfg)
{
	if(LAST_IMG_PATH.Compare(path)==0)
	{
		printImage(cfg.left,LAST_IMG_CACHE,LAST_IMG_WIDTH,LAST_IMG_HEIGHT,LAST_IMG_THRESHOLD);
		return TRUE;
	}
	else
	{
		CImage imgB;
		if(imgB.Load(path)==S_OK)
		{
			if(LAST_IMG_CACHE!=NULL)
				delete LAST_IMG_CACHE;
			LAST_IMG_PATH.Format(_T("%s"),path);
			int threshold=0x80;
			LAST_IMG_CACHE = new byte[imgB.GetHeight()*imgB.GetWidth()];
			Img2BW(imgB,LAST_IMG_CACHE,threshold);
			LAST_IMG_WIDTH=imgB.GetWidth();
			LAST_IMG_HEIGHT=imgB.GetHeight();
			LAST_IMG_THRESHOLD=threshold;
			printImage(cfg.left,LAST_IMG_CACHE,LAST_IMG_WIDTH,LAST_IMG_HEIGHT,LAST_IMG_THRESHOLD);
			return TRUE;
		}
	}
	return FALSE;
}
BOOL ESCPrinter::PrintBarcode(LPCSTR csMessage,PrintItemCfg& cfg)
{
	printBarcode(csMessage,cfg.left,0,0);
	return TRUE;
}
//控制打印机打开钱箱
void ESCPrinter::OpenDrawer()
{
	openDrawer('0',60,240);
}

