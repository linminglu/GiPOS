#include "StdAfx.h"
#include "POSClient.h"
#include "FloorViewDlg.h"
#include "FunctionDlg.h"
#include "OrderDlg.h"
#include "PayDlg.h"
#include "NumberInputDlg.h"
#include "ViewWebCheckDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(FloorViewDlg, FloorDlg)

FloorViewDlg::FloorViewDlg(CWnd* pParent)
:FloorDlg(pParent)
{
	//m_nID=FloorViewDlg::IDD;
	ITEM_COLUMNSIZE=7;
	ITEM_LINESIZE=6;
	m_nPageSize=ITEM_LINESIZE*ITEM_COLUMNSIZE-2;//每页的大小，需扣除翻页按钮
	m_SelectedTable=NULL;
	m_SelectedRvc=NULL;
	m_tableId=0;
	m_headId=-1;
	for(int i=0;i<6;i++)
		m_bpTableStatus[i]=NULL;
}

FloorViewDlg::~FloorViewDlg(void)
{
	for (std::vector<CButton*>::iterator iter = m_itemButtons.begin(); iter!= m_itemButtons.end();iter++)
	{
		CButton *b = (*iter);
		b->DestroyWindow();
		delete b;
	}
	m_itemButtons.clear();
	for(int i=0;i<6;i++)
		delete m_bpTableStatus[i];
}
void FloorViewDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_LOG, m_logCtrl);
	DDX_Control(pDX, IDC_STATIC_TIME, m_time);
	DDX_Control(pDX, IDC_STATIC_TABLE, m_tableCtrl);
	DDX_Control(pDX, IDC_STATIC_CHECK, m_checkCtrl);
}
BEGIN_MESSAGE_MAP(FloorViewDlg, CDialog)
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_BUTTON_BEGIN, &FloorDlg::OnBnClickedBeginTable)
	ON_BN_CLICKED(IDC_BUTTON_PICKTAB, &FloorDlg::OnBnClickedPickTable)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, &FloorDlg::OnBnClickedButtonCancel)
//	ON_BN_CLICKED(IDC_BUTTON_STATUS, &FloorDlg::OnBnClickedStatus)
	ON_BN_CLICKED(IDC_BUTTON_EDITCHK, &FloorDlg::OnBnClickedEditCheck)
	ON_BN_CLICKED(IDC_BUTTON_TAKEOUT, &FloorDlg::OnBnClickedTakeOut)
	ON_BN_CLICKED(IDC_BUTTON_REFUND, &FloorDlg::OnBnClickedRefund)
	ON_BN_CLICKED(IDC_BUTTON_PARTY, &FloorDlg::OnBnClickedParty)
	ON_BN_CLICKED(IDC_BUTTON_FUNCTION, &FloorDlg::OnBnClickedFunction)
	ON_BN_CLICKED(IDC_BUTTON_NOTIFYKIT, &FloorDlg::OnBnClickedNotifyKitchen)
	ON_BN_CLICKED(IDC_BUTTON_RESERVE,&FloorDlg::OnBnClickedReserve)
	ON_BN_CLICKED(IDC_BUTTON_TAINFO,&FloorDlg::OnMsgIncall)

	ON_BN_CLICKED(IDC_BUTTON_LEFT, &FloorViewDlg::OnBnClickedButtonLeft)
	ON_BN_CLICKED(IDC_BUTTON_RIGHT, &FloorViewDlg::OnBnClickedButtonRight)
	ON_BN_CLICKED(IDC_BUTTON_EATIN, &FloorViewDlg::OnBnClickedEatIn)
	ON_BN_CLICKED(IDC_BUTTON_PRE, &FloorViewDlg::OnBnClickedButtonBack)
	ON_BN_CLICKED(IDC_BUTTON_EATIN, &FloorViewDlg::OnBnClickedOpenTbl)
	ON_BN_CLICKED(IDC_BUTTON_PAY, &FloorViewDlg::OnBnClickedButtonPay)
	ON_BN_CLICKED(IDC_BUTTON_PICKCHK, &FloorViewDlg::OnBnClickedOrder)
	ON_BN_CLICKED(IDC_BUTTON_REMINDDISH, &FloorViewDlg::OnBnClickedRemindDish)
	ON_BN_CLICKED(IDC_BUTTON_TRANSFER, &FloorViewDlg::OnBnClickedTransfer)
	ON_BN_CLICKED(IDC_BUTTON_PRINT, &FloorViewDlg::OnBnClickedPrePrint)
	ON_BN_CLICKED(IDC_BUTTON_MAKED, &FloorViewDlg::OnBnClickedDishMaked)
	ON_BN_CLICKED(IDC_BUTTON_CLEANTBL, &FloorViewDlg::OnBnClickedCleanTable)
	ON_BN_CLICKED(IDC_BUTTON_ASSEMBLE_TABLE, &FloorViewDlg::OnBnClickedAssembleTable)
	ON_BN_CLICKED(IDC_BUTTON_VIEW_WEBCHK,&FloorViewDlg::OnBnClickedViewWebcheck)
	ON_WM_SIZE()
	ON_WM_CTLCOLOR()
	ON_WM_TIMER()
	ON_COMMAND_RANGE(IDC_SLU_BUTTON,IDC_SLU_BUTTON+10, &FloorViewDlg::OnBnClickedTblStatus)
	ON_COMMAND_RANGE(IDC_TABLE0,IDC_TABLE0+999,OnItemBnClicked)
	ON_COMMAND_RANGE(IDC_CLASS_BUTTON,IDC_CLASS_BUTTON+99, &FloorViewDlg::OnBnClickedRadio)
	ON_MESSAGE(WM_MESSAGE_UPDATE,OnMsgUpdate)
END_MESSAGE_MAP()

BOOL FloorViewDlg::OnInitDialog()
{
	try{
		if (m_strBackground.GetLength()==0)
		{
			m_strBackground=_T("Picture\\floorview.png");
		}
		CPosPage::InitDialog(m_strBackground);
		CString path;
		CRect   rect;
		SIZE buttonSize;
		for(int i=0;i<6;i++)
		{
			path.Format(_T("Picture\\table%d.png"),i+1);
			m_bpTableStatus[i]=Gdiplus::Image::FromFile(path);
			if(i==0)
			{
				buttonSize.cx=m_bpTableStatus[i]->GetWidth()*CreatButton::m_nFullWidth/1024;
				buttonSize.cy=m_bpTableStatus[i]->GetHeight()*CreatButton::m_nFullHeight/768;
			}
		}
		m_strTmplate=_T("Page\\IDD_2_FLOOR_VIEW.ini");
		m_checkDlg.Create(IDD_CHECK,this);
		m_checkDlg.ShowWindow(SW_SHOW);
		m_btnCtrl.GenaratePage2(m_strTmplate,this);
		//创建桌子按钮
		mTableRect.left=385*CreatButton::m_nFullWidth/1024;
		mTableRect.top=120*CreatButton::m_nFullHeight/768;
		int space=ScaleX(10);
		mTableRect.right=mTableRect.left+ITEM_COLUMNSIZE*(buttonSize.cx+space);
		mTableRect.bottom=mTableRect.top+ITEM_LINESIZE*(buttonSize.cy+space);
		LOGFONT m_tLogFont;
		memset(&m_tLogFont,0,sizeof(LOGFONT));
		m_tLogFont.lfHeight	= ScaleX(20);
		wcscpy_s(m_tLogFont.lfFaceName, _T("Microsoft YaHei"));
		mTableFont.CreateFontIndirect(&m_tLogFont);
		
		
		for(int i=0;i<ITEM_LINESIZE;i++)
		{
			POINT topleft;
			CImage bmp;
			topleft.y=mTableRect.top+i*(buttonSize.cy+space);
			for(int j=0;j<ITEM_COLUMNSIZE;j++)
			{
				int count=i*ITEM_COLUMNSIZE+j;
				topleft.x=mTableRect.left+j*(buttonSize.cx+space);
				
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
		//读取营业地点
		CRecordset rs( &theDB);
		CString strSQL;
		int rvcCount=0;
		strSQL.Format(_T("SELECT COUNT(*) FROM rvc_center"));
		if(rs.Open(CRecordset::forwardOnly,strSQL))
		{
			CString strVal;
			rs.GetFieldValue((short)0,strVal);
			rvcCount=_wtoi(strVal);
		}
		rs.Close();
		strSQL.Format(_T("SELECT * FROM rvc_center ORDER BY rvc_center_id"));
		if(rs.Open(CRecordset::forwardOnly,strSQL))
		{
			CDBVariant variant;
			CString strName;
			CRect _rect=CRect(mTableRect.left,CreatButton::m_nFullHeight-100,90+mTableRect.left,CreatButton::m_nFullHeight-70);
			if(rvcCount>5)//2行
			{
				_rect.top-=22;
				_rect.bottom-=22;
			}
			CRoundButton2* pBtn=new CRoundButton2;
			theLang.LoadString(strName,IDS_ALL);
			pBtn->Create(strName, WS_CHILD|WS_VISIBLE|BS_AUTORADIOBUTTON| WS_GROUP, _rect,this,IDC_CLASS_BUTTON);
			Gdiplus::Image* img1=Gdiplus::Image::FromFile(_T("Picture/bt_rvc.png"));
			Gdiplus::Image* img2=Gdiplus::Image::FromFile(_T("Picture/bt_rvc_.png"));
			pBtn->SetImages(img1,img2);
			pBtn->SetTextColor(RGB(255,255,255));
			pBtn->SetCheck(TRUE);
			m_SelectedRvc=pBtn;
			int count=0;
			while(!rs.IsEOF())
			{
				count++;
				_rect.left+=ScaleX(100);
				_rect.right+=ScaleX(100);
				if(count==6)
				{
					_rect.top+=31;
					_rect.bottom+=31;
					_rect.left=mTableRect.left;
					_rect.right=90+mTableRect.left;
				}
				rs.GetFieldValue(_T("rvc_center_id"),variant);
				rs.GetFieldValue(_T("rvc_center_name"),strName);
				CRoundButton2* pBtn=new CRoundButton2;
				pBtn->Create(strName, WS_CHILD|WS_VISIBLE|BS_AUTORADIOBUTTON, _rect,this, IDC_CLASS_BUTTON+variant.m_iVal);
				pBtn->SetImages(img1,img2);
				pBtn->SetTextColor(RGB(255,255,255));
				rs.MoveNext();
			}
		}
		rs.Close();
		//状态分类
		//mFont.CreatePointFont(120,_T("Microsoft YaHei"));    //720为字体的大小
		strSQL.Format(_T("SELECT * FROM table_status"));
		if(rs.Open(CRecordset::forwardOnly,strSQL))
		{
			CDBVariant variant;
			CString strName;
			CRect _rect=CRect(mTableRect.left,CreatButton::m_nFullHeight-60,160+mTableRect.left,CreatButton::m_nFullHeight-30);
			while(!rs.IsEOF())
			{
				rs.GetFieldValue(_T("table_stauts_id"),variant);
				if (variant.m_iVal>4)
				{
					rs.MoveNext();
					continue;
				}
				rs.GetFieldValue(_T("table_status_name"),strName);
				strStatus[variant.m_iVal-1]=strName;
				CButtonST* pBtn=new CButtonST;
				pBtn->Create(strName, WS_CHILD|WS_VISIBLE, _rect,this, IDC_SLU_BUTTON+variant.m_iVal);
				CString path;
				path.Format(_T("Icon\\%d.ico"),variant.m_iVal);
				HICON hIcon=(HICON)::LoadImage(NULL,(LPCTSTR)path , IMAGE_ICON,44,18,LR_LOADFROMFILE);
				pBtn->SetIcon(hIcon);
				pBtn->SetFont(GetFont());
				rs.MoveNext();
				_rect.left+=ScaleX(160);
				_rect.right+=ScaleX(160);
			}
		}
		rs.Close();
	}catch(...)
	{
	}
	TIMER=macrosInt[_T("TABLE_UPDATE_TIMER")]*1000;
	if (TIMER<3)
		TIMER=10*1000;
	SetTimer(1001,TIMER,NULL);//每隔10秒刷新桌位状态
	return TRUE;
}
void FloorViewDlg::OnSize(UINT nType, int cx, int cy)
{
	CPosPage::OnSize(nType, cx, cy);
	cx=CreatButton::m_nFullWidth;
	cy=CreatButton::m_nFullHeight;
	if (m_logCtrl.m_hWnd)
	{
		int line_y1=65;
		int height=28;
		m_logCtrl.MoveWindow(60,35,250*cx/1024,height);
		m_tableCtrl.MoveWindow(25,line_y1,95,height);
		m_time.MoveWindow(140*cx/1024,line_y1,220*cx/1024,height);
		
		m_checkDlg.MoveWindow(23*cx/1024,100*cy/768,328*cx/1024,(int)(cy*0.65));
		m_checkCtrl.ShowWindow(SW_HIDE);
		m_tableCtrl.ShowWindow(SW_SHOW);
	}
}
/************************************************************************
* 函数介绍：按时刷新时间显示
* 输入参数：
* 输出参数：
* 返回值  ：
************************************************************************/
void FloorViewDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent==1001)
	{
		CPOSClientApp* pApp=(CPOSClientApp*)AfxGetApp();
		if(pApp->m_pMain->GetActiveIndex()==DLG_FLOOR)
		{//只有在开单界面才自动刷新
			FloorDlg::OnSetActive();
		}
	}
	CPosPage::OnTimer(nIDEvent);
}
LRESULT FloorViewDlg::OnMsgUpdate(WPARAM wParam, LPARAM lParam)
{
	{//CMainSheet已保证在开单界面
		FloorDlg::OnSetActive();
	}
	return 0;
}
void FloorViewDlg::OnSetActive()
{
	m_inputTbl.Empty();
	CPosPage::OnSetActive();
	theLang.UpdatePage(this,_T("IDD_2_FLOOR_VIEW"));
	m_logCtrl.SetWindowText(((CPOSClientApp*)AfxGetApp())->m_strUserName);
	UpdateTables();
	UpdateRvc(m_nCurrentRvc,FALSE);
	UpdateCheck();
	KillTimer(1001);
	SetTimer(1001,TIMER,NULL);
}

void FloorViewDlg::OnBnClickedButtonBack()
{
	theApp.m_pMain->SetActivePage(DLG_LOGIN);
}
void FloorViewDlg::OnBnClickedRadio(UINT uID)
{
	if(m_SelectedTable)
	{
		m_SelectedTable->SetCheck(FALSE);
		m_SelectedTable=NULL;
	}
	CRoundButton2* pButton2=(CRoundButton2*)GetDlgItem(uID);
	if (pButton2&&pButton2!=m_SelectedRvc)
	{
		if(m_SelectedRvc)
			m_SelectedRvc->SetCheck(FALSE);
		pButton2->SetCheck(TRUE);
	}
	m_SelectedRvc=pButton2;
	int rvc_id=uID-IDC_CLASS_BUTTON;
	if (rvc_id<=0)
	{
		m_nCurrentRvc=0;
		OnSetActive();
	}
	else
		UpdateRvc(rvc_id,TRUE);
}
void FloorViewDlg::OnBnClickedTblStatus(UINT uID)
{
	int status_id=uID-IDC_SLU_BUTTON-1;
	if (status_id<0||status_id>7)
		status_id=0;
	if(m_SelectedTable)
	{
		m_SelectedTable->SetCheck(FALSE);
		m_SelectedTable=NULL;
	}
	FloorDlg::UpdateTables();
	m_RVCTables.clear();
	{
		vector<TableItem>::iterator iter;
		for (iter=m_Tables.begin();iter!=m_Tables.end();iter++)
		{
			if (status_id==iter->status)
			{
				m_RVCTables.push_back(*iter);
			}
		}
	}
	m_nCurrentPage=0;
	m_nPageCount=(int)ceil((float)m_RVCTables.size()/m_nPageSize);
	ShowCurrentPage();
}
void FloorViewDlg::OnItemBnClicked(UINT uID)
{
	CTableButton* pButton2=(CTableButton*)GetDlgItem(uID);
	if (pButton2&&pButton2!=m_SelectedTable)
	{
		if(m_SelectedTable)
			m_SelectedTable->SetCheck(FALSE);
		pButton2->SetCheck(TRUE);
	}
	UINT index=m_nCurrentPage*m_nPageSize+(uID-IDC_TABLE0);
	if (index>=m_RVCTables.size())
	{//越界
		LOG4CPLUS_ERROR(log_pos,"index=["<<index<<"] out of range. m_RVCTables.size()="<<m_RVCTables.size());
		return;
	}
	m_tableId=m_RVCTables[index].id;
	m_rawid=m_RVCTables[index].raw_id;
	if (pButton2==m_SelectedTable)
	{//双击
		if(GetLock(m_tableId)==TRUE)
		{
			if(BeginTable(m_tableId,2,m_RVCTables[index].raw_id)==FALSE)//开桌失败
				ReleaseLock(m_tableId);
		}
		return;
	}
	else
	{
		m_SelectedTable=pButton2;
	}
	theApp.m_strTblName=m_RVCTables[index].name;
	//去掉带有金额的桌名
	int idx=theApp.m_strTblName.Find('\n');
	if (idx>0)
	{
		theApp.m_strTblName=theApp.m_strTblName.Left(idx);
	}
	CString str2,tmpMsg;
	theLang.LoadString(str2,IDS_TBLNAME);
	tmpMsg.Format(_T("%s:%s"),str2,theApp.m_strTblName);
	m_tableCtrl.SetWindowText(tmpMsg);
	UpdateCheck(TRUE);
}
void FloorViewDlg::UpdateCheck(BOOL bOpen)
{
	CRect rect(0,0,350*CreatButton::m_nFullWidth/1024,200*CreatButton::m_nFullHeight/768);
	CString str2,tmpMsg;
	while(!m_orderList.IsEmpty())
	{
		OrderDetail* item=m_orderList.GetTail();
		m_orderList.RemoveTail();
		delete item;
	}
	m_checkDlg.m_fPayed=0;
	CString strSQL;
	strSQL.Format(_T("SELECT * FROM order_head WHERE table_id=%d"),m_tableId);
	CRecordset rs( &theDB);
	if(rs.Open(CRecordset::forwardOnly,strSQL))
	{
		if(rs.IsEOF())
		{//空桌
			m_headId=-1;
			m_checkDlg.ResetContent(TRUE);
			m_checkDlg.UpdateSubtotal();
			m_time.SetWindowText(_T(""));
			m_checkCtrl.SetWindowText(_T(""));
			InvalidateRect(rect);
			return;
		}
		CDBVariant variant;
		CString strVal;
		rs.GetFieldValue(_T("order_head_id"),variant);
		m_headId=variant.m_lVal;
		rs.GetFieldValue(_T("check_name"),strVal);
		if (strVal.GetLength()==0)
		{
			rs.GetFieldValue(_T("check_number"),variant);
			theLang.LoadString(str2,IDS_CHKNUM);
			tmpMsg.Format(_T("%s%05d"),str2,variant.m_lVal);
		}
		else
		{
			theLang.LoadString(str2,IDS_CHKNAME);
			tmpMsg.Format(_T("%s:%s"),str2,strVal);
		}
		m_checkCtrl.SetWindowText(tmpMsg);
		rs.GetFieldValue(_T("order_start_time"),variant);
		theLang.LoadString(str2,IDS_OPENTIME);
		tmpMsg.Format(_T("%s: %02d:%02d:%02d"),str2,variant.m_pdate->hour,variant.m_pdate->minute,variant.m_pdate->second);
		m_time.SetWindowText(tmpMsg);
		
		rs.GetFieldValue(_T("actual_amount"),strVal);
		m_checkDlg.m_fPayed=_wtof(strVal);
	}
	rs.Close();
	InvalidateRect(rect);
	strSQL.Format(_T("SELECT * FROM order_detail LEFT JOIN menu_item ON menu_item_id=item_id WHERE check_id=1 AND is_return_item=0 AND order_head_id=%d;")
		,m_headId);
	FloorDlg::GetOrderDetail(strSQL,&m_orderList);
	UpdateCheckData();
}
/************************************************************************
* 函数介绍：更新账单信息
* 输入参数：
* 输出参数：
* 返回值  ：
************************************************************************/
void FloorViewDlg::UpdateCheckData()
{
	try{
		m_checkDlg.ResetContent(FALSE);
		m_checkDlg.LockWindowUpdate();
		m_checkDlg.m_nStatus=1;
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
		m_checkDlg.ComputeSubtotal();
		m_checkDlg.UnlockWindowUpdate();
	}
	catch(...)
	{
		LOG4CPLUS_ERROR(log_pos,"Catch Exception GetLastError="<<GetLastError());
	}
}
/************************************************************************
* 函数介绍： 桌台显示翻页
* 输入参数：
* 输出参数：
* 返回值  ：
************************************************************************/
void FloorViewDlg::OnBnClickedButtonLeft()
{
	if(m_nCurrentPage>0)
		m_nCurrentPage--;
	else
		return;
	ShowCurrentPage();
}

void FloorViewDlg::OnBnClickedButtonRight()
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
void FloorViewDlg::ShowCurrentPage()
{
	try{
		unsigned int index;
		CString str2;
		theLang.LoadString(str2,IDS_TABLEGST);
		for(int i=0;i<m_nPageSize;i++)
		{
			index=i+m_nCurrentPage*m_nPageSize;
			CTableButton* pButton2=(CTableButton*)GetDlgItem(IDC_TABLE0+i);
			if(index<m_RVCTables.size())
			{
				TableItem& table=m_RVCTables[index];
				pButton2->SetImages(m_bpTableStatus[table.status],m_bpTableStatus[table.status],false);
				pButton2->SetStrTop(table.party_table);
				if(table.cur_gst>=0&&table.status>0)
					pButton2->m_strBottom.Format(_T("%s   %d/%d"),table.open_time,table.cur_gst,table.seat_num);
				else
					pButton2->m_strBottom.Format(str2,table.seat_num);
				pButton2->SetWindowText(table.name);
				if (table.ismake)
				{
					pButton2->SetIcon(IDI_ICON_MAKE);
				}
				else if(table.isWechat)
				{
					pButton2->SetIcon(IDI_ICON_WECHAT);
				}
				else
					pButton2->SetIcon((HICON)NULL);
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
		//InvalidateRect(mTableRect,FALSE);
	}
	catch(...)
	{
		LOG4CPLUS_ERROR(log_pos,"Catch Exception GetLastError="<<GetLastError());
	}
}
void FloorViewDlg::OnBnClickedOpenTbl()
{
	if (m_tableId<=0)
		return;
	if(GetLock(m_tableId)==TRUE)
	{
		if(BeginTable(m_tableId,2)==FALSE)//开桌失败
			ReleaseLock(m_tableId);
	}
}
void FloorViewDlg::OnBnClickedButtonPay()
{
	if (m_headId<0)
		return;
	//验证是否有收银权限
	CString userid;
	int auth=OrderDlg::RequeastAuth(userid,_T("payment"));
	if(auth!=0)
	{
		LOG4CPLUS_WARN(log_pos,"not have payment privilege!");
		return;
	}
	if(GetLock(m_tableId)==FALSE)
		return;
	CRecordset rs(&theDB);
	CString strSQL;
	CDBVariant variant;
	CPOSClientApp* pApp=(CPOSClientApp*)AfxGetApp();
	pApp->m_nTableId=m_tableId;
	pApp->m_bRefund=FALSE;
	pApp->m_bDirty=TRUE;
	//检查tables是否有这张桌
	strSQL.Format(_T("SELECT * FROM tables LEFT JOIN consumption_limit ON tables.consumption_limit=")
		_T("consumption_limit.consumption_limit_id WHERE table_id=\'%d\';"),m_tableId);
	if(!rs.Open(-1,strSQL))
	{
		return ;
	}
	if(rs.IsEOF())
	{
		POSMessageBox(IDS_NOTFINDTBL);
		return ;
	}
	else
	{
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
	//查询RVC name
	strSQL.Format(_T("select rvc_center_name from rvc_center where rvc_center_id = %d"),pApp->m_nRVC);
	if(rs.Open(-1,strSQL))
	{
		if(!rs.IsEOF())
		{
			rs.GetFieldValue(_T("rvc_center_name"),pApp->m_strRVC);
		}
	}
	rs.Close();
	//查询head信息
	strSQL.Format(_T("SELECT * FROM order_head WHERE table_id=\'%d\';"),m_tableId);
	if(!rs.Open(-1,strSQL))
	{
		LOG4CPLUS_ERROR(log_pos,"CRecordset Open Failed");
		return;
	}
	pApp->m_nActiveCheck=0;
	rs.GetFieldValue(_T("order_head_id"),variant);
	pApp->m_nOrderHeadid=variant.m_lVal;
	rs.GetFieldValue(_T("check_number"),variant);
	pApp->m_nCheckNum=variant.m_lVal;
	rs.GetFieldValue(_T("check_name"),pApp->m_strChkName);
	rs.GetFieldValue(_T("customer_num"),variant);
	pApp->m_nGuests=variant.m_lVal;
	rs.GetFieldValue(_T("order_start_time"),variant);
	pApp->m_strBeginDate.Format(_T("%04d-%02d-%02d"),variant.m_pdate->year,variant.m_pdate->month,variant.m_pdate->day);
	pApp->m_strBeginTime.Format(_T("%02d:%02d:%02d"),variant.m_pdate->hour,variant.m_pdate->minute,variant.m_pdate->second);
	pApp->m_strEndTime.Empty();
	rs.GetFieldValue(_T("edit_time"),variant);
	if (variant.m_dwType!=DBVT_NULL)
	{//存在edit_time字段，说明是反结帐的单
		rs.GetFieldValue(_T("order_end_time"),pApp->m_strEndTime);
	}
	rs.GetFieldValue(_T("party_id"),variant);
	if (variant.m_dwType==DBVT_NULL)
		pApp->m_nPartyId=-1;
	else
		pApp->m_nPartyId=variant.m_lVal;
	rs.Close();
	//关联桌是否合并付款
	while(theApp.m_nPartyId>0)
	{
		CString strSQL;
		strSQL.Format(_T("SELECT * FROM order_head WHERE party_id=%d AND order_head_id<>%d"),theApp.m_nPartyId,theApp.m_nOrderHeadid);
		CRecordset rs(&theDB);
		if(!rs.Open(-1,strSQL))
			break;
		if (rs.GetRecordCount()==0)
			break;
		if(POSMessageBox(IDS_COMBINEPAY,MB_YESNO)!=IDOK)
			break;
		while(!rs.IsEOF())
		{
			CDBVariant variant;
			rs.GetFieldValue(_T("table_id"),variant);
			strSQL.Format(_T("CALL join_table_1(%d,%d,@r);"),variant.m_iVal,pApp->m_nTableId);
			theDB.ExecuteSQL(strSQL);
			rs.MoveNext();
		}
		rs.Close();
		//刷新数据
		pApp->m_bDirty=TRUE;
		break;
	}
	theApp.m_bDirty=1;
	theApp.m_pMain->SetActivePage(DLG_PAY);
}
void FloorViewDlg::OnBnClickedOrder()
{
	if (m_headId<0)
		return;
	if(GetLock(m_tableId)==TRUE)
	{
		if(BeginTable(m_tableId,1)==FALSE)//开桌失败
			ReleaseLock(m_tableId);
	}
}

void FloorViewDlg::OnBnClickedRemindDish()
{
	if (m_headId<0)
		return;
	try
	{
		BOOL bFind=FALSE;
		CListBoxEx* ptrDetailList=&m_checkDlg.m_ctrlDetailList;
		CString str2,str_wait;
		CString strSQL;
		strSQL.Format(_T("UPDATE order_detail SET rush=rush+1 WHERE order_head_id=%d AND is_send=1"),theApp.m_nOrderHeadid);
		theDB.ExecuteSQL(strSQL);
		theLang.LoadString(str_wait,IDS_WAITMK);
		for(int  i=0;i<ptrDetailList->GetCount();i++)
		{
			OrderDetail* item=(OrderDetail*)ptrDetailList->GetItemDataPtr(i);
			if (item->item_id<=0||item->n_saved!=2)
				continue;//未送厨的不能催菜
			item->rush_times++;
			if(wcsstr(item->description,str_wait))
			{
				bFind=TRUE;
				CString str=item->description;
				int index = str.Find(str_wait);
				str.Delete(index,str_wait.GetLength());
				theLang.LoadString(str2,IDS_MAKENOW);
				str.Append(str2);
				wcsncpy_s(item->description,str,99);
				if(item->n_saved!=0)
				{
					strSQL.Format(_T("UPDATE order_detail SET description=\'%s\' WHERE order_detail_id=%d;")
						,item->description,item->order_id);
					theDB.ExecuteSQL(strSQL);
				}
			}
			m_checkDlg.UpdateItemString(i,FALSE);
		}

		CRecordset rs( &theDB );
		CString strSql;
		strSql.Format(_T("SELECT * from print_devices where print_device_id in( SELECT DISTINCT(print_device_id) ")
			_T("FROM print_class_relation where print_class_id in (SELECT DISTINCT(menu_item.print_class) ")
			_T("FROM order_detail,menu_item where order_detail.menu_item_id=menu_item.item_id ")
			_T("and order_head_id = %d and is_return_item=0)) AND is_print_note=1 group by check_info_print,com_port,printer_name;")
			,m_headId);

		rs.Open( CRecordset::snapshot,strSql);
		while (!rs.IsEOF())
		{
			JSONVALUE printTask;
			printTask[_T("template")]=TEMPLATE_MESSAGE;
			CTime time=CTime::GetCurrentTime();
			printTask[_T("time")]=time.Format("%Y-%m-%d %H:%M");
			printTask[_T("tbl_name")]=theApp.m_strTblName;
			printTask[_T("emp_name")]=theApp.m_strUserName;
			printTask[_T("serial")]=m_headId;
			GetPrinterInfo(rs,printTask);
			ReFormatTableInfo(printTask,1);
			CString str1,str2;
			theLang.LoadString(str2,IDS_REMINDHEAD);
			printTask[_T("head")]=str2;
			theLang.LoadString(str2,IDS_REQUESTMAKE);
			str1.Format(str2,theApp.m_strTblName);
			printTask[_T("message")]=str1;
			WritePrintTask(printTask,TRUE);
			rs.MoveNext();
		}
		rs.Close();
	}
	catch (CDBException* ex)
	{
		LOG4CPLUS_ERROR(log_pos,(LPCTSTR)ex->m_strError);
	}
}
void FloorViewDlg::OnBnClickedTransfer()
{
	if (m_headId<0)
		return;
	theApp.m_nTableId=m_tableId;
	FunctionDlg::TransTable();
	m_tableId=theApp.m_nTableId;
	CString str2,tmpMsg;
	theLang.LoadString(str2,IDS_TBLNAME);
	tmpMsg.Format(_T("%s:%s"),str2,theApp.m_strTblName);
	m_tableCtrl.SetWindowText(tmpMsg);
	//刷新显示
	OnSetActive();
	if(m_SelectedTable)
 	{
 		m_SelectedTable->SetCheck(FALSE);
 		m_SelectedTable=NULL;
 	}
}
void FloorViewDlg::OnBnClickedDishMaked()
{
	try{
		if (m_headId<0)
			return;
		for (vector <TableItem>::iterator iter = m_RVCTables.begin() ; iter != m_RVCTables.end() ; iter++ )
		{
			TableItem& item=(*iter);
			if(item.id==m_tableId)
			{
				CString str2,msg,strSQL;
				if (item.ismake==0)
					theLang.LoadString(IDS_DISHMAKED,str2);
				else
					theLang.LoadString(IDS_DISHMAKED2,str2);
				msg.Format(str2,theApp.m_strTblName);
				if (POSMessageBox(msg,MB_YESNO)==IDOK)
				{
					if (item.ismake==0)
					{
						item.ismake=1;
						strSQL.Format(_T("UPDATE order_head SET is_make=1 WHERE order_head_id=%d"),m_headId);
					}
					else
					{
						item.ismake=0;
						strSQL.Format(_T("UPDATE order_head SET is_make=NULL WHERE order_head_id=%d"),m_headId);
					}
					theDB.ExecuteSQL(strSQL);
				}
				ShowCurrentPage();
				return;
			}
		}

	}catch(...)
	{
	}

}
void FloorViewDlg::OnBnClickedPrePrint()
{
	if (m_headId<0)
		return;
	if (theApp.m_prePrinter.nDeviceType<0)
	{
		POSMessageBox(IDS_NOPREPRINT);
		return;
	}
	CString userid;
	int auth=OrderDlg::RequeastAuth(userid,_T("print_prestatement"));
	if (auth!=0)
		return;
	CRecordset rs( &theDB);
	CString strSQL,cvalue;
	int nPrint=0;
	//更新并获取打印次数
	strSQL.Format(_T("SELECT print_count FROM order_head WHERE order_head_id=%d AND check_id=%d;")
		,m_headId,1);
	rs.Open( CRecordset::forwardOnly,strSQL);
	if (!rs.IsEOF())
	{
		rs.GetFieldValue((short)0,cvalue);
		nPrint=_wtoi(cvalue);
		strSQL.Format(_T("UPDATE order_head SET print_count=print_count+1 WHERE order_head_id=%d AND check_id=%d;")
			,m_headId,1);
		theDB.ExecuteSQL(strSQL);
	}
	rs.Close();
	nPrint++;
	JSONVALUE root;
	root[_T("template")]=TEMPLATE_PREPAY;
// 	if(PayDlg::GetWeixinQRCode(m_checkDlg.m_fDebt*100+0.5))
// 	{
// 		root[_T("qrcode")]=QRPAY_PATH;
// 	}
	root["print_count"]=nPrint;
	theApp.m_nOrderHeadid=m_headId;
	PayDlg::FormatPrint(root,theApp.m_prePrinter,m_checkDlg,0);
	ReFormatTableInfo(root);
	CPOSClientApp::PrintJson(root);
	//更新桌态为已印单
	strSQL.Format(_T("UPDATE tables SET table_status=4 WHERE table_id=\'%d\';"),m_tableId);
	theDB.ExecuteSQL(strSQL);
}
void FloorViewDlg::ReFormatTableInfo(JSONVALUE& root,int type)
{
	CString strSQL;
	strSQL.Format(_T("SELECT * FROM order_head WHERE order_head_id=%d AND check_id=%d"),m_headId,1);
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
		rs.GetFieldValue(_T("customer_num"),variant);
		root[_T("gst_num")]=variant.m_lVal;
		if(type!=0)
			return;
		rs.GetFieldValue(_T("table_name"),strVal);
		root[_T("tbl_name")]=strVal;
		rs.GetFieldValue(_T("check_name"),strVal);
		root[_T("chk_name")]=strVal;
		root[_T("tbl_id")]=m_tableId;
		rs.GetFieldValue(_T("order_start_time"),strVal);
		root[_T("open_time")]=strVal;
		root[_T("serial")]=m_headId;
		rs.GetFieldValue(_T("check_number"),variant);
		root[_T("chk_num")]=variant.m_lVal;
	}
	rs.Close();
}
/************************************************************************
* 函数介绍：堂食
* 输入参数：
* 输出参数：
* 返回值  ：
************************************************************************/
void FloorViewDlg::OnBnClickedEatIn()
{
	int table_id=-999;
	if(!m_inputTbl.IsEmpty())
	{
		if(m_inputTbl.GetLength()<=6)
		{//手动输入桌号
			table_id=_wtol(m_inputTbl);
		}
		else
		{//扫描枪扫描流水号
			CString strSQL;
			strSQL.Format(_T("SELECT table_id FROM order_head WHERE order_head_id=%s"),m_inputTbl);
			CRecordset rs( &theDB);
			if(rs.Open(-1,strSQL))
			{
				if (!rs.IsEOF())
				{
					CDBVariant var;
					rs.GetFieldValue((short)0,var);
					table_id=var.m_lVal;
				}
			}
			rs.Close();
		}
	}
	else
	{
		NumberInputDlg dlg;
		theLang.LoadString(IDS_INPUTTBL,dlg.m_strHint);
		if(dlg.DoModal()==IDOK)
		{
			table_id=_wtoi(dlg.m_strNum);
			if (table_id<=0||table_id>MAX_TABLE_NUM)
			{
				POSMessageBox(IDS_TBLNOERROR);
				return;
			}
		}
		else
			return;
	}
	m_nStatus=0;
	if(GetLock(table_id)==TRUE)
	{
		if(BeginTable(table_id,2,0,TYPE_DINE)==FALSE)//开桌失败
			ReleaseLock(table_id);
	}
	m_inputTbl.Empty();
}
void FloorViewDlg::OnBnClickedCleanTable()
{
	try{
		if (m_tableId<=0)
			return;
		for (vector <TableItem>::iterator iter = m_RVCTables.begin() ; iter != m_RVCTables.end() ; iter++ )
		{
			if((*iter).id==m_tableId)
			{
				CString strSQL;
				if(m_headId<0)
				{
					strSQL.Format(_T("UPDATE tables SET table_status=0 WHERE table_id=%d"),m_tableId);
					theDB.ExecuteSQL(strSQL);
					(*iter).status=0;
				}
				else
				{
					if(IsFreeLock(m_tableId)==FALSE)
						return;
					strSQL.Format(_T("CALL flush_order(%d,%d);"),m_headId,m_tableId);
					theDB.ExecuteSQL(strSQL);
					//如果清台成功才重置桌态
					strSQL.Format(_T("SELECT * FROM order_head WHERE table_id=%d"),m_tableId);
					CRecordset rs( &theDB);
					if(rs.Open(-1,strSQL))
					{
						if (rs.GetRecordCount()==0)
						{
							(*iter).status=0;
						}
						rs.Close();
					}
				}
				ShowCurrentPage();
				return;
			}
		}

	}catch(...)
	{
	}
}
/************************************************************************
* 函数介绍：搭台
* 输入参数：
* 输出参数：
* 返回值  ：
************************************************************************/
void FloorViewDlg::OnBnClickedAssembleTable()
{
	if(m_headId<0){
		OnBnClickedOpenTbl();
		return;
	}
	int pId=m_tableId;
	if(m_rawid>0)
		pId=m_rawid;
	if(BeginTable(-2,2,pId)){//搭台成功再加锁
		GetLock(theApp.m_nTableId);
	}
}
/************************************************************************
* 函数介绍：查看网络订单
* 输入参数：
* 输出参数：
* 返回值  ：
************************************************************************/
void FloorViewDlg::OnBnClickedViewWebcheck()
{
	ViewWebCheckDlg* pDlg=new ViewWebCheckDlg();
	pDlg->m_hParent=this;
	pDlg->Create(IDD_VIEWWEBCHK,theApp.m_pMain);
	pDlg->ShowWindow(SW_SHOW);
	pDlg->SetFocus();

}

BOOL FloorViewDlg::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message==WM_KEYDOWN)
	{
		if(theApp.m_pMain->GetActiveIndex()!=DLG_FLOOR)
			return TRUE;
		if(pMsg->wParam==VK_PROCESSKEY)
		{
			pMsg->wParam=ImmGetVirtualKey(this->m_hWnd);
		}
		switch (pMsg->wParam)
		{
		case VK_RETURN:
			::PostMessage(m_hWnd,WM_COMMAND, MAKEWPARAM(IDC_BUTTON_EATIN,0),0);
			return TRUE;
		case VK_UP:
		case VK_DOWN:
		case VK_LEFT:
		case VK_RIGHT:
				return TRUE;
		case VK_F1:
			{
				CString userid;
				int auth=OrderDlg::RequeastAuth(userid,_T("open_drawer"));
				if(auth!=0)
					return TRUE;
				theApp.OpenDrawer();
			}
			return TRUE;
		}
		if (pMsg->wParam>='0'&&pMsg->wParam<='9')
		{
			if(m_inputTbl.GetLength()<10)
				m_inputTbl.AppendChar(pMsg->wParam);
		}
		else if (pMsg->wParam>=VK_NUMPAD0&&pMsg->wParam<=VK_NUMPAD9)
		{
			if(m_inputTbl.GetLength()<10)
				m_inputTbl.AppendFormat(_T("%d"),pMsg->wParam-VK_NUMPAD0);
		}
	}
	return CPosPage::PreTranslateMessage(pMsg);
}
HBRUSH FloorViewDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	if(nCtlColor==CTLCOLOR_STATIC)
	{
		pDC->SetBkMode(TRANSPARENT);
		return (HBRUSH)::GetStockObject(NULL_BRUSH); //返回此画刷可以使静态文本透明
	}
	return   hbr; 
}