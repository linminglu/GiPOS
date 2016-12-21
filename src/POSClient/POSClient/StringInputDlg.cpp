// StringInputDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "POSClient.h"
#include "StringInputDlg.h"



// StringInputDlg 对话框

IMPLEMENT_DYNAMIC(StringInputDlg, CDialog)

StringInputDlg::StringInputDlg(CWnd* pParent /*=NULL*/)
	: CDialog(StringInputDlg::IDD, pParent)
{
	m_bSearchMode=FALSE;
	m_bAutoComplete=FALSE;
	m_bpBackgrd=NULL;
	last_clock=0;
	m_x=1024;
	m_y=768;
}

StringInputDlg::~StringInputDlg()
{
	m_btnCtrl.ReleaseBtn();
	::DeleteObject(m_bpBackgrd);
}

void StringInputDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_ctrlEdit);
}


BEGIN_MESSAGE_MAP(StringInputDlg, CDialog)
	ON_COMMAND_RANGE(IDC_BUTTON0,IDC_BUTTON9,OnNumBnClicked)
	ON_COMMAND_RANGE(IDC_ASCII_BUTTON_A,IDC_ASCII_BUTTON_Z,OnAsciiBnClicked)
	ON_BN_CLICKED(IDC_BUTTON_OK, &StringInputDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, &StringInputDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, &StringInputDlg::OnBnClickedClear)
	ON_BN_CLICKED(IDC_BUTTON_CTRLSHIFT, &StringInputDlg::OnBnClickedCtrlShfit)
	ON_BN_CLICKED(IDC_BUTTON_HANDINPUT, &StringInputDlg::OnBnClickedCtrlHandInput)
	ON_MESSAGE(ENAC_UPDATE, &StringInputDlg::OnEnChangeEdit1)
	ON_WM_TIMER()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// StringInputDlg 消息处理程序

BOOL StringInputDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	this->SetWindowText(m_strTitle);
	if (m_strTmplate.GetLength()==0)
	{
		m_strTmplate=_T("Page\\IDD_STRING.ini");
	}
	CRect rect=m_btnCtrl.GenaratePage2(m_strTmplate,this);
	rect.bottom+=30;
	rect.right+=10;
	rect.OffsetRect(350*CreatButton::m_nFullWidth/1024,300*CreatButton::m_nFullHeight/768);
	this->MoveWindow(rect);
	theLang.UpdatePage(this,_T("IDD_STRING"),TRUE);
	CImage img;
	if(img.Load(_T("Picture\\string.png"))==S_OK)
	{
		m_x=img.GetWidth();
		m_y=img.GetHeight();
		m_bpBackgrd=img.Detach();
	}
	m_ctrlEdit.Init();
	if (m_bSearchMode)
		m_ctrlEdit.SetMode(0);
	else
		m_ctrlEdit.SetMode();
	m_ctrlEdit.SetWindowText(m_strInput);
	m_ctrlEdit.SetFocus();
	m_ctrlEdit.SetEditSel(0,m_strInput.GetLength());
	CRecentFileList* list=theApp.m_pRecentFileList;
	if(m_bAutoComplete)
	{
		for(int i=0;i<list->GetSize();i++)
			m_ctrlEdit.AddSearchString((LPCTSTR)(*list)[i]);
	}
	return FALSE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
void  StringInputDlg::OnNumBnClicked(UINT uID)
{
	int vkey=uID-IDC_BUTTON0+48;
	m_ctrlEdit.SetFocus();
	keybd_event(vkey,0,0,0);
	keybd_event(vkey,0,KEYEVENTF_KEYUP,0);
}
void StringInputDlg::OnAsciiBnClicked(UINT uID)
{
	int vkey=uID-IDC_ASCII_BUTTON_A;
	m_ctrlEdit.SetFocus();
	keybd_event(vkey,0,0,0);
	keybd_event(vkey,0,KEYEVENTF_KEYUP,0);
}

void StringInputDlg::OnBnClickedCancel()
{
	OnCancel();
}
void StringInputDlg::OnCancel()
{
	if (m_bSearchMode)
	{
		this->ShowWindow(SW_HIDE);
	}
	else
	{
		CDialog::OnCancel();
	}
}
void StringInputDlg::OnBnClickedClear()
{
	m_ctrlEdit.SetWindowText(_T(""));
	m_ctrlEdit.SetFocus();
}
void StringInputDlg::OnBnClickedCtrlShfit()
{
	m_ctrlEdit.SetFocus();
	keybd_event(VK_CONTROL,   0x1d,   0,   0); 
	keybd_event(VK_SHIFT,   0x2a,   0,   0);   
	keybd_event(VK_CONTROL,0x1d,   KEYEVENTF_KEYUP,   0); 
	keybd_event(VK_SHIFT,   0x2a,   KEYEVENTF_KEYUP,   0); 
}
void StringInputDlg::OnBnClickedCtrlHandInput()
{
	ShellExecute(GetSafeHwnd(), NULL, _T("HandInput.exe"), NULL, NULL,SW_NORMAL);
	m_ctrlEdit.SetFocus();
}
BOOL StringInputDlg::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message==WM_CHAR)
	{//限制输入的字符不包括特殊字符
		if (pMsg->wParam=='\\'||pMsg->wParam=='\''||pMsg->wParam=='\"')
		{
			return TRUE;
		}
	}
	return CDialog::PreTranslateMessage(pMsg);
}

void StringInputDlg::OnOK()
{
	StringInputDlg::OnBnClickedOk();
	if (m_bSearchMode)
	{
		ShowWindow(SW_HIDE);
	}
}
void StringInputDlg::OnBnClickedOk()
{
	BOOL bSwipe;
	int now=clock();
	if (now-last_clock<50)
	{
		bSwipe=TRUE;
	}
	else
	{
		bSwipe=FALSE;
	}
	m_ctrlEdit.GetWindowText(m_strInput);
	if (m_bSearchMode)
	{//回车消息
		if(!m_strInput.IsEmpty())
		{
			KillTimer(1001);
			::SendMessage(GetParent()->GetSafeHwnd(),WM_MESSAGE_SEARCH,1,bSwipe);
			m_ctrlEdit.SetWindowText(_T(""));
		}
	}
	else
	{
		CDialog::OnOK();
	}
}
/************************************************************************
延迟搜索
/************************************************************************/
void StringInputDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent==1001)
	{
		KillTimer(1001);
		m_ctrlEdit.GetWindowText(m_strInput);
		if(m_strInput.GetLength()!=0)
			::SendMessage(GetParent()->GetSafeHwnd(),WM_MESSAGE_SEARCH,NULL,NULL);
	}
	CDialog::OnTimer(nIDEvent);
}
LRESULT StringInputDlg::OnEnChangeEdit1(WPARAM wParam, LPARAM lParam)
{
	if (m_bSearchMode&&wParam==EN_UPDATE)
	{
		last_clock=clock();
		KillTimer(1001);
		SetTimer(1001,500,NULL);//0.5秒后开始搜索
	}
	return 0;
}
BOOL StringInputDlg::OnEraseBkgnd(CDC* pDC)
{
	if (m_bpBackgrd==NULL)
	{
		return CDialog::OnEraseBkgnd(pDC);
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