#pragma once


// CWebLoginDlg 对话框

class CWebLoginDlg : public CDialog
{
	DECLARE_DYNAMIC(CWebLoginDlg)

public:
	CWebLoginDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CWebLoginDlg();

// 对话框数据
	enum { IDD = IDD_WEBLOGIN };
	CRoundButton2 m_btOK;
	CRoundButton2 m_btCancel;
	CRoundButton2 m_btDemo;
	BOOL m_bDemo;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
	afx_msg void OnBnClickedCancel2();
};
