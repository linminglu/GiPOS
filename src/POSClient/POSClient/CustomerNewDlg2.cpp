// CustomerNewDlg2.cpp : 实现文件
//

#include "stdafx.h"
#include "POSClient.h"
#include "CustomerNewDlg2.h"
#include "GenFirstPYLetter.h"


// CustomerNewDlg2 对话框

IMPLEMENT_DYNAMIC(CustomerNewDlg2, CDialog)

CustomerNewDlg2::CustomerNewDlg2(CWnd* pParent /*=NULL*/)
	: CDialog(CustomerNewDlg2::IDD, pParent)
{
	m_cusID=-1;
}

CustomerNewDlg2::~CustomerNewDlg2()
{
}

void CustomerNewDlg2::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, mEditName);
	DDX_Control(pDX, IDC_EDIT2, mEditPhone);
	DDX_Control(pDX, IDC_EDIT3, mEditAddress);
	DDX_Control(pDX, IDOK, m_btOK);
	DDX_Control(pDX, IDCANCEL, m_btCancel);
}


BEGIN_MESSAGE_MAP(CustomerNewDlg2, CDialog)
	ON_BN_CLICKED(IDOK, &CustomerNewDlg2::OnBnClickedOk)
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CustomerNewDlg2 消息处理程序
BOOL CustomerNewDlg2::OnInitDialog()
{
	CDialog::OnInitDialog();
	CString str2;
	m_btOK.SetImage(_T("Picture\\bt_ok.png"));
	m_btCancel.SetImage(_T("Picture\\bt_cancel.png"));
	if (!theLang.m_bDefaultLang)
	{
		CWnd* pCtrl=pCtrl=GetDlgItem(IDOK);
		theLang.TranslateDlgItem(pCtrl,IDS_OK);
		pCtrl=GetDlgItem(IDCANCEL);
		theLang.TranslateDlgItem(pCtrl,IDS_CANCEL);
		pCtrl=GetDlgItem(IDC_STATIC1);
		theLang.TranslateDlgItem(pCtrl,IDS_FMNAME);
		pCtrl=GetDlgItem(IDC_STATIC2);
		theLang.TranslateDlgItem(pCtrl,IDS_PHONE);
		pCtrl=GetDlgItem(IDC_STATIC3);
		theLang.TranslateDlgItem(pCtrl,IDS_ADRESS);
		theLang.LoadString(IDS_ADDCUS,str2);
		SetWindowText(str2);
	}
	if (m_cusID>0)
	{
		CString strSQL;
		strSQL.Format(_T("SELECT * FROM customer WHERE customer_id=%d"),m_cusID);
		CRecordset rs(&theDB);
		rs.Open( CRecordset::forwardOnly,strSQL);
		CString strValue;
		if (!rs.IsEOF())
		{
			rs.GetFieldValue(_T("customer_name"),strValue);
			mEditName.SetWindowText(strValue);
			rs.GetFieldValue(_T("telephone_1"),strValue);
			mEditPhone.SetWindowText(strValue);
			rs.GetFieldValue(_T("address"),strValue);
			mEditAddress.SetWindowText(strValue);
		}
		else
		{
			CDialog::OnCancel();
		}
		rs.Close();
	}
	return FALSE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
HBRUSH CustomerNewDlg2::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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
void CustomerNewDlg2::OnBnClickedOk()
{
	CString strName,strTel,strAdr;
	mEditName.GetWindowText(strName);
	strName.Trim();
	if (strName.IsEmpty())
	{
		POSMessageBox(IDS_INPUTVIPNAME);
		return;
	}
	CString py;
	GenFirstPYLetter(strName,py);
	mEditPhone.GetWindowText(strTel);
	mEditAddress.GetWindowText(strAdr);
	strAdr.Replace(_T("\""),_T("\"\""));
	strAdr.Replace(_T("\'"),_T("\'\'"));
	CString strSQL;
	if (m_cusID>0)
	{
		strSQL.Format(_T("UPDATE customer SET customer_name=\'%s\',telephone_1=\'%s\',address=\'%s\',postcode=\'%s\'")
		_T(" WHERE customer_id=%d")
		,FormatDBStr(strName),strTel,FormatDBStr(strAdr),py,m_cusID);
	}
	else
	{
		strSQL.Format(_T("insert into customer(customer_name,telephone_1,address,postcode)")
		_T(" values(\'%s\',\'%s\',\'%s\',\'%s\');")
		,FormatDBStr(strName),strTel,FormatDBStr(strAdr),py);
	}
	theDB.ExecuteSQL(strSQL);
	OnOK();
}
void CustomerNewDlg2::OnPaint()
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
