// LoginDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "POSClient.h"
#include "LoginDlg.h"
#include "InformationDlg.h"
#include "AboutDlg.h"
#include "SoftwareKey2.h"
#include "MSGBoxDlg.h"
#include "LanguageDlg.h"
#include "ClockDlg.h"
#include "OrderPage.h"
#include "ZipArchive.h"
#include "SecondScreen.h"

//#include "deelx.h"
#include <windows.h>
#include <openssl/aes.h>
// CLoginDlg 对话框

CString m_strCloudURL=_T("www.gicater.me");

IMPLEMENT_DYNAMIC(CLoginDlg, CPosPage)

CLoginDlg::CLoginDlg(CWnd* pParent /*=NULL*/)
: CPosPage(CLoginDlg::IDD)
, m_strHint(_T(""))
{
	m_bClock=FALSE;
	m_bSwipe=FALSE;
}

CLoginDlg::~CLoginDlg()
{
}

void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CPosPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_HINT, m_hintCtrl);
	DDX_Control(pDX, IDC_STATIC_TIME, m_timeCtrl);
}
void CLoginDlg::OnSetActive()
{
	try{
		//清除原有信息
		theLang.UpdatePage(this,_T("IDD_1_LOGIN"));
		OnBnClickedButtonClear();
		if(m_pSecond)
		{
			m_pSecond->HideDetail();
		}
		//重启客显
		theApp.m_cusDisplay.Close();
		theApp.m_cusDisplay.Open();
		CString text;
		text.Format(_T("Welcome to %s"),theApp.m_strResName);
		theApp.m_cusDisplay.ShowRollingText(text);
		text.AppendChar('\n');
		theApp.m_VCR.Print(text);
		CPosPage::OnSetActive();

	}
	catch(...)
	{
		LOG4CPLUS_ERROR(log_pos,"Catch Exception GetLastError="<<GetLastError());
	}
}

BEGIN_MESSAGE_MAP(CLoginDlg, CDialog)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BUTTON_OK, &CLoginDlg::OnBnClickedOK)
	ON_COMMAND_RANGE(IDC_BUTTON0,IDC_BUTTON9,OnNumBnClicked)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, &CLoginDlg::OnBnClickedButtonClear)
	ON_BN_CLICKED(IDC_BUTTON00, &CLoginDlg::OnBnClickedButton00)
	ON_BN_CLICKED(IDC_BUTTON_CLOCK, &CLoginDlg::OnBnClickedButtonClock)
	ON_BN_CLICKED(IDC_BUTTON_SIGN, &CLoginDlg::OnBnClickedButtonSign)
	ON_BN_CLICKED(IDC_BUTTON_CHANGE, &CLoginDlg::OnBnClickedButtonChange)
	ON_BN_CLICKED(IDC_BUTTON_HELP, &CLoginDlg::OnBnClickedButtonHelp)
	ON_BN_CLICKED(IDC_BUTTON_DOT, &CLoginDlg::OnBnClickedButtonDot)
	ON_BN_CLICKED(IDC_BUTTON_SHUTDOWN,&CLoginDlg::OnBnClickedButtonShutDown)
	ON_BN_CLICKED(IDC_BUTTON_ABOUT, &CLoginDlg::OnBnClickedButtonAbout)
	ON_BN_CLICKED(IDC_BUTTON_CONFIG, &CLoginDlg::OnBnClickedButtonConfig)
	ON_BN_CLICKED(IDC_BUTTON_REPORT, &CLoginDlg::OnBnClickedButtonReport)
	ON_BN_CLICKED(IDC_BUTTON_TOOLS, &CLoginDlg::OnBnClickedButtonTools)
	ON_BN_CLICKED(IDC_BUTTON_TRAINMODE, &CLoginDlg::OnBnClickedButtonTrainMode)
	ON_BN_CLICKED(IDC_BUTTON_BACKUP, &CLoginDlg::OnBnClickedBackup)
	ON_BN_CLICKED(IDC_BUTTON_INVENTORY, &CLoginDlg::OnBnClickedButtonInventory)
	ON_BN_CLICKED(IDC_BUTTON_WEBSITE, &CLoginDlg::OnBnClickedButtonWebsite)
	ON_BN_CLICKED(IDC_BUTTON_WEBVIPNEW, &CLoginDlg::OnBnClickedButtonWebVip)
	ON_BN_CLICKED(IDC_BUTTON_REGISTER, &CLoginDlg::OnBnClickedButtonRegister)
	ON_BN_CLICKED(IDC_BUTTON_SERVERIP, &CLoginDlg::OnBnClickedServerIpSetting)
	ON_BN_CLICKED(IDC_BUTTON_PARTY, &CLoginDlg::OnBnClickedParty)
	ON_BN_CLICKED(IDC_BUTTON_TEMPLATE, &CLoginDlg::OnBnClickedTemplate)
	ON_BN_CLICKED(IDC_BUTTON_LANGUAGE, &CLoginDlg::OnBnClickedLanguage)
	ON_BN_CLICKED(IDCANCEL, &CLoginDlg::OnBnClickedeExit)
	ON_BN_CLICKED(IDC_BUTTON_MINIMIZE, &CLoginDlg::OnBnClickedMinimize)
	ON_BN_CLICKED(IDC_BUTTON_SYNC,&CLoginDlg::OnBnClickedSync)
	ON_COMMAND_RANGE(IDC_BUTTON_NEXTPAGE,IDC_BUTTON_NEXTPAGE+50,&CPosPage::OnNextPage)
	ON_WM_TIMER()
	ON_WM_CTLCOLOR()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

// CLoginDlg 消息处理程序

/************************************************************************
* 函数介绍：登录
* 输入参数：type:  0-输入ID登录  1-刷卡登录
* 输出参数：
* 返回值  ：
************************************************************************/
void CLoginDlg::Signin(int type)
{
	try{
		m_bSwipe=FALSE;
		m_bTrainingMode=FALSE;
		OpenDatabase(TRUE);
		CRecordset rs(&theDB);
		CString strSQL,strID;
		CString strPSW;
		if(type==0)
		{
			strID=m_strLoginID.Left(3);//前3位为ID
			strPSW=m_strLoginID.Mid(3);
			strSQL.Format(_T("SELECT * FROM employee WHERE employee_id=\'%s\';"),strID);
		}
		else
		{
			strSQL.Format(_T("SELECT * FROM employee WHERE pc_aps_id=\'%s\';"),m_strLoginID);
		}
		if(!rs.Open(CRecordset::forwardOnly,strSQL))
			return;
		if (rs.GetRecordCount()==0)
		{
			theLang.LoadString(IDS_NOUSER,m_strHint);
			MessageBeep(MB_ICONERROR);
			m_strLoginID.Empty();
			UpdateHintData();
			rs.Close();
		}
		else
		{
			if(type==0)
			{
				CString psw;
				rs.GetFieldValue(_T("password_id"),psw);
				if(psw!=strPSW)
				{
					theLang.LoadString(IDS_WRONGPSW,m_strHint);
					MessageBeep(MB_ICONERROR);
					m_strLoginID.Empty();
					UpdateHintData();
					return;
				}
			}
			else if (type==1)
			{
				rs.GetFieldValue(_T("employee_id"),strID);
			}
			{
				if (m_bClock)
				{//打卡
					ClockDlg dlg;
					dlg.m_strUserID=strID;
					rs.GetFieldValue(_T("employee_last_name"),strPSW);
					strPSW.Replace('\'',' ');
					dlg.m_strUserName.Format(_T("%s"),strPSW);
					dlg.DoModal();
// 					if(UpdateClock(strID)==1)
// 					{
// 						POSMessageBox(IDS_CLOCKIN);
// 					}
// 					else
// 					{
// 						POSMessageBox(IDS_CLOCKOUT);
// 					}
					m_bClock=FALSE;
					theLang.LoadString(IDS_INPUTLOGIN,m_strHint);
				}
				else
				{//登陆成功
					CPOSClientApp* pApp=((CPOSClientApp*)AfxGetApp());
					CDBVariant variant;
					rs.GetFieldValue(_T("is_in_traning"),variant);
					m_bTrainingMode=variant.m_boolVal;
					rs.GetFieldValue(_T("employee_last_name"),strPSW);
					strPSW.Replace('\'',' ');
					pApp->m_strUserName.Format(_T("%s"),strPSW);
					pApp->m_strUserID=strID;
					//获取该用户的权限列表
					pApp->m_privilegeMap.RemoveAll();
					rs.GetFieldValue(_T("employee_class"),variant);
					strSQL.Format(_T("SELECT * FROM employee_class WHERE employee_class_id=\'%d\';"),variant.m_lVal);
					rs.Close();
					if(!rs.Open(CRecordset::forwardOnly,strSQL))
						return;
					if(!rs.IsEOF())
					{
						//rs.GetFieldValue(_T("employee_class_name"),pApp->m_strUserClass);
						for(int i=3;i<rs.GetODBCFieldCount();i++)
						{
							CODBCFieldInfo   fieldinfo;
							variant.m_lVal=0;
							rs.GetODBCFieldInfo(i,fieldinfo);
							rs.GetFieldValue(fieldinfo.m_strName,variant);
							pApp->m_privilegeMap.SetAt(fieldinfo.m_strName,variant.m_lVal);
						}
					}
					rs.Close();
					//查询当前的班次用于显示
					strSQL.Format(_T("SELECT period_name FROM periods WHERE CURTIME() BETWEEN start_time AND end_time"));
					if(!rs.Open(CRecordset::forwardOnly,strSQL))
						return;
					if(rs.IsEOF())
					{//跨天导致查询不到
						rs.Close();
						strSQL.Format(_T("SELECT period_name FROM periods WHERE end_time<start_time AND (CURTIME()>start_time OR CURTIME()<end_time)"));
						rs.Open(CRecordset::forwardOnly,strSQL);
					}
					if(!rs.IsEOF())
						rs.GetFieldValue(_T("period_name"),pApp->m_strPeriod);
					rs.Close();
					//切换到楼层界面
					LOG4CPLUS_INFO(log_pos,"User Loged in : "<<(LPCTSTR)strID);
					if (m_bTrainingMode)
					{//培训模式，关闭数据库以连接到培训数据库
						theDB.Close();
						if(POSMessageBox(IDS_TRAINMODE,MB_YESNO)==IDCANCEL)
						{
							m_bTrainingMode=FALSE;
							OnBnClickedButtonClear();
							return;
						}
					}
					//关闭提示对话框
					::SendMessage(m_hTip,WM_COMMAND,IDCLOSE,0);
					pApp->m_bDirty=TRUE;

					if (pApp->m_bQuickService)
					{
						//清空数据
						theApp.m_bDirty=1;
						theApp.m_nOrderHeadid=0;
						theApp.m_nTableId=-1;
						theApp.m_pMain->SetActivePage(DLG_ORDER);
					}
					else
					{
						if(COrderPage::bNewTainfo)
						{//有外卖电话,直接开外卖桌
							theApp.m_nOrderHeadid=0;
							theApp.m_bQuickService=TRUE;
							theApp.m_bQuickOnce=TRUE;
							theApp.m_pMain->SetActivePage(DLG_QUICK_ORDER);
							theApp.m_nEatType=TYPE_TAKEOUT;
						}
						else
						{
							theApp.m_pMain->SetActivePage(DLG_FLOOR);
						}
						
					}
				}
			}
			
		}
		m_strLoginID.Empty();
		UpdateHintData();
	}
	catch(CDBException* e)
	{
		LOG4CPLUS_ERROR(log_pos,e->m_nRetCode<<(LPCTSTR)e->m_strError);
		AfxMessageBox(e->m_strError);
		e->Delete();
		return;
	}
	catch(...)
	{
		LOG4CPLUS_ERROR(log_pos,"Catch Exception GetLastError="<<GetLastError());
	}
}
int CLoginDlg::UpdateClock(CString strID)
{
	CString strSQL;
	CRecordset rs(&theDB);
	//查询当天的
	strSQL.Format(_T("SELECT * FROM history_time_clock WHERE employee_id=%s AND ISNULL(clock_out_time) AND HOUR(TIMEDIFF(now(),clock_in_time))<12")
	,strID);
	rs.Open( CRecordset::forwardOnly,strSQL);
	if (!rs.IsEOF())
	{//clock out
		CDBVariant variant;
		rs.GetFieldValue(_T("time_clock_id"),variant);
		strSQL.Format(_T("UPDATE history_time_clock SET clock_out_time=now(),duration=TIMEDIFF(clock_out_time,clock_in_time) WHERE time_clock_id=%d"),variant.m_lVal);
		theDB.ExecuteSQL(strSQL);
		return 0;
	}else
	{//clock in
		strSQL.Format(_T("INSERT INTO history_time_clock(employee_id,clock_in_time) VALUES(\'%s\',now());")
		,strID);
		theDB.ExecuteSQL(strSQL);
		return 1;
	}
}
void CLoginDlg::OnBnClickedOK()
{
	Signin(0);
}
void  CLoginDlg::OnNumBnClicked(UINT uID)
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
	m_strLoginID+=num;
	if (m_strLoginID.GetLength()==1)
	{
		m_strHint=_T("*");
	}
	else
		m_strHint.AppendChar('*');
	UpdateHintData();
}
void CLoginDlg::OnBnClickedButton00()
{
	m_strLoginID+=_T("00");
}
BOOL CLoginDlg::OnInitDialog()
{
	CPosPage::InitDialog(_T("Picture\\login.png"));

	CString strPath;
	::GetPrivateProfileString(_T("SECOND_SCREEN"),_T("SCAN_FILE"),_T(""),strPath.GetBuffer(200),200,_T(".\\config.ini"));
	strPath.ReleaseBuffer();
	if(!strPath.IsEmpty())
	{
		m_pSecond=new SecondScreenDlg;
		m_pSecond->m_scan_file=strPath;
		m_pSecond->Create(IDD_SNDSCREEN,this);
		//m_pSecond->ShowWindow(SW_SHOW);
	}

	CImage img;
	if (m_strTmplate.GetLength()==0)
	{
		m_strTmplate=_T("Page\\IDD_1_LOGIN.ini");
	}
	m_btnCtrl.GenaratePage2(m_strTmplate,this);
	CStatic* pVer=(CStatic*)GetDlgItem(IDC_STATIC_VER);
	pVer->SetWindowText(theApp.m_strVersion);
	mFont.CreatePointFont(90,_T("Microsoft YaHei"));
	pVer->SetFont(&mFont);
	//TODO  删除
	CStatic* pWnd = (CStatic*)GetDlgItem(IDC_STATIC);
	pWnd->ShowWindow(SW_HIDE);
//窗口模式下隐藏关闭按钮
	if(CMainSheet::m_iFullScreen==0)
	{
		GetDlgItem(IDC_BUTTON_MINIMIZE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDCANCEL)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BUTTON_SHUTDOWN)->ShowWindow(SW_HIDE);
	}
	if(!theApp.IS_SERVER)
	{
		CWnd* pCtrl=GetDlgItem(IDC_BUTTON_SYNC);
		if(pCtrl)
			pCtrl->ShowWindow(SW_HIDE);
	}
	mProgDlg=new ProgressDlg;
	mProgDlg->Create(IDD_PROGRESS,this);

	SetTimer(1000,5000,NULL);//每隔5秒刷新时间显示
//	if(theApp.m_bUSB)
//		SetTimer(1001,3600000,NULL);//每隔1小时签到，检查软件注册
	CTime time=CTime::GetCurrentTime();
	CString strTime=time.Format(_T("%Y-%m-%d %H:%M"));
	m_timeCtrl.SetWindowText(strTime);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CLoginDlg::OnBnClickedButtonClear()
{
	theLang.LoadString(IDS_INPUTLOGIN,m_strHint);
	m_strLoginID.Empty();
	m_bClock=FALSE;
	UpdateHintData();
}

void CLoginDlg::OnSize(UINT nType, int cx, int cy)
{
	CPosPage::OnSize(nType, cx, cy);
	cx=CreatButton::m_nFullWidth;
	cy=CreatButton::m_nFullHeight;

// 	int height=(int)(cx/10);
// 	int start=int(cx*0.2);
// 	if (m_hintCtrl.m_hWnd)
// 	{
// 		m_hintCtrl.MoveWindow(start+15,140,int(cx*0.6)-30,35);
// 	}
// 	if (m_timeCtrl.m_hWnd)
// 	{
// 		m_timeCtrl.MoveWindow(cx-210,30,200,30);
// 		m_timeCtrl.GetWindowRect(&m_timeRect);
// 		ScreenToClient(&m_timeRect); 
// 	}
#ifdef GICATER_VERSION
	if (m_timeCtrl.m_hWnd)
	{
		int width=ScaleX(220);
		m_timeCtrl.MoveWindow(cx-width-10,50,width,30);
		m_timeCtrl.GetWindowRect(&m_timeRect);
		ScreenToClient(&m_timeRect); 
	}
#else
	if (m_timeCtrl.m_hWnd)
	{
		m_timeCtrl.MoveWindow(325*cx/1024,80,374*cx/1024,30);
		m_timeCtrl.GetWindowRect(&m_timeRect);
		ScreenToClient(&m_timeRect); 
	}
#endif
	if (m_hintCtrl.m_hWnd)
	{
		m_hintCtrl.MoveWindow(325*cx/1024,165,374*cx/1024,45);
	}
	

}
void CLoginDlg::OnBnClickedButtonClock()
{
	if(m_strLoginID.IsEmpty())
	{
	m_bClock=TRUE;
	theLang.LoadString(IDS_CLOCKHINT,m_strHint);
	UpdateHintData();
	}
	else
	{
		m_bClock=TRUE;
		Signin(0);
	}
}

void CLoginDlg::OnBnClickedButtonSign()
{
	m_bClock=FALSE;
	Signin(0);
}

void CLoginDlg::OnBnClickedButtonChange()
{

}

void CLoginDlg::OnBnClickedButtonHelp()
{
#ifdef GICATER_VERSION
	ShellExecute(GetSafeHwnd(), _T("OPEN"), _T("http://www.kancloud.cn/gicater/pos_start"), NULL, NULL,SW_NORMAL);
	return;
#endif
#ifdef EN_VERSION
	ShellExecute(GetSafeHwnd(), _T("OPEN"), _T("http://doc.pluscore.net/enpos"), NULL, NULL,SW_NORMAL);
	return;
#else
	ShellExecute(GetSafeHwnd(), _T("OPEN"), _T("http://doc.pluscore.net/cnpos"), NULL, NULL,SW_NORMAL);
#endif
}

void CLoginDlg::OnBnClickedButtonDot()
{
	m_strLoginID+=_T(".");
}
void CLoginDlg::OnBnClickedButtonShutDown()
{
	if(POSMessageBox(IDS_CONFIRMSHUT,MB_YESNO)==IDCANCEL)
		return;
	HANDLE hProcess = NULL;
    HANDLE hToken = NULL;
    LUID uID = {0};
    TOKEN_PRIVILEGES stToken_Privileges = {0};
    hProcess = ::GetCurrentProcess();  //获取当前应用程序进程句柄
    if(!::OpenProcessToken(hProcess,TOKEN_ADJUST_PRIVILEGES,&hToken))  //打开当前进程的访问令牌句柄(OpenProcessToken函数调用失败返回值为零)
        return ;
    if(!::LookupPrivilegeValue(NULL,SE_SHUTDOWN_NAME,&uID))  //获取权限名称为"SeShutdownPrivilege"的LUID(LookupPrivilegeValue函数调用失败返回值为零)
        return ;
    stToken_Privileges.PrivilegeCount = 1;  //欲调整的权限个数
    stToken_Privileges.Privileges[0].Luid = uID;  //权限的LUID
    stToken_Privileges.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;  //权限的属性,SE_PRIVILEGE_ENABLED为使能该权限
    
    if(!::AdjustTokenPrivileges(hToken,FALSE,&stToken_Privileges,sizeof stToken_Privileges,NULL,NULL))  //调整访问令牌里的指定权限(AdjustTokenPrivileges函数调用失败返回值为零)
        return ;
    if(::GetLastError() != ERROR_SUCCESS)  //查看权限是否调整成功
        return ;
    ::CloseHandle(hToken);
	::ExitWindowsEx(EWX_SHUTDOWN,0);
}
void CLoginDlg::OnBnClickedButtonAbout()
{
#ifdef GICATER_VERSION
	ShellExecute(GetSafeHwnd(), _T("OPEN"), _T("http://forum.gicater.com/"), NULL, NULL,SW_NORMAL);
#else
	//CAboutDlg dlg;
	//dlg.DoModal();
#endif
}
void CLoginDlg::OnBnClickedButtonConfig()
{
	ShellExecute(GetSafeHwnd(), NULL, _T("POSManager.exe"), NULL, NULL,SW_NORMAL);
}
void CLoginDlg::OnBnClickedButtonReport()
{
	ShellExecute(GetSafeHwnd(), NULL, _T("ReportManage.exe"), NULL, NULL,SW_NORMAL);
}
void CLoginDlg::OnBnClickedButtonTools()
{
	LPCTSTR lpParameters=NULL;
	if (theLang.m_strLang.Find(_T("English"))>=0)
	{
		lpParameters=_T("lang=1");
	}
	else if (theLang.m_strLang.Find(_T("简体"))>=0)
	{
		lpParameters=_T("lang=0");
	}
	else if (theLang.m_strLang.Find(_T("繁體"))>=0)
	{
		lpParameters=_T("lang=2");
	}
	ShellExecute(GetSafeHwnd(), NULL, _T("CheckTool.exe"), lpParameters, NULL,SW_NORMAL);
}
/************************************************************************
* 函数介绍：进入培训模式，通过模拟点击888登录实现
* 输入参数：
* 输出参数：
* 返回值  ：
************************************************************************/
void CLoginDlg::OnBnClickedButtonTrainMode()
{
	m_strLoginID=_T("888");
	OnBnClickedButtonSign();
}
void CLoginDlg::OnBnClickedButtonInventory()
{
	try{
		OpenDatabase();
		CString strSQL;
		CRecordset rs(&theDB);
		strSQL.Format(_T("select * from inventory_setting"));
		rs.Open( CRecordset::forwardOnly,strSQL);
		if (!rs.IsEOF())
		{
			CString ip_addr;
			rs.GetFieldValue(_T("ip_addr"),ip_addr);
			CString strCurrentUrl;
#ifdef GICATER_VERSION
			ip_addr.Trim();
			if(ip_addr.IsEmpty())
				ip_addr=_T("item.taobao.com/item.htm?id=20652483109");
#endif
			strCurrentUrl.Format(_T("http://%s"),ip_addr);
			ShellExecute(GetSafeHwnd(), _T("OPEN"), strCurrentUrl, NULL, NULL,SW_NORMAL);
		}
		rs.Close();
	}catch(...)
	{
	}
}
void CLoginDlg::OnBnClickedButtonRegister()
{
	LPCTSTR lpParameters=NULL;
	if (theLang.m_strLang.Find(_T("English"))>=0)
	{
		lpParameters=_T("1");
	}
	else if (theLang.m_strLang.Find(_T("简体"))>=0)
	{
		lpParameters=_T("0");
	}
	else if (theLang.m_strLang.Find(_T("繁體"))>=0)
	{
		lpParameters=_T("2");
	}
	ShellExecute(NULL, NULL, _T("LicenseManager.exe"), lpParameters, NULL,SW_NORMAL);
}
void CLoginDlg::OnBnClickedButtonWebsite()
{
#ifdef GICATER_VERSION
	ShellExecute(GetSafeHwnd(), _T("OPEN"), _T("http://www.gicater.com"), NULL, NULL,SW_NORMAL);
#else
	ShellExecute(GetSafeHwnd(), _T("OPEN"), _T("http://www.coolroid.com"), NULL, NULL,SW_NORMAL);
#endif
}
void CLoginDlg::OnBnClickedButtonWebVip()
{
	try{
		OpenDatabase();
		CString strSQL;
		CRecordset rs(&theDB);
		strSQL.Format(_T("select * from vip_setting"));
		rs.Open( CRecordset::forwardOnly,strSQL);
		if (!rs.IsEOF())
		{
			CString ip_addr;
			rs.GetFieldValue(_T("ip_addr"),ip_addr);
			CString strCurrentUrl;
			strCurrentUrl.Format(_T("http://%s"),ip_addr);
			ShellExecute(GetSafeHwnd(), _T("OPEN"), strCurrentUrl, NULL, NULL,SW_NORMAL);
		}
		rs.Close();
	}catch(...)
	{
	}
}
/************************************************************************
* 函数介绍：数据库备份
* 输入参数：
* 输出参数：
* 返回值  ：
************************************************************************/
void CLoginDlg::OnBnClickedBackup()
{
	LPCTSTR lpParameters=NULL;
	if (theLang.m_strLang.Find(_T("English"))>=0)
	{
		lpParameters=_T("backupdb lang=1");
	}
	else if (theLang.m_strLang.Find(_T("简体"))>=0)
	{
		lpParameters=_T("backupdb=1 lang=0");
	}
	else if (theLang.m_strLang.Find(_T("繁體"))>=0)
	{
		lpParameters=_T("backupdb=1 lang=2");
	}
	else
	{
		lpParameters=_T("backupdb");
	}
	ShellExecute(GetSafeHwnd(), NULL, _T("POSManager.exe"), lpParameters, NULL,SW_NORMAL);
}
void CLoginDlg::OnBnClickedServerIpSetting()
{
	ShellExecute(GetSafeHwnd(), NULL, _T("ServerIpSetting.exe"), NULL, NULL,SW_NORMAL);
}
void CLoginDlg::OnBnClickedParty()
{
	ShellExecute(GetSafeHwnd(), NULL, _T("PartyManager.exe"), NULL, NULL,SW_NORMAL);
}
void CLoginDlg::OnBnClickedTemplate()
{
	ShellExecute(GetSafeHwnd(), NULL, _T("PrintTemplateManager.exe"), NULL, NULL,SW_NORMAL);
}
void CLoginDlg::OnBnClickedeExit()
{
	theApp.m_pMain->SendMessage(WM_CLOSE);
}
void CLoginDlg::OnBnClickedMinimize()
{
	theApp.m_pMain->ShowWindow(SW_MINIMIZE);
}
void CLoginDlg::OnBnClickedLanguage()
{
#ifdef EN_VERSION
	CLanguageDlg dlg;
	if(dlg.DoModal()==IDOK)
		OnSetActive();
#endif
}

UINT DownloadThread(LPVOID pParam)
{
	CLoginDlg *pDlg = (CLoginDlg*)pParam;
	pDlg->DoDownload();
	return 0;
}
UINT ChangeToCloudThread(LPVOID pParam)
{
	CLoginDlg *pDlg = (CLoginDlg*)pParam;
	pDlg->ChangeEditMode(1);
	return 0;
}

int CLoginDlg::DoDownload()
{
	try{
		CDatabase db;
		db.OpenEx(_T("DSN=agile_pos"));
		CString strDir=_T("sql_data");
		CreateDirectory(strDir,NULL);
		CRecordset rs(&db);
		CString strSQL;
		CString strVer;
		strSQL.Format(_T("SELECT db_version FROM total_statistics"));
		rs.Open(CRecordset::forwardOnly,strSQL);
		if (!rs.IsEOF())
		{
			rs.GetFieldValue((short)0,strVer);
		}
		rs.Close();
		JSONVALUE root;
		root[_T("db_version")] = strVer;
		root[_T("guid")]=theApp.m_strResId;
		JSONVALUE versions;
		strSQL.Format(_T("SELECT * FROM www_version"));
		rs.Open(CRecordset::forwardOnly,strSQL);
		if(!rs.IsEOF())
		{
			CDBVariant variant;
			for(int i=0;i<rs.GetODBCFieldCount();i++)
			{
				CODBCFieldInfo   fieldinfo;
				variant.m_lVal=0;
				rs.GetODBCFieldInfo(i,fieldinfo);
				rs.GetFieldValue(fieldinfo.m_strName,variant);
				versions[fieldinfo.m_strName]=variant.m_lVal;
			}
		}
		root["versions"] = versions;
		CString strURL,strValue;
		CInternetSession session;
		session.SetOption(INTERNET_OPTION_CONNECT_TIMEOUT, 1000 * 10);
		session.SetOption(INTERNET_OPTION_CONNECT_BACKOFF, 1000);
		session.SetOption(INTERNET_OPTION_CONNECT_RETRIES, 1);
		CHttpConnection* pConnection = session.GetHttpConnection(m_strCloudURL,(INTERNET_PORT)80);
		CString szHeaders   = L"Content-Type: application/x-www-form-urlencoded;";
		std::string str;
		root.ToString(str);
		int wcsLen0 =str.length();
		// aes encrypt
		AES_KEY aes_enc_ctx;
		unsigned char ivec[AES_BLOCK_SIZE]={'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'};
		int len = 0;
		if ((wcsLen0 + 1) % AES_BLOCK_SIZE == 0) {
			len = wcsLen0 + 1;
		} else {
			len = ((wcsLen0 + 1) / AES_BLOCK_SIZE + 1) * AES_BLOCK_SIZE;
		}
		unsigned char *encrypt_text=(unsigned char *) new char[len];
		AES_set_encrypt_key(theApp.enctrypkey, 128, &aes_enc_ctx);
		AES_cbc_encrypt((const unsigned char *)str.c_str(), encrypt_text, len, &aes_enc_ctx, ivec, AES_ENCRYPT); 
		strURL.Format(_T("/client_download/"));
		CHttpFile* pFile = pConnection->OpenRequest(CHttpConnection::HTTP_VERB_POST,strURL);
		pFile->SendRequest(szHeaders,szHeaders.GetLength(),(LPVOID)encrypt_text,len);
		delete encrypt_text;
		DWORD dwStatus;
		pFile->QueryInfoStatusCode(dwStatus);
		if(dwStatus != HTTP_STATUS_OK)
		{
			LOG4CPLUS_ERROR(log_pos,"Connect "<<(LPCTSTR)m_strCloudURL<<":"<<" status code="<<dwStatus);
			session.Close();
			pFile->Close();
			delete pFile;
			mProgDlg->Stop();
			return 0;
		}
		CString strHeader;
		pFile->QueryInfo(HTTP_QUERY_CONTENT_TYPE,strHeader);
		if(strHeader.CompareNoCase(_T("application/json"))==0)
		{
			char buf[1024]={0};
			pFile->ReadString((LPTSTR)buf,sizeof(buf)-1);
			wcsLen0 = ::MultiByteToWideChar(CP_UTF8, NULL, buf, strlen(buf), NULL, 0);
			TCHAR* sz1 = new TCHAR[wcsLen0 + 1];
			::MultiByteToWideChar(CP_UTF8, NULL, buf, -1, sz1, wcsLen0);
			sz1[wcsLen0] = '\0';
			CString jStr;
			JSONVALUE::Unescape(sz1,jStr);
			delete sz1;
			root.Parse((LPCTSTR)jStr,JSON_FLAG_LOOSE);
			CString msg=root[_T("description")].asCString();
			POSMessageBox(msg);
		}
		else
		{
			CFile NetFile;
			if(!NetFile.Open(_T("_tmp_download"), CFile::modeWrite|CFile::modeCreate))
			{
				LOG4CPLUS_ERROR(log_pos,"Create download file ERROR");
				session.Close();
				pFile->Close();
				delete pFile;
				mProgDlg->Stop();
				return 0;
			}
			char buffer[2049]={0};
			int nReadCount = 0;
			while((nReadCount = pFile->Read(buffer, 2048)) > 0)
			{
				NetFile.Write(buffer,nReadCount);
			}
			NetFile.Close();
			CZipArchive zip;
			zip.Open(_T("_tmp_download"));
			int zip_count=zip.GetNoEntries();
			for(int i=0;i<zip_count;i++)
			{
				zip.ExtractFile(i,strDir);
				CZipFileHeader fhInfo;
				zip.GetFileInfo(fhInfo,i);
				CString fileName=fhInfo.GetFileName();
				CString fullPath=strDir+_T("/")+fileName;
				CStdioFile file;
				file.Open(fullPath,CFile::modeRead);
				CString line;
				file.ReadString(line);
				file.Close();
				line.Replace(_T(","),_T("`,`"));
				line.Insert(0,'`');
				line.AppendChar('`');
				strSQL.Format(_T("TRUNCATE TABLE %s"),fileName);
				db.ExecuteSQL(strSQL);
				strSQL.Format(_T("LOAD DATA LOCAL INFILE '%s' REPLACE INTO TABLE %s FIELDS TERMINATED BY ',' OPTIONALLY ENCLOSED BY '\"' LINES TERMINATED BY '\\n' IGNORE 1 LINES (%s)"),fullPath,fileName,line);
				db.ExecuteSQL(strSQL);
			}
			zip.Close();
			POSMessageBox(IDS_SYNCOK);
		}
		pFile->Close();
		db.Close();
		mProgDlg->Stop();
		
	}catch(...)
	{}
	mProgDlg->Stop();
	return 0;
}


void CLoginDlg::ChangeEditMode(int mode)
{
	CString strSQL;
	CString strVal;
	try{
	CRecordset rs(&theDB);
	if(mode==1)
	{//上传数据
		strSQL=_T("SELECT cr_last_time,tender_media+major_group+family_group+rvc_center+periods+menu_item+employee+`tables`+res_info AS col FROM webreport_setting");
		rs.Open(CRecordset::forwardOnly,strSQL);
		CString last_time;
		rs.GetFieldValue((short)0,last_time);
		rs.GetFieldValue((short)1,strVal);
		rs.Close();
		if(strVal!=_T("0"))
		{
			KillProcessByName(_T("WebReport.exe"));
			ShellExecute(NULL, NULL, _T("WebReport.exe"), NULL, NULL,SW_NORMAL);
			//检测是否上传成功
			BOOL bSuccess=FALSE;
			strSQL=_T("SELECT cr_last_time FROM webreport_setting");
			for(int i=0;i<10;i++)
			{
				Sleep(2000);
				rs.Open(CRecordset::forwardOnly,strSQL);
				rs.GetFieldValue((short)0,strVal);
				rs.Close();
				if(last_time.Compare(strVal)!=0)
				{
					bSuccess=TRUE;
					mProgDlg->Step(1,_T("Switching ..."));
					break;
				}
			}
			if(bSuccess==FALSE)
			{
				mProgDlg->Step(1,_T("Upload timeout..."));
			}
			Sleep(15000);
		}
	}
	JSONVALUE root;
	root[_T("guid")]=theApp.m_strResId;
	if(mode==0)
		root[_T("set_mode")]=_T("local");
	else
		root[_T("set_mode")]=_T("web");
	strSQL=_T("SELECT major_version FROM www_version");
	rs.Open(CRecordset::forwardOnly,strSQL);
	if (!rs.IsEOF())
	{
		rs.GetFieldValue((short)0,strVal);
	}
	rs.Close();
	root[_T("major_version")]=_wtoi(strVal);
	if(theLang.m_strLang==_T("Default")||theLang.m_strLang==_T("简体中文"))
		root[_T("lang")]=_T("zh-CN");
	else if(theLang.m_strLang==_T("繁體中文"))
		root[_T("lang")]=_T("zh-TW");
	else
		root[_T("lang")]=_T("en");
	JSONVALUE response;
	if(HttpPost(m_strCloudURL,80,_T("/client_switch/"),root,response))
	{
		mProgDlg->Stop();
		int result=response[_T("result")].asInt();
		if(result==0||result==2)
		{
			strSQL.Format(_T("UPDATE webreport_setting SET edit_mode=1"));
			theDB.ExecuteSQL(strSQL);
			POSMessageBox(IDS_SWITCHOK);
			CString strCurrentUrl;
			strCurrentUrl.Format(_T("http://%s/center/center_register/?guid=%s"),m_strCloudURL,theApp.m_strResId);
			ShellExecute(GetSafeHwnd(), _T("OPEN"), strCurrentUrl, NULL, NULL,SW_NORMAL);
		}
		else
		{
			
			CString str,str2;
			theLang.LoadString(str2,IDS_SWITCHFAIL);
			str2.Append(_T("\n[%s]"));
			str.Format(str2,response[_T("error")].asCString());
			POSMessageBox(str);
		}
	}
	else
	{
		mProgDlg->Stop();
		POSMessageBox(IDS_NETWARNING);
	}
	}catch(...)
	{

	}
	mProgDlg->Stop();
}


void CLoginDlg::OnBnClickedSync()
{
	return;
	//暂不开放
	if(!theApp.IS_SERVER)
		return;
	OpenDatabase();
	CString strSQL=_T("SELECT edit_mode FROM webreport_setting");
	CRecordset rs(&theDB);
	int mode=0;
	rs.Open(CRecordset::forwardOnly,strSQL);
	if (!rs.IsEOF())
	{
		CDBVariant variant;
		rs.GetFieldValue((short)0,variant);
		mode=variant.m_iVal;
	}
	rs.Close();
	if(mode!=1)
	{//本地模式，提示切换
		if(POSMessageBox(IDS_CLOUDHINT,MB_YESNO)==IDCANCEL)
			return;
		//ChangeEditMode(1);
		mProgDlg->Start();
		mProgDlg->m_nStep=3;//预计30秒
		AfxBeginThread(ChangeToCloudThread,this);
		return;
	}
	mProgDlg->Start();
	AfxBeginThread(DownloadThread,this);
}
void CLoginDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent==1000)
	{
		if(m_timeCtrl.m_hWnd)
		{
			CTime time=CTime::GetCurrentTime();
			CString strTime=time.Format(_T("%Y-%m-%d %H:%M"));
			m_timeCtrl.SetWindowText(strTime);
			InvalidateRect(m_timeRect); 
		}
	}
	else if (nIDEvent==1001)
	{
		if(theApp.m_bUSB&&theApp.CheckUsbKey()==FALSE)
		{
			POSMessageBox(IDS_NOTREG);
			ExitProcess(0);
		}
#ifdef CHECK_SIGNATUR
		CPOSClientApp* pApp=((CPOSClientApp*)AfxGetApp());
		if (pApp->Checkin()==FALSE)
		{
			ExitProcess(0);
		}
		CSoftwareKey key;
		CString strExpire;
		if(key.VerifySoftwareKey(_T("license.key"),strExpire)!=0)
		{
			POSMessageBox(_T("软件未注册！"));
			ExitProcess(0);
		}
#endif
	}
 
	CPosPage::OnTimer(nIDEvent);
}

void CLoginDlg::UpdateHintData()
{
	m_hintCtrl.SetWindowText(m_strHint);
	CRect   rc;
	m_hintCtrl.GetWindowRect(&rc);    
	ScreenToClient(&rc);      
	InvalidateRect(rc); 
}
BOOL CLoginDlg::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message==WM_KEYDOWN&&pMsg->wParam==VK_ESCAPE)     
		return TRUE;
	if(theApp.m_pMain->GetActiveIndex()==DLG_LOGIN)
	{//只有当前页面是登录时才能刷卡
		if(pMsg->message==WM_KEYDOWN)
		{
			if(pMsg->wParam==VK_PROCESSKEY)
			{
				pMsg->wParam=ImmGetVirtualKey(this->m_hWnd);
			}
			if (pMsg->wParam==VK_RETURN)
			{
				//static CRegexpT <wchar_t> regexp(theApp.CARD_REGEX);
				//MatchResult result = regexp.MatchExact((LPCTSTR)m_strLoginID);
				if (m_bSwipe)
				{//刷卡
					Signin(1);
				}
				else
				{//键盘
					Signin(0);
				}
				return TRUE;
			}
			else if (pMsg->wParam>='0'&&pMsg->wParam<='9')
			{
				OnNumBnClicked(pMsg->wParam-'0'+IDC_BUTTON0);
				return TRUE;
			}
			else if (pMsg->wParam>=VK_NUMPAD0&&pMsg->wParam<=VK_NUMPAD9)
			{
				OnNumBnClicked(pMsg->wParam-VK_NUMPAD0+IDC_BUTTON0);
				return TRUE;
			}
			else if (pMsg->wParam==VK_DELETE||pMsg->wParam==VK_BACK)
			{
				OnBnClickedButtonClear();
				return TRUE;
			}
		}
	}
	return CDialog::PreTranslateMessage(pMsg);
}
HBRUSH CLoginDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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