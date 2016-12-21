// order_detail.h : COrder_Detail 类的实现



// COrder_Detail 实现

// 代码生成在 2012-05-23 , 16:51

#include "stdafx.h"
#include "order_detail.h"
IMPLEMENT_DYNAMIC(COrder_Detail, CRecordset)

COrder_Detail::COrder_Detail(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_order_detail_id = 0;
	m_order_head_id = 0;
	m_check_id = 0;
	m_menu_item_id = 0;
	m_menu_item_name = "";
	m_product_price = 0.0;
	m_is_discount = FALSE;
	m_original_price = 0.0;
	m_discount_id = 0;
	m_actual_price = 0.0;
	m_is_return_item = FALSE;
	m_order_employee_id = 0;
	m_order_employee_name = "";
	m_pos_device_id = 0;
	m_pos_name = "";
	m_order_time;
	m_return_time;
	m_return_reason = "";
	m_unit = "";
	m_is_send = FALSE;
	m_condiment_belong_item = 0;
	m_quantity = 0.0;
	m_eat_type = 0;
	m_auth_id = 0;
	m_auth_name = "";
	m_weight_entry_required = FALSE;
	m_description = "";
	m_n_service_type = 0;
	m_notprint=0;
	m_n_seat_num=0;
	m_discount_price=0;
	m_sales_amount=0;
	m_print_class=0;
	m_nFields = 33;
	m_nDefaultType = snapshot;
}
// 此连接字符串中可能包含明文密码和/或其他重要
// 信息。请在查看完此连接字符串并找到所有与安全
// 有关的问题后移除 #error。可能需要将此密码存
// 储为其他格式或使用其他的用户身份验证。
CString COrder_Detail::GetDefaultConnect()
{
	return _T("DSN=agile_pos");
}

CString COrder_Detail::GetDefaultSQL()
{
	return _T("[order_detail]");
}

void COrder_Detail::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// RFX_Text() 和 RFX_Int() 这类宏依赖的是
// 成员变量的类型，而不是数据库字段的类型。
// ODBC 尝试自动将列值转换为所请求的类型
	RFX_Long(pFX, _T("[order_detail_id]"), m_order_detail_id);
	RFX_Long(pFX, _T("[order_head_id]"), m_order_head_id);
	RFX_Long(pFX, _T("[check_id]"), m_check_id);
	RFX_Long(pFX, _T("[menu_item_id]"), m_menu_item_id);
	RFX_Text(pFX, _T("[menu_item_name]"), m_menu_item_name);
	RFX_Single(pFX, _T("[product_price]"), m_product_price);
	RFX_Bool(pFX, _T("[is_discount]"), m_is_discount);
	RFX_Single(pFX, _T("[original_price]"), m_original_price);
	RFX_Long(pFX, _T("[discount_id]"), m_discount_id);
	RFX_Single(pFX, _T("[actual_price]"), m_actual_price);
	RFX_Bool(pFX, _T("[is_return_item]"), m_is_return_item);
	RFX_Long(pFX, _T("[order_employee_id]"), m_order_employee_id);
	RFX_Text(pFX, _T("[order_employee_name]"), m_order_employee_name);
	RFX_Long(pFX, _T("[pos_device_id]"), m_pos_device_id);
	RFX_Text(pFX, _T("[pos_name]"), m_pos_name);
	RFX_Date(pFX, _T("[order_time]"), m_order_time);
	RFX_Date(pFX, _T("[return_time]"), m_return_time);
	RFX_Text(pFX, _T("[return_reason]"), m_return_reason);
	RFX_Text(pFX, _T("[unit]"), m_unit);
	RFX_Bool(pFX, _T("[is_send]"), m_is_send);
	RFX_Long(pFX, _T("[condiment_belong_item]"), m_condiment_belong_item);
	RFX_Single(pFX, _T("[quantity]"), m_quantity);
	RFX_Long(pFX, _T("[eat_type]"), m_eat_type);
	RFX_Long(pFX, _T("[auth_id]"), m_auth_id);
	RFX_Text(pFX, _T("[auth_name]"), m_auth_name);
	RFX_Bool(pFX, _T("[weight_entry_required]"), m_weight_entry_required);
	RFX_Text(pFX, _T("[description]"), m_description);
	RFX_Long(pFX, _T("[n_service_type]"), m_n_service_type);
	RFX_Long(pFX, _T("[not_print]"), m_notprint);
	RFX_Long(pFX, _T("[seat_num]"), m_n_seat_num);
	RFX_Single(pFX, _T("[discount_price]"), m_discount_price);
	RFX_Single(pFX, _T("[sales_amount]"), m_sales_amount);
	RFX_Long(pFX,_T("print_class"),m_print_class);

}
/////////////////////////////////////////////////////////////////////////////
// COrder_Detail 诊断

#ifdef _DEBUG
void COrder_Detail::AssertValid() const
{
	CRecordset::AssertValid();
}

void COrder_Detail::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


