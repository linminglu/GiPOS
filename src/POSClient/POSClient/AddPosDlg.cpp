// AddPosDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "POSClient.h"
#include "AddPosDlg.h"


// CAddPosDlg 对话框

IMPLEMENT_DYNAMIC(CAddPosDlg, CDialog)

CAddPosDlg::CAddPosDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAddPosDlg::IDD, pParent)
{
	m_nOS=0;
	m_nResult=-1;
}

CAddPosDlg::~CAddPosDlg()
{
}

void CAddPosDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDOK, m_btOK);
	DDX_Control(pDX, IDCANCEL, m_btCancel);
}


BEGIN_MESSAGE_MAP(CAddPosDlg, CDialog)
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	ON_BN_CLICKED(IDOK, &CAddPosDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CAddPosDlg 消息处理程序
BOOL CAddPosDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	CString str2;
	m_btOK.SetImage(_T("Picture\\bt_ok.png"));
	m_btCancel.SetImage(_T("Picture\\bt_cancel.png"));
	m_btCancel.SetTextColor(DEFALUT_TXT_COLOR);
	m_btOK.SetTextColor(DEFALUT_TXT_COLOR);	
	if (!theLang.m_bDefaultLang)
	{
		SetFont(&theLang.m_dialogFont);
		CWnd* pCtrl=GetDlgItem(IDOK);
		theLang.TranslateDlgItem(pCtrl,IDS_OK);
		pCtrl=GetDlgItem(IDCANCEL);
		theLang.TranslateDlgItem(pCtrl,IDS_CANCEL);
	}
	OSVERSIONINFO versionInfo;
	versionInfo.dwOSVersionInfoSize = sizeof (OSVERSIONINFO);
	if (::GetVersionEx(&versionInfo))
	{
		m_nOS=versionInfo.dwMajorVersion*10+versionInfo.dwMinorVersion;
	}
	SYSTEM_INFO si;
	GetNativeSystemInfo(&si);
	if (si.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64 || si.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_IA64)
		m_nSys=64;
	else
		m_nSys=32;
	if(theApp.m_strPhone!=_T("123456"))
	{
		GetDlgItem(IDC_EDIT1)->SetWindowText(theApp.m_strPhone);
	}
	return TRUE;
}
void CAddPosDlg::OnBnClickedOk()
{
	JSONVALUE root;
	CString str;
	root[_T("guid")]=theApp.m_strResId;
	GetDlgItemText(IDC_EDIT1,str);
	root[_T("phone")]=str;
	GetDlgItemText(IDC_EDIT2,str);
	root[_T("password")]=str;
	root[_T("machine")]=theApp.m_strDiskId;
	GetDlgItemText(IDC_EDIT3,str);
	root[_T("pos_name")]=str;
	root[_T("pos_type")]=0;
	root[_T("os")]=m_nOS;
	root[_T("arch")]=m_nSys;

	JSONVALUE response;
	BOOL bOK=HttpPost(theApp.m_strCloudURL,80,_T("/register/api/add_pos/"),root,response);
	if(bOK)
	{
		m_nResult=response[_T("result")].asInt();
		if(m_nResult==0)
			OnOK();
		else //if(m_nResult>3)
		{
			POSMessageBox(response[_T("message")].asCString());
			return;
		}
// 		else
// 		{
// 			OnCancel();
// 		}
	}
}
HBRUSH CAddPosDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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
void CAddPosDlg::OnPaint()
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