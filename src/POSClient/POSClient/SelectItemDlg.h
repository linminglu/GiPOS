#pragma once
#include "listboxex.h"
#include "afxwin.h"
#include "coloredit.h"


// SelectItemDlg 对话框

class SelectItemDlg : public CDialog
{
	DECLARE_DYNAMIC(SelectItemDlg)

public:
	SelectItemDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~SelectItemDlg();
	CreatButton m_btnCtrl;
	CTypedPtrList<CPtrList,OrderDetail *> *m_pOrderList;
	int m_nCheckID;//哪一张单
	double percent;//打折的比例
	//int discount_level;//属于的折扣级别
	double amount;//根据选择的菜品计算出来的打折金额
	CString m_strHint;
	int m_nType; //0 打折时选择菜品； 1 复制菜单时选择；2 服务费选择菜品
// 对话框数据
	enum { IDD = IDD_SELECTITEM };
	HBITMAP m_bpBackgrd;
	int m_x;
	int m_y;
	CWnd* pParentWnd;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	void OnSetActive();
	CListBoxEx m_list;
	CStatic m_logCtrl;
	CStatic m_timeCtrl;
	CStatic m_guestCtrl;
	CStatic m_tableCtrl;
	CStatic m_checkCtrl;
	CColorEdit m_hint;
	afx_msg void OnBnClickedSelectAll();
	afx_msg void OnBnClickedOK();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedClear();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
