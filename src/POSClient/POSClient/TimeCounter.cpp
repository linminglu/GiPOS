// TimeCounter.cpp : 实现文件
//

#include "stdafx.h"
#include "POSClient.h"
#include "TimeCounter.h"


// TimeCounter 对话框

IMPLEMENT_DYNAMIC(TimeCounter, CDialog)

TimeCounter::TimeCounter(CWnd* pParent /*=NULL*/)
	: CDialog(TimeCounter::IDD, pParent)
{
	m_nCount=5;
}

TimeCounter::~TimeCounter()
{
}

void TimeCounter::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDOK, m_btOK);
	DDX_Control(pDX, IDC_STATIC2, m_hintCtrl);
	DDX_Control(pDX, IDC_STATIC_1, m_ctrlTime);
}


BEGIN_MESSAGE_MAP(TimeCounter, CDialog)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDOK, &TimeCounter::OnBnClickedOk)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// TimeCounter 消息处理程序

BOOL TimeCounter::OnInitDialog()
{
	CDialog::OnInitDialog();
	//SetWindowPos(NULL,0,0,462,212,SWP_NOZORDER|SWP_NOMOVE);
	m_hintCtrl.SetWindowText(m_strText);
	CImage img,img1;
	if(img.Load(_T("Picture\\bg_message.png"))==S_OK)
	{
		CStatic* pWnd = (CStatic*)GetDlgItem(IDC_STATIC1);
		pWnd->SetBitmap(img.Detach());
	}
	if (!theLang.m_bDefaultLang)
	{
		SetFont(&theLang.m_dialogFont);
		CWnd* pCtrl=GetDlgItem(IDC_STATIC_2);
		theLang.TranslateDlgItem(pCtrl,IDS_SENCONDCLOSE);
		pCtrl=GetDlgItem(IDOK);
		theLang.TranslateDlgItem(pCtrl,IDS_OK);
	}
	m_btOK.SetImage(_T("Picture\\bt_ok.png"));
	if(m_nCount>0)
	{
		LOGFONT m_tLogFont;
		memset(&m_tLogFont,0,sizeof(LOGFONT));
		m_tLogFont.lfHeight = ScaleY(18);
		wcscpy_s(m_tLogFont.lfFaceName, _T("Microsoft YaHei"));
		m_font.CreateFontIndirect(&m_tLogFont);
		m_ctrlTime.SetFont(&m_font);
		CString msg;
		msg.Format(_T("%d"),m_nCount);
		m_ctrlTime.SetWindowText(msg);
		GetDlgItem(IDC_STATIC_2)->SetFont(&m_font);
		SetTimer(1003,1000,NULL);
	}
	else
	{
		m_ctrlTime.ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_2)->ShowWindow(SW_HIDE);
	}
 	m_btOK.SetTextColor(DEFALUT_TXT_COLOR);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
HBRUSH TimeCounter::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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
void TimeCounter::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	OnOK();
}

void TimeCounter::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent==1003)
	{
		if (m_nCount>1)
		{
			m_nCount--;
			CString msg;
			msg.Format(_T("%d"),m_nCount);
			m_ctrlTime.SetWindowText(msg);
			CRect   rc;
			m_ctrlTime.GetWindowRect(&rc);    
			ScreenToClient(&rc);      
			InvalidateRect(rc); 
		}
		else if (m_nCount==1)
		{
			//this->ShowWindow(SW_HIDE);
			OnOK();
		}
	}
	CDialog::OnTimer(nIDEvent);
}
