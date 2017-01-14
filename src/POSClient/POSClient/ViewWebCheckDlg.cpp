// ViewWebCheckDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "POSClient.h"
#include "FloorDlg.h"
#include "FloorViewDlg.h"
#include "ViewWebCheckDlg.h"


// ViewWebCheckDlg 对话框

IMPLEMENT_DYNAMIC(ViewWebCheckDlg, CPosPage2)

ViewWebCheckDlg::ViewWebCheckDlg(CWnd* pParent /*=NULL*/)
	: CPosPage2(ViewWebCheckDlg::IDD)
{
	m_nType=1;
	m_textColor=RGB(0,0,0);
}

ViewWebCheckDlg::~ViewWebCheckDlg()
{
}

void ViewWebCheckDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_TABLE, m_tableCtrl);
	DDX_Control(pDX, IDC_LIST2, m_listCtrl);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_datetimeCtrl);
	DDX_Control(pDX, IDC_BUTTON_PRE, m_btnPrepage);
	DDX_Control(pDX, IDC_BUTTON_GOTO,m_btnGoto);
}


BEGIN_MESSAGE_MAP(ViewWebCheckDlg, CDialog)
	ON_WM_SIZE()
	ON_WM_CTLCOLOR()
	ON_WM_ERASEBKGND()
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST2, &ViewWebCheckDlg::OnLvnItemchangedList2)
	ON_NOTIFY(DTN_CLOSEUP, IDC_DATETIMEPICKER1, &ViewWebCheckDlg::OnDtnCloseupDatetimepicker1)
	ON_BN_CLICKED(IDC_BUTTON_PRE, &ViewWebCheckDlg::OnBnClickedButtonPre)
	ON_BN_CLICKED(IDC_BUTTON_GOTO, &ViewWebCheckDlg::OnBnClickedButtonGoto)
END_MESSAGE_MAP()


// ViewWebCheckDlg 消息处理程序

void ViewWebCheckDlg::OnSize(UINT nType, int cx, int cy)
{
	CPosPage2::OnSize(nType, cx, cy);
	cx=CreatButton::m_nFullWidth;
	cy=CreatButton::m_nFullHeight;
	int width=(int)(cx*0.4);
	int height=30;
	if (m_checkDlg.m_hWnd)
	{
		int line_y1=35*cy/768;
		height=28*cy/768;
		int bt_width=cx*0.12;
		int line_y2=line_y1+height;
		m_tableCtrl.MoveWindow(25,line_y1,328*cx/1024,height*2);

		m_listCtrl.MoveWindow((int)(cx*0.36),(int)(cy*0.23),(int)(cx*0.62),(int)(cy*0.75));
		m_datetimeCtrl.MoveWindow((int)(cx*0.4),50,(int)(cx*0.18),height);
		int bt_height=72;

		m_btnPrepage.MoveWindow((int)(cx*0.86),25,bt_width,bt_height);
		m_btnGoto.MoveWindow((int)(cx*0.72),25,bt_width,bt_height);
		m_checkDlg.MoveWindow(23*cx/1024,100,328*cx/1024,(int)(cy*0.8));
	}

}

BOOL ViewWebCheckDlg::OnInitDialog()
{
	m_checkDlg.Create(IDD_CHECK,this);
	m_checkDlg.ShowWindow(SW_SHOW);
	CPosPage2::InitDialog(_T("Picture\\viewcheck.png"));
	CString str2;
	m_listCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_HEADERDRAGDROP);

	theLang.LoadString(str2,IDS_SERIAL);
	m_listCtrl.InsertColumn(0,str2,LVCFMT_LEFT,80);
	theLang.LoadString(str2,IDS_AMOUNT);
	m_listCtrl.InsertColumn(1,str2,LVCFMT_LEFT,100);
	theLang.LoadString(str2,IDS_ADRESS);
	m_listCtrl.InsertColumn(2,str2,LVCFMT_LEFT,300);
	theLang.LoadString(str2,IDS_TIMESPAN);
	m_listCtrl.InsertColumn(3,str2,LVCFMT_LEFT,100);
	theLang.LoadString(str2,IDS_STATUS);
	m_listCtrl.InsertColumn(4,str2,LVCFMT_LEFT,80);

	m_datetimeCtrl.SetFormat(_T("yyyy-MM-dd"));

	theLang.LoadString(str2,IDS_PREPAGE);
	m_btnPrepage.SetWindowText(str2);
	m_btnPrepage.SetImage(_T("Picture\\class\\prepage.png"));
	m_btnPrepage.SetTextColor(DEFALUT_TXT_COLOR);

	theLang.LoadString(str2,IDS_GOTOCHK);
	m_btnGoto.SetWindowText(str2);
	m_btnGoto.SetImage(_T("Picture\\bt_orange_71.png"));
	m_btnGoto.SetTextColor(DEFALUT_TXT_COLOR);
	m_btnGoto.ShowWindow(SW_HIDE);
	LRESULT lret=1;
	OnDtnCloseupDatetimepicker1(0,&lret);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void ViewWebCheckDlg::OnBnClickedButtonPre()
{
	CPosPage2::OnCancel();
}
/************************************************************************
* 函数介绍：更新账单信息
* 输入参数：
* 输出参数：
* 返回值  ：
************************************************************************/
void ViewWebCheckDlg::UpdateCheckData()
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
void ViewWebCheckDlg::OnLvnItemchangedList2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	if(pNMLV->uChanged==LVIF_STATE
		&&(pNMLV->uNewState&LVIS_SELECTED))
	{
		int nRow=pNMLV->iItem;
		m_nOrderHeadid=_wtol(m_listCtrl.GetItemText(nRow,0));
		CString strCloseTime=m_listCtrl.GetItemText(nRow,3);

		try{
			while(!m_orderList.IsEmpty())
			{
				OrderDetail* item=m_orderList.GetTail();
				m_orderList.RemoveTail();
				delete item;
			}
			CString strSQL;
			m_nType=m_listCtrl.GetItemData(nRow);
			if(m_nType==0)
			{
				strSQL.Format(_T("SELECT order_detail.*,item_name2 FROM order_detail LEFT JOIN menu_item ON menu_item_id=item_id WHERE order_head_id=\'%d\' AND check_id=1 AND is_return_item=0;")
					,m_nOrderHeadid);
				if(!theApp.m_bQuickService)
					m_btnGoto.ShowWindow(SW_SHOW);
			}
			else
			{
				strSQL.Format(_T("SELECT history_order_detail.*,item_name2 FROM history_order_detail LEFT JOIN menu_item ON menu_item_id=item_id WHERE order_head_id=\'%d\' AND check_id=1 AND is_return_item=0;")
					,m_nOrderHeadid);
				m_btnGoto.ShowWindow(SW_HIDE);
			}
			FloorDlg::GetOrderDetail(strSQL,&m_orderList);
			if(CMainSheet::m_iStaticsInfo&0x08)
			{
				if(m_nType==0)
					strSQL.Format(_T("SELECT tax_amount FROM order_head WHERE order_head_id=\'%d\' AND check_id=1'"),m_nOrderHeadid);
				else
					strSQL.Format(_T("SELECT tax_amount FROM history_order_head WHERE order_head_id=\'%d\' AND check_id=1'"),m_nOrderHeadid);
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
			tmpMsg=m_listCtrl.GetItemText(nRow,2);
			m_tableCtrl.SetWindowText(tmpMsg);
			CRect rc=CRect(0,0,360*CreatButton::m_nFullWidth/1024,150*CreatButton::m_nFullHeight/768);
			InvalidateRect(rc); 
		}catch(...)
		{
		}
	}
	*pResult = 0;
}
void ViewWebCheckDlg::OnDtnCloseupDatetimepicker1(NMHDR *pNMHDR, LRESULT *pResult)
{
	CString strDate,strSQL;
	CTime time_choose;
	m_datetimeCtrl.GetTime(time_choose);
	m_datetimeCtrl.GetWindowText(strDate);
	CTime time_now=CTime::GetCurrentTime();
	CTimeSpan span=time_choose-time_now;
	if(span.GetDays()==0)
	{
		strSQL.Format(_T("SELECT * FROM order_head WHERE customer_id=1 ORDER BY order_head_id DESC"));
		ShowOrderheads(strSQL,0);//order_head
	}
	else
	{
		m_listCtrl.DeleteAllItems();
	}
	
	strSQL.Format(_T("SELECT * FROM history_order_head WHERE customer_id=1 AND date(order_start_time)='%s' ORDER BY order_head_id DESC")
		,strDate);
	ShowOrderheads(strSQL,1);//history
	*pResult = 0;
}
void ViewWebCheckDlg::ShowOrderheads(CString strSQL,int type)
{
	if(type==0)
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
		int nRow=m_listCtrl.InsertItem(0, _T(""));
		m_listCtrl.SetItemData(nRow,type);
		rs.GetFieldValue(_T("order_head_id"),strValue);
		m_listCtrl.SetItemText(nRow,0,strValue);
		rs.GetFieldValue(_T("should_amount"),strValue);
		double should_amount=_wtof(strValue);
		strValue.Format(_T("%s")+theApp.m_decPlace,theApp.CURRENCY_SYMBOL,should_amount);
		m_listCtrl.SetItemText(nRow,1,strValue);
		
		rs.GetFieldValue(_T("table_id"),variant);
		if(variant.m_lVal<0)
		{
			rs.GetFieldValue(_T("delivery_info"),strValue);
			m_listCtrl.SetItemText(nRow,2,strValue);
		}
		else
		{
			rs.GetFieldValue(_T("table_name"),strValue);
			m_listCtrl.SetItemText(nRow,2,strValue);
		}
		rs.GetFieldValue(_T("order_start_time"),variant);
		CString strTime;
		strTime.Format(_T("%02d:%02d:%02d"),variant.m_pdate->hour,variant.m_pdate->minute,variant.m_pdate->second);
		m_listCtrl.SetItemText(nRow,3,strTime);
		rs.GetFieldValue(_T("actual_amount"),strValue);
		double actual_amount=_wtof(strValue);
		CString str2;
		if (actual_amount>0.01)
		{
			theLang.LoadString(str2,IDS_PAYED2);
			m_listCtrl.SetItemText(nRow,4,str2);
		}
		else
		{
			theLang.LoadString(str2,IDS_UNPAYED);
				m_listCtrl.SetItemText(nRow,4,str2);
		}
		rs.MoveNext();
	}
	rs.Close();
	m_listCtrl.SetItemState(0,LVIS_SELECTED,LVIS_SELECTED |LVIS_FOCUSED);
}

void ViewWebCheckDlg::OnBnClickedButtonGoto()
{
	if(m_nType>0||theApp.m_bQuickService)
		return;
	FloorViewDlg* pOrder=(FloorViewDlg*)theApp.m_pMain->GetPage(DLG_FLOOR);
	pOrder->m_headId=m_nOrderHeadid;
	pOrder->m_tableId=0;
	CString strSQL;
	strSQL.Format(_T("SELECT table_id FROM order_head WHERE order_head_id=%d"),m_nOrderHeadid);
	CRecordset rs( &theDB);
	rs.Open(-1,strSQL);
	if(!rs.IsEOF())
	{
		CDBVariant var;
		rs.GetFieldValue(_T("table_id"),var);
		pOrder->m_tableId=var.m_lVal;
	}
	
	pOrder->OnBnClickedOrder();
	CPosPage2::OnCancel();
}
