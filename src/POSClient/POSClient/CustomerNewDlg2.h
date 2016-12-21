#pragma once


// CustomerNewDlg2 对话框

class CustomerNewDlg2 : public CDialog
{
	DECLARE_DYNAMIC(CustomerNewDlg2)

public:
	CustomerNewDlg2(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CustomerNewDlg2();

// 对话框数据
	enum { IDD = IDD_CUSTNEW2 };
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	long m_cusID;
	CRoundButton2 m_btOK;
	CRoundButton2 m_btCancel;
	CEdit mEditPhone;
	CEdit mEditName;
	CEdit mEditAddress;
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedOk();
	afx_msg void OnPaint();
};
