#pragma once
#include "afxcmn.h"


// CServerIPDlg 对话框

class CServerIPDlg : public CDialog
{
	DECLARE_DYNAMIC(CServerIPDlg)

public:
	CServerIPDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CServerIPDlg();

// 对话框数据
	enum { IDD = IDD_SERVERIPSETTING };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	CIPAddressCtrl m_IPCtrl;
};
