#pragma once
/*********************************************************************
*Copyright (c) 2015 COOLROID Technologies Co., Ltd
*DESCRIPTION：
*		打印机基类
*AUTHOR ：zhangyi
*HISTORY：
*		author time    version   desc

*********************************************************************/

#define POS_FONT_STYLE_BOLD		 1
#define POS_FONT_STYLE_UNDERLINE 2
#define POS_FONT_STYLE_ITALIC	 4
#define POS_FONT_STYLE_STRIKEOUT 8

#define PRINTER_TYPE_COM 0
#define PRINTER_TYPE_LPT 1
#define PRINTER_TYPE_USB 2
#define PRINTER_TYPE_IP 3
#define PRINTER_TYPE_WIN 4
#define PRINTER_TYPE_COMP 5

#define PRINT_ERROR_OPENFAIL	1
#define PRINT_ERROR_NETFAIL		2
#define PRINT_ERROR_COVEOPEN	3
#define PRINT_ERROR_PAPEROUT	4
#define PRINT_ERROR_ERRO		5
#define PRINT_ERROR_OTHER		9

struct PrintItemCfg{
	int left;
	int align;
	int style;
	int size;
	int width;
	int text_align;
	LPCTSTR font;
};

class Printer {

public:
	int m_nPaperWidth;//物理纸宽(单位为mm)

    Printer();
	virtual ~Printer(){}
	virtual int OpenPrinterDev(LPCTSTR wPrinterName,int type,
		int nComBaudrate=0,int nComDataBits=0,
		int nComStopBits=0, int nComParity=0) {return 0;}
	virtual BOOL ClosePrinterDev(){return FALSE;}
	virtual void CutPaper(){};
	virtual int Phy2LogicPix(int phypix){return 0;};
	virtual BOOL Print(LPCTSTR lpchText,PrintItemCfg& cfg){return FALSE;}
	virtual BOOL PrintBitmap(LPCTSTR path,PrintItemCfg& cfg){return FALSE;}
	virtual BOOL PrintBarcode(LPCSTR csMessage,PrintItemCfg& cfg){return FALSE;}
};

