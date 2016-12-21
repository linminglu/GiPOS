////////////////////////////////////////////////////////////////
// CoolTabCtrl.cpp : implementation file                      //
//															  //
// Copyright 2001 WangJun									  //
// All Rights Reserved.										  //
//															  //
// Email: wangjun98@sohu.com								  //
// URL:   www.vckbase.com									  //
//															  //
// 1.0     2001/9/30   First release version.				  //
//															  //
////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"
#include "POSClient.h"
#include "CoolTabCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCoolTabCtrl

IMPLEMENT_DYNCREATE(CCoolTabCtrl, CWnd)

#define	ITEMBUTTON_HEIGHT		36

CCoolTabCtrl::CCoolTabCtrl()
{
	m_nStyle = TCS_DOWN;
	m_nActivePage = -1;
}

CCoolTabCtrl::~CCoolTabCtrl()
{
	POSITION pos;
	CPageItem* pItem;
	for(pos=m_PageList.GetHeadPosition();pos!=NULL;)
	{
		pItem=(CPageItem*)m_PageList.GetNext(pos);
		if(pItem)
		{	
			if(pItem->m_nStyle == 1 &&pItem->m_pWnd) ///Dialog
				delete pItem->m_pWnd;
			delete pItem;
			pItem=NULL;
		}
	}
	m_PageList.RemoveAll();
	DeleteObject(m_dcBk);
}


BEGIN_MESSAGE_MAP(CCoolTabCtrl, CWnd)
	//{{AFX_MSG_MAP(CCoolTabCtrl)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CCoolTabCtrl message handlers
//CFont	CCoolTabCtrl::m_font;
BOOL CCoolTabCtrl::Create(UINT wStyle, const CRect &rect, CWnd *pParentWnd, UINT nID)
{
	m_nStyle = wStyle & TCS_MASK;
	if(m_nStyle == 0)
		m_nStyle = TCS_UP;
	if (CWnd::Create(AfxRegisterWndClass(CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW, AfxGetApp()->LoadStandardCursor(IDC_ARROW), (HBRUSH)GetStockObject(LTGRAY_BRUSH), NULL),
						NULL,
						wStyle&~TCS_MASK | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
						rect, 
						pParentWnd, 
						nID))
	{
		return TRUE;
	}
	return FALSE;
}

BOOL CCoolTabCtrl::OnEraseBkgnd(CDC* pDC) 
{
	return FALSE;
}

void CCoolTabCtrl::OnPaint() 
{
	CPaintDC	dc(this);
	CPen	*pOldPen = dc.GetCurrentPen();
	int		nOldBkMode = dc.SetBkMode(TRANSPARENT);
	CPageItem	*pItem;
	POSITION	pos;
	int		nItemIndex = 0;
	
	if (m_PageList.GetSize()>=2)
	{
		CRect rect;
		GetWindowRect(&rect);
		rect.top=rect.bottom-ITEMBUTTON_HEIGHT;
		if (m_dcBk.m_hDC == NULL)
		{
			CRect rect1=rect;
			CClientDC clDC(GetParent());
			GetParent()->ScreenToClient(&rect1);
			m_dcBk.CreateCompatibleDC(&dc);
			CBitmap bmp;
			bmp.CreateCompatibleBitmap(&dc, rect1.Width(), rect1.Height());
			m_dcBk.SelectObject(&bmp);
			m_dcBk.BitBlt(0, 0, rect1.Width(), rect1.Height(), &clDC, rect1.left, rect1.top, SRCCOPY);
		}
		else
		{
			ScreenToClient(&rect);
		}
		dc.BitBlt(rect.left, rect.top, rect.Width(), rect.Height(), &m_dcBk, 0, 0, SRCCOPY);
	}
	CPageItem* pSelected=NULL;
	for(pos=m_PageList.GetHeadPosition();pos!=NULL;nItemIndex++)
	{
		pItem=(CPageItem*)m_PageList.GetNext(pos);
		if(pItem)
		{
			if (nItemIndex==m_nActivePage)
			{
				pSelected=pItem;
			}
			else
			{
				pItem->Draw(&dc,m_nStyle,FALSE);
			}
		}
	}
	pSelected->Draw(&dc,m_nStyle,TRUE);
	dc.SetBkMode(nOldBkMode);
	dc.SelectObject(pOldPen);
}

void CCoolTabCtrl::UpdateTitle(int nIndex,LPCTSTR sText)
{
	CPageItem* pItem = (CPageItem*)GetPageItem(nIndex);
	pItem->m_sText=sText;
}
void CCoolTabCtrl::AddPage(CWnd *pWnd, LPCTSTR sText, UINT IconID)
{
	ASSERT(IsWindow(pWnd->m_hWnd));
	CPageItem *pItem;
	pItem = new CPageItem();
	pItem->m_pWnd = pWnd;
	pItem->m_nStyle = 0;//Window
	pItem->m_sText = sText;
	if(IconID)
		pItem->m_hIcon = AfxGetApp()->LoadIcon(IconID);
	else
		pItem->m_hIcon = NULL;
	if(pWnd)
	{
		CRect	rect;
		GetClientRect(rect);
		pWnd->MoveWindow(rect);
	}
	m_PageList.AddTail(pItem);
}
void CCoolTabCtrl::RemovePage(int nIndex)
{
	CPageItem *pItem = NULL;
	POSITION pos = m_PageList.FindIndex(nIndex);
	if(pos)
	{
		pItem = (CPageItem*)m_PageList.GetAt(pos);
		m_PageList.RemoveAt(pos);
		if(pItem)
		{
 			if(pItem->m_pWnd) ///Dialog
			{
				pItem->m_pWnd->ShowWindow(SW_HIDE);
			}
			DestroyIcon(pItem->m_hIcon);
			delete pItem;
			pItem=NULL;
		}
	}
}
int CCoolTabCtrl::GetPageCount()
{
	return m_PageList.GetCount();
}
int CCoolTabCtrl::GetActivePageIndex()
{
	return m_nActivePage;
}
CWnd* CCoolTabCtrl::GetActivePage()
{
	CPageItem *pItem = NULL;
	POSITION pos = m_PageList.FindIndex(m_nActivePage);
	if(pos)
	{
		pItem = (CPageItem*)m_PageList.GetAt(pos);
		return pItem->m_pWnd;
	}
	else 
		return NULL;
}
BOOL CCoolTabCtrl::AddPage(CRuntimeClass* pClass,UINT nIDTemplate, LPCTSTR sText, UINT IconID)
{
	CDialog *pDlg = (CDialog*)pClass->CreateObject();
	if(pDlg != NULL)
		if(pDlg->Create(nIDTemplate,this))
		{
			CPageItem *pItem;
			pItem = new CPageItem();
			pItem->m_pWnd = (CWnd*)pDlg;
			pItem->m_nStyle = 1;///Dialog
			pItem->m_sText = sText;
			if(IconID)
				pItem->m_hIcon = AfxGetApp()->LoadIcon(IconID);
			else
				pItem->m_hIcon = NULL;
			CRect	rect;
			GetClientRect(rect);
			pDlg->MoveWindow(rect);
			m_PageList.AddTail(pItem);
			return TRUE;
		}
	return FALSE;
}


void CCoolTabCtrl::GetClientRect(LPRECT lpRect)
{
	CWnd::GetClientRect(lpRect);
	if(m_nStyle&TCS_DOWN)
	{
		lpRect->left += 2;
		lpRect->right -= 1;
		lpRect->top += 1;
		lpRect->bottom -= ITEMBUTTON_HEIGHT;
	}
	else if(m_nStyle&TCS_UP)
	{
		lpRect->left += 2;
		lpRect->right -= 1;
		lpRect->top += ITEMBUTTON_HEIGHT;
		lpRect->bottom -= 1;
	}
}

///////取得需要占用的宽度/////
UINT CCoolTabCtrl::CPageItem::GetAreaWidth(CDC *pDC)
{
	UINT width = pDC->GetTextExtent(m_sText).cx;
	if(m_hIcon)
		width += 18;
	return width + 9;
}
void CCoolTabCtrl::CPageItem::ComputeRgn()
{
	m_rgn.DeleteObject();
	int diff=m_rect.Height()/4;
	CRgn round,leftTriangle,rigthTriangle;
	round.CreateRoundRectRgn(m_rect.left,m_rect.top,m_rect.right-diff+1,m_rect.bottom+1,4,4);
	CPoint rightPoints[3];
	rightPoints[0]= CPoint(m_rect.right+diff, m_rect.top);
	rightPoints[1]= CPoint(m_rect.right-diff-1, m_rect.bottom-2);
	rightPoints[2]= CPoint(m_rect.right-diff-4, m_rect.top);
	rigthTriangle.CreatePolygonRgn(rightPoints, 3, ALTERNATE);
	m_rgn.CreateRectRgn( 0, 0, 50, 50 );
	m_rgn.CombineRgn(&round,&rigthTriangle,RGN_OR);
}
void CCoolTabCtrl::CPageItem::Draw(CDC *pDC, UINT nStyle, BOOL bActive)
{
	try{
		if (m_rect.Width()<=0)
			return;
		CBrush boder_brush(RGB(102,54,31));
		CRect rect = m_rect;
		if(bActive)
		{
			COLORREF bgColor =RGB(254,247,235);
			CBrush brush(bgColor);
			pDC->FillRgn(&m_rgn, &brush);
			pDC->FrameRgn(&m_rgn, &boder_brush,1,1);
			//line
			CPen m_Pen1(PS_SOLID,2,bgColor);
			pDC->SelectObject(&m_Pen1);
			pDC->MoveTo(m_rect.left+2,m_rect.top);
			pDC->LineTo(m_rect.right+m_rect.Height()/4-2,m_rect.top);
		}
		else
		{
			COLORREF bgColor =RGB(215, 215, 215) ;
			CBrush brush(bgColor);
			pDC->FillRgn(&m_rgn, &brush);
			pDC->FrameRgn(&m_rgn, &boder_brush,1,1);
		}
		if(!bActive)
		{
			//pDC->LineTo(rect.left-rect.Height()/3,rect.top);
		}
		///////////调整位置//////////
		rect.left += 2;
		rect.right -= 2;
		///////////显示图标//////////
		if(rect.Width() > 16 && m_hIcon != NULL)
		{
			::DrawIconEx(pDC->m_hDC,rect.left,rect.top + 3,m_hIcon,32,32,0,NULL,DI_NORMAL);
			rect.left += 18;
		}
		if (!m_sText.IsEmpty())
		{
			if (bActive)
			{
				rect.top += 3;
				pDC->SetTextColor(RGB(0,0,0));
				static CFont l_font;
				if(l_font.m_hObject==NULL)
				{
					LOGFONT logFont;
					GetObject(::GetStockObject(DEFAULT_GUI_FONT),sizeof(logFont),&logFont);
					logFont.lfHeight=30;
					logFont.lfWeight=FW_BOLD;
					l_font.CreateFontIndirect(&logFont);
				}
				pDC->SelectObject(&(l_font));
			}
			else
			{
				rect.top += 5;
				pDC->SetTextColor(RGB(255,255,255));
				static CFont s_font;
				if(s_font.m_hObject==NULL)
				{
					LOGFONT logFont;
					GetObject(::GetStockObject(DEFAULT_GUI_FONT),sizeof(logFont),&logFont);
					logFont.lfHeight=24;
					logFont.lfWeight=FW_BOLD;
					s_font.CreateFontIndirect(&logFont);
				}
				pDC->SelectObject(&(s_font));
			}
			pDC->DrawText(m_sText, &rect, DT_CENTER| DT_SINGLELINE);

		}
	}catch(...)
	{
	}
}


////调整尺寸////
void CCoolTabCtrl::AutoSize()
{
	UINT PageCount = m_PageList.GetCount();
	if(PageCount < 1) return;

	CPageItem	*pItem;
	POSITION	pos;
	CRect		rect,ClientRect,ItemRect;

	GetClientRect(ClientRect);
	GetWindowRect(rect);
	ScreenToClient(rect);
	//只有一页时不需要标签页
	if (PageCount==1)
	{
		pItem=(CPageItem*)m_PageList.GetHead();
		if(pItem)
		{
			pItem->m_rect = CRect(0,0,0,0);
			if(pItem->m_pWnd)
				pItem->m_pWnd->MoveWindow(ClientRect);
		}
		return;
	}

	CDC* pDC = GetDC();
	if (pDC==NULL)
		return;

	if(m_nStyle&TCS_DOWN)
	{
		rect.bottom -= 1;
		rect.top = rect.bottom - ITEMBUTTON_HEIGHT + 1;
		rect.left += 1;
		rect.right -= 6;
	}
	else if(m_nStyle&TCS_UP)
	{
		rect.left += 2;
		rect.right -= 6;
		rect.bottom = rect.top + ITEMBUTTON_HEIGHT;
	}
	ItemRect = rect;
	int AreaWidth = 0,ItemMaxWidth,ItemIndex=0;
	ItemMaxWidth = rect.Width()/m_PageList.GetCount();
	BOOL	bMonoSpace = TRUE;//((m_nStyle&TCS_MONOSPACE) == TCS_MONOSPACE)?1:0;
	////////设置按钮初始宽度，并得到按钮所需占用的总宽度///////
	for(pos=m_PageList.GetHeadPosition();pos!=NULL;ItemIndex++)
	{
		pItem=(CPageItem*)m_PageList.GetNext(pos);
		if(pItem)
		{
			if(!bMonoSpace)
				ItemMaxWidth = pItem->GetAreaWidth(pDC);
			AreaWidth += ItemMaxWidth;
			ItemRect.right = ItemRect.left+ItemMaxWidth-1;
			pItem->m_rect = ItemRect;
			ItemRect.left = ItemRect.right + 1;
			if(pItem->m_pWnd)
				pItem->m_pWnd->MoveWindow(ClientRect);
			pItem->ComputeRgn();
		}
	}
	////////当需要的空间大于实际空间时进行调整////
	if(AreaWidth > rect.Width() && !bMonoSpace)
	{
		ItemRect = rect;
		int AreaWidth,MaxWidth = rect.Width()/PageCount;
		for(pos=m_PageList.GetHeadPosition();pos!=NULL;)
		{
			pItem=(CPageItem*)m_PageList.GetNext(pos);
			if(pItem)
			{
				AreaWidth = pItem->GetAreaWidth(pDC);
				ItemMaxWidth = (ItemMaxWidth < AreaWidth)?MaxWidth:AreaWidth;
				ItemRect.right = ItemRect.left+ItemMaxWidth;
				pItem->m_rect = ItemRect;
				ItemRect.left = ItemRect.right + 1;
			}
		}
	}
//	pDC->SelectObject(pOldFont);
	ReleaseDC(pDC);
}
void CCoolTabCtrl::SetActivePage(int nIndex,BOOL bRedraw)
{
	if(nIndex == m_nActivePage&&bRedraw==FALSE)
		return;
	CPageItem *pOldItem,*pItem;
	if(m_nActivePage >= 0)
	{
		pOldItem = (CPageItem*)GetPageItem(m_nActivePage);
		if(pOldItem)
		{
			pOldItem->m_pWnd->ShowWindow(SW_HIDE);
		}
	}
	pItem = (CPageItem*)GetPageItem(nIndex);
	if(!pItem) return;
	m_nActivePage = nIndex;
	pItem->m_pWnd->ShowWindow(SW_SHOW);
}

void* CCoolTabCtrl::GetPageItem(UINT nIndex)
{
	CPageItem *pItem = NULL;
	POSITION pos = m_PageList.FindIndex(nIndex);
	if(pos)
		pItem = (CPageItem*)m_PageList.GetAt(pos);
	return pItem;
}
BOOL CCoolTabCtrl::DisablePage(UINT nIndex,BOOL bDisable)
{
	CPageItem* pItem = (CPageItem*)GetPageItem(nIndex);
	if(!pItem)
		return FALSE;
	if(bDisable)
	{
		pItem->m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON_STOP);
		pItem->m_pWnd->SendMessage(WM_MESSAGE_ENABLE,FALSE);
	}
	else
	{
		pItem->m_hIcon =NULL;
		pItem->m_pWnd->SendMessage(WM_MESSAGE_ENABLE,TRUE);
	}
	return TRUE;
}
void CCoolTabCtrl::UpdateWindow()
{
 	AutoSize();
 	if(m_nActivePage < 0)
 		SetActivePage(0);
 	else
 		SetActivePage(m_nActivePage);
 	Invalidate();
}

void CCoolTabCtrl::OnLButtonDown(UINT nFlags, CPoint point) 
{
	UINT nItemIndex=0;
	POSITION pos;
	CPageItem *pItem;
	for(pos=m_PageList.GetHeadPosition();pos!=NULL;nItemIndex++)
	{
		pItem=(CPageItem*)m_PageList.GetNext(pos);
		if(pItem)
		{
			if(pItem->m_rect.PtInRect(point))
			{
				SetActivePage(nItemIndex);
				Invalidate();
				break;
			}
		}
	}
	CWnd::OnLButtonDown(nFlags, point);
}

void CCoolTabCtrl::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy);
	AutoSize();
}
