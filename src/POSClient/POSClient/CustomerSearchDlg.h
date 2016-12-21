#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CustomerSearchDlg 对话框

class CustomerSearchDlg : public CDialog
{
	DECLARE_DYNAMIC(CustomerSearchDlg)

public:
	CustomerSearchDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CustomerSearchDlg();

	CRoundButton2 m_btOK;
	CRoundButton2 m_btCancel;
	CRoundButton2 m_readButton;
	CRoundButton2 m_clearButton;
	CRoundButton2 m_softButton;
	CStatic m_hint;
	CEdit m_edit;
	CListCtrl m_list;
// 对话框数据
	enum { IDD = IDD_CUSTSEARCH };
	CString m_strCardId;
	CString m_strName;
	CString server;
	int port;
	Gdiplus::Image* m_bpButtonItem[2];

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()
	BOOL m_bAutoOK;
public:
	afx_msg void OnBnClickedButtonSoftkey();
	afx_msg void OnEnChangeEdit1();
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	void DoSearch();
	afx_msg void OnBnClickedButtonClear();
	afx_msg void OnBnClickedOk();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButtonRead();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnHdnItemdblclickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnPaint();
};
