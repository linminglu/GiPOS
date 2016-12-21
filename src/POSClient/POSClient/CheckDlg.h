#pragma once
#include "listboxex.h"
#include "POSClient.h"

// CCheckDlg 对话框

class CCheckDlg : public CDialog
{
	DECLARE_DYNAMIC(CCheckDlg)

public:
	CCheckDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCheckDlg();
	CTypedPtrList<CPtrList,OrderDetail *> *m_pOrderList;
// 对话框数据
	enum { IDD = IDD_CHECK };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	CListBoxEx m_ctrlDetailList;
	CListBoxEx m_subTotalList;
	double m_fSubtotal;//小计，不包括折扣和服务费！
	double m_fService;//服务费
	double m_fDiscount;//折扣
	double m_fTax;//税金
	double m_fPayed;//已付金额
	double m_fDebt;//剩余未付金额
	double m_fMolin;//抹零
	int m_nTotal;//总菜品数
	int m_nStatus;//0 -open, 1 -close
	int m_nEatType; //堂食还是外带
	BOOL m_bHideDesc;//是否显示备注
	BOOL m_bDiscountChange;//整单折扣变化
	OrderDetail* m_pDiscount;//整单折扣
	OrderDetail* m_pService;//整单服务费
	int m_iDxDiscount;
	int m_iDxService;
	//BOOL m_bTaxInclude;
	std::map<int,TaxItem*> mTaxGroup;
	static CString TAX_NAME;
	void ResetContent(BOOL bAll=TRUE);
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	int AddOrderItem(OrderDetail* order,BOOL bUpdate=TRUE,int index=-1);
	int DeleteOrderItem(int index);
	void InsertCondiment(int index,OrderDetail* order,BOOL bUpdate);
	OrderDetail* GetLastItem();
	BOOL UpdateItemString(int nIndex,BOOL bReCompute=TRUE);
	static void FormatString(OrderDetail* pOrder,CString& strLine,BOOL bHideDesc);
	void AddPay(double fPayed);
	void UpdateSubtotal();
	void ComputeSubtotal();
	double GetSubtotalToDiscount();
	//double GetSubtotalToService(int service);
	static double Round(double total,int round_type);
	afx_msg void OnLbnSelchangeList();
	LRESULT EnablePage(WPARAM wParam, LPARAM lParam);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};
