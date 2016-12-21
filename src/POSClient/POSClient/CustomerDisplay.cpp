// MyPrinter.cpp : 实现文件
//

#include "stdafx.h"
#include "CustomerDisplay.h"
#include "StringConvert.h"
#include "POSClient.h"

// CMyPrinter

CustomerDisplay::CustomerDisplay()
{
	m_strPort = _T("");
	m_BaudRate = 9600;
	m_ByteSize = 8;
	m_Parity = NOPARITY;
	m_StopBits = ONESTOPBIT;
	m_hPort = INVALID_HANDLE_VALUE;
	m_nDeviceType=0;
}

CustomerDisplay::~CustomerDisplay()
{
}


//strPort:com1, BaudRate设置波特率:9600,bytesize数据位, 8bit:8,parity校验, 无,StopBits:停止位, 1位
//ture :打开成功，false：打开失败
BOOL CustomerDisplay::Open(CString strPort, DWORD BaudRate,BYTE ByteSize,BYTE Parity,BYTE StopBits)
{
		BOOL bSuccess;
		DCB dcb;
		COMMTIMEOUTS TimeOuts;
		//打开端口
		m_hPort = CreateFile(strPort, GENERIC_READ | GENERIC_WRITE,
			0, NULL, 
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL, NULL );

		if (m_hPort == INVALID_HANDLE_VALUE)
		{
			return FALSE;
		}

		SetupComm(m_hPort, 1024, 1024);			//设置端口缓冲

		TimeOuts.ReadIntervalTimeout = MAXDWORD;
		TimeOuts.ReadTotalTimeoutMultiplier = 0;
		TimeOuts.ReadTotalTimeoutConstant = 0;
		TimeOuts.WriteTotalTimeoutMultiplier = 50;
		TimeOuts.WriteTotalTimeoutConstant = 2000;

		SetCommTimeouts(m_hPort, &TimeOuts);		//设置超时控制		

		bSuccess = GetCommState(m_hPort, &dcb);	//获得当前串口配置

		dcb.BaudRate = BaudRate;			//设置波特率 
		dcb.ByteSize = ByteSize;			//数据位, 8bit
		dcb.Parity = Parity;					//校验, 无
		dcb.StopBits = StopBits;				//停止位, 1位

		bSuccess = SetCommState(m_hPort, &dcb);	//配置串口
		PurgeComm(m_hPort, PURGE_TXCLEAR);
		return TRUE;
}

//0:打印机，1：开启钱箱，2：顾显操作
//打印错误次数，如果大于10并且有备份打印机则使用备份打印机打印，大于30则说明备份打印错误，使用原始打印机
BOOL CustomerDisplay::Open()
{
	try{
		if(m_strPort.IsEmpty())
			return FALSE;
		return Open(m_strPort,m_BaudRate,m_ByteSize,m_Parity,m_StopBits);
	}
	catch(...)
	{
	}
	return FALSE;

}
BOOL CustomerDisplay::IsOpen()
{
	if(m_hPort == INVALID_HANDLE_VALUE)
		return FALSE;
	return TRUE;
}

//关闭设备
void CustomerDisplay::Close()
{
	if(m_hPort != INVALID_HANDLE_VALUE)
	{
		try
		{
			BOOL re = CloseHandle(m_hPort);
			if(re==FALSE)
			{
				LOG4CPLUS_DEBUG(log_pos,"CloseHandle failed GetLastError="<<GetLastError());;
			}
			m_hPort = INVALID_HANDLE_VALUE;

		}
		catch (CException* e)
		{
			LOG4CPLUS_DEBUG(log_pos,"CloseHandle Exception");
		}

	}
}

void CustomerDisplay::Print(CString strOutput)
{
	DWORD iBytesLength;
	char chQueryCode2[512]={0};
	CString2MultiByte(strOutput,chQueryCode2,512);
	WriteFile(m_hPort, chQueryCode2, (DWORD)strlen(chQueryCode2), &iBytesLength, NULL);
}

//控制打印机打开钱箱
void CustomerDisplay::OpenDrawer()
{
	DWORD iBytesLength;
	char chQueryCode2[] = "\x1B\x70\x30\x3C\xF0";
	WriteFile(m_hPort, chQueryCode2, (DWORD)5L, &iBytesLength, NULL);
}
void CustomerDisplay::OpenDrawer2()
{
	DWORD iBytesLength;
	char chQueryCode2[] = "\x1B\x70\x07\x1C";
	WriteFile(m_hPort, chQueryCode2, (DWORD)5L, &iBytesLength, NULL);
}

//顾显
/************************************************************************/
/*说明：price为显示的价格，type如下
(1)当   type=0，四种字符   全暗。 
(2)当   type=1，“单价”字符   亮，其它三种   全暗。 
(3)当   type=2，“总计”字符   亮，其它三种   全暗。 
(4)当   type=3，“收款”字符   亮，其它三种   全暗。 
(5)当   type=4，“找零”字符   亮，其它三种   全暗                                                                     */
/************************************************************************/
BOOL CustomerDisplay::ShowCustomerScreen(double price,int type)
{
	if (type < 0 || type > 4)
	{
		return FALSE;
	}
	DWORD iBytesLength;
	//ESC  Q  A  d1d2d3…dn  CR
	CStringA strPrice;
	strPrice.Format("\x1B\x51\x41%0.2f\x0D",price);
	WriteFile(m_hPort, (LPCSTR)strPrice, (DWORD)strPrice.GetLength(), &iBytesLength, NULL);
	//ESC  s  n
	CStringA strType;
	strType.Format("\x1B\x73%d",type);
	WriteFile(m_hPort, (LPCSTR)strType, (DWORD)3L, &iBytesLength, NULL);
	return TRUE;

}

BOOL CustomerDisplay::Display(double price,int type)
{
	if(m_hPort == INVALID_HANDLE_VALUE)
		return FALSE;
	if(m_nDeviceType==0)
	{//LED8
		return ShowCustomerScreen(price,type);
	}
	else if(m_nDeviceType==1)
	{//VFD220
		CString line;
		if(type==1)
		{//单价
			line.Format(_T("Price: %0.2f"),price);
		}
		else if(type==2)
		{//总计
			line.Format(_T("Total: %0.2f"),price);
		}
		else if(type==3)
		{//收款
			line.Format(_T("Paid: %0.2f"),price);
		}
		else if(type==4)
		{//找零
			line.Format(_T("Change: %0.2f"),price);
		}
		return ShowLine1(line);
	}
	return FALSE;
}
BOOL CustomerDisplay::DisplayPrice(double price,LPCTSTR name)
{
	if(m_hPort == INVALID_HANDLE_VALUE)
		return FALSE;
	if(m_nDeviceType==0)
	{//LED8
		return ShowCustomerScreen(price,1);
	}
	else if(m_nDeviceType==1)
	{//VFD220
		ShowLine1(name);
		CString line;
		line.Format(_T("Price: %0.2f"),price);
		return ShowLine2(line);
	}
	return FALSE;
}
//ESC  Q  A  d1d2d3…….dn  CR在第一行显示字符
BOOL CustomerDisplay::ShowLine1(LPCTSTR pText)
{
	DWORD iBytesLength;
	char chQueryCode3[] = "\xCH";//清除屏幕上的所有字符。
	WriteFile(m_hPort, chQueryCode3, (DWORD)1L, &iBytesLength, NULL);
	if(pText==NULL)
		return TRUE;
	CString strPrice;
	strPrice.Format(_T("\x1B\x51\x41%s\x0D"),pText);
	char chQueryCode2[256];
	CString2MultiByte(strPrice,chQueryCode2,256);
	WriteFile(m_hPort, chQueryCode2, (DWORD)strPrice.GetLength(), &iBytesLength, NULL);
	return TRUE;
}
//ESC  Q  B  d1d2d3…….dn  CR在第二行显示字符
BOOL CustomerDisplay::ShowLine2(LPCTSTR pText)
{
	DWORD iBytesLength;
// 	char chQueryCode3[] = "\xCH";//清除屏幕上的所有字符。
// 	WriteFile(m_hPort, chQueryCode3, (DWORD)1L, &iBytesLength, NULL);
	if(pText==NULL)
		return TRUE;
	CString strPrice;
	strPrice.Format(_T("\x1B\x51\x42%s\x0D"),pText);
	char chQueryCode2[256];
	CString2MultiByte(strPrice,chQueryCode2,256);
	WriteFile(m_hPort, chQueryCode2, (DWORD)strPrice.GetLength(), &iBytesLength, NULL);
	return TRUE;
}
//ESC  Q  D  d1d2d3…dn  CR在顶行显示持续滚动字符
BOOL CustomerDisplay::ShowRollingText(LPCTSTR pText)
{
	if(m_hPort == INVALID_HANDLE_VALUE)
		return FALSE;
	if(m_nDeviceType==1)
	{
		DWORD iBytesLength;
		char chQueryCode3[] = "\xCH";//清除屏幕上的所有字符。
		WriteFile(m_hPort, chQueryCode3, (DWORD)1L, &iBytesLength, NULL);
		if(pText==NULL)
			return TRUE;
		CString strText;
		strText.Format(_T("\x1B\x51\x44%s\x0D"),pText);
		char chQueryCode2[256]={0};
		CString2MultiByte(strText,chQueryCode2,256);
		WriteFile(m_hPort, chQueryCode2, (DWORD)strlen(chQueryCode2), &iBytesLength, NULL);
	}
	return TRUE;
}

void CustomerDisplay::SetOpenParam(int type,CString strPort, DWORD BaudRate,BYTE ByteSize,BYTE Parity,BYTE StopBits)
{
	m_strPort = strPort;
	m_BaudRate = BaudRate;
	m_ByteSize = ByteSize;
	m_Parity = Parity;
	m_StopBits = StopBits;
	m_nDeviceType = type;
}
