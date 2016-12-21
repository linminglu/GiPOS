DROP TRIGGER IF EXISTS trigger_tables_update ;
DROP TRIGGER IF EXISTS trigger_tables_add ;
DROP TRIGGER IF EXISTS trigger_tables_del ;

DROP TRIGGER IF EXISTS trigger_desheader_update;
DROP TRIGGER IF EXISTS trigger_desheader_add;
DROP TRIGGER IF EXISTS trigger_desheader_del;
DROP TRIGGER IF EXISTS trigger_destrailer_update;
DROP TRIGGER IF EXISTS trigger_destrailer_add;
DROP TRIGGER IF EXISTS trigger_destrailer_del;

DROP TRIGGER IF EXISTS trigger_order_detail_add;

DELIMITER ;;

CREATE TRIGGER `trigger_order_detail_add` BEFORE INSERT ON `order_detail` FOR EACH ROW BEGIN 
if NEW.order_detail_id IS NULL then
	set NEW.order_time=now();
end if;
END;;

DROP TRIGGER IF EXISTS trigger_tendermedia_update ;;
CREATE TRIGGER trigger_tendermedia_update AFTER UPDATE ON tender_media
FOR EACH ROW BEGIN
	UPDATE webreport_setting SET tender_media = tender_media | 1;
END;;

DROP TRIGGER IF EXISTS trigger_tendermedia_add ;;
CREATE TRIGGER trigger_tendermedia_add AFTER INSERT ON tender_media
FOR EACH ROW BEGIN
	UPDATE webreport_setting SET tender_media = tender_media | 1;
END;;

DROP TRIGGER IF EXISTS trigger_tendermedia_del ;;
CREATE TRIGGER trigger_tendermedia_del AFTER DELETE ON tender_media
FOR EACH ROW BEGIN
	UPDATE webreport_setting SET tender_media = tender_media | 1;
END;;

DROP TRIGGER IF EXISTS trigger_discount_service_update ;;
CREATE TRIGGER trigger_discount_service_update AFTER UPDATE ON discount_service
FOR EACH ROW BEGIN
	UPDATE webreport_setting SET tender_media = tender_media | 2;
END;;

DROP TRIGGER IF EXISTS trigger_discount_service_add ;;
CREATE TRIGGER trigger_discount_service_add AFTER INSERT ON discount_service
FOR EACH ROW BEGIN
	UPDATE webreport_setting SET tender_media = tender_media | 2;
END;;

DROP TRIGGER IF EXISTS trigger_discount_service_del ;;
CREATE TRIGGER trigger_discount_service_del AFTER DELETE ON discount_service
FOR EACH ROW BEGIN
	UPDATE webreport_setting SET tender_media = tender_media | 2;
END;;

DROP TRIGGER IF EXISTS trigger_service_tip_update ;;
CREATE TRIGGER trigger_service_tip_update AFTER UPDATE ON service_tip
FOR EACH ROW BEGIN
	UPDATE webreport_setting SET tender_media = tender_media | 4;
END;;

DROP TRIGGER IF EXISTS trigger_service_tip_add ;;
CREATE TRIGGER trigger_service_tip_add AFTER INSERT ON service_tip
FOR EACH ROW BEGIN
	UPDATE webreport_setting SET tender_media = tender_media | 4;
END;;

DROP TRIGGER IF EXISTS trigger_service_tip_del ;;
CREATE TRIGGER trigger_service_tip_del AFTER DELETE ON service_tip
FOR EACH ROW BEGIN
	UPDATE webreport_setting SET tender_media = tender_media | 4;
END;;

DROP TRIGGER IF EXISTS trigger_major_group_update ;;
CREATE TRIGGER trigger_major_group_update AFTER UPDATE ON major_group
FOR EACH ROW BEGIN
	UPDATE webreport_setting SET major_group = major_group | 1;
END;;

DROP TRIGGER IF EXISTS trigger_major_group_add ;;
CREATE TRIGGER trigger_major_group_add AFTER INSERT ON major_group
FOR EACH ROW BEGIN
	UPDATE webreport_setting SET major_group = major_group | 1;
END;;

DROP TRIGGER IF EXISTS trigger_major_group_del ;;
CREATE TRIGGER trigger_major_group_del AFTER DELETE ON major_group
FOR EACH ROW BEGIN
	UPDATE webreport_setting SET major_group = major_group | 1;
END;;

DROP TRIGGER IF EXISTS trigger_print_devices_update ;;
CREATE TRIGGER trigger_print_devices_update AFTER UPDATE ON print_devices
FOR EACH ROW BEGIN
	UPDATE webreport_setting SET major_group = major_group | 2;
END;;

DROP TRIGGER IF EXISTS trigger_print_devices_add ;;
CREATE TRIGGER trigger_print_devices_add AFTER INSERT ON print_devices
FOR EACH ROW BEGIN
	UPDATE webreport_setting SET major_group = major_group | 2;
END;;

DROP TRIGGER IF EXISTS trigger_print_devices_del ;;
CREATE TRIGGER trigger_print_devices_del AFTER DELETE ON print_devices
FOR EACH ROW BEGIN
	UPDATE webreport_setting SET major_group = major_group | 2;
END;;

DROP TRIGGER IF EXISTS trigger_print_class_update ;;
CREATE TRIGGER trigger_print_class_update AFTER UPDATE ON print_class_relation
FOR EACH ROW BEGIN
	UPDATE webreport_setting SET major_group = major_group | 4;
END;;

DROP TRIGGER IF EXISTS trigger_print_class_add ;;
CREATE TRIGGER trigger_print_class_add AFTER INSERT ON print_class_relation
FOR EACH ROW BEGIN
	UPDATE webreport_setting SET major_group = major_group | 4;
END;;

DROP TRIGGER IF EXISTS trigger_print_class_del ;;
CREATE TRIGGER trigger_print_class_del AFTER DELETE ON print_class_relation
FOR EACH ROW BEGIN
	UPDATE webreport_setting SET major_group = major_group | 4;
END;;

DROP TRIGGER IF EXISTS trigger_family_group_update ;;
CREATE TRIGGER trigger_family_group_update AFTER UPDATE ON family_group
FOR EACH ROW BEGIN
	UPDATE webreport_setting SET family_group = family_group | 1;
END;;

DROP TRIGGER IF EXISTS trigger_family_group_add ;;
CREATE TRIGGER trigger_family_group_add AFTER INSERT ON family_group
FOR EACH ROW BEGIN
	UPDATE webreport_setting SET family_group = family_group | 1;
END;;

DROP TRIGGER IF EXISTS trigger_family_group_del ;;
CREATE TRIGGER trigger_family_group_del AFTER DELETE ON family_group
FOR EACH ROW BEGIN
	UPDATE webreport_setting SET family_group = family_group | 1;
END;;

DROP TRIGGER IF EXISTS trigger_rvc_center_update ;;
CREATE TRIGGER trigger_rvc_center_update AFTER UPDATE ON rvc_center
FOR EACH ROW BEGIN
	UPDATE webreport_setting SET rvc_center = rvc_center | 1;
END;;

DROP TRIGGER IF EXISTS trigger_rvc_center_add ;;
CREATE TRIGGER trigger_rvc_center_add AFTER INSERT ON rvc_center
FOR EACH ROW BEGIN
	UPDATE webreport_setting SET rvc_center = rvc_center | 1;
END;;

DROP TRIGGER IF EXISTS trigger_rvc_center_del ;;
CREATE TRIGGER trigger_rvc_center_del AFTER DELETE ON rvc_center
FOR EACH ROW BEGIN
	UPDATE webreport_setting SET rvc_center = rvc_center | 1;
END;;

DROP TRIGGER IF EXISTS trigger_serving_rvc_class_add ;;
CREATE TRIGGER trigger_serving_rvc_class_add AFTER INSERT ON serving_rvc_class
FOR EACH ROW BEGIN
	UPDATE webreport_setting SET rvc_center = rvc_center | 2;
END;;

DROP TRIGGER IF EXISTS trigger_workstation_update ;;
CREATE TRIGGER trigger_workstation_update AFTER UPDATE ON user_workstations
FOR EACH ROW BEGIN
	UPDATE webreport_setting SET rvc_center = rvc_center | 4;
END;;

DROP TRIGGER IF EXISTS trigger_workstation_add ;;
CREATE TRIGGER trigger_workstation_add AFTER INSERT ON user_workstations
FOR EACH ROW BEGIN
	UPDATE webreport_setting SET rvc_center = rvc_center | 4;
END;;

DROP TRIGGER IF EXISTS trigger_workstation_del ;;
CREATE TRIGGER trigger_workstation_del AFTER DELETE ON user_workstations
FOR EACH ROW BEGIN
	UPDATE webreport_setting SET rvc_center = rvc_center | 4;
END;;

DROP TRIGGER IF EXISTS trigger_macros_update ;;
CREATE TRIGGER trigger_macros_update AFTER UPDATE ON macros
FOR EACH ROW BEGIN
	UPDATE webreport_setting SET rvc_center = rvc_center | 8;
END;;

DROP TRIGGER IF EXISTS trigger_periods_update ;;
CREATE TRIGGER trigger_periods_update AFTER UPDATE ON periods
FOR EACH ROW BEGIN
	UPDATE webreport_setting SET periods = periods | 1;
END;;

DROP TRIGGER IF EXISTS trigger_periods_add ;;
CREATE TRIGGER trigger_periods_add AFTER INSERT ON periods
FOR EACH ROW BEGIN
	UPDATE webreport_setting SET periods = periods | 1;
END;;

DROP TRIGGER IF EXISTS trigger_periods_del ;;
CREATE TRIGGER trigger_periods_del AFTER DELETE ON periods
FOR EACH ROW BEGIN
	UPDATE webreport_setting SET periods = periods | 1;
END;;

DROP TRIGGER IF EXISTS trigger_serving_period_class_add ;;
CREATE TRIGGER trigger_serving_period_class_add AFTER INSERT ON serving_period_class
FOR EACH ROW BEGIN
	UPDATE webreport_setting SET periods = periods | 2;
END;;

DROP TRIGGER IF EXISTS trigger_employee_update ;;
CREATE TRIGGER trigger_employee_update AFTER UPDATE ON employee
FOR EACH ROW BEGIN
	UPDATE webreport_setting SET employee = employee | 1;
END;;

DROP TRIGGER IF EXISTS trigger_employee_add ;;
CREATE TRIGGER trigger_employee_add AFTER INSERT ON employee
FOR EACH ROW BEGIN
	UPDATE webreport_setting SET employee = employee | 1;
END;;

DROP TRIGGER IF EXISTS trigger_employee_del ;;
CREATE TRIGGER trigger_employee_del AFTER DELETE ON employee
FOR EACH ROW BEGIN
	UPDATE webreport_setting SET employee = employee | 1;
END;;

DROP TRIGGER IF EXISTS trigger_employee_class_update ;;
CREATE TRIGGER trigger_employee_class_update AFTER UPDATE ON employee_class
FOR EACH ROW BEGIN
	UPDATE webreport_setting SET employee = employee | 2;
END;;

DROP TRIGGER IF EXISTS trigger_employee_class_add ;;
CREATE TRIGGER trigger_employee_class_add AFTER INSERT ON employee_class
FOR EACH ROW BEGIN
	UPDATE webreport_setting SET employee = employee | 2;
END;;

DROP TRIGGER IF EXISTS trigger_employee_class_del ;;
CREATE TRIGGER trigger_employee_class_del AFTER DELETE ON employee_class
FOR EACH ROW BEGIN
	UPDATE webreport_setting SET employee = employee | 2;
END;;

DROP TRIGGER IF EXISTS trigger_reasons_update ;;
CREATE TRIGGER trigger_reasons_update AFTER UPDATE ON reasons
FOR EACH ROW BEGIN
	UPDATE webreport_setting SET employee = employee | 4;
END;;

DROP TRIGGER IF EXISTS trigger_reasons_add ;;
CREATE TRIGGER trigger_reasons_add AFTER INSERT ON reasons
FOR EACH ROW BEGIN
	UPDATE webreport_setting SET employee = employee | 4;
END;;

DROP TRIGGER IF EXISTS trigger_reasons_del ;;
CREATE TRIGGER trigger_reasons_del AFTER DELETE ON reasons
FOR EACH ROW BEGIN
	UPDATE webreport_setting SET employee = employee | 4;
END;;

DROP TRIGGER IF EXISTS trigger_menu_item_update ;;
CREATE TRIGGER trigger_menu_item_update AFTER UPDATE ON menu_item
FOR EACH ROW BEGIN
	UPDATE webreport_setting SET menu_item = menu_item | 1;
END;;

DROP TRIGGER IF EXISTS trigger_menu_item_add ;;
CREATE TRIGGER trigger_menu_item_add AFTER INSERT ON menu_item
FOR EACH ROW BEGIN
	UPDATE webreport_setting SET menu_item = menu_item | 1;
END;;

DROP TRIGGER IF EXISTS trigger_menu_item_del ;;
CREATE TRIGGER trigger_menu_item_del AFTER DELETE ON menu_item
FOR EACH ROW BEGIN
	UPDATE webreport_setting SET menu_item = menu_item | 1;
END;;

DROP TRIGGER IF EXISTS trigger_menu_item_slu_update ;;
CREATE TRIGGER trigger_menu_item_slu_update AFTER UPDATE ON descriptors_menu_item_slu
FOR EACH ROW BEGIN
	UPDATE webreport_setting SET menu_item = menu_item | 2;
END;;

DROP TRIGGER IF EXISTS trigger_menu_item_slu_add ;;
CREATE TRIGGER trigger_menu_item_slu_add AFTER INSERT ON descriptors_menu_item_slu
FOR EACH ROW BEGIN
	UPDATE webreport_setting SET menu_item = menu_item | 2;
END;;

DROP TRIGGER IF EXISTS trigger_menu_item_slu_del ;;
CREATE TRIGGER trigger_menu_item_slu_del AFTER DELETE ON descriptors_menu_item_slu
FOR EACH ROW BEGIN
	UPDATE webreport_setting SET menu_item = menu_item | 2;
END;;

DROP TRIGGER IF EXISTS trigger_course_group_update ;;
CREATE TRIGGER trigger_course_group_update AFTER UPDATE ON course_group
FOR EACH ROW BEGIN
	UPDATE webreport_setting SET menu_item = menu_item | 4;
END;;

DROP TRIGGER IF EXISTS trigger_course_group_add ;;
CREATE TRIGGER trigger_course_group_add AFTER INSERT ON course_group
FOR EACH ROW BEGIN
	UPDATE webreport_setting SET menu_item = menu_item | 4;
END;;

DROP TRIGGER IF EXISTS trigger_course_group_del ;;
CREATE TRIGGER trigger_course_group_del AFTER DELETE ON course_group
FOR EACH ROW BEGIN
	UPDATE webreport_setting SET menu_item = menu_item | 4;
END;;

DROP TRIGGER IF EXISTS trigger_course_detail_update ;;
CREATE TRIGGER trigger_course_detail_update AFTER UPDATE ON course_detail
FOR EACH ROW BEGIN
	UPDATE webreport_setting SET menu_item = menu_item | 4;
END;;

DROP TRIGGER IF EXISTS trigger_course_detail_add ;;
CREATE TRIGGER trigger_course_detail_add AFTER INSERT ON course_detail
FOR EACH ROW BEGIN
	UPDATE webreport_setting SET menu_item = menu_item | 4;
END;;

DROP TRIGGER IF EXISTS trigger_course_detail_del ;;
CREATE TRIGGER trigger_course_detail_del AFTER DELETE ON course_detail
FOR EACH ROW BEGIN
	UPDATE webreport_setting SET menu_item = menu_item | 4;
END;;

DROP TRIGGER IF EXISTS trigger_condiment_membership_update ;;
CREATE TRIGGER trigger_condiment_membership_update AFTER UPDATE ON condiment_membership
FOR EACH ROW BEGIN
	UPDATE webreport_setting SET menu_item = menu_item | 8;
END;;

DROP TRIGGER IF EXISTS trigger_condiment_membership_add ;;
CREATE TRIGGER trigger_condiment_membership_add AFTER INSERT ON condiment_membership
FOR EACH ROW BEGIN
	UPDATE webreport_setting SET menu_item = menu_item | 8;
END;;

DROP TRIGGER IF EXISTS trigger_condiment_membership_del ;;
CREATE TRIGGER trigger_condiment_membership_del AFTER DELETE ON condiment_membership
FOR EACH ROW BEGIN
	UPDATE webreport_setting SET menu_item = menu_item | 8;
END;;

DROP TRIGGER IF EXISTS trigger_consumption_limit_update ;;
CREATE TRIGGER trigger_consumption_limit_update AFTER UPDATE ON consumption_limit
FOR EACH ROW BEGIN
	UPDATE webreport_setting SET tables = tables | 2;
END;;

DROP TRIGGER IF EXISTS trigger_consumption_limit_add ;;
CREATE TRIGGER trigger_consumption_limit_add AFTER INSERT ON consumption_limit
FOR EACH ROW BEGIN
	UPDATE webreport_setting SET tables = tables | 2;
END;;

DROP TRIGGER IF EXISTS trigger_consumption_limit_del ;;
CREATE TRIGGER trigger_consumption_limit_del AFTER DELETE ON consumption_limit
FOR EACH ROW BEGIN
	UPDATE webreport_setting SET tables = tables | 2;
END;;

DROP TRIGGER IF EXISTS trigger_price_scheme_update ;;
CREATE TRIGGER trigger_price_scheme_update AFTER UPDATE ON price_scheme
FOR EACH ROW BEGIN
	UPDATE webreport_setting SET tables = tables | 4;
END;;

DROP TRIGGER IF EXISTS trigger_price_scheme_add ;;
CREATE TRIGGER trigger_price_scheme_add AFTER INSERT ON price_scheme
FOR EACH ROW BEGIN
	UPDATE webreport_setting SET tables = tables | 4;
END;;

DROP TRIGGER IF EXISTS trigger_price_scheme_del ;;
CREATE TRIGGER trigger_price_scheme_del AFTER DELETE ON price_scheme
FOR EACH ROW BEGIN
	UPDATE webreport_setting SET tables = tables | 4;
END;;

DROP TRIGGER IF EXISTS trigger_restaurant_update ;;
CREATE TRIGGER trigger_restaurant_update AFTER UPDATE ON restaurant
FOR EACH ROW BEGIN
	UPDATE webreport_setting SET res_info = res_info | 1;
END;;

DROP TRIGGER IF EXISTS trigger_restaurant_add ;;
CREATE TRIGGER trigger_restaurant_add AFTER INSERT ON restaurant
FOR EACH ROW BEGIN
	UPDATE webreport_setting SET res_info = res_info | 1;
END;;

DROP TRIGGER IF EXISTS trigger_restaurant_del ;;
CREATE TRIGGER trigger_restaurant_del AFTER DELETE ON restaurant
FOR EACH ROW BEGIN
	UPDATE webreport_setting SET res_info = res_info | 1;
END;;

DROP TRIGGER IF EXISTS trigger_order_detail_default_update ;;
CREATE TRIGGER trigger_order_detail_default_update AFTER UPDATE ON order_detail_default
FOR EACH ROW BEGIN
	UPDATE webreport_setting SET res_info = res_info | 2;
END;;

DROP TRIGGER IF EXISTS trigger_order_detail_default_add ;;
CREATE TRIGGER trigger_order_detail_default_add AFTER INSERT ON order_detail_default
FOR EACH ROW BEGIN
	UPDATE webreport_setting SET res_info = res_info | 2;
END;;

DROP TRIGGER IF EXISTS trigger_order_detail_default_del ;;
CREATE TRIGGER trigger_order_detail_default_del AFTER DELETE ON order_detail_default
FOR EACH ROW BEGIN
	UPDATE webreport_setting SET res_info = res_info | 2;
END;;

DROP TRIGGER IF EXISTS trigger_order_default_group_update ;;
CREATE TRIGGER trigger_order_default_group_update AFTER UPDATE ON order_default_group
FOR EACH ROW BEGIN
	UPDATE webreport_setting SET res_info = res_info | 2;
END;;

DROP TRIGGER IF EXISTS trigger_order_default_group_add ;;
CREATE TRIGGER trigger_order_default_group_add AFTER INSERT ON order_default_group
FOR EACH ROW BEGIN
	UPDATE webreport_setting SET res_info = res_info | 2;
END;;

DROP TRIGGER IF EXISTS trigger_order_default_group_del ;;
CREATE TRIGGER trigger_order_default_group_del AFTER DELETE ON order_default_group
FOR EACH ROW BEGIN
	UPDATE webreport_setting SET res_info = res_info | 2;
END;;

DROP TRIGGER IF EXISTS trigger_tax_primary_update ;;
CREATE TRIGGER trigger_tax_primary_update AFTER UPDATE ON tax_primary
FOR EACH ROW BEGIN
	UPDATE webreport_setting SET res_info = res_info | 4;
END;;

DROP TRIGGER IF EXISTS trigger_tax_primary_add ;;
CREATE TRIGGER trigger_tax_primary_add AFTER INSERT ON tax_primary
FOR EACH ROW BEGIN
	UPDATE webreport_setting SET res_info = res_info | 4;
END;;

DROP TRIGGER IF EXISTS trigger_tax_primary_del ;;
CREATE TRIGGER trigger_tax_primary_del AFTER DELETE ON tax_primary
FOR EACH ROW BEGIN
	UPDATE webreport_setting SET res_info = res_info | 4;
END;;

DROP TRIGGER IF EXISTS trigger_tax_update ;;
CREATE TRIGGER trigger_tax_update AFTER UPDATE ON tax
FOR EACH ROW BEGIN
	UPDATE webreport_setting SET res_info = res_info | 4;
END;;

DROP TRIGGER IF EXISTS trigger_tax_add ;;
CREATE TRIGGER trigger_tax_add AFTER INSERT ON tax
FOR EACH ROW BEGIN
	UPDATE webreport_setting SET res_info = res_info | 4;
END;;

DROP TRIGGER IF EXISTS trigger_tax_del ;;
CREATE TRIGGER trigger_tax_del AFTER DELETE ON tax
FOR EACH ROW BEGIN
	UPDATE webreport_setting SET res_info = res_info | 4;
END;;

DROP TRIGGER IF EXISTS trigger_trailer_update ;;
CREATE TRIGGER trigger_trailer_update AFTER UPDATE ON descriptors_trailers
FOR EACH ROW BEGIN
	UPDATE webreport_setting SET res_info = res_info | 8;
END;;

DROP TRIGGER IF EXISTS trigger_header_update ;;
CREATE TRIGGER trigger_header_update AFTER UPDATE ON descriptors_headers
FOR EACH ROW BEGIN
	UPDATE webreport_setting SET res_info = res_info | 8;
END;;

DROP TRIGGER IF EXISTS trigger_soldout_add ;;
CREATE TRIGGER `trigger_soldout_add` AFTER INSERT ON `bargain_price_item` 
FOR EACH ROW BEGIN
	UPDATE webreport_setting SET soldout = soldout | 2;
END;;

DROP TRIGGER IF EXISTS trigger_soldout_del ;;
CREATE TRIGGER `trigger_soldout_del` AFTER DELETE ON `bargain_price_item` 
FOR EACH ROW BEGIN
	UPDATE webreport_setting SET soldout = soldout | 2;
END;;

DROP TRIGGER IF EXISTS trigger_soldout_update ;;
CREATE TRIGGER `trigger_soldout_update` AFTER UPDATE ON `bargain_price_item` 
FOR EACH ROW BEGIN
	UPDATE webreport_setting SET soldout = soldout | 1;
END;;

DELIMITER ;
