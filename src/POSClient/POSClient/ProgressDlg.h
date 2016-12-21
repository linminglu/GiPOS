#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// ProgressDlg 对话框

class ProgressDlg : public CDialog
{
	DECLARE_DYNAMIC(ProgressDlg)

public:
	ProgressDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~ProgressDlg();

// 对话框数据
	enum { IDD = IDD_PROGRESS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CProgressCtrl mProgress;
	int m_nStep;//进度条每秒前进百分比
	void Start();
	void Stop();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual BOOL OnInitDialog();
	void Reset();
	void Step(int nPos,CString msg);
	CStatic mCtrlHint;
};
