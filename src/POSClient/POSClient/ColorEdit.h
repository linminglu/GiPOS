#pragma once
/*********************************************************************
*Copyright (c) 2011 Coolroid Co.Ltd.
*DESCRIPTION：
*		自绘的CEdit控件，用于显示客户信息和提示信息。
*AUTHOR ：zhangyi
*HISTORY：
*		author time    version   desc

*********************************************************************/

// CColorEdit

class CColorEdit : public CEdit
{
	DECLARE_DYNAMIC(CColorEdit)

public:
	CColorEdit();
	virtual ~CColorEdit();
	COLORREF m_BackColor;
	//BOOL m_bTransparent;
	UINT m_nFormat;
	COLORREF m_TextColor;
protected:
	CBrush m_Brush;
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
};


