// ModifyDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "POSClient.h"
#include "ModifyDlg.h"


// ModifyDlg 对话框

IMPLEMENT_DYNAMIC(ModifyDlg, CDialog)

ModifyDlg::ModifyDlg(CWnd* pParent /*=NULL*/)
: CDialog(ModifyDlg::IDD, pParent)
{
}

ModifyDlg::~ModifyDlg()
{
	delete m_bpButtonItem[0];
	delete m_bpButtonItem[1];
}

void ModifyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDCANCEL, m_cancelBt);
	DDX_Control(pDX, IDC_BUTTON1, m_button[0]);
	DDX_Control(pDX, IDC_BUTTON2, m_button[1]);
	DDX_Control(pDX, IDC_BUTTON3, m_button[2]);
	DDX_Control(pDX, IDC_BUTTON4, m_button[3]);
	DDX_Control(pDX, IDC_BUTTON5, m_button[4]);
}


BEGIN_MESSAGE_MAP(ModifyDlg, CDialog)
	ON_COMMAND_RANGE(IDC_BUTTON1,IDC_BUTTON5,&ModifyDlg::OnBnClickedUnit)
	ON_BN_CLICKED(IDCANCEL, &ModifyDlg::OnBnClickedCancel)
	ON_WM_PAINT()
END_MESSAGE_MAP()

// ModifyDlg 消息处理程序

BOOL ModifyDlg::OnInitDialog()
{
	try{
		CDialog::OnInitDialog();
		CString strTmp,str2;
		theLang.LoadString(str2,IDS_MODIFY);
		strTmp.Format(_T("%s [%s]"),str2,m_item->item_name);
		this->SetWindowText(strTmp);
		theLang.LoadString(str2,IDS_CANCEL);
		m_cancelBt.SetWindowText(str2);
		theLang.LoadString(str2,IDS_DISH);
		GetDlgItem(IDC_BUTTON1)->SetWindowText(str2);
		m_cancelBt.SetImage(_T("Picture\\bt_cancel.png"));
		m_bpButtonItem[0]=Gdiplus::Image::FromFile(_T("Picture\\class\\unit.png"));
		m_bpButtonItem[1]=Gdiplus::Image::FromFile(_T("Picture\\class\\unit_.png"));
		LOGFONT m_tLogFont;
		memset(&m_tLogFont,0,sizeof(LOGFONT));
		m_tLogFont.lfHeight	=ScaleY(27);
		wcscpy_s(m_tLogFont.lfFaceName, _T("Microsoft YaHei"));
		//从数据库中初始化规格
		OpenDatabase();
		CRecordset rs( &theDB);
		CString strSQL;
		strSQL.Format(_T("SELECT * FROM menu_item WHERE item_id=\'%d\';"),m_item->item_id);
		rs.Open( CRecordset::forwardOnly,strSQL);
		if(!rs.IsEOF())
		{
			CTime time=CTime::GetCurrentTime();
			CString strVal;
			CString field1,field2;
			BOOL bDefault=TRUE;
			for (int i=0;i<5;i++)
			{
				field1.Format(_T("price_%d"),i+1);
				rs.GetFieldValue(field1,strVal);
				m_prices[i]=_wtof(strVal);
				m_button[i].m_strBottom.Format(_T("%s%g"),theApp.CURRENCY_SYMBOL,m_prices[i]);
				//WCHAR c=0x2460+i;
				//m_button[i].m_strTop.Format(_T("%c"),c);
				m_button[i].SetFont(&m_tLogFont);
				field2.Format(_T("unit_%d"),i+1);
				rs.GetFieldValue(field2,m_unit[i]);
				if (m_unit[i].GetLength()!=0)
				{
					m_button[i].SetWindowText(m_unit[i]);
					m_button[i].ShowWindow(SW_SHOW);
					bDefault=FALSE;
				}
				if (m_prices[i]>0.01)
				{
					m_button[i].ShowWindow(SW_SHOW);
				}
			}
			if (bDefault)
			{
				m_button[0].ShowWindow(SW_SHOW);
			}
		}
		for(int i=0;i<5;i++)
			m_button[i].SetImages(m_bpButtonItem[0],m_bpButtonItem[1],false);
	m_cancelBt.SetTextColor(DEFALUT_TXT_COLOR);
	m_button[0].SetTextColor(DEFALUT_TXT_COLOR);
	m_button[1].SetTextColor(DEFALUT_TXT_COLOR);
	m_button[2].SetTextColor(DEFALUT_TXT_COLOR);
	m_button[3].SetTextColor(DEFALUT_TXT_COLOR);
	m_button[4].SetTextColor(DEFALUT_TXT_COLOR);
	}
	catch(CDBException* e)
	{
		LOG4CPLUS_ERROR(log_pos,(LPCTSTR)e->m_strError);
		e->Delete();
	}
	catch(...)
	{
		LOG4CPLUS_ERROR(log_pos,"Catch Exception GetLastError="<<GetLastError());
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void ModifyDlg::OnBnClickedUnit(UINT uID)
{
	if(!m_button[uID-IDC_BUTTON1].IsWindowVisible())
		return;
	//套餐内不改价
	if (m_item->n_belong_item>=0)
	{
		m_item->item_price=m_prices[uID-IDC_BUTTON1];
	}
	wcsncpy_s(m_item->unit,m_unit[uID-IDC_BUTTON1],9);
	CDialog::OnOK();
}

void ModifyDlg::OnBnClickedCancel()
{
	OnCancel();
}

BOOL ModifyDlg::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message==WM_KEYDOWN)
	{
		
		if ((pMsg->wParam>=VK_F1&&pMsg->wParam<=VK_F5))
		{
			OnBnClickedUnit(pMsg->wParam-VK_F1+IDC_BUTTON1);
		}
		//连续刷条码时，不能因为弹出规格框阻止继续扫码
// 		else if ((pMsg->wParam>='A'&&pMsg->wParam<='Z')||(pMsg->wParam>='0'&&pMsg->wParam<='9')||(pMsg->wParam>=VK_NUMPAD0&&pMsg->wParam<=VK_NUMPAD9))
// 		{
// 			OnBnClickedUnit(IDC_BUTTON1);
// 			//转给点菜界面处理
// 			if(m_pParentWnd){
// 				::PostMessage(m_pParentWnd->m_hWnd,WM_KEYDOWN,pMsg->wParam,pMsg->lParam);
// 			//pWnd->PostMessage();
// 			}
// 		}
	}
	return CDialog::PreTranslateMessage(pMsg);
}

void ModifyDlg::OnPaint()
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
