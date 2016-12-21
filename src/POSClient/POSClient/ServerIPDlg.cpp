// ServerIPDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "POSClient.h"
#include "ServerIPDlg.h"


// CServerIPDlg 对话框

IMPLEMENT_DYNAMIC(CServerIPDlg, CDialog)

CServerIPDlg::CServerIPDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CServerIPDlg::IDD, pParent)
{

}

CServerIPDlg::~CServerIPDlg()
{
}

void CServerIPDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_IPADDRESS1, m_IPCtrl);
}


BEGIN_MESSAGE_MAP(CServerIPDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CServerIPDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CServerIPDlg 消息处理程序

void CServerIPDlg::OnBnClickedOk()
{

	CString ip;
	TCHAR server[256];
	m_IPCtrl.GetWindowText(ip);
	wsprintf(server,_T("DSN=agile_pos;SERVER=%s;"),ip);
	if(SQLConfigDataSource(NULL,ODBC_ADD_SYS_DSN,_T("MySQL ODBC 5.1 Driver"),server)==FALSE)
	{
		//SQLInstallerError();
		POSMessageBox(_T("FAIL"));
	}
	OnOK();
}

BOOL CServerIPDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	HKEY hKey;
	CString strServer;
	DWORD len = 256;
	DWORD dwtype = REG_SZ;
	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, _T("SOFTWARE\\ODBC\\ODBC.INI\\agile_pos"), 0, KEY_READ, &hKey) == ERROR_SUCCESS)
	{
		RegQueryValueEx(hKey, _T("SERVER"), 0, &dwtype, (LPBYTE)strServer.GetBuffer(256), &len);
		strServer.ReleaseBuffer();
		m_IPCtrl.SetWindowText(strServer);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
