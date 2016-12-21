#include "StdAfx.h"
#include <math.h>
#include <GdiPlus.h>
#include <GdiPlusPixelFormats.h>
#include ".\TableButton.h"
//#include "CreateGrayscaleIcon.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/************************************************************************/
/* Construction and Destruction                                         */
/************************************************************************/
//! Construction
CTableButton::CTableButton(void):	
 m_rBtnSize(CRect(0, 0, 0, 0))
, m_bRedraw(true)
{
	m_tImage=NULL;
	m_tImagep=NULL;
	m_hIcon = NULL;
	m_bDeleteImage=true;
	m_tTextColor[0]= RGB(0, 0, 0);
	m_tTextColor[1]= RGB(0, 0, 0);
	m_nCheck=-1;
	m_tBtnFont=NULL;
}

//! Destruction
CTableButton::~CTableButton(void)
{
	if (m_hIcon)
		DestroyIcon(m_hIcon);
	m_hIcon = NULL;
	if(m_bDeleteImage)
	{
		delete m_tImage;
		delete m_tImagep;
	}
	m_Memdc.DeleteDC();
	m_dcBk.DeleteDC();
}

/************************************************************************/
/* public Functions                                                     */
/************************************************************************/

void CTableButton::SetStrTop(LPCTSTR strMark)
{
	m_strTop=strMark;
	m_bRedraw=true;
}
// Set Font of Button
bool CTableButton::SetFont(CFont* pFont)
{
	m_tBtnFont=pFont;
	m_bRedraw = true;
	return true;
}

//=============================================================================	
// Sets icon from resource id
CTableButton& CTableButton::SetIcon(UINT nIDResource, ICON_ALIGNMENT ia /*= LEFT*/)
//=============================================================================	
{
	HICON hIcon = (HICON) LoadImage(AfxGetInstanceHandle(),
		MAKEINTRESOURCE(nIDResource),
		IMAGE_ICON,
		0,
		0,
		0);

	return SetIcon(hIcon, ia);
}

//=============================================================================	
// Sets icon from HICON
CTableButton& CTableButton::SetIcon(HICON hIcon, ICON_ALIGNMENT ia /*= LEFT*/,BOOL bDestroy)
//=============================================================================	
{
	if (bDestroy&&m_hIcon)
		DestroyIcon(m_hIcon);

	m_hIcon = hIcon;
	m_eIconAlignment = ia;
	m_bRedraw=true;
	Invalidate();
	return *this;
}
//=============================================================================	
void CTableButton::DrawIcon()
{
	if (m_hIcon)
	{
		CRect rectImage(m_rBtnSize);
		rectImage.DeflateRect(4,4);
		m_Memdc.DrawState(CPoint(rectImage.left,rectImage.top),
			CSize(rectImage.Width(),rectImage.Height()),
			m_hIcon,
			DSS_NORMAL|DST_ICON,
			(CBrush *) NULL);
	}
}
//! Set Color of Caption
bool CTableButton::SetTextColor(COLORREF _ptTextColor)
{
	m_tTextColor[0]=_ptTextColor;
	m_tTextColor[1]=_ptTextColor;
	// Button should be redrawn
	m_bRedraw = true;
	return true;
}
bool CTableButton::SetTextColor(COLORREF _ptTextColor,COLORREF _ptPressColor)
{
	m_tTextColor[0]=_ptTextColor;
	m_tTextColor[1]=_ptPressColor;
	// Button should be redrawn
	m_bRedraw = true;
	return true;
}
/************************************************************************/
/* Own Drawing-Functions                                                */
/************************************************************************/


//! Draw-Item-Function
/*! This Function is called each time, the Button needs a redraw
*/
void CTableButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
	CString strCaption;
	GetWindowText(strCaption);
	m_rBtnSize = lpDrawItemStruct->rcItem;
	CRect rectText = lpDrawItemStruct->rcItem;
	if (m_bRedraw)
	{
		if(m_Memdc.m_hDC==NULL)
			m_Memdc.CreateCompatibleDC(pDC);
		CBitmap bmpBk;
		bmpBk.CreateCompatibleBitmap(pDC, m_rBtnSize.Width(), m_rBtnSize.Height());
		m_Memdc.SelectObject(&bmpBk);
		bmpBk.DeleteObject();
		if(m_tImage && m_tImage->GetPixelFormat()& PixelFormatAlpha)
		{//含有透明图层
			if (m_dcBk.m_hDC == NULL)
			{
				CRect rect;
				GetWindowRect(rect);
				GetParent()->ScreenToClient(rect);
				CClientDC clDC(GetParent());
				m_dcBk.CreateCompatibleDC(&clDC);
				bmpBk.CreateCompatibleBitmap(&clDC, m_rBtnSize.Width(), m_rBtnSize.Height());
				m_dcBk.SelectObject(&bmpBk);
				m_dcBk.BitBlt(0, 0, m_rBtnSize.Width(), m_rBtnSize.Height(), &clDC, rect.left, rect.top, SRCCOPY);
				bmpBk.DeleteObject();
			}
			m_Memdc.BitBlt(0, 0, m_rBtnSize.Width(), m_rBtnSize.Height(), &m_dcBk, 0, 0, SRCCOPY);
		}
		Gdiplus::Graphics graphics(m_Memdc.GetSafeHdc());
		graphics.DrawImage(m_tImage,0,0,m_rBtnSize.Width(), m_rBtnSize.Height());
		//graphics.DrawImage(m_tImagep,0,m_rBtnSize.Height(),m_rBtnSize.Width(), m_rBtnSize.Height());

		DrawIcon();
		// Draw Button-Caption
		DrawButtonCaption(&m_Memdc,strCaption,rectText);
		m_bRedraw=false;
	}
	// Copy correct Bitmap to Screen
	pDC->BitBlt(0,0,m_rBtnSize.Width(),m_rBtnSize.Height(),&m_Memdc,0,0,SRCCOPY);
	if(m_nCheck==1)
	{
		pDC->SelectStockObject(NULL_BRUSH);
		CRect focusRect = m_rBtnSize;
		focusRect.DeflateRect(3, 2);
		CPen penBlack(PS_SOLID, 3, RGB(1, 170, 255));
		pDC->SelectObject(&penBlack);
		pDC->RoundRect(focusRect,CPoint(6, 6));
	} // if
}


//! Draw Caption on Button
void CTableButton::DrawButtonCaption(CDC *_pDC,LPCTSTR sCaption,CRect& rect)
{
	// Select Transparency for Background
	_pDC->SetBkMode(TRANSPARENT);
	rect.DeflateRect(3,3);

		_pDC->SetTextColor(m_tTextColor[0]);
		static CFont mFont;
		if(mFont.m_hObject==NULL)
			mFont.CreatePointFont(90,_T("Microsoft YaHei"));
		CRect temp ;
		CRect temp_raw=CRect(rect.left,  rect.top, rect.right, rect.bottom);
		//画脚注
		if (!m_strTop.IsEmpty())
		{
			_pDC->SelectObject(&mFont);
			temp = CRect(rect.left, rect.top, rect.right-5, rect.bottom);
			_pDC->DrawText(m_strTop,temp,DT_RIGHT| DT_TOP|DT_SINGLELINE);
			temp_raw.right-=8;
		}
		if (!m_strBottom.IsEmpty())
		{
			
			_pDC->SelectObject(&mFont);
			temp = CRect(rect.left,  rect.top, rect.right-5, rect.bottom);
			_pDC->DrawText(m_strBottom,temp,DT_RIGHT| DT_BOTTOM| DT_SINGLELINE);
			temp_raw.bottom-=8;
		}
		temp=temp_raw;
		_pDC->SelectObject(m_tBtnFont);
		int height = _pDC->DrawText(sCaption,temp,DT_CENTER | DT_WORDBREAK | DT_CALCRECT | DT_EDITCONTROL); // 获得文本高度
		if(temp_raw.Height() > height)
			temp_raw.DeflateRect(0,(temp_raw.Height() - height)/2); // 改变rect才能垂直居中
		_pDC->DrawText(sCaption,temp_raw,DT_CENTER | DT_EDITCONTROL | DT_WORDBREAK);
	
}

/************************************************************************/
/* Overwritten Functions for Init and Draw of Button                    */
/************************************************************************/

//! Presubclass-Window-Function
void CTableButton::PreSubclassWindow()
{
#ifdef _DEBUG
	// We really should be only sub classing a button control
	TCHAR buffer[255];
	GetClassName (m_hWnd, buffer, sizeof(buffer) / sizeof(TCHAR));
	ASSERT (CString (buffer) == _T("Button"));
#endif

	// Make the button owner-drawn
	ModifyStyle (0x0FL, BS_OWNERDRAW | BS_AUTOCHECKBOX, SWP_FRAMECHANGED);

	CButton::PreSubclassWindow();
}
BOOL CTableButton::OnEraseBkgnd(CDC* pDC) 
{
	return TRUE;
}
BEGIN_MESSAGE_MAP(CTableButton, CButton)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

LRESULT CTableButton::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	if (message == WM_LBUTTONDBLCLK)
	{
		message = WM_LBUTTONDOWN;
	}
	return CButton::DefWindowProc(message, wParam, lParam);
}

void CTableButton::SetImage(CString path)
{
	Gdiplus::Image* img1=Gdiplus::Image::FromFile(path);
	if(img1)
	{
		path.Replace(_T("."),_T("_."));
		Gdiplus::Image* img2=Gdiplus::Image::FromFile(path);
		SetImages(img1,img2);
	}
}
BOOL CTableButton::SetImages(Gdiplus::Image* hBitmapIn,Gdiplus::Image* hBitmapOut,bool bDestroy)
{
	m_bDeleteImage=bDestroy;
	if (bDestroy)
	{
		delete m_tImage;
		delete m_tImagep;
	}
	if (hBitmapIn)
	{
		m_tImage = hBitmapIn;
		if (hBitmapOut&&hBitmapOut->GetLastStatus()==Gdiplus::Ok)
		{
			m_tImagep=hBitmapOut;
		}
		else
		{
			m_tImagep = CreateDarkerBitmap(hBitmapIn);
		}
	}
// 	if(bDestroy)
// 		RedrawWindow();
	m_bRedraw=true;
	return TRUE;
} // End of SetBitmaps
DWORD CTableButton::SetCheck(int nCheck, BOOL bRepaint)
{
	if (nCheck == 0)
		m_nCheck = 0;
	else 
		m_nCheck = 1;
	if (bRepaint)
		RedrawWindow();
	return BTNST_OK;
}
int CTableButton::GetCheck()
{
	return m_nCheck;
}
Gdiplus::Image* CTableButton::CreateDarkerBitmap(Gdiplus::Image* originalImage)
{
	if(originalImage==NULL)
		return NULL;
	Gdiplus::Image* clonedImage=originalImage->Clone();
	Gdiplus::ColorMatrix cm =
	{
		1.5, 0, 0, 0, 0,
		0, 1.5, 0, 0, 0,
		0, 0, 1.5, 0, 0,
		0, 0, 0, 1, 0,
		-0.3, -0.3, -0.3, 0, 1
	};
	Gdiplus::ImageAttributes imageAttributes;
	imageAttributes.SetColorMatrix(&cm);
	Gdiplus::Rect destRect(0, 0, originalImage->GetWidth(), originalImage->GetHeight());
	Gdiplus::Graphics graphics(clonedImage);
	graphics.DrawImage(originalImage,destRect,0,0,originalImage->GetWidth(), originalImage->GetHeight(),Gdiplus::UnitPixel,&imageAttributes);
	return clonedImage;
		
} // End of CreateDarkerBitmap

COLORREF CTableButton::DarkenColor(COLORREF crColor, double dFactor)
{
	if (dFactor > 0.0 && dFactor <= 1.0)
	{
		BYTE red,green,blue,lightred,lightgreen,lightblue;
		red = GetRValue(crColor);
		green = GetGValue(crColor);
		blue = GetBValue(crColor);
		lightred = (BYTE)(red-(dFactor * red));
		lightgreen = (BYTE)(green-(dFactor * green));
		lightblue = (BYTE)(blue-(dFactor * blue));
		crColor = RGB(lightred,lightgreen,lightblue);
	} // if

	return crColor;
} // End of DarkenColor