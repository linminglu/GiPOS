#pragma once
#include "roundbutton2.h"
#include "information_screens.h"
#include "afxwin.h"

// InformationDlg 对话框

class InformationDlg : public CDialog
{
	DECLARE_DYNAMIC(InformationDlg)

public:
	InformationDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~InformationDlg();

// 对话框数据
	enum { IDD = IDD_INFOMATION };

protected:
	Cinformation_screens m_infoSet;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonLeft();
	afx_msg void OnBnClickedButtonRight();
	CRoundButton2 m_btLeft;
	CRoundButton2 m_btRight;
	CRoundButton2 m_btCancel;
	HBITMAP m_bpBackgrd;
	int m_x;
	int m_y;
	virtual BOOL OnInitDialog();
	CListBox m_list;
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};
