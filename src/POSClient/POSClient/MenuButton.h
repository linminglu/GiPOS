#pragma once
#include "afxwin.h"
#include "RoundButton2.h"

class CMenuButton :
	public CRoundButton2
{
public:
	//! Constructor
	CMenuButton(void);
	int m_nType;//0- 旧风格 1-特殊显示
	//! Destructor
	virtual ~CMenuButton(void);
	/************************************************************************/
	/* Message-Map of Control                                               */
	/************************************************************************/
	DECLARE_MESSAGE_MAP()
protected:

	/************************************************************************/
	/* Own Drawing-Functions                                                */
	/************************************************************************/
	//! Draw Caption on Button
	void DrawButtonCaption(CDC *_pDC,LPCTSTR sCaption,CRect& rect);
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	
};