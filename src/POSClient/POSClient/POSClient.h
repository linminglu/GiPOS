// POSClient.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif
#if !defined __POSCLIENT_H
# define __POSCLIENT_H
//�Ի���ID������������˳��һ��
enum{DLG_LOGIN,DLG_FLOOR, DLG_ORDER,DLG_PAY,DLG_SPLIT,DLG_FUNCTION,DLG_MANAGER,DLG_VIEWCHK,DLG_QUICK_ORDER};

#include "resource.h"		// ������
#include "MainSheet.h"
#include "ProgressDlg.h"
#include "MultiLanguage.h"

// CPOSClientApp:
// �йش����ʵ�֣������ POSClient.cpp
//
//ÿҳ���X����
#define MAX_ITEMS 100
//ÿ�����8�ŵ�
#define MAX_CHECKS 8
#define MAX_HEADS 5000
//#define ITEM_ID_OPENITEM 10
#define ITEM_ID_SERVICE -1
#define ITEM_ID_DISCOUNT -2
#define ITEM_ID_SENDINFO -3
#define ITEM_ID_PAYINFO  -4
#define ITEM_ID_TEXTINFO -5
#define ITEM_ID_TIPS	 -6
enum {TYPE_DINE,TYPE_TAKEOUT};
enum OPR_TYPES{OPR_UNKNOW,OPR_FREE,OPR_REPRICE,OPR_VOID,OPR_ABORTPAY,OPR_TRANS,OPR_COMBINE,OPR_REFUND,OPR_SHIFT,OPR_DAYEND};
#define MAX_GUEST_NUM 9999
#define MAX_TABLE_NUM 9999
#define MAX_ITEM_QUANTITY 9999
const TCHAR* const OPR_TYPES_NAME[] = {
	L"UNKNOW",
	L"FREE",
	L"REPRICE",
	L"VOID",
	L"ABORTPAY",
	L"TRANS",
	L"COMBINE",
	L"REFUND",
	L"SHIFT",
	L"DAYEND",
};

#define WM_MESSAGE_SEARCH	(WM_USER+101)
#define PRINT_LIST_FULL		(WM_USER+102)
#define WM_MESSAGE_ENABLE	(WM_USER+103)
#define WM_MESSAGE_UPDATE	(WM_USER+104)
#define WM_MESSAGE_LOCK		(WM_USER+105)
#define WM_MESSAGE_SHOWNOTIFY (WM_USER+106)
#define WM_MESSAGE_CLOSEOK (WM_USER+200)
struct OrderDetail
{
	int n_saved;//0-δ���浽���ݿ� 1-�ѱ��� 2-���ͳ�
	BOOL weight_required;//�Ƿ���Ҫ����
	int b_hascondiment; //0 �����ϣ�1 �����ϣ�3 ���ײ�
	long order_id;//order_detail_id
	long item_id;//��Ʒ��id
	int n_checkID;//�ֵ���
	long n_belong_item;//�����ĸ��˵�����;-���� ��ʾ�ײͣ�����ֵΪ�����ײ͵�ID
	int n_eattype;//��ʳ�������
	int n_discount_type;//��Ʒ������ʹ�õ��ۿۼ��������ǰΪ�ۿۣ���ʾ�ۿ�ID
	int n_service_type;//��Ʒ����ʹ�õķ���Ѽ���
	int n_seat_num;//���͵�λ��
	int time_accuracy;// >0 ��ʱ��Ʒ�ļ�ʱ���ȣ����ӣ�
	int tax_group;//˰����
	long n_sortindex;//���ڷ������������ֵ 
	double quantity;//��Ʒ������������
	double item_price;//����
	double total_price;//�ܼ�=����*����
	double tax_amount;//˰��
	double discount_price;//�ۿ۽��
	double sales_amount;//��Ʒ���������۶�(�۳��ۿۺ�Ľ��)
	double orignal_price;//�ļ�ǰ��ԭ��
	WCHAR unit[10];//��Ʒ��λ
	WCHAR item_name[64];//��Ʒ����
	WCHAR item_name2[32];//��Ʒ��������
	WCHAR authID[10];//�˲˵���ȨID
	WCHAR authUser[10];//�˲˵���Ȩ�û�
	WCHAR* return_reason;
	double discount_percent;//��Ϊ�����͵��ۿۻ�����ʱ>0; -1 ��ֵ�ͻ򲿷ִ���; 0 ����Ĩ��
	BOOL noDiscount;//��Ϊ�����ʱ���Ƿ񲻴���
	int round_type;//�ۿ�ʱ��Ĩ������
	int bargain_stype;//0 ������ 1 �ֶ����� 2 ��������
	BOOL b_isfree;//�Ƿ����Ͳ�Ʒ
	BOOL b_reprice;//�Ƿ��ض��۹�
	BOOL b_notprint; //�Ƿ�����������ӡ
	int family_group;//��������
	int rush_times;//�߲˴���
	OrderDetail* belongto;
	WCHAR description[100];//��Ʒ����
	~OrderDetail()
	{
		delete return_reason;
	}
};
struct PrintDeviceInfo
{
	int nDeviceType;
	int nComBaudrate;
	int nComDataBits;
	int nComStopBits;
	int nComParity;
	int nFlowControl;
	int nPaperWidth;
	BOOL bCutPaper;
	CString printerName;
	PrintDeviceInfo()
	{
		nDeviceType=-1;
	}
};

struct TableItem {
	int id;
	int raw_id;//��̨��ID
	int status;
	int rvc;
	int cur_gst;
	int seat_num;
	int ismake;//�Ƿ��������
	BOOL isWechat;
	CString name;
	CString party_table;
	CString open_time;//��̨ʱ��
	bool operator == (const TableItem&  tbl)
	{   
		return  (id == tbl.id);
	}
};
struct CheckItem
{
	long order_head_id;
	int check_number;
	int table_id;
	int check_id;
	int status;//�˵�״̬
	CString order_start_time;
	CString table_name;
	double should_amount;
	CString display;
};
struct TaxItem
{
	int id;
	CString name;
	double rate;
	double total;
};

typedef std::vector<CPosPage*> CPageList;
class SecondScreenDlg;

class CPOSClientApp : public CWinApp
{
public:
	CPOSClientApp();
	CMainSheet* m_pMain;//������

	//�㵥��Ϣ
	CString CURRENCY_SYMBOL;//���ҷ���
	CString m_strUserName;
//	CString m_strUserClass;//�û��ȼ�
	CString m_strUserID;
	CString m_strChkName;
	CString m_strTblName;//����
	CString m_strPeriod; //���
	CString m_strHostName;//��ǰ������
	CString m_strIP;
	CString m_strResId;//����ID
	CString m_strDiskId;//Ӳ�̺�
	CString m_strCloudURL;//�Ʒ�������ַ
	CString m_strVipURL;  //��Ա��������ַ
	int		m_nVipPort;
	CString m_strPhone;//�Ʒ�����ֻ���
	CString m_strVersion;
	CString m_wxSubMchid;//΢�����̻���
	string m_aliAuthToken;//֧����token
	CString m_aliStoreId;//֧��������ID
	CString m_strQfAppcode;
	CString m_strQfServerURL;
	CMap<CString, LPCTSTR, int, int> m_privilegeMap;//�û�Ȩ�ޱ�
	BOOL m_bRefund;//�˿�״̬
	BOOL m_bUseIE;
	CString m_strRefundReason;//�˿��ԭ��
	int m_nRVC;//RVC id,��ǰ��������
	CString m_strRVC;//RVC name
	CString m_strResName;
	int m_editMode;//0 ����ģʽ(�°�װ) 1-����ģʽ 2-����ģʽ
	int m_nCheckNum;//��������
	long m_nOrderHeadid;//���к�
	int m_nGuests;
	int m_nTableId;
	int m_nRawTable;
	int m_nEatType;//��ʳ�������
	int m_nDeviceId;//�豸��
	int m_isCusFloor;//��¼����ʾ�ĵ�һ��ҳ��
	int m_nLimitType;//1������������� 2���˾��������
	int m_nScaleType;//0: ��ʹ�� 1- PS1���ӳ� 2- OS2���ӳ�
	long m_nPartyId;//������ID
	double m_fLimitAmount;//������ѽ��
	double m_fMemberDiscount;//��Ա���Żݽ�� 
	CString m_strDeviceName;
	static BOOL m_bQuickService;//���ģʽ
	BOOL m_bQuickOnce;//��һ�ο�ͣ�ʹ�����������ģʽ
	BOOL m_bInputChkName;//�Ƿ�ǿ�������ƺ�
	int m_nAutoSendType;//0-���Զ��ͳ�;1-�ҵ�ʱ�Զ��ͳ�;2-�ᵥ���Զ��ͳ�
	int m_nShiftType;//0- ���ఴ����ͳ�� 1-��Ա��ͳ��
	CString m_strBeginDate;
	CString m_strBeginTime;
	CString m_strEndTime;//�ᵥʱ�䣬�����ʵĵ�����
	int m_bDirty;//�Ƿ���Ҫ�����ڴ���Ϣ: 0 �������ݿ���£��������ѽ᣻ 1 �����ݿ���� ��2 �����£��������ѽ�(��̨�Զ����)
	CTypedPtrList<CPtrList,OrderDetail *> m_orderList;//�ѵ��Ʒ�б�
	int m_nCheckStatus[MAX_CHECKS];//�˵���״̬���Ƿ��ѽᡣ
	int m_nActiveCheck;//��ǰ������ĸ��ֵ�
	CustomerDisplay m_cusDisplay;//����
	CustomerDisplay m_VCR;//��Ƶ���
	PrintDeviceInfo m_prePrinter;
	PrintDeviceInfo m_payPrinter;
	CString m_strPrintHead;
	CString m_strPrintTail;
//	BOOL m_bCanRollback;//�Ƿ��ܽ���ȡ������
//	std::map<CString,PrintTemplate*> theTemplates;
	CRecentList* m_pRecentFileList;
	vector<int> m_tipSuggests;
	double m_dTaxRate;
	BOOL m_bTaxGST;//�Ƿ�ΪGST˰�������Ҳ��˰��
	int m_nTaxRound;//˰����������ȡ��(�ձ�ʹ��)
	int m_nTaxType;// ˰������ 2-��Ʒ�Ѻ�˰
	int m_nRoundType;//�����ۿ�����
	int DECIMAL_PLACES;//С����λ��
	CString m_decPlace;
	unsigned char* enctrypkey;
	ULONG_PTR m_gdiplusToken;
	CFont m_txtFont;
	BOOL IS_SERVER;
private:
	CPageList m_pageList;
// ��д
	public:
	virtual BOOL InitInstance();
	double GetWeight();
	BOOL CheckInit();
	int GetDeviceID();
	BOOL InitPrinter();
	void ResetAutoIncrement();
	void OpenDrawer();
	static CString GetFileVersion(LPCTSTR cPath);
	void AddRecentString(CString str);
	void ClearQuickOnce();
	static void CriticalLogs(OPR_TYPES,CString detail);
	static void FormatPrintDevice(JSONVALUE& root,PrintDeviceInfo& printer);
	static BOOL PrintJson(JSONVALUE& root);
// ʵ��

	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
};
extern CPOSClientApp theApp;
extern CMultiLanguage	theLang;
extern Logger log_pos;
extern CDatabase theDB;
extern BOOL m_bTrainingMode;//�Ƿ���ѵģʽ
extern int m_bNotReg;
//extern CString m_strFont;
extern DWORD m_dTextColor;
extern DWORD DEFALUT_BACKGROUND_COLOR;
extern std::map<CString,int> macrosInt;
extern SecondScreenDlg* m_pSecond;
BOOL OpenDatabase(BOOL bRecounect=FALSE);
CString GetFiledValue(LPCTSTR strSQL);
BOOL HttpPost(LPCTSTR server,int port,LPCTSTR url,JSONVALUE& request,JSONVALUE& response);
void KillProcessByName(LPCTSTR lpProcessName);
INT_PTR POSMessageBox(LPCTSTR lpszText, UINT nType = MB_OK);
int POSMessageBox(UINT nIDPrompt,UINT nType = MB_OK);
void ComputeTotalPrice(OrderDetail* pOrder);
void ComputeTax(OrderDetail* pOrder);
CString FormatDBStr(LPCTSTR str);
CString GetMacAddress();
int ScaleX(int pt);
int ScaleY(int pt);

#endif // !defined POSCLIENT_H