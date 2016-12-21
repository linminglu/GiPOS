// SplitCheckDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "POSClient.h"
#include "SplitCheckDlg.h"
#include "OrderDlg.h"
#include "NumberInputDlg.h"
#include <math.h> 

// SplitCheckDlg 对话框

IMPLEMENT_DYNAMIC(SplitCheckDlg, CPosPage)

SplitCheckDlg::SplitCheckDlg()
: CPosPage(SplitCheckDlg::IDD)
{
	m_pOrderList=NULL;
	m_nActive=0;
}

SplitCheckDlg::~SplitCheckDlg()
{
	::DeleteObject(bpStatic);
}

void SplitCheckDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

void SplitCheckDlg::OnSetActive()
{
	CPosPage::OnSetActive();
	try{
		theLang.UpdatePage(this,_T("IDD_5_SPLIT"));
		if (m_pOrderList==NULL)
		{
			return;
		}
		m_splitedList.RemoveAll();
		m_newList.RemoveAll();
		CPOSClientApp* pApp=(CPOSClientApp*)AfxGetApp();
		m_nCheckCount=1;
		for (int i=0;i<MAX_CHECKS;i++)
		{
			m_list[i].ResetContent();
			if (pApp->m_nCheckStatus[i]==1)
			{//closed
				m_list[i].EnableWindow(FALSE);
			}
			else
				m_list[i].EnableWindow();
			CString strTmp,str2;
			theLang.LoadString(str2,IDS_TBLNAME);
			strTmp.Format(_T("%s:%d"),str2,pApp->m_nTableId);
			m_table[i].SetWindowText(strTmp);
			theLang.LoadString(str2,IDS_CHKNUM);
			strTmp.Format(_T("%s%d/%d"),str2,pApp->m_nCheckNum,i+1);
			m_edit[i].SetWindowText(strTmp);
		}
		ShowWindow(0,SW_SHOW);
		POSITION pos=NULL;
		CString strTmp;
		CString decPlace;
		decPlace.Format(_T(".%df|"),theApp.DECIMAL_PLACES);
		for(pos=m_pOrderList->GetHeadPosition();pos!=NULL;)
		{
			OrderDetail* item=m_pOrderList->GetNext(pos);
			//非菜品不显示
			if (item->item_id<=0)
			{
				continue;
			}
			int activePage=item->n_checkID-1;
			if (activePage<0||activePage>=MAX_CHECKS)
			{
				activePage=0;
			}
			if (m_nCheckCount<activePage)
			{
				m_nCheckCount=activePage;
			}
			if (item->weight_required)//称重产品显示重量
			{
				strTmp.Format(_T("|1|%s\n%g %s|%")+decPlace,item->item_name,item->quantity,item->unit,item->total_price);
			}
			else
			{
				int iQuantity=(int)ceil(item->quantity);
				strTmp.Format(_T("|%d|%s|%")+decPlace,iQuantity,item->item_name,item->total_price);
			}
			int index=m_list[activePage].AddString(strTmp);
			m_list[activePage].SetItemDataPtr(index,item);
		}
		m_nCurrentPage=1;
		ShowCurrentPage();
	}
	catch(...)
	{
		LOG4CPLUS_ERROR(log_pos,"Catch Exception GetLastError="<<GetLastError());
	}
}
BEGIN_MESSAGE_MAP(SplitCheckDlg, CDialog)
	ON_WM_SIZE()
	ON_COMMAND_RANGE(IDC_BUTTON_NEXTPAGE,IDC_BUTTON_NEXTPAGE+50,&CPosPage::OnNextPage)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &SplitCheckDlg::OnBnClickedAddCheck)
	ON_BN_CLICKED(IDC_BUTTON_OK, &SplitCheckDlg::OnBnClickedDone)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, &SplitCheckDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON_PRE, &SplitCheckDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON_SHARE, &SplitCheckDlg::OnBnClickedShare)
	ON_BN_CLICKED(IDC_BUTTON_SPLITITEM, &SplitCheckDlg::OnBnClickedSplit)
	ON_BN_CLICKED(IDC_BUTTON_COMBINE, &SplitCheckDlg::OnBnClickedCommbine)
	ON_LBN_SETFOCUS(IDC_LIST1, &SplitCheckDlg::OnLbnSetfocusList1)
	ON_LBN_SETFOCUS(IDC_LIST1+1, &SplitCheckDlg::OnLbnSetfocusList2)
	ON_LBN_SETFOCUS(IDC_LIST1+2, &SplitCheckDlg::OnLbnSetfocusList3)
	ON_LBN_SETFOCUS(IDC_LIST1+3, &SplitCheckDlg::OnLbnSetfocusList4)
	ON_LBN_SETFOCUS(IDC_LIST1+4, &SplitCheckDlg::OnLbnSetfocusList5)
	ON_LBN_SETFOCUS(IDC_LIST1+5, &SplitCheckDlg::OnLbnSetfocusList6)
	ON_LBN_SETFOCUS(IDC_LIST1+6, &SplitCheckDlg::OnLbnSetfocusList7)
	ON_LBN_SETFOCUS(IDC_LIST1+7, &SplitCheckDlg::OnLbnSetfocusList8)
	ON_BN_CLICKED(IDC_BUTTON_LEFT, &SplitCheckDlg::OnBnClickedLeft)
	ON_BN_CLICKED(IDC_BUTTON_RIGHT, &SplitCheckDlg::OnBnClickedRight)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// SplitCheckDlg 消息处理程序

BOOL SplitCheckDlg::OnInitDialog()
{
	CPosPage::InitDialog(_T("Picture\\split.png"));
	CImage img;
	if(img.Load(_T("Picture\\splitbg.png"))==S_OK)
	{
		bpStatic=img.Detach();
	}
	CRect rect(0,0,0,0);
	//创建背景
	for (int i=0;i<MAX_CHECKS;i++)
	{
		m_static[i].Create(_T(""),WS_CHILD|SS_BITMAP,rect,this);
		m_static[i].SetBitmap(bpStatic);
	}
	CFont* font= GetFont();
	for (int i=0;i<MAX_CHECKS;i++)
	{
		m_list[i].Create(WS_CHILD|LBS_OWNERDRAWVARIABLE |LBS_HASSTRINGS|LBS_NOINTEGRALHEIGHT|WS_VISIBLE|LBS_MULTIPLESEL
			|WS_VSCROLL,rect,this,IDC_LIST1+i);
		m_list[i].m_nSubWidth[0]=30*CreatButton::m_nFullWidth/1024;
		m_list[i].m_nSubWidth[1]=100*CreatButton::m_nFullWidth/1024;
		m_list[i].m_nSubWidth[2]=60*CreatButton::m_nFullWidth/1024;
		m_edit[i].Create(WS_CHILD|WS_DISABLED,rect,this,1220+i);
		m_table[i].Create(WS_CHILD|WS_DISABLED,rect,this,1230+i);
		m_edit[i].SetFont(font);
		m_table[i].SetFont(font);
	}
	if (m_strTmplate.GetLength()==0)
	{
		m_strTmplate=_T("Page\\IDD_5_SPLIT.ini");
	}
	m_btnCtrl.GenaratePage2(m_strTmplate,this);

	m_pOrderList=&((CPOSClientApp*)AfxGetApp())->m_orderList;
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
void SplitCheckDlg::ShowWindow(int i,int nCmd)
{
	m_static[i].ShowWindow(nCmd);
	m_list[i].ShowWindow(nCmd);
	m_edit[i].ShowWindow(nCmd);
	m_table[i].ShowWindow(nCmd);
}
void SplitCheckDlg::ShowCurrentPage()
{
	for (int i=1;i<=m_nCheckCount;i++)
	{
		ShowWindow(i,SW_HIDE);
	}
	int nCount=1;
	for (int i=m_nCurrentPage;i<=m_nCheckCount&&(nCount<=3);i++,nCount++)
	{
		m_static[i].MoveWindow(nCount*m_nWidth+10,10,215*CreatButton::m_nFullWidth/1024,744*CreatButton::m_nFullHeight/768);
		m_table[i].MoveWindow(nCount*m_nWidth+15,30,80,30);
		m_edit[i].MoveWindow(nCount*m_nWidth+105*CreatButton::m_nFullWidth/1024,30,110*CreatButton::m_nFullWidth/1024,30);
		m_list[i].MoveWindow(nCount*m_nWidth+15,85,m_nWidth-15,650*CreatButton::m_nFullHeight/768);
		ShowWindow(i,SW_SHOW);
	}
}
void SplitCheckDlg::OnSize(UINT nType, int cx, int cy)
{
	CPosPage::OnSize(nType, cx, cy);
	cx=CreatButton::m_nFullWidth;
	cy=CreatButton::m_nFullHeight;
	m_nWidth=215*CreatButton::m_nFullWidth/1024;
// 	m_nHeight1=(int)(cy*0.04);
// 	m_nHeight=(int)(cy*0.9);
	int i=0;
	if (m_list[i].m_hWnd)
	{
		m_static[i].MoveWindow(10,10,215*CreatButton::m_nFullWidth/1024,744*CreatButton::m_nFullHeight/768);
		m_table[i].MoveWindow(15,30,80,30);
		m_edit[i].MoveWindow(105*CreatButton::m_nFullWidth/1024,30,110*CreatButton::m_nFullWidth/1024,30);
		m_list[i].MoveWindow(15,85,m_nWidth-15,650*CreatButton::m_nFullHeight/768);
	}
}
BOOL SplitCheckDlg::LockScreen()
{
	return FALSE;
}
void SplitCheckDlg::OnBnClickedAddCheck()
{
	if(m_nCheckCount>=MAX_CHECKS-1)
	{
		return;
	}
	m_nCheckCount++;
	if(m_nCheckCount>=4)
		m_nCurrentPage=m_nCheckCount-2;
	ShowCurrentPage();
}
void SplitCheckDlg::OnBnClickedDone()
{
	try{
		LOG4CPLUS_INFO(log_pos,"SplitCheckDlg::OnBnClickedDone Begin");
		OpenDatabase();
		CString strSQL;
		//更新列表里面的checkid
		for (int i=0;i<MAX_CHECKS;i++)
		{
			int length=m_list[i].GetCount();
			for(int j=0;j<length;j++)
			{
				OrderDetail* item=(OrderDetail*)m_list[i].GetItemDataPtr(j);
				int checkID=i+1;
				if (item->n_checkID!=checkID)
				{
					item->n_checkID=checkID;
					strSQL.Format(_T("UPDATE order_detail SET check_id=%d WHERE order_detail_id=%d;"),checkID,item->order_id);
					theDB.ExecuteSQL(strSQL);
				}
			}
		}
		
		//删除原来的菜品
		while(!m_splitedList.IsEmpty())
		{
			OrderDetail* item=m_splitedList.GetTail();
			m_splitedList.RemoveTail();
			POSITION pos=m_pOrderList->Find(item);
			if (pos)
			{
				m_pOrderList->RemoveAt(pos);
			}
			else
			{
				pos=m_newList.Find(item);
				m_newList.RemoveAt(pos);
			}
			//从数据库删除
			strSQL.Format(_T("DELETE FROM order_detail WHERE order_detail_id='%d';"),item->order_id);
			theDB.ExecuteSQL(strSQL);
			delete item;
		}
		//拆分后的加入列表和数据库
		CPOSClientApp* pApp=(CPOSClientApp*)AfxGetApp();
		while(!m_newList.IsEmpty())
		{
			OrderDetail* item=m_newList.GetTail();
			m_newList.RemoveTail();
			m_pOrderList->AddTail(item);
			//插入数据库
			strSQL.Format(_T("INSERT INTO order_detail(order_head_id,menu_item_id,menu_item_name,actual_price,")
				_T("order_time,condiment_belong_item,quantity,check_id,order_employee_id,product_price,unit,eat_type)")
				_T(" VALUES(\'%d\',\'%d\',\'%s\',\'%f\',now(),\'%d\',\'%f\',\'%d\',\'%s\',\'%f\',\'%s\',\'%d\');"),
				pApp->m_nOrderHeadid,item->item_id,item->item_name,item->total_price,item->n_belong_item,item->quantity,
				item->n_checkID,pApp->m_strUserID,item->item_price,item->unit,item->n_eattype);
			theDB.ExecuteSQL(strSQL);
			//获取item_id
			strSQL.Format(_T("SELECT LAST_INSERT_ID();"));
			CRecordset rs(&theDB);
			rs.Open(-1,strSQL);
			CString strCount;
			rs.GetFieldValue((short)0,strCount);
			item->order_id=_wtoi(strCount);
		}
		//对不存在的分单
		strSQL.Format(_T("UPDATE order_head SET should_amount=0,actual_amount=0,tax_amount=0 WHERE order_head_id=%d AND check_id NOT IN(SELECT check_id FROM order_detail WHERE order_head_id=%d GROUP BY check_id)")
			,pApp->m_nOrderHeadid,pApp->m_nOrderHeadid);
		theDB.ExecuteSQL(strSQL);
		//切换页面
		pApp->m_pMain->SetActivePage(DLG_ORDER);
	}
	catch(CDBException* e)
	{
		LOG4CPLUS_ERROR(log_pos,(LPCTSTR)e->m_strError);
		e->Delete();
		return;
	}
	catch(...)
	{
		LOG4CPLUS_ERROR(log_pos,"Catch Exception GetLastError="<<GetLastError());
	}
	LOG4CPLUS_INFO(log_pos,"SplitCheckDlg::OnBnClickedDone End");
}
void SplitCheckDlg::OnBnClickedCancel()
{
	//删除
	m_splitedList.RemoveAll();
	while(!m_newList.IsEmpty())
	{
		OrderDetail* item=m_newList.GetTail();
		m_newList.RemoveTail();
		delete item;
	}
	theApp.m_pMain->SetActivePage(m_nPrePage,TRUE);
}
void SplitCheckDlg::OnBnClickedShare()
{
}
void SplitCheckDlg::OnBnClickedSplit()
{
	try{
		if(m_list[m_nActive].GetSelCount()==0)
		{
			POSMessageBox(IDS_SELECTSPLIT);
			return;
		}
		//检查是否有未送厨的项
		for (int i=0;i<m_list[m_nActive].GetCount();i++)
		{
			if (m_list[m_nActive].GetSel(i))
			{
				OrderDetail* item=(OrderDetail*)m_list[m_nActive].GetItemDataPtr(i);
				if (item->n_saved==0)
				{
					POSMessageBox(IDS_CANOTSPLIT);
					return;
				}
			}
		}
		//输入份数
		NumberInputDlg dlg;
		theLang.LoadString(dlg.m_strHint,IDS_SPLITCOUNT);
		if(dlg.DoModal()==IDCANCEL)
			return;
		int count=_wtoi(dlg.m_strNum);
		if (count<=0||count>8)
		{
			POSMessageBox(IDS_NUMERROR);
			return;
		}
		CString strTmp;
		CString decPlace;
		decPlace.Format(_T(".%df|"),theApp.DECIMAL_PLACES);
		for (int i=0;i<m_list[m_nActive].GetCount();i++)
		{
			if (m_list[m_nActive].GetSel(i))
			{
				OrderDetail* item=(OrderDetail*)m_list[m_nActive].GetItemDataPtr(i);
				int iQuantity=(int)item->quantity;
				if(iQuantity==0&&!item->weight_required)
				{
					POSMessageBox(IDS_ALREADYSPLIT);
					continue;
				}
				m_list[m_nActive].DeleteString(i);
				m_splitedList.AddTail(item);
				for (int j=0;j<count;j++)
				{
					OrderDetail* newItem=new OrderDetail;
					memcpy(newItem,item,sizeof(OrderDetail));
					newItem->quantity=item->quantity/count;
					newItem->total_price=item->total_price/count;
					//ComputeTax(newItem);

					if(item->weight_required)
						strTmp.Format(_T("|1|%s\n%g %s|%")+decPlace,newItem->item_name,newItem->quantity,newItem->unit,newItem->total_price);
					else
					{
						if (iQuantity%count!=0)
						{
							CString name;
							name.Format(_T("%d/%d %s"),iQuantity,count,newItem->item_name);
							wcsncpy_s(newItem->item_name,name,63);
						}
						int tmpi=(int)ceil(newItem->quantity);
						strTmp.Format(_T("|%d|%s|%")+decPlace,tmpi,newItem->item_name,newItem->total_price);
					}
					int index=m_list[m_nActive].InsertString(i,strTmp);
					m_list[m_nActive].SetItemDataPtr(index,newItem);
					m_newList.AddTail(newItem);
				}
			}
		}
	}
	catch(...)
	{
		LOG4CPLUS_ERROR(log_pos,"Catch Exception GetLastError="<<GetLastError());
	}
}
void SplitCheckDlg::MoveSelected(int from,int to)
{
	try{
		//先复制
		int length=m_list[from].GetCount();
		for (int i=0;i<length;i++)
		{
			if (m_list[from].GetSel(i))
			{
				CString strTmp;
				m_list[from].GetText(i,strTmp);
				OrderDetail* item=(OrderDetail*)m_list[from].GetItemDataPtr(i);
				//加红色
				if (strTmp[0]=='|')
				{
					strTmp=_T("24")+strTmp;
				}
				int index=m_list[to].AddString(strTmp);
				m_list[to].SetItemDataPtr(index,item);
			}
		}
		//从原list中删除
		for (int i=length-1;i>=0;i--)
		{
			if (m_list[from].GetSel(i))
			{
				m_list[from].DeleteString(i);
			}
		}
		//设置没有选中
		m_list[to].SetCurSel(-1);
		//设置选中高亮
// 		m_edit[from].Invalidate();
// 		m_edit[to].Invalidate();
	}
	catch(...)
	{
		LOG4CPLUS_ERROR(log_pos,"Catch Exception GetLastError="<<GetLastError());
	}
}
void SplitCheckDlg::OnLbnSetfocusList1()
{
	if(m_nActive==0)
		return;
	MoveSelected(m_nActive,0);
	//设置当前list为active
	m_nActive=0;
}
void SplitCheckDlg::OnLbnSetfocusList2()
{
	if(m_nActive==1)
		return;
	MoveSelected(m_nActive,1);
	//设置当前list为active
	m_nActive=1;
}
void SplitCheckDlg::OnLbnSetfocusList3()
{
	if(m_nActive==2)
		return;
	MoveSelected(m_nActive,2);
	//设置当前list为active
	m_nActive=2;
}
void SplitCheckDlg::OnLbnSetfocusList4()
{
	if(m_nActive==3)
		return;
	MoveSelected(m_nActive,3);
	//设置当前list为active
	m_nActive=3;
}
void SplitCheckDlg::OnLbnSetfocusList5()
{
	if(m_nActive==4)
		return;
	MoveSelected(m_nActive,4);
	//设置当前list为active
	m_nActive=4;
}
void SplitCheckDlg::OnLbnSetfocusList6()
{
	if(m_nActive==5)
		return;
	MoveSelected(m_nActive,5);
	//设置当前list为active
	m_nActive=5;
}
void SplitCheckDlg::OnLbnSetfocusList7()
{
	if(m_nActive==6)
		return;
	MoveSelected(m_nActive,6);
	//设置当前list为active
	m_nActive=6;
}
void SplitCheckDlg::OnLbnSetfocusList8()
{
	if(m_nActive==7)
		return;
	MoveSelected(m_nActive,7);
	//设置当前list为active
	m_nActive=7;
}
void SplitCheckDlg::OnBnClickedCommbine()
{
	m_list[m_nActive].SelItemRange(TRUE,0,m_list[m_nActive].GetCount());
}
void SplitCheckDlg::OnBnClickedLeft()
{
	if(m_nCurrentPage<=1)
	{
		return;
	}
	m_nCurrentPage--;
	ShowCurrentPage();
}
void SplitCheckDlg::OnBnClickedRight()
{
	if(m_nCurrentPage>=m_nCheckCount-2)
	{
		return;
	}
	m_nCurrentPage++;
	ShowCurrentPage();
}

