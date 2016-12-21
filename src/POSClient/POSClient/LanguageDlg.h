#pragma once


// CLanguageDlg 对话框

class CLanguageDlg : public CDialog
{
	DECLARE_DYNAMIC(CLanguageDlg)

public:
	CLanguageDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLanguageDlg();

// 对话框数据
	enum { IDD = IDD_LANGUAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	Gdiplus::Image* hbmp;
	Gdiplus::Image* hbmp1;
	std::vector<CButton*> m_itemButtons;
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedRadio(UINT uID);
};
