// CustomerDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "POSClient.h"
#include "CustomerDlg.h"
#include "NumberInputDlg.h"
#include <openssl/aes.h>
// CCustomerDlg 对话框

IMPLEMENT_DYNAMIC(CCustomerDlg, CDialog)

CCustomerDlg::CCustomerDlg(CWnd* pParent /*=NULL*/)
: CDialog(CCustomerDlg::IDD, pParent)
{
	m_dConsume=0;
}

CCustomerDlg::~CCustomerDlg()
{
}

void CCustomerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_CRADID, mEdit_card);
	DDX_Control(pDX, IDC_EDIT_NAME, mEdit_name);
	DDX_Control(pDX, IDC_EDIT_PHONE, mEdit_phone);
	DDX_Control(pDX, IDC_EDIT_AMOUNT, mEdit_amount);
	DDX_Control(pDX, IDC_EDIT_SCORE, mEdit_score);
	DDX_Control(pDX, IDC_EDIT_STATE, mEdit_state);
	DDX_Control(pDX, IDC_EDIT_LEVEL, mEdit_level);
	DDX_Control(pDX, IDC_EDIT_PAY, mEdit_pay);
	DDX_Control(pDX, IDC_CHECK1, mButtonPrint);
	DDX_Control(pDX, IDOK, m_btOK);
	DDX_Control(pDX, IDCANCEL, m_btCancel);
	DDX_Control(pDX, IDC_EDIT_PASSWORD, mEdit_psw);
	DDX_Control(pDX, IDC_EDIT_POINT, mEdit_point);
}


BEGIN_MESSAGE_MAP(CCustomerDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CCustomerDlg::OnBnClickedOk)
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CCustomerDlg 消息处理程序

BOOL CCustomerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	CString str2;
	m_btOK.SetImage(_T("Picture\\bt_ok.png"));
	m_btCancel.SetImage(_T("Picture\\bt_cancel.png"));
	if (!theLang.m_bDefaultLang)
	{
		CWnd* pCtrl=GetDlgItem(IDC_CHECK1);
		theLang.TranslateDlgItem(pCtrl,IDS_PRINTCHARGE);
		pCtrl=GetDlgItem(IDOK);
		theLang.TranslateDlgItem(pCtrl,IDS_OK);
		pCtrl=GetDlgItem(IDCANCEL);
		theLang.TranslateDlgItem(pCtrl,IDS_CANCEL);
		pCtrl=GetDlgItem(IDC_STATIC1);
		theLang.TranslateDlgItem(pCtrl,IDS_CARDNO);
		pCtrl=GetDlgItem(IDC_STATIC2);
		theLang.TranslateDlgItem(pCtrl,IDS_FMNAME);
		pCtrl=GetDlgItem(IDC_STATIC3);
		theLang.TranslateDlgItem(pCtrl,IDS_PHONE);
		pCtrl=GetDlgItem(IDC_STATIC4);
		theLang.TranslateDlgItem(pCtrl,IDS_BALANCE);
		pCtrl=GetDlgItem(IDC_STATIC5);
		theLang.TranslateDlgItem(pCtrl,IDS_CONSUME);
		pCtrl=GetDlgItem(IDC_STATIC_1);
		theLang.TranslateDlgItem(pCtrl,IDS_SCORE);
		pCtrl=GetDlgItem(IDC_STATIC6);
		theLang.TranslateDlgItem(pCtrl,IDS_STATUS);
		pCtrl=GetDlgItem(IDC_STATIC7);
		theLang.TranslateDlgItem(pCtrl,IDS_LEVEL);
		pCtrl=GetDlgItem(IDC_STATIC8);
		theLang.TranslateDlgItem(pCtrl,IDS_PASSWORD);
		pCtrl=GetDlgItem(IDC_STATIC9);
		theLang.TranslateDlgItem(pCtrl,IDS_USEPOINT);
		theLang.LoadString(IDS_VIPINFO,str2);
		SetWindowText(str2);
	}
	m_btOK.SetTextColor(DEFALUT_TXT_COLOR);
	m_btCancel.SetTextColor(DEFALUT_TXT_COLOR);
	CString str;
	str.Format(_T("%0.2f"),m_dConsume);
	mEdit_card.SetWindowText(m_strCradId);
	mEdit_pay.SetWindowText(str);
	mEdit_pay.SetLimitText(8);
	mEdit_name.SetWindowText(m_strName);
	mEdit_psw.SetLimitText(20);
	int check=GetPrivateProfileInt(_T("POS"),  _T("PrintCustomerInfo"), 0,_T(".\\config.ini"));
	if(check>0)
		mButtonPrint.SetCheck(TRUE);
	UpdateMemeberInfo();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
void CCustomerDlg::UpdateMemeberInfo()
{
	try
	{
		CString strSend,strURL;
		CInternetSession session;
		session.SetOption(INTERNET_OPTION_CONNECT_TIMEOUT, 1000 * 10);
		session.SetOption(INTERNET_OPTION_CONNECT_BACKOFF, 1000);
		session.SetOption(INTERNET_OPTION_CONNECT_RETRIES, 1);
		CHttpConnection* pConnection = session.GetHttpConnection(server,(INTERNET_PORT)port);
		CString szHeaders   = L"Content-Type: application/x-www-form-urlencoded;";
		strSend.Format(_T("{\"guid\":\"%s\",\"card_id\":\"%s\",\"consume_type\":1"),theApp.m_strResId,m_strCradId);
		if(theLang.m_strLang==_T("Default")||theLang.m_strLang==_T("简体中文"))
			strSend.AppendFormat(_T(",\"lang\":\"zh-CN\"}"));
		else if(theLang.m_strLang==_T("繁體中文"))
			strSend.AppendFormat(_T(",\"lang\":\"zh-TW\"}"));
		else
			strSend.AppendFormat(_T(",\"lang\":\"en\"}"));
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
		strURL.Format(_T("/api2/get_card/"));
		CHttpFile* pFile = pConnection->OpenRequest(CHttpConnection::HTTP_VERB_POST,strURL);
		pFile->SendRequest(szHeaders,szHeaders.GetLength(),(LPVOID)encrypt_text,len);
		delete sz0;
		delete encrypt_text;
		DWORD dwRet;
		pFile->QueryInfoStatusCode(dwRet);
		if(dwRet != HTTP_STATUS_OK)
		{
			LOG4CPLUS_ERROR(log_pos,"Connect "<<(LPCTSTR)server<<":"<<port<<" status code="<<dwRet);
			session.Close();
			pFile->Close();
			delete pFile;
			return;
		}
		char buf[4096]={0};
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
		CString strMsg;
		if(root[_T("card_status_id")].asInt()!=1)
		{
			m_btOK.EnableWindow(FALSE);
			m_btOK.ShowWindow(SW_HIDE);
		}
		if(root.isMember(_T("tel")))
		{
			strMsg.Format(_T("%s"),root[_T("tel")].asCString());
			mEdit_phone.SetWindowText(strMsg);
			strMsg.Format(_T("%0.2f"),root[_T("surplus")].asDouble());
			mEdit_amount.SetWindowText(strMsg);
			mEdit_state.SetWindowText(root[_T("card_status")].asCString());
			mEdit_level.SetWindowText(root[_T("card_level")].asCString());
			int score=root[_T("cur_score")].asInt();
			strMsg.Format(_T("%d"),score);
			mEdit_score.SetWindowText(strMsg);
			double p=root[_T("score_money")].asDouble();
			if(p>0.1)
			{
				CString str2;
				theLang.LoadString(str2,IDS_POINTCONSUME);
				strMsg.Format(str2,score/p);
				GetDlgItem(IDC_STATIC_POINT)->SetWindowText(strMsg);
			}
		}
		
	}catch(...)
	{
	}
}
/************************************************************************
会员支付接口
*************************************************************************/
void CCustomerDlg::OnBnClickedOk()
{
	m_btOK.EnableWindow(FALSE);
	JSONVALUE root;
	try
	{
		CString strURL,strValue;
		CInternetSession session;
		session.SetOption(INTERNET_OPTION_CONNECT_TIMEOUT, 1000 * 10);
		session.SetOption(INTERNET_OPTION_CONNECT_BACKOFF, 1000);
		session.SetOption(INTERNET_OPTION_CONNECT_RETRIES, 1);
		CHttpConnection* pConnection = session.GetHttpConnection(server,(INTERNET_PORT)port);
		CString szHeaders   = L"Content-Type: application/x-www-form-urlencoded;";
		srand (time(NULL));
		JSONVALUE json;
		json[_T("order_head_id")]=theApp.m_nOrderHeadid;
		json[_T("trans_id")]=rand();
		mEdit_psw.GetWindowText(strValue);
		json[_T("card_id")]=m_strCradId;
		json[_T("pwd")]=strValue;
		mEdit_pay.GetWindowText(strValue);
		json[_T("money")]=_wtof(strValue);
		mEdit_point.GetWindowText(strValue);
		json[_T("use_score")]=_wtoi(strValue);

		json[_T("money_discount")]=toDisc;
		json[_T("username")]=theApp.m_strUserName;
		json[_T("user_id")]=theApp.m_strUserID;
		json[_T("guid")]=theApp.m_strResId;
		json[_T("machine_id")]=theApp.m_strHostName;
		CTime ctime=CTime::GetCurrentTime();
		json[_T("time")]=ctime.Format(_T("%Y-%m-%d %H:%M:%S"));
		if(theLang.m_strLang==_T("Default")||
			theLang.m_strLang==_T("简体中文"))
			json[_T("lang")]=_T("zh-CN");
		else if(theLang.m_strLang==_T("繁體中文"))
			json[_T("lang")]=_T("zh-TW");
		else
			json[_T("lang")]=_T("en");
		//	strSend.AppendFormat(_T(",\"lang\":\"en\"}"));
		//else
		//	strSend.AppendFormat(_T("}"));
		std::wstring str;
		json.ToString(str);
		int wcsLen0 = ::WideCharToMultiByte(CP_UTF8, NULL, str.c_str(), str.length(), NULL, 0, NULL, NULL);
		char* sz0 = new char[wcsLen0 + 1];
		::WideCharToMultiByte(CP_UTF8, NULL, str.c_str(), -1, sz0, wcsLen0,  NULL, NULL);
		sz0 [wcsLen0] = '\0';
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
		AES_cbc_encrypt((const unsigned char *)sz0, (unsigned char *)encrypt_text, len, &aes_enc_ctx, ivec, AES_ENCRYPT); 

		// 		char buf2[10240]={0};
		//  		AES_KEY aes_dec_ctx;
		//  		AES_set_decrypt_key(theApp.enctrypkey, 128, &aes_dec_ctx);
		//  		char * plain_text=(char *)buf2;
		//  		memset(ivec,0,AES_BLOCK_SIZE);
		//  		AES_cbc_encrypt((const unsigned char *)encrypt_text, (unsigned char *)plain_text, len, &aes_dec_ctx, ivec, AES_DECRYPT); 

		strURL.Format(_T("/api2/consume/"));
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
			POSMessageBox(hint);
			session.Close();
			pFile->Close();
			delete pFile;
			m_btOK.EnableWindow(TRUE);
			return;
		}
		char buf[1024]={0};
		pFile->ReadString((LPTSTR)buf,sizeof(buf)-1);
		pFile->Close();
		
		if(!root.Parse(buf,JSON_FLAG_LOOSE))
		{//请求失败
			POSMessageBox(_T("Json parse error!"));
			m_btOK.EnableWindow(TRUE);
			return;
		}
		CString strMsg;
		if(root.isMember(_T("error")))
		{
			root.Unescape(root[_T("error")].asCString(),strMsg);
			POSMessageBox(strMsg);
			CDialog::OnCancel();
			return;
		}
		m_dConsume=root[_T("card_money")].asDouble();//卡扣的钱
		m_dOripay=root[_T("ori_pay")].asDouble();//输入框的应付金额
		m_dBalance=root[_T("amount")].asDouble();//卡内余额
		m_iScore=root[_T("cur_score")].asDouble();
		if(root.isMember(_T("discount_money")))//折扣金额
		{
			m_dDiscount=root[_T("discount_money")].asDouble();
			m_dDiscName=root[_T("discount")].asDouble();//折扣比例
		}
		else
		{
			m_dConsume=root[_T("act_pay")].asDouble();
			m_dDiscount=m_dOripay-m_dConsume;
		}
		m_strCradId=root[_T("card_id")].asCString();
		long id=root[_T("log")].asInt();
		CString strSQL;
		strSQL.Format(_T("UPDATE order_head SET customer_name='%d' WHERE order_head_id=%d"),id,theApp.m_nOrderHeadid);
		theDB.ExecuteSQL(strSQL);
		//消费，记录关联单号\余额
		strSQL.Format(_T("insert into customer_consume(card_id,amount,employee_id,employee_name,order_head_id,time,extend_1,type,web_id,device_id)")
			_T(" values('%s','%f',%s,'%s',%d,now(),%0.1f,2,%d,%d)"),
			m_strCradId,-m_dConsume,theApp.m_strUserID,FormatDBStr(theApp.m_strUserName),theApp.m_nOrderHeadid,m_dBalance,id,theApp.m_nDeviceId);
		theDB.ExecuteSQL(strSQL);
		//获取item_id
		strSQL.Format(_T("SELECT LAST_INSERT_ID();"));
		CRecordset rs( &theDB);
		rs.Open(-1,strSQL);
		CString strCount;
		rs.GetFieldValue((short)0,strCount);
		m_nConsume_id=_wtol(strCount);
		rs.Close();
	}catch(...)
	{
	}
	try{
		CString strCheck=_T("0");
		if (mButtonPrint.GetCheck())
		{
			strCheck=_T("1");
			PrintDeviceInfo printer;
			if(theApp.m_prePrinter.nDeviceType==-1||theApp.m_prePrinter.nPaperWidth==0)
			{
				if (theApp.m_payPrinter.nDeviceType==-1)
				{//没有配置打印机，无法打印
					//return;
				}
				printer=theApp.m_payPrinter;
			}
			else
				printer=theApp.m_prePrinter;

			if(printer.nDeviceType>=0)
			{
				JSONVALUE printTask;
				CPOSClientApp::FormatPrintDevice(printTask,printer);
				printTask[_T("template")]=TEMPLATE_VIP;
				CTime time_to=CTime::GetCurrentTime();
				printTask[_T("time")]=time_to.Format(_T("%Y-%m-%d %H:%M:%S"));
				printTask[_T("emp_name")]=theApp.m_strUserName;
				printTask[_T("card")]=m_strCradId;
				printTask[_T("name")]=m_strName;
				printTask[_T("ori_pay")]= m_dOripay;
				if(m_dDiscount>0.001)
					printTask[_T("discount")]=m_dDiscount;
				printTask[_T("amount")]= m_dConsume;
				printTask[_T("balance")]= m_dBalance;
				printTask[_T("score")]= m_iScore;
				printTask[_T("add_score")]= (int)root[_T("add_score")].asDouble();
				CPOSClientApp::PrintJson(printTask);
				if(macrosInt[_T("PRINT_MEMBER_TWICE")]==1)
				{
					Sleep(10);
					CPOSClientApp::PrintJson(printTask);
				}
			}
		}
		WritePrivateProfileString(_T("POS"),  _T("PrintCustomerInfo"), strCheck,_T(".\\config.ini"));
	}catch(...){

	}
	OnOK();
}

HBRUSH CCustomerDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何属性
	int ctlId=pWnd->GetDlgCtrlID();
	switch ( ctlId)
	{
	case IDC_STATIC:
	case IDC_STATIC_1:
	case IDC_STATIC_2:
	case IDC_STATIC1:
	case IDC_STATIC2:
	case IDC_STATIC3:
	case IDC_STATIC4:
	case IDC_STATIC5:
	case IDC_STATIC6:
	case IDC_STATIC7:
	case IDC_STATIC8:
	case IDC_STATIC9:
	case IDC_STATIC_POINT:
		pDC->SetTextColor(RGB(179,139,123));
		pDC->SetBkMode(TRANSPARENT);
		return (HBRUSH)::GetStockObject(NULL_BRUSH); //返回此画刷可以使静态文本透明
	case IDC_EDIT_AMOUNT:
	case IDC_EDIT_CRADID:
	case IDC_EDIT_NAME:
	case IDC_EDIT_SCORE:
	case IDC_EDIT_PHONE:
	case IDC_EDIT_STATE:
	case IDC_EDIT_LEVEL:
		pDC->SetTextColor(RGB(255,255,255));
		pDC->SetBkMode(TRANSPARENT);
		return (HBRUSH)::GetStockObject(NULL_BRUSH);
	case IDC_EDIT_PAY:
		pDC->SetTextColor(RGB(250,0,0));
		return hbr;
	}
	return   hbr; 

}

void CCustomerDlg::OnPaint()
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
