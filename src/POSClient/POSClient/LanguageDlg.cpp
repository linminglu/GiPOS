// LanguageDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "POSClient.h"
#include "LanguageDlg.h"


// CLanguageDlg 对话框

IMPLEMENT_DYNAMIC(CLanguageDlg, CDialog)

CLanguageDlg::CLanguageDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLanguageDlg::IDD, pParent)
{

}

CLanguageDlg::~CLanguageDlg()
{
	m_itemButtons.clear();
	delete hbmp;
	delete hbmp1;
}

void CLanguageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CLanguageDlg, CDialog)
	ON_COMMAND_RANGE(IDC_CLASS_BUTTON,IDC_CLASS_BUTTON+99, &CLanguageDlg::OnBnClickedRadio)
END_MESSAGE_MAP()


// CLanguageDlg 消息处理程序

BOOL CLanguageDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	int lcount=GetPrivateProfileInt(_T("LANGUAGES"),_T("COUNT"), 0,_T(".\\config.ini"));
	if(lcount>1)
	{
		
		int width,height;
		hbmp=Gdiplus::Image::FromFile(_T("Picture\\bt_remind.png"));
		hbmp1=Gdiplus::Image::FromFile(_T("Picture\\bt_remind_.png"));
		width=230;//img.GetWidth();
		height=hbmp->GetHeight();
		CRect _rect=CRect(0,0,width,height);
		for(int i=1;i<=lcount;i++)
		{
			CString lang,str;
			str.Format(_T("Lang%d"),i);
			::GetPrivateProfileString(_T("LANGUAGES"),str,_T("Default"),lang.GetBuffer(40),40,_T(".\\config.ini"));
			lang.ReleaseBuffer();
			CRoundButton2* pBtn=new CRoundButton2;
			pBtn->Create(lang, WS_CHILD|WS_VISIBLE, _rect,this,IDC_CLASS_BUTTON+i);
			//pBtn->SetFont(GetFont());
			pBtn->SetImages(hbmp,hbmp1,false);
			_rect.top+=height;
			_rect.bottom+=height;
			m_itemButtons.push_back(pBtn);
		}
		
		CRoundButton2* pBtn=new CRoundButton2;
		pBtn->Create(_T("Cancel"), WS_CHILD|WS_VISIBLE, _rect,this,IDCANCEL);
		pBtn->SetImage(_T("Picture\\bt_exit2.png"));
		m_itemButtons.push_back(pBtn);
		MoveWindow(0,0,width+5,_rect.bottom+30);
		this->CenterWindow();
	}
	else
	{
		CDialog::OnCancel();
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
void CLanguageDlg::OnBnClickedRadio(UINT uID)
{
	CButton* pCb =(CButton*)GetDlgItem(uID);
	if(pCb)
	{
		CString lang;
		pCb->GetWindowText(lang);
		if(theLang.m_strLang==lang)
		{
			CDialog::OnCancel();
		}
		theLang.Initialize(lang);
		theLang.ReadButtonName(lang);
		WritePrivateProfileString(_T("POS"),_T("LANGUAGE"),lang,_T(".\\config.ini"));
		CDialog::OnOK();
	}
}