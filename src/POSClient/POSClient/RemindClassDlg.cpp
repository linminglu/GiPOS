// RemindClassDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "POSClient.h"
#include "RemindClassDlg.h"


// CRemindClassDlg 对话框

IMPLEMENT_DYNAMIC(CRemindClassDlg, CDialog)

CRemindClassDlg::CRemindClassDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRemindClassDlg::IDD, pParent)
{
	m_Class=-1;
}

CRemindClassDlg::~CRemindClassDlg()
{
	for (std::vector<CButton*>::iterator iter = m_itemButtons.begin(); iter!= m_itemButtons.end();iter++)
	{
		CButton *b = (*iter);
		b->DestroyWindow();
		delete b;
	}
	m_itemButtons.clear();

	delete hbmp;
	delete hbmp1;
}

void CRemindClassDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CRemindClassDlg, CDialog)
	ON_COMMAND_RANGE(IDC_CLASS_BUTTON,IDC_CLASS_BUTTON+999, &CRemindClassDlg::OnBnClickedRadio)
END_MESSAGE_MAP()


// CRemindClassDlg 消息处理程序

BOOL CRemindClassDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	try
	{
		CString strSQL;
		OpenDatabase();
		CRecordset rs( &theDB);
		strSQL.Format(_T("SELECT * FROM family_group LIMIT 12"));
		rs.Open(CRecordset::forwardOnly,strSQL);
		hbmp=Gdiplus::Image::FromFile(_T("Picture\\bt_remind.png"));
		hbmp1=Gdiplus::Image::FromFile(_T("Picture\\bt_remind_.png"));
		int width=230;
		int height=hbmp->GetHeight();
		CRect _rect=CRect(0,0,width,height);
		while (!rs.IsEOF())
		{
			CDBVariant variant;
			CString class_name;
			rs.GetFieldValue(_T("family_group_id"),variant);
			rs.GetFieldValue(_T("family_group_name"),class_name);
			CRoundButton2* pBtn=new CRoundButton2;
			pBtn->Create(class_name, WS_CHILD|WS_VISIBLE, _rect,this,IDC_CLASS_BUTTON+variant.m_iVal);
			pBtn->SetImages(hbmp,hbmp1,false);
			//pBtn->SetTextColor(DEFALUT_TXT_COLOR);
			_rect.top+=height;
			_rect.bottom+=height;
			m_itemButtons.push_back(pBtn);
			rs.MoveNext();
		}
		rs.Close();

		CRoundButton2* pBtn=new CRoundButton2;
		pBtn->Create(_T("Cancel"), WS_CHILD|WS_VISIBLE, _rect,this,IDCANCEL);
		pBtn->SetTextColor(DEFALUT_TXT_COLOR);
		pBtn->SetImage(_T("Picture\\bt_exit2.png"));
		
		m_itemButtons.push_back(pBtn);
		MoveWindow(0,0,width+5,_rect.bottom+30);
		this->CenterWindow();
	}
	catch(CDBException* e)
	{
		LOG4CPLUS_ERROR(log_pos,(LPCTSTR)e->m_strError);
		e->Delete();
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
void CRemindClassDlg::OnBnClickedRadio(UINT uID)
{
	m_Class=uID-IDC_CLASS_BUTTON;
	CDialog::OnOK();
}