// OpenTableDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "POSClient.h"
#include "OpenTableDlg.h"


// COpenTableDlg 对话框

IMPLEMENT_DYNAMIC(COpenTableDlg, CDialog)

COpenTableDlg::COpenTableDlg(CWnd* pParent /*=NULL*/)
	: CDialog(COpenTableDlg::IDD, pParent)
	, m_strGst(_T(""))
	, m_strRemark(_T(""))
{

}

COpenTableDlg::~COpenTableDlg()
{
	m_btnCtrl.ReleaseBtn();
	::DeleteObject(m_bpBackgrd);
}

void COpenTableDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT3, m_strGst);
	DDX_Text(pDX, IDC_EDIT4, m_strRemark);
}


BEGIN_MESSAGE_MAP(COpenTableDlg, CDialog)
	//ON_BN_CLICKED(IDC_BUTTON_OK, OnBnClickedOK)
	ON_COMMAND_RANGE(IDC_BUTTON0,IDC_BUTTON9,OnNumBnClicked)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, OnBnClickedButtonClear)
	//ON_BN_CLICKED(IDC_BUTTON_CANCEL, OnBnClickedCancel)
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// COpenTableDlg 消息处理程序
BOOL COpenTableDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	static CImage img;
	m_strTmplate=_T("Page\\IDD_OPENTBL.ini");
	if(img.Load(_T("Picture\\bg_opentbl.png"))==S_OK)
	{
		m_x=img.GetWidth();
		m_y=img.GetHeight();
		m_bpBackgrd=img.Detach();
	}
	if (!theLang.m_bDefaultLang)
	{
		//SetFont(&theLang.m_dialogFont);
		CString str2;
		CWnd* pCtrl=GetDlgItem(IDC_STATIC1);
		theLang.LoadString(IDS_GUESTNUM2,str2);
		pCtrl->SetWindowText(str2);
		pCtrl=GetDlgItem(IDC_STATIC2);
		theLang.LoadString(IDS_REMARK,str2);
		pCtrl->SetWindowText(str2);
	}
	CRect rect=m_btnCtrl.GenaratePage2(m_strTmplate,this);
	rect.bottom+=20;
	rect.right+=20;
	MoveWindow(rect);
	theLang.UpdatePage(this,_T("DEFAULT"),TRUE);
	this->CenterWindow();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
void  COpenTableDlg::OnNumBnClicked(UINT uID)
{
	int vkey=uID-IDC_BUTTON0+48;
	::SetFocus(hOld);
	keybd_event(vkey,0,0,0);
	keybd_event(vkey,0,KEYEVENTF_KEYUP,0);
}
void COpenTableDlg::OnBnClickedButtonClear()
{
	::SetFocus(hOld);
	keybd_event(VK_BACK,0,0,0);
	keybd_event(VK_BACK,0,KEYEVENTF_KEYUP,0);
}
void COpenTableDlg::OnOK()
{
	if(macrosInt[_T("OPEN_TABLE_GUEST")]==2)
	{
		CString text;
		((CEdit*)GetDlgItem(IDC_EDIT3))->GetWindowText(text);
		int num=_wtoi(text);
		if(num<=0)
			return;
	}
	CDialog::OnOK();
}
void COpenTableDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
}

BOOL COpenTableDlg::OnEraseBkgnd(CDC* pDC)
{
	if (m_bpBackgrd==NULL)
	{
		return FALSE;
	}
	CRect rect;
	GetClientRect(&rect);
	CDC MemDc;
	MemDc.CreateCompatibleDC(pDC);
	HGDIOBJ hOldBmp = MemDc.SelectObject(m_bpBackgrd);
	pDC->SetStretchBltMode(HALFTONE);
	pDC->StretchBlt(0,0,rect.right,rect.bottom,&MemDc,0,0,m_x,m_y,SRCCOPY);
	MemDc.SelectObject(hOldBmp);
	return TRUE;
}

BOOL   COpenTableDlg::PreTranslateMessage(MSG*   pMsg)   
{ 
	if(pMsg-> message   ==   WM_LBUTTONDOWN) 
	{ 
		hOld   =   ::GetFocus(); 
	} 
	return   CDialog::PreTranslateMessage(pMsg); 
} 
HBRUSH COpenTableDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	if(nCtlColor==CTLCOLOR_STATIC)
	{
		 pDC->SetTextColor(m_dTextColor);
		pDC->SetBkMode(TRANSPARENT);
		return (HBRUSH)::GetStockObject(NULL_BRUSH); //返回此画刷可以使静态文本透明
	}
	return hbr;
}