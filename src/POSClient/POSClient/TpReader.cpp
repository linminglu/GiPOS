#include "stdafx.h"
#include "TpReader.h"
#include <iostream>
#include <Windows.h>
#include "StringConvert.h"
#include "resource.h"

#pragma warning(disable:4996)
#pragma warning(disable:4267)



char  szResults[STR_BUF];
CString strResult;
CTpReader::CTpReader(char* szFileName)
{ 
	memset(m_szFileName, 0x00, STR_BUF); 
	memcpy(m_szFileName, szFileName, strlen(szFileName));
}

CTpReader::CTpReader(CString strFileName)
{ 
	m_strFileName = strFileName;
	int len = strFileName.GetLength();
	memset(m_szFileName, 0x00, STR_BUF); 
	CString2MultiByte(strFileName, m_szFileName, len+1);
}

int CTpReader::ReadInteger(char* szSection, char* szKey, int iDefaultValue)
{ 
	int iResult = GetPrivateProfileIntA(szSection,  szKey, iDefaultValue, m_szFileName);  

	return iResult;
}

double CTpReader::ReadFloat(char* szSection, char* szKey, float fltDefaultValue)
{ 
	char szResult[STR_BUF]; 
	char szDefault[STR_BUF]; 
	double fltResult; 

	sprintf(szDefault, "%f",fltDefaultValue); 
	GetPrivateProfileStringA(szSection,  szKey, szDefault, szResult, STR_BUF, m_szFileName);  
	fltResult =  atof(szResult); 

	return fltResult;
}

bool CTpReader::ReadBoolean(char* szSection, char* szKey, bool bolDefaultValue)
{ 
	char szResult[STR_BUF]; 
	char szDefault[STR_BUF]; 
	bool bolResult; 

	sprintf(szDefault, "%s", bolDefaultValue? "True" : "False"); 
	GetPrivateProfileStringA(szSection, szKey, szDefault, szResult, STR_BUF, m_szFileName); 
	if(strcmp(szResult, "True") == 0
		||strcmp(szResult, "true") == 0
		||strcmp(szResult, "TRUE") == 0)
	{
		bolResult = true; 
	}
	else
	{
		bolResult = false;
	}


	return bolResult;
}

char* CTpReader::ReadString(char* szSection, char* szKey, const char* szDefaultValue)
{ 
	memset(szResults, 0x00, 512); 
	GetPrivateProfileStringA(szSection,  szKey, szDefaultValue, szResults, 512, m_szFileName);  

	return szResults;
}

CString CTpReader::ReadCString(char* szSection, char* szKey, const char* szDefaultValue)
{
	char* pStr = NULL;
	pStr		= ReadString(szSection,szKey,szDefaultValue);
	CString strCString;
	MultiByte2CString(pStr,strlen(pStr)+1,strCString);

	return strCString;
	/*CString strCString;
	memset(szResults, 0x00, 512); 
	GetPrivateProfileStringA(szSection,  szKey, szDefaultValue, szResults, 512, m_szFileName);  

	MultiByte2CString(szResults,strlen(szResults)+1,strCString);

	return strCString;*/
}

COLORREF CTpReader::ReadRGB(char* szSection, char* szKey, const COLORREF rgbDefaultValue)
{
	char szResult[STR_BUF]; 
	char szDefault[STR_BUF];

	sprintf(szDefault, "RGB(%d,%d,%d)", GetRValue(rgbDefaultValue), GetGValue(rgbDefaultValue), GetBValue(rgbDefaultValue));
	GetPrivateProfileStringA(szSection, szKey, szDefault, szResult, STR_BUF, m_szFileName); 

	UINT r,g,b;
	sscanf(szResult, "RGB(%d,%d,%d)", &r, &g, &b);

	return RGB(r,g,b);
}


CRect CTpReader::ReadCRect(char* pStrSection,char* pStrKey,CRect rcDefault)
{
	char strResult[STR_BUF]; 
	char strDefault[STR_BUF];

	sprintf(strDefault, "%d,%d,%d,%d",rcDefault.left,rcDefault.top,rcDefault.Width(),rcDefault.Height() );
	GetPrivateProfileStringA(pStrSection, pStrKey, strDefault, strResult, STR_BUF, m_szFileName); 

	UINT l,t,w,h;
	sscanf(strResult, "%d,%d,%d,%d", &l, &t, &w ,&h);

	CPoint point	= CPoint(l,t);
	CSize  size		= CSize(w,h); 

	return CRect(point,size);
}

//////////////////////////////////////////////////////////////////////////
/// CString
//////////////////////////////////////////////////////////////////////////

int	CTpReader::ReadInteger(CString strSection, CString strKey, int iDefaultValue)
{

	int iResult = GetPrivateProfileInt(strSection,  strKey, iDefaultValue, m_strFileName);  

	return iResult;
}

double CTpReader::ReadFloat(CString strSection, CString strKey, float fltDefaultValue)
{ 
	CString strDefault;
	CString strResult;
	double fltResult; 


	strDefault.Format(_T("%f"),fltDefaultValue); 

#ifdef UNICODE
	WCHAR strResultW[STR_BUF];
	CString2WideChar(strResult,strResultW,STR_BUF);
	GetPrivateProfileString(strSection,  strKey, strDefault, strResultW, STR_BUF, m_strFileName);
	fltResult =  _wtof(strResult); 
#else
	char szResult[STR_BUF]; 
	char szKey[STR_BUF];
	char szDefault[STR_BUF]; 
	char szSection[STR_BUF];

	CString2MultiByte(strSection,szSection,STR_BUF);
	CString2MultiByte(strKey,szKey,STR_BUF);
	CString2MultiByte(strDefault,szDefault,STR_BUF);
	CString2MultiByte(strResult,szResult,STR_BUF);

	sprintf(szDefault, "%f",fltDefaultValue); 
	GetPrivateProfileString(szSection,  szKey, szDefault, szResult, STR_BUF, m_szFileName); 
	fltResult =  atof(strResult); 
#endif


	return fltResult;
}

BOOL CTpReader::ReadBoolean(CString strSection, CString strKey, BOOL bolDefaultValue)
{ 
	CString strResult;
	CString strDefault;
	BOOL bResult;
#ifdef UNICODE
	WCHAR strResultW[STR_BUF];
	CString2WideChar(strResult,strResultW,STR_BUF);
	if(TRUE == bolDefaultValue)
	{
		strDefault = _T("TRUE");
	}
	else
	{
		strDefault = _T("FALSE");
	}
	GetPrivateProfileString(strSection,  strKey, strDefault, strResultW, STR_BUF, m_strFileName);
	strResult.MakeUpper();
	if(_T("TRUE") == strResult)
	{
		bResult = TRUE; 
	}
	else
	{
		bResult = FALSE; 
	}
#else
	char szResult[STR_BUF]; 
	char szKey[STR_BUF];
	char szDefault[STR_BUF]; 
	char szSection[STR_BUF];

	CString2MultiByte(strSection,szSection,STR_BUF);
	CString2MultiByte(strKey,szKey,STR_BUF);
	CString2MultiByte(strDefault,szDefault,STR_BUF);
	CString2MultiByte(strResult,szResult,STR_BUF);

	sprintf(szDefault, "%s", bolDefaultValue? "True" : "False"); 
	GetPrivateProfileStringA(strSection, strKey, strDefault, szResult, STR_BUF, m_strFileName); 
	if(strcmp(strResult, "True") == 0
		||strcmp(strResult, "true") == 0
		||strcmp(strResult, "TRUE") == 0)
	{
		bResult = true; 
	}
	else
	{
		bResult = false;
	}
#endif


	return bResult;
}

CString CTpReader::ReadString(CString strSection, CString strKey, const CString strDefault)
{ 
	CString strResult;
#ifdef UNICODE
	WCHAR* strResultW = new WCHAR[STR_BUF];
	CString2WideChar(strResult,strResultW,STR_BUF);
	GetPrivateProfileString(strSection,  strKey, strDefault, strResultW, STR_BUF, m_strFileName);
	WideChar2CString(strResultW,STR_BUF,strResult);
	delete strResultW;
#else
	char szResult[STR_BUF]; 
	char szKey[STR_BUF];
	char szDefault[STR_BUF]; 
	char szSection[STR_BUF];

	CString2MultiByte(strSection,szSection,STR_BUF);
	CString2MultiByte(strKey,szKey,STR_BUF);
	CString2MultiByte(strDefault,szDefault,STR_BUF);
	CString2MultiByte(strResult,szResult,STR_BUF);

	GetPrivateProfileString(strSection, strKey, strDefault, szResult, STR_BUF, m_strFileName); 
	MultiByte2CString(szResult,strlen(szResult) + 1,strResult);
#endif
	return strResult;
}


COLORREF CTpReader::ReadRGB(CString strSection, CString strKey, const COLORREF rgbDefaultValue)
{
	/*CString strResult;
	CString strDefault;
#ifdef UNICODE
	WCHAR* strResultW = new WCHAR[STR_BUF];
	CString2WideChar(strResult,strResultW,STR_BUF);
	strDefault.Format(_T("RGB(%d,%d,%d)"), GetRValue(rgbDefaultValue), GetGValue(rgbDefaultValue), GetBValue(rgbDefaultValue));
	GetPrivateProfileString(strSection, strKey, strDefault, strResultW, STR_BUF, m_strFileName); 

	UINT r,g,b;
	_stscanf(strResult,_T("RGB(%d,%d,%d)"), &r, &g, &b);
	delete strResultW;

#else
	char szResult[STR_BUF]; 
	char szKey[STR_BUF];
	char szDefault[STR_BUF]; 
	char szSection[STR_BUF];


	CString2MultiByte(strSection,szSection,STR_BUF);
	CString2MultiByte(strKey,szKey,STR_BUF);
	CString2MultiByte(strDefault,szDefault,STR_BUF);
	CString2MultiByte(strResult,szResult,STR_BUF);

	sprintf(szDefault, "RGB(%d,%d,%d)", GetRValue(rgbDefaultValue), GetGValue(rgbDefaultValue), GetBValue(rgbDefaultValue));
	GetPrivateProfileString(strSection, strKey, strDefault, szResult, STR_BUF, m_strFileName); 

	UINT r,g,b;
	sscanf(strResult, "RGB(%d,%d,%d)", &r, &g, &b);
#endif



	return RGB(r,g,b);*/
	TCHAR szResult[255]; 
	TCHAR szDefault[255];
	_stprintf(szDefault, _T("RGB(%d,%d,%d)"), GetRValue(rgbDefaultValue), GetGValue(rgbDefaultValue), GetBValue(rgbDefaultValue));
	GetPrivateProfileString(strSection, strKey, szDefault, szResult, 255, m_strFileName); 

	UINT r,g,b;
	_stscanf(szResult, _T("RGB(%d,%d,%d)"), &r, &g, &b);

	return RGB(r,g,b);
}

void CTpReader::ReadRect(PCTSTR szSection, PCTSTR szKey, RECT * pRect)
{
	TCHAR szResult[255]; 
	TCHAR szDefault[255];
	_stprintf(szDefault, _T("RECT(%d,%d,%d,%d)"), 0, 0, 0, 0);	//如果读取失败时的默认值为RECT(0,0,0,0)
	GetPrivateProfileString(szSection, szKey, szDefault, szResult, 255, m_strFileName);
	_stscanf(szResult, _T("RECT(%d,%d,%d,%d)"), &pRect->left, &pRect->top, &pRect->right, &pRect->bottom);
	//pRect->right+=pRect->left;
	//pRect->bottom+=&pRect->top;
}