// ServerIpSettingDlg.h : 头文件
//

#pragma once
#include "afxwin.h"


// CServerIpSettingDlg 对话框
class CServerIpSettingDlg : public CDialog
{
// 构造
public:
	CServerIpSettingDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_SERVERIPSETTING_DIALOG };
	CString m_strServer;

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CIPAddressCtrl m_IPCtrl;
	afx_msg void OnBnClickedButton1();
	CButton m_radio1;
	CButton m_radio2;
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
};
