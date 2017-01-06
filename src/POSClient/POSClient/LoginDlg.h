#pragma once
/*********************************************************************
*Copyright (c) 2011 Coolroid Co.Ltd.
*DESCRIPTION：
*		登陆界面。
*AUTHOR ：zhangyi
*HISTORY：
*		author time    version   desc

*********************************************************************/
#include "afxwin.h"

// CLoginDlg 对话框
typedef struct _LoginInfo{
	CString loginID;
	CString machineID;
}LoginInfo;
class CLoginDlg : public CPosPage
{
	DECLARE_DYNAMIC(CLoginDlg)
public:
	CLoginDlg(CWnd* pParent = NULL);
	virtual ~CLoginDlg();

// 对话框数据
	enum { IDD = IDD_LOGINDLG };
	CString m_strLoginID;
	CStatic m_hintCtrl;
	CStatic m_timeCtrl;
	CRect m_timeRect;
	CString m_strHint;
	BOOL m_bClock;
	HWND m_hTip;
	ProgressDlg *mProgDlg;//进度条窗口
protected:
	CFont mFont;
	BOOL m_bSwipe;//判断键盘输入或刷卡
	CRoundButton2* m_pSyncBtn;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()
public:
	int CheckForUpdate();
	void OnSetActive();
	void UpdateHintData();
	void Signin(int type=0);
	static int DoDownload(ProgressDlg* progress);
	int UpdateClock(CString strID);
	afx_msg void OnBnClickedOK();
	afx_msg void OnNumBnClicked(UINT uID);
	void OnSize(UINT nType, int cx, int cy);
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonClear();
	afx_msg void OnBnClickedButton00();
	afx_msg void OnBnClickedButtonClock();
	afx_msg void OnBnClickedButtonSign();
	afx_msg void OnBnClickedButtonChange();
	afx_msg void OnBnClickedButtonHelp();
	afx_msg void OnBnClickedButtonDot();
	afx_msg void OnBnClickedButtonShutDown();
	afx_msg void OnBnClickedButtonAbout();
	afx_msg void OnBnClickedButtonConfig();
	afx_msg void OnBnClickedButtonReport();
	afx_msg void OnBnClickedButtonTools();
	afx_msg void OnBnClickedBackup();
	afx_msg void OnBnClickedButtonTrainMode();
	afx_msg void OnBnClickedButtonInventory();
	afx_msg void OnBnClickedButtonWebsite();
	afx_msg void OnBnClickedButtonWebVip();
	afx_msg void OnBnClickedButtonRegister();
	afx_msg void OnBnClickedServerIpSetting();
	afx_msg void OnBnClickedParty();
	afx_msg void OnBnClickedTemplate();
	afx_msg void OnBnClickedLanguage();
	afx_msg void OnBnClickedeExit();
	afx_msg void OnBnClickedMinimize();
	afx_msg void OnBnClickedSync();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
