#pragma once
#include "afxwin.h"


// MSGBoxDlg 对话框

class MSGBoxDlg : public CDialog
{
	DECLARE_DYNAMIC(MSGBoxDlg)

public:
	MSGBoxDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~MSGBoxDlg();

// 对话框数据
	enum { IDD = IDD_MSGBOX };
	CString m_strText;
	CString m_strYes;
	CString m_strNo;
	int m_nType;
	HBITMAP m_bpBackgrd;
	int m_x;
	int m_y;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CRoundButton2 m_btOK;
	CRoundButton2 m_btCancel;
	CStatic m_hintCtrl;
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};
