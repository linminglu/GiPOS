// ProgressDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "POSClient.h"
#include "ProgressDlg.h"


// ProgressDlg 对话框

IMPLEMENT_DYNAMIC(ProgressDlg, CDialog)

ProgressDlg::ProgressDlg(CWnd* pParent /*=NULL*/)
	: CDialog(ProgressDlg::IDD, pParent)
{
	m_nStep=10;
}

ProgressDlg::~ProgressDlg()
{
}

void ProgressDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRESS1, mProgress);
	DDX_Control(pDX, IDC_STATIC2, mCtrlHint);
}


BEGIN_MESSAGE_MAP(ProgressDlg, CDialog)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// ProgressDlg 消息处理程序

void ProgressDlg::OnTimer(UINT_PTR nIDEvent)
{
 	if (nIDEvent==1001)
 	{
		Step(m_nStep,_T(""));
 	}

	CDialog::OnTimer(nIDEvent);
}
void ProgressDlg::Reset()
{
	mProgress.SetPos(0);
}
void ProgressDlg::Step(int nPos,CString msg)
{
	int curr=mProgress.GetPos();
	mProgress.SetPos(curr+nPos);
	if(!msg.IsEmpty())
		mCtrlHint.SetWindowText(msg);
	Invalidate();
}
void ProgressDlg::Start()
{
	Reset();
	CString str2;
	theLang.LoadString(str2,IDS_DOWNLOAD);
	mCtrlHint.SetWindowText(str2);
	ShowWindow(SW_SHOW);
	SetTimer(1001,1000,NULL);//设置进度条更新时钟
}
void ProgressDlg::Stop()
{
	KillTimer(1001);
	ShowWindow(SW_HIDE);
}
BOOL ProgressDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
