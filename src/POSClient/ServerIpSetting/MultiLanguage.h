#pragma once
#include <map>
using namespace std;

class CMultiLanguage
{
public:
	//int m_nCodePage;
	BOOL m_bDefaultLang;
	CFont m_dialogFont;
	CMultiLanguage(void);
	~CMultiLanguage(void);
	void Initialize();
	void LoadString(UINT uResID, CString& strVal);
	void LoadString(CString& strVal,UINT uResID);
	void TranslateDlgItem(CWnd* pWnd,UINT uResID);
protected:
	std::map<UINT,CString> m_StringTable;
};
