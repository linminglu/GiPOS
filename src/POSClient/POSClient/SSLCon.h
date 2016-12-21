// SslCon: interface for the CSslConnection class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WINETSEC_H__91AD1B9B_5B03_457E_A6B6_D66BB03147B7__INCLUDED_)
#define AFX_WINETSEC_H__91AD1B9B_5B03_457E_A6B6_D66BB03147B7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <Wininet.h>
#include <wincrypt.h>

#pragma warning(disable:4786)


enum CertStoreType {certStoreMY, certStoreCA, certStoreROOT, certStoreSPC};

class CSslConnection  
{
public:
	CSslConnection();
	virtual ~CSslConnection();	
public:	
	bool ConnectToHttpsServer(LPCTSTR strVerb);
	bool SendHttpsRequest(LPCSTR request);
	void GetRequestResult(CString& strResult);
	BOOL m_bUseWechatCert;
public: //accessors
	void SetServerName(LPCTSTR strServerName) { m_strServerName.Format(_T("%s"),strServerName); }
	void SetObjectName(LPCTSTR strObjectName) { m_strObjectName.Format(_T("%s"),strObjectName); }
	void SetPort(INTERNET_PORT wPort = INTERNET_DEFAULT_HTTPS_PORT) { m_wPort = wPort; }
	void SetRequestID(int reqID) { m_ReqID = reqID; }
	void SetSecurityFlags(int flags) { m_secureFlags = flags; }
	void SetHeader(LPCTSTR str){m_strHeader=str;}
	//Search indicators	

	CString GetLastErrorString() { return m_strLastError; }
	int GetLastErrorCode() { return m_lastErrorCode; }
	void ClearHandles();
private:
	/////////////////////////////////////
	bool SetWechatCert();
	
private:
	HINTERNET m_hInternet;
	HINTERNET m_hRequest;
	HINTERNET m_hSession;

	CString m_strServerName;
	CString m_strObjectName;
	CString m_strHeader;
	INTERNET_PORT m_wPort;
	int m_secureFlags;

	PCCERT_CONTEXT m_pContext;
	CString m_strUserName;
	CString m_strPassword;

	CString m_strLastError;
	int m_lastErrorCode;
	int m_ReqID;
};

#endif // !defined(AFX_WINETSEC_H__91AD1B9B_5B03_457E_A6B6_D66BB03147B7__INCLUDED_)

