// RemindDishDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "POSClient.h"
#include "RemindDishDlg.h"


// RemindDishDlg 对话框

IMPLEMENT_DYNAMIC(RemindDishDlg, CDialog)

RemindDishDlg::RemindDishDlg(CWnd* pParent /*=NULL*/)
	: CDialog(RemindDishDlg::IDD, pParent)
{
	pCheckDlg=NULL;
}

RemindDishDlg::~RemindDishDlg()
{
	delete hbmp;
	delete hbmp1;
}

void RemindDishDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON2, m_btWaitAll);
	DDX_Control(pDX, IDC_BUTTON1, m_btMakeAll);
	DDX_Control(pDX, IDC_BUTTON4, m_btRemindAll);
	DDX_Control(pDX, IDC_BUTTON3, m_btRemindSelect);
	DDX_Control(pDX, IDCANCEL, m_btExit);
}


BEGIN_MESSAGE_MAP(RemindDishDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &RemindDishDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &RemindDishDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &RemindDishDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &RemindDishDlg::OnBnClickedButton4)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// RemindDishDlg 消息处理程序
 /************************************************************************
 * 函数介绍：整桌催菜、起菜
 * 输入参数：
 * 输出参数：
 * 返回值  ：
 ************************************************************************/
 void RemindDishDlg::OnBnClickedButton1()
{
	BOOL bFind=FALSE;
	if (pCheckDlg)
	{
		CListBoxEx* ptrDetailList=&pCheckDlg->m_ctrlDetailList;
		CString str2,str_wait;
		CString strSQL;
		strSQL.Format(_T("UPDATE order_detail SET rush=rush+1 WHERE order_head_id=%d AND is_send=1"),theApp.m_nOrderHeadid);
		theDB.ExecuteSQL(strSQL);
		theLang.LoadString(str_wait,IDS_WAITMK);
		for(int  i=0;i<ptrDetailList->GetCount();i++)
		{
			OrderDetail* item=(OrderDetail*)ptrDetailList->GetItemDataPtr(i);
			if (item->item_id<=0||item->n_saved!=2)
				continue;//未送厨的不能催菜
			item->rush_times++;
			if(wcsstr(item->description,str_wait))
			{
				bFind=TRUE;
				CString str=item->description;
				int index = str.Find(str_wait);
				str.Delete(index,str_wait.GetLength());
				theLang.LoadString(str2,IDS_MAKENOW);
				str.Append(str2);
				wcsncpy_s(item->description,str,99);
				if(item->n_saved!=0)
				{
					strSQL.Format(_T("UPDATE order_detail SET description=\'%s\' WHERE order_detail_id=%d;")
						,item->description,item->order_id);
					theDB.ExecuteSQL(strSQL);
				}
			}
			pCheckDlg->UpdateItemString(i,FALSE);
		}
	}
	if(bFind==FALSE)
		GetPrinters(1);//催菜
	else
		GetPrinters(2);//叫起
	CDialog::OnCancel();
}
/************************************************************************
* 函数介绍：整桌等叫
* 输入参数：
* 输出参数：
* 返回值  ：
************************************************************************/
void RemindDishDlg::OnBnClickedButton2()
{
	//存储
	if (pCheckDlg)
	{
		CListBoxEx* ptrDetailList=&pCheckDlg->m_ctrlDetailList;
		CString str2;
		theLang.LoadString(str2,IDS_WAITMK);
		for(int  i=0;i<ptrDetailList->GetCount();i++)
		{
			OrderDetail* item=(OrderDetail*)ptrDetailList->GetItemDataPtr(i);
			if (item->item_id<=0||item->n_saved==2)
				continue;
			if(wcsstr(item->description,str2)==NULL)
			{//没有找到
				CString str=item->description;
				str.Append(str2);
				wcsncpy_s(item->description,str,99);
				if(item->n_saved!=0)
				{
					CString strSQL;
					strSQL.Format(_T("UPDATE order_detail SET description=\'%s\' WHERE order_detail_id=%d;")
						,item->description,item->order_id);
					theDB.ExecuteSQL(strSQL);
				}
			}
			pCheckDlg->UpdateItemString(i,FALSE);
		}
	}
	//GetPrinters(0);//等叫
	CDialog::OnCancel();
}
void RemindDishDlg::GetPrinters(int type)
{
	CPOSClientApp* pApp=(CPOSClientApp*)AfxGetApp();
	try
	{
		CRecordset rs( &theDB );
		CString strSql;
		strSql.Format(_T("SELECT * from print_devices where print_device_id in( SELECT DISTINCT(print_device_id) ")
			_T("FROM print_class_relation where print_class_id in (SELECT DISTINCT(menu_item.print_class) ")
			_T("FROM order_detail,menu_item where order_detail.menu_item_id=menu_item.item_id ")
			_T("and order_head_id = %d and is_return_item=0)) AND is_print_note=1 group by check_info_print,com_port,printer_name;")
			,pApp->m_nOrderHeadid);

		rs.Open( CRecordset::snapshot,strSql);
		while (!rs.IsEOF())
		{
			JSONVALUE printTask;
			GetPrinterInfo(rs,printTask);
			printTask[_T("template")]=TEMPLATE_MESSAGE;
			CTime time=CTime::GetCurrentTime();
			printTask[_T("tbl_name")]=theApp.m_strTblName;
			printTask[_T("chk_num")]=theApp.m_nCheckNum;
			printTask[_T("gst_num")]=theApp.m_nGuests;
			printTask[_T("emp_name")]=theApp.m_strUserName;
			printTask[_T("time")]=time.Format("%Y-%m-%d %H:%M");
			printTask[_T("serial")]=theApp.m_nOrderHeadid;
			CString str1,str2;
			if (type==0)
			{
				theLang.LoadString(str2,IDS_MESSAGEHEAD);
				printTask[_T("head")]=str2;
				theLang.LoadString(str2,IDS_WAITTHINT);
				str1.Format(str2,pApp->m_strTblName);
				printTask[_T("message")]=str1;
			}
			else if (type==1)
			{
				theLang.LoadString(str2,IDS_REMINDHEAD);
				printTask[_T("head")]=str2;
				theLang.LoadString(str2,IDS_REQUESTMAKE);
				str1.Format(str2,pApp->m_strTblName);
				printTask[_T("message")]=str1;
			}
			else if (type==2)
			{
				theLang.LoadString(str2,IDS_MAKEHEAD);
				printTask[_T("head")]=str2;
				theLang.LoadString(str2,IDS_MAKETBL);
				str1.Format(str2,pApp->m_strTblName);
				printTask[_T("message")]=str1;
			}
			WritePrintTask(printTask,TRUE);
			rs.MoveNext();
		}
		rs.Close();
	}
	catch (CDBException* ex)
	{
		LOG4CPLUS_ERROR(log_pos,(LPCTSTR)ex->m_strError);
	}
}
void RemindDishDlg::OnBnClickedButton3()
{
	CDialog::OnOK();
}

BOOL RemindDishDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	hbmp=Gdiplus::Image::FromFile(_T("Picture\\bt_remind.png"));
	hbmp1=Gdiplus::Image::FromFile(_T("Picture\\bt_remind_.png"));
	m_btWaitAll.SetImages(hbmp,hbmp1,false);
	m_btMakeAll.SetImages(hbmp,hbmp1,false);
	m_btRemindAll.SetImages(hbmp,hbmp1,false);
	m_btRemindSelect.SetImages(hbmp,hbmp1,false);
	m_btExit.SetImage(_T("Picture\\bt_exit2.png"));

	if (!theLang.m_bDefaultLang)
	{
		CWnd* pCtrl=GetDlgItem(IDCANCEL);
		theLang.TranslateDlgItem(pCtrl,IDS_EXIT);
		pCtrl=GetDlgItem(IDC_BUTTON1);
		theLang.TranslateDlgItem(pCtrl,IDS_MAKECHK);
		pCtrl=GetDlgItem(IDC_BUTTON2);
		theLang.TranslateDlgItem(pCtrl,IDS_WAITCHK);
		pCtrl=GetDlgItem(IDC_BUTTON3);
		theLang.TranslateDlgItem(pCtrl,IDS_REMINDSEL);
		pCtrl=GetDlgItem(IDC_BUTTON4);
		theLang.TranslateDlgItem(pCtrl,IDS_REMINDCHK);
		CString str2;
		theLang.LoadString(str2,IDS_REMINDISHT);
		SetWindowText(str2);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void RemindDishDlg::OnBnClickedButton4()
{
	OnBnClickedButton1();
}

void RemindDishDlg::OnPaint()
{
	CRect   rect;
	CPaintDC   dc(this);
	GetClientRect(rect);
	dc.FillSolidRect(rect,DEFALUT_BACKGROUND_COLOR);
	CDialog::OnPaint();
}
