// WebLoginDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "POSClient.h"
#include "WebLoginDlg.h"


// CWebLoginDlg 对话框

IMPLEMENT_DYNAMIC(CWebLoginDlg, CDialog)

CWebLoginDlg::CWebLoginDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWebLoginDlg::IDD, pParent)
{
	m_bDemo=FALSE;
}

CWebLoginDlg::~CWebLoginDlg()
{
}

void CWebLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDOK, m_btOK);
	DDX_Control(pDX, IDCANCEL, m_btCancel);
	DDX_Control(pDX, IDCANCEL2, m_btDemo);
}


BEGIN_MESSAGE_MAP(CWebLoginDlg, CDialog)
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	ON_BN_CLICKED(IDOK, &CWebLoginDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL2, &CWebLoginDlg::OnBnClickedCancel2)
END_MESSAGE_MAP()


// CWebLoginDlg 消息处理程序
BOOL CWebLoginDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	CString str2;
	m_btOK.SetImage(_T("Picture\\bt_ok.png"));
	m_btCancel.SetImage(_T("Picture\\bt_cancel.png"));
	m_btDemo.SetImage(_T("Picture\\bt_cancel.png"));
	m_btCancel.SetTextColor(DEFALUT_TXT_COLOR);
	m_btOK.SetTextColor(DEFALUT_TXT_COLOR);	
	m_btDemo.SetTextColor(DEFALUT_TXT_COLOR);	
	if (!theLang.m_bDefaultLang)
	{
		SetFont(&theLang.m_dialogFont);
		CWnd* pCtrl=GetDlgItem(IDOK);
		theLang.TranslateDlgItem(pCtrl,IDS_OK);
		pCtrl=GetDlgItem(IDCANCEL);
		theLang.TranslateDlgItem(pCtrl,IDS_CANCEL);
		pCtrl=GetDlgItem(IDCANCEL2);
		theLang.TranslateDlgItem(pCtrl,IDS_DEMOBTN);
	}
	
	return TRUE;
}
void CWebLoginDlg::OnBnClickedOk()
{
	JSONVALUE root;
	CString str,phone;
	GetDlgItemText(IDC_EDIT1,phone);
	root[_T("username")]=phone;
	GetDlgItemText(IDC_EDIT2,str);
	root[_T("password")]=str;
	JSONVALUE response;
	BOOL bOK=HttpPost(theApp.m_strCloudURL,80,_T("/client_bind_user/"),root,response);
	if(bOK)
	{
		int nResult=response[_T("result")].asInt();
		if(nResult==0)
		{
			JSONVALUE org;
			JSONVALUE& itemsArray=response[_T("orgs")];
			int i=0;
			itemsArray.At(i,org);
			theApp.m_strResId=org[_T("org__org_guid")].asCString();
			//更新餐厅ID和手机
			theApp.m_strPhone=phone;
			CString strSQL;
			strSQL.Format(_T("UPDATE webreport_setting SET cr_res_id=\"%s\",cr_res_pwd=\"%s\",edit_mode=1"),theApp.m_strResId,phone);
			theDB.ExecuteSQL(strSQL);
			//重置版本号
			strSQL.Format(_T("DELETE FROM www_version"));
			theDB.ExecuteSQL(strSQL);
			OnOK();
		}
		else
		{
			POSMessageBox(response[_T("error")].asCString());
		}
	}
}
HBRUSH CWebLoginDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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
void CWebLoginDlg::OnPaint()
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
void CWebLoginDlg::OnBnClickedCancel2()
{
	m_bDemo=TRUE;
	m_bTrainingMode=TRUE;
	OnOK();
}
