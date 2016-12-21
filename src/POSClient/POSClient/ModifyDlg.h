#pragma once
#include "coloredit.h"
#include "afxwin.h"
#include "roundbutton2.h"


// ModifyDlg 对话框

class ModifyDlg : public CDialog
{
	DECLARE_DYNAMIC(ModifyDlg)

public:
	ModifyDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~ModifyDlg();
	OrderDetail* m_item;
//	CString
// 对话框数据
	enum { IDD = IDD_MODIFY };

protected:
	double m_prices[5];
	CString m_unit[5];
	Gdiplus::Image* m_bpButtonItem[2];
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedUnit(UINT uID);
	CRoundButton2 m_cancelBt;
	CRoundButton2 m_button[5];
	afx_msg void OnBnClickedCancel();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnPaint();
};
