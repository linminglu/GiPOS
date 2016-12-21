// PosPage.cpp : 实现文件
//

#include "stdafx.h"
#include "POSClient.h"
#include "PosPage.h"


// CPosPage

IMPLEMENT_DYNAMIC(CPosPage, CDialog)

CPosPage::CPosPage(int nId)
: CDialog(nId)
{
	m_nID=nId;
	m_nPrePage=-1;
	m_x=1024;
	m_y=768;
}

CPosPage::~CPosPage()
{
	m_btnCtrl.ReleaseBtn();
	::DeleteObject(m_bpBackgrd);
}
void CPosPage::OnSetActive()
{
}
BOOL CPosPage::LockScreen()
{
	return TRUE;
}

BEGIN_MESSAGE_MAP(CPosPage, CDialog)
	ON_COMMAND_RANGE(IDC_BUTTON_NEXTPAGE,IDC_BUTTON_NEXTPAGE+50,&CPosPage::OnNextPage)
END_MESSAGE_MAP()



// CPosPage 消息处理程序


/************************************************************************
* 函数介绍：屏蔽掉回车键和esc键
* 输入参数：
* 输出参数：
* 返回值  ：
************************************************************************/
BOOL CPosPage::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message==WM_KEYDOWN)
	{
		switch (pMsg->wParam)
		{
		case VK_RETURN:
		case VK_SPACE:
			return TRUE;
		case VK_ESCAPE:
		case VK_BACK:
			this->SendMessage(WM_COMMAND,IDC_BUTTON_PRE);
			return TRUE;
		case VK_INSERT:
			this->SendMessage(WM_COMMAND,IDC_BUTTON_CHKNAME);
			return TRUE;
		case VK_HOME:
			this->SendMessage(WM_COMMAND,IDC_BUTTON_FUNCTION);
			return TRUE;
		}
	}
	return CDialog::PreTranslateMessage(pMsg); 
}

void CPosPage::OnNextPage(UINT uID)
{
	CPOSClientApp* pApp=(CPOSClientApp*)AfxGetApp();
	pApp->m_pMain->SetActivePage(uID-IDC_BUTTON_NEXTPAGE-1);
}
void CPosPage::InitDialog(CString strImgPath)
{
	CDialog::OnInitDialog();
	CImage img;
	if(img.Load(strImgPath)==S_OK)
	{
		m_x=img.GetWidth();
		m_y=img.GetHeight();
		m_bpBackgrd=img.Detach();
	}
}
BOOL CPosPage::OnEraseBkgnd(CDC* pDC)
{
	if (m_bpBackgrd==NULL)
	{
		return FALSE;
	}
	CDC MemDc;
	MemDc.CreateCompatibleDC(pDC);
	MemDc.SelectObject(m_bpBackgrd);
	pDC->SetStretchBltMode(HALFTONE);
	pDC->StretchBlt(0,0,CreatButton::m_nFullWidth,CreatButton::m_nFullHeight,&MemDc,0,0,m_x,m_y,SRCCOPY);
// TRACE(this->GetRuntimeClass()->m_lpszClassName);
// TRACE(" bSetBk=%d\n",m_btnCtrl.bSetBk);
	m_btnCtrl.SetBkGnd(pDC);
	return TRUE;
}
HBRUSH CPosPage::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	if(nCtlColor==CTLCOLOR_STATIC)
	{
		//pDC->SetTextColor(m_dTextColor);
		pDC->SetBkMode(TRANSPARENT);
		return (HBRUSH)::GetStockObject(NULL_BRUSH); //返回此画刷可以使静态文本透明
	}
	return   hbr; 
}