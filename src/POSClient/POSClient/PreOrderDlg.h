#pragma once
#include "afxwin.h"


// PreOrderDlg 对话框

class PreOrderDlg : public CDialog
{
	DECLARE_DYNAMIC(PreOrderDlg)

public:
	PreOrderDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~PreOrderDlg();
	CRecordset* rs;
	int m_nGuestNum;
	int m_nPreorderId;
// 对话框数据
	enum { IDD = IDD_PREORDER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonArrive();
	afx_msg void OnBnClickedButtonCancleorder();
	afx_msg void OnBnClickedButtonIgnore();
	virtual BOOL OnInitDialog();
	CEdit m_ctrlGuestNum;
	CRoundButton2 m_btArrive;
	CRoundButton2 m_btCancel;
	CRoundButton2 m_btIgnore;
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
