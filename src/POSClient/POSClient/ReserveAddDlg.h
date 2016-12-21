#pragma once

#include "PosPage2.h"
#include "CheckDlg.h"
#include "afxcmn.h"
#include "afxdtctl.h"
#include "afxwin.h"
#include "TableButton.h"
// ReserveAddDlg 对话框
#define WM_MESSAGE_REFRESH	(WM_USER+130)

class ReserveAddDlg : public CPosPage2
{
	DECLARE_DYNAMIC(ReserveAddDlg)

public:
	ReserveAddDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~ReserveAddDlg();

// 对话框数据
	enum { IDD = IDD_RESERVEADD };
	CDateTimeCtrl m_dateCtrl;
	CRoundButton2 m_btnPrepage;
	CRoundButton2 m_btnOK;
	CRoundButton2 m_btnCancel;
	CTableButton* m_SelectedTable;
	CComboBox mComboBox;
	CFont mTableFont;
	Gdiplus::Image* m_bpTableStatus[6];
	int m_nTableId;
	int m_nPageSize;
	int m_nCurrentPage;
	int m_nPageCount;
	CString m_strUname;
	CString m_strPhone;
	std::vector<CButton*> m_itemButtons;
	vector<TableItem> m_RVCTables;//当前RVC显示的桌子
	long m_lOrderId;
protected:
	CRect mRectHint;
	void ShowCurrentPage();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonPre();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButtonLeft();
	afx_msg void OnBnClickedButtonRight();
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnTableClicked(UINT uID);
};
