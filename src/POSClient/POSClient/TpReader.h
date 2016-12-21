#ifndef _TpReader_H
#define _TpReader_H

#define		STRING_LEN_MAX	3076
#define		STR_BUF		1024

class CTpReader

{
public:
	CTpReader(char* szFileName); 
	CTpReader(char* szFileName,char* strSection); 
	CTpReader(CString strFileName);
	int			ReadInteger(char* szSection, char* szKey, int iDefaultValue);
	double		ReadFloat(char* szSection, char* szKey, float fltDefaultValue);
	bool		ReadBoolean(char* szSection, char* szKey, bool bolDefaultValue);
	char*		ReadString(char* szSection, char* szKey, const char* szDefaultValue);
	COLORREF	ReadRGB(char* szSection, char* szKey, const COLORREF rgbDefaultValue);
	CRect		ReadCRect(char* pStrSection,char* pStrKey,CRect rcDefault);

	CString		ReadCString(char* szSection, char* szKey, const char* szDefaultValue);

public:
	int			ReadInteger(CString strSection, CString strKey, int iDefaultValue);
	double		ReadFloat(CString strSection, CString strKey, float fltDefaultValue);
	BOOL		ReadBoolean(CString strSection, CString strKey, BOOL bolDefaultValue);
	CString		ReadString(CString strSection, CString strKey, const CString strDefaultValue);
	COLORREF	ReadRGB(CString strSection, CString strKey, const COLORREF rgbDefaultValue);
	CRect		ReadCRect(CString pStrSection,CString pStrKey,CRect rcDefault);
	void		ReadRect(PCTSTR szSection, PCTSTR szKey, RECT * pRect);

private:
	char m_szFileName[STR_BUF];
	CString m_strFileName;
};
#endif//TpReader_H