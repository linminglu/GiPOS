// SecondScreen.cpp : 实现文件
//

#include "stdafx.h"
#include "POSClient.h"
#include "SecondScreen.h"
#include "CheckDlg.h"


// SecondScreen 对话框

IMPLEMENT_DYNAMIC(SecondScreenDlg, CDialog)

SecondScreenDlg::SecondScreenDlg(CWnd* pParent /*=NULL*/)
	: CDialog(SecondScreenDlg::IDD, pParent)
{
	m_picIndex = 0;
}

SecondScreenDlg::~SecondScreenDlg()
{
}

void SecondScreenDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(SecondScreenDlg, CDialog)
	ON_WM_TIMER()
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	ON_WM_DESTROY()
	//ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

// SecondScreen 消息处理程序

BOOL SecondScreenDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	//整个窗口大小
	m_total_width =GetPrivateProfileInt(_T("SECOND_SCREEN"),  _T("TOTAL_WIDTH"), 0,_T(".\\config.ini"));
	m_total_height=GetPrivateProfileInt(_T("SECOND_SCREEN"),  _T("TOTAL_HEIGHT"), 0,_T(".\\config.ini"));
	m_bHideDetail =GetPrivateProfileInt(_T("SECOND_SCREEN"),  _T("HIDE_DETAIL"), 0,_T(".\\config.ini"));
	int m_timeer = GetPrivateProfileInt(_T("SECOND_SCREEN"),  _T("PIC_TIMER"), 0,_T(".\\config.ini"));
	//移动窗口到第二屏幕
	MoveWindow2(m_hWnd,m_total_width,m_total_height);
	m_checkDlg.Create(IDD_CHECK,this);
	m_checkDlg.ShowWindow(SW_HIDE);
	m_checkDlg.EnableWindow(FALSE);
	m_checkDlg.MoveWindow(10,10,ScaleX(330),m_total_height-20);
	//加载图片
	ScanDiskFile(m_scan_file);
	//设置图片滚动定时器
	if (m_vStrAllFiles.size() > 0)
	{
		ShowPicture(m_vStrAllFiles[m_picIndex]);
		m_picIndex = (m_picIndex+1)%m_vStrAllFiles.size();
	}
	SetTimer(1001,m_timeer*1000,0);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
//重新加载显示所有菜品列表
BOOL SecondScreenDlg::ReshowAll(CCheckDlg& from)
{
	if(m_bHideDetail)
		return FALSE;
	m_checkDlg.ResetContent(FALSE);
	m_checkDlg.LockWindowUpdate();
	int size=from.m_ctrlDetailList.GetCount();
	for (int i=0;i<size;i++)
	{
		CString text;
		from.m_ctrlDetailList.GetText(i,text);
		m_checkDlg.m_ctrlDetailList.AddString(text);
	}
	m_checkDlg.m_subTotalList.ResetContent();
	size=from.m_subTotalList.GetCount();
	for (int i=0;i<size;i++)
	{
		CString text;
		from.m_subTotalList.GetText(i,text);
		m_checkDlg.m_subTotalList.AddString(text);
	}
	m_checkDlg.UnlockWindowUpdate();
	m_checkDlg.ShowWindow(SW_SHOW);
	return TRUE;
}
void SecondScreenDlg::HideDetail()
{
	m_checkDlg.ShowWindow(SW_HIDE);
}
//新增一行（一个菜品，加在最后）
VOID SecondScreenDlg::AddItem(CCheckDlg& from,LPCTSTR item)
{
	m_checkDlg.m_ctrlDetailList.AddString(item);
	m_checkDlg.m_subTotalList.ResetContent();
	int size=from.m_subTotalList.GetCount();
	for (int i=0;i<size;i++)
	{
		CString text;
		from.m_subTotalList.GetText(i,text);
		m_checkDlg.m_subTotalList.AddString(text);
	}
}
//显示总价
VOID SecondScreenDlg::ShowAmount(double m_fDue,double m_fDebt)
{
	if(m_bHideDetail)
		return;

}
void SecondScreenDlg::OnPaint()
{
	CPaintDC dc(this); 
	CDC MemDc;
	MemDc.CreateCompatibleDC(&dc);
	HGDIOBJ hOldBmp = MemDc.SelectObject(m_bpBackgrd);
	dc.SetStretchBltMode(HALFTONE);
	dc.StretchBlt(0,0,m_total_width,m_total_height,&MemDc,0,0,i_image_width,i_image_height,SRCCOPY);
}
//显示图片函数
void SecondScreenDlg::ShowPicture(CString path)
{
	CImage image;       //使用图片类
	image.Load(path);   //装载路径下图片信息到图片类
	if(image.IsNull())                
		return;
	i_image_width=image.GetWidth();
	i_image_height=image.GetHeight();

	DeleteObject(m_bpBackgrd);
	m_bpBackgrd=image.Detach();
	
	Invalidate();
}
//定时器
void SecondScreenDlg::OnTimer(UINT_PTR nIDEvent)
{
	if(nIDEvent==1001)
	{
		if (m_vStrAllFiles.size() > 0)
		{
			ShowPicture(m_vStrAllFiles[m_picIndex]);
			m_picIndex = (m_picIndex+1)%m_vStrAllFiles.size();
		}
	}
	CDialog::OnTimer(nIDEvent);
}
//
void SecondScreenDlg::ScanDiskFile(const CString& strPath)
{
	m_vStrAllFiles.clear();
	CFileFind find;
	CString Path = strPath;
	CString lpsz =  Path +L"\\";
	Path = Path +L"\\*.*";
	BOOL IsFind = find.FindFile(Path);
	while(IsFind )
	{
		IsFind=find.FindNextFile();
		//如果是"."则不扫描
		if(find.IsDots())
			continue;
		//是目录,继续扫描此目录
		else if(find.IsDirectory())
		{
			continue;
		}
		//文件
		else
		{
			//获得文件的路径
			CString  strFile= find.GetFileName();
			CString extend = strFile.Right(strFile.GetLength() - strFile.ReverseFind('.') - 1);//取得扩展名
			if (extend == _T("jpg") | extend == _T("png"))
			{
				m_vStrAllFiles.push_back(lpsz + strFile); 
			}
		}
	}
	find.Close();
}

BOOL SecondScreenDlg::OnEraseBkgnd(CDC* pDC)
{
	return TRUE; // CDialog::OnEraseBkgnd(pDC);
}

void SecondScreenDlg::OnDestroy()
{
	CDialog::OnDestroy();
	KillTimer(1001);
	delete this;
}
// 获得显示区宽度
short GetScreenWidth(short ScreenNo, const int m_monitorNum)
{
	if (ScreenNo < 0 || ScreenNo >= m_monitorNum) return 0;
	BOOL flag;
	DISPLAY_DEVICE dd;
	ZeroMemory(&dd, sizeof(dd));
	dd.cb = sizeof(dd);
	flag = EnumDisplayDevices(NULL, ScreenNo, &dd, 0);
	if (!flag) return 0;
	DEVMODE dm;
	ZeroMemory(&dm, sizeof(dm));
	dm.dmSize = sizeof(dm);
	flag = EnumDisplaySettings((TCHAR*)dd.DeviceName,ENUM_CURRENT_SETTINGS, &dm);
	if (!flag) return 0;
	return (short) dm.dmPelsWidth;
}

// 获得显示区宽度
short GetScreenHeight(short ScreenNo, const int m_monitorNum)
{
	if (ScreenNo < 0 || ScreenNo >= m_monitorNum) return 0;
	BOOL flag;
	DISPLAY_DEVICE dd;
	ZeroMemory(&dd, sizeof(dd));
	dd.cb = sizeof(dd);
	flag = EnumDisplayDevices(NULL, ScreenNo, &dd, 0);
	if (!flag) return 0;
	DEVMODE dm;
	ZeroMemory(&dm, sizeof(dm));
	dm.dmSize = sizeof(dm);
	flag = EnumDisplaySettings((TCHAR*)dd.DeviceName,ENUM_CURRENT_SETTINGS, &dm);
	if (!flag) return 0;
	return (short) dm.dmPelsHeight;
}

// 獲得顯示區Y坐標
short GetScreenTop(short ScreenNo, const int m_monitorNum)
{
	if (ScreenNo < 0 || ScreenNo >= m_monitorNum) return -1;
	BOOL flag;
	DISPLAY_DEVICE dd;
	ZeroMemory(&dd, sizeof(dd));
	dd.cb = sizeof(dd);
	flag = EnumDisplayDevices(NULL, ScreenNo, &dd, 0);
	if (!flag) return -1;
	DEVMODE dm;
	ZeroMemory(&dm, sizeof(dm));
	dm.dmSize = sizeof(dm);
	flag = EnumDisplaySettings((TCHAR*)dd.DeviceName,ENUM_CURRENT_SETTINGS, &dm);
	if (!flag) return -1;
	return (short) dm.dmPosition.y ;
}

// 獲得顯示區X坐標
short GetScreenLeft(short ScreenNo, const int m_monitorNum)
{
	if (ScreenNo < 0 || ScreenNo >= m_monitorNum) return -1;
	BOOL flag;
	DISPLAY_DEVICE dd;
	ZeroMemory(&dd, sizeof(dd));
	dd.cb = sizeof(dd);
	flag = EnumDisplayDevices(NULL, ScreenNo, &dd, 0);
	if (!flag) return -1;
	DEVMODE dm;
	ZeroMemory(&dm, sizeof(dm));
	dm.dmSize = sizeof(dm);
	flag = EnumDisplaySettings((TCHAR*)dd.DeviceName,ENUM_CURRENT_SETTINGS, &dm);
	if (!flag) return -1;
	return (short) dm.dmPosition.x ;
}
// 獲得主顯示區
short GetPrimaryScreen(const int m_monitorNum)
{
	// TODO: Add your property handler here
	if (m_monitorNum <= 1) return 0;
	// if the Screen Top = 0 and Left = 0, then, it's the Primary Screen
	short i;
	for (i=0; i< m_monitorNum; i++)
	{
		if (GetScreenTop(i, m_monitorNum)==0 && GetScreenLeft(i, m_monitorNum)==0) return i;
	}
	return 0;
}
//移动窗口到第二显示器
//m_hWnd窗口句柄 width:窗口大小 height：窗口高 其中一个为0则全屏显示
void SecondScreenDlg::MoveWindow2(HWND m_hWnd,int width,int height)
{
	int cx, cy;
	RECT hMWork; 
	// 新窗口原来位置,获得的是对于整个多屏来说的位置
	::GetWindowRect(m_hWnd,&hMWork);
	int m_monitorNum = GetSystemMetrics(SM_CMONITORS); // 屏幕数目

	vector<int> heights;
	vector<int> widths;
	int primNum = GetPrimaryScreen(m_monitorNum); //主屏幕序号
	int secondNum = 0;
	for (int i = 0; i < m_monitorNum; ++i)
	{
		if (i != primNum)
		{
			secondNum = i;
		}
		widths.push_back(GetScreenWidth(i, m_monitorNum));
		heights.push_back(GetScreenHeight(i, m_monitorNum));
	}

	CString strMsg;
	HDC dc = ::GetDC(NULL);
	// 获得主屏的长宽
	cx = GetDeviceCaps(dc, HORZRES) + GetSystemMetrics(SM_CXBORDER);
	cy = GetDeviceCaps(dc, VERTRES) + GetSystemMetrics(SM_CYBORDER);

	// 获得虚拟屏幕的长宽
	int allX = GetSystemMetrics(SM_CXVIRTUALSCREEN);
	int allY = GetSystemMetrics(SM_CYVIRTUALSCREEN);

	//窗口大小
	if (width ==0 ||height==0)
	{
		width = widths.at(secondNum);
		height = heights.at(secondNum);
		m_total_width = width;
		m_total_height = height;
	}

	// 如果只有一个主屏幕
	if (m_monitorNum == 1)
	{
		::MoveWindow(m_hWnd, 0, 0, width, height, 1);
	}
	else
	{
		::MoveWindow(m_hWnd, cx, 0, width, height, 1);
	}
	::ReleaseDC(0,dc);
}

HBRUSH SecondScreenDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	int ctlId=pWnd->GetDlgCtrlID();
	if ( ctlId== IDC_STATIC_AMOUNT)
	{
		pDC->SetTextColor(RGB(250,0,0));
		//pDC->SetBkMode(TRANSPARENT);
		//return (HBRUSH)::GetStockObject(NULL_BRUSH); //返回此画刷可以使静态文本透明
	}
	return hbr;
}
