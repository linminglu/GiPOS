#pragma once


// FunctionDlg 对话框

class FunctionDlg : public CPosPage
{
	DECLARE_DYNAMIC(FunctionDlg)

public:
	FunctionDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~FunctionDlg();
	void OnSetActive();
	BOOL LockScreen();
// 对话框数据
	enum { IDD = IDD_FUNCTION };
	CStatic m_logCtrl;
	CStatic m_guestCtrl;
	CStatic m_tableCtrl;
	CStatic m_checkCtrl;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedSendOrder();
	afx_msg void OnBnClickedPrepage();
	afx_msg void OnBnClickedTransfer();
	afx_msg void OnBnClickedSplit();
	static BOOL TransTable();
	static void CombineTable();
	static void ClearPercentDsicServ(long order_head_id);
	afx_msg void OnBnClickedCombine();
	afx_msg void OnBnClickedAddCheck();
	//afx_msg void OnBnClickedCheckName();
	afx_msg void OnBnClickedReport();
	afx_msg void OnBnClickedRecharge();
	afx_msg void OnBnClickedNotifyKitchen();
	afx_msg void OnBnClickedCopyCheck();
	afx_msg void OnBnClickedSoldout();
	afx_msg void OnBnClickedNewCustomer();
	afx_msg void OnBnClickedWebRecharge();
	afx_msg void OnBnClickedWebNewCustomer();
	afx_msg void OnBnClickedViewVip();
	afx_msg void OnBnClickedLinkTable();
	afx_msg void OnBnClickedChangePsw();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
