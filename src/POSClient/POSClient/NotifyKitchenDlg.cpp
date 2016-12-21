// NotifyKitchenDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "POSClient.h"
#include "NotifyKitchenDlg.h"
#include "NumberInputDlg.h"


// NotifyKitchenDlg 对话框

IMPLEMENT_DYNAMIC(NotifyKitchenDlg, CDialog)

NotifyKitchenDlg::NotifyKitchenDlg(CWnd* pParent /*=NULL*/)
	: CDialog(NotifyKitchenDlg::IDD, pParent)
{
	m_bpBackgrd=NULL;
	pBelongItem=NULL;
	pOrderDlg=NULL;
	pComboDlg=NULL;
	CLASS_LINESIZE=8;
	type=0;
	m_nShowHint=0;
	m_nDefaultGroup=1;
	m_CheckedClassButton=NULL;
}

NotifyKitchenDlg::~NotifyKitchenDlg()
{
	for (CPbuttonIter iter = m_itemButtons.begin(); iter!= m_itemButtons.end();iter++)
	{
		CRoundButton2 *b = (*iter);
		b->DestroyWindow();
		delete b;
	}
	m_itemButtons.clear();

	::DeleteObject(m_bpBackgrd);
	delete m_bpButtonItem[0];
	delete m_bpButtonItem[1];
	delete m_bpButtonSLU[0];
	delete m_bpButtonSLU[1];
	delete m_bpSlodoutItem[0];
	delete m_bpSlodoutItem[1];
}

void NotifyKitchenDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, mComboBox);
	DDX_Control(pDX, IDC_EDIT1, mEdit);
	DDX_Control(pDX, IDOK, m_btOK);
	DDX_Control(pDX, IDCANCEL, m_btCancel);
	DDX_Control(pDX, IDC_BUTTON_CLEAR, m_btClear);
	DDX_Control(pDX, IDC_BUTTON_CLEARPRE, m_btClearPre);
	DDX_Control(pDX, IDC_BUTTON_SOFTKEY, m_softButton);
	DDX_Control(pDX, IDC_BUTTON_HANDINPUT,m_handButton);
	DDX_Control(pDX, IDC_BUTTON1, m_bt1);
	DDX_Control(pDX, IDC_BUTTON2, m_bt2);
	DDX_Control(pDX, IDC_BUTTON3, m_bt3);
	DDX_Control(pDX, IDC_BUTTON4, m_bt4);
}


BEGIN_MESSAGE_MAP(NotifyKitchenDlg, CDialog)
	ON_COMMAND_RANGE(IDC_SLU_BUTTON,IDC_SLU_BUTTON+999,OnSluBnClicked)//SLU
	ON_COMMAND_RANGE(IDC_DYNAMIC_CTRL,IDC_DYNAMIC_CTRL+MAX_ITEMS,OnItemBnClicked)
	ON_COMMAND_RANGE(IDC_BUTTON1,IDC_BUTTON4,OnBnClickedButtonPrefix)
	ON_BN_CLICKED(IDC_BUTTON_LEFT, OnBnClickedButtonLeft)
	ON_BN_CLICKED(IDC_BUTTON_RIGHT, OnBnClickedButtonRight)
	ON_BN_CLICKED(IDOK, &NotifyKitchenDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_SOFTKEY, &NotifyKitchenDlg::OnBnClickedButtonSoftkey)
	ON_BN_CLICKED(IDC_BUTTON_HANDINPUT, &NotifyKitchenDlg::OnBnClickedCtrlHandInput)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, OnBnClickedButtonClear)
	ON_BN_CLICKED(IDC_BUTTON_CLEARPRE, OnBnClickedButtonClearPre)
	ON_BN_CLICKED(IDC_BUTTON_UP, &NotifyKitchenDlg::OnBnClickedButtonUp)
	ON_BN_CLICKED(IDC_BUTTON_DOWN, &NotifyKitchenDlg::OnBnClickedButtonDown)
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


BOOL NotifyKitchenDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	//SetWindowPos(NULL,0,0,ScaleX(775),ScaleY(577),SWP_NOZORDER|SWP_NOMOVE);
	CImage imgB;
	if(imgB.Load(_T("Picture\\bg_notifykit.png"))==S_OK)
	{
		m_x=imgB.GetWidth();
		m_y=imgB.GetHeight();
		m_bpBackgrd=imgB.Detach();
	}
	m_btOK.SetImage(_T("Picture\\bt_ok.png"));
	m_btCancel.SetImage(_T("Picture\\bt_cancel.png"));
	m_btClear.SetImage(_T("Picture\\bt_orange_71.png"));
	m_btClearPre.SetImage(_T("Picture\\bt_orange_71.png"));
	m_handButton.SetImage(_T("Picture\\bt_orange_71.png"));
		
	m_bt1.SetImage(_T("Picture\\bt_100.png"));
	m_bt2.SetImage(_T("Picture\\bt_100.png"));
	m_bt3.SetImage(_T("Picture\\bt_100.png"));
	m_bt4.SetImage(_T("Picture\\bt_100.png"));
	m_softButton.SetImage(_T("Picture\\softboard.png"));

	if (!theLang.m_bDefaultLang)
	{
		SetFont(&theLang.m_dialogFont);
		CWnd* pCtrl=GetDlgItem(IDOK);
		theLang.TranslateDlgItem(pCtrl,IDS_OK);
		pCtrl=GetDlgItem(IDCANCEL);
		theLang.TranslateDlgItem(pCtrl,IDS_CANCEL);
		pCtrl=GetDlgItem(IDC_STATIC2);
		theLang.TranslateDlgItem(pCtrl,IDS_SELECTDEPART);
		pCtrl=GetDlgItem(IDC_BUTTON1);
		theLang.TranslateDlgItem(pCtrl,IDS_WITH);
		pCtrl=GetDlgItem(IDC_BUTTON2);
		theLang.TranslateDlgItem(pCtrl,IDS_WITHOUT);
		pCtrl=GetDlgItem(IDC_BUTTON3);
		theLang.TranslateDlgItem(pCtrl,IDS_MORE);
		pCtrl=GetDlgItem(IDC_BUTTON4);
		theLang.TranslateDlgItem(pCtrl,IDS_LESS);
		pCtrl=GetDlgItem(IDC_BUTTON_CLEAR);
		theLang.TranslateDlgItem(pCtrl,IDS_IDS_CLEARALL);
		pCtrl=GetDlgItem(IDC_BUTTON_CLEARPRE);
		theLang.TranslateDlgItem(pCtrl,IDS_CANCELMAKE);
		pCtrl=GetDlgItem(IDC_BUTTON_HANDINPUT);
		theLang.TranslateDlgItem(pCtrl,IDS_HANDINPUT);
	}
	CString str2;
	CString strSQL;
	if(type==2)
		mEdit.SetLimitText(50);
	else
		mEdit.SetLimitText(150);
	if (m_nShowHint==1)
	{
		theLang.LoadString(str2,IDS_ADDREQHINT);
		mEdit.SetPromptText(str2);
	}
	else
		mEdit.SetWindowText(m_strText);
	if (!m_strTtitle.IsEmpty())
	{
		SetWindowText(m_strTtitle);
	}
	
	if(type==0)
	{//通知厨房
		mComboBox.ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC2)->ShowWindow(SW_SHOW);
		theLang.LoadString(str2,IDS_ALLDEPART);
		mComboBox.AddString(str2);
		mPrintclassId.push_back(-1);
		try
		{
			OpenDatabase();
			CRecordset rs( &theDB);
			strSQL.Format(_T("SELECT * FROM print_class;"));
			rs.Open(CRecordset::forwardOnly,strSQL);
			while (!rs.IsEOF())
			{
				CDBVariant variant;
				CString class_name;
				rs.GetFieldValue(_T("print_class_id"),variant);
				mPrintclassId.push_back(variant.m_iVal);
				rs.GetFieldValue(_T("print_class_name"),class_name);
				mComboBox.AddString(class_name);
				rs.MoveNext();
			}
			rs.Close();
		}
		catch(CDBException* e)
		{
			LOG4CPLUS_ERROR(log_pos,(LPCTSTR)e->m_strError);
			AfxMessageBox(e->m_strError,MB_ICONEXCLAMATION);
			e->Delete();
		}
		mComboBox.SetCurSel(0);
	}
	
	SIZE buttonSize;
	buttonSize.cx=122;
	buttonSize.cy=58;
	m_bpButtonItem[0]=Gdiplus::Image::FromFile(_T("Picture\\class\\cond.png"));
	m_bpButtonItem[1]=Gdiplus::Image::FromFile(_T("Picture\\class\\cond_.png"));
	m_bpButtonSLU[0]=Gdiplus::Image::FromFile(_T("Picture\\class\\class.png"));
	m_bpButtonSLU[1]=Gdiplus::Image::FromFile(_T("Picture\\class\\class_.png"));
	m_btOK.SetTextColor(DEFALUT_TXT_COLOR);
	m_btCancel.SetTextColor(DEFALUT_TXT_COLOR);
	m_btClear.SetTextColor(DEFALUT_TXT_COLOR);
	m_btClearPre.SetTextColor(DEFALUT_TXT_COLOR);
	m_softButton.SetTextColor(DEFALUT_TXT_COLOR);
	m_handButton.SetTextColor(DEFALUT_TXT_COLOR);
	m_bt1.SetTextColor(DEFALUT_TXT_COLOR);
	m_bt2.SetTextColor(DEFALUT_TXT_COLOR);
	m_bt3.SetTextColor(DEFALUT_TXT_COLOR);
	m_bt4.SetTextColor(DEFALUT_TXT_COLOR);
	m_bpSlodoutItem[0]=Gdiplus::Image::FromFile(_T("Picture\\class\\sold.png"));
	m_bpSlodoutItem[1]=Gdiplus::Image::FromFile(_T("Picture\\class\\sold_.png"));
	//创建左侧分类按钮
	try{
		int TOPHEIGHT=10;
		CRecordset rs( &theDB);
		strSQL.Format(_T("SELECT * FROM condiment_groups "));
		if(rs.Open(CRecordset::snapshot,strSQL))
		{
			POINT topleft;
			topleft.x=14;
			topleft.y=TOPHEIGHT;
			int count=0;
			while (!rs.IsEOF())
			{
				count++;
				rs.MoveNext();
			}
			if(count<=CLASS_LINESIZE)
				m_uTotalPage=1;
			else
			{
				m_uTotalPage=ceil((count-2*(CLASS_LINESIZE-1))/(CLASS_LINESIZE-2.0))+2;
			}
			rs.MoveFirst();
			//分页，创建翻页按钮
			CRoundButton2* upBtn;
			CRoundButton2* downBtn;
			if (m_uTotalPage>1)
			{
				upBtn=new CRoundButton2;
				upBtn->Create(_T(""),WS_CHILD ,CRect(topleft,buttonSize),this,IDC_BUTTON_UP);
				upBtn->SetImage(_T("Picture\\class\\bt_up.png"));
				m_itemButtons.push_back(upBtn);

				topleft.y+=(buttonSize.cy)*(CLASS_LINESIZE-1);
				downBtn=new CRoundButton2;
				downBtn->Create(_T(""),WS_CHILD ,CRect(topleft,buttonSize),this,IDC_BUTTON_DOWN);
				downBtn->SetImage(_T("Picture\\class\\bt_down.png"));
				m_itemButtons.push_back(downBtn);
			}
			CDBVariant variant;
			CString strName;
			int pIndex=0;//在页内的索引
			m_uCurPage=0;
			while(!rs.IsEOF())
			{
				rs.GetFieldValue(_T("scomdiment_groups_id"),variant);
				topleft.y=pIndex*(buttonSize.cy)+TOPHEIGHT;
				rs.GetFieldValue(_T("comdiment_groups_name"),strName);
				CRoundButton2* pBtn=new CRoundButton2;
				pBtn->SetTextColor(RGB(0,0,0),RGB(236,148,65));
				pBtn->Create(strName,WS_CHILD ,CRect(topleft,buttonSize),this,IDC_SLU_BUTTON+variant.m_iVal);
				pBtn->SetImages(m_bpButtonSLU[0],m_bpButtonSLU[1],false);
				m_itemButtons.push_back(pBtn);
				m_classButtons.push_back(pBtn);
				rs.MoveNext();
				//下一次的位置
				pIndex++;
				if(m_uTotalPage>1)
				{//有翻页
					if (pIndex==CLASS_LINESIZE-1)
					{
						//如果不是最后一页,插入下一页
						if (m_uCurPage<m_uTotalPage-1)
						{
							m_classButtons.push_back(downBtn);
							m_classButtons.push_back(upBtn);
							pIndex=1;
							m_uCurPage++;
						}
					}
				}
			}
			rs.Close();
			m_uCurPage=0;
			ShowClassPage();
		}

	}catch(...)
	{
	}
	
	CRect   rect;
	rect.top=ScaleY(15);
	rect.left=buttonSize.cx+ScaleX(22);
	buttonSize.cx=ScaleX(100);
	//创建菜品按钮
	int ITEM_COLUMNSIZE=6;
	int ITEM_LINESIZE=6;
	int i=0;
	if (type==0)
	{
		ITEM_LINESIZE=5;//通知厨房，第一行不要
		rect.top+=(buttonSize.cy+5);
	}
	m_nPageSize=ITEM_LINESIZE*ITEM_COLUMNSIZE-2;
	for(;i<ITEM_LINESIZE;i++)
	{
		POINT topleft;
		topleft.y=rect.top+i*(buttonSize.cy+5);
		CString str2;
		for(int j=0;j<ITEM_COLUMNSIZE;j++)
		{
			int count=i*ITEM_COLUMNSIZE+j;
			topleft.x=rect.left+j*(buttonSize.cx+5);
			CRoundButton2* pBtn=new CRoundButton2;
			//最后2个按钮为翻页按钮
			if (count==m_nPageSize)
			{//前一页
				pBtn->Create(_T(""),WS_CHILD ,CRect(topleft,buttonSize),this,IDC_BUTTON_LEFT);
				pBtn->SetImage(_T("Picture\\bt_left.png"));
			}
			else if (count==m_nPageSize+1)
			{//后一页
				pBtn->Create(_T(""),WS_CHILD ,CRect(topleft,buttonSize),this,IDC_BUTTON_RIGHT);
				pBtn->SetImage(_T("Picture\\bt_right.png"));
			}
			else
			{
				pBtn->Create(_T(""),WS_CHILD ,CRect(topleft,buttonSize),this,IDC_DYNAMIC_CTRL+count);
				pBtn->SetImages(m_bpButtonItem[0],m_bpButtonItem[1],false);
			}
			m_itemButtons.push_back(pBtn);
			pBtn->SetTextColor(DEFALUT_TXT_COLOR);
		}
	}
	if (m_nDefaultGroup>=0)
	{
		OnSluBnClicked(m_nDefaultGroup+IDC_SLU_BUTTON);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

// NotifyKitchenDlg 消息处理程序
BOOL NotifyKitchenDlg::OnEraseBkgnd(CDC* pDC)
{
	if (m_bpBackgrd==NULL)
	{
		return FALSE;
	}
	CRect rect;
	GetClientRect(&rect);
	CDC MemDc;
	MemDc.CreateCompatibleDC(pDC);
	MemDc.SelectObject(m_bpBackgrd);
	pDC->SetStretchBltMode(HALFTONE);
	pDC->StretchBlt(0,0,rect.Width(),rect.Height(),&MemDc,0,0,m_x,m_y,SRCCOPY);
	return TRUE;
}

void NotifyKitchenDlg::OnBnClickedButtonClear()
{
	mEdit.SetWindowText(_T(""));
}
/************************************************************************
* 函数介绍：取消最近一次的做法
* 输入参数：
* 输出参数：
* 返回值  ：
************************************************************************/
void NotifyKitchenDlg::OnBnClickedButtonClearPre()
{
	CString line;
	mEdit.GetWindowText(line);
	int index=line.ReverseFind(' ');
	if (index==-1)
	{//没有空格
		mEdit.SetWindowText(_T(""));
	}
	else if(index==line.GetLength()-1)
	{//最后一个是空格
		line = line.Left(index);
		index=line.ReverseFind(' ');
		if (index!=-1)
		{
			line.Delete(index+1,line.GetLength()-index-1);
			mEdit.SetWindowText(line);
		}
		else
			mEdit.SetWindowText(_T(""));
		
	}
	else
	{
		line.Delete(index+1,line.GetLength()-index-1);
		mEdit.SetWindowText(line);
	}
	
}
/************************************************************************
* 函数介绍：获取调味品
* 输入参数：
* 输出参数：
* 返回值  ：
************************************************************************/
BOOL NotifyKitchenDlg::GetCondimentItems(int nGroup,vector<MenuItem>& items)
{
	OpenDatabase();
	CRecordset rs( &theDB);
	CString strSQL;
	if (nGroup==-1)
	{
		strSQL.Format(_T("SELECT * FROM(SELECT * FROM menu_item LEFT JOIN menu_item_class ON menu_item.class_id")
			_T("=menu_item_class.item_class_id WHERE item_type=1 ORDER BY slu_priority DESC)")
			_T(" AS T LEFT JOIN bargain_price_item ON T.item_id=bargain_price_item.bargain_item_number;"));
	}
	else
	{
		strSQL.Format(_T("SELECT * FROM(SELECT * FROM menu_item LEFT JOIN menu_item_class ON menu_item.class_id")
			_T("=menu_item_class.item_class_id WHERE item_id IN(SELECT DISTINCT menu_item_id FROM")
			_T(" condiment_membership WHERE condiment_groups_id=\'%d\') ORDER BY slu_priority DESC)")
			_T(" AS T LEFT JOIN bargain_price_item ON T.item_id=bargain_price_item.bargain_item_number;"),nGroup);
	}
	rs.Open( CRecordset::forwardOnly,strSQL);
	if(rs.GetRecordCount()==0)
	{//找不到配料，退出
		return FALSE;
	}
	items.clear();
	while(!rs.IsEOF())
	{
		MenuItem item={0};
		item.type=ITEM_CONDIMENT;
		CDBVariant variant;
		rs.GetFieldValue(_T("item_name1"), item.item_name1);
		rs.GetFieldValue(_T("item_name2"), item.item_name2);
		rs.GetFieldValue(_T("item_id"), variant);
		item.item_number=variant.m_lVal;
		variant.m_fltVal=0;
		rs.GetFieldValue(_T("price_1"), variant);
		item.price=variant.m_fltVal;
		rs.GetFieldValue(_T("unit_1"),item.unit);
		rs.GetFieldValue(_T("tax_group"), variant);
		item.tax_group=variant.m_iVal;
		//估清内容
		variant.m_iVal=0;
		rs.GetFieldValue(_T("bargain_stype"), variant);
		if (variant.m_iVal==1||variant.m_iVal==3)
		{//估清
			item.bargain_stype=1;
			item.bargain_num_cur=0;
		}
		else if (variant.m_iVal==2)
		{//限量销售
			item.bargain_stype=2;
			variant.m_fltVal=0;
			rs.GetFieldValue(_T("bargain_num_cur"), variant);
			item.bargain_num_cur=variant.m_fltVal;
		}
		try
		{
			variant.m_boolVal=FALSE;
			rs.GetFieldValue(_T("no_access_mgr"),variant);
			if(variant.m_boolVal)
				item.type=ITEM_OPEN;
			rs.GetFieldValue(_T("weight_entry_required"), variant);
			item.weight_required=variant.m_boolVal;
			variant.m_iVal=9;//不配置折扣级别的菜，默认最高级别，所有折扣都可使用
			rs.GetFieldValue(_T("discount_itemizer"), variant);
			item.n_discount_level=variant.m_iVal;
			variant.m_iVal=9;
			rs.GetFieldValue(_T("service_itemizer"), variant);
			item.n_service_level=variant.m_iVal;
		}catch(...)
		{
		}
		items.push_back(item);
		rs.MoveNext();
	}
	rs.Close();
	return TRUE;
}
/************************************************************************
* 函数介绍：显示当前页的菜品
* 输入参数：
* 输出参数：
* 返回值  ：
************************************************************************/
void NotifyKitchenDlg::ShowCurrentPage()
{
	try{
		unsigned int index;
		for(int i=0;i<m_nPageSize;i++)
		{
			index=i+m_nCurrentPage*m_nPageSize;
			CRoundButton2* pButton2=(CRoundButton2*)GetDlgItem(IDC_DYNAMIC_CTRL+i);
			if(index<m_Items.size())
			{
				CString tmp;
				{
					tmp.Format(_T("%s\n"),m_Items[index].item_name1);
					if (abs(m_Items[index].price)>0.001)
					{
						tmp.AppendFormat(_T("%0.1f"),m_Items[index].price);
					}
				}
				if (m_Items[index].type==ITEM_SLU||m_Items[index].type==ITEM_OPEN)
				{//SLU 颜色
					pButton2->SetImages(m_bpButtonSLU[0],m_bpButtonSLU[1],false);
				}
				else
					pButton2->SetImages(m_bpButtonItem[0],m_bpButtonItem[1],false);
				if (m_Items[index].bargain_stype!=0)
				{
					CString strTop;
					strTop.Format(_T("%.0f"),m_Items[index].bargain_num_cur);
					pButton2->SetStrTop(strTop);
					if (m_Items[index].bargain_num_cur<=0)
					{
						pButton2->SetImages(m_bpSlodoutItem[0],m_bpSlodoutItem[1],false);
					}
				}
				else
					pButton2->SetStrTop(_T(""));
				pButton2->SetWindowText(tmp);
				pButton2->ShowWindow(SW_SHOW);
			}
			else
			{
				pButton2->ShowWindow(SW_HIDE);
			}
		}
		CRoundButton2* pButton2=(CRoundButton2*)GetDlgItem(IDC_BUTTON_LEFT);
		if (m_nCurrentPage>0)
			pButton2->ShowWindow(SW_SHOW);
		else
			pButton2->ShowWindow(SW_HIDE);

		pButton2=(CRoundButton2*)GetDlgItem(IDC_BUTTON_RIGHT);
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
/************************************************************************
* 函数介绍：显示分类按钮的当前页
* 输入参数：
* 输出参数：
* 返回值  ：
************************************************************************/
void NotifyKitchenDlg::ShowClassPage()
{
	try{
		for(int i=0;i<m_classButtons.size();i++)
		{
			m_classButtons[i]->ShowWindow(SW_HIDE);
		}
		for (int i=m_uCurPage*CLASS_LINESIZE;i<(m_uCurPage+1)*CLASS_LINESIZE&&i<m_classButtons.size();i++)
		{
			m_classButtons[i]->ShowWindow(SW_SHOW);
		}
	}
	catch(...)
	{
		LOG4CPLUS_ERROR(log_pos,"Catch Exception GetLastError="<<GetLastError());
	}
}
/************************************************************************
* 函数介绍：分类显示翻页
* 输入参数：
* 输出参数：
* 返回值  ：
************************************************************************/
void NotifyKitchenDlg::OnBnClickedButtonUp()
{
	if(m_uCurPage>0)
		m_uCurPage--;
	else
		return;
	ShowClassPage();
}
void NotifyKitchenDlg::OnBnClickedButtonDown()
{
	if(m_uCurPage<m_uTotalPage-1)
		m_uCurPage++;
	else
		return;
	ShowClassPage();
}
/************************************************************************
* 函数介绍：翻页
* 输入参数：
* 输出参数：
* 返回值  ：
************************************************************************/
void NotifyKitchenDlg::OnBnClickedButtonLeft()
{
	if(m_nCurrentPage>0)
		m_nCurrentPage--;
	else
		return;
	ShowCurrentPage();
}

void NotifyKitchenDlg::OnBnClickedButtonRight()
{
	if(m_nCurrentPage<m_nPageCount-1)
		m_nCurrentPage++;
	else
		return;
	ShowCurrentPage();
}
/************************************************************************
* 函数介绍：点击了自定义菜
* 输入参数：
* 输出参数：
* 返回值  ：TRUE 成功  FALSE 用户取消
************************************************************************/
BOOL NotifyKitchenDlg::SetOpenItem(OrderDetail* item)
{
	try
	{
		CString userid;
		int auth=OrderDlg::RequeastAuth(userid,_T("open_item"));
		if (auth!=0)
			return FALSE;
		//输入菜品名称
		CString strname;
		StringInputDlg dlg;
		theLang.LoadString(dlg.m_strTitle,IDS_INPUTITEMNAME);
		dlg.m_bAutoComplete=TRUE;
		if(dlg.DoModal()==IDOK)
		{
			strname=dlg.m_strInput;
		}
		else
			return FALSE;
		strname.Trim();
		if (strname.GetLength()==0)
		{
			POSMessageBox(IDS_CANNOTEMPTY);
			return FALSE;
		}
		//输入菜品价格
		double price=0;
		NumberInputDlg dlgn;
		theLang.LoadString(dlgn.m_strHint,IDS_INPUTPRICE);
		while(true)
		{
			if(dlgn.DoModal()==IDOK)
			{
				price=_wtof(dlgn.m_strNum);
				if(price>999999){
					POSMessageBox(IDS_TOOMUCH);
					dlgn.m_strNum.Empty();
				}
				else
					break;
			}
			else
				return FALSE;
		}
		item->item_price=price;
		wcsncpy_s(item->item_name,strname,63);
		return TRUE;
	}
	catch(...)
	{
		LOG4CPLUS_ERROR(log_pos,"Catch Exception GetLastError="<<GetLastError());
	}
}

void NotifyKitchenDlg::OnItemBnClicked(UINT uID)
{
	try
	{
		UINT index=m_nCurrentPage*m_nPageSize+(uID-IDC_DYNAMIC_CTRL);
		//如果点击的是SLU
		if (index>=m_Items.size())
		{//越界
			LOG4CPLUS_ERROR(log_pos,"index=["<<index<<"] out of range. m_Items.size()="<<m_Items.size());
			return;
		}
		if ((type==1&&pBelongItem)&&(abs(m_Items[index].price)>0.001||m_Items[index].type==ITEM_OPEN))
		{//有价格配料特殊处理
			OrderDetail* item=new OrderDetail;
			memset(item,0,sizeof(OrderDetail));
			item->item_id=m_Items[index].item_number;
			item->n_discount_type=m_Items[index].n_discount_level;
			item->n_service_type=m_Items[index].n_service_level;
			item->n_eattype=theApp.m_nEatType;
			item->n_checkID=pBelongItem->n_checkID;
			item->n_seat_num=pBelongItem->n_seat_num;
			if(m_Items[index].weight_required)
			{//称重菜品根据重量来
				item->quantity=pBelongItem->quantity;
				item->weight_required=TRUE;
			}
			else
			{
				if(pBelongItem->quantity<0)
					item->quantity=-1;
				else
					item->quantity=1;
			}
			item->item_price=m_Items[index].price;
			item->belongto=pBelongItem;
			item->n_belong_item=pBelongItem->item_id;
			pBelongItem->b_hascondiment=TRUE;
			wcsncpy_s(item->unit,m_Items[index].unit,9);
			wcsncpy_s(item->item_name,m_Items[index].item_name1,63);
			wcsncpy_s(item->item_name2,m_Items[index].item_name2,31);
			if (m_Items[index].type==ITEM_OPEN)
			{
				if(SetOpenItem(item)==FALSE)
				{
					delete item;
					return;
				}
			}
			ComputeTotalPrice(item);
			item->bargain_stype=m_Items[index].bargain_stype;
			//设置沽清
			if(m_Items[index].bargain_stype==2&&item->quantity>0)
			{
				m_Items[index].bargain_num_cur=m_Items[index].bargain_num_cur-item->quantity;
				CString strSQL;
				strSQL.Format(_T("UPDATE bargain_price_item SET bargain_num_cur=bargain_num_cur-%f WHERE bargain_item_number=%d")
					,item->quantity,item->item_id);
				theDB.ExecuteSQL(strSQL);
				//刷新显示
				CRoundButton2* pButton2=(CRoundButton2*)GetDlgItem(uID);
				CString strTop;
				strTop.Format(_T("%.0f"),m_Items[index].bargain_num_cur);
				pButton2->SetStrTop(strTop);
				pButton2->Invalidate();
			}
			if (pOrderDlg!=NULL)
			{
				pOrderDlg->m_checkDlg[item->n_checkID-1].InsertCondiment(m_insertIdx,item,TRUE);
				POSITION pos=pOrderDlg->m_pOrderList->Find(pBelongItem);
				pOrderDlg->m_pOrderList->InsertAfter(pos,item);
				//pOrderDlg->m_pOrderList->AddTail(item);
			}
			else if (pComboDlg!=NULL)
			{
				pComboDlg->InsertCondiment(m_insertIdx,item);
			}
		}
		else
		{
			CString line;
			mEdit.GetWindowText(line);
			if(line.IsEmpty())
			{
				line.Format(_T("%s "),m_Items[index].item_name1);
				mEdit.SetWindowText(line);
			}
			else
			{
				mEdit.SetSel(line.GetLength(), line.GetLength());
				line.Format(_T("%s "),m_Items[index].item_name1);
				mEdit.ReplaceSel(line);
			}
			
		}
	}
	catch(...)
	{
		LOG4CPLUS_ERROR(log_pos,"Catch Exception GetLastError="<<GetLastError());
	}
}
/************************************************************************
* 函数介绍：点击了SLU
* 输入参数：
* 输出参数：
* 返回值  ：
************************************************************************/
void NotifyKitchenDlg::OnSluBnClicked(UINT uID)
{
	try{
		CRoundButton2* pButton2=(CRoundButton2*)GetDlgItem(uID);
		if (pButton2&&pButton2!=m_CheckedClassButton)
		{//切换选中分类
			if(m_CheckedClassButton)
			{
				m_CheckedClassButton->SetCheck(FALSE);
			}
			m_CheckedClassButton=pButton2;
			m_CheckedClassButton->SetCheck(TRUE);
		}
		if (GetCondimentItems(uID-IDC_SLU_BUTTON,m_Items)==FALSE)
			return;
		m_nCurrentPage=0;
		m_nPageCount=(int)ceil((float)m_Items.size()/m_nPageSize);
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

void NotifyKitchenDlg::OnBnClickedOk()
{
	mEdit.GetWindowText(m_strText);
	if (type>=1)
	{
		OnOK();
		return;
	}
	if (m_strText.IsEmpty())
	{
		POSMessageBox(IDS_EMPTYINPUT);
		return;
	}
	// 送厨打印
	int printclass=mPrintclassId[mComboBox.GetCurSel()];
	//对打印机创建打印任务
	try
	{
		CRecordset rs( &theDB );
		CString strSql;
		strSql.Format(_T("select * from print_devices,print_class_relation where print_devices.print_device_id=")
			_T("print_class_relation.print_device_id and print_class_id='%d' AND is_print_note=1 GROUP BY printer_name,com_port"),printclass);
		rs.Open( CRecordset::snapshot,strSql);
		if (rs.GetRecordCount()==0)
		{//没有找到打印机,全部发送
			strSql.Format(_T("select * from print_devices  WHERE is_print_note=1 GROUP BY printer_name,com_port"));
			rs.Close();
			rs.Open( CRecordset::snapshot,strSql);
		}
		while (!rs.IsEOF())
		{
			JSONVALUE printTask;
			GetPrinterInfo(rs,printTask);
			printTask[_T("template")]=TEMPLATE_MESSAGE;
			CString str2;
			theLang.LoadString(str2,IDS_MESSAGEHEAD);
			printTask[_T("head")]=str2;
			CTime time=CTime::GetCurrentTime();
			if(!m_strTtitle.IsEmpty())
			{
				printTask[_T("tbl_name")]=theApp.m_strTblName;
				printTask[_T("chk_num")]=theApp.m_nCheckNum;
				printTask[_T("gst_num")]=theApp.m_nGuests;
			}
			printTask[_T("emp_name")]=theApp.m_strUserName;
			printTask[_T("time")]=time.Format("%Y-%m-%d %H:%M");
			printTask[_T("message")]=m_strText;
			WritePrintTask(printTask,TRUE);
			rs.MoveNext();
		}
		rs.Close();
	}
	catch (CDBException* ex)
	{
		LOG4CPLUS_ERROR(log_pos,(LPCTSTR)ex->m_strError);
	}
	catch (CException* e)
	{
		TCHAR szError[300];
		e->GetErrorMessage(szError,300);
		LOG4CPLUS_ERROR(log_pos,(LPCTSTR)szError);
	}
	OnOK();
}

HBRUSH NotifyKitchenDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	if(nCtlColor==CTLCOLOR_STATIC)
	{
		pDC->SetTextColor(m_dTextColor);
		pDC->SetBkMode(TRANSPARENT);
		return (HBRUSH)::GetStockObject(NULL_BRUSH); //返回此画刷可以使静态文本透明
	}
	return hbr;
}
BOOL NotifyKitchenDlg::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message==WM_CHAR)
	{//限制输入的字符不包括特殊字符
		if (pMsg->wParam=='\\'||pMsg->wParam=='\''||pMsg->wParam=='\"')
		{
			return TRUE;
		}
	}
	return CDialog::PreTranslateMessage(pMsg);
}
/************************************************************************
* 函数介绍：添加前缀
* 输入参数：
* 输出参数：
* 返回值  ：
************************************************************************/
void NotifyKitchenDlg::OnBnClickedButtonPrefix(UINT uID)
{
	CString line,btStr;
	GetDlgItem(uID)->GetWindowText(btStr);
	mEdit.GetWindowText(line);
	int index=line.ReverseFind(' ');
	if (index!=-1)
	{//删除末尾
		line.Delete(index+1,line.GetLength()-index);
	}
	else
	{
		line.Format(_T(""));
	}
	line.Append(btStr);
	mEdit.SetWindowText(line);
}

void NotifyKitchenDlg::OnBnClickedButtonSoftkey()
{
	ShellExecute(GetSafeHwnd(), NULL, _T("SoftBoard.exe"), NULL, NULL,SW_NORMAL);
	mEdit.SetFocus();
}
void NotifyKitchenDlg::OnBnClickedCtrlHandInput()
{
	ShellExecute(GetSafeHwnd(), NULL, _T("HandInput.exe"), NULL, NULL,SW_NORMAL);
	mEdit.SetFocus();
}
