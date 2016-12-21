#pragma once
#include "afxwin.h"
#include "xhyperlink.h"

// CAboutDlg 对话框

class CAboutDlg : public CDialog
{
	DECLARE_DYNAMIC(CAboutDlg)

public:
	CAboutDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CAboutDlg();
	BOOL GetOsInfo(CString& szOsName);

// 对话框数据
	enum { IDD = IDD_ABOUT };
	HBITMAP m_bpBackgrd;
	CEdit m_VersionCtrl;
	CXHyperLink m_url;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CRoundButton2 m_btOK;
};
