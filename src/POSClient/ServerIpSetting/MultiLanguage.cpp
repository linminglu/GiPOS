#include "StdAfx.h"
#include "MultiLanguage.h"
#include <locale.h>

CMultiLanguage::CMultiLanguage(void)
{
	m_bDefaultLang=TRUE;
}

CMultiLanguage::~CMultiLanguage(void)
{
}

void CMultiLanguage::Initialize()
{
	CString lang;
	::GetPrivateProfileString(_T("POS"),_T("LANGUAGE"),_T("zh_CN"),lang.GetBuffer(40),40,_T(".\\config.ini"));
	lang.ReleaseBuffer();
	CString line;
	TCHAR str[512];
	int i_type=0;
	line.Format(_T("Languages\\Ipsetting_%s.lng"),lang);
	FILE* fin=0;
#ifdef UNICODE
	_wfopen_s(&fin,line,_T("r,ccs=UNICODE"));
#else
	fopen_s(&fin,line,_T("r"));
#endif
	if (fin==NULL)
		return;
	m_bDefaultLang=FALSE;
	int fontsize;
	LOGFONT m_tLogFont;
	memset(&m_tLogFont,0,sizeof(LOGFONT));
	CStdioFile file(fin);
	while( file.ReadString(line) )
	{
		memset(str,0,512);
		line.TrimLeft();
		if(line.IsEmpty())
			continue;
		if (line==_T("[STRING_TABLE]"))
		{
			i_type=1;
			continue;
		}
		if (i_type==0)
		{
			if (line.Find(_T("DialogFontName"))>=0)
			{
#ifdef UNICODE
				swscanf_s(line,_T("DialogFontName=%[^\n]"),m_tLogFont.lfFaceName,32);
#else
				sscanf_s(line,_T("DialogFontName=%[^\n]"),m_tLogFont.lfFaceName,32);
#endif
			}
			else if (line.Find(_T("DialogFontSize"))>=0)
			{
#ifdef UNICODE
				swscanf_s(line,_T("DialogFontSize=%d"),&fontsize);
#else
				sscanf_s(line,_T("DialogFontSize=%d"),&fontsize);
#endif
			}
		}
		else if(i_type==1)
		{
			int resID=0;
#ifdef UNICODE
			swscanf_s(line,_T("%d=%[^\n]"),&resID,str,512);
#else
			sscanf_s(line,_T("%d=%[^\n]"),&resID,str,512);
#endif
			if (resID>0)
			{
				CString str2=str;
				str2.Replace(_T("\\n"),_T("\n"));
				str2.Replace(_T("\\r"),_T("\r"));
				str2.Replace(_T("\\t"),_T("\t"));
				m_StringTable.insert(pair<UINT,CString>(resID,str2));
			}
		}
	}
	
	m_tLogFont.lfHeight	= fontsize;
	m_tLogFont.lfWeight=FW_NORMAL;
	m_dialogFont.CreateFontIndirect(&m_tLogFont);
	fclose(fin);
}
void CMultiLanguage::LoadString(UINT uResID, CString& strVal)
{
	map<UINT,CString>::iterator iter;
	iter=m_StringTable.find(uResID);
	if (iter==m_StringTable.end())
	{
		strVal.LoadString(uResID);
	}
	else
	{
		strVal=iter->second;
	}
}
void CMultiLanguage::LoadString(CString& strVal,UINT uResID)
{
	map<UINT,CString>::iterator iter;
	iter=m_StringTable.find(uResID);
	if (iter==m_StringTable.end())
	{
		strVal.LoadString(uResID);
	}
	else
	{
		strVal=iter->second;
	}
}
void CMultiLanguage::TranslateDlgItem(CWnd* pCtrl,UINT uResID)
{
	if (pCtrl)
	{
		CString str2;
		LoadString(uResID,str2);
		pCtrl->SetWindowText(str2);
		pCtrl->SetFont(&m_dialogFont);
	}
}
