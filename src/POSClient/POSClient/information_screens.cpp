// information_screens.h : Cinformation_screens 类的实现



// Cinformation_screens 实现

// 代码生成在 2011年4月22日, 16:21

#include "stdafx.h"
#include "information_screens.h"
IMPLEMENT_DYNAMIC(Cinformation_screens, CRecordset)

Cinformation_screens::Cinformation_screens(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_info_id = 0;
	m_info_number = 0;
	m_info_name = "";
	m_line1 = "";
	m_line2 = "";
	m_line3 = "";
	m_line4 = "";
	m_line5 = "";
	m_line6 = "";
	m_line7 = "";
	m_line8 = "";
	m_line9 = "";
	m_line10 = "";
	m_nFields = 13;
	m_nDefaultType = snapshot;
}
// 此连接字符串中可能包含明文密码和/或其他重要
// 信息。请在查看完此连接字符串并找到所有与安全
// 有关的问题后移除 #error。可能需要将此密码存
// 储为其他格式或使用其他的用户身份验证。
CString Cinformation_screens::GetDefaultConnect()
{
	return _T("DATABASE=coolroid;DSN=agile_pos;");
}

CString Cinformation_screens::GetDefaultSQL()
{
	return _T("[information_screens]");
}

void Cinformation_screens::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// RFX_Text() 和 RFX_Int() 这类宏依赖的是
// 成员变量的类型，而不是数据库字段的类型。
// ODBC 尝试自动将列值转换为所请求的类型
	RFX_Long(pFX, _T("[info_id]"), m_info_id);
	RFX_Long(pFX, _T("[info_number]"), m_info_number);
	RFX_Text(pFX, _T("[info_name]"), m_info_name);
	RFX_Text(pFX, _T("[line1]"), m_line1);
	RFX_Text(pFX, _T("[line2]"), m_line2);
	RFX_Text(pFX, _T("[line3]"), m_line3);
	RFX_Text(pFX, _T("[line4]"), m_line4);
	RFX_Text(pFX, _T("[line5]"), m_line5);
	RFX_Text(pFX, _T("[line6]"), m_line6);
	RFX_Text(pFX, _T("[line7]"), m_line7);
	RFX_Text(pFX, _T("[line8]"), m_line8);
	RFX_Text(pFX, _T("[line9]"), m_line9);
	RFX_Text(pFX, _T("[line10]"), m_line10);

}
/////////////////////////////////////////////////////////////////////////////
// Cinformation_screens 诊断

#ifdef _DEBUG
void Cinformation_screens::AssertValid() const
{
	CRecordset::AssertValid();
}

void Cinformation_screens::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


