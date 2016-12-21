// InformationDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "POSClient.h"
#include "InformationDlg.h"


// InformationDlg 对话框

IMPLEMENT_DYNAMIC(InformationDlg, CDialog)

InformationDlg::InformationDlg(CWnd* pParent /*=NULL*/)
	: CDialog(InformationDlg::IDD, pParent)
{

}

InformationDlg::~InformationDlg()
{
	::DeleteObject(m_bpBackgrd);
}

void InformationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_LEFT, m_btLeft);
	DDX_Control(pDX, IDC_BUTTON_RIGHT, m_btRight);
	DDX_Control(pDX, IDCANCEL, m_btCancel);
	DDX_Control(pDX, IDC_LIST1, m_list);
}


BEGIN_MESSAGE_MAP(InformationDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_LEFT, &InformationDlg::OnBnClickedButtonLeft)
	ON_BN_CLICKED(IDC_BUTTON_RIGHT, &InformationDlg::OnBnClickedButtonRight)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// InformationDlg 消息处理程序
BOOL InformationDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
// 	HICON picon;
// 	picon = (HICON)::LoadImage(NULL,_T("Icon\\left.ico"), IMAGE_ICON,48,48,LR_LOADFROMFILE);
// 	m_btLeft.SetIcon(picon,CRoundButton2::CENTER);
// 	picon = (HICON)::LoadImage(NULL,_T("Icon\\right.ico"), IMAGE_ICON,48,48,LR_LOADFROMFILE);
// 	m_btRight.SetIcon(picon,CRoundButton2::CENTER);
	CImage img,img1;
	if(img.Load(_T("Picture\\help.png"))==S_OK)
	{
		m_x=img.GetWidth();
		m_y=img.GetHeight();
		m_bpBackgrd=img.Detach();
	}
	CString str2;
	theLang.LoadString(str2,IDS_CANCEL);
	m_btCancel.SetWindowText(str2);
	m_btCancel.SetImage(_T("Picture\\bt_cancel.png"));
	m_btLeft.SetImage(_T("Picture\\bt_page.png"));
	m_btRight.SetImage(_T("Picture\\bt_page.png"));
	
	theLang.LoadString(str2,IDS_PREPAGE);
	m_btLeft.SetWindowText(str2);
	theLang.LoadString(str2,IDS_NEXTPAGE);
	m_btRight.SetWindowText(str2);
	m_btCancel.SetTextColor(DEFALUT_TXT_COLOR);
	m_btLeft.SetTextColor(DEFALUT_TXT_COLOR);
	m_btRight.SetTextColor(DEFALUT_TXT_COLOR);
	m_infoSet.Open(CRecordset::snapshot, NULL, CRecordset::readOnly);
	m_list.ResetContent();
	if (!m_infoSet.IsEOF())
	{
		m_list.AddString(m_infoSet.m_info_name);
		m_list.AddString(m_infoSet.m_line1);
		m_list.AddString(m_infoSet.m_line2);
		m_list.AddString(m_infoSet.m_line3);
		m_list.AddString(m_infoSet.m_line4);
		m_list.AddString(m_infoSet.m_line5);
		m_list.AddString(m_infoSet.m_line6);
		m_list.AddString(m_infoSet.m_line7);
		m_list.AddString(m_infoSet.m_line8);
		m_list.AddString(m_infoSet.m_line9);
		m_list.AddString(m_infoSet.m_line10);
		//m_infoSet.MoveNext();
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void InformationDlg::OnBnClickedButtonLeft()
{
	if (!m_infoSet.IsBOF())
	{
		m_infoSet.MovePrev();
		if (m_infoSet.IsBOF())
		{
			m_infoSet.MoveNext();
			return;
		}
		m_list.ResetContent();
		m_list.AddString(m_infoSet.m_info_name);
		m_list.AddString(m_infoSet.m_line1);
		m_list.AddString(m_infoSet.m_line2);
		m_list.AddString(m_infoSet.m_line3);
		m_list.AddString(m_infoSet.m_line4);
		m_list.AddString(m_infoSet.m_line5);
		m_list.AddString(m_infoSet.m_line6);
		m_list.AddString(m_infoSet.m_line7);
		m_list.AddString(m_infoSet.m_line8);
		m_list.AddString(m_infoSet.m_line9);
		m_list.AddString(m_infoSet.m_line10);
	}
}

void InformationDlg::OnBnClickedButtonRight()
{
	
	if (!m_infoSet.IsEOF())
	{
		m_infoSet.MoveNext();
		if (m_infoSet.IsEOF())
		{
			m_infoSet.MovePrev();
			return;
		}
		m_list.ResetContent();
		m_list.AddString(m_infoSet.m_info_name);
		m_list.AddString(m_infoSet.m_line1);
		m_list.AddString(m_infoSet.m_line2);
		m_list.AddString(m_infoSet.m_line3);
		m_list.AddString(m_infoSet.m_line4);
		m_list.AddString(m_infoSet.m_line5);
		m_list.AddString(m_infoSet.m_line6);
		m_list.AddString(m_infoSet.m_line7);
		m_list.AddString(m_infoSet.m_line8);
		m_list.AddString(m_infoSet.m_line9);
		m_list.AddString(m_infoSet.m_line10);
		
	}
}



BOOL InformationDlg::OnEraseBkgnd(CDC* pDC)
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
	pDC->StretchBlt(0,0,rect.Width(),rect.Height(),&MemDc,0,0,m_x,m_y,SRCCOPY);
	//pDC->BitBlt(0,0,rect.Width(),rect.Height(),&MemDc,0,0,SRCCOPY);
	MemDc.SelectObject(hOldBmp);
	return TRUE;
}
