#pragma once
/*********************************************************************
*Copyright (c) 2011 Coolroid Co.Ltd.
*DESCRIPTION：
*		点菜的页面。
*AUTHOR ：zhangyi
*HISTORY：
*		author time    version   desc

*********************************************************************/
#include "afxwin.h"
#include <vector>
using namespace std;
#include "OrderPage.h"
#include "StringInputDlg.h"
//#include "AlterItemDlg.h"

class OrderDlg : public COrderPage
{
	DECLARE_DYNAMIC(OrderDlg)
public:
	OrderDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~OrderDlg();
	void OnSetActive();
	BOOL LockScreen();
	void OnSize(UINT nType, int cx, int cy);
	void ShowCurrentPage();
	void ShowClassPage();
	int ShowCondiment(OrderDetail* pOrder,int nGroup);
	virtual void UpdateSoldoutInfo(OrderDetail* item,double diff);
	
	static void UpdateInfo(CWnd* parent);
	static int SaveOrderToDB(CTypedPtrList<CPtrList,OrderDetail *> *pOrderList,CCheckDlg (*m_checkDlg)[MAX_CHECKS]);
	static void SendOrder(CCheckDlg (&m_checkDlg)[MAX_CHECKS],int count);
	static void PrintTableOrder(vector<PrintItem>& menu_list,CCheckDlg& currentChkDlg);
	
	
	static BOOL SaveOrderHead();
	static void EmptyCheck();
// 对话框数据
	enum { IDD = IDD_ORDER };

public:
	//每页最多24个菜品,3列x8行
	int ITEM_COLUMNSIZE;
	int ITEM_LINESIZE;
	int CLASS_LINES;
	static int ITEM_TEXTSIZE;
	int CLASS_TEXTSIZE;
	int m_bCloseSearch;
	//菜品分页
	int m_nCurrentPage;
	int m_nPageCount;
	int m_nPageSize;//每页的大小，需扣除翻页按钮
	//主类别分页
	UINT m_uTotalPage; // 总页数
	UINT m_uCurPage; // 当前位于多少页

	BOOL m_bUpdateItems;//更新了菜品，右侧的数据需刷新
	Gdiplus::Image* m_bpButtonItem[2];
	Gdiplus::Image* m_bpSlodoutItem[2];
	Gdiplus::Image* m_bpButtonSLU[2];
	Gdiplus::Image* m_bpButtonClass[2];
	Gdiplus::Image* m_bpButtonPre[2];
	Gdiplus::Image* m_bpButtonNext[2];

	CRoundButton2* m_CheckedClassButton;

	int m_nCurrentClass;//保存当前菜品的分类
	static double m_nQuantity;
	static int m_nSeat;

	static int m_nChkNum;//单号
//	static long m_lHeadId;//缓存上一次的head_id
	static vector<MenuItem> m_Items;
	StringInputDlg* m_searchDlg; 
	//AlterItemDlg* m_alterDlg;
	std::vector<CButton*> m_itemButtons;
	CPButtonList m_classButtons;
	CString m_strTmpUser;
	static CString m_strTblRemark;//桌注

	CStatic m_logCtrl;
	CStatic m_timeCtrl;
	CStatic m_guestCtrl;
	CStatic m_tableCtrl;
	CStatic m_checkCtrl;

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnClassBnClicked(UINT uID);
	afx_msg void OnSluBnClicked(UINT uID);
	afx_msg void OnItemBnClicked(UINT uID);
	afx_msg void OnNumBnClicked(UINT uID);
	afx_msg void OnBnClickedButtonPay();
	afx_msg void OnBnClickedButtonCancel();
	afx_msg void OnBnClickedButtonLeft();
	afx_msg void OnBnClickedButtonRight();
	afx_msg void OnBnClickedButtonUp();
	afx_msg void OnBnClickedButtonDown();
	afx_msg void OnBnClickedButtonVoid();
	afx_msg void OnBnClickedButtonView();
	afx_msg void OnBnClickedButtonFunction();
	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnBnClickedSendOrder();

	afx_msg void OnBnClickedQuantity();
	afx_msg void OnBnClickedSeatNum();
	afx_msg void OnBnClickedNextSeat();
	afx_msg void OnBnClickedTransfer();
	afx_msg void OnBnClickedCombine();//将其他台的账单合并到当前台
	afx_msg void OnBnClickedAddCheck();
	afx_msg void OnBnClickedPrepage();
	afx_msg void OnBnClickedModify();
	afx_msg void OnBnClickedTakeOut();
	afx_msg void OnBnClickedOpenItem();
	void SetOpenItem(OrderDetail* item);
	afx_msg void OnBnClickedSearch();
	afx_msg void OnBnClickedRePrice();
	afx_msg void OnBnClickedRemindDish();
	afx_msg void OnBnClickedRemindDishByClass();
	afx_msg void OnBnClickedChangFamilyGroup();
	afx_msg void OnBnClickedAlterItem();
	afx_msg void OnBnClickedFreeDish();
	afx_msg void OnBnClickedNotifyKitchen();
	afx_msg void OnBnClickedAddRequest();
	afx_msg void OnBnClickedSwapCourse();
	afx_msg void OnBnClickedPrintRound();
	afx_msg void OnBnClickedPrePrint();
	afx_msg void OnBnClickedButtonParty();
	afx_msg void OnBnClickedButtonTransItem();
	afx_msg void OnBnClickedSelectAll();
	afx_msg void OnBnClickedTableRemark();
	afx_msg void OnBnClickedRepeat();
	afx_msg void OnBnClickedIncrease();
	afx_msg void OnBnClickedDecrease();
	afx_msg void OnBnClickedPickCheck();
	afx_msg void OnBnClickedTakeOutChk();
	afx_msg void OnBnClickedDeleteAll();
	afx_msg void OnBnClickedSuspend();
	afx_msg void OnBnClickedRefund();
	LRESULT OnMsgSearch(WPARAM wParam, LPARAM lParam);
	void AddMenuItem(CString& strSQL);
		void QuickOrderLogout();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
