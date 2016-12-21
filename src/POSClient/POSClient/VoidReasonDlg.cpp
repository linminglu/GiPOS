// VoidReasonDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "POSClient.h"
#include "VoidReasonDlg.h"


// CVoidReasonDlg 对话框

IMPLEMENT_DYNAMIC(CVoidReasonDlg, CDialog)

CVoidReasonDlg::CVoidReasonDlg(CWnd* pParent /*=NULL*/)
: CDialog(CVoidReasonDlg::IDD, pParent)
{

}

CVoidReasonDlg::~CVoidReasonDlg()
{
	::DeleteObject(m_bpBackgrd);
}

void CVoidReasonDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Control(pDX, IDOK, m_btnOK);
	DDX_Control(pDX, IDCANCEL, m_btCancel);
}


BEGIN_MESSAGE_MAP(CVoidReasonDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CVoidReasonDlg::OnBnClickedOk)
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CVoidReasonDlg 消息处理程序

void CVoidReasonDlg::OnBnClickedOk()
{
	int index=m_list.GetCurSel();
	if (index==-1)
	{
		POSMessageBox(IDS_VOIDREASON);
		return;
	}
	m_list.GetText(index,m_strReason);
	OnOK();
}

BOOL CVoidReasonDlg::OnInitDialog()
{
	try{
		CDialog::OnInitDialog();
		CImage cimg;
		if(cimg.Load(_T("Picture\\tablestatus.png"))==S_OK)
		{
			m_x=cimg.GetWidth();
			m_y=cimg.GetHeight();
			m_bpBackgrd=cimg.Detach();
		}
		int x=122,y=58;
		m_btnOK.SetImage(_T("Picture\\bt_ok.png"));
		m_btCancel.SetImage(_T("Picture\\bt_cancel.png"));
		
		CString str2;
		theLang.LoadString(str2,IDS_OK);
		m_btnOK.SetWindowText(str2);
		theLang.LoadString(str2,IDS_CANCEL);
		m_btCancel.SetWindowText(str2);
	m_btCancel.SetTextColor(DEFALUT_TXT_COLOR);
	m_btnOK.SetTextColor(DEFALUT_TXT_COLOR);

		theLang.LoadString(str2,IDS_VOIDREASON);
		GetDlgItem(IDC_STATIC)->SetWindowText(str2);
		OpenDatabase();
		CRecordset rs( &theDB);
		CString strSQL;
		strSQL.Format(_T("SELECT reason_id,reason_name FROM reasons WHERE is_returns=1 ORDER BY reason_id;"));
		rs.Open( CRecordset::forwardOnly,strSQL);
		while(!rs.IsEOF())
		{
			CString line,strReason;
			rs.GetFieldValue(_T("reason_name"), strReason);
			m_list.AddString(strReason);
			rs.MoveNext();
		}
	}
	catch(CDBException* e)
	{
		LOG4CPLUS_ERROR(log_pos,(LPCTSTR)e->m_strError);
		e->Delete();
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

BOOL CVoidReasonDlg::OnEraseBkgnd(CDC* pDC)
{
	if (m_bpBackgrd==NULL)
	{
		return FALSE;
	}
	CRect rect;
	GetClientRect(&rect);
	CDC MemDc;
	MemDc.CreateCompatibleDC(pDC);
	HGDIOBJ hOldBmp = MemDc.SelectObject(m_bpBackgrd);
	pDC->SetStretchBltMode(HALFTONE);
	pDC->StretchBlt(0,0,rect.Width(),rect.Height(),&MemDc,0,0,m_x,m_y,SRCCOPY);
	//MemDc.SelectObject(hOldBmp);
	return TRUE;
}
HBRUSH CVoidReasonDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	if(nCtlColor==CTLCOLOR_STATIC)
	{
		pDC->SetTextColor(m_dTextColor);
		pDC->SetBkMode(TRANSPARENT);
		return (HBRUSH)::GetStockObject(NULL_BRUSH); //返回此画刷可以使静态文本透明
	}
	return   hbr; 
	
}