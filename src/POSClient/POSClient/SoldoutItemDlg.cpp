// SoldoutItemDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "POSClient.h"
#include "SoldoutItemDlg.h"
#include "NumberInputDlg.h"


// SoldoutItemDlg 对话框

IMPLEMENT_DYNAMIC(SoldoutItemDlg, CDialog)

SoldoutItemDlg::SoldoutItemDlg(CWnd* pParent /*=NULL*/)
	: CDialog(SoldoutItemDlg::IDD, pParent)
{

}

SoldoutItemDlg::~SoldoutItemDlg()
{
}

void SoldoutItemDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, mComboBox);
	DDX_Control(pDX, IDC_EDIT1, m_numEdit);
	DDX_Control(pDX, IDC_CHECK1, mCheckBox);
	DDX_Control(pDX, IDC_BUTTON_NUM, mButtonNum);
	DDX_Control(pDX, IDOK, m_btOK);
	DDX_Control(pDX, IDCANCEL, m_btCancel);
}


BEGIN_MESSAGE_MAP(SoldoutItemDlg, CDialog)
	ON_CBN_SELCHANGE(IDC_COMBO1, &SoldoutItemDlg::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON_NUM, &SoldoutItemDlg::OnBnClickedButtonNum)
	ON_BN_CLICKED(IDOK, &SoldoutItemDlg::OnBnClickedOk)
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
END_MESSAGE_MAP()


// SoldoutItemDlg 消息处理程序

BOOL SoldoutItemDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	try
	{
		CString str2;
		m_btOK.SetImage(_T("Picture\\bt_ok.png"));
		m_btCancel.SetImage(_T("Picture\\bt_cancel.png"));
		if (!theLang.m_bDefaultLang)
		{
			CWnd* pCtrl=GetDlgItem(IDOK);
			theLang.TranslateDlgItem(pCtrl,181);
			pCtrl=GetDlgItem(IDCANCEL);
			theLang.TranslateDlgItem(pCtrl,182);
			theLang.LoadString(str2,IDS_SOLDSETTING);
			SetWindowText(str2);
			pCtrl=GetDlgItem(IDC_STATIC1);
			theLang.TranslateDlgItem(pCtrl,IDS_LIMITAVAL);
			pCtrl=GetDlgItem(IDC_STATIC2);
			theLang.TranslateDlgItem(pCtrl,IDS_LIMITTYPE);
			pCtrl=GetDlgItem(IDC_STATIC_CHECK);
			theLang.TranslateDlgItem(pCtrl,IDS_RECOVERAFTER);
		}
		mButtonNum.SetIcon(AfxGetApp()->LoadIcon(IDI_ICONNUM));
		theLang.LoadString(str2,IDS_SALEABLE);
		mComboBox.AddString(str2);
		theLang.LoadString(str2,IDS_MANUALSOLD);
		mComboBox.AddString(str2);
		theLang.LoadString(str2,IDS_NUMSOLD);
		mComboBox.AddString(str2);
		theLang.LoadString(str2,IDS_TODAYSOLD);
		mComboBox.AddString(str2);
		m_numEdit.SetLimitText(10);
		m_btOK.SetTextColor(DEFALUT_TXT_COLOR);
		m_btCancel.SetTextColor(DEFALUT_TXT_COLOR);
		OpenDatabase();
		CRecordset rs( &theDB);
		CString strSQL;
		strSQL.Format(_T("SELECT * FROM bargain_price_item where bargain_item_number=%d;"),m_nItemId);
		rs.Open(CRecordset::forwardOnly,strSQL);
		if (!rs.IsEOF())
		{
			CDBVariant variant;
			CString str;
			rs.GetFieldValue(_T("bargain_stype"),variant);
			mComboBox.SetCurSel(variant.m_iVal);
			if (variant.m_iVal==2)
			{//数量沽清
				rs.GetFieldValue(_T("is_every_day"),variant);
				if (variant.m_boolVal)
				{
					mCheckBox.SetCheck(TRUE);
					rs.GetFieldValue(_T("bargain_num"),str);
					m_numEdit.SetWindowText(str);
				}
				else
				{
					rs.GetFieldValue(_T("bargain_num_cur"),str);
					m_numEdit.SetWindowText(str);
				}
			}
			rs.GetFieldValue(_T("bargain_item_name"),str);
			SetWindowText(str);
			OnCbnSelchangeCombo1();
		}
		rs.Close();
	}
	catch(CDBException* e)
	{
		LOG4CPLUS_ERROR(log_pos,(LPCTSTR)e->m_strError);
		AfxMessageBox(e->m_strError,MB_ICONEXCLAMATION);
		e->Delete();
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void SoldoutItemDlg::OnCbnSelchangeCombo1()
{
	CWnd* pWnd=GetDlgItem(IDC_STATIC1);
	if (mComboBox.GetCurSel()==2)
	{
		pWnd->ShowWindow(SW_SHOW);
		mButtonNum.ShowWindow(SW_SHOW);
		mCheckBox.ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_CHECK)->ShowWindow(SW_SHOW);
		m_numEdit.ShowWindow(SW_SHOW);
	}
	else
	{
		pWnd->ShowWindow(SW_HIDE);
		mButtonNum.ShowWindow(SW_HIDE);
		mCheckBox.ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_CHECK)->ShowWindow(SW_HIDE);
		m_numEdit.ShowWindow(SW_HIDE);
	}
}

void SoldoutItemDlg::OnBnClickedButtonNum()
{
	NumberInputDlg dlg;
	if(dlg.DoModal()==IDOK)
	{
		int price=_wtoi(dlg.m_strNum);
		if (price>999999)
		{
			POSMessageBox(IDS_TOOMUCH);
			return;
		}
		m_numEdit.SetWindowText(dlg.m_strNum);
	}
}

void SoldoutItemDlg::OnBnClickedOk()
{
	CString strSql;
	int sel=mComboBox.GetCurSel();
	if (sel==2)
	{
		CString str;
		m_numEdit.GetWindowText(str);
		double num=_wtof(str);
		strSql.Format(_T("UPDATE bargain_price_item SET bargain_stype=%d,bargain_num=%f,bargain_num_cur=%f,")
			_T("is_every_day=%d WHERE bargain_item_number=%d;")
			,sel,num,num,mCheckBox.GetCheck(),m_nItemId);
		theDB.ExecuteSQL(strSql);
	}
	else if (sel==0)
	{//取消沽清
		strSql.Format(_T("DELETE FROM bargain_price_item WHERE bargain_item_number=%d;")
			,m_nItemId);
		theDB.ExecuteSQL(strSql);
	}
	else
	{
		strSql.Format(_T("UPDATE bargain_price_item SET bargain_stype=%d WHERE bargain_item_number=%d;")
			,sel,m_nItemId);
		theDB.ExecuteSQL(strSql);
	}
	OnOK();
}

HBRUSH SoldoutItemDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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
void SoldoutItemDlg::OnPaint()
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
