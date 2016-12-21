#pragma once
#include "afxcmn.h"
//#include "POSClient.h"
#include "afxwin.h"
#include "CheckDlg.h"
//


// CMySecondScreen 对话框

class SecondScreenDlg : public CDialog
{
	DECLARE_DYNAMIC(SecondScreenDlg)

public:
	SecondScreenDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~SecondScreenDlg();

	// 对话框数据
	enum { IDD = IDD_SNDSCREEN };
	int m_picIndex;//指定当前显示的图片
	std::vector<CString> m_vStrAllFiles;//保存指定文件夹下所有的图片
	CString m_scan_file;
	int m_total_width ;//整个对话框的大小
	int m_total_height;
	BOOL m_bHideDetail;
	HBITMAP m_bpBackgrd;
	int i_image_width;
	int i_image_height;
	CCheckDlg m_checkDlg;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	BOOL ReshowAll(CCheckDlg& from);
	VOID AddItem(CCheckDlg& from,LPCTSTR item);
	void ScanDiskFile(const CString& strPath);
	void ShowPicture(CString path);
	VOID ShowAmount(double m_fDue,double m_fDebt);
	void MoveWindow2(HWND m_hWnd,int width,int height);
	void HideDetail();

public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnDestroy();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
