#pragma once

#ifdef _WIN32_WCE
#error "Windows CE 不支持 CDHtmlDialog。"
#endif 
#include "WebDlgInterface.h"
// CWebDlg 对话框

class CWebDlg : public CDHtmlDialog,public CWebDlgInterface
{
	DECLARE_DYNCREATE(CWebDlg)

public:
	CWebDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CWebDlg();
// 重写
	HRESULT OnButtonOK(IHTMLElement *pElement);
	void PaySuccess(LPCTSTR str);
// 对话框数据
	enum { IDD = IDD_WEBDLG, IDH = 0 };
	

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	virtual BOOL IsExternalDispatchSafe(){ return TRUE;}
	

	DECLARE_MESSAGE_MAP()
	DECLARE_DHTML_EVENT_MAP()
	DECLARE_DISPATCH_MAP()
	virtual void OnOK();
};
