// ClockDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "POSClient.h"
#include "ClockDlg.h"


// ClockDlg 对话框

IMPLEMENT_DYNAMIC(ClockDlg, CDialog)

ClockDlg::ClockDlg(CWnd* pParent /*=NULL*/)
	: CDialog(ClockDlg::IDD, pParent)
{

}

ClockDlg::~ClockDlg()
{
	::DeleteObject(m_bpBackgrd);
}

void ClockDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CLOCKIN, m_btClockin);
	DDX_Control(pDX, IDC_CLOCKOUT, m_btClockout);
	DDX_Control(pDX, IDCANCEL, m_btCancel);
	DDX_Control(pDX, IDC_EDIT1, m_edit);
	DDX_Control(pDX, IDC_STATIC_TIME, m_timeCtrl);
}


BEGIN_MESSAGE_MAP(ClockDlg, CDialog)
	ON_BN_CLICKED(IDC_CLOCKIN, &ClockDlg::OnBnClickedClockin)
	ON_BN_CLICKED(IDC_CLOCKOUT, &ClockDlg::OnBnClickedClockout)
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
	//ON_WM_TIMER()
END_MESSAGE_MAP()


// ClockDlg 消息处理程序

BOOL ClockDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	CImage cimg;
	if(cimg.Load(_T("Picture\\tablestatus.png"))==S_OK)
	{
		m_x=cimg.GetWidth();
		m_y=cimg.GetHeight();
		m_bpBackgrd=cimg.Detach();
	}
	int x=122,y=58;
	m_btCancel.SetImage(_T("Picture\\bt_cancel.png"));
	m_btCancel.SetTextColor(DEFALUT_TXT_COLOR);
	m_btClockin.SetTextColor(DEFALUT_TXT_COLOR);
	m_btClockout.SetTextColor(DEFALUT_TXT_COLOR);
	CString str2;
	theLang.LoadString(str2,IDS_CANCEL);
	m_btCancel.SetWindowText(str2);
	try{
		CString strSQL;
		CRecordset rs(&theDB);
		//查询当天的
		strSQL.Format(_T("SELECT * FROM history_time_clock WHERE employee_id=%s AND ISNULL(clock_out_time) AND HOUR(TIMEDIFF(now(),clock_in_time))<15")
			,m_strUserID);
		rs.Open(CRecordset::forwardOnly,strSQL);
		if (!rs.IsEOF())
		{//clock out
			CDBVariant variant;
			rs.GetFieldValue(_T("time_clock_id"),variant);
			m_clockid=variant.m_lVal;
			m_btClockin.ShowWindow(SW_HIDE);
			m_btClockout.SetImage(_T("Picture\\146X70\\1.png"));
			theLang.LoadString(str2,IDS_CLOCKOUT);
			m_btClockout.SetWindowText(str2);
		}else
		{//clock in
			m_btClockout.ShowWindow(SW_HIDE);
			m_btClockin.SetImage(_T("Picture\\146X70\\1.png"));
			theLang.LoadString(str2,IDS_CLOCKIN);
			m_btClockin.SetWindowText(str2);
		}
		rs.Close();
		CString strResult,str2;
		strResult=_T("\t\t")+m_strUserName;
		theLang.LoadString(str2,IDS_CLOCKIN);
		strResult+=_T("\r\n")+str2;
		theLang.LoadString(str2,IDS_CLOCKOUT);
		strResult+=_T("\t\t     ")+str2;
		theLang.LoadString(str2,IDS_TIMESPAN);
		strResult+=_T("\t")+str2;
		strResult+=_T("\r\n---------------------------------------------------");
		strSQL.Format(_T("select clock_in_time,TIME(clock_out_time),DATE_FORMAT(duration,'%%H:%%i') from history_time_clock where employee_id=%s AND  hour(TIMEDIFF(now(),clock_in_time))<=24")
			,m_strUserID);
		rs.Open(CRecordset::forwardOnly,strSQL);
		while (!rs.IsEOF())
		{
			CString strVal;
			rs.GetFieldValue((short)0,strVal);
			strResult.AppendFormat(_T("\r\n%s"),strVal);
			rs.GetFieldValue((short)1,strVal);
			strResult.AppendFormat(_T("    %s"),strVal);
			rs.GetFieldValue((short)2,strVal);
			strResult.AppendFormat(_T("\t%s"),strVal);
			rs.MoveNext();
		}
		rs.Close();
		m_edit.SetWindowText(strResult);
	}
	catch(...)
	{
	}
// 	CTime time=CTime::GetCurrentTime();
// 	CString strTime=time.Format(_T("%Y-%m-%d %H:%M"));
// 	m_timeCtrl.SetWindowText(strTime);
// 	SetTimer(1000,10000,NULL);//每隔5秒刷新时间显示
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void ClockDlg::OnBnClickedClockin()
{
	CString strSQL;
	strSQL.Format(_T("INSERT INTO history_time_clock(employee_id,clock_in_time) VALUES(\'%s\',now());")
		,m_strUserID);
	theDB.ExecuteSQL(strSQL);
	CDialog::OnOK();
}

void ClockDlg::OnBnClickedClockout()
{
	CString strSQL;
	strSQL.Format(_T("UPDATE history_time_clock SET clock_out_time=now(),duration=TIMEDIFF(clock_out_time,clock_in_time) WHERE time_clock_id=%d"),m_clockid);
	theDB.ExecuteSQL(strSQL);
	CDialog::OnOK();
}
BOOL ClockDlg::OnEraseBkgnd(CDC* pDC)
{
	if (m_bpBackgrd==NULL)
	{
		return FALSE;
	}
	CRect rect;
	GetClientRect(&rect);
	CDC MemDc;
	MemDc.CreateCompatibleDC(pDC);
	HGDIOBJ hOldBmp = MemDc.SelectObject(m_bpBackgrd);
	pDC->SetStretchBltMode(HALFTONE);
	pDC->StretchBlt(0,0,rect.Width(),rect.Height(),&MemDc,0,0,m_x,m_y,SRCCOPY);
	return TRUE;
}
HBRUSH ClockDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	if(pWnd->GetDlgCtrlID()==IDC_STATIC_TIME)
	{
		pDC->SetTextColor(m_dTextColor);
		pDC->SetBkMode(TRANSPARENT);
		return (HBRUSH)::GetStockObject(NULL_BRUSH);
	}
	return   hbr; 
	
}
void ClockDlg::OnTimer(UINT_PTR nIDEvent)
{
// 	if (nIDEvent==1000)
// 	{
// 		if(m_timeCtrl.m_hWnd)
// 		{
// 			CTime time=CTime::GetCurrentTime();
// 			CString strTime=time.Format(_T("%Y-%m-%d %H:%M"));
// 			m_timeCtrl.SetWindowText(strTime);
// 			Invalidate();
// 		}
// 	}
	CDialog::OnTimer(nIDEvent);
}
