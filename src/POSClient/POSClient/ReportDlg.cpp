// ReportDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "POSClient.h"
#include "ReportDlg.h"
#include "OrderDlg.h"



// CReportDlg 对话框

IMPLEMENT_DYNAMIC(CReportDlg, CDialog)

CReportDlg::CReportDlg(CWnd* pParent /*=NULL*/)
: CDialog(CReportDlg::IDD, pParent)
{
	m_iType=0;
}

CReportDlg::~CReportDlg()
{
}

void CReportDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_edit);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_fromDate);
	DDX_Control(pDX, IDC_DATETIMEPICKER2, m_toDate);
	DDX_Control(pDX, IDC_REFRESH, m_freshButton);
	DDX_Control(pDX, IDC_BTPRINT, m_printButton);
	DDX_Control(pDX, IDOK, m_closeButton);
	DDX_Control(pDX, IDC_CURDAY, m_btCurday);
	DDX_Control(pDX, IDC_LASTDAY, m_btYesday);
	DDX_Control(pDX, IDC_CURMONTH, m_btCurmonth);
	DDX_Control(pDX, IDC_LASTMONTH, m_btLastmonth);
}


BEGIN_MESSAGE_MAP(CReportDlg, CDialog)
	ON_BN_CLICKED(IDC_REFRESH, &CReportDlg::OnBnClickedRefresh)
	ON_BN_CLICKED(IDC_BTPRINT, &CReportDlg::OnBnClickedBtprint)
	//ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_CURDAY, &CReportDlg::OnBnClickedCurday)
	ON_BN_CLICKED(IDC_LASTDAY, &CReportDlg::OnBnClickedLastday)
	ON_BN_CLICKED(IDC_CURMONTH, &CReportDlg::OnBnClickedCurmonth)
	ON_BN_CLICKED(IDC_LASTMONTH, &CReportDlg::OnBnClickedLastmonth)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CReportDlg 消息处理程序


void CReportDlg::OnBnClickedRefresh()
{
	ShowReport();
}

void CReportDlg::OnBnClickedBtprint()
{
	CString userid;
	int auth=OrderDlg::RequeastAuth(userid,_T("manager_privilege"),3);
	if(auth!=0)
		return;
	LOG4CPLUS_INFO(log_pos,"CReportDlg::OnBnClickedBtprint");
	PrintDeviceInfo printer;
	if(theApp.m_prePrinter.nDeviceType==-1||theApp.m_prePrinter.nPaperWidth==0)
	{
		if (theApp.m_payPrinter.nDeviceType==-1)
		{//没有配置打印机，无法打印
			return;
		}
		printer=theApp.m_payPrinter;
	}
	else
		printer=theApp.m_prePrinter;

	JSONVALUE root;
	CPOSClientApp::FormatPrintDevice(root,printer);
	root[_T("template")]=TEMPLATE_REPORT;
	root[_T("head")]=m_strTitle;
	root[_T("open_time")]=m_strStartDate;
	root[_T("end_time")]=m_strEndDate;
	root[_T("message")]=m_strResult;
	CTime time_to=CTime::GetCurrentTime();
	root[_T("time")]=time_to.Format(_T("%Y-%m-%d %H:%M:%S"));
	CPOSClientApp::PrintJson(root);
}

BOOL CReportDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	CString userid;
	int auth=OrderDlg::RequeastAuth(userid,_T("manager_privilege"),2);
	if(auth!=0)
	{
		CDialog::OnCancel();
		return TRUE;
	}
	SetWindowText(m_strTitle);
	m_btCurday.SetImage(_T("Picture\\bt_day.png"));
	m_btYesday.SetImage(_T("Picture\\bt_day.png"));
	m_btCurmonth.SetImage(_T("Picture\\bt_day.png"));
	m_btLastmonth.SetImage(_T("Picture\\bt_day.png"));
	m_freshButton.SetImage(_T("Picture\\table1.png"));
	m_printButton.SetImage(_T("Picture\\table1.png"));
	m_closeButton.SetImage(_T("Picture\\table1.png"));
	m_btCurday.SetTextColor(DEFALUT_TXT_COLOR);
	m_btYesday.SetTextColor(DEFALUT_TXT_COLOR);
	m_btCurmonth.SetTextColor(DEFALUT_TXT_COLOR);
	m_btLastmonth.SetTextColor(DEFALUT_TXT_COLOR);
	if (!theLang.m_bDefaultLang)
	{
		LOGFONT logFont;
		theLang.m_dialogFont.GetLogFont(&logFont);
		CWnd* pCtrl=GetDlgItem(IDC_CURDAY);
		theLang.TranslateDlgItem(pCtrl,IDS_CURDAY);
		m_btCurday.SetFont(&logFont);
		pCtrl=GetDlgItem(IDC_LASTDAY);
		theLang.TranslateDlgItem(pCtrl,IDS_YESTERDAY);
		m_btYesday.SetFont(&logFont);
		pCtrl=GetDlgItem(IDC_CURMONTH);
		theLang.TranslateDlgItem(pCtrl,IDS_CURMONTH);
		m_btCurmonth.SetFont(&logFont);
		pCtrl=GetDlgItem(IDC_LASTMONTH);
		theLang.TranslateDlgItem(pCtrl,IDS_LASTMONTH);
		m_btLastmonth.SetFont(&logFont);
		pCtrl=GetDlgItem(IDC_REFRESH);
		theLang.TranslateDlgItem(pCtrl,IDS_REFRESH);
		pCtrl=GetDlgItem(IDC_BTPRINT);
		theLang.TranslateDlgItem(pCtrl,IDS_PRINT);
		pCtrl=GetDlgItem(IDOK);
		theLang.TranslateDlgItem(pCtrl,IDS_EXIT);
	}

	HFONT hFont = (HFONT)::GetStockObject(SYSTEM_FIXED_FONT);
    CFont *pFont = CFont::FromHandle(hFont);
	m_edit.SetFont(pFont);
	m_fromDate.SetFormat(_T("yyyy-MM-dd"));
	m_toDate.SetFormat(_T("yyyy-MM-dd"));

	//读取End of Day
	OpenDatabase();
	CRecordset rs(&theDB);
	CString strSQL;
	strSQL.Format(_T("SELECT start_time FROM restaurant ;"));
	rs.Open( CRecordset::forwardOnly,strSQL);
	if (!rs.IsEOF())
	{
		CDBVariant variant;
		rs.GetFieldValue((short)0,variant);
		m_eodTime= CTime(variant.m_pdate->year,variant.m_pdate->month,variant.m_pdate->day,variant.m_pdate->hour,variant.m_pdate->minute,variant.m_pdate->second);
	}
	if(theApp.m_prePrinter.nPaperWidth<76)
		m_bShortFormat=TRUE;
	else
		m_bShortFormat=FALSE;
	OnBnClickedCurday();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

/************************************************************************
* 函数介绍：获取实际打印的长度，一个中文字符为2
* 输入参数：
* 输出参数：
* 返回值  ：
************************************************************************/
int CReportDlg::GetPrintLength(LPCTSTR str)
{
	int length=0;
	int len=wcslen(str);
	for (int i = 0 ; i <len;i++)
	{
		TCHAR unicode=str[i];
		//int unicode = (int)str.GetAt(i);
		if (unicode==0)
			break;
		if (unicode > 255)
			length+=2;
		else
		{
			length++;
		}

	}
	return length;
}
/************************************************************************
* 函数介绍：格式化字符，不足用空格补足
* 输入参数：
* 输出参数：
* 返回值  ：
************************************************************************/
CString CReportDlg::FormatString(LPCTSTR str,int len,BOOL bCompact)
{
	CString strResult;
	if (bCompact)
	{
		strResult.Format(_T("%s\t"),str);
		return strResult;
	}
	strResult.Format(_T("%s"),str);
	int spaces=len-GetPrintLength(str);
	for (int j=0;j<spaces;j++)
	{
		strResult.AppendChar(' ');
	}
	return strResult;
}
CString CReportDlg::FormatString(double d,int len)
{
	CString strResult;
	strResult.Format(theApp.m_decPlace,d);
	int spaces=len-strResult.GetLength();
	for (int j=0;j<spaces;j++)
	{
		strResult.Insert(0,' ');
	}
	return strResult;
}
CString CReportDlg::FormatString(int d,int len)
{
	CString strResult;
	strResult.Format(_T("%d"),d);
	int spaces=len-strResult.GetLength();
	for (int j=0;j<spaces;j++)
	{
		strResult.Insert(0,' ');
	}
	return strResult;
}
void CReportDlg::ShowReport()
{
	try
	{
		CTime from_time,to_time;
		m_fromDate.GetTime(from_time);
		m_toDate.GetTime(to_time);
		if( macrosInt[_T("USE_SALE_TIME")]==0)
		{
			m_strStartDate=from_time.Format(_T("%Y-%m-%d 00:00:00"));
			m_strEndDate=to_time.Format(_T("%Y-%m-%d 23:59:59"));
		}
		else
		{
			m_strStartDate=from_time.Format(_T("%Y-%m-%d"))+m_eodTime.Format(_T(" %H:%M:%S"));
			m_strEndDate=to_time.Format(_T("%Y-%m-%d"))+m_eodTime.Format(_T(" %H:%M:%S"));
		}
		
		
		if(m_iType==1)
		{
			ShowReport1();
			return;
		}
		else if(m_iType==2)
		{
			ShowReport2();
			return;
		}
		else if(m_iType==3)
		{
			ShowReport3();
			return;
		}
		OpenDatabase();
		CRecordset rs(&theDB);
		CString strSQL;
		strSQL.Format(m_strQuerry,m_strStartDate,m_strEndDate);
		rs.Open( CRecordset::forwardOnly,strSQL);
		//查看返回值
		m_strResult.Empty();
		int column_count=rs.GetODBCFieldCount();
		int field_len[5]={6,10,10,7,6};
		//表头
		for(int i=0;i<column_count&&i<5;i++)
		{
			CODBCFieldInfo fieldinfo;
			rs.GetODBCFieldInfo(i,fieldinfo);
			//m_strResult.Append(FormatString(fieldinfo.m_strName,field_len[i]));
		}
		//m_strResult.Append(_T("\r\n"));
		while (!rs.IsEOF())
		{
			CString fvalue;
			for(int i=0;i<column_count&&i<5;i++)
			{
				rs.GetFieldValue(i,fvalue);
				m_strResult.Append(FormatString(fvalue,field_len[i]));
			}
			m_strResult.Append(_T("\r\n"));
			rs.MoveNext();
		}
		rs.Close();
		m_edit.SetWindowText(m_strResult);
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
}
/************************************************************************
* 函数介绍：销售总结报告，特殊显示
* 输入参数：bSms -TRUE 用于发送短信，精简内容
* 输出参数： 
* 返回值  ：
************************************************************************/
void CReportDlg::ShowReport1(BOOL bSms)
{
	OpenDatabase();
	CRecordset rs(&theDB);
	CString strSQL,str1,str2,strVal;
	double fvalue=0;
	double fTotalSale;//菜品中销售额
	double fActualSale;//单据总额
	double fTips;
	m_strResult.Empty();
	theLang.LoadString(m_strResult,IDS_RPTOVERVIEW);
	strSQL.Format(_T("select round(sum(actual_price),2) from history_order_detail,history_order_head where menu_item_id>0 AND is_return_item=0 ")
		_T("AND history_order_detail.order_head_id=history_order_head.order_head_id AND history_order_detail.check_id=history_order_head.check_id AND order_end_time>=\'%s\' AND order_end_time<=\'%s\'")
		,m_strStartDate,m_strEndDate);
	rs.Open( CRecordset::forwardOnly,strSQL);
	if (!rs.IsEOF())
	{
		rs.GetFieldValue((short)0,strVal);
		fvalue=_wtof(strVal);
		theLang.LoadString(str2,IDS_SALEDISHES);
		str2.Append(_T(":"));
		m_strResult.Append(FormatString(str2,20,bSms));
		m_strResult.Append(FormatString(fvalue,7));
		m_strResult.Append(_T("\r\n"));
		fTotalSale=fvalue;
		
	}
	rs.Close();

	strSQL.Format(_T("select round(sum(actual_price),2) from history_order_detail,history_order_head where menu_item_id=-6 AND is_return_item=0 ")
		_T("AND history_order_detail.order_head_id=history_order_head.order_head_id AND history_order_detail.check_id=history_order_head.check_id AND order_end_time>=\'%s\' AND order_end_time<=\'%s\'")
		,m_strStartDate,m_strEndDate);
	rs.Open( CRecordset::forwardOnly,strSQL);
	if (!rs.IsEOF())
	{
		rs.GetFieldValue((short)0,strVal);
		fTips=_wtof(strVal);
	}
	rs.Close();

	strSQL.Format(_T("select round(sum(discount_amount),2),round(sum(service_amount),2),round(sum(tax_amount),2),")
		_T("round(sum(actual_amount),2) from history_order_head where order_end_time>=\'%s\' AND order_end_time<\'%s\'")
		,m_strStartDate,m_strEndDate);
	rs.Open( CRecordset::forwardOnly,strSQL);
	if (!rs.IsEOF())
	{
		rs.GetFieldValue((short)0,strVal);
		fvalue=_wtof(strVal);
		theLang.LoadString(str2,IDS_DISCOUNT);
		str1.Format(_T("-%s:"),str2);
		m_strResult.Append(FormatString(str1,20,bSms));
		m_strResult.Append(FormatString(fvalue,7));
		m_strResult.Append(_T("\r\n"));

		theLang.LoadString(str2,IDS_NETSALE);
		str1.Format(_T("=%s:"),str2);
		m_strResult.Append(FormatString(str1,20,bSms));
		m_strResult.Append(FormatString(fTotalSale+fvalue,7));
		m_strResult.Append(_T("\r\n"));

		rs.GetFieldValue((short)1,strVal);
		fvalue=_wtof(strVal);
		theLang.LoadString(str2,IDS_SERVICE);
		str1.Format(_T("+%s:"),str2);
		m_strResult.Append(FormatString(str1,20,bSms));
		m_strResult.Append(FormatString(fvalue,7));
		m_strResult.Append(_T("\r\n"));
#ifdef EN_VERSION
		rs.GetFieldValue((short)2,strVal);
		fvalue=_wtof(strVal);
		//theLang.LoadString(str2,IDS_TAX);
		str1.Format(_T("+%s:"),CCheckDlg::TAX_NAME);
		m_strResult.Append(FormatString(str1,20,bSms));
		m_strResult.Append(FormatString(fvalue,7));
		m_strResult.Append(_T("\r\n"));

		theLang.LoadString(str2,IDS_TIPS);
		str1.Format(_T("+%s:"),str2);
		m_strResult.Append(FormatString(str1,20,bSms));
		m_strResult.Append(FormatString(fTips,7));
		m_strResult.Append(_T("\r\n"));
#endif
		rs.GetFieldValue((short)3,strVal);
		fvalue=_wtof(strVal);
		theLang.LoadString(str2,IDS_TTLSALE);
		str2.Append(_T(":"));
		m_strResult.Append(FormatString(str2,20,bSms));
		m_strResult.Append(FormatString(fvalue,7));
		m_strResult.Append(_T("\r\n"));
		fActualSale=fvalue;

	}
	rs.Close();

	//单据数，人均
	CString strtmp;
	int iTtlChk=0,iTtlGst=0;
	strSQL.Format(_T("select COUNT(*) from history_order_head where order_end_time>=\'%s\' AND order_end_time<\'%s\'")
		,m_strStartDate,m_strEndDate);
	rs.Open( CRecordset::forwardOnly,strSQL);
	if (!rs.IsEOF())
	{
		m_strResult.Append(_T("\r\n"));
		rs.GetFieldValue((short)0,strtmp);
		if(!strtmp.IsEmpty())
			iTtlChk=_wtoi(strtmp);
		theLang.LoadString(str2,IDS_CHECKNUMS);
		m_strResult.Append(FormatString(str2,20,bSms));
		m_strResult.Append(FormatString(iTtlChk,7));
		m_strResult.Append(_T("\r\n"));
	}
	rs.Close();

	strSQL.Format(_T("select SUM(customer_num) from history_order_head where check_id=1 AND order_end_time>=\'%s\' AND order_end_time<\'%s\'")
		,m_strStartDate,m_strEndDate);
	rs.Open( CRecordset::forwardOnly,strSQL);
	if (!rs.IsEOF())
	{
		rs.GetFieldValue((short)0,strtmp);
		if(!strtmp.IsEmpty())
			iTtlGst=_wtoi(strtmp);
		theLang.LoadString(str2,IDS_GSTNUMS);
		m_strResult.Append(FormatString(str2,20,bSms));
		m_strResult.Append(FormatString(iTtlGst,7));
		m_strResult.Append(_T("\r\n"));
	}
	rs.Close();

	theLang.LoadString(str2,IDS_SALEPCHK);
	if(iTtlChk==0)
		iTtlChk=1;
	m_strResult.Append(FormatString(str2,20,bSms));
	m_strResult.Append(FormatString(fActualSale/iTtlChk,7));
	m_strResult.Append(_T("\r\n"));
	theLang.LoadString(str2,IDS_SALEPGST);
	if(iTtlGst==0)
		iTtlGst=1;
	m_strResult.Append(FormatString(str2,20,bSms));
	m_strResult.Append(FormatString(fActualSale/iTtlGst,7));
	m_strResult.Append(_T("\r\n"));

	if(!bSms){
		int type=macrosInt[_T("SALES_REPORT_TYPE")];
		int remain;
		remain=type%10;
		type=type/10;
		if(remain>=1)
		{//分段销量
			theLang.LoadString(str2,IDS_RPTPERIOD);
			m_strResult.Append(str2);
			strSQL.Format(_T("{CALL c_period_sales(\'%s\',\'%s\')}"),m_strStartDate,m_strEndDate);
			rs.Open( CRecordset::forwardOnly,strSQL);
			while (!rs.IsEOF())
			{
				rs.GetFieldValue((short)1,str2);
				rs.GetFieldValue((short)2,strVal);
				fvalue=_wtof(strVal);
				m_strResult.Append(FormatString(str2,14,bSms));
				m_strResult.Append(FormatString(fvalue,6));
				if(abs(fActualSale)>0.001)
					m_strResult.AppendFormat(_T(" %5.1f%%\r\n"),(100*fvalue)/fActualSale);
				else
					m_strResult.AppendFormat(_T("   0.0%%\r\n"));
				rs.MoveNext();
			}
			rs.Close();
		}
		//分类销量
		remain=type%10;
		type=type/10;
		if(remain>=1)
		{
			theLang.LoadString(str2,IDS_MAJORSALES);
			m_strResult.Append(str2);
			strSQL.Format(_T("{CALL c_major_sales(\'%s\',\'%s\')}"),m_strStartDate,m_strEndDate);
			rs.Open( CRecordset::forwardOnly,strSQL);
			while (!rs.IsEOF())
			{
				rs.GetFieldValue((short)1,str2);
				rs.GetFieldValue((short)2,strVal);
				fvalue=_wtof(strVal);
				str2.Append(_T(":"));
				m_strResult.Append(FormatString(str2,14,bSms));
				m_strResult.Append(FormatString(fvalue,6));
				if(abs(fTotalSale)>0.05)
					m_strResult.AppendFormat(_T(" %5.1f%%\r\n"),(100*fvalue)/fTotalSale);
				else
					m_strResult.AppendFormat(_T("   0.0%%\r\n"));
				rs.MoveNext();
			}
			rs.Close();
		}
		//部门销量
		remain=type%10;
		//type=type/10;
		if(remain>=1)
		{
			theLang.LoadString(str2,IDS_RPTDEPART);
			m_strResult.Append(str2);
			strSQL.Format(_T("{CALL c_department_sales(\'%s\',\'%s\')}"),m_strStartDate,m_strEndDate);
			rs.Open( CRecordset::forwardOnly,strSQL);
			while (!rs.IsEOF())
			{
				rs.GetFieldValue((short)1,str2);
				rs.GetFieldValue((short)2,strVal);
				fvalue=_wtof(strVal);
				str2.Append(_T(":"));
				m_strResult.Append(FormatString(str2,14,bSms));
				m_strResult.Append(FormatString(fvalue,6));
				if(abs(fTotalSale)>0.001)
					m_strResult.AppendFormat(_T(" %5.1f%%\r\n"),(100*fvalue)/fTotalSale);
				else
					m_strResult.AppendFormat(_T("   0.0%%\r\n"));
				rs.MoveNext();
			}
			rs.Close();
		}
	}

	theLang.LoadString(str2,IDS_PAMENTOV);
	m_strResult.Append(str2);
	strSQL.Format(_T("{CALL c_pay_style(\'%s\',\'%s\',0,99)}"),m_strStartDate,m_strEndDate);
	rs.Open( CRecordset::forwardOnly,strSQL);
	while (!rs.IsEOF())
	{
		rs.GetFieldValue((short)0,str2);
		rs.GetFieldValue((short)1,strVal);
		fvalue=_wtof(strVal);
		str2.Append(_T(":"));
		m_strResult.Append(FormatString(str2,20,bSms));
		m_strResult.Append(FormatString(fvalue,7));
		m_strResult.Append(_T("\r\n"));
		rs.MoveNext();
	}
	rs.Close();
	if(!bSms){
		theLang.LoadString(str2,IDS_RPTRETURN);
		m_strResult.Append(str2);
		strSQL.Format(_T("select SUM(ABS(quantity)),SUM(ABS(actual_price))")
			_T(" from history_order_detail ")
			_T("where menu_item_id>0 AND return_time>=\'%s\' AND return_time<=\'%s\'AND (is_return_item=1 OR quantity<0)")
			,m_strStartDate,m_strEndDate);
		rs.Open( CRecordset::forwardOnly,strSQL);
		if (!rs.IsEOF())
		{
			rs.GetFieldValue((short)1,strtmp);
			double freturn=_wtof(strtmp);
			theLang.LoadString(str2,IDS_RETURNAMOUNT);
			m_strResult.Append(FormatString(str2,20,bSms));
			m_strResult.Append(FormatString(freturn,7));
			m_strResult.Append(_T("\r\n"));
			rs.GetFieldValue((short)0,strtmp);
			int num=(_wtof(strtmp)+0.5);//四舍五入
			theLang.LoadString(str2,IDS_RETURNNUMS);
			m_strResult.Append(FormatString(str2,20,bSms));
			m_strResult.Append(FormatString(num,7));
			m_strResult.Append(_T("\r\n"));
		}
		rs.Close();

		theLang.LoadString(str2,IDS_RPTREFUND);
		m_strResult.Append(str2);
		strSQL.Format(_T("select count(*),round(sum(actual_amount),2) from history_order_head where actual_amount<0 AND order_end_time>=\'%s\' AND order_end_time<\'%s\'")
			,m_strStartDate,m_strEndDate);
		rs.Open( CRecordset::forwardOnly,strSQL);
		if (!rs.IsEOF())
		{
			rs.GetFieldValue((short)1,strtmp);
			fvalue=_wtof(strtmp);
			theLang.LoadString(str2,IDS_REFUNDAMOUNT);
			m_strResult.Append(FormatString(str2,20,bSms));
			m_strResult.Append(FormatString(fvalue,7));
			m_strResult.Append(_T("\r\n"));
			rs.GetFieldValue((short)0,strtmp);
			int num=(_wtof(strtmp)+0.5);//四舍五入
			theLang.LoadString(str2,IDS_REFUNDNUMS);
			m_strResult.Append(FormatString(str2,20,bSms));
			m_strResult.Append(FormatString(num,7));
			m_strResult.Append(_T("\r\n"));
		}
		rs.Close();
		strSQL.Format(_T("select count(*),round(sum(should_amount),2) from order_head"));
		rs.Open( CRecordset::forwardOnly,strSQL);
		if (!rs.IsEOF())
		{
			m_strResult.Append(_T("\r\n"));
			rs.GetFieldValue((short)0,strtmp);
			int num=_wtoi(strtmp);
			theLang.LoadString(str2,IDS_UNPAYNUMS);
			m_strResult.Append(FormatString(str2,20,bSms));
			m_strResult.Append(FormatString(num,7));
			m_strResult.Append(_T("\r\n"));
			rs.GetFieldValue((short)1,strtmp);
			fvalue=_wtof(strtmp);
			theLang.LoadString(str2,IDS_UNPAYAMOUNT);
			m_strResult.Append(FormatString(str2,20,bSms));
			m_strResult.Append(FormatString(fvalue,7));
			m_strResult.Append(_T("\r\n"));
		}
		rs.Close();
	}

	if(bSms==FALSE)
		m_edit.SetWindowText(m_strResult);
	else
		m_strResult.Remove(' ');
}
/************************************************************************
* 函数介绍：菜品销售明细
* 输入参数：
* 输出参数：
* 返回值  ：
************************************************************************/
void CReportDlg::ShowReport3()
{
	OpenDatabase();
	CRecordset rs(&theDB);
	CRecordset rs2(&theDB);
	CString strSQL,str2;
	CString fvalue;
	CDBVariant variant;
	int field_len[5]={5,18,6,5,6};
	int filed_size=5;
	if(m_bShortFormat)
	{
		field_len[0]=4;
		field_len[1]=15;
		field_len[2]=4;
		field_len[3]=4;
		field_len[4]=0;
		filed_size=4;
	}

	m_strResult.Empty();
	theLang.LoadString(m_strResult,IDS_RPTDISHT);

	double total=0;
	double quantity=0;
	strSQL.Format(_T("select * from major_group union (select -1,\'NULL\')"));
	rs.Open( CRecordset::forwardOnly,strSQL);
	while (!rs.IsEOF())
	{
		rs.GetFieldValue(_T("major_group_id"),fvalue);
		rs.GetFieldValue(_T("major_group_name"),str2);
		
		strSQL.Format(_T("{CALL c_item_sales(\'%s\',\'%s\',\'%s\')}"),m_strStartDate,m_strEndDate,fvalue);
		rs2.Open( CRecordset::forwardOnly,strSQL);
		if (rs2.GetRecordCount()>0)
		{
			m_strResult.AppendFormat(_T("\r\n<<  %s  >>\r\n"),str2);
			m_strResult.Append(_T("------------------------\r\n"));
		}
		while (!rs2.IsEOF())
		{
			CString fvalue;
			for(int i=0;i<filed_size;i++)
			{
				rs2.GetFieldValue(i,fvalue);
				if(i==1)
				{//缩短名字
					CString str;
					str.Format(_T("%s"),fvalue);
					int t=GetPrintLength(str)-field_len[i];
					int index=str.GetLength()-1;
					while (t>0)
					{
						TCHAR unicode=str.GetAt(index);
						if (unicode==0)
							break;
						if (unicode > 255)
							t-=2;
						else
							t--;
						str.Delete(index);
						index--;
					}
					fvalue=str;
				}
				if(i==3)
				{//数量 右对齐
					int num=_wtof(fvalue);
					quantity+=_wtof(fvalue);
					m_strResult.Append(FormatString(num,field_len[i]));
				}
				else if(i==4)
				{//销售额 右对齐
					double num=_wtof(fvalue);
					m_strResult.AppendFormat(_T(" %5.1f"),num);
					//m_strResult.Append(FormatString(fvalue,field_len[i]));
				}
				else
					m_strResult.Append(FormatString(fvalue,field_len[i]));
			}
			total+=_wtof(fvalue);
			m_strResult.Append(_T("\r\n"));
			rs2.MoveNext();
		}
		rs2.Close();

		rs.MoveNext();
	}
	rs.Close();
	m_strResult.Append(_T("------------------------\r\n"));
	theLang.LoadString(str2,IDS_SALEDISHES);
	if(m_bShortFormat)
		m_strResult.AppendFormat(_T("\r\n%s: %0.0f\r\n"),str2,quantity);
	else
		m_strResult.AppendFormat(_T("\r\n%s: %0.0f / %0.2f\r\n"),str2,quantity,total);
	m_edit.SetWindowText(m_strResult);
}
/************************************************************************
* 函数介绍：退菜明细
* 输入参数：
* 输出参数：
* 返回值  ：
************************************************************************/
void CReportDlg::ShowReport2()
{
	OpenDatabase();
	CRecordset rs(&theDB);
	CString strSQL,str2;
	CString fvalue;
	CDBVariant variant;
	int field_len[4]={5,6,23,6};
	int filed_size=4;
	if(m_bShortFormat)
	{
		field_len[0]=4;
		field_len[1]=6;
		field_len[2]=16;
		field_len[3]=0;
		filed_size=3;
	}

	m_strResult.Empty();
// 	theLang.LoadString(m_strResult,IDS_RPTDISHT);
// 	m_strResult.Append(_T("\r\n"));
	double total=0;
	double quantity=0;
	strSQL.Format(_T("SELECT SUM(ABS(quantity)),unit,menu_item_name,SUM(ABS(actual_price)) FROM history_order_detail ")
		_T("WHERE menu_item_id>0 AND return_time>=\'%s\' AND return_time<=\'%s\' AND (is_return_item=1 OR quantity<0) GROUP BY menu_item_id")
		,m_strStartDate,m_strEndDate);
	rs.Open( CRecordset::forwardOnly,strSQL);
	while (!rs.IsEOF())
	{
		CString fvalue;
		for(int i=0;i<filed_size;i++)
		{
			rs.GetFieldValue(i,fvalue);
			if(i==2)
			{//缩短名字
				CString str;
				str.Format(_T("%s"),fvalue);
				int t=GetPrintLength(str)-field_len[i];
				int index=str.GetLength()-1;
				while (t>0)
				{
					TCHAR unicode=str.GetAt(index);
					if (unicode==0)
						break;
					if (unicode > 255)
						t-=2;
					else
						t--;
					str.Delete(index);
					index--;
				}
				fvalue=str;
			}
			if(i==0)
			{//数量 左对齐
				//int num=_wtof(fvalue);
				quantity+=_wtof(fvalue);
				CString format;
				format.Format(_T("%.2g"),_wtof(fvalue));
				m_strResult.Append(FormatString(format,field_len[i]));
			}
			else if(i==3)
			{//销售额 右对齐
				double num=_wtof(fvalue);
				m_strResult.AppendFormat(_T(" %5.1f"),num);
				total+=num;
			}
			else
				m_strResult.Append(FormatString(fvalue,field_len[i]));
		}
		m_strResult.Append(_T("\r\n"));
		rs.MoveNext();
	}
	rs.Close();
	m_strResult.Append(_T("------------------------\r\n"));
	theLang.LoadString(str2,IDS_SUBTOTAL);
	if(m_bShortFormat)
		m_strResult.AppendFormat(_T("\r\n%s: %0.0f\r\n"),str2,quantity);
	else
		m_strResult.AppendFormat(_T("\r\n%s: %0.0f / %0.2f\r\n"),str2,quantity,total);
	m_edit.SetWindowText(m_strResult);
}
HBRUSH CReportDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	return hbr;
}

void CReportDlg::OnBnClickedCurday()
{
	CTime time_c=CTime::GetCurrentTime();
	if ( macrosInt[_T("USE_SALE_TIME")]==0)
	{
		m_toDate.SetTime(&time_c);
		m_fromDate.SetTime(&time_c);
	}
	else 
	{//跨天营业
		if (time_c.GetHour()<m_eodTime.GetHour())
		{
			m_toDate.SetTime(&time_c);
			time_c+=CTimeSpan(-1,0,0,0);
			m_fromDate.SetTime(&time_c);
		}
		else
		{
			m_fromDate.SetTime(&time_c);
			time_c+=CTimeSpan(1,0,0,0);
			m_toDate.SetTime(&time_c);
		}
	}
	ShowReport();
}

void CReportDlg::OnBnClickedLastday()
{
	CTime time_c=CTime::GetCurrentTime();
	time_c+=CTimeSpan(-1,0,0,0);
	if ( macrosInt[_T("USE_SALE_TIME")]==0)
	{
		m_toDate.SetTime(&time_c);
		m_fromDate.SetTime(&time_c);
	}
	else
	{//跨天营业
		if (time_c.GetHour()<m_eodTime.GetHour())
		{
			m_toDate.SetTime(&time_c);
			time_c+=CTimeSpan(-1,0,0,0);
			m_fromDate.SetTime(&time_c);
		}
		else
		{
			m_fromDate.SetTime(&time_c);
			time_c+=CTimeSpan(1,0,0,0);
			m_toDate.SetTime(&time_c);
		}
	}
	ShowReport();
}

void CReportDlg::OnBnClickedCurmonth()
{
	CTime time_c=CTime::GetCurrentTime();
	time_c=CTime(time_c.GetYear(),time_c.GetMonth(),1,0,0,0);
	m_fromDate.SetTime(&time_c);
	int year=time_c.GetYear();
	int month=time_c.GetMonth()+1;
	if (month>12)
	{
		month=1;
		year++;
	}
	time_c=CTime(year,month,1,0,0,0);
	if ( macrosInt[_T("USE_SALE_TIME")]==0)
	{
		time_c+=CTimeSpan(-1,0,0,0);
	}
	m_toDate.SetTime(&time_c);
	ShowReport();
}

void CReportDlg::OnBnClickedLastmonth()
{
	CTime time_c=CTime::GetCurrentTime();
	time_c=CTime(time_c.GetYear(),time_c.GetMonth(),1,0,0,0);
	if ( macrosInt[_T("USE_SALE_TIME")]==0)
	{
		time_c+=CTimeSpan(-1,0,0,0);
		m_toDate.SetTime(&time_c);
		int year=time_c.GetYear();
		int month=time_c.GetMonth();
		time_c=CTime(year,month,1,0,0,0);
		m_fromDate.SetTime(&time_c);
	}
	else
	{
		m_toDate.SetTime(&time_c);
		int year=time_c.GetYear();
		int month=time_c.GetMonth()-1;
		if (month<=0)
		{
			month=12;
			year--;
		}
		time_c=CTime(year,month,1,0,0,0);
		m_fromDate.SetTime(&time_c);
	}
	ShowReport();
}

void CReportDlg::OnPaint()
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
