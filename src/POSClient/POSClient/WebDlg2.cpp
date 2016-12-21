// WebDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "POSClient.h"
#include "WebDlg2.h"


// CWebDlg 对话框

IMPLEMENT_DYNCREATE(CWebDlg2, CDialog)

CWebDlg2::CWebDlg2(CWnd* pParent /*=NULL*/)
: CDialog(CWebDlg2::IDD, pParent)
{
}

CWebDlg2::~CWebDlg2()
{
}

BOOL CWebDlg2::OnInitDialog()
{
	CDialog::OnInitDialog();
	CRect rtBody;
	GetWindowRect(&rtBody);
	ScreenToClient(rtBody);
	rtBody.top+=30;
	CefWindowInfo cefWindowInfo;
	cefWindowInfo.SetAsChild(GetSafeHwnd(), rtBody);
	CefBrowserSettings browserSetting;
	g_handler=new CCefBrowserEventHandler();
	CefString url=(LPCTSTR)m_strCurrentUrl;
	CefBrowserHost::CreateBrowser(cefWindowInfo, g_handler.get(),url , browserSetting, NULL);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

BEGIN_MESSAGE_MAP(CWebDlg2, CDialog)
	ON_WM_SIZE()
	ON_WM_CLOSE()
END_MESSAGE_MAP()



LRESULT CWebDlg2::OnOK(WPARAM wParam, LPARAM lParam)
{
	CDialog::OnOK();
	return 0;
}
void CWebDlg2::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	if (g_handler != NULL){  
		CefRefPtr<CefBrowser> browser = g_handler->GetBrowser();  
		if (browser){
			CefWindowHandle hwnd = browser->GetHost()->GetWindowHandle();
			::MoveWindow(hwnd, 0, 0, cx, cy, TRUE);
		}  
	}  
}

void CWebDlg2::OnClose()
{
	if (g_handler.get() && !g_handler->IsClosing()) {
		CefRefPtr<CefBrowser> browser = g_handler->GetBrowser();
		if (browser.get()) {
			// Notify the browser window that we would like to close it. This will result in a call to 
			// MyHandler::DoClose() if the JavaScript 'onbeforeunload' event handler allows it.
			browser->GetHost()->CloseBrowser(false);
			// Cancel the close.
			return;
		}
	}
	// Allow the close.
	CDialog::OnClose();
}
