// PreOrderDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "POSClient.h"
#include "PreOrderDlg.h"
#include "NumberInputDlg.h"

// PreOrderDlg 对话框

IMPLEMENT_DYNAMIC(PreOrderDlg, CDialog)

PreOrderDlg::PreOrderDlg(CWnd* pParent /*=NULL*/)
	: CDialog(PreOrderDlg::IDD, pParent)
{
	m_nGuestNum=0;
}

PreOrderDlg::~PreOrderDlg()
{
}

void PreOrderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_GUESTNUM, m_ctrlGuestNum);
	DDX_Control(pDX, IDC_BUTTON_ARRIVE, m_btArrive);
	DDX_Control(pDX, IDC_BUTTON_CANCLEORDER, m_btCancel);
	DDX_Control(pDX, IDC_BUTTON_IGNORE, m_btIgnore);
}


BEGIN_MESSAGE_MAP(PreOrderDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_ARRIVE, &PreOrderDlg::OnBnClickedButtonArrive)
	ON_BN_CLICKED(IDC_BUTTON_CANCLEORDER, &PreOrderDlg::OnBnClickedButtonCancleorder)
	ON_BN_CLICKED(IDC_BUTTON_IGNORE, &PreOrderDlg::OnBnClickedButtonIgnore)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// PreOrderDlg 消息处理程序


BOOL PreOrderDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	CString str2;
	theLang.LoadString(IDS_PRE_ARRIVE,str2);
	m_btArrive.SetWindowText(str2);
	m_btArrive.SetImage(_T("Picture\\bt_orange_71.png"));
	m_btArrive.SetTextColor(DEFALUT_TXT_COLOR);
	theLang.LoadString(IDS_PRE_DELETE,str2);
	m_btCancel.SetWindowText(str2);
	m_btCancel.SetImage(_T("Picture\\bt_orange_71.png"));
	m_btCancel.SetTextColor(DEFALUT_TXT_COLOR);
	theLang.LoadString(IDS_IGNORE,str2);
	m_btIgnore.SetWindowText(str2);
	m_btIgnore.SetImage(_T("Picture\\bt_orange_71.png"));
	m_btIgnore.SetTextColor(DEFALUT_TXT_COLOR);

	CString strVal;
	CDBVariant variant;
	rs->GetFieldValue(_T("customer_num"),strVal);
	m_ctrlGuestNum.SetWindowText(strVal);
	m_nGuestNum=_wtoi(strVal);
	rs->GetFieldValue(_T("pre_order_id"),variant);
	m_nPreorderId=variant.m_lVal;
	rs->GetFieldValue(_T("arrived_time"),variant);
	strVal.Format(_T("%02d:%02d"),variant.m_pdate->hour,variant.m_pdate->minute);
	CWnd* pCtrl=GetDlgItem(IDC_EDIT_TIME);
	pCtrl->SetWindowText(strVal);
	rs->GetFieldValue(_T("customer_name"),strVal);
	pCtrl=GetDlgItem(IDC_EDIT_GUESTNAME);
	pCtrl->SetWindowText(strVal);
	rs->GetFieldValue(_T("telephone_1"),strVal);
	pCtrl=GetDlgItem(IDC_EDIT_PHONE);
	pCtrl->SetWindowText(strVal);

	pCtrl=GetDlgItem(IDC_STATIC_GUEST);
	theLang.LoadString(IDS_GUESTNUM,strVal);
	pCtrl->SetWindowText(strVal);
	pCtrl=GetDlgItem(IDC_STATIC_ARRIVE);
	theLang.LoadString(IDS_ARRIVETIME,strVal);
	pCtrl->SetWindowText(strVal);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
//预定抵达
void PreOrderDlg::OnBnClickedButtonArrive()
{
	CString strSQL;
	strSQL.Format(_T("UPDATE pre_order SET pre_order_status=3,preorder_time=now() WHERE pre_order_id=%d"),m_nPreorderId);
	theDB.ExecuteSQL(strSQL);
	strSQL.Format(_T("UPDATE webreport_setting SET soldoutp = 1"));
	theDB.ExecuteSQL(strSQL);
	return CDialog::OnOK();
}

//取消预定
void PreOrderDlg::OnBnClickedButtonCancleorder()
{
	if(POSMessageBox(IDS_CANCELORDER,MB_YESNO)==IDCANCEL)
	{
		return;
	}
	CString strSQL;
	strSQL.Format(_T("UPDATE pre_order SET pre_order_status=5,preorder_time=now() WHERE pre_order_id=%d"),m_nPreorderId);
	theDB.ExecuteSQL(strSQL);
	strSQL.Format(_T("UPDATE webreport_setting SET soldoutp = 1"));
	theDB.ExecuteSQL(strSQL);
	return CDialog::OnCancel();
}

void PreOrderDlg::OnBnClickedButtonIgnore()
{
	m_nGuestNum=0;
	return CDialog::OnOK();
}


void PreOrderDlg::OnPaint()
{
	if(!IsIconic())
	{
		CRect   rect;
		CPaintDC   dc(this);
		GetClientRect(rect);
		dc.FillSolidRect(rect,DEFALUT_BACKGROUND_COLOR);
		CDialog::OnPaint();
	}
}

HBRUSH PreOrderDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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
