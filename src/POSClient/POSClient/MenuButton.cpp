#include "StdAfx.h"
#include "POSClient.h"
#include <math.h>
#include <GdiPlus.h>
#include <GdiPlusPixelFormats.h>
#include "MenuButton.h"
//#include "CreateGrayscaleIcon.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define BTN_STATE_NUM 2
/************************************************************************/
/* Construction and Destruction                                         */
/************************************************************************/
//! Construction
CMenuButton::CMenuButton(void):	
CRoundButton2()
{
	m_nType=0;
}

//! Destruction
CMenuButton::~CMenuButton(void)
{
}

//! Draw-Item-Function
/*! This Function is called each time, the Button needs a redraw
*/
void CMenuButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
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
			CBitmap bmp;
			bmp.CreateCompatibleBitmap(pDC, m_rBtnSize.Width(), m_rBtnSize.Height()*BTN_STATE_NUM);
			m_Memdc.SelectObject(&bmp);
			bmp.DeleteObject();
			if(m_nType==0&&m_tImage && m_tImage->GetPixelFormat()& PixelFormatAlpha)
			{//含有透明图层
				if (m_dcBk.m_hDC == NULL)
				{
					CRect rect;
					GetWindowRect(rect);
					GetParent()->ScreenToClient(rect);
					CClientDC clDC(GetParent());
					m_dcBk.CreateCompatibleDC(&clDC);
					bmp.CreateCompatibleBitmap(&clDC, m_rBtnSize.Width(), m_rBtnSize.Height());
					m_dcBk.SelectObject(&bmp);
					m_dcBk.BitBlt(0, 0, m_rBtnSize.Width(), m_rBtnSize.Height(), &clDC, rect.left, rect.top, SRCCOPY);
					bmp.DeleteObject();
				}
				m_Memdc.BitBlt(0, 0, m_rBtnSize.Width(), m_rBtnSize.Height(), &m_dcBk, 0, 0, SRCCOPY);
				m_Memdc.BitBlt(0, m_rBtnSize.Height(), m_rBtnSize.Width(), m_rBtnSize.Height(), &m_dcBk, 0, 0, SRCCOPY);
			}
			Gdiplus::Graphics graphics(m_Memdc.GetSafeHdc());
			if(m_nType==1)
			{
				//COLORREF bgColor =RGB(144, 105, 136) ;
				COLORREF bgColor =DEFALUT_BACKGROUND_COLOR ;
				CBrush brush(bgColor);
				CRect rect=m_rBtnSize;
				rect.bottom+=rect.bottom;
				m_Memdc.FillRect(&rect, &brush);
				rect=m_rBtnSize;
				rect.bottom-=20;
				graphics.DrawImage(m_tImage,0,0,rect.Width(), rect.Height());
				graphics.DrawImage(m_tImagep,0,m_rBtnSize.Height(),rect.Width(), rect.Height());
			}
			else
			{
				graphics.DrawImage(m_tImage,0,0,m_rBtnSize.Width(), m_rBtnSize.Height());
				graphics.DrawImage(m_tImagep,0,m_rBtnSize.Height(),m_rBtnSize.Width(), m_rBtnSize.Height());
			}
			
			BOOL bHasText=TRUE;
			if(strCaption.GetLength()==0)
				bHasText=FALSE;
			DrawIcon(bHasText,rectText);
			// Draw Button-Caption
			DrawButtonCaption(&m_Memdc,strCaption,rectText);
			m_bRedraw=false;
		}
		int nButtonState = 0;
		if ((lpDrawItemStruct->itemState & ODS_SELECTED) == ODS_SELECTED)
			nButtonState = 1;
		if(m_nCheck>=0)
		{
			nButtonState=m_nCheck;
		}
		// Copy correct Bitmap to Screen
		pDC->BitBlt(0,0,m_rBtnSize.Width(),m_rBtnSize.Height(),&m_Memdc,0,m_rBtnSize.Height() * nButtonState,SRCCOPY);
}


//! Draw Caption on Button
void CMenuButton::DrawButtonCaption(CDC *_pDC,LPCTSTR sCaption,CRect& rect)
{
	// Select Transparency for Background
	_pDC->SetBkMode(TRANSPARENT);
	CFont* captionFont=NULL;
	if (m_tBtnFont.m_hObject == NULL)
	{
		captionFont=GetParent()->GetFont();
	}
	else
		captionFont=&m_tBtnFont;
	static CFont smallFont;
	if(smallFont.m_hObject==NULL)
		smallFont.CreatePointFont(90,_T("Microsoft YaHei"));
	for (int nState = 0; nState < BTN_STATE_NUM; nState++)
	{
		_pDC->SetTextColor(m_tTextColor[nState]);
		CRect temp ;
		CRect temp_raw=CRect(rect.left, nState * m_rBtnSize.Height() + rect.top, rect.right, nState * m_rBtnSize.Height() + rect.bottom);
		//画脚注
		if (!m_strTop.IsEmpty())
		{
			_pDC->SelectObject(&smallFont);
			temp = CRect(rect.left, nState * m_rBtnSize.Height() + rect.top, rect.right-5, nState * m_rBtnSize.Height() + rect.bottom);
			_pDC->DrawText(m_strTop,temp,DT_RIGHT| DT_TOP| DT_EDITCONTROL | DT_WORDBREAK);
			temp_raw.right-=8;
		}
		if (m_nType!=1&&!m_strBottom.IsEmpty())
		{
			_pDC->SelectObject(&smallFont);
			temp = CRect(rect.left, nState * m_rBtnSize.Height() + rect.top, rect.right-5, nState * m_rBtnSize.Height() + rect.bottom);
			_pDC->DrawText(m_strBottom,temp,DT_RIGHT| DT_BOTTOM| DT_SINGLELINE);
			temp_raw.bottom-=8;
		}
		if(m_nType==1)
		{
			_pDC->SelectObject(&smallFont);
			temp = CRect(rect.left, nState * m_rBtnSize.Height() + rect.top, rect.right-40, nState * m_rBtnSize.Height() + rect.bottom);
			_pDC->DrawText(sCaption,temp,DT_LEFT| DT_BOTTOM| DT_SINGLELINE);
		}
		else
		{
			temp=temp_raw;
			_pDC->SelectObject(captionFont);
			if(m_textPos==1)
			{
				_pDC->DrawText(sCaption,temp,DT_TOP| DT_CENTER | DT_EDITCONTROL | DT_WORDBREAK);
			}
			else if(m_textPos==2)
			{
				_pDC->DrawText(sCaption,temp,DT_BOTTOM| DT_CENTER | DT_SINGLELINE);
			}
			else
			{
				int height = _pDC->DrawText(sCaption,temp,DT_CENTER | DT_WORDBREAK | DT_CALCRECT | DT_EDITCONTROL); // 获得文本高度
				if(temp_raw.Height() > height)
					temp_raw.DeflateRect(0,(temp_raw.Height() - height)/2); // 改变rect才能垂直居中
				_pDC->DrawText(sCaption,temp_raw,DT_CENTER | DT_EDITCONTROL | DT_WORDBREAK);
			}
		}
	}
}

/************************************************************************/
/* Overwritten Functions for Init and Draw of Button                    */
/************************************************************************/

BEGIN_MESSAGE_MAP(CMenuButton, CButton)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()