#pragma once
/*********************************************************************
*Copyright (c) 2011 Coolroid Co.Ltd.
*DESCRIPTION：
*		付款对话框页面。
*AUTHOR ：zhangyi
*HISTORY：
*		author time    version   desc

*********************************************************************/
#include "afxwin.h"
#include "OrderPage.h"
#include "TimeCounter.h"

// PayDlg 对话框

class PayDlg : public COrderPage
{
	DECLARE_DYNAMIC(PayDlg)

public:
	PayDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~PayDlg();
	void OnSetActive();
	BOOL LockScreen();
	void UpdateSubtotal(void);
	void ShowClassPage();
// 对话框数据
	enum { IDD = IDD_PAY };

	CString m_strNum;
	//BOOL m_bQuickPay;
	static int CHECK_COUNT;
	int CLASS_LINES;
	CStatic m_logCtrl;
	CStatic m_timeCtrl;
	CStatic m_guestCtrl;
	CStatic m_tableCtrl;
	CStatic m_checkCtrl;
	CStatic m_numCtrl;
	CRect mRectNum;
	double m_fEpsinon;
	BOOL m_bMemberPrice;
	Gdiplus::Image* m_bpButtonClass[2];
	CPButtonList m_classButtons;
	CFont m_numFont;
	//支付方式分页
	UINT m_uTotalPage; // 总页数
	UINT m_uCurPage; // 当前位于多少页

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	BOOL SetCheckName(LPCTSTR name);
	static void FormatName(OrderDetail* pItem,CString& name);
	static BOOL OrderDetail2Json(OrderDetail* pItem,JSONVALUE& retrunItem);
	
	//BOOL m_bVoidState;
	//int comport,baud_rate,parity_type,num_data_bit,num_stop_bits;
	DECLARE_MESSAGE_MAP()
public:
	static void FormatTableInfo(JSONVALUE& root);
	static void PrintRound(CCheckDlg& currentChkDlg,int active);
	static void PrintCheck(CCheckDlg& currentChkDlg,int active,int type);
	static void FormatPrint(JSONVALUE& root,PrintDeviceInfo& printer,CCheckDlg& checkDlg,int active);
	static void OnBnClickedTakeOutChk(CTypedPtrList<CPtrList,OrderDetail *> *pOrderList);
	BOOL CheckCosumeLimit();
	BOOL IsRegLimit();
	BOOL CleanTable(BOOL bForce);
	void UpdateNumber(LPCTSTR str);
	static BOOL GetWeixinQRCode(int total_fee);

	virtual BOOL OnInitDialog();
	void OnSize(UINT nType, int cx, int cy);
//	afx_msg void OnBnClickedSaveOrder();
	afx_msg void OnBnClickedPrepage();
	afx_msg void OnNumBnClicked(UINT uID);
	afx_msg void OnBnClickedPayment(UINT uID);
	afx_msg void OnBnClickedButtonClear();
	afx_msg void OnBnClickedOK();
	afx_msg void OnBnClickedButton00();
	afx_msg void OnBnClickedButton10();
	afx_msg void OnBnClickedButton20();
	afx_msg void OnBnClickedButton50();
	afx_msg void OnBnClickedButton100();
	afx_msg void OnBnClickedButtonDot();
	afx_msg void OnBnClickedGuest();
	afx_msg void OnBnClickedService();
	afx_msg void OnBnClickedDiscount();
	afx_msg void OnBnClickedButtonVoid();
	afx_msg void OnBnClickedButtonFunction();
	afx_msg void OnBnClickedManagFunction();
	afx_msg void OnBnClickedCheckName();
	afx_msg void OnBnClickedPrePrint();
	afx_msg void OnBnClickedPrintRound();
	afx_msg void OnBnClickedCustomerName();
	afx_msg void OnBnClickedButtonInvoice();
	afx_msg void OnBnClickedTakeOutChk();
	afx_msg void OnBnClickedSelectAll();
	afx_msg void OnBnClickedTakeOutInfo();
	afx_msg void OnBnClickedMemberPrice();
	afx_msg void OnBnClickedActualPayed();
	afx_msg void OnBnClickedSeparateCheck();
	afx_msg void OnBnClickedButtonUp();
	afx_msg void OnBnClickedButtonDown();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
