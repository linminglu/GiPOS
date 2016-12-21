#pragma once
#include "afxwin.h"


// ClockDlg 对话框

class ClockDlg : public CDialog
{
	DECLARE_DYNAMIC(ClockDlg)

public:
	ClockDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~ClockDlg();

// 对话框数据
	enum { IDD = IDD_CLOCK };
	HBITMAP m_bpBackgrd;
	int m_x;
	int m_y;
	CString m_strUserID;
	CString m_strUserName;
	CRoundButton2 m_btClockin;
	CRoundButton2 m_btClockout;
	CRoundButton2 m_btCancel;
	int m_clockid;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	
	afx_msg void OnBnClickedClockin();
	afx_msg void OnBnClickedClockout();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	
	CEdit m_edit;
	CStatic m_timeCtrl;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
