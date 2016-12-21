// SSLCon.cpp: implementation of the CSslConnection class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SSLCon.h"
#pragma comment(lib, "crypt32.lib")
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSslConnection::CSslConnection()
{
	m_hInternet = NULL;
	m_hRequest = NULL;
	m_hSession = NULL;
	m_pContext = NULL;
	m_bUseWechatCert=TRUE;
	m_wPort = 443;	
	m_secureFlags = INTERNET_FLAG_RELOAD|INTERNET_FLAG_KEEP_CONNECTION|INTERNET_FLAG_NO_CACHE_WRITE|
					INTERNET_FLAG_SECURE|INTERNET_FLAG_IGNORE_CERT_CN_INVALID;
}

CSslConnection::~CSslConnection()
{
	ClearHandles();
}


bool CSslConnection::ConnectToHttpsServer(LPCTSTR strVerb)
{
	try {	
		m_hInternet = InternetOpen(_T(""), INTERNET_OPEN_TYPE_PRECONFIG , 
				NULL, NULL, 0);
		if (!m_hInternet) {
			m_strLastError = _T("Cannot open internet");
			m_lastErrorCode = GetLastError();
			return false;
		}
			
		m_hSession = InternetConnect(m_hInternet, 
			m_strServerName, 
			m_wPort,
			m_strUserName, 
			m_strPassword,
			INTERNET_SERVICE_HTTP,
			0,
			0);
		if (!m_hSession) {			
			m_strLastError = _T("Cannot connect to internet");
			m_lastErrorCode = GetLastError();
			ClearHandles();
			return false;
		}
		m_hRequest = HttpOpenRequest(m_hSession, 
				strVerb,
				m_strObjectName,
				NULL,
				_T(""),
				NULL,
				m_secureFlags, 
				m_ReqID);
		if (!m_hRequest) {
			m_strLastError = _T("Cannot perform http request");
			m_lastErrorCode = GetLastError();
			ClearHandles();		
			return false;
		}
		
		m_ReqID++;
	}
	catch(...) {
		m_strLastError = _T("Memory Exception occured");
		m_lastErrorCode = GetLastError();
		return false;
	}
	return true;
}

bool CSslConnection::SendHttpsRequest(LPCSTR request)
{
	try {	
		for (int tries = 0; tries < 20; ++tries) {
			int len=0;
			if(request!=NULL)
				len=strlen(request);
			int result =  HttpSendRequest(m_hRequest, m_strHeader, m_strHeader.GetLength(), (LPVOID)request, len);
			if (result) 				
				return true;							
			int lastErr = GetLastError();
			if (lastErr == ERROR_INTERNET_CLIENT_AUTH_CERT_NEEDED) {
				if (m_bUseWechatCert&&!SetWechatCert()) {
					return false;
				}					
			}
			else if (lastErr == ERROR_INTERNET_INVALID_CA) {
				m_strLastError = _T("ERROR_INTERNET_INVALID_CA");
				m_lastErrorCode = GetLastError();
				return false;
			}
			else {
				m_strLastError = _T("Cannot perform http request");
				m_lastErrorCode = GetLastError();
				return false;
			}
		} 
	}
	catch(...) {
		m_strLastError = _T("Memory Exception occured");
		m_lastErrorCode = GetLastError();
		return false;
	}
	return false;
}

void CSslConnection::ClearHandles()
{
	if (m_hInternet) {
		InternetCloseHandle(m_hInternet);
		m_hInternet = NULL;
	}
		
	if (m_hSession) {
		InternetCloseHandle(m_hSession);
		m_hSession = NULL;
	}
		
	if (m_pContext) {
		CertFreeCertificateContext(m_pContext);
		m_pContext = NULL;
	}
}
/************************************************************************
微信支付需要双向认证，读取客户端证书
************************************************************************/
bool CSslConnection::SetWechatCert()
{
	CRYPT_DATA_BLOB data;
	FILE *fIn = _wfopen(_T("apiclient_cert.p12"), _T("rb"));
	if(fIn==NULL)
	{
		m_strLastError = _T("Open certificate failed");
		m_lastErrorCode = GetLastError();
		ClearHandles();
		return false;
	}
	char buffer[10240]={0};
	fseek(fIn, 0, SEEK_END);
	data.cbData = ftell(fIn);
	fseek(fIn, 0, SEEK_SET);
	data.pbData = (BYTE *)buffer;
	fread(data.pbData, 1, data.cbData, fIn);
	fclose(fIn);
	// Convert key-pair data to the in-memory certificate store
	// If the P12 file is protected with a password, pass it to
	// the function    
	HCERTSTORE hCertStore = PFXImportCertStore(&data, _T("1243900002"), 0);

	// Find the certificate in P12 file (we expect there is only one)    
	m_pContext = CertFindCertificateInStore
		(hCertStore, X509_ASN_ENCODING | PKCS_7_ASN_ENCODING, 0, CERT_FIND_ANY, NULL, NULL);

	if (!m_pContext) {
		m_strLastError = _T("Cannot find the required certificate");
		m_lastErrorCode = GetLastError();
		ClearHandles();
		return false;
	}
	
	// INTERNET_OPTION_CLIENT_CERT_CONTEXT is 84
	int res = InternetSetOption(m_hRequest, 
							INTERNET_OPTION_CLIENT_CERT_CONTEXT, 
							(void *) m_pContext, sizeof(CERT_CONTEXT));
	if (!res) {
		m_strLastError = _T("Cannot set certificate context");
		m_lastErrorCode = GetLastError();
		ClearHandles();
		return false;
	}
	
	return true;
}
void CSslConnection::GetRequestResult(CString& strResult)
{
	DWORD dwBytesRead;
	char buf[10240]={0};
	char tmp[1024]={0};
	int result;
	while (InternetReadFile(m_hRequest, tmp,sizeof(tmp)-1,&dwBytesRead)){
		if (0==dwBytesRead) 
			break;							
		tmp[dwBytesRead]=0;
		if(strcat_s(buf,10240,tmp))
			break;
		ZeroMemory(tmp,sizeof(tmp));
	}
	int textlen = ::MultiByteToWideChar(CP_UTF8, 0, buf,  -1, NULL, 0);
	WCHAR* sz0 = new WCHAR[textlen + 1];
	memset(sz0,0,textlen+1);
	::MultiByteToWideChar(CP_UTF8, NULL, buf, -1, sz0, textlen);
	strResult.Format(_T("%s"),sz0);
	delete sz0;
}