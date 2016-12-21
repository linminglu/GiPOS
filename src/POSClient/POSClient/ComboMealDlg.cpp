// omboMealDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "POSClient.h"
#include "ComboMealDlg.h"
#include "ModifyDlg.h"
#include "NumberInputDlg.h"
#include "NotifyKitchenDlg.h"


// ComboMealDlg 对话框

IMPLEMENT_DYNAMIC(ComboMealDlg, CDialog)

ComboMealDlg::ComboMealDlg(CWnd* pParent /*=NULL*/)
	: CDialog(ComboMealDlg::IDD, pParent)
{
	pParentItem=NULL;
	m_CheckedButton=NULL;
	m_nQuantity=1;
	m_nMode=0;
	m_nVoidNum=0;
	ITEM_COLUMNSIZE=3;
	ITEM_LINESIZE=7;
	m_bnotify=TRUE;
}

ComboMealDlg::~ComboMealDlg()
{
	for (std::vector<CButton*>::iterator iter = m_itemButtons.begin(); iter!= m_itemButtons.end();iter++)
	{
		CButton *b = (*iter);
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

void ComboMealDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_listEx);
	DDX_Control(pDX, IDC_STATIC_HINT, m_Hint);
	DDX_Control(pDX, IDC_BUTTON_ADDREQUEST, m_btCondiment);
	DDX_Control(pDX, IDC_BUTTON_NUMBER, m_btNum);
	DDX_Control(pDX, IDC_BUTTON_VOID, m_btVoid);
	DDX_Control(pDX, IDCANCEL, m_btCancel);
	DDX_Control(pDX, IDOK, m_btOK);
	//DDX_Control(pDX, IDC_EDIT2, m_searchEdit);
}


BEGIN_MESSAGE_MAP(ComboMealDlg, CDialog)
	ON_COMMAND_RANGE(IDC_SLU_BUTTON,IDC_SLU_BUTTON+999,OnSluBnClicked)//SLU
	ON_COMMAND_RANGE(IDC_DYNAMIC_CTRL,IDC_DYNAMIC_CTRL+MAX_ITEMS,OnItemBnClicked)
	ON_BN_CLICKED(IDC_BUTTON_LEFT, OnBnClickedButtonLeft)
	ON_BN_CLICKED(IDC_BUTTON_RIGHT, OnBnClickedButtonRight)
	ON_BN_CLICKED(IDC_BUTTON_UP, OnBnClickedButtonUp)
	ON_BN_CLICKED(IDC_BUTTON_DOWN, OnBnClickedButtonDown)
	ON_BN_CLICKED(IDC_BUTTON_NUMBER,OnBnClickedQuantity)
	ON_BN_CLICKED(IDC_BUTTON_VOID, OnBnClickedButtonVoid)
	ON_BN_CLICKED(IDC_BUTTON_ADDREQUEST,OnBnClickedAddRequest)
	ON_BN_CLICKED(IDOK, &ComboMealDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &ComboMealDlg::OnBnClickedCancel)
	ON_LBN_SELCHANGE(IDC_LIST1, &ComboMealDlg::OnLbnSelchangeList)
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
	//ON_EN_CHANGE(IDC_EDIT2, &ComboMealDlg::OnEnChangeEdit2)
END_MESSAGE_MAP()


// ComboMealDlg 消息处理程序
BOOL ComboMealDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	if (pParentItem==NULL)
		return TRUE;
	if (pParentItem->quantity<0)
		m_nQuantity=-1;
	else
		m_nQuantity=1;
	int TOPHEIGHT=50;
	m_listEx.m_nSubWidth[0]=50;
	m_listEx.m_nSubWidth[1]=180;
	m_listEx.m_nSubWidth[2]=70;
	SIZE buttonSize;
	buttonSize.cx=122;
	buttonSize.cy=58;
	CString str2;
	CImage imgB;
	if(imgB.Load(_T("Picture\\bg_course.png"))==S_OK)
	{
		m_x=imgB.GetWidth();
		m_y=imgB.GetHeight();
		m_bpBackgrd=imgB.Detach();
	}
	m_btOK.SetImage(_T("Picture\\bt_ok.png"));
	m_btCancel.SetImage(_T("Picture\\bt_cancel.png"));
	Gdiplus::Image* img1=Gdiplus::Image::FromFile(_T("Picture\\bt_orange_71.png"));
	if(img1)
	{
		Gdiplus::Image* img2=Gdiplus::Image::FromFile(_T("Picture\\bt_orange_71_.png"));
		m_btCondiment.SetImages(img1,img2);
		m_btNum.SetImages(img1->Clone(),img2->Clone());
		m_btVoid.SetImages(img1->Clone(),img2->Clone());
	}
	img1=Gdiplus::Image::FromFile(_T("Picture\\class\\item.png"));
	if(img1)
	{
		m_bpButtonItem[0]=img1;
	}
	m_bpButtonItem[1]=Gdiplus::Image::FromFile(_T("Picture\\class\\item_.png"));
	m_bpButtonSLU[0]=Gdiplus::Image::FromFile(_T("Picture\\class\\class.png"));
	m_bpButtonSLU[1]=Gdiplus::Image::FromFile(_T("Picture\\class\\class_.png"));
	m_bpSlodoutItem[0]=Gdiplus::Image::FromFile(_T("Picture\\class\\sold.png"));
	m_bpSlodoutItem[1]=Gdiplus::Image::FromFile(_T("Picture\\class\\sold_.png"));
	m_btCancel.SetTextColor(DEFALUT_TXT_COLOR);
	m_btOK.SetTextColor(DEFALUT_TXT_COLOR);
	m_btCondiment.SetTextColor(DEFALUT_TXT_COLOR);
	m_btNum.SetTextColor(DEFALUT_TXT_COLOR);
	m_btVoid.SetTextColor(DEFALUT_TXT_COLOR);
	if (!theLang.m_bDefaultLang)
	{
		SetFont(&theLang.m_dialogFont);
		CWnd* pCtrl=GetDlgItem(IDOK);
		theLang.TranslateDlgItem(pCtrl,IDS_COMPLETE);
		pCtrl=GetDlgItem(IDCANCEL);
		theLang.TranslateDlgItem(pCtrl,IDS_CANCEL);
		pCtrl=GetDlgItem(IDC_BUTTON_ADDREQUEST);
		theLang.TranslateDlgItem(pCtrl,IDS_CONDIMENT);
		pCtrl=GetDlgItem(IDC_BUTTON_NUMBER);
		theLang.TranslateDlgItem(pCtrl,IDS_NUM);
		pCtrl=GetDlgItem(IDC_BUTTON_VOID);
		theLang.TranslateDlgItem(pCtrl,IDS_VOID);
		theLang.LoadString(IDS_CHOOSECOMBOME,str2);
		SetWindowText(str2);
	}
	CWnd* pCtrl=GetDlgItem(IDC_STATIC1);
	pCtrl->SetWindowText(pParentItem->item_name);
	pCtrl=GetDlgItem(IDC_STATIC2);
	CString strName;
	strName.Format(theApp.m_decPlace+_T(" * %0.f"),pParentItem->item_price,pParentItem->quantity);
	pCtrl->SetWindowText(strName);

	CString strSQL;
	//创建分组按钮
	try{
		CRecordset rs( &theDB);
		strSQL.Format(_T("SELECT * FROM course_group WHERE menu_item_id=%d AND is_must=0 AND(slu_id>0 OR")
			_T(" EXISTS(SELECT 1 FROM course_detail WHERE course_group_id=course_group.course_group_id))"),pParentItem->item_id);
		if(rs.Open(CRecordset::snapshot,strSQL))
		{
			POINT topleft;
			topleft.x=324;
			topleft.y=TOPHEIGHT;
			int count=0;
			while (!rs.IsEOF())
			{
				count++;
				rs.MoveNext();
			}
			if (count==0)
			{//没有可选组，不需要弹出对话框
				CDialog::OnOK();
			}
			if(count<=ITEM_LINESIZE)
				m_uTotalPage=1;
			else
			{
				m_uTotalPage=ceil((count-2*(ITEM_LINESIZE-1))/(ITEM_LINESIZE-2.0))+2;
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

				topleft.y+=(buttonSize.cy+5)*(ITEM_LINESIZE-1);
				downBtn=new CRoundButton2;
				downBtn->Create(_T(""),WS_CHILD ,CRect(topleft,buttonSize),this,IDC_BUTTON_DOWN);
				upBtn->SetImage(_T("Picture\\class\\bt_down.png"));
				m_itemButtons.push_back(downBtn);
			}
			CDBVariant variant;
			CString strName;
			int pIndex=0;//在页内的索引
			int i=0;
			m_uCurPage=0;
			while(!rs.IsEOF())
			{
				rs.GetFieldValue(_T("course_group_id"), variant);
				CourseInfo course;
				course.id=variant.m_lVal;
				rs.GetFieldValue(_T("choose_num"), variant);
				course.total_select=abs(variant.m_iVal*pParentItem->quantity);
				course.can_select=course.total_select;
				rs.GetFieldValue(_T("slu_id"), variant);
				course.slu_id=variant.m_iVal;
				m_CourseGroups.push_back(course);
				topleft.y=pIndex*(buttonSize.cy)+TOPHEIGHT;
				CString strVal;
				rs.GetFieldValue(_T("course_group_name"),strVal);
				strName.Format(_T("%d-%s"),i+1,strVal);
				CRoundButton2* pBtn=new CRoundButton2;
				pBtn->Create(strName,WS_CHILD ,CRect(topleft,buttonSize),this,IDC_SLU_BUTTON+i);
				pBtn->SetImages(m_bpButtonSLU[0],m_bpButtonSLU[1],false);
				//pBtn->SetFont(GetFont());
				pBtn->SetTextColor(RGB(0,0,0),RGB(236,148,65));
				if (pIndex==0)
				{
					pBtn->SetCheck(TRUE);
					m_CheckedButton=pBtn;
				}
				m_itemButtons.push_back(pBtn);
				m_classButtons.push_back(pBtn);
				rs.MoveNext();
				//下一次的位置
				i++;
				pIndex++;
				if(m_uTotalPage>1)
				{//有翻页
					if (pIndex==ITEM_LINESIZE-1)
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

	LOGFONT m_tLogFont;
	memset(&m_tLogFont,0,sizeof(LOGFONT));
	m_tLogFont.lfHeight	= ScaleY(OrderDlg::ITEM_TEXTSIZE);
	wcscpy_s(m_tLogFont.lfFaceName, _T("Microsoft YaHei"));
	//创建菜品按钮
	m_nPageSize=ITEM_LINESIZE*ITEM_COLUMNSIZE-2;
	for(int i=0;i<ITEM_LINESIZE;i++)
	{
		POINT topleft;
		topleft.y=TOPHEIGHT+i*(buttonSize.cy+5);
		for(int j=0;j<ITEM_COLUMNSIZE;j++)
		{
			int count=i*ITEM_COLUMNSIZE+j;
			topleft.x=455+j*(buttonSize.cx+5);
			CRoundButton2* pBtn=new CRoundButton2;
			pBtn->SetFont(&m_tLogFont);
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
			pBtn->SetTextColor(RGB(255,255,255));
			m_itemButtons.push_back(pBtn);
		}
	}
	//显示已点的套餐(套餐换菜)
	if(m_nMode==0)
		AddFixedSetItem(pParentItem);
	else
	{
		POSITION pos;
		for(pos=m_subOrderList.GetHeadPosition();pos!=NULL;)
		{
			OrderDetail* order=m_subOrderList.GetNext(pos);
			CString strTmp;
			FormatString(order,strTmp);
			int index=m_listEx.AddString(strTmp);
			m_listEx.SetItemDataPtr(index,order);
			//初始化可选组
		}
	}
	m_Hint.GetWindowRect(&m_hintRect);    
	ScreenToClient(&m_hintRect);
	//显示第一组
	ShowCourse(0,_T(""));
	return TRUE;  // return TRUE unless you set the focus to a control
}
/************************************************************************
* 函数介绍：显示分类按钮的当前页
* 输入参数：
* 输出参数：
* 返回值  ：
************************************************************************/
void ComboMealDlg::ShowClassPage()
{
	try{
		for(int i=0;i<m_classButtons.size();i++)
		{
			m_classButtons[i]->ShowWindow(SW_HIDE);
		}
		for (int i=m_uCurPage*ITEM_LINESIZE;i<(m_uCurPage+1)*ITEM_LINESIZE&&i<m_classButtons.size();i++)
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
void ComboMealDlg::OnBnClickedButtonUp()
{
	if(m_uCurPage>0)
		m_uCurPage--;
	else
		return;
	ShowClassPage();
}
void ComboMealDlg::OnBnClickedButtonDown()
{
	if(m_uCurPage<m_uTotalPage-1)
		m_uCurPage++;
	else
		return;
	ShowClassPage();
}
/************************************************************************
* 函数介绍：显示当前页的菜品
* 输入参数：
* 输出参数：
* 返回值  ：
************************************************************************/
void ComboMealDlg::ShowCurrentPage()
{
	try{
		unsigned int index;
		for(int i=0;i<m_nPageSize;i++)
		{
			index=i+m_nCurrentPage*m_nPageSize;
			CRoundButton2* pButton2=(CRoundButton2*)GetDlgItem(IDC_DYNAMIC_CTRL+i);
			if(index<m_Items.size())
			{
				CString itemName;
				if (m_Items[index].type>ITEM_SLU&&macrosInt[_T("SHOW_ITEM_ID")]!=0)
				{
					itemName.Format(_T("%d-"),m_Items[index].item_number);
				}
				itemName.AppendFormat(_T("%s\n%s"),m_Items[index].item_name1,m_Items[index].item_name2);
				if (m_Items[index].type<=ITEM_SLU)//ITEM_CONDIMENT_GROUP
				{//SLU 颜色
					pButton2->SetImages(m_bpButtonSLU[0],m_bpButtonSLU[1],false);
				}
				else
					pButton2->SetImages(m_bpButtonItem[0],m_bpButtonItem[1],false);
				if (m_Items[index].bargain_stype!=0)
				{
					CString strtop;
					strtop.Format(_T("%.0f"),m_Items[index].bargain_num_cur);
					pButton2->SetStrTop(strtop);
					if (m_Items[index].bargain_num_cur<=0)
					{
						pButton2->SetImages(m_bpSlodoutItem[0],m_bpSlodoutItem[1],false);
					}
				}
				else
				{
					pButton2->SetStrTop(_T(""));
				}
				pButton2->SetWindowText(itemName);

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
* 函数介绍：翻页
* 输入参数：
* 输出参数：
* 返回值  ：
************************************************************************/
void ComboMealDlg::OnBnClickedButtonLeft()
{
	if(m_nCurrentPage>0)
		m_nCurrentPage--;
	else
		return;
	ShowCurrentPage();
}

void ComboMealDlg::OnBnClickedButtonRight()
{
	if(m_nCurrentPage<m_nPageCount-1)
		m_nCurrentPage++;
	else
		return;
	ShowCurrentPage();
}
/************************************************************************
* 函数介绍：点击了SLU
* 输入参数：
* 输出参数：
* 返回值  ：
************************************************************************/
void ComboMealDlg::OnSluBnClicked(UINT uID)
{
	try{
		int index=uID-IDC_SLU_BUTTON;
		ShowCourse(index,_T(""));
	}
	catch(...)
	{
		LOG4CPLUS_ERROR(log_pos,"Catch Exception GetLastError="<<GetLastError());
	}
}
void ComboMealDlg::OnItemBnClicked(UINT uID)
{
	if(m_nMode==0)
	{
		if(m_CourseGroups[m_nCurrentCourse].can_select<=0)
		{//该组已点完
			POSMessageBox(IDS_COMMEALGPOK);
			return;
		}
	}
	else
	{
		if (m_nVoidNum<=0)
		{
			POSMessageBox(IDS_COMMEALGPOK);
			return;
		}
	}
	UINT index=m_nCurrentPage*m_nPageSize+(uID-IDC_DYNAMIC_CTRL);
	if (index>=m_Items.size())
	{//越界
		LOG4CPLUS_ERROR(log_pos,"index=["<<index<<"] out of range. m_Items.size()="<<m_Items.size());
		return;
	}
	//提示沽清
	if (m_Items[index].bargain_stype&&m_Items[index].bargain_num_cur<=0)
	{
		CString msg,str2;
		theLang.LoadString(str2,IDS_SOLDOUTCTN);
		msg.Format(_T("[%s]%s"),m_Items[index].item_name1,str2);
		if(POSMessageBox(msg,MB_YESNO)!=IDOK)
			return;
	}
	//添加到新点菜品列表
	OrderDetail* item=new OrderDetail;
	memset(item,0,sizeof(OrderDetail));
	item->item_id=m_Items[index].item_number;
	item->n_discount_type=m_Items[index].n_discount_level;
	item->n_service_type=m_Items[index].n_service_level;
	item->n_eattype=pParentItem->n_eattype;
	item->n_checkID=pParentItem->n_checkID;
	item->n_seat_num=pParentItem->n_seat_num;
	if(pParentItem->quantity<0)
	{
		wcsncpy_s(item->authID,pParentItem->authID,9);
		wcsncpy_s(item->authUser,pParentItem->authID,9);
		int length=wcslen(pParentItem->return_reason);
		item->return_reason=new wchar_t[length+1];
		item->return_reason[length]=0;
		wcsncpy_s(item->return_reason,length+1,pParentItem->return_reason,length);
	}
	item->bargain_stype=m_Items[index].bargain_stype;
	if(m_nMode==0)
	{
		double diff=m_CourseGroups[m_nCurrentCourse].can_select-abs(m_nQuantity);
		if(diff<0)
		{//套餐内的菜不能超出套餐总数
			if(pParentItem->quantity>0)
				m_nQuantity=m_CourseGroups[m_nCurrentCourse].can_select;
			else
				m_nQuantity=-m_CourseGroups[m_nCurrentCourse].can_select;
		}
		m_CourseGroups[m_nCurrentCourse].can_select-=abs(m_nQuantity);
		UpdateHint();
		item->quantity=m_nQuantity;
		if (m_Items[index].default_num>0)
		{//套餐中设置了默认数量
			item->quantity=m_Items[index].default_num*m_nQuantity;
		}
		item->n_sortindex=m_nQuantity;//临时存储数量
	}
	else
	{
		double diff=m_nVoidNum-abs(m_nQuantity);
		if(diff<0)
		{//套餐内的菜不能超出套餐总数
			if(pParentItem->quantity>0)
				m_nQuantity=m_nVoidNum;
			else
				m_nQuantity=-m_nVoidNum;
		}
		m_nVoidNum-=abs(m_nQuantity);
		item->quantity=m_nQuantity;
		if (m_Items[index].default_num>0)
		{//套餐中设置了默认数量
			item->quantity=m_Items[index].default_num*m_nQuantity;
		}
	}
	item->belongto=pParentItem;
	item->n_belong_item=-pParentItem->item_id;
	item->item_price=0;
	item->sales_amount=m_Items[index].price*item->quantity;
	wcsncpy_s(item->unit,m_Items[index].unit,9);
	wcsncpy_s(item->item_name,m_Items[index].item_name1,63);
	wcsncpy_s(item->item_name2,m_Items[index].item_name2,31);
	if (m_Items[index].modify)
	{//选规格
		ModifyDlg dlg;
		dlg.m_item=item;
		if(dlg.DoModal()==IDCANCEL)
		{
			m_CourseGroups[m_nCurrentCourse].can_select+=abs(m_nQuantity);
			return;
		}
	}
	OrderDetail* pNew=AddOrderItem(item);
	if(pNew!=NULL)
	{//合并
		delete item;
		item=pNew;
	}
	//需要配料
	if (m_Items[index].condiment>0)
	{
		int selIndex=m_listEx.GetCount()-1;
		for(int i=m_listEx.GetCount()-1;i>=0;i--)
		{
			OrderDetail* pTmp=(OrderDetail*)m_listEx.GetItemDataPtr(i);
			if (pTmp==item)
			{
				selIndex=i;
				break;
			}
		}
		NotifyKitchenDlg dlg;
		dlg.m_nDefaultGroup=m_Items[index].condiment;
		theLang.LoadString(dlg.m_strTtitle,IDS_ADDREQUEST);
		dlg.type=1;
		dlg.pBelongItem=item;
		dlg.m_insertIdx=selIndex+1;
		dlg.pComboDlg=this;
		if(dlg.DoModal()==IDOK)
		{
			CString strTmp;
			wcsncpy_s(item->description,dlg.m_strText,99);
			FormatString(item,strTmp);
			m_listEx.DeleteString(selIndex);
			m_listEx.InsertString(selIndex,strTmp);
			m_listEx.SetItemDataPtr(selIndex,item);
		}
	}
	if(m_CourseGroups[m_nCurrentCourse].can_select<=0)
	{//跳到下一组
		m_nCurrentCourse++;
		if (m_nCurrentCourse<m_CourseGroups.size())
		{//还有其他套餐组
			ShowCourse(m_nCurrentCourse,_T(""));
		}
		else
		{//已点完套餐
			m_nCurrentCourse--;
		}
	}
	//恢复数量
	if (pParentItem->quantity<0)
		m_nQuantity=-1;
	else
		m_nQuantity=1;
}
/************************************************************************
* 函数介绍：显示套餐
* 输入参数：course -套餐组信息
* 输出参数：
* 返回值  ：
************************************************************************/
void ComboMealDlg::ShowCourse(int index,CString filter)
{
	try
	{
		if (index>=m_CourseGroups.size()||index<0)
			return;
		int uID=index+IDC_SLU_BUTTON;
		CRoundButton2* pButton2=(CRoundButton2*)GetDlgItem(uID);
		if (pButton2&&pButton2!=m_CheckedButton)
		{//切换选中分类
			if(m_CheckedButton)
			{
				m_CheckedButton->SetCheck(FALSE);
			}
			m_CheckedButton=pButton2;
			m_CheckedButton->SetCheck(TRUE);
		}
		m_nCurrentCourse=index;
		CourseInfo course=m_CourseGroups[index];
		m_Items.clear();
		CRecordset rs( &theDB);
		CString strSQL;
		//detail
		strSQL.Format(_T("SELECT * FROM(SELECT * FROM menu_item,course_detail WHERE menu_item.item_id=course_detail.menu_item_id AND course_group_id=%d")
			_T(" AND (item_id LIKE \'%s%%\'OR nlu LIKE \'%%%s%%\'))AS T LEFT JOIN bargain_price_item ON T.item_id=bargain_price_item.bargain_item_number;")
			,course.id,filter,filter);
		rs.Open( CRecordset::forwardOnly,strSQL);
		while(!rs.IsEOF())
		{
			MenuItem item=readCourseItem(rs);
			m_Items.push_back(item);
			rs.MoveNext();
		}
		rs.Close();
		//slu
		if(course.slu_id>0)
		{
			strSQL.Format(_T("SELECT * FROM(SELECT * FROM menu_item  WHERE slu_id>0 AND slu_id=%d")
				_T(" AND (item_id LIKE \'%s%%\'OR nlu LIKE \'%%%s%%\'))AS T LEFT JOIN bargain_price_item ON T.item_id=bargain_price_item.bargain_item_number;")
				,course.slu_id,filter,filter);
			rs.Open( CRecordset::forwardOnly,strSQL);
			while(!rs.IsEOF())
			{
				MenuItem item=readCourseItem(rs);
				m_Items.push_back(item);
				rs.MoveNext();
			}
			rs.Close();
		}

		m_nCurrentPage=0;
		m_nPageCount=(int)ceil((float)m_Items.size()/m_nPageSize);
		ShowCurrentPage();
		UpdateHint();
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
}
/************************************************************************
* 函数介绍：读取套餐中的菜品信息
* 输入参数：
* 输出参数：
* 返回值  ：
************************************************************************/
MenuItem ComboMealDlg::readCourseItem(CRecordset& rs)
{
	CDBVariant variant;
	MenuItem item={0};
	item.type=ITEM_ITEM;
	item.default_num=1;
	try{
		rs.GetFieldValue(_T("item_course_name"), item.item_name1);
		rs.GetFieldValue(_T("unit"), item.unit);
		variant.m_fltVal=1;
		rs.GetFieldValue(_T("num"), variant);
		item.default_num=variant.m_fltVal;
	}catch(...){
	}
	if (item.item_name1.IsEmpty())
	{
		rs.GetFieldValue(_T("item_name1"), item.item_name1);
	}
	rs.GetFieldValue(_T("item_name2"), item.item_name2);
	rs.GetFieldValue(_T("item_id"), variant);
	item.item_number=variant.m_lVal;
	try{
		rs.GetFieldValue(_T("price"), variant);
		item.price=variant.m_fltVal;
	}catch(...){
		rs.GetFieldValue(_T("price_1"), variant);
		item.price=variant.m_fltVal;
	}
	
	//多种规格？
	if(item.unit.IsEmpty())
	{
		variant.m_fltVal=0;
		rs.GetFieldValue(_T("price_2"), variant);
		if(variant.m_fltVal>0)
			item.modify=TRUE;
	}
	variant.m_lVal=0;
	rs.GetFieldValue(_T("required_condiment"), variant);
	item.condiment=variant.m_lVal;
	rs.GetFieldValue(_T("tax_group"), variant);
	item.tax_group=variant.m_lVal;
//	item.price=0;
	//价格为0，不需要打折服务费等信息
	//沽清内容
	variant.m_iVal=0;
	rs.GetFieldValue(_T("bargain_stype"), variant);
	if (variant.m_iVal==1||variant.m_iVal==3)
	{//沽清
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
	return item;
}
/************************************************************************
* 函数介绍：添加已点菜品到显示列表,只在当前组合并
* 输入参数：
* 输出参数：
* 返回值  ：
			成功:新插入返回NULL; 合并返回合并后的指针
************************************************************************/
OrderDetail* ComboMealDlg::AddOrderItem(OrderDetail* order)
{
	CString strTmp;
	FormatString(order,strTmp);
	if(macrosInt[_T("NO_AUTO_COMBINE")]==0&&m_nCurrentCourse>=0)
	//相同菜品自动合并数量
	if (order->item_id>0&&!order->weight_required&&order->n_saved==0
		&&order->b_hascondiment==FALSE&&order->n_belong_item<=0&&order->b_isfree==FALSE)
	{//自定菜、折扣、服务费，配料，称重产品，有配料的产品不合并
		for (int i=0;i<m_CourseGroups[m_nCurrentCourse].m_orders.size();i++)
		{
			OrderDetail* pTmpOder=m_CourseGroups[m_nCurrentCourse].m_orders[i];
			if (pTmpOder->n_saved==0&&!pTmpOder->b_hascondiment&&pTmpOder->item_id==order->item_id
				&&(pTmpOder->description[0]==0)//添加过做法的不合并
				&&(pTmpOder->item_price==order->item_price)&&(pTmpOder->n_eattype==order->n_eattype)
				&&(wcscmp(pTmpOder->unit,order->unit)==0)&&pTmpOder->b_isfree==FALSE
				&&(wcscmp(pTmpOder->item_name,order->item_name)==0))//相同规格
			{//找到一样的
				pTmpOder->quantity+=order->quantity;
				pTmpOder->n_sortindex+=order->n_sortindex;
				pTmpOder->total_price+=order->total_price;
				//找到在显示列表中的位置
				for(int j=0;j<m_listEx.GetCount();j++)
				{
					OrderDetail* pTmpOder2=(OrderDetail*)m_listEx.GetItemDataPtr(j);
					if(pTmpOder2==pTmpOder)
					{
						FormatString(pTmpOder,strTmp);
						m_listEx.DeleteString(j);
						m_listEx.InsertString(j,strTmp);
						m_listEx.SetItemDataPtr(j,pTmpOder);
						m_listEx.SetCaretIndex(j);
						return pTmpOder;
					}
				}
			}
		}
	}
	int index=m_listEx.AddString(strTmp);
	m_listEx.SetItemDataPtr(index,order);
	if(m_nMode==0)
		m_subOrderList.AddTail(order);
	else
		m_addOrderList.AddTail(order);
	if(m_nCurrentCourse>=0)
		m_CourseGroups[m_nCurrentCourse].m_orders.push_back(order);
	return NULL;
}
/************************************************************************
* 函数介绍：添加必须菜品
* 输入参数：
* 输出参数：
* 返回值  ：
************************************************************************/
void ComboMealDlg::AddFixedSetItem(OrderDetail* item)
{
	m_nCurrentCourse=-1;//不合并
	try
	{
		LOG4CPLUS_INFO(log_pos,"OrderDlg::OnAddSetItem course_id="<<item->item_id);
		OpenDatabase();
		CRecordset rs( &theDB);
		//1.查必选菜
		CString strSQL;
		CDBVariant variant;
		strSQL.Format(_T("SELECT * FROM menu_item WHERE slu_id IN(SELECT slu_id FROM course_group WHERE menu_item_id=%d AND is_must=1 AND slu_id>0)"),item->item_id);
		rs.Open(CRecordset::forwardOnly,strSQL);
		while(!rs.IsEOF())
		{
			OrderDetail* order=new OrderDetail;
			memset(order,0,sizeof(OrderDetail));
			order->n_eattype=item->n_eattype;
			order->n_checkID=item->n_checkID;
			order->item_price=0;
			order->total_price=0;
			order->belongto=pParentItem;
			order->n_belong_item=-pParentItem->item_id;
			if(pParentItem->quantity<0)
			{
				wcsncpy_s(item->authID,pParentItem->authID,9);
				wcsncpy_s(item->authUser,pParentItem->authID,9);
				int length=wcslen(pParentItem->return_reason);
				item->return_reason=new wchar_t[length+1];
				item->return_reason[length]=0;
				wcsncpy_s(item->return_reason,length+1,pParentItem->return_reason,length);
			}
			CString strname;
			rs.GetFieldValue(_T("item_name1"), strname);
			wcsncpy_s(order->item_name,strname,63);
			rs.GetFieldValue(_T("item_name2"), strname);
			wcsncpy_s(order->item_name2,strname,31);
			rs.GetFieldValue(_T("item_id"), variant);
			order->item_id=variant.m_lVal;
			rs.GetFieldValue(_T("item_type"), variant);
			if (variant.m_iVal==ITEM_TEXT)
			{
				order->b_notprint=TRUE;
				order->quantity=1;
			}
			else
			{
				rs.GetFieldValue(_T("unit_1"), strname);
				wcsncpy_s(order->unit,strname,9);
				order->quantity=pParentItem->quantity;
				try{
					rs.GetFieldValue(_T("price"), variant);
				}catch(...){
					rs.GetFieldValue(_T("price_1"), variant);
				}
				order->sales_amount=variant.m_fltVal*pParentItem->quantity;
			}
			AddOrderItem(order);
			rs.MoveNext();
		}
		rs.Close();

		strSQL.Format(_T("SELECT * FROM menu_item,course_detail WHERE menu_item.item_id=course_detail.menu_item_id AND course_group_id IN")
			_T(" (SELECT course_group_id FROM course_group WHERE menu_item_id=%d AND is_must=1)"),item->item_id);
		rs.Open( CRecordset::forwardOnly,strSQL);
		while(!rs.IsEOF())
		{
			OrderDetail* order=new OrderDetail;
			memset(order,0,sizeof(OrderDetail));
			order->n_eattype=item->n_eattype;
			order->n_checkID=item->n_checkID;
			order->item_price=0;
			order->total_price=0;
			order->belongto=pParentItem;
			order->n_belong_item=-pParentItem->item_id;
			CString strname;
			rs.GetFieldValue(_T("item_course_name"), strname);
			wcsncpy_s(order->item_name,strname,63);
			rs.GetFieldValue(_T("item_name2"), strname);
			wcsncpy_s(order->item_name2,strname,31);
			rs.GetFieldValue(_T("menu_item_id"), variant);
			order->item_id=variant.m_lVal;
			rs.GetFieldValue(_T("item_type"), variant);
			if (variant.m_iVal==ITEM_TEXT)
			{
				order->b_notprint=TRUE;
				order->quantity=1;
			}
			else
			{
				rs.GetFieldValue(_T("unit"), strname);
				wcsncpy_s(order->unit,strname,9);
				//数量
				variant.m_fltVal=0;
				rs.GetFieldValue(_T("num"), variant);
				order->quantity=variant.m_fltVal*pParentItem->quantity;
				rs.GetFieldValue(_T("price"), variant);
				order->sales_amount=variant.m_fltVal*order->quantity;
			}
			AddOrderItem(order);
			rs.MoveNext();
		}
		rs.Close();
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
}
void ComboMealDlg::UpdateHint()
{
	CString str1,str2;
	if (m_nMode==1)
	{//套餐换菜
		theLang.LoadString(str2,IDS_SWAPCOURSE2);
		str1.Format(str2,m_nVoidNum);
	}
	else
	{
		theLang.LoadString(str2,IDS_COMBOMEALNUM);
		str1.Format(str2,m_nCurrentCourse+1,m_CourseGroups[m_nCurrentCourse].can_select);
	}
	m_Hint.SetWindowText(str1);
	InvalidateRect(m_hintRect);
}
/************************************************************************
* 函数介绍：菜品数量
* 输入参数：
* 输出参数：
* 返回值  ：
************************************************************************/
void ComboMealDlg::OnBnClickedQuantity()
{
	try{
		LOG4CPLUS_INFO(log_pos,"ComboMealDlg::OnBnClickedQuantity Begin");
		if (m_listEx.GetSelCount()==0)
		{//未选中，数量下次生效
			NumberInputDlg dlg;
			theLang.LoadString(dlg.m_strHint,IDS_INPUTQUANTITY);
			if(dlg.DoModal()==IDOK)
			{
				int num=_wtoi(dlg.m_strNum);
				if (num<=0||num>macrosInt[_T("MAX_ITEM_QUANTITY")])
				{
					POSMessageBox(IDS_NUMERROR);
					return;
				}
				m_nQuantity=num;
				if (pParentItem->quantity<0)
				{
					m_nQuantity=m_nQuantity*(-1);
				}
			}
			return;
		}
		//套餐换菜模式下不能修改选中菜
		if (m_nMode==1)
			return;
		BOOL bFirst=TRUE;
		double num=0,usednum;
		for(int  i=0;i<m_listEx.GetCount();i++)
		{
			if(m_listEx.GetSel(i))
			{
				OrderDetail* item=(OrderDetail*)m_listEx.GetItemDataPtr(i);
				if (item==NULL||item->item_id<=0)
					continue;
				if(item->n_belong_item>0&&item->item_price==0)
				{//没有价格的配料不用修改
					m_listEx.SetSel(i,FALSE);
					continue;
				}
				if (item->n_saved==0)
				{//未送厨
					if(bFirst)
					{//第一次，弹出数量对话框
						NumberInputDlg dlg;
						theLang.LoadString(dlg.m_strHint,IDS_INPUTQUANTITY);
						if(dlg.DoModal()==IDCANCEL)
							return;
						num=_wtof(dlg.m_strNum);
						if (num<=0||num>macrosInt[_T("MAX_ITEM_QUANTITY")])
						{
							POSMessageBox(IDS_NUMERROR);
							return;
						}
						bFirst=FALSE;
					}
					CString strSQL;
					usednum=num;
					if (item->quantity<0)
					{//退菜不修改沽清值
						usednum*=-1;
					}
					int defaulttimes=abs(item->quantity/item->n_sortindex);
					int diff=abs(usednum/defaulttimes)-abs(item->n_sortindex);
					//更新套餐组已点数
					for (int j=0;j<m_CourseGroups.size();j++)
					{
						std::vector<OrderDetail*>::iterator iter=
						find(m_CourseGroups[j].m_orders.begin(),m_CourseGroups[j].m_orders.end(),item);
						if (iter!=m_CourseGroups[j].m_orders.end())
						{
							if(m_CourseGroups[j].can_select-diff<0)
							{
								POSMessageBox(IDS_NUMERROR);
								return;
							}
							m_CourseGroups[j].can_select-=diff;
							if(j==m_nCurrentCourse)
							{
								UpdateHint();
							}
							break;
						}
					}
					item->quantity=usednum;
					ComputeTotalPrice(item);
					item->n_sortindex+=diff;
					//刷新显示
					CString strLine;
					FormatString(item,strLine);
					m_listEx.DeleteString(i);
					m_listEx.InsertString(i,strLine);
					m_listEx.SetItemDataPtr(i,item);
				}
				else
				{
					POSMessageBox(IDS_ALREADYSEND);
					m_listEx.SetSel(i,FALSE);
					return;
				}
			}
		}
	}
	catch(...)
	{
		LOG4CPLUS_ERROR(log_pos,"Catch Exception GetLastError="<<GetLastError());
	}

	LOG4CPLUS_INFO(log_pos,"ComboMealDlg::OnBnClickedQuantity m_nQuantity="<<m_nQuantity);
}

void ComboMealDlg::OnBnClickedButtonVoid()
{
	try
	{
		CString userid;
		WCHAR username[10];
		BOOL flag=TRUE;
		for(int  i=m_listEx.GetCount()-1;i>=0;i--)
		{
			if(m_listEx.GetSel(i))
			{
				OrderDetail* item=(OrderDetail*)m_listEx.GetItemDataPtr(i);
				if (item->item_id==ITEM_ID_SENDINFO)
				{//提示字符串不能删除
					continue;
				}
				double voidQuantity=item->quantity;
				m_listEx.DeleteString(i);
				if(m_nMode==1)
				{//套餐换菜
					if(item->n_belong_item<0)
						m_nVoidNum+=item->quantity;
					POSITION pos=m_addOrderList.Find(item);
					if (pos!=NULL)
					{//是新点的菜品
						m_addOrderList.RemoveAt(pos);
						delete item;
					}
					else
					{//插入退菜
						m_voidOrderList.AddTail(item);
					}
				}
				else
				{
					POSITION pos=m_subOrderList.Find(item);
					m_subOrderList.RemoveAt(pos);
					//找到所属套餐组
					for (int j=0;j<m_CourseGroups.size();j++)
					{
						std::vector<OrderDetail*>::iterator iter=
							find(m_CourseGroups[j].m_orders.begin(),m_CourseGroups[j].m_orders.end(),item);
						if (iter!=m_CourseGroups[j].m_orders.end())
						{
							m_CourseGroups[j].can_select+=abs((*iter)->n_sortindex);
							if(j==m_nCurrentCourse)
							{
								UpdateHint();
							}
							m_CourseGroups[j].m_orders.erase(iter);
							break;
						}
					}
					delete item;
				}
				
			}
		}
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
/************************************************************************
* 函数介绍：格式化菜品的显示
* 输入参数：
* 输出参数：
* 返回值  ：
************************************************************************/
void ComboMealDlg::FormatString(OrderDetail* pOrder,CString& strLine)
{
	CString name;
	name=pOrder->item_name;
	if (pOrder->n_belong_item>0)
	{//配料,默认不需要显示数量
		CString strNum,strPrice;
		if (pOrder->quantity==1)
			strNum=_T("||");
		else
			strNum.Format(_T("|%g|"),pOrder->quantity);
		CString decPlace;
		decPlace.Format(_T("|%%.%df|"),theApp.DECIMAL_PLACES);
		if(fabs(pOrder->total_price-0)>0.001)
			strPrice.Format(decPlace,pOrder->total_price);
		else
			strPrice=_T("||");
		if (pOrder->unit[0]!=0)
			name.AppendFormat(_T("(%s)"),pOrder->unit);
		strLine.Format(_T("%s %s%s"),strNum,name,strPrice);
	}
	else
	{
		if (pOrder->description[0]!=0)
		{
			name.AppendFormat(_T("\n%s"),pOrder->description);
		}
		strLine.Format(_T("|%g%s|%s||"),pOrder->quantity,pOrder->unit,name);
	}
}
/************************************************************************
* 函数介绍：插入配料。该函数可不按点菜顺序插入配料
* 输入参数：
* 输出参数：
* 返回值  ：
************************************************************************/
void ComboMealDlg::InsertCondiment(int index,OrderDetail* order)
{
	CString strLine;
	FormatString(order,strLine);
	OrderDetail* pParent=(OrderDetail*)m_listEx.GetItemDataPtr(index-1);
	int ind=m_listEx.InsertString(index,strLine);
	m_listEx.SetItemDataPtr(ind,order);
	if(m_nMode==0)
	{
		POSITION pos=m_subOrderList.Find(pParent);
		m_subOrderList.InsertAfter(pos,order);
	}
	else
	{
		m_addOrderList.AddTail(order);
	}
}
void ComboMealDlg::OnBnClickedAddRequest()
{
	if (m_listEx.GetSelCount()==0)
		return;
	
	int selCount=m_listEx.GetSelCount();
	OrderDetail* pTmpOrder=NULL;
	CString desc;
	int selIndex=-1;
	BOOL bSetAll=TRUE,bFirst=TRUE;
	
	for(int  i=0;i<m_listEx.GetCount();i++)
	{
		if(m_listEx.GetSel(i))
		{
			OrderDetail* item=(OrderDetail*)m_listEx.GetItemDataPtr(i);
			if (item==NULL||item->item_id<0||item->n_saved==2)
				return;
			if (item->n_belong_item>0)
			{//调味品
				selCount--;
				continue;
			}
			if(bFirst)
			{//第一个选中
				bFirst=FALSE;
				desc.Format(_T("%s"),item->description);
				pTmpOrder=item;
				selIndex=i;
			}
			else if(desc.Compare(item->description)!=0)
			{//内容不相同
				desc.Empty();
				bSetAll=FALSE;
				break;
			}
		}
	}
	if (pTmpOrder==NULL)
		return;//选中的不符合修改条件
	NotifyKitchenDlg dlg;
	if(!bSetAll)
		dlg.m_nShowHint=1;
	theLang.LoadString(dlg.m_strTtitle,IDS_ADDREQUEST);
	dlg.m_strText=desc;
	dlg.type=1;
	dlg.pBelongItem=pTmpOrder;
	dlg.m_insertIdx=selIndex+1;
	dlg.pComboDlg=this;
	if(dlg.DoModal()==IDCANCEL)
		return;
	CString strSQL;
	for(int  i=0;i<m_listEx.GetCount();i++)
	{
		if(m_listEx.GetSel(i))
		{
			OrderDetail* item=(OrderDetail*)m_listEx.GetItemDataPtr(i);
			if (item==NULL||item->item_id<0||item->n_saved==2)
				continue;
			if (item->n_belong_item>0)
			{
				m_listEx.SetSel(i,FALSE);
				continue;
			}
			if (bSetAll)
			{
				wcsncpy_s(item->description,dlg.m_strText,99);
			}
			else
			{
				if(dlg.m_strText.GetLength()!=0)
					wcscat_s(item->description,100,dlg.m_strText);
				else
					item->description[0]=0;
			}
			CString strLine;
			FormatString(item,strLine);
			m_listEx.DeleteString(i);
			m_listEx.InsertString(i,strLine);
			m_listEx.SetItemDataPtr(i,item);
			if(m_nMode==1)//标记修改
				item->n_sortindex=1;
		}
	}
}
void ComboMealDlg::OnBnClickedOk()
{
	if(m_nMode==0)
	{//检查套餐组是否已点完
		for (int j=0;j<m_CourseGroups.size();j++)
		{
			if (m_CourseGroups[j].can_select>0)
			{
				CString str1,str2;
				theLang.LoadString(IDS_COMMEALHINT,str2);
				str1.Format(str2,j+1);
				if(POSMessageBox(str1,MB_YESNO)!=IDOK)
					return;
			}
		}
	}
	OnOK();
}

void ComboMealDlg::OnBnClickedCancel()
{
	if (m_nMode==1)
	{
		OnCancel();
		return;
	}
	//删除点菜品
	while(!m_subOrderList.IsEmpty())
	{
		OrderDetail* item=m_subOrderList.GetHead();
		OrderDetail* item2=m_subOrderList.GetTail();
		m_subOrderList.RemoveHead();
		delete item;
	}
	OnCancel();
}
void ComboMealDlg::OnLbnSelchangeList()
{
	BOOL bSetSel=FALSE;
	for (int i=0;i<m_listEx.GetCount();i++)
	{
		OrderDetail* pTmpOder=(OrderDetail*)m_listEx.GetItemDataPtr(i);
		if (m_listEx.GetSel(i))
		{
			if (pTmpOder->b_hascondiment)
			{//如果有配料，自动选中配料
				bSetSel=TRUE;
			}
		}
		else if (bSetSel==TRUE)
		{
			if (pTmpOder->n_belong_item>0)
			{//选中配料
				m_listEx.SetSel(i);
			}
			else//到达下一个菜品
				bSetSel=FALSE;	
		}
	}
}

HBRUSH ComboMealDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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
BOOL ComboMealDlg::OnEraseBkgnd(CDC* pDC)
{
	if (m_bpBackgrd==NULL)
	{
		return FALSE;
	}
	CRect rect;
	GetClientRect(&rect);
	CDC MemDc;
	MemDc.CreateCompatibleDC(pDC);
	HGDIOBJ hOldBmp = MemDc.SelectObject(m_bpBackgrd);
	pDC->SetStretchBltMode(HALFTONE);
	pDC->StretchBlt(0,0,rect.Width(),rect.Height(),&MemDc,0,0,m_x,m_y,SRCCOPY);
	//pDC->BitBlt(0,0,rect.Width(),rect.Height(),&MemDc,0,0,SRCCOPY);
	MemDc.SelectObject(hOldBmp);
	return TRUE;
}
