#include "StdAfx.h"
#include "DrawPrinter.h"
#include "POSClient.h"
#include <atlimage.h>
#include "BaseCodes.h"
#include "I2of5.h"

DrawPrinter::DrawPrinter()
:Printer()
{
	dpiRatio=1;
	mPosition.x=0;
	mPosition.y=0;
	nLineHeight=0;
}

CString LF_FaceName=_T("SimSun");
UINT LF_CHARSET=DEFAULT_CHARSET;
DrawPrinter::~DrawPrinter()
{
}
int DrawPrinter::OpenPrinterDev(LPCTSTR pPrinterName,int type,
							 int nComBaudrate,int nComDataBits,
							 int nComStopBits, int nComParity)
{
	m_printerDC=CreateDC(_T(""),pPrinterName,NULL,NULL);
	if (m_printerDC<=0)
		return 1;
	memDC.Attach(m_printerDC);
	static DOCINFO di = {sizeof (DOCINFO), _T("POS_Print")} ;
	if(memDC.StartDoc( &di ) < 0)
		return 1;
	xDPI = memDC.GetDeviceCaps(LOGPIXELSX);
	yDPI = memDC.GetDeviceCaps(LOGPIXELSY);
	dpiRatio=180.0/xDPI;
	int wid=memDC.GetDeviceCaps(HORZSIZE);
	nPaperWidth=memDC.GetDeviceCaps(HORZRES);
	LOGFONT logFont;
	memset(&logFont,0,sizeof(LOGFONT));
//	GetObject(::GetStockObject(DEVICE_DEFAULT_FONT),sizeof(logFont),&logFont);
	if(nPaperWidth>70)
		logFont.lfHeight=CreateFontSize(10);
	else
		logFont.lfHeight=CreateFontSize(9);
	logFont.lfCharSet=LF_CHARSET;
	//logFont.lfPitchAndFamily=FIXED_PITCH;
	wcscpy_s(logFont.lfFaceName,LF_FaceName);
	defaultFont.CreateFontIndirect(&logFont);
	return 0;
}
BOOL DrawPrinter::ClosePrinterDev()
{
	memDC.EndDoc();
	memDC.DeleteDC();
	DeleteDC(m_printerDC);
	return TRUE;
}
int DrawPrinter::CreateFontSize(int points)
{
	// This will calculate the font size for the printer that is specified
	// by a point size.
	//
	// if points is:
	//  (-) negative uses height as value for Net Font Height (ie. point size)
	//	(+) positive height is Total Height plus Leading Height!
	POINT size;
	size.x = size.y = MulDiv(points,yDPI, 72);
	// here we scale the font...
	//return (float)floor(size.y*dpiRatio);
	memDC.DPtoLP(&size);
	return size.y;
}
/************************************************************************
物理单位(mm)转为逻辑的像素
************************************************************************/
int DrawPrinter::Phy2LogicPix(int phypix)
{
	return (int)(phypix*xDPI)/25.4;
}
BOOL DrawPrinter::PrintBitmap(LPCTSTR path,PrintItemCfg& cfg)
{
	CDC  MemDC2;
	CImage imgB;
	if(imgB.Load(path)==S_OK)
	{
		int w=imgB.GetWidth();
		int h=imgB.GetHeight();
		HBITMAP bitmap=imgB.Detach();
		MemDC2.CreateCompatibleDC(&memDC);
		HGDIOBJ hOldBmp =MemDC2.SelectObject(bitmap);
		int left=cfg.left;
		if (cfg.align==BaseCodes::ALIGN_RIGHT)
		{
			left=nPaperWidth-w;
		}
		else if(cfg.align==BaseCodes::ALIGN_CENTER)
		{
			left=(nPaperWidth-w)/2;
		}
		memDC.BitBlt(left,mPosition.y,w,h,&MemDC2,0,0,SRCCOPY);
		MemDC2.SelectObject(hOldBmp);
		::DeleteObject(bitmap);
		mPosition.y+=h;
		return TRUE;
	}
	return FALSE;
}
BOOL DrawPrinter::PrintBarcode(LPCSTR csMessage,PrintItemCfg& cfg)
{
	double height=0.24;
	int h=height*yDPI;
	CI2of5	oBarcode;
	oBarcode.LoadData(csMessage,0.018,height,m_printerDC,0,mPosition.y,2.67);
	oBarcode.DrawBitmap();
	mPosition.y+=h;
	return TRUE;
}
BOOL DrawPrinter::Print(LPCTSTR lpchText,PrintItemCfg& cfg)
{
	try{
		CFont font;
		if(cfg.left!=0)
			mPosition.x=cfg.left;
		BOOL bSameCfg=FALSE;
		if(memcmp(&cfg,&last_cfg,sizeof(PrintItemCfg)-sizeof(LPCTSTR))==0)
		{//相同配置
			if(last_cfg.font==NULL)
				bSameCfg=FALSE;
			else if(cfg.font==NULL||wcscmp(cfg.font,last_cfg.font)==0)
			{
				bSameCfg=TRUE;
			}
		}
		if(bSameCfg==FALSE)
		{
			last_cfg=cfg;
			if(cfg.size<=1&&cfg.font==NULL&&cfg.style==0)
			{
				memDC.SelectObject(&defaultFont);
			}
			else
			{
				LOGFONT m_tLogFont;
				memset(&m_tLogFont,0,sizeof(LOGFONT));
				switch(cfg.size)
				{
				case 0:
				case 1:
					m_tLogFont.lfHeight = CreateFontSize(9);
					break;
				case 2://双倍
					m_tLogFont.lfHeight = CreateFontSize(18);
					m_tLogFont.lfWidth=0;
					break;
				case 3://倍高
					m_tLogFont.lfHeight=CreateFontSize(18);
					m_tLogFont.lfWidth =m_tLogFont.lfHeight/4;
					break;
				case 4://倍宽
					m_tLogFont.lfHeight = CreateFontSize(9);
					m_tLogFont.lfWidth=m_tLogFont.lfHeight;
					break;
				default://其他大小
					m_tLogFont.lfHeight = CreateFontSize(cfg.size);
					m_tLogFont.lfWidth=0;
				}

				if (cfg.style&POS_FONT_STYLE_BOLD)
				{
					m_tLogFont.lfWeight=FW_BOLD;
				}
				if (cfg.style&POS_FONT_STYLE_UNDERLINE)
				{
					m_tLogFont.lfUnderline=TRUE;
				}
				if (cfg.style&POS_FONT_STYLE_ITALIC)
				{
					m_tLogFont.lfItalic=TRUE;
				}
				if (cfg.style&POS_FONT_STYLE_STRIKEOUT)
				{
					m_tLogFont.lfStrikeOut=TRUE;
				}
				m_tLogFont.lfCharSet=LF_CHARSET;
				if(cfg.font==NULL)
					wcscpy_s(m_tLogFont.lfFaceName, LF_FaceName);
				else
					wcscpy_s(m_tLogFont.lfFaceName, cfg.font);
				font.CreateFontIndirect(&m_tLogFont);
				memDC.SelectObject(&font);
			}
		}
		TCHAR* pText=(TCHAR*)lpchText;
		bool bNewChar=false;
		int len=wcslen(lpchText);
		if(len>0&&pText[len-1]=='\n')
		{//末尾为换行，则删除换行符
			pText=new TCHAR[len+1];
			wcscpy_s(pText,len+1,lpchText);
			pText[len-1]=0;
			bNewChar=true;
		}
		int height=0;
		CRect rect;
		rect.top=mPosition.y;
		rect.bottom=rect.top+500;
		if(cfg.width>0)
		{//先计算文本框位置，再对齐
			if (cfg.align==BaseCodes::ALIGN_RIGHT)
			{
				rect.left=nPaperWidth-cfg.width;
				rect.right=nPaperWidth;
			}
			else if(cfg.align==BaseCodes::ALIGN_CENTER)
			{
				rect.left=(nPaperWidth-cfg.width)/2;
				rect.right=rect.left+cfg.width;
			}
			else
			{
				rect.left=mPosition.x;
				rect.right=rect.left+cfg.width;
			}
			if (cfg.text_align==BaseCodes::ALIGN_RIGHT)
			{
				height=DrawText(m_printerDC,pText,-1,&rect,DT_RIGHT|DT_NOCLIP);
			}
			else if(cfg.text_align==BaseCodes::ALIGN_CENTER)
			{
				height=DrawText(m_printerDC,pText,-1,&rect,DT_CENTER|DT_NOCLIP);
			}
			else
			{//支持自动换行
				height=DrawText(m_printerDC,lpchText,-1,&rect,DT_LEFT|DT_WORDBREAK | DT_EDITCONTROL);
			}
		}
		else
		{//未设置字符串宽度，居中和右对齐整行生效
			if (cfg.align==BaseCodes::ALIGN_RIGHT)
			{
				rect.left=mPosition.x;
				rect.right=nPaperWidth;
				height=DrawText(m_printerDC,pText,-1,&rect,DT_RIGHT|DT_NOCLIP);
			}
			else if(cfg.align==BaseCodes::ALIGN_CENTER)
			{
				rect.left=0;
				rect.right=nPaperWidth;
				height=DrawText(m_printerDC,pText,-1,&rect,DT_CENTER|DT_NOCLIP);
			}
			else
			{//支持自动换行
				rect.left=mPosition.x;
				rect.right=nPaperWidth;
				height=DrawText(m_printerDC,lpchText,-1,&rect,DT_LEFT|DT_WORDBREAK | DT_EDITCONTROL);
			}
		}
		if(bNewChar)
			delete pText;
		if(height>nLineHeight)
			nLineHeight=height;
		if(wcsstr(lpchText,_T("\n")))
		{//换行
			mPosition.x=0;
			mPosition.y+=nLineHeight;
			nLineHeight=20;//最小行高
		}
		else if (cfg.left==0)
		{//兼容针式打印模板
			CRect rect=CRect(0,0,nPaperWidth,300);
			DrawText(m_printerDC, lpchText, -1,&rect, DT_CALCRECT);
			mPosition.x+=rect.right;
		}
		return TRUE;
	}catch(...)
	{
		LOG4CPLUS_ERROR(log_pos,"Catch Exception GetLastError="<<GetLastError());
	}
	return FALSE;
}