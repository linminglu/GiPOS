// ServerIpSettingDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ServerIpSetting.h"
#include "ServerIpSettingDlg.h"
#include <odbcinst.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#pragma comment(lib,"odbccp32.lib")

// CServerIpSettingDlg 对话框




CServerIpSettingDlg::CServerIpSettingDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CServerIpSettingDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CServerIpSettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_IPADDRESS1, m_IPCtrl);
	DDX_Control(pDX, IDC_RADIO1, m_radio1);
	DDX_Control(pDX, IDC_RADIO2, m_radio2);
}

BEGIN_MESSAGE_MAP(CServerIpSettingDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CServerIpSettingDlg::OnBnClickedOk)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, &CServerIpSettingDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_RADIO1, &CServerIpSettingDlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CServerIpSettingDlg::OnBnClickedRadio2)
END_MESSAGE_MAP()


// CServerIpSettingDlg 消息处理程序

BOOL CServerIpSettingDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	HKEY hKey;
	DWORD len = 256;
	DWORD dwtype = REG_SZ;
	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, _T("SOFTWARE\\ODBC\\ODBC.INI\\agile_pos"), 0, KEY_READ, &hKey) == ERROR_SUCCESS)
	{
		RegQueryValueEx(hKey, _T("SERVER"), 0, &dwtype, (LPBYTE)m_strServer.GetBuffer(256), &len);
		m_strServer.ReleaseBuffer();
		m_IPCtrl.SetWindowText(m_strServer);
		if(m_strServer==_T("127.0.0.1"))
		{
			m_radio1.SetCheck(TRUE);
			m_IPCtrl.ShowWindow(SW_HIDE);
		}
		else
		{
			m_radio2.SetCheck(TRUE);
			m_IPCtrl.ShowWindow(SW_SHOW);
		}
	}
	if (!theLang.m_bDefaultLang)
	{
		SetFont(&theLang.m_dialogFont);
		CWnd* pCtrl=GetDlgItem(IDC_STATIC1);
		theLang.TranslateDlgItem(pCtrl,IDS_INPUTIP);
		pCtrl=GetDlgItem(IDC_BUTTON1);
		theLang.TranslateDlgItem(pCtrl,IDS_CONNECT);
		pCtrl=GetDlgItem(IDOK);
		theLang.TranslateDlgItem(pCtrl,IDS_OK);
		pCtrl=GetDlgItem(IDCANCEL);
		theLang.TranslateDlgItem(pCtrl,IDS_CANCEL);
		pCtrl=GetDlgItem(IDC_RADIO1);
		theLang.TranslateDlgItem(pCtrl,IDS_LOCAL);
		pCtrl=GetDlgItem(IDC_RADIO2);
		theLang.TranslateDlgItem(pCtrl,IDS_REMOTE);
	}
	m_IPCtrl.SetFocus();
	return FALSE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CServerIpSettingDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
//
HCURSOR CServerIpSettingDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CServerIpSettingDlg::OnBnClickedOk()
{
	CString ip;
	TCHAR server[1024]={0};
	m_IPCtrl.GetWindowText(ip);
	if(m_radio1.GetCheck())
		ip=_T("127.0.0.1");
	wsprintf(server,_T("DSN=agile_pos;DATABASE=coolroid;PORT=3308;USER=root;PASSWORD=agile;SERVER=%s;"),ip);
	if(SQLConfigDataSource(NULL,ODBC_ADD_SYS_DSN,_T("MySQL ODBC 5.1 Driver"),server)==FALSE)
	{
		RETCODE rc;
		WORD iError, cbErrorMsg;
		DWORD fErrorCode;
		TCHAR szErrorMsg[512];
		CString errorMsg;
		for (iError = 1; iError <= 8; iError++) {
			rc = SQLInstallerError(iError,
				&fErrorCode,
				szErrorMsg,
				sizeof(szErrorMsg),
				&cbErrorMsg);
			if (rc == SQL_NO_DATA ||
				rc == SQL_ERROR) {
					break;
			}
			errorMsg.AppendFormat(_T("[%d]%s\n"),fErrorCode,szErrorMsg);
		}
		AfxMessageBox(errorMsg,MB_ICONERROR);
	}
	else
	{
		wsprintf(server,_T("DSN=agile_pos_training;DATABASE=coolroid_train;PORT=3308;USER=root;PASSWORD=agile;SERVER=%s;"),ip);
		SQLConfigDataSource(NULL,ODBC_ADD_SYS_DSN,_T("MySQL ODBC 5.1 Driver"),server);
	}
	OnOK();
}
void CServerIpSettingDlg::OnBnClickedButton1()
{
	if (!AfxSocketInit())
	{
		AfxMessageBox(_T("Windows Socket init fail!"));
		return ;
	}
	CString ip;
	CSocket m_socket;
	m_IPCtrl.GetWindowText(ip);
	if(m_radio1.GetCheck())
		ip=_T("127.0.0.1");
	m_socket.m_hSocket=INVALID_SOCKET;
	//创建套接字
	BOOL flag=m_socket.Create();
	if(!flag)
	{
		theLang.LoadString(IDS_CONNECTFAIL,ip);
		AfxMessageBox(ip);
		return;
	}
	if(!m_socket.Connect(ip,3308))
	{
		theLang.LoadString(IDS_CONNECTFAIL,ip);
		AfxMessageBox(ip);
		return;
	}
	m_socket.Close();
	theLang.LoadString(IDS_CONNECTOK,ip);
	AfxMessageBox(ip);
}

void CServerIpSettingDlg::OnBnClickedRadio1()
{
	m_IPCtrl.ShowWindow(SW_HIDE);
}

void CServerIpSettingDlg::OnBnClickedRadio2()
{
	m_IPCtrl.ShowWindow(SW_SHOW);
}
