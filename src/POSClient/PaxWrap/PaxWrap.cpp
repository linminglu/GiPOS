// 这是主 DLL 文件。

#include "stdafx.h"
#include <stdio.h>
#include <windows.h>
#include <vcclr.h>
#include "PaxWrap.h"

//#define MARKUP_STL 
//#include "Markup.h"

#using "POSLink.dll"
using namespace POSLink;
using namespace System;
using namespace System::Text;
using namespace System::Xml;

wchar_t g_szText[1024]; 

extern "C" _declspec(dllexport) LPCWSTR PaxPayRequest(int& result,LPCWSTR refNum,double amount)
{
	PosLink ^poslink = gcnew PosLink();
	PaymentRequest ^payRequest = gcnew PaymentRequest(); 
	CommSetting ^commSetting = gcnew CommSetting();
	wchar_t buffer[100];
	::GetPrivateProfileString(L"COMMUNICATE",L"PORT",L"",buffer,100,L".\\commsetting.ini");
	commSetting->DestPort=gcnew String(buffer);
	::GetPrivateProfileString(L"COMMUNICATE",L"IP",L"",buffer,100,L".\\commsetting.ini");
	commSetting->DestIP=gcnew String(buffer);
	::GetPrivateProfileString(L"COMMUNICATE",L"TIMEOUT",L"",buffer,100,L".\\commsetting.ini");
	commSetting->TimeOut=gcnew String(buffer);
	::GetPrivateProfileString(L"COMMUNICATE",L"CommType",L"",buffer,100,L".\\commsetting.ini");
	commSetting->CommType=gcnew String(buffer);

	poslink->CommSetting = commSetting;
	payRequest->TenderType = payRequest->ParseTenderType(gcnew String(L"CREDIT"));
	payRequest->TransType = payRequest->ParseTransType(gcnew String(L"SALE"));
	payRequest->ECRRefNum = gcnew String(refNum);
	int total=amount*100;
	payRequest->Amount = String::Format("{0}",total);
	// 	if (wcslen(refNum)!=0) {
	// 		payRequest->OrigRefNum = gcnew String(refNum);
	// 	}
	poslink->PaymentRequest = payRequest;
	ProcessTransResult ^transResult = poslink->ProcessTrans();
	PaymentResponse ^r;
	switch (transResult->Code)
	{
	case ProcessTransResultCode::OK:
		{
			r = poslink->PaymentResponse;
			StringBuilder^ strRet=gcnew StringBuilder();
			strRet->AppendFormat("#:******{0}\r\n",r->BogusAccountNum);

			XmlDocument^ doc = gcnew XmlDocument();
			String^ strXml="<root>"+r->ExtData+"</root>";
			doc->LoadXml(strXml);
			XmlNode^ root = doc->SelectSingleNode("/root");
			XmlNode^ node = root->SelectSingleNode("APPLAB");
			strRet->AppendFormat("{0}\r\n",node->InnerText);

			strRet->AppendFormat("{0}",r->Timestamp);

			node = root->SelectSingleNode("AID");
			strRet->AppendFormat("#:{0}\r\n",node->InnerText);
			swprintf(g_szText,L"%s",PtrToStringChars(strRet->ToString()));
			result=0;
		}
	case ProcessTransResultCode::TimeOut:
		result=1;
		OutputDebugString(L"Transaction timeout");
		return L"Transaction timeout";
		//case ProcessTransResultCode::ERROR:
	default:
		result=2;
		pin_ptr<const WCHAR> str=PtrToStringChars(transResult->Msg);
		OutputDebugString(str);
		return str;
	}
}