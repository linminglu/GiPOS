// AboutDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "POSClient.h"
#include "AboutDlg.h"


// CAboutDlg 对话框

IMPLEMENT_DYNAMIC(CAboutDlg, CDialog)

CAboutDlg::CAboutDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAboutDlg::IDD, pParent)
{

}

CAboutDlg::~CAboutDlg()
{
	::DeleteObject(m_bpBackgrd);
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_VersionCtrl);
	DDX_Control(pDX, IDC_STATIC_URL, m_url);
}


BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//ON_WM_ERASEBKGND()
	//ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CAboutDlg 消息处理程序

BOOL CAboutDlg::GetOsInfo(CString& szOsName)
{
    char szOsType[MAX_PATH];
    HKEY hKey;
    if (ERROR_SUCCESS==::RegOpenKeyEx(HKEY_LOCAL_MACHINE,_T("Software\\Microsoft\\Windows NT\\CurrentVersion"),NULL,KEY_READ,&hKey))
    {
        DWORD dwSize = 255;
        DWORD dwType = REG_SZ;
        if (ERROR_SUCCESS!=::RegQueryValueEx(hKey,_T("ProductName"),0,&dwType,(BYTE *)szOsType,&dwSize))
        {
            return FALSE;
        }
        ::RegCloseKey(hKey);
    }

    OSVERSIONINFO osVer;
    osVer.dwOSVersionInfoSize = sizeof (OSVERSIONINFO);
    if (!::GetVersionEx (&osVer)) 
    {
        return FALSE;
    }
    szOsName.Format(_T("%s Build %d"),szOsType,osVer.dwBuildNumber);
    return TRUE;
}
BOOL CAboutDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

//	m_bpBackgrd=LoadBitmap(AfxGetApp()->m_hInstance,MAKEINTRESOURCE(IDB_BITMAP_ABOUT));
	
#ifdef GICATER_VERSION
	m_url.SetURL(_T("http://www.gicater.com"));
#else
	m_url.SetURL(_T("http://www.coolroid.com"));
#endif
	CString strOS,strVersion,str2;
	GetOsInfo(strOS);
	GetDlgItem(IDC_STATIC1)->SetWindowText(strOS);
	strVersion=CPOSClientApp::GetFileVersion(_T("POSClient.exe"));
	if(!strVersion.IsEmpty())
	{
		theLang.LoadString(IDS_POSCSYS,str2);
		strOS.Format(_T("%s:%s\r\n"),str2,strVersion);
		m_VersionCtrl.SetSel(-1,-1);
		m_VersionCtrl.ReplaceSel(strOS);
	}
	strVersion=CPOSClientApp::GetFileVersion(_T("POSManager.exe"));
	if(!strVersion.IsEmpty())
	{
		theLang.LoadString(IDS_CONFIGSYS,str2);
		strOS.Format(_T("%s:%s\r\n"),str2,strVersion);
		m_VersionCtrl.SetSel(-1,-1);
		m_VersionCtrl.ReplaceSel(strOS);
	}
	strVersion=CPOSClientApp::GetFileVersion(_T("ReportManage.exe"));
	if(!strVersion.IsEmpty())
	{
		theLang.LoadString(IDS_REPORTSYS,str2);
		strOS.Format(_T("%s:%s\r\n"),str2,strVersion);
		m_VersionCtrl.SetSel(-1,-1);
		m_VersionCtrl.ReplaceSel(strOS);
	}
	strVersion=CPOSClientApp::GetFileVersion(_T("PartyManager.exe"));
	if(!strVersion.IsEmpty())
	{
		theLang.LoadString(str2,IDS_PARTYSYS);
		strOS.Format(_T("%s:%s\r\n"),str2,strVersion);
		m_VersionCtrl.SetSel(-1,-1);
		m_VersionCtrl.ReplaceSel(strOS);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

BOOL CAboutDlg::OnEraseBkgnd(CDC* pDC)
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
	pDC->BitBlt(0,0,rect.Width(),rect.Height(),&MemDc,0,0,SRCCOPY);
	MemDc.SelectObject(hOldBmp);
	return TRUE;
}

HBRUSH CAboutDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	int ctlId=pWnd->GetDlgCtrlID();
	if ( ctlId== IDC_STATIC||ctlId== IDC_STATIC1)
	{
		 pDC->SetTextColor(m_dTextColor);
		pDC->SetBkMode(TRANSPARENT);
		return (HBRUSH)::GetStockObject(NULL_BRUSH); //返回此画刷可以使静态文本透明
	}
	return hbr;
}
