/*********************************************************************
*Copyright (c) 2016 Coolroid Co.Ltd.
*DESCRIPTION：
*		支付宝支付
*AUTHOR ：zhangyi
*********************************************************************/
#include "stdafx.h"
#include "POSClient.h"
#include "AliPayDlg.h"
#include "SSLCon.h"
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/md5.h>
// CAliPayDlg 对话框
static const  CHAR* m_priKey="-----BEGIN RSA PRIVATE KEY-----\n"
"MIICXQIBAAKBgQC7GWKBeOgPjIwHh5XgCyyeHG+msMMvHNUTkjl/rdbAH0CLLwhY\n"
"WK+U4Zz07wlzNs5jVPz884oahCrDYQmihBXqRwIpU9qk9RvJhvTzKi4Bwm7npbDI\n"
"ru8x+sk6vKwYdLVM6pREqhC7oZCNkn25YOP25Ql+DQqQujLQZ0mZf7DYXQIDAQAB\n"
"AoGBALMDocWBWn/uGNjneJYp+uG5EXbq74W3T4PvR4aLXMrr3ASP1qs5B54qk9Oi\n"
"lmcfTC+sVHbtyfh+9q+DvAU73f5qsdIEX5SKUf2frOuNYYFbyC9APkeKMqOHA0vH\n"
"h0OevVUtYmHH0ErcarkLw4TnQ7g60AcrqFZpBtChJlE7laQhAkEA77x//5g1EezP\n"
"1UCmeg1L4DHQkA4jnzVnA5b1tagUADgvCvPiZSTSW/Himdk6MbapELunfc7zJEf2\n"
"rwgUzX6+aQJBAMfKvDoL9pGsCtBbvzETpa7KnRpCPjXcVTRE0mWJPIWATCFyuB4W\n"
"Y1S1+DEbWNVIlglHaHgaUlVe05iSLlQxs9UCQEHbA0JgOnvhFLqdFt5CVsyQgp1/\n"
"9NMgZVr8FiU/tbbVuD6G/nMQaWTujnP601yis9Cv6/PIbMxTpHUygBxvK7kCQG6A\n"
"E8DrEvGYvNZmmAU1v6JAD8oRL0Us2rcxBUkBMUcJIZIyV+DUMxYMGvxWCrjUD5+M\n"
"LhyXOkhbTR6KYzNP1g0CQQDL7253pGIqAT837Jq5f9z9Cs2x7oTGCdEg+TZxNDt+\n"
"ysF2u0CO/QuiN0GTkaAZNe6CEjQ2tnZKexazjghisyG1\n"
"-----END RSA PRIVATE KEY-----";

static CString m_strUrl=_T("openapi.alipay.com");
static CString m_strSpId=_T("2088421591079251");
static string m_strAppid="2016080201696029";

IMPLEMENT_DYNAMIC(CAliPayDlg, CDialog)

CAliPayDlg::CAliPayDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAliPayDlg::IDD, pParent)
{
	m_bProcessing=FALSE;
	m_bDialogClosed=FALSE;
}

CAliPayDlg::~CAliPayDlg()
{
}

void CAliPayDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_HINT, m_hint);
	DDX_Control(pDX, IDC_EDIT1, m_edit);
}


BEGIN_MESSAGE_MAP(CAliPayDlg, CDialog)
	ON_MESSAGE(WM_MESSAGE_CLOSEOK,OnThreadOK)
END_MESSAGE_MAP()

UINT doPayQueryThreadAli(LPVOID pParam)
{
	CAliPayDlg *pDlg = (CAliPayDlg*)pParam;
	pDlg->doPayQueryLoop(6);
	return 0;
}
// CAliPayDlg 消息处理程序
BOOL CAliPayDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_hint.ModifyStyle(0,SS_CENTER);
	m_hint.GetWindowRect(&mRectHint);    
	ScreenToClient(&mRectHint);
	m_strTradeNO.Format(_T("%s_%09d_%d"),theApp.m_strResId.Mid(1,16),theApp.m_nOrderHeadid,time(NULL));
	m_edit.SetFocus();
	return FALSE;
}

string CAliPayDlg::base64Encode(const unsigned char *bytes, int len) {

	BIO *bmem = NULL;
	BIO *b64 = NULL;
	BUF_MEM *bptr = NULL;

	b64 = BIO_new(BIO_f_base64());
	BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
	bmem = BIO_new(BIO_s_mem());
	b64 = BIO_push(b64, bmem);
	BIO_write(b64, bytes, len);
	BIO_flush(b64);
	BIO_get_mem_ptr(b64, &bptr);

	string str = string(bptr->data, bptr->length);
	BIO_free_all(b64);
	return str;
}
void CAliPayDlg::rsaSign(const char* content,string& signed_str) 
{
	int key_len = strlen(m_priKey);
	BIO *p_key_bio = BIO_new_mem_buf((void *)m_priKey, key_len);
	RSA *p_rsa = PEM_read_bio_RSAPrivateKey(p_key_bio, NULL, NULL, NULL);

	if (p_rsa != NULL) {
		unsigned char hash[SHA_DIGEST_LENGTH] = {0};
		SHA1((unsigned char *)content, strlen(content), hash);
		unsigned char sign[1024 / 8] = {0};
		unsigned int sign_len = sizeof(sign);
		int r = RSA_sign(NID_sha1, hash, SHA_DIGEST_LENGTH, sign, &sign_len, p_rsa);

		if (0 != r && sizeof(sign) == sign_len) {
			signed_str = base64Encode(sign, sign_len);
		}
	}

	RSA_free(p_rsa);
	BIO_free(p_key_bio);
}
inline BYTE ToHex(const BYTE &x)
{
	return x > 9 ? x + 55: x + 48;
}
string URLEncode_UTF8(string str)
{
	std::string strTemp = "";  
	size_t length = str.length();  
	for (size_t i = 0; i < length; i++)  
	{
		if (isalnum((unsigned char)str[i]) ||   
			(str[i] == '-') ||  
			(str[i] == '_') ||   
			(str[i] == '.') ||   
			(str[i] == '~'))  
			strTemp += str[i];  
		else if (str[i] == ' ')  
			strTemp += "+";  
		else  
		{  
			strTemp += '%';  
			strTemp += ToHex((unsigned char)str[i] >> 4);  
			strTemp += ToHex((unsigned char)str[i] % 16);  
		}  
	}  
	return strTemp;
}
/************************************************************************
* 函数介绍：拼接字符串
*	STL map 默认按照key升序排列
* 输入参数：bEncode 是否做URLEncode
* 输出参数：
* 返回值  ：
************************************************************************/
string CAliPayDlg::buildContent(const StringMap &contentPairs,bool bEncode) {
    string content;
    for (StringMap::const_iterator iter = contentPairs.begin();
         iter != contentPairs.end(); ++iter) {
        if (!content.empty()) {
            content.push_back('&');
        }
        content.append(iter->first);
        content.push_back('=');
		if(bEncode)
		{
			content.append(URLEncode_UTF8(iter->second));
		}
		else
		{
			content.append(iter->second);
		}
    }
    return content;
}
LRESULT CAliPayDlg::OnThreadOK(WPARAM wParam, LPARAM lParam)
{
	CDialog::OnOK();
	return 0;
}
void CAliPayDlg::OnCancel()
{
	m_bDialogClosed=TRUE;
	CDialog::OnCancel();
}
void CAliPayDlg::OnOK()
{
	try{
		if(m_bProcessing)
			return;//有其他线程正在处理
		CSslConnection inetSec;
		inetSec.SetServerName(m_strUrl);
		inetSec.SetObjectName(_T("/gateway.do"));
		inetSec.SetHeader(_T("Content-Type:application/x-www-form-urlencoded;charset=utf-8"));
		inetSec.m_bUseWechatCert=FALSE;
		if (!inetSec.ConnectToHttpsServer(_T("POST"))) {
			return;
		}
		JSONVALUE root;
		JSONVALUE extend_params;
		extend_params[_T("sys_service_provider_id")]=m_strSpId;
		root[_T("out_trade_no")]=m_strTradeNO;
		root[_T("scene")]=_T("bar_code");
		root[_T("extend_params")]=extend_params;
		CString input;
		m_edit.GetWindowText(input);
		root[_T("auth_code")]=input;
		root[_T("total_amount")]=total_amount;
		root[_T("subject")]=theApp.m_strResName;
		root[_T("operator_id")]=theApp.m_strUserName;
		root[_T("alipay_store_id")]=theApp.m_aliStoreId;
		std::wstring str;
		root.ToString(str);
		int wcsLen0 = ::WideCharToMultiByte(CP_UTF8, NULL, str.c_str(), str.length(), NULL, 0, NULL, NULL);
		char* sz0 = new char[wcsLen0 + 1];
		::WideCharToMultiByte(CP_UTF8, NULL, str.c_str(), -1, sz0, wcsLen0,  NULL, NULL);
		sz0 [wcsLen0] = '\0';
		StringMap requestPairs;
		requestPairs.insert(StringMap::value_type("app_id", m_strAppid));
		requestPairs.insert(StringMap::value_type("biz_content", sz0));
		requestPairs.insert(StringMap::value_type("charset","utf-8"));
		requestPairs.insert(StringMap::value_type("method", "alipay.trade.pay"));
		requestPairs.insert(StringMap::value_type("sign_type", "RSA"));
		requestPairs.insert(StringMap::value_type("app_auth_token", theApp.m_aliAuthToken));
		time_t t = time(0);
		char time_c[64];
		strftime(time_c, sizeof(time_c), "%Y-%m-%d %X", localtime(&t));
		requestPairs.insert(StringMap::value_type("timestamp", time_c));
		requestPairs.insert(StringMap::value_type("version", "2.0"));
		string wholeContent = buildContent(requestPairs,false);
		//计算RSA
		string sign;
		rsaSign(wholeContent.c_str(),sign);
		requestPairs.insert(StringMap::value_type("sign", sign));
		//URL编码
		wholeContent = buildContent(requestPairs,true);
		delete sz0;
		if (!inetSec.SendHttpsRequest(wholeContent.c_str())) {
			return;
		}
		CString line;
		inetSec.GetRequestResult(line);
		inetSec.ClearHandles();
		LOG4CPLUS_DEBUG(log_pos,(LPCTSTR)line);
		if(root.Parse((LPCTSTR)line,JSON_FLAG_LOOSE))
		{
			JSONVALUE response=root[_T("alipay_trade_pay_response")];
			CString ret=response[_T("code")].asCString();
			if(ret==_T("10000"))
			{//1)直接扣款成功
				m_wxTransactionID.Format(_T("%s"),response[_T("trade_no")].asCString());
				m_bDialogClosed=TRUE;
				CDialog::OnOK();
				return;
			}
			 if(ret==_T("10003"))
			{//3)需要输入密码
				AfxBeginThread(doPayQueryThreadAli,this);
			}
			else
			{
				CString hint=response[_T("sub_msg")].asCString();
				if(hint.IsEmpty())
					hint=response[_T("msg")].asCString();
				m_hint.SetWindowText(hint);
			}
		}
	}
	catch(...){
	}
}

BOOL CAliPayDlg::doPayQueryLoop(int loopCount)
{
	//进行循环查询
	m_bProcessing=TRUE;
	for (int i = 0; i < loopCount; i++){
		if(m_bDialogClosed)
			return FALSE;
		if (doOnePayQuery()) {
			::PostMessage(m_hWnd,WM_MESSAGE_CLOSEOK,0,0);
			return TRUE;
		}
	}
	m_bProcessing=FALSE;
	return FALSE;
}
/************************************************************************/
/* 进行一次支付订单查询操作
/************************************************************************/
BOOL CAliPayDlg::doOnePayQuery()
{
	Sleep(5000);
	try{
		CSslConnection inetSec;
		inetSec.SetServerName(m_strUrl);
		inetSec.SetObjectName(_T("/gateway.do"));
		inetSec.SetHeader(_T("Content-Type:application/x-www-form-urlencoded;charset=utf-8"));
		inetSec.m_bUseWechatCert=FALSE;
		if (!inetSec.ConnectToHttpsServer(_T("POST"))) {
			return FALSE;
		}
		JSONVALUE root;
		root[_T("out_trade_no")]=m_strTradeNO;
		std::wstring str;
		root.ToString(str);
		int wcsLen0 = ::WideCharToMultiByte(CP_UTF8, NULL, str.c_str(), str.length(), NULL, 0, NULL, NULL);
		char* sz0 = new char[wcsLen0 + 1];
		::WideCharToMultiByte(CP_UTF8, NULL, str.c_str(), -1, sz0, wcsLen0,  NULL, NULL);
		sz0 [wcsLen0] = '\0';
		StringMap requestPairs;
		requestPairs.insert(StringMap::value_type("app_id", m_strAppid));
		requestPairs.insert(StringMap::value_type("biz_content", sz0));
		requestPairs.insert(StringMap::value_type("charset","utf-8"));
		requestPairs.insert(StringMap::value_type("method", "alipay.trade.query"));
		requestPairs.insert(StringMap::value_type("sign_type", "RSA"));
		time_t t = time(0);
		char time_c[64];
		strftime(time_c, sizeof(time_c), "%Y-%m-%d %X", localtime(&t));
		requestPairs.insert(StringMap::value_type("timestamp", time_c));
		requestPairs.insert(StringMap::value_type("version", "2.0"));
		string wholeContent = buildContent(requestPairs,false);
		//计算RSA
		string sign;
		rsaSign(wholeContent.c_str(),sign);
		requestPairs.insert(StringMap::value_type("sign", sign));
		//URL编码
		wholeContent = buildContent(requestPairs,true);
		delete sz0;
		if (!inetSec.SendHttpsRequest(wholeContent.c_str())) {
			return FALSE;
		}
		CString line;
		inetSec.GetRequestResult(line);
		inetSec.ClearHandles();
		LOG4CPLUS_DEBUG(log_pos,(LPCTSTR)line);
		if(root.Parse((LPCTSTR)line,JSON_FLAG_LOOSE))
		{
			JSONVALUE response=root[_T("alipay_trade_query_response")];
			CString ret=response[_T("trade_status")].asCString();
			if(ret==_T("TRADE_SUCCESS"))
			{
				m_wxTransactionID.Format(_T("%s"),response[_T("trade_no")].asCString());
				return TRUE;//交易成功，且可对该交易做操作，如：多级分润、退款等。
			}
			else if(ret==_T("TRADE_FINISHED"))
			{
				m_wxTransactionID.Format(_T("%s"),response[_T("trade_no")].asCString());
				return TRUE;//交易成功且结束，即不可再做任何操作。
			}
		}
		
	}catch(...){
	}
	return FALSE;
}
