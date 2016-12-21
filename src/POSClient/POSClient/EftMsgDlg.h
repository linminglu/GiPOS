#pragma once
#include "csdeft.h"
// CEftMsgDlg 对话框

class CEftMsgDlg : public CDialog
{
	DECLARE_DYNAMIC(CEftMsgDlg)

public:
	CEftMsgDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CEftMsgDlg();

// 对话框数据
	enum { IDD = IDD_EFTMSG };
	CCsdEft m_CsdEft;
	double fPayed;
	afx_msg void OnTransactionEventCsdeft();
	virtual BOOL OnInitDialog();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	DECLARE_EVENTSINK_MAP()
};
