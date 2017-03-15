// POSClient.h : PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif
#if !defined __POSCLIENT_H
# define __POSCLIENT_H
//对话框ID，必须与加入的顺序一致
enum{DLG_LOGIN,DLG_FLOOR, DLG_ORDER,DLG_PAY,DLG_SPLIT,DLG_FUNCTION,DLG_MANAGER,DLG_VIEWCHK,DLG_QUICK_ORDER};

#include "resource.h"		// 主符号
#include "MainSheet.h"
#include "ProgressDlg.h"
#include "MultiLanguage.h"

// CPOSClientApp:
// 有关此类的实现，请参阅 POSClient.cpp
//
//每页最多X个菜
#define MAX_ITEMS 100
//每桌最多8张单
#define MAX_CHECKS 8
#define MAX_HEADS 5000
//#define ITEM_ID_OPENITEM 10
#define ITEM_ID_SERVICE -1
#define ITEM_ID_DISCOUNT -2
#define ITEM_ID_SENDINFO -3
#define ITEM_ID_PAYINFO  -4
#define ITEM_ID_TEXTINFO -5
#define ITEM_ID_TIPS	 -6
enum {TYPE_DINE,TYPE_TAKEOUT};
enum OPR_TYPES{OPR_UNKNOW,OPR_FREE,OPR_REPRICE,OPR_VOID,OPR_ABORTPAY,OPR_TRANS,OPR_COMBINE,OPR_REFUND,OPR_SHIFT,OPR_DAYEND};
#define MAX_GUEST_NUM 9999
#define MAX_TABLE_NUM 9999
#define MAX_ITEM_QUANTITY 9999
const TCHAR* const OPR_TYPES_NAME[] = {
	L"UNKNOW",
	L"FREE",
	L"REPRICE",
	L"VOID",
	L"ABORTPAY",
	L"TRANS",
	L"COMBINE",
	L"REFUND",
	L"SHIFT",
	L"DAYEND",
};

#define WM_MESSAGE_SEARCH	(WM_USER+101)
#define PRINT_LIST_FULL		(WM_USER+102)
#define WM_MESSAGE_ENABLE	(WM_USER+103)
#define WM_MESSAGE_UPDATE	(WM_USER+104)
#define WM_MESSAGE_LOCK		(WM_USER+105)
#define WM_MESSAGE_SHOWNOTIFY (WM_USER+106)
#define WM_MESSAGE_CLOSEOK (WM_USER+200)
struct OrderDetail
{
	int n_saved;//0-未保存到数据库 1-已保存 2-已送厨
	BOOL weight_required;//是否需要称重
	int b_hascondiment; //0 无配料；1 有配料；3 是套餐
	long order_id;//order_detail_id
	long item_id;//菜品的id
	int n_checkID;//分单号
	long n_belong_item;//属于哪个菜的配料;-负数 表示套餐，绝对值为所属套餐的ID
	int n_eattype;//堂食还是外带
	int n_discount_type;//菜品，可以使用的折扣级别；如果当前为折扣，表示折扣ID
	int n_service_type;//菜品可以使用的服务费级别
	int n_seat_num;//西餐的位号
	int time_accuracy;// >0 计时菜品的计时精度（分钟）
	int tax_group;//税率组
	long n_sortindex;//用于分类排序的索引值 
	double quantity;//菜品的数量或重量
	double item_price;//单价
	double total_price;//总价=单价*数量
	double tax_amount;//税金
	double discount_price;//折扣金额
	double sales_amount;//菜品产生的销售额(扣除折扣后的金额)
	double orignal_price;//改价前的原价
	WCHAR unit[10];//菜品单位
	WCHAR item_name[64];//菜品名称
	WCHAR item_name2[32];//菜品厨打名称
	WCHAR authID[10];//退菜的授权ID
	WCHAR authUser[10];//退菜的授权用户
	WCHAR* return_reason;
	double discount_percent;//当为比例型的折扣或服务费时>0; -1 数值型或部分打折; 0 整单抹零
	BOOL noDiscount;//当为服务费时，是否不打折
	int round_type;//折扣时，抹零类型
	int bargain_stype;//0 不限量 1 手动估清 2 限量估清
	BOOL b_isfree;//是否赠送菜品
	BOOL b_reprice;//是否重定价过
	BOOL b_notprint; //是否在收银单打印
	int family_group;//报表子类
	int rush_times;//催菜次数
	OrderDetail* belongto;
	WCHAR description[100];//菜品描述
	~OrderDetail()
	{
		delete return_reason;
	}
};
struct PrintDeviceInfo
{
	int nDeviceType;
	int nComBaudrate;
	int nComDataBits;
	int nComStopBits;
	int nComParity;
	int nFlowControl;
	int nPaperWidth;
	BOOL bCutPaper;
	CString printerName;
	PrintDeviceInfo()
	{
		nDeviceType=-1;
	}
};

struct TableItem {
	int id;
	int raw_id;//搭台的ID
	int status;
	int rvc;
	int cur_gst;
	int seat_num;
	int ismake;//是否已上齐菜
	BOOL isWechat;
	CString name;
	CString party_table;
	CString open_time;//开台时间
	bool operator == (const TableItem&  tbl)
	{   
		return  (id == tbl.id);
	}
};
struct CheckItem
{
	long order_head_id;
	int check_number;
	int table_id;
	int check_id;
	int status;//账单状态
	CString order_start_time;
	CString table_name;
	double should_amount;
	CString display;
};
struct TaxItem
{
	int id;
	CString name;
	double rate;
	double total;
};

typedef std::vector<CPosPage*> CPageList;
class SecondScreenDlg;

class CPOSClientApp : public CWinApp
{
public:
	CPOSClientApp();
	CMainSheet* m_pMain;//主窗口

	//点单信息
	CString CURRENCY_SYMBOL;//货币符号
	CString m_strUserName;
//	CString m_strUserClass;//用户等级
	CString m_strUserID;
	CString m_strChkName;
	CString m_strTblName;//桌名
	CString m_strPeriod; //班次
	CString m_strHostName;//当前电脑名
	CString m_strIP;
	CString m_strResId;//餐厅ID
	CString m_strDiskId;//硬盘号
	CString m_strCloudURL;//云服务器地址
	CString m_strVipURL;  //会员服务器地址
	int		m_nVipPort;
	CString m_strPhone;//云服务绑定手机号
	CString m_strVersion;
	CString m_wxSubMchid;//微信子商户号
	string m_aliAuthToken;//支付宝token
	CString m_aliStoreId;//支付宝店铺ID
	CString m_strQfAppcode;
	CString m_strQfServerURL;
	CMap<CString, LPCTSTR, int, int> m_privilegeMap;//用户权限表
	BOOL m_bRefund;//退款状态
	BOOL m_bUseIE;
	CString m_strRefundReason;//退款的原因
	int m_nRVC;//RVC id,当前桌的区域
	CString m_strRVC;//RVC name
	CString m_strResName;
	int m_editMode;//0 本地模式(新安装) 1-网络模式 2-本地模式
	int m_nCheckNum;//本机单号
	long m_nOrderHeadid;//序列号
	int m_nGuests;
	int m_nTableId;
	int m_nRawTable;
	int m_nEatType;//堂食还是外带
	int m_nDeviceId;//设备号
	int m_isCusFloor;//登录后显示的第一个页面
	int m_nLimitType;//1：整桌最低消费 2：人均最低消费
	int m_nScaleType;//0: 不使用 1- PS1电子秤 2- OS2电子秤
	long m_nPartyId;//宴会分组ID
	double m_fLimitAmount;//最低消费金额
	double m_fMemberDiscount;//会员价优惠金额 
	CString m_strDeviceName;
	static BOOL m_bQuickService;//快餐模式
	BOOL m_bQuickOnce;//仅一次快餐，使用完后清除快餐模式
	BOOL m_bInputChkName;//是否强制输入牌号
	int m_nAutoSendType;//0-不自动送厨;1-挂单时自动送厨;2-结单后自动送厨
	int m_nShiftType;//0- 交班按电脑统计 1-按员工统计
	CString m_strBeginDate;
	CString m_strBeginTime;
	CString m_strEndTime;//结单时间，反结帐的单才有
	int m_bDirty;//是否需要更新内存信息: 0 不从数据库更新，不重设已结； 1 从数据库更新 ；2 不更新，但重设已结(开台自动点菜)
	CTypedPtrList<CPtrList,OrderDetail *> m_orderList;//已点菜品列表
	int m_nCheckStatus[MAX_CHECKS];//账单的状态，是否已结。
	int m_nActiveCheck;//当前活动的是哪个分单
	CustomerDisplay m_cusDisplay;//客显
	CustomerDisplay m_VCR;//视频监控
	PrintDeviceInfo m_prePrinter;
	PrintDeviceInfo m_payPrinter;
	CString m_strPrintHead;
	CString m_strPrintTail;
//	BOOL m_bCanRollback;//是否能进行取消操作
//	std::map<CString,PrintTemplate*> theTemplates;
	CRecentList* m_pRecentFileList;
	vector<int> m_tipSuggests;
	double m_dTaxRate;
	BOOL m_bTaxGST;//是否为GST税（服务费也收税）
	int m_nTaxRound;//税金四舍五入取整(日本使用)
	int m_nTaxType;// 税率类型 2-菜品已含税
	int m_nRoundType;//整单折扣类型
	int DECIMAL_PLACES;//小数点位数
	CString m_decPlace;
	unsigned char* enctrypkey;
	ULONG_PTR m_gdiplusToken;
	CFont m_txtFont;
	BOOL IS_SERVER;
private:
	CPageList m_pageList;
// 重写
	public:
	virtual BOOL InitInstance();
	double GetWeight();
	BOOL CheckInit();
	int GetDeviceID();
	BOOL InitPrinter();
	void ResetAutoIncrement();
	void OpenDrawer();
	static CString GetFileVersion(LPCTSTR cPath);
	void AddRecentString(CString str);
	void ClearQuickOnce();
	static void CriticalLogs(OPR_TYPES,CString detail);
	static void FormatPrintDevice(JSONVALUE& root,PrintDeviceInfo& printer);
	static BOOL PrintJson(JSONVALUE& root);
// 实现

	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
};
extern CPOSClientApp theApp;
extern CMultiLanguage	theLang;
extern Logger log_pos;
extern CDatabase theDB;
extern BOOL m_bTrainingMode;//是否培训模式
extern int m_bNotReg;
//extern CString m_strFont;
extern DWORD m_dTextColor;
extern DWORD DEFALUT_BACKGROUND_COLOR;
extern std::map<CString,int> macrosInt;
extern SecondScreenDlg* m_pSecond;
BOOL OpenDatabase(BOOL bRecounect=FALSE);
CString GetFiledValue(LPCTSTR strSQL);
BOOL HttpPost(LPCTSTR server,int port,LPCTSTR url,JSONVALUE& request,JSONVALUE& response);
void KillProcessByName(LPCTSTR lpProcessName);
INT_PTR POSMessageBox(LPCTSTR lpszText, UINT nType = MB_OK);
int POSMessageBox(UINT nIDPrompt,UINT nType = MB_OK);
void ComputeTotalPrice(OrderDetail* pOrder);
void ComputeTax(OrderDetail* pOrder);
CString FormatDBStr(LPCTSTR str);
CString GetMacAddress();
int ScaleX(int pt);
int ScaleY(int pt);

#endif // !defined POSCLIENT_H