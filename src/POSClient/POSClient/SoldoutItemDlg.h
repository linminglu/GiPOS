#pragma once
#include "afxwin.h"


// SoldoutItemDlg 对话框

class SoldoutItemDlg : public CDialog
{
	DECLARE_DYNAMIC(SoldoutItemDlg)

public:
	SoldoutItemDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~SoldoutItemDlg();

// 对话框数据
	enum { IDD = IDD_SOLDITEM };
	int m_nItemId;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CComboBox mComboBox;
	CEdit m_numEdit;
	CButton mCheckBox;
	afx_msg void OnCbnSelchangeCombo1();
	CButton mButtonNum;
	CRoundButton2 m_btOK;
	CRoundButton2 m_btCancel;
	afx_msg void OnBnClickedButtonNum();
	afx_msg void OnBnClickedOk();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
};
