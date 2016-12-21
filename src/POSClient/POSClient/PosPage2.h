#pragma once
/*********************************************************************
*Copyright (c) 2011 Coolroid Co.Ltd.
*DESCRIPTION：
*		各页面的父类。
*AUTHOR ：zhangyi
*HISTORY：
*		author time    version   desc

*********************************************************************/

// CPosPage

class CPosPage2 : public CDialog
{
	DECLARE_DYNAMIC(CPosPage2)

public:
	int m_nID;
	int m_x;
	int m_y;
	CWnd* m_hParent;
	DWORD m_textColor;
	HBITMAP m_bpBackgrd;
	CPosPage2(int nId);
	virtual ~CPosPage2();
protected:
	virtual void OnCancel();
	virtual void PostNcDestroy();
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	void InitDialog(CString strImgPath);
};


