// ColorEdit.cpp : 实现文件
//

#include "stdafx.h"
#include "POSClient.h"
#include "ColorEdit.h"


// CColorEdit

IMPLEMENT_DYNAMIC(CColorEdit, CEdit)

CColorEdit::CColorEdit()
{
	m_BackColor=RGB(255,255,255);
	m_TextColor=RGB(0,0,0);
//	m_bTransparent=FALSE;
	m_nFormat=DT_CENTER|DT_VCENTER|DT_SINGLELINE;
}

CColorEdit::~CColorEdit()
{
}


BEGIN_MESSAGE_MAP(CColorEdit, CEdit)
	ON_WM_PAINT()
END_MESSAGE_MAP()



// CColorEdit 消息处理程序



void CColorEdit::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	CString text;
	GetWindowText(text);

	// Delete the old brush
	m_Brush.DeleteObject();
	m_Brush.CreateSolidBrush(m_BackColor);
	CDC* pDC = GetDC();
	if (pDC==NULL)
	{
		return;
	}
// 	if(m_bTransparent)
// 	{
// 		pDC->SetBkMode(TRANSPARENT);
// 	}
// 	else

	{
		pDC->SetBkMode(OPAQUE);
		pDC->SetBkColor(m_BackColor);
		pDC->SelectObject(&m_Brush);
	}
	
	CRect rc,rc2;
	GetClientRect(&rc);
	ScreenToClient(&rc);
// 	CFont   font;   
// 	LOGFONT   log;
// 	GetObject(::GetStockObject(DEFAULT_GUI_FONT),sizeof(log),&log);   
// 	log.lfHeight=22;      //字体高度
// 	log.lfWeight=600;
// 	font.CreateFontIndirect(&log);
	CFont*   font=GetFont();
	pDC->SelectObject(font);
	rc2=CRect(0, 0, rc.Width(), rc.Height());
	pDC->SetTextColor(m_TextColor);
//	if(m_bTransparent==FALSE)
	{
		pDC->FillRect(rc2,&m_Brush);
		pDC->DrawText(text,-1,&rc2,m_nFormat);
	}
	ReleaseDC(pDC);
// 	else
// 		pDC->DrawText(text,-1,&rc2,DT_LEFT);
	// Do not call CEdit::OnPaint() for painting messages
}
