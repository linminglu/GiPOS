#pragma once
#include "afxwin.h"
#include "roundbutton2.h"


// TableStatusDlg 对话框

class TableStatusDlg : public CDialog
{
	DECLARE_DYNAMIC(TableStatusDlg)

public:
	TableStatusDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~TableStatusDlg();

// 对话框数据
	enum { IDD = IDD_TABLESTATUS };
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListBox m_infoList;
	int m_nTblID;
	virtual BOOL OnInitDialog();
	CRoundButton2 m_closeButton;
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
};
