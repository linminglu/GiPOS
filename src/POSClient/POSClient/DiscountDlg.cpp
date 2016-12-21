// DiscountDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "POSClient.h"
#include "DiscountDlg.h"
#include "OrderDlg.h"
#include "SelectItemDlg.h"
#include "NumberInputDlg.h"


// DiscountDlg 对话框

IMPLEMENT_DYNAMIC(DiscountDlg, CDialog)

DiscountDlg::DiscountDlg(CWnd* pParent /*=NULL*/)
: CDialog(DiscountDlg::IDD, pParent)
{
	ITEM_COLUMNSIZE=4;
	ITEM_LINESIZE=8;
	selectedItem.percent=0;
	m_nIsService=0;
	pParentWnd=NULL;
}

DiscountDlg::~DiscountDlg()
{
	for (CPbuttonIter iter = m_itemButtons.begin(); iter!= m_itemButtons.end();iter++)
	{
		CRoundButton2 *b = (*iter);
		b->DestroyWindow();
		delete b;
	}
	m_itemButtons.clear();
	delete m_bpButtonItem[0];
	delete m_bpButtonItem[1];
}

void DiscountDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_DISCOUNT, m_editDiscount);
	DDX_Control(pDX, IDC_BUTTON_PREPAGE, m_btnPrepage);
}


BEGIN_MESSAGE_MAP(DiscountDlg, CDialog)
	ON_COMMAND_RANGE(IDC_DYNAMIC_CTRL,IDC_DYNAMIC_CTRL+MAX_ITEMS,OnItemBnClicked)
	ON_BN_CLICKED(IDC_BUTTON_PREPAGE, &DiscountDlg::OnBnClickedButtonPre)
END_MESSAGE_MAP()


// DiscountDlg 消息处理程序

BOOL DiscountDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	int x=(int)(CreatButton::m_nFullWidth*0.356);
	CRect rect;
	CString str2;
	if(pParentWnd==NULL)
		pParentWnd= GetParent();
	pParentWnd->GetClientRect(&rect);
	pParentWnd->ClientToScreen(&rect);
	MoveWindow(rect.left+x,rect.top+15,(int)(CreatButton::m_nFullWidth*0.635),CreatButton::m_nFullHeight-30);
	//m_editDiscount.m_BackColor=RGB(148, 0, 211);
	int width=(int)(CreatButton::m_nFullWidth*0.4);
	m_editDiscount.MoveWindow(0,0,(int)(CreatButton::m_nFullWidth*0.45),CreatButton::m_nFullHeight/10);
	if(m_nIsService)
	{
		theLang.LoadString(str2,IDS_SERVICE);
		m_editDiscount.SetWindowText(str2);
	}
	else
	{
		theLang.LoadString(str2,IDS_DISCOUNT);
		m_editDiscount.SetWindowText(str2);
	}
	m_btnPrepage.MoveWindow((int)(CreatButton::m_nFullWidth*0.45)+20,0,150*CreatButton::m_nFullWidth/1024,75*CreatButton::m_nFullHeight/768);
	m_btnPrepage.SetImage(_T("Picture\\class\\prepage.png"));
	m_btnPrepage.SetTextColor(DEFALUT_TXT_COLOR);
	m_bpButtonItem[0]=Gdiplus::Image::FromFile(_T("Picture\\class\\pay.png"));
	m_bpButtonItem[1]=Gdiplus::Image::FromFile(_T("Picture\\class\\pay_.png"));
	theLang.LoadString(str2,IDS_PREPAGE);
	m_btnPrepage.SetWindowText(str2);
	CreatButtons();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
void DiscountDlg::CreatButtons()
{
	try{
		//获取位置
		CRect   rect;
		GetWindowRect(rect);
		ScreenToClient(&rect);
		rect.top=CreatButton::m_nFullHeight/10+10;
		rect.left+=20;
		SIZE buttonSize;
		buttonSize.cx=(rect.right-rect.left-10)/ITEM_COLUMNSIZE-8;
		buttonSize.cy=(rect.bottom-rect.top)/ITEM_LINESIZE-8;
		OpenDatabase();
		CRecordset rs( &theDB);
		CString strSQL,strName,strId;
		if(m_nIsService)
		{
			strSQL.Format(_T("SELECT * FROM service_tip;"));
			strName=_T("service_tip_name");
			strId=_T("service_tip_id");
		}
		else
		{
			strSQL.Format(_T("SELECT * FROM discount_service;"));
			strName=_T("discount_service_name");
			strId=_T("discount_service_id");
		}
		LOGFONT m_tLogFont;
		memset(&m_tLogFont,0,sizeof(LOGFONT));
		m_tLogFont.lfHeight	= ScaleY(24);
		wcscpy_s(m_tLogFont.lfFaceName, _T("Microsoft YaHei"));
		rs.Open( CRecordset::forwardOnly,strSQL);
		for(int i=0;i<ITEM_LINESIZE;i++)
		{
			POINT topleft;
			topleft.y=rect.top+i*(buttonSize.cy+8);
			for(int j=0;j<ITEM_COLUMNSIZE;j++)
			{
				if (rs.IsEOF())
					return;
				int count=i*ITEM_COLUMNSIZE+j;
				topleft.x=rect.left+j*(buttonSize.cx+8);
				DiscountItem item={0};
				rs.GetFieldValue(strName,item.name);
				rs.GetFieldValue(_T("display_name"),item.display_name);
				CRoundButton2* pBtn = new CRoundButton2;
				//pBtn->SetFont(&m_tLogFont);
				pBtn->Create(item.name,WS_CHILD|WS_VISIBLE ,CRect(topleft,buttonSize),this,IDC_DYNAMIC_CTRL+count);
				if (count<=9)
				{
					CString strTop;
					WCHAR c=0x2460+count;
					strTop.Format(_T("%c"),c);
					pBtn->SetStrTop(strTop);
				}
				pBtn->SetImages(m_bpButtonItem[0],m_bpButtonItem[1],false);
				m_itemButtons.push_back(pBtn);
				CDBVariant variant;
				variant.m_lVal=0;
				rs.GetFieldValue(strId, variant);
				item.id=variant.m_lVal;
				variant.m_iVal=0;
				rs.GetFieldValue(_T("privilege"), variant);
				item.privilege=variant.m_iVal;
				//是否自定义折扣
				variant.m_iVal=0;
				rs.GetFieldValue(_T("type"), variant);
				if(variant.m_iVal==1)
				{
					item.isOpenItem=TRUE;
				}
				variant.m_boolVal=0;
				rs.GetFieldValue(_T("preset"), variant);
				if(variant.m_boolVal)
				{
					CString strVal;
					rs.GetFieldValue(_T("percent"), strVal);
					item.percent=_wtof(strVal);
					//自定义比例
					if (item.isOpenItem)
					{
						item.percent=1;
					}
					variant.m_boolVal=FALSE;
					rs.GetFieldValue(_T("select_discount"), variant);
					item.select=variant.m_boolVal;
				}
				else
				{
					item.percent=-1;
					CString strVal;
					rs.GetFieldValue(_T("amount"), strVal);
					item.amount=_wtof(strVal);
				}
				variant.m_iVal=0;
				rs.GetFieldValue(_T("menu_level_class"), variant);
				item.round_type=variant.m_iVal;
				if(m_nIsService)
				{
					variant.m_boolVal=FALSE;
					rs.GetFieldValue(_T("discount_over_threshold"), variant);
					item.noDiscount=variant.m_boolVal;
				}
				m_Items.push_back(item);
				rs.MoveNext();
			}
		}
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
void DiscountDlg::OnItemBnClicked(UINT uID)
{
	try{
		int index=(uID-IDC_DYNAMIC_CTRL);
		if (index>=m_Items.size())
			return;
		CString userid;
		if (m_Items[index].privilege>0)
		{//需要权限
			int auth=OrderDlg::RequeastAuth(userid,_T("payment"),m_Items[index].privilege);
			if(auth!=0)
				return;
		}
		selectedItem=m_Items[index];
		if (m_Items[index].isOpenItem)
		{//自定义折扣
			NumberInputDlg dlg;
			if(m_Items[index].percent<0.001)
			{//按金额
				theLang.LoadString(IDS_INPUTAMOUNT,dlg.m_strHint);
				if(dlg.DoModal()==IDOK)
				{
					selectedItem.percent=-1;
					selectedItem.amount=_wtof(dlg.m_strNum);
					if (selectedItem.amount>=10000)
					{
						POSMessageBox(IDS_TOOMUCH);
						return;
					}
				}
				else
					return CDialog::OnCancel();
			}
			else
			{//按比例
				theLang.LoadString(dlg.m_strHint,IDS_INPUTPERCENT);
				if(dlg.DoModal()==IDOK)
				{
					selectedItem.percent=_wtof(dlg.m_strNum);
					if (selectedItem.percent>100)
					{
						POSMessageBox(IDS_TOOMUCH);
						return;
					}
					selectedItem.name.Format(_T("%s %0.0f%%"),selectedItem.name,selectedItem.percent);
					selectedItem.amount=0;
					if (m_Items[index].select)
					{//需要选择打折范围
						SelectItemDlg dlg;
						dlg.pParentWnd=pParentWnd;
						CPOSClientApp* pApp=(CPOSClientApp*)AfxGetApp();
						dlg.m_pOrderList=&(pApp->m_orderList);
						if(m_nIsService)
						{
							theLang.LoadString(dlg.m_strHint,IDS_SELECTSERVICE);
							dlg.m_nType=2;
						}
						else
							theLang.LoadString(dlg.m_strHint,IDS_SELECTDISCOUNT);
						dlg.m_nCheckID=m_nCheckID;
						dlg.percent=selectedItem.percent;
						if(dlg.DoModal()==IDCANCEL)
							return;
						selectedItem.percent=-1;
						selectedItem.amount=dlg.amount;
					}
				}
				else
					return CDialog::OnCancel();
			}
		}
		else
		{
			if (m_Items[index].select)
			{//需要选择打折范围
				SelectItemDlg dlg;
				dlg.pParentWnd=pParentWnd;
				CPOSClientApp* pApp=(CPOSClientApp*)AfxGetApp();
				dlg.m_pOrderList=&(pApp->m_orderList);
				if(m_nIsService)
				{
					theLang.LoadString(dlg.m_strHint,IDS_SELECTSERVICE);
					dlg.m_nType=2;
				}
				else
					theLang.LoadString(dlg.m_strHint,IDS_SELECTDISCOUNT);
				dlg.m_nCheckID=m_nCheckID;
				dlg.percent=m_Items[index].percent;
				if(dlg.DoModal()==IDCANCEL)
					return;
				selectedItem.percent=-1;//部分折
				selectedItem.amount=dlg.amount;
			}
			else
			{
				selectedItem.percent=m_Items[index].percent;
				selectedItem.amount=m_Items[index].amount;
			}
		}
		CDialog::OnOK();
	}
	catch(...)
	{
		LOG4CPLUS_ERROR(log_pos,"Catch Exception GetLastError="<<GetLastError());
	}
}
void DiscountDlg::OnBnClickedButtonPre()
{
	CDialog::OnCancel();
}
BOOL DiscountDlg::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message==WM_KEYDOWN)
	{
		switch (pMsg->wParam)
		{
		case VK_RETURN:
		case VK_SPACE:
			return TRUE;
		case VK_BACK:
		case VK_PRIOR:
		case VK_NEXT:
			CDialog::OnCancel();
			return TRUE;
		}
		if (pMsg->wParam>='1'&&pMsg->wParam<='9')
		{
			OnItemBnClicked(pMsg->wParam-'1'+IDC_DYNAMIC_CTRL);
			return TRUE;
		}
		else if (pMsg->wParam>=VK_NUMPAD1&&pMsg->wParam<=VK_NUMPAD9)
		{
			OnItemBnClicked(pMsg->wParam-VK_NUMPAD1+IDC_DYNAMIC_CTRL);
			return TRUE;
		}
	}
	return CDialog::PreTranslateMessage(pMsg); 
}