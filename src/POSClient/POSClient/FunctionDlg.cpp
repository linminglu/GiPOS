// FunctionDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "POSClient.h"
#include "FunctionDlg.h"
#include "OrderDlg.h"
#include "NumberInputDlg.h"
#include "StringInputDlg.h"
#include "PickUpDlg.h"
#include "FloorDlg.h"
#include "PayDlg.h"
//#include "CustomerDlg.h"
//#include "CustomerSearchDlg.h"
#include "NotifyKitchenDlg.h"
#include "SelectItemDlg.h"
#include "SoldOutDlg.h"
#include "FloorChooseDlg.h"
#include "WebDlg.h"
#include "WebDlg2.h"
#include "ChangePswDlg.h"

// FunctionDlg 对话框

IMPLEMENT_DYNAMIC(FunctionDlg, CPosPage)

FunctionDlg::FunctionDlg(CWnd* pParent /*=NULL*/)
: CPosPage(FunctionDlg::IDD)
{

}

FunctionDlg::~FunctionDlg()
{
}

void FunctionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_LOG, m_logCtrl);
	DDX_Control(pDX, IDC_STATIC_GUEST, m_guestCtrl);
	DDX_Control(pDX, IDC_STATIC_TABLE, m_tableCtrl);
	DDX_Control(pDX, IDC_STATIC_CHECK, m_checkCtrl);
}


BEGIN_MESSAGE_MAP(FunctionDlg, CDialog)
	ON_WM_SIZE()
	ON_WM_CTLCOLOR()
	//ON_COMMAND_RANGE(IDC_BUTTON_NEXTPAGE,IDC_BUTTON_NEXTPAGE+50,&CPosPage::OnNextPage)
	ON_BN_CLICKED(IDC_BUTTON_SEND, &FunctionDlg::OnBnClickedSendOrder)
	ON_BN_CLICKED(IDC_BUTTON_PRE, &FunctionDlg::OnBnClickedPrepage)
	ON_BN_CLICKED(IDC_BUTTON_TRANSFER, &FunctionDlg::OnBnClickedTransfer)
	ON_BN_CLICKED(IDC_BUTTON_SPLIT,&FunctionDlg::OnBnClickedSplit)
	ON_BN_CLICKED(IDC_BUTTON_COMBINE, &FunctionDlg::OnBnClickedCombine)//合台
	ON_BN_CLICKED(IDC_BUTTON_ADDCHK, &FunctionDlg::OnBnClickedAddCheck)//合单
	ON_BN_CLICKED(IDC_BUTTON_REPORT, &FunctionDlg::OnBnClickedReport)
	ON_BN_CLICKED(IDC_BUTTON_NOTIFYKIT, &FunctionDlg::OnBnClickedNotifyKitchen)
	ON_BN_CLICKED(IDC_BUTTON_COPYCHK, &FunctionDlg::OnBnClickedCopyCheck)
	ON_BN_CLICKED(IDC_BUTTON_SOLDOUT, &FunctionDlg::OnBnClickedSoldout)
	ON_BN_CLICKED(IDC_BUTTON_NEWCUSTOMER, &FunctionDlg::OnBnClickedNewCustomer)
	ON_BN_CLICKED(IDC_BUTTON_RECHARGE, &FunctionDlg::OnBnClickedRecharge)
	ON_BN_CLICKED(IDC_BUTTON_WEBRECHARGE,&FunctionDlg::OnBnClickedWebRecharge)
	ON_BN_CLICKED(IDC_BUTTON_WEBVIPNEW,&FunctionDlg::OnBnClickedWebNewCustomer)
	ON_BN_CLICKED(IDC_BUTTON_VIEWVIP_WEB,&FunctionDlg::OnBnClickedViewVip)
	ON_BN_CLICKED(IDC_BUTTON_LINKTABLE, &FunctionDlg::OnBnClickedLinkTable)
	ON_BN_CLICKED(IDC_BUTTON_CHANGEPSW, &FunctionDlg::OnBnClickedChangePsw)
	ON_BN_CLICKED(IDC_BUTTON_CHKNAME, &PayDlg::OnBnClickedCheckName)
	ON_BN_CLICKED(IDC_BUTTON_EDITCHK, &FloorDlg::OnBnClickedEditCheck)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// FunctionDlg 消息处理程序

BOOL FunctionDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	CImage img;
	if(img.Load(_T("Picture\\function.png"))==S_OK)
	{
		m_bpBackgrd=img.Detach();
	}
	if (m_strTmplate.GetLength()==0)
	{
		if(theApp.m_bQuickService)
			m_strTmplate=_T("Page\\IDD_6_QUICK_FUNCTION.ini");
		else
			m_strTmplate=_T("Page\\IDD_6_FUNCTION.ini");
	}
	m_btnCtrl.GenaratePage2(m_strTmplate,this);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
void FunctionDlg::OnSetActive()
{
	theLang.UpdatePage(this,_T("IDD_6_FUNCTION"));
	CPosPage::OnSetActive();
	OrderDlg::UpdateInfo(this);
}
void FunctionDlg::OnSize(UINT nType, int cx, int cy)
{
	CPosPage::OnSize(nType, cx, cy);
	cx=CreatButton::m_nFullWidth;
	cy=CreatButton::m_nFullHeight;
	int height=(int)(cy*0.04);

	if (m_logCtrl.m_hWnd)
	{
		m_logCtrl.MoveWindow(200,25,150,height);
	}
	if (m_tableCtrl.m_hWnd)
	{
		m_tableCtrl.MoveWindow(350,25,150,height);
	}
	if (m_guestCtrl.m_hWnd)
	{
		m_guestCtrl.MoveWindow(500,25,150,height);
	}
	if (m_checkCtrl.m_hWnd)
	{
		m_checkCtrl.MoveWindow(650,25,200,height);
	}
}

void FunctionDlg::OnBnClickedSendOrder()
{
	try
	{
		//向OrderDlg发送消息
		OrderDlg* pOrder=(OrderDlg*)theApp.m_pMain->GetPage(DLG_ORDER);
		pOrder->OnBnClickedSendOrder();
	}catch(...)
	{
		LOG4CPLUS_ERROR(log_pos,"Catch Exception GetLastError="<<GetLastError());
	}
}
void FunctionDlg::OnBnClickedPrepage()
{
	theApp.m_pMain->SetActivePage(m_nPrePage,TRUE);
}
/************************************************************************
* 函数介绍：锁屏自动注销
* 输入参数：
* 输出参数：
* 返回值  ：
************************************************************************/
BOOL FunctionDlg::LockScreen()
{
	return FALSE;
}
/************************************************************************
* 函数介绍：将当前桌移动到用户输入的桌子里
* 输入参数：
* 输出参数：
* 返回值  ：
************************************************************************/
BOOL FunctionDlg::TransTable()
{
	if (theApp.m_bQuickService)
		return FALSE;
	try
	{
		CString userid;
		int auth=OrderDlg::RequeastAuth(userid,_T("trans_table"));
		if(auth!=0)
			return FALSE;
		CFloorChooseDlg dlg;
		dlg.m_nFilterId=theApp.m_nTableId;
		theLang.LoadString(dlg.m_strPrefix,IDS_INPUTTOTBL);
		if(dlg.DoModal()==IDCANCEL)
			return FALSE;
		int tableId=dlg.m_nTableId;
		if (tableId<=0)
		{
			POSMessageBox(IDS_WRONGTBL);
			return FALSE;
		}
		OpenDatabase();
		CRecordset rs( &theDB);
		CString strSQL,strTbl,strMsg;
		//在order_head中查找输入的桌子是否已开台
		CPOSClientApp* pApp=(CPOSClientApp*) AfxGetApp();
		strSQL.Format(_T("SELECT COUNT(*) FROM order_head WHERE table_id=\'%d\';"),tableId);
		rs.Open(-1,strSQL);
		CString strCount;
		rs.GetFieldValue((short)0,strCount);
		if (strCount!="0")
		{
			POSMessageBox(IDS_INUSING);
			return FALSE;
		}
		if(FloorDlg::GetLock(tableId)==FALSE)
		{
			POSMessageBox(IDS_INUSING);
			return FALSE;
		}
		rs.Close();
		//检查tables是否有这张桌
		strSQL.Format(_T("SELECT * FROM tables LEFT JOIN consumption_limit ON tables.consumption_limit=")
			_T("consumption_limit.consumption_limit_id WHERE table_id=\'%d\';"),tableId);
		if(!rs.Open(-1,strSQL))
		{
			LOG4CPLUS_ERROR(log_pos,"CRecordset Open Failed");
			return FALSE;
		}
		if(rs.IsEOF())
		{
			POSMessageBox(IDS_NOTFINDTBL);
			return FALSE;
		}
		else
		{
			strTbl=pApp->m_strTblName;//保存原有桌名
			rs.GetFieldValue(_T("table_name"),pApp->m_strTblName);
			CDBVariant variant;
			variant.m_iVal=0;
			rs.GetFieldValue(_T("rvc_center_id"),variant);
			pApp->m_nRVC=variant.m_iVal;
			variant.m_iVal=0;
			rs.GetFieldValue(_T("limit_type"),variant);
			pApp->m_nLimitType=variant.m_iVal;
			variant.m_fltVal=0;
			rs.GetFieldValue(_T("limit_amount"),variant);
			pApp->m_fLimitAmount=variant.m_fltVal;
		}
		rs.Close();
		strSQL.Format(_T("CALL trans_table(%d,%d);"),pApp->m_nTableId,tableId);
		theDB.ExecuteSQL(strSQL);
		pApp->m_nTableId=tableId;

		//打印转台信息
		if (macrosInt[_T("PRINT_TRANS")]!=0)
		{
			strSQL.Format(_T("select * from print_devices where  is_print_note=1 group by check_info_print,com_port,printer_name;"));
			rs.Open( CRecordset::snapshot,strSQL);
			while(!rs.IsEOF())
			{
				JSONVALUE printTask;
				GetPrinterInfo(rs,printTask);
				printTask[_T("template")]=TEMPLATE_CHANGET;
				printTask[_T("from_tbl")]=strTbl;
				printTask[_T("to_tbl")]=pApp->m_strTblName;
				COrderPage::FormatTableInfo(printTask);
				WritePrintTask(printTask,TRUE);
				rs.MoveNext();
			}
			rs.Close();
		}
		LOG4CPLUS_INFO(log_pos,"TransTable from ["<<(LPCTSTR)strTbl<<"] to ["<<(LPCTSTR)pApp->m_strTblName<<"]");
		CString str2;
		theLang.LoadString(str2,IDS_TRANSINFO);
		strMsg.Format(str2,strTbl,pApp->m_strTblName);
		CPOSClientApp::CriticalLogs(OPR_TRANS,strMsg);
		POSMessageBox(strMsg);
		return TRUE;
	}
	catch(CDBException* e)
	{
		LOG4CPLUS_ERROR(log_pos,(LPCTSTR)e->m_strError);
		e->Delete();
		return FALSE;
	}
	catch(...)
	{
		LOG4CPLUS_ERROR(log_pos,"Catch Exception GetLastError="<<GetLastError());
		return FALSE;
	}
}
void FunctionDlg::OnBnClickedTransfer()
{
	TransTable();
	OrderDlg::UpdateInfo(this);
}
void FunctionDlg::OnBnClickedSplit()
{
	if (theApp.m_bQuickService)
	{//快餐模式禁用分单
		return;
	}
	CString userid;
	int auth=OrderDlg::RequeastAuth(userid,_T("split_check"));
	if(auth!=0)
		return;
	CPOSClientApp* pApp=(CPOSClientApp*) AfxGetApp();
	pApp->m_pMain->SetActivePage(DLG_SPLIT);
}
/************************************************************************
* 函数介绍：将用户输入的桌子合并到当前桌
* 输入参数：
* 输出参数：
* 返回值  ：
************************************************************************/
void FunctionDlg::CombineTable()
{
	if (theApp.m_bQuickService)
		return;
	try
	{
		CString userid;
		int auth=OrderDlg::RequeastAuth(userid,_T("trans_table"));
		if(auth!=0)
			return;
		CFloorChooseDlg dlg;
		dlg.m_nFilterId=theApp.m_nTableId;
		theLang.LoadString(dlg.m_strPrefix,IDS_COMBINE);
		if(dlg.DoModal()==IDCANCEL)
			return;
		//如果输入的是当前桌号，直接返回
		CPOSClientApp* pApp=(CPOSClientApp*) AfxGetApp();
		int tableid=dlg.m_nTableId;
		if (tableid==pApp->m_nTableId)
			return;
		//检查是否在操作中
		if(FloorDlg::IsFreeLock(tableid)==FALSE)
		{
			POSMessageBox(IDS_INUSING);
			return;
		}
		LOG4CPLUS_INFO(log_pos,"FunctionDlg::CombineTable Begin");
		OpenDatabase();
//		OrderDlg::SaveOrderToDB();
		CString strSQL;
		CRecordset rs(&theDB);
		if (macrosInt[_T("COMBINE_ONE_CHECK")]==1)
		{
			//如果第一张单已结不能合桌
			strSQL.Format(_T("SELECT status FROM order_head WHERE order_head_id=%d AND check_id=1;"),pApp->m_nOrderHeadid);
			rs.Open( CRecordset::forwardOnly,strSQL);
			CString strRet;
			rs.GetFieldValue((short)0,strRet);
			if(strRet==_T("1"))
			{
				POSMessageBox(IDS_NOACTION);
				return;
			}
			rs.Close();
			strSQL.Format(_T("CALL join_table_1(%d,%d,@r);"),tableid,pApp->m_nTableId);
		}
		else
		{
			strSQL.Format(_T("CALL join_table(%d,%d,@r);"),tableid,pApp->m_nTableId);
		}
		theDB.ExecuteSQL(strSQL);
		//查看返回值
		rs.Close();
		strSQL.Format(_T("select @r;"));
		rs.Open( CRecordset::forwardOnly,strSQL);
		if (!rs.IsEOF())
		{
			CString strRet,str2;
			rs.GetFieldValue((short)0,strRet);
			if(strRet==_T("0"))
			{
				rs.Close();
				CString strMsg;
				strMsg.Format(_T("[%d] → [%s]"),tableid,theApp.m_strTblName);
				CPOSClientApp::CriticalLogs(OPR_COMBINE,strMsg);
				strSQL.Format(_T("SELECT * FROM order_head WHERE table_id=\'%d\';"),pApp->m_nTableId);
				if(!rs.Open(-1,strSQL))
				{
					LOG4CPLUS_ERROR(log_pos,"CRecordset Open Failed");
					return;
				}
				CDBVariant variant;
				rs.GetFieldValue(_T("order_head_id"),variant);
				pApp->m_nOrderHeadid=variant.m_lVal;
				rs.GetFieldValue(_T("customer_num"),variant);
				ClearPercentDsicServ(pApp->m_nOrderHeadid);
				pApp->m_nGuests=variant.m_lVal;
				pApp->m_bDirty=TRUE;
				pApp->m_pMain->SetActivePage(DLG_ORDER);
			}
			else if (strRet==_T("-1"))
			{
				theLang.LoadString(str2,IDS_COMBINEFAIL1);
				LOG4CPLUS_ERROR(log_pos,(LPCTSTR)str2);
				POSMessageBox(str2);
			}
			else if (strRet==_T("-2"))
			{
				theLang.LoadString(str2,IDS_COMBINEFAIL2);
				LOG4CPLUS_ERROR(log_pos,(LPCTSTR)str2);
				POSMessageBox(IDS_COMBINEFAIL2);
			}
			else if (strRet==_T("-3"))
			{
				theLang.LoadString(str2,IDS_TBLINOPERATE);
				LOG4CPLUS_ERROR(log_pos,(LPCTSTR)str2);
				POSMessageBox(IDS_TBLINOPERATE);
			}
			else
			{
				theLang.LoadString(str2,IDS_COMBINEFAIL);
				LOG4CPLUS_ERROR(log_pos,(LPCTSTR)str2);
				POSMessageBox(str2);
			}

		}
	}
	catch(CDBException* e)
	{
		LOG4CPLUS_ERROR(log_pos,(LPCTSTR)e->m_strError);
		AfxMessageBox(e->m_strError,MB_ICONEXCLAMATION);
		e->Delete();
		return;
	}
	catch(...)
	{
		LOG4CPLUS_ERROR(log_pos,"Catch Exception GetLastError="<<GetLastError());
	}
	LOG4CPLUS_INFO(log_pos,"FunctionDlg::CombineTable End");
}
void FunctionDlg::OnBnClickedCombine()
{
	CombineTable();
}
/************************************************************************
* 函数介绍：删除多余的整单折扣、服务费(合单/合台后调用)
* 输入参数：
* 输出参数：
* 返回值  ：
************************************************************************/
void FunctionDlg::ClearPercentDsicServ(long order_head_id)
{
	try
	{
		CString strSQL;
		CRecordset rs1(&theDB);
		CRecordset rs(&theDB);
		strSQL.Format(_T("SELECT DISTINCT check_id FROM order_head WHERE order_head_id=%d"),order_head_id);
		if(!rs1.Open( CRecordset::forwardOnly,strSQL))
			return;
		while(!rs1.IsEOF())
		{
			CDBVariant sub_check;
			rs1.GetFieldValue((short)0,sub_check);
			//服务费
			strSQL.Format(_T("SELECT order_detail_id FROM order_detail,service_tip WHERE order_head_id=%d AND check_id=%d")
				_T(" AND menu_item_id=-1 AND discount_id=service_tip_id AND preset=1 AND select_discount=0"),order_head_id,sub_check.m_lVal);
			if(rs.Open( CRecordset::forwardOnly,strSQL))
			{
				int count=0;
				while(!rs.IsEOF())
				{//只保留1个
					if(count!=0)
					{
						CDBVariant variant;
						rs.GetFieldValue((short)0,variant);
						strSQL.Format(_T("DELETE FROM order_detail WHERE order_detail_id=%d"),variant.m_lVal);
						theDB.ExecuteSQL(strSQL);
					}
					rs.MoveNext();
					count++;
				}
			}
			rs.Close();
			//折扣
			strSQL.Format(_T("SELECT order_detail_id FROM order_detail,discount_service WHERE order_head_id=%d AND check_id=%d")
				_T(" AND menu_item_id=-2 AND discount_id=discount_service_id AND preset=1 AND select_discount=0"),order_head_id,sub_check.m_lVal);
			if(rs.Open( CRecordset::forwardOnly,strSQL))
			{
				int count=0;
				while(!rs.IsEOF())
				{//只保留1个
					if(count!=0)
					{
						CDBVariant variant;
						rs.GetFieldValue((short)0,variant);
						strSQL.Format(_T("DELETE FROM order_detail WHERE order_detail_id=%d"),variant.m_lVal);
						theDB.ExecuteSQL(strSQL);
					}
					rs.MoveNext();
					count++;
				}
			}
			rs.Close();
			rs1.MoveNext();
		}
		rs1.Close();
	}
	catch (...)
	{

	}
}
/************************************************************************
* 函数介绍：合单
* 输入参数：
* 输出参数：
* 返回值  ：
************************************************************************/
void FunctionDlg::OnBnClickedAddCheck()
{
	if (theApp.m_bQuickService)
		return;
	try{
		CString userid;
		int auth=OrderDlg::RequeastAuth(userid,_T("trans_table"));
		if(auth!=0)
			return;
		CPOSClientApp* pApp=(CPOSClientApp*) AfxGetApp();
		//选择一个check
		PickUpDlg dlg;
		dlg.pParentWnd=this;
		dlg.m_nFilterTable=pApp->m_nTableId;
		if(dlg.DoModal()==IDCANCEL)
			return;
		if (dlg.m_nIndex<0)
		{
			return;
		}
		//如果输入的是当前桌号，直接返回
		int tableid=dlg.m_Items[dlg.m_nIndex].table_id;
		int checkId=dlg.m_Items[dlg.m_nIndex].check_id;
		if (tableid==pApp->m_nTableId)
			return;
		//检查是否在操作中
		if(FloorDlg::IsFreeLock(tableid)==FALSE)
		{
			POSMessageBox(IDS_TBLINOPERATE);
			return;
		}
		LOG4CPLUS_INFO(log_pos,"FunctionDlg::OnBnClickedAddCheck Begin");
		OpenDatabase();
		CRecordset rs(&theDB);
		CString strSQL;
		if (macrosInt[_T("COMBINE_ONE_CHECK")]==1)
		{
			//如果第一张单已结不能合桌
			strSQL.Format(_T("SELECT status FROM order_head WHERE order_head_id=%d AND check_id=1;"),pApp->m_nOrderHeadid);
			rs.Open( CRecordset::forwardOnly,strSQL);
			CString strRet;
			rs.GetFieldValue((short)0,strRet);
			if(strRet==_T("1"))
			{
				POSMessageBox(IDS_NOACTION);
				return;
			}
			rs.Close();
			strSQL.Format(_T("call move_check_1(%d,%d,%d,@r);"),tableid,checkId,pApp->m_nTableId);
		}
		else
		{
			strSQL.Format(_T("call move_check(%d,%d,%d,@r);"),tableid,checkId,pApp->m_nTableId);
		}
		theDB.ExecuteSQL(strSQL);
		//查看返回值
		rs.Close();
		strSQL.Format(_T("select @r;"));
		rs.Open( CRecordset::forwardOnly,strSQL);
		if (!rs.IsEOF())
		{
			CString strRet,str2;
			rs.GetFieldValue((short)0,strRet);
			if(strRet==_T("0"))
			{
				rs.Close();
				CString strMsg;
				strMsg.Format(_T("[%d/%d] → [%s]"),tableid,checkId,theApp.m_strTblName);
				CPOSClientApp::CriticalLogs(OPR_COMBINE,strMsg);
				strSQL.Format(_T("SELECT * FROM order_head WHERE table_id=\'%d\';"),pApp->m_nTableId);
				if(!rs.Open(-1,strSQL))
				{
					LOG4CPLUS_ERROR(log_pos,"CRecordset Open Failed");
					return;
				}
				CDBVariant variant;
				rs.GetFieldValue(_T("order_head_id"),variant);
				pApp->m_nOrderHeadid=variant.m_lVal;
				rs.GetFieldValue(_T("customer_num"),variant);
				pApp->m_nGuests=variant.m_lVal;
				ClearPercentDsicServ(pApp->m_nOrderHeadid);
				pApp->m_bDirty=TRUE;
				pApp->m_pMain->SetActivePage(DLG_ORDER);
			}
			else if (strRet==_T("-1"))
			{
				theLang.LoadString(str2,IDS_COMBINEFAIL1);
				LOG4CPLUS_ERROR(log_pos,(LPCTSTR)str2);
				POSMessageBox(str2);
			}
			else if (strRet==_T("-2"))
			{
				theLang.LoadString(str2,IDS_NOTFINDTBL);
				LOG4CPLUS_ERROR(log_pos,(LPCTSTR)str2);
				POSMessageBox(IDS_NOTFINDTBL);
			}
			else if (strRet==_T("-3"))
			{
				theLang.LoadString(str2,IDS_TBLINOPERATE);
				LOG4CPLUS_ERROR(log_pos,(LPCTSTR)str2);
				POSMessageBox(IDS_TBLINOPERATE);
			}
			else
			{
				theLang.LoadString(str2,IDS_COMBINEFAIL);
				LOG4CPLUS_ERROR(log_pos,(LPCTSTR)str2);
				POSMessageBox(str2);
			}
		}
		else
			LOG4CPLUS_ERROR(log_pos,"rs.IsEOF()==TRUE");
	}
	catch(CDBException* e)
	{
		LOG4CPLUS_ERROR(log_pos,(LPCTSTR)e->m_strError);
		AfxMessageBox(e->m_strError,MB_ICONEXCLAMATION);
		e->Delete();
		return;
	}
	catch(...)
	{
		LOG4CPLUS_ERROR(log_pos,"Catch Exception GetLastError="<<GetLastError());
	}
	//LOG4CPLUS_INFO(log_pos,"FunctionDlg::OnBnClickedAddCheck End");
}

void FunctionDlg::OnBnClickedReport()
{
}

/*本地会员（废弃）*/
void FunctionDlg::OnBnClickedRecharge()
{
	return;
}

/************************************************************************
* 函数介绍：通知厨房，叫起、等叫等信息
* 输入参数：
* 输出参数：
* 返回值  ：
************************************************************************/
void FunctionDlg::OnBnClickedNotifyKitchen()
{
	CPOSClientApp* pApp=(CPOSClientApp*)AfxGetApp();
	NotifyKitchenDlg dlg;
	CString str2;
	theLang.LoadString(str2,IDS_SENDFROM);
	dlg.m_strTtitle.AppendFormat(str2,pApp->m_strTblName);
	dlg.DoModal();
}
/************************************************************************
* 函数介绍：复制其他单的菜品
* 输入参数：
* 输出参数：
* 返回值  ：
************************************************************************/
void FunctionDlg::OnBnClickedCopyCheck()
{
	if (theApp.m_bQuickService)
		return;
	CPOSClientApp* pApp=(CPOSClientApp*) AfxGetApp();
	//选择一个check
	PickUpDlg dlg;
	dlg.pParentWnd=this;
	dlg.m_nFilterTable=pApp->m_nTableId;
	if(dlg.DoModal()==IDCANCEL)
		return;
	if (dlg.m_nIndex<0)
	{
		return;
	}
	long headid=dlg.m_Items[dlg.m_nIndex].order_head_id;
	int checkId=dlg.m_Items[dlg.m_nIndex].check_id;

	//从数据库中查询账单信息
	SelectItemDlg sdlg;
	sdlg.pParentWnd=this;
	sdlg.m_nCheckID=checkId;
	sdlg.m_nType=1;
	CTypedPtrList<CPtrList,OrderDetail *> orderList;
	CString strSQL;
	strSQL.Format(_T("SELECT * FROM order_detail LEFT JOIN menu_item ON menu_item_id=item_id WHERE order_head_id=%d AND check_id=%d AND menu_item_id>0 AND is_return_item=0;")
		,headid,checkId);
	FloorDlg::GetOrderDetail(strSQL,&orderList);
	sdlg.m_pOrderList=&orderList;
	theLang.LoadString(sdlg.m_strHint,IDS_CHOOSEITEMCOPY);
	if(sdlg.DoModal()==IDOK)
	{//添加到当前的菜品列表
		pApp->m_bDirty=FALSE;
		strSQL.Format(_T("SELECT check_id FROM order_head WHERE table_id=\'%d\' AND status=0;")
			,pApp->m_nTableId);
		CRecordset rs(&theDB);
		if(!rs.Open(-1,strSQL))
		{
			LOG4CPLUS_ERROR(log_pos,"CRecordset Open Failed");
			return;
		}
		if (!rs.IsEOF())
		{
			CDBVariant var;
			rs.GetFieldValue(_T("check_id"),var);
			while(!orderList.IsEmpty())
			{
				OrderDetail* item=orderList.GetHead();
				item->n_saved=0;
				item->n_checkID=var.m_lVal;
				orderList.RemoveHead();
				pApp->m_orderList.AddTail(item);
			}
		}
	}

	while(!orderList.IsEmpty())
	{
		OrderDetail* item=orderList.GetTail();
		orderList.RemoveTail();
		delete item;
	}

}
/************************************************************************
* 函数介绍：设置估清
* 输入参数：
* 输出参数：
* 返回值  ：
************************************************************************/
void FunctionDlg::OnBnClickedSoldout()
{
	SoldOutDlg* pDlg=new SoldOutDlg();
	pDlg->m_hParent=this;
	pDlg->Create(IDD_SOLDOUT,theApp.m_pMain);
	pDlg->ShowWindow(SW_SHOW);
	pDlg->SetFocus();
}
/*本地会员（废弃）*/
void FunctionDlg::OnBnClickedNewCustomer()
{
	return;
}

void FunctionDlg::OnBnClickedWebNewCustomer()
{
	if(m_bTrainingMode){
		POSMessageBox(IDS_TRAINMODE);
		return;
	}
	try{
		OpenDatabase();
		CString userid;
		int auth=OrderDlg::RequeastAuth(userid,_T("edit_customer"));
		if(auth!=0)
			return;
		CString strSQL;
		CRecordset rs(&theDB);
		strSQL.Format(_T("select * from vip_setting"));
		rs.Open( CRecordset::forwardOnly,strSQL);
		if (!rs.IsEOF())
		{
			CString ip_addr,str_url;
			rs.GetFieldValue(_T("ip_addr"),ip_addr);
			//rs.GetFieldValue(_T("res_id"),res_id);
			if (ip_addr.Find(_T("http"))==0)
				str_url=ip_addr;
			else
				str_url.Format(_T("http://%s"),ip_addr);
			str_url.AppendFormat(_T("/orgs/storedvaluecard_open_card//?source=agile&username=%s&user_id=%s&guid=%s&machine_id=%s")
								,URLEncode(theApp.m_strUserName),theApp.m_strUserID,theApp.m_strResId,URLEncode(theApp.m_strHostName));
			if(theLang.m_strLang==_T("Default")||theLang.m_strLang==_T("简体中文"))
				str_url.AppendFormat(_T("&lang=zh-CN"));
			else if(theLang.m_strLang==_T("繁體中文"))
				str_url.AppendFormat(_T("&lang=zh-TW"));
			else
				str_url.AppendFormat(_T("&lang=en"));

			if(theApp.m_bUseIE)
			{
				CWebDlg dlg;
				dlg.m_strCurrentUrl=str_url;
				dlg.DoModal();
			}
			else
			{
				CWebDlg2 dlg;
				dlg.m_strCurrentUrl=str_url;
				dlg.DoModal();
			}
		}
	}catch(...)
	{
	}
}
void FunctionDlg::OnBnClickedWebRecharge()
{
	if(m_bTrainingMode){
		POSMessageBox(IDS_TRAINMODE);
		return;
	}
	try{
		OpenDatabase();
		CString userid;
		int auth=OrderDlg::RequeastAuth(userid,_T("edit_customer"));
		if(auth!=0)
			return;
		CString strSQL;
		CRecordset rs(&theDB);
		strSQL.Format(_T("select * from vip_setting"));
		rs.Open( CRecordset::forwardOnly,strSQL);
		if (!rs.IsEOF())
		{
			CString ip_addr,str_url;
			rs.GetFieldValue(_T("ip_addr"),ip_addr);
			//rs.GetFieldValue(_T("res_id"),res_id);
			if (ip_addr.Find(_T("http"))==0)
				str_url=ip_addr;
			else
				str_url.Format(_T("http://%s"),ip_addr);
			str_url.AppendFormat(_T("/orgs/storedvaluecard_recharge_card//?source=agile&username=%s&user_id=%s&guid=%s&machine_id=%s")
								,URLEncode(theApp.m_strUserName),theApp.m_strUserID,theApp.m_strResId,URLEncode(theApp.m_strHostName));
			if(theLang.m_strLang==_T("Default")||theLang.m_strLang==_T("简体中文"))
				str_url.AppendFormat(_T("&lang=zh-CN"));
			else if(theLang.m_strLang==_T("繁體中文"))
				str_url.AppendFormat(_T("&lang=zh-TW"));
			else
				str_url.AppendFormat(_T("&lang=en"));

			if(theApp.m_bUseIE)
			{
				CWebDlg dlg;
				dlg.m_strCurrentUrl=str_url;
				dlg.DoModal();
			}
			else
			{
				CWebDlg2 dlg;
				dlg.m_strCurrentUrl=str_url;
				dlg.DoModal();
			}
		}
	}catch(...)
	{
	}
}
void FunctionDlg::OnBnClickedViewVip()
{
	if(m_bTrainingMode){
		POSMessageBox(IDS_TRAINMODE);
		return;
	}
	try{
		OpenDatabase();
		CString strSQL;
		CRecordset rs(&theDB);
		strSQL.Format(_T("select * from vip_setting"));
		rs.Open( CRecordset::forwardOnly,strSQL);
		if (!rs.IsEOF())
		{
			CString ip_addr,str_url;
			rs.GetFieldValue(_T("ip_addr"),ip_addr);
			//rs.GetFieldValue(_T("res_id"),res_id);
			if (ip_addr.Find(_T("http"))==0)
				str_url=ip_addr;
			else
				str_url.Format(_T("http://%s"),ip_addr);
			str_url.AppendFormat(_T("/orgs/report_card_info//?auto_query=1&source=agile&username=%s&user_id=%s&guid=%s&machine_id=%s")
				,URLEncode(theApp.m_strUserName),theApp.m_strUserID,theApp.m_strResId,URLEncode(theApp.m_strHostName));
			if(theLang.m_strLang==_T("Default")||theLang.m_strLang==_T("简体中文"))
				str_url.AppendFormat(_T("&lang=zh-CN"));
			else if(theLang.m_strLang==_T("繁體中文"))
				str_url.AppendFormat(_T("&lang=zh-TW"));
			else
				str_url.AppendFormat(_T("&lang=en"));
			if(theApp.m_bUseIE)
			{
				CWebDlg dlg;
				dlg.m_strCurrentUrl=str_url;
				dlg.DoModal();
			}
			else
			{
				CWebDlg2 dlg;
				dlg.m_strCurrentUrl=str_url;
				dlg.DoModal();
			}
		}
	}catch(...)
	{
	}
}
void FunctionDlg::OnBnClickedLinkTable()
{
	if (theApp.m_bQuickService)
		return;
	CString strSQL;
	strSQL.Format(_T("SELECT DISTINCT table_id FROM order_head WHERE party_id=%d AND table_id<>%d"),theApp.m_nPartyId,theApp.m_nTableId);
	CRecordset rs( &theDB);
	CDBVariant variant;
	std::vector<int> tableList;
	if(!rs.Open(CRecordset::forwardOnly,strSQL))
		return;
	while(!rs.IsEOF())
	{
		rs.GetFieldValue(_T("table_id"),variant);
		tableList.push_back(variant.m_lVal);
		rs.MoveNext();
	}
	rs.Close();
	//选择桌子
	CFloorChooseDlg fDlg;
	fDlg.m_tableList=tableList;
	fDlg.m_bMultiSelect=TRUE;
	fDlg.m_nFilterId=theApp.m_nTableId;
	CString str2;
	theLang.LoadString(str2,IDS_LINKTABLE);
	fDlg.m_strTitle.Format(str2,theApp.m_strTblName);
	if(fDlg.DoModal()==IDCANCEL)
		return;
	//去除原有的关联
	if(tableList.size()>0)
	{
		strSQL.Format(_T("UPDATE order_head SET party_id=NULL WHERE table_id IN("));
		for (int i=0;i<tableList.size();i++)
		{
			strSQL.AppendFormat(_T("%d,"),tableList[i]);
		}
		strSQL.AppendFormat(_T("%d)"),theApp.m_nTableId);
		theDB.ExecuteSQL(strSQL);
	}
	//未开台的桌自动开台
	for (int i=0;i<fDlg.m_tableList.size();i++)
	{
		strSQL.Format(_T("SELECT * FROM order_head WHERE table_id=%d"),fDlg.m_tableList[i]);
		rs.Open(CRecordset::forwardOnly,strSQL);
		if (!rs.IsEOF())
		{
			rs.Close();
			continue;
		}
		rs.Close();
		int nChkNum=0;
		//将开单信息存入数据库中
		CDBVariant variant;
		strSQL.Format(_T("CALL update_checknum(%d);"),theApp.m_nDeviceId);
		theDB.ExecuteSQL(strSQL);
		strSQL.Format(_T("SELECT check_num FROM user_workstations WHERE workstations_id=%d;"),theApp.m_nDeviceId);
		rs.Open( CRecordset::forwardOnly,strSQL);
		if (!rs.IsEOF()) 
		{
			rs.GetFieldValue((short)0,variant);
			nChkNum=variant.m_lVal;
		}
		rs.Close();
		strSQL.Format(_T("SELECT * FROM tables WHERE table_id=\'%d\';"),fDlg.m_tableList[i]);
		rs.Open(CRecordset::forwardOnly,strSQL);
		if (!rs.IsEOF()) 
		{
			CString tblName;
			rs.GetFieldValue(_T("table_name"),tblName);
			//对表加锁，保证原子性
			strSQL.Format(_T("lock table history_order_head READ ,order_head WRITE,order_head AS T2 READ,history_order_head AS T3 READ;"));
			theDB.ExecuteSQL(strSQL);
			long head_id=FloorDlg::GetHeadID(macrosInt[_T("HEAD_BEGIN_ID")]);
			strSQL.Format(_T("INSERT INTO order_head(order_head_id,check_number,table_id,table_name,check_id,customer_num,order_start_time,eat_type")
				_T(",open_employee_id,open_employee_name,pos_device_id,pos_name,rvc_center_id,rvc_center_name)")
				_T(" VALUES(%d,%d,\'%d\',\'%s\',1,1,NOW(),0,\'%s\',\'%s\',\'%d\',\'%s\',\'%d\',\'%s\')")
				,head_id,nChkNum,fDlg.m_tableList[i],tblName,theApp.m_strUserID
				,theApp.m_strUserName,theApp.m_nDeviceId,theApp.m_strDeviceName,theApp.m_nRVC,theApp.m_strRVC);
			theDB.ExecuteSQL(strSQL);
			//解锁
			strSQL.Format(_T("unlock tables;"));
			theDB.ExecuteSQL(strSQL);
			strSQL.Format(_T("UPDATE tables SET table_status=2 WHERE table_id=%d;"),fDlg.m_tableList[i]);
			theDB.ExecuteSQL(strSQL);
		}
		rs.Close();
	}
	//新建关联
	strSQL.Format(_T("SELECT MAX(party_id)+1 FROM order_head;"));
	if(!rs.Open(CRecordset::forwardOnly,strSQL))
		return;
	CString strValue;
	rs.GetFieldValue(short(0),strValue);
	if (strValue.IsEmpty())
	{
		strValue.Format(_T("1"));
	}
	theApp.m_nPartyId=_wtol(strValue);
	if(fDlg.m_tableList.size()>0)
	{
		strSQL.Format(_T("UPDATE order_head SET party_id=%s WHERE table_id IN("),strValue);
		for (int i=0;i<fDlg.m_tableList.size();i++)
		{
			strSQL.AppendFormat(_T("%d,"),fDlg.m_tableList[i]);
		}
		strSQL.AppendFormat(_T("%d)"),theApp.m_nTableId);
		theDB.ExecuteSQL(strSQL);
	}
}
void FunctionDlg::OnBnClickedChangePsw()
{
	ChangePswDlg dlg;
	dlg.DoModal();
}
HBRUSH FunctionDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	if(nCtlColor==CTLCOLOR_STATIC)
	{
		pDC->SetTextColor(m_dTextColor);
		pDC->SetBkMode(TRANSPARENT);
		return (HBRUSH)::GetStockObject(NULL_BRUSH); //返回此画刷可以使静态文本透明
	}
	return hbr;
}
BOOL FunctionDlg::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message==WM_KEYDOWN)
	{
		switch (pMsg->wParam)
		{
		case VK_HOME:

			OnBnClickedPrepage();
			return TRUE;
		}
	}
	return CPosPage::PreTranslateMessage(pMsg); 
}