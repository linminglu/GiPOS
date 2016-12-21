#pragma once
#include "cefclient/CefBrowserEventHandler.h"
// CWebDlg2 对话框
class CWebDlg2 : public CDialog
{
	DECLARE_DYNCREATE(CWebDlg2)

public:
	CWebDlg2(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CWebDlg2();

// 对话框数据
	enum { IDD = IDD_WEBDLG};
	CefRefPtr<CCefBrowserEventHandler> g_handler;
	CString m_strCurrentUrl;
	LRESULT OnOK(WPARAM wParam, LPARAM lParam);
protected:
	virtual BOOL OnInitDialog();
	
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnClose();
};
