#include "StdAfx.h"
#include "POSClient.h"
#include "SoftwareKey2.h"
#include <openssl/md5.h>
#pragma comment(lib,"libeay32.lib")

CSoftwareKey2::CSoftwareKey2(void)
{
}

CSoftwareKey2::~CSoftwareKey2(void)
{
}
/************************************************************************
* 函数介绍：验证产品密钥是否正确
* 输入参数：key_id		-要检查的模块
*			 1-前台 2-报表 3-会员 4-库存
* 输出参数：strExpire	- 如果是正确的密钥，传出到期时间
* 返回值  ：1  - 成功  0  -试用
-1 - 不合法的密钥
-2 - 密钥过期
-3 - userid不匹配
-4 - 未找到KEY
-5 - 未开放对应的功能
************************************************************************/
int CSoftwareKey2::VerifySoftwareKey(int key_id,CString& strExpire)
{
	try{
		//读取key
		int module=(key_id+1)*2+1;//module 5-前台 7-报表 9-会员 11-库存
		CString strSQL;
		strSQL.Format(_T("SELECT * FROM macros_key where key_id=%d;"),key_id);
		CRecordset rs(&theDB);
		if(!rs.Open(CRecordset::forwardOnly,strSQL))
			return -4;
		CTime timeNow=CTime::GetCurrentTime();
		CStringA strKey;
		if(!rs.IsEOF())
		{
			rs.GetFieldValue(_T("key_str"),strKey);
		}
		rs.Close();
		if (strKey.IsEmpty())
		{//没有KEY，检查试用是否到期
			strSQL.Format(_T("SELECT AES_DECRYPT(install_date,(select cr_res_id from webreport_setting)) FROM macros_key where key_id=%d"),key_id);
			if(!rs.Open(CRecordset::forwardOnly,strSQL))
				return -4;
			if (rs.IsEOF())
				return -4;
			rs.GetFieldValue((short)0,strKey);
			if (strKey.IsEmpty())
			{//解密失败
				return -4;
			}
			int   nYear=2000,nMonth=1,nDate=1;
			sscanf_s(strKey,"%d-%d-%d",&nYear,&nMonth,&nDate);
			CTime installTime(nYear,nMonth,nDate,0,0,0);
			CTimeSpan span=timeNow-installTime;
			if(span.GetDays()<0||span.GetDays()>60)
			{//过期
				return -2;
			}
			return 0;
		}
		else
		{//验证KEY
			if (strKey.GetLength()!=64)
				return -1;
			int num=strKey.GetAt(3)-'0';
			if (num<0||num>9)
				return -1;
			CStringA strmd5,inputstr;
			MD5_CTX hash_ctx;
			unsigned char hash_ret[16];

			inputstr ="coolroid"+strKey.Left(32);
			if (num%2==1)
			{//奇数，验证餐厅ID
				strSQL.Format(_T("SELECT cr_res_id FROM webreport_setting"));
				rs.Open(CRecordset::forwardOnly,strSQL);
				if (rs.IsEOF())
					return -4;
				rs.GetFieldValue(_T("cr_res_id"),strmd5);
				inputstr.Append(strmd5);
			}
			MD5_Init(&hash_ctx);
			MD5_Update(&hash_ctx, (LPCSTR)inputstr, inputstr.GetLength());
			MD5_Final(hash_ret, &hash_ctx);
			strmd5.Empty();
			for( int i=0; i<16; i++ ){
				strmd5.AppendFormat("%02X",hash_ret[i]);
			}
			if(strmd5.Compare(strKey.Right(32))!=0)
				return -1;
			//是否开放功能
			num=strKey.GetAt(module)-'0';
			if (num<0||num>9||num%2==0)
				return -5;
			//检查时间是否到期
			int diff=atoi(strKey.Mid(20,4));
			num=atoi(strKey.Mid(24,4));
			num=(num+diff)%10000;
			strExpire.Format(_T("%04d"),num);//year
			num=atoi(strKey.Mid(28,4));
			num=(num+diff)%10000;
			strExpire.AppendFormat(_T("%04d"),num);
			CString now=timeNow.Format(_T("%Y%m%d"));
			if(now>strExpire)
				return -2;
		}
		return 1;
	}catch(CDBException* e)
	{
		LOG4CPLUS_ERROR(log_pos,(LPCTSTR)e->m_strError);
		AfxMessageBox(e->m_strError,MB_ICONEXCLAMATION);
		e->Delete();
	}
	catch(...)
	{
		LOG4CPLUS_ERROR(log_pos,"Catch Exception GetLastError="<<GetLastError());
	}
	return -4;
}