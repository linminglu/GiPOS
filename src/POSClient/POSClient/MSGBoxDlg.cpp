// MSGBoxDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "POSClient.h"
#include "MSGBoxDlg.h"


// MSGBoxDlg 对话框

IMPLEMENT_DYNAMIC(MSGBoxDlg, CDialog)

MSGBoxDlg::MSGBoxDlg(CWnd* pParent /*=NULL*/)
	: CDialog(MSGBoxDlg::IDD, pParent)
{
	m_nType=0;
	m_bpBackgrd=NULL;
}

MSGBoxDlg::~MSGBoxDlg()
{
	::DeleteObject(m_bpBackgrd);
}

void MSGBoxDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDOK, m_btOK);
	DDX_Control(pDX, IDCANCEL, m_btCancel);
	DDX_Control(pDX, IDC_STATIC2, m_hintCtrl);
}


BEGIN_MESSAGE_MAP(MSGBoxDlg, CDialog)
	ON_WM_CTLCOLOR()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// MSGBoxDlg 消息处理程序

BOOL MSGBoxDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	SetWindowPos(NULL,0,0,ScaleX(462),ScaleY(212),SWP_NOZORDER|SWP_NOMOVE);
	m_hintCtrl.SetWindowText(m_strText);
	int x=ScaleX(122);
	int y=ScaleY(58);
	CImage imgB;
	if(imgB.Load(_T("Picture\\bg_message.png"))==S_OK)
	{
		m_x=imgB.GetWidth();
		m_y=imgB.GetHeight();
		m_bpBackgrd=imgB.Detach();
	}
	if (!theLang.m_bDefaultLang)
	{
		SetFont(&theLang.m_dialogFont);
		CWnd* pCtrl=GetDlgItem(IDOK);
		theLang.TranslateDlgItem(pCtrl,181);
		pCtrl=GetDlgItem(IDCANCEL);
		theLang.TranslateDlgItem(pCtrl,182);
	}
	m_btOK.SetImage(_T("Picture\\bt_ok.png"));
	if (m_nType==MB_OK)
	{
		m_btOK.MoveWindow(ScaleX(170),ScaleY(130),x,y);
		m_btCancel.ShowWindow(SW_HIDE);
	}
	else if (m_nType==MB_YESNO)
	{
		m_btCancel.SetImage(_T("Picture\\bt_cancel.png"));
		m_btOK.MoveWindow(ScaleX(100),ScaleY(130),x,y);
		m_btCancel.MoveWindow(ScaleX(118)+x,ScaleY(130),x,y);
	}
	if (!m_strYes.IsEmpty())
		m_btOK.SetWindowText(m_strYes);
	if (!m_strNo.IsEmpty())
		m_btCancel.SetWindowText(m_strNo);
	m_btOK.SetTextColor(DEFALUT_TXT_COLOR);
	m_btCancel.SetTextColor(DEFALUT_TXT_COLOR);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
HBRUSH MSGBoxDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	if(nCtlColor==CTLCOLOR_STATIC)
	{
		pDC->SetTextColor(m_dTextColor);
		pDC->SetBkMode(TRANSPARENT);
		return (HBRUSH)::GetStockObject(NULL_BRUSH); //返回此画刷可以使静态文本透明
	}
	return   hbr; 
	
}
BOOL MSGBoxDlg::OnEraseBkgnd(CDC* pDC)
{
	if (m_bpBackgrd==NULL)
	{
		return FALSE;
	}
	CRect rect;
	GetClientRect(&rect);
	CDC MemDc;
	MemDc.CreateCompatibleDC(pDC);
	MemDc.SelectObject(m_bpBackgrd);
	pDC->SetStretchBltMode(HALFTONE);
	pDC->StretchBlt(0,0,rect.Width(),rect.Height(),&MemDc,0,0,m_x,m_y,SRCCOPY);
	return TRUE;
}
