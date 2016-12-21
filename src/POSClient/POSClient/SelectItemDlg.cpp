// SelectItemDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "POSClient.h"
#include "SelectItemDlg.h"
#include "OrderDlg.h"


// SelectItemDlg 对话框

IMPLEMENT_DYNAMIC(SelectItemDlg, CDialog)

SelectItemDlg::SelectItemDlg(CWnd* pParent /*=NULL*/)
	: CDialog(SelectItemDlg::IDD, pParent)
{
	m_nCheckID=0;
	m_nType=0;
	pParentWnd=NULL;
}

SelectItemDlg::~SelectItemDlg()
{
	m_btnCtrl.ReleaseBtn();
	::DeleteObject(m_bpBackgrd);
}

void SelectItemDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Control(pDX, IDC_STATIC_LOG, m_logCtrl);
	DDX_Control(pDX, IDC_STATIC_TIME, m_timeCtrl);
	DDX_Control(pDX, IDC_STATIC_GUEST, m_guestCtrl);
	DDX_Control(pDX, IDC_STATIC_TABLE, m_tableCtrl);
	DDX_Control(pDX, IDC_STATIC_CHECK, m_checkCtrl);
	DDX_Control(pDX, IDC_EDIT2, m_hint);
}


BEGIN_MESSAGE_MAP(SelectItemDlg, CDialog)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BUTTON_SELECTALL, &SelectItemDlg::OnBnClickedSelectAll)
	ON_BN_CLICKED(IDOK, &SelectItemDlg::OnBnClickedOK)
	ON_BN_CLICKED(IDCANCEL, &SelectItemDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON_OK, &SelectItemDlg::OnBnClickedOK)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, &SelectItemDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, &SelectItemDlg::OnBnClickedClear)
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// SelectItemDlg 消息处理程序

BOOL SelectItemDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	CImage img;
	if(img.Load(_T("Picture\\floorview.png"))==S_OK)
	{
		m_x=img.GetWidth();
		m_y=img.GetHeight();
		m_bpBackgrd=img.Detach();
	}
 	CRect rect2;
 	if(pParentWnd==NULL)
 		pParentWnd= theApp.m_pMain;
 	pParentWnd->GetClientRect(&rect2);
 	pParentWnd->ClientToScreen(&rect2);
 	MoveWindow(rect2);

	m_btnCtrl.GenaratePage2(_T("Page\\IDD_SELECTITEM.ini"),this);
	theLang.UpdatePage(this,_T("DEFAULT"),TRUE);
	m_list.m_nSubWidth[0]=50*CreatButton::m_nFullWidth/1024;
	m_list.m_nSubWidth[1]=150*CreatButton::m_nFullWidth/1024;
	m_list.m_nSubWidth[2]=100*CreatButton::m_nFullWidth/1024;
	m_logCtrl.SetFont(&theApp.m_txtFont);
	m_checkCtrl.SetFont(&theApp.m_txtFont);
	m_tableCtrl.SetFont(&theApp.m_txtFont);
	m_guestCtrl.SetFont(&theApp.m_txtFont);
	m_timeCtrl.SetFont(&theApp.m_txtFont);
	OrderDlg::UpdateInfo(this);
	m_hint.m_BackColor=RGB(200, 200, 200);
	m_hint.SetWindowText(m_strHint);
	OnSetActive();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
void SelectItemDlg::OnSetActive()
{
	if (m_pOrderList==NULL)
	{
		return;
	}
	CPOSClientApp* pApp=(CPOSClientApp*)AfxGetApp();
	m_list.ResetContent();
	POSITION pos=NULL;
	CString strTmp;
	CString decPlace;
	decPlace.Format(_T(".%df|"),theApp.DECIMAL_PLACES);
	for(pos=m_pOrderList->GetHeadPosition();pos!=NULL;)
	{
		OrderDetail* item=m_pOrderList->GetNext(pos);
		//非菜品不显示
		if (item->item_id<=0)
			continue;
		//打折时根据级别过滤
		if (m_nType==0&&(item->n_discount_type<=0))
			continue;
		//服务费根据级别过滤
		if (m_nType==2&&(item->n_service_type<=0))
			continue;
		if (item->n_checkID!=m_nCheckID)
		{
			continue;
		}
		if (item->weight_required)//称重产品显示重量
		{
			strTmp.Format(_T("|1|%s\n%0.2f %s|%")+decPlace,item->item_name,item->quantity,item->unit,item->total_price);
		}
		else
		{
			strTmp.Format(_T("|%g%s|%s|%")+decPlace,item->quantity,item->unit,item->item_name,item->total_price);
		}
		int index=m_list.AddString(strTmp);
		m_list.SetItemDataPtr(index,item);
	}
	//m_list.SelItemRange(TRUE,0,m_list.GetCount());
}
void SelectItemDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	cx=CreatButton::m_nFullWidth;
	cy=CreatButton::m_nFullHeight;
	int width=(int)(cx*0.4);
	int height=(int)(cy*0.04);
	if (m_list.m_hWnd)
	{
		int line_y1=78;
		height=28;
		int line_y2=line_y1+height;
		m_logCtrl.MoveWindow(25,line_y1,95,height);
		m_checkCtrl.MoveWindow(140*cx/1024,line_y1,220*cx/1024,height);
		m_tableCtrl.MoveWindow(25,line_y2,115*cx/1024,height);
		m_guestCtrl.MoveWindow(140*cx/1024,line_y2,115*cx/1024,height);
		m_timeCtrl.MoveWindow(245*cx/1024,line_y2,95*cx/1024,height);
		m_hint.MoveWindow(cx/2,(int)(cy*0.4),width,height);
		m_list.MoveWindow(23,133*cy/768,328*cx/1024,(int)(cy*0.73));
	}
}

void SelectItemDlg::OnBnClickedSelectAll()
{
	m_list.SelItemRange(TRUE,0,m_list.GetCount());
}
void SelectItemDlg::OnBnClickedOK()
{
	int length=m_list.GetCount();
	BOOL bSel=FALSE;
	if(m_nType==0||m_nType==2)
	{
		double total=0;
		for (int i=0;i<length;i++)
		{
			if (m_list.GetSel(i))
			{
				OrderDetail* item=(OrderDetail*)m_list.GetItemDataPtr(i);
				if(item==NULL)
					continue;
				if (m_nType==0)
				{//打折
					if (item->n_discount_type>0)
					{
						total+=item->total_price;
						bSel=TRUE;
					}
				}
				else if (m_nType==2)
				{//服务费
					if (item->n_service_type>0)
					{
						total+=item->total_price;
						bSel=TRUE;
					}
				}
			}
		}
		if (bSel==FALSE)
		{
			return CDialog::OnCancel();
		}
		amount=(total*percent)/100;
	}
	else if (m_nType==1)
	{//复制账单，只保留选择的
		for (int i=0;i<length;i++)
		{
			if (m_list.GetSel(i))
			{
				bSel=TRUE;
			}
			else
			{
				OrderDetail* item=(OrderDetail*)m_list.GetItemDataPtr(i);
				POSITION p= m_pOrderList->Find(item);
				m_pOrderList->RemoveAt(p);
				delete item;
			}
		}
		if (bSel==FALSE)
		{
			return CDialog::OnCancel();
		}
	}
	return CDialog::OnOK();
}
void SelectItemDlg::OnBnClickedCancel()
{
	return CDialog::OnCancel();
}
void SelectItemDlg::OnBnClickedClear()
{
	m_list.SelItemRange(FALSE,0,m_list.GetCount()-1);
}
// virtual INT_PTR SelectItemDlg::DoModal()
// {
//   if (pParentWnd)
//   {
//   }
//   //CDialog::DoModal;
//   //遍历程序中所有除自身之外的所有窗口，再将其enable；
// }
BOOL SelectItemDlg::OnEraseBkgnd(CDC* pDC)
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
BOOL SelectItemDlg::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message==WM_KEYDOWN)
	{
		switch (pMsg->wParam)
		{
		case VK_ESCAPE:
		case VK_BACK:
			OnBnClickedCancel();
			return TRUE;
		case VK_RETURN:
			OnBnClickedOK();
			return TRUE;
		}
	}
	return CDialog::PreTranslateMessage(pMsg); 
}

HBRUSH SelectItemDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	if(nCtlColor==CTLCOLOR_STATIC)
	{
		//pDC->SetTextColor(m_dTextColor);
		pDC->SetBkMode(TRANSPARENT);
		return (HBRUSH)::GetStockObject(NULL_BRUSH); //返回此画刷可以使静态文本透明
	}
	return   hbr; 
}
