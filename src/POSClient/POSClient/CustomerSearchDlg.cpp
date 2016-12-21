// ustomerSearchDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "POSClient.h"
#include "CustomerSearchDlg.h"
#include <openssl/aes.h>
#include "mwrf32.h"

#pragma comment(lib,"mwrf32.lib")

HANDLE   g_newSearchSemaphore=NULL;
BOOL bRun=TRUE;

UINT SearchThread(LPVOID pParam)
{
	while(bRun)
	{
		WaitForSingleObject(g_newSearchSemaphore,INFINITE);
		if(!bRun)
			return 0;
		CustomerSearchDlg *pDlg = (CustomerSearchDlg*)pParam;
		pDlg->DoSearch();
	}
	return 0;
}
// CustomerSearchDlg 对话框

IMPLEMENT_DYNAMIC(CustomerSearchDlg, CDialog)

CustomerSearchDlg::CustomerSearchDlg(CWnd* pParent /*=NULL*/)
: CDialog(CustomerSearchDlg::IDD, pParent)
{
	port=80;
	m_bAutoOK=FALSE;
}

CustomerSearchDlg::~CustomerSearchDlg()
{
	delete m_bpButtonItem[0];
	delete m_bpButtonItem[1];
	bRun=FALSE;
	ReleaseSemaphore(g_newSearchSemaphore,1,NULL);
	CloseHandle(g_newSearchSemaphore);
	g_newSearchSemaphore=NULL;
}

void CustomerSearchDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_edit);
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Control(pDX, IDOK, m_btOK);
	DDX_Control(pDX, IDCANCEL, m_btCancel);
	DDX_Control(pDX, IDC_BUTTON_READ, m_readButton);
	DDX_Control(pDX, IDC_BUTTON_CLEAR, m_clearButton);
	DDX_Control(pDX, IDC_BUTTON_SOFTKEY, m_softButton);
	DDX_Control(pDX, IDC_STATIC_HINT,m_hint);
}


BEGIN_MESSAGE_MAP(CustomerSearchDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_SOFTKEY, &CustomerSearchDlg::OnBnClickedButtonSoftkey)
	ON_EN_CHANGE(IDC_EDIT1, &CustomerSearchDlg::OnEnChangeEdit1)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, &CustomerSearchDlg::OnBnClickedButtonClear)
	ON_BN_CLICKED(IDOK, &CustomerSearchDlg::OnBnClickedOk)
	ON_WM_TIMER()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON_READ, &CustomerSearchDlg::OnBnClickedButtonRead)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &CustomerSearchDlg::OnHdnItemdblclickList1)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CustomerSearchDlg 消息处理程序

void CustomerSearchDlg::OnBnClickedButtonSoftkey()
{
	ShellExecute(GetSafeHwnd(), NULL, _T("SoftBoard.exe"), NULL, NULL,SW_NORMAL);
}

void CustomerSearchDlg::OnEnChangeEdit1()
{
	// 刷新搜索显示
	KillTimer(1001);
	SetTimer(1001,300,NULL);//0.3秒后开始搜索
}

BOOL CustomerSearchDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	CString str2;
	theLang.LoadString(str2,IDS_SELECTVIP);
	CDialog::SetWindowText(str2);
	theLang.LoadString(str2,IDS_OK);
	m_btOK.SetWindowText(str2);
	theLang.LoadString(str2,IDS_OK);
	m_btOK.SetWindowText(str2);
	m_btOK.SetImage(_T("Picture\\bt_ok.png"));
	m_btCancel.SetImage(_T("Picture\\bt_cancel.png"));
	theLang.LoadString(str2,IDS_CANCEL);
	m_btCancel.SetWindowText(str2);
	m_bpButtonItem[0]=Gdiplus::Image::FromFile(_T("Picture\\bt_orange_71.png"));
	m_bpButtonItem[1]=Gdiplus::Image::FromFile(_T("Picture\\bt_orange_71_.png"));
	m_clearButton.SetImages(m_bpButtonItem[0],m_bpButtonItem[1],false);
	theLang.LoadString(str2,IDS_CLEAR);
	m_clearButton.SetWindowText(str2);
	m_readButton.SetImages(m_bpButtonItem[0],m_bpButtonItem[1],false);
	theLang.LoadString(str2,IDS_READCARD);
	m_readButton.SetWindowText(str2);
	m_softButton.SetImage(_T("Picture\\softboard.png"));
	

	m_edit.SetLimitText(20);
	m_edit.SetFocus();
	m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);

	theLang.LoadString(str2,IDS_CARDNO);
	m_list.InsertColumn(0,str2,LVCFMT_LEFT,200);
	theLang.LoadString(str2,IDS_FMNAME);
	m_list.InsertColumn(1,str2,LVCFMT_LEFT,150);
	theLang.LoadString(str2,IDS_PHONE);
	m_list.InsertColumn(2,str2,LVCFMT_LEFT,150);
	m_clearButton.SetTextColor(DEFALUT_TXT_COLOR);
	m_softButton.SetTextColor(DEFALUT_TXT_COLOR);
	m_btOK.SetTextColor(DEFALUT_TXT_COLOR);
	m_btCancel.SetTextColor(DEFALUT_TXT_COLOR);
	m_readButton.SetTextColor(DEFALUT_TXT_COLOR);
	g_newSearchSemaphore=CreateSemaphore(NULL,0,1,NULL);
	bRun=TRUE;
	AfxBeginThread(SearchThread,this);
	return FALSE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
BOOL CustomerSearchDlg::PreTranslateMessage(MSG* pMsg)
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
void CustomerSearchDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent==1001)
	{
		KillTimer(1001);
		CString strText;
		m_edit.GetWindowText(strText);
		ReleaseSemaphore(g_newSearchSemaphore,1,NULL);
	}
	CDialog::OnTimer(nIDEvent);
}
void CustomerSearchDlg::DoSearch()
{
	try{
		CString strSearch;
		m_edit.GetWindowText(strSearch);
		m_hint.SetWindowText(_T(""));
		if(strSearch.IsEmpty())
			return;
		m_list.DeleteAllItems();
		CString strSend,strURL;
		CInternetSession session;
		session.SetOption(INTERNET_OPTION_CONNECT_TIMEOUT, 1000 * 20);
		session.SetOption(INTERNET_OPTION_CONNECT_BACKOFF, 1000);
		//session.SetOption(INTERNET_OPTION_CONNECT_RETRIES, 1);
		CHttpConnection* pConnection = session.GetHttpConnection(server,(INTERNET_PORT)port);
		CString szHeaders   = L"Content-Type: application/x-www-form-urlencoded;";
		strSend.Format(_T("{\"guid\":\"%s\",\"card_id\":\"%s\""),theApp.m_strResId,strSearch);
		if(theLang.m_strLang==_T("English"))
			strSend.AppendFormat(_T(",\"lang\":\"en\"}"));
		else
			strSend.AppendFormat(_T("}"));
		int wcsLen0 = ::WideCharToMultiByte(CP_UTF8, NULL, strSend, strSend.GetLength(), NULL, 0, NULL, NULL);
		char* sz0 = new char[wcsLen0 + 1];
		::WideCharToMultiByte(CP_UTF8, NULL, strSend, -1, sz0, wcsLen0,  NULL, NULL);
		sz0[wcsLen0] = '\0';
		// aes encrypt
		AES_KEY aes_enc_ctx;
		unsigned char ivec[AES_BLOCK_SIZE]={'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'};
		int len = 0;
		if ((wcsLen0 + 1) % AES_BLOCK_SIZE == 0) {
			len = wcsLen0 + 1;
		} else {
			len = ((wcsLen0 + 1) / AES_BLOCK_SIZE + 1) * AES_BLOCK_SIZE;
		}
		unsigned char *encrypt_text=(unsigned char *) new char[len];
		AES_set_encrypt_key(theApp.enctrypkey, 128, &aes_enc_ctx);
		AES_cbc_encrypt((const unsigned char *)sz0, encrypt_text, len, &aes_enc_ctx, ivec, AES_ENCRYPT); 
		strURL.Format(_T("/api2/get_cards/"));
		CHttpFile* pFile = pConnection->OpenRequest(CHttpConnection::HTTP_VERB_POST,strURL);
		pFile->SendRequest(szHeaders,szHeaders.GetLength(),(LPVOID)encrypt_text,len);
		delete sz0;
		delete encrypt_text;
		DWORD dwRet;
		pFile->QueryInfoStatusCode(dwRet);
		if(dwRet != HTTP_STATUS_OK)
		{
			CString hint;
			hint.Format(_T("HTTP %d"),dwRet);
			m_hint.SetWindowText(hint);
			LOG4CPLUS_ERROR(log_pos,"Connect "<<(LPCTSTR)server<<":"<<port<<" status code="<<dwRet);
			session.Close();
			pFile->Close();
			delete pFile;
			return;
		}
		char buf[10240]={0};
		pFile->ReadString((LPTSTR)buf,sizeof(buf)-1);
		pFile->Close();
		wcsLen0 = ::MultiByteToWideChar(CP_UTF8, NULL, buf, strlen(buf), NULL, 0);
		TCHAR* sz1 = new TCHAR[wcsLen0 + 1];
		::MultiByteToWideChar(CP_UTF8, NULL, buf, -1, sz1, wcsLen0);
		sz1[wcsLen0] = '\0';
		CString jStr;
		JSONVALUE::Unescape(sz1,jStr);
		delete sz1;
		JSONVALUE root;
		if(!root.Parse((LPCTSTR)jStr,JSON_FLAG_LOOSE))
		{//请求失败
			LOG4CPLUS_ERROR(log_pos,"JSON Parse error");
			return;
		}
		if(root.isMember(_T("error")))
		{
			m_hint.SetWindowText(root[_T("error")].asCString());
			return;
		}
		int size = root.Size();
		for (int i = 0; i < size; i++)
		{
			JSONVALUE item;
			root.At(i,item);
			m_list.InsertItem(i,_T(""));
			m_list.SetItemText(i,0,item[_T("card_id")].asCString());
			CString tmp;
			m_list.SetItemText(i,1,item[_T("uname")].asCString());
			//m_list.SetItemText(i,2,item[_T("amount")].asCString());
			m_list.SetItemText(i,2,item[_T("phone")].asCString());
		}
		if(m_bAutoOK)
		{
			m_bAutoOK=FALSE;
			OnBnClickedOk();
		}
	}catch(CInternetException*  e)
	{
		CString hint;
		hint.Format(_T("connection failed: %d"),e->m_dwError);
		if(m_hint.m_hWnd)
			m_hint.SetWindowText(hint);
	}
	catch(...)
	{

	}
}
void CustomerSearchDlg::OnBnClickedButtonClear()
{
	m_edit.SetWindowText(_T(""));
}

void CustomerSearchDlg::OnBnClickedOk()
{
//TRACE("OnBnClickedOk\n");
	if(m_list.GetItemCount()==0)
	{
		m_bAutoOK=TRUE;
		return;//过滤掉刷卡器的第一次回车
	}
	if (m_list.GetItemCount()==1)
	{
		m_strCardId=m_list.GetItemText(0,0);
		m_strName=m_list.GetItemText(0,1);
	}
	else
	{//找选中的
		POSITION pos=m_list.GetFirstSelectedItemPosition(); 
		if   (NULL   ==   pos) 
		{
			POSMessageBox(IDS_SELECTRECORD); 
			return; 
		} 
		int   index   =   m_list.GetNextSelectedItem(pos);
		m_strCardId=m_list.GetItemText(index,0);
		m_strName=m_list.GetItemText(index,1);
	}
	if(m_strCardId.IsEmpty())
		return;
	OnOK();
}
void CustomerSearchDlg::OnBnClickedButtonRead()
{
	int _Adr=1;
	unsigned char Sec =_Adr/4;
	HANDLE icdev;
	unsigned long Snr;
	__int16 st;
	char* mkey = "FFFFFFFFFFFF";
	unsigned long val;
	std::string strRet;
    icdev=rf_init(0,115200);
	if(icdev>0)
	{
		rf_reset(icdev,5);
		unsigned char key[7];
		memset(key,0,7);
		a_hex(mkey,key,12);
		st = rf_card(icdev,0,&Snr);
		if(st)
		{
			rf_exit(icdev);
			return ;
		}
		st = rf_load_key(icdev,0,Sec,key);
		if(st)
		{
			rf_exit(icdev);
			return ;
		}
		st = rf_authentication(icdev,0,Sec);
		if(st)
		{
			rf_exit(icdev);
			return ;
		}
        st=rf_readval(icdev,_Adr,&val);
		rf_beep(icdev,10);
		rf_exit(icdev);
		CString strResult;
		strResult.Format(_T("%d"),val);
		m_edit.SetWindowText(strResult);
	}
}
HBRUSH CustomerSearchDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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
void CustomerSearchDlg::OnHdnItemdblclickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);
	OnBnClickedOk();
	*pResult = 0;
}

void CustomerSearchDlg::OnPaint()
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
