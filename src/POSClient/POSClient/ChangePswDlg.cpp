// hangePswDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "POSClient.h"
#include "ChangePswDlg.h"


// ChangePswDlg 对话框

IMPLEMENT_DYNAMIC(ChangePswDlg, CDialog)

ChangePswDlg::ChangePswDlg(CWnd* pParent /*=NULL*/)
	: CDialog(ChangePswDlg::IDD, pParent)
{

}

ChangePswDlg::~ChangePswDlg()
{
}

void ChangePswDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDOK, m_btOK);
	DDX_Control(pDX, IDCANCEL, m_btCancel);
	DDX_Control(pDX, IDC_BUTTON_SOFTKEY, m_softButton);
}


BEGIN_MESSAGE_MAP(ChangePswDlg, CDialog)
	ON_BN_CLICKED(IDOK, &ChangePswDlg::OnBnClickedOk)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON_SOFTKEY, &ChangePswDlg::OnBnClickedButtonSoftkey)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// ChangePswDlg 消息处理程序

void ChangePswDlg::OnBnClickedOk()
{
	CString text,text2;
	((CEdit*)GetDlgItem(IDC_EDIT2))->GetWindowText(text);
	((CEdit*)GetDlgItem(IDC_EDIT3))->GetWindowText(text2);
	if (text!=text2)
	{
		POSMessageBox(IDS_NOTSAMEPSW);
		return;
	}
	((CEdit*)GetDlgItem(IDC_EDIT1))->GetWindowText(text);
	OpenDatabase(TRUE);
	CRecordset rs(&theDB);
	CString strSQL;
	strSQL.Format(_T("SELECT password_id FROM employee WHERE employee_id=\'%s\';"),theApp.m_strUserID);
	if(!rs.Open(CRecordset::forwardOnly,strSQL))
		return;
	if (!rs.IsEOF())
	{
		CString psw;
		rs.GetFieldValue(_T("password_id"),psw);
		if(psw!=text)
		{
			POSMessageBox(IDS_WRONGPSW2);
			return;
		}
	}
	rs.Close();
	strSQL.Format(_T("UPDATE employee SET password_id=\'%s\' WHERE employee_id=\'%s\'"),text2,theApp.m_strUserID);
	theDB.ExecuteSQL(strSQL);
	OnOK();
}

BOOL ChangePswDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	CString str2;
	m_btOK.SetImage(_T("Picture\\bt_ok.png"));
	m_btCancel.SetImage(_T("Picture\\bt_cancel.png"));
	m_softButton.SetImage(_T("Picture\\softboard.png"));
	m_btCancel.SetTextColor(DEFALUT_TXT_COLOR);
	m_btOK.SetTextColor(DEFALUT_TXT_COLOR);	
	if (!theLang.m_bDefaultLang)
	{
		SetFont(&theLang.m_dialogFont);
		CWnd* pCtrl=GetDlgItem(IDOK);
		theLang.TranslateDlgItem(pCtrl,IDS_OK);
		pCtrl=GetDlgItem(IDCANCEL);
		theLang.TranslateDlgItem(pCtrl,IDS_CANCEL);
		pCtrl=GetDlgItem(IDC_STATIC1);
		theLang.TranslateDlgItem(pCtrl,IDS_CURRENTPSW);
		pCtrl=GetDlgItem(IDC_STATIC2);
		theLang.TranslateDlgItem(pCtrl,IDS_NEWPSW);
		pCtrl=GetDlgItem(IDC_STATIC3);
		theLang.TranslateDlgItem(pCtrl,IDS_REPEATPSW);
		theLang.LoadString(IDS_CHANGEPSW,str2);
		SetWindowText(str2);
	}
	((CEdit*)GetDlgItem(IDC_EDIT2))->SetLimitText(20);
	((CEdit*)GetDlgItem(IDC_EDIT3))->SetLimitText(20);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

HBRUSH ChangePswDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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

void ChangePswDlg::OnBnClickedButtonSoftkey()
{
	ShellExecute(GetSafeHwnd(), NULL, _T("SoftBoard.exe"), NULL, NULL,SW_NORMAL);
	((CEdit*)GetDlgItem(IDC_EDIT1))->SetFocus();
}

void ChangePswDlg::OnPaint()
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
