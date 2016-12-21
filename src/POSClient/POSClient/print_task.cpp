// print_task.h : Cprint_task 类的实现



// Cprint_task 实现

// 代码生成在 2015年11月11日, 16:22

#include "stdafx.h"
#include "print_task.h"
IMPLEMENT_DYNAMIC(CPrint_Task, CRecordset)

CPrint_Task::CPrint_Task(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_id = 0;
	m_data = L"";
	m_time;
	m_nFields = 3;
	m_nDefaultType = dynaset;
}
// 此连接字符串中可能包含明文密码和/或其他重要
// 信息。请在查看完此连接字符串并找到所有与安全
// 有关的问题后移除 #error。可能需要将此密码存
// 储为其他格式或使用其他的用户身份验证。
CString CPrint_Task::GetDefaultConnect()
{
	return _T("DSN=agile_pos");
}

CString CPrint_Task::GetDefaultSQL()
{
	return _T("[print_task]");
}

void CPrint_Task::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// RFX_Text() 和 RFX_Int() 这类宏依赖的是
// 成员变量的类型，而不是数据库字段的类型。
// ODBC 尝试自动将列值转换为所请求的类型
	RFX_Long(pFX, _T("[id]"), m_id);
	RFX_Text(pFX, _T("[data]"), m_data,21840);
	RFX_Date(pFX, _T("[time]"), m_time);

}
/////////////////////////////////////////////////////////////////////////////
// Cprint_task 诊断

#ifdef _DEBUG
void CPrint_Task::AssertValid() const
{
	CRecordset::AssertValid();
}

void CPrint_Task::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


