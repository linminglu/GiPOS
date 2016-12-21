#include "StdAfx.h"
#include "StringConvert.h"





#ifdef UNICODE
BOOL CString2MultiByteW( CString srcStr, CHAR* lpMultiByte, int iByteLen )
{
	if ( NULL == lpMultiByte )
	{
		return FALSE;
	}
	int strLen = srcStr.GetLength()+1;
	WCHAR *szStr = new WCHAR[strLen];
	lstrcpy(szStr, srcStr.GetBuffer());
	if ( FALSE == WideChar2MultiByte(szStr, strLen, lpMultiByte, iByteLen ))
	{
		delete szStr;
		return FALSE;	
	}
	delete szStr;
	return TRUE;
}




#else

BOOL  CString2MultiByteA( CString srcStr, CHAR* lpMultiByte, int iByteLen )
{

	
	if ( srcStr.GetLength()+1 > iByteLen)
	{
		return FALSE;
	}
	
	strcpy(lpMultiByte, srcStr.GetBuffer());
	return TRUE;
}




#endif


#ifdef UNICODE

BOOL CString2WideCharW( CString srcStr, WCHAR* lpWideChar, int iCharLen )
{ 
	if ( NULL == lpWideChar )
	{
		return FALSE;
	}
	int strLen = srcStr.GetLength()+1;

	lstrcpy(lpWideChar, srcStr.GetBuffer()); 	 

	return TRUE;

}


#else

BOOL CString2WideCharA( CString srcStr, WCHAR* lpWideChar, int iCharLen )
{
	if ( NULL == lpWideChar )
	{
		return FALSE;
	}
	int strLen = srcStr.GetLength()+1;

	if ( strLen > iCharLen)
	{
		return FALSE;
	}


	CHAR *charStr = new CHAR[strLen];

	CString2MultiByteA(srcStr, charStr, strLen);
	MultiByte2WideChar(charStr, strLen, lpWideChar, strLen);


	delete charStr;

	return TRUE;
}


#endif // UNICODE





#ifdef UNICODE

BOOL  MultiByte2CStringW( CHAR* lpMultiByte, int iByteLen, CString &destStr )
{
	if ( NULL == lpMultiByte)
	{
		return FALSE;
	}


	lpMultiByte[iByteLen-1] = '\0';
	WCHAR *szBuf =  new WCHAR[iByteLen];
	MultiByte2WideChar(lpMultiByte, iByteLen,szBuf, iByteLen);
	
	destStr.Format(_T("%s"),szBuf );

	delete szBuf;

	return TRUE;
}

#else

BOOL  MultiByte2CStringA( CHAR* lpMultiByte, int iByteLen, CString &destStr )
{
	if ( NULL == lpMultiByte )
	{
		return FALSE;
	}

	destStr.Format(_T("%s"), lpMultiByte);

	return TRUE;
}

#endif


#ifdef UNICODE
 

BOOL  WideChar2CStringW( WCHAR* lpWideChar, int iCharLen, CString &destStr )
{
	if ( NULL == lpWideChar )
	{
		return FALSE;
	}

	destStr.Format(_T("%s"), lpWideChar);

	return TRUE;
}

#else

BOOL  WideChar2CStringA( WCHAR* lpWideChar, int iCharLen, CString &destStr )
{
	if ( NULL == lpWideChar )
	{
		return FALSE;
	}

	CHAR * szBuf = new CHAR[iCharLen];
	WideChar2MultiByte(lpWideChar, iCharLen, szBuf, iCharLen);

	destStr.Format(_T("%s"), szBuf);

	delete szBuf;

	return TRUE;
}


#endif // UNICODE

BOOL  MultiByte2WideChar( CHAR* lpMultiByte, int iByteLen, WCHAR* lpWideChar, int iCharLen )
{
	MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, lpMultiByte, iByteLen, lpWideChar, iCharLen);
	return TRUE;
}



BOOL  WideChar2MultiByte( WCHAR* lpWideChar, int iCharLen, CHAR* lpMultiByte, int iByteLen )
{

	if ( NULL == lpWideChar || NULL == lpMultiByte || iCharLen > iByteLen )
	{
		return FALSE;
	}

	
	WideCharToMultiByte(CP_ACP, WC_NO_BEST_FIT_CHARS, lpWideChar, iCharLen, lpMultiByte, iByteLen, NULL, NULL);


	return TRUE;
}

UINT CODE_PAGE=CP_ACP;
static char TEXT_POOL[2048];
char* UnicodeToANSI(LPCTSTR str)
{
	char* result;
	int textlen;
	textlen = WideCharToMultiByte( CODE_PAGE, 0, str, -1, NULL, 0, NULL, NULL );
	if(textlen>2047)
		result =(char *)malloc((textlen+1)*sizeof(char));
	else
		result=TEXT_POOL;
	memset( result, 0, sizeof(char) * ( textlen + 1 ) );
	WideCharToMultiByte( CODE_PAGE, 0, str, -1, result, textlen, NULL, NULL );
	return result;
}
WCHAR W_TEXT_POOL[2048];
WCHAR* ANSI2Unicode(LPCSTR str)
{
	WCHAR* result;
	int textlen;
	textlen = MultiByteToWideChar( CODE_PAGE, 0, str, -1, NULL, 0);
	if(textlen>2047)
		result =(WCHAR *)malloc((textlen+1)*sizeof(WCHAR));
	else
		result=W_TEXT_POOL;
	memset( result, 0, sizeof(WCHAR) * ( textlen + 1 ) );
	MultiByteToWideChar( CODE_PAGE, 0, str, -1, result, textlen);
	return result;
}

inline BYTE toHex(const BYTE &x)
{
	return x > 9 ? x + 55: x + 48;
}
bool my_isalnum( char ch )
{
	return (  (ch >= 'a' && ch <= '}')
		|| (ch >= 'A' && ch <= 'Z')
		|| (ch > '%' && ch <= '?') ); 
}
CString URLEncode2(CStringA sIn)
{
	CString sOut;

	const int nLen = sIn.GetLength() + 1;

	register LPTSTR pOutTmp = NULL;
	LPTSTR  pOutBuf = NULL;
	register LPBYTE pInTmp = NULL;
	LPBYTE pInBuf =(LPBYTE)sIn.GetBuffer(nLen);

	//alloc out buffer
	pOutBuf = (LPTSTR)sOut.GetBuffer(nLen  * 3 - 2);//new BYTE [nLen  * 3];

	if(pOutBuf)
	{
		pInTmp	= pInBuf;
		pOutTmp = pOutBuf;

		// do encoding
		while (*pInTmp)
		{
			if (isalnum(*pInTmp) || 
				(*pInTmp == '-') ||
				(*pInTmp== '_') ||
				(*pInTmp== '.') ||
				(*pInTmp== '~'))
				*pOutTmp++ = *pInTmp;
			else
				if(isspace(*pInTmp))
					*pOutTmp++ = '+';
				else
				{
					*pOutTmp++ = '%';
					*pOutTmp++ = toHex(*pInTmp>>4);
					*pOutTmp++ = toHex(*pInTmp%16);
				}
				pInTmp++;
		}
		*pOutTmp = '\0';
		sOut.ReleaseBuffer();
	}
	sIn.ReleaseBuffer();
	return sOut;
}
CString URLEncode(CString strIn)
{
	int wcsLen0 = ::WideCharToMultiByte(CP_UTF8, NULL, strIn,strIn.GetLength(), NULL, 0, NULL, NULL);
	char* sz0 = new char[wcsLen0 + 1];
	memset(sz0,0,wcsLen0 + 1);
	::WideCharToMultiByte(CP_UTF8, NULL, strIn, strIn.GetLength(), sz0, wcsLen0,  NULL, NULL);
	CStringA tmp;
	tmp.Format("%s",sz0);
	delete sz0;
	return URLEncode2(tmp);
}

CString URLEncode3(CString strIn)
{
	unsigned long size = 512;
	TCHAR lpszBuffer [512];
	//InternetCanonicalizeUrl(strIn,lpszBuffer,&size,0);
	UrlEscape(strIn,lpszBuffer,&size,0);
	CString strOut;
	strOut.Format(_T("%s"),lpszBuffer);
	return strOut;
}
