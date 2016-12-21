#pragma once
/*********************************************************************
*Copyright (c) 2013 Coolroid Co.Ltd.
*DESCRIPTION：
*		点菜和付款对话框的父类。
*AUTHOR ：zhangyi
*HISTORY：
*		author time    version   desc

*********************************************************************/
#include "afxwin.h"
#include "CoolTabCtrl.h"
#include "CheckDlg.h"
#include "order_detail.h"

// OrderDlg 对话框
struct MenuItem
{
	int type;//-1 slu ,0 普通; 1 配料;2 时价 ;3 套餐
	int item_number;
	int condiment;//需要的配料组
	int n_discount_level;//对菜品可以使用的折扣级别
	int n_service_level;//对菜品可以使用的服务费级别
	int bargain_stype;//0 不限量 1 手动估清 2 限量估清
	int time_accuracy;// >0 计时菜品的计时精度（分钟）
	int tax_group;//税率组
	BOOL weight_required;//是否需要称重
	BOOL modify;//是否需要选择规格
	BOOL is_time;//
	double price;
	double bargain_num_cur;//当前剩余的限量
	double default_num;//在套餐里面默认的数量
	CString item_name1;
	CString item_name2;
	CString icon;
	CString unit;//默认规格
};
struct CourseInfo
{
	int id;//组号
	int total_select;//该套餐组总共可点的次数
	int can_select;//剩余可点的份数
	int slu_id;
	vector<OrderDetail*> m_orders;//该组内已点菜品
};
enum ITEM_TYPE{ITEM_CONDIMENT_GROUP=-2,ITEM_SLU=-1,ITEM_ITEM,ITEM_CONDIMENT,ITEM_PRICE,ITEM_SET,ITEM_OPEN,ITEM_TEXT};


class COrderPage :
	public CPosPage
{
public:
	COrderPage(int nId);
	~COrderPage();
	CCoolTabCtrl	m_TabCtrl;//账单信息
	CCheckDlg		m_checkDlg[MAX_CHECKS];
	CTypedPtrList<CPtrList,OrderDetail *> *m_pOrderList;
	static int m_nLastActive;
	int m_nVoidState;//0 正常点菜,1 退菜， 2 退菜，已输入原因，3 套餐中退菜

	CStatic m_ctrlHint;
	CRect mRectHint;

	static CString m_strTAInfo;
	static BOOL bNewTainfo;
	static CString m_strCardID;

	void UpdateHint(LPCTSTR strHint);
	void UpdateCheckData();
	void LoadCheckData();
	void UpdateSencondScreen(int active,OrderDetail* pOder);
	void VoidItem(int active);
	void DeletePay(long order_id);
	virtual void UpdateSoldoutInfo(OrderDetail* item,double diff);
	static void CopyPrintItem(PrintItem& pItem,OrderDetail* from);
	static void readOrderDetail(CRecordset& rs,OrderDetail* order);
	static void SetRsDetail(COrder_Detail& rsDetail,OrderDetail* item);
	static void FormatTableInfo(JSONVALUE& root);
	static int RequeastAuth(CString& authID,CString strPrivilege,int nMiniPermission=1,WCHAR* pAuthUser=NULL);
};
