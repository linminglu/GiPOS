// ShiftDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "POSClient.h"
#include "ShiftDlg.h"
#include "ReportDlg.h"
#include <afxinet.h>


// ShiftDlg 对话框

IMPLEMENT_DYNAMIC(ShiftDlg, CDialog)

ShiftDlg::ShiftDlg(CWnd* pParent /*=NULL*/)
	: CDialog(ShiftDlg::IDD, pParent)
{
	m_bReadonly=FALSE;
}

ShiftDlg::~ShiftDlg()
{
}

void ShiftDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDOK, m_btOK);
	DDX_Control(pDX, IDCANCEL, m_btCancel);
	DDX_Control(pDX, IDC_EDIT1, m_Edit);
}


BEGIN_MESSAGE_MAP(ShiftDlg, CDialog)
	ON_BN_CLICKED(IDOK, &ShiftDlg::OnBnClickedOk)
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
END_MESSAGE_MAP()

// ShiftDlg 消息处理程序

BOOL ShiftDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_btOK.SetImage(_T("Picture\\bt_ok.png"));
	m_btCancel.SetImage(_T("Picture\\bt_cancel.png"));
	if (!theLang.m_bDefaultLang)
	{
		CWnd* pCtrl=GetDlgItem(IDC_STATIC1);
		theLang.TranslateDlgItem(pCtrl,IDS_LASTSHIFT);
		pCtrl=GetDlgItem(IDC_STATIC3);
		theLang.TranslateDlgItem(pCtrl,IDS_SHIFTTOTAL);
		pCtrl=GetDlgItem(IDOK);
		theLang.TranslateDlgItem(pCtrl,IDS_OK);
		pCtrl=GetDlgItem(IDCANCEL);
		theLang.TranslateDlgItem(pCtrl,IDS_CANCEL);
	}
	m_btOK.SetTextColor(DEFALUT_TXT_COLOR);
	m_btCancel.SetTextColor(DEFALUT_TXT_COLOR);

	HFONT hFont = (HFONT)::GetStockObject(SYSTEM_FIXED_FONT);
	CFont *pFont = CFont::FromHandle(hFont);
	GetDlgItem(IDC_EDIT1)->SetFont(pFont);
	OpenDatabase();
	if(theApp.m_nShiftType<=0)
	{
		GetShiftInfoByPos();
	}
	else 
	{
		int nAllCheck=0;
		theApp.m_privilegeMap.Lookup(_T("authority_4"),nAllCheck);
		if(nAllCheck==0)
		{//普通收银
			GetShiftInfoByUser(theApp.m_strUserID);
		}
		else
		{//经理,查看所有员工交班报表
			m_bReadonly=TRUE;
			ListAllShiftInfo();
		}
	}
	m_Edit.SetWindowText(m_strMsg);
	return TRUE;  // return TRUE unless you set the focus to a control
}
void ShiftDlg::ListAllShiftInfo()
{
	CRecordset rs( &theDB);
	CString strSQL;
	CString strVal,str2;
	CDBVariant variant;
	m_strMsg.Empty();
	//更新时间
	CTime time_now=CTime::GetCurrentTime();
	strSQL.Format(_T("SELECT now(),end_date FROM employee WHERE employee_id=%s"),theApp.m_strUserID);
	rs.Open( CRecordset::forwardOnly,strSQL);
	if (!rs.IsEOF())
	{
		rs.GetFieldValue((short)0,strVal);
		str_to.Format(_T("%s"),strVal);
		rs.GetFieldValue((short)1,strVal);
		str_from.Format(_T("%s"),strVal);
		if(str_from.IsEmpty())
		{//第一次空白
			str_from=time_now.Format(_T("%Y-%m-%d %H:%M:%S"));
		}
	}
	rs.Close();
	GetDlgItem(IDC_STATIC2)->SetWindowText(str_from);
	//查出最近24小时内的交班
	strSQL.Format(_T("SELECT s1.* FROM shift_info s1 INNER JOIN")
		_T("(SELECT max(shift_id) AS id FROM shift_info WHERE type=1 AND TIMESTAMPDIFF(HOUR,NOW(),end_time)<24 GROUP BY employee_id) s2 ON s1.shift_id =s2.id"));
	rs.Open(CRecordset::forwardOnly,strSQL);
	BOOL bFirst=TRUE;
	while(!rs.IsEOF())
	{
		m_strMsg.Append(_T("\r\n"));
		rs.GetFieldValue(_T("employee_name"),strVal);
		m_strMsg.AppendFormat(_T("%s:\r\n"),strVal);
		rs.GetFieldValue(_T("detail"),strVal);
		JSONVALUE root;
		CString strName;
		if(root.Parse((LPCTSTR)strVal,JSON_FLAG_LOOSE))
		{
			JSONVALUE arrayItems=root[_T("pays")];
			for (int j=0;j<arrayItems.Size();j++)
			{
				JSONVALUE jItem;
				arrayItems.At(j,jItem);
				strName.Format(_T("  +%s"),jItem[_T("k")].asCString());
				m_strMsg.Append(CReportDlg::FormatString(strName,18,FALSE));
				m_strMsg.Append(CReportDlg::FormatString(jItem[_T("v")].asDouble(),8));
				m_strMsg.Append(_T("\r\n"));
			}
			//小费
			theLang.LoadString(IDS_TIPS,str2);
			strName.Format(_T("  -%s"),str2);
			m_strMsg.Append(CReportDlg::FormatString(strName,18,FALSE));
			m_strMsg.Append(CReportDlg::FormatString(root[_T("tip")].asDouble(),8));
			m_strMsg.Append(_T("\r\n"));
		}
		rs.MoveNext();
	}
	rs.Close();
}
void ShiftDlg::GetShiftInfoByUser(LPCTSTR strUser)
{
	try
	{
		CRecordset rs( &theDB);
		CString strSQL;
		CString strVal,str2;
		CDBVariant variant;
		m_strMsg.Empty();
		CPOSClientApp* pApp=(CPOSClientApp*)AfxGetApp();
		//更新时间
		CTime time_now=CTime::GetCurrentTime();
		strSQL.Format(_T("SELECT now(),end_date FROM employee WHERE employee_id=%s"),strUser);
		rs.Open( CRecordset::forwardOnly,strSQL);
		if (!rs.IsEOF())
		{
			rs.GetFieldValue((short)0,strVal);
			str_to.Format(_T("%s"),strVal);
			rs.GetFieldValue((short)1,strVal);
			str_from.Format(_T("%s"),strVal);
			if(str_from.IsEmpty())
			{//第一次空白
				str_from=time_now.Format(_T("%Y-%m-%d %H:%M:%S"));
			}
		}
		rs.Close();
		GetDlgItem(IDC_STATIC2)->SetWindowText(str_from);
		//存入的现金
		BOOL bSet=FALSE;
		double total=0;
		strSQL.Format(_T("SELECT SUM(cash_amount) FROM cashbox_in_out WHERE employee_id=%s AND in_out_time>=\'%s\'")
			_T(" AND in_out_time<\'%s\' AND cash_amount>0")
			,strUser,str_from,str_to);
		rs.Open( CRecordset::forwardOnly,strSQL);
		if (!rs.IsEOF())
		{
			rs.GetFieldValue((short)0,strVal);
			double fvalue=_wtof(strVal);
			if(fvalue>0)
			{
				total+=fvalue;
				theLang.LoadString(str2,IDS_CASHIN);
				m_strMsg.Append(CReportDlg::FormatString(str2,18,FALSE));
				m_strMsg.Append(CReportDlg::FormatString(fvalue,8));
				m_strMsg.Append(_T("\r\n"));
				bSet=TRUE;
			}
		}
		rs.Close();
		//取出的现金
		strSQL.Format(_T("SELECT SUM(cash_amount) FROM cashbox_in_out WHERE employee_id=%s AND in_out_time>=\'%s\'")
			_T(" AND in_out_time<\'%s\' AND cash_amount<0")
			,strUser,str_from,str_to);
		rs.Open( CRecordset::forwardOnly,strSQL);
		if (!rs.IsEOF())
		{
			rs.GetFieldValue((short)0,strVal);
			double fvalue=_wtof(strVal);
			if(fvalue<-0.001)
			{
				total+=fvalue;
				theLang.LoadString(str2,IDS_CASHOUT);
				m_strMsg.Append(CReportDlg::FormatString(str2,18,FALSE));
				double fvalue=_wtof(strVal);
				m_strMsg.Append(CReportDlg::FormatString(fvalue,8));
				m_strMsg.Append(_T("\r\n"));
				bSet=TRUE;
			}
		}
		rs.Close();
		if(bSet)
			m_strMsg.Append(_T("--------------------------\r\n"));
		//1.总小费金额。按买单员工统计
		double total_tips=0;
		strSQL.Format(_T("select round(sum(tips_amount),2) from history_order_head,payment where")
			_T(" order_end_time>=\'%s\' AND order_end_time<=\'%s\' AND history_order_head.order_head_id=payment.order_head_id AND history_order_head.check_id=payment.check_id AND payment.employee_id=%s")
			,str_from,str_to,strUser);
		rs.Open( CRecordset::forwardOnly,strSQL);
		if (!rs.IsEOF())
		{
			rs.GetFieldValue((short)0,strVal);
			total_tips=_wtof(strVal);
		}
		rs.Close();
		//2.银行卡小费。
		double card_tips=0;
		strSQL.Format(_T("select round(sum(actual_price),2) from history_order_detail,history_order_head,payment where menu_item_id=-6")
			_T(" AND history_order_detail.order_head_id=history_order_head.order_head_id AND history_order_head.order_head_id=payment.order_head_id")
			_T(" AND history_order_detail.check_id=payment.check_id AND history_order_head.check_id=payment.check_id AND payment.employee_id=%s AND order_end_time>=\'%s\' AND order_end_time<=\'%s\'"),
			strUser,str_from,str_to);
		rs.Open( CRecordset::forwardOnly,strSQL);
		if (!rs.IsEOF())
		{
			rs.GetFieldValue((short)0,strVal);
			card_tips=_wtof(strVal);
		}
		rs.Close();
		//现金小费未计入支付方式，调整显示
		double cash_tips=total_tips-card_tips;
		JSONVALUE arrayItems(JSONTYPE::JT_ARRAY);
		//支付方式
		strSQL.Format(_T("{CALL c_pay_style_emp(\'%s\',\'%s\',%s)}"),str_from,str_to,strUser);
		rs.Open(CRecordset::forwardOnly,strSQL);
		BOOL bFirst=TRUE;
		while(!rs.IsEOF())
		{
			rs.GetFieldValue((short)0,str2);
			rs.GetFieldValue(1,strVal);
			double fvalue=_wtof(strVal);
			if(bFirst)
			{
				bFirst=FALSE;
				fvalue+=cash_tips;
			}
			total+=fvalue;
			if(fvalue>0)
			{
				JSONVALUE item;
				item[_T("k")]=str2;
				item[_T("v")]=fvalue;
				arrayItems.Push(item);
			}
			m_strMsg.Append(CReportDlg::FormatString(str2,18,FALSE));
			m_strMsg.Append(CReportDlg::FormatString(fvalue,8));
			m_strMsg.Append(_T("\r\n"));
			rs.MoveNext();
		}
		rs.Close();
		payinfo[_T("pays")]=arrayItems;
		m_strMsg.Append(_T("--------------------------\r\n"));
		//显示小费
		theLang.LoadString(str2,IDS_TIPS);
		m_strMsg.Append(CReportDlg::FormatString(str2,18,FALSE));
		m_strMsg.Append(CReportDlg::FormatString(total_tips,8));
		m_strMsg.Append(_T("\r\n"));
		payinfo[_T("tip")]=total_tips;
		//不支持WEB 会员充值
		
		//未结账单
		strSQL.Format(_T("select count(*),round(sum(should_amount),2) from order_head where status=0 AND open_employee_id=%s"),strUser);
		rs.Open( CRecordset::forwardOnly,strSQL);
		if (!rs.IsEOF())
		{
			rs.GetFieldValue((short)0,strVal);
			theLang.LoadString(str2,IDS_UNPAYNUMS);
			m_strMsg.Append(CReportDlg::FormatString(str2,18,FALSE));
			int dvalue=_wtoi(strVal);
			m_strMsg.Append(CReportDlg::FormatString(dvalue,8));
			m_strMsg.Append(_T("\r\n"));
			if(dvalue>0)
			{
				rs.GetFieldValue((short)1,strVal);
				theLang.LoadString(str2,IDS_UNPAYAMOUNT);
				m_strMsg.Append(CReportDlg::FormatString(str2,18,FALSE));
				double fvalue=_wtof(strVal);
				m_strMsg.Append(CReportDlg::FormatString(fvalue,8));
				m_strMsg.Append(_T("\r\n"));
			}
		}
		rs.Close();
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
	// 异常: OCX 属性页应返回 FALSE
}
void ShiftDlg::GetShiftInfoByPos()
{
	try
	{
		CRecordset rs( &theDB);
		CString strSQL;
		CString strVal,str2;
		CDBVariant variant;
		m_strMsg.Empty();
		CPOSClientApp* pApp=(CPOSClientApp*)AfxGetApp();
		OpenDatabase();
		//更新时间
		GetPrivateProfileString(_T("POS"),_T("SHIFT_TIME"),_T("2016-1-1"),str_from.GetBuffer(40),40,_T(".\\config.ini"));
		strSQL.Format(_T("SELECT now()"));
		rs.Open( CRecordset::forwardOnly,strSQL);
		if (!rs.IsEOF())
		{
			rs.GetFieldValue((short)0,strVal);
			str_to.Format(_T("%s"),strVal);
		}
		else
		{
			CTime time_to=CTime::GetCurrentTime();
			str_to=time_to.Format(_T("%Y-%m-%d %H:%M:%S"));
		}
		rs.Close();
		GetDlgItem(IDC_STATIC2)->SetWindowText(str_from);
		//支付方式
		JSONVALUE arrayItems(JSONTYPE::JT_ARRAY);
		strSQL.Format(_T("{CALL c_pay_style(\'%s\',\'%s\',%d,%d)}"),str_from,str_to,pApp->m_nDeviceId,pApp->m_nDeviceId);
		rs.Open(CRecordset::forwardOnly,strSQL);
		double total=0;
		while(!rs.IsEOF())
		{
			rs.GetFieldValue((short)0,str2);
			rs.GetFieldValue(1,strVal);
			double fvalue=_wtof(strVal);
			total+=fvalue;
			if(fvalue>0)
			{
				JSONVALUE item;
				item[_T("k")]=str2;
				item[_T("v")]=fvalue;
				arrayItems.Push(item);
			}
			m_strMsg.Append(CReportDlg::FormatString(str2,18,FALSE));
			m_strMsg.Append(CReportDlg::FormatString(fvalue,8));
			m_strMsg.Append(_T("\r\n"));
			rs.MoveNext();
		}
		rs.Close();
		payinfo[_T("pays")]=arrayItems;
		m_strMsg.Append(_T("--------------------------\r\n"));
		BOOL bSet=FALSE;
		//WEB 会员充值
		try{
			if (!theApp.m_strVipURL.IsEmpty())
			{
				CString ip_addr;
				ip_addr.Format(_T("/api/get_recharge/1/json/?source=agile&date_from=%s&date_to=%s&guid=%s&machine_id=%s&random=%d")
					,str_from,str_to,theApp.m_strResId,URLEncode(theApp.m_strHostName),rand()%32767);
				if(theLang.m_strLang==_T("Default")||theLang.m_strLang==_T("简体中文"))
					ip_addr.AppendFormat(_T("&lang=zh-CN"));
				else if(theLang.m_strLang==_T("繁體中文"))
					ip_addr.AppendFormat(_T("&lang=zh-TW"));
				else
					ip_addr.AppendFormat(_T("&lang=en"));
				LOG4CPLUS_DEBUG(log_pos,(LPCTSTR)ip_addr);
				CInternetSession session;
				session.SetOption(INTERNET_OPTION_CONNECT_TIMEOUT, 1000 * 20);
				session.SetOption(INTERNET_OPTION_CONNECT_BACKOFF, 1000);
				session.SetOption(INTERNET_OPTION_CONNECT_RETRIES, 1);

				CHttpConnection* pConnection = session.GetHttpConnection(theApp.m_strVipURL,(INTERNET_PORT)theApp.m_nVipPort);
				CHttpFile* pFile = pConnection->OpenRequest(CHttpConnection::HTTP_VERB_GET,ip_addr); 
				pFile->SendRequest();
				DWORD dwRet;
				pFile->QueryInfoStatusCode(dwRet);
				if(dwRet == HTTP_STATUS_OK)
				{
					char buf[1024]={0};
					pFile->Read((LPTSTR)buf,sizeof(buf)-1);
					LOG4CPLUS_DEBUG(log_pos,buf);
					pFile->Close();
					for (int i=strlen(buf)-1;i>=0;i--)
					{
						if(buf[i]=='}')
							break;
						buf[i]=0;
					}
					int wcsLen0 = ::MultiByteToWideChar(CP_UTF8, NULL, buf, strlen(buf), NULL, 0);
					TCHAR* sz1 = new TCHAR[wcsLen0 + 1];
					::MultiByteToWideChar(CP_UTF8, NULL, buf, -1, sz1, wcsLen0);
					sz1[wcsLen0] = '\0';
					JSONVALUE root;
					if(root.Parse(sz1,JSON_FLAG_LOOSE))
					{
						double ori_recharge=root[_T("ori_recharge")].asDouble();
						total+=ori_recharge;
						JSONVALUE arrayItems=root[_T("detail")];
						if(arrayItems.Size()==0)
						{
							theLang.LoadString(str2,IDS_VIPRECHARGE);
							m_strMsg.Append(CReportDlg::FormatString(str2,18,FALSE));
							m_strMsg.Append(CReportDlg::FormatString(ori_recharge,8));
							m_strMsg.Append(_T("\r\n"));
						}
						else
						{//详细金额
							theLang.LoadString(str2,IDS_VIPRECHARGE);
							m_strMsg.AppendFormat(_T("%s:\r\n"),str2);
							for (int j=0;j<arrayItems.Size();j++)
							{
								JSONVALUE jItem;
								arrayItems.At(j,jItem);
								CString name=jItem[_T("payment")].asCString();
								m_strMsg.Append(CReportDlg::FormatString(name,18,FALSE));
								m_strMsg.Append(CReportDlg::FormatString(jItem[_T("ori_amount")].asDouble(),8));
								m_strMsg.Append(CReportDlg::FormatString(jItem[_T("count")].asInt(),4));
								m_strMsg.Append(_T("\r\n"));
							}
						}

						bSet=TRUE;
					}
					delete sz1;
				}
				delete pFile;

			}
		}
		catch (CInternetException* pEx)
		{
			TCHAR szErr[1024];
			pEx->GetErrorMessage(szErr, 1024);
			LOG4CPLUS_ERROR(log_pos,szErr);
			pEx->Delete();
			theLang.LoadString(str2,IDS_VIPRECHARGE);
			m_strMsg.AppendFormat(_T("%s:\tERROR\r\n"),str2);
		}
		catch(...)
		{
			LOG4CPLUS_ERROR(log_pos,"Catch Exception GetLastError="<<GetLastError());
		}
		//存入的现金
		strSQL.Format(_T("SELECT SUM(cash_amount) FROM cashbox_in_out WHERE cashbox_id=%d AND in_out_time>=\'%s\'")
			_T(" AND in_out_time<\'%s\' AND cash_amount>0")
			,pApp->m_nDeviceId,str_from,str_to);
		rs.Open( CRecordset::forwardOnly,strSQL);
		if (!rs.IsEOF())
		{
			rs.GetFieldValue((short)0,strVal);
			double fvalue=_wtof(strVal);
			if(fvalue>0)
			{
				total+=fvalue;
				theLang.LoadString(str2,IDS_CASHIN);
				m_strMsg.Append(CReportDlg::FormatString(str2,18,FALSE));
				m_strMsg.Append(CReportDlg::FormatString(fvalue,8));
				m_strMsg.Append(_T("\r\n"));
				bSet=TRUE;
			}
		}
		rs.Close();
		//取出的现金
		strSQL.Format(_T("SELECT SUM(cash_amount) FROM cashbox_in_out WHERE cashbox_id=%d AND in_out_time>=\'%s\'")
			_T(" AND in_out_time<\'%s\' AND cash_amount<0")
			,pApp->m_nDeviceId,str_from,str_to);
		rs.Open( CRecordset::forwardOnly,strSQL);
		if (!rs.IsEOF())
		{
			rs.GetFieldValue((short)0,strVal);
			double fvalue=_wtof(strVal);
			if(fvalue<-0.001)
			{
				total+=fvalue;
				theLang.LoadString(str2,IDS_CASHOUT);
				m_strMsg.Append(CReportDlg::FormatString(str2,18,FALSE));
				double fvalue=_wtof(strVal);
				m_strMsg.Append(CReportDlg::FormatString(fvalue,8));
				m_strMsg.Append(_T("\r\n"));
				bSet=TRUE;
			}
		}
		rs.Close();
		if(bSet)
			m_strMsg.Append(_T("--------------------------\r\n"));
		//未结账单
		strSQL.Format(_T("select count(*),round(sum(should_amount),2) from order_head where status=0"));
		rs.Open( CRecordset::forwardOnly,strSQL);
		if (!rs.IsEOF())
		{
			rs.GetFieldValue((short)0,strVal);
			theLang.LoadString(str2,IDS_UNPAYNUMS);
			m_strMsg.Append(CReportDlg::FormatString(str2,18,FALSE));
			int dvalue=_wtoi(strVal);
			m_strMsg.Append(CReportDlg::FormatString(dvalue,8));
			m_strMsg.Append(_T("\r\n"));
			if(dvalue>0)
			{
				rs.GetFieldValue((short)1,strVal);
				theLang.LoadString(str2,IDS_UNPAYAMOUNT);
				m_strMsg.Append(CReportDlg::FormatString(str2,18,FALSE));
				double fvalue=_wtof(strVal);
				m_strMsg.Append(CReportDlg::FormatString(fvalue,8));
				m_strMsg.Append(_T("\r\n"));
			}
		}
		rs.Close();
		//发票金额
		strSQL.Format(_T("SELECT SUM(amount) FROM invoices WHERE pos_device_id=%d AND edit_time>=\'%s\' AND edit_time<\'%s\'")
			,pApp->m_nDeviceId,str_from,str_to);
		rs.Open( CRecordset::forwardOnly,strSQL);
		if (!rs.IsEOF())
		{
			rs.GetFieldValue((short)0,strVal);
			double fvalue=_wtof(strVal);
			if(fvalue>0.001)
			{
				theLang.LoadString(str2,IDS_INVOICE);
				m_strMsg.Append(CReportDlg::FormatString(str2,18,FALSE));
				m_strMsg.Append(CReportDlg::FormatString(fvalue,8));
				m_strMsg.Append(_T("\r\n"));
			}

		}
		rs.Close();

		//快餐模式添加大类销售统计
		if(macrosInt[_T("SHIFT_MAJORSALES")]==1)
		{
			CString strVal;
			theLang.LoadString(str2,IDS_MAJORSALES);
			m_strMsg.Append(str2);
			strSQL.Format(_T("{CALL c_major_sales(\'%s\',\'%s\')}"),str_from,str_to);
			rs.Open( CRecordset::forwardOnly,strSQL);
			while (!rs.IsEOF())
			{
				rs.GetFieldValue((short)1,str2);
				rs.GetFieldValue((short)3,strVal);
				int ivalue=_wtoi(strVal);
				str2.Append(_T(":"));
				m_strMsg.Append(CReportDlg::FormatString(str2,10,FALSE));
				m_strMsg.Append(CReportDlg::FormatString(ivalue,6));
				rs.GetFieldValue((short)2,strVal);
				double fvalue=_wtof(strVal);
				m_strMsg.Append(CReportDlg::FormatString(fvalue,10));
				m_strMsg.Append(_T("\r\n"));
				rs.MoveNext();
			}
			rs.Close();

			strSQL.Format(_T("SELECT ROUND(SUM(quantity)) FROM history_order_detail WHERE is_return_item=0 AND menu_item_id>0 AND order_time>=\'%s\' AND order_time<\'%s\'")
				,str_from,str_to);
			rs.Open( CRecordset::forwardOnly,strSQL);
			if (!rs.IsEOF())
			{
				rs.GetFieldValue((short)0,strVal);
				theLang.LoadString(IDS_QTOTAL,str2);
				m_strMsg.Append(CReportDlg::FormatString(str2,10,FALSE));
				int fvalue=_wtoi(strVal);
				m_strMsg.Append(CReportDlg::FormatString(fvalue,6));
				m_strMsg.Append(_T("\r\n"));
			}
			rs.Close();

			strSQL.Format(_T("SELECT ROUND(SUM(quantity)) FROM history_order_detail WHERE is_discount=1 AND menu_item_id>0 AND order_time>=\'%s\' AND order_time<\'%s\'")
				,str_from,str_to);
			rs.Open( CRecordset::forwardOnly,strSQL);
			if (!rs.IsEOF())
			{
				rs.GetFieldValue((short)0,strVal);
				theLang.LoadString(IDS_QFREE,str2);
				m_strMsg.Append(CReportDlg::FormatString(str2,10,FALSE));
				int fvalue=_wtoi(strVal);
				m_strMsg.Append(CReportDlg::FormatString(fvalue,6));
				m_strMsg.Append(_T("\r\n"));
			}
			rs.Close();
		}		
	}
	catch(...)
	{
		LOG4CPLUS_ERROR(log_pos,"Catch Exception GetLastError="<<GetLastError());
	}
	// 异常: OCX 属性页应返回 FALSE
}

void ShiftDlg::OnBnClickedOk()
{
	if (m_bTrainingMode)
		return;
	LOG4CPLUS_INFO(log_pos,"ShiftDlg::OnBnClickedOk Begin");
	try{
	PrintDeviceInfo printer;
	if(theApp.m_prePrinter.nDeviceType==-1||theApp.m_prePrinter.nPaperWidth==0)
	{
		if (theApp.m_payPrinter.nDeviceType==-1)
		{//没有配置打印机，无法打印
			POSMessageBox(IDS_NOPREPRINT);
			return;
		}
		printer=theApp.m_payPrinter;
	}
	else
		printer=theApp.m_prePrinter;
	if(theApp.m_nShiftType<=0)
	{
		WritePrivateProfileString(_T("POS"),_T("SHIFT_TIME"),str_to,_T(".\\config.ini"));
	}
	else
	{
		CString strSQL;
		strSQL.Format(_T("UPDATE employee SET end_date=\'%s\' WHERE employee_id=%s"),str_to,theApp.m_strUserID);
		theDB.ExecuteSQL(strSQL);
	}

	JSONVALUE root;
	root[_T("message")]=m_strMsg;
	CPOSClientApp::FormatPrintDevice(root,printer);
	root[_T("template")]=TEMPLATE_SHIFT;
	root[_T("open_time")]=str_from;
	root[_T("end_time")]=str_to;
	root[_T("dev_id")]=theApp.m_strDeviceName;
	root[_T("emp_name")]=theApp.m_strUserName;
	root[_T("period")]=theApp.m_strPeriod;
	m_strMsg.AppendFormat(_T("%s"),theApp.m_strDeviceName);
	CPOSClientApp::CriticalLogs(OPR_SHIFT,m_strMsg);

	//记录到数据库
	if(!m_bReadonly)
	{
		std::wstring str;
		payinfo.ToString(str);
		CString jstr=str.c_str();
		jstr.Replace(_T("\""),_T("\\\""));
		CString strSQL;
		strSQL.Format(_T("INSERT INTO shift_info(type,employee_id,employee_name,start_time,end_time,pos_device_id,detail)")
			_T(" VALUES(%d,%s,\'%s\',\'%s\',\'%s\',%d,\'%s\')"),theApp.m_nShiftType,theApp.m_strUserID,theApp.m_strUserName,str_from,str_to,theApp.m_nDeviceId,jstr);
		theDB.ExecuteSQL(strSQL);
	}
	
	//添加到打印任务
	CPOSClientApp::PrintJson(root);
	if(macrosInt[_T("PRINT_SHIFT_TWICE")]==1)
	{
		Sleep(10);
		CPOSClientApp::PrintJson(root);
	}
	OnOK();
	}
	catch(...)
	{
		LOG4CPLUS_ERROR(log_pos,"Catch Exception GetLastError="<<GetLastError());
	}
}

HBRUSH ShiftDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	if(nCtlColor==CTLCOLOR_STATIC)
	{
		 pDC->SetTextColor(m_dTextColor);
		 if(pWnd->GetDlgCtrlID()==IDC_EDIT1)
			 return CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
		pDC->SetBkMode(TRANSPARENT);
		return (HBRUSH)::GetStockObject(NULL_BRUSH); //返回此画刷可以使静态文本透明
	}
	return hbr;
}
void ShiftDlg::OnPaint()
{
	if(!IsIconic())
	{
		CRect   rect;
		CPaintDC   dc(this);
		GetClientRect(rect);
		dc.FillSolidRect(rect,DEFALUT_BACKGROUND_COLOR);
		CDialog::OnPaint();
	}
}