#pragma once
#include "afxwin.h"
#include "roundbutton2.h"
#include "ACEdit.h"


// StringInputDlg 对话框

class StringInputDlg : public CDialog
{
	DECLARE_DYNAMIC(StringInputDlg)

public:
	StringInputDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~StringInputDlg();
	CString m_strTitle;
	CString m_strInput;
	CString m_strTmplate;
	int m_x;
	int	m_y;
// 对话框数据
	enum { IDD = IDD_STRINGINPUT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	CreatButton m_btnCtrl;
	HBITMAP m_bpBackgrd;
	int last_clock;
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedClear();
	afx_msg void OnNumBnClicked(UINT uID);
	afx_msg void OnAsciiBnClicked(UINT uID);
	afx_msg void OnBnClickedCtrlShfit();
	afx_msg void OnBnClickedCtrlHandInput();
	afx_msg void OnCancel();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CACEdit m_ctrlEdit;
	BOOL m_bSearchMode;//是否为编码点菜模式
	BOOL m_bAutoComplete;//是否打开自动完成
	virtual BOOL PreTranslateMessage(MSG* pMsg);
protected:
	virtual void OnOK();
public:
	afx_msg LRESULT OnEnChangeEdit1(WPARAM wParam, LPARAM lParam);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};
