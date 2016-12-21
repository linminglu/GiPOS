#pragma once


// AlterItemDlg 对话框

class AlterItemDlg : public CDialog
{
	DECLARE_DYNAMIC(AlterItemDlg)

public:
	AlterItemDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~AlterItemDlg();

// 对话框数据
	enum { IDD = IDD_ALTER };

	HBITMAP m_bpBackgrd;
	HWND hParent;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	CreatButton m_btnCtrl;
	
	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnBnClicked(UINT uID);
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg LRESULT OnNcHitTest(CPoint point);
};
