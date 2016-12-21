// ManagerDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "POSClient.h"
#include "ManagerDlg.h"
#include "ReportDlg.h"
#include "OrderDlg.h"
#include "printer.h"
#include "PickUpDlg.h"
#include "FunctionDlg.h"
#include "FloorDlg.h"
#include "LoginDlg.h"
#include "ShiftDlg.h"
#include "NumberInputDlg.h"


// ManagerDlg 对话框

IMPLEMENT_DYNAMIC(ManagerDlg, CPosPage)

ManagerDlg::ManagerDlg(CWnd* pParent /*=NULL*/)
: CPosPage(ManagerDlg::IDD)
{

}

ManagerDlg::~ManagerDlg()
{
}

void ManagerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ManagerDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_PRE, &ManagerDlg::OnBnClickedPrepage)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, &ManagerDlg::OnBnClickedButtonCancel)
	ON_BN_CLICKED(IDC_BUTTON_MINIMIZE, &ManagerDlg::OnBnClickedMinimize)
	ON_BN_CLICKED(IDC_BUTTON_OPEN, &ManagerDlg::OnBnClickedOpenDrawer)
	ON_BN_CLICKED(IDC_BUTTON_REPORT1, &ManagerDlg::OnBnClickedReport1)
	ON_BN_CLICKED(IDC_BUTTON_REPORT2, &ManagerDlg::OnBnClickedReport2)
	ON_BN_CLICKED(IDC_BUTTON_REPORT3, &ManagerDlg::OnBnClickedReport3)
	ON_BN_CLICKED(IDC_BUTTON_REPORT4, &ManagerDlg::OnBnClickedReport4)
	ON_BN_CLICKED(IDC_BUTTON_SHIFT, &ManagerDlg::OnBnClickedShift)
	ON_BN_CLICKED(IDC_BUTTON_DAYEND,&ManagerDlg::OnBnClickedDayend)
	ON_BN_CLICKED(IDC_BUTTON_ABORTPAY,&ManagerDlg::OnBnClickedAbortPay)
	ON_BN_CLICKED(IDC_BUTTON_EDITPRICE,&ManagerDlg::OnBnClickedEditPrice)
	ON_BN_CLICKED(IDC_BUTTON_CASHIN,&ManagerDlg::OnBnClickedCashIn)
	ON_BN_CLICKED(IDC_BUTTON_CASHOUT,&ManagerDlg::OnBnClickedCashOut)
	ON_BN_CLICKED(IDC_BUTTON_SOLDOUT, &FunctionDlg::OnBnClickedSoldout)
	ON_BN_CLICKED(IDC_BUTTON_NEWCUSTOMER, &FunctionDlg::OnBnClickedNewCustomer)
	ON_BN_CLICKED(IDC_BUTTON_RECHARGE, &FunctionDlg::OnBnClickedRecharge)
	ON_BN_CLICKED(IDC_BUTTON_EDITCHK, &FloorDlg::OnBnClickedEditCheck)
	ON_BN_CLICKED(IDC_BUTTON_WEBRECHARGE,&FunctionDlg::OnBnClickedWebRecharge)
	ON_BN_CLICKED(IDC_BUTTON_WEBVIPNEW,&FunctionDlg::OnBnClickedWebNewCustomer)
	ON_BN_CLICKED(IDC_BUTTON_VIEWVIP_WEB,&FunctionDlg::OnBnClickedViewVip)
	ON_BN_CLICKED(IDC_BUTTON_BACKUP,&CLoginDlg::OnBnClickedBackup)
	ON_BN_CLICKED(IDC_BUTTON_EXTERNAL,&ManagerDlg::RunExternal)
	ON_COMMAND_RANGE(IDC_BUTTON_NEXTPAGE,IDC_BUTTON_NEXTPAGE+50,&CPosPage::OnNextPage)
//	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// ManagerDlg 消息处理程序
void ManagerDlg::OnSetActive()
{
	theLang.UpdatePage(this,_T("IDD_7_MANAGER"));
	CPosPage::OnSetActive();
}
BOOL ManagerDlg::OnInitDialog()
{
	CPosPage::InitDialog(_T("Picture\\manager.png"));
	if (m_strTmplate.GetLength()==0)
	{
		m_strTmplate=_T("Page\\IDD_7_MANAGER.ini");
	}
	mProgDlg=new ProgressDlg;
	mProgDlg->Create(IDD_PROGRESS,this);
	mProgDlg->ShowWindow(SW_HIDE);
	m_btnCtrl.GenaratePage2(m_strTmplate,this);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

// void ManagerDlg::OnSize(UINT nType, int cx, int cy)
// {
// 	CPosPage::OnSize(nType, cx, cy);
// }
void ManagerDlg::OnBnClickedPrepage()
{
	theApp.m_pMain->SetActivePage(m_nPrePage,TRUE);
}
void ManagerDlg::OnBnClickedButtonCancel()
{
	theApp.m_pMain->SetActivePage(DLG_LOGIN);
}
void ManagerDlg::OnBnClickedMinimize()
{
	theApp.m_pMain->ShowWindow(SW_MINIMIZE);
}
/************************************************************************
* 函数介绍：打开钱箱
* 输入参数：
* 输出参数：
* 返回值  ：
************************************************************************/
void ManagerDlg::OnBnClickedOpenDrawer()
{
	CString userid;
	int auth=OrderDlg::RequeastAuth(userid,_T("open_drawer"));
	if(auth!=0)
		return;
	if(theApp.m_VCR.IsOpen())
	{
		theApp.m_VCR.Print(_T("OPEN DRAWER\n"));
	}
	CPOSClientApp::CriticalLogs(OPR_UNKNOW,_T("Open Drawer"));
	theApp.OpenDrawer();
}
//销售总结
void ManagerDlg::OnBnClickedReport1()
{
	CReportDlg dlg;
	GetDlgItem(IDC_BUTTON_REPORT1)->GetWindowText(dlg.m_strTitle);
	dlg.m_iType=1;
	dlg.DoModal();
}
//退菜明细
void ManagerDlg::OnBnClickedReport2()
{
	CReportDlg dlg;
	GetDlgItem(IDC_BUTTON_REPORT2)->GetWindowText(dlg.m_strTitle);
	dlg.m_iType=2;
	dlg.DoModal();
}
//菜品销售明细
void ManagerDlg::OnBnClickedReport3()
{
	CReportDlg dlg;
	GetDlgItem(IDC_BUTTON_REPORT3)->GetWindowText(dlg.m_strTitle);
	dlg.m_iType=3;
	dlg.DoModal();
}
/************************************************************************
挂账统计
************************************************************************/
void ManagerDlg::OnBnClickedReport4()
{
	CReportDlg dlg;
	GetDlgItem(IDC_BUTTON_REPORT4)->GetWindowText(dlg.m_strTitle);
	dlg.m_iType=0;
	dlg.m_strQuerry=_T("SELECT customer.card_id AS 卡号,customer_name AS 名称,customer_consume.amount AS 金额,order_head_id AS 账单号 FROM customer_consume,customer")
		_T(" WHERE customer_consume.card_id=customer.card_id AND is_pre_comsume=1 AND time>=\'%s\' AND time<\'%s\' ORDER BY customer.card_id");
	dlg.DoModal();
}
/************************************************************************
* 函数介绍：交接班
* 输入参数：
* 输出参数：
* 返回值  ：
************************************************************************/
void ManagerDlg::OnBnClickedShift()
{
	CString userid;
	int auth=OrderDlg::RequeastAuth(userid,_T("shift"));
	if(auth!=0)
		return;
	LOG4CPLUS_INFO(log_pos,"ManagerDlg::OnBnClickedShift");
	ShiftDlg dlg;
	dlg.DoModal();
}
/************************************************************************
* 函数介绍：日结清机
* 输入参数：
* 输出参数：
* 返回值  ：
************************************************************************/
UINT EODThread(LPVOID pParam)
{
	ManagerDlg *pDlg = (ManagerDlg*)pParam;
	pDlg->DoEndofDay();
	return 0;
}
void ManagerDlg::DoEndofDay()
{
	try
	{
		CRecordset rs(&theDB);
		CString strSQL;
		//重置估清菜品
		theDB.ExecuteSQL(_T("UPDATE bargain_price_item SET bargain_num_cur=bargain_num WHERE is_every_day=1;"));
		theDB.ExecuteSQL(_T("UPDATE bargain_price_item SET bargain_stype=0 WHERE bargain_stype=3;"));
		//重置账单号
		theDB.ExecuteSQL(_T("UPDATE user_workstations SET check_num=0;"));
		//更新起始流水号
		theDB.ExecuteSQL(_T("UPDATE macros SET macros_value=(SELECT MAX(order_head_id)-200 FROM history_order_head) WHERE macros_name='HEAD_BEGIN_ID';"));
		//插入日结历史统计表
		//CStringA m_strSMSTel;
		strSQL.Format(_T("SELECT location_name_2,start_time,restaurant_name FROM restaurant;"));
		rs.Open(CRecordset::forwardOnly,strSQL);
		if (!rs.IsEOF())
		{
			//rs.GetFieldValue((short)0,m_strSMSTel);
			CDBVariant variant;
			rs.GetFieldValue((short)1,variant);
			m_eodTime= CTime(2012,1,1,variant.m_pdate->hour,variant.m_pdate->minute,variant.m_pdate->second);
			rs.GetFieldValue((short)2,m_strResName);

		}
		rs.Close();
		if (macrosInt[_T("USE_SALE_TIME")]==0)
		{//不使用营业开始时间(不跨天营业)
			m_eodTime= CTime(2012,1,1,23,59,59);
		}
		//提取更新前的单数，客人数
		CString strStart,strEnd,strSQL1;
		CTime time_e=GetEndDay();
		CTime time_s=time_e+CTimeSpan(-1,0,0,0);
		long cus_num=0,chk_num=0;
		strSQL1.Format(_T("SELECT SUM(customer_num),SUM(chk_num) FROM history_day_end WHERE day='%s'"),time_s.Format(_T("%Y-%m-%d")));
		rs.Open(CRecordset::forwardOnly,strSQL1);
		if (!rs.IsEOF())
		{
			CString strVal;
			rs.GetFieldValue((short)0,strVal);
			cus_num=_wtol(strVal);
			strVal.Empty();
			rs.GetFieldValue((short)1,strVal);
			chk_num=_wtol(strVal);
		}
		rs.Close();
		//critical_operations只保留100天数据
		CTime time_log=time_s+CTimeSpan(-100,0,0,0);
		strSQL.Format(_T("DELETE FROM critical_operations WHERE operation_time<'%s'"),time_log.Format(_T("%Y-%m-%d")));
		theDB.ExecuteSQL(strSQL);
		//清理预定表
		strSQL.Format(_T("DELETE FROM pre_order WHERE arrived_time<'%s'"),time_log.Format(_T("%Y-%m-%d")));
		theDB.ExecuteSQL(strSQL);
		strSQL.Format(_T("DELETE FROM shift_info WHERE end_time<'%s'"),time_log.Format(_T("%Y-%m-%d")));
		theDB.ExecuteSQL(strSQL);

		//缓存当天时间
		strStart=time_s.Format(_T("%Y-%m-%d"))+m_eodTime.Format(_T(" %H:%M:%S"));
		strEnd=time_e.Format(_T("%Y-%m-%d"))+m_eodTime.Format(_T(" %H:%M:%S"));
		CTime time_c;//当天
		if (macrosInt[_T("USE_SALE_TIME")]==0)
			time_c=time_e;
		else
			time_c=time_s;
		//1.删除当天和前一天的记录
		strSQL.Format(_T("DELETE FROM history_day_end WHERE day='%s'"),time_c.Format(_T("%Y-%m-%d")));
		theDB.ExecuteSQL(strSQL);
		strSQL.Format(_T("DELETE FROM history_payment WHERE day='%s'"),time_c.Format(_T("%Y-%m-%d")));
		theDB.ExecuteSQL(strSQL);
		strSQL.Format(_T("DELETE FROM history_major_group WHERE day='%s'"),time_c.Format(_T("%Y-%m-%d")));
		theDB.ExecuteSQL(strSQL);
		CTime time_y=time_c+CTimeSpan(-1,0,0,0);
		strSQL.Format(_T("DELETE FROM history_day_end WHERE day='%s'"),time_y.Format(_T("%Y-%m-%d")));
		theDB.ExecuteSQL(strSQL);
		strSQL.Format(_T("DELETE FROM history_payment WHERE day='%s'"),time_y.Format(_T("%Y-%m-%d")));
		theDB.ExecuteSQL(strSQL);
		strSQL.Format(_T("DELETE FROM history_major_group WHERE day='%s'"),time_y.Format(_T("%Y-%m-%d")));
		theDB.ExecuteSQL(strSQL);
		//删除后会造成主键ID不连续，影响远程报表，更新AUTO_INCREMENT
		strSQL.Format(_T("ALTER TABLE history_day_end AUTO_INCREMENT=1"));
		theDB.ExecuteSQL(strSQL);
		strSQL.Format(_T("ALTER TABLE history_payment AUTO_INCREMENT=1"));
		theDB.ExecuteSQL(strSQL);
		strSQL.Format(_T("ALTER TABLE history_major_group AUTO_INCREMENT=1"));
		theDB.ExecuteSQL(strSQL);
		
		CString str2;
		theLang.LoadString(str2,IDS_SAVEEODDATA);
		mProgDlg->Step(20,str2);
		//查找并插入2天前的数据
		time_e=time_s+CTimeSpan(-2,0,0,0);
		for (int i=0;i<2;i++)
		{
			mProgDlg->Step(10,_T(""));
			time_s=time_e;
			time_e=time_s+CTimeSpan(1,0,0,0);
			CTime time_c1;
			if (macrosInt[_T("USE_SALE_TIME")]==0)
				time_c1=time_e;
			else
				time_c1=time_s;
			strSQL.Format(_T("SELECT count(*) FROM history_day_end WHERE day='%s'"),time_c1.Format(_T("%Y-%m-%d")));
			rs.Open(CRecordset::forwardOnly,strSQL);
			if (!rs.IsEOF())
			{
				CString strCount;
				rs.GetFieldValue((short)0,strCount);
				if (strCount==_T("0"))
				{
					CString strStart=time_s.Format(_T("%Y-%m-%d"))+m_eodTime.Format(_T(" %H:%M:%S"));
					CString strEnd=time_e.Format(_T("%Y-%m-%d"))+m_eodTime.Format(_T(" %H:%M:%S"));
					CString strDay=time_c1.Format(_T("%Y-%m-%d"));
					InsertDayend(strStart,strEnd,strDay);
				}
			}
			rs.Close();
		}
		//插入当天的数据
		InsertDayend(strStart,strEnd,time_c.Format(_T("%Y-%m-%d")));
		//更新总计点单数
		try{
			rs.Open(CRecordset::forwardOnly,strSQL1);
			if (!rs.IsEOF())
			{
				CString strVal;
				rs.GetFieldValue((short)0,strVal);
				cus_num=_wtol(strVal)-cus_num;
				rs.GetFieldValue((short)1,strVal);
				chk_num=_wtol(strVal)-chk_num;
				strSQL.Format(_T("UPDATE total_statistics SET total_guests=total_guests+(%d),total_checks=total_checks+(%d),dayend_time=now()"),cus_num,chk_num);
				theDB.ExecuteSQL(strSQL);
			}
			rs.Close();
		}
		catch(CDBException* e)
		{
			LOG4CPLUS_ERROR(log_pos,(LPCTSTR)e->m_strError);
			e->Delete();
		}
		CPOSClientApp::CriticalLogs(OPR_DAYEND,_T(""));
		//发送库存数据
		theLang.LoadString(str2,IDS_SENDDEPOS);
		mProgDlg->Step(20,str2);
		SendDepotData();
		mProgDlg->ShowWindow(SW_HIDE);
		POSMessageBox(IDS_EOFSUCCESS);
	}
	catch(CDBException* e)
	{
		LOG4CPLUS_ERROR(log_pos,(LPCTSTR)e->m_strError);
		e->Delete();
	}
	catch(...)
	{
		LOG4CPLUS_ERROR(log_pos,"Catch Exception GetLastError="<<GetLastError());
	}
	mProgDlg->ShowWindow(SW_HIDE);
}
void ManagerDlg::OnBnClickedDayend()
{
	if (m_bTrainingMode)
		return;
	CString userid;
	int auth=OrderDlg::RequeastAuth(userid,_T("end_of_day"));
	if(auth!=0)
		return ;
	if(POSMessageBox(IDS_CONFIRMEOD,MB_YESNO)!=IDOK)
		return;
	LOG4CPLUS_INFO(log_pos,"ManagerDlg::OnBnClickedDayend");
	OpenDatabase();
	CRecordset rs(&theDB);
	CString strSQL;
	//检查是否有未结单
	strSQL.Format(_T("select order_head_id from order_head;"));
	rs.Open( CRecordset::forwardOnly,strSQL);
	if (rs.GetRecordCount()!=0)
	{
		if(POSMessageBox(IDS_HASUNPAYCHK,MB_YESNO)!=IDOK)
			return;
	}
	rs.Close();
	mProgDlg->ShowWindow(SW_SHOW);
	mProgDlg->Reset();
	CString str2;
	theLang.LoadString(str2,IDS_DODAYEND);
	mProgDlg->Step(10,str2);
	AfxBeginThread(EODThread, this);
}
void ManagerDlg::SendDepotData()
{
	USES_CONVERSION;
	try{
		CRecordset rs(&theDB);
		CString strSQL,strVal;
		//获取上次统计的时间
		CInternetSession session;
		session.SetOption(INTERNET_OPTION_CONNECT_TIMEOUT, 1000 * 20);
		session.SetOption(INTERNET_OPTION_CONNECT_BACKOFF, 1000);
		session.SetOption(INTERNET_OPTION_CONNECT_RETRIES, 1);
		strSQL.Format(_T("SELECT ip_addr FROM inventory_setting"));
		rs.Open(CRecordset::forwardOnly,strSQL);
		CString ip_addr,server;
		rs.GetFieldValue(_T("ip_addr"),ip_addr);
		rs.Close();
		ip_addr.Trim();
		if (ip_addr.IsEmpty())
			return;
		server=ip_addr;
		int index=ip_addr.Find(':');
		int port=80;
		if (index>0)
		{
			server=ip_addr.Left(index);
			port=_wtoi(ip_addr.Right(ip_addr.GetLength()-index-1));
		}
		CString strSend,strURL;
		CHttpConnection* pConnection = session.GetHttpConnection(server,(INTERNET_PORT)port);
		strURL.Format(_T("/cost/cost_sync/?guid=%s"),theApp.m_strResId);
		CHttpFile* pFile = pConnection->OpenRequest(CHttpConnection::HTTP_VERB_GET,strURL); 
		pFile->SendRequest();
		DWORD dwRet;
		pFile->QueryInfoStatusCode(dwRet);
		if(dwRet != HTTP_STATUS_OK)
		{
			LOG4CPLUS_ERROR(log_pos,"Connect "<<(LPCTSTR)server<<":"<<port<<" status code="<<dwRet);
			session.Close();
			pFile->Close();
			delete pFile;
			return;
		}

		char buf[512]={0};
		pFile->Read((LPTSTR)buf,sizeof(buf)-1);
		pFile->Close();
		for (int i=strlen(buf)-1;i>=0;i--)
		{
			if(buf[i]=='}')
				break;
			buf[i]=0;
		}
		LOG4CPLUS_DEBUG(log_pos,(LPCTSTR)server<<":"<<port<<" "<<buf);
		JSONVALUE root;
		CString last_time;
		if(root.Parse(buf,JSON_FLAG_LOOSE))
		{
			last_time=root[_T("last_sync")].asCString();
		}
		else
		{//请求失败
			return;
		}
		CTime c_time=CTime::GetCurrentTime();
		CString szHeaders   = L"Content-Type: application/x-www-form-urlencoded;";
		strSend.Format(_T("sale_str={\"guid\":\"%s\",\"datas\":[{\"zdate\":\"%s\",\"details\":["),theApp.m_strResId,c_time.Format(_T("%Y-%m-%d")));
		strSQL.Format(_T("select menu_item_id,nlu,unit,sum(quantity),round(sum(actual_price),2),product_price,item_name1 from history_order_detail,menu_item WHERE ")
			_T(" history_order_detail.menu_item_id=menu_item.item_id")
			_T(" AND order_time>=\'%s\' AND order_time<now() AND is_return_item=0 AND LENGTH(nlu)>0 group by menu_item_id,unit"),last_time);
		rs.Open(CRecordset::forwardOnly,strSQL);
		while (!rs.IsEOF())
		{
			CString str_id,str_nlu,str_unit,str_qty,str_act,str_price,str_name;
			rs.GetFieldValue((short)0,str_id);
			rs.GetFieldValue((short)1,str_nlu);
			rs.GetFieldValue((short)2,str_unit);
			rs.GetFieldValue((short)3,str_qty);
			rs.GetFieldValue((short)4,str_act);
			rs.GetFieldValue((short)5,str_price);
			rs.GetFieldValue((short)6,str_name);
			strSend.AppendFormat(_T("{\"item_id\":%s,\"item_name\":\"%s\",\"nlu\":\"%s\",\"num\":%s,\"unit\":\"%s\",\"total_price\":%s,\"price\":%s}"),
				str_id,URLEncode(str_name),URLEncode(str_nlu),str_qty,URLEncode(str_unit),str_act,str_price);
			rs.MoveNext();
			if (!rs.IsEOF())
			{
				strSend.AppendChar(',');
			}
		}
		rs.Close();
		strSend.Append(_T("]}]}"));
		int wcsLen0 = ::WideCharToMultiByte(CP_UTF8, NULL, strSend, strSend.GetLength(), NULL, 0, NULL, NULL);
		char* sz0 = new char[wcsLen0 + 1];
		memset(sz0,0,wcsLen0+1);
		::WideCharToMultiByte(CP_UTF8, NULL, strSend, -1, sz0, wcsLen0,  NULL, NULL);
		sz0 [wcsLen0] = '\0';
		pFile = pConnection->OpenRequest( CHttpConnection::HTTP_VERB_POST,strURL);
		pFile->SendRequest(szHeaders,szHeaders.GetLength(),(LPVOID)sz0,wcsLen0);
		delete sz0;
		pFile->Close();
	}catch(CDBException* e )
	{
		LOG4CPLUS_ERROR(log_pos,(LPCTSTR)e->m_strError);
		e->Delete();
	}
	catch(...)
	{
		LOG4CPLUS_ERROR(log_pos,"Catch Exception GetLastError="<<GetLastError());
	}
}
void ManagerDlg::InsertDayend(LPCTSTR strStart,LPCTSTR strEnd, LPCTSTR strDay)
{
	try{
		CString strSQL;
		CRecordset rs3(&theDB);

		int rvc_id=1;
		int period_id=1;

		strSQL.Format(_T("SELECT sum(discount_amount),sum(service_amount),sum(should_amount),sum(actual_amount),sum(tax_amount),count(order_head_id)")
			_T(",sum(if(check_id=1,customer_num,0)),count(if(check_id=1,1,NULL)) FROM history_order_head where ")
			_T(" order_end_time>='%s' and order_end_time<='%s'"),strStart,strEnd);
		CString str1,str2,str3sh,str4a,strTax,str5chk,str6cu,str7t,strRet,strSale,insertSql;
		rs3.Open(CRecordset::forwardOnly,strSQL);
		if (!rs3.IsEOF())
		{
			rs3.GetFieldValue((short)0,str1);
			rs3.GetFieldValue((short)1,str2);
			rs3.GetFieldValue((short)2,str3sh);
			rs3.GetFieldValue((short)3,str4a);
			rs3.GetFieldValue((short)4,strTax);
			rs3.GetFieldValue((short)5,str5chk);
			rs3.GetFieldValue((short)6,str6cu);
			rs3.GetFieldValue((short)7,str7t);
		}
		rs3.Close();
		//菜品销售额
		strSQL.Format(_T("select sum(actual_price) from history_order_detail where is_return_item=0 and menu_item_id>0")
			_T(" and order_head_id in(select distinct order_head_id from history_order_head where ")
			_T(" order_end_time>='%s' and order_end_time<='%s')"),strStart,strEnd);
		rs3.Open(CRecordset::forwardOnly,strSQL);
		if (!rs3.IsEOF())
		{
			rs3.GetFieldValue((short)0,strSale);
		}
		if(strSale.IsEmpty())
			strSale=_T("0");
		rs3.Close();
		//查退菜
		strSQL.Format(_T("select sum(abs(actual_price)) from history_order_detail where ((is_return_item=1 OR quantity<0) and menu_item_id>0)")
			_T(" and order_head_id in(select distinct order_head_id from history_order_head where ")
			_T(" order_end_time>='%s' and order_end_time<='%s')"),strStart,strEnd);
		rs3.Open(CRecordset::forwardOnly,strSQL);
		if (!rs3.IsEOF())
		{
			rs3.GetFieldValue((short)0,strRet);
		}
		rs3.Close();
		if(strRet.IsEmpty())
			strRet=_T("0");
		if(str1.IsEmpty())
			str1=_T("0");
		if(str2.IsEmpty())
			str2=_T("0");
		if(str3sh.IsEmpty())
			str3sh=_T("0");
		if(str4a.IsEmpty())
			str4a=_T("0");
		if(str6cu.IsEmpty())
			str6cu=_T("0");

		//插入history_day_end
		insertSql.Format(_T("INSERT INTO history_day_end(day,rvc_center_id,period_id,eidt_time,sales_amount,discount_amount,service_amount")
			_T(",return_amount,should_amount,actual_amount,tax_amount,customer_num,chk_num,table_num) VALUES(DATE('%s'),%d,%d,NOW(),'%s','%s','%s'")
			_T(",'%s','%s','%s','%s','%s','%s','%s')")
			,strDay,rvc_id,period_id,strSale,str1,str2,strRet,str3sh,str4a,strTax,str6cu,str5chk,str7t);
		theDB.ExecuteSQL(insertSql);
		//插入history_payment
		strSQL.Format(_T("select tender_media_id,round(sum(total),2) as total from payment  WHERE order_head_id in")
			_T("(select distinct order_head_id from history_order_head where")
			_T(" order_end_time>='%s' and order_end_time<='%s') group by tender_media_id")
			,strStart,strEnd);
		rs3.Open(CRecordset::forwardOnly,strSQL);
		while (!rs3.IsEOF())
		{
			rs3.GetFieldValue((short)0,str1);
			rs3.GetFieldValue((short)1,str2);
			insertSql.Format(_T("INSERT INTO history_payment VALUES(NULL,DATE('%s'),%d,%d,%s,'%s')"),
				strDay,rvc_id,period_id,str1,str2);
			theDB.ExecuteSQL(insertSql);
			rs3.MoveNext();
		}
		rs3.Close();
		//插入history_major_group
		strSQL.Format(_T("select major_group,sum(actual_price) from history_order_detail left join menu_item on history_order_detail.menu_item_id")
			_T("=menu_item.item_id where menu_item_id>0 and is_return_item=0 and  order_head_id in (select distinct order_head_id from ")
			_T("history_order_head where order_end_time>='%s' and order_end_time<='%s') group by major_group")
			,strStart,strEnd);
		rs3.Open(CRecordset::forwardOnly,strSQL);
		while (!rs3.IsEOF())
		{
			rs3.GetFieldValue((short)0,str1);
			rs3.GetFieldValue((short)1,str2);
			insertSql.Format(_T("INSERT INTO history_major_group VALUES(NULL,DATE('%s'),%d,%d,'%s','%s')"),
				strDay,rvc_id,period_id,str1,str2);
			theDB.ExecuteSQL(insertSql);
			rs3.MoveNext();
		}
		rs3.Close();
	}catch(CDBException* e )
	{
		LOG4CPLUS_ERROR(log_pos,(LPCTSTR)e->m_strError);
		e->Delete();
	}
}
CTime ManagerDlg::GetEndDay()
{
	CTime time_c=CTime::GetCurrentTime();
	if (macrosInt[_T("USE_SALE_TIME")]==0)
	{
		if (time_c.GetHour()<m_eodTime.GetHour())
		{
			CTime time2=CTime(time_c.GetYear(),time_c.GetMonth(),time_c.GetDay(),23,59,59);
			return time2;
		}
	}
	if(m_eodTime.GetHour()>=12)
	{
		return time_c;
	}
	else
	{//跨天营业
		if (time_c.GetHour()<m_eodTime.GetHour())
		{
			return time_c;
		}
		else
		{
			time_c+=CTimeSpan(1,0,0,0);
			return time_c;
		}
	}
}
void ManagerDlg::GetReportString(CString& m_strResult)
{

	CString str2;
	CReportDlg dlg;
	CTime time_e=GetEndDay();
	CTime time_s=time_e+CTimeSpan(-1,0,0,0);
	dlg.m_strStartDate=time_s.Format(_T("%Y-%m-%d"))+m_eodTime.Format(_T(" %H:%M:%S"));
	dlg.m_strEndDate=time_e.Format(_T("%Y-%m-%d"))+m_eodTime.Format(_T(" %H:%M:%S"));	
	theLang.LoadString(str2,IDS_SAILREPORT);
	m_strResult.AppendFormat(_T("%s%s %s\r\n"),m_strResName,str2,time_s.Format(_T("%Y-%m-%d")));
	dlg.ShowReport1(TRUE);
	m_strResult.Append(dlg.m_strResult);
}
/************************************************************************
* 函数介绍：取消结帐
* 输入参数：
* 输出参数：
* 返回值  ：
************************************************************************/
void ManagerDlg::OnBnClickedAbortPay()
{
	CString userid;
	int auth=OrderDlg::RequeastAuth(userid,_T("authority_3"));
	if (auth!=0)
		return;
	theApp.m_pMain->SetActivePage(DLG_VIEWCHK);
}
/************************************************************************
* 函数介绍：菜品改价
* 输入参数：
* 输出参数：
* 返回值  ：
************************************************************************/
void ManagerDlg::OnBnClickedEditPrice()
{
// 	CString userid;
// 	int auth=OrderDlg::RequeastAuth(userid,_T("open_menu_item"));
// 	if (auth!=0)
// 		return;
// 	EditPriceDlg dlg;
// 	dlg.DoModal();
}

void ManagerDlg::OnBnClickedCashIn()
{
	try{
		CString userid;
		WCHAR username[10];
		int auth=OrderDlg::RequeastAuth(userid,_T("open_drawer"),1,username);
		if(auth!=0)
			return;
		NumberInputDlg dlg;
		theLang.LoadString(IDS_INPUTCASHIN,dlg.m_strHint);
		if(dlg.DoModal()==IDCANCEL)
			return;
		double amount=_wtof(dlg.m_strNum);
		if (amount<=0||amount>1000000)
		{
			POSMessageBox(IDS_NUMERROR);
			return;
		}
		theApp.OpenDrawer();
		if(theApp.m_VCR.IsOpen())
		{
			theApp.m_VCR.Print(_T("OPEN DRAWER\n"));
		}
		CString strSQL;
		strSQL.Format(_T("INSERT INTO cashbox_in_out(cashbox_id,type,cash_amount,in_out_time,employee_id,employee_name)")
			_T(" VALUES(%d,0,%f,now(),%s,\'%s\')"),theApp.m_nDeviceId,amount,userid,username);
		theDB.ExecuteSQL(strSQL);
	}catch(...)
	{
		LOG4CPLUS_ERROR(log_pos,"Catch Exception GetLastError="<<GetLastError());
	}
}

void ManagerDlg::OnBnClickedCashOut()
{
	try{
		CString userid;
		WCHAR username[10];
		int auth=OrderDlg::RequeastAuth(userid,_T("open_drawer"),1,username);
		if(auth!=0)
			return;
		NumberInputDlg dlg;
		theLang.LoadString(IDS_INPUTCASHOUT,dlg.m_strHint);
		if(dlg.DoModal()==IDCANCEL)
			return;
		double amount=_wtof(dlg.m_strNum);
		if (amount<=0||amount>1000000)
		{
			POSMessageBox(IDS_NUMERROR);
			return;
		}
		theApp.OpenDrawer();
		if(theApp.m_VCR.IsOpen())
		{
			theApp.m_VCR.Print(_T("OPEN DRAWER\n"));
		}
		CString strSQL;
		strSQL.Format(_T("INSERT INTO cashbox_in_out(cashbox_id,type,cash_amount,in_out_time,employee_id,employee_name)")
			_T(" VALUES(%d,1,-%f,now(),%s,\'%s\')"),theApp.m_nDeviceId,amount,userid,username);
		theDB.ExecuteSQL(strSQL);
	}catch(...)
	{
		LOG4CPLUS_ERROR(log_pos,"Catch Exception GetLastError="<<GetLastError());
	}
}

void ManagerDlg::RunExternal()
{
	ShellExecute(NULL, NULL, _T("external.vbs"), NULL, NULL,SW_HIDE);
}

BOOL ManagerDlg::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message==WM_KEYDOWN)
	{
		switch (pMsg->wParam)
		{
		case VK_HOME:
			OnBnClickedPrepage();
			return TRUE;
		case VK_F1:
			OnBnClickedOpenDrawer();
			return TRUE;
		}
	}
	return CPosPage::PreTranslateMessage(pMsg); 
}