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

class CPosPage : public CDialog
{
	DECLARE_DYNAMIC(CPosPage)

public:
	int m_nID;
	int m_nPrePage;//前页要跳转的页
	CString m_strTmplate;
	HBITMAP m_bpBackgrd;
	int m_x;
	int m_y;
	CPosPage(int nId);
	virtual ~CPosPage();
	virtual void OnSetActive();
	virtual BOOL LockScreen();
protected:
	CreatButton m_btnCtrl;//按钮列表
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnNextPage(UINT uID);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	void InitDialog(CString strImgPath);
};


