#pragma once
#include "afxwin.h"


// ManagerDlg 对话框

class ManagerDlg : public CPosPage
{
	DECLARE_DYNAMIC(ManagerDlg)

public:
	ManagerDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~ManagerDlg();
	void OnSetActive();
	void GetReportString(CString& m_strResult);
	CTime GetEndDay();
	void DoEndofDay();
	void InsertDayend(LPCTSTR strStart,LPCTSTR strEnd, LPCTSTR strDay);
	void SendDepotData();
// 对话框数据
	enum { IDD = IDD_MANAGER };

	CTime m_eodTime;
	CString m_strResName;
	ProgressDlg *mProgDlg;//进度条窗口

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

	//afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedPrepage();
	afx_msg void OnBnClickedButtonCancel();
	afx_msg void OnBnClickedMinimize();
	afx_msg void OnBnClickedOpenDrawer();
	afx_msg void OnBnClickedReport1();
	afx_msg void OnBnClickedReport2();
	afx_msg void OnBnClickedReport3();
	afx_msg void OnBnClickedReport4();
	afx_msg void OnBnClickedCashReport();
	afx_msg void OnBnClickedShift();
	afx_msg void OnBnClickedDayend();
	afx_msg void OnBnClickedAbortPay();
	afx_msg void OnBnClickedEditPrice();
	afx_msg void OnBnClickedBackup();
	afx_msg void OnBnClickedCashIn();
	afx_msg void OnBnClickedCashOut();
	afx_msg void RunExternal();
	afx_msg void OnBnClickedDispalySet();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
