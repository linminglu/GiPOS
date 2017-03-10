#pragma once
/*********************************************************************
*Copyright (c) 2011 Coolroid Co.Ltd.
*DESCRIPTION��
*		��˵�ҳ�档
*AUTHOR ��zhangyi
*HISTORY��
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
	OrderDlg(CWnd* pParent = NULL);   // ��׼���캯��
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
// �Ի�������
	enum { IDD = IDD_ORDER };

public:
	//ÿҳ���24����Ʒ,3��x8��
	int ITEM_COLUMNSIZE;
	int ITEM_LINESIZE;
	int CLASS_LINES;
	static int ITEM_TEXTSIZE;
	int CLASS_TEXTSIZE;
	int m_bCloseSearch;
	//��Ʒ��ҳ
	int m_nCurrentPage;
	int m_nPageCount;
	int m_nPageSize;//ÿҳ�Ĵ�С����۳���ҳ��ť
	//������ҳ
	UINT m_uTotalPage; // ��ҳ��
	UINT m_uCurPage; // ��ǰλ�ڶ���ҳ

	BOOL m_bUpdateItems;//�����˲�Ʒ���Ҳ��������ˢ��
	Gdiplus::Image* m_bpButtonItem[2];
	Gdiplus::Image* m_bpSlodoutItem[2];
	Gdiplus::Image* m_bpButtonSLU[2];
	Gdiplus::Image* m_bpButtonClass[2];
	Gdiplus::Image* m_bpButtonPre[2];
	Gdiplus::Image* m_bpButtonNext[2];

	CRoundButton2* m_CheckedClassButton;

	int m_nCurrentClass;//���浱ǰ��Ʒ�ķ���
	static double m_nQuantity;
	static int m_nSeat;

	static int m_nChkNum;//����
//	static long m_lHeadId;//������һ�ε�head_id
	static vector<MenuItem> m_Items;
	StringInputDlg* m_searchDlg; 
	//AlterItemDlg* m_alterDlg;
	std::vector<CButton*> m_itemButtons;
	CPButtonList m_classButtons;
	CString m_strTmpUser;
	static CString m_strTblRemark;//��ע

	CStatic m_logCtrl;
	CStatic m_timeCtrl;
	CStatic m_guestCtrl;
	CStatic m_tableCtrl;
	CStatic m_checkCtrl;

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
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
	afx_msg void OnBnClickedCombine();//������̨���˵��ϲ�����ǰ̨
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
