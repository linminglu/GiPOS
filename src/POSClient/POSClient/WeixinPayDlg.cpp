/*********************************************************************
*Copyright (c) 2016 Coolroid Co.Ltd.
*DESCRIPTION：
*		微信子商户支付
*AUTHOR ：zhangyi
*********************************************************************/

#include "stdafx.h"
#include "POSClient.h"
#include "WeixinPayDlg.h"
#include "SSLCon.h"
#include "Markup.h"
#include <openssl/md5.h>
// CWeixinPayDlg 对话框

static CString m_strMchid=_T("1288015101");
static CString m_strAppid=_T("wxf3383278ce3189fd");

IMPLEMENT_DYNAMIC(CWeixinPayDlg, CDialog)

CWeixinPayDlg::CWeixinPayDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWeixinPayDlg::IDD, pParent)
{
}

CWeixinPayDlg::~CWeixinPayDlg()
{
}

void CWeixinPayDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_HINT, m_hint);
	DDX_Control(pDX, IDC_EDIT1, m_edit);
}


BEGIN_MESSAGE_MAP(CWeixinPayDlg, CDialog)
END_MESSAGE_MAP()

void getRandomString(CString& str,int length) {
	CString base = _T("abcdefghijklmnopqrstuvwxyz0123456789");
	srand ((unsigned)time(NULL));
	for (int i = 0; i < length; i++) {
		int number = rand()%base.GetLength();
		str.AppendChar(base.GetAt(number));
	}
}
static int  SortDescendingString(const void* left, const void* right)
{
	return ((CString*)left)->Compare(*((CString*)right));
}
UINT doPayQueryThreadWx(LPVOID pParam)
{
	CWeixinPayDlg *pDlg = (CWeixinPayDlg*)pParam;
	pDlg->doPayQueryLoop(3);
	return 0;
}
// CWeixinPayDlg 消息处理程序
BOOL CWeixinPayDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_hint.ModifyStyle(0,SS_CENTER);
	getRandomString(m_strRandom,16);
	m_strTradeNO.Format(_T("%s_%09d_%d"),theApp.m_strResId.Mid(1,8),theApp.m_nOrderHeadid,time(NULL));
	m_edit.SetFocus();
	return FALSE;
}


void CWeixinPayDlg::getSign(CString& sign,CStringArray& clist)
{
	qsort(clist.GetData(), clist.GetSize(), sizeof(CString*), SortDescendingString);
	CString str;
	for (int n = 0; n < clist.GetCount(); n++)
	{
		str.AppendFormat(_T("%s"),clist.GetAt(n));
	}
	str.AppendFormat(_T("key=ChegongmiaoCoolroidGicater9b2075"));
	//转为UTF-8
	int wcsLen0 = ::WideCharToMultiByte(CP_UTF8, NULL, str, str.GetLength(), NULL, 0, NULL, NULL);
	char* sz0 = new char[wcsLen0 + 1];
	memset(sz0,0,wcsLen0+1);
	::WideCharToMultiByte(CP_UTF8, NULL, str, -1, sz0, wcsLen0,  NULL, NULL);
	sz0 [wcsLen0] = '\0';
	//计算MD5
	MD5_CTX hash_ctx;
	unsigned char hash_ret[16];
	MD5_Init(&hash_ctx);
	MD5_Update(&hash_ctx, sz0, wcsLen0);
	MD5_Final(hash_ret, &hash_ctx);
	for( int i=0; i<16; i++ ){
		sign.AppendFormat(_T("%02X"),hash_ret[i]);
	}
	delete sz0;
}


void CWeixinPayDlg::OnOK()
{
	
	try{
		CSslConnection inetSec;
		inetSec.SetServerName(_T("api.mch.weixin.qq.com"));
		inetSec.SetObjectName(_T("/pay/micropay"));	
		if (!inetSec.ConnectToHttpsServer(_T("POST"))) {
LOG4CPLUS_ERROR(log_pos,(LPCTSTR)inetSec.GetLastErrorString()<<", "<<inetSec.GetLastErrorCode());
			return;
		}
		CStringArray clist;
		CString item;
		CMarkup xml_req;
		xml_req.AddElem(_T("xml"));
		xml_req.IntoElem();
		xml_req.AddElem(_T("appid"),m_strAppid);
		item.Format(_T("%s=%s&"),_T("appid"),m_strAppid);
		clist.Add(item);
		xml_req.AddElem(_T("mch_id"),m_strMchid);
		item.Format(_T("%s=%s&"),_T("mch_id"),m_strMchid);
		clist.Add(item);
		xml_req.AddElem(_T("sub_mch_id"),theApp.m_wxSubMchid);
		item.Format(_T("%s=%s&"),_T("sub_mch_id"),theApp.m_wxSubMchid);
		clist.Add(item);
		xml_req.AddElem(_T("device_info"),theApp.m_strDeviceName);
		item.Format(_T("%s=%s&"),_T("device_info"),theApp.m_strDeviceName);
		clist.Add(item);
		xml_req.AddElem(_T("nonce_str"),m_strRandom);
		item.Format(_T("%s=%s&"),_T("nonce_str"),m_strRandom);
		clist.Add(item);
		xml_req.AddElem(_T("body"),theApp.m_strResName);
		item.Format(_T("%s=%s&"),_T("body"),theApp.m_strResName);
		clist.Add(item);
		xml_req.AddElem(_T("attach"),theApp.m_strResId);
		item.Format(_T("%s=%s&"),_T("attach"),theApp.m_strResId);
		clist.Add(item);
		xml_req.AddElem(_T("out_trade_no"),m_strTradeNO);
		item.Format(_T("%s=%s&"),_T("out_trade_no"),m_strTradeNO);
		clist.Add(item);
		xml_req.AddElem(_T("total_fee"),total_fee);
		item.Format(_T("%s=%d&"),_T("total_fee"),total_fee);
		clist.Add(item);
		xml_req.AddElem(_T("spbill_create_ip"),theApp.m_strIP);
		item.Format(_T("%s=%s&"),_T("spbill_create_ip"),theApp.m_strIP);
		clist.Add(item);
		CString input;
		m_edit.GetWindowText(input);
		xml_req.AddElem(_T("auth_code"),input);
		item.Format(_T("%s=%s&"),_T("auth_code"),input);
		clist.Add(item);
		CString sign;
		getSign(sign,clist);
		xml_req.AddElem(_T("sign"),sign);
		CString request=xml_req.GetDoc();
		//LOG4CPLUS_DEBUG(log_pos,(LPCTSTR)request);
		//转为UTF-8
		int wcsLen0 = ::WideCharToMultiByte(CP_UTF8, NULL, request, request.GetLength(), NULL, 0, NULL, NULL);
		char* sz0 = new char[wcsLen0 + 1];
		memset(sz0,0,wcsLen0+1);
		::WideCharToMultiByte(CP_UTF8, NULL, request, -1, sz0, wcsLen0,  NULL, NULL);
		sz0 [wcsLen0] = '\0';
		if (!inetSec.SendHttpsRequest(sz0)) {
LOG4CPLUS_ERROR(log_pos,(LPCTSTR)inetSec.GetLastErrorString()<<", "<<inetSec.GetLastErrorCode());
			return;
		}
		CString response;
		inetSec.GetRequestResult(response);
		LOG4CPLUS_DEBUG(log_pos,(LPCTSTR)response);
		CMarkup xml_rsp;
		xml_rsp.SetDoc(response);
		xml_rsp.FindElem();
		xml_rsp.IntoElem();
		xml_rsp.FindElem(_T("return_code"));
		CString ret=xml_rsp.GetData();
		if(ret==_T("SUCCESS"))
		{
			xml_rsp.FindElem(_T("result_code"));
			if(xml_rsp.GetData()==_T("SUCCESS"))
			{//1)直接扣款成功
				xml_rsp.FindElem(_T("transaction_id"));
				m_wxTransactionID.Format(_T("%s"),xml_rsp.GetData());
				CDialog::OnOK();
				return;
			}else
			{
				xml_rsp.FindElem(_T("err_code"));
				ret=xml_rsp.GetData();
				//2)扣款明确失败
				if (ret==_T("AUTHCODEEXPIRE")) 
				{
					m_edit.SetWindowText(_T(""));
					m_hint.SetWindowText(_T("支付条码已过期，请重新扫码"));
					AfxBeginThread(doReverseLoop,(LPVOID)(LPCTSTR)m_strTradeNO);
				}
				else if(ret==_T("AUTH_CODE_INVALID"))
				{
					m_edit.SetWindowText(_T(""));
					m_hint.SetWindowText(_T("支付条码无效，请刷新后重新扫码"));
					AfxBeginThread(doReverseLoop,(LPVOID)(LPCTSTR)m_strTradeNO);
				}
				else if(ret==_T("NOTENOUGH"))
				{
					m_edit.SetWindowText(_T(""));
					m_hint.SetWindowText(_T("用户余额不足"));
					AfxBeginThread(doReverseLoop,(LPVOID)(LPCTSTR)m_strTradeNO);
				}
				else
				{
					//3)需要输入密码
					//4)扣款未知失败
					AfxBeginThread(doPayQueryThreadWx,this);
					return;
				}
			}
		}
		else
		{
			xml_rsp.FindElem(_T("return_msg"));
			m_hint.SetWindowText(xml_rsp.GetData());
		}
	}
	catch(...){
	}
}

BOOL CWeixinPayDlg::doPayQueryLoop(int loopCount)
{
	//至少查询一次
	if (loopCount == 0) {
		loopCount = 1;
	}
	//进行循环查询
	for (int i = 0; i < loopCount; i++){
		if (doOnePayQuery()) {
			EndDialog(IDOK);
			return TRUE;
		}
	}
	doReverseLoop((LPVOID)(LPCTSTR)m_strTradeNO);
	return FALSE;
}
/************************************************************************/
/* 进行一次支付订单查询操作
/************************************************************************/
BOOL CWeixinPayDlg::doOnePayQuery()
{
	Sleep(5000);
	LOG4CPLUS_DEBUG(log_pos,"CWeixinPayDlg::doOnePayQuery");
	try{
		CSslConnection inetSec;
		inetSec.SetServerName(_T("api.mch.weixin.qq.com"));
		inetSec.SetObjectName(_T("/pay/orderquery"));	
		if (!inetSec.ConnectToHttpsServer(_T("POST"))) {
			return FALSE;
		}
		CStringArray clist;
		CString item;
		CMarkup xml_req;
		xml_req.AddElem(_T("xml"));
		xml_req.IntoElem();
		xml_req.AddElem(_T("appid"),m_strAppid);
		item.Format(_T("%s=%s&"),_T("appid"),m_strAppid);
		clist.Add(item);
		xml_req.AddElem(_T("mch_id"),m_strMchid);
		item.Format(_T("%s=%s&"),_T("mch_id"),m_strMchid);
		clist.Add(item);
		xml_req.AddElem(_T("sub_mch_id"),theApp.m_wxSubMchid);
		item.Format(_T("%s=%s&"),_T("sub_mch_id"),theApp.m_wxSubMchid);
		clist.Add(item);
		xml_req.AddElem(_T("out_trade_no"),m_strTradeNO);
		item.Format(_T("%s=%s&"),_T("out_trade_no"),m_strTradeNO);
		clist.Add(item);
		xml_req.AddElem(_T("nonce_str"),m_strRandom);
		item.Format(_T("%s=%s&"),_T("nonce_str"),m_strRandom);
		clist.Add(item);
		CString sign;
		getSign(sign,clist);
		xml_req.AddElem(_T("sign"),sign);
		CString request=xml_req.GetDoc();
		//转为UTF-8
		int wcsLen0 = ::WideCharToMultiByte(CP_UTF8, NULL, request, request.GetLength(), NULL, 0, NULL, NULL);
		char* sz0 = new char[wcsLen0 + 1];
		memset(sz0,0,wcsLen0+1);
		::WideCharToMultiByte(CP_UTF8, NULL, request, -1, sz0, wcsLen0,  NULL, NULL);
		sz0 [wcsLen0] = '\0';
		if (!inetSec.SendHttpsRequest(sz0)) {
			return FALSE;
		}
		CString response;
		inetSec.GetRequestResult(response);
		LOG4CPLUS_DEBUG(log_pos,(LPCTSTR)response);
		CMarkup xml_rsp;
		xml_rsp.SetDoc(response);
		xml_rsp.FindElem();
		xml_rsp.IntoElem();
		xml_rsp.FindElem(_T("return_code"));
		CString ret=xml_rsp.GetData();
		if(ret==_T("SUCCESS"))
		{
			xml_rsp.FindElem(_T("result_code"));
			if(xml_rsp.GetData()==_T("SUCCESS"))
			{
				xml_rsp.FindElem(_T("transaction_id"));
				m_wxTransactionID.Format(_T("%s"),xml_rsp.GetData());
				xml_rsp.FindElem(_T("trade_state"));
				if(xml_rsp.GetData()==_T("SUCCESS"))
					return TRUE;
			}
		}
	}catch(...){
	}
	return FALSE;
}

BOOL doOneReverse(int type,LPCTSTR outTradeNo,BOOL& needRecallReverse)
{
	Sleep(5000);
	LOG4CPLUS_DEBUG(log_pos,"doOneReverse "<<outTradeNo);
	try{
		CSslConnection inetSec;
		inetSec.SetServerName(_T("api.mch.weixin.qq.com"));
		inetSec.SetObjectName(_T("/secapi/pay/reverse"));
		if (!inetSec.ConnectToHttpsServer(_T("POST"))) {
			return FALSE;
		}
		CStringArray clist;
		CString item;
		CMarkup xml_req;
		xml_req.AddElem(_T("xml"));
		xml_req.IntoElem();
		xml_req.AddElem(_T("appid"),m_strAppid);
		item.Format(_T("%s=%s&"),_T("appid"),m_strAppid);
		clist.Add(item);
		xml_req.AddElem(_T("mch_id"),m_strMchid);
		item.Format(_T("%s=%s&"),_T("mch_id"),_T("1243900002"));
		clist.Add(item);
		xml_req.AddElem(_T("sub_mch_id"),theApp.m_wxSubMchid);
		item.Format(_T("%s=%s&"),_T("sub_mch_id"),theApp.m_wxSubMchid);
		clist.Add(item);
		if(type==0)
		{
			xml_req.AddElem(_T("out_trade_no"),outTradeNo);
			item.Format(_T("%s=%s&"),_T("out_trade_no"),outTradeNo);
			clist.Add(item);
		}else{
			xml_req.AddElem(_T("transaction_id"),outTradeNo);
			item.Format(_T("%s=%s&"),_T("transaction_id"),outTradeNo);
			clist.Add(item);
		}
		CString strRandom;
		getRandomString(strRandom,16);
		xml_req.AddElem(_T("nonce_str"),strRandom);
		item.Format(_T("%s=%s&"),_T("nonce_str"),strRandom);
		clist.Add(item);
		CString sign;
		CWeixinPayDlg::getSign(sign,clist);
		xml_req.AddElem(_T("sign"),sign);
		CString request=xml_req.GetDoc();
		//转为UTF-8
		int wcsLen0 = ::WideCharToMultiByte(CP_UTF8, NULL, request, request.GetLength(), NULL, 0, NULL, NULL);
		char* sz0 = new char[wcsLen0 + 1];
		memset(sz0,0,wcsLen0+1);
		::WideCharToMultiByte(CP_UTF8, NULL, request, -1, sz0, wcsLen0,  NULL, NULL);
		sz0 [wcsLen0] = '\0';
		if (!inetSec.SendHttpsRequest(sz0)) {
			return FALSE;
		}
		CString response;
		inetSec.GetRequestResult(response);
		LOG4CPLUS_DEBUG(log_pos,(LPCTSTR)response);
		CMarkup xml_rsp;
		xml_rsp.SetDoc(response);
		xml_rsp.FindElem();
		xml_rsp.IntoElem();
		xml_rsp.FindElem(_T("return_code"));
		CString ret=xml_rsp.GetData();
		if(ret==_T("SUCCESS"))
		{
			xml_rsp.FindElem(_T("result_code"));
			if(xml_rsp.GetData()==_T("FAIL"))
			{
				xml_rsp.FindElem(_T("recall"));
				if(xml_rsp.GetData()==_T("Y"))
				{
					//表示需要重试
					needRecallReverse = TRUE;
					return FALSE;
				}
			} else {
				//表示不需要重试，也可以当作是撤销成功
				needRecallReverse = FALSE;
				return TRUE;
			}
			}else{
				return TRUE;
			}
	}catch(...){
	}
	return FALSE;
}
/************************************************************************
用商户系统内部的订单号out_trade_no撤销支付
************************************************************************/
UINT doReverseLoop(LPVOID pParam)
{
	LPCTSTR outTradeNo=(LPCTSTR) pParam;
	//初始化这个标记
	BOOL needRecallReverse = TRUE;
	//进行循环撤销，直到撤销成功，或是API返回recall字段为"Y"
	while (needRecallReverse) {
		if (doOneReverse(0,outTradeNo,needRecallReverse)) {
			return 0;
		}
	}
	return 0;
}
/************************************************************************
用微信的订单号transaction_id撤销支付
************************************************************************/
UINT doReverseLoop1(LPVOID pParam)
{
	LPCTSTR outTradeNo=(LPCTSTR) pParam;
	//初始化这个标记
	BOOL needRecallReverse = TRUE;
	//进行循环撤销，直到撤销成功，或是API返回recall字段为"Y"
	while (needRecallReverse) {
		if (doOneReverse(1,outTradeNo,needRecallReverse)) {
			return 0;
		}
	}
	return 0;
}