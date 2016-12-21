#pragma once
#include "CheckDlg.h"
#include "OrderDlg.h"
#include "afxwin.h"

// ComboMealDlg 对话框

class ComboMealDlg : public CDialog
{
	DECLARE_DYNAMIC(ComboMealDlg)

public:
	ComboMealDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~ComboMealDlg();

// 对话框数据
	enum { IDD = IDD_COMBOMEAL };

	OrderDetail* pParentItem;
	CTypedPtrList<CPtrList,OrderDetail *> m_subOrderList;
	int m_nMode;// 1 -套餐换菜模式
	CTypedPtrList<CPtrList,OrderDetail *> m_voidOrderList;//套餐换菜删除的菜
	CTypedPtrList<CPtrList,OrderDetail *> m_addOrderList;//套餐换菜新增的菜
	int m_nVoidNum;
	

protected:
	int m_nQuantity;//当前点菜时的菜品数量
	CListBoxEx	m_listEx;
	CStatic m_Hint;
	CRect m_hintRect;
	CRoundButton2* m_CheckedButton;
	UINT m_nPageSize;
	UINT m_nCurrentPage;
	UINT m_nPageCount;
	UINT m_uTotalPage; // 总页数
	UINT m_uCurPage; // 当前位于多少页
	vector<CourseInfo> m_CourseGroups;//记录套餐可选组
	std::vector<MenuItem> m_Items;
	int m_nCurrentCourse;//当前显示的套餐组index

	HBITMAP m_bpBackgrd;
	Gdiplus::Image* m_bpButtonItem[2];
	Gdiplus::Image* m_bpButtonSLU[2];
	Gdiplus::Image* m_bpSlodoutItem[2];
	std::vector<CButton*> m_itemButtons;
	CPButtonList m_classButtons;
	int ITEM_COLUMNSIZE;
	int ITEM_LINESIZE;
	CRoundButton2 m_btCondiment;
	CRoundButton2 m_btNum;
	CRoundButton2 m_btVoid;
	CRoundButton2 m_btCancel;
	CRoundButton2 m_btOK;
	int m_x;
	int m_y;

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	void ShowCurrentPage();
	void ShowClassPage();
	void ShowCourse(int index,CString filter);
	void FormatString(OrderDetail* pOrder,CString& strLine);
	OrderDetail* AddOrderItem(OrderDetail* item);
	void AddFixedSetItem(OrderDetail* item);
	void InsertCondiment(int index,OrderDetail* order);
	void UpdateHint();
	MenuItem readCourseItem(CRecordset& rs);

	afx_msg void OnBnClickedButtonLeft();
	afx_msg void OnBnClickedButtonRight();
	afx_msg void OnBnClickedButtonUp();
	afx_msg void OnBnClickedButtonDown();
	afx_msg void OnItemBnClicked(UINT uID);
	afx_msg void OnSluBnClicked(UINT uID);
	afx_msg void OnBnClickedQuantity();
	afx_msg void OnBnClickedButtonVoid();
	afx_msg void OnBnClickedAddRequest();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnLbnSelchangeList();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
//	CEdit m_searchEdit;
	BOOL m_bnotify;
};
