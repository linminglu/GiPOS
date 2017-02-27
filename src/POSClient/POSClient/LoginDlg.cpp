// LoginDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "POSClient.h"
#include "LoginDlg.h"
#include "InformationDlg.h"
#include "AboutDlg.h"
#include "MSGBoxDlg.h"
#include "LanguageDlg.h"
#include "ClockDlg.h"
#include "OrderPage.h"
#include "ZipArchive.h"
#include "SecondScreen.h"

//#include "deelx.h"
#include <windows.h>
#include <openssl/aes.h>
// CLoginDlg �Ի���

IMPLEMENT_DYNAMIC(CLoginDlg, CPosPage)

CLoginDlg::CLoginDlg(CWnd* pParent /*=NULL*/)
: CPosPage(CLoginDlg::IDD)
, m_strHint(_T(""))
{
	m_bClock=FALSE;
	m_bSwipe=FALSE;
	m_pSyncBtn=NULL;
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
		//���ԭ����Ϣ
		theLang.UpdatePage(this,_T("IDD_1_LOGIN"));
		OnBnClickedButtonClear();
		if(m_pSecond)
		{
			m_pSecond->HideDetail();
		}
		//��������
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

// CLoginDlg ��Ϣ�������

/************************************************************************
* �������ܣ���¼
* ���������type:  0-����ID��¼  1-ˢ����¼
* ���������
* ����ֵ  ��
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
			strID=m_strLoginID.Left(3);//ǰ3λΪID
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
				{//��
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
				{//��½�ɹ�
					CPOSClientApp* pApp=((CPOSClientApp*)AfxGetApp());
					CDBVariant variant;
					rs.GetFieldValue(_T("is_in_traning"),variant);
					m_bTrainingMode=variant.m_boolVal;
					rs.GetFieldValue(_T("employee_last_name"),strPSW);
					strPSW.Replace('\'',' ');
					pApp->m_strUserName.Format(_T("%s"),strPSW);
					pApp->m_strUserID=strID;
					//��ȡ���û���Ȩ���б�
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
					//��ѯ��ǰ�İ��������ʾ
					strSQL.Format(_T("SELECT period_name FROM periods WHERE CURTIME() BETWEEN start_time AND end_time"));
					if(!rs.Open(CRecordset::forwardOnly,strSQL))
						return;
					if(rs.IsEOF())
					{//���쵼�²�ѯ����
						rs.Close();
						strSQL.Format(_T("SELECT period_name FROM periods WHERE end_time<start_time AND (CURTIME()>start_time OR CURTIME()<end_time)"));
						rs.Open(CRecordset::forwardOnly,strSQL);
					}
					if(!rs.IsEOF())
						rs.GetFieldValue(_T("period_name"),pApp->m_strPeriod);
					rs.Close();
					//�л���¥�����
					LOG4CPLUS_INFO(log_pos,"User Loged in : "<<(LPCTSTR)strID);
					if (m_bTrainingMode)
					{//��ѵģʽ���ر����ݿ������ӵ���ѵ���ݿ�
						theDB.Close();
						if(POSMessageBox(IDS_TRAINMODE,MB_YESNO)==IDCANCEL)
						{
							m_bTrainingMode=FALSE;
							OnBnClickedButtonClear();
							return;
						}
					}
					//�ر���ʾ�Ի���
					::SendMessage(m_hTip,WM_COMMAND,IDCLOSE,0);
					pApp->m_bDirty=TRUE;

					if (pApp->m_bQuickService)
					{
						//�������
						theApp.m_bDirty=1;
						theApp.m_nOrderHeadid=0;
						theApp.m_nTableId=-1;
						theApp.m_pMain->SetActivePage(DLG_ORDER);
					}
					else
					{
						if(COrderPage::bNewTainfo)
						{//�������绰,ֱ�ӿ�������
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
	//��ѯ�����
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
	//TODO  ɾ��
	CStatic* pWnd = (CStatic*)GetDlgItem(IDC_STATIC);
	pWnd->ShowWindow(SW_HIDE);
//����ģʽ�����عرհ�ť
	if(CMainSheet::m_iFullScreen==0)
	{
		GetDlgItem(IDC_BUTTON_MINIMIZE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDCANCEL)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BUTTON_SHUTDOWN)->ShowWindow(SW_HIDE);
	}
	
	m_pSyncBtn=(CRoundButton2*)GetDlgItem(IDC_BUTTON_SYNC);
	if(!theApp.IS_SERVER)
	{
		if(m_pSyncBtn)
			m_pSyncBtn->ShowWindow(SW_HIDE);
	}
	mProgDlg=new ProgressDlg;
	mProgDlg->Create(IDD_PROGRESS,this);

	SetTimer(1000,5000,NULL);//ÿ��5��ˢ��ʱ����ʾ
//	if(theApp.m_bUSB)
//		SetTimer(1001,3600000,NULL);//ÿ��1Сʱǩ����������ע��
	if(theApp.IS_SERVER&&m_pSyncBtn&&theApp.m_editMode==1)
		SetTimer(1002,5000,NULL);
	CTime time=CTime::GetCurrentTime();
	CString strTime=time.Format(_T("%Y-%m-%d %H:%M"));
	m_timeCtrl.SetWindowText(strTime);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
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
    hProcess = ::GetCurrentProcess();  //��ȡ��ǰӦ�ó�����̾��
    if(!::OpenProcessToken(hProcess,TOKEN_ADJUST_PRIVILEGES,&hToken))  //�򿪵�ǰ���̵ķ������ƾ��(OpenProcessToken��������ʧ�ܷ���ֵΪ��)
        return ;
    if(!::LookupPrivilegeValue(NULL,SE_SHUTDOWN_NAME,&uID))  //��ȡȨ������Ϊ"SeShutdownPrivilege"��LUID(LookupPrivilegeValue��������ʧ�ܷ���ֵΪ��)
        return ;
    stToken_Privileges.PrivilegeCount = 1;  //��������Ȩ�޸���
    stToken_Privileges.Privileges[0].Luid = uID;  //Ȩ�޵�LUID
    stToken_Privileges.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;  //Ȩ�޵�����,SE_PRIVILEGE_ENABLEDΪʹ�ܸ�Ȩ��
    
    if(!::AdjustTokenPrivileges(hToken,FALSE,&stToken_Privileges,sizeof stToken_Privileges,NULL,NULL))  //���������������ָ��Ȩ��(AdjustTokenPrivileges��������ʧ�ܷ���ֵΪ��)
        return ;
    if(::GetLastError() != ERROR_SUCCESS)  //�鿴Ȩ���Ƿ�����ɹ�
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
	else if (theLang.m_strLang.Find(_T("����"))>=0)
	{
		lpParameters=_T("lang=0");
	}
	else if (theLang.m_strLang.Find(_T("���w"))>=0)
	{
		lpParameters=_T("lang=2");
	}
	ShellExecute(GetSafeHwnd(), NULL, _T("CheckTool.exe"), lpParameters, NULL,SW_NORMAL);
}
/************************************************************************
* �������ܣ�������ѵģʽ��ͨ��ģ����888��¼ʵ��
* ���������
* ���������
* ����ֵ  ��
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
	else if (theLang.m_strLang.Find(_T("����"))>=0)
	{
		lpParameters=_T("0");
	}
	else if (theLang.m_strLang.Find(_T("���w"))>=0)
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
		if (!theApp.m_strVipURL.IsEmpty())
		{
			CString strCurrentUrl;
			strCurrentUrl.Format(_T("http://%s:%d"),theApp.m_strVipURL,theApp.m_nVipPort);
			ShellExecute(GetSafeHwnd(), _T("OPEN"), strCurrentUrl, NULL, NULL,SW_NORMAL);
		}
	}catch(...)
	{
	}
}
/************************************************************************
* �������ܣ����ݿⱸ��
* ���������
* ���������
* ����ֵ  ��
************************************************************************/
void CLoginDlg::OnBnClickedBackup()
{
// 	LPCTSTR lpParameters=NULL;
// 	if (theLang.m_strLang.Find(_T("English"))>=0)
// 	{
// 		lpParameters=_T("backupdb lang=1");
// 	}
// 	else if (theLang.m_strLang.Find(_T("����"))>=0)
// 	{
// 		lpParameters=_T("backupdb=1 lang=0");
// 	}
// 	else if (theLang.m_strLang.Find(_T("���w"))>=0)
// 	{
// 		lpParameters=_T("backupdb=1 lang=2");
// 	}
// 	else
// 	{
// 		lpParameters=_T("backupdb");
// 	}
// 	ShellExecute(GetSafeHwnd(), NULL, _T("POSManager.exe"), lpParameters, NULL,SW_NORMAL);
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
	pDlg->DoDownload(pDlg->mProgDlg);
	return 0;
}

int CLoginDlg::DoDownload(ProgressDlg* progress)
{
	int nCode=-1;
	try{
		CDatabase db;
		db.OpenEx(_T("DSN=agile_pos"));
		CString strDir=_T("sql_data");
		CreateDirectory(strDir,NULL);
		CRecordset rs(&db);
		CString strSQL;
		CString strDbVer;
		strSQL.Format(_T("SELECT db_version FROM total_statistics"));
		rs.Open(CRecordset::forwardOnly,strSQL);
		if (!rs.IsEOF())
		{
			rs.GetFieldValue((short)0,strDbVer);
		}
		rs.Close();
		JSONVALUE root;
		root[_T("db_version")] = strDbVer;
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
		rs.Close();
		root["versions"] = versions;
		CString strURL,strValue;
		CInternetSession session;
		session.SetOption(INTERNET_OPTION_CONNECT_TIMEOUT, 1000 * 10);
		session.SetOption(INTERNET_OPTION_CONNECT_BACKOFF, 1000);
		session.SetOption(INTERNET_OPTION_CONNECT_RETRIES, 1);
		CHttpConnection* pConnection = session.GetHttpConnection(theApp.m_strCloudURL,(INTERNET_PORT)80);
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
			LOG4CPLUS_ERROR(log_pos,"Connect "<<(LPCTSTR)theApp.m_strCloudURL<<":"<<" status code="<<dwStatus);
			session.Close();
			pFile->Close();
			delete pFile;
			if(progress)
				progress->Stop();
			return -1;
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
			nCode=root[_T("result")].asInt();
			if(progress||nCode!=0)
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
				if(progress)
					progress->Stop();
				return -2;
			}
			char buffer[2049]={0};
			int nReadCount = 0;
			while((nReadCount = pFile->Read(buffer, 2048)) > 0)
			{
				NetFile.Write(buffer,nReadCount);
			}
			NetFile.Close();
			CString strRestart=_T("restaurant macros tax_primary user_workstations ");
			BOOL bNeedRestart=FALSE;
			CZipArchive zip;
			zip.Open(_T("_tmp_download"));
			int zip_count=zip.GetNoEntries();
			for(int i=0;i<zip_count;i++)
			{
				try{
					zip.ExtractFile(i,strDir);
					CZipFileHeader fhInfo;
					zip.GetFileInfo(fhInfo,i);
					CString fileName=fhInfo.GetFileName();
					CString fullPath=strDir+_T("/")+fileName;
					if(fileName.Right(4)==_T(".jpg"))
					{//��ӡģ��ͼƬ
						MoveFileEx(fullPath,fileName,MOVEFILE_REPLACE_EXISTING);
						continue;
					}
					else if(fileName.Right(4)==_T(".db3"))
					{//ƽ�������ļ�
						CString newPath=_T("../pad_server/file/")+fileName;
						MoveFileEx(fullPath,newPath,MOVEFILE_REPLACE_EXISTING);
						continue;
					}

					CStdioFile file;
					file.Open(fullPath,CFile::modeRead);
					CString line,columns,db_col;
					file.ReadString(line);
					file.Close();
					strSQL.Format(_T("SELECT COLUMN_NAME FROM INFORMATION_SCHEMA.COLUMNS WHERE TABLE_NAME='%s' AND TABLE_SCHEMA='coolroid'"),fileName);
					rs.Open(CRecordset::forwardOnly,strSQL);
					while (!rs.IsEOF())
					{
						rs.GetFieldValue((short)0,strDbVer);
						db_col.AppendFormat(_T("%s "),strDbVer);
						rs.MoveNext();
					}
					rs.Close();
					int nTokenPos = 0;
					CString strToken = line.Tokenize(_T(","), nTokenPos);
					while (!strToken.IsEmpty())
					{
						if(db_col.Find(strToken)>=0)
						{
							columns.AppendFormat(_T("`%s`,"),strToken);
						}
						else
						{
							columns.AppendFormat(_T("@%s,"),strToken);
						}
						strToken = line.Tokenize(_T(","), nTokenPos);
					}
					columns.Delete(columns.GetLength()-1);
					try{
						strSQL.Format(_T("TRUNCATE TABLE %s"),fileName);
						db.ExecuteSQL(strSQL);
						strSQL.Format(_T("LOAD DATA LOCAL INFILE '%s' REPLACE INTO TABLE %s FIELDS TERMINATED BY ',' OPTIONALLY ENCLOSED BY '\"' LINES TERMINATED BY '\\n' IGNORE 1 LINES (%s)"),fullPath,fileName,columns);
						db.ExecuteSQL(strSQL);
						if(!bNeedRestart&&progress)
						{
							int nPos=strRestart.Find(fileName);
							if(nPos>=0)
								bNeedRestart=TRUE;
						}
						if(fileName.Compare(_T("print_templates"))==0)
						{
							//֪ͨ��ӡ�������¼���
							HWND hWnd=::FindWindow(_T("CPrintServerDlg"),_T("AgilePrintServer"));
							if(hWnd)
							{
								::PostMessage(hWnd, WM_USER+100, 0,0);
							}
						}
					}catch(CDBException* ex)
					{
						POSMessageBox(ex->m_strError);
					}
				}catch(...)
				{

				}
			}
			zip.Close();
			JSONVALUE notify;
			notify["db_version"] =strDbVer;
			notify[_T("guid")]=theApp.m_strResId;
			JSONVALUE response;
			HttpPost(theApp.m_strCloudURL,80,_T("/client_download/?doupdate=1"),notify,response);
			if(progress)
			{
				if(bNeedRestart)
					POSMessageBox(IDS_SYNCOK2);
				else
					POSMessageBox(IDS_SYNCOK);
			}
			nCode=0;
		}
		pFile->Close();
		db.Close();	
	}catch (CInternetException* pEx)
	{
		TCHAR szErr[1024];
		pEx->GetErrorMessage(szErr, 1024);
		POSMessageBox(szErr);
		nCode=-3;
	}
	catch(...)
	{
		nCode=-3;
	}
	if(progress)
		progress->Stop();
	return nCode;
}
void CLoginDlg::OnBnClickedSync()
{
	if(!theApp.IS_SERVER||m_bTrainingMode)
		return;
	m_pSyncBtn->SetIcon((HICON)NULL,CRoundButton2::RIGHTUP);
	KillTimer(1002);
	SetTimer(1002,600*1000,NULL);//10���Ӻ��ټ��

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
	if(mode==1)
	{
		mProgDlg->Start();
		AfxBeginThread(DownloadThread,this);
	}
	
}
/************************************************************************
* �������ܣ�������ݿ����
* ���������
* ���������
* ����ֵ  ���´β�ѯ�ȴ�ʱ��(��)
************************************************************************/
int CLoginDlg::CheckForUpdate()
{
	CRecordset rs(&theDB);
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
	strSQL.Format(_T("SELECT major_version FROM www_version"));
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

	JSONVALUE response;
	BOOL bRet=HttpPost(theApp.m_strCloudURL,80,_T("/client_download/?checkupdate=1"),root,response);
	if(bRet)
	{
		int status = response[_T("has_update")].asInt();
		if (status > 0)
		{//�и���
			m_pSyncBtn->SetIcon(IDI_ICON_NEW,CRoundButton2::RIGHTUP);
			return -1;
		}
		int wait=response[_T("wait_minutes")].asInt();
		if(wait<1)
			wait=10;
		return wait*60;
	}
	else
		return 600;
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
	else if(nIDEvent==1002)
	{
		if(theApp.m_pMain->GetActiveIndex()==DLG_LOGIN)
		{//ֻ���ڵ�¼�����ˢ��
			int wait=CheckForUpdate();
			KillTimer(1002);
			if(wait>0)
			{
				SetTimer(1002,wait*1000,NULL);
			}
		}
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
	{//ֻ�е�ǰҳ���ǵ�¼ʱ����ˢ��
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
				{//ˢ��
					Signin(1);
				}
				else
				{//����
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
		return (HBRUSH)::GetStockObject(NULL_BRUSH); //���ش˻�ˢ����ʹ��̬�ı�͸��
	}
	return   hbr; 
}