// PrintHelper.cpp : 定义 DLL 的初始化例程。
//

#include "stdafx.h"
#include "resource.h"
#include "POSClient.h"
#include <algorithm>
#include "PrintHelper.h"
#include "print_task.h"
//using namespace std;
#include <log4cplus/logger.h>
#include <log4cplus/fileappender.h>
#include <log4cplus/configurator.h>
using namespace log4cplus;


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// 唯一的一个 CPrintHelperApp 对象

extern Logger log_pos;
extern BOOL m_bTrainingMode;//是否培训模式

CString thePrintDir;
CString theDatabaseIp;
BOOL bLocalPrint=FALSE;
HANDLE   g_newNotifySemaphore;

// CPrintHelperApp 初始化
BOOL InitPrintService()
{
	HKEY hKey;
    DWORD dwtype, len = 256;
	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, _T("SOFTWARE\\COOLROID\\AgilePOS"), 0, KEY_ALL_ACCESS, &hKey) == ERROR_SUCCESS)
    {
        RegQueryValueEx(hKey, _T("PrintDir"), 0, &dwtype, (LPBYTE)thePrintDir.GetBuffer(256), &len);
		thePrintDir.ReleaseBuffer();
		RegCloseKey(hKey);
	}
	if (thePrintDir.IsEmpty())
	{
		thePrintDir=_T("D:\\print\\");
	}
	if (thePrintDir.GetAt(thePrintDir.GetLength()-1)!='\\')
	{
		thePrintDir.AppendChar('\\');
	}
	CreateDirectory(thePrintDir,NULL);
	bLocalPrint=::GetPrivateProfileInt(_T("POS"),_T("LOCAL_PRINT"),0,_T(".\\config.ini"));
	if(!bLocalPrint)
	{
		g_newNotifySemaphore =CreateSemaphore(NULL,0,1,NULL);
		AfxBeginThread(NotifyThread,NULL);
	}
	//
	dwtype = REG_SZ;
	len=256;
	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, _T("SOFTWARE\\ODBC\\ODBC.INI\\agile_pos"), 0, KEY_READ, &hKey) == ERROR_SUCCESS)
	{
		RegQueryValueEx(hKey, _T("SERVER"), 0, &dwtype, (LPBYTE)theDatabaseIp.GetBuffer(256), &len);
		theDatabaseIp.ReleaseBuffer();
		RegCloseKey(hKey);
	}
	return TRUE;
}

/************************************************************************
* 函数介绍：获取监视文件夹内未使用的唯一文件名
* 输入参数：
* 输出参数：
* 返回值  ：
************************************************************************/
CString getNextFileName(CString strPrefix)
{
	try
	{
		SYSTEMTIME   st; 
		GetLocalTime(&st);
		CString path=thePrintDir;
		path.AppendFormat(_T("%s_"),strPrefix);
		path.AppendFormat(_T("%02d%02d%d%d_"),st.wHour,st.wMinute,st.wSecond,st.wMilliseconds);
		CFileFind finder;
		BOOL bWorking=finder.FindFile(path+_T("*.pf"));
		int max_num=0;
		while(bWorking)
		{
			bWorking =finder.FindNextFile();
			CString title=finder.GetFileTitle();
			int index=title.ReverseFind('_');
			title=title.Right(title.GetLength()-index-1);
			int temp;
			temp=_wtoi(title);
			if (max_num<temp)
			{
				max_num=temp;
			}
		}
		path.AppendFormat(_T("%d.pf"),max_num+1);
		return path;
	}catch(...)
	{
		LOG4CPLUS_ERROR(log_pos,"Catch Exception GetLastError="<<GetLastError());
		return _T("");
	}
}
/************************************************************************
* 函数介绍：从数据库读取打印机信息
* 输入参数：
* 输出参数：
* 返回值  ：
************************************************************************/
void GetPrinterInfo(CRecordset& rs,JSONVALUE& printTask)
{
	CDBVariant    varVal;
	int printer_type=0;
	CString printerName;
	rs.GetFieldValue(_T("check_info_print"),varVal);
	printer_type=varVal.m_iVal;
	if (printer_type==0)
	{//串口
		rs.GetFieldValue(_T("com_port"),varVal);
		printerName.Format(_T("COM%d"),varVal.m_iVal);
		rs.GetFieldValue(_T("baud_rate"),varVal);
		printTask[_T("baud_rate")]=varVal.m_lVal;
		rs.GetFieldValue(_T("parity_type"),varVal);
		printTask[_T("parity_type")]=varVal.m_iVal;
		rs.GetFieldValue(_T("num_data_bit"),varVal);
		printTask[_T("num_data_bit")]=varVal.m_iVal;
		rs.GetFieldValue(_T("num_stop_bits"),varVal);
		printTask[_T("num_stop_bits")]=varVal.m_iVal;
// 		rs.GetFieldValue(_T("flow_control"),varVal);
// 		printTask[_T("flow_control")]=varVal.m_iVal;
	}
	else if (printer_type==1)
	{//并口
		rs.GetFieldValue(_T("com_port"),varVal);
		printerName.Format(_T("LPT%d"),varVal.m_iVal);
	}
	else
	{
		rs.GetFieldValue(_T("printer_name"),printerName);
	}
	varVal.m_iVal=0;
	rs.GetFieldValue(_T("beep"),varVal);
	printTask[_T("bp")]=varVal.m_iVal;
	varVal.m_boolVal=FALSE;
	rs.GetFieldValue(_T("print_table_number"),varVal);
	printTask[_T("cut_paper")] = varVal.m_boolVal;
	printTask[_T("printer_type")]=printer_type;
	printTask[_T("printer")]=(LPCTSTR)printerName;
	rs.GetFieldValue(_T("paper_width"),varVal);
	printTask[_T("paper_width")]=varVal.m_iVal;
}
/************************************************************************
* 函数介绍：将PrintItem格式化为Json
* 输入参数：
* 输出参数：
* 返回值  ：
************************************************************************/
void PrintItem2Json(PrintItem* pItem,JSONVALUE& retrunItem)
{
	CString str2,end;
	if (pItem->b_isvoid||pItem->quantity<0)
	{
		theLang.LoadString(IDS_VOID2,str2);
		end.AppendFormat(str2);
	}
	if (pItem->b_isfree)
	{
		theLang.LoadString(IDS_FREE,str2);
		end.AppendFormat(str2);
	}
	if (pItem->n_eattype&&pItem->n_belong_item<=0)
	{
		theLang.LoadString(IDS_TAKEOUT,str2);
		end.AppendFormat(str2);
	}
	if (pItem->n_belong_item>0)
	{//配料
		if (pItem->quantity!=1&&pItem->item_price>0)
		{
			retrunItem[_T("num")] = pItem->quantity;
		}
	}
	else if(pItem->n_belong_item<0)
	{//套餐
		if (pItem->quantity!=1)
		{
			retrunItem[_T("num")] = pItem->quantity;
		}
	}
	else
	{
		retrunItem[_T("num")] = pItem->quantity;
	}
	retrunItem[_T("idx")] = pItem->index;
	retrunItem[_T("id")] = pItem->item_id;
	retrunItem[_T("price")] = pItem->item_price;
	retrunItem[_T("total")] = pItem->total_price;
	if (pItem->n_seat>0)
	{
		retrunItem[_T("seat")] = pItem->n_seat;
	}
	CString name=pItem->item_name+end;
	retrunItem[_T("name")] = (LPCTSTR)name;
	if (!pItem->item_name2.IsEmpty())
	{
		name=pItem->item_name2+end;
		retrunItem[_T("name2")] = (LPCTSTR)name;
	}
	retrunItem[_T("unit")] = (LPCTSTR)pItem->unit;
	if(!pItem->return_reason.IsEmpty())
		retrunItem[_T("reason")] = (LPCTSTR)pItem->return_reason;
	if(!pItem->description.IsEmpty())
		retrunItem[_T("desc")] = (LPCTSTR)pItem->description;
}

#define PRINT_ERROR_OPENFAIL	1
#define PRINT_ERROR_NETFAIL		2
#define PRINT_ERROR_COVEOPEN	3
#define PRINT_ERROR_PAPEROUT	4
#define PRINT_ERROR_ERRO		5
#define PRINT_ERROR_OTHER		9

UINT NotifyThread(LPVOID pParam)
{
	USES_CONVERSION;
	while(true)
	{//通知服务器更新
		WaitForSingleObject(g_newNotifySemaphore,INFINITE);
		CString strOut;
		SOCKET   sockClient=socket(AF_INET,SOCK_STREAM,0); 
		SOCKADDR_IN   addrSrv; 
		addrSrv.sin_addr.S_un.S_addr=inet_addr(W2A(theDatabaseIp));
		addrSrv.sin_family=AF_INET; 
		addrSrv.sin_port=htons(2011); 
		if(connect(sockClient,(SOCKADDR*)&addrSrv,sizeof(SOCKADDR)))
		{
			theLang.LoadString(IDS_PRINTSERVERNOTRUN,strOut);
			::SendMessage(theApp.m_pMain->GetSafeHwnd(),WM_MESSAGE_SHOWNOTIFY,(WPARAM)(LPCTSTR)strOut,NULL);
			continue;
		}
		char* sendStr ="status";
		send(sockClient, sendStr,strlen(sendStr)+1,0);
		wchar_t recvBuf[512]={0};
		recv(sockClient,(char*)recvBuf,1024,0); 
		closesocket(sockClient);
		int strLen=wcslen(recvBuf);
		if(strLen>0)
		{//向窗口发送消息
			bool bInName=true;
			for(int i=0;i<strLen;i++)
			{
				TCHAR c=recvBuf[i];
				if(recvBuf[i]==',')
				{
					bInName=false;
					continue;
				}
				else if(recvBuf[i]==';')
				{
					strOut.AppendChar('\n');
					bInName=true;
					continue;
				}
				if(bInName)
					strOut.AppendChar(recvBuf[i]);
				else
				{
					CString str2;
					int err=_wtoi(&c);
					switch (err){
						case PRINT_ERROR_OPENFAIL:
							theLang.LoadString(str2,IDS_PRINT_ERROR_OPENFAIL);
							break;
						case PRINT_ERROR_NETFAIL:
							theLang.LoadString(str2,IDS_PRINT_ERROR_NETFAIL);
							break;
						case PRINT_ERROR_COVEOPEN:
							theLang.LoadString(str2,IDS_PRINT_ERROR_COVEOPEN);
							break;
						case PRINT_ERROR_PAPEROUT:
							theLang.LoadString(str2,IDS_PRINT_ERROR_PAPEROUT);
							break;
						case PRINT_ERROR_ERRO:
							theLang.LoadString(str2,IDS_PRINT_ERROR_ERRO);
							break;
						default:
							theLang.LoadString(str2,IDS_PRINT_ERROR_OTHER);
							break;
					}
					strOut.AppendFormat(str2);
				}
			}
			::SendMessage(theApp.m_pMain->GetSafeHwnd(),WM_MESSAGE_SHOWNOTIFY,(WPARAM)(LPCTSTR)strOut,NULL);
		}
	}
}
BOOL WritePrintTask(JSONVALUE& root,BOOL bNotify)
{
	try
	{
		int sreailid=0;
		try{
			if(root.isMember(_T("serial")))
				sreailid=root[_T("serial")].asInt();
			if (m_bTrainingMode)
			{//培训模式下
				CString str2;
				theLang.LoadString(IDS_TRAINMODE,str2);
				root[_T("head")]=(LPCTSTR)str2;
			}
			if(bLocalPrint)
			{//本地打印
				CString prefix;
				prefix.Format(_T("%d"),sreailid);
				int count=0;
				while(count<5)
				{//重试几次,以免冲突
					count++;
					CString file_name=getNextFileName(prefix);
					FILE* fp = _wfopen(file_name , L"w,ccs=UNICODE");
					if(fp!=NULL){
						std::wstring str;
						root.ToString(str);
						LPCTSTR pBuf=str.c_str();
						size_t strSize = wcslen(pBuf);
						fwrite(pBuf, sizeof(wchar_t), strSize, fp);
						fclose(fp);
						return TRUE;
					}
					else
					{//打开失败，多个进程下同一个单。
						prefix.AppendChar('-');
					}
				}
			}
			else
			{
				OpenDatabase();
				CPrint_Task rsTask(&theDB);
				rsTask.Open(CRecordset::snapshot, NULL, CRecordset::appendOnly);
				rsTask.AddNew();
				std::wstring str;
				root.ToString(str);
				rsTask.m_data.Format(_T("%s"),str.c_str());
				rsTask.Update();
				rsTask.Close();
				if(bNotify)//通知线程
					ReleaseSemaphore(g_newNotifySemaphore,1,NULL);
			}
		}
		catch (CDBException* ex)
		{
			//LOG4CPLUS_ERROR(log_pos,(LPCTSTR)ex->m_strError);
		}
		catch(...)
		{
		}
	}catch(...)
	{
		LOG4CPLUS_ERROR(log_pos,"Catch Exception GetLastError="<<GetLastError());
	}
	return FALSE;
}

struct PrintDevice
{
	int index;
	int print_device_id;//逻辑打印机id
	vector<PrintItem*> item_list;
};

bool CompareByClass(const PrintItem* item1, const PrintItem* item2)
{
	return (item1->n_class)<(item2->n_class);
}

void PrintMenu(vector<PrintItem>& menu_list, JSONVALUE& root,int nSort)
{
	if (theApp.m_bQuickService)
	{
		root[_T("kcms")]=1;
	}
	vector<PrintDevice> printDeviceList;//每个打印机的打印任务，根据菜品分配
	vector<int> lastPrintId;//缓存上一个菜的打印机，用于配料
	try
	{
		//CDatabase _theDB;
		//_theDB.OpenEx(_T("DSN=agile_pos"));
		OpenDatabase();
		CString strSQL;
		CRecordset rs(&theDB);
		for (UINT i = 0;i<menu_list.size();i++)
		{
			menu_list[i].index=i+1;
			if (menu_list[i].n_belong_item>0)
			{//配料,分配到所属菜品的打印机
				BOOL bFind=FALSE;
				for (UINT j=0;j<printDeviceList.size();j++)
				{
					if (find(lastPrintId.begin(),lastPrintId.end(),printDeviceList[j].print_device_id)
						!=lastPrintId.end())
					{//找到所属菜的打印机id
						printDeviceList[j].item_list.push_back((PrintItem *)&(menu_list[i]));
						bFind=TRUE;
					}
				}
				//配料的分类按所属菜品来
				if (i>=1)
				{
					menu_list[i].n_class=menu_list[i-1].n_class;
				}
				if (bFind)
				{//如果没有找到，当成普通菜处理；找到，则处理下一个菜
					continue;
				}
			}
			lastPrintId.clear();
			//查询所属的逻辑打印机ID
			strSQL.Format(_T("select family_group,print_device_id from menu_item,print_class_relation where print_class=print_class_id AND item_id = '%d' ORDER BY print_device_id")
				,menu_list[i].item_id);
			rs.Open( CRecordset::forwardOnly,strSQL);
			if (rs.GetRecordCount()==0)
			{
				rs.Close();
				LOG4CPLUS_WARN(log_pos,"No printer :"<<menu_list[i].item_id);
				continue;
			}
			CDBVariant varVal;
			if(nSort==1&&menu_list[i].n_class<=0)
			{
				varVal.m_iVal=0;
				rs.GetFieldValue(_T("family_group"),varVal);
				menu_list[i].n_class=varVal.m_iVal;
			}
			int index=0;
			int lastId=0;
			while(!rs.IsEOF())
			{
				varVal.m_lVal=0;
				rs.GetFieldValue(_T("print_device_id"),varVal);
				int printId = varVal.m_lVal;
				if (lastId==printId)
					index++;
				else
					index=0;
				lastId=printId;
//LOG4CPLUS_WARN(log_pos,"2. id="<<menu_list[i].item_id<<" print_class="<<menu_list[i].print_class<<" device="<<printId);
				BOOL isFind = FALSE;
				for (UINT j = 0;j<printDeviceList.size();j++)
				{
					if (printDeviceList[j].print_device_id == printId
						&&printDeviceList[j].index==index)
					{
						printDeviceList[j].item_list.push_back((PrintItem *)&menu_list[i]);
						isFind = TRUE;
						break;
					}
				}
				if (isFind == FALSE)
				{
					PrintDevice newDevice;
					newDevice.index=index;
					newDevice.print_device_id = printId;
					newDevice.item_list.push_back((PrintItem *)&menu_list[i]);
					printDeviceList.push_back(newDevice);
				}
				lastPrintId.push_back(printId);
				rs.MoveNext();
			}
			rs.Close();
		}
		//根据分配好的打印机创建打印任务
		for (UINT i=0;i<printDeviceList.size();i++)
		{
			strSQL.Format(_T("select * from print_devices where print_device_id='%d'"),
				printDeviceList[i].print_device_id);
			rs.Open( CRecordset::forwardOnly,strSQL);
			if (!rs.IsEOF())
			{
				CDBVariant    varVal;
				int printer_type=0;
				int n_beep=0;
				int baud_rate,parity_type,num_data_bit,num_stop_bits,flow_control,nPaperWidth;
				CStringW printerName,print_device_name;
				rs.GetFieldValue(_T("print_device_name"),print_device_name);

				varVal.m_iVal=0;
				rs.GetFieldValue(_T("paper_width"),varVal);
				nPaperWidth=varVal.m_iVal;
				varVal.m_iVal=0;
				rs.GetFieldValue(_T("beep"),varVal);
				n_beep=varVal.m_iVal;

				rs.GetFieldValue(_T("check_info_print"),varVal);
				printer_type=varVal.m_iVal;
				if (printer_type==0)
				{//串口
					rs.GetFieldValue(_T("com_port"),varVal);
					printerName.Format(L"COM%d",varVal.m_iVal);
					rs.GetFieldValue(_T("baud_rate"),varVal);
					baud_rate=varVal.m_iVal;
					rs.GetFieldValue(_T("parity_type"),varVal);
					parity_type=varVal.m_iVal;
					rs.GetFieldValue(_T("num_data_bit"),varVal);
					num_data_bit=varVal.m_iVal;
					rs.GetFieldValue(_T("num_stop_bits"),varVal);
					num_stop_bits=varVal.m_iVal;
					rs.GetFieldValue(_T("flow_control"),varVal);
					flow_control=varVal.m_iVal;
				}
				else if (printer_type==1)
				{//并口
					rs.GetFieldValue(_T("com_port"),varVal);
					printerName.Format(L"LPT%d",varVal.m_iVal);
				}
				else
				{
					rs.GetFieldValue(_T("printer_name"),printerName);
				}
				varVal.m_boolVal=FALSE;
				rs.GetFieldValue(_T("print_table_number"),varVal);
				BOOL bCutPaper = varVal.m_boolVal;
				rs.GetFieldValue(_T("redirection_device_id"),varVal);
				int isPrintOnebyOne = varVal.m_iVal;
				if (isPrintOnebyOne == 1)
				{//一菜一单
					if (wcscmp(TEMPLATE_SEND,root["template"].asCString())!=0)
					{//催菜和退菜
						varVal.m_iVal=0;
						rs.GetFieldValue(_T("is_print_note"),varVal);
						if (varVal.m_iVal==0)
						{//分单不打印
							rs.Close();
							continue;
						}
					}
					for(UINT j = 0;j<printDeviceList[i].item_list.size();j++)
					{
						JSONVALUE printTask=root;
						JSONVALUE arrayObj,item;

						PrintItem2Json(printDeviceList[i].item_list[j],item);
						arrayObj.Push(item);
						//如果有配料添加配料
						for (UINT k=j+1;k<printDeviceList[i].item_list.size();k++)
						{
							if(printDeviceList[i].item_list[k]->n_belong_item > 0
								||(macrosInt[_T("PRINT_COURSE_COMBINE")]==1&&printDeviceList[i].item_list[k]->n_belong_item<0))
							{
								JSONVALUE condiment;
								PrintItem2Json(printDeviceList[i].item_list[k],condiment);
								arrayObj.Push(condiment);
								j++;
							}
							else
								break;
						}
						if(printDeviceList[i].item_list[j]->n_check>1)
							printTask[_T("chk_id")]=printDeviceList[i].item_list[j]->n_check;
						printTask[_T("items")]=arrayObj;
						printTask[_T("item_total")]=printDeviceList[i].item_list.size();
						printTask[_T("idx")]=j+1;
						if(!printTask.isMember(_T("head")))
							printTask["head"]=print_device_name;
						printTask[_T("printer_type")]=printer_type;
						printTask[_T("paper_width")]=nPaperWidth;
						if (printer_type==0)
						{
							printTask[_T("baud_rate")]=baud_rate;
							printTask[_T("parity_type")]=parity_type;
							printTask[_T("num_data_bit")]=num_data_bit;
							printTask[_T("num_stop_bits")]=num_stop_bits;
							printTask[_T("flow_control")]=flow_control;
						}
						if(n_beep>0)
							printTask[_T("bp")]=n_beep;
						if(bCutPaper)
							printTask[_T("cut_paper")]=bCutPaper;
						printTask[_T("printer")]=printerName;
						WritePrintTask(printTask,FALSE);
					}
				}
				else
				{
					JSONVALUE printTask=root;
					JSONVALUE arrayObj;
					if(nSort==1)
					{//按分类排序
						sort(printDeviceList[i].item_list.begin(),printDeviceList[i].item_list.end(),CompareByClass);
					}
					for(UINT j = 0;j<printDeviceList[i].item_list.size();j++)
					{
						JSONVALUE item;
						PrintItem2Json(printDeviceList[i].item_list[j],item);
						if(nSort==1)
						{
							int k=j+1;
							if (k<printDeviceList[i].item_list.size())
							{
								if (printDeviceList[i].item_list[j]->n_class!=printDeviceList[i].item_list[k]->n_class)
								{
									item[_T("class")]=1;
								}
							}
						}
						arrayObj.Push(item);
					}
					printTask[_T("items")]=arrayObj;
					if(printDeviceList[i].item_list[0]->n_check>1)
						printTask[_T("chk_id")]=printDeviceList[i].item_list[0]->n_check;
					if(!printTask.isMember(_T("head")))
						printTask[_T("head")]=print_device_name;
					printTask[_T("printer_type")]=printer_type;
					printTask[_T("paper_width")]=nPaperWidth;
					if (printer_type==0)
					{
						printTask[_T("baud_rate")]=baud_rate;
						printTask[_T("parity_type")]=parity_type;
						printTask[_T("num_data_bit")]=num_data_bit;
						printTask[_T("num_stop_bits")]=num_stop_bits;
						printTask[_T("flow_control")]=flow_control;
					}
					if(n_beep>0)
						printTask[_T("bp")]=n_beep;
					if(bCutPaper)
						printTask[_T("cut_paper")]=bCutPaper;
					printTask[_T("printer")]=printerName;
					WritePrintTask(printTask,FALSE);
				}
			}
			else
			{
				LOG4CPLUS_ERROR(log_pos,"NOT FIND print_device_id="<<printDeviceList[i].print_device_id);
			}
			rs.Close();			
		}
		//_theDB.Close();
		if(!bLocalPrint)
			ReleaseSemaphore(g_newNotifySemaphore,1,NULL);//最后一起通知
	}
	catch (CDBException* ex)
	{
		LOG4CPLUS_ERROR(log_pos,(LPCTSTR)ex->m_strError);
	}
}
