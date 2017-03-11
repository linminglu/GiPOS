// PayDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "POSClient.h"
#include "PayDlg.h"
#include "VoidReasonDlg.h"
#include "NumberInputDlg.h"
#include "OrderDlg.h"
#include "DiscountDlg.h"
#include "TicketsDlg.h"
#include "CustomerDlg.h"
#include "WeixinPayDlg.h"
#include "AliPayDlg.h"
#include "QfPayDlg.h"
#include "StringInputDlg.h"
#include "CustomerSearchDlg.h"
#include "CustomerSearchDlg2.h"
#include "FloorDlg.h"
#include "printer.h"
#include "WebDlg.h"
#include "SSLCon.h"
//#include "WebDlg2.h"
#include "MSGBoxDlg.h"
#include "EftMsgDlg.h"
#include "ManagerDlg.h"
#include "SecondScreen.h"
#include "TipsAddDlg.h"
#include <math.h>

// PayDlg �Ի���
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


typedef const char* (__stdcall *payfunc)(const char* cmd);
extern HINSTANCE hSQBDll;//��Ǯ�ɽӿ�

IMPLEMENT_DYNAMIC(PayDlg, COrderPage)

int PayDlg::CHECK_COUNT=0;
PayDlg::PayDlg(CWnd* pParent /*=NULL*/)
: COrderPage(PayDlg::IDD)
{
	//	m_bVoidState=FALSE;
	m_fEpsinon=0.01;
	m_bMemberPrice=FALSE;
	CLASS_LINES=8;
}

PayDlg::~PayDlg()
{
}

void PayDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_HINT, m_ctrlHint);
	DDX_Control(pDX, IDC_STATIC_LOG, m_logCtrl);
	DDX_Control(pDX, IDC_STATIC_TIME, m_timeCtrl);
	DDX_Control(pDX, IDC_STATIC_GUEST, m_guestCtrl);
	DDX_Control(pDX, IDC_STATIC_TABLE, m_tableCtrl);
	DDX_Control(pDX, IDC_STATIC_CHECK, m_checkCtrl);
	DDX_Control(pDX, IDC_STATIC_NUM, m_numCtrl);
	//DDX_Control(pDX, IDC_CSDEFTCTRL1, m_CsdEft);
}


BEGIN_MESSAGE_MAP(PayDlg, CDialog)
	//ON_BN_CLICKED(IDC_BUTTON_SAVE, &PayDlg::OnBnClickedSaveOrder)
	ON_BN_CLICKED(IDC_BUTTON_PRE, &PayDlg::OnBnClickedPrepage)
	//	ON_BN_CLICKED(IDC_BUTTON_CASH, &PayDlg::OnBnClickedCash)
	ON_COMMAND_RANGE(IDC_SLU_BUTTON,IDC_SLU_BUTTON+20,OnBnClickedPayment)
	ON_BN_CLICKED(IDC_BUTTON_UP, &PayDlg::OnBnClickedButtonUp)
	ON_BN_CLICKED(IDC_BUTTON_DOWN, &PayDlg::OnBnClickedButtonDown)
	ON_BN_CLICKED(IDC_BUTTON_OK, &PayDlg::OnBnClickedOK)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, &PayDlg::OnBnClickedButtonClear)
	ON_COMMAND_RANGE(IDC_BUTTON0,IDC_BUTTON9,OnNumBnClicked)
	ON_BN_CLICKED(IDC_BUTTON00, &PayDlg::OnBnClickedButton00)
	ON_BN_CLICKED(IDC_BUTTON10, &PayDlg::OnBnClickedButton10)
	ON_BN_CLICKED(IDC_BUTTON20, &PayDlg::OnBnClickedButton20)
	ON_BN_CLICKED(IDC_BUTTON50, &PayDlg::OnBnClickedButton50)
	ON_BN_CLICKED(IDC_BUTTON100, &PayDlg::OnBnClickedButton100)
	ON_BN_CLICKED(IDC_BUTTON_DOT, &PayDlg::OnBnClickedButtonDot)
	ON_BN_CLICKED(IDC_BUTTON_GUEST, &PayDlg::OnBnClickedGuest)
	ON_BN_CLICKED(IDC_BUTTON_SERVICE, &PayDlg::OnBnClickedService)
	ON_BN_CLICKED(IDC_BUTTON_DISCOUNT, &PayDlg::OnBnClickedDiscount)
	ON_BN_CLICKED(IDC_BUTTON_VOID, &PayDlg::OnBnClickedButtonVoid)
	ON_BN_CLICKED(IDC_BUTTON_FUNCTION, &PayDlg::OnBnClickedButtonFunction)
	ON_BN_CLICKED(IDC_BUTTON_CHKNAME, &PayDlg::OnBnClickedCheckName)
	ON_BN_CLICKED(IDC_BUTTON_PRINT, &PayDlg::OnBnClickedPrePrint)
	ON_BN_CLICKED(IDC_BUTTON_PRINTROUND, &PayDlg::OnBnClickedPrintRound)
	ON_BN_CLICKED(IDC_BUTTON_CUSNAME, &PayDlg::OnBnClickedCustomerName)
	ON_BN_CLICKED(IDC_BUTTON_INVOICE, &PayDlg::OnBnClickedButtonInvoice)
	ON_BN_CLICKED(IDC_BUTTON_TACHK,&PayDlg::OnBnClickedTakeOutChk)
	ON_BN_CLICKED(IDC_BUTTON_SELECTALL,&PayDlg::OnBnClickedSelectAll)
	ON_BN_CLICKED(IDC_BUTTON_MANAGEFUN,&PayDlg::OnBnClickedManagFunction)
	ON_BN_CLICKED(IDC_BUTTON_TAINFO,&PayDlg::OnBnClickedTakeOutInfo)
	ON_BN_CLICKED(IDC_BUTTON_VIPPRICE,&PayDlg::OnBnClickedMemberPrice)
	ON_BN_CLICKED(IDC_BUTTON_OPEN, &ManagerDlg::OnBnClickedOpenDrawer)
	ON_BN_CLICKED(IDC_BUTTON_ACTUALPAYED, &PayDlg::OnBnClickedActualPayed)
	ON_BN_CLICKED(IDC_BUTTON_SEPARATECHK,&PayDlg::OnBnClickedSeparateCheck)
	ON_COMMAND_RANGE(IDC_BUTTON_NEXTPAGE,IDC_BUTTON_NEXTPAGE+50,&CPosPage::OnNextPage)
	ON_WM_SIZE()
	ON_WM_CTLCOLOR()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()
// CLoginDlg ��Ϣ�������

bool CompareBySLU(const OrderDetail* item1, const OrderDetail* item2)
{
	return (item1->n_sortindex)<(item2->n_sortindex);
}
bool CompareByPrice(const OrderDetail* item1, const OrderDetail* item2)
{
	return (item1->total_price)>(item2->total_price);
}

BOOL PayDlg::OnInitDialog()
{
	CPosPage::InitDialog(_T("Picture\\pay.png"));

	if (m_strTmplate.GetLength()==0)
	{
		if(theApp.m_bQuickService)
			m_strTmplate=_T("Page\\IDD_4_QUICK_PAY.ini");
		else
			m_strTmplate=_T("Page\\IDD_4_PAY.ini");
	}
	m_btnCtrl.GenaratePage2(m_strTmplate,this);
	m_numFont.CreatePointFont(240,_T("Microsoft YaHei"));
	m_numCtrl.SetFont(&m_numFont);
	m_logCtrl.SetFont(&theApp.m_txtFont);
	m_checkCtrl.SetFont(&theApp.m_txtFont);
	m_tableCtrl.SetFont(&theApp.m_txtFont);
	m_guestCtrl.SetFont(&theApp.m_txtFont);
	m_timeCtrl.SetFont(&theApp.m_txtFont);
	m_ctrlHint.SetFont(&theApp.m_txtFont);
	m_TabCtrl.Create(TCS_DOWN|WS_CHILD|WS_VISIBLE,CRect(0,0,200,200),this,125);
	for(int i=0;i<MAX_CHECKS;i++)
	{
		m_checkDlg[i].Create(IDD_CHECK,&m_TabCtrl);	
		//m_checkDlg[i].m_bHideDesc=TRUE;
	}
	m_TabCtrl.AddPage(&m_checkDlg[0],_T("1"),NULL);
	m_pOrderList=&((CPOSClientApp*)AfxGetApp())->m_orderList;
	try{
		m_fEpsinon=1;
		for (int i=0;i<theApp.DECIMAL_PLACES;i++)
		{
			m_fEpsinon=m_fEpsinon/10;
		}
		m_fEpsinon=m_fEpsinon/2;
		//�������༭��û�����ã������ݿ��ʼ��
		CWnd* pCtrl=GetDlgItem(IDC_SLU_BUTTON+1);
		if (pCtrl==NULL)
		{
			int LINE_SIZE=4;
			int space_x=20;
			int space_y=8;
			CImage img;
			POINT topleft;
			topleft.x=400*CreatButton::m_nFullWidth/1024;
			topleft.y=135*CreatButton::m_nFullHeight/768;
			POINT anchor=topleft;
			SIZE buttonSize;
			buttonSize.cx=(580*CreatButton::m_nFullWidth/1024-space_x*(LINE_SIZE-1))/LINE_SIZE;
			buttonSize.cy=74*CreatButton::m_nFullHeight/768;
			m_bpButtonClass[0]=Gdiplus::Image::FromFile(_T("Picture\\class\\pay.png"));
			m_bpButtonClass[1]=Gdiplus::Image::FromFile(_T("Picture\\class\\pay_.png"));
			try{
				CRecordset rs( &theDB);
				CString strSQL;
				strSQL.Format(_T("SELECT * FROM tender_media"));
				if(rs.Open(CRecordset::snapshot,strSQL))
				{
					int count=0;
					while (!rs.IsEOF())
					{
						count++;
						rs.MoveNext();
					}
					if(count>8)
					{
						CLASS_LINES=10;
						LINE_SIZE=5;
						space_x=10;
						buttonSize.cx=(580*CreatButton::m_nFullWidth/1024-space_x*(LINE_SIZE-1))/LINE_SIZE;
					}
					if(count<=CLASS_LINES)
						m_uTotalPage=1;
					else
					{
						m_uTotalPage=ceil((count-2*(CLASS_LINES-1))/(CLASS_LINES-2.0))+2;
					}
					rs.MoveFirst();
					//��ҳ��������ҳ��ť
					CRoundButton2* upBtn;
					CRoundButton2* downBtn;
					if (m_uTotalPage>1)
					{
						CString str2;
						upBtn=new CRoundButton2;
						upBtn->Create(_T(""),WS_CHILD ,CRect(topleft,buttonSize),this,IDC_BUTTON_UP);
						upBtn->SetImage(_T("Picture\\bt_left.png"));
						m_btnCtrl.m_buttonList.push_back(upBtn);

						anchor.x=topleft.x+(buttonSize.cx+space_x)*(CLASS_LINES/2-1);
						anchor.y=topleft.y+(buttonSize.cy+space_y);
						downBtn=new CRoundButton2;
						downBtn->Create(_T(""),WS_CHILD ,CRect(anchor,buttonSize),this,IDC_BUTTON_DOWN);
						downBtn->SetImage(_T("Picture\\bt_right.png"));
						m_btnCtrl.m_buttonList.push_back(downBtn);
					}
					CDBVariant variant;
					CString strName;
					int pIndex=0;//��ҳ�ڵ�����
					m_uCurPage=0;
					while(!rs.IsEOF())
					{
						rs.GetFieldValue(_T("tender_media_id"),variant);
						rs.GetFieldValue(_T("tender_media_name"),strName);
						rs.MoveNext();
						int line_x=pIndex%LINE_SIZE;
						int line_y=pIndex/LINE_SIZE;
						anchor.x=topleft.x+(buttonSize.cx+space_x)*line_x;
						anchor.y=topleft.y+(buttonSize.cy+space_y)*line_y;
						CRoundButton2* pBtn=new CRoundButton2;
						pBtn->Create(strName,WS_CHILD ,CRect(anchor,buttonSize),this,IDC_SLU_BUTTON+variant.m_iVal);
						pBtn->SetImages(m_bpButtonClass[0],m_bpButtonClass[1],false);
						pBtn->SetTextColor(DEFALUT_TXT_COLOR);
						m_btnCtrl.m_buttonList.push_back(pBtn);
						m_classButtons.push_back(pBtn);
						//��һ�ε�λ��
						pIndex++;
						if(m_uTotalPage>1)
						{//�з�ҳ
							if (pIndex==CLASS_LINES-1)
							{
								//����������һҳ,������һҳ
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
		}
		else
		{//���ݾɰ�
			//ˢ�¸��ʽ��ť������
			try{
				CRecordset rs( &theDB);
				CString strSQL;
				strSQL.Format(_T("SELECT * FROM tender_media;"));
				if(rs.Open(CRecordset::forwardOnly,strSQL))
				{
					CDBVariant variant;
					CString strName;
					while(!rs.IsEOF())
					{
						rs.GetFieldValue(_T("tender_media_id"),variant);
						rs.GetFieldValue(_T("tender_media_name"),strName);
						if(variant.m_lVal<20)
						{
							CWnd* pCtrl=GetDlgItem(IDC_SLU_BUTTON+variant.m_iVal);
							if (pCtrl)
								pCtrl->SetWindowText(strName);
						}
						rs.MoveNext();
					}
					rs.Close();
				}
			}catch(...)
			{
			}
		}

	}catch(...)
	{
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
void PayDlg::OnSetActive()
{
	try{
		theLang.UpdatePage(this,_T("IDD_4_PAY"));
		//Ĭ�ϴ��ڴ����
		if(theApp.m_bDirty==FALSE)
			UpdateCheckData();
		else
		{
			LoadCheckData();
			if (m_pSecond)
			{
				UpdateSencondScreen(m_TabCtrl.GetActivePageIndex(),NULL);
			}
			theApp.m_bDirty=FALSE;
			OrderDlg::m_nSeat=0;
			OrderDlg::m_nQuantity=0;
		}
		int active=m_TabCtrl.GetActivePageIndex();
		theApp.m_cusDisplay.Display((double)m_checkDlg[active].m_fDebt,2);
		//������Ϣ
		m_bMemberPrice=FALSE;
		OrderDlg::UpdateInfo(this);
		m_strNum.Empty();
		UpdateNumber(m_strNum);

		CPosPage::OnSetActive();
	}
	catch(...)
	{
		LOG4CPLUS_ERROR(log_pos,"Catch Exception GetLastError="<<GetLastError());
	}
}
void PayDlg::OnSize(UINT nType, int cx, int cy)
{
	CPosPage::OnSize(nType, cx, cy);
	cx=CreatButton::m_nFullWidth;
	cy=CreatButton::m_nFullHeight;
	int width=(int)(cx*0.4);
	int height=(int)(cy*0.04);
	if (m_logCtrl.m_hWnd)
	{
		m_numCtrl.MoveWindow(420*cx/1024,60*cy/768,(int)(cx*0.4),100*cy/768);
		m_numCtrl.GetWindowRect(&mRectNum);    
		ScreenToClient(&mRectNum);

		m_ctrlHint.MoveWindow(60*cx/1024,35,250*cx/1024,height);
		m_ctrlHint.GetWindowRect(&mRectHint);    
		ScreenToClient(&mRectHint);

		int line_y1=65*cy/768;
		height=25*cy/768;
		int line_y2=line_y1+height;
		m_logCtrl.MoveWindow(25*cx/1024,line_y1,95,height);
		m_checkCtrl.MoveWindow(140*cx/1024,line_y1,220*cx/1024,height);
		m_tableCtrl.MoveWindow(25*cx/1024,line_y2,115*cx/1024,height);
		m_guestCtrl.MoveWindow(140*cx/1024,line_y2,115*cx/1024,height);
		m_timeCtrl.MoveWindow(245*cx/1024,line_y2,95*cx/1024,height);
		m_TabCtrl.MoveWindow(21*cx/1024,120*cy/768,330*cx/1024,(int)(cy*0.73));
	}
}
/************************************************************************
* �������ܣ���ʾ���ఴť�ĵ�ǰҳ
* ���������
* ���������
* ����ֵ  ��
************************************************************************/
void PayDlg::ShowClassPage()
{
	try{
		for(int i=0;i<m_classButtons.size();i++)
		{
			m_classButtons[i]->ShowWindow(SW_HIDE);
		}
		for (int i=m_uCurPage*CLASS_LINES;i<(m_uCurPage+1)*CLASS_LINES&&i<m_classButtons.size();i++)
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
* �������ܣ�������ʾ��ҳ
* ���������
* ���������
* ����ֵ  ��
************************************************************************/
void PayDlg::OnBnClickedButtonUp()
{
	if(m_uCurPage>0)
		m_uCurPage--;
	else
		return;
	ShowClassPage();
}
void PayDlg::OnBnClickedButtonDown()
{
	if(m_uCurPage<m_uTotalPage-1)
		m_uCurPage++;
	else
		return;
	ShowClassPage();
}
/************************************************************************
* �������ܣ���ɵ㵥
* ���������
* ���������
* ����ֵ  ��
************************************************************************/
// void PayDlg::OnBnClickedSaveOrder()
// {
// 	try{
// 		OrderDlg::SaveOrderToDB(m_pOrderList,&m_checkDlg);
// 		CPOSClientApp* pApp=(CPOSClientApp*)AfxGetApp();
// 		CString strSQL;
// 		strSQL.Format(_T("CALL flush_order(%d,%d);"),pApp->m_nOrderHeadid,pApp->m_nTableId);
// 		theDB.ExecuteSQL(strSQL);
// 		//�ͷ���
// 		if(theApp.m_bQuickService)
// 			FloorDlg::ReleaseLock(theApp.m_nOrderHeadid);
// 		else
// 			FloorDlg::ReleaseLock(theApp.m_nTableId);
// 		theApp.m_pMain->SetActivePage(DLG_LOGIN);
// 	}
// 	catch(CDBException* e)
// 	{
// 		LOG4CPLUS_ERROR(log_pos,(LPCTSTR)e->m_strError);
// 		AfxMessageBox(e->m_strError,MB_ICONEXCLAMATION);
// 		e->Delete();
// 		return;
// 	}
// 	catch(...)
// 	{
// 		LOG4CPLUS_ERROR(log_pos,"Catch Exception GetLastError="<<GetLastError());
// 	}
// }
/************************************************************************
* �������ܣ�ǰҳ
* ���������
* ���������
* ����ֵ  ��
************************************************************************/
void PayDlg::OnBnClickedPrepage()
{
	try{
		CPOSClientApp* pApp=(CPOSClientApp*)AfxGetApp();
		pApp->m_nActiveCheck=m_TabCtrl.GetActivePageIndex();
		int nPage=DLG_ORDER;
		if(theApp.m_bQuickOnce)
			nPage=DLG_QUICK_ORDER;
		OrderDlg* pOrder=(OrderDlg*)pApp->m_pMain->GetPage(nPage);
		//���·���Ѻ��Ѹ����
		for (int i=0;i<MAX_CHECKS;i++)
		{
			pOrder->m_checkDlg[i].m_fPayed=m_checkDlg[i].m_fPayed;
			pOrder->m_checkDlg[i].m_nStatus=m_checkDlg[i].m_nStatus;
		}
		pApp->m_bDirty=3;
		pApp->m_pMain->SetActivePage(nPage);
	}
	catch(...)
	{
		LOG4CPLUS_ERROR(log_pos,"Catch Exception GetLastError="<<GetLastError());
	}
}
/************************************************************************
* �������ܣ�������
* ���������
* ���������
* ����ֵ  ��
************************************************************************/
void PayDlg::OnBnClickedButtonFunction()
{
	try
	{
		CPOSClientApp* pApp=(CPOSClientApp*)AfxGetApp();
		if (pApp->m_bRefund)
		{
			return;
		}
		//�����˵�״̬
		for (int i=0;i<MAX_CHECKS;i++)
		{
			pApp->m_nCheckStatus[i]=m_checkDlg[i].m_nStatus;
		}
		pApp->m_pMain->SetActivePage(DLG_FUNCTION);
	}
	catch(...)
	{
		LOG4CPLUS_ERROR(log_pos,"Catch Exception GetLastError="<<GetLastError());
	}
}
void PayDlg::OnBnClickedManagFunction()
{
	try
	{
		CString userid;
		int auth=OrderDlg::RequeastAuth(userid,_T("manager_privilege"));
		if(auth!=0)
			return;
		theApp.m_pMain->SetActivePage(DLG_MANAGER);
	}
	catch(...)
	{
		LOG4CPLUS_ERROR(log_pos,"Catch Exception GetLastError="<<GetLastError());
	}
}
/************************************************************************
* �������ܣ��ж��Ƿ�ﵽע������
* ���������
* ���������
* ����ֵ  ��
************************************************************************/
BOOL PayDlg::IsRegLimit()
{
	if (m_bNotReg)
	{
		POSMessageBox(IDS_NOTREG);
		CHECK_COUNT++;
		if (CHECK_COUNT>10)
			return TRUE;
		CString strSQL;
		CRecordset rs(&theDB);
		strSQL.Format(_T("SELECT (SELECT COUNT(order_head_id) FROM history_order_head WHERE date(order_start_time)=date(now()))") );
		rs.Open( CRecordset::forwardOnly,strSQL);
		if (!rs.IsEOF()) 
		{
			rs.GetFieldValue((short)0,strSQL);
			int count=_wtoi(strSQL);
			if (count>=10)
				return TRUE;
		}
		rs.Close();
	}
	return FALSE;
}
/************************************************************************
* �������ܣ��ж��Ƿ�ﵽ������ѣ�û�������
* ���������
* ���������
* ����ֵ  ��TRUE ��������жϳɹ�
			FALSE �������������ȡ
************************************************************************/
BOOL PayDlg::CheckCosumeLimit()
{
	if(theApp.m_nLimitType>0&&(!theApp.m_bRefund))
	{
		//��������һ�ŵ�������������
		int unpayed=0;
		double table_total_amount=0;
		for(int i=0;i<m_TabCtrl.GetPageCount();i++)
		{
			if((double)m_checkDlg[i].m_fDebt>0.01)
			{
				unpayed++;
				table_total_amount+=m_checkDlg[i].m_fSubtotal+m_checkDlg[i].m_fService+m_checkDlg[i].m_fDiscount+m_checkDlg[i].m_fTax;
			}
			else
			{
				table_total_amount+=m_checkDlg[i].m_fPayed;
			}
		}
		if (unpayed==1)
		{
			double limit_total=0;
			if (theApp.m_nLimitType==2)
			{//�˾��������
				limit_total=theApp.m_fLimitAmount*theApp.m_nGuests;
			}
			else if (theApp.m_nLimitType==1)
			{//�����������
				limit_total=theApp.m_fLimitAmount;
			}
			if (table_total_amount<limit_total)
			{//�����������
				CString msg,str2;
				BOOL bAdd=TRUE;
				theLang.LoadString(str2,IDS_CONSUMELIMIT);
				msg.Format(str2,limit_total);
				if (macrosInt[_T("FORCE_MINLIMIT")]==1)
				{//ǿ���������
					if(POSMessageBox(msg,MB_YESNO)==IDCANCEL)
						return FALSE;
				}
				else
				{
					if(POSMessageBox(msg,MB_YESNO)==IDCANCEL)
						bAdd=FALSE;
				}
				if (bAdd)
				{
					int active=m_TabCtrl.GetActivePageIndex();
					double balance=limit_total-table_total_amount;
					//��˰��ʱ��Ҫ����
					if(CMainSheet::m_iStaticsInfo&0x08)
					{//˰��
						if(theApp.m_bTaxGST)
						{//�������˰
							balance=100*balance/(theApp.m_dTaxRate+100);
						}
					}
					OrderDetail* service=new OrderDetail;
					memset(service,0,sizeof(OrderDetail));
					service->n_checkID=active+1;
					service->item_id=ITEM_ID_SERVICE;
					service->item_price=balance;
					service->total_price=balance;
					service->noDiscount=TRUE;
					theLang.LoadString(str2,IDS_MINIADJUST);
					wcsncpy_s(service->item_name,str2,63);
					m_pOrderList->AddTail(service);
					m_checkDlg[active].AddOrderItem(service);
				}
			}
		}
	}
	return TRUE;
}
/************************************************************************
* �������ܣ�������̨��ת
* ���������bForce --ǿ����̨
* ���������
* ����ֵ  ���Ƿ���̨�ɹ�
************************************************************************/
BOOL PayDlg::CleanTable(BOOL bForce)
{
	CString strSQL;
	//�����еĵ�������ƶ���history��
	for(int i=0;i<m_TabCtrl.GetPageCount();i++)
	{
		if(abs(m_checkDlg[i].m_fDebt)>m_fEpsinon&&m_checkDlg[i].m_nStatus==0)
		{//��δ��ĵ�
			return FALSE;
		}
	}
	LOG4CPLUS_INFO(log_pos,"PayDlg::CleanTable close check "<<theApp.m_nOrderHeadid);
	m_strTAInfo.Empty();
	if(bForce||theApp.m_bQuickService||theApp.m_bRefund||macrosInt[_T("NOT_CLEAN_TABLE")]==0)
	{
		strSQL.Format(_T("CALL cut_items(%d,%d);"),theApp.m_nOrderHeadid,theApp.m_nTableId);
		theDB.ExecuteSQL(strSQL);
	}
	if(!bForce)
	{
		if (macrosInt[_T("NOT_CLEAN_TABLE")]==1)
		{
			strSQL.Format(_T("UPDATE tables SET table_status=4 WHERE table_id=%d"),theApp.m_nTableId);
			theDB.ExecuteSQL(strSQL);
		}
	}

	theApp.m_cusDisplay.ShowRollingText(_T("Thank You!"));
	if(theApp.m_VCR.IsOpen())
	{
		CString strLine;
		strLine.Format(_T("CLOSE CHECK %d\n"),theApp.m_nOrderHeadid);
		theApp.m_VCR.Print(strLine);
	}
	if(m_pSecond)
	{
		m_pSecond->HideDetail();
	}
	if(theApp.m_bQuickService)
	{
		//�ͷ���
		FloorDlg::ReleaseLock(theApp.m_nOrderHeadid);
		//��յ�ǰ��
		while(!m_pOrderList->IsEmpty())
		{
			OrderDetail* item=m_pOrderList->GetTail();
			m_pOrderList->RemoveTail();
			delete item;
		}
		OrderDlg::EmptyCheck();
		OrderDlg* pOrder=(OrderDlg*)theApp.m_pMain->GetPage(DLG_ORDER);
		if(pOrder)
			pOrder->m_checkDlg[0].m_fPayed=0;
		if(theApp.m_bQuickOnce)
		{
			theApp.ClearQuickOnce();
			theApp.m_pMain->SetActivePage(DLG_FLOOR);
		}
		else
		{
			if(macrosInt[_T("EXIT_AFTER_PAY")]==2)
				theApp.m_pMain->SetActivePage(DLG_LOGIN);
			else
				theApp.m_pMain->SetActivePage(DLG_ORDER);
		}
	}
	else
	{
		//�ͷ���
		FloorDlg::ReleaseLock(theApp.m_nTableId);
		if(macrosInt[_T("EXIT_AFTER_PAY")]==1)
			theApp.m_pMain->SetActivePage(DLG_FLOOR);
		else
			theApp.m_pMain->SetActivePage(DLG_LOGIN);
	}
	return TRUE;
}
/************************************************************************
* �������ܣ����ʽ
* ���������
* ���������
* ����ֵ  ��
************************************************************************/
void PayDlg::OnBnClickedPayment(UINT uID)
{
	try
	{
		int active=m_TabCtrl.GetActivePageIndex();
		if (m_checkDlg[active].m_nStatus==1)
		{
			return;
		}
		CPOSClientApp* pApp=(CPOSClientApp*)AfxGetApp();
		if (theApp.m_bQuickService)
		{
			if (m_pOrderList->IsEmpty())
			{
				POSMessageBox(IDS_NOPAYMENT);
				return;
			}
		}
		if(IsRegLimit())
			return;
		int payment_id=uID-IDC_SLU_BUTTON;
		LOG4CPLUS_INFO(log_pos,"PayDlg::OnBnClickedPayment uID="<<payment_id);
		OpenDatabase();
		CRecordset rs( &theDB);
		CString strSQL,str2;
		CString strReamrk=_T("");
		CString strCardId;
		double fPayed=0;
		BOOL bPaidfull=TRUE;//�Ƿ�����
		BOOL bAddTips=FALSE;//�Ƿ�֧��С��
		int maxAamout=0;//���������ֵ
		long consume_id=0;
		long ticket_id=0;
		CString wechat_id;
		OrderDetail* payinfo=new OrderDetail;
		memset(payinfo,0,sizeof(OrderDetail));
		payinfo->item_id=ITEM_ID_PAYINFO;
		payinfo->n_checkID=active+1;
		CString tender_media_name;
		CString strchange=L"";
		if(CheckCosumeLimit()==FALSE)
			return;
		//������ʾ�˿�
		theApp.m_cusDisplay.Display((double)m_checkDlg[active].m_fDebt,2);
		//�޸ĵ���
		if (theApp.m_bQuickService&&theApp.m_bInputChkName&&theApp.m_strChkName.IsEmpty())
		{
			if(SetCheckName(NULL)==FALSE)
				return;
		}

		strSQL.Format(_T("SELECT * FROM tender_media WHERE tender_media_id=%d"),payment_id);
		rs.Open(CRecordset::forwardOnly,strSQL);
		if (rs.IsEOF())//δ���ø��ʽ
			return;

		CDBVariant variant;
		variant.m_iVal=0;
		rs.GetFieldValue(_T("privilege"), variant);
		if (variant.m_lVal!=0)
		{//��ҪȨ��
			CString userid;
			int auth=OrderDlg::RequeastAuth(userid,_T("payment"),variant.m_lVal);
			if(auth!=0)
				return;
		}
		//��������
		rs.GetFieldValue(_T("tender_media_name"),tender_media_name);
		//�Ƿ�����
		variant.m_boolVal=TRUE;
		rs.GetFieldValue(_T("paid_full"),variant);
		bPaidfull=variant.m_boolVal;
		variant.m_lVal=0;
		rs.GetFieldValue(_T("halo_limits_amount"),variant);
		maxAamout=variant.m_lVal;
		variant.m_boolVal=FALSE;
		rs.GetFieldValue(_T("declare_tips_paid"),variant);
		bAddTips=variant.m_boolVal;

		variant.m_lVal=0;
		rs.GetFieldValue(_T("halo"),variant);
		int pay_type=variant.m_lVal;
		if (theApp.m_bRefund&&pay_type!=0&&pay_type!=5)
		{//����ĸ��ʽ�������˿�
			POSMessageBox(IDS_REFUNDHINT);
			return;
		}
		switch(pay_type)
		{// ֧������
			//case 1://��Ա��
			//case 2://����(����)
		case 3://����ȯ
			{
				TicketsDlg dlg;
				dlg.pParentWnd=this;
				//dlg.m_nCheckID=active+1;
				dlg.m_fTax=m_checkDlg[active].m_fTax;
				if(dlg.DoModal()==IDCANCEL)
					return;
				ticket_id=dlg.selectedItem.id;
				fPayed=dlg.selectedItem.amount;
				if(dlg.selectedItem.display_name.GetLength()!=0)
					tender_media_name=dlg.selectedItem.display_name;
				else
					tender_media_name=dlg.selectedItem.name;
				break;
			}
		case 4://web��Ա
			{
				if(m_bTrainingMode){
					POSMessageBox(IDS_TRAINMODE);
					break;
				}
				if (!theApp.m_strVipURL.IsEmpty())
				{
					CustomerSearchDlg dlg;
					dlg.server=theApp.m_strVipURL;
					dlg.port=theApp.m_nVipPort;
					if(dlg.DoModal()==IDCANCEL)
						return;
					strCardId=dlg.m_strCardId;
					CCustomerDlg customDlg;
					customDlg.server=dlg.server;
					customDlg.port=dlg.port;
					customDlg.m_strCradId=strCardId;
					customDlg.m_strName=dlg.m_strName;
					customDlg.m_dConsume=m_checkDlg[active].m_fDebt-m_checkDlg[active].m_fMolin;
					customDlg.toDisc=m_checkDlg[active].GetSubtotalToDiscount();
					customDlg.toDisc+=m_checkDlg[active].m_fTax;//˰ҲҪ����
					if(customDlg.DoModal()==IDCANCEL)
						return;
					double discount=customDlg.m_dDiscount;
					if (discount>0.01||abs(customDlg.m_dConsume)<=0.001)
					{//�����Ա�����۽��,���ֿ�����Ϊ0ҲҪ��ʾ
						if(customDlg.m_dDiscName>0.001)
						{//����˰�ʵ��ۿ�
							discount-=m_checkDlg[active].m_fTax*(1-customDlg.m_dDiscName);
						}
						OrderDetail* item=new OrderDetail;
						memset(item,0,sizeof(OrderDetail));
						item->total_price=-discount;
						item->item_id=ITEM_ID_DISCOUNT;
						item->n_checkID=active+1;
						theLang.LoadString(str2,IDS_DISCOUNT);
						if(customDlg.m_dDiscName>0.001)
							str2.AppendFormat(_T(" %g"),customDlg.m_dDiscName);
						if(macrosInt[_T("PRINT_WEBVIPID")]!=0)
						{
							CString str3;
							theLang.LoadString(IDS_CARDNO,str3);
							str2.AppendFormat(_T("  %s%s"),str3,customDlg.m_strCradId);
						}
						wcsncpy_s(item->item_name,str2,63);
						m_pOrderList->AddTail(item);
						if (customDlg.m_dConsume<=0)
							m_checkDlg[active].AddOrderItem(item,TRUE);
						else
							m_checkDlg[active].AddOrderItem(item,FALSE);
					}
					if (customDlg.m_dConsume<=0&&m_checkDlg[active].m_fDebt>m_fEpsinon)
						return;//�ۿۿ�
					fPayed=customDlg.m_dConsume;
					consume_id=customDlg.m_nConsume_id;
				}
				break;
			}
		case 6://΢��֧��
			{
				if(m_bTrainingMode){
					POSMessageBox(IDS_TRAINMODE);
					break;
				}
				CWeixinPayDlg dlg;
				dlg.total_fee=m_checkDlg[active].m_fDebt*100+0.5;//��������
				if(dlg.DoModal()==IDCANCEL)
					return;
				wechat_id=dlg.m_wxTransactionID;
				fPayed=m_checkDlg[active].m_fDebt;
				break;
			}
		case 7://Ǯ��΢��
			{
				if(m_bTrainingMode){
					POSMessageBox(IDS_TRAINMODE);
					break;
				}
				CQfPayDlg dlg;
				dlg.total_fee=m_checkDlg[active].m_fDebt*100+0.5;//��������
				if(dlg.DoModal()==IDCANCEL)
					return;
				wechat_id=dlg.m_wxTransactionID;
				fPayed=m_checkDlg[active].m_fDebt;
				break;
			}
		case 8://Ǯ��֧����
			{
				if(m_bTrainingMode){
					POSMessageBox(IDS_TRAINMODE);
					break;
				}
				CQfPayDlg dlg;
				dlg.m_nType=1;
				dlg.total_fee=m_checkDlg[active].m_fDebt*100+0.5;//��������
				if(dlg.DoModal()==IDCANCEL)
					return;
				wechat_id=dlg.m_wxTransactionID;
				fPayed=m_checkDlg[active].m_fDebt;
				break;
			}
		case 9:
			{//֧�����ڱ�
				if(m_bTrainingMode){
					POSMessageBox(IDS_TRAINMODE);
					break;
				}
				CAliPayDlg dlg;
				dlg.total_amount=m_checkDlg[active].m_fDebt;
				if(dlg.DoModal()==IDCANCEL)
					return;
				wechat_id=dlg.m_wxTransactionID;
				fPayed=m_checkDlg[active].m_fDebt;
				break;
			}
	//��Ǯ��(΢��/֧����)
// 			{
// 				if (theApp.m_bQuickService&&theApp.m_nOrderHeadid==0)
// 				{
// 					if(OrderDlg::SaveOrderHead()==FALSE)
// 						return;
// 				}
// 				payfunc pf=(payfunc)GetProcAddress(hSQBDll,"_payUI@4");
// 				if (pf)
// 				{
// 					CString pay_request;
// 					pay_request.AppendFormat(_T("%d"),theApp.m_nOrderHeadid);
// 					CString subject=theApp.m_strResName;
// 					subject.Replace('&',' ');
// 					pay_request.AppendFormat(_T("&%s"),subject);
// 					pay_request.AppendFormat(_T("&%s&&"),theApp.m_strUserID);
// 
// 					int fee=m_checkDlg[active].m_fDebt*100+0.5;//��������
// 					pay_request.AppendFormat(_T("&%d&&&"),fee);
// 					//תΪUTF-8
// 					int wcsLen0 = ::WideCharToMultiByte(CP_UTF8, NULL, pay_request, pay_request.GetLength(), NULL, 0, NULL, NULL);
// 					char* sz0 = new char[wcsLen0 + 1];
// 					memset(sz0,0,wcsLen0+1);
// 					::WideCharToMultiByte(CP_UTF8, NULL, pay_request, -1, sz0, wcsLen0,  NULL, NULL);
// 					sz0 [wcsLen0] = '\0';
// 					string ret = (*pf)(sz0);
// 					delete sz0;
// 					if(ret.find("Pay Success")==0)
// 					{//֧���ɹ�
// 						fPayed=m_checkDlg[active].m_fDebt;
// 					}
// 					else
// 						return;
// 					break;
// 				}
// 				else
// 					return;
// 			}
		default:
			{
				if (theApp.m_bRefund)
				{
					fPayed=m_checkDlg[active].m_fDebt;
					theApp.m_bRefund=FALSE;
					CString msg,str2;
					theLang.LoadString(str2,IDS_REFUNDTOTAL);
					msg.Format(_T("%s:%0.2f"),str2,-fPayed);
					POSMessageBox(msg);
				}
				else
				{
					if(!m_strNum.IsEmpty())
					{//ֻ�п��ٽ��ʲ��õ���
						fPayed=_wtof(m_strNum);
					}
					else
					{//��Ҫȷ��������
						NumberInputDlg dlg;
						CString str2;
						theLang.LoadString(IDS_INPUTAMOUNT,str2);
						dlg.m_strHint.Format(_T("%s: %s"),tender_media_name,str2);
						if(dlg.DoModal()!=IDOK)
							return;
						if (dlg.m_strNum.GetLength()==0)
							fPayed=m_checkDlg[active].m_fDebt;
						else
							fPayed=_wtof(dlg.m_strNum);
					}
					//�����������ֵ
					if(maxAamout>0&&fPayed>=maxAamout)
					{
						CString hint,str2;
						theLang.LoadString(str2,IDS_AMOUNTHINT);
						hint.Format(str2,fPayed);
						if(POSMessageBox(hint,MB_YESNO)!=IDOK)
							return;
					}
			 }
			}
		}
		m_strNum.Empty();
		UpdateNumber(m_strNum);
		if (pay_type==5)
		{//EFTPOS
			CEftMsgDlg dlg;
			dlg.fPayed=fPayed;
			if(dlg.DoModal()!=IDOK)
			{
				return;//ˢ��ʧ�ܻ�ʱ
			}
		}
		//PAX�ӿ�

		//��Ǯ��
		variant.m_boolVal=FALSE;
		rs.GetFieldValue(_T("open_drawer"),variant);
		if(theApp.m_prePrinter.nDeviceType!=-1&&variant.m_boolVal&&m_bTrainingMode==FALSE)
		{
			theApp.OpenDrawer();
		}
		//��Ҫ���뱸ע��Ϣ
		variant.m_boolVal=FALSE;
		rs.GetFieldValue(_T("reference_required"),variant);
		if (variant.m_boolVal)
		{
			StringInputDlg dlg;
			theLang.LoadString(dlg.m_strTitle,IDS_INPUTCOMMENT);
			if(dlg.DoModal()==IDOK)
			{
				strReamrk=dlg.m_strInput;
			}
		}
		rs.Close();

		double actualPaid=0;//ʵ�ս����۳�����
		actualPaid=fPayed;
		double fChange=fPayed-m_checkDlg[active].m_fDebt;
		double fTips=0;
		if(fChange>=0.01)
		{
			if(bAddTips)
			{//��ȡС��
				if(bPaidfull)
				{//�ֽ����㣬�ֶ�����С��. 
					TipsAddDlg tipDlg;
					tipDlg.m_fTotal=m_checkDlg[active].m_fDebt;
					tipDlg.m_fPayed=fPayed;
					if(tipDlg.DoModal()==IDCANCEL)
						return;
					//���¼�������
					fChange=tipDlg.m_fChange;
					fTips=tipDlg.m_fTips;

					OrderDetail* tipsinfo=new OrderDetail;
					memset(tipsinfo,0,sizeof(OrderDetail));
					tipsinfo->item_id=ITEM_ID_TIPS;
					tipsinfo->n_checkID=active+1;
					tipsinfo->n_discount_type=payment_id;
					wcsncpy_s(tipsinfo->item_name,_T("Tips"),63);
					tipsinfo->total_price=fTips;
					tipsinfo->item_price=fTips;
					m_pOrderList->AddTail(tipsinfo);

					if(fChange>=0.01)
					{
						CString str2;
						theLang.LoadString(str2,IDS_CHANGE);
						strchange.Format(_T("%s:")+theApp.m_decPlace,str2,fChange);
						UpdateNumber(strchange);
						pApp->m_cusDisplay.Display(fChange,4);
					}
					fPayed=m_checkDlg[active].m_fDebt;
					payinfo->item_price =fChange;
				}
				else
				{//���п������㣬ֱ�ӽ��ึ�Ľ����ΪС��
					OrderDetail* tipsinfo=new OrderDetail;
					memset(tipsinfo,0,sizeof(OrderDetail));
					tipsinfo->item_id=ITEM_ID_TIPS;
					tipsinfo->n_checkID=active+1;
					tipsinfo->n_discount_type=payment_id;
					wcsncpy_s(tipsinfo->item_name,_T("Tips"),63);
					tipsinfo->total_price=fChange;
					tipsinfo->item_price=fChange;
					fTips=fChange;
					m_pOrderList->AddTail(tipsinfo);
					//fPayed=m_checkDlg[active].m_fDebt;
				}
			}
			else
			{//��ʹ��С��
				if(bPaidfull)
				{//��Ҫ����
					CString str2;
					theLang.LoadString(str2,IDS_CHANGE);
					strchange.Format(_T("%s:")+theApp.m_decPlace,str2,fChange);
					UpdateNumber(strchange);
					pApp->m_cusDisplay.Display(fChange,4);
					fPayed=m_checkDlg[active].m_fDebt;
					payinfo->item_price =fChange;
				}
				//else ������
			}
		}
		m_checkDlg[active].AddPay(fPayed);
		payinfo->total_price=actualPaid;
		wcsncpy_s(payinfo->item_name,tender_media_name,63);
		m_pOrderList->AddTail(payinfo);
		m_checkDlg[active].AddOrderItem(payinfo,FALSE);
		if(theApp.m_VCR.IsOpen())
		{
			CString strLine;
			CCheckDlg::FormatString(payinfo,strLine,TRUE);
			strLine.Replace('|',' ');
			strLine.Append(_T("\n"));
			theApp.m_VCR.Print(strLine);
		}
		//�ڴ�֮ǰ��Ҫ����order_head����Ϊ�ֵ����ܻ�û������
		if (theApp.m_bQuickService&&theApp.m_nOrderHeadid==0)
		{
			if(OrderDlg::SaveOrderHead()==FALSE)
				return;
		}
		OrderDlg::SaveOrderToDB(m_pOrderList,&m_checkDlg);
		//�������ݿ��еĸ�����
		if(strCardId.GetLength()==0)
		{
			strSQL.Format(_T("UPDATE order_head SET actual_amount=\'%0.2f\' WHERE order_head_id=%d AND check_id=%d"),
				(double)m_checkDlg[active].m_fPayed,pApp->m_nOrderHeadid,active+1);
		}
		else
		{
			strSQL.Format(_T("UPDATE order_head SET actual_amount=\'%0.2f\',customer_name=\'%s\' WHERE order_head_id=%d AND check_id=%d"),
				(double)m_checkDlg[active].m_fPayed,strCardId,pApp->m_nOrderHeadid,active+1);
		}
		theDB.ExecuteSQL(strSQL);
		if(fTips>0.001)
		{
			strSQL.Format(_T("UPDATE order_head SET tips_amount=%f WHERE order_head_id=%d AND check_id=%d"),fTips,theApp.m_nOrderHeadid,active+1);
			theDB.ExecuteSQL(strSQL);
		}
		if(m_pSecond)
		{
			m_pSecond->ShowAmount((double)m_checkDlg[active].m_fPayed,(double)m_checkDlg[active].m_fDebt);
			//if (!strchange.IsEmpty())
				//m_pSecond->m_amount.SetWindowText(strchange);
		}
		//��¼���ʽ
		if (fabs(fPayed)>=0.0001)
		{
			if(theApp.m_strEndTime.IsEmpty())
			{
				strSQL.Format(_T("INSERT INTO payment(order_head_id,check_id,tender_media_id,total,employee_id,remark")
					_T(",payment_time,pos_device_id,rvc_center_id,order_detail_id,consume_id,ticket_id,wechat_id)")
					_T(" VALUES (\'%d\',\'%d\',\'%d\',\'%0.2f\',\'%s\',\'%s\',NOW(),\'%d\',%d,%d,%d,%d,\'%s\');"),
					pApp->m_nOrderHeadid,active+1,payment_id,fPayed,pApp->m_strUserID,
					strReamrk,pApp->m_nDeviceId,pApp->m_nRVC,payinfo->order_id,consume_id,ticket_id,wechat_id);
			}
			else
			{//�����ʵ�
				strSQL.Format(_T("INSERT INTO payment(order_head_id,check_id,tender_media_id,total,employee_id,remark")
					_T(",payment_time,pos_device_id,rvc_center_id,order_detail_id,consume_id,ticket_id)")
					_T(" VALUES (\'%d\',\'%d\',\'%d\',\'%0.2f\',\'%s\',\'%s\',\'%s\',\'%d\',%d,%d,%d,%d);"),
					pApp->m_nOrderHeadid,active+1,payment_id,fPayed,pApp->m_strUserID,strReamrk,
					theApp.m_strEndTime,pApp->m_nDeviceId,pApp->m_nRVC,payinfo->order_id,consume_id,ticket_id);
			}
			theDB.ExecuteSQL(strSQL);
		}
		if (m_checkDlg[active].m_fDebt<m_fEpsinon&&(!theApp.m_bRefund))
		{//�Զ��ͳ�
			if(theApp.m_bQuickService)
			{
				if(theApp.m_nAutoSendType>=1)
					OrderDlg::SendOrder(m_checkDlg,active+1);
			}else
			{
				if(theApp.m_nAutoSendType==2)
					OrderDlg::SendOrder(m_checkDlg,active+1);
			}
		}
		//���ʺ�õ��޷�����
		if (theApp.m_bRefund||m_checkDlg[active].m_fDebt<m_fEpsinon)
		{
			//ˢ��edit_time,�Ա�Զ�̱��������ϴ�
			if(!theApp.m_strEndTime.IsEmpty())
			{
				strSQL.Format(_T("UPDATE order_head SET edit_time=NOW() WHERE order_head_id=%d"),pApp->m_nOrderHeadid);
				theDB.ExecuteSQL(strSQL);
			}
			theApp.m_strEndTime.Empty();
			//��ӡ������Ϣ
			if(theApp.m_payPrinter.nDeviceType!=-1)
			{
				JSONVALUE root;
				//��ȡ��ӡ����
				strSQL.Format(_T("SELECT print_count FROM order_head WHERE order_head_id=%d AND check_id=%d")
					,pApp->m_nOrderHeadid,active+1);
				rs.Open( CRecordset::forwardOnly,strSQL);
				int nPrint=0;
				if (!rs.IsEOF())
				{
					CString cvalue;
					rs.GetFieldValue((short)0,cvalue);
					nPrint=_wtoi(cvalue)+1;
				}
				rs.Close();
				//��ȡ��Ʊ���
				strSQL.Format(_T("SELECT amount FROM invoices WHERE order_head_id=%d AND check_id=%d")
					,pApp->m_nOrderHeadid,active+1);
				rs.Open( CRecordset::forwardOnly,strSQL);
				if (!rs.IsEOF())
				{
					CString cvalue;
					rs.GetFieldValue((short)0,cvalue);
					root["invoice"]=_wtof(cvalue);
				}
				rs.Close();
				root["print_count"]=nPrint;
				FormatPrint(root,theApp.m_payPrinter,m_checkDlg[active],active);
				root["chk_total"]=(double)m_checkDlg[active].m_fPayed;
				if(macrosInt[_T("PRINTCHK_TWICE")]==2)
				{
					if(POSMessageBox(IDS_IFPRINTCHK,MB_YESNO)==IDOK)
					{
						root[_T("template")]=TEMPLATE_PAY;
						//���´�ӡ����
						strSQL.Format(_T("UPDATE order_head SET print_count=print_count+1 WHERE order_head_id=%d AND check_id=%d;")
							,pApp->m_nOrderHeadid,active+1);
						theDB.ExecuteSQL(strSQL);
						CPOSClientApp::PrintJson(root);
					}
				}
				else
				{
					root[_T("template")]=TEMPLATE_PAY;
					//���´�ӡ����
					strSQL.Format(_T("UPDATE order_head SET print_count=print_count+1 WHERE order_head_id=%d AND check_id=%d;")
						,pApp->m_nOrderHeadid,active+1);
					theDB.ExecuteSQL(strSQL);
					CPOSClientApp::PrintJson(root);
				}
				if (macrosInt[_T("PRINTCHK_TWICE")]==1)
				{//��ӡ2��
					if(POSMessageBox(IDS_PRINTTWICE,MB_YESNO)==IDOK)
					{
						strSQL.Format(_T("UPDATE order_head SET print_count=print_count+1 WHERE order_head_id=%d AND check_id=%d;")
							,pApp->m_nOrderHeadid,active+1);
						theDB.ExecuteSQL(strSQL);
						root["print_count"]=nPrint+1;
						CPOSClientApp::PrintJson(root);
					}
				}
			}
			//����Ĩ����
			if(abs(m_checkDlg[active].m_fMolin)>=m_fEpsinon)
			{
				theLang.LoadString(str2,IDS_MOLIN);
				strSQL.Format(_T("INSERT INTO order_detail(order_head_id,check_id,menu_item_id,menu_item_name,discount_id,")
					_T("actual_price,order_employee_id,order_employee_name,pos_device_id,pos_name,order_time)")
					_T("VALUES(%d,%d,-2,'%s',-1,%f,%s,'%s',%d,'%s',now())"),
					theApp.m_nOrderHeadid,active+1,str2,m_checkDlg[active].m_fMolin,theApp.m_strUserID,theApp.m_strUserName,theApp.m_nDeviceId,theApp.m_strDeviceName);
				theDB.ExecuteSQL(strSQL);
			}
			if(macrosInt[_T("NOT_CLEAN_TABLE")]==0||theApp.m_bRefund)
			{
				m_TabCtrl.DisablePage(active);
				m_TabCtrl.Invalidate();
				m_checkDlg[active].m_nStatus=1;
				strSQL.Format(_T("UPDATE order_head SET status=1,order_end_time=IF(order_end_time IS NULL, NOW(),order_end_time) WHERE order_head_id=%d AND check_id=%d;"),
					pApp->m_nOrderHeadid,active+1);
				theDB.ExecuteSQL(strSQL);
				//����ÿ���˵��ۿ�
				CListBoxEx* ptrDetailList=&m_checkDlg[active].m_ctrlDetailList;
				//�����һ�������ۿ�
				OrderDetail* pTmpDiscount=NULL;
				for(int  i=ptrDetailList->GetCount()-1;i>0;i--)
				{
					OrderDetail* item=(OrderDetail*)ptrDetailList->GetItemDataPtr(i);
					if (item!=NULL&&item->item_id==ITEM_ID_DISCOUNT)
					{
						if (item->discount_percent>0.001)
						{//�����͵������ۿ�
							pTmpDiscount=item;
							break;
						}
					}
				}
				//�Է��ϴ��۵Ĳ˼���discount_price
				for(int  i=0;i<ptrDetailList->GetCount();i++)
				{
					OrderDetail* item=(OrderDetail*)ptrDetailList->GetItemDataPtr(i);
					if (item==NULL||item->item_id<0)
						continue;
					double disc=0;
					if(pTmpDiscount&&pTmpDiscount->discount_percent>0.001&&item->n_discount_type>0)
					{//���¸ò˵��ۿ۽��
						disc=(pTmpDiscount->discount_percent*item->total_price)/100;
						strSQL.Format(_T("UPDATE order_detail SET discount_price=discount_price+%f WHERE order_detail_id=%d")
							,disc,item->order_id);
						theDB.ExecuteSQL(strSQL);
					}
					strSQL.Format(_T("SELECT discount_price FROM order_detail WHERE order_detail_id=%d"),item->order_id);
					rs.Open(CRecordset::forwardOnly,strSQL);
					variant.m_fltVal=0;
					rs.GetFieldValue(_T("discount_price"),variant);
					disc=variant.m_fltVal;
					rs.Close();
					//�������۶�,�ײͲ��޸�
					if (item->n_belong_item<0)
						continue;
					if (i+1<ptrDetailList->GetCount())
					{
						OrderDetail* item1=(OrderDetail*)ptrDetailList->GetItemDataPtr(i+1);
						if (item1->n_belong_item<0)
							continue;
					}
					strSQL.Format(_T("UPDATE order_detail SET sales_amount=%f WHERE order_detail_id=%d")
						,item->total_price-disc,item->order_id);
					theDB.ExecuteSQL(strSQL);
				}
			}
		}
		if (!strchange.IsEmpty())
		{
			TimeCounter dlg;
			dlg.m_strText=strchange;
			dlg.m_nCount=macrosInt[_T("PAYMENT_CHANGE_TIME")];
			dlg.DoModal();
		}
		CleanTable(FALSE);
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
* �������ܣ���ʽ����ӡ��Ϣ
* ���������
* ���������
* ����ֵ  ��
************************************************************************/
void PayDlg::FormatPrint(JSONVALUE& root,PrintDeviceInfo& printer,CCheckDlg& checkDlg,int active)
{
	JSONVALUE arrayItems;
	root[_T("chk_id")]=active+1;
	root[_T("head")]=theApp.m_strPrintHead;
	root[_T("tail")]=theApp.m_strPrintTail;
	if (theApp.m_bQuickService)
	{
		root[_T("kcms")]=1;
	}
	if (!m_strTAInfo.IsEmpty())
	{
		root[_T("tainfo")]=m_strTAInfo;
	}
	if (m_bNotReg)
	{
		CString str2;
		theLang.LoadString(str2,IDS_NOTREG);
		root[_T("reginfo")]=str2;
	}
	CPOSClientApp::FormatPrintDevice(root,printer);
	FormatTableInfo(root);
	root[_T("id")]=theApp.m_nOrderHeadid;//���ڴ�ӡ����
	CList <OrderDetail*> tempPayList,tmpDiscList,tmpServiceList;
	std::vector<OrderDetail*> tmpItemList;
	CListBoxEx* ptrDetailList=&checkDlg.m_ctrlDetailList;
	CString strSQL;
	CRecordset rs( &theDB);
	double fChange=0;
	for(int  i=0;i<ptrDetailList->GetCount();i++)
	{
		OrderDetail* item=(OrderDetail*)ptrDetailList->GetItemDataPtr(i);
		if (item->item_id==ITEM_ID_SENDINFO||item->b_notprint)
			continue;//����ӡ�µ�ʱ��
		if(item->item_id==ITEM_ID_PAYINFO)
		{
			tempPayList.AddTail(item);
			fChange+=item->item_price;
		}
		else if(item->item_id==ITEM_ID_DISCOUNT)
		{
			tmpDiscList.AddTail(item);
		}
		else if (item->item_id==ITEM_ID_SERVICE)
		{
			tmpServiceList.AddTail(item);
		}
		else
		{
			//����ӡ����Ϊ0��Ʒ
			if (macrosInt[_T("NOT_PRINT_FREEITEM")]==1)
			{
				if(item->item_price==0)
					continue;
			}
			if (macrosInt[_T("PAYMENT_ORDER")]==1||macrosInt[_T("PAYMENT_ORDER")]==3)
			{//����������
				if (item->n_belong_item>0)
				{
					OrderDetail* item1=(OrderDetail*)ptrDetailList->GetItemDataPtr(i-1);
					if(item1)
						item->n_sortindex=item1->n_sortindex;
				}
				strSQL.Format(_T("SELECT family_group FROM menu_item WHERE item_id=%d"),item->item_id);
				rs.Open( CRecordset::forwardOnly,strSQL);
				if (!rs.IsEOF())
				{
					CString strVal;
					rs.GetFieldValue((short)0,strVal);
					item->n_sortindex=_wtol(strVal);
				}
				rs.Close();
			}
			tmpItemList.push_back(item);
		}
	}
	if (macrosInt[_T("PAYMENT_ORDER")]==1)
	{
		sort(tmpItemList.begin(),tmpItemList.end(),CompareBySLU);
	}
	else if (macrosInt[_T("PAYMENT_ORDER")]==2)
	{
		sort(tmpItemList.begin(),tmpItemList.end(),CompareByPrice);
	}
	else if(macrosInt[_T("PAYMENT_ORDER")]==3)
	{
		sort(tmpItemList.begin(),tmpItemList.end(),CompareBySLU);
		//��ӡ����С��
		int last_class=-99;
		double subtotal=0;
		for (int i=0;i<tmpItemList.size();i++)
		{
			if (tmpItemList[i]->n_sortindex==last_class)
			{
				subtotal+=tmpItemList[i]->total_price;
				continue;
			}
			else
			{
				if(last_class!=-99)
				{//���������Ϣ
					OrderDetail* class_info=new OrderDetail;
					memset(class_info,0,sizeof(OrderDetail));
					class_info->item_id=ITEM_ID_SENDINFO;
					class_info->total_price=subtotal;
					strSQL.Format(_T("SELECT family_group_name FROM family_group WHERE family_group_id=%d")
						,last_class);
					rs.Open( CRecordset::forwardOnly,strSQL);
					if (!rs.IsEOF())
					{
						CString strVal,strTmp;
						rs.GetFieldValue((short)0,strVal);
						strTmp.Format(_T("----%s----"),strVal);
						wcsncpy_s(class_info->item_name,strTmp,63);
					}
					else
					{
						wcsncpy_s(class_info->item_name,_T("----OTHER----"),63);
					}
					rs.Close();
					tmpItemList.insert(tmpItemList.begin()+i,class_info);
					subtotal=0;
					i++;
				}
				last_class=tmpItemList[i]->n_sortindex;
				subtotal+=tmpItemList[i]->total_price;
			}
		}
		if (subtotal>0&&last_class!=-99)
		{
			OrderDetail* class_info=new OrderDetail;
			memset(class_info,0,sizeof(OrderDetail));
			class_info->item_id=ITEM_ID_SENDINFO;
			class_info->total_price=subtotal;
			strSQL.Format(_T("SELECT family_group_name FROM family_group WHERE family_group_id=%d")
				,last_class);
			rs.Open( CRecordset::forwardOnly,strSQL);
			if (!rs.IsEOF())
			{
				CString strVal,strTmp;
				rs.GetFieldValue((short)0,strVal);
				strTmp.Format(_T("----%s----"),strVal);
				wcsncpy_s(class_info->item_name,strTmp,63);
			}
			else
			{
				wcsncpy_s(class_info->item_name,_T("----OTHER----"),63);
			}
			rs.Close();
			tmpItemList.push_back(class_info);
		}
	}
	POSITION  pos;
	for(int i=0;i<tmpItemList.size();i++)
	{
		OrderDetail* item=tmpItemList[i];
		BOOL bFind=FALSE;
		if(macrosInt[_T("COMBINE_PAYITEM")]==1)
		{
			if (item->b_isfree==FALSE&&item->item_id>0)
			{
				for (int j=0;j<arrayItems.Size();j++)
				{//��unicodeתΪascii���ж�ʧ��������
					JSONVALUE jItem;
					arrayItems.At(j,jItem);
					int item_id=jItem[_T("id")].asInt();
					double price=jItem[_T("price")].asDouble();
					CString unit=jItem[_T("unit")].asCString();
					CString name=jItem[_T("name")].asCString();
					CString fname;
					FormatName(item,fname);
					CString unit2,name2;
					unit2.Format(_T("%s"),item->unit);
					name2.Format(_T("%s"),fname);
					if (item_id==item->item_id
						&&price==item->item_price&&name.Compare(name2)==0
						&&unit.Compare(unit2)==0)//��ͬ���
					{//�ҵ�һ����
						jItem[_T("num")]=jItem[_T("num")].asDouble()+item->quantity;
						jItem[_T("total")]=jItem[_T("total")].asDouble()+item->total_price;
						bFind=TRUE;
						arrayItems.SetAt(j,jItem);
						break;
					}
				}
			}
		}
		if(!bFind)
		{
			//��ζƷ�ϲ���ӡ
			int i=arrayItems.Size()-1;
			if (item->n_belong_item>0&&macrosInt[_T("COMBINE_CONDIMENT")]==1
				&&i>=0)
			{
				JSONVALUE jItem;
				arrayItems.At(i,jItem);
				CString desc=jItem[_T("desc")].asCString();
				desc.AppendFormat(_T(" %s"),item->item_name);
				jItem[_T("desc")]=desc;
				jItem[_T("total")]=jItem[_T("total")].asDouble()+item->total_price;
				arrayItems.SetAt(i,jItem);
			}
			else
			{
				JSONVALUE jsItem;
				if(OrderDetail2Json(item,jsItem))
					arrayItems.Push(jsItem);
			}
			
		}
		if (item->item_id==ITEM_ID_SENDINFO)
		{//new �ķ�����Ϣ
			delete item;
		}
	}
	if(macrosInt[_T("PRINT_VOID_PAY")]==1)
	{
		strSQL.Format(_T("SELECT * FROM order_detail WHERE order_head_id=%d  AND check_id=%d AND is_return_item=1 AND menu_item_id>0")
			,theApp.m_nOrderHeadid,active+1);
		CRecordset rs( &theDB);
		rs.Open( CRecordset::forwardOnly,strSQL);
		if(rs.GetRecordCount()>0)
		{
			OrderDetail class_info={0};
			class_info.item_id=ITEM_ID_SENDINFO;
			class_info.total_price=0;
			CString str1,str2;
			theLang.LoadString(IDS_VOID,str1);
			str2.Format(_T("----%s----"),str1);
			wcsncpy_s(class_info.item_name,str2,63);
			JSONVALUE jsItem;
			if(OrderDetail2Json(&class_info,jsItem))
				arrayItems.Push(jsItem);
		}
		while(!rs.IsEOF())
		{
			OrderDetail order={0};
			readOrderDetail(rs,&order);
			if(order.quantity>0)
				order.quantity*=-1;
			order.total_price=0;
			JSONVALUE jsItem;
			if(OrderDetail2Json(&order,jsItem))
				arrayItems.Push(jsItem);
			rs.MoveNext();
		}
	}


	if(macrosInt[_T("PRINT_DISCOUNT_SEPARATE")]==1)
	{
		JSONVALUE arrayDiscount;
		pos=tmpDiscList.GetHeadPosition();
		while(pos!= NULL)
		{
			JSONVALUE jsItem;
			OrderDetail* item=tmpDiscList.GetNext(pos);
			jsItem[_T("dis_name")]=(LPCTSTR)item->item_name;
			jsItem[_T("dis_val")]=item->total_price;
			arrayDiscount.Push(jsItem);
		}
		root[_T("discounts")]=arrayDiscount;

		JSONVALUE arrayService;
		pos=tmpServiceList.GetHeadPosition();
		while(pos!= NULL)
		{
			JSONVALUE jsItem;
			OrderDetail* item=tmpServiceList.GetNext(pos);
			jsItem[_T("srv_name")]=(LPCTSTR)item->item_name;
			jsItem[_T("srv_val")]=item->total_price;
			arrayService.Push(jsItem);
		}
		root[_T("services")]=arrayService;
	}
	else
	{//���ݾɰ棬����Ѻ��ۿ۸���Ʒһ���ӡ
		pos=tmpDiscList.GetHeadPosition();
		while(pos!= NULL)
		{
			JSONVALUE jsItem;
			OrderDetail* item=tmpDiscList.GetNext(pos);
			if(OrderDetail2Json(item,jsItem))
				arrayItems.Push(jsItem);
		}
		pos=tmpServiceList.GetHeadPosition();
		while(pos!= NULL)
		{
			JSONVALUE jsItem;
			OrderDetail* item=tmpServiceList.GetNext(pos);
			if(OrderDetail2Json(item,jsItem))
				arrayItems.Push(jsItem);
		}
	}
	root[_T("items")]=arrayItems;

	if(!tempPayList.IsEmpty())
	{
		JSONVALUE arrayPays;
		pos=tempPayList.GetHeadPosition();
		while(pos!= NULL)
		{
			JSONVALUE jsItem;
			OrderDetail* detail=tempPayList.GetNext(pos);
			jsItem[_T("pay_name")]=detail->item_name;
			jsItem[_T("pay_val")]=detail->total_price;
			CString strTmp;
			strTmp.Format(_T("%s:%0.2f"),detail->item_name,detail->total_price);
			jsItem[_T("name")]=(LPCTSTR)strTmp;
			arrayPays.Push(jsItem);
			if (macrosInt[_T("PRINT_VIPINFO")])
			{//���뿨��������Ϣ
				strSQL.Format(_T("SELECT * FROM customer_consume,payment ")
					_T("where order_detail_id=%d AND consume_id=id"),detail->order_id);
				CRecordset rs(&theDB);
				CString strVal,strName,str2;
				rs.Open(CRecordset::snapshot,strSQL);
				if (!rs.IsEOF())
				{
					JSONVALUE vipItem;
					rs.GetFieldValue(_T("card_id"),strVal);
					theLang.LoadString(str2,IDS_CARDNO);
					strName.Format(_T("%s:%s"),str2,strVal);
					rs.GetFieldValue(_T("extend_1"),strVal);
					theLang.LoadString(str2,IDS_CARDBALANCE);
					strName.AppendFormat(_T("  %s:%s\n"),str2,strVal);
					vipItem[_T("pay_name")] = strName;
					arrayPays.Push(vipItem);
				}
				rs.Close();
			}
		}
		root[_T("pays")]=arrayPays;
	}
	//��ǰ���
	root[_T("subtotal")]=(double)checkDlg.m_fSubtotal;
	if(checkDlg.m_fDiscount<-0.005)
	{
		root[_T("be4_disc")]=(double)(checkDlg.m_fSubtotal+checkDlg.m_fService);
		root[_T("discount")]=(double)checkDlg.m_fDiscount;
	}
	root[_T("service")]=(double)checkDlg.m_fService;
	if(CMainSheet::m_iStaticsInfo&0x08)
	{
		root[_T("tax")]=(double)checkDlg.m_fTax;
		if(checkDlg.m_fTax>0.005)
		{
			root[_T("be4_tax")]=(double)(checkDlg.m_fSubtotal+checkDlg.m_fService+checkDlg.m_fDiscount);
		}
		if(CCheckDlg::TAX_NAME.IsEmpty())
		{
			CString str2;
			theLang.LoadString(str2,IDS_TAX);
			root[_T("tax_name")]=str2;
		}
		else
		{
			root[_T("tax_name")]=CCheckDlg.TAX_NAME;
		}
		//��ʽ��ÿ��˰�ʵ��ܶ�
		JSONVALUE arrayTaxs;
		std::map<int,TaxItem*>::iterator iter;
		for(iter=checkDlg.mTaxGroup.begin();iter!=checkDlg.mTaxGroup.end();iter++)
		{
			if(iter->second->total>0)
			{
				JSONVALUE jsItem;
				jsItem[_T("id")]=iter->second->id;
				jsItem[_T("rate")]=iter->second->rate;
				jsItem[_T("name")]=iter->second->name;
				jsItem[_T("total")]=iter->second->total;
				arrayTaxs.Push(jsItem);
			}
		}
		root[_T("taxs")]=arrayTaxs;
	}
	if(fChange>=0.01)
		root[_T("change")]=fChange;
	root[_T("chk_name")]=theApp.m_strChkName;
	root[_T("chk_total")]=(double)checkDlg.m_fDebt;
	root[_T("item_total")]=checkDlg.m_nTotal;
	CString strTmp;
	SYSTEMTIME st;
	GetLocalTime(&st);
	strTmp.Format(_T("%04d-%02d-%02d %02d:%02d:%02d"),st.wYear,st.wMonth,st.wDay,
		st.wHour,st.wMinute,st.wSecond);
	root[_T("end_time")]=strTmp;
}
/************************************************************************
* �������ܣ���ӡԤ�ᵥ
* ���������
* ���������
* ����ֵ  ��
************************************************************************/
void PayDlg::OnBnClickedPrePrint()
{
	LOG4CPLUS_INFO(log_pos,"PayDlg::OnBnClickedPrint Begin");
	int active=m_TabCtrl.GetActivePageIndex();
	if (theApp.m_bQuickService&&theApp.m_nOrderHeadid==0)
	{
		if(OrderDlg::SaveOrderHead()==FALSE)
			return;
	}
	if(CheckCosumeLimit()==FALSE)
		return;
	OrderDlg::SaveOrderToDB(m_pOrderList,&m_checkDlg);
	PrintCheck(m_checkDlg[active],active,0);
}
/************************************************************************
* �������ܣ���ӡ�˵�
* ���������type 0- Ԥ�ᵥ 1-���ʵ�
* ���������
* ����ֵ  ��
************************************************************************/
void PayDlg::PrintCheck(CCheckDlg& currentChkDlg,int active,int type)
{
	PrintDeviceInfo printer;
	if(theApp.m_prePrinter.nDeviceType==-1||theApp.m_prePrinter.nPaperWidth==0)
	{
		if (theApp.m_payPrinter.nDeviceType==-1)
		{//û�����ô�ӡ�����޷���ӡ
			POSMessageBox(IDS_NOPREPRINT);
			return;
		}
		printer=theApp.m_payPrinter;
	}
	else
		printer=theApp.m_prePrinter;
	CString userid;
	int auth=OrderDlg::RequeastAuth(userid,_T("print_prestatement"));
	if (auth!=0)
		return;
	CPOSClientApp* pApp=(CPOSClientApp*)AfxGetApp();
	CRecordset rs( &theDB);
	CString strSQL,cvalue;
	int nPrint=0;
	BOOL bHistory=FALSE;
	//���²���ȡ��ӡ����
	strSQL.Format(_T("SELECT print_count FROM order_head WHERE order_head_id=%d AND check_id=%d;")
		,pApp->m_nOrderHeadid,active+1);
	rs.Open( CRecordset::forwardOnly,strSQL);
	if (!rs.IsEOF())
	{
		rs.GetFieldValue((short)0,cvalue);
		nPrint=_wtoi(cvalue);
		strSQL.Format(_T("UPDATE order_head SET print_count=print_count+1 WHERE order_head_id=%d AND check_id=%d;")
			,pApp->m_nOrderHeadid,active+1);
		theDB.ExecuteSQL(strSQL);
	}
	else
	{//����head�У���ѯhistory
		rs.Close();
		strSQL.Format(_T("SELECT print_count FROM history_order_head WHERE order_head_id=%d AND check_id=%d;")
			,pApp->m_nOrderHeadid,active+1);
		rs.Open( CRecordset::forwardOnly,strSQL);
		if (!rs.IsEOF())
		{
			rs.GetFieldValue((short)0,cvalue);
			nPrint=_wtoi(cvalue);
		}
		bHistory=TRUE;
		strSQL.Format(_T("UPDATE history_order_head SET print_count=print_count+1 WHERE order_head_id=%d AND check_id=%d;")
			,pApp->m_nOrderHeadid,active+1);
		theDB.ExecuteSQL(strSQL);
	}
	rs.Close();
	nPrint++;

	JSONVALUE root;
	root[_T("print_count")]=nPrint;
	FormatPrint(root,printer,currentChkDlg,active);
	if(type==0)//Ԥ�ᵥ
	{
// 		if(GetWeixinQRCode(currentChkDlg.m_fDebt*100+0.5))
// 		{
// 			root[_T("qrcode")]=QRPAY_PATH;
// 		}
		root[_T("template")]=TEMPLATE_PREPAY;
		//��ӽ���С��
		CString strTips;
		for(int i=0;i<theApp.m_tipSuggests.size();i++)
		{
			int tip=theApp.m_tipSuggests[i];
			double tips=(currentChkDlg.m_fDebt+currentChkDlg.m_fPayed)/100*tip;
			strTips.AppendFormat(_T("%%%d Tips = %0.2f\n"),tip,tips);
		}
		root[_T("suggest_tips")]=strTips;
		CPOSClientApp::PrintJson(root);
	}
	else//�˿�
	{
		root[_T("template")]=TEMPLATE_PAY;
		CPOSClientApp::PrintJson(root);
	}
	if(bHistory==FALSE)
	{
		//������̬Ϊ��ӡ��
		strSQL.Format(_T("UPDATE tables SET table_status=4 WHERE table_id=\'%d\';"),pApp->m_nTableId);
		theDB.ExecuteSQL(strSQL);
	}
}
/************************************************************************
* �������ܣ���ȡ΢��֧����ά��
* ���������
* ���������
* ����ֵ  ��
************************************************************************/
BOOL PayDlg::GetWeixinQRCode(int total_fee)
{
 	if(theApp.m_wxSubMchid.IsEmpty()||theApp.m_wxSubMchid==_T("6118256272844390558"))
 		return FALSE;//δ�����򲻴�ӡ
	try{
		CSslConnection inetSec;
		inetSec.SetServerName(theApp.m_strQfServerURL);
		inetSec.SetObjectName(_T("/trade/v1/payment"));
		inetSec.m_bUseWechatCert=FALSE;
		if (!inetSec.ConnectToHttpsServer(_T("POST"))) {
			return FALSE;
		}
		CString strTradeNO;
		strTradeNO.Format(_T("%s_%09d_%d"),theApp.m_strResId.Mid(1,16),theApp.m_nOrderHeadid,time(NULL));
		CStringArray clist;
		CString item;
		item.Format(_T("%s=%d"),_T("txamt"),total_fee);
		clist.Add(item);
		item.Format(_T("%s=%s"),_T("txcurrcd"),_T("CNY"));
		clist.Add(item);
		item.Format(_T("%s=%d"),_T("pay_type"),800201);//΢��ɨ��
		clist.Add(item);
		item.Format(_T("%s=%s"),_T("out_trade_no"),strTradeNO);
		clist.Add(item);
		CTime c_time=CTime::GetCurrentTime();
		item.Format(_T("%s=%s"),_T("txdtm"),c_time.Format(_T("%Y-%m-%d %H:%M:%S")));
		clist.Add(item);
		CString gName=theApp.m_strResName;
		gName.Replace('&',' ');
		item.Format(_T("%s=%s"),_T("goods_name"),gName);
		clist.Add(item);
 		item.Format(_T("%s=%s"),_T("mchid"),theApp.m_wxSubMchid);
 		clist.Add(item);
		CString sign;
		CQfPayDlg::getSign(sign,clist);
		CString strHeader;
		strHeader.Format(_T("X-QF-APPCODE:%s\r\n"),theApp.m_strQfAppcode);
		strHeader.AppendFormat(_T("X-QF-SIGN:%s"),sign);
		inetSec.SetHeader(strHeader);
		CString sendStr;
		for (int n = 0; n < clist.GetCount(); n++)
		{
			sendStr.AppendFormat(_T("%s"),clist.GetAt(n));
			sendStr.Append(_T("&"));
		}
		//תΪUTF-8
		int wcsLen0 = ::WideCharToMultiByte(CP_UTF8, NULL, sendStr, sendStr.GetLength(), NULL, 0, NULL, NULL);
		char* sz0 = new char[wcsLen0 + 1];
		memset(sz0,0,wcsLen0+1);
		::WideCharToMultiByte(CP_UTF8, NULL, sendStr, -1, sz0, wcsLen0,  NULL, NULL);
		sz0 [wcsLen0] = '\0';
		if (!inetSec.SendHttpsRequest(sz0)) {
			return FALSE;
		}
		CString line;
		inetSec.GetRequestResult(line);
		inetSec.ClearHandles();
		CString message;
		JSONVALUE::Unescape((LPCTSTR)line,message);
		LOG4CPLUS_DEBUG(log_pos,(LPCTSTR)message);
		JSONVALUE root;
		if(root.Parse((LPCTSTR)message,JSON_FLAG_LOOSE))
		{
			CString ret=root[_T("respcd")].asCString();
			if(ret==_T("0000"))
			{//1)�����ɹ�
				CString url=root[_T("qrcode")].asCString();
				CInternetSession cis;
				CHttpFile* phf=NULL;
				char pstr[10240];
				int maxlen=10240;
				int len=0;   
				FILE *fp=_wfopen(QRPAY_PATH,_T("wb")); 
				DWORD dwFlags = INTERNET_FLAG_TRANSFER_BINARY|INTERNET_FLAG_DONT_CACHE|INTERNET_FLAG_SECURE ;
				phf=(CHttpFile*)cis.OpenURL(url,1,dwFlags,NULL,0);
				if(phf!=INVALID_HANDLE_VALUE)  
				{
					while(len=phf->Read(pstr,maxlen))
						fwrite(pstr,sizeof(char),len,fp);    
					phf->Close();
					cis.Close();
					fclose(fp);
					return TRUE;
				}
				fclose(fp);
			}
			else
			{
				return FALSE;
			}
		}
	}
	catch(...){
	}
	return FALSE;
}
/************************************************************************
* �������ܣ���ӡ���˵�
* ���������
* ���������
* ����ֵ  ��
************************************************************************/
void PayDlg::OnBnClickedPrintRound()
{
	LOG4CPLUS_INFO(log_pos,"PayDlg::OnBnClickedPrintRound Begin");
	int active=m_TabCtrl.GetActivePageIndex();
	PrintRound(m_checkDlg[active],active);
}
void PayDlg::PrintRound(CCheckDlg& currentChkDlg,int active)
{
	PrintDeviceInfo printer;
	if(theApp.m_prePrinter.nDeviceType==-1||theApp.m_prePrinter.nPaperWidth==0)
	{
		if (theApp.m_payPrinter.nDeviceType==-1)
		{//û�����ô�ӡ�����޷���ӡ
			POSMessageBox(IDS_NOPREPRINT);
			return;
		}
		printer=theApp.m_payPrinter;
	}
	else
		printer=theApp.m_prePrinter;

	CRecordset rs( &theDB);
	CString strSQL,cvalue;

	JSONVALUE root,arrayItems;
	CPOSClientApp::FormatPrintDevice(root,printer);
	root[_T("template")]=TEMPLATE_MAKE;
	root[_T("chk_id")]=active+1;
	FormatTableInfo(root);
	if(!OrderDlg::m_strTblRemark.IsEmpty())
		root[_T("remark")]=OrderDlg::m_strTblRemark;
	CListBoxEx* ptrDetailList=&currentChkDlg.m_ctrlDetailList;
	int begin_id=0;
	BOOL bFindItem=FALSE;
	for(int  i=ptrDetailList->GetCount()-1;i>=0;i--)
	{//��ĩβ�ҵ���һ���µ���־
		OrderDetail* item=(OrderDetail*)ptrDetailList->GetItemDataPtr(i);
		if (item->item_id==ITEM_ID_SENDINFO)
		{
			if(bFindItem)
			{
				begin_id=i;
				break;
			}
		}
		else if (item->item_id>0)
			bFindItem=TRUE;

	}
	if (macrosInt[_T("PRINT_ALLMAKEITEM")]==1)
	{
		begin_id=0;
	}
	double round_total=0;
	for(int  i=begin_id;i<ptrDetailList->GetCount();i++)
	{
		OrderDetail* item=(OrderDetail*)ptrDetailList->GetItemDataPtr(i);
		if (item->item_id<0)
			continue;//����ӡ�µ�ʱ��
		JSONVALUE jsItem;
		if(OrderDetail2Json(item,jsItem))
			arrayItems.Push(jsItem);
		round_total+=item->total_price;
	}
	root[_T("items")]=arrayItems;
	SYSTEMTIME st;
	GetLocalTime(&st);
	CString strTmp;
	strTmp.Format(_T("%04d-%02d-%02d %02d:%02d:%02d"),st.wYear,st.wMonth,st.wDay,
		st.wHour,st.wMinute,st.wSecond);
	root[_T("end_time")]=strTmp;
	root[_T("round_total")]=round_total;//��һ�ֻ��˵���Ʒ�ܼ�
	root[_T("subtotal")]=(double)currentChkDlg.m_fSubtotal;//��Ʒ�ܼ�
	root[_T("service")]=(double)currentChkDlg.m_fService;
	root[_T("chk_total")]=(double)currentChkDlg.m_fDebt;//Ӧ�����
	root[_T("item_total")]=currentChkDlg.m_nTotal;//��Ʒ����
	CPOSClientApp::PrintJson(root);
}
void PayDlg::UpdateNumber(LPCTSTR str)
{
	m_numCtrl.SetWindowText(str);
	InvalidateRect(mRectNum);
}
/************************************************************************
* �������ܣ����ּ�
* ���������
* ���������
* ����ֵ  ��
************************************************************************/
void  PayDlg::OnNumBnClicked(UINT uID)
{
	char num='0'+uID-IDC_BUTTON0;
	m_strNum+=num;
	UpdateNumber(m_strNum);
}
void PayDlg::OnBnClickedButton00()
{
	m_strNum+=_T("00");
	UpdateNumber(m_strNum);
}
void PayDlg::OnBnClickedButton10()
{
	double num=_wtof(m_strNum);
	CString text,strNum;
	GetDlgItem(IDC_BUTTON10)->GetWindowText(text);
	for(int i=0;i<text.GetLength();i++)
	{
		TCHAR ch=text.GetAt(i);
		if(ch>='0'&&ch<='9')
			strNum.AppendChar(ch);
	}
	num+=_wtol(strNum);
	m_strNum.Format(_T("%g"),num);
	UpdateNumber(m_strNum);
}
void PayDlg::OnBnClickedButton20()
{
	double num=_wtof(m_strNum);
	CString text,strNum;
	GetDlgItem(IDC_BUTTON20)->GetWindowText(text);
	for(int i=0;i<text.GetLength();i++)
	{
		TCHAR ch=text.GetAt(i);
		if(ch>='0'&&ch<='9')
			strNum.AppendChar(ch);
	}
	num+=_wtol(strNum);
	m_strNum.Format(_T("%g"),num);
	UpdateNumber(m_strNum);
}
void PayDlg::OnBnClickedButton50()
{
	double num=_wtof(m_strNum);
	CString text,strNum;
	GetDlgItem(IDC_BUTTON50)->GetWindowText(text);
	for(int i=0;i<text.GetLength();i++)
	{
		TCHAR ch=text.GetAt(i);
		if(ch>='0'&&ch<='9')
			strNum.AppendChar(ch);
	}
	num+=_wtol(strNum);
	m_strNum.Format(_T("%g"),num);
	UpdateNumber(m_strNum);
}
void PayDlg::OnBnClickedButton100()
{
	double num=_wtof(m_strNum);
	CString text,strNum;
	GetDlgItem(IDC_BUTTON100)->GetWindowText(text);
	for(int i=0;i<text.GetLength();i++)
	{
		TCHAR ch=text.GetAt(i);
		if(ch>='0'&&ch<='9')
			strNum.AppendChar(ch);
	}
	num+=_wtol(strNum);
	m_strNum.Format(_T("%g"),num);
	UpdateNumber(m_strNum);
}
void PayDlg::OnBnClickedButtonDot()
{
	m_strNum+=_T(".");
	UpdateNumber(m_strNum);
}
void PayDlg::OnBnClickedButtonClear()
{
	m_strNum.Empty();
	UpdateNumber(m_strNum);
}
/************************************************************************
* �������ܣ�AA������
* ���������
* ���������
* ����ֵ  ��
************************************************************************/
void PayDlg::OnBnClickedSeparateCheck()
{
	PrintDeviceInfo printer;
	if(theApp.m_prePrinter.nDeviceType==-1||theApp.m_prePrinter.nPaperWidth==0)
	{
		if (theApp.m_payPrinter.nDeviceType==-1)
		{//û�����ô�ӡ�����޷���ӡ
			POSMessageBox(IDS_NOPREPRINT);
			return;
		}
		printer=theApp.m_payPrinter;
	}
	else
		printer=theApp.m_prePrinter;
	CString userid;
	int auth=OrderDlg::RequeastAuth(userid,_T("print_prestatement"));
	if (auth!=0)
		return;

	NumberInputDlg dlg;
	theLang.LoadString(dlg.m_strHint,IDS_SPLITCOUNT);
	if(dlg.DoModal()==IDCANCEL)
		return;
	int nCount=_wtoi(dlg.m_strNum);
	int active=m_TabCtrl.GetActivePageIndex();
	double amount=m_checkDlg[active].m_fDebt/nCount;
	CString str;
	str.Format(_T("%0.2f/%d = %0.2f"),m_checkDlg[active].m_fDebt,nCount,amount); 
	if(POSMessageBox(str,MB_YESNO)==IDCANCEL)
		return;
	
	CPOSClientApp* pApp=(CPOSClientApp*)AfxGetApp();
	CRecordset rs( &theDB);
	CString strSQL,cvalue;
	int nPrint=0;
	BOOL bHistory=FALSE;
	//���²���ȡ��ӡ����
	strSQL.Format(_T("SELECT print_count FROM order_head WHERE order_head_id=%d AND check_id=%d;")
		,pApp->m_nOrderHeadid,active+1);
	rs.Open( CRecordset::forwardOnly,strSQL);
	if (!rs.IsEOF())
	{
		rs.GetFieldValue((short)0,cvalue);
		nPrint=_wtoi(cvalue);
		strSQL.Format(_T("UPDATE order_head SET print_count=print_count+1 WHERE order_head_id=%d AND check_id=%d;")
			,pApp->m_nOrderHeadid,active+1);
		theDB.ExecuteSQL(strSQL);
	}
	rs.Close();
	nPrint++;
	JSONVALUE root;
	root[_T("print_count")]=nPrint;
	FormatPrint(root,printer,m_checkDlg[active],active);
	root[_T("template")]=TEMPLATE_PREPAY;
	
	root[_T("separate_chk")]=str;
	for(int i=0;i<nCount;i++)
	{
		Sleep(10);
		CPOSClientApp::PrintJson(root);
	}
}
/************************************************************************
* �������ܣ���ʵ�ս��ʣ�Ӧ�ս����ΪĨ��
* ���������
* ���������
* ����ֵ  ��
************************************************************************/
void PayDlg::OnBnClickedActualPayed()
{
	if (theApp.m_bRefund)
		return;
	int active=m_TabCtrl.GetActivePageIndex();
	int percent=100*(m_checkDlg[active].m_fDebt)/m_checkDlg[active].m_fSubtotal;
	//Ĩ��ı������ܳ���20%
	if(percent>20&&m_checkDlg[active].m_fDebt>10)
	{
		POSMessageBox(IDS_TOOMUCH);
		return;
	}
	percent=100*(m_checkDlg[active].m_fDebt-m_checkDlg[active].m_fDiscount)/m_checkDlg[active].m_fSubtotal;
	CString userid;
	if (RequeastAuth(userid,_T("authority_12"),percent))
	{
		return;
	}
	CString strSQL;
	//����Ĩ����
	if(abs(m_checkDlg[active].m_fDebt)>m_fEpsinon)
	{
		CString str2;
		theLang.LoadString(str2,IDS_MOLIN);
		OrderDetail* item=new OrderDetail;
		memset(item,0,sizeof(OrderDetail));
		item->total_price=-m_checkDlg[active].m_fDebt+m_checkDlg[active].m_fMolin;
		item->item_id=ITEM_ID_DISCOUNT;
		item->n_checkID=active+1;
		wcsncpy_s(item->item_name,str2,63);
		//����ϲ�
		m_pOrderList->AddTail(item);
		m_checkDlg[active].m_nStatus=1;
		m_checkDlg[active].AddOrderItem(item);
		PrintCheck(m_checkDlg[active],active,1);
	}
	m_strNum.Empty();
	//��̨
	if (theApp.m_bQuickService&&theApp.m_nOrderHeadid==0)
	{
		OrderDlg::SaveOrderHead();
	}
	OrderDlg::SaveOrderToDB(m_pOrderList,&m_checkDlg);
	CleanTable(TRUE);
}
/************************************************************************
* �������ܣ��˿�״̬ʱ��ȷ���˿��������˳�����¼����
* ���������
* ���������
* ����ֵ  ��
************************************************************************/
void PayDlg::OnBnClickedOK()
{
	try{
		LOG4CPLUS_INFO(log_pos,"PayDlg::OnBnClickedOK Begin");
		CString msg,strSQL;
		if (theApp.m_bQuickService&&theApp.m_nOrderHeadid==0)
		{
			OrderDlg::SaveOrderHead();
		}
		OrderDlg::SaveOrderToDB(m_pOrderList,&m_checkDlg);
		if(m_strNum.IsEmpty())
		{
			//ˢ��edit_time,�Ա�Զ�̱��������ϴ�
			if(!theApp.m_strEndTime.IsEmpty())
			{
				strSQL.Format(_T("UPDATE order_head SET edit_time=NOW() WHERE order_head_id=%d"),theApp.m_nOrderHeadid);
				theDB.ExecuteSQL(strSQL);
			}
			theApp.m_strEndTime.Empty();
			if(CleanTable(TRUE))//������̨
				return;
		}
		if(!theApp.m_bRefund)
		{
			OnBnClickedPayment(IDC_SLU_BUTTON+1);//Ĭ����ID 1֧��
			m_strNum.Empty();
			UpdateNumber(m_strNum);
			return;
		}
	}
	catch(CDBException* e)
	{
		LOG4CPLUS_ERROR(log_pos,(LPCTSTR)e->m_strError);
		AfxMessageBox(e->m_strError,MB_ICONEXCLAMATION);
		e->Delete();
		return;
	}
}
/************************************************************************
* �������ܣ������Զ�ע��
* ���������
* ���������
* ����ֵ  ��
************************************************************************/
BOOL PayDlg::LockScreen()
{
	if(theApp.m_bQuickService)
	{//���ģʽ������
		return FALSE;
	}
	else
	{
		OrderDlg::SaveOrderToDB(m_pOrderList,&m_checkDlg);
		m_strTAInfo.Empty();
		//�ͷ���
		FloorDlg::ReleaseLock(theApp.m_nTableId);
	}
	return TRUE;
}
/************************************************************************
* �������ܣ��޸ĵ���
* ���������
* ���������
* ����ֵ  ��
************************************************************************/
BOOL PayDlg::SetCheckName(LPCTSTR strName)
{
	try{
		CPOSClientApp* pApp=(CPOSClientApp*)AfxGetApp();
		if(strName==NULL)
		{
			CString userid;
			int auth=OrderDlg::RequeastAuth(userid,_T("edit_checkname"));
			if (auth!=0)
				return FALSE;
			StringInputDlg dlg;
			if(pApp->m_bQuickService)
				theLang.LoadString(dlg.m_strTitle,IDS_INPUTCHKNAME2);
			else
				theLang.LoadString(dlg.m_strTitle,IDS_INPUTCHKNAME);
			dlg.m_strInput=pApp->m_strChkName;
			if(dlg.DoModal()==IDCANCEL)
				return FALSE;
			LOG4CPLUS_INFO(log_pos,"PayDlg::OnBnClickedCheckName Begin");
			//ȥ��'��
			dlg.m_strInput.Replace('\'',' ');
			if (dlg.m_strInput.GetLength()>30)
			{
				POSMessageBox(IDS_TOOMUCH);
				return FALSE;
			}
			pApp->m_strChkName=dlg.m_strInput;
		}
		else
		{
			pApp->m_strChkName=strName;
		}
		OrderDlg::UpdateInfo(this);
		OpenDatabase();
		CString strSQL;
		strSQL.Format(_T("UPDATE order_head SET check_name=\'%s\' WHERE order_head_id=%d;"),
			pApp->m_strChkName,pApp->m_nOrderHeadid);
		theDB.ExecuteSQL(strSQL);
		return TRUE;
	}
	catch(CDBException* e)
	{
		LOG4CPLUS_ERROR(log_pos,(LPCTSTR)e->m_strError);
		AfxMessageBox(e->m_strError,MB_ICONEXCLAMATION);
		e->Delete();
	}
	catch(...)
	{
		LOG4CPLUS_ERROR(log_pos,"Catch Exception GetLastError="<<GetLastError());
	}
	return FALSE;
}
void PayDlg::OnBnClickedCheckName()
{
	SetCheckName(NULL);
}
/************************************************************************
* �������ܣ��޸Ŀ�����
* ���������
* ���������
* ����ֵ  ��
************************************************************************/
void PayDlg::OnBnClickedGuest()
{
	try{
		CPOSClientApp* pApp=(CPOSClientApp*)AfxGetApp();
		LOG4CPLUS_INFO(log_pos,"PayDlg::OnBnClickedGuest Begin");
		int guest=0;
		NumberInputDlg dlg;
		theLang.LoadString(dlg.m_strHint,IDS_INPUTGUEST);
		if(dlg.DoModal()==IDOK)
		{
			guest=_wtoi(dlg.m_strNum);
		}
		else
			return;
		if (guest>MAX_GUEST_NUM)
		{
			POSMessageBox(IDS_TOMANYG);
			return;
		}

		pApp->m_nGuests=guest;
		CString tmpMsg,str2;
		theLang.LoadString(str2,IDS_GUESTNUM);
		tmpMsg.Format(_T("%s:%d"),str2,guest);
		m_guestCtrl.SetWindowText(tmpMsg);
		CRect rc;
		m_guestCtrl.GetWindowRect(&rc);    
		ScreenToClient(&rc); 
		InvalidateRect(rc); 
		//�������ݿ�
		OpenDatabase();
		CString strSQL;
		strSQL.Format(_T("UPDATE order_head SET customer_num=\'%d\' WHERE table_id=\'%d\';"),guest,pApp->m_nTableId);
		theDB.ExecuteSQL(strSQL);
		//ˢ�²�λ��
		strSQL.Format(_T("select * from order_detail_default where menu_item_id>0 and is_cus_num>0 and extend_1 in (select ")
			_T("order_default_groupid from order_default_group where serving_place_class=-1 or serving_place_class in (select ")
			_T("rvc_class_id from serving_rvc_class where rvc_center_id=%d))"),theApp.m_nRVC);
		CRecordset rs(&theDB);
		rs.Open(CRecordset::forwardOnly,strSQL);
		while (!rs.IsEOF())
		{
			CDBVariant variant;
			rs.GetFieldValue(_T("menu_item_id"),variant);
			int item_id=variant.m_iVal;
			int count=m_TabCtrl.GetPageCount();
			for (int i=0;i<count;i++)
			{
				CListBoxEx* ptrDetailList=&m_checkDlg[i].m_ctrlDetailList;
				for(int  j=0;j<ptrDetailList->GetCount();j++)
				{
					OrderDetail* item=(OrderDetail*)ptrDetailList->GetItemDataPtr(j);
					if (item->item_id>0&&item->item_id==item_id)
					{//�ҵ�ͬһ����,ȷ�����
						rs.GetFieldValue(_T("unit_id"),variant);
						if(variant.m_iVal<=0)
							variant.m_iVal=1;
						strSQL.Format(_T("SELECT unit_%d FROM menu_item WHERE item_id=%d"),variant.m_iVal,item_id);
						CRecordset rs1(&theDB);
						rs1.Open(CRecordset::forwardOnly,strSQL);
						if(!rs1.IsEOF())
						{
							CString unit;
							rs1.GetFieldValue((short)0,unit);
							if(unit.Compare(item->unit)==0)
							{
								rs.GetFieldValue(_T("quantity"),variant);
								item->quantity=pApp->m_nGuests*variant.m_fltVal;
								item->b_isfree=FALSE;
								//ˢ����ʾ
								ComputeTotalPrice(item);
								m_checkDlg[i].UpdateItemString(j);
								//�洢�ĸ������ݿ�
								if(item->order_id>0)
								{
									strSQL.Format(_T("UPDATE order_detail SET quantity=%f,actual_price=%f WHERE order_detail_id=%d")
										,item->quantity,item->total_price,item->order_id);
									theDB.ExecuteSQL(strSQL);
								}
							}
						}
						rs1.Close();
					}
				}
			}
			rs.MoveNext();
		}
		rs.Close();
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
* �������ܣ���ӷ����
* ���������
* ���������
* ����ֵ  ��
************************************************************************/
void PayDlg::OnBnClickedService()
{
	try{
		int active=m_TabCtrl.GetActivePageIndex();
		if (m_checkDlg[active].m_nStatus==1)
		{
			return;
		}
		CString userid;
		int auth=OrderDlg::RequeastAuth(userid,_T("authority_2"));
		if(auth!=0)
			return;
		DiscountDlg discountDlg;
		discountDlg.pParentWnd=this;
		discountDlg.m_nIsService=1;
		discountDlg.m_nCheckID=active+1;
		if(discountDlg.DoModal()==IDCANCEL)
			return;

		OrderDetail* item=new OrderDetail;
		memset(item,0,sizeof(OrderDetail));
		item->noDiscount=discountDlg.selectedItem.noDiscount;
		item->round_type=discountDlg.selectedItem.round_type;
		item->discount_percent=discountDlg.selectedItem.percent;
		if(item->discount_percent>0.001)
		{
			item->total_price=0;
			if(m_checkDlg[active].m_pService!=NULL)
			{//�Ѿ������������
				delete item;
				return;
			}
		}
		else
		{
			item->total_price=discountDlg.selectedItem.amount;
			//Ĩ��
			double diff=CCheckDlg::Round(item->total_price,discountDlg.selectedItem.round_type);
			item->total_price-=diff;
			item->item_price=item->total_price;
		}
		item->n_discount_type=discountDlg.selectedItem.id;
		item->item_id=ITEM_ID_SERVICE;
		item->n_checkID=active+1;
		if (discountDlg.selectedItem.display_name.GetLength()!=0)
			wcsncpy_s(item->item_name,discountDlg.selectedItem.display_name,63);
		else
			wcsncpy_s(item->item_name,discountDlg.selectedItem.name,63);
		//����ϲ�
		m_pOrderList->AddTail(item);
		m_checkDlg[active].AddOrderItem(item);
		if(theApp.m_VCR.IsOpen())
		{
			CString strLine;
			strLine.Format(_T("SERVICE %0.2f\n"),item->total_price);
			theApp.m_VCR.Print(strLine);
		}
		UpdateSencondScreen(active,item);
		theApp.m_cusDisplay.Display((double)m_checkDlg[active].m_fDebt,2);

	}
	catch(...)
	{
		LOG4CPLUS_ERROR(log_pos,"Catch Exception GetLastError="<<GetLastError());
	}
}
/************************************************************************
* �������ܣ�����ۿ�
* ���������
* ���������
* ����ֵ  ��
************************************************************************/
void PayDlg::OnBnClickedDiscount()
{
	try{
		int active=m_TabCtrl.GetActivePageIndex();
		if (m_checkDlg[active].m_nStatus==1)
		{
			return;
		}
		CString userid;
		int auth=OrderDlg::RequeastAuth(userid,_T("authority_1"));//�ɴ���
		if(auth!=0)
			return;
		DiscountDlg discountDlg;
		discountDlg.pParentWnd=this;
		discountDlg.m_nCheckID=active+1;
		if(discountDlg.DoModal()==IDCANCEL)
			return;
		OrderDetail* item=new OrderDetail;
		memset(item,0,sizeof(OrderDetail));
		//item->discount_level=discountDlg.selectedItem.discount_level;
		item->round_type=discountDlg.selectedItem.round_type;
		item->discount_percent=discountDlg.selectedItem.percent;
		if(item->discount_percent>0.001)
		{//�����ۺ�������
			item->total_price=0;
			if(m_checkDlg[active].m_pDiscount!=NULL)
			{//�Ѿ���������
				delete item;
				POSMessageBox(IDS_NOTDISCOUNT);
				return;
			}
//�ж�Ȩ��
// 			if (RequeastAuth(userid,_T("authority_12"),item->discount_percent))//�ۿ�����
// 			{
// 				delete item;
// 				return;
// 			}
		}
		else
		{
			item->total_price=discountDlg.selectedItem.amount;
			//��Ե�ǰ�ۿ�Ĩ��
			double diff=CCheckDlg::Round(item->total_price,discountDlg.selectedItem.round_type);
			item->total_price-=diff;
		}
		int percent=100*(-m_checkDlg[active].m_fDiscount+item->total_price)/m_checkDlg[active].m_fSubtotal;
		if(item->discount_percent>0.001)
			percent+=item->discount_percent;
		if (RequeastAuth(userid,_T("authority_12"),percent))//�ۿ�����
		{
			delete item;
			return;
		}
		CPOSClientApp* pApp=(CPOSClientApp*)AfxGetApp();
		if (!pApp->m_bRefund&&item->total_price>m_checkDlg[active].m_fDebt)
		{
			POSMessageBox(IDS_TOOMUCH);
			delete item;
			return;
		}
		item->total_price*=(-1);
		item->n_discount_type=discountDlg.selectedItem.id;
		item->item_id=ITEM_ID_DISCOUNT;
		item->n_checkID=active+1;
		if (discountDlg.selectedItem.display_name.GetLength()!=0)
			wcsncpy_s(item->item_name,discountDlg.selectedItem.display_name,63);
		else
			wcsncpy_s(item->item_name,discountDlg.selectedItem.name,63);
		//����ϲ�
		m_pOrderList->AddTail(item);
		m_checkDlg[active].AddOrderItem(item);
		if(theApp.m_VCR.IsOpen())
		{
			CString strLine;
			strLine.Format(_T("DISCOUNT %0.2f\n"),item->total_price);
			theApp.m_VCR.Print(strLine);
		}
		UpdateSencondScreen(active,item);
		theApp.m_cusDisplay.Display((double)m_checkDlg[active].m_fDebt,2);
	}
	catch(...)
	{
		LOG4CPLUS_ERROR(log_pos,"Catch Exception GetLastError="<<GetLastError());
	}
}

/************************************************************************
* �������ܣ��˲�
* ���������
* ���������
* ����ֵ  ��
************************************************************************/
void PayDlg::OnBnClickedButtonVoid()
{
	int active=m_TabCtrl.GetActivePageIndex();
	int nVoidState=0;
	VoidItem(active);
}
/************************************************************************
* �������ܣ����������(����)
* ���������
* ���������
* ����ֵ  ��
************************************************************************/
void PayDlg::OnBnClickedCustomerName()
{
	try{
		CPOSClientApp* pApp=(CPOSClientApp*)AfxGetApp();
		StringInputDlg dlg;
		theLang.LoadString(dlg.m_strTitle,IDS_INPUTVIPCARD);
		if(dlg.DoModal()==IDOK)
		{
			CString strSQL;
			//ȥ��'��
			dlg.m_strInput.Replace('\'',' ');

			OpenDatabase();
			//��ѯ������
			strSQL.Format(_T("SELECT customer_name FROM customer WHERE card_id=\'%s\';"),dlg.m_strInput);
			CRecordset rs(&theDB);
			rs.Open( CRecordset::forwardOnly,strSQL);
			if(rs.GetRecordCount()==0)
			{
				POSMessageBox(IDS_NOCARD);
				return;
			}
			CString cusName;
			rs.GetFieldValue((short)0,cusName);
			pApp->m_strChkName=cusName;
			OrderDlg::UpdateInfo(this);
			strSQL.Format(_T("UPDATE order_head SET customer_name=\'%s\',check_name=\'%s\' WHERE order_head_id=%d;"),
				dlg.m_strInput,cusName,pApp->m_nOrderHeadid);
			theDB.ExecuteSQL(strSQL);
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
* �������ܣ���������Ϊ���
* ���������
* ���������
* ����ֵ  ��
************************************************************************/
void PayDlg::OnBnClickedTakeOutChk()
{
	OnBnClickedTakeOutChk(m_pOrderList);
	UpdateCheckData();
}
void PayDlg::OnBnClickedTakeOutChk(CTypedPtrList<CPtrList,OrderDetail *> *pOrderList)
{
	if(theApp.m_nEatType==TYPE_DINE)
	{//��Ϊ���
		theApp.m_nEatType=TYPE_TAKEOUT;
	}
	else
	{
		theApp.m_nEatType=TYPE_DINE;
		m_strTAInfo.Empty();
	}
	//�����еĲ�
	POSITION pos=NULL;
	CString strSQL;
	for(pos=pOrderList->GetHeadPosition();pos!=NULL;)
	{
		OrderDetail* item=pOrderList->GetNext(pos);
		if (item->n_saved==0)
		{
			item->n_eattype=theApp.m_nEatType;
		}
		else if (item->n_saved==1)
		{
			item->n_eattype=theApp.m_nEatType;
			strSQL.Format(_T("UPDATE order_detail SET eat_type=\'%d\' WHERE order_detail_id=\'%d\';"),
				item->n_eattype,item->order_id);
			theDB.ExecuteSQL(strSQL);
		}
	}
	strSQL.Format(_T("UPDATE order_head SET eat_type=\'%d\' WHERE order_head_id=\'%d\'"),
		theApp.m_nEatType,theApp.m_nOrderHeadid);
	theDB.ExecuteSQL(strSQL);
}
void PayDlg::OnBnClickedTakeOutInfo()
{
	try{
		CustomerSearchDlg2 dlg;
		dlg.m_strResult=m_strTAInfo;
		if(dlg.DoModal()==IDOK)
		{
			m_strTAInfo=dlg.m_strResult;
			int pos=m_strTAInfo.Find('\n');
			if(pos<=0)
				pos=m_strTAInfo.GetLength();
			CString showTAInfo=m_strTAInfo.Left(pos);
			UpdateHint(showTAInfo);
			bNewTainfo=TRUE;
			if(m_pOrderList->IsEmpty())
			{//�¿��ĵ�����Ϊ����ģʽ
				PayDlg::OnBnClickedTakeOutChk(m_pOrderList);
				UpdateCheckData();
			}
			
			//SetCheckName((LPCTSTR)dlg.m_strPhone);
		}
	}
	catch(...)
	{
		LOG4CPLUS_ERROR(log_pos,"Catch Exception GetLastError="<<GetLastError());
	}
}
/************************************************************************
* �������ܣ���Ա��
* ���������
* ���������
* ����ֵ  ��
************************************************************************/
void PayDlg::OnBnClickedMemberPrice()
{
	try{
		OpenDatabase();
		CString userid;
		int auth=OrderDlg::RequeastAuth(userid,_T("edit_customer"));
		if(auth!=0)
			return;
		CRecordset rs(&theDB);
		CDBVariant variant;
		POSITION pos=NULL;
		CString strSQL,strVal;
		if (m_bMemberPrice)
		{//ȡ����Ա��
			if(POSMessageBox(IDS_MEMBERCANCEL,MB_YESNO)==IDCANCEL)
				return;
			m_bMemberPrice=FALSE;
			theApp.m_fMemberDiscount=0;
			for(pos=m_pOrderList->GetHeadPosition();pos!=NULL;)
			{
				OrderDetail* item=m_pOrderList->GetNext(pos);
				if (item->item_id>0&&item->b_reprice&&item->total_price>0)
				{//��Ա�۲�Ʒ
					int uIndex=1;
					strSQL.Format(_T("SELECT unit_1,unit_2,unit_3,unit_4,unit_5 FROM menu_item WHERE item_id=%d"),item->item_id);
					if(rs.Open(-1,strSQL))
					{
						if(!rs.IsEOF())
						{
							for(uIndex=1;uIndex<=5;uIndex++)
							{
								rs.GetFieldValue((short)(uIndex-1),strVal);
								if(strVal.Compare(item->unit)==0)
									break;
							}
						}
					}
					rs.Close();
					strSQL.Format(_T("SELECT price_%d FROM menu_item WHERE item_id=%d"),
						uIndex,item->item_id);
					if(rs.Open(-1,strSQL))
					{
						if(!rs.IsEOF())
						{
							rs.GetFieldValue((short)0,variant);
							item->orignal_price=0;
							item->item_price=variant.m_fltVal;
							item->b_reprice=FALSE;
							ComputeTotalPrice(item);
							if (item->order_id>0)
							{
								strSQL.Format(_T("UPDATE order_detail SET actual_price=\'%f\',product_price=\'%f\',original_price=NULL WHERE order_detail_id=%d")
									,item->total_price,item->item_price,item->order_id);
								theDB.ExecuteSQL(strSQL);
							}
						}
					}
					rs.Close();
				}
			}
		}
		else
		{//���û�Ա��
			m_bMemberPrice=TRUE;
			theApp.m_fMemberDiscount=0;
			for(pos=m_pOrderList->GetHeadPosition();pos!=NULL;)
			{
				OrderDetail* item=m_pOrderList->GetNext(pos);
				if (item->item_id>0&&item->total_price>0)
				{//��ͨ��Ʒ
					int uIndex=1;
					strSQL.Format(_T("SELECT unit_1,unit_2,unit_3,unit_4,unit_5 FROM menu_item WHERE item_id=%d"),item->item_id);
					if(rs.Open(-1,strSQL))
					{
						if(!rs.IsEOF())
						{
							for(uIndex=1;uIndex<=5;uIndex++)
							{
								rs.GetFieldValue((short)(uIndex-1),strVal);
								if(strVal.Compare(item->unit)==0)
									break;
							}
						}
					}
					rs.Close();
					strSQL.Format(_T("SELECT surcharge_%d FROM menu_item WHERE item_id=%d"),
						uIndex,item->item_id);
					if(rs.Open(-1,strSQL))
					{
						if(!rs.IsEOF())
						{
							rs.GetFieldValue((short)0,variant);
							if(variant.m_fltVal>0)
							{
								if(abs(item->orignal_price)<=0.001)
									item->orignal_price=item->item_price;
								item->item_price=variant.m_fltVal;
								item->b_reprice=TRUE;
								double diff=(item->orignal_price-item->item_price)*item->quantity;
								theApp.m_fMemberDiscount+=diff;
								ComputeTotalPrice(item);
								if (item->order_id>0)
								{
									strSQL.Format(_T("UPDATE order_detail SET actual_price=\'%f\',product_price=\'%f\',original_price=%f WHERE order_detail_id=%d")
										,item->total_price,item->item_price,item->orignal_price,item->order_id);
									theDB.ExecuteSQL(strSQL);
								}
							}
						}
					}
					rs.Close();
				}
			}
		}
		strSQL.Format(_T("UPDATE order_head SET member_discount=%0.2f WHERE order_head_id=%d"),theApp.m_fMemberDiscount,theApp.m_nOrderHeadid);
		theDB.ExecuteSQL(strSQL);
		UpdateCheckData();
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
* �������ܣ����÷�Ʊ���
* ���������
* ���������
* ����ֵ  ��
************************************************************************/
void PayDlg::OnBnClickedButtonInvoice()
{
	try{
		LOG4CPLUS_INFO(log_pos,"PayDlg::OnBnClickedButtonInvoice Begin");
		int active=m_TabCtrl.GetActivePageIndex();
		OpenDatabase();
		CString strSQL,strValue;
		strSQL.Format(_T("SELECT amount FROM invoices WHERE order_head_id=%d AND check_id=%d"),theApp.m_nOrderHeadid,active+1);
		CRecordset rs(&theDB);
		if(rs.Open(-1,strSQL))
		{
			if(!rs.IsEOF())
			{
				rs.GetFieldValue(_T("amount"),strValue);
			}
		}
		NumberInputDlg dlg;
		theLang.LoadString(dlg.m_strHint,IDS_INVOCENUM);
		if (!strValue.IsEmpty())
		{
			CString str2;
			theLang.LoadString(str2,IDS_ORIGNALINVOICE);
			dlg.m_strHint.AppendFormat(str2,strValue);
		}
		double amount;
		if(dlg.DoModal()!=IDOK)
			return;
		if (dlg.m_strNum.IsEmpty())
			return;
		amount=_wtof(dlg.m_strNum);
		//�������ݿ�
		if(strValue.IsEmpty())
		{
			strSQL.Format(_T("INSERT INTO invoices(order_head_id, check_id,amount,employee_id,edit_time,pos_device_id)")
				_T(" VALUES(%d,%d,\'%g\',%s,now(),%d)"),theApp.m_nOrderHeadid,active+1,amount,theApp.m_strUserID,theApp.m_nDeviceId);
		}
		else
		{
			strSQL.Format(_T("UPDATE invoices SET amount=\'%g\',employee_id=%s,edit_time=now(),pos_device_id=%d")
				_T(" WHERE order_head_id=%d AND check_id=%d"),amount,theApp.m_strUserID,theApp.m_nDeviceId,theApp.m_nOrderHeadid,active+1);
		}
		theDB.ExecuteSQL(strSQL);
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
void PayDlg::OnBnClickedSelectAll()
{
	int active=m_TabCtrl.GetActivePageIndex();
	if (m_checkDlg[active].m_nStatus==1)
	{
		return;
	}
	CListBoxEx* ptrDetailList=&m_checkDlg[active].m_ctrlDetailList;
	if (ptrDetailList->GetCount()<=0)
		return;
	if(ptrDetailList->GetSel(0))
	{
		ptrDetailList->SelItemRange(FALSE,0,ptrDetailList->GetCount());
	}
	else
	{
		ptrDetailList->SelItemRange(TRUE,0,ptrDetailList->GetCount());
	}
}

void PayDlg::FormatTableInfo(JSONVALUE& root)
{
	root[_T("serial")]=theApp.m_nOrderHeadid;
	root[_T("tbl_name")]=theApp.m_strTblName;
	root[_T("emp_name")]=theApp.m_strUserName;
	root[_T("chk_name")]=theApp.m_strChkName;
	root[_T("tbl_id")]=theApp.m_nTableId;
	root[_T("chk_num")]=theApp.m_nCheckNum;
	root[_T("gst_num")]=theApp.m_nGuests;
	if(theApp.m_nEatType==TYPE_DINE)
		root[_T("eat_di")]=1;
	else
		root[_T("eat_ta")]=1;
	CString time=theApp.m_strBeginDate+_T(" ");
	time.Append(theApp.m_strBeginTime);
	root[_T("open_time")]=time;
	if(theApp.m_fMemberDiscount>0.01)
		root[_T("member_discount")]=theApp.m_fMemberDiscount;
}

extern UINT CODE_PAGE;
void PayDlg::FormatName(OrderDetail* pItem,CString& name)
{
	name=pItem->item_name;
	// 	if(pItem->item_id>0)
	// 	{
	// 		int textlen;
	// 		textlen = WideCharToMultiByte( CODE_PAGE, 0, pItem->item_name, -1, NULL, 0, NULL, NULL );
	// 		if (textlen>35)
	// 		{//��������
	// 			char result[38]={0};
	// 			WideCharToMultiByte( CODE_PAGE, 0, pItem->item_name, -1, result, 36, NULL, NULL );
	// 			textlen = MultiByteToWideChar( CODE_PAGE, 0, result, -1, NULL, 0);
	// 			name=name.Left(textlen-1);
	// 		}
	// 	}
	if(pItem->n_belong_item<0)
	{//�ײ�����
		name.Insert(0,_T("  "));
	}
	CString str2;
	if (pItem->b_isfree)
	{
		theLang.LoadString(str2,IDS_FREE);
		name.Append(str2);
	}
	if (pItem->n_eattype==TYPE_TAKEOUT&&pItem->n_belong_item<=0)
	{
		theLang.LoadString(str2,IDS_TAKEOUT);
		name.Append(str2);
	}
}
/************************************************************************
* �������ܣ���OrderDetail��ʽ��ΪJson
* ���������
* ���������
* ����ֵ  �� TRUE ʵ������ˣ�FALSE ���ϲ����
************************************************************************/
BOOL PayDlg::OrderDetail2Json(OrderDetail* pItem,JSONVALUE& retrunItem)
{
	CString name;
	FormatName(pItem,name);
	if (pItem->n_belong_item>0)
	{//����
		name=_T("  ")+name;
	}
	if(pItem->item_id>0)
	{
		retrunItem[_T("num")] = pItem->quantity;
	}
	retrunItem[_T("id")] = pItem->item_id;
	retrunItem[_T("name")] = name;
	if (pItem->item_name2[0]!=0)
	{
		retrunItem[_T("name2")] = pItem->item_name2;
	}
	// 	if(pItem->item_id==ITEM_ID_SERVICE||pItem->item_id==ITEM_ID_DISCOUNT)
	// 	{//�ۿۺͷ����ֻ��ʾname2�����
	// 		retrunItem[_T("name2")] = pItem->item_name;
	// 	}
	retrunItem[_T("total")] = pItem->total_price;
	if(pItem->item_id>0)
	{
		retrunItem[_T("price")] = pItem->item_price;
		retrunItem[_T("unit")] = pItem->unit;
		if (pItem->n_seat_num>0)
		{
			retrunItem[_T("seat")] = pItem->n_seat_num;
		}
		if(pItem->description[0]!=0)
			retrunItem[_T("desc")] = pItem->description;
	}
	return TRUE;
}

BOOL PayDlg::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message==WM_KEYDOWN)
	{
		if(theApp.m_pMain->GetActiveIndex()!=DLG_PAY)
			return TRUE;
		if(pMsg->wParam==VK_PROCESSKEY)
		{
			pMsg->wParam=ImmGetVirtualKey(this->m_hWnd);
		}
		switch (pMsg->wParam)
		{
		case VK_F7:
		case VK_PRIOR:
			OnBnClickedDiscount();
			return TRUE;
		case VK_F8:
		case VK_NEXT:
			OnBnClickedService();
			return TRUE;
		case VK_DELETE:
			OnBnClickedButtonClear();
			return TRUE;
		case VK_BACK:
			if(m_strNum.IsEmpty())
			{
				OnBnClickedPrepage();
			}
			else
			{
				m_strNum.Delete(m_strNum.GetLength()-1);
				UpdateNumber(m_strNum);
			}

			return TRUE;
		case VK_RETURN://Ĭ�ϸ��ʽ
			OnBnClickedOK();
			return TRUE;
		case VK_F11:
			OnBnClickedPrintRound();
			return TRUE;
		case VK_F12:
			OnBnClickedPrePrint();
			return TRUE;
		case VK_DECIMAL:
		case VK_OEM_PERIOD:
			OnBnClickedButtonDot();
			return TRUE;
		case VK_UP:
			{
				CListBoxEx* ptrDetailList=&m_checkDlg[m_TabCtrl.GetActivePageIndex()].m_ctrlDetailList;
				if (ptrDetailList->GetSelCount()==0)
				{//ѡ�����һ��
					ptrDetailList->SetSel(ptrDetailList->GetCount()-1);
				}
				else
				{
					BOOL bSet=FALSE;
					for(int  i=ptrDetailList->GetCount()-1;i>=0;i--)
					{
						if (bSet)
						{
							ptrDetailList->SetSel(i,FALSE);
							continue;
						}
						if(ptrDetailList->GetSel(i))
						{
							ptrDetailList->SetSel(i,FALSE);
							i--;
							if(i>=0)
								ptrDetailList->SetSel(i,TRUE);
							bSet=TRUE;
						}
					}
				}
				return TRUE;
			}
		case VK_DOWN:
			{
				CListBoxEx* ptrDetailList=&m_checkDlg[m_TabCtrl.GetActivePageIndex()].m_ctrlDetailList;
				if (ptrDetailList->GetSelCount()==0)
				{//ѡ�е�һ��
					ptrDetailList->SetSel(0);
				}
				else
				{
					BOOL bSet=FALSE;
					for(int i=0;i<ptrDetailList->GetCount();i++)
					{
						if (bSet)
						{
							ptrDetailList->SetSel(i,FALSE);
							continue;
						}
						if(ptrDetailList->GetSel(i))
						{
							ptrDetailList->SetSel(i,FALSE);
							i++;
							ptrDetailList->SetSel(i,TRUE);
							bSet=TRUE;
						}
					}
				}
				return TRUE;
			}
		}
		if(pMsg->wParam>=VK_F1&&pMsg->wParam<=VK_F6)
		{
			OnBnClickedPayment(pMsg->wParam-VK_F1+IDC_SLU_BUTTON+1);
			return TRUE;
		}
		else if (pMsg->wParam>='0'&&pMsg->wParam<='9')
		{
			OnNumBnClicked(pMsg->wParam-'0'+IDC_BUTTON0);
			return TRUE;
		}
		else if (pMsg->wParam>=VK_NUMPAD0&&pMsg->wParam<=VK_NUMPAD9)
		{
			OnNumBnClicked(pMsg->wParam-VK_NUMPAD0+IDC_BUTTON0);
			return TRUE;
		}
	}

	return CPosPage::PreTranslateMessage(pMsg);
}
HBRUSH PayDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	if(nCtlColor==CTLCOLOR_STATIC)
	{
		if(pWnd->GetDlgCtrlID()==IDC_STATIC_NUM)
			pDC->SetTextColor(RGB(255,255,255));
		else
			pDC->SetTextColor(RGB(0,0,0));
		pDC->SetBkMode(TRANSPARENT);
		return (HBRUSH)::GetStockObject(NULL_BRUSH); //���ش˻�ˢ����ʹ��̬�ı�͸��
	}
	return   hbr; 
}