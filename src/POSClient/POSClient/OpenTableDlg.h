#pragma once


// COpenTableDlg 对话框

class COpenTableDlg : public CDialog
{
	DECLARE_DYNAMIC(COpenTableDlg)

public:
	COpenTableDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~COpenTableDlg();

// 对话框数据
	enum { IDD = IDD_OPENTABLE };
	HBITMAP m_bpBackgrd;
	CreatButton m_btnCtrl;
	int m_x;
	int m_y;
	CString m_strTmplate;

	HWND   hOld;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	//afx_msg void OnBnClickedOK();
	//afx_msg void OnBnClickedCancel();
	afx_msg void OnNumBnClicked(UINT uID);
	afx_msg void OnBnClickedButtonClear();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void OnOK();
	CString m_strGst;
	CString m_strRemark;
};
