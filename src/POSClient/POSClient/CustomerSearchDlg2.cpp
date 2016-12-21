// ustomerSearchDlg2.cpp : 实现文件
//

#include "stdafx.h"
#include "POSClient.h"
#include "CustomerSearchDlg2.h"
#include "CustomerNewDlg2.h"
#include "WebDlg2.h"


// CustomerSearchDlg2 对话框

IMPLEMENT_DYNAMIC(CustomerSearchDlg2, CDialog)

CustomerSearchDlg2::CustomerSearchDlg2(CWnd* pParent /*=NULL*/)
	: CDialog(CustomerSearchDlg2::IDD, pParent)
	, m_strResult(_T(""))
{

}

CustomerSearchDlg2::~CustomerSearchDlg2()
{
}

void CustomerSearchDlg2::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_edit);
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Control(pDX, IDC_BUTTON_OK, m_btOK);
	DDX_Control(pDX, IDCANCEL, m_btCancel);
	DDX_Control(pDX, IDC_BUTTON_ADD, m_addButton);
	DDX_Control(pDX, IDC_BUTTON_EDIT, m_editButton);
	DDX_Control(pDX, IDC_BUTTON_SOFTKEY, m_softButton);
	DDX_Text(pDX, IDC_EDIT2, m_strResult);
}


BEGIN_MESSAGE_MAP(CustomerSearchDlg2, CDialog)
	ON_EN_CHANGE(IDC_EDIT1, &CustomerSearchDlg2::OnEnChangeEdit1)
	ON_BN_CLICKED(IDC_BUTTON_OK, &CustomerSearchDlg2::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CustomerSearchDlg2::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_EDIT, &CustomerSearchDlg2::OnBnClickedButtonEdit)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &CustomerSearchDlg2::OnLvnItemchangedList1)
	ON_BN_CLICKED(IDC_BUTTON_LOCATION, &CustomerSearchDlg2::OnBnClickedButtonLocation)
	ON_BN_CLICKED(IDC_BUTTON_SOFTKEY, &CustomerSearchDlg2::OnBnClickedButtonSoftkey)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CustomerSearchDlg2 消息处理程序
void CustomerSearchDlg2::OnEnChangeEdit1()
{
	// 刷新搜索显示
	CString strText;
	m_edit.GetWindowText(strText);
	Search(strText.Trim());
}
BOOL CustomerSearchDlg2::OnInitDialog()
{
	CDialog::OnInitDialog();
	CString str2;
	
	if (!theLang.m_bDefaultLang)
	{
		SetFont(&theLang.m_dialogFont);
		CWnd* pCtrl=GetDlgItem(IDC_BUTTON_OK);
		theLang.TranslateDlgItem(pCtrl,IDS_OK);
		pCtrl=GetDlgItem(IDCANCEL);
		theLang.TranslateDlgItem(pCtrl,IDS_CANCEL);
		pCtrl=GetDlgItem(IDC_BUTTON_ADD);
		theLang.TranslateDlgItem(pCtrl,IDS_ADDCUS);
		pCtrl=GetDlgItem(IDC_BUTTON_EDIT);
		theLang.TranslateDlgItem(pCtrl,IDS_EDIT);
		pCtrl=GetDlgItem(IDC_BUTTON_LOCATION);
		theLang.TranslateDlgItem(pCtrl,IDS_LOCATION);
		theLang.LoadString(str2,IDS_ADDCUSINFO);
		SetWindowText(str2);
	}
	m_btOK.SetImage(_T("Picture\\bt_ok.png"));
	m_btCancel.SetImage(_T("Picture\\bt_cancel.png"));
	m_addButton.SetImage(_T("Picture\\bt_orange_71.png"));
	m_editButton.SetImage(_T("Picture\\bt_orange_71.png"));
	m_softButton.SetImage(_T("Picture\\softboard.png"));
	m_addButton.ShowWindow(SW_SHOW);
	m_editButton.ShowWindow(SW_SHOW);
	m_edit.SetLimitText(20);
	m_edit.SetFocus();
	m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);

	theLang.LoadString(str2,IDS_FMNAME);
	m_list.InsertColumn(0,str2,LVCFMT_LEFT,150);
	theLang.LoadString(str2,IDS_PHONE);
	m_list.InsertColumn(1,str2,LVCFMT_LEFT,150);
	theLang.LoadString(str2,IDS_ADRESS);
	m_list.InsertColumn(3,str2,LVCFMT_LEFT,300);
	m_editButton.SetTextColor(DEFALUT_TXT_COLOR);
	m_addButton.SetTextColor(DEFALUT_TXT_COLOR);
	m_btOK.SetTextColor(DEFALUT_TXT_COLOR);
	m_btCancel.SetTextColor(DEFALUT_TXT_COLOR);
	Search(_T(""));
	return FALSE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
BOOL CustomerSearchDlg2::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message==WM_CHAR)
	{//限制输入的字符不包括特殊字符
		if (pMsg->wParam=='\\'||pMsg->wParam=='\''||pMsg->wParam=='\"')
		{
			return TRUE;
		}
	}
	return CDialog::PreTranslateMessage(pMsg);
}
void CustomerSearchDlg2::Search(CString strSearch)
{
	CString strSQL;
	if (strSearch.IsEmpty())
	{
		strSQL.Format(_T("SELECT * FROM customer WHERE card_status=0"));
	}
	else
	{
		strSQL.Format(_T("SELECT * FROM customer WHERE card_status=0 AND (telephone_1 like '%%%s%%' OR customer_name like '%%%s%%' or postcode like '%%%s%%')")
			,strSearch,strSearch,strSearch);
	}
	OpenDatabase();
	CRecordset rs(&theDB);
	rs.Open( CRecordset::forwardOnly,strSQL);
	m_list.DeleteAllItems();
	int i=0;
	CString strValue;
	while (!rs.IsEOF())
	{
		m_list.InsertItem(i,_T(""));
		rs.GetFieldValue(_T("customer_id"),strValue);
		long id=_wtol(strValue);
		m_list.SetItemData(i,id);
		rs.GetFieldValue(_T("customer_name"),strValue);
		m_list.SetItemText(i,0,strValue);
		rs.GetFieldValue(_T("telephone_1"),strValue);
		m_list.SetItemText(i,1,strValue);
		rs.GetFieldValue(_T("address"),strValue);
		m_list.SetItemText(i,2,strValue);
		i++;
		rs.MoveNext();
	}
}
void CustomerSearchDlg2::OnBnClickedOk()
{
	UpdateData(TRUE);
	CDialog::OnOK();
}

void CustomerSearchDlg2::OnBnClickedButtonAdd()
{
	CustomerNewDlg2 dlg;
	if(dlg.DoModal()==IDOK)
	{
		OnEnChangeEdit1();
	}
}

void CustomerSearchDlg2::OnBnClickedButtonEdit()
{
	POSITION pos=m_list.GetFirstSelectedItemPosition(); 
	if   (NULL   ==   pos) 
	{
		POSMessageBox(IDS_SELECTRECORD); 
		return; 
	}
	int   index   =   m_list.GetNextSelectedItem(pos);
	CustomerNewDlg2 dlg;
	dlg.m_cusID=m_list.GetItemData(index);
	if(dlg.DoModal()==IDOK)
	{
		OnEnChangeEdit1();
	}
}

void CustomerSearchDlg2::OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	if(pNMLV->uChanged==LVIF_STATE
		&&(pNMLV->uNewState&LVIS_SELECTED))
	{
		int nRow=pNMLV->iItem;
		m_strResult=m_list.GetItemText(nRow,0);
		m_strResult.AppendFormat(_T(",%s"),m_list.GetItemText(nRow,1));
		m_strPhone=m_list.GetItemText(nRow,1);
		m_strResult.AppendFormat(_T("\r\n%s"),m_list.GetItemText(nRow,2));
		UpdateData(FALSE);
	}
	*pResult = 0;
}

void CustomerSearchDlg2::OnBnClickedButtonLocation()
{
	try{
		UpdateData(TRUE);
		OpenDatabase();
		CString strURL;
		CRecordset rs(&theDB);
		rs.Open( CRecordset::forwardOnly,_T("SELECT macros_value FROM macros WHERE macros_name='MAP_ENGINE'"));
		if(rs.IsEOF())
		{
			strURL=_T("https://bing.com/maps?q=");
		}
		else
		{
			rs.GetFieldValue((short)0,strURL);
		}
		int index=m_strResult.ReverseFind('\n');
		CWebDlg2 dlg;
		dlg.m_strCurrentUrl.Format(_T("%s%s"),strURL,m_strResult.Right(m_strResult.GetLength()-index-1));
		dlg.DoModal();
	}catch(...)
	{
	}
}

void CustomerSearchDlg2::OnOK()
{
	int i=0;
}

void CustomerSearchDlg2::OnBnClickedButtonSoftkey()
{
	ShellExecute(GetSafeHwnd(), NULL, _T("SoftBoard.exe"), NULL, NULL,SW_NORMAL);
	m_edit.SetFocus();
}

void CustomerSearchDlg2::OnPaint()
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
