// TipsAddDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "POSClient.h"
#include "TipsAddDlg.h"


// TipsAddDlg 对话框

IMPLEMENT_DYNAMIC(TipsAddDlg, CDialog)

TipsAddDlg::TipsAddDlg(CWnd* pParent /*=NULL*/)
	: CDialog(TipsAddDlg::IDD, pParent)
{
	m_fTips=0;
	m_fChange=0;
}

TipsAddDlg::~TipsAddDlg()
{
}

void TipsAddDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_AMOUNT, mCtrlTotal);
	DDX_Control(pDX, IDC_STATIC_1, mCtrlChange);
	DDX_Control(pDX, IDC_STATIC_PAYED, mCtrlPayed);
	DDX_Control(pDX, IDC_EDIT1, mCtrlTips);
	DDX_Control(pDX, IDOK, m_btOK);
	DDX_Control(pDX, IDCANCEL, m_btCancel);
}


BEGIN_MESSAGE_MAP(TipsAddDlg, CDialog)
	ON_BN_CLICKED(IDOK, &TipsAddDlg::OnBnClickedOk)
	ON_COMMAND_RANGE(IDC_BUTTON0,IDC_BUTTON9,OnNumBnClicked)
	ON_BN_CLICKED(IDC_BUTTON_DOT, &TipsAddDlg::OnBnClickedButtonDot)
	ON_BN_CLICKED(IDC_BUTTON_DEL, &TipsAddDlg::OnBnClickedButtonDel)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	ON_EN_CHANGE(IDC_EDIT1, &TipsAddDlg::OnEnChangeEdit1)
END_MESSAGE_MAP()


// TipsAddDlg 消息处理程序

BOOL TipsAddDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	decPlace.Format(_T("%%0.%df"),theApp.DECIMAL_PLACES);
	CString str;
	str.Format(decPlace,m_fTotal);
	mCtrlTotal.SetWindowText(str);
	str.Format(decPlace,m_fPayed);
	mCtrlPayed.SetWindowText(str);
	m_fTips=m_fPayed-m_fTotal;
	str.Format(decPlace,m_fTips);
	mCtrlTips.SetWindowText(str);
	mCtrlTips.SetSel(0,str.GetLength());
	m_btOK.SetImage(_T("Picture\\bt_ok.png"));
	m_btCancel.SetImage(_T("Picture\\bt_cancel.png"));
	m_btOK.SetTextColor(DEFALUT_TXT_COLOR);
	m_btCancel.SetTextColor(DEFALUT_TXT_COLOR);

	theLang.LoadString(IDS_OK,str);
	m_btOK.SetWindowText(str);
	theLang.LoadString(IDS_CANCEL,str);
	m_btCancel.SetWindowText(str);
	CWnd* pCtrl=GetDlgItem(IDC_STATIC1);
	theLang.LoadString(IDS_TOTAL,str);
	pCtrl->SetWindowText(str);
	pCtrl=GetDlgItem(IDC_STATIC2);
	theLang.LoadString(IDS_TIPS,str);
	pCtrl->SetWindowText(str);
	pCtrl=GetDlgItem(IDC_STATIC3);
	theLang.LoadString(IDS_ACTUALM,str);
	pCtrl->SetWindowText(str);
	pCtrl=GetDlgItem(IDC_STATIC4);
	theLang.LoadString(IDS_CHANGE,str);
	pCtrl->SetWindowText(str);

	mCtrlTips.SetFocus();
	return FALSE;  // return TRUE unless you set the focus to a control
}
void TipsAddDlg::OnBnClickedOk()
{
	OnOK();
}

void  TipsAddDlg::OnNumBnClicked(UINT uID)
{
	int vkey=uID-IDC_BUTTON0+48;
	::SetFocus(hOld);
	keybd_event(vkey,0,0,0);
	keybd_event(vkey,0,KEYEVENTF_KEYUP,0);
}

void TipsAddDlg::OnBnClickedButtonDot()
{
	::SetFocus(hOld);
	keybd_event(VK_DECIMAL,0,0,0);
	keybd_event(VK_DECIMAL,0,KEYEVENTF_KEYUP,0);
}

void TipsAddDlg::OnBnClickedButtonDel()
{
	::SetFocus(hOld);
	keybd_event(VK_BACK,0,0,0);
	keybd_event(VK_BACK,0,KEYEVENTF_KEYUP,0);
}

BOOL   TipsAddDlg::PreTranslateMessage(MSG*   pMsg)   
{
	if(pMsg-> message   ==   WM_LBUTTONDOWN) 
	{
		hOld   =   ::GetFocus(); 
	}
	return   CDialog::PreTranslateMessage(pMsg); 
} 
HBRUSH TipsAddDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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
void TipsAddDlg::OnPaint()
{
	if(!IsIconic())
	{
		CRect   rect;
		CPaintDC   dc(this);
		GetClientRect(rect);
		dc.FillSolidRect(rect,DEFALUT_BACKGROUND_COLOR);
		CDialog::OnPaint();
	}
}
void TipsAddDlg::OnEnChangeEdit1()
{
	CString text;
	mCtrlTips.GetWindowText(text);
	m_fTips=_wtof(text);
	m_fChange=m_fPayed-m_fTotal-m_fTips;
	if(abs(m_fChange)<0.01)
	{
		m_fChange=0;
		m_fTips=m_fPayed-m_fTotal;
	}
	text.Format(decPlace,m_fChange);
	mCtrlChange.SetWindowText(text);
	Invalidate();
}
