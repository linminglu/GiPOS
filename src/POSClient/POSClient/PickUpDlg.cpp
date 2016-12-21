// PickUpDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "POSClient.h"
#include "PickUpDlg.h"
#include "FloorDlg.h"
#include <math.h> 
using namespace std;

// PickUpDlg 对话框

IMPLEMENT_DYNAMIC(PickUpDlg, CDialog)

PickUpDlg::PickUpDlg(CWnd* pParent /*=NULL*/)
: CDialog(PickUpDlg::IDD, pParent)
{
	m_nCurrentPage=0;
	m_nType=0;
	m_nPageCount=1;
	ITEM_COLUMNSIZE=6;
	ITEM_LINESIZE=3;
	m_nIndex=-1;
	m_nFilterTable=-1;
	pParentWnd=NULL;
}

PickUpDlg::~PickUpDlg()
{
	m_Items.clear();
	for (CPbuttonIter iter = m_itemButtons.begin(); iter!= m_itemButtons.end();iter++)
	{
		CRoundButton2 *b = (*iter);
		b->DestroyWindow();
		delete b;
	}
	m_itemButtons.clear();
	m_btnCtrl.ReleaseBtn();
	::DeleteObject(m_bpBackgrd);
	delete m_bpCheckItem[0];
	delete m_bpCheckItem[1];
}

void PickUpDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_LOG, m_user);
	DDX_Control(pDX, IDC_STATIC_TIME, m_time);
	DDX_Control(pDX, IDC_STATIC_HINT, m_hint);
}


BEGIN_MESSAGE_MAP(PickUpDlg, CDialog)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, &PickUpDlg::OnBnClickedButtonCancel)
	ON_BN_CLICKED(IDC_BUTTON_UP, &PickUpDlg::OnBnClickedButtonUp)
	ON_BN_CLICKED(IDC_BUTTON_DOWN, &PickUpDlg::OnBnClickedButtonDown)
	ON_COMMAND_RANGE(IDC_DYNAMIC_CTRL,IDC_DYNAMIC_CTRL+MAX_ITEMS,OnItemBnClicked)
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// PickUpDlg 消息处理程序

void PickUpDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	cx=CreatButton::m_nFullWidth;
	cy=CreatButton::m_nFullHeight;
	if (m_user.m_hWnd)
	{
		int height=(int)(cy*0.04);
		m_user.MoveWindow(200*cx/1024,30,130*cx/1024,height);
		m_time.MoveWindow(350*cx/1024,30,300*cx/1024,height);
		m_hint.MoveWindow(680*cx/1024,30,300*cx/1024,height);
	}
	CStatic* pCtrl=(CStatic*)GetDlgItem(IDC_STATIC);
	if (pCtrl)
	{
		pCtrl->MoveWindow(30,110,cx-60,(int)(cy*0.75));
	}
}

BOOL PickUpDlg::OnInitDialog()
{
	try{
		CDialog::OnInitDialog();
		CRect rect;
		if(pParentWnd==NULL)
		pParentWnd= GetParent();
		pParentWnd->GetClientRect(&rect);
		pParentWnd->ClientToScreen(&rect);
		MoveWindow(rect);

		CImage img;
		if(img.Load(_T("Picture\\pickup.png"))==S_OK)
		{
			m_x=img.GetWidth();
			m_y=img.GetHeight();
			m_bpBackgrd=img.Detach();
		}
		m_bpCheckItem[0]=Gdiplus::Image::FromFile(_T("Picture\\bg_checkitem.png"));
		m_bpCheckItem[1]=Gdiplus::Image::FromFile(_T("Picture\\bg_checkitem_.png"));
		
		m_btnCtrl.GenaratePage2(_T("Page\\IDD_PICKUP.ini"),this);
		theLang.UpdatePage(this,_T("DEFAULT"),TRUE);
		//获取位置
		GetDlgItem(IDC_STATIC)->GetWindowRect(rect);
		ScreenToClient(&rect);
		SIZE buttonSize;
		buttonSize.cx=rect.Width()/ITEM_COLUMNSIZE-5;
		buttonSize.cy=(rect.bottom-rect.top)/ITEM_LINESIZE-10;
		//创建按钮
		for(int i=0;i<ITEM_LINESIZE;i++)
		{
			POINT topleft;
			topleft.y=rect.top+i*(buttonSize.cy+10);
			for(int j=0;j<ITEM_COLUMNSIZE;j++)
			{
				int count=i*ITEM_COLUMNSIZE+j;
				topleft.x=rect.left+j*(buttonSize.cx+5);
				CRoundButton2* pBtn = new CRoundButton2;
				pBtn->Create(_T(""),WS_CHILD ,CRect(topleft,buttonSize),this,IDC_DYNAMIC_CTRL+count);
				pBtn->SetImages(m_bpCheckItem[0],m_bpCheckItem[1],false);
				//pBtn->SetTextColor()
				m_itemButtons.push_back(pBtn);
			}
		}
		if(m_strHint.IsEmpty())
			theLang.LoadString(m_strHint,IDS_READY);
		m_hint.SetWindowText(m_strHint);
		m_user.SetWindowText(((CPOSClientApp*)AfxGetApp())->m_strUserName);
		SYSTEMTIME st;
		CString strTime;
		GetLocalTime(&st);
		strTime.Format(_T("%4d-%02d-%02d %02d:%02d"),st.wYear,st.wMonth,st.wDay,st.wHour,st.wMinute);
		m_time.SetWindowText(strTime);

		if(m_nType==0)
		{
			if(m_strSQL.IsEmpty())
				m_strSQL.Format(_T("SELECT * FROM order_head WHERE status=0 AND table_id>0 AND table_id<>%d"),m_nFilterTable);
			GetOpenChecks(m_strSQL);
		}
		else if(m_nType==2)
		{//已结单
			GetOpenChecks(m_strSQL);
		}
		else
		{
			m_strSQL.Format(_T("SELECT * FROM parties WHERE status=0"));
			GetParties(m_strSQL);
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
/************************************************************************
* 函数介绍：查询所有的单
* 输入参数：
* 输出参数：
* 返回值  ：
************************************************************************/
void PickUpDlg::GetOpenChecks(CString strSQL)
{
	try{
		m_Items.clear();
		OpenDatabase();
		CRecordset rs( &theDB);
		
		rs.Open( CRecordset::forwardOnly,strSQL);
		while(!rs.IsEOF())
		{
			CheckItem item={0};
			CDBVariant variant;
			rs.GetFieldValue(_T("check_number"), variant);
			item.check_number=variant.m_lVal;
			rs.GetFieldValue(_T("order_head_id"), variant);
			item.order_head_id=variant.m_lVal;
			rs.GetFieldValue(_T("table_id"), variant);
			item.table_id=variant.m_lVal;
			rs.GetFieldValue(_T("table_name"), item.table_name);
			rs.GetFieldValue(_T("check_id"), variant);
			item.check_id=variant.m_iVal;
			CString check_name;
			rs.GetFieldValue(_T("check_name"), check_name);

			rs.GetFieldValue(_T("order_start_time"), variant);
			item.order_start_time.Format(_T("%02d:%02d"),variant.m_pdate->hour,variant.m_pdate->minute);
			CString strVal;
			if(m_nType==2)
				rs.GetFieldValue(_T("actual_amount"), strVal);
			else
				rs.GetFieldValue(_T("should_amount"), strVal);
			item.should_amount=_wtof(strVal);
			rs.GetFieldValue(_T("status"),variant);
			item.status=variant.m_iVal;
			CString strTbl,strChk,strChkname;
			theLang.LoadString(strChk,IDS_CHKNUM);
			theLang.LoadString(strTbl,IDS_TBLNAME);
			theLang.LoadString(strChkname,IDS_CHKNAME);
			if (check_name.GetLength()==0)
			{
				item.display.Format(_T("%s: %s/%d\n%s %d\n%s\n%s%0.2f"),strTbl,item.table_name,
				item.check_id,strChk,item.check_number,item.order_start_time,theApp.CURRENCY_SYMBOL,item.should_amount);
			}
			else
			{
				item.display.Format(_T("%s: %s/%d\n%s %d\n%s %s\n%s\n%s%0.2f"),strTbl,item.table_name,
				item.check_id,strChk,item.check_number,strChkname,check_name,item.order_start_time,theApp.CURRENCY_SYMBOL,item.should_amount);
			}
			
			m_Items.push_back(item);
			rs.MoveNext();
		}
		rs.Close();
		m_nCurrentPage=0;
		m_nPageCount=(int)ceil((float)m_Items.size()/(ITEM_LINESIZE*ITEM_COLUMNSIZE));
		ShowCurrentPage();
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
}
/************************************************************************
* 函数介绍：查询宴会单
* 输入参数：
* 输出参数：
* 返回值  ：
************************************************************************/
void PickUpDlg::GetParties(CString strSQL)
{
	try{
		m_Items.clear();
		OpenDatabase();
		CRecordset rs( &theDB);
		rs.Open( CRecordset::forwardOnly,strSQL);
		while(!rs.IsEOF())
		{
			CheckItem item={0};
			CDBVariant variant;
			rs.GetFieldValue(_T("party_id"), variant);
			item.order_head_id=variant.m_lVal;
			rs.GetFieldValue(_T("table_num"), variant);
			item.table_id=variant.m_lVal;
			rs.GetFieldValue(_T("table_str"), item.table_name);
			item.table_name=item.table_name.Left(10);
			CString check_name,amount;
			rs.GetFieldValue(_T("party_name"), check_name);
			rs.GetFieldValue(_T("party_time"), item.order_start_time);
			rs.GetFieldValue(_T("table_price"), amount);

			CString str2;
			theLang.LoadString(str2,IDS_PICKUPPARTY);
			item.display.Format(str2,check_name,item.order_start_time,item.table_name,item.table_id,amount);
			m_Items.push_back(item);
			rs.MoveNext();
		}
		rs.Close();
		m_nCurrentPage=0;
		m_nPageCount=(int)ceil((float)m_Items.size()/(ITEM_LINESIZE*ITEM_COLUMNSIZE));
		ShowCurrentPage();
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
}

/************************************************************************
* 函数介绍：显示当前页
* 输入参数：
* 输出参数：
* 返回值  ：
************************************************************************/
void PickUpDlg::ShowCurrentPage()
{
	try{
		UINT index;
		for(int i=0;i<ITEM_LINESIZE*ITEM_COLUMNSIZE;i++)
		{
			index=i+m_nCurrentPage*(ITEM_LINESIZE*ITEM_COLUMNSIZE);
			CRoundButton2* pButton2=(CRoundButton2*)GetDlgItem(IDC_DYNAMIC_CTRL+i);
			if(index<m_Items.size())
			{
				pButton2->SetWindowText(m_Items[index].display);
				pButton2->ShowWindow(SW_SHOW);
			}
			else
			{
				pButton2->ShowWindow(SW_HIDE);
			}
		}
	}
	catch(...)
	{
		LOG4CPLUS_ERROR(log_pos,"Catch Exception GetLastError="<<GetLastError());
	}
}

void PickUpDlg::OnBnClickedButtonCancel()
{
	CDialog::OnCancel();
}
void PickUpDlg::OnItemBnClicked(UINT uID)
{
	m_nIndex=m_nCurrentPage*(ITEM_LINESIZE*ITEM_COLUMNSIZE)+(uID-IDC_DYNAMIC_CTRL);
	return CDialog::OnOK();
}
void PickUpDlg::OnBnClickedButtonUp()
{
	if(m_nCurrentPage>0)
		m_nCurrentPage--;
	else
		return;
	ShowCurrentPage();
}
void PickUpDlg::OnBnClickedButtonDown()
{
	if(m_nCurrentPage<m_nPageCount-1)
		m_nCurrentPage++; 
	else
		return;
	ShowCurrentPage();
}
BOOL PickUpDlg::OnEraseBkgnd(CDC* pDC)
{
	if (m_bpBackgrd==NULL)
	{
		return FALSE;
	}
	CDC MemDc;
	MemDc.CreateCompatibleDC(pDC);
	HGDIOBJ hOldBmp = MemDc.SelectObject(m_bpBackgrd);
	pDC->SetStretchBltMode(HALFTONE);
	pDC->StretchBlt(0,0,CreatButton::m_nFullWidth,CreatButton::m_nFullHeight,&MemDc,0,0,m_x,m_y,SRCCOPY);
	MemDc.SelectObject(hOldBmp);
	return TRUE;
}
HBRUSH PickUpDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	if(nCtlColor==CTLCOLOR_STATIC)
	{
		pDC->SetTextColor(m_dTextColor);
		pDC->SetBkMode(TRANSPARENT);
		return (HBRUSH)::GetStockObject(NULL_BRUSH); //返回此画刷可以使静态文本透明
	}
	return   hbr; 
	
}
