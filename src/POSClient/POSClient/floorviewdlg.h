#pragma once
#include "Floordlg.h"
#include "CheckDlg.h"
#include "TableButton.h"

class FloorViewDlg : public FloorDlg
{
	DECLARE_DYNAMIC(FloorViewDlg)

public:
	FloorViewDlg(CWnd* pParent = NULL);
	~FloorViewDlg();
	void OnSetActive();
	virtual void ShowCurrentPage();
	void UpdateCheckData();
	void UpdateCheck(BOOL bOpen=FALSE);
// 对话框数据
	enum { IDD = IDD_FLOORVIEW };

	int m_tableId;
	int m_headId;

private:
//	vector<CheckItem> m_Items;
	CCheckDlg	m_checkDlg;
	std::vector<CButton*> m_itemButtons;
	CTableButton* m_SelectedTable;
	CRoundButton2* m_SelectedRvc;
	CTypedPtrList<CPtrList,OrderDetail *> m_orderList;
	Gdiplus::Image* m_bpTableStatus[6];

	int m_rawid;
	CStatic m_tableCtrl;
	CStatic m_checkCtrl;
	CString m_inputTbl;
	CFont mTableFont;
	CRect mTableRect;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()
	void ReFormatTableInfo(JSONVALUE& root,int type=0);
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedButtonBack();
	afx_msg void OnItemBnClicked(UINT uID);
	afx_msg void OnBnClickedOrder();
	afx_msg void OnBnClickedButtonPay();
	afx_msg void OnBnClickedRemindDish();
	afx_msg void OnBnClickedTransfer();
	afx_msg void OnBnClickedPrePrint();
	afx_msg void OnBnClickedTblStatus(UINT uID);
	afx_msg void OnBnClickedRadio(UINT uID);
	afx_msg void OnBnClickedOpenTbl();
	afx_msg void OnBnClickedDishMaked();
	afx_msg void OnBnClickedEatIn();
	afx_msg void OnBnClickedCleanTable();
	afx_msg void OnBnClickedAssembleTable();
	afx_msg void OnBnClickedViewWebcheck();
	afx_msg void OnBnClickedButtonLeft();
	afx_msg void OnBnClickedButtonRight();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	LRESULT OnMsgUpdate(WPARAM wParam, LPARAM lParam);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
