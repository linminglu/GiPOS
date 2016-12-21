// ViewReserveDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "POSClient.h"
#include "ReserveDlg.h"
#include "ReserveAddDlg.h"


// ViewReserveDlg 对话框

IMPLEMENT_DYNAMIC(ReserveDlg, CPosPage2)

ReserveDlg::ReserveDlg(CWnd* pParent /*=NULL*/)
	: CPosPage2(ReserveDlg::IDD)
{
	m_lSelOrderId=0;
}

ReserveDlg::~ReserveDlg()
{
}

void ReserveDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_ADD, m_btnAdd);
	DDX_Control(pDX, IDC_LIST2, m_listCtrl);
	DDX_Control(pDX, IDC_BUTTON_PRE, m_btnPrepage);
	DDX_Control(pDX, IDC_BUTTON_GOTO,m_btnGoto);
}


BEGIN_MESSAGE_MAP(ReserveDlg, CDialog)
	ON_WM_SIZE()
	ON_WM_CTLCOLOR()
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_BUTTON_PRE, &ReserveDlg::OnBnClickedButtonPre)
	ON_BN_CLICKED(IDC_BUTTON_GOTO, &ReserveDlg::OnBnClickedButtonGoto)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &ReserveDlg::OnBnClickedButtonAdd)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST2, &ReserveDlg::OnLvnItemchangedList2)
	ON_MESSAGE(WM_MESSAGE_REFRESH,OnMsgRefresh)
END_MESSAGE_MAP()


// ViewReserveDlg 消息处理程序

void ReserveDlg::OnSize(UINT nType, int cx, int cy)
{
	CPosPage2::OnSize(nType, cx, cy);
	cx=CreatButton::m_nFullWidth;
	cy=CreatButton::m_nFullHeight;
	int width=(int)(cx*0.4);
	int height=30;
	if (m_listCtrl.m_hWnd)
	{
		int line_y1=35*cy/768;
		height=28*cy/768;
		int bt_width=cx*0.12;
		m_listCtrl.MoveWindow(20,(int)(cy*0.23),cx-40,(int)(cy*0.75));
		int bt_height=72;
		m_btnAdd.MoveWindow(20,10,bt_width,bt_height);
		m_btnGoto.MoveWindow(40+bt_width,10,bt_width,bt_height);
		m_btnPrepage.MoveWindow((int)(cx*0.86),10,bt_width,bt_height);
	}

}

BOOL ReserveDlg::OnInitDialog()
{
	CPosPage2::InitDialog(_T("Picture\\pickup.png"));
	CString str2;
	m_listCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_HEADERDRAGDROP);

	theLang.LoadString(str2,IDS_TIMESPAN);
	m_listCtrl.InsertColumn(0,str2,LVCFMT_LEFT,300);
	theLang.LoadString(str2,IDS_FMNAME);
	m_listCtrl.InsertColumn(1,str2,LVCFMT_LEFT,100);
	theLang.LoadString(str2,IDS_PHONE);
	m_listCtrl.InsertColumn(2,str2,LVCFMT_LEFT,200);
	theLang.LoadString(str2,IDS_TBLNAME);
	m_listCtrl.InsertColumn(3,str2,LVCFMT_LEFT,100);
	theLang.LoadString(str2,IDS_GUESTNUM);
	m_listCtrl.InsertColumn(4,str2,LVCFMT_LEFT,100);
	theLang.LoadString(str2,IDS_STATUS);
	m_listCtrl.InsertColumn(5,str2,LVCFMT_LEFT,100);


	theLang.LoadString(str2,IDS_PREPAGE);
	m_btnPrepage.SetWindowText(str2);
	m_btnPrepage.SetImage(_T("Picture\\class\\prepage.png"));
	m_btnPrepage.SetTextColor(DEFALUT_TXT_COLOR);

	theLang.LoadString(str2,IDS_ADDRESERVE);
	m_btnAdd.SetWindowText(str2);
	m_btnAdd.SetImage(_T("Picture\\bt_orange_71.png"));
	m_btnAdd.SetTextColor(DEFALUT_TXT_COLOR);

	theLang.LoadString(str2,IDS_PROCESS);
	m_btnGoto.SetWindowText(str2);
	m_btnGoto.SetImage(_T("Picture\\bt_orange_71.png"));
	m_btnGoto.SetTextColor(DEFALUT_TXT_COLOR);

	ShowOrders();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
LRESULT ReserveDlg::OnMsgRefresh(WPARAM wParam, LPARAM lParam)
{
	ShowOrders();
	return 0;
}
void ReserveDlg::ShowOrders()
{
	m_listCtrl.DeleteAllItems();
	CString strSQL;
	strSQL.Format(_T("SELECT pre_order.*,`tables`.table_name AS name2 FROM pre_order LEFT JOIN `tables` ON pre_order.table_id=`tables`.table_id WHERE TIMESTAMPDIFF(MINUTE,NOW(),arrived_time)>-60 AND pre_order_status<3 ORDER BY arrived_time DESC"));
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
		rs.GetFieldValue(_T("pre_order_id"),variant);
		m_listCtrl.SetItemData(nRow,variant.m_lVal);
		rs.GetFieldValue(_T("arrived_time"),strValue);
		m_listCtrl.SetItemText(nRow,0,strValue);
		rs.GetFieldValue(_T("customer_name"),strValue);
		m_listCtrl.SetItemText(nRow,1,strValue);
		rs.GetFieldValue(_T("telephone_1"),strValue);
		m_listCtrl.SetItemText(nRow,2,strValue);
		rs.GetFieldValue(_T("name2"),strValue);
		m_listCtrl.SetItemText(nRow,3,strValue);
		rs.GetFieldValue(_T("customer_num"),strValue);
		m_listCtrl.SetItemText(nRow,4,strValue);
		rs.GetFieldValue(_T("pre_order_status"),variant);
		if(variant.m_iVal==1)
			theLang.LoadString(IDS_PRE_PENDING,strValue);
		else if(variant.m_iVal==2)
			theLang.LoadString(IDS_PRE_CONFIRM,strValue);
		m_listCtrl.SetItemText(nRow,5,strValue);
		rs.MoveNext();

	}
	rs.Close();
}

void ReserveDlg::OnBnClickedButtonPre()
{
	CPosPage2::OnCancel();
}

void ReserveDlg::OnBnClickedButtonGoto()
{
	ReserveAddDlg* pDlg=new ReserveAddDlg();
	pDlg->m_lOrderId=m_lSelOrderId;
	pDlg->m_hParent=this;
	pDlg->Create(IDD_RESERVEADD,theApp.m_pMain);
	pDlg->ShowWindow(SW_SHOW);
	pDlg->SetFocus();
}

void ReserveDlg::OnBnClickedButtonAdd()
{
	ReserveAddDlg* pDlg=new ReserveAddDlg();
	pDlg->m_hParent=this;
	pDlg->Create(IDD_RESERVEADD,theApp.m_pMain);
	pDlg->ShowWindow(SW_SHOW);
	pDlg->SetFocus();
}

void ReserveDlg::OnLvnItemchangedList2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	if(pNMLV->uChanged==LVIF_STATE
		&&(pNMLV->uNewState&LVIS_SELECTED))
	{
		int nRow=pNMLV->iItem;
		m_lSelOrderId=m_listCtrl.GetItemData(nRow);
	}
	*pResult = 0;
}
