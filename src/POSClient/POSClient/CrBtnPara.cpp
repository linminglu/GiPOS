#include "StdAfx.h"
#include "POSClient.h"
#include "CrBtnPara.h"
#include "TpReader.h"


//int CreatButton::m_nFullWidth=GetSystemMetrics(SM_CXSCREEN);
//int CreatButton::m_nFullHeight=GetSystemMetrics(SM_CYSCREEN);
//int CreatButton::m_nFullWidth=(CreatButton::m_nFullHeight*4)/3;
//为测试方便，定为1024*768
 int CreatButton::m_nFullWidth=1024;
 int CreatButton::m_nFullHeight=768;

CreatButton::CreatButton()
{
	bSetBk=FALSE;
}
CRect CreatButton::GenaratePage2(CString fileName,CDialog* dlg)
{
	CTpReader readIni(fileName);
	CString pageName=_T("PAGE");
	int btnNum = readIni.ReadInteger(pageName,BTN_NUM,0);
	int rightMost=0;
	int bottomMost=0;
	for (int i = 1; i <= btnNum; i++)
	{
		CString btnName = BTN_NAME,btnRect=BTN_RECT;
		CString btnIcon=BTN_ICON,btnIconPos=BTN_ICON_POSITION,btnFont=BTN_FONT,btnFontSize=BTN_FONT_SIZE,btnPic=BTN_BKG_PIC;
		CString btnBkgColor=BTN_BKG_COLOR,btnTxtColor=BTN_TXT_COLOR,btnNextPage=BTN_NEXT_PAGE,btnFun=BTN_FUNCTION;
		CString btnIndex;
		btnIndex.Format(_T("%d"),i);
		CR_BTN_PARA btnPara;
		readIni.ReadRect(pageName,btnRect+btnIndex,&btnPara.rect);
		if (btnPara.rect.right==0&&btnPara.rect.bottom==0)
		{
			continue;
		}
		btnPara.name = readIni.ReadString(pageName,btnName+btnIndex,_T(""));
		btnPara.name.Replace(_T("\\n"),_T("\n"));
		btnPara.function = readIni.ReadInteger(pageName,btnFun+btnIndex,0);
		btnPara.font = readIni.ReadString(pageName,btnFont+btnIndex,_T("Arial"));
		btnPara.fontSize = readIni.ReadInteger(pageName,btnFontSize+btnIndex,16);
		btnPara.txt_color = readIni.ReadRGB(pageName,btnTxtColor+btnIndex,RGB(0,0,0));
		btnPara.txt_pos = readIni.ReadInteger(pageName,_T("txt_pos")+btnIndex,0);
		btnPara.picture=readIni.ReadString(pageName,btnPic+btnIndex,_T(""));
// 		if(btnPara.picture.GetLength()==0)
// 		{
// 			btnPara.icon = readIni.ReadString(pageName,btnIcon+btnIndex,_T(""));
// 			btnPara.iconPos = readIni.ReadString(pageName,btnIconPos+btnIndex,_T("top"));
// 			//btnPara.bkg_color = readIni.ReadRGB(pageName,btnBkgColor+btnIndex,RGB(164, 164, 164));
// 		}
		int n=btnPara.rect.bottom*m_nFullHeight/768;
		if(bottomMost<n)
			bottomMost=n;
		n=btnPara.rect.right*m_nFullWidth/1024;
		if(rightMost<n)
			rightMost=n;
		CreateBtn2(btnPara,dlg);
	}
	return CRect(0,0,rightMost,bottomMost);
}

void CreatButton::CreateBtn2(CR_BTN_PARA btnParam,CDialog* dlg)
{
	CRect rect;
	//比例尺设为400*300
	rect.top=btnParam.rect.top*m_nFullHeight/768;
	rect.bottom=btnParam.rect.bottom*m_nFullHeight/768;
	rect.left=btnParam.rect.left*m_nFullWidth/1024;
	rect.right=btnParam.rect.right*m_nFullWidth/1024;
	CRoundButton2* pBtn = new CRoundButton2;
	pBtn->Create(btnParam.name,WS_CHILD ,
		rect,dlg,btnParam.function);
	m_buttonList.push_back(pBtn);

	if (btnParam.picture.GetLength()!=0)
	{
		Gdiplus::Image* img1=Gdiplus::Image::FromFile(btnParam.picture);
		if(img1)
		{
			btnParam.picture.Replace(_T("."),_T("_."));
			Gdiplus::Image* img2=Gdiplus::Image::FromFile(btnParam.picture);
			pBtn->SetImages(img1,img2);
		}
	}
	if (btnParam.function==-1)
	{
		pBtn->EnableWindow(FALSE);
		pBtn->SetWindowPos(NULL,rect.left,rect.top,rect.Width(),rect.Height(),SWP_NOZORDER|SWP_NOMOVE);
	}
	else
		pBtn->MoveWindow(&rect);
	//设置字体
	LOGFONT m_tLogFont;
	if (btnParam.fontSize != 0)
	{	
		m_tLogFont.lfHeight			= ScaleY(btnParam.fontSize);
	}
	else
	{
		m_tLogFont.lfHeight			= ScaleY(18);
	}
	m_tLogFont.lfWidth			= 0;
	m_tLogFont.lfEscapement		= 0;
	m_tLogFont.lfOrientation	= 0;
	m_tLogFont.lfWeight			= FW_BOLD;
	m_tLogFont.lfItalic			= false;
	m_tLogFont.lfUnderline		= false;
	m_tLogFont.lfStrikeOut		= false;
	m_tLogFont.lfCharSet		= DEFAULT_CHARSET;
	m_tLogFont.lfOutPrecision	= OUT_DEFAULT_PRECIS;
	m_tLogFont.lfClipPrecision	= CLIP_DEFAULT_PRECIS;
	m_tLogFont.lfQuality		= ANTIALIASED_QUALITY;
	m_tLogFont.lfPitchAndFamily	= DEFAULT_PITCH;
	if (btnParam.font != _T(""))
	{
		wcscpy_s(m_tLogFont.lfFaceName, btnParam.font);
	}
	else
	{
		wcscpy_s(m_tLogFont.lfFaceName, _T("Calibri"));
	}
	pBtn->SetFont(&m_tLogFont);

	pBtn->SetTextColor(btnParam.txt_color);
	pBtn->m_textPos=btnParam.txt_pos;

	pBtn->ShowWindow(SW_SHOW);

}


void CreatButton::ReleaseBtn()
{
	for (CPbuttonIter iter = m_buttonList.begin(); iter!= m_buttonList.end();iter++)
	{
		CRoundButton2 *b = (*iter);
		b->DestroyWindow();
		delete b;
	}
	m_buttonList.clear();
}
void CreatButton::ShowButtons(int nCmdShow)
{
	m_nShowStatus=nCmdShow;
	for (CPbuttonIter iter = m_buttonList.begin(); iter!= m_buttonList.end();iter++)
	{
		CRoundButton2 *b = (*iter);
		b->ShowWindow(nCmdShow);
	}
}
void CreatButton::SetBkGnd(CDC* pDC)
{
	if(bSetBk)
		return;
	bSetBk=TRUE;
	for (CPbuttonIter iter = m_buttonList.begin(); iter!= m_buttonList.end();iter++)
	{
		CRoundButton2 *b = (*iter);
		b->SetBkGnd(pDC,TRUE);
	}
}