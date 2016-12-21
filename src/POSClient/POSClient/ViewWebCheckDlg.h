#pragma once

#include "PosPage2.h"
#include "CheckDlg.h"
#include "afxcmn.h"
#include "afxdtctl.h"
#include "SortListCtrl.h"
// ViewWebCheckDlg 对话框

class ViewWebCheckDlg : public CPosPage2
{
	DECLARE_DYNAMIC(ViewWebCheckDlg)

public:
	ViewWebCheckDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~ViewWebCheckDlg();

// 对话框数据
	enum { IDD = IDD_VIEWWEBCHK };

	CStatic m_tableCtrl;
	CRoundButton2 m_btnPrepage;
	CRoundButton2 m_btnGoto;
	CCheckDlg	m_checkDlg;
	CSortListCtrl m_listCtrl;
	CDateTimeCtrl m_datetimeCtrl;
	long m_nOrderHeadid;
	int m_nType;
	CTypedPtrList<CPtrList,OrderDetail *> m_orderList;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	void ShowOrderheads(CString strSQL,int type);
	void UpdateCheckData();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonPre();
	afx_msg void OnLvnItemchangedList2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDtnCloseupDatetimepicker1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonGoto();
};
