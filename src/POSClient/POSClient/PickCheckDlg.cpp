// PickCheck.cpp : 实现文件
//

#include "stdafx.h"
#include "POSClient.h"
#include "PickCheckDlg.h"
#include "NumberInputDlg.h"


// CPickCheck 对话框

IMPLEMENT_DYNAMIC(CPickCheckDlg, CDialog)

CPickCheckDlg::CPickCheckDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPickCheckDlg::IDD, pParent)
{
	m_nHeadid=0;
}

CPickCheckDlg::~CPickCheckDlg()
{
}

void CPickCheckDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, mList1);
	DDX_Control(pDX, IDC_LIST2, mList2);
	DDX_Control(pDX, IDC_EDIT2, m_editCtrl);
	DDX_Control(pDX, IDC_BUTTON_NUM, mButtonNum);
	DDX_Control(pDX, IDOK, m_btOK);
	DDX_Control(pDX, IDCANCEL, m_btCancel);
}


BEGIN_MESSAGE_MAP(CPickCheckDlg, CDialog)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &CPickCheckDlg::OnLvnItemchangedList1)
	ON_BN_CLICKED(IDOK, &CPickCheckDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_NUM, &CPickCheckDlg::OnBnClickedButtonNum)
	ON_EN_CHANGE(IDC_EDIT2, &CPickCheckDlg::OnEnChangeEdit2)
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CPickCheck 消息处理程序

BOOL CPickCheckDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	HICON hIcon=AfxGetApp()->LoadIcon(IDI_ICONNUM);
	mButtonNum.SetIcon(hIcon);
 	m_btOK.SetTextColor(DEFALUT_TXT_COLOR);
	m_btCancel.SetTextColor(DEFALUT_TXT_COLOR);
	CString str2;
	m_btOK.SetImage(_T("Picture\\bt_ok.png"));
	m_btCancel.SetImage(_T("Picture\\bt_cancel.png"));
	if(!theLang.m_bDefaultLang)
	{
		theLang.LoadString(str2,IDS_OK);
		m_btOK.SetWindowText(str2);
		theLang.LoadString(str2,IDS_CANCEL);
		m_btCancel.SetWindowText(str2);
		CWnd* pCtrl=GetDlgItem(IDC_STATIC1);
		theLang.TranslateDlgItem(pCtrl,IDS_INPUTCHKNUM);
		theLang.LoadString(str2,IDS_PICKCHKQ);
		SetWindowText(str2);
	}

	mList1.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	theLang.LoadString(str2,IDS_CHKNUM);
	mList1.InsertColumn(0,str2,LVCFMT_LEFT,80);
	theLang.LoadString(str2,IDS_OPENTIME);
	mList1.InsertColumn(1,str2,LVCFMT_LEFT,170);
	theLang.LoadString(str2,IDS_AMOUNT);
	mList1.InsertColumn(2,str2,LVCFMT_LEFT,80);
	theLang.LoadString(str2,IDS_CHKNAME2);
	mList1.InsertColumn(3,str2,LVCFMT_LEFT,80);

	mList2.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	theLang.LoadString(str2,IDS_ITEMID);
	mList2.InsertColumn(0,str2,LVCFMT_LEFT,100);
	theLang.LoadString(str2,IDS_ITEMNAME);
	mList2.InsertColumn(1,str2,LVCFMT_LEFT,150);
	theLang.LoadString(str2,IDS_UNIT);
	mList2.InsertColumn(2,str2,LVCFMT_LEFT,100);
	theLang.LoadString(str2,IDS_NUM);
	mList2.InsertColumn(3,str2,LVCFMT_LEFT,80);
	theLang.LoadString(str2,IDS_PRICE);
	mList2.InsertColumn(4,str2,LVCFMT_LEFT,80);
	CString strSQL;
	strSQL.Format(_T("SELECT * FROM order_head WHERE table_id=-1 AND order_head_id<>%d"),m_nFilter);
	ShowOrderheads(strSQL);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

HBRUSH CPickCheckDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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
void CPickCheckDlg::ShowOrderheads(CString strSQL)
{
	mList1.DeleteAllItems();
	m_nHeadid=0;
	CRecordset rs( &theDB);
	if(!rs.Open(-1,strSQL))
	{
		LOG4CPLUS_ERROR(log_pos,"CRecordset Open Failed");
		return;
	}
	while(!rs.IsEOF())
	{
		CString strValue;
		CDBVariant variant;
		int nRow=mList1.InsertItem(0, _T(""));
		rs.GetFieldValue(_T("order_head_id"),variant);
		mList1.SetItemData(nRow,variant.m_lVal);

		rs.GetFieldValue(_T("check_number"),strValue);
		mList1.SetItemText(nRow,0,strValue);
		rs.GetFieldValue(_T("order_start_time"),strValue);
		mList1.SetItemText(nRow,1,strValue);
		rs.GetFieldValue(_T("should_amount"),strValue);
		mList1.SetItemText(nRow,2,strValue);
		rs.GetFieldValue(_T("check_name"),strValue);
		mList1.SetItemText(nRow,3,strValue);
		
		rs.MoveNext();
	}
	rs.Close();
	//m_nActive=-1;
	mList1.SetItemState(0,LVIS_SELECTED,LVIS_SELECTED |LVIS_FOCUSED);
}


void CPickCheckDlg::OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	if(pNMLV->uChanged==LVIF_STATE
		&&(pNMLV->uNewState&LVIS_SELECTED))
	{
		int nRow=pNMLV->iItem;
		m_nHeadid=mList1.GetItemData(nRow);
		try{
			mList2.DeleteAllItems();
			CString strSQL;
			strSQL.Format(_T("SELECT * FROM order_detail WHERE order_head_id=\'%d\' AND is_return_item=0;"),m_nHeadid);
			CRecordset rs( &theDB);
			if(!rs.Open(-1,strSQL))
			{
				LOG4CPLUS_ERROR(log_pos,"CRecordset Open Failed");
				return;
			}
			while(!rs.IsEOF())
			{
				CString strValue;
				CDBVariant variant;
				int nRow=mList2.InsertItem(mList2.GetItemCount(), _T(""));
				rs.GetFieldValue(_T("menu_item_id"),strValue);
				int id=_wtol(strValue);
				if(id>0)
					mList2.SetItemText(nRow,0,strValue);
				rs.GetFieldValue(_T("menu_item_name"),strValue);
				mList2.SetItemText(nRow,1,strValue);
				rs.GetFieldValue(_T("unit"),strValue);
				mList2.SetItemText(nRow,2,strValue);
				rs.GetFieldValue(_T("quantity"),strValue);
				mList2.SetItemText(nRow,3,strValue);
				rs.GetFieldValue(_T("actual_price"),strValue);
				mList2.SetItemText(nRow,4,strValue);

				rs.MoveNext();
			}
			rs.Close();

		}catch(...)
		{
		}
	}
	*pResult = 0;
}

void CPickCheckDlg::OnBnClickedOk()
{
	POSITION   pos   =   mList1.GetFirstSelectedItemPosition();
	if(NULL   ==   pos)
	{
		POSMessageBox(IDS_SELECTRECORD); 
		return; 
	}
	OnOK();
}

void CPickCheckDlg::OnBnClickedButtonNum()
{
	NumberInputDlg dlg;
	if(dlg.DoModal()==IDOK)
	{
		m_editCtrl.SetWindowText(dlg.m_strNum);
	}
}

void CPickCheckDlg::OnEnChangeEdit2()
{
	CString strNum,strSQL;
	m_editCtrl.GetWindowText(strNum);
	strSQL.Format(_T("SELECT * FROM order_head WHERE table_id=-1 AND order_head_id<>%d AND ")
		_T("(check_number LIKE \'%%%s%%\' OR check_name LIKE \'%s%%\')")
		,m_nFilter,strNum,strNum);
	ShowOrderheads(strSQL);
}

void CPickCheckDlg::OnPaint()
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
