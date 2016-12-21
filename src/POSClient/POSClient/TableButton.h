#pragma once
#include "afxwin.h"
#include <GdiPlus.h>

class CTableButton :
	public CButton
{
public:
	enum ICON_ALIGNMENT
	{
		CENTER = 0,
		LEFT,
		RIGHT,
		UP,
		DOWN,
		RIGHTDOWN
	};
	CString m_strBottom;
	//! Constructor
	CTableButton(void);
	//! Destructor
	~CTableButton(void);

	/************************************************************************/
	/* Functions for Design of Button                                       */
	/************************************************************************/
	void SetStrTop(LPCTSTR strMark);
	//! Set Font of Button
	bool SetFont(CFont* pFont);
	//! Set Color of Caption
	bool SetTextColor(COLORREF	_ptTextColor);
	bool SetTextColor(COLORREF _ptTextColor,COLORREF _ptPressColor);
	CTableButton& SetIcon(UINT nIDResource, ICON_ALIGNMENT ia = LEFT);
	CTableButton& SetIcon(HICON hIcon, ICON_ALIGNMENT ia = LEFT,BOOL bDestroy = TRUE);
//	BOOL SetImage(HBITMAP hBitmapIn,HBITMAP hBitmapOut,BOOL bDestroy=TRUE);
	BOOL SetImages(Gdiplus::Image* hBitmapIn,Gdiplus::Image* hBitmapOut,bool bDestroy=true);
	void SetImage(CString path);
	static Gdiplus::Image* CreateDarkerBitmap(Gdiplus::Image* hBitmap);
	static COLORREF DarkenColor(COLORREF crColor, double dFactor);
	DWORD SetCheck(int nCheck, BOOL bRepaint = TRUE);
	int GetCheck();
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
	//! PreSubclass-Function
	virtual void PreSubclassWindow();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	void DrawIcon();
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
private:
	//! Size of Button-Images
	CRect	m_rBtnSize;
	//! Font for Caption
	CFont*	m_tBtnFont;
	//! Color Scheme of Caption
	COLORREF	m_tTextColor[2];
	HICON			m_hIcon;
	ICON_ALIGNMENT	m_eIconAlignment;
	Gdiplus::Image* m_tImage;
	Gdiplus::Image* m_tImagep;
	CDC m_Memdc;
	CDC	m_dcBk;
	bool	m_bRedraw;
	bool	m_bDeleteImage;
	CString m_strTop;
	int m_nCheck;
};