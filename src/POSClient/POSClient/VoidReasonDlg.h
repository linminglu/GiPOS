#pragma once
#include "afxwin.h"


// CVoidReasonDlg 对话框

class CVoidReasonDlg : public CDialog
{
	DECLARE_DYNAMIC(CVoidReasonDlg)

public:
	CVoidReasonDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CVoidReasonDlg();

// 对话框数据
	enum { IDD = IDD_VOIDREASON };
	HBITMAP m_bpBackgrd;
	int m_x;
	int m_y;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	CListBox m_list;
	CString m_strReason;//存储退菜原因
	CRoundButton2 m_btnOK;
	CRoundButton2 m_btCancel;
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
