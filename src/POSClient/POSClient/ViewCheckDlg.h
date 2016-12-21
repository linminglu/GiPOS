#pragma once
/*********************************************************************
*Copyright (c) 2011 Coolroid Co.Ltd.
*DESCRIPTION：
*		查看已结单页面。
*AUTHOR ：zhangyi
*HISTORY：
*		author time    version   desc

*********************************************************************/
#include "afxwin.h"
#include "CoolTabCtrl.h"
#include "CheckDlg.h"
#include "afxcmn.h"
#include "afxdtctl.h"
#include "SortListCtrl.h"
// ViewCheckDlg 对话框

class ViewCheckDlg :public CPosPage
{
	DECLARE_DYNAMIC(ViewCheckDlg)

public:
	ViewCheckDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~ViewCheckDlg(void);
	void OnSetActive();
	void UpdateCheckData();
	void ShowOrderheads(CString strSQL);
	void ReFormatTableInfo(JSONVALUE& root);
	// 对话框数据
	enum { IDD = IDD_VIEWCHK };

	CStatic m_logCtrl;
	CStatic m_timeCtrl;
	CStatic m_guestCtrl;
	CStatic m_tableCtrl;
	CStatic m_checkCtrl;
	CCheckDlg	m_checkDlg;
	BOOL m_bSetBg;
	//全局账单信息，用于打印
	int m_nActive;
	long m_nOrderHeadid;
	int m_nCheckNum;
	int m_nGuests;
	CString m_strUser;
	CString m_strInvoice;
	CTime m_dayendTime;

	CRoundButton2 m_btnPrepage;
	CRoundButton2 m_btPrint;
	CRoundButton2 m_btPrePrint;
	CRoundButton2 m_btInvoice;
	CRoundButton2 m_btReopen;
	CRoundButton2 m_btTable;
	CRoundButton2 m_btTips;
	CSortListCtrl m_listCtrl;
	CTypedPtrList<CPtrList,OrderDetail *> m_orderList;
	CDateTimeCtrl m_datetimeCtrl;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	void OnSize(UINT nType, int cx, int cy);
	void OnBnClickedSearch();
	afx_msg void OnBnClickedButtonPre();
	afx_msg void OnLvnItemchangedList2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDtnCloseupDatetimepicker1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonNum();
	afx_msg void OnBnClickedButtonPrint();
	afx_msg void OnBnClickedButtonInvoice();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnBnClickedButtonReopen();
	afx_msg void OnBnClickedButtonPreprint();
	afx_msg void OnBnClickedButtonTips();
	void ResetButton();
};
