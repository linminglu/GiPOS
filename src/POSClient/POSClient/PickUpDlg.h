#pragma once
#include <vector>
using namespace std;

// PickUpDlg 对话框
class PickUpDlg : public CDialog
{
	DECLARE_DYNAMIC(PickUpDlg)

public:
	PickUpDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~PickUpDlg();
	void GetOpenChecks(CString strSQL);
	void GetParties(CString strSQL);
	void ShowCurrentPage();
// 对话框数据
	enum { IDD = IDD_PICKUP };
	CStatic m_user;
	CStatic m_time;
	CStatic m_hint;
	vector<CheckItem> m_Items;
	CPButtonList m_itemButtons;
	int ITEM_COLUMNSIZE;
	int ITEM_LINESIZE;
	int m_x;
	int m_y;
	int m_nCurrentPage;
	int m_nPageCount;
	int m_nIndex;//选择的index
	int m_nFilterTable;//过滤不显示的table
	int m_nType;//0 选择账单；1 选择宴会；2 查看已结单
	CString m_strSQL;
	CString m_strHint;
	CWnd* pParentWnd;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	CreatButton m_btnCtrl;
	HBITMAP m_bpBackgrd;
	Gdiplus::Image* m_bpCheckItem[2];
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedButtonCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnItemBnClicked(UINT uID);
	afx_msg void OnBnClickedButtonUp();
	afx_msg void OnBnClickedButtonDown();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
