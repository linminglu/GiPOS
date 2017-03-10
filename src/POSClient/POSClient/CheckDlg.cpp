// CheckDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "POSClient.h"
#include "CheckDlg.h"
#include <math.h> 

extern std::map<int,TaxItem*> taxGroup;
// CCheckDlg 对话框
CString CCheckDlg::TAX_NAME;
IMPLEMENT_DYNAMIC(CCheckDlg, CDialog)

CCheckDlg::CCheckDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCheckDlg::IDD, pParent)
{
	m_fSubtotal=0;
	m_fService=0;
	m_fDiscount=0;
	m_fTax=0;
	m_fPayed=0;
	m_nStatus=0;
	m_nTotal=0;
	m_nEatType=0;
	m_bHideDesc=FALSE;
	m_pDiscount=NULL;
	m_pService=NULL;
	m_iDxDiscount=-1;
	m_iDxService=-1;
	m_bDiscountChange=FALSE;
	//m_bTaxInclude=TRUE;
}

CCheckDlg::~CCheckDlg()
{
}

void CCheckDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ctrlDetailList);
	DDX_Control(pDX, IDC_LIST2, m_subTotalList);
}

BEGIN_MESSAGE_MAP(CCheckDlg, CDialog)
	ON_WM_SIZE()
	ON_LBN_SELCHANGE(IDC_LIST1, &CCheckDlg::OnLbnSelchangeList)
	ON_MESSAGE(WM_MESSAGE_ENABLE,EnablePage)
END_MESSAGE_MAP()

/************************************************************************
* 函数介绍：作为只窗口，按键事件都不处理
* 输入参数：
* 输出参数：
* 返回值  ：
************************************************************************/
BOOL CCheckDlg::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message==WM_KEYDOWN)     
		return FALSE;
	return CDialog::PreTranslateMessage(pMsg); 
}
// CCheckDlg 消息处理程序

void CCheckDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	if (m_ctrlDetailList.m_hWnd)
	{
		double cent=0.7;
		if(CMainSheet::m_iStaticsInfo<3)
			cent=0.75;
		m_ctrlDetailList.MoveWindow(0,0,cx,(int)(cy*cent));
		m_subTotalList.MoveWindow(0,(int)(cy*cent),cx,(int)(cy*(1-cent)));
	}
}
/************************************************************************
* 函数介绍：清空小计信息
* 输入参数：
* 输出参数：
* 返回值  ：
************************************************************************/
void CCheckDlg::ResetContent(BOOL bAll)
{
	m_ctrlDetailList.ResetContent();
	m_fSubtotal=0;
	m_fService=0;
	m_fDiscount=0;
	m_pDiscount=NULL;
	m_pService=NULL;
	m_iDxDiscount=-1;
	m_iDxService=-1;
	m_bDiscountChange=FALSE;
	if (bAll)
	{
		m_fPayed=0;
		m_fTax=0;
	}
}
BOOL CCheckDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_ctrlDetailList.m_nSubWidth[0]=50*CreatButton::m_nFullWidth/1024;
	m_ctrlDetailList.m_nSubWidth[1]=180*CreatButton::m_nFullWidth/1024;
	m_ctrlDetailList.m_nSubWidth[2]=70*CreatButton::m_nFullWidth/1024;

	m_subTotalList.m_nSubWidth[0]=10*CreatButton::m_nFullWidth/1024;
	m_subTotalList.m_nSubWidth[1]=130*CreatButton::m_nFullWidth/1024;
	m_subTotalList.m_nSubWidth[2]=160*CreatButton::m_nFullWidth/1024;

	m_pOrderList=&((CPOSClientApp*)AfxGetApp())->m_orderList;

	if(CMainSheet::m_iStaticsInfo&0x08)
	{//税率
		std::map<int,TaxItem*>::iterator iter;
		for(iter=taxGroup.begin();iter!=taxGroup.end();iter++)
		{
			TaxItem* tax=new TaxItem;
			tax->id=iter->second->id;
			tax->name=iter->second->name;
			tax->rate=iter->second->rate;
			tax->total=0;
			mTaxGroup[tax->id]=tax;
		}
		//首先税率
		TaxItem* tax=new TaxItem;
		tax->id=0;
		tax->name=TAX_NAME;
		tax->rate=theApp.m_dTaxRate;
		tax->total=0;
		mTaxGroup[0]=tax;
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
/************************************************************************
* 函数介绍：格式化菜品的显示
* 输入参数：
* 输出参数：
* 返回值  ：
************************************************************************/
void CCheckDlg::FormatString(OrderDetail* pOrder,CString& strLine,BOOL bHideDesc)
{
	strLine.Empty();
	CString decPlace;
	decPlace.Format(_T(".%df|"),theApp.DECIMAL_PLACES);
	if (pOrder->item_id<0)
	{//特殊类型
		switch(pOrder->item_id)
		{
		case ITEM_ID_PAYINFO:
			{
				if(abs(pOrder->total_price)<0.01)
				{//兼容旧版
					strLine.Format(_T("|| %s"),pOrder->item_name);
				}
				else
				{
					strLine.Format(_T("|| %s:")+theApp.m_decPlace,pOrder->item_name,pOrder->total_price);
				}

				if(pOrder->item_price>0.01)
				{
					CString str2;
					theLang.LoadString(str2,IDS_CHANGE);
					strLine.AppendFormat(_T(" %s:")+theApp.m_decPlace+_T("||"),str2,pOrder->item_price);
				}
				else
				{
					strLine.Append(_T("||"));
				}
				break;
			}
		case ITEM_ID_DISCOUNT:
		case ITEM_ID_SERVICE:
		case ITEM_ID_TIPS:
			{//服务费或者折扣,显示为红色
				strLine.Format(_T("25|| %s|%")+decPlace,pOrder->item_name,pOrder->total_price);
				break;
			}
		default:
			{//文字信息
				strLine.Format(_T("|| %s||"),pOrder->item_name);
			}
		}
		return;
	}
	//菜品
	CString name;
	CString str2;
	if (pOrder->n_eattype==TYPE_TAKEOUT)
	{
		theLang.LoadString(str2,IDS_TAKEOUT);
		name.Append(str2);
	}
	name.Append(pOrder->item_name);
	if (pOrder->b_reprice)
	{
		name.Append(_T("*"));
	}
	if (pOrder->b_isfree)
	{
		theLang.LoadString(str2,IDS_FREE);
		name.Append(str2);
	}
	if(pOrder->rush_times>0)
	{
		strLine=_T("24");
	}
	if (pOrder->n_belong_item!=0)
	{//配料,默认不需要显示数量
		CString strNum,strPrice;
		if (pOrder->quantity==1)
			strNum=_T("||");
		else
			strNum.Format(_T("|%g|"),pOrder->quantity);

		if(fabs(pOrder->total_price-0)>0.001)
			strPrice.Format(_T("|%")+decPlace,pOrder->total_price);
		else
			strPrice=_T("||");

		if (pOrder->unit[0]!=0)
		{
			name.AppendFormat(_T("(%s)"),pOrder->unit);
		}
		if (bHideDesc==FALSE&&pOrder->description[0]!=0)
		{
			name.AppendFormat(_T("\n %s"),pOrder->description);
		}
		strLine.AppendFormat(_T("%s  %s%s"),strNum,name,strPrice);
		return;
	}
	
	if (pOrder->weight_required)//称重产品显示重量
	{
		if (bHideDesc==FALSE&&pOrder->description[0]!=0)
			strLine.AppendFormat(_T("|1|%s\n%g %s\n%s|%")+decPlace,name,pOrder->quantity,pOrder->unit,pOrder->description,pOrder->total_price);
		else
			strLine.AppendFormat(_T("|1|%s\n%g %s|%")+decPlace,name,pOrder->quantity,pOrder->unit,pOrder->total_price);
	}
	else
	{
		if (bHideDesc==FALSE&&pOrder->description[0]!=0)
		{
			name.AppendFormat(_T("\n%s"),pOrder->description);
		}
		strLine.AppendFormat(_T("|%g%s|%s|%")+decPlace,pOrder->quantity,pOrder->unit,name,pOrder->total_price);
	}
}
int CCheckDlg::DeleteOrderItem(int index)
{
	OrderDetail* pTmpOder=(OrderDetail*)m_ctrlDetailList.GetItemDataPtr(index);
	if(pTmpOder->item_id==ITEM_ID_SERVICE&&pTmpOder->discount_percent>0.001)
	{
		m_pService=NULL;
		m_iDxService=-1;
	}
	else if(pTmpOder->item_id==ITEM_ID_DISCOUNT&&pTmpOder->discount_percent>0.001)
	{
		m_pDiscount=NULL;
		m_iDxDiscount=-1;
		m_bDiscountChange=TRUE;
	}
	if(index<=m_iDxService)
		m_iDxService--;
	if(index<=m_iDxDiscount)
		m_iDxDiscount--;
	return m_ctrlDetailList.DeleteString(index);
}
/************************************************************************
* 函数介绍：添加已点菜品到显示列表
* 输入参数：order	--新点的菜
*			bUpdate	--是否重新计算总额(可提高效率)
*			insertIndex --插入位置
* 输出参数：
* 返回值  ：
			成功:新插入返回-1; 合并则返回合并的索引
************************************************************************/
int CCheckDlg::AddOrderItem(OrderDetail* order,BOOL bUpdate,int insertIndex)
{
	if (order==NULL)
		return NULL;
	if (m_nStatus==0&&order->time_accuracy>0&&order->order_id>0)
	{//计时菜品更新价格
		CString strSQL;
		strSQL.Format(_T("SELECT TIMESTAMPDIFF(MINUTE,order_time,now()) FROM order_detail WHERE order_detail_id=%d"),order->order_id);
		CRecordset rs(&theDB);
		rs.Open( CRecordset::forwardOnly,strSQL);
		if (!rs.IsEOF())
		{
			CString strVal;
			rs.GetFieldValue((short)0,strVal);
			double quantity=(int)(_wtof(strVal)/order->time_accuracy+0.5);
			if (quantity>0)
			{
				order->quantity=quantity;
				ComputeTotalPrice(order);
			}
		}
	}
	CString strTmp;
	FormatString(order,strTmp,m_bHideDesc);
	if(macrosInt[_T("NO_AUTO_COMBINE")]==0&&insertIndex==-1)
	//相同菜品自动合并数量
	if (order->item_id>0&&!order->weight_required&&order->n_saved==0&&order->time_accuracy<=0
		&&order->b_hascondiment==FALSE&&order->n_belong_item<=0&&order->b_isfree==FALSE)
	{//自定菜、折扣、服务费，配料，称重产品，有配料的产品不合并
		for (int i=0;i<m_ctrlDetailList.GetCount();i++)
		{
			OrderDetail* pTmpOder=(OrderDetail*)m_ctrlDetailList.GetItemDataPtr(i);
			if (pTmpOder->n_saved==0&&!pTmpOder->b_hascondiment&&pTmpOder->item_id==order->item_id
				&&(pTmpOder->description[0]==0)//添加过做法的不合并
				&&(pTmpOder->item_price==order->item_price)&&(pTmpOder->n_eattype==order->n_eattype)
				&&(wcscmp(pTmpOder->unit,order->unit)==0)&&pTmpOder->b_isfree==FALSE
				&&(wcscmp(pTmpOder->item_name,order->item_name)==0))//相同规格
			{//找到一样的
				if((pTmpOder->n_belong_item<0&&order->n_belong_item<0)&&(i!=m_ctrlDetailList.GetCount()-1))
					continue;
				
				pTmpOder->quantity+=order->quantity;
				pTmpOder->total_price+=order->total_price;
				//pTmpOder->tax_amount+=order->tax_amount;
				//不能直接相加，抹零后要重新计算
				m_fTax-=pTmpOder->tax_amount;
				ComputeTax(pTmpOder);
				m_fTax+=pTmpOder->tax_amount;
				m_fSubtotal+=order->total_price;
				
				FormatString(pTmpOder,strTmp,m_bHideDesc);
				m_ctrlDetailList.DeleteString(i);
				m_ctrlDetailList.InsertString(i,strTmp);
				m_ctrlDetailList.SetItemDataPtr(i,pTmpOder);
				m_ctrlDetailList.SetCaretIndex(i);
				if (bUpdate)
					ComputeSubtotal();
				return i;
			}
		}
	}
	
	int index;
	if(insertIndex==-1)
	{
		index=m_ctrlDetailList.AddString(strTmp);
	}
	else
	{
		index=m_ctrlDetailList.InsertString(insertIndex,strTmp);
	}
	m_ctrlDetailList.SetCaretIndex(index);
	m_ctrlDetailList.SetItemDataPtr(index,order);
	if(order->item_id==ITEM_ID_SERVICE)
	{
		m_fService+=order->total_price;
		if(order->discount_percent>0.001)
		{
			m_pService=order;
			m_iDxService=index;
		}
		m_bDiscountChange=TRUE;
	}
	else if (order->item_id==ITEM_ID_DISCOUNT)
	{
		m_fDiscount+=order->total_price;
		if(order->discount_percent>0.001)
		{
			m_pDiscount=order;
			m_iDxDiscount=index;
			m_bDiscountChange=TRUE;
		}
	}
	else if(order->item_id>0)
	{//菜品
		m_fSubtotal+=order->total_price;
	}
	m_fTax+=order->tax_amount;
	if (bUpdate)
	{
		ComputeSubtotal();
	}
	return -1;
}
/************************************************************************
* 函数介绍：插入配料。该函数可不按点菜顺序插入配料
* 输入参数：
* 输出参数：
* 返回值  ：
************************************************************************/
void CCheckDlg::InsertCondiment(int index,OrderDetail* order,BOOL bUpdate)
{
	CString strTmp;
	FormatString(order,strTmp,m_bHideDesc);
	int ind=m_ctrlDetailList.InsertString(index,strTmp);
	m_ctrlDetailList.SetItemDataPtr(ind,order);
	if (bUpdate)
		ComputeSubtotal();
}
/************************************************************************
* 函数介绍：更新已点菜品的显示。例如修改菜品数量后刷新显示
* 输入参数：
* 输出参数：
* 返回值  ：
************************************************************************/
BOOL CCheckDlg::UpdateItemString(int nIndex,BOOL bReCompute)
{
	if(nIndex>=m_ctrlDetailList.GetCount())
		return FALSE;//下标越界
	OrderDetail* pOrder=(OrderDetail*)m_ctrlDetailList.GetItemDataPtr(nIndex);
	if (pOrder==NULL)
		return FALSE;
	CString strTmp;
	FormatString(pOrder,strTmp,m_bHideDesc);
	m_ctrlDetailList.DeleteString(nIndex);
	m_ctrlDetailList.InsertString(nIndex,strTmp);
	m_ctrlDetailList.SetItemDataPtr(nIndex,pOrder);
	if(bReCompute)
		ComputeSubtotal();
	return TRUE;
}
/************************************************************************
* 函数介绍：获取最近输入的菜品id
* 输入参数：
* 输出参数：
* 返回值  ：
************************************************************************/
OrderDetail* CCheckDlg::GetLastItem()
{
	for (int i=m_ctrlDetailList.GetCount()-1;i>=0;i--)
	{
		OrderDetail* pTmpOder=(OrderDetail*)m_ctrlDetailList.GetItemDataPtr(i);
		if (pTmpOder!=NULL&&pTmpOder->item_id>0
			&&(pTmpOder->n_belong_item<=0))
		{
			pTmpOder->b_hascondiment=TRUE;
			return pTmpOder;
		}
	}
	return NULL;
}
/************************************************************************
* 函数介绍：添加已付金额
* 输入参数：
* 输出参数：
* 返回值  ：
************************************************************************/
void CCheckDlg::AddPay(double fPayed)
{
	m_fPayed+=fPayed;
	UpdateSubtotal();
}
/************************************************************************
* 函数介绍：刷新小计信息显示
* 输入参数：
* 输出参数：
* 返回值  ：
************************************************************************/
void CCheckDlg::UpdateSubtotal()
{
	CString strTmp,str2;
	m_fDebt=0;
	m_subTotalList.ResetContent();
	if(CMainSheet::m_iStaticsInfo&0x04)
	{
		theLang.LoadString(str2,IDS_ORDERED);
		strTmp.Format(_T("||%s|[%d]|"),str2,m_nTotal);
		m_subTotalList.AddString(strTmp);
	}
	CString decPlace;
	decPlace.Format(_T(".%df|"),theApp.DECIMAL_PLACES);
	if((CMainSheet::m_iStaticsInfo&0x03)==0x03)
	{//折扣和服务费同时显示
		theLang.LoadString(str2,IDS_SUBTOTAL);
		strTmp.Format(_T("||%s|%")+decPlace,str2,m_fSubtotal);
		m_subTotalList.AddString(strTmp);
		theLang.LoadString(str2,IDS_DISCOUNT);
		strTmp.Format(_T("||%s|%")+decPlace,str2,m_fDiscount);
		m_subTotalList.AddString(strTmp);
		theLang.LoadString(str2,IDS_SERVICE);
		strTmp.Format(_T("||%s|%")+decPlace,str2,m_fService);
		m_subTotalList.AddString(strTmp);
	}
	else if(CMainSheet::m_iStaticsInfo&0x02)
	{//只显示折扣
		theLang.LoadString(str2,IDS_SUBTOTAL);
		strTmp.Format(_T("||%s|%")+decPlace,str2,m_fSubtotal+m_fService);
		m_subTotalList.AddString(strTmp);
		theLang.LoadString(str2,IDS_DISCOUNT);
		strTmp.Format(_T("||%s|%")+decPlace,str2,m_fDiscount);
		m_subTotalList.AddString(strTmp);
	}
	else
	{//只显示服务费
		theLang.LoadString(str2,IDS_SUBTOTAL);
		strTmp.Format(_T("||%s|%")+decPlace,str2,m_fSubtotal+m_fDiscount);
		m_subTotalList.AddString(strTmp);
		theLang.LoadString(str2,IDS_SERVICE);
		strTmp.Format(_T("||%s|%")+decPlace,str2,m_fService);
		m_subTotalList.AddString(strTmp);
	}
	if(CMainSheet::m_iStaticsInfo&0x08)
	{//税率
		if(CCheckDlg::TAX_NAME.IsEmpty())
		{
			CString str2;
			theLang.LoadString(str2,IDS_TAX);
			strTmp.Format(_T("||%s|%")+decPlace,str2,(double)m_fTax);
		}
		else
		{
			strTmp.Format(_T("||%s|%")+decPlace,TAX_NAME,(double)m_fTax);
		}
		m_subTotalList.AddString(strTmp);
		if(theApp.m_nTaxType!=1)//已含税，不再相加
			m_fDebt+=m_fTax;
	}
	
	theLang.LoadString(str2,IDS_PAYED);
	strTmp.Format(_T("||%s|%")+decPlace,str2,(double)m_fPayed);
	m_subTotalList.AddString(strTmp);
	
	m_fDebt+=m_fSubtotal+m_fService+m_fDiscount-m_fPayed;
	//整单抹零-已结的单不要再抹零
	m_fMolin=0;
	if (theApp.m_nRoundType>0&&m_nStatus==0)
	{
		m_fMolin=-CCheckDlg::Round(m_fDebt,theApp.m_nRoundType);
		m_fDebt+=m_fMolin;
	}
	CPOSClientApp* pApp=(CPOSClientApp*)AfxGetApp();
	m_nEatType=pApp->m_nEatType;
	if (m_nEatType==TYPE_TAKEOUT)
	{
		theLang.LoadString(str2,IDS_TAKEAWAY);
		strTmp.Format(_T("35||%s|%")+decPlace,str2,(double)m_fDebt);
	}
	else
	{
		theLang.LoadString(str2,IDS_DEBT);
		strTmp.Format(_T("35||%s|%")+decPlace,str2,(double)m_fDebt);
	}
	m_subTotalList.AddString(strTmp);
}
/************************************************************************
* 函数介绍：重新计算小计信息,主要是根据点的菜重新计算折扣、服务费
*	计算顺序：总额-折扣+服务费+税率
*	折扣需要更新到每个菜品/服务费，以便后续计算税金
* 输入参数：
* 输出参数：
* 返回值  ：
************************************************************************/
void CCheckDlg::ComputeSubtotal()
{
	m_fSubtotal=0;
	m_fService=0;
	m_fDiscount=0;
	m_fTax=0;
	m_nTotal=0;
	std::map<int,TaxItem*>::iterator iter;
	for(iter=mTaxGroup.begin();iter!=mTaxGroup.end();iter++)
	{
		if(iter->second)
			iter->second->total=0;
	}
	CString strSQL;
	//计算小计信息
	double canService=0;//可收服务费的金额
	double canDiscount=0;
	double taxDiscount=0;
	for (int i=0;i<m_ctrlDetailList.GetCount();i++)
	{
		OrderDetail* pTmpOder=(OrderDetail*)m_ctrlDetailList.GetItemDataPtr(i);
		if (pTmpOder->item_id==ITEM_ID_SERVICE)
		{
			if(pTmpOder->discount_percent<0.001)
			{//非整单服务费
				if(m_bDiscountChange)
				{
					//服务费也要打折
					if(m_pDiscount&&pTmpOder->noDiscount==FALSE)
					{
						double disc=(m_pDiscount->discount_percent*pTmpOder->item_price)/100;
						double diff=CCheckDlg::Round(disc,m_pDiscount->round_type);
						disc-=diff;
						pTmpOder->total_price=pTmpOder->item_price-disc;
					}
					else
					{
						pTmpOder->discount_price=0;
						pTmpOder->total_price=pTmpOder->item_price;
					}
					UpdateItemString(i,FALSE);//防止递归死循环
					if (pTmpOder->n_saved!=0&&m_nStatus==0)
					{
						strSQL.Format(_T("UPDATE order_detail SET actual_price=%f WHERE order_detail_id=%d")
							,pTmpOder->total_price,pTmpOder->order_id);
						theDB.ExecuteSQL(strSQL);
					}
					
				}
				m_fService+=pTmpOder->total_price;
			}
			//else 整单服务费，后面更新
		}
		else if (pTmpOder->item_id==ITEM_ID_DISCOUNT)
		{
			if(pTmpOder->discount_percent<0.001)
			{//非整单折扣
				taxDiscount+=pTmpOder->total_price;
			}
		}
		else if(pTmpOder->item_id>0)
		{//普通菜品
			m_fSubtotal+=pTmpOder->total_price;
			if(m_pService&&pTmpOder->n_service_type>0)//可收服务费
				canService+=pTmpOder->total_price;
			if(m_pDiscount&&pTmpOder->n_discount_type>0)//可打折
			{
				pTmpOder->discount_price=-(m_pDiscount->discount_percent*pTmpOder->total_price)/100;
				canDiscount+=pTmpOder->total_price;
			}
			else
			{
				pTmpOder->discount_price=0;
			}
			ComputeTax(pTmpOder);
			if (pTmpOder->n_belong_item<=0)
			{
				if(pTmpOder->weight_required)
					m_nTotal++;
				else
					m_nTotal+=pTmpOder->quantity;
			}
			m_fTax+=pTmpOder->tax_amount;
			if(pTmpOder->tax_group>0)
			{
				TaxItem* pTax=mTaxGroup[pTmpOder->tax_group];
				if(pTax)
					pTax->total+=pTmpOder->tax_amount;
			}
		}
		
	}
	m_bDiscountChange=FALSE;
	m_fDiscount=taxDiscount;
	int nIndex=0;
	if(m_pDiscount!=NULL)//更新整单折扣
	{
		m_pDiscount->total_price=(m_pDiscount->discount_percent*canDiscount)/100;
		//抹零
		double diff=CCheckDlg::Round(m_pDiscount->total_price,m_pDiscount->round_type);
		m_pDiscount->total_price-=diff;
		m_pDiscount->total_price*=-1;
		m_fDiscount+=m_pDiscount->total_price;
		UpdateItemString(m_iDxDiscount,FALSE);//防止递归死循环
		if (m_pDiscount->n_saved!=0&&m_nStatus==0)
		{
			strSQL.Format(_T("UPDATE order_detail SET actual_price=%f WHERE order_detail_id=%d")
				,m_pDiscount->total_price,m_pDiscount->order_id);
			theDB.ExecuteSQL(strSQL);
		}
	}
	if (m_pService!=NULL)//更新整单服务费
	{
		if(m_pService->noDiscount==FALSE)
			canService+=m_fDiscount;
		m_pService->total_price=(m_pService->discount_percent*(canService))/100;
		//只针对当前抹零
		double diff=CCheckDlg::Round(m_pService->total_price,m_pService->round_type);
		m_pService->total_price-=diff;
		m_pService->item_price=m_pService->total_price;
		m_fService+=m_pService->total_price;
		UpdateItemString(m_iDxService,FALSE);//防止递归死循环
		//如果已存储，需要更新数据库
		if (m_pService->n_saved!=0&&m_nStatus==0)
		{
			strSQL.Format(_T("UPDATE order_detail SET actual_price=%f WHERE order_detail_id=%d")
							,m_pService->total_price,m_pService->order_id);
			theDB.ExecuteSQL(strSQL);
		}
	}
	
	if(CMainSheet::m_iStaticsInfo&0x08)
	{//税率
		if(theApp.m_bTaxGST)
		{//服务费收税
			m_fTax+=m_fService*theApp.m_dTaxRate/100;
		}
		//金额折扣也要计算到税率
		taxDiscount=taxDiscount*theApp.m_dTaxRate/100;
		m_fTax+=taxDiscount;
		if (theApp.m_nTaxRound==1)
			m_fTax=int(m_fTax+0.5);
		else if (theApp.m_nTaxRound==2)
			m_fTax=int(m_fTax);
		double tax_total=0;
		std::map<int,TaxItem*>::iterator iter;
		for(iter=mTaxGroup.begin();iter!=mTaxGroup.end();iter++)
		{
			if(iter->first!=0)
				tax_total+=iter->second->total;
		}
		//更新首先税率金额
		mTaxGroup[0]->total=m_fTax-tax_total;
	}
	UpdateSubtotal();
}
/************************************************************************
* 函数介绍：计算可以打折的菜品总价
* 输入参数：
* 输出参数：
* 返回值  ：
************************************************************************/
double CCheckDlg::GetSubtotalToDiscount()
{
	double fSubtotal=0;
	for (int i=0;i<m_ctrlDetailList.GetCount();i++)
	{
		OrderDetail* pTmpOder=(OrderDetail*)m_ctrlDetailList.GetItemDataPtr(i);
		if (pTmpOder->item_id==ITEM_ID_SERVICE)
			continue;//不算服务费
		else if(pTmpOder->item_id==ITEM_ID_DISCOUNT)
			continue;//不算折扣
		else if(pTmpOder->n_discount_type>0)
		{
			fSubtotal+=pTmpOder->total_price;
			//更新该菜的折扣金额
		}
	}
	return fSubtotal;
}
/************************************************************************
* 函数介绍：计算抹零
* 输入参数：total-要抹零的金额
round_type：1- 小数抹零； 2- 个位抹零； 3- 十位抹零 ；4- 二舍八入、三七作五
* 输出参数： 
* 返回值  ：抹零抹掉的差额
* 负数的抹零参考：https://en.wikipedia.org/wiki/Rounding#Tie-breaking
************************************************************************/
double CCheckDlg::Round(double total,int round_type)
{
	double round_total=0;
	BOOL bNegtive=FALSE;
	if(total<0){
		total=total*(-1);
		bNegtive=TRUE;
	}
	switch (round_type)
	{
	case 1://小数抹零
		round_total=(int)total;
		break;
	case 2://个位抹零
		round_total=((int)total/10)*10;
		break;
	case 3://十位抹零
		round_total=((int)total/100)*100;
		break;
	case 4://二舍八入、三七作五（针对个位）
		{
			int end=(int)total%10;
			int ten=total/10;
			if(end<=2){
				end=0;
			}
			else if(end>=3&&end<=7){
				end=5;
			}
			else{
				end=10;
			}
			round_total=ten*10+end;
		}
		break;
	case 5://个位四舍五入
		{
			if(bNegtive)
				round_total=ceil(total/10-0.5);
			else
				round_total=int(total/10+0.5);
			round_total=round_total*10;
		}
		break;
	case 6://小数位四舍五入
		if(bNegtive)
			round_total=ceil(total-0.5);
		else
			round_total=int(total+0.5);
		break;
	case 7://分位四舍五入
		if(bNegtive)
		{
			double d=total*10-0.5;
			double decimal=d-(int)d;
			if(decimal<0.00000001)//double 精度问题，特殊处理
				round_total=(int)d;
			else
				round_total=ceil(d);
		}
		else
			round_total=int(total*10+0.5);
		round_total=round_total/10;
		break;
	case 8://分位二舍八入、三七作五
		{
			double tmpt=total*100;
			int end=(int)tmpt%10;
			int ten=tmpt/10;
			if(end<=2){
				end=0;
			}
			else if(end>=3&&end<=7){
				end=5;
			}
			else{
				end=10;
			}
			round_total=(ten*10+end)/100.0;
		}
		break;
	case 9://分位一四进五 六九进角
		{
			double tmpt=total*100;
			int end=(int)tmpt%10;
			int ten=tmpt/10;
			if(end>=1&&end<=4){
				end=5;
			}
			else if(end>=6&&end<=9){
				end=10;
			}
			round_total=(ten*10+end)/100.0;
		}
		break;
	default:
		return 0;
	}
	if(bNegtive)
		return round_total-total;
	else
		return total-round_total;
}
void CCheckDlg::OnLbnSelchangeList()
{
	BOOL bSetSel=FALSE;
	BOOL bInSet=FALSE;//在套餐内部
	for (int i=0;i<m_ctrlDetailList.GetCount();i++)
	{
		if (m_ctrlDetailList.GetSel(i))
		{
			OrderDetail* pTmpOder=(OrderDetail*)m_ctrlDetailList.GetItemDataPtr(i);
			if (pTmpOder->b_hascondiment)
			{//如果有配料，自动选中配料
				bSetSel=TRUE;
			}
			if (pTmpOder->n_belong_item<0)
				bInSet=TRUE;
			else
				bInSet=FALSE;
		}
		else if (bSetSel==TRUE)
		{
			OrderDetail* pTmpOder=(OrderDetail*)m_ctrlDetailList.GetItemDataPtr(i);
			if (bInSet)
			{
				if (pTmpOder->n_belong_item>0)
				{//选中配料
					m_ctrlDetailList.SetSel(i);
				}
				else//到达下一个菜品
					bSetSel=FALSE;
			}
			else
			{
				if (pTmpOder->n_belong_item!=0)
				{//选中配料
					m_ctrlDetailList.SetSel(i);
				}
				else//到达下一个菜品
					bSetSel=FALSE;
			}
			
		}
	}
}
LRESULT CCheckDlg::EnablePage(WPARAM wParam, LPARAM lParam)
{
	m_ctrlDetailList.m_bCanSelect=(BOOL)wParam;
	return 0;
}
