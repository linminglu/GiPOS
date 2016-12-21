////////////////////////////////////////////////////////////////
// CoolTabCtrl.h : header file                                //
//															  //
// Copyright 2001 WangJun									  //
// All Rights Reserved.										  //
//															  //
// Email: wangjun98@sohu.com								  //
// URL:   www.vckbase.com									  //
//															  //
// 1.0     2001/9/30   First release version.				  //
//															  //
////////////////////////////////////////////////////////////////

#if !defined(AFX_COOLTABCTRL_H__83DD41F0_25C9_417D_9353_777A80FAD1CF__INCLUDED_)
#define AFX_COOLTABCTRL_H__83DD41F0_25C9_417D_9353_777A80FAD1CF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#define TCS_UP			0x0001		///向上
#define TCS_DOWN		0x0002		///向下
#define TCS_MONOSPACE	0x0004		///等宽效果
#define TCS_ANIMATE		0x0008		///窗口拉动的动画效果
#define TCS_MASK		0x000f		///掩码:所有类型值相"或",供程序内部使用

/////////////////////////////////////////////////////////////////////////////
// CCoolTabCtrl window

class CCoolTabCtrl : public CWnd
{
public:
	class CPageItem
	{
		friend class CCoolTabCtrl;
		CWnd*		m_pWnd;		///窗口,可以为NULL
		UINT		m_nStyle;	///窗口类型，0:普通，1:对话框
		CString		m_sText;	///文字
		HICON		m_hIcon;	///图标
		CRgn		m_rgn;
	public:
		CRect		m_rect;		
	public:
		CPageItem()
		{
			m_rect=CRect(0,0,0,0);
		}
		UINT GetAreaWidth(CDC *pDC);
		void ComputeRgn();
		void Draw(CDC *pDC,UINT nStyle,BOOL bActive);

	};
	DECLARE_DYNCREATE(CCoolTabCtrl)
// Construction
public:
	CCoolTabCtrl();

// Attributes
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCoolTabCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	void UpdateWindow();
	void* GetPageItem(UINT nIndex);
	BOOL DisablePage(UINT nIndex,BOOL bDisable=TRUE);
	void SetActivePage(int nIndex,BOOL bRedraw=FALSE);
	void UpdateTitle(int nIndex,LPCTSTR sText);
	BOOL AddPage(CRuntimeClass* pClass,UINT nIDTemplate,LPCTSTR sText,UINT IconID = NULL);
	void AddPage(CWnd *pWnd,LPCTSTR sText,UINT IconID = NULL);
	void AutoSize();
	void GetClientRect(LPRECT lpRect );
	BOOL Create(UINT wStyle, const CRect & rect, CWnd * pParentWnd, UINT nID);
	void RemovePage(int nIndex);
	int GetPageCount();
	CWnd* GetActivePage();
	int GetActivePageIndex();
	virtual ~CCoolTabCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CCoolTabCtrl)
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	int			m_nActivePage;
	UINT		m_nStyle;
	CPtrList	m_PageList;
	CDC			m_dcBk;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COOLTABCTRL_H__83DD41F0_25C9_417D_9353_777A80FAD1CF__INCLUDED_)
