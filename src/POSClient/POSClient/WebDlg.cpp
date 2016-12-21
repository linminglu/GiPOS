// WebDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "POSClient.h"
#include "WebDlg.h"


// CWebDlg 对话框

IMPLEMENT_DYNCREATE(CWebDlg, CDHtmlDialog)

CWebDlg::CWebDlg(CWnd* pParent /*=NULL*/)
	: CDHtmlDialog(CWebDlg::IDD, CWebDlg::IDH, pParent)
{
	m_dDiscount=0;
	m_dDiscName=0;
}

CWebDlg::~CWebDlg()
{
}

void CWebDlg::DoDataExchange(CDataExchange* pDX)
{
	CDHtmlDialog::DoDataExchange(pDX);
}

BOOL CWebDlg::OnInitDialog()
{
	SetHostFlags(DOCHOSTUIFLAG_FLAT_SCROLLBAR);
	EnableAutomation();
	CDHtmlDialog::OnInitDialog();
	//SetExternalDispatch(GetIDispatch(TRUE));
	/*
	{"act_pay":13.2,"ori_pay":22,"add_score":26,"ticket_type":"storedvaluecard_consume",
	"discount":0.6,"has_ticket":true,"ori_money":22,"card_id":"22222222","log":344,
	"add_money":0,"des":"折扣0.6[金卡6折(0.6)金卡双倍积分:赠送积分13.0]","amount":1305.9}
	*/
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

BEGIN_MESSAGE_MAP(CWebDlg, CDHtmlDialog)
END_MESSAGE_MAP()

BEGIN_DHTML_EVENT_MAP(CWebDlg)
	//DHTML_EVENT_ONCLICK(_T("btn_consume"), OnButtonOK)
END_DHTML_EVENT_MAP()

BEGIN_DISPATCH_MAP(CWebDlg, CDHtmlDialog)
	//DISP_FUNCTION(CWebDlg,"PaySuccess",PaySuccess,VT_EMPTY, VTS_BSTR)
END_DISPATCH_MAP()


// CWebDlg 消息处理程序

HRESULT CWebDlg::OnButtonOK(IHTMLElement* /*pElement*/)
{
	return S_FALSE;
}

void CWebDlg::PaySuccess(LPCTSTR str)
{
	try{
		LOG4CPLUS_DEBUG(log_pos,"json: "<<str);
		JSONVALUE root;
		if(root.Parse(str,JSON_FLAG_LOOSE))
		{
			m_dConsume=root[_T("card_money")].asDouble();//卡扣的钱
			m_dOripay=root[_T("ori_pay")].asDouble();//输入框的应付金额
			m_dBalance=root[_T("amount")].asDouble();//卡内余额
			if(root.isMember(_T("discount_money")))//折扣金额
			{
				m_dDiscount=root[_T("discount_money")].asDouble();
				m_dDiscName=root[_T("discount")].asDouble();//折扣比例
			}
			else
			{
				m_dConsume=root[_T("act_pay")].asDouble();
				m_dDiscount=m_dOripay-m_dConsume;
			}
			m_strCardid=root[_T("card_id")].asCString();
			long id=root[_T("log")].asInt();
			CString sqlStr;
			//消费，记录关联单号\余额
			sqlStr.Format(_T("insert into customer_consume(card_id,amount,employee_id,employee_name,order_head_id,time,extend_1,type,web_id,device_id)")
				_T(" values('%s','%f',%s,'%s',%d,now(),%0.1f,2,%d,%d)"),
				m_strCardid,-m_dConsume,theApp.m_strUserID,theApp.m_strUserName,theApp.m_nOrderHeadid,m_dBalance,id,theApp.m_nDeviceId);
			theDB.ExecuteSQL(sqlStr);
			//获取item_id
			sqlStr.Format(_T("SELECT LAST_INSERT_ID();"));
			CRecordset rs( &theDB);
			rs.Open(-1,sqlStr);
			CString strCount;
			rs.GetFieldValue((short)0,strCount);
			m_nConsume_id=_wtol(strCount);
			rs.Close();
		}
		CDHtmlDialog::OnOK();
	}catch(...)
	{
		LOG4CPLUS_ERROR(log_pos,"Catch Exception GetLastError="<<GetLastError());
	}
}

void CWebDlg::OnOK()
{
	//PaySuccess(_T("{\"act_money\":13.2,\"ori_pay\":22,\"card_id\":\"12345\",\"log\":344,\"ori_money\":22,\"amount\":1305.9}"));
	//CDHtmlDialog::OnCancel();
}
