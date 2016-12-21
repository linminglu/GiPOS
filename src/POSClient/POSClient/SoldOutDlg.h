#pragma once
#include "afxwin.h"
#include "PosPage2.h"
#include "OrderDlg.h"

// SoldOutDlg 对话框

class SoldOutDlg : public CPosPage2
{
	DECLARE_DYNAMIC(SoldOutDlg)

public:
	SoldOutDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~SoldOutDlg();

// 对话框数据
	enum { IDD = IDD_SOLDOUT };
	Gdiplus::Image* m_bpButtonLf[2];
	Gdiplus::Image* m_bpButtonRt[2];
	CPButtonList m_itemButtons;
	std::vector<int> mSluId;
	int m_nCurrentPagel;
	int m_nPageCountl;
	int m_nPageSizel;
	std::vector<MenuItem> m_ItemsL;
	int m_nCurrentPageR;
	int m_nPageCountR;
	int m_nPageSizeR;
	std::vector<MenuItem> m_ItemsR;


	CRoundButton2 m_btOK;
	CRoundButton2 m_btClear;
	CRoundButton2 m_btClean;
	CRoundButton2 m_btPrepage;
	CComboBox mComboBox;
	CEdit mEdit;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	void ShowCurrentPage();
	void ShowCurrentPageR();
	void UpdateBargainItem(BOOL bEnd=TRUE);
	afx_msg void OnBnClickedButtonLeft();
	afx_msg void OnBnClickedButtonRight();
	afx_msg void OnLItemBnClicked(UINT uID);
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnBnClickedButtonLeftR();
	afx_msg void OnBnClickedButtonRightR();
	afx_msg void OnRItemBnClicked(UINT uID);
	afx_msg void OnBnClickedButtonClear();
	afx_msg void OnBnClickedOk();
	
	afx_msg void OnBnClickedButtonSearch();
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnBnClickedButtonClean();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	
};
