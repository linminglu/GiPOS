#pragma once
#include "afxwin.h"
#include "OrderDlg.h"
#include "ComboMealDlg.h"
#include "XEditPrompt.h"

// NotifyKitchenDlg 对话框

class NotifyKitchenDlg : public CDialog
{
	DECLARE_DYNAMIC(NotifyKitchenDlg)

public:
	NotifyKitchenDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~NotifyKitchenDlg();
	std::vector<int> mPrintclassId;
	CString m_strTtitle;
	CString m_strText;
	int type;//0 通知厨房； 1 调味品；2 整桌备注
	int m_nShowHint;
	OrderDetail* pBelongItem;
	OrderDlg* pOrderDlg;
	ComboMealDlg* pComboDlg;
	int m_insertIdx;
	int m_x;
	int m_y;
	int m_nDefaultGroup;
	CXEditPrompt mEdit;
	UINT m_nPageSize;
	UINT m_nCurrentPage;
	UINT m_nPageCount;
	UINT m_uTotalPage; // 总页数
	UINT m_uCurPage; // 当前位于多少页
	std::vector<MenuItem> m_Items;

	HBITMAP m_bpBackgrd;
	Gdiplus::Image* m_bpButtonItem[2];
	Gdiplus::Image* m_bpButtonSLU[2];
	Gdiplus::Image* m_bpSlodoutItem[2];
	CPButtonList m_itemButtons;
	CPButtonList m_classButtons;
	

// 对话框数据
	enum { IDD = IDD_NOTIFYKIT };
	
	CRoundButton2 m_btOK;
	CRoundButton2 m_btCancel;
	CRoundButton2 m_btClear;
	CRoundButton2 m_btClearPre;
	CRoundButton2 m_softButton;
	CRoundButton2 m_handButton;
	CRoundButton2 m_bt1;
	CRoundButton2 m_bt2;
	CRoundButton2 m_bt3;
	CRoundButton2 m_bt4;
	CRoundButton2* m_CheckedClassButton;
protected:
	int CLASS_LINESIZE;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonClear();
	afx_msg void OnBnClickedButtonClearPre();
	afx_msg void OnBnClickedButtonLeft();
	afx_msg void OnBnClickedButtonRight();
	afx_msg void OnBnClickedButtonUp();
	afx_msg void OnBnClickedButtonDown();
	afx_msg void OnItemBnClicked(UINT uID);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSluBnClicked(UINT uID);

	CComboBox mComboBox;
	virtual BOOL OnInitDialog();
	void ShowCurrentPage();
	void ShowClassPage();
	BOOL SetOpenItem(OrderDetail* item);
	static BOOL GetCondimentItems(int nGroup,vector<MenuItem>& items);
	
	afx_msg void OnBnClickedOk();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedButtonPrefix(UINT uID);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedButtonSoftkey();
	afx_msg void OnBnClickedCtrlHandInput();
};
