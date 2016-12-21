// ViewReserveAddDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "POSClient.h"
#include "ReserveAddDlg.h"

#define ITEM_COLUMNSIZE 6
#define ITEM_LINESIZE	6
// ViewReserveAddDlg 对话框

IMPLEMENT_DYNAMIC(ReserveAddDlg, CPosPage2)

ReserveAddDlg::ReserveAddDlg(CWnd* pParent /*=NULL*/)
	: CPosPage2(ReserveAddDlg::IDD)
{
	m_nPageSize=ITEM_LINESIZE*ITEM_COLUMNSIZE-2;//每页的大小，需扣除翻页按钮
	m_SelectedTable=NULL;
	m_nTableId=0;
	m_lOrderId=0;
}

ReserveAddDlg::~ReserveAddDlg()
{
}

void ReserveAddDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_PRE, m_btnPrepage);
	DDX_Control(pDX, IDOK, m_btnOK);
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_dateCtrl);
	DDX_Control(pDX, IDC_COMBO1, mComboBox);
}


BEGIN_MESSAGE_MAP(ReserveAddDlg, CDialog)
	ON_WM_SIZE()
	ON_WM_CTLCOLOR()
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_BUTTON_PRE, &ReserveAddDlg::OnBnClickedButtonPre)
	ON_BN_CLICKED(IDOK, &ReserveAddDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &ReserveAddDlg::OnBnClickedCancel)
	ON_CBN_SELCHANGE(IDC_COMBO1, &ReserveAddDlg::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON_LEFT, &ReserveAddDlg::OnBnClickedButtonLeft)
	ON_BN_CLICKED(IDC_BUTTON_RIGHT, &ReserveAddDlg::OnBnClickedButtonRight)
	ON_COMMAND_RANGE(IDC_TABLE0,IDC_TABLE0+999,&ReserveAddDlg::OnTableClicked)
END_MESSAGE_MAP()


// ViewReserveAddDlg 消息处理程序

void ReserveAddDlg::OnSize(UINT nType, int cx, int cy)
{
	CPosPage2::OnSize(nType, cx, cy);
	if (m_btnPrepage.m_hWnd)
	{
		int bt_width=cx*0.14;
		int bt_height=ScaleY(72);
		if(m_lOrderId>0)
		{
			int left=(cx-3*bt_width)/2;
			m_btnOK.MoveWindow(left,cy-90,bt_width,bt_height);
			left+=2*bt_width;
			m_btnCancel.MoveWindow(left,cy-90,bt_width,bt_height);
		}
		else
		{
			int left=(cx-bt_width)/2;
			m_btnOK.MoveWindow(left,cy-90,bt_width,bt_height);
		}
		bt_width=cx*0.12;
		m_btnPrepage.MoveWindow((int)(cx*0.86),10,bt_width,bt_height);
	}
}

BOOL ReserveAddDlg::OnInitDialog()
{
	CPosPage2::InitDialog(_T("Picture\\pickup.png"));
	CString str2;
	m_dateCtrl.SetFormat(_T("yyyy-MM-dd HH:mm"));

	theLang.LoadString(str2,IDS_PREPAGE);
	m_btnPrepage.SetWindowText(str2);
	m_btnPrepage.SetImage(_T("Picture\\class\\prepage.png"));
	m_btnPrepage.SetTextColor(DEFALUT_TXT_COLOR);

	theLang.LoadString(str2,IDS_OK);
	m_btnOK.SetWindowText(str2);
	m_btnOK.SetImage(_T("Picture\\bt_ok.png"));
	m_btnOK.SetTextColor(DEFALUT_TXT_COLOR);

	theLang.LoadString(str2,IDS_PRE_DELETE);
	m_btnCancel.SetWindowText(str2);
	m_btnCancel.SetImage(_T("Picture\\bt_cancel.png"));
	m_btnCancel.SetTextColor(DEFALUT_TXT_COLOR);

	theLang.LoadString(str2,IDS_FMNAME);
	GetDlgItem(IDC_STATIC_NAME)->SetWindowText(str2);
	theLang.LoadString(str2,IDS_PHONE);
	GetDlgItem(IDC_STATIC_PHONE)->SetWindowText(str2);
	theLang.LoadString(str2,IDS_ARRIVETIME);
	GetDlgItem(IDC_STATIC_TIME)->SetWindowText(str2);
	theLang.LoadString(str2,IDS_GUESTNUM);
	GetDlgItem(IDC_STATIC_GUEST)->SetWindowText(str2);
	theLang.LoadString(str2,IDS_TBLNAME);
	GetDlgItem(IDC_STATIC_TABLE1)->SetWindowText(str2);
	theLang.LoadString(str2,IDS_REMARK);
	GetDlgItem(IDC_STATIC_REMARK)->SetWindowText(str2);

	GetDlgItem(IDC_EDIT1)->SetWindowText(m_strUname);
	GetDlgItem(IDC_EDIT2)->SetWindowText(m_strPhone);

	try{
		//读取营业地点
		CRecordset rs( &theDB);
		CString strSQL;
		strSQL.Format(_T("SELECT * FROM rvc_center ORDER BY rvc_center_id"));
		if(rs.Open(CRecordset::forwardOnly,strSQL))
		{
			while(!rs.IsEOF())
			{
				CDBVariant variant;
				CString strName;
				rs.GetFieldValue(_T("rvc_center_id"),variant);
				rs.GetFieldValue(_T("rvc_center_name"),strName);
				int idx=mComboBox.AddString(strName);
				mComboBox.SetItemData(idx,variant.m_lVal);
				rs.MoveNext();
			}
		}
		rs.Close();
	}catch(...)
	{
	}
	//桌台按钮
	SIZE buttonSize;
	CString path;
	for(int i=0;i<6;i++)
	{
		path.Format(_T("Picture\\table%d.png"),i+1);
		m_bpTableStatus[i]=Gdiplus::Image::FromFile(path);
		if(i==0)
		{
			buttonSize.cx=ScaleX(m_bpTableStatus[i]->GetWidth());
			buttonSize.cy=ScaleY(m_bpTableStatus[i]->GetHeight());
		}
	}
	LOGFONT m_tLogFont;
	memset(&m_tLogFont,0,sizeof(LOGFONT));
	m_tLogFont.lfHeight	=ScaleX(20);
	wcscpy_s(m_tLogFont.lfFaceName, _T("Microsoft YaHei"));
	mTableFont.CreateFontIndirect(&m_tLogFont);
	for(int i=0;i<ITEM_LINESIZE;i++)
	{
		POINT topleft;
		topleft.y=ScaleY(120)+i*(buttonSize.cy+8);
		CString str2;
		for(int j=0;j<ITEM_COLUMNSIZE;j++)
		{
			int count=i*ITEM_COLUMNSIZE+j;
			topleft.x=CreatButton::m_nFullWidth/2+j*(buttonSize.cx+5);
			//最后2个按钮为翻页按钮
			if (count==m_nPageSize)
			{//前一页
				CRoundButton2* pBtn=new CRoundButton2;
				pBtn->Create(_T(""),WS_CHILD ,CRect(topleft,buttonSize),this,IDC_BUTTON_LEFT);
				pBtn->SetImage(_T("Picture\\bt_up.png"));
				m_itemButtons.push_back(pBtn);
			}
			else if (count==m_nPageSize+1)
			{//后一页
				CRoundButton2* pBtn=new CRoundButton2;
				pBtn->Create(_T(""),WS_CHILD ,CRect(topleft,buttonSize),this,IDC_BUTTON_RIGHT);
				pBtn->SetImage(_T("Picture\\bt_down.png"));
				m_itemButtons.push_back(pBtn);
			}
			else
			{
				CTableButton* pBtn=new CTableButton;
				pBtn->SetFont(&mTableFont);
				pBtn->Create(_T(""),WS_CHILD,CRect(topleft,buttonSize),this,IDC_TABLE0+count);
				pBtn->SetImages(m_bpTableStatus[0],m_bpTableStatus[0],false);
				m_itemButtons.push_back(pBtn);
			}
		}
	}
	CWnd* pTableText=GetDlgItem(IDC_STATIC_TABLE);
	pTableText->GetWindowRect(mRectHint);
	ScreenToClient(&mRectHint);
	if(m_lOrderId>0)
	{//修改
		CRecordset rs( &theDB);
		CString strSQL;
		strSQL.Format(_T("SELECT pre_order.*,`tables`.table_name AS name2 FROM pre_order LEFT JOIN `tables` ON pre_order.table_id=`tables`.table_id WHERE pre_order_id=%d"),m_lOrderId);
		if(rs.Open(CRecordset::forwardOnly,strSQL))
		{
			if(!rs.IsEOF())
			{
				CDBVariant variant;
				CString strVal;
				rs.GetFieldValue(_T("customer_name"),strVal);
				GetDlgItem(IDC_EDIT1)->SetWindowText(strVal);
				rs.GetFieldValue(_T("telephone_1"),strVal);
				GetDlgItem(IDC_EDIT2)->SetWindowText(strVal);
				rs.GetFieldValue(_T("name2"),strVal);
				GetDlgItem(IDC_STATIC_TABLE)->SetWindowText(strVal);
				rs.GetFieldValue(_T("table_id"),variant);
				m_nTableId=variant.m_lVal;
				rs.GetFieldValue(_T("arrived_time"),variant);
				CTime arriveTime= CTime(variant.m_pdate->year,variant.m_pdate->month,variant.m_pdate->day,variant.m_pdate->hour,variant.m_pdate->minute,0);
				m_dateCtrl.SetTime(&arriveTime);
				rs.GetFieldValue(_T("customer_num"),strVal);
				GetDlgItem(IDC_EDIT3)->SetWindowText(strVal);
				rs.GetFieldValue(_T("description"),strVal);
				GetDlgItem(IDC_EDIT4)->SetWindowText(strVal);
			}
		}
		rs.Close();
	}
	else
	{//新增
		m_btnCancel.ShowWindow(SW_HIDE);
		CTime cTime= CTime::GetCurrentTime()+CTimeSpan(1,0,0,0);
		CTime arriveTime( cTime.GetYear(), cTime.GetMonth(), cTime.GetDay(), cTime.GetHour(), 0, 0);
		m_dateCtrl.SetTime(&arriveTime);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
void ReserveAddDlg::OnTableClicked(UINT uID)
{
	UINT index=m_nCurrentPage*m_nPageSize+(uID-IDC_TABLE0);
	if (index>=m_RVCTables.size())
	{//越界
		LOG4CPLUS_ERROR(log_pos,"index=["<<index<<"] out of range. m_RVCTables.size()="<<m_RVCTables.size());
		return;
	}
	CTableButton* pButton2=(CTableButton*)GetDlgItem(uID);
	if (pButton2&&pButton2!=m_SelectedTable)
	{
		if(m_SelectedTable)
			m_SelectedTable->SetCheck(FALSE);
		pButton2->SetCheck(TRUE);
	}
	m_SelectedTable=pButton2;
	CWnd* pTableText=GetDlgItem(IDC_STATIC_TABLE);
	pTableText->SetWindowText(m_RVCTables[index].name);
	InvalidateRect(mRectHint);
	m_nTableId=m_RVCTables[index].id;
}
void ReserveAddDlg::OnBnClickedButtonPre()
{
	CPosPage2::OnCancel();
}

void ReserveAddDlg::OnBnClickedOk()
{
	CString strCusName,strTel,strTime,strDesc;
	GetDlgItem(IDC_EDIT1)->GetWindowText(strCusName);
	GetDlgItem(IDC_EDIT2)->GetWindowText(strTel);
	if(strCusName.IsEmpty()||strTel.IsEmpty())
		return;
	m_dateCtrl.GetWindowText(strTime);
	CString str;
	GetDlgItem(IDC_EDIT3)->GetWindowText(str);
	int nCustNum=_wtoi(str);
	GetDlgItem(IDC_EDIT4)->GetWindowText(strDesc);
	//插入记录
	CString strSQL;
	if(m_lOrderId>0)
	{
		strSQL.Format(_T("UPDATE pre_order SET customer_name=\'%s\',telephone_1=\'%s\',table_id=%d,customer_num=%d,description=\'%s\',arrived_time=\'%s\',pre_order_status=2")
			_T(",preorder_time=now() WHERE pre_order_id=%d"),strCusName,strTel,m_nTableId,nCustNum,strDesc,strTime,m_lOrderId);
	}
	else
	{
		strSQL.Format(_T("INSERT INTO pre_order(customer_name,telephone_1,table_id,customer_num,description,pre_order_status,preorder_time,arrived_time)")
			_T("VALUES (\'%s\',\'%s\',%d,%d,\'%s\',2,now(),\'%s\')"),strCusName,strTel,m_nTableId,nCustNum,strDesc,strTime);
	}
	theDB.ExecuteSQL(strSQL);
	strSQL.Format(_T("UPDATE webreport_setting SET soldoutp = 1"));
	theDB.ExecuteSQL(strSQL);
	//刷新父窗口显示
	::PostMessage(m_hParent->GetSafeHwnd(),WM_MESSAGE_REFRESH,0,0);
	CPosPage2::OnCancel();
}

void ReserveAddDlg::OnBnClickedCancel()
{
	if(m_lOrderId<=0)
		return;
	if(POSMessageBox(IDS_CANCELORDER,MB_YESNO)==IDCANCEL)
	{
		return;
	}
	CString strSQL;
	strSQL.Format(_T("UPDATE pre_order SET pre_order_status=5,preorder_time=now() WHERE pre_order_id=%d"),m_lOrderId);
	theDB.ExecuteSQL(strSQL);
	strSQL.Format(_T("UPDATE webreport_setting SET soldoutp = 1"));
	theDB.ExecuteSQL(strSQL);
	//刷新父窗口显示
	::PostMessage(m_hParent->GetSafeHwnd(),WM_MESSAGE_REFRESH,0,0);
	CPosPage2::OnCancel();
}

void ReserveAddDlg::OnCbnSelchangeCombo1()
{
	int idx=mComboBox.GetCurSel();
	int rvc_id=mComboBox.GetItemData(idx);
	m_RVCTables.clear();
	CString strDate;
	m_dateCtrl.GetWindowText(strDate);
	int   nYear,   nMonth,   nDate,   nHour,   nMin;
	swscanf(strDate,_T("%d-%d-%d %d:%d"),   &nYear,   &nMonth,   &nDate,   &nHour,   &nMin);
	CTime time_mid(nYear,   nMonth,   nDate,   nHour,   nMin,   0);
	CTime time_from=time_mid-CTimeSpan(0,4,0,0);
	CTime time_to=time_mid+CTimeSpan(0,4,0,0);
	//从数据库查询
	CString strSQL;
	strSQL.Format(_T("SELECT * FROM  tables LEFT JOIN (SELECT table_id,arrived_time FROM pre_order WHERE pre_order_status=2 AND arrived_time>='%s' AND arrived_time<='%s' GROUP BY table_id)AS P")
		_T(" ON `tables`.table_id=P.table_id WHERE `tables`.rvc_center_id=%d AND `tables`.table_id>0")
		,time_from.Format(_T("%Y-%m-%d %H:%M:%S")),time_to.Format(_T("%Y-%m-%d %H:%M:%S")),rvc_id);
	CRecordset rs( &theDB);
	if(!rs.Open(-1,strSQL))
	{
		LOG4CPLUS_ERROR(log_pos,"CRecordset Open Failed");
		return;
	}
	while(!rs.IsEOF())
	{
		TableItem table={0};
		CString strName;
		CDBVariant variant;
		rs.GetFieldValue(_T("table_id"),variant);
		table.id=variant.m_lVal;
		rs.GetFieldValue(_T("seat_num"),variant);
		table.seat_num=variant.m_iVal;
		rs.GetFieldValue(_T("rvc_center_id"),variant);
		table.rvc=variant.m_lVal;
		rs.GetFieldValue(_T("table_name"),strName);
		table.name.Format(_T("%s"),strName);
		variant.Clear();
		rs.GetFieldValue(_T("arrived_time"),variant);
		if(variant.m_dwType!=DBVT_NULL)
			table.open_time.Format(_T("%02d:%02d"),variant.m_pdate->hour,variant.m_pdate->minute);
		m_RVCTables.push_back(table);
		rs.MoveNext();
	}
	rs.Close();
	m_nCurrentPage=0;
	m_nPageCount=(int)ceil((float)m_RVCTables.size()/m_nPageSize);
	ShowCurrentPage();
}
/************************************************************************
* 函数介绍： 桌台显示翻页
* 输入参数：
* 输出参数：
* 返回值  ：
************************************************************************/
void ReserveAddDlg::OnBnClickedButtonLeft()
{
	if(m_nCurrentPage>0)
		m_nCurrentPage--;
	else
		return;
	ShowCurrentPage();
}

void ReserveAddDlg::OnBnClickedButtonRight()
{
	if(m_nCurrentPage<m_nPageCount-1)
		m_nCurrentPage++;
	else
		return;
	ShowCurrentPage();
}
/************************************************************************
* 函数介绍：显示当前页的桌子
* 输入参数：
* 输出参数：
* 返回值  ：
************************************************************************/
void ReserveAddDlg::ShowCurrentPage()
{
	try{
		unsigned int index;
		for(int i=0;i<m_nPageSize;i++)
		{
			index=i+m_nCurrentPage*m_nPageSize;
			CTableButton* pButton2=(CTableButton*)GetDlgItem(IDC_TABLE0+i);
			if(index<m_RVCTables.size())
			{
				TableItem table=m_RVCTables[index];
				if(table.open_time.IsEmpty())
				{
					pButton2->SetStrTop(_T(""));
					pButton2->SetImages(m_bpTableStatus[0],m_bpTableStatus[0],false);
				}
				else
				{
					pButton2->SetStrTop(table.open_time);
					pButton2->SetImages(m_bpTableStatus[1],m_bpTableStatus[1],false);
				}
				pButton2->SetWindowText(table.name);
				
				pButton2->Invalidate();
				pButton2->ShowWindow(SW_SHOW);
			}
			else
			{
				pButton2->ShowWindow(SW_HIDE);
			}
		}
		CWnd* pButton2=GetDlgItem(IDC_BUTTON_LEFT);
		if (m_nCurrentPage>0)
			pButton2->ShowWindow(SW_SHOW);
		else
			pButton2->ShowWindow(SW_HIDE);

		pButton2=GetDlgItem(IDC_BUTTON_RIGHT);
		if (m_nCurrentPage<m_nPageCount-1)
			pButton2->ShowWindow(SW_SHOW);
		else
			pButton2->ShowWindow(SW_HIDE);
	}
	catch(...)
	{
		LOG4CPLUS_ERROR(log_pos,"Catch Exception GetLastError="<<GetLastError());
	}
}

