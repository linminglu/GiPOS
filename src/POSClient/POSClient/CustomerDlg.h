#pragma once
#include "afxwin.h"


// CCustomerDlg 对话框

class CCustomerDlg : public CDialog
{
	DECLARE_DYNAMIC(CCustomerDlg)

public:
	CCustomerDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCustomerDlg();

// 对话框数据
	enum { IDD = IDD_CUSTOMER };
	CRoundButton2 m_btOK;
	CRoundButton2 m_btCancel;
	CStatic mEdit_card;
	CStatic mEdit_name;
	CStatic mEdit_phone;
	CStatic mEdit_amount;
	CStatic mEdit_state;
	CStatic mEdit_level;
	CStatic mEdit_score;
	CEdit mEdit_pay;
	CEdit mEdit_psw;
	CEdit mEdit_point;
	CButton mButtonPrint;
protected:

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	double m_dConsume;//消费金额
	double toDisc;
	CString m_strCradId;
	CString m_strName;
	CString m_strPhone;
	double m_dBalance;
	double m_dOripay;
	double m_dDiscount;//折扣金额
	double m_dDiscName;
	int m_iScore;
	long m_nConsume_id;
	CString server;
	int port;
	BOOL m_bPrint;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	void UpdateMemeberInfo();
	afx_msg void OnPaint();
};
