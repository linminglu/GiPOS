// DisplaySettingDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "POSClient.h"
#include "DisplaySettingDlg.h"


// DisplaySettingDlg 对话框

IMPLEMENT_DYNAMIC(DisplaySettingDlg, CDialog)

DisplaySettingDlg::DisplaySettingDlg(CWnd* pParent /*=NULL*/)
	: CDialog(DisplaySettingDlg::IDD, pParent)
{

}

DisplaySettingDlg::~DisplaySettingDlg()
{
}

void DisplaySettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK1, mCheck1);
	DDX_Control(pDX, IDC_CHECK2, mCheck2);
	DDX_Control(pDX, IDC_CHECK3, mCheck3);
	DDX_Control(pDX, IDOK, m_btOK);
	DDX_Control(pDX, IDCANCEL, m_btCancel);
	DDX_Control(pDX, IDC_SPIN1, mSpin1);
	DDX_Control(pDX, IDC_SPIN2, mSpin2);
	DDX_Control(pDX, IDC_SPIN3, mSpin3);
}


BEGIN_MESSAGE_MAP(DisplaySettingDlg, CDialog)
	//ON_WM_CTLCOLOR()
	//ON_WM_PAINT()
	ON_BN_CLICKED(IDC_CHECK3, &DisplaySettingDlg::OnBnClickedCheck3)
	ON_BN_CLICKED(IDC_BUTTON1, &DisplaySettingDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDOK,&DisplaySettingDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// DisplaySettingDlg 消息处理程序
BOOL DisplaySettingDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	CString str2;
	m_btOK.SetImage(_T("Picture\\bt_ok.png"));
	m_btCancel.SetImage(_T("Picture\\bt_cancel.png"));
	m_btCancel.SetTextColor(DEFALUT_TXT_COLOR);
	m_btOK.SetTextColor(DEFALUT_TXT_COLOR);	if (!theLang.m_bDefaultLang)
	{
		SetFont(&theLang.m_dialogFont);
		CWnd* pCtrl=GetDlgItem(IDOK);
		theLang.TranslateDlgItem(pCtrl,IDS_OK);
		pCtrl=GetDlgItem(IDCANCEL);
		theLang.TranslateDlgItem(pCtrl,IDS_CANCEL);
	}
	int FULLSCREEN=GetPrivateProfileInt(_T("POS"),  _T("FULLSCREEN"), 0,_T(".\\config.ini"));
	if(FULLSCREEN==1)
		mCheck1.SetCheck(TRUE);
	int CUSTOMER_FLOOR=GetPrivateProfileInt(_T("POS"),  _T("CUSTOMER_FLOOR"), 0,_T(".\\config.ini"));
	if(CUSTOMER_FLOOR==1)
		mCheck2.SetCheck(TRUE);
	int ITEM_LINESIZE=::GetPrivateProfileInt(_T("POS"),_T("ITEM_LINESIZE"),4,_T(".\\config.ini"));
	mSpin1.SetBuddy(GetDlgItem(IDC_EDIT1));
	mSpin1.SetRange(1,20);
	mSpin1.SetPos(ITEM_LINESIZE);
	int ITEM_COLUMNSIZE=::GetPrivateProfileInt(_T("POS"),_T("ITEM_COLUMNSIZE"),4,_T(".\\config.ini"));
	mSpin2.SetBuddy(GetDlgItem(IDC_EDIT2));
	mSpin2.SetRange(1,20);
	mSpin2.SetPos(ITEM_COLUMNSIZE);
	int PIC_TIMER = GetPrivateProfileInt(_T("SECOND_SCREEN"),  _T("PIC_TIMER"), 0,_T(".\\config.ini"));
	mSpin3.SetBuddy(GetDlgItem(IDC_EDIT4));
	mSpin3.SetRange(1,200);
	mSpin3.SetPos(PIC_TIMER);
	CString strPath;
	::GetPrivateProfileString(_T("SECOND_SCREEN"),_T("SCAN_FILE"),_T(""),strPath.GetBuffer(200),200,_T(".\\config.ini"));
	strPath.ReleaseBuffer();
	if(!strPath.IsEmpty())
	{
		mCheck3.SetCheck(TRUE);
		GetDlgItem(IDC_EDIT3)->SetWindowText(strPath);
	}
	else
	{
		mCheck3.SetCheck(FALSE);
		GetDlgItem(IDC_EDIT3)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT4)->EnableWindow(FALSE);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
void DisplaySettingDlg::OnBnClickedOk()
{
	if(mCheck1.GetCheck())
		WritePrivateProfileString(_T("POS"),  _T("FULLSCREEN"),_T("1"),_T(".\\config.ini"));
	else
		WritePrivateProfileString(_T("POS"),  _T("FULLSCREEN"),_T("0"),_T(".\\config.ini"));
	if(mCheck2.GetCheck())
		WritePrivateProfileString(_T("POS"),  _T("CUSTOMER_FLOOR"),_T("1"),_T(".\\config.ini"));
	else
		WritePrivateProfileString(_T("POS"),  _T("CUSTOMER_FLOOR"),_T("0"),_T(".\\config.ini"));
	CString text;
	GetDlgItem(IDC_EDIT1)->GetWindowText(text);
	WritePrivateProfileString(_T("POS"),  _T("ITEM_LINESIZE"),text,_T(".\\config.ini"));
	GetDlgItem(IDC_EDIT2)->GetWindowText(text);
	WritePrivateProfileString(_T("POS"),  _T("ITEM_COLUMNSIZE"),text,_T(".\\config.ini"));
	if(mCheck3.GetCheck())
	{
		GetDlgItem(IDC_EDIT3)->GetWindowText(text);
	}
	else
	{
		text=_T("");
	}
	WritePrivateProfileString(_T("SECOND_SCREEN"),_T("SCAN_FILE"),text,_T(".\\config.ini"));
	GetDlgItem(IDC_EDIT4)->GetWindowText(text);
	WritePrivateProfileString(_T("SECOND_SCREEN"),_T("PIC_TIMER"),text,_T(".\\config.ini"));

	OnOK();
	POSMessageBox(_T("重启程序生效"));
	
}
HBRUSH DisplaySettingDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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
void DisplaySettingDlg::OnPaint()
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
void DisplaySettingDlg::OnBnClickedCheck3()
{
	if(mCheck3.GetCheck())
	{
		GetDlgItem(IDC_EDIT3)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT4)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON1)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_EDIT3)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT4)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON1)->EnableWindow(FALSE);
	}
}

void DisplaySettingDlg::OnBnClickedButton1()
{
	TCHAR szPath[MAX_PATH];     //存放选择的目录路径 
	CString str;
	ZeroMemory(szPath, sizeof(szPath));   
	BROWSEINFO bi;   
	bi.hwndOwner = m_hWnd;   
	bi.pidlRoot = NULL;   
	bi.pszDisplayName = szPath;   
	bi.lpszTitle = NULL;   
	bi.ulFlags = 0;   
	bi.lpfn = NULL;   
	bi.lParam = 0;   
	bi.iImage = 0;   
	//弹出选择目录对话框
	LPITEMIDLIST lp = SHBrowseForFolder(&bi);   
	if(lp && SHGetPathFromIDList(lp, szPath))   
	{
		GetDlgItem(IDC_EDIT3)->SetWindowText(szPath);
	}
}
