#pragma once

#include "PosPage2.h"
#include "CheckDlg.h"
#include "afxcmn.h"
#include "afxdtctl.h"
#include "SortListCtrl.h"
// ViewReserveDlg 对话框

class ReserveDlg : public CPosPage2
{
	DECLARE_DYNAMIC(ReserveDlg)

public:
	ReserveDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~ReserveDlg();

// 对话框数据
	enum { IDD = IDD_RESERVE };

	CRoundButton2 m_btnPrepage;
	CRoundButton2 m_btnGoto;
	CRoundButton2 m_btnAdd;
	CListCtrl m_listCtrl;
	long m_lSelOrderId;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonPre();
	afx_msg void OnBnClickedButtonGoto();
	void ShowOrders();
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnLvnItemchangedList2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg LRESULT OnMsgRefresh(WPARAM wParam, LPARAM lParam);
};
