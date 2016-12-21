#pragma once
/*********************************************************************
*Copyright (c) 2015 COOLROID Technologies Co., Ltd
*DESCRIPTION：
*		ESC/POS指令打印机
*AUTHOR ：zhangyi
*HISTORY：
*		author time    version   desc

*********************************************************************/
#include "EscPosCommands.h"

class ESCPrinter: public Printer,EscPosCommands{
private:
	HANDLE g_hComm;
	int m_logpix;//每英寸的像素数
	int m_printType;

	int last_align;
	int last_size;
	int last_style;

public:
    ESCPrinter();
    virtual ~ESCPrinter();
	virtual int OpenPrinterDev(LPCTSTR wPrinterName,int type,
		int nComBaudrate=0,int nComDataBits=0,
		int nComStopBits=0, int nComParity=0);
	virtual BOOL ClosePrinterDev();
	BOOL Print(char* data);
	virtual std::size_t writeBytes(const byte* buffer, std::size_t size);
	virtual int Phy2LogicPix(int phypix);
	virtual BOOL Print(LPCTSTR lpchText,PrintItemCfg& cfg);
	virtual BOOL PrintBitmap(LPCTSTR path,PrintItemCfg& cfg);
	virtual BOOL PrintBarcode(LPCSTR csMessage,PrintItemCfg& cfg);

	virtual void CutPaper();
	void OpenDrawer();
};

