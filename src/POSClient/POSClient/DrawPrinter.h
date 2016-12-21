#pragma once
/*********************************************************************
*Copyright (c) 2015 COOLROID Technologies Co., Ltd
*DESCRIPTION：
*		Windows绘图打印机
*AUTHOR ：zhangyi
*HISTORY：
*		author time    version   desc

*********************************************************************/
class DrawPrinter: public Printer
{
private:
	HDC m_printerDC;
	CDC memDC;
	int xDPI;
	int yDPI;
	int nPaperWidth;//逻辑纸宽(单位为像素)
	int nLineHeight;
	double dpiRatio;//不同分辨率缩放比例
	POINT mPosition;//记录当前的画笔位置
	CFont defaultFont;
	PrintItemCfg last_cfg;
	int CreateFontSize(int points);
public:
	DrawPrinter(void);
	virtual ~DrawPrinter(void);
	
	virtual int OpenPrinterDev(LPCTSTR pPrinterName,int type,
		int nComBaudrate=0,int nComDataBits=0,
		int nComStopBits=0, int nComParity=0);
	virtual BOOL ClosePrinterDev();
	virtual int Phy2LogicPix(int phypix);
	virtual BOOL Print(LPCTSTR lpchText,PrintItemCfg& cfg);
	virtual BOOL PrintBitmap(LPCTSTR path,PrintItemCfg& cfg);
	virtual BOOL PrintBarcode(LPCSTR csMessage,PrintItemCfg& cfg);
	
};
