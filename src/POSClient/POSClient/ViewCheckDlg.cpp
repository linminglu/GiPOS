#include "stdafx.h"
#include "POSClient.h"
#include "ViewCheckDlg.h"
#include "OrderDlg.h"
#include "FloorDlg.h"
#include "FloorChooseDlg.h"
#include "ReportDlg.h"
#include "PayDlg.h"
#include "NumberInputDlg.h"

// ViewCheckDlg 对话框

IMPLEMENT_DYNAMIC(ViewCheckDlg, CPosPage)

ViewCheckDlg::ViewCheckDlg(CWnd* pParent /*=NULL*/)
: CPosPage(ViewCheckDlg::IDD)
{
	m_nActive=-1;
	m_nOrderHeadid=0;
	m_bSetBg=FALSE;
}

ViewCheckDlg::~ViewCheckDlg(void)
{
	while(!m_orderList.IsEmpty())
	{
		OrderDetail* item=m_orderList.GetTail();
		m_orderList.RemoveTail();
		delete item;
	}
}
void ViewCheckDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_LOG, m_logCtrl);
	DDX_Control(pDX, IDC_STATIC_TIME, m_timeCtrl);
	DDX_Control(pDX, IDC_STATIC_GUEST, m_guestCtrl);
	DDX_Control(pDX, IDC_STATIC_TABLE, m_tableCtrl);
	DDX_Control(pDX, IDC_STATIC_CHECK, m_checkCtrl);
	DDX_Control(pDX, IDC_LIST2, m_listCtrl);
	DDX_Control(pDX, IDC_BUTTON_PRE, m_btnPrepage);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_datetimeCtrl);
	DDX_Control(pDX, IDC_BUTTON_PRINT, m_btPrint);
	DDX_Control(pDX, IDC_BUTTON_PREPRINT,m_btPrePrint);
	DDX_Control(pDX, IDC_BUTTON_INVOICE, m_btInvoice);
	DDX_Control(pDX, IDC_BUTTON_REOPEN,m_btReopen);
	DDX_Control(pDX, IDC_BUTTON_NUM, m_btTable);
	DDX_Control(pDX, IDC_BUTTON_TIPS, m_btTips);
	DDX_Control(pDX, IDC_BUTTON_PRINT_SERIAL,m_btPrintSerial);
}
BEGIN_MESSAGE_MAP(ViewCheckDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_PRE, &ViewCheckDlg::OnBnClickedButtonPre)
	ON_WM_SIZE()
	ON_WM_CTLCOLOR()
	ON_WM_ERASEBKGND()
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST2, &ViewCheckDlg::OnLvnItemchangedList2)
	ON_NOTIFY(DTN_CLOSEUP, IDC_DATETIMEPICKER1, &ViewCheckDlg::OnDtnCloseupDatetimepicker1)
	ON_BN_CLICKED(IDC_BUTTON_NUM, &ViewCheckDlg::OnBnClickedButtonNum)
	ON_BN_CLICKED(IDC_BUTTON_PRINT, &ViewCheckDlg::OnBnClickedButtonPrint)
	ON_BN_CLICKED(IDC_BUTTON_INVOICE, &ViewCheckDlg::OnBnClickedButtonInvoice)
	ON_BN_CLICKED(IDC_BUTTON_REOPEN, &ViewCheckDlg::OnBnClickedButtonReopen)
	ON_BN_CLICKED(IDC_BUTTON_PREPRINT, &ViewCheckDlg::OnBnClickedButtonPreprint)
	ON_BN_CLICKED(IDC_BUTTON_TIPS, &ViewCheckDlg::OnBnClickedButtonTips)
	ON_BN_CLICKED(IDC_BUTTON_PRINT_SERIAL, &ViewCheckDlg::OnBnClickedButtonPrintSerial)
END_MESSAGE_MAP()
BOOL ViewCheckDlg::OnInitDialog()
{
	CPosPage::InitDialog(_T("Picture\\viewcheck.png"));
	m_checkDlg.Create(IDD_CHECK,this);
	m_checkDlg.ShowWindow(SW_SHOW);

	CString str2;
	m_listCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_HEADERDRAGDROP);
	theLang.LoadString(str2,IDS_SERIAL);
	m_listCtrl.InsertColumn(0,str2,LVCFMT_LEFT,80);
	if(theApp.m_bQuickService)
	{
		theLang.LoadString(str2,IDS_CHKNAME2);
		m_listCtrl.InsertColumn(1,str2,LVCFMT_LEFT,80);
	}
	else
	{
		theLang.LoadString(str2,IDS_TBLNAME);
		m_listCtrl.InsertColumn(1,str2,LVCFMT_LEFT,80);
	}
	theLang.LoadString(str2,IDS_SUBCHK);
	m_listCtrl.InsertColumn(2,str2,LVCFMT_LEFT,60);
	theLang.LoadString(str2,IDS_GUESTNUM);
	m_listCtrl.InsertColumn(3,str2,LVCFMT_LEFT,60);
	theLang.LoadString(str2,IDS_AMOUNT);
	m_listCtrl.InsertColumn(4,str2,LVCFMT_LEFT,100);
	theLang.LoadString(str2,IDS_CLOSETIME);
	m_listCtrl.InsertColumn(5,str2,LVCFMT_LEFT,220);
	theLang.LoadString(str2,IDS_EMPLOYE);
	m_listCtrl.InsertColumn(6,str2,LVCFMT_LEFT,100);
	theLang.LoadString(str2,IDS_CHKNAME);
	m_listCtrl.InsertColumn(7,str2,LVCFMT_LEFT,80);
	theLang.LoadString(str2,IDS_INVOICE);
	m_listCtrl.InsertColumn(8,str2,LVCFMT_LEFT,100);
	theLang.LoadString(str2,IDS_ADRESS);
	m_listCtrl.InsertColumn(9,str2,LVCFMT_LEFT,200);
	
	m_datetimeCtrl.SetFormat(_T("yyyy-MM-dd"));

	theLang.LoadString(str2,IDS_PREPAGE);
	m_btnPrepage.SetWindowText(str2);
	m_btnPrepage.SetImage(_T("Picture\\class\\prepage.png"));
	theLang.LoadString(str2,IDS_PRINT);
	m_btPrint.SetWindowText(str2);
	m_btPrint.SetImage(_T("Picture\\bt_orange_71.png"));
	theLang.LoadString(str2,IDS_PREPRINT);
	m_btPrePrint.SetWindowText(str2);
	m_btPrePrint.SetImage(_T("Picture\\bt_orange_71.png"));
	theLang.LoadString(str2,IDS_INVOICE);
	m_btInvoice.SetWindowText(str2);
 	m_btInvoice.SetImage(_T("Picture\\bt_orange_71.png"));
	theLang.LoadString(str2,IDS_REOPEN);
	m_btReopen.SetWindowText(str2);
 	m_btReopen.SetImage(_T("Picture\\bt_orange_71.png"));
	theLang.LoadString(str2,IDS_TBLNAME);
	m_btTable.SetWindowText(str2);
	m_btTable.SetImage(_T("Picture\\bt_orange_71.png"));
	theLang.LoadString(str2,IDS_TIPS);
	m_btTips.SetWindowText(str2);
	m_btTips.SetImage(_T("Picture\\bt_orange_71.png"));
	//theLang.LoadString(str2,IDS_PRINT_SERIAL);
	//m_btPrintSerial.SetWindowText(str2);
	m_btPrintSerial.SetImage(_T("Picture\\bt_orange_71.png"));

	m_logCtrl.SetFont(&theApp.m_txtFont);
	m_checkCtrl.SetFont(&theApp.m_txtFont);
	m_tableCtrl.SetFont(&theApp.m_txtFont);
	m_guestCtrl.SetFont(&theApp.m_txtFont);
	m_timeCtrl.SetFont(&theApp.m_txtFont);

	ResetButton();
#ifndef EN_VERSION
	m_btTips.ShowWindow(SW_HIDE);
#endif
	return FALSE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

/************************************************************************
重设按钮颜色，强制重绘
************************************************************************/
void ViewCheckDlg::ResetButton()
{
	m_btPrint.SetTextColor(DEFALUT_TXT_COLOR);
	m_btPrePrint.SetTextColor(DEFALUT_TXT_COLOR);
	m_btInvoice.SetTextColor(DEFALUT_TXT_COLOR);
	m_btnPrepage.SetTextColor(DEFALUT_TXT_COLOR);
	m_btReopen.SetTextColor(DEFALUT_TXT_COLOR);
	m_btTable.SetTextColor(DEFALUT_TXT_COLOR);
	m_btTips.SetTextColor(DEFALUT_TXT_COLOR);
	m_btPrintSerial.SetTextColor(DEFALUT_TXT_COLOR);
}

void ViewCheckDlg::OnSetActive()
{
	CPosPage::OnSetActive();
	try{
		if(theLang.pageSet[_T("IDD_VIEWCHK")]==0)
		{
			theLang.pageSet[_T("IDD_VIEWCHK")]=1;
			CString str2;
			theLang.LoadString(str2,IDS_PRINT);
			m_btPrint.SetWindowText(str2);
			theLang.LoadString(str2,IDS_PREPRINT);
			m_btPrePrint.SetWindowText(str2);
			theLang.LoadString(str2,IDS_INVOICE);
			m_btInvoice.SetWindowText(str2);
			theLang.LoadString(str2,IDS_PREPAGE);
			m_btnPrepage.SetWindowText(str2);
			theLang.LoadString(str2,IDS_TBLNAME);
			m_btTable.SetWindowText(str2);
			theLang.LoadString(str2,IDS_REOPEN);
			m_btReopen.SetWindowText(str2);
			theLang.LoadString(str2,IDS_TIPS);
			m_btTips.SetWindowText(str2);
			theLang.LoadString(str2,IDS_PRINT_SERIAL);
			m_btPrintSerial.SetWindowText(str2);
			ResetButton();

			HDITEM htItem = {0};
			htItem.mask = HDI_TEXT;
			theLang.LoadString(str2,IDS_SERIAL);
			htItem.pszText = (LPTSTR)(LPCTSTR)str2;
			m_listCtrl.GetHeaderCtrl()->SetItem(0, &htItem);

			if(theApp.m_bQuickService)
			{
				theLang.LoadString(str2,IDS_CHKNAME2);
				htItem.pszText = (LPTSTR)(LPCTSTR)str2;
				m_listCtrl.GetHeaderCtrl()->SetItem(1, &htItem);
			}
			else
			{
				theLang.LoadString(str2,IDS_TBLNAME);
				htItem.pszText =(LPTSTR)(LPCTSTR) str2;
				m_listCtrl.GetHeaderCtrl()->SetItem(1, &htItem);
			}
			theLang.LoadString(str2,IDS_SUBCHK);
			htItem.pszText = (LPTSTR)(LPCTSTR)str2;
			m_listCtrl.GetHeaderCtrl()->SetItem(2, &htItem);
			theLang.LoadString(str2,IDS_GUESTNUM);
			htItem.pszText = (LPTSTR)(LPCTSTR)str2;
			m_listCtrl.GetHeaderCtrl()->SetItem(3, &htItem);
			theLang.LoadString(str2,IDS_AMOUNT);
			htItem.pszText = (LPTSTR)(LPCTSTR)str2;
			m_listCtrl.GetHeaderCtrl()->SetItem(4, &htItem);
			theLang.LoadString(str2,IDS_CLOSETIME);
			htItem.pszText = (LPTSTR)(LPCTSTR)str2;
			m_listCtrl.GetHeaderCtrl()->SetItem(5, &htItem);
			theLang.LoadString(str2,IDS_EMPLOYE);
			htItem.pszText = (LPTSTR)(LPCTSTR)str2;
			m_listCtrl.GetHeaderCtrl()->SetItem(6, &htItem);
			theLang.LoadString(str2,IDS_CHKNAME);
			htItem.pszText = (LPTSTR)(LPCTSTR)str2;
			m_listCtrl.GetHeaderCtrl()->SetItem(7, &htItem);
			theLang.LoadString(str2,IDS_INVOICE);
			htItem.pszText = (LPTSTR)(LPCTSTR)str2;
			m_listCtrl.GetHeaderCtrl()->SetItem(8, &htItem);
			theLang.LoadString(str2,IDS_ADRESS);
			htItem.pszText = (LPTSTR)(LPCTSTR)str2;
			m_listCtrl.GetHeaderCtrl()->SetItem(9, &htItem);
		}
		m_checkDlg.m_nStatus=1;
		m_checkDlg.ResetContent();
		//查询当天的已结单
		CString strSQL;
		if(macrosInt[_T("FOOD_COURT")]==0)
		{
			strSQL.Format(_T("SELECT * FROM history_order_head  AS h LEFT JOIN invoices i ON (h.order_head_id=i.order_head_id AND h.check_id=i.check_id)")
				_T(" WHERE date(order_end_time)=curdate() ORDER BY h.order_head_id"));
		}
		else
		{//美食广场只能查看本机的数据
			strSQL.Format(_T("SELECT * FROM history_order_head  AS h LEFT JOIN invoices i ON (h.order_head_id=i.order_head_id AND h.check_id=i.check_id)")
				_T(" WHERE date(order_end_time)=curdate() AND pos_device_id=%d ORDER BY h.order_head_id"),theApp.m_nDeviceId);
		}
		ShowOrderheads(strSQL);
		UpdateCheckData();
		strSQL.Format(_T("select dayend_time FROM total_statistics LIMIT 1"));
		CRecordset rs( &theDB);
		if(rs.Open(-1,strSQL))
		{
			if(!rs.IsEOF())
			{
				CDBVariant variant;
				rs.GetFieldValue((short)0,variant);
				m_dayendTime= CTime(variant.m_pdate->year,variant.m_pdate->month,variant.m_pdate->day,
					variant.m_pdate->hour,variant.m_pdate->minute,variant.m_pdate->second);
			}
		}
		
	}
	catch(...)
	{
		LOG4CPLUS_ERROR(log_pos,"Catch Exception GetLastError="<<GetLastError());
	}
}
void ViewCheckDlg::ShowOrderheads(CString strSQL)
{
	m_listCtrl.DeleteAllItems();
	CRecordset rs( &theDB);
	if(!rs.Open(-1,strSQL))
	{
		LOG4CPLUS_ERROR(log_pos,"CRecordset Open Failed");
		return;
	}
	while(!rs.IsEOF())
	{
		CString strValue;
		CDBVariant variant;
		rs.GetFieldValue(_T("order_head_id"),strValue);
		int nRow=m_listCtrl.InsertItem(0, _T(""));
		m_listCtrl.SetItemText(nRow,0,strValue);
		rs.GetFieldValue(_T("check_number"),variant);
		m_listCtrl.SetItemData(nRow,variant.m_lVal);
		rs.GetFieldValue(_T("table_id"),variant);
		BOOL bQuickService=FALSE;
		if(variant.m_lVal<0)
			bQuickService=TRUE;
		if(bQuickService)
		{
			rs.GetFieldValue(_T("check_name"),strValue);
			m_listCtrl.SetItemText(nRow,1,strValue);
		}
		else
		{
			rs.GetFieldValue(_T("table_name"),strValue);
			m_listCtrl.SetItemText(nRow,1,strValue);
		}
		rs.GetFieldValue(_T("check_id"),strValue);
		m_listCtrl.SetItemText(nRow,2,strValue);
		rs.GetFieldValue(_T("customer_num"),strValue);
		m_listCtrl.SetItemText(nRow,3,strValue);
		rs.GetFieldValue(_T("actual_amount"),strValue);
		double damount=_wtof(strValue);
		strValue.Format(_T("%0.2f"),damount);
		m_listCtrl.SetItemText(nRow,4,strValue);
		rs.GetFieldValue(_T("order_end_time"),strValue);
		m_listCtrl.SetItemText(nRow,5,strValue);
		rs.GetFieldValue(_T("open_employee_name"),strValue);
		m_listCtrl.SetItemText(nRow,6,strValue);
		rs.GetFieldValue(_T("check_name"),strValue);
		m_listCtrl.SetItemText(nRow,7,strValue);
		rs.GetFieldValue(_T("amount"),strValue);
		m_listCtrl.SetItemText(nRow,8,strValue);
		try{
			rs.GetFieldValue(_T("delivery_info"),strValue);
			m_listCtrl.SetItemText(nRow,9,strValue);
		}catch(...){
		}
		rs.MoveNext();
	}
	rs.Close();
	m_nActive=-1;
	m_listCtrl.SetItemState(0,LVIS_SELECTED,LVIS_SELECTED |LVIS_FOCUSED);
}
/************************************************************************
* 函数介绍：更新账单信息
* 输入参数：
* 输出参数：
* 返回值  ：
************************************************************************/
void ViewCheckDlg::UpdateCheckData()
{
	try{
		m_checkDlg.ResetContent(FALSE);
		m_checkDlg.LockWindowUpdate();
		POSITION pos=NULL;
		CString strTmp;
		for(pos=m_orderList.GetHeadPosition();pos!=NULL;)
		{
			POSITION prePos=pos;
			OrderDetail* item=m_orderList.GetNext(pos);
			if(m_checkDlg.AddOrderItem(item,FALSE)>=0)
			{//进行了合并，从总列表中删除
				m_orderList.RemoveAt(prePos);
				delete item;
			}
		}
		//刷新小计
		m_checkDlg.UpdateSubtotal();
		m_checkDlg.UnlockWindowUpdate();
	}
	catch(...)
	{
		LOG4CPLUS_ERROR(log_pos,"Catch Exception GetLastError="<<GetLastError());
	}
}

void ViewCheckDlg::OnSize(UINT nType, int cx, int cy)
{
	CPosPage::OnSize(nType, cx, cy);
	cx=CreatButton::m_nFullWidth;
	cy=CreatButton::m_nFullHeight;
	int width=(int)(cx*0.4);
	int height=30;
	if (m_logCtrl.m_hWnd)
	{
		int line_y1=35*cy/768;
		height=28*cy/768;
		int bt_width=cx*0.12;
		int line_y2=line_y1+height;
		m_logCtrl.MoveWindow(25,line_y1,95,height);
		m_checkCtrl.MoveWindow(140*cx/1024,line_y1,220*cx/1024,height);
		m_tableCtrl.MoveWindow(25,line_y2,115*cx/1024,height);
		m_guestCtrl.MoveWindow(140*cx/1024,line_y2,115*cx/1024,height);
		m_timeCtrl.MoveWindow(245*cx/1024,line_y2,95*cx/1024,height);

		m_listCtrl.MoveWindow((int)(cx*0.36),(int)(cy*0.23),(int)(cx*0.62),(int)(cy*0.75));
		m_datetimeCtrl.MoveWindow((int)(cx*0.4),50,(int)(cx*0.18),height);
		int bt_height=72;
		m_btPrint.MoveWindow((int)(cx*0.61),25,bt_width,bt_height);
		m_btInvoice.MoveWindow((int)(cx*0.735),25,bt_width,bt_height);
		m_btnPrepage.MoveWindow((int)(cx*0.86),25,bt_width,bt_height);
		
		m_btTips.MoveWindow((int)(cx*0.36),30+bt_height,bt_width,bt_height);
		m_btPrintSerial.MoveWindow((int)(cx*0.485),30+bt_height,bt_width,bt_height);
		m_btPrePrint.MoveWindow((int)(cx*0.61),30+bt_height,bt_width,bt_height);
		m_btTable.MoveWindow((int)(cx*0.735),30+bt_height,bt_width,bt_height);
		m_btReopen.MoveWindow((int)(cx*0.86),30+bt_height,bt_width,bt_height);
		

		m_checkDlg.MoveWindow(23*cx/1024,100,328*cx/1024,(int)(cy*0.8));
	}
	CWnd* pCtrl=GetDlgItem(IDC_STATIC1);
	if (pCtrl)
	{
		pCtrl->MoveWindow((int)(cx*0.4),50+cy/10,(int)(cx*0.16),height);
	}
}
void ViewCheckDlg::OnBnClickedButtonPre()
{
	theApp.m_pMain->SetActivePage(m_nPrePage,TRUE);
}

void ViewCheckDlg::OnLvnItemchangedList2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	if(pNMLV->uChanged==LVIF_STATE
		&&(pNMLV->uNewState&LVIS_SELECTED))
	{
		int nRow=pNMLV->iItem;
		m_nOrderHeadid=_wtol(m_listCtrl.GetItemText(nRow,0));
		m_nCheckNum=m_listCtrl.GetItemData(nRow);
		m_nActive=_wtoi(m_listCtrl.GetItemText(nRow,2));
		CString strCloseTime=m_listCtrl.GetItemText(nRow,5);
		int   nYear,   nMonth,   nDate,   nHour,   nMin,   nSec;
		swscanf(strCloseTime,_T("%d-%d-%d   %d:%d:%d"),   &nYear,   &nMonth,   &nDate,   &nHour,   &nMin,   &nSec);
		CTime time_close(nYear,   nMonth,   nDate,   nHour,   nMin,   nSec);
		if(time_close>m_dayendTime){
			m_btReopen.ShowWindow(SW_SHOW);
		}else{
			m_btReopen.ShowWindow(SW_HIDE);
		}
		try{
			while(!m_orderList.IsEmpty())
			{
				OrderDetail* item=m_orderList.GetTail();
				m_orderList.RemoveTail();
				delete item;
			}
			CString strSQL;
			strSQL.Format(_T("SELECT history_order_detail.*,item_name2 FROM history_order_detail LEFT JOIN menu_item ON menu_item_id=item_id WHERE order_head_id=\'%d\' AND check_id=\'%d\' AND is_return_item=0;")
				,m_nOrderHeadid,m_nActive);
			FloorDlg::GetOrderDetail(strSQL,&m_orderList);
			if(CMainSheet::m_iStaticsInfo&0x08)
			{
				strSQL.Format(_T("SELECT tax_amount FROM history_order_head WHERE order_head_id=\'%d\' AND check_id=\'%d\'"),m_nOrderHeadid,m_nActive);
				CRecordset rs( &theDB);
				CString strVal;
				rs.Open( CRecordset::forwardOnly,strSQL);
				if(!rs.IsEOF())
				{
					rs.GetFieldValue(_T("tax_amount"),strVal);
					m_checkDlg.m_fTax=_wtof(strVal);
				}
				rs.Close();
			}
			UpdateCheckData();
			
			CString str2,tmpMsg;
			m_strUser=m_listCtrl.GetItemText(nRow,6);
			m_logCtrl.SetWindowText(m_strUser);
			tmpMsg=m_listCtrl.GetItemText(nRow,5);
			m_strInvoice=m_listCtrl.GetItemText(nRow,8);
			tmpMsg=tmpMsg.Right(8);
			//theApp.m_strBeginDate=tmpMsg.Left(tmpMsg.GetLength()-9);
			m_timeCtrl.SetWindowText(tmpMsg);
			
			theLang.LoadString(str2,IDS_GUESTNUM);
			m_nGuests=_wtoi(m_listCtrl.GetItemText(nRow,3));
			tmpMsg.Format(_T("%s:%d"),str2,m_nGuests);
			m_guestCtrl.SetWindowText(tmpMsg);
			if(theApp.m_bQuickService)
			{
				theLang.LoadString(str2,IDS_CHKNAME2);
			}
			else
			{
				theLang.LoadString(str2,IDS_TBLNAME);
			}
			CString strChkName=m_listCtrl.GetItemText(nRow,1);
			tmpMsg.Format(_T("%s:%s"),str2,strChkName);
			m_tableCtrl.SetWindowText(tmpMsg);
			theLang.LoadString(str2,IDS_CHKNUM);
			tmpMsg.Format(_T("%s%05d/%d"),str2,m_nCheckNum,m_nActive);
			m_checkCtrl.SetWindowText(tmpMsg);
			CRect rc=CRect(0,0,360*CreatButton::m_nFullWidth/1024,150*CreatButton::m_nFullHeight/768);
			InvalidateRect(rc); 
		}catch(...)
		{
		}
	}
	*pResult = 0;
}
void ViewCheckDlg::OnBnClickedSearch()
{
	m_nOrderHeadid=0;
	CString strSQL;
	m_datetimeCtrl.GetWindowText(m_strDate);
	if(macrosInt[_T("FOOD_COURT")]==0)
	{
		strSQL.Format(_T("SELECT * FROM history_order_head AS h LEFT JOIN invoices i ON (h.order_head_id=i.order_head_id AND h.check_id=i.check_id) WHERE date(order_end_time)='%s' ORDER BY h.order_head_id")
			,m_strDate);
	}
	else
	{//美食广场
		strSQL.Format(_T("SELECT * FROM history_order_head AS h LEFT JOIN invoices i ON (h.order_head_id=i.order_head_id AND h.check_id=i.check_id) WHERE date(order_end_time)='%s' AND pos_device_id=%d ORDER BY h.order_head_id")
			,m_strDate,theApp.m_nDeviceId);
	}
	ShowOrderheads(strSQL);
}
void ViewCheckDlg::OnDtnCloseupDatetimepicker1(NMHDR *pNMHDR, LRESULT *pResult)
{
	
	OnBnClickedSearch();
	*pResult = 0;
}
/************************************************************************
* 函数介绍：设置小费金额
* 输入参数：
* 输出参数：
* 返回值  ：
************************************************************************/
void ViewCheckDlg::OnBnClickedButtonTips()
{
	try{
		if (m_nActive<0)
			return;
		LOG4CPLUS_INFO(log_pos,"PayDlg::OnBnClickedButtonTips Begin");
		OpenDatabase();
		CString strSQL;
		NumberInputDlg dlg;
		strSQL.Format(_T("SELECT tips_amount FROM history_order_head WHERE order_head_id=%d AND check_id=%d"),m_nOrderHeadid,m_nActive);
		CRecordset rs( &theDB);
		CString cvalue,str2;
		rs.Open( CRecordset::forwardOnly,strSQL);
		if (!rs.IsEOF())
		{
			rs.GetFieldValue((short)0,cvalue);
		}
		rs.Close();
		theLang.LoadString(dlg.m_strHint,IDS_TIPS);
		if (!cvalue.IsEmpty())
		{
			theLang.LoadString(str2,IDS_ORIGNALINVOICE);
			dlg.m_strHint.AppendFormat(str2,cvalue);
		}
		double amount;
		if(dlg.DoModal()!=IDOK)
			return;
		if (dlg.m_strNum.IsEmpty())
			return;
		amount=_wtof(dlg.m_strNum);
		//更新数据库
		strSQL.Format(_T("UPDATE history_order_head SET tips_amount=%0.2f WHERE order_head_id=%d AND check_id=%d")
			,amount,m_nOrderHeadid,m_nActive);
		theDB.ExecuteSQL(strSQL);
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
void ViewCheckDlg::OnBnClickedButtonNum()
{
	CFloorChooseDlg dlg;
	if(dlg.DoModal()==IDCANCEL)
		return;
	//m_editCtrl.SetWindowText(dlg.);
	CString strSQL;
	m_datetimeCtrl.GetWindowText(m_strDate);
	if(macrosInt[_T("FOOD_COURT")]==0)
	{
		strSQL.Format(_T("SELECT * FROM history_order_head AS h LEFT JOIN invoices i ON (h.order_head_id=i.order_head_id AND h.check_id=i.check_id) WHERE date(order_end_time)='%s' AND h.table_id=%d ORDER BY h.order_head_id")
		,m_strDate,dlg.m_nTableId);
	}
	else
	{//美食广场
		strSQL.Format(_T("SELECT * FROM history_order_head AS h LEFT JOIN invoices i ON (h.order_head_id=i.order_head_id AND h.check_id=i.check_id) WHERE date(order_end_time)='%s' AND h.table_id=%d  AND pos_device_id=%d ORDER BY h.order_head_id")
		,m_strDate,dlg.m_nTableId,theApp.m_nDeviceId);
	}
	ShowOrderheads(strSQL);
}

void ViewCheckDlg::OnBnClickedButtonPreprint()
{
	if (m_nActive<0)
		return;
	PrintDeviceInfo printer;
	if(theApp.m_prePrinter.nDeviceType==-1)
	{
		if (theApp.m_payPrinter.nDeviceType==-1||theApp.m_prePrinter.nPaperWidth==0)
		{//没有配置打印机，无法打印
			POSMessageBox(IDS_NOPREPRINT);
			return;
		}
		printer=theApp.m_payPrinter;
	}
	else
		printer=theApp.m_prePrinter;
	CString userid;
	int auth=OrderDlg::RequeastAuth(userid,_T("reprint_check"));
	if (auth!=0)
		return;
	LOG4CPLUS_INFO(log_pos,"ViewCheckDlg::OnBnClickedButtonPrint Begin");
	int active=m_nActive-1;
	CRecordset rs( &theDB);
	CString strSQL,cvalue;
	int nPrint=0;
	{//不在head中，查询history
		strSQL.Format(_T("SELECT print_count FROM history_order_head WHERE order_head_id=%d AND check_id=%d;")
			,m_nOrderHeadid,m_nActive);
		rs.Open( CRecordset::forwardOnly,strSQL);
		if (!rs.IsEOF())
		{
			rs.GetFieldValue((short)0,cvalue);
			nPrint=_wtoi(cvalue);
		}
		strSQL.Format(_T("UPDATE history_order_head SET print_count=print_count+1 WHERE order_head_id=%d AND check_id=%d;")
			,m_nOrderHeadid,m_nActive);
		theDB.ExecuteSQL(strSQL);
	}
	rs.Close();
	nPrint++;
	JSONVALUE root;
	root[_T("template")]=TEMPLATE_PREPAY;
	root[_T("print_count")]=nPrint;
	root[_T("reprint")]=1;//重印
	PayDlg::FormatPrint(root,printer,m_checkDlg,active);
	ReFormatTableInfo(root);
	CPOSClientApp::PrintJson(root);
}
void ViewCheckDlg::OnBnClickedButtonPrint()
{
	if (m_nActive<0)
		return;
	PrintDeviceInfo printer;
	if(theApp.m_payPrinter.nDeviceType==-1)
	{
		if (theApp.m_prePrinter.nDeviceType==-1||theApp.m_prePrinter.nPaperWidth==0)
		{//没有配置打印机，无法打印
			POSMessageBox(IDS_NOPREPRINT);
			return;
		}
		printer=theApp.m_prePrinter;
	}
	else
		printer=theApp.m_payPrinter;
	CString userid;
	int auth=OrderDlg::RequeastAuth(userid,_T("reprint_check"));
	if (auth!=0)
		return;
	LOG4CPLUS_INFO(log_pos,"ViewCheckDlg::OnBnClickedButtonPrint Begin");
	int active=m_nActive-1;
	CRecordset rs( &theDB);
	CString strSQL,cvalue;
	int nPrint=0;
	{//不在head中，查询history
		strSQL.Format(_T("SELECT print_count FROM history_order_head WHERE order_head_id=%d AND check_id=%d;")
		,m_nOrderHeadid,m_nActive);
		rs.Open( CRecordset::forwardOnly,strSQL);
		if (!rs.IsEOF())
		{
			rs.GetFieldValue((short)0,cvalue);
			nPrint=_wtoi(cvalue);
		}
		strSQL.Format(_T("UPDATE history_order_head SET print_count=print_count+1,raw_talbe=1 WHERE order_head_id=%d AND check_id=%d")
		,m_nOrderHeadid,m_nActive);
		theDB.ExecuteSQL(strSQL);
	}
	rs.Close();
	nPrint++;
	JSONVALUE root;
	root[_T("template")]=TEMPLATE_PAY;
	root[_T("print_count")]=nPrint;
	root[_T("reprint")]=1;//重印
	PayDlg::FormatPrint(root,printer,m_checkDlg,active);
	ReFormatTableInfo(root);
	CPOSClientApp::PrintJson(root);
}
void ViewCheckDlg::ReFormatTableInfo(JSONVALUE& root)
{
	root[_T("serial")]=m_nOrderHeadid;
	root[_T("emp_name")]=theApp.m_strUserName;
	root[_T("chk_num")]=m_nCheckNum;
	root[_T("gst_num")]=m_nGuests;

	CString strSQL;
	strSQL.Format(_T("SELECT * FROM history_order_head WHERE order_head_id=%d AND check_id=%d"),m_nOrderHeadid,m_nActive);
	CRecordset rs( &theDB);
	if(!rs.Open(-1,strSQL))
	{
		LOG4CPLUS_ERROR(log_pos,"CRecordset Open Failed");
		return;
	}
	if(!rs.IsEOF())
	{
		CString strVal;
		CDBVariant variant;
		rs.GetFieldValue(_T("table_name"),strVal);
		root[_T("tbl_name")]=strVal;
		rs.GetFieldValue(_T("check_name"),strVal);
		root[_T("chk_name")]=strVal;
		rs.GetFieldValue(_T("table_id"),variant);
		root[_T("tbl_id")]=variant.m_lVal;
		rs.GetFieldValue(_T("order_start_time"),strVal);
		root[_T("open_time")]=strVal;

		rs.GetFieldValue(_T("eat_type"),variant);
		if(variant.m_iVal==TYPE_DINE)
			root[_T("eat_di")]=1;
		else
			root[_T("eat_ta")]=1;
		rs.GetFieldValue(_T("delivery_info"),strVal);
		if (!strVal.IsEmpty())
		{
			root[_T("tainfo")]=strVal;
		}
	}
}
/************************************************************************
* 函数介绍：设置发票金额
* 输入参数：
* 输出参数：
* 返回值  ：
************************************************************************/
void ViewCheckDlg::OnBnClickedButtonInvoice()
{
	try{
		if (m_nActive<0)
			return;
		LOG4CPLUS_INFO(log_pos,"ViewCheckDlg::OnBnClickedButtonInvoice Begin");
		OpenDatabase();
		CString strSQL;
		NumberInputDlg dlg;
		theLang.LoadString(dlg.m_strHint,IDS_INVOCENUM);
		if (!m_strInvoice.IsEmpty())
		{
			CString str2;
			theLang.LoadString(str2,IDS_ORIGNALINVOICE);
			dlg.m_strHint.AppendFormat(str2,m_strInvoice);
		}
		double amount;
		if(dlg.DoModal()!=IDOK)
			return;
		if (dlg.m_strNum.IsEmpty())
			return;
		amount=_wtof(dlg.m_strNum);
		//更新数据库
		if(m_strInvoice.IsEmpty())
		{
			strSQL.Format(_T("INSERT INTO invoices(order_head_id, check_id,amount,employee_id,edit_time,pos_device_id)")
				_T(" VALUES(%d,%d,\'%g\',%s,now(),%d)"),m_nOrderHeadid,m_nActive,amount,theApp.m_strUserID,theApp.m_nDeviceId);
		}
		else
		{
			strSQL.Format(_T("UPDATE invoices SET amount=\'%g\',employee_id=%s,edit_time=now(),pos_device_id=%d")
				_T(" WHERE order_head_id=%d AND check_id=%d"),amount,theApp.m_strUserID,theApp.m_nDeviceId,m_nOrderHeadid,m_nActive);
		}
		theDB.ExecuteSQL(strSQL);
		//刷新显示
		OnBnClickedSearch();
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
BOOL ViewCheckDlg::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message==WM_KEYDOWN)
	{
		switch (pMsg->wParam)
		{
		case VK_RETURN:
			return TRUE;
		case VK_ESCAPE:
			this->SendMessage(WM_COMMAND,IDC_BUTTON_PRE);
			return TRUE;
		}
	}
	return CDialog::PreTranslateMessage(pMsg);
}

void ViewCheckDlg::OnBnClickedButtonReopen()
{
	if (m_nActive<0)
		return;
	try{
		CString userid;
		int auth=OrderDlg::RequeastAuth(userid,_T("edit_check"));
		if (auth!=0)
			return;
		long headid=m_nOrderHeadid;
		int tableId=0;
		int checkId=m_nActive;
		CString strSQL;
		strSQL.Format(_T("SELECT table_id FROM history_order_head WHERE order_head_id=%d AND check_id=%d"),m_nOrderHeadid,m_nActive);
		CRecordset rs( &theDB);
		if(!rs.Open(-1,strSQL))
		{
			LOG4CPLUS_ERROR(log_pos,"CRecordset Open Failed");
			return;
		}
		if(!rs.IsEOF())
		{
			CDBVariant variant;
			rs.GetFieldValue(_T("table_id"),variant);
			tableId=variant.m_lVal;
		}
		if(tableId>0)
		{//查询桌子是否已被占用
			CRecordset rs( &theDB);
			strSQL.Format(_T("SELECT COUNT(*) FROM order_head WHERE table_id=\'%d\';"),tableId);
			rs.Open(-1,strSQL);
			CString strCount;
			rs.GetFieldValue((short)0,strCount);
			if (strCount!="0")
			{
				POSMessageBox(IDS_INUSING);
				return ;
			}
		}
		CString strDetail,str1,str2;
		theLang.LoadString(str1,IDS_SERIAL);
		strDetail.Format(_T("%s:%d/%d  %s:%0.2f"),str1,headid,checkId,theApp.CURRENCY_SYMBOL,m_checkDlg.m_fDebt);
		CPOSClientApp::CriticalLogs(OPR_ABORTPAY,strDetail);
		//恢复数据库
		strSQL.Format(_T("CALL revert_check(%d,%d);"),headid,checkId);
		theDB.ExecuteSQL(strSQL);
		//填写反结帐员工名称
		strSQL.Format(_T("UPDATE order_head SET edit_employee_name='%s' WHERE order_head_id=%d AND check_id=%d")
			,theApp.m_strUserName,headid,checkId);
		theDB.ExecuteSQL(strSQL);
		//删除抹零
		strSQL.Format(_T("DELETE FROM order_detail WHERE discount_id=-1 AND order_head_id=%d AND check_id=%d")
			,headid,checkId);
		theDB.ExecuteSQL(strSQL);
		POSMessageBox(IDS_REOPENCHK);
		//刷新显示
		OnBnClickedSearch();
	}
	catch(...)
	{
		LOG4CPLUS_ERROR(log_pos,"Catch Exception GetLastError="<<GetLastError());
	}
}
BOOL ViewCheckDlg::OnEraseBkgnd(CDC* pDC)
{
	if (m_bpBackgrd==NULL)
	{
		return FALSE;
	}
	CDC MemDc;
	MemDc.CreateCompatibleDC(pDC);
	MemDc.SelectObject(m_bpBackgrd);
	pDC->SetStretchBltMode(HALFTONE);
	pDC->StretchBlt(0,0,CreatButton::m_nFullWidth,CreatButton::m_nFullHeight,&MemDc,0,0,m_x,m_y,SRCCOPY);
	if(m_bSetBg==FALSE)
	{
		m_bSetBg=TRUE;
		m_btPrint.SetBkGnd(pDC,TRUE);
		m_btPrePrint.SetBkGnd(pDC,TRUE);
		m_btInvoice.SetBkGnd(pDC,TRUE);
		m_btnPrepage.SetBkGnd(pDC,TRUE);
		m_btReopen.SetBkGnd(pDC,TRUE);
		m_btTable.SetBkGnd(pDC,TRUE);
		m_btTips.SetBkGnd(pDC,TRUE);
		m_btPrintSerial.SetBkGnd(pDC,TRUE);
	}
	return TRUE;
}

void ViewCheckDlg::OnBnClickedButtonPrintSerial()
{
	CString userid;
	int auth=OrderDlg::RequeastAuth(userid,_T("manager_privilege"),3);
	if(auth!=0)
		return;
	LOG4CPLUS_INFO(log_pos,"ViewCheckDlg::OnBnClickedButtonPrintSerial");
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

	CString strResult;
	int size=m_listCtrl.GetItemCount();
	for(int i=size-1;i>=0;i--)
	{
		long head_id=_wtol(m_listCtrl.GetItemText(i,0));
		strResult.AppendFormat(_T("%09d  "),head_id);
		
		strResult.Append(CReportDlg::FormatString(m_listCtrl.GetItemText(i,1),8));
		int nCheck=_wtoi(m_listCtrl.GetItemText(i,2));
		double amount=_wtof(m_listCtrl.GetItemText(i,4));
		strResult.Append(CReportDlg::FormatString(amount,8));
		strResult.Append(_T("\r\n"));
	}

	JSONVALUE root;
	CPOSClientApp::FormatPrintDevice(root,printer);
	root[_T("template")]=TEMPLATE_REPORT;
	root[_T("head")]=_T("Serial Report");
	root[_T("open_time")]=m_strDate;
	root[_T("message")]=strResult;
	CTime time_to=CTime::GetCurrentTime();
	root[_T("time")]=time_to.Format(_T("%Y-%m-%d %H:%M:%S"));
	CPOSClientApp::PrintJson(root);
}
