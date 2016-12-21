// information_screens.h : Cinformation_screens 的声明

#pragma once

// 代码生成在 2011年4月22日, 16:21

class Cinformation_screens : public CRecordset
{
public:
	Cinformation_screens(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(Cinformation_screens)

// 字段/参数数据

// 以下字符串类型(如果存在)反映数据库字段(ANSI 数据类型的 CStringA 和 Unicode
// 数据类型的 CStringW)的实际数据类型。
//  这是为防止 ODBC 驱动程序执行可能
// 不必要的转换。如果希望，可以将这些成员更改为
// CString 类型，ODBC 驱动程序将执行所有必要的转换。
// (注意: 必须使用 3.5 版或更高版本的 ODBC 驱动程序
// 以同时支持 Unicode 和这些转换)。

	long	m_info_id;
	long	m_info_number;
	CString	m_info_name;
	CString	m_line1;
	CString	m_line2;
	CString	m_line3;
	CString	m_line4;
	CString	m_line5;
	CString	m_line6;
	CString	m_line7;
	CString	m_line8;
	CString	m_line9;
	CString	m_line10;

// 重写
	// 向导生成的虚函数重写
	public:
	virtual CString GetDefaultConnect();	// 默认连接字符串

	virtual CString GetDefaultSQL(); 	// 记录集的默认 SQL
	virtual void DoFieldExchange(CFieldExchange* pFX);	// RFX 支持

// 实现
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

};


