#pragma once
#include "coloredit.h"
#include "afxwin.h"


// DiscountDlg 对话框
struct DiscountItem
{
	int id;
	double percent;
	int privilege;//权限
	//int discount_level;//折扣级别
	int round_type;//抹零类型
	BOOL isOpenItem;//是否为自定义折扣
	BOOL select;//选择打折范围
	BOOL noDiscount;//服务费是否不打折
	double amount;
	CString name;
	CString display_name;
};
class DiscountDlg : public CDialog
{
	DECLARE_DYNAMIC(DiscountDlg)

public:
	DiscountDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~DiscountDlg();

// 对话框数据
	enum { IDD = IDD_DISCOUNT };
	DiscountItem selectedItem;
	int m_nCheckID;//哪一张单
	int m_nIsService; //0 -折扣；1 服务费
	CWnd* pParentWnd;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	void CreatButtons();
	CPButtonList m_itemButtons;
	vector<DiscountItem> m_Items;
	Gdiplus::Image* m_bpButtonItem[2];
	int ITEM_COLUMNSIZE;
	int ITEM_LINESIZE;
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnItemBnClicked(UINT uID);
	CColorEdit m_editDiscount;
	CRoundButton2 m_btnPrepage;
	afx_msg void OnBnClickedButtonPre();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
