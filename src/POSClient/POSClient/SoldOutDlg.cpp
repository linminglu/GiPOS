// SoldOutDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "POSClient.h"
#include "SoldOutDlg.h"
#include "SoldoutItemDlg.h"


// SoldOutDlg 对话框

IMPLEMENT_DYNAMIC(SoldOutDlg, CPosPage2)

SoldOutDlg::SoldOutDlg(CWnd* pParent /*=NULL*/)
	: CPosPage2(SoldOutDlg::IDD)
{

}

SoldOutDlg::~SoldOutDlg()
{
	for (CPbuttonIter iter = m_itemButtons.begin(); iter!= m_itemButtons.end();iter++)
	{
		CRoundButton2 *b = (*iter);
		b->DestroyWindow();
		delete b;
	}
	m_itemButtons.clear();

	delete m_bpButtonLf[0];
	delete m_bpButtonLf[1];
	delete m_bpButtonRt[0];
	delete m_bpButtonRt[1];
}

void SoldOutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, mComboBox);
	DDX_Control(pDX, IDOK, m_btOK);
	DDX_Control(pDX, IDC_BUTTON_CLEAR, m_btClear);
	DDX_Control(pDX, IDC_BUTTON_CLEAN, m_btClean);
	DDX_Control(pDX, IDC_BUTTON_PRE, m_btPrepage);
	DDX_Control(pDX, IDC_EDIT1, mEdit);
}


BEGIN_MESSAGE_MAP(SoldOutDlg, CDialog)
	ON_WM_SIZE()
	ON_COMMAND_RANGE(IDC_DYNAMIC_CTRL,IDC_DYNAMIC_CTRL+MAX_ITEMS,OnLItemBnClicked)
	ON_COMMAND_RANGE(IDC_CLASS_BUTTON,IDC_CLASS_BUTTON+50,OnRItemBnClicked)
	ON_BN_CLICKED(IDC_BUTTON_LEFT, &OnBnClickedButtonLeft)
	ON_BN_CLICKED(IDC_BUTTON_RIGHT, &OnBnClickedButtonRight)
	ON_BN_CLICKED(IDC_BUTTON_UP, &OnBnClickedButtonLeftR)
	ON_BN_CLICKED(IDC_BUTTON_DOWN, &OnBnClickedButtonRightR)
	ON_CBN_SELCHANGE(IDC_COMBO1, &SoldOutDlg::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, &SoldOutDlg::OnBnClickedButtonClear)
	ON_BN_CLICKED(IDOK, &SoldOutDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_PRE, &SoldOutDlg::OnBnClickedOk)
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON_CLEAN, &SoldOutDlg::OnBnClickedButtonClean)
	ON_EN_CHANGE(IDC_EDIT1, &SoldOutDlg::OnEnChangeEdit1)
END_MESSAGE_MAP()


// SoldOutDlg 消息处理程序

BOOL SoldOutDlg::OnInitDialog()
{
	CPosPage2::InitDialog(_T("Picture\\bg_soldout.png"));
	mEdit.SetLimitText(10);
	m_btOK.SetImage(_T("Picture\\bt_ok.png"));
	m_btClear.SetImage(_T("Picture\\bt_cancel.png"));
	m_btClean.SetImage(_T("Picture\\bt_orange_71.png"));
	m_btPrepage.SetImage(_T("Picture\\class\\prepage.png"));
	COLORREF tColor=RGB(255,255,255);
	m_btOK.SetTextColor(tColor);
	m_btClean.SetTextColor(tColor);
	m_btClear.SetTextColor(tColor);
	m_btPrepage.SetTextColor(tColor);
	if (!theLang.m_bDefaultLang)
	{
		CWnd* pCtrl=GetDlgItem(IDC_BUTTON_PRE);
		theLang.TranslateDlgItem(pCtrl,IDS_PREPAGE);
		pCtrl=GetDlgItem(IDC_BUTTON_CLEAN);
		theLang.TranslateDlgItem(pCtrl,IDS_CLEAR);
		pCtrl=GetDlgItem(IDOK);
		theLang.TranslateDlgItem(pCtrl,IDS_OK);
		pCtrl=GetDlgItem(IDC_BUTTON_CLEAR);
		theLang.TranslateDlgItem(pCtrl,IDS_CLEARSOLDOUT);
		pCtrl=GetDlgItem(IDC_STATIC2);
		theLang.TranslateDlgItem(pCtrl,IDS_SOLDDETAIL);
		pCtrl=GetDlgItem(IDC_STATIC1);
		theLang.TranslateDlgItem(pCtrl,IDS_ITEMDETAIL);
	}
 	CRect rect;
	try
	{
		OpenDatabase();
		CRecordset rs( &theDB);
		CString strSQL;
		strSQL.Format(_T("SELECT * FROM descriptors_menu_item_slu;"));
		rs.Open(CRecordset::forwardOnly,strSQL);
		while (!rs.IsEOF())
		{
			CDBVariant variant;
			CString class_name;
			rs.GetFieldValue(_T("dmi_slu_id"),variant);
			mSluId.push_back(variant.m_lVal);
			rs.GetFieldValue(_T("dmi_slu_name"),class_name);
			mComboBox.AddString(class_name);
			rs.MoveNext();
		}
		rs.Close();
		mComboBox.SetCurSel(0);
	}
	catch(CDBException* e)
	{
		LOG4CPLUS_ERROR(log_pos,(LPCTSTR)e->m_strError);
		AfxMessageBox(e->m_strError,MB_ICONEXCLAMATION);
		e->Delete();
	}
	SIZE buttonSize;
	buttonSize.cx=122;
	buttonSize.cy=58;
	m_bpButtonLf[0]=Gdiplus::Image::FromFile(_T("Picture\\class\\item.png"));
	m_bpButtonLf[1]=Gdiplus::Image::FromFile(_T("Picture\\class\\item_.png"));
	m_bpButtonRt[0]=Gdiplus::Image::FromFile(_T("Picture\\class\\sold.png"));
	m_bpButtonRt[1]=Gdiplus::Image::FromFile(_T("Picture\\class\\sold_.png"));
	
	LOGFONT m_tLogFont;
	memset(&m_tLogFont,0,sizeof(LOGFONT));
	m_tLogFont.lfHeight			= ScaleY(OrderDlg::ITEM_TEXTSIZE);
	wcscpy_s(m_tLogFont.lfFaceName, _T("Microsoft YaHei"));
//创建左侧菜品按钮
	rect=  CRect(30,150,400*CreatButton::m_nFullWidth/1024,650*CreatButton::m_nFullHeight/768);
	int ITEM_LINESIZE=8;
	int ITEM_COLUMNSIZE=3;
	m_nPageSizel=ITEM_LINESIZE*ITEM_COLUMNSIZE-2;
	buttonSize.cx=(rect.right-rect.left)/ITEM_COLUMNSIZE-8;
	buttonSize.cy=(rect.bottom-rect.top)/ITEM_LINESIZE-8;
	for(int i=0;i<ITEM_LINESIZE;i++)
	{
		POINT topleft;
		topleft.y=rect.top+i*(buttonSize.cy+8);
		CImage img;
		CString str2;
		for(int j=0;j<ITEM_COLUMNSIZE;j++)
		{
			int count=i*ITEM_COLUMNSIZE+j;
			topleft.x=rect.left+j*(buttonSize.cx+8);
			CRoundButton2* pBtn=new CRoundButton2;
			pBtn->SetFont(&m_tLogFont);
			//最后2个按钮为翻页按钮
			if (count==m_nPageSizel)
			{//前一页
				pBtn->Create(_T(""),WS_CHILD ,CRect(topleft,buttonSize),this,IDC_BUTTON_LEFT);
				pBtn->SetImage(_T("Picture\\bt_left.png"));
			}
			else if (count==m_nPageSizel+1)
			{//后一页
				pBtn->Create(_T(""),WS_CHILD ,CRect(topleft,buttonSize),this,IDC_BUTTON_RIGHT);
				pBtn->SetImage(_T("Picture\\bt_right.png"));
			}
			else
			{
				pBtn->Create(_T(""),WS_CHILD ,CRect(topleft,buttonSize),this,IDC_DYNAMIC_CTRL+count);
				pBtn->SetImages(m_bpButtonLf[0],m_bpButtonLf[1],false);
			}
			pBtn->SetTextColor(RGB(255,255,255));
			m_itemButtons.push_back(pBtn);
		}
	}
//创建右侧菜品按钮
	rect=  CRect(480*CreatButton::m_nFullWidth/1024,80,1010*CreatButton::m_nFullWidth/1024,660*CreatButton::m_nFullHeight/768);
	ITEM_LINESIZE=9;
	ITEM_COLUMNSIZE=4;
	m_nPageSizeR=ITEM_LINESIZE*ITEM_COLUMNSIZE-2;
	buttonSize.cx=(rect.right-rect.left)/ITEM_COLUMNSIZE-8;
	buttonSize.cy=(rect.bottom-rect.top)/ITEM_LINESIZE-8;
	for(int i=0;i<ITEM_LINESIZE;i++)
	{
		POINT topleft;
		topleft.y=rect.top+i*(buttonSize.cy+8);
		CBitmap bmp;
		CString str2;
		for(int j=0;j<ITEM_COLUMNSIZE;j++)
		{
			int count=i*ITEM_COLUMNSIZE+j;
			topleft.x=rect.left+j*(buttonSize.cx+8);
			CRoundButton2* pBtn=new CRoundButton2;
			pBtn->SetFont(&m_tLogFont);
			//最后2个按钮为翻页按钮
			if (count==m_nPageSizeR)
			{//前一页
				pBtn->Create(_T(""),WS_CHILD ,CRect(topleft,buttonSize),this,IDC_BUTTON_UP);
				pBtn->SetImage(_T("Picture\\bt_left.png"));
			}
			else if (count==m_nPageSizeR+1)
			{//后一页
				pBtn->Create(_T(""),WS_CHILD ,CRect(topleft,buttonSize),this,IDC_BUTTON_DOWN);
				pBtn->SetImage(_T("Picture\\bt_right.png"));
			}
			else
			{
				pBtn->Create(_T(""),WS_CHILD ,CRect(topleft,buttonSize),this,IDC_CLASS_BUTTON+count);
				pBtn->SetImages(m_bpButtonRt[0],m_bpButtonRt[1],false);
			}
			pBtn->SetTextColor(RGB(255,255,255));
			m_itemButtons.push_back(pBtn);
		}
	}
	OnCbnSelchangeCombo1();
//查询已有的估清菜品
	UpdateBargainItem(FALSE);
	return FALSE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void SoldOutDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	CWnd* pCtrl=GetDlgItem(IDOK);
	if (pCtrl)
	{
		pCtrl->MoveWindow(cx*0.7-120,cy-90,120,60);
	}
	pCtrl=GetDlgItem(IDC_BUTTON_CLEAR);
	if (pCtrl)
	{
		pCtrl->MoveWindow(cx*0.7+20,cy-90,120,60);
	}
	pCtrl=GetDlgItem(IDC_EDIT1);
	if (pCtrl)
	{
		pCtrl->MoveWindow(30,cy-90,240,30);
	}
	pCtrl=GetDlgItem(IDC_BUTTON_CLEAN);
	if (pCtrl)
	{
		pCtrl->MoveWindow(280,cy-90,80,48);
	}
	pCtrl=GetDlgItem(IDC_BUTTON_PRE);
	if (pCtrl)
	{
		pCtrl->MoveWindow(cx-136,12,120,60);
	}
}
void SoldOutDlg::UpdateBargainItem(BOOL bEnd)
{
	try{
		m_ItemsR.clear();
		CRecordset rs( &theDB);
		CString strSQL;//AND condiment_membership IS NULL
		strSQL.Format(_T("SELECT bargain_price_item.*,item_name1,item_name2 FROM bargain_price_item,menu_item WHERE bargain_item_number=item_id and bargain_stype>0;"));
		rs.Open( CRecordset::forwardOnly,strSQL);
		while(!rs.IsEOF())
		{
			MenuItem item={0};
			CDBVariant variant;
			rs.GetFieldValue(_T("item_name1"), item.item_name1);
			rs.GetFieldValue(_T("item_name2"), item.item_name2);
			rs.GetFieldValue(_T("bargain_item_number"), variant);
			item.item_number=variant.m_lVal;
			//估清内容
			variant.m_iVal=0;
			rs.GetFieldValue(_T("bargain_stype"), variant);
			if (variant.m_iVal==1||variant.m_iVal==3)
			{//估清
				item.bargain_stype=variant.m_iVal;
				item.bargain_num_cur=0;
			}
			else if (variant.m_iVal==2)
			{//限量销售
				item.bargain_stype=2;
				variant.m_fltVal=0;
				rs.GetFieldValue(_T("bargain_num_cur"), variant);
				item.bargain_num_cur=variant.m_fltVal;
			}
			m_ItemsR.push_back(item);
			rs.MoveNext();
		}
		rs.Close();
		//刷新左侧的状态
		for(int j=0;j<m_ItemsL.size();j++)
		{
			BOOL bFind=FALSE;
			int uID=j+IDC_DYNAMIC_CTRL;
			CRoundButton2* pButton2=(CRoundButton2*)GetDlgItem(uID);
			if(pButton2==NULL)
				continue;//左侧没有该按钮
			for(int i=0;i<m_ItemsR.size();i++)
			{
				if (m_ItemsL[j].item_number==m_ItemsR[i].item_number)
				{//内存中有
					m_ItemsL[j].bargain_stype=m_ItemsR[i].item_number;
					m_ItemsL[j].bargain_num_cur=m_ItemsR[i].bargain_num_cur;
					
					if (m_ItemsL[j].bargain_stype!=0)
					{
						CString strTop;
						strTop.Format(_T("%.0f"),m_ItemsL[j].bargain_num_cur);
						pButton2->SetStrTop(strTop);
						pButton2->SetImages(m_bpButtonRt[0],m_bpButtonRt[1],false);
					}
					else
					{
						pButton2->SetStrTop(_T(""));
						pButton2->SetImages(m_bpButtonLf[0],m_bpButtonLf[1],false);
					}
					bFind=TRUE;
					break;
				}
			}
			if (!bFind)
			{
				pButton2->SetStrTop(_T(""));
				pButton2->SetImages(m_bpButtonLf[0],m_bpButtonLf[1],false);
			}
		}

		m_nPageCountR=(int)ceil((float)m_ItemsR.size()/m_nPageSizeR);
		if(bEnd)
			m_nCurrentPageR=m_nPageCountR-1;//默认显示尾页
		else
			m_nCurrentPageR=0;
		ShowCurrentPageR();
	}
	catch(CDBException* e)
	{
		LOG4CPLUS_ERROR(log_pos,(LPCTSTR)e->m_strError);
		e->Delete();
	}
}
/************************************************************************
* 函数介绍：显示当前页的菜品
* 输入参数：
* 输出参数：
* 返回值  ：
************************************************************************/
void SoldOutDlg::ShowCurrentPage()
{
	try{
		unsigned int index;
		for(int i=0;i<m_nPageSizel;i++)
		{
			index=i+m_nCurrentPagel*m_nPageSizel;
			CRoundButton2* pButton2=(CRoundButton2*)GetDlgItem(IDC_DYNAMIC_CTRL+i);
			if(index<m_ItemsL.size())
			{
				CString tmp;
				{
					HICON icon=NULL;
					pButton2->SetIcon(icon);
					tmp.Format(_T("%s\n%s"),m_ItemsL[index].item_name1,m_ItemsL[index].item_name2);
				}
				if (m_ItemsL[index].bargain_stype!=0)
				{
					CString strTop;
					strTop.Format(_T("%.0f"),m_ItemsL[index].bargain_num_cur);
					pButton2->SetStrTop(strTop);
					pButton2->SetImages(m_bpButtonRt[0],m_bpButtonRt[1],false);
				}
				else
				{
					pButton2->SetStrTop(_T(""));
					pButton2->SetImages(m_bpButtonLf[0],m_bpButtonLf[1],false);
				}
				pButton2->SetWindowText(tmp);
				pButton2->ShowWindow(SW_SHOW);
			}
			else
			{
				pButton2->ShowWindow(SW_HIDE);
			}
		}
		CRoundButton2* pButton2=(CRoundButton2*)GetDlgItem(IDC_BUTTON_LEFT);
		if (m_nCurrentPagel>0)
			pButton2->ShowWindow(SW_SHOW);
		else
			pButton2->ShowWindow(SW_HIDE);

		pButton2=(CRoundButton2*)GetDlgItem(IDC_BUTTON_RIGHT);
		if (m_nCurrentPagel<m_nPageCountl-1)
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
* 函数介绍：左侧按钮翻页
* 输入参数：
* 输出参数：
* 返回值  ：
************************************************************************/
void SoldOutDlg::OnBnClickedButtonLeft()
{
	if(m_nCurrentPagel>0)
		m_nCurrentPagel--;
	else
		return;
	ShowCurrentPage();
}

void SoldOutDlg::OnBnClickedButtonRight()
{
	if(m_nCurrentPagel<m_nPageCountl-1)
		m_nCurrentPagel++;
	else
		return;
	ShowCurrentPage();
}
void SoldOutDlg::OnLItemBnClicked(UINT uID)
{
	UINT index=m_nCurrentPagel*m_nPageSizel+(uID-IDC_DYNAMIC_CTRL);
	if (index>=m_ItemsL.size())
	{//越界
		LOG4CPLUS_ERROR(log_pos,"index=["<<index<<"] out of range. m_Items.size()="<<m_ItemsL.size());
		return;
	}
	CString strSQL;
	//如果已存在，对不估清的菜品设置为手动估清
	CRecordset rs( &theDB);
	strSQL.Format(_T("SELECT * FROM bargain_price_item WHERE bargain_item_number=%d"),m_ItemsL[index].item_number);
	rs.Open(CRecordset::forwardOnly,strSQL);
	if (!rs.IsEOF())
	{
		CDBVariant variant;
		variant.m_iVal=0;
		rs.GetFieldValue(_T("bargain_stype"),variant);
		if (variant.m_iVal==0)
		{//设置为手动估清
			strSQL.Format(_T("UPDATE bargain_price_item SET bargain_stype=1 WHERE bargain_item_number=%d"),m_ItemsL[index].item_number);
			theDB.ExecuteSQL(strSQL);
			UpdateBargainItem();
		}
		else
		{//已经估清，显示设置
			SoldoutItemDlg dlg(this);
			dlg.m_nItemId=m_ItemsL[index].item_number;
			if(dlg.DoModal()==IDOK)
			{
				UpdateBargainItem(FALSE);
			}
			this->SetFocus();
		}
	}
	else
	{//不存在，插入估清表
		rs.Close();
		//查询主键递增值
		strSQL.Format(_T("select max(bargain_item_id)+1 from bargain_price_item;"));
		rs.Open(CRecordset::forwardOnly,strSQL);
		CString bargain_id;
		rs.GetFieldValue((short)0,bargain_id);
		if(bargain_id.IsEmpty())
			bargain_id=_T("1");

		strSQL.Format(_T("insert into bargain_price_item(bargain_item_id,bargain_item_number,bargain_item_name,bargain_stype,bargain_num,bargain_num_cur,is_every_day)")
            _T(" values(%s,%d,'%s','1',0,0,0);"),bargain_id,m_ItemsL[index].item_number,FormatDBStr(m_ItemsL[index].item_name1));
		theDB.ExecuteSQL(strSQL);
		UpdateBargainItem();
	}
	rs.Close();
}
void SoldOutDlg::OnCbnSelchangeCombo1()
{
	try{
		int sluid=0;
		if(mComboBox.GetCurSel()>=0&&mComboBox.GetCurSel()<mSluId.size())
		sluid=mSluId[mComboBox.GetCurSel()];
		m_ItemsL.clear();
		OpenDatabase();
		CRecordset rs( &theDB);
		CString strSQL;//AND condiment_membership IS NULL
		strSQL.Format(_T("SELECT * FROM menu_item LEFT JOIN bargain_price_item ON item_id=bargain_item_number")
			_T(" WHERE slu_id=\'%d\' ORDER BY slu_priority DESC"),sluid);
		rs.Open( CRecordset::forwardOnly,strSQL);
		while(!rs.IsEOF())
		{
			MenuItem item={0};
			CDBVariant variant;
			rs.GetFieldValue(_T("item_name1"), item.item_name1);
			rs.GetFieldValue(_T("item_id"), variant);
			item.item_number=variant.m_lVal;
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
			m_ItemsL.push_back(item);
			rs.MoveNext();
		}
		rs.Close();
		m_nCurrentPagel=0;
		m_nPageCountl=(int)ceil((float)m_ItemsL.size()/m_nPageSizel);
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
* 函数介绍：右侧按钮翻页
* 输入参数：
* 输出参数：
* 返回值  ：
************************************************************************/
void SoldOutDlg::OnBnClickedButtonLeftR()
{
	if(m_nCurrentPageR>0)
		m_nCurrentPageR--;
	else
		return;
	ShowCurrentPageR();
}

void SoldOutDlg::OnBnClickedButtonRightR()
{
	if(m_nCurrentPageR<m_nPageCountR-1)
		m_nCurrentPageR++;
	else
		return;
	ShowCurrentPageR();
}
void SoldOutDlg::OnRItemBnClicked(UINT uID)
{
	UINT index=m_nCurrentPageR*m_nPageSizeR+(uID-IDC_CLASS_BUTTON);
	if (index>=m_ItemsR.size())
	{//越界
		LOG4CPLUS_ERROR(log_pos,"index=["<<index<<"] out of range. m_Items.size()="<<m_ItemsR.size());
		return;
	}
	SoldoutItemDlg dlg(this);
	dlg.m_nItemId=m_ItemsR[index].item_number;
	if(dlg.DoModal()==IDOK)
	{
		UpdateBargainItem(FALSE);
	}
	this->SetFocus();
}
void SoldOutDlg::ShowCurrentPageR()
{
	try{
		unsigned int index;
		for(int i=0;i<m_nPageSizeR;i++)
		{
			index=i+m_nCurrentPageR*m_nPageSizeR;
			CRoundButton2* pButton2=(CRoundButton2*)GetDlgItem(IDC_CLASS_BUTTON+i);
			if(index<m_ItemsR.size())
			{
				CString itemName;
				if (macrosInt[_T("SHOW_ITEM_ID")]!=0)
				{
					itemName.Format(_T("%d-"),m_ItemsR[index].item_number);
				}
				itemName.AppendFormat(_T("%s\n%s"),m_ItemsR[index].item_name1,m_ItemsR[index].item_name2);
				if (m_ItemsR[index].bargain_stype>1)
				{
					CString strTop;
					strTop.Format(_T("%.0f"),m_ItemsR[index].bargain_num_cur);
					pButton2->SetStrTop(strTop);
				}
				else
					pButton2->SetStrTop(_T(""));
				pButton2->SetWindowText(itemName);
				pButton2->ShowWindow(SW_SHOW);
			}
			else
			{
				pButton2->ShowWindow(SW_HIDE);
			}
		}
		CRoundButton2* pButton2=(CRoundButton2*)GetDlgItem(IDC_BUTTON_UP);
		if (m_nCurrentPageR>0)
			pButton2->ShowWindow(SW_SHOW);
		else
			pButton2->ShowWindow(SW_HIDE);

		pButton2=(CRoundButton2*)GetDlgItem(IDC_BUTTON_DOWN);
		if (m_nCurrentPageR<m_nPageCountR-1)
			pButton2->ShowWindow(SW_SHOW);
		else
			pButton2->ShowWindow(SW_HIDE);
	}
	catch(...)
	{
		LOG4CPLUS_ERROR(log_pos,"Catch Exception GetLastError="<<GetLastError());
	}
}
void SoldOutDlg::OnBnClickedButtonClear()
{
	try
	{
		if(POSMessageBox(IDS_CONFIRM_CLEANSOLD,MB_YESNO)==IDCANCEL)
			return;
		m_ItemsR.clear();
		CString strSQL;
		strSQL.Format(_T("DELETE FROM bargain_price_item"));
		theDB.ExecuteSQL(strSQL);
		UpdateBargainItem();
	}
	catch(CDBException* e)
	{
		LOG4CPLUS_ERROR(log_pos,(LPCTSTR)e->m_strError);
		e->Delete();
	}
}

void SoldOutDlg::OnBnClickedOk()
{
	CPOSClientApp* pApp=(CPOSClientApp*)AfxGetApp();
	OrderDlg* pOrder=(OrderDlg*)pApp->m_pMain->GetPage(DLG_ORDER);
	pOrder->m_bUpdateItems=TRUE;
	CPosPage2::OnCancel();
}


void SoldOutDlg::OnBnClickedButtonSearch()
{
	try
	{
		m_ItemsL.clear();
		OpenDatabase();
		CRecordset rs( &theDB);
		CString strSQL,str;
		mEdit.GetWindowText(str);
		strSQL.Format(_T("SELECT * FROM menu_item LEFT JOIN bargain_price_item ON item_id=bargain_item_number")
			_T(" WHERE item_id LIKE \'%s%%\'OR nlu LIKE \'%%%s%%\' LIMIT 20;"),
			str,str);
		rs.Open( CRecordset::forwardOnly,strSQL);
		while(!rs.IsEOF())
		{
			MenuItem item={0};
			CDBVariant variant;
			rs.GetFieldValue(_T("item_name1"), item.item_name1);
			rs.GetFieldValue(_T("item_id"), variant);
			item.item_number=variant.m_lVal;
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
			m_ItemsL.push_back(item);
			rs.MoveNext();
		}
		rs.Close();
		m_nCurrentPagel=0;
		m_nPageCountl=(int)ceil((float)m_ItemsL.size()/m_nPageSizel);
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



void SoldOutDlg::OnEnChangeEdit1()
{
	OnBnClickedButtonSearch();
}

void SoldOutDlg::OnBnClickedButtonClean()
{
	mEdit.SetWindowText(_T(""));
}
BOOL SoldOutDlg::PreTranslateMessage(MSG* pMsg)
{
	return CPosPage2::PreTranslateMessage(pMsg);
}