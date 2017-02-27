// POSClient.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include <Windows.h>
#include <Iphlpapi.h>
#include <Tlhelp32.h>
#include "POSClient.h"
#include "MainSheet.h"
#include "MSGBoxDlg.h"
#include "LoginDlg.h"
#include "OrderDlg.h"
#include "FloorDlg.h"
#include "FloorViewDlg.h"
#include "PayDlg.h"
#include "SplitCheckDlg.h"
#include "PickUpDlg.h"
#include "FunctionDlg.h"
#include "SecondScreen.h"
#include "ManagerDlg.h"
#include "ViewCheckDlg.h"
#include "WebDlg.h"
#include "AddPosDlg.h"
#include "WebLoginDlg.h"
#include <GdiPlus.h>
#include "SplashWnd.h"
#include "HardwareInfo.h"
#include "cefclient/CefBrowserApp.h"

#include "Winspool.h"
#include "ESCPrinter.h"

#include <openssl/pem.h>
#include <openssl/evp.h>
#include <openssl/md5.h>
#include <openssl/aes.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define WEB_VERSION
#define LATEST_DB_VERSION _T("20170301")

// CPOSClientApp

BEGIN_MESSAGE_MAP(CPOSClientApp, CWinApp)
//	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CPOSClientApp 构造

CPOSClientApp::CPOSClientApp()
{
	// 将所有重要的初始化放置在 InitInstance 中
	m_bDirty=TRUE;
	m_bRefund=FALSE;
	m_nDeviceId=1;
	m_bQuickService=FALSE;
	m_bQuickOnce=FALSE;
	m_bInputChkName=FALSE;
	m_nAutoSendType=0;
	m_pRecentFileList=NULL;
	m_pSecond=NULL;
	CURRENCY_SYMBOL = _T("￥");
	DECIMAL_PLACES=1;
	m_bTaxGST=FALSE;
	m_nTaxType=1;
	m_dTaxRate=0;
	enctrypkey = (unsigned char*)"COOLROIDagilePOS";
	m_strQfAppcode=_T("DC61EA9C7D46494BA82E84CD292748A8");
	m_strQfServerURL=_T("openapi.qfpay.com");
	IS_SERVER=FALSE;
}

// 唯一的一个 CPOSClientApp 对象

CPOSClientApp theApp;
CMultiLanguage	theLang;
Logger log_pos;
CDatabase theDB;//全局的数据库连接
SecondScreenDlg* m_pSecond;
BOOL m_bTrainingMode=FALSE;//是否培训模式
int m_bNotReg=FALSE;//0 注册 ，1 未注册，2 过期
BOOL NO_FLOOR_PRICE=0;
DWORD m_dTextColor=RGB(255,255,255);
DWORD DEFALUT_BACKGROUND_COLOR=RGB(89,67,58);
std::map<CString,int> macrosInt;//全局宏定义
std::map<int,TaxItem*> taxGroup;
extern UINT CODE_PAGE;
extern UINT LF_CHARSET;
extern CString LF_FaceName;
extern CString thePrintDir;
BOOL CPOSClientApp::m_bQuickService=FALSE;
HINSTANCE hSQBDll;//收钱吧接口
typedef const char* (__stdcall *pfunc)(const char* cmd);
typedef const char* (__stdcall *versionFunc)(void);

BOOL OpenDatabase(BOOL bRecounect)
{
	try
	{
		if (bRecounect)
		{
			theDB.Close();
		}
		if(!theDB.IsOpen())
		{
			if(m_bTrainingMode==FALSE)
				return theDB.OpenEx(_T("DSN=agile_pos"),CDatabase::noOdbcDialog);
			else
				return theDB.OpenEx(_T("DSN=agile_pos_training"),CDatabase::noOdbcDialog);
		}
	}
	catch(CDBException* e )
	{
		LOG4CPLUS_ERROR(log_pos,(LPCTSTR)e->m_strError);
		if(bRecounect)
		{
			CString str2;
			theLang.LoadString(str2,IDS_NETWARNING);
			AfxMessageBox(str2,MB_ICONEXCLAMATION|MB_SYSTEMMODAL);
		}
		else
			AfxMessageBox(e->m_strError,MB_ICONEXCLAMATION);
		e->Delete();
		return FALSE;
	}
	return TRUE;
}

CString GetFiledValue(LPCTSTR strSQL)
{
	CRecordset rs(&theDB);
	if(rs.Open(CRecordset::forwardOnly,strSQL))
	{
		if(!rs.IsEOF())
		{
			CString strKey;
			rs.GetFieldValue((short)0,strKey);
			return strKey;
		}
	}
	rs.Close();
	return _T("");
}

BOOL HttpPost(LPCTSTR server,int port,LPCTSTR url,JSONVALUE& request,JSONVALUE& response)
{
	try
	{
		CString strSend,strURL;
		CInternetSession session;
		session.SetOption(INTERNET_OPTION_CONNECT_TIMEOUT, 1000 * 15);
		session.SetOption(INTERNET_OPTION_CONNECT_BACKOFF, 1000);
		session.SetOption(INTERNET_OPTION_CONNECT_RETRIES, 1);
		CHttpConnection* pConnection = session.GetHttpConnection(server,(INTERNET_PORT)port);
		CString szHeaders   = L"Content-Type: application/x-www-form-urlencoded;";
		std::wstring str;
		request.ToString(str);
		int wcsLen0 = ::WideCharToMultiByte(CP_UTF8, NULL, str.c_str(), str.length(), NULL, 0, NULL, NULL);
		char* sz0 = new char[wcsLen0 + 1];
		::WideCharToMultiByte(CP_UTF8, NULL, str.c_str(), -1, sz0, wcsLen0,  NULL, NULL);
		sz0 [wcsLen0] = '\0';
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
		AES_cbc_encrypt((const unsigned char *)sz0, encrypt_text, len, &aes_enc_ctx, ivec, AES_ENCRYPT); 
		CHttpFile* pFile = pConnection->OpenRequest(CHttpConnection::HTTP_VERB_POST,url);
		pFile->SendRequest(szHeaders,szHeaders.GetLength(),(LPVOID)encrypt_text,len);
		delete sz0;
		delete encrypt_text;
		DWORD dwRet;
		pFile->QueryInfoStatusCode(dwRet);
		if(dwRet != HTTP_STATUS_OK)
		{
			LOG4CPLUS_ERROR(log_pos,"Connect "<<(LPCTSTR)server<<":"<<port<<" status code="<<dwRet);
			session.Close();
			pFile->Close();
			delete pFile;
			return FALSE;
		}
		CString strHeader;
		pFile->QueryInfo(HTTP_QUERY_CONTENT_TYPE,strHeader);
		char buf[4096]={0};
		TCHAR* sz1=NULL;
		if(strHeader.CompareNoCase(_T("text/plain"))==0)
		{//需要解密
			len=pFile->Read(buf,sizeof(buf));
			AES_KEY aes_dec_ctx;
			unsigned char ivec[AES_BLOCK_SIZE]={'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'};
			unsigned char *plain_text=(unsigned char *) new char[len];
			AES_set_decrypt_key(theApp.enctrypkey, 128, &aes_dec_ctx);
			AES_cbc_encrypt((const unsigned char *)buf, plain_text, len, &aes_dec_ctx, ivec, AES_DECRYPT);
			wcsLen0 = ::MultiByteToWideChar(CP_UTF8, NULL, (char*)plain_text, strlen((char*)plain_text), NULL, 0);
			sz1 = new TCHAR[wcsLen0 + 1];
			::MultiByteToWideChar(CP_UTF8, NULL, (char*)plain_text, -1, sz1, wcsLen0);
			sz1[wcsLen0] = '\0';
			delete plain_text;
		}
		else
		{
			pFile->ReadString((LPTSTR)buf,sizeof(buf)-1);
			wcsLen0 = ::MultiByteToWideChar(CP_UTF8, NULL, buf, strlen(buf), NULL, 0);
			sz1 = new TCHAR[wcsLen0 + 1];
			::MultiByteToWideChar(CP_UTF8, NULL, buf, -1, sz1, wcsLen0);
			sz1[wcsLen0] = '\0';
		}
		pFile->Close();
		CString jStr;
		JSONVALUE::Unescape(sz1,jStr);
		delete sz1;
		if(!response.Parse((LPCTSTR)jStr,JSON_FLAG_LOOSE))
		{//请求失败
			LOG4CPLUS_ERROR(log_pos,"JSON Parse error");
			return FALSE;
		}
		return TRUE;
	}catch(...)
	{
		return FALSE;
	}
}
void KillProcessByName(LPCTSTR lpProcessName)
{
    HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPALL, NULL);
    PROCESSENTRY32 pEntry;
    pEntry.dwSize = sizeof (pEntry);
    BOOL hRes = Process32First(hSnapShot, &pEntry);
    while (hRes)
    {
		TRACE(_T("%s\n"),pEntry.szExeFile);
        if (wcscmp(pEntry.szExeFile, lpProcessName) == 0)
        {
            HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, 0,(DWORD) pEntry.th32ProcessID);
            if (hProcess != NULL)
            {
                TerminateProcess(hProcess, 9);
                CloseHandle(hProcess);
            }
        }
        hRes = Process32Next(hSnapShot, &pEntry);
    }
    CloseHandle(hSnapShot);
}
INT_PTR POSMessageBox(LPCTSTR lpszText,UINT nType)
{
	MSGBoxDlg dlg;
	dlg.m_strText=lpszText;
	dlg.m_nType=nType;
	return dlg.DoModal();
}
int POSMessageBox(UINT nIDPrompt,UINT nType)
{
	MSGBoxDlg dlg;
	theLang.LoadString(nIDPrompt,dlg.m_strText);
	dlg.m_nType=nType;
	return dlg.DoModal();
}
int _dpiY=96;
int _dpiX=96;
void DpiInit()
{
	HDC hdc = GetDC(NULL); 
	if (hdc) 
	{ 
		_dpiX = GetDeviceCaps(hdc, LOGPIXELSX); 
		_dpiY = GetDeviceCaps(hdc, LOGPIXELSY); 
		ReleaseDC(NULL, hdc); 
	}
}
int ScaleX(int pt) 
{
	return MulDiv(pt, _dpiX, 96);
} 
int ScaleY(int pt) 
{
	return MulDiv(pt, _dpiY, 96); 
} 
// CPOSClientApp 初始化
CSplashWnd splash;

BOOL CPOSClientApp::InitInstance()
{
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();
	WNDCLASS wc;
	::GetClassInfo(AfxGetInstanceHandle(),  _T("#32770"), &wc);
	wc.lpszClassName = _T("CoolroidPOS");
	AfxRegisterClass(&wc);

	int argc = 0;
	LPWSTR *lpszArgv = NULL;
	LPTSTR szCmdLine = GetCommandLine(); //获取命令行参数；
	lpszArgv = CommandLineToArgvW(szCmdLine, &argc); //拆分命令行参数字符串；
	if (argc >= 2) {
		if (lpszArgv[1]=_T("-qs"))
		{//快餐模式
			m_bQuickService=TRUE;
		}
	}
	m_bUseIE=GetPrivateProfileInt(_T("POS"),  _T("USE_IE"), 0,_T(".\\config.ini"));
	try{
		if(m_bUseIE==FALSE)
		{
			if(CCefBrowserApp::Init(m_hInstance)>=0)
				return FALSE;
		}
	}catch(...)
	{
	}
	CODE_PAGE=GetPrivateProfileInt(_T("POS"),  _T("CodePage"), 0,_T(".\\config.ini"));
	NO_FLOOR_PRICE=GetPrivateProfileInt(_T("POS"),  _T("NO_FLOOR_PRICE"), 0,_T(".\\config.ini"));
	LF_CHARSET=GetPrivateProfileInt(_T("POS"),  _T("LF_CHARSET"), DEFAULT_CHARSET,_T(".\\config.ini"));
	::GetPrivateProfileString(_T("POS"),_T("LF_FaceName"),_T("宋体"),LF_FaceName.GetBuffer(40),40,_T(".\\config.ini"));
	LF_FaceName.ReleaseBuffer();
	theLang.Initialize();
	
	CString str2;
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	Gdiplus::GdiplusStartup(&m_gdiplusToken, &gdiplusStartupInput, NULL);
	Gdiplus::Image* pImage = Gdiplus::Image::FromFile(L"Picture\\splash.jpg");
	if (pImage)
	{
		splash.SetImage(pImage);
		//delete pImage; // you are free to delete now
		splash.Show();
		splash.SetProgress( 0, IDS_INICFG);
		splash.SetAutoProgress(0, 30, 3);
	}
	TCHAR cPath[200];
	//setlocale(LC_ALL, "En_US");
	//LOG4CPLUS 记录中文用到
	std::locale::global(std::locale::classic());
	::GetModuleFileName(NULL,cPath,sizeof(cPath));
	PropertyConfigurator::doConfigure(L"log4cplus.properties"); 
	log_pos = Logger::getInstance(_T("pos"));
	LOG4CPLUS_INFO(log_pos,"***********************Agile POS Start**************************");
	m_strVersion=_T("V")+GetFileVersion(cPath);
	m_strVersion.Replace(',','.');
	LOG4CPLUS_INFO(log_pos,"File version: "<<(LPCTSTR)m_strVersion);
	DEFALUT_BACKGROUND_COLOR=::GetPrivateProfileInt(_T("POS"),_T("BACKGRD_COLOR"),0,_T(".\\config.ini"));
	if(DEFALUT_BACKGROUND_COLOR==0)
		DEFALUT_BACKGROUND_COLOR=RGB(89,67,58);
	//m_dTextColor=::GetPrivateProfileInt(_T("POS"),_T("TEXT_COLOR"),0,_T(".\\config.ini"));
#ifndef _DEBUG
	HANDLE hMutex = CreateMutex(NULL, TRUE, _T("COOLROID_POS_CLIENT"));
	if ( GetLastError() == ERROR_ALREADY_EXISTS)
	{
		CloseHandle(hMutex);
		hMutex = NULL;
		theLang.LoadString(IDS_ALREADYRUN,str2);
		AfxMessageBox(str2,MB_SYSTEMMODAL);
		return FALSE;
	}
#endif
	if (!AfxSocketInit())
	{
		AfxMessageBox(_T("Windows Socket init fail!"),MB_SYSTEMMODAL);
		return FALSE;
	}

	AfxEnableControlContainer();
	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	SetRegistryKey(_T("COOLROID"));
	DpiInit();
	static const TCHAR _afxFileSection[] = _T("Recent List");
	static const TCHAR _afxFileEntry[] = _T("String%d");
	m_pRecentFileList = new CRecentList(0, _afxFileSection, _afxFileEntry, 20);
	m_pRecentFileList->ReadList();
	
	CreatButton::m_nFullWidth=::GetPrivateProfileInt(_T("POS"),_T("CXSCREEN"),1024,_T(".\\config.ini"));
	CreatButton::m_nFullHeight=::GetPrivateProfileInt(_T("POS"),_T("CYSCREEN"),768,_T(".\\config.ini"));
	m_isCusFloor=::GetPrivateProfileInt(_T("POS"),_T("CUSTOMER_FLOOR"),0,_T(".\\config.ini"));
	CMainSheet::m_iStaticsInfo=::GetPrivateProfileInt(_T("POS"),_T("STATIS_INFO"),1,_T(".\\config.ini"));
	splash.SetProgress( 20, IDS_CONECTDB);
	if(!OpenDatabase(TRUE))
	{
		LOG4CPLUS_INFO(log_pos,"OpenDatabase Failed");
		ShellExecute(NULL, NULL, _T("ServerIpSetting.exe"), NULL, NULL,SW_NORMAL);
		return FALSE;
	}
	CString strSQL;
	CRecordset rs(&theDB);
	try{
		strSQL.Format(_T("SELECT cr_url,cr_res_id,cr_res_pwd,edit_mode FROM webreport_setting"));
		if(rs.Open(CRecordset::forwardOnly,strSQL))
		{
			if (!rs.IsEOF())
			{
				CString strVal;
				rs.GetFieldValue(_T("cr_url"),strVal);
				m_strCloudURL.Format(_T("%s"),strVal);
				rs.GetFieldValue(_T("cr_res_id"),strVal);
				m_strResId.Format(_T("%s"),strVal);
				rs.GetFieldValue(_T("cr_res_pwd"),strVal);
				m_strPhone.Format(_T("%s"),strVal);
				rs.GetFieldValue(_T("edit_mode"),strVal);
				m_editMode=_wtoi(strVal);
			}
			rs.Close();
		}
	}catch(...)
	{
		POSMessageBox(IDS_DATABASE_LOWER);
		return FALSE;
	}
	strSQL.Format(_T("select * from vip_setting"));
	rs.Open( CRecordset::forwardOnly,strSQL);
	if (!rs.IsEOF())
	{
		CString strVal;
		rs.GetFieldValue(_T("ip_addr"),strVal);
		strVal.Trim();
		m_strVipURL=strVal;
		int index=strVal.Find(':');
		m_nVipPort=80;
		if (index>0)
		{
			m_strVipURL=strVal.Left(index);
			m_nVipPort=_wtoi(strVal.Right(strVal.GetLength()-index-1));
		}
	}
	rs.Close();
#if defined(WEB_VERSION)
	if(CheckInit()==FALSE)
		return FALSE;
#endif
	//ResetAutoIncrement();//测试发现不需要
	//从macros表获取全局的设置
	strSQL.Format(_T("SELECT db_version FROM total_statistics"));
	if(rs.Open(CRecordset::forwardOnly,strSQL))
	{
		if(!rs.IsEOF())
		{
			CString strKey;
			rs.GetFieldValue(_T("db_version"),strKey);
			if(strKey.Compare(LATEST_DB_VERSION)<0)
			{
				POSMessageBox(IDS_DATABASE_LOWER);
			}
		}
	}
	rs.Close();
	strSQL.Format(_T("SELECT * FROM macros;"));
	if(!rs.Open(CRecordset::forwardOnly,strSQL))
	{
		LOG4CPLUS_INFO(log_pos,"Open Table macros Failed");
		return FALSE;
	}
	macrosInt[_T("TABLE_UPDATE_TIMER")]=10;
	macrosInt[_T("PRINT_SERVICE_DETAIL")]=1;
	while(!rs.IsEOF())
	{
		CString strKey,strValue;
		rs.GetFieldValue(_T("macros_name"),strKey);
		rs.GetFieldValue(_T("macros_value"),strValue);
		//macrosInt.insert(pair<CString,int>(strKey,_wtoi(strValue)));
		if(strKey==_T("TIPS_SUGGEST"))
		{
			CString strToken;
			for(int i=0;i<strValue.GetLength();i++)
			{
				if(strValue[i]==0)
				{//end
					m_tipSuggests.push_back(_wtol(strToken));
					break;
				}
				if(iswdigit(strValue[i]))
				{
					strToken+=strValue[i];
				}
				else
				{
					m_tipSuggests.push_back(_wtol(strToken));
					strToken.Empty();
				}
			}
		}
		else
		{
			macrosInt[strKey]=_wtoi(strValue);
		}
		
		rs.MoveNext();
	}
	rs.Close();
	splash.SetProgress( 60, IDS_CHECKREG);
	
	

//验证是否注册
#if defined(WEB_VERSION)
	int reg_pos=0;
	strSQL.Format(_T("SELECT AES_DECRYPT(pos,\"%s1\") FROM pos_keys"),m_strResId);
	try{
	if(rs.Open(CRecordset::forwardOnly,strSQL))
	{
		if (!rs.IsEOF())
		{
			CString strVal;
			rs.GetFieldValue((short)0,strVal);
			int index=strVal.Find('|');
			reg_pos=_wtoi(strVal.Left(index));
			if(reg_pos<=0)
			{
				m_bNotReg=TRUE;
				POSMessageBox(IDS_NOTREG);
			}
			else
			{
				CString strExpire=strVal.Right(strVal.GetLength()-index-1);
				CTime timeNow=CTime::GetCurrentTime();
				CTime time(_wtoi(strExpire.Mid(0,4)),_wtoi(strExpire.Mid(5,2)),_wtoi(strExpire.Mid(8,2)),0,0,0);
				CTimeSpan span=time-timeNow;
				if(span.GetDays()<=30)
				{
					CString hint,str2;
					theLang.LoadString(str2,IDS_EXPIER);
					hint.Format(str2,span.GetDays());
					POSMessageBox(hint);
				}
				if(span.GetDays()<=0)
					m_bNotReg=TRUE;
				
			}
		}
		rs.Close();
	}
	}catch(...)
	{
		m_bNotReg=TRUE;
		POSMessageBox(IDS_NOTREG);
	}
	if(reg_pos>0)
	{//检查注册数
		strSQL.Format(_T("SELECT COUNT(*) FROM user_workstations WHERE opos_device_name IS NOT NULL"));
		if(rs.Open(CRecordset::forwardOnly,strSQL))
		{
			if (!rs.IsEOF())
			{
				CString strVal;
				rs.GetFieldValue((short)0,strVal);
				int count=_wtoi(strVal);
				if(reg_pos<count)
				{
					m_bNotReg=TRUE;
					POSMessageBox(IDS_NOTVALID);
				}
			}
		}
		rs.Close();
		//检查更新时间
		strSQL.Format(_T("SELECT datediff(NOW(),cr_last_endtime) FROM webreport_setting"));
		if(rs.Open(CRecordset::forwardOnly,strSQL))
		{
			if (!rs.IsEOF())
			{
				CString strVal;
				rs.GetFieldValue((short)0,strVal);
				int days=_wtoi(strVal);
				if(days>30)
				{
					m_bNotReg=TRUE;
					POSMessageBox(IDS_NEED_ACTIVE);
				}
				else if(days>15)
				{
					POSMessageBox(IDS_NEED_ACTIVE);
				}
			}
			rs.Close();
		}
	}
	
#else
	#if defined(GICATER_VERSION)
		CSoftwareKey softkey;
		softkey.m_nKeyType=2;
		CString strExpire;
		TCHAR LocalDir[MAX_PATH]; 
		SHGetSpecialFolderPath(NULL,LocalDir,CSIDL_LOCAL_APPDATA,0);
		CString strDir=LocalDir;
		strDir+=_T("\\Agile\\license-1.key");
		int iRet=softkey.VerifySoftwareKey(strDir,PRODUCT_POS,strExpire);
		if(iRet<0)
		{
			m_bNotReg=TRUE;
			MSGBoxDlg dlg;
			CString strVal;
			dlg.m_nType=MB_YESNO;
			theLang.LoadString(dlg.m_strText,IDS_NOTREG2);
			theLang.LoadString(dlg.m_strYes,IDS_BUYNOW);
			theLang.LoadString(dlg.m_strNo,IDS_REGLATER);
			if(dlg.DoModal()==IDOK)
			{
				ShellExecute(NULL, _T("OPEN"), _T("http://gicater.taobao.com/"), NULL, NULL,SW_NORMAL);
			}
		}
		else
		{
			CTime timeNow=CTime::GetCurrentTime();
			CTime time(_wtoi(strExpire.Mid(0,4)),_wtoi(strExpire.Mid(4,2)),_wtoi(strExpire.Mid(6,2)),0,0,0);
			CTimeSpan span=time-timeNow;
			if(span.GetDays()<=30)
			{
				CString hint,str2;
				theLang.LoadString(str2,IDS_EXPIER);
				hint.Format(str2,span.GetDays());
				POSMessageBox(hint);
			}
		}
	#else

		CSoftwareKey softkey;
	  #ifdef EN_VERSION
		softkey.m_nKeyType=3;
	  #endif
		CString strExpire;
		TCHAR LocalDir[MAX_PATH]; 
		SHGetSpecialFolderPath(NULL,LocalDir,CSIDL_LOCAL_APPDATA,0);
		CString strDir=LocalDir;
		strDir+=_T("\\Agile\\license.key");
		int iRet=softkey.VerifySoftwareKey(strDir,PRODUCT_POS,strExpire);
		if(iRet<0)
		{
			m_bNotReg=TRUE;
			switch(iRet)
			{
			case -1:
				POSMessageBox(IDS_NOTVALID);
				break;
			case -2:
				POSMessageBox(IDS_GUOQI);
				m_bNotReg=2;
				break;
			case -3:
				POSMessageBox(IDS_NOTTHISMACH);
				break;
			default:
				POSMessageBox(IDS_NOTREG);
				//return FALSE;
			}

		}
		else
		{
			CTime timeNow=CTime::GetCurrentTime();
			CTime time(_wtoi(strExpire.Mid(0,4)),_wtoi(strExpire.Mid(4,2)),_wtoi(strExpire.Mid(6,2)),0,0,0);
			CTimeSpan span=time-timeNow;
			if(span.GetDays()<=30)
			{
				CString hint,str2;
				theLang.LoadString(str2,IDS_EXPIER);
				hint.Format(str2,span.GetDays());
				POSMessageBox(hint);
			}
		}
	#endif
#endif
	splash.SetProgress( 80, IDS_INITPRINT);
	//初始化打印目录
	InitPrintService();
	int ret=GetDeviceID();
	if (ret<0)
	{
		AfxMessageBox(_T("Get POS Config Fail!"),MB_SYSTEMMODAL);
		return FALSE;
	}
	else if(ret>0)
		return FALSE;
	//查找并启动打印进程
	if(::FindWindow(_T("CPrintServerDlg"),_T("AgilePrintServer"))==NULL)
	{
		STARTUPINFO si = { sizeof(STARTUPINFO) };
		si.cb = sizeof(si);
		si.dwFlags = STARTF_USESHOWWINDOW;
		si.wShowWindow = SW_HIDE;
		PROCESS_INFORMATION pi;
		CreateProcess(_T("PrintServer.exe"), NULL , NULL, NULL, FALSE, CREATE_NO_WINDOW , NULL, NULL, &si, &pi);
	}

#ifdef CHECK_SIGNATUR
	//签到
	if(Checkin()==FALSE)
	{
		POSMessageBox(_T("系统时间不匹配！\n请将系统时间设置为正确的值。"));
		return FALSE;
	}
#endif
	InitPrinter();
	m_txtFont.CreatePointFont(120,_T("Microsoft YaHei"));
	splash.SetProgress( 90, IDS_LOADDISPLAY);
	//判断是服务器端还是客户端
	HKEY hKey;
	CString strServer;
	DWORD dwtype = REG_SZ;
	DWORD len=256;
	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, _T("SOFTWARE\\ODBC\\ODBC.INI\\agile_pos"), 0, KEY_READ, &hKey) == ERROR_SUCCESS)
	{
		RegQueryValueEx(hKey, _T("SERVER"), 0, &dwtype, (LPBYTE)strServer.GetBuffer(256), &len);
		strServer.ReleaseBuffer();
		RegCloseKey(hKey);
	}
	if(strServer.Compare(_T("127.0.0.1"))==0)
		IS_SERVER=TRUE;
	if(IS_SERVER==FALSE)
	{//判断当前IP是否为ODBC中的IP
		char szName[256]={0}; 
		gethostname(szName,256);
		hostent *pHost=gethostbyname(szName);
		if(pHost)
		{
			for(int i=0;pHost->h_addr_list[i] != NULL;i++)
			{
				in_addr addr; 
				addr.s_addr   =*(DWORD*)(pHost-> h_addr_list[i]);
				char* ch=inet_ntoa(addr);
				WCHAR ip[128]={0};
				MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED,ch,strlen(ch),ip,128);
				if(strServer.Compare(ip)==0)
				{
					IS_SERVER=TRUE;
					break;
				}
			}
			
		}
	}
	CMainSheet dlg;
	dlg.pSplash=&splash;
	m_pMain = &dlg;
	CLoginDlg m_dlgLogin;
	OrderDlg m_dlgOrder;
	FloorViewDlg m_dlgFloor;
	PayDlg m_dlgPay;
	SplitCheckDlg m_dlgSplit;
	FunctionDlg m_dlgFunction;
	ManagerDlg m_dlgManager;
	ViewCheckDlg m_dlgViewCheck;
	OrderDlg m_dlgQOrder;

	dlg.AddPage(&m_dlgLogin);
	if (m_isCusFloor)
		dlg.AddPage(new FloorDlg);
	else
		dlg.AddPage(&m_dlgFloor);
	dlg.AddPage(&m_dlgOrder);
	dlg.AddPage(&m_dlgPay);
	dlg.AddPage(&m_dlgSplit);
	dlg.AddPage(&m_dlgFunction);
	dlg.AddPage(&m_dlgManager);
	dlg.AddPage(&m_dlgViewCheck);

	if(!theApp.m_bQuickService)
	{
		m_dlgQOrder.m_strTmplate=_T("Page\\IDD_3_QUICK_ORDER.ini");
		dlg.AddPage(&m_dlgQOrder);
	}

	//添加动态页面
	CFileFind finder;
	BOOL bWorking=finder.FindFile(_T(".\\PAGE\\DYN_*.ini"));
	while (bWorking)
	{
		bWorking   =   finder.FindNextFile();
		CString name=finder.GetFileTitle();
		int index=name.ReverseFind('_');
		CString strTemplate=name.Mid(index+1);
		CPosPage* pPage=NULL;
		if (strTemplate==_T("FLOOR"))
		{
			FloorDlg* pFloor=new FloorDlg;
			CString strPath;
			::GetPrivateProfileString(_T("POS"),name,_T(""),strPath.GetBuffer(40),40,_T(".\\config.ini"));
			strPath.ReleaseBuffer();
			pFloor->m_strBackground=strPath;
			pPage=pFloor;
		}
		else if (strTemplate==_T("MANAGER"))
		{
			pPage=new ManagerDlg;
		}
		else if (strTemplate==_T("LOGIN"))
		{
			pPage=new CLoginDlg;
		}
		else if (strTemplate==_T("PAY"))
		{
			pPage=new PayDlg;
		}
		else if (strTemplate==_T("FUNCTION"))
		{
			pPage=new FunctionDlg;
		}
		else
			continue;
		pPage->m_strTmplate=finder.GetFilePath();
		m_pageList.push_back(pPage);
		dlg.AddPage(pPage);
	}
	finder.Close();
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// 在此处放置处理何时用“确定”来关闭
		//  对话框的代码
	}
	else if (nResponse == IDCANCEL)
	{
		//在此放置处理何时用“取消”来关闭
		//  对话框的代码
	}
	// 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
	//  而不是启动应用程序的消息泵。
	return FALSE;
}

int CPOSClientApp::ExitInstance()
{
	try{
		for (std::vector<CPosPage*>::iterator iter = m_pageList.begin(); iter!= m_pageList.end();iter++)
		{
			CPosPage *b = (*iter);
			delete b;
		}
		m_pageList.clear();
		if(m_pRecentFileList)
			m_pRecentFileList->WriteList();
		if(m_cusDisplay.m_strPort.IsEmpty()==FALSE)
		{
			m_cusDisplay.Close();
		}
		if(m_VCR.m_strPort.IsEmpty()==FALSE)
			m_VCR.Close();
		Gdiplus::GdiplusShutdown(m_gdiplusToken);
		CefShutdown();
	}catch(...)
	{
	}
	return CWinApp::ExitInstance();
}

static RSA* pubKey=NULL;
static RSA* OpenPubKey(const char* fileName)
{
	RSA *rsaK;
	OpenSSL_add_all_algorithms();
	BIO *BP=BIO_new(BIO_s_file());;
	BIO_read_filename(BP,fileName); 
	rsaK=PEM_read_bio_RSAPublicKey(BP,NULL,NULL,NULL);
	return rsaK;
}

/************************************************************************
* 函数介绍：从数据库获取当前机器的DeviceID
* 输入参数：
* 输出参数：
* 返回值  ：0 成功 -1 异常 1-用户取消
************************************************************************/
int CPOSClientApp::GetDeviceID()
{
	USES_CONVERSION;
	try{
		CRecordset rs(&theDB);
		CString strSQL,strVal;
		char szName[256]; 
		if(gethostname(szName,256))
		{
			int err=WSAGetLastError();
		}
		m_strHostName=szName;
		hostent *pHost=gethostbyname(szName);
		if(   NULL   ==   pHost   )//   failed 
			return   FALSE;
		in_addr addr; 
		addr.s_addr   =**(DWORD**)(pHost-> h_addr_list);
		
		char* ch=inet_ntoa(addr);
		WCHAR ip[128]={0};
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED,ch,strlen(ch),ip,128);
		LOG4CPLUS_INFO(log_pos,_T("IP Address:")<<ip);
		m_strIP.Format(_T("%s"),ip);
#if defined(WEB_VERSION)
		HardwareInfo hard;
		m_strDiskId=hard.GetHDSerial();
		if(m_bTrainingMode)
			strSQL.Format(_T("SELECT * FROM user_workstations"));
		else
			strSQL.Format(_T("SELECT * FROM user_workstations WHERE opos_device_name=\'%s\'"),m_strDiskId);
		rs.Open( CRecordset::forwardOnly,strSQL);
		if (rs.GetRecordCount()==0)
		{//找不到，跳转到添加页面
			CAddPosDlg dlg;
			if(dlg.DoModal()==IDCANCEL)
			{
// 				if(dlg.m_nResult==1||dlg.m_nResult==2)
// 				{
// 					POSMessageBox(IDS_REGMAX);
// 				}
				return 1;
			}
			else
			{//重新下载数据
				splash.SetProgress( 70, IDS_CHECKREG);
				if(CLoginDlg::DoDownload(NULL)==0)
				{//下载成功,重新查询
					rs.Close();
					strSQL.Format(_T("SELECT * FROM user_workstations WHERE opos_device_name=\'%s\'"),m_strDiskId);
					rs.Open( CRecordset::forwardOnly,strSQL);
					if (rs.GetRecordCount()==0)
						return -1;
				}
				else
				{//下载失败
					return -1;
				}
			}
			//rs.Close();
		}
#else

		strSQL.Format(_T("SELECT * FROM user_workstations WHERE ip_address=\'%s\' OR pos_name=\'%s\';"),ip,m_strHostName);
		rs.Open( CRecordset::forwardOnly,strSQL);
		if (rs.GetRecordCount()==0)
		{
			rs.Close();
			strSQL.Format(_T("SELECT * FROM user_workstations;"));
			rs.Open( CRecordset::snapshot,strSQL);
			if (rs.GetRecordCount()==0)
			{
				POSMessageBox(IDS_DATABASENOIP);
				return 1;
			}
			int count=0;
			while(!rs.IsEOF())
			{//提示用户
				count++;
				rs.MoveNext();
			}
			rs.MoveFirst();
			if (count>=2)
			{
				POSMessageBox(IDS_DATABASENOIP);
			}
			
		}
#endif
		CDBVariant variant;
		rs.GetFieldValue(_T("workstations_id"),variant);
		m_nDeviceId=variant.m_iVal;
		rs.GetFieldValue(_T("pos_name"),strVal);
		m_strDeviceName.Format(_T("%s"),strVal);
		variant.m_boolVal=FALSE;
		if(!m_bQuickService)
		{
			rs.GetFieldValue(_T("is_quickservice"),variant);
			m_bQuickService=variant.m_boolVal;
		}
		rs.GetFieldValue(_T("revenue_center"),variant);
		m_nRVC=variant.m_iVal;
		rs.Close();
		//查询RVC name
		strSQL.Format(_T("select rvc_center_name from rvc_center where rvc_center_id = %d"),m_nRVC);
		if(rs.Open(-1,strSQL))
		{
			if(!rs.IsEOF())
			{
				rs.GetFieldValue(_T("rvc_center_name"),m_strRVC);
			}
		}
		rs.Close();
		if(m_bQuickService)
		{
			strSQL.Format(_T("select table_name from tables where table_id = -1"));
			rs.Open(-1,strSQL);
			if(!rs.IsEOF())
			{
				rs.GetFieldValue(_T("table_name"),strVal);
				m_strTblName.Format(_T("%s"),strVal);
			}
			rs.Close();
			
		}
		strSQL.Format(_T("select * from restaurant"));
		rs.Open(-1,strSQL);
		if(!rs.IsEOF())
		{
			variant.m_iVal=0;
			rs.GetFieldValue(_T("is_input_chk"),variant);
			m_bInputChkName=variant.m_iVal;
			variant.m_iVal=0;
			rs.GetFieldValue(_T("auto_send_type"),variant);
			m_nAutoSendType=variant.m_iVal;
			variant.m_iVal=0;
			rs.GetFieldValue(_T("type"),variant);
			m_nRoundType=variant.m_iVal;
			rs.GetFieldValue(_T("currency_name"),strVal);
			CURRENCY_SYMBOL.Format(_T("%s"),strVal);
			rs.GetFieldValue(_T("restaurant_name"),strVal);
			m_strResName.Format(_T("%s"),strVal);
			rs.GetFieldValue(_T("backup_server_node"),variant);
			m_nShiftType=variant.m_iVal;


			variant.m_iVal=1;
			rs.GetFieldValue(_T("decimal_places"),variant);
			DECIMAL_PLACES=variant.m_iVal;
			m_decPlace.Format(_T("%%.%df"),theApp.DECIMAL_PLACES);

			rs.GetFieldValue(_T("wechat_mchid"),strVal);
			m_wxSubMchid.Format(_T("%s"),strVal);
			rs.GetFieldValue(_T("ali_mchid"),strVal);
			m_aliStoreId.Format(_T("%s"),strVal);
			CStringA strA;
			rs.GetFieldValue(_T("ali_appid"),strA);
			m_aliAuthToken=strA;
		}
		rs.Close();
		
// 		if(!m_wxSubMchid.IsEmpty())
// 		{
// 			strSQL.Format(_T("SELECT COUNT(*) FROM tender_media WHERE halo=9"));
// 			rs.Open(-1,strSQL);
// 			rs.GetFieldValue((short)0,strVal);
// 			int count=_wtoi(strVal);
// 			if(count>0)
// 			{//加载收钱吧接口
// 				hSQBDll = ::LoadLibrary(_T("CashBarV2.dll"));
// 				if (hSQBDll)
// 				{
// 					pfunc activateUI=(pfunc)GetProcAddress(hSQBDll,"_activate@4");
// 					if (activateUI)
// 					{
// 						string cmd="20160301185100&0918b9c109a98beb52af5442eaae29f3&";
// 						cmd.append(W2A(m_wxSubMchid));
// 						string ret=(*activateUI)(cmd.c_str());
// 						LOG4CPLUS_INFO(log_pos,"Shouqianba activate "<<ret.c_str());
// 					}
// 				}
// 			}
// 		}
		return 0;
	}
	catch(CDBException* e)
	{
		LOG4CPLUS_ERROR(log_pos,(LPCTSTR)e->m_strError);
		e->Delete();
		return -1;
	}
	catch(...)
	{
		LOG4CPLUS_ERROR(log_pos,"Catch Exception GetLastError="<<GetLastError());
		return -1;
	}
}
/************************************************************************
* 函数介绍：初始化收银和预结单打印机
* 输入参数：
* 输出参数：
* 返回值  ：
************************************************************************/
BOOL CPOSClientApp::InitPrinter()
{
	try{
		CRecordset rs(&theDB);
		CString strSql;
		strSql.Format(_T("SELECT * FROM print_devices WHERE print_device_id=(SELECT customer_receipt_printer")
			_T(" FROM user_workstations WHERE workstations_id=%d);"),m_nDeviceId);
		rs.Open( CRecordset::forwardOnly,strSql);
		if(!rs.IsEOF())
		{
			CDBVariant  varVal;
			int printer_type=0;
			CString printerName;
			rs.GetFieldValue(_T("print_device_name"),printerName);
			rs.GetFieldValue(_T("check_info_print"),varVal);
			printer_type=varVal.m_iVal;
			m_payPrinter.nDeviceType=printer_type;
			varVal.m_iVal=0;
			rs.GetFieldValue(_T("paper_width"),varVal);
			m_payPrinter.nPaperWidth=varVal.m_iVal;
			if (printer_type==0)
			{//串口
				rs.GetFieldValue(_T("com_port"),varVal);
				printerName.Format(_T("COM%d"),varVal.m_iVal);
				rs.GetFieldValue(_T("baud_rate"),varVal);
				m_payPrinter.nComBaudrate=varVal.m_iVal;
				rs.GetFieldValue(_T("parity_type"),varVal);
				m_payPrinter.nComParity=varVal.m_iVal;
				rs.GetFieldValue(_T("num_data_bit"),varVal);
				m_payPrinter.nComDataBits=varVal.m_iVal;
				rs.GetFieldValue(_T("num_stop_bits"),varVal);
				m_payPrinter.nComStopBits=varVal.m_iVal;
				rs.GetFieldValue(_T("flow_control"),varVal);
				m_payPrinter.nFlowControl=varVal.m_iVal;
			}
			else if (printer_type==1)
			{//并口
				rs.GetFieldValue(_T("com_port"),varVal);
				printerName.Format(_T("LPT%d"),varVal.m_iVal);
			}
			else
			{
				rs.GetFieldValue(_T("printer_name"),printerName);
			}
			m_payPrinter.printerName=printerName;

			varVal.m_boolVal=FALSE;
			rs.GetFieldValue(_T("print_table_number"),varVal);
			m_payPrinter.bCutPaper = varVal.m_boolVal;
			rs.GetFieldValue(_T("header"),varVal);
			CRecordset rs1(&theDB);
			strSql.Format(_T("SELECT * FROM descriptors_headers WHERE descriptors_headers_id=%d;"),varVal.m_iVal);
			rs1.Open( CRecordset::forwardOnly,strSql);
			if (!rs1.IsEOF())
			{
				CString filed;
				int ncount=0;
				for (int i=1;i<=6;i++)
				{
					filed.Format(_T("line_%d"),i);
					CString line;
					rs1.GetFieldValue(filed,line);
					if (line.GetLength()==0)
						ncount++;
					else
					{
						for (;ncount>0;ncount--)
						{
							m_strPrintHead.Append(_T("\n"));
						}
						m_strPrintHead.AppendFormat(_T("%s\n"),line);
					}
				}
			}
			rs1.Close();

			rs.GetFieldValue(_T("trailer"),varVal);
			strSql.Format(_T("SELECT * FROM descriptors_trailers WHERE descriptors_trailers_id=%d;"),varVal.m_iVal);
			rs1.Open( CRecordset::forwardOnly,strSql);
			if (!rs1.IsEOF())
			{
				CString filed;
				int ncount=0;
				for (int i=1;i<=12;i++)
				{
					filed.Format(_T("line_%d"),i);
					CString line;
					rs1.GetFieldValue(filed,line);
					if (line.GetLength()==0)
						ncount++;
					else
					{
						for (;ncount>0;ncount--)
						{
							m_strPrintTail.Append(_T("\n"));
						}
						m_strPrintTail.AppendFormat(_T("%s\n"),line);
					}
				}
			}
			rs1.Close();
		}
		rs.Close();
		strSql.Format(_T("SELECT * FROM customer_display WHERE customer_display_id=(SELECT customer_display")
			_T(" FROM user_workstations WHERE workstations_id=%d);"),m_nDeviceId);
		rs.Open( CRecordset::forwardOnly,strSql);
		if(!rs.IsEOF())
		{
			int comport,baud_rate,parity_type,num_data_bit,num_stop_bits,type;
			CDBVariant    varVal;
			rs.GetFieldValue(_T("com_port"),varVal);
			comport = varVal.m_iVal;

			rs.GetFieldValue(_T("baud_rate"),varVal);
			baud_rate = varVal.m_iVal;

			rs.GetFieldValue(_T("parity_type"),varVal);
			parity_type = varVal.m_iVal;

			rs.GetFieldValue(_T("num_data_bit"),varVal);
			num_data_bit = varVal.m_iVal;

			rs.GetFieldValue(_T("num_stop_bits"),varVal);
			num_stop_bits = varVal.m_iVal;
			varVal.m_iVal=0;
			rs.GetFieldValue(_T("type"),varVal);
			type = varVal.m_iVal;

			CString portStr;
			portStr.Format(_T("COM%d"),comport);

			m_cusDisplay.SetOpenParam(type,portStr,baud_rate,num_data_bit,parity_type,num_stop_bits);
			//m_cusDisplay.Open();
		}
		rs.Close();
		//视频监控
		CString strPort;
		::GetPrivateProfileString(_T("POS"),_T("VCR_PORT"),_T(""),strPort.GetBuffer(40),40,_T(".\\config.ini"));
		strPort.ReleaseBuffer(); 
		if(!strPort.IsEmpty())
		{
			int baudRate=::GetPrivateProfileInt(_T("POS"),_T("VCR_RATE"),9600,_T(".\\config.ini"));
			m_VCR.SetOpenParam(0,strPort,baudRate,8,0,0);
			m_VCR.Open();
		}
		//预结单打印机
		strSql.Format(_T("SELECT * FROM print_devices WHERE print_device_id=(SELECT guest_check_printer")
			_T(" FROM user_workstations WHERE workstations_id=%d);"),m_nDeviceId);
		rs.Open( CRecordset::forwardOnly,strSql);
		if(!rs.IsEOF())
		{
			CDBVariant  varVal;
			int printer_type=0;
			//int baud_rate,parity_type,num_data_bit,num_stop_bits,flow_control;
			CString printerName;
			rs.GetFieldValue(_T("print_device_name"),printerName);
			rs.GetFieldValue(_T("check_info_print"),varVal);
			printer_type=varVal.m_iVal;
			m_prePrinter.nDeviceType=printer_type;
			varVal.m_iVal=0;
			rs.GetFieldValue(_T("paper_width"),varVal);
			m_prePrinter.nPaperWidth=varVal.m_iVal;
			if (printer_type==0)
			{//串口
				rs.GetFieldValue(_T("com_port"),varVal);
				printerName.Format(_T("COM%d"),varVal.m_iVal);
				rs.GetFieldValue(_T("baud_rate"),varVal);
				m_prePrinter.nComBaudrate=varVal.m_iVal;
				rs.GetFieldValue(_T("parity_type"),varVal);
				m_prePrinter.nComParity=varVal.m_iVal;
				rs.GetFieldValue(_T("num_data_bit"),varVal);
				m_prePrinter.nComDataBits=varVal.m_iVal;
				rs.GetFieldValue(_T("num_stop_bits"),varVal);
				m_prePrinter.nComStopBits=varVal.m_iVal;
				rs.GetFieldValue(_T("flow_control"),varVal);
				m_prePrinter.nFlowControl=varVal.m_iVal;
			}
			else if (printer_type==1)
			{//并口
				rs.GetFieldValue(_T("com_port"),varVal);
				printerName.Format(_T("LPT%d"),varVal.m_iVal);
			}
			else
			{
				rs.GetFieldValue(_T("printer_name"),printerName);
			}
			m_prePrinter.printerName=printerName;
			varVal.m_boolVal=FALSE;
			rs.GetFieldValue(_T("print_table_number"),varVal);
			m_prePrinter.bCutPaper = varVal.m_boolVal;
			CRecordset rs1(&theDB);
			if(m_strPrintHead.GetLength()==0)
			{
				rs.GetFieldValue(_T("header"),varVal);
				strSql.Format(_T("SELECT * FROM descriptors_headers WHERE descriptors_headers_id=%d;"),varVal.m_lVal);
				rs1.Open( CRecordset::forwardOnly,strSql);
				if (!rs1.IsEOF())
				{
					CString filed;
					int ncount=0;
					for (int i=1;i<=6;i++)
					{
						filed.Format(_T("line_%d"),i);
						CString line;
						rs1.GetFieldValue(filed,line);
						if (line.GetLength()==0)
							ncount++;
						else
						{
							for (;ncount>0;ncount--)
							{
								m_strPrintHead.Append(_T("\n"));
							}
							m_strPrintHead.AppendFormat(_T("%s\n"),line);
						}
					}
				}
				rs1.Close();
			}
			if(m_strPrintTail.GetLength()==0)
			{
				rs.GetFieldValue(_T("trailer"),varVal);
				strSql.Format(_T("SELECT * FROM descriptors_trailers WHERE descriptors_trailers_id=%d;"),varVal.m_lVal);
				rs1.Open( CRecordset::forwardOnly,strSql);
				if (!rs1.IsEOF())
				{
					CString filed;
					int ncount=0;
					for (int i=1;i<=12;i++)
					{
						filed.Format(_T("line_%d"),i);
						CString line;
						rs1.GetFieldValue(filed,line);
						if (line.GetLength()==0)
							ncount++;
						else
						{
							for (;ncount>0;ncount--)
							{
								m_strPrintTail.Append(_T("\n"));
							}
							m_strPrintTail.AppendFormat(_T("%s\n"),line);
						}
					}
				}
				rs1.Close();
			}
		}
		rs.Close();
		if(CMainSheet::m_iStaticsInfo&0x08)
		{//未配置显示税率则不生效！！
			strSql.Format(_T("SELECT * FROM tax_primary"));
			rs.Open( CRecordset::forwardOnly,strSql);
			if (!rs.IsEOF())
			{
				CString strVal;
				rs.GetFieldValue(_T("tax_name"),strVal);
				CCheckDlg::TAX_NAME.Format(_T("%s"),strVal);
				CDBVariant varaint;
				varaint.m_dblVal=0;
				rs.GetFieldValue(_T("amount"),varaint);
				m_dTaxRate=varaint.m_dblVal;
				varaint.m_iVal=0;
				rs.GetFieldValue(_T("tax_type"),varaint);
				m_nTaxType=varaint.m_iVal;
				if(m_nTaxType==1)
				{//菜品已含税，税率值重新计算
					m_dTaxRate=100-10000/(100+m_dTaxRate);
				}
				varaint.m_iVal=0;
				rs.GetFieldValue(_T("include_service"),varaint);
				m_bTaxGST=varaint.m_iVal;
				varaint.m_iVal=0;
				rs.GetFieldValue(_T("round"),varaint);
				m_nTaxRound=varaint.m_iVal;
			}
			rs.Close();
			//根据税率组分类
			strSql.Format(_T("SELECT tax_group_id,tax_group_name,SUM(amount) FROM tax_group LEFT JOIN tax ON tax.tax_group=tax_group.tax_group_id GROUP BY tax_group_id"));
			rs.Open( CRecordset::forwardOnly,strSql);
			while (!rs.IsEOF())
			{
				CDBVariant varaint;
				varaint.m_iVal=0;
				rs.GetFieldValue(_T("tax_group_id"),varaint);
				TaxItem* tax=new TaxItem;
				tax->total=0;
				tax->id=varaint.m_iVal;
				CString strVal;
				rs.GetFieldValue(_T("tax_group_name"),strVal);
				tax->name=strVal;
				rs.GetFieldValue(_T("SUM(amount)"),strVal);
				tax->rate=_wtof(strVal);
				if(m_nTaxType==1)
				{//菜品已含税，税率值重新计算
					tax->rate=100-10000/(100+tax->rate);
				}
				taxGroup[varaint.m_lVal]=tax;
				rs.MoveNext();
			}
			rs.Close();
		}
		
		return TRUE;
	}
	catch(CDBException* e)
	{
		LOG4CPLUS_ERROR(log_pos,(LPCTSTR)e->m_strError);
		e->Delete();
		return FALSE;
	}
	catch(...)
	{
		LOG4CPLUS_ERROR(log_pos,"Catch Exception GetLastError="<<GetLastError());
		return FALSE;
	}
}
void CPOSClientApp::ResetAutoIncrement()
{
	try{
		CRecordset rs(&theDB);
		CString strSql=_T("SELECT MAX(order_head_id)+1 FROM history_order_head;");
		rs.Open( CRecordset::forwardOnly,strSql);
		if(!rs.IsEOF())
		{
			CString id;
			rs.GetFieldValue((short)0,id);
			if (id.IsEmpty())
				id=_T("1");
			strSql.Format(_T("alter table order_head auto_increment = %s"),id);
			theDB.ExecuteSQL(strSql);
		}
		rs.Close();

		strSql=_T("SELECT MAX(order_detail_id)+1 FROM history_order_detail");
		rs.Open( CRecordset::forwardOnly,strSql);
		if(!rs.IsEOF())
		{
			CString id;
			rs.GetFieldValue((short)0,id);
			if (!id.IsEmpty())
			{//初始化时由服务器确定最大值
				strSql.Format(_T("alter table order_detail auto_increment = %s"),id);
				theDB.ExecuteSQL(strSql);
			}
		}
		rs.Close();
	}
	catch(CDBException* e)
	{
		LOG4CPLUS_ERROR(log_pos,(LPCTSTR)e->m_strError);
		e->Delete();
	}
	catch(...)
	{
		LOG4CPLUS_ERROR(log_pos,"Catch Exception GetLastError="<<GetLastError());
	}
}
/************************************************************************
* 函数介绍： 获取文件的版本信息
* 输入参数：
* 输出参数：
* 返回值  ：
************************************************************************/
CString CPOSClientApp::GetFileVersion(LPCTSTR cPath)
{
	DWORD dwHandle,InfoSize;
	CString strVersion;
	try{
		InfoSize = GetFileVersionInfoSize(cPath,&dwHandle); //将版本信息资源读入缓冲区
		if(InfoSize==0) return strVersion;
		TCHAR *InfoBuf = new TCHAR[InfoSize];
		GetFileVersionInfo(cPath,0,InfoSize,InfoBuf); //获得生成文件使用的代码页及文件版本
		unsigned int  cbTranslate = 0;
		struct LANGANDCODEPAGE {
			WORD wLanguage;
			WORD wCodePage;
		} *lpTranslate;
		VerQueryValue(InfoBuf, TEXT("\\VarFileInfo\\Translation"),(LPVOID*)&lpTranslate,&cbTranslate);
		// Read the file description for each language and code page.
		for( int i=0; i < (cbTranslate/sizeof(struct LANGANDCODEPAGE)); i++ )
		{
			TCHAR  SubBlock[200];
			wsprintf( SubBlock,
				TEXT("\\StringFileInfo\\%04x%04x\\FileVersion"),
				lpTranslate[i].wLanguage,
				lpTranslate[i].wCodePage);
			void *lpBuffer=NULL;
			unsigned int dwBytes=0;
			VerQueryValue(InfoBuf,
				SubBlock,
				&lpBuffer,
				&dwBytes);
			CString strTemp=(TCHAR *)lpBuffer;
			strVersion+=strTemp;
		}
		delete InfoBuf;
	}catch(...)
	{
	}
	return strVersion;
}
void CPOSClientApp::FormatPrintDevice(JSONVALUE& root,PrintDeviceInfo& printer)
{
	root[_T("printer_type")]=printer.nDeviceType;
	root[_T("paper_width")]=printer.nPaperWidth;
	root[_T("printer")]=printer.printerName;
	if (printer.nDeviceType==0)
	{
		root[_T("baud_rate")]=printer.nComBaudrate;
		root[_T("parity_type")]=printer.nComParity;
		root[_T("num_data_bit")]=printer.nComDataBits;
		root[_T("num_stop_bits")]=printer.nComStopBits;
		root[_T("flow_control")]=printer.nFlowControl;
	}
	if(printer.bCutPaper)
		root[_T("cut_paper")]=printer.bCutPaper;
}
/************************************************************************
* 函数介绍：按照模板直接打印
* 输入参数：
* 输出参数：
* 返回值  ：
************************************************************************/
BOOL CPOSClientApp::PrintJson(JSONVALUE& root)
{
	int sreailid=0;
	try{
		if(root.isMember(_T("serial")))
			sreailid=root[_T("serial")].asInt();
		if (m_bTrainingMode)
		{//培训模式下
			CString str;
			theLang.LoadString(str,IDS_TRAINMODE);
			root[_T("head")]=str;
		}
		CString prefix;
		SYSTEMTIME   st; 
		GetLocalTime(&st);
		prefix.Format(_T("%d_%02d%02d%d%d"),sreailid,st.wHour,st.wMinute,st.wSecond,st.wMilliseconds);
		int count=0;
		while(count<3)
		{//重试几次,以免冲突
			count++;
			CString file_name=thePrintDir;
			srand ((unsigned)time(NULL));
			file_name.AppendFormat(_T("%s_%d.pf"),prefix,rand());
			FILE* fp = _wfopen(file_name , L"w,ccs=UNICODE");
			if(fp!=NULL){
				std::wstring str;
				root.ToString(str);
				LPCTSTR pBuf=str.c_str();
				size_t strSize = wcslen(pBuf);
				fwrite(pBuf, sizeof(wchar_t), strSize, fp);
				fclose(fp);
				break;
			}
			else
			{//打开失败，多个进程下同一个单。
				prefix.AppendChar('-');
			}
		}
		//查找并启动打印进程
		if(::FindWindow(_T("CPrintServerDlg"),_T("AgilePrintServer"))==NULL)
		{
			STARTUPINFO si = { sizeof(STARTUPINFO) };
			si.cb = sizeof(si);
			si.dwFlags = STARTF_USESHOWWINDOW;
			si.wShowWindow = SW_HIDE;
			PROCESS_INFORMATION pi;
			CreateProcess(_T("PrintServer.exe"), NULL , NULL, NULL, FALSE, CREATE_NO_WINDOW , NULL, NULL, &si, &pi);
		}
		return TRUE;
	}catch(...)
	{
		LOG4CPLUS_ERROR(log_pos,"Catch Exception GetLastError="<<GetLastError());
	}
	return FALSE;
}

void CPOSClientApp::AddRecentString(CString str)
{
	m_pRecentFileList->Add(str);
}
void CPOSClientApp::ClearQuickOnce()
{
	theApp.m_bQuickService=FALSE;
	theApp.m_bQuickOnce=FALSE;
	theApp.m_nEatType=TYPE_DINE;
}
void CPOSClientApp::CriticalLogs(OPR_TYPES opr,CString detail)
{
	try{
	if (opr>10)
		opr=OPR_UNKNOW;
	detail.Replace('\'',' ');
	CString strSQL;
	strSQL.Format(_T("INSERT INTO critical_operations VALUES(NULL,%d,%d,%d,%s,\'%s\',now(),\'%s\',\'%s\')")
		,opr,theApp.m_nDeviceId,theApp.m_nOrderHeadid,theApp.m_strUserID,theApp.m_strUserName,OPR_TYPES_NAME[opr],detail);
	theDB.ExecuteSQL(strSQL);
	}catch(...)
	{
	}
}

void CPOSClientApp::OpenDrawer()
{
	//培训模式不能打开
	if (m_bTrainingMode)
		return;
	try
	{
		if(m_prePrinter.nDeviceType==0&&m_prePrinter.nPaperWidth==0)
		{//IBM串口钱箱
			CustomerDisplay cashDrawer;//客显
			cashDrawer.SetOpenParam(0,m_prePrinter.printerName,m_prePrinter.nComBaudrate,m_prePrinter.nComDataBits
				,m_prePrinter.nComParity,m_prePrinter.nComStopBits);
			cashDrawer.Open();
			cashDrawer.OpenDrawer2();
			cashDrawer.Close();
		}
		else if (m_prePrinter.nDeviceType==PRINTER_TYPE_COMP||m_prePrinter.nDeviceType==PRINTER_TYPE_WIN)
		{
			HANDLE     hPrinter;
			DOC_INFO_1 DocInfo;
			DWORD      dwBytesWritten;
			// Need a handle to the printer.
			if( ! OpenPrinter((LPWSTR)(LPCTSTR)m_prePrinter.printerName, &hPrinter, NULL ) )
				return;
			// Fill in the structure with info about this "document."
			DocInfo.pDocName = _T("OpenDrawer");
			DocInfo.pOutputFile = NULL;
			DocInfo.pDatatype = _T("RAW");
			// Inform the spooler the document is beginning.
			if(StartDocPrinter( hPrinter, 1, (LPBYTE)&DocInfo ) == 0)
			{
				ClosePrinter(hPrinter);
				return;
			}
			// Send the data to the printer.
			const byte command[5] = { BaseCodes::ESC, 'p','0',60,240};
			WritePrinter(hPrinter, (LPVOID)command, 5, &dwBytesWritten);
			EndDocPrinter( hPrinter );
			ClosePrinter( hPrinter );
		}
		else
		{
			ESCPrinter printer;
			printer.OpenPrinterDev(m_prePrinter.printerName,m_prePrinter.nDeviceType,
				m_prePrinter.nComBaudrate,m_prePrinter.nComDataBits
				,m_prePrinter.nComStopBits,m_prePrinter.nComParity);
			printer.OpenDrawer();
			printer.ClosePrinterDev();
		}
	}catch(...)
	{
		LOG4CPLUS_ERROR(log_pos,"OpenDrawer Failed!");
	}
}
BOOL CPOSClientApp::CheckInit()
{
	if(m_strPhone.IsEmpty())
	{//需要初始化下载数据
		CWebLoginDlg dlg;
		if(dlg.DoModal()==IDCANCEL)
			return FALSE;
		else if(dlg.m_bDemo==FALSE)
		{
			splash.SetProgress( 30, IDS_DOWNLOAD);
			if(CLoginDlg::DoDownload(NULL)==0)
			{//下载成功
				return TRUE;
			}
		}
	}
	return TRUE;
}
/************************************************************************
* 函数介绍：计算菜品总价
* 输入参数：
* 输出参数：
* 返回值  ：
************************************************************************/
void ComputeTotalPrice(OrderDetail* pOrder)
{
	double total=pOrder->quantity*pOrder->item_price;
	if (macrosInt[_T("ROUND_ITEM_TTLPRICE")]==1)
	{//需要四舍五入
		if (pOrder->quantity<0)
		{
			total=total*(-1);//改为正数
			total=int(total+0.5);
			total=total*(-1);
		}
		else
			total=int(total+0.5);
	}
	pOrder->total_price=total;
	//更新税率值
	ComputeTax(pOrder);
}
void ComputeTax(OrderDetail* pOrder)
{
	if((CMainSheet::m_iStaticsInfo&0x08)&&pOrder->item_id>0)//普通菜品
		//(theApp.m_bTaxGST&&pOrder->item_id==ITEM_ID_SERVICE)))//服务费在ComputeSubtotal时整个计算
	{
		pOrder->tax_amount=0;
		double toTax=pOrder->total_price+pOrder->discount_price;
		//如果价格0的菜品，税金直接为0
		if (abs(toTax)<0.001)
			return;
		if (pOrder->tax_group>0)
		{//查询税率组
			TaxItem* tax=taxGroup[pOrder->tax_group];
			if(tax)
				pOrder->tax_amount=toTax*tax->rate/100;
		}
		else
		{//使用全局税率
			pOrder->tax_amount=toTax*theApp.m_dTaxRate/100;
		}
	}
}

CString FormatDBStr(LPCTSTR str)
{
	CString str_to=str;
	str_to.Replace(_T("'"),_T("''"));
	str_to.Replace(_T("\\"),_T("\\\\"));
	return str_to;
}
CString GetMacAddress()
{
	CString strMAC=_T("00-00-00-00-00-00");
	PIP_ADAPTER_ADDRESSES pAddresses = NULL;  
	ULONG outBufLen = 0;  
	DWORD dwRetVal = 0;  

	GetAdaptersAddresses(AF_UNSPEC,0, NULL, pAddresses,&outBufLen);  

	pAddresses = (IP_ADAPTER_ADDRESSES*) malloc(outBufLen);  

	if ((dwRetVal = GetAdaptersAddresses(AF_INET,GAA_FLAG_SKIP_ANYCAST,NULL,pAddresses,&outBufLen)) == NO_ERROR)
	{
		while(pAddresses)
		{
			if(wcsstr(pAddresses->Description,_T("PCI"))>0//物理网卡
				||pAddresses->IfType==71)//无线网卡
			{
				strMAC.Format(_T("%.2X-%.2X-%.2X-%.2X-%.2X-%.2X"),   
					pAddresses->PhysicalAddress[0],pAddresses->PhysicalAddress[1],  
					pAddresses->PhysicalAddress[2],pAddresses->PhysicalAddress[3],  
					pAddresses->PhysicalAddress[4],pAddresses->PhysicalAddress[5]);
			}
			pAddresses = pAddresses->Next;
		}
	}
	free(pAddresses);
	return strMAC;
}