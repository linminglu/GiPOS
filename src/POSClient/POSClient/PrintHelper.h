#pragma once
#include <vector>
using   namespace   std;
struct PrintItem
{
	int index;//在列表内的索引
	int item_id;//菜品的id
	long n_belong_item;//属于哪个菜的配料;<0 表示套餐
	int n_eattype;//堂食还是外带
	int n_class;  //菜品分类
	int n_seat;	  //所属的位号 
	int n_check;  //分单号
	BOOL b_isfree;//是否赠送菜品
	BOOL b_isvoid;//是否退菜
	double quantity;//菜品的数量或重量
	double item_price;//单价
	double total_price;//总价=单价*数量
	CString item_name; //菜品名称
	CString item_name2; //名称2
	CString unit;
	CString return_reason;
	CString description;//菜品描述
	
	PrintItem()
	{
		index=0;
		item_id=0;
		n_belong_item=0;
		n_eattype=0;
		n_class=-1;
		n_seat=0;
		b_isfree=FALSE;
		b_isvoid=FALSE;
		quantity=0;
		item_price=0;
		total_price=0;
	}
};
#define TEMPLATE_SEND		_T("send_order")
#define TEMPLATE_VOID		_T("void_item")
#define TEMPLATE_REMIND		_T("reminder")
#define TEMPLATE_PAY		_T("payment")
#define TEMPLATE_PREPAY		_T("prepayment")
#define TEMPLATE_MESSAGE	_T("message")
#define TEMPLATE_REPORT		_T("report")
#define TEMPLATE_SHIFT		_T("shiftinfo")
#define TEMPLATE_VIP		_T("vip_modify")
#define TEMPLATE_MAKE		_T("make_item")
#define TEMPLATE_CHANGET	_T("change_table")

BOOL InitPrintService();
UINT NotifyThread(LPVOID pParam);
BOOL WritePrintTask(JSONVALUE& root,BOOL bNotify);
void PrintMenu(vector<PrintItem>& menu_list, JSONVALUE& root,int nSort);
void PrintItem2Json(PrintItem* pItem,JSONVALUE& retrunItem);
void GetPrinterInfo(CRecordset& rs,JSONVALUE& printTask);