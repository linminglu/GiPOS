// order_detail.h : COrder_Detail 的声明

#pragma once

// 代码生成在 2012-05-23 , 16:51

class COrder_Detail : public CRecordset
{
public:
	COrder_Detail(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(COrder_Detail)

// 字段/参数数据

// 以下字符串类型(如果存在)反映数据库字段(ANSI 数据类型的 CStringA 和 Unicode
// 数据类型的 CStringW)的实际数据类型。
//  这是为防止 ODBC 驱动程序执行可能
// 不必要的转换。如果希望，可以将这些成员更改为
// CString 类型，ODBC 驱动程序将执行所有必要的转换。
// (注意: 必须使用 3.5 版或更高版本的 ODBC 驱动程序
// 以同时支持 Unicode 和这些转换)。

	long	m_order_detail_id;
	long	m_order_head_id;
	long	m_check_id;
	long	m_menu_item_id;
	CString	m_menu_item_name;
	float	m_product_price;
	BOOL	m_is_discount;
	float	m_original_price;
	long	m_discount_id;
	float	m_actual_price;
	BOOL	m_is_return_item;
	long	m_order_employee_id;
	CString	m_order_employee_name;
	long	m_pos_device_id;
	CString	m_pos_name;
	CTime	m_order_time;
	CTime	m_return_time;
	CString	m_return_reason;
	CString	m_unit;
	BOOL	m_is_send;
	long	m_condiment_belong_item;
	float	m_quantity;
	long	m_eat_type;
	long	m_auth_id;
	CString	m_auth_name;
	BOOL	m_weight_entry_required;
	CString	m_description;
	long	m_n_service_type;
	long    m_notprint;
	long	m_n_seat_num;
	float   m_discount_price;
	float	m_sales_amount;
	long	m_print_class;

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


