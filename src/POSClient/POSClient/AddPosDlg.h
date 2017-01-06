#pragma once


// CAddPosDlg 对话框

class CAddPosDlg : public CDialog
{
	DECLARE_DYNAMIC(CAddPosDlg)

public:
	CAddPosDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CAddPosDlg();

// 对话框数据
	enum { IDD = IDD_ADDPOS };
	CRoundButton2 m_btOK;
	CRoundButton2 m_btCancel;
	int m_nOS;
	int m_nSys;
	int m_nResult;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
};
