// NumberInputDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "POSClient.h"
#include "NumberInputDlg.h"
//#include "deelx.h"

// NumberInputDlg 对话框

IMPLEMENT_DYNAMIC(NumberInputDlg, CDialog)

NumberInputDlg::NumberInputDlg(CWnd* pParent /*=NULL*/)
	: CDialog(NumberInputDlg::IDD, pParent)
{
	m_bPassword=FALSE;
	m_bSwipe=FALSE;
}

NumberInputDlg::~NumberInputDlg()
{
	m_btnCtrl.ReleaseBtn();
	::DeleteObject(m_bpBackgrd);
}

void NumberInputDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_HINT, m_hint);
}


BEGIN_MESSAGE_MAP(NumberInputDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_OK, &NumberInputDlg::OnBnClickedOK)
	ON_COMMAND_RANGE(IDC_BUTTON0,IDC_BUTTON9,OnNumBnClicked)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, &NumberInputDlg::OnBnClickedButtonClear)
	ON_BN_CLICKED(IDC_BUTTON00, &NumberInputDlg::OnBnClickedButton00)
	ON_BN_CLICKED(IDC_BUTTON10, &NumberInputDlg::OnBnClickedButton10)
	ON_BN_CLICKED(IDC_BUTTON20, &NumberInputDlg::OnBnClickedButton20)
	ON_BN_CLICKED(IDC_BUTTON50, &NumberInputDlg::OnBnClickedButton50)
	ON_BN_CLICKED(IDC_BUTTON100, &NumberInputDlg::OnBnClickedButton100)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, &NumberInputDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON_DOT, &NumberInputDlg::OnBnClickedButtonDot)
	ON_WM_SIZE()
	ON_WM_CTLCOLOR()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// NumberInputDlg 消息处理程序

BOOL NumberInputDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_hint.SetWindowText(m_strHint);
	static CImage img;
	if(img.Load(_T("Picture\\num.png"))==S_OK)
	{
		m_x=img.GetWidth();
		m_y=img.GetHeight();
		m_bpBackgrd=img.Detach();
	}
	CRect rect=m_btnCtrl.GenaratePage2(_T("Page\\IDD_NUM.ini"),this);
	rect.bottom+=20;
	rect.right+=20;
	MoveWindow(rect);
	theLang.UpdatePage(this,_T("DEFAULT"),TRUE);
	this->CenterWindow();
	this->SetFocus();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
void  NumberInputDlg::OnNumBnClicked(UINT uID)
{
	static int last_clock=0;
	int now=clock();
	if(last_clock>0)
	{
		if (now-last_clock<50)
		{
			m_bSwipe=TRUE;
		}
		else
		{
			m_bSwipe=FALSE;
		}
	}
	last_clock=now;
	char num='0'+uID-IDC_BUTTON0;
	if (m_strNum.GetLength()>30)
		return;
	m_strNum+=num;
	if(!m_bPassword)
		m_hint.SetWindowText(m_strNum);
	else
	{
		CString tmp;
		for (int i=0;i<m_strNum.GetLength();i++)
		{
			tmp.AppendChar('*');
		}
		m_hint.SetWindowText(tmp);
	}
	UpdateHintData();
}
void NumberInputDlg::OnBnClickedButton00()
{
	m_strNum+="00";
	if(!m_bPassword)
		m_hint.SetWindowText(m_strNum);
	UpdateHintData();
}
void NumberInputDlg::OnBnClickedButton10()
{
	m_strNum="10";
	if(!m_bPassword)
		m_hint.SetWindowText(m_strNum);
	UpdateHintData();
}
void NumberInputDlg::OnBnClickedButton20()
{
	m_strNum="20";
	if(!m_bPassword)
		m_hint.SetWindowText(m_strNum);
	UpdateHintData();
}
void NumberInputDlg::OnBnClickedButton50()
{
	m_strNum="50";
	if(!m_bPassword)
		m_hint.SetWindowText(m_strNum);
	UpdateHintData();
}
void NumberInputDlg::OnBnClickedButton100()
{
	m_strNum="100";
	if(!m_bPassword)
		m_hint.SetWindowText(m_strNum);
	UpdateHintData();
}
void NumberInputDlg::OnBnClickedButtonDot()
{
	m_strNum+=".";
	if(!m_bPassword)
		m_hint.SetWindowText(m_strNum);
	UpdateHintData();
}
void NumberInputDlg::OnBnClickedButtonClear()
{
	m_bSwipe=FALSE;
	m_strNum.Empty();
	m_hint.SetWindowText(m_strHint);
	UpdateHintData();
}
void NumberInputDlg::OnBnClickedOK()
{
	m_bSwipe=FALSE;//标志位，表明不是刷卡
	CDialog::OnOK();
}
void NumberInputDlg::OnBnClickedCancel()
{
	CDialog::OnCancel();
}
void NumberInputDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	if (m_hint.m_hWnd)
	{
		m_hint.MoveWindow(30,45,cx-60,50);
	}
}

BOOL NumberInputDlg::OnEraseBkgnd(CDC* pDC)
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
HBRUSH NumberInputDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	if(nCtlColor==CTLCOLOR_STATIC)
	{
		pDC->SetTextColor(DEFALUT_TXT_COLOR);
		pDC->SetBkMode(TRANSPARENT);
		return (HBRUSH)::GetStockObject(NULL_BRUSH); //返回此画刷可以使静态文本透明
	}
	return   hbr; 
	
}
void NumberInputDlg::UpdateHintData()
{
	CRect   rc;
	m_hint.GetWindowRect(&rc);    
	ScreenToClient(&rc);
	InvalidateRect(rc); 
}
BOOL NumberInputDlg::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message==WM_KEYDOWN)
	{
		if(pMsg->wParam==VK_PROCESSKEY)
		{
			pMsg->wParam=ImmGetVirtualKey(this->m_hWnd);
		}
		if (pMsg->wParam>='0'&&pMsg->wParam<='9')
		{
			OnNumBnClicked(pMsg->wParam-'0'+IDC_BUTTON0);
			return TRUE;
		}
		else if (pMsg->wParam>=VK_NUMPAD0&&pMsg->wParam<=VK_NUMPAD9)
		{
			OnNumBnClicked(pMsg->wParam-VK_NUMPAD0+IDC_BUTTON0);
			return TRUE;
		}
		else if (pMsg->wParam==VK_DECIMAL)
		{
			OnBnClickedButtonDot();
			return TRUE;
		}
		else if (pMsg->wParam==VK_DELETE||pMsg->wParam==VK_BACK)
		{
			OnBnClickedButtonClear();
			return TRUE;
		}
		else if (pMsg->wParam==VK_RETURN)
		{
			
			//return TRUE; 继续处理回车
		}
	}

	return CDialog::PreTranslateMessage(pMsg);
}
