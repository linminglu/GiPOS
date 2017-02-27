// MainSheet.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "POSClient.h"
#include "MainSheet.h"
#include "OrderPage.h"
#include "ReserveAddDlg.h"


// CMainSheet �Ի���

IMPLEMENT_DYNAMIC(CMainSheet, CDialog)

int CMainSheet::m_iFullScreen;
int CMainSheet::m_iStaticsInfo;

CMainSheet::CMainSheet(CWnd* pParent /*=NULL*/)
	: CDialog(CMainSheet::IDD, pParent)
{
	m_nCurrentPage=0;
}

CMainSheet::~CMainSheet()
{
}

void CMainSheet::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMainSheet, CDialog)
	//ON_MESSAGE(PRINT_LIST_FULL, OnPrintListFull)
	ON_MESSAGE(WM_MESSAGE_SEARCH,OnMsgSearch)
	ON_MESSAGE(WM_MESSAGE_UPDATE,OnMsgUpdate)
	ON_MESSAGE(WM_SETTEXT, OnVipCall)
	ON_MESSAGE(WM_MESSAGE_SHOWNOTIFY,OnMsgShowNotify)
	ON_WM_NCCALCSIZE()
	ON_WM_CLOSE()
	ON_WM_ACTIVATE()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CMainSheet ��Ϣ�������

/************************************************************************
* �������ܣ����ҳ�档��ҳ������б�
* ���������pPage	-Ҫ��ӵ�ҳ��
* ���������
* ����ֵ  ��
************************************************************************/
void CMainSheet::AddPage(CPosPage* pPage)
{
	if (pPage==NULL)
		return;
	m_pages.Add(pPage);
}
/************************************************************************
* �������ܣ����б��л�ȡҳ��
* ���������nPage	-ҳ�������
* ���������
* ����ֵ  ��ҳ��ָ��
************************************************************************/
CPosPage* CMainSheet::GetPage(int nPage) const
{
	if(m_pages.GetCount()<=nPage)
		return NULL;
	CPosPage* pPage=((CPosPage*)m_pages[nPage]);
	return pPage;
}
/************************************************************************
* �������ܣ����ûҳ��
* ���������nPage	-��ת��ҳ������� 
*			bPre -����ǰҳʱ��Ҫ�޸���תҳ���m_nPrePage
* ���������
* ����ֵ  ����������ҳ��ʱ����false
************************************************************************/
BOOL  CMainSheet::SetActivePage(int nPage,BOOL bPre)
{
	try
	{
		if(m_pages.GetCount()<=nPage)
			return FALSE;
		CPosPage* pCurPage=((CPosPage*)m_pages[m_nCurrentPage]);
		if (!IsWindow(pCurPage->GetSafeHwnd()))
		{
			pCurPage->Create(pCurPage->m_nID,this);
			CRect rect2;
			this->GetClientRect(&rect2);
			pCurPage->MoveWindow(rect2);
		}
		CPosPage* pPage=((CPosPage*)m_pages[nPage]);
		if (!IsWindow(pPage->GetSafeHwnd()))
		{
			pPage->Create(pPage->m_nID,this);
			CRect rect2;
			this->GetClientRect(&rect2);
			pPage->MoveWindow(rect2);
		}
		if(bPre==FALSE&&m_nCurrentPage!=nPage)
			pPage->m_nPrePage=m_nCurrentPage;
		m_nCurrentPage=nPage;
		pCurPage->ShowWindow(SW_HIDE);
		pPage->ShowWindow(SW_SHOW);
		//::SetWindowPos(pPage->m_hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		
		LOG4CPLUS_INFO(log_pos,"SetActivePage to ["<<pPage->GetRuntimeClass()->m_lpszClassName<<"]");
		pPage->OnSetActive();
		pPage->SetFocus();
		return TRUE;
	}
	catch(...)
	{
		LOG4CPLUS_ERROR(log_pos,"Catch Exception GetLastError="<<GetLastError());
		return FALSE;
	}
}
/************************************************************************
* �������ܣ���ȡ��ǰ�ҳ�������
* ���������
* ���������
* ����ֵ  ��
************************************************************************/
int CMainSheet::GetActiveIndex() const
{
	return m_nCurrentPage;
}
/************************************************************************
* �������ܣ���ȡ��ǰ�ҳ��
* ���������
* ���������
* ����ֵ  ��
************************************************************************/
CPosPage* CMainSheet::GetActivePage() const
{
	return (CPosPage*)m_pages[m_nCurrentPage];
}

BOOL CMainSheet::OnInitDialog()
{
	CDialog::OnInitDialog();
	CString title;
	//���ñ���
// #ifdef FREE_VERSION
// 	title=_T("Gicater");
// #else
// 	title=_T("POS");
// #endif
// 	SetWindowText(title);
	HICON m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	SetIcon(m_hIcon,TRUE);
	SetIcon(m_hIcon,FALSE);
	//����ȫ��
	m_iFullScreen=::GetPrivateProfileInt(_T("POS"),_T("FULLSCREEN"),1,_T(".\\config.ini"));
	if(m_iFullScreen==1)
	{
		LONG style = ::GetWindowLong(this->m_hWnd,GWL_STYLE);
		style &= ~(WS_DLGFRAME | WS_THICKFRAME);
		SetWindowLong(this->m_hWnd,GWL_STYLE, style);
		::SetWindowPos(this->m_hWnd, HWND_TOPMOST, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), SWP_FRAMECHANGED);
		this->ShowWindow(SW_SHOWMAXIMIZED);
	}
	else
	{
		::SetWindowPos(this->m_hWnd,HWND_NOTOPMOST,0, 0, CreatButton::m_nFullWidth, CreatButton::m_nFullHeight+20, SWP_SHOWWINDOW );
	}
	//�����ӶԻ���
	CreateAllPages();
	SetActivePage(0);
	//������������
	if (pSplash)
	{
		pSplash->Hide();
		pSplash=NULL;
	}
	//SetTimer(1000,6000,NULL);//ÿ��60��ˢ��
	return TRUE;
}
/************************************************************************
* �������ܣ�Ԥ�ȴ���������ҳ�棬����ʹ��ʱ��ȡ�����ļ������ӳ�
* ���������
* ���������
* ����ֵ  ��
************************************************************************/
void CMainSheet::CreateAllPages()
{
	try
	{
		for (int i=0;i<m_pages.GetCount();i++)
		{
			CPosPage* pPage=(CPosPage*)m_pages[i];
			if (!IsWindow(pPage->GetSafeHwnd()))
			{
				pPage->Create(pPage->m_nID,this);
				pPage->MoveWindow(0,0,CreatButton::m_nFullWidth,CreatButton::m_nFullHeight);
				pPage->CenterWindow();
			}
		}
	}catch(...)
	{
		LOG4CPLUS_ERROR(log_pos,"Catch Exception in CMainSheet::CreateAllPages");
	}
}
/************************************************************************
* �������ܣ���ʾ��ʱ��ӵ�ҳ��
* ���������
* ���������
* ����ֵ  ��
************************************************************************/
void CMainSheet::ShowCurrentPage(int nCmd)
{
	try{
		CPosPage* pCurPage=((CPosPage*)m_pages[m_nCurrentPage]);
		pCurPage->ShowWindow(nCmd);
		pCurPage->SetFocus();
	}
	catch(...)
	{
		LOG4CPLUS_ERROR(log_pos,"Catch Exception GetLastError="<<GetLastError());
	}
}
 LRESULT CMainSheet::OnPrintListFull(WPARAM wParam, LPARAM lParam)
 {
	 //POSMessageBox(_T("��ӡ������������鿴��ӡ���Ƿ���������"));
	 return 0;
 }
 LRESULT CMainSheet::OnMsgSearch(WPARAM wParam, LPARAM lParam)
 {
	 if (m_nCurrentPage==DLG_ORDER)
	 {
		 ::SendMessage(((CPosPage*)m_pages[m_nCurrentPage])->GetSafeHwnd(),WM_MESSAGE_SEARCH,wParam,lParam);
	 }
	 return 0;
 }
 LRESULT CMainSheet::OnMsgUpdate(WPARAM wParam, LPARAM lParam)
 {
	 if (m_nCurrentPage==DLG_FLOOR)
	 {
		 ::SendMessage(((CPosPage*)m_pages[m_nCurrentPage])->GetSafeHwnd(),WM_MESSAGE_UPDATE,wParam,lParam);
	 }
	 return 0;
 }
 LRESULT CMainSheet::OnMsgShowNotify(WPARAM wParam, LPARAM lParam)
 {
	 static bool bFirst=true;
	 if(bFirst)
	 {
		 m_tnd.cbSize=sizeof(NOTIFYICONDATA);
		 m_tnd.hWnd = this->m_hWnd;
		 m_tnd.uFlags = NIF_INFO;
		 m_tnd.uVersion = NOTIFYICON_VERSION;
		 m_tnd.uTimeout = 10000;
		 m_tnd.dwInfoFlags =NIF_ICON|NIF_MESSAGE|NIF_TIP ; 
		 m_tnd.hIcon=LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDR_MAINFRAME));
		 wcscpy_s( m_tnd.szInfoTitle, _T("Error") );
		 wcscpy_s( m_tnd.szInfo, (LPCTSTR)wParam);
		 Shell_NotifyIcon( NIM_ADD,&m_tnd);
		 bFirst=false;
	 }
	 else
	 {
		 wcscpy_s( m_tnd.szInfoTitle, _T("Error") );
		 wcscpy_s( m_tnd.szInfo, (LPCTSTR)wParam);
		 Shell_NotifyIcon( NIM_MODIFY,&m_tnd);
	 }
	
	 return 0;
 }
 LRESULT CMainSheet::OnVipCall(WPARAM wParam, LPARAM lParam)
 {
	 try{
		 JSONVALUE root;
		 if(root.Parse((LPCTSTR)lParam,JSON_FLAG_LOOSE))
		 {
			 //����֮ǰ�ĵ�
			 if (theApp.m_bQuickService)
			 {
				 ::SendMessage(((CPosPage*)m_pages[m_nCurrentPage])->GetSafeHwnd(),WM_COMMAND,MAKEWPARAM(IDC_BUTTON_PENDING,BN_CLICKED),0);
			 }
			 COrderPage::m_strCardID=root[_T("card_id")].asCString();
			 CString uname=root[_T("uname")].asCString();
			 CString phone=root[_T("phone")].asCString();
			 CString address=root[_T("address")].asCString();
			 if(wParam==1)
			 {//Ԥ��
				 HWND topWnd=((CPosPage*)m_pages[m_nCurrentPage])->GetSafeHwnd();
				 if(::IsWindowVisible(topWnd)==FALSE)
				 {//���������棬������Ϣ
					 return 0;
				 }
				 ReserveAddDlg* pDlg=new ReserveAddDlg();
				 pDlg->m_hParent=(CPosPage*)m_pages[m_nCurrentPage];
				 pDlg->m_strUname=uname;
				 pDlg->m_strPhone=phone;
				 pDlg->Create(IDD_RESERVEADD,theApp.m_pMain);
				 pDlg->ShowWindow(SW_SHOW);
				 pDlg->SetFocus();
			 }
			 else
			 {//�µ�
				 COrderPage::m_strTAInfo.Format(_T("%s,%s\r\n%s"),uname,phone,address);
				 COrderPage::bNewTainfo=TRUE;
				 HWND topWnd=((CPosPage*)m_pages[m_nCurrentPage])->GetSafeHwnd();
				 if(::IsWindowVisible(topWnd))
				 {
					 ::PostMessage(topWnd,WM_COMMAND,MAKEWPARAM(IDC_BUTTON_TAINFO,BN_CLICKED),0);
					 SetWindowPos(&this->wndTopMost, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
				 }
				 
			 }
		 }
	 }catch(...)
	 {
	 }
	 return 0;
 }
 void CMainSheet::OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp)
 {
	//lpncsp->rgrc[0].top+=20-GetSystemMetrics(SM_CYCAPTION);
	 CDialog::OnNcCalcSize(bCalcValidRects, lpncsp);
 }

 void CMainSheet::OnClose()
 {
	 if(POSMessageBox(IDS_CONFIRMQUIT,MB_YESNO)==IDOK)
	 {
		CDialog::OnClose();
		//TODO
		//ExitProcess(0);
	 }
 }

 void CMainSheet::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
 {
	 CDialog::OnActivate(nState, pWndOther, bMinimized);
	 CPosPage* pPage=GetActivePage();
	 if(pPage!=NULL&&pPage->m_hWnd!=NULL)
		 pPage->SetFocus();
 }
 /************************************************************************
 * �������ܣ���ʱ������û��Ƿ��в���
 * ���������
 * ���������
 * ����ֵ  ��
 ************************************************************************/
 void CMainSheet::OnTimer(UINT_PTR nIDEvent)
 {
	 if (nIDEvent==1000)
	 {
// 		 TRACE("OnTimer %d\n",m_nCurrentPage);
// 		 if(m_nCurrentPage==DLG_LOGIN)
// 			 return;
// 		 CWnd* topWnd=((CPosPage*)m_pages[m_nCurrentPage])->GetActiveWindow();
// 		 if(topWnd==NULL||topWnd==this)
// 		 {
// 			 TRACE("No other window!\n");
// 			if(((CPosPage*)m_pages[m_nCurrentPage])->LockScreen())
// 				SetActivePage(DLG_LOGIN);
// 		 }
	 }
	 CDialog::OnTimer(nIDEvent);
 }