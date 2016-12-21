#ifndef _WSAP_RECENT_FILE_LIST_H
#define _WSAP_RECENT_FILE_LIST_H

class CRecentList : public CRecentFileList
{
public:
	CRecentList(UINT nStart, LPCTSTR lpszSection,
		LPCTSTR lpszEntryFormat, int nSize,
		int nMaxDispLen = AFX_ABBREV_FILENAME_LEN);
	
	virtual void Add(LPCTSTR lpszPathName);
};

#endif //_WSAP_RECENT_FILE_LIST_H