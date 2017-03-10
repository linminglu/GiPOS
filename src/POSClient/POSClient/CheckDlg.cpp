// CheckDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "POSClient.h"
#include "CheckDlg.h"
#include <math.h> 

extern std::map<int,TaxItem*> taxGroup;
// CCheckDlg �Ի���
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
* �������ܣ���Ϊֻ���ڣ������¼���������
* ���������
* ���������
* ����ֵ  ��
************************************************************************/
BOOL CCheckDlg::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message==WM_KEYDOWN)     
		return FALSE;
	return CDialog::PreTranslateMessage(pMsg); 
}
// CCheckDlg ��Ϣ�������

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
* �������ܣ����С����Ϣ
* ���������
* ���������
* ����ֵ  ��
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
	{//˰��
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
		//����˰��
		TaxItem* tax=new TaxItem;
		tax->id=0;
		tax->name=TAX_NAME;
		tax->rate=theApp.m_dTaxRate;
		tax->total=0;
		mTaxGroup[0]=tax;
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
/************************************************************************
* �������ܣ���ʽ����Ʒ����ʾ
* ���������
* ���������
* ����ֵ  ��
************************************************************************/
void CCheckDlg::FormatString(OrderDetail* pOrder,CString& strLine,BOOL bHideDesc)
{
	strLine.Empty();
	CString decPlace;
	decPlace.Format(_T(".%df|"),theApp.DECIMAL_PLACES);
	if (pOrder->item_id<0)
	{//��������
		switch(pOrder->item_id)
		{
		case ITEM_ID_PAYINFO:
			{
				if(abs(pOrder->total_price)<0.01)
				{//���ݾɰ�
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
			{//����ѻ����ۿ�,��ʾΪ��ɫ
				strLine.Format(_T("25|| %s|%")+decPlace,pOrder->item_name,pOrder->total_price);
				break;
			}
		default:
			{//������Ϣ
				strLine.Format(_T("|| %s||"),pOrder->item_name);
			}
		}
		return;
	}
	//��Ʒ
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
	{//����,Ĭ�ϲ���Ҫ��ʾ����
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
	
	if (pOrder->weight_required)//���ز�Ʒ��ʾ����
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
* �������ܣ�����ѵ��Ʒ����ʾ�б�
* ���������order	--�µ�Ĳ�
*			bUpdate	--�Ƿ����¼����ܶ�(�����Ч��)
*			insertIndex --����λ��
* ���������
* ����ֵ  ��
			�ɹ�:�²��뷵��-1; �ϲ��򷵻غϲ�������
************************************************************************/
int CCheckDlg::AddOrderItem(OrderDetail* order,BOOL bUpdate,int insertIndex)
{
	if (order==NULL)
		return NULL;
	if (m_nStatus==0&&order->time_accuracy>0&&order->order_id>0)
	{//��ʱ��Ʒ���¼۸�
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
	//��ͬ��Ʒ�Զ��ϲ�����
	if (order->item_id>0&&!order->weight_required&&order->n_saved==0&&order->time_accuracy<=0
		&&order->b_hascondiment==FALSE&&order->n_belong_item<=0&&order->b_isfree==FALSE)
	{//�Զ��ˡ��ۿۡ�����ѣ����ϣ����ز�Ʒ�������ϵĲ�Ʒ���ϲ�
		for (int i=0;i<m_ctrlDetailList.GetCount();i++)
		{
			OrderDetail* pTmpOder=(OrderDetail*)m_ctrlDetailList.GetItemDataPtr(i);
			if (pTmpOder->n_saved==0&&!pTmpOder->b_hascondiment&&pTmpOder->item_id==order->item_id
				&&(pTmpOder->description[0]==0)//��ӹ������Ĳ��ϲ�
				&&(pTmpOder->item_price==order->item_price)&&(pTmpOder->n_eattype==order->n_eattype)
				&&(wcscmp(pTmpOder->unit,order->unit)==0)&&pTmpOder->b_isfree==FALSE
				&&(wcscmp(pTmpOder->item_name,order->item_name)==0))//��ͬ���
			{//�ҵ�һ����
				if((pTmpOder->n_belong_item<0&&order->n_belong_item<0)&&(i!=m_ctrlDetailList.GetCount()-1))
					continue;
				
				pTmpOder->quantity+=order->quantity;
				pTmpOder->total_price+=order->total_price;
				//pTmpOder->tax_amount+=order->tax_amount;
				//����ֱ����ӣ�Ĩ���Ҫ���¼���
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
	{//��Ʒ
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
* �������ܣ��������ϡ��ú����ɲ������˳���������
* ���������
* ���������
* ����ֵ  ��
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
* �������ܣ������ѵ��Ʒ����ʾ�������޸Ĳ�Ʒ������ˢ����ʾ
* ���������
* ���������
* ����ֵ  ��
************************************************************************/
BOOL CCheckDlg::UpdateItemString(int nIndex,BOOL bReCompute)
{
	if(nIndex>=m_ctrlDetailList.GetCount())
		return FALSE;//�±�Խ��
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
* �������ܣ���ȡ�������Ĳ�Ʒid
* ���������
* ���������
* ����ֵ  ��
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
* �������ܣ�����Ѹ����
* ���������
* ���������
* ����ֵ  ��
************************************************************************/
void CCheckDlg::AddPay(double fPayed)
{
	m_fPayed+=fPayed;
	UpdateSubtotal();
}
/************************************************************************
* �������ܣ�ˢ��С����Ϣ��ʾ
* ���������
* ���������
* ����ֵ  ��
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
	{//�ۿۺͷ����ͬʱ��ʾ
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
	{//ֻ��ʾ�ۿ�
		theLang.LoadString(str2,IDS_SUBTOTAL);
		strTmp.Format(_T("||%s|%")+decPlace,str2,m_fSubtotal+m_fService);
		m_subTotalList.AddString(strTmp);
		theLang.LoadString(str2,IDS_DISCOUNT);
		strTmp.Format(_T("||%s|%")+decPlace,str2,m_fDiscount);
		m_subTotalList.AddString(strTmp);
	}
	else
	{//ֻ��ʾ�����
		theLang.LoadString(str2,IDS_SUBTOTAL);
		strTmp.Format(_T("||%s|%")+decPlace,str2,m_fSubtotal+m_fDiscount);
		m_subTotalList.AddString(strTmp);
		theLang.LoadString(str2,IDS_SERVICE);
		strTmp.Format(_T("||%s|%")+decPlace,str2,m_fService);
		m_subTotalList.AddString(strTmp);
	}
	if(CMainSheet::m_iStaticsInfo&0x08)
	{//˰��
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
		if(theApp.m_nTaxType!=1)//�Ѻ�˰���������
			m_fDebt+=m_fTax;
	}
	
	theLang.LoadString(str2,IDS_PAYED);
	strTmp.Format(_T("||%s|%")+decPlace,str2,(double)m_fPayed);
	m_subTotalList.AddString(strTmp);
	
	m_fDebt+=m_fSubtotal+m_fService+m_fDiscount-m_fPayed;
	//����Ĩ��-�ѽ�ĵ���Ҫ��Ĩ��
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
* �������ܣ����¼���С����Ϣ,��Ҫ�Ǹ��ݵ�Ĳ����¼����ۿۡ������
*	����˳���ܶ�-�ۿ�+�����+˰��
*	�ۿ���Ҫ���µ�ÿ����Ʒ/����ѣ��Ա��������˰��
* ���������
* ���������
* ����ֵ  ��
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
	//����С����Ϣ
	double canService=0;//���շ���ѵĽ��
	double canDiscount=0;
	double taxDiscount=0;
	for (int i=0;i<m_ctrlDetailList.GetCount();i++)
	{
		OrderDetail* pTmpOder=(OrderDetail*)m_ctrlDetailList.GetItemDataPtr(i);
		if (pTmpOder->item_id==ITEM_ID_SERVICE)
		{
			if(pTmpOder->discount_percent<0.001)
			{//�����������
				if(m_bDiscountChange)
				{
					//�����ҲҪ����
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
					UpdateItemString(i,FALSE);//��ֹ�ݹ���ѭ��
					if (pTmpOder->n_saved!=0&&m_nStatus==0)
					{
						strSQL.Format(_T("UPDATE order_detail SET actual_price=%f WHERE order_detail_id=%d")
							,pTmpOder->total_price,pTmpOder->order_id);
						theDB.ExecuteSQL(strSQL);
					}
					
				}
				m_fService+=pTmpOder->total_price;
			}
			//else ��������ѣ��������
		}
		else if (pTmpOder->item_id==ITEM_ID_DISCOUNT)
		{
			if(pTmpOder->discount_percent<0.001)
			{//�������ۿ�
				taxDiscount+=pTmpOder->total_price;
			}
		}
		else if(pTmpOder->item_id>0)
		{//��ͨ��Ʒ
			m_fSubtotal+=pTmpOder->total_price;
			if(m_pService&&pTmpOder->n_service_type>0)//���շ����
				canService+=pTmpOder->total_price;
			if(m_pDiscount&&pTmpOder->n_discount_type>0)//�ɴ���
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
	if(m_pDiscount!=NULL)//���������ۿ�
	{
		m_pDiscount->total_price=(m_pDiscount->discount_percent*canDiscount)/100;
		//Ĩ��
		double diff=CCheckDlg::Round(m_pDiscount->total_price,m_pDiscount->round_type);
		m_pDiscount->total_price-=diff;
		m_pDiscount->total_price*=-1;
		m_fDiscount+=m_pDiscount->total_price;
		UpdateItemString(m_iDxDiscount,FALSE);//��ֹ�ݹ���ѭ��
		if (m_pDiscount->n_saved!=0&&m_nStatus==0)
		{
			strSQL.Format(_T("UPDATE order_detail SET actual_price=%f WHERE order_detail_id=%d")
				,m_pDiscount->total_price,m_pDiscount->order_id);
			theDB.ExecuteSQL(strSQL);
		}
	}
	if (m_pService!=NULL)//�������������
	{
		if(m_pService->noDiscount==FALSE)
			canService+=m_fDiscount;
		m_pService->total_price=(m_pService->discount_percent*(canService))/100;
		//ֻ��Ե�ǰĨ��
		double diff=CCheckDlg::Round(m_pService->total_price,m_pService->round_type);
		m_pService->total_price-=diff;
		m_pService->item_price=m_pService->total_price;
		m_fService+=m_pService->total_price;
		UpdateItemString(m_iDxService,FALSE);//��ֹ�ݹ���ѭ��
		//����Ѵ洢����Ҫ�������ݿ�
		if (m_pService->n_saved!=0&&m_nStatus==0)
		{
			strSQL.Format(_T("UPDATE order_detail SET actual_price=%f WHERE order_detail_id=%d")
							,m_pService->total_price,m_pService->order_id);
			theDB.ExecuteSQL(strSQL);
		}
	}
	
	if(CMainSheet::m_iStaticsInfo&0x08)
	{//˰��
		if(theApp.m_bTaxGST)
		{//�������˰
			m_fTax+=m_fService*theApp.m_dTaxRate/100;
		}
		//����ۿ�ҲҪ���㵽˰��
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
		//��������˰�ʽ��
		mTaxGroup[0]->total=m_fTax-tax_total;
	}
	UpdateSubtotal();
}
/************************************************************************
* �������ܣ�������Դ��۵Ĳ�Ʒ�ܼ�
* ���������
* ���������
* ����ֵ  ��
************************************************************************/
double CCheckDlg::GetSubtotalToDiscount()
{
	double fSubtotal=0;
	for (int i=0;i<m_ctrlDetailList.GetCount();i++)
	{
		OrderDetail* pTmpOder=(OrderDetail*)m_ctrlDetailList.GetItemDataPtr(i);
		if (pTmpOder->item_id==ITEM_ID_SERVICE)
			continue;//��������
		else if(pTmpOder->item_id==ITEM_ID_DISCOUNT)
			continue;//�����ۿ�
		else if(pTmpOder->n_discount_type>0)
		{
			fSubtotal+=pTmpOder->total_price;
			//���¸ò˵��ۿ۽��
		}
	}
	return fSubtotal;
}
/************************************************************************
* �������ܣ�����Ĩ��
* ���������total-ҪĨ��Ľ��
round_type��1- С��Ĩ�㣻 2- ��λĨ�㣻 3- ʮλĨ�� ��4- ������롢��������
* ��������� 
* ����ֵ  ��Ĩ��Ĩ���Ĳ��
* ������Ĩ��ο���https://en.wikipedia.org/wiki/Rounding#Tie-breaking
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
	case 1://С��Ĩ��
		round_total=(int)total;
		break;
	case 2://��λĨ��
		round_total=((int)total/10)*10;
		break;
	case 3://ʮλĨ��
		round_total=((int)total/100)*100;
		break;
	case 4://������롢�������壨��Ը�λ��
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
	case 5://��λ��������
		{
			if(bNegtive)
				round_total=ceil(total/10-0.5);
			else
				round_total=int(total/10+0.5);
			round_total=round_total*10;
		}
		break;
	case 6://С��λ��������
		if(bNegtive)
			round_total=ceil(total-0.5);
		else
			round_total=int(total+0.5);
		break;
	case 7://��λ��������
		if(bNegtive)
		{
			double d=total*10-0.5;
			double decimal=d-(int)d;
			if(decimal<0.00000001)//double �������⣬���⴦��
				round_total=(int)d;
			else
				round_total=ceil(d);
		}
		else
			round_total=int(total*10+0.5);
		round_total=round_total/10;
		break;
	case 8://��λ������롢��������
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
	case 9://��λһ�Ľ��� ���Ž���
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
	BOOL bInSet=FALSE;//���ײ��ڲ�
	for (int i=0;i<m_ctrlDetailList.GetCount();i++)
	{
		if (m_ctrlDetailList.GetSel(i))
		{
			OrderDetail* pTmpOder=(OrderDetail*)m_ctrlDetailList.GetItemDataPtr(i);
			if (pTmpOder->b_hascondiment)
			{//��������ϣ��Զ�ѡ������
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
				{//ѡ������
					m_ctrlDetailList.SetSel(i);
				}
				else//������һ����Ʒ
					bSetSel=FALSE;
			}
			else
			{
				if (pTmpOder->n_belong_item!=0)
				{//ѡ������
					m_ctrlDetailList.SetSel(i);
				}
				else//������һ����Ʒ
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
