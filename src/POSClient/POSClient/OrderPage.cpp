#include "StdAfx.h"
#include "OrderPage.h"
#include "NumberInputDlg.h"
#include "VoidReasonDlg.h"
#include <afxinet.h>
#include "WeixinPayDlg.h"
#include "SecondScreen.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

int COrderPage::m_nLastActive;
CString COrderPage::m_strTAInfo;
CString COrderPage::m_strCardID;
BOOL COrderPage::bNewTainfo=FALSE;
COrderPage::COrderPage(int nId)
:CPosPage(nId)
{
}

COrderPage::~COrderPage()
{
}
void COrderPage::UpdateSencondScreen(int active,OrderDetail* pOder)
{
	if(m_pSecond==NULL)
		return;
	if (active!=m_nLastActive||pOder==NULL)
	{
		m_nLastActive=active;
		m_pSecond->ReshowAll(m_checkDlg[active]);
	}
	else
	{
		CListBoxEx* ptrDetailList=&m_checkDlg[active].m_ctrlDetailList;
		CString text;
		ptrDetailList->GetText(ptrDetailList->GetCount()-1,text);
		m_pSecond->AddItem(m_checkDlg[active],text);
	}
	//ˢ���ܼ�
	
	m_pSecond->ShowAmount((double)m_checkDlg[active].m_fPayed,(double)m_checkDlg[active].m_fDebt);
}
void COrderPage::UpdateHint(LPCTSTR strHint)
{
	m_ctrlHint.SetWindowText(strHint);
	InvalidateRect(mRectHint);
}
/************************************************************************
* �������ܣ����ڴ��и����˵���Ϣ
* ���������
* ���������
* ����ֵ  ��
************************************************************************/
void COrderPage::UpdateCheckData()
{
	try{
		if (m_pOrderList==NULL)
			return;
		//�����˵���Ϣ
		int count=m_TabCtrl.GetPageCount()-1;
		m_TabCtrl.DisablePage(0,FALSE);
		for (int i=count;i>0;i--)
		{
			m_TabCtrl.DisablePage(i,FALSE);
			m_TabCtrl.RemovePage(i);
		}
		for (int i=0;i<MAX_CHECKS;i++)
		{
			m_checkDlg[i].ResetContent(FALSE);
			//Ϊ�˲���˸���Ƚ�ֹˢ��
			m_checkDlg[i].LockWindowUpdate();
		}
		POSITION pos=NULL;
		CString strTmp;
		for(pos=m_pOrderList->GetHeadPosition();pos!=NULL;)
		{
			POSITION prePos=pos;
			OrderDetail* item=m_pOrderList->GetNext(pos);
			int activePage=item->n_checkID-1;
			int size=m_TabCtrl.GetPageCount();
			if(item->n_checkID>size&&item->n_checkID<=MAX_CHECKS)
			{
				for(int i=size;i<item->n_checkID;i++)
				{
					strTmp.Format(_T("%d"),i+1);
					m_TabCtrl.AddPage(&m_checkDlg[i],strTmp,NULL);
				}
				//m_TabCtrl.UpdateWindow();
			}
			if (activePage<0||activePage>=MAX_CHECKS)
			{
				activePage=0;
			}
			if(m_checkDlg[activePage].AddOrderItem(item,FALSE)>=0)
			{//�����˺ϲ��������б���ɾ��
				m_pOrderList->RemoveAt(prePos);
				delete item;
			}
		}
		//ˢ��С��
		CPOSClientApp* pApp=((CPOSClientApp*)AfxGetApp());
		for (int i=0;i<MAX_CHECKS;i++)
		{
			if (m_checkDlg[i].m_nStatus==1)
			{
				m_TabCtrl.DisablePage(i);
			}
			//if(theApp.m_bDirty==3)
			//	m_checkDlg[i].UpdateSubtotal();//��ˢ��
			//else
				m_checkDlg[i].ComputeSubtotal();//���¼���
			m_checkDlg[i].UnlockWindowUpdate();
		}
		int active=pApp->m_nActiveCheck;
		if (active==-1)
			active=0;
		if(active>=m_TabCtrl.GetPageCount())
			active=m_TabCtrl.GetPageCount()-1;
		m_TabCtrl.SetActivePage(active,TRUE);
		m_TabCtrl.UpdateWindow();
	}
	catch(...)
	{
		LOG4CPLUS_ERROR(log_pos,"Catch Exception GetLastError="<<GetLastError());
	}
}
/************************************************************************
* �������ܣ������ݿ��м����˵���Ϣ
* ���������
* ���������
* ����ֵ  ��
************************************************************************/
void COrderPage::LoadCheckData()
{
	try
	{
		//�����ѵ��Ʒ��Ϣ
		while(!m_pOrderList->IsEmpty())
		{
			OrderDetail* item=m_pOrderList->GetTail();
			m_pOrderList->RemoveTail();
			delete item;
		}
		
		//�����˵���Ϣ
		int count=m_TabCtrl.GetPageCount()-1;
		m_TabCtrl.DisablePage(0,FALSE);
		for (int i=count;i>0;i--)
		{
			m_TabCtrl.DisablePage(i,FALSE);
			m_TabCtrl.RemovePage(i);
		}
		for (int i=0;i<MAX_CHECKS;i++)
		{
			m_checkDlg[i].ResetContent();
			//Ϊ�˲���˸���Ƚ�ֹˢ��
			m_checkDlg[i].LockWindowUpdate();
			m_checkDlg[i].m_nStatus=0;
			//m_checkDlg[i].EnableWindow();
		}
		OpenDatabase();
		CRecordset rs( &theDB);
		CString strSQL;

		//�����Ѹ����
		strSQL.Format(_T("SELECT * FROM order_head WHERE order_head_id=\'%d\';"),theApp.m_nOrderHeadid);
		BOOL bSetType=FALSE;
		rs.Open( CRecordset::forwardOnly,strSQL);
		while(!rs.IsEOF())
		{
			try{
			CDBVariant var_check;
			CString strVal;
			rs.GetFieldValue(_T("check_id"),var_check);
			rs.GetFieldValue(_T("actual_amount"),strVal);
			int index=var_check.m_iVal-1;
			if(index>=0&&index<MAX_CHECKS)
			{
				m_checkDlg[index].m_fPayed=_wtof(strVal);
				rs.GetFieldValue(_T("tax_amount"),strVal);
				m_checkDlg[index].m_fTax=_wtof(strVal);
				var_check.m_iVal=0;
				rs.GetFieldValue(_T("status"),var_check);
				m_checkDlg[index].m_nStatus=var_check.m_iVal;
			}
			if (!bSetType)
			{
				CDBVariant variant;
				variant.m_iVal=0;
				rs.GetFieldValue(_T("eat_type"),variant);
				theApp.m_nEatType=variant.m_iVal;
				rs.GetFieldValue(_T("member_discount"),strVal);
				theApp.m_fMemberDiscount=_wtof(strVal);
				rs.GetFieldValue(_T("delivery_info"),strVal);
				m_strTAInfo.Format(_T("%s"),strVal);
				bSetType=TRUE;
			}
			}catch(...){
			}
			rs.MoveNext();
		}
		rs.Close();

		strSQL.Format(_T("SELECT * FROM order_detail LEFT JOIN menu_item ON menu_item_id=item_id WHERE order_head_id=%d AND is_return_item=0")
			,theApp.m_nOrderHeadid);
		rs.Open( CRecordset::forwardOnly,strSQL);
		while(!rs.IsEOF())
		{
			CString name;
			CString strTmp;
			CDBVariant variant;
			//�����˵��Ĳ�Ʒ
			rs.GetFieldValue(_T("is_return_item"),variant);
			if(variant.m_boolVal)
			{
				rs.MoveNext();
				continue;
			}
			OrderDetail* order=new OrderDetail;
			memset(order,0,sizeof(OrderDetail));
			rs.GetFieldValue(_T("check_id"),variant);
			order->n_checkID=variant.m_iVal;
			int activePage=variant.m_iVal-1;
			int size=m_TabCtrl.GetPageCount();
			if(variant.m_iVal>size&&variant.m_iVal<=MAX_CHECKS)
			{
				for(int i=size;i<variant.m_iVal;i++)
				{
					strTmp.Format(_T("%d"),i+1);
					m_TabCtrl.AddPage(&m_checkDlg[i],strTmp,NULL);
					//m_TabCtrl.SetActivePage(i);
				}
				//m_TabCtrl.UpdateWindow();
			}
			if (activePage<0||activePage>=MAX_CHECKS)
			{
				activePage=0;
			}
			readOrderDetail(rs,order);
			if(!theApp.m_strEndTime.IsEmpty())
				order->time_accuracy=0;//�����ʵĵ������¼�ʱ��
			//���ǰһ�������ϵ�����
			BOOL bAdd=FALSE;
			if(order->n_belong_item>0)
			{
				for(int i=m_checkDlg[activePage].m_ctrlDetailList.GetCount()-1;i>=0;i--)
				{
					OrderDetail* pBefore=(OrderDetail*)m_checkDlg[activePage].m_ctrlDetailList.GetItemDataPtr(i);
					if (pBefore!=NULL&&pBefore->order_id==order->n_belong_item)
					{
						order->belongto=pBefore;
						pBefore->b_hascondiment=TRUE;
						m_checkDlg[activePage].InsertCondiment(i+1,order,FALSE);
						bAdd=TRUE;
						break;
					}
				}
			}
			//�ײ�
			else if (order->n_belong_item<0)
			{
				int lastSub=-1;//���һ���ײ��Ӳ�
				for(int i=m_checkDlg[activePage].m_ctrlDetailList.GetCount()-1;i>=0;i--)
				{//��ĩβ��ʼ
					OrderDetail* pBefore=(OrderDetail*)m_checkDlg[activePage].m_ctrlDetailList.GetItemDataPtr(i);
					if (pBefore<=NULL)
						continue;
					if (lastSub==-1)
					{
						if(pBefore->n_belong_item==order->n_belong_item||
							(pBefore->n_belong_item>0&&pBefore->belongto>0&&pBefore->belongto->n_belong_item==order->n_belong_item))
						{
							lastSub=i;
							m_checkDlg[activePage].AddOrderItem(order,FALSE,lastSub+1);
							bAdd=TRUE;
							break;
						}
					}
					if (pBefore->order_id==abs(order->n_belong_item))
					{
						pBefore->b_hascondiment=ITEM_SET;
						break;
					}
				}
			}
			//���δ����ݿ��ж�ȡ�������кϲ�����
			if(bAdd==FALSE)
				m_checkDlg[activePage].AddOrderItem(order,FALSE);
			m_pOrderList->AddTail(order);
			rs.MoveNext();
		}
		rs.Close();
		
		//ˢ��С��
		int active=theApp.m_nActiveCheck;
		for (int i=0;i<MAX_CHECKS;i++)
		{
			if(m_checkDlg[i].m_nStatus==1)
			m_TabCtrl.DisablePage(i);
			m_checkDlg[i].ComputeSubtotal();
			m_checkDlg[i].UnlockWindowUpdate();
		}
		m_TabCtrl.SetActivePage(active,TRUE);
		m_TabCtrl.UpdateWindow();
	}
	catch(CDBException* e)
	{
		LOG4CPLUS_ERROR(log_pos,(LPCTSTR)e->m_strError);
		e->Delete();
		for (int i=0;i<MAX_CHECKS;i++)
		{
			m_checkDlg[i].UnlockWindowUpdate();
		}
		m_TabCtrl.UpdateWindow();
		return;
	}
}

void COrderPage::readOrderDetail(CRecordset& rs,OrderDetail* order)
{
	try{
		CDBVariant variant;
		CString strVal;
		rs.GetFieldValue(_T("check_id"),variant);
		order->n_checkID=variant.m_iVal;
		variant.m_iVal=0;
		rs.GetFieldValue(_T("condiment_belong_item"),variant);
		order->n_belong_item=variant.m_lVal;
		CString name;
		rs.GetFieldValue(_T("menu_item_name"),name);
		wcsncpy_s(order->item_name,name,63);
		try{
			rs.GetFieldValue(_T("item_name2"),name);
			wcsncpy_s(order->item_name2,name,31);
			variant.m_iVal=0;
			rs.GetFieldValue(_T("is_time_price"),variant);
			if(variant.m_iVal>0)
			{
				rs.GetFieldValue(_T("price_per_minute"),variant);
				order->time_accuracy=variant.m_iVal;
			}
			variant.m_lVal=0;
			rs.GetFieldValue(_T("rush"),variant);
			order->rush_times=variant.m_lVal;
		}catch(...)
		{
		}
		rs.GetFieldValue(_T("actual_price"),strVal);
		order->total_price=_wtof(strVal);
		rs.GetFieldValue(_T("sales_amount"),variant);
		order->sales_amount=variant.m_fltVal;
		rs.GetFieldValue(_T("product_price"),strVal);
		order->item_price=_wtof(strVal);
		rs.GetFieldValue(_T("order_detail_id"),variant);
		order->order_id=variant.m_lVal;
		variant.m_fltVal=0;
		rs.GetFieldValue(_T("quantity"),variant);
		order->quantity=variant.m_fltVal;
		variant.m_boolVal=FALSE;
		rs.GetFieldValue(_T("is_send"),variant);
		order->n_saved=variant.m_boolVal?2:1;
		rs.GetFieldValue(_T("menu_item_id"),variant);
		order->item_id=variant.m_lVal;
		variant.m_iVal=0;
		rs.GetFieldValue(_T("eat_type"),variant);
		order->n_eattype=variant.m_iVal;
		rs.GetFieldValue(_T("unit"),name);
		wcsncpy_s(order->unit,name,9);
		rs.GetFieldValue(_T("description"),name);
		wcsncpy_s(order->description,name,99);
		variant.m_boolVal=0;
		rs.GetFieldValue(_T("weight_entry_required"),variant);
		order->weight_required=variant.m_boolVal;
		variant.m_iVal=9;
		rs.GetFieldValue(_T("discount_id"),variant);
		order->n_discount_type=variant.m_iVal;
		variant.m_iVal=9;
		rs.GetFieldValue(_T("n_service_type"),variant);
		order->n_service_type=variant.m_iVal;
		variant.m_boolVal=0;
		rs.GetFieldValue(_T("is_discount"),variant);
		order->b_isfree=variant.m_boolVal;
		variant.m_boolVal=0;
		rs.GetFieldValue(_T("not_print"),variant);
		order->b_notprint=variant.m_boolVal;
		variant.m_iVal=0;
		rs.GetFieldValue(_T("seat_num"),variant);
		order->n_seat_num=variant.m_iVal;
		variant.m_lVal=0;
		rs.GetFieldValue(_T("print_class"),variant);
		order->family_group=variant.m_lVal;
		if(order->family_group<=0)
		{
			variant.m_lVal=0;
			rs.GetFieldValue(_T("family_group"),variant);
			order->family_group=variant.m_lVal;
		}
		rs.GetFieldValue(_T("original_price"),variant);
		if (variant.m_dwType!=DBVT_NULL)
		{
			order->b_reprice=TRUE;
			order->orignal_price=variant.m_fltVal;
		}
		variant.m_lVal=0;
		rs.GetFieldValue(_T("tax_group"), variant);
		order->tax_group=variant.m_lVal;
		ComputeTax(order);
		CString strSQL;
		//������ۿۣ���ȡ�ۿ�����
		if (order->item_id==ITEM_ID_DISCOUNT||order->item_id==ITEM_ID_SERVICE)
		{
			CRecordset rs1( &theDB);
			if (order->item_id==ITEM_ID_DISCOUNT)
			{
				strSQL.Format(_T("SELECT * FROM discount_service WHERE discount_service_id=\'%d\';"),order->n_discount_type);
			}
			else if (order->item_id==ITEM_ID_SERVICE)
			{
				strSQL.Format(_T("SELECT * FROM service_tip WHERE service_tip_id=\'%d\';"),order->n_discount_type);
			}
			order->discount_percent=-1;//������
			rs1.Open( CRecordset::forwardOnly,strSQL);
			if (!rs1.IsEOF())
			{
				variant.m_iVal=0;
				rs1.GetFieldValue(_T("type"), variant);
				int type=variant.m_iVal;
				variant.m_boolVal=FALSE;
				rs1.GetFieldValue(_T("preset"), variant);
				if(variant.m_boolVal&&type!=1)
				{//�����ۿ� (�Զ����ۿ۲�����)
					variant.m_boolVal=FALSE;
					rs1.GetFieldValue(_T("select_discount"), variant);
					if(variant.m_boolVal==FALSE)
					{
						CString strVal;
						rs1.GetFieldValue(_T("percent"), strVal);
						order->discount_percent=_wtof(strVal);
					}
				}
				variant.m_iVal=0;
				rs1.GetFieldValue(_T("menu_level_class"), variant);
				order->round_type=variant.m_iVal;
				if (order->item_id==ITEM_ID_SERVICE)
				{
					variant.m_boolVal=FALSE;
					rs1.GetFieldValue(_T("discount_over_threshold"), variant);
					order->noDiscount=variant.m_boolVal;
				}
			}
			rs1.Close();
		}
		else if(order->n_saved==1)//δ�ͳ��Ĳ�Ʒ����ȡ��������
		{
			CRecordset rs1( &theDB);
			strSQL.Format(_T("SELECT bargain_stype FROM bargain_price_item WHERE bargain_item_number=%d"),order->item_id);
			rs1.Open( CRecordset::forwardOnly,strSQL);
			if (!rs1.IsEOF())
			{
				variant.m_iVal=0;
				rs1.GetFieldValue(_T("bargain_stype"), variant);
				order->bargain_stype=variant.m_iVal;
			}
			rs1.Close();
		}
	}
	catch(CDBException* e)
	{
		//LOG4CPLUS_ERROR(log_pos,(LPCTSTR)e->m_strError);
		e->Delete();
	}
}

/************************************************************************
* �������ܣ��˲�
* ���������
* ���������
* ����ֵ  ��
************************************************************************/
void COrderPage::VoidItem(int active)
{
	try
	{
		if (m_checkDlg[active].m_nStatus==1)
		{
			return;
		}
		CPOSClientApp* pApp=(CPOSClientApp*)AfxGetApp();
		CListBoxEx* ptrDetailList=&m_checkDlg[active].m_ctrlDetailList;
		if (ptrDetailList==NULL)
			return;
		if (ptrDetailList->GetSelCount()==0)
		{
			if (m_nVoidState==1)
			{//�˵����һ����Ʒ
				ptrDetailList->SetSel(ptrDetailList->GetCount()-1);
				m_nVoidState=0;
				UpdateHint(_T(""));
			}
			else
			{
				m_nVoidState=1;
				CString str2;
				theLang.LoadString(IDS_VOIDMODE,str2);
				UpdateHint(str2);
				return;
			}
		}
		CVoidReasonDlg reasonDlg;
		CString userid;
		CString strSQL;
		CString strDetail;
		CString strDetail2;
		WCHAR username[10];
		BOOL flag=TRUE;
		vector<PrintItem> menu_list;
		OpenDatabase();
		for(int  i=ptrDetailList->GetCount()-1;i>=0;i--)
		{
			if(ptrDetailList->GetSel(i))
			{
				OrderDetail* item=(OrderDetail*)ptrDetailList->GetItemDataPtr(i);
				if (item->item_id==ITEM_ID_SENDINFO)
				{//��ʾ�ַ�������ɾ��
					continue;
				}
				double voidQuantity=item->quantity;
				BOOL voidAll=TRUE;
				POSITION pos=m_pOrderList->Find(item);
				if (pos!=NULL)
				{
					if(item->n_saved)
					{
						//�Ѵ洢����ҪȨ��ɾ��
						while(flag)
						{
							int auth=RequeastAuth(userid,_T("void_item"),1,username);
							if (auth==-1)
							{//�û�ȡ��
								m_checkDlg[active].ComputeSubtotal();
								return;
							}
							else if(auth==0)
							{
								flag=FALSE;
								//ѡ���˲�ԭ��
								if(reasonDlg.DoModal()==IDCANCEL)
								{
									m_checkDlg[active].ComputeSubtotal();
									return;
								}
							}
						}
						//����1�ݵĲˣ�Ҫ���û������˲�����
						if (item->item_id>0&&item->quantity>1&&item->weight_required==FALSE
							&&item->b_hascondiment!=ITEM_SET&&item->n_belong_item>=0)
						{//�ײͺ��ײ��ڲ���Ʒȫ���˵�
							NumberInputDlg dlg;
							theLang.LoadString(dlg.m_strHint,IDS_INPUTVOIDNUM);
							if (dlg.DoModal()==IDCANCEL)
								continue;
							if (dlg.m_strNum.IsEmpty())
							{//�û�δ���룬Ĭ��ȫ���˲�
								voidQuantity=item->quantity;
							}
							else
							{
								voidQuantity=_wtof(dlg.m_strNum);
								if (voidQuantity>item->quantity)
									voidQuantity=item->quantity;
								if (voidQuantity<=0)
									continue;
							}
						}
						//������ͳ���֪ͨ����
						if (item->n_saved==2&&item->item_id>0&&macrosInt[_T("NOPRINT_VOID")]!=1&&item->b_notprint==FALSE)
						{
							PrintItem pItem;
							CopyPrintItem(pItem,item);
							pItem.description=reasonDlg.m_strReason;
							pItem.b_isvoid=TRUE;
							if (voidQuantity<item->quantity)
							{//�����˲�
								pItem.quantity=voidQuantity;
								pItem.total_price=item->item_price*voidQuantity;
							}
							menu_list.insert(menu_list.begin(),pItem);
						}
						if (voidQuantity<item->quantity&&item->item_id>0)
						{//�����˲�
							voidAll=FALSE;
							//1.����ԭ��¼�Ĳ�Ʒ����
							item->quantity-=voidQuantity;
							if(!item->b_isfree)
								ComputeTotalPrice(item);
							CString strTmp;
							CCheckDlg::FormatString(item,strTmp,m_checkDlg[active].m_bHideDesc);
							ptrDetailList->DeleteString(i);
							ptrDetailList->InsertString(i,strTmp);
							ptrDetailList->SetItemDataPtr(i,item);
							strSQL.Format(_T("UPDATE order_detail SET quantity=%f,actual_price=%f WHERE order_detail_id=%d")
								,item->quantity,item->total_price,item->order_id);
							theDB.ExecuteSQL(strSQL);
							//2.���ͳ��ģ������˲˼�¼
							if(item->n_saved==2)
							{
								COrder_Detail rsDetail(&theDB);
								rsDetail.Open(CRecordset::snapshot, NULL, CRecordset::appendOnly);
								rsDetail.AddNew();
								SetRsDetail(rsDetail,item);
								rsDetail.m_quantity=voidQuantity;
								rsDetail.m_actual_price=item->item_price*voidQuantity;
								rsDetail.m_is_return_item=TRUE;
								rsDetail.m_return_reason=reasonDlg.m_strReason;
								rsDetail.m_return_time=CTime::GetCurrentTime();
								rsDetail.m_auth_id=_wtol(userid);
								rsDetail.m_auth_name=username;
								rsDetail.Update();
								rsDetail.Close();
								strDetail.AppendFormat(_T("%s(%g) "),item->item_name,voidQuantity);
							}
						}
						else
						{//��ȫ����
// 							if(item->item_id>0&&item->n_saved==1)
// 							{//�����δ�ͳ��Ĳ�Ʒ��ֱ��ɾ��
// 								strSQL.Format(_T("DELETE FROM order_detail WHERE order_detail_id=\'%d\'")
// 								,item->order_id);
// 								theDB.ExecuteSQL(strSQL);
// 							}
// 							else
							{
							strSQL.Format(_T("UPDATE order_detail SET is_return_item=1,return_reason=\'%s\',auth_id=\'%s\',return_time=now()")
							_T(",auth_name=\'%s\' WHERE order_detail_id=\'%d\';"),
							reasonDlg.m_strReason,userid,username,item->order_id);
							theDB.ExecuteSQL(strSQL);
							if(item->item_id>0)
								strDetail.AppendFormat(_T("%s(%g) "),item->item_name,voidQuantity);
							}
						}
					}
					else
					{
						strDetail2.AppendFormat(_T("%s(%g) "),item->item_name,voidQuantity);
					}
				}
				if(item->item_id==ITEM_ID_SERVICE)
					m_checkDlg[active].m_fService-=item->total_price;
				else
					m_checkDlg[active].m_fSubtotal-=item->total_price;
				if (item->item_id==ITEM_ID_PAYINFO)
				{//ɾ���������⴦��
					DeletePay(item->order_id);
					//���¼����Ѹ����
					strSQL.Format(_T("SELECT SUM(total) FROM payment WHERE order_head_id=%d AND check_id=%d"),pApp->m_nOrderHeadid,active+1);
					CRecordset rs( &theDB);
					CString strVal;
					rs.Open(CRecordset::forwardOnly,strSQL);
					if(!rs.IsEOF())
					{
						rs.GetFieldValue((short)0,strVal);
					}
					m_checkDlg[active].m_fPayed=_wtof(strVal);
					strSQL.Format(_T("UPDATE order_head SET actual_amount=\'%0.2f\' WHERE order_head_id=%d AND check_id=%d;"),
					m_checkDlg[active].m_fPayed,pApp->m_nOrderHeadid,active+1);
					theDB.ExecuteSQL(strSQL);
				}
				if (item->item_id<0)
				{
					strDetail.AppendFormat(_T("%s "),item->item_name);
				}
				UpdateSoldoutInfo(item,voidQuantity);
				if (voidAll)
				{//��ȫ����
					//ptrDetailList->DeleteString(i);
					m_checkDlg[active].DeleteOrderItem(i);
					m_pOrderList->RemoveAt(pos);
					delete item;
				}
			}
		}
		if(!strDetail.IsEmpty())
		{
			CPOSClientApp::CriticalLogs(OPR_VOID,strDetail);
		}
		if(theApp.m_VCR.IsOpen())
		{
			CString strLine;
			strLine.Format(_T("VOID %s\n"),strDetail2,strDetail);
			theApp.m_VCR.Print(strLine);
		}
		LOG4CPLUS_INFO(log_pos,"COrderPage::OnBnClickedButtonVoid "<<(LPCTSTR)strDetail);
		if(macrosInt[_T("NOPRINT_VOID")]!=1)
		{
			//���ô�ӡ
			JSONVALUE root;
			root["template"]=TEMPLATE_VOID;
			FormatTableInfo(root);
			PrintMenu(menu_list,root,0);
		}
		m_checkDlg[active].ComputeSubtotal();
		UpdateSencondScreen(active,NULL);
		theApp.m_cusDisplay.Display((double)m_checkDlg[active].m_fDebt,2);
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
* �������ܣ�����Ȩ�ޡ�����ǰ�û���strPrivilege��Ȩ����ֱ�ӷ��أ�������Ҫ
��������Ȩ�û�ID
* ���������-nTryTime			���ԵĴ���
-strPrivilege		��Ҫ��Ȩ��
-nMiniPermission	��СȨ��
* ���������-authID				����ͨ����Ȩ���û�ID
-pAuthUser			����ͨ����Ȩ���û���
* ����ֵ  �� 0 --ͨ����֤
-1 --�û�ȡ��
-2 --��֤ʧ��
************************************************************************/
int COrderPage::RequeastAuth(CString& authID,CString strPrivilege,int nMiniPermission,WCHAR* pAuthUser)
{
	try{
		int nValue=0;
		if(theApp.m_privilegeMap.Lookup(strPrivilege,nValue))
		{
			if (nValue>=nMiniPermission)
			{//����Ȩ��
				authID=theApp.m_strUserID;
				if(pAuthUser)
					wcsncpy_s(pAuthUser,10,(LPCTSTR)theApp.m_strUserName,_TRUNCATE);
				return 0;
			}
		}
		LOG4CPLUS_WARN(log_pos,"User "<<(LPCTSTR)theApp.m_strUserID<<" requeast \'"<<(LPCTSTR)strPrivilege<<"\' fail");
		int nTryTime=3;
		//��������Ȩ�û�ID
		while(nTryTime>0)
		{
			nTryTime--;
			NumberInputDlg dlg;
			CString strSQL;
			CString strPSW;
			dlg.m_bPassword=TRUE;
			theLang.LoadString(dlg.m_strHint,IDS_REQUESTAUTH);
			if (dlg.DoModal()==IDCANCEL)
			{
				return -1;
			}
			else
			{
				//������Ȩ�û�
				OpenDatabase();
				CRecordset rs(&theDB);
				if(dlg.m_bSwipe==FALSE)
				{
					authID=dlg.m_strNum.Left(3);//ǰ3λΪID
					strPSW=dlg.m_strNum.Mid(3);
					strSQL.Format(_T("SELECT e.password_id,e.employee_last_name,c.%s FROM employee e LEFT JOIN employee_class c")
						_T(" ON e.employee_class=c.employee_class_id WHERE employee_id=\'%s\';"),strPrivilege,authID);
				}
				else
				{
					strSQL.Format(_T("SELECT e.employee_id,e.employee_last_name,c.%s FROM employee e LEFT JOIN employee_class c")
						_T(" ON e.employee_class=c.employee_class_id WHERE pc_aps_id=\'%s\';"),strPrivilege,dlg.m_strNum);
				}
				rs.Open( CRecordset::forwardOnly,strSQL);
				if (rs.GetRecordCount()==0)
				{
					POSMessageBox(IDS_NOUSER);
				}
				else
				{
					if(dlg.m_bSwipe==FALSE)
					{//�ֶ����룬�������
						CString psw;
						rs.GetFieldValue(_T("password_id"),psw);
						if(psw!=strPSW)
						{
							POSMessageBox(IDS_WRONGPSW);
							continue;
						}
					}
					else
					{
						rs.GetFieldValue(_T("employee_id"),authID);
					}

					CDBVariant variant;
					rs.GetFieldValue(strPrivilege,variant);
					if (variant.m_lVal>=nMiniPermission)
					{
						if (pAuthUser)
						{
							CString tmp;
							rs.GetFieldValue(_T("employee_last_name"),tmp);
							wcsncpy_s(pAuthUser,10,(LPCTSTR)tmp,_TRUNCATE);
						}
						return 0;
					}
					else
					{
						POSMessageBox(IDS_NOPRIVALAGE);
					}
				}
			}
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
	return -2;
}
/************************************************************************
* �������ܣ��������Ϣת��ΪPrintItem��������ӡ
* ���������
* ���������
* ����ֵ  ��
************************************************************************/
void COrderPage::CopyPrintItem(PrintItem& pItem,OrderDetail* from)
{
	pItem.item_id=from->item_id;
	pItem.n_belong_item=from->n_belong_item;
	pItem.item_name=from->item_name;
	pItem.item_name2=from->item_name2;
// #ifdef EN_VERSION
// 	if(from->n_belong_item>0&&pItem.item_name2.IsEmpty()){//��ζƷ����name2
// 		pItem.item_name2=from->item_name;
// 	}
// #endif
	pItem.b_isfree=from->b_isfree;
	if (from->quantity<0)
		pItem.b_isvoid=TRUE;
	else
		pItem.b_isvoid=FALSE;
	pItem.description=from->description;
	pItem.item_price=from->item_price;
	pItem.n_eattype=from->n_eattype;
	pItem.n_seat=from->n_seat_num;
	pItem.unit=from->unit;
	pItem.total_price=from->total_price;
	pItem.quantity=from->quantity;
	pItem.n_class=from->family_group;
	pItem.n_check=from->n_checkID;
}

// CString FormatString(LPCTSTR str)
// {
// 	if (str==NULL)
// 		return _T("NULL");
// 	CString re=str;
// 	re.Replace(_T("'"),_T("''"));
// 	re.Replace(_T("\\"),_T("\\\\"));
// 	re.Format(_T("'%s'"),re);
// 	return re;
// }
// void COrderPage::BuildInsertSQL(CString& strSQL,OrderDetail* item)
// {
// 	strSQL.Format(_T("INSERT INTO order_detail (order_head_id,check_id,menu_item_id,menu_item_name,product_price,is_discount,")
// 		_T("original_price,discount_id,actual_price,is_return_item,order_employee_id,order_employee_name,")
// 		_T("pos_device_id, pos_name, order_time, return_time, return_reason, unit,")
// 		_T("is_send, condiment_belong_item, quantity, eat_type, auth_id, auth_name,")
// 		_T("weight_entry_required, description, n_service_type, not_print, seat_num, discount_price,")
// 		_T("sales_amount) VALUES (%d,%d,%d,%s,%f,%d,")
// 		_T("%f,%d,%f,%d,%d,%s,")
// 		_T("%d,%s,now(),%s,%s,%s,")
// 		_T("%d,%d,%f,%d,%d,%s,")
// 		_T("%d,%s,%d,%d,%d,%f,%f)")
// 		,theApp.m_nOrderHeadid,item->n_checkID,item->item_id,FormatString(item->item_name),item->item_price,item->b_isfree
// 		,);
// }
void COrderPage::SetRsDetail(COrder_Detail& rsDetail,OrderDetail* item)
{
	rsDetail.m_order_head_id=theApp.m_nOrderHeadid;
	rsDetail.m_check_id=item->n_checkID;
	rsDetail.m_menu_item_id=item->item_id;
	rsDetail.m_menu_item_name=item->item_name;
	rsDetail.m_product_price=item->item_price;
	rsDetail.m_is_discount=item->b_isfree;
	//rsDetail.m_discount_price=
	rsDetail.m_discount_id=item->n_discount_type;
	rsDetail.m_actual_price=item->total_price;
	//rsDetail.m_is_return_item=
	rsDetail.m_order_employee_id=_wtol(theApp.m_strUserID);
	rsDetail.m_order_employee_name=theApp.m_strUserName;
	rsDetail.m_pos_device_id=theApp.m_nDeviceId;
	rsDetail.m_pos_name=theApp.m_strDeviceName;
	rsDetail.m_order_time=CTime::GetCurrentTime();
	rsDetail.m_unit=item->unit;
	//rsDetail.m_is_send=
	rsDetail.m_condiment_belong_item=item->n_belong_item;
	if (item->belongto&&item->n_belong_item>=0)
	{
		rsDetail.m_condiment_belong_item=item->belongto->order_id;
	}
	if (item->belongto&&item->n_belong_item<0)
	{//�ײ�
		rsDetail.m_condiment_belong_item=-item->belongto->order_id;
	}
	rsDetail.m_quantity=item->quantity;
	rsDetail.m_eat_type=item->n_eattype;
	rsDetail.m_auth_id=_wtol(item->authID);
	rsDetail.m_auth_name=item->authUser;
	rsDetail.m_weight_entry_required=item->weight_required;
	rsDetail.m_description=item->description;
	rsDetail.m_n_service_type=item->n_service_type;
	rsDetail.m_notprint=item->b_notprint;
	rsDetail.m_n_seat_num=item->n_seat_num;
	rsDetail.m_discount_price=item->discount_price;
	rsDetail.m_sales_amount=item->sales_amount;
	rsDetail.m_print_class=item->family_group;
	if (item->b_reprice)
	{
		rsDetail.m_original_price=item->orignal_price;
	}

	if (item->quantity<0)
	{//���˲�
		rsDetail.m_return_time=CTime::GetCurrentTime();
		rsDetail.m_return_reason=item->return_reason;
	}
}
void COrderPage::FormatTableInfo(JSONVALUE& root)
{
	root[_T("serial")]=theApp.m_nOrderHeadid;
	root[_T("tbl_name")]=theApp.m_strTblName;
	root[_T("emp_name")]=theApp.m_strUserName;
	if(!theApp.m_strChkName.IsEmpty())
		root[_T("chk_name")]=theApp.m_strChkName;
	root[_T("tbl_id")]=theApp.m_nTableId;
	root[_T("chk_num")]=theApp.m_nCheckNum;
	root[_T("gst_num")]=theApp.m_nGuests;
	CTime time=CTime::GetCurrentTime();
	root[_T("time")]=time.Format("%Y-%m-%d %H:%M");
}
/************************************************************************
* �������ܣ�ɾ������
* ���������order_id --order_detail_id
* ���������
* ����ֵ  ��
************************************************************************/
void COrderPage::DeletePay(long order_id)
{
	try{
	USES_CONVERSION;
	CString strSQL;
	//1.����actual_amount
	strSQL.Format(_T("select total,consume_id,wechat_id from payment where order_detail_id=\'%d\'"),order_id);
	CRecordset rs( &theDB);
	if(rs.Open( CRecordset::forwardOnly,strSQL))
	{
		int consume_id=0;
		TCHAR* wechat_id=NULL;
		double payed;
		if (!rs.IsEOF())
		{
			CDBVariant variant;
			CString strVal;
			rs.GetFieldValue(_T("total"),strVal);
			payed=_wtof(strVal);
			variant.m_lVal=0;
			rs.GetFieldValue(_T("consume_id"),variant);
			consume_id=variant.m_lVal;
			rs.GetFieldValue(_T("wechat_id"),strVal);
			if(!strVal.IsEmpty())
			{
				wechat_id=new TCHAR[strVal.GetLength()];
				wcscpy_s(wechat_id,strVal.GetLength(),(LPCTSTR)strVal);
			}
		}
		rs.Close();
		if(wechat_id!=NULL)
		{//΢��֧��
		 //�������˿������������⡣�˿�Ӧ��¼�̻����˿����ʵ�ֵ�����΢���˿��
			//AfxBeginThread(doReverseLoop1,(LPVOID)wechat_id);
		}
		//2.��Ա�����˿�
		if (consume_id!=0)
		{
			strSQL.Format(_T("select * from customer_consume where id=%d"),consume_id);
			if(rs.Open(CRecordset::forwardOnly,strSQL))
			{
				if(!rs.IsEOF())
				{
					CString card_id;
					rs.GetFieldValue(_T("card_id"),card_id);
					CDBVariant variant;
					variant.m_iVal=0;
					rs.GetFieldValue(_T("type"),variant);
					if (variant.m_iVal==2)
					{//web��Ա
						rs.GetFieldValue(_T("web_id"),variant);
						long web_id=variant.m_lVal;
						try{
							if (!theApp.m_strVipURL.IsEmpty())
							{
								CString ip_addr;
								ip_addr.Format(_T("/orgs/revoke_storedvaluecard//?source=agile&username=%s&user_id=%s&guid=%s&machine_id=%s")
									,URLEncode(theApp.m_strUserName),theApp.m_strUserID,theApp.m_strResId,URLEncode(theApp.m_strHostName));
								CInternetSession session;
								session.SetOption(INTERNET_OPTION_CONNECT_TIMEOUT, 1000 * 20);
								session.SetOption(INTERNET_OPTION_CONNECT_BACKOFF, 1000);
								session.SetOption(INTERNET_OPTION_CONNECT_RETRIES, 1);
								CHttpConnection* pConnection = session.GetHttpConnection(theApp.m_strVipURL,(INTERNET_PORT)theApp.m_nVipPort);
								CHttpFile* pFile = pConnection->OpenRequest(CHttpConnection::HTTP_VERB_GET,ip_addr); 
								pFile->SendRequest();
								DWORD dwRet;
								pFile->QueryInfoStatusCode(dwRet);
								if(dwRet == HTTP_STATUS_OK)
								{
									char buf[256]={0};
									pFile->ReadString((LPTSTR)buf,sizeof(buf)-1);
									pFile->Close();
									CString token=A2W(buf);
									token.Trim();
									CString szHeaders   = L"Content-Type: application/x-www-form-urlencoded;";
									CString strSend;
									strSend.Format(_T("csrfmiddlewaretoken=%s&log=%d"),token,web_id);
									int wcsLen0 = ::WideCharToMultiByte(CP_UTF8, NULL, strSend, strSend.GetLength(), NULL, 0, NULL, NULL);
									char* sz0 = new char[wcsLen0 + 1];
									memset(sz0,0,wcsLen0+1);
									::WideCharToMultiByte(CP_UTF8, NULL, strSend, strSend.GetLength(), sz0, wcsLen0,  NULL, NULL);
									sz0 [wcsLen0] = '\0';
									pFile = pConnection->OpenRequest(CHttpConnection::HTTP_VERB_POST,ip_addr);
									pFile->SendRequest(szHeaders,szHeaders.GetLength(),(LPVOID)sz0,wcsLen0);
									delete sz0;
									pFile->Close();
								}
								delete pFile;
							}
						}catch(...)
						{
						}
					}
					else
					{
						strSQL.Format(_T("update customer set amount = amount + %f,score = score - %f where card_id=%s ")
							,payed,payed,card_id);
						theDB.ExecuteSQL(strSQL);
					}
				}
			}
			rs.Close();
			strSQL.Format(_T("delete from customer_consume where id=%d;"),consume_id);
			theDB.ExecuteSQL(strSQL);
		}
	}
	//3.ɾ��payment���¼
	strSQL.Format(_T("delete from payment where order_detail_id=\'%d\';"),order_id);
	theDB.ExecuteSQL(strSQL);
	}catch(...)
	{
	}
}

/************************************************************************
* �������ܣ����²�Ʒ������Ϣ
* ���������diff -ʣ���Ʒ�����ı仯
* ���������
* ����ֵ  ��
************************************************************************/
void COrderPage::UpdateSoldoutInfo(OrderDetail* item,double diff)
{
	CString strSQL;
	if (item->bargain_stype==2&&item->quantity>0)
	{
		strSQL.Format(_T("UPDATE bargain_price_item SET bargain_num_cur=bargain_num_cur %+f WHERE bargain_item_number=%d AND bargain_stype=2;")
			,diff,item->item_id);
		theDB.ExecuteSQL(strSQL);
	}
}
