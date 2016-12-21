// EftMsgDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "POSClient.h"
#include "EftMsgDlg.h"


// CEftMsgDlg 对话框

IMPLEMENT_DYNAMIC(CEftMsgDlg, CDialog)

CEftMsgDlg::CEftMsgDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEftMsgDlg::IDD, pParent)
{
	fPayed=0;
}

CEftMsgDlg::~CEftMsgDlg()
{
}

void CEftMsgDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CEftMsgDlg, CDialog)
END_MESSAGE_MAP()

BEGIN_EVENTSINK_MAP(CEftMsgDlg, CDialog)
    //{{AFX_EVENTSINK_MAP(PayDlg)
	//ON_EVENT(PayDlg, IDC_CSDEFT, 28 /* PrintReceiptEvent */, OnPrintReceiptEventCsdeft, VTS_BSTR)
	//ON_EVENT(PayDlg, IDC_CSDEFT, 20 /* GetLastReceiptEvent */, OnGetLastReceiptEventCsdeft, VTS_NONE)
	ON_EVENT(CEftMsgDlg, IDC_CSDEFT, 12 /* TransactionEvent */, OnTransactionEventCsdeft, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()
// CEftMsgDlg 消息处理程序

BOOL CEftMsgDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	try{
		if(m_CsdEft.Create(_T(""),_T(""),WS_VISIBLE|WS_EX_TOPMOST, CRect(0,0,100,100), this, IDC_CSDEFT)==FALSE)
		{
			GetDlgItem(IDC_STATIC1)->SetWindowText(_T("PC-EFTPOS not installed"));
			return TRUE;
		}
		if(fPayed<0)
		{//退款
			m_CsdEft.SetTxnType(_T("R"));
		}
		else
		{
			m_CsdEft.SetTxnType(_T("P"));
		}
		
		CString txnRef;
		txnRef.Format(_T("%d"),theApp.m_nOrderHeadid);
		m_CsdEft.SetTxnRef(txnRef);
		CY Amt;		
		Amt.int64 = fPayed*10000;
		m_CsdEft.SetAmtPurchase(Amt);
		if(macrosInt[_T("EFT_NO_PRINT")]==1)
		{
			m_CsdEft.SetReceiptAutoPrint(FALSE);
			m_CsdEft.SetCutReceipt(FALSE);
		}
		else
		{
			m_CsdEft.SetReceiptAutoPrint(TRUE);
			m_CsdEft.SetCutReceipt(TRUE);
		}

		m_CsdEft.DoTransaction();
	}catch(...)
	{

	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
void CEftMsgDlg::OnTransactionEventCsdeft() 
{
	CString m_ResponseCode = m_CsdEft.GetResponseCode();
	CString m_ResponseText = m_CsdEft.GetResponseText();
	if(m_CsdEft.GetSuccess()) {
		CDialog::OnOK();
	}
	else {
		CDialog::OnCancel();
	}
}