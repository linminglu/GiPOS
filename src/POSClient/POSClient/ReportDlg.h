#pragma once
#include "afxwin.h"
#include "afxdtctl.h"


// CReportDlg 对话框

class CReportDlg : public CDialog
{
	DECLARE_DYNAMIC(CReportDlg)

public:
	CReportDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CReportDlg();
	CString m_strTitle;
	CString m_strQuerry;
	CString m_strResult;
	CString m_strStartDate;
	CString m_strEndDate;
	int m_iType;
	CTime m_eodTime;
	BOOL m_bShortFormat;

// 对话框数据
	enum { IDD = IDD_REPORT };
	CRoundButton2 m_freshButton;
	CRoundButton2 m_printButton;
	CRoundButton2 m_closeButton;
	CRoundButton2 m_btCurday;
	CRoundButton2 m_btYesday;
	CRoundButton2 m_btCurmonth;
	CRoundButton2 m_btLastmonth;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	
	DECLARE_MESSAGE_MAP()
public:

	void ShowReport();
	void ShowReport1(BOOL bSms=FALSE);
	void ShowReport2();
	void ShowReport3();
	static int GetPrintLength(LPCTSTR str);
	static CString FormatString(LPCTSTR str,int len,BOOL bCompact=FALSE);
	static CString FormatString(double str,int len);
	static CString FormatString(int d,int len);
	afx_msg void OnBnClickedRefresh();
	afx_msg void OnBnClickedBtprint();
	virtual BOOL OnInitDialog();
	CEdit m_edit;
	CDateTimeCtrl m_fromDate;
	CDateTimeCtrl m_toDate;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedCurday();
	afx_msg void OnBnClickedLastday();
	afx_msg void OnBnClickedCurmonth();
	afx_msg void OnBnClickedLastmonth();
	afx_msg void OnPaint();
};
