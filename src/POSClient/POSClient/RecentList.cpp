#include "stdafx.h"
#include "RecentList.h"

CRecentList::CRecentList(UINT nStart, LPCTSTR lpszSection, 
		 LPCTSTR lpszEntryFormat, int nSize, int nMaxDispLen /* = AFX_ABBREV_FILENAME_LEN */)
		: CRecentFileList(nStart,lpszSection,lpszEntryFormat,nSize,nMaxDispLen)
{
}

void CRecentList::Add(LPCTSTR lpszPathName)
{	
	ASSERT(m_arrNames != NULL); 
	ASSERT(lpszPathName != NULL); 
	ASSERT(AfxIsValidString(lpszPathName)); 

	// 查找,看是否已经有此文件名
	int iMRU = 0;
	for (; iMRU < m_nSize-1; iMRU++) 
	{
		if (m_arrNames[iMRU]==lpszPathName)
			break; // iMRU will point to matching entry 
	} 
	// 其前面的各项后移 
	for (; iMRU > 0; iMRU--) 
	{ 
		ASSERT(iMRU > 0); 
		ASSERT(iMRU < m_nSize); 
		m_arrNames[iMRU] = m_arrNames[iMRU-1]; 
	} 
	//添加到起始位置 
	m_arrNames[0] = lpszPathName; 
}
