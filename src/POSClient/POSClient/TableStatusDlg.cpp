// TableStatusDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "POSClient.h"
#include "TableStatusDlg.h"


// TableStatusDlg 对话框

IMPLEMENT_DYNAMIC(TableStatusDlg, CDialog)

TableStatusDlg::TableStatusDlg(CWnd* pParent /*=NULL*/)
	: CDialog(TableStatusDlg::IDD, pParent)
{

}

TableStatusDlg::~TableStatusDlg()
{
}

void TableStatusDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_infoList);
	DDX_Control(pDX, IDCANCEL, m_closeButton);
}


BEGIN_MESSAGE_MAP(TableStatusDlg, CDialog)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// TableStatusDlg 消息处理程序

BOOL TableStatusDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_closeButton.SetImage(_T("Picture\\bt_cancel.png"));
	CString line,str2;
	theLang.LoadString(str2,IDS_OK);
	m_closeButton.SetWindowText(str2);
	m_closeButton.SetTextColor(RGB(255,255,255));
	theLang.LoadString(str2,IDS_TBLNAME);
	line.Format(_T("%s:            %d"),str2,m_nTblID);
	m_infoList.AddString(line);
	try
	{
		OpenDatabase();
		CRecordset rs( &theDB);
		CString strSQL;
		strSQL.Format(_T("SELECT check_number,check_name,customer_num,open_employee_name,order_start_time,round(sum(should_amount),2) as total FROM order_head WHERE table_id=\'%d\';"),m_nTblID);
		rs.Open( CRecordset::forwardOnly,strSQL);
		while(!rs.IsEOF())
		{
			CDBVariant variant;
			rs.GetFieldValue(_T("check_number"), variant);
			if (variant.m_dwType==DBVT_NULL)
				break;
			
			theLang.LoadString(str2,IDS_CHKNUM);
			line.Format(_T("%s            %d"),str2,variant.m_lVal);
			m_infoList.AddString(line);
			CString strVal;
			rs.GetFieldValue(_T("check_name"), strVal);
			if (strVal.GetLength()!=0)
			{
				theLang.LoadString(str2,IDS_CHKNAME);
				line.Format(_T("%s:            %s"),str2,strVal);
				m_infoList.AddString(line);
			}

			rs.GetFieldValue(_T("customer_num"), variant);
			theLang.LoadString(str2,IDS_GUESTNUM);
			line.Format(_T("%s:            %d"),str2,variant.m_lVal);
			m_infoList.AddString(line);

			rs.GetFieldValue(_T("open_employee_name"), strVal);
			theLang.LoadString(str2,IDS_EMPSERVICE);
			line.Format(_T("%s         %s"),str2,strVal);
			m_infoList.AddString(line);

			rs.GetFieldValue(_T("order_start_time"), variant);
			theLang.LoadString(str2,IDS_OPENTIME);
			line.Format(_T("%s:      %d-%02d-%02d %02d:%02d:%02d"),str2,variant.m_pdate->year,variant.m_pdate->month,variant.m_pdate->day,
				variant.m_pdate->hour,variant.m_pdate->minute,variant.m_pdate->second);
			m_infoList.AddString(line);

			SYSTEMTIME st;
			GetLocalTime(&st);
			COleDateTime dTimeCurrent(st);
			COleDateTime dTimeOpen(variant.m_pdate->year,variant.m_pdate->month,variant.m_pdate->day,
				variant.m_pdate->hour,variant.m_pdate->minute,variant.m_pdate->second);
			COleDateTimeSpan   dTimeSpan=dTimeCurrent -dTimeOpen;
			int minutes=dTimeSpan.GetMinutes();
			int hours=(int)dTimeSpan.GetTotalHours();
			theLang.LoadString(str2,IDS_TIMEGO);
			CString str3,str4;
			theLang.LoadString(str3,IDS_HOUR);
			theLang.LoadString(str4,IDS_MINUTE);
			line.Format(_T("%s:      %d %s %d %s"),str2,hours,str3,minutes,str4);
			m_infoList.AddString(line);

			rs.GetFieldValue(_T("total"), strVal);
			theLang.LoadString(str2,IDS_AMOUNTDUE);
			line.Format(_T("%s:      %s%s"),str2,theApp.CURRENCY_SYMBOL,strVal);
			m_infoList.AddString(line);

			break;
		}
		rs.Close();
		strSQL.Format(_T("SELECT * FROM pre_order WHERE table_id=\'%d\' AND pre_order_status=2"),m_nTblID);
		rs.Open( CRecordset::forwardOnly,strSQL);
		if (!rs.IsEOF())
		{
			m_infoList.AddString(_T(""));
			CDBVariant variant;
			CString strTmp;
			rs.GetFieldValue(_T("customer_name"), strTmp);
			theLang.LoadString(str2,IDS_PREORDERCUS);
			line.Format(_T("%s:      %s"),str2,strTmp);
			m_infoList.AddString(line);

			rs.GetFieldValue(_T("telephone_1"), strTmp);
			theLang.LoadString(str2,IDS_PHONE);
			line.Format(_T("%s:          %s"),str2,strTmp);
			m_infoList.AddString(line);

			rs.GetFieldValue(_T("arrived_time"), variant);
			theLang.LoadString(str2,IDS_ARRIVETIME);
			line.Format(_T("%s:      %d-%02d-%02d %02d:%02d"),str2,variant.m_pdate->year,variant.m_pdate->month,
				variant.m_pdate->day,variant.m_pdate->hour,variant.m_pdate->minute);
			m_infoList.AddString(line);
		}
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
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void TableStatusDlg::OnPaint()
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
