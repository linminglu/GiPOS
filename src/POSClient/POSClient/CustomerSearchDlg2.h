#pragma once
#include "afxwin.h"


// CustomerSearchDlg2 对话框

class CustomerSearchDlg2 : public CDialog
{
	DECLARE_DYNAMIC(CustomerSearchDlg2)

public:
	CustomerSearchDlg2(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CustomerSearchDlg2();

	CRoundButton2 m_btOK;
	CRoundButton2 m_btCancel;
	CRoundButton2 m_addButton;
	CRoundButton2 m_editButton;
	CRoundButton2 m_softButton;
	CEdit m_edit;
	CListCtrl m_list;
// 对话框数据
	enum { IDD = IDD_CUSTSEARCH2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	afx_msg void OnEnChangeEdit1();
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	void Search(CString strSearch);
	afx_msg void OnBnClickedOk();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedButtonEdit();
public:
	afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);
	CString m_strResult;
	CString m_strPhone;
	BOOL m_bIgnore;
	afx_msg void OnBnClickedButtonLocation();
protected:
	virtual void OnOK();
public:
	afx_msg void OnBnClickedButtonSoftkey();
	afx_msg void OnPaint();
	afx_msg void OnBnClickedCancel();
};
