/*
Navicat MySQL Data Transfer

Source Server         : coolroid
Source Server Version : 50537
Source Host           : localhost:3308
Source Database       : coolroid

Target Server Type    : MYSQL
Target Server Version : 50537
File Encoding         : 65001

Date: 2016-12-13 15:48:24
*/

SET FOREIGN_KEY_CHECKS=0;
SET UNIQUE_CHECKS=0;
SET autocommit=0;
create database IF NOT EXISTS coolroid default character set utf8 collate utf8_general_ci;
create database IF NOT EXISTS coolroid_train default character set utf8 collate utf8_general_ci;
use coolroid;
-- ----------------------------
-- Table structure for `bargain_price_item`
-- ----------------------------
CREATE TABLE `bargain_price_item` (
`bargain_item_id`  int(11) NOT NULL ,
`bargain_item_number`  int(11) NOT NULL ,
`bargain_item_name`  varchar(60) NULL DEFAULT NULL ,
`bargain_status`  int(11) NULL DEFAULT NULL ,
`bargain_stype`  int(11) NULL DEFAULT NULL ,
`bargain_num_cur`  float NULL DEFAULT NULL ,
`bargain_num`  float NULL DEFAULT NULL ,
`bargain_price`  float NULL DEFAULT NULL ,
`bargain_vip`  bit(1) NULL DEFAULT NULL ,
`bargain_start_date`  date NULL DEFAULT NULL ,
`bargain_end_date`  date NULL DEFAULT NULL ,
`bargain_start_time`  time NULL DEFAULT NULL ,
`bargain_end_time`  time NULL DEFAULT NULL ,
`is_every_day`  bit(1) NULL DEFAULT NULL ,
`now_use_date`  date NULL DEFAULT NULL ,
PRIMARY KEY (`bargain_item_id`)
)
ENGINE=InnoDB

;

-- ----------------------------
-- Records of bargain_price_item
-- ----------------------------

-- ----------------------------
-- Table structure for `cashbox_in_out`
-- ----------------------------
CREATE TABLE `cashbox_in_out` (
`in_out_id`  int(11) NOT NULL AUTO_INCREMENT ,
`cashbox_id`  int(11) NULL DEFAULT NULL ,
`type`  int(11) NULL DEFAULT NULL ,
`cash_amount`  decimal(11,2) NULL DEFAULT NULL ,
`in_out_time`  datetime NULL DEFAULT NULL ,
`employee_id`  int(11) NULL DEFAULT NULL ,
`employee_name`  varchar(30) NULL DEFAULT NULL ,
PRIMARY KEY (`in_out_id`)
)
ENGINE=InnoDB
AUTO_INCREMENT=1

;

-- ----------------------------
-- Records of cashbox_in_out
-- ----------------------------

-- ----------------------------
-- Table structure for `cashbox_period_amout`
-- ----------------------------
CREATE TABLE `cashbox_period_amout` (
`employee_id`  int(11) NULL DEFAULT NULL ,
`cashbox_id`  int(11) NULL DEFAULT NULL ,
`date_from`  datetime NULL DEFAULT NULL ,
`cash_from`  float NULL DEFAULT NULL ,
`date_to`  datetime NULL DEFAULT NULL ,
`cash_to`  float NULL DEFAULT NULL 
)
ENGINE=InnoDB

;

-- ----------------------------
-- Records of cashbox_period_amout
-- ----------------------------

-- ----------------------------
-- Table structure for `condiment_groups`
-- ----------------------------
CREATE TABLE `condiment_groups` (
`scomdiment_groups_id`  int(11) NOT NULL ,
`comdiment_groups_name`  varchar(30) NULL DEFAULT NULL ,
`touchscreen_style`  int(11) NULL DEFAULT NULL ,
`price`  float(11,0) NOT NULL ,
PRIMARY KEY (`scomdiment_groups_id`)
)
ENGINE=InnoDB

;

-- ----------------------------
-- Records of condiment_groups
-- ----------------------------
INSERT INTO condiment_groups VALUES ('1', '特别要求', null, '0'), ('2', '蔬菜做法', null, '0'), ('3', '牛扒做法', null, '0'), ('4', '咖啡风味', null, '0'), ('5', '免放类', null, '0'), ('6', '口味', null, '0'), ('7', '调味汁酱', null, '0'), ('9', '数量', null, '0');

-- ----------------------------
-- Table structure for `condiment_membership`
-- ----------------------------
CREATE TABLE `condiment_membership` (
`condiment_groups_id`  int(11) NOT NULL ,
`menu_item_id`  int(11) NOT NULL ,
PRIMARY KEY (`condiment_groups_id`, `menu_item_id`)
)
ENGINE=InnoDB

;

-- ----------------------------
-- Records of condiment_membership
-- ----------------------------
INSERT INTO condiment_membership VALUES ('1', '6000'), ('1', '6004'), ('1', '6670'), ('1', '6671'), ('1', '6672'), ('1', '6673'), ('1', '6674'), ('1', '6675'), ('1', '6676'), ('1', '6677'), ('1', '6678'), ('1', '6679'), ('1', '6680'), ('1', '6681'), ('1', '6682'), ('1', '6683'), ('1', '6684'), ('1', '6685'), ('1', '6686'), ('1', '6687'), ('1', '6688'), ('1', '6689'), ('1', '6690'), ('1', '6691'), ('1', '6692'), ('1', '6693'), ('1', '6694'), ('1', '6695'), ('2', '6041'), ('2', '6042'), ('2', '6043'), ('2', '6044'), ('2', '6045'), ('2', '6047'), ('2', '6048'), ('2', '6049'), ('2', '6050'), ('2', '6051'), ('2', '6052'), ('2', '6053'), ('2', '6054'), ('2', '6055'), ('2', '6056'), ('2', '6057'), ('2', '6059'), ('2', '6060'), ('2', '6061'), ('2', '6062'), ('2', '6066'), ('2', '6067'), ('2', '6068'), ('2', '6069'), ('2', '6070'), ('2', '6071'), ('2', '6072'), ('2', '6073'), ('2', '6074'), ('2', '6075'), ('2', '6077'), ('2', '6078'), ('2', '6079'), ('2', '6080'), ('2', '6081'), ('2', '6082'), ('2', '6083'), ('3', '6011'), ('3', '6016'), ('3', '6017'), ('3', '6018'), ('3', '6026'), ('3', '6091'), ('3', '6092'), ('3', '6093'), ('3', '6094'), ('3', '6095'), ('3', '6096'), ('3', '7236'), ('3', '7237'), ('3', '7238'), ('3', '7272'), ('3', '7277'), ('3', '7282'), ('3', '7283'), ('4', '6019'), ('4', '6020'), ('4', '6021'), ('4', '6022'), ('4', '6023'), ('5', '6005'), ('5', '6008'), ('5', '6027'), ('5', '6028'), ('5', '6029'), ('5', '6030'), ('5', '6031'), ('5', '6032'), ('5', '6033'), ('5', '6034'), ('5', '6035'), ('5', '6036'), ('5', '6037');
INSERT INTO condiment_membership VALUES ('5', '6038'), ('5', '6039'), ('6', '6351'), ('6', '6361'), ('6', '6362'), ('6', '6363'), ('6', '6364'), ('6', '6365'), ('6', '6366'), ('6', '6367'), ('6', '6368'), ('6', '6369'), ('6', '6370'), ('6', '6371'), ('6', '6372'), ('6', '6373'), ('6', '6374'), ('6', '6375'), ('6', '6376'), ('6', '6377'), ('6', '6378'), ('6', '6379'), ('6', '6380'), ('6', '6381'), ('6', '6382'), ('6', '6383'), ('6', '6385'), ('6', '6386'), ('7', '6001'), ('7', '6002'), ('7', '6003'), ('7', '6006'), ('7', '6007'), ('7', '6009'), ('7', '6012'), ('7', '6013'), ('7', '6014'), ('7', '6015'), ('7', '6024'), ('7', '6040'), ('7', '6046'), ('7', '6058'), ('7', '6063'), ('7', '6064'), ('7', '6065'), ('7', '6076'), ('7', '6084'), ('7', '6085'), ('7', '6086'), ('9', '6087'), ('9', '6088'), ('9', '6089'), ('9', '6090');

-- ----------------------------
-- Table structure for `consumption_limit`
-- ----------------------------
CREATE TABLE `consumption_limit` (
`consumption_limit_id`  int(11) NOT NULL DEFAULT 0 ,
`consumption_limit_name`  varchar(30) NULL DEFAULT NULL ,
`limit_type`  int(11) NULL DEFAULT NULL ,
`limit_amount`  float NULL DEFAULT NULL ,
PRIMARY KEY (`consumption_limit_id`)
)
ENGINE=InnoDB

;

-- ----------------------------
-- Records of consumption_limit
-- ----------------------------
INSERT INTO consumption_limit VALUES ('1', '默认最低消费', '0', '0');

-- ----------------------------
-- Table structure for `course`
-- ----------------------------
CREATE TABLE `course` (
`course_id`  int(11) NOT NULL ,
`course_name_1`  varchar(40) NULL DEFAULT '' ,
`course_name_2`  varchar(40) NULL DEFAULT '' ,
`course_description`  varchar(200) NULL DEFAULT NULL ,
`price`  float NULL DEFAULT NULL ,
`icon`  varchar(256) NULL DEFAULT NULL ,
`serving _period_class`  int(11) NULL DEFAULT NULL ,
`serving _rvc_class`  int(11) NULL DEFAULT NULL ,
`print_class`  int(11) NULL DEFAULT NULL ,
PRIMARY KEY (`course_id`)
)
ENGINE=InnoDB

;

-- ----------------------------
-- Records of course
-- ----------------------------

-- ----------------------------
-- Table structure for `course_detail`
-- ----------------------------
CREATE TABLE `course_detail` (
`detail_id`  int(11) NOT NULL AUTO_INCREMENT ,
`course_group_id`  int(11) NOT NULL DEFAULT 0 ,
`menu_item_id`  int(11) NOT NULL DEFAULT 0 ,
`item_course_name`  varchar(200) NULL DEFAULT NULL ,
`unit`  varchar(100) NULL DEFAULT NULL ,
`num`  float NULL DEFAULT 1 ,
`price`  float NULL DEFAULT 0 ,
`description`  varchar(200) NULL DEFAULT NULL ,
PRIMARY KEY (`detail_id`)
)
ENGINE=InnoDB
AUTO_INCREMENT=1

;

-- ----------------------------
-- Records of course_detail
-- ----------------------------

-- ----------------------------
-- Table structure for `course_group`
-- ----------------------------
CREATE TABLE `course_group` (
`course_group_id`  int(11) NOT NULL DEFAULT 0 ,
`course_group_name`  varchar(40) NULL DEFAULT NULL ,
`menu_item_id`  int(11) NULL DEFAULT NULL ,
`is_must`  int(11) NULL DEFAULT NULL ,
`choose_num`  int(11) NULL DEFAULT NULL ,
`slu_id`  int(11) NULL DEFAULT '-1' ,
PRIMARY KEY (`course_group_id`)
)
ENGINE=InnoDB

;

-- ----------------------------
-- Records of course_group
-- ----------------------------

-- ----------------------------
-- Table structure for `critical_operation_type`
-- ----------------------------
CREATE TABLE `critical_operation_type` (
`operation_type_id`  int(11) NOT NULL DEFAULT 0 ,
`operation_type_name`  varchar(30) NULL DEFAULT NULL ,
PRIMARY KEY (`operation_type_id`)
)
ENGINE=InnoDB

;

-- ----------------------------
-- Records of critical_operation_type
-- ----------------------------
INSERT INTO critical_operation_type VALUES ('0', '未知类型'), ('1', '赠送'), ('2', '改价'), ('3', '删除'), ('4', '反结账'), ('5', '转台'), ('6', '合台\\合单'), ('7', '退款'), ('8', '交接班'), ('9', '日结');

-- ----------------------------
-- Table structure for `critical_operations`
-- ----------------------------
CREATE TABLE `critical_operations` (
`operation_id`  int(11) NOT NULL AUTO_INCREMENT ,
`operation_type`  int(11) NULL DEFAULT NULL ,
`device_id`  int(11) NULL DEFAULT NULL ,
`order_head_id`  int(11) NULL DEFAULT NULL ,
`employee_id`  int(11) NULL DEFAULT NULL ,
`employee_name`  varchar(30) NULL DEFAULT NULL ,
`operation_time`  datetime NULL DEFAULT NULL ,
`operation_name`  varchar(30) NULL DEFAULT NULL ,
`operation_detail`  varchar(1024) NULL DEFAULT NULL ,
PRIMARY KEY (`operation_id`)
)
ENGINE=InnoDB
AUTO_INCREMENT=1

;

-- ----------------------------
-- Records of critical_operations
-- ----------------------------

-- ----------------------------
-- Table structure for `customer`
-- ----------------------------
CREATE TABLE `customer` (
`customer_id`  int(11) NOT NULL AUTO_INCREMENT ,
`card_id`  varchar(40) NULL DEFAULT '' ,
`customer_name`  varchar(40) NULL DEFAULT NULL ,
`customer_class`  int(11) NULL DEFAULT 0 ,
`times`  int(11) NULL DEFAULT 0 ,
`amount`  decimal(11,2) NULL DEFAULT NULL ,
`telephone_1`  varchar(40) NULL DEFAULT NULL ,
`telephone_2`  varchar(40) NULL DEFAULT NULL ,
`company`  varchar(100) NULL DEFAULT NULL ,
`position`  varchar(100) NULL DEFAULT NULL ,
`address`  varchar(200) NULL DEFAULT NULL ,
`postcode`  varchar(30) NULL DEFAULT NULL ,
`email`  varchar(200) NULL DEFAULT NULL ,
`is_set_birthday`  bit(1) NULL DEFAULT b'0' ,
`birthday`  date NULL DEFAULT NULL ,
`sex`  bit(1) NULL DEFAULT b'1' ,
`description`  varchar(200) NULL DEFAULT '' ,
`score`  int(11) NULL DEFAULT 0 ,
`is_pre_comsume`  int(11) NULL DEFAULT NULL ,
`card_status`  int(11) NULL DEFAULT 0 ,
`cid`  varchar(40) NULL DEFAULT NULL ,
`pwd`  varchar(40) NULL DEFAULT NULL ,
`open_date`  datetime NULL DEFAULT NULL ,
PRIMARY KEY (`customer_id`)
)
ENGINE=InnoDB
AUTO_INCREMENT=1

;

-- ----------------------------
-- Records of customer
-- ----------------------------

-- ----------------------------
-- Table structure for `customer_consume`
-- ----------------------------
CREATE TABLE `customer_consume` (
`card_id`  varchar(40) NOT NULL ,
`amount`  decimal(11,2) NULL DEFAULT NULL ,
`employee_id`  int(11) NULL DEFAULT NULL ,
`employee_name`  varchar(40) NULL DEFAULT NULL ,
`time`  datetime NULL DEFAULT NULL ,
`extend_1`  varchar(40) NULL DEFAULT NULL ,
`id`  int(10) UNSIGNED NOT NULL AUTO_INCREMENT ,
`type`  int(11) NULL DEFAULT 0 ,
`order_head_id`  int(11) NULL DEFAULT NULL ,
`web_id`  int(11) NULL DEFAULT NULL ,
`device_id`  int(11) NULL DEFAULT NULL ,
PRIMARY KEY (`id`)
)
ENGINE=InnoDB
AUTO_INCREMENT=1

;

-- ----------------------------
-- Records of customer_consume
-- ----------------------------

-- ----------------------------
-- Table structure for `customer_display`
-- ----------------------------
CREATE TABLE `customer_display` (
`customer_display_id`  int(11) NOT NULL DEFAULT 0 ,
`customer_display_name`  varchar(30) NULL DEFAULT '' ,
`com_port`  int(11) NOT NULL DEFAULT 0 ,
`baud_rate`  int(11) NULL DEFAULT NULL ,
`parity_type`  int(11) NULL DEFAULT NULL ,
`num_data_bit`  int(11) NULL DEFAULT NULL ,
`num_stop_bits`  int(11) NULL DEFAULT NULL ,
`type`  int(11) NULL DEFAULT 0 ,
PRIMARY KEY (`customer_display_id`, `com_port`)
)
ENGINE=InnoDB

;

-- ----------------------------
-- Records of customer_display
-- ----------------------------
INSERT INTO customer_display VALUES ('1', '顾显1', '1', '2400', '0', '8', '0', '0');

-- ----------------------------
-- Table structure for `dcb_order`
-- ----------------------------
CREATE TABLE `dcb_order` (
`order_head_id`  int(11) NOT NULL ,
`time_diff`  varchar(30) NULL DEFAULT NULL ,
`dcb_id`  varchar(10) NOT NULL 
)
ENGINE=InnoDB

;

-- ----------------------------
-- Records of dcb_order
-- ----------------------------

-- ----------------------------
-- Table structure for `descriptors_headers`
-- ----------------------------
CREATE TABLE `descriptors_headers` (
`descriptors_headers_id`  int(11) NOT NULL ,
`descriptors_headers_number`  int(11) NULL DEFAULT NULL ,
`descriptors_headers_name`  varchar(30) NULL DEFAULT NULL ,
`line_1`  varchar(100) NULL DEFAULT NULL ,
`pirnt_type_1`  int(11) NULL DEFAULT 0 ,
`line_2`  varchar(100) NULL DEFAULT NULL ,
`pirnt_type_2`  int(11) NULL DEFAULT 0 ,
`line_3`  varchar(100) NULL DEFAULT NULL ,
`pirnt_type_3`  int(11) NULL DEFAULT 0 ,
`line_4`  varchar(100) NULL DEFAULT NULL ,
`pirnt_type_4`  int(11) NULL DEFAULT 0 ,
`line_5`  varchar(100) NULL DEFAULT NULL ,
`pirnt_type_5`  int(11) NULL DEFAULT 0 ,
`line_6`  varchar(100) NULL DEFAULT NULL ,
`pirnt_type_6`  int(11) NULL DEFAULT 0 ,
PRIMARY KEY (`descriptors_headers_id`)
)
ENGINE=InnoDB

;

-- ----------------------------
-- Records of descriptors_headers
-- ----------------------------
INSERT INTO descriptors_headers VALUES ('1', null, '餐厅名称账单头', 'XX咖啡厅', '0', '', '0', '', '0', '', '0', '', '0', '', '0');

-- ----------------------------
-- Table structure for `descriptors_menu_item_slu`
-- ----------------------------
CREATE TABLE `descriptors_menu_item_slu` (
`dmi_slu_id`  int(11) NOT NULL ,
`dmi_slu_number`  int(11) NULL DEFAULT NULL ,
`dmi_slu_name`  varchar(30) NULL DEFAULT NULL ,
`touchscreen_style`  int(11) NULL DEFAULT NULL ,
`class_id`  int(11) NULL DEFAULT '-1' ,
`print_class`  int(11) NULL DEFAULT '-1' ,
`allow_condimentint`  int(11) NULL DEFAULT '-1' ,
`required_condiment`  int(11) NULL DEFAULT '-1' ,
`item_type`  int(11) NULL DEFAULT 0 ,
`major_group`  int(11) NULL DEFAULT '-1' ,
`family_group`  int(11) NULL DEFAULT '-1' ,
`period_class_id`  int(11) NULL DEFAULT '-1' ,
`rvc_class_id`  int(11) NULL DEFAULT '-1' ,
`ticket_class`  int(11) NULL DEFAULT 1 ,
`tax_group`  int(11) NULL DEFAULT '-1' ,
`commission_type`  int(11) NULL DEFAULT 0 ,
`commission_value`  float NULL DEFAULT 0 ,
PRIMARY KEY (`dmi_slu_id`)
)
ENGINE=InnoDB

;

-- ----------------------------
-- Records of descriptors_menu_item_slu
-- ----------------------------
INSERT INTO descriptors_menu_item_slu VALUES ('10', '1', '比利时咖啡', null, '6', '4', '-1', '-1', '0', '1', '4', '-1', '-1', '1', '-1', '0', '0'), ('12', null, '意式咖啡', null, '6', '4', '-1', '-1', '0', '1', '4', '-1', '-1', '1', '-1', '0', '0'), ('30', '1', '浓汤类', null, '6', '-1', '-1', '-1', '0', '3', '17', '-1', '-1', '1', '-1', '0', '0'), ('91', '1', '自定义菜', null, '6', '-1', '-1', '-1', '4', '-1', '18', '-1', '-1', '1', '-1', '0', '0'), ('9999', null, '回收站', null, '6', '-1', '-1', '-1', '0', '-1', '-1', '-1', '-1', '1', '-1', '0', '0');

-- ----------------------------
-- Table structure for `descriptors_trailers`
-- ----------------------------
CREATE TABLE `descriptors_trailers` (
`descriptors_trailers_id`  int(11) NOT NULL ,
`descriptors_trailers_number`  int(11) NULL DEFAULT NULL ,
`descriptors_trailers_name`  varchar(30) NULL DEFAULT NULL ,
`line_1`  varchar(100) NULL DEFAULT NULL ,
`pirnt_type_1`  int(11) NULL DEFAULT 0 ,
`line_2`  varchar(100) NULL DEFAULT NULL ,
`pirnt_type_2`  int(11) NULL DEFAULT 0 ,
`line_3`  varchar(100) NULL DEFAULT NULL ,
`pirnt_type_3`  int(11) NULL DEFAULT 0 ,
`line_4`  varchar(100) NULL DEFAULT NULL ,
`pirnt_type_4`  int(11) NULL DEFAULT 0 ,
`line_5`  varchar(100) NULL DEFAULT NULL ,
`pirnt_type_5`  int(11) NULL DEFAULT 0 ,
`line_6`  varchar(100) NULL DEFAULT NULL ,
`pirnt_type_6`  int(11) NULL DEFAULT 0 ,
`line_7`  varchar(100) NULL DEFAULT NULL ,
`pirnt_type_7`  int(11) NULL DEFAULT 0 ,
`line_8`  varchar(100) NULL DEFAULT NULL ,
`pirnt_type_8`  int(11) NULL DEFAULT 0 ,
`line_9`  varchar(100) NULL DEFAULT NULL ,
`pirnt_type_9`  int(11) NULL DEFAULT 0 ,
`line_10`  varchar(100) NULL DEFAULT NULL ,
`pirnt_type_10`  int(11) NULL DEFAULT 0 ,
`line_11`  varchar(100) NULL DEFAULT NULL ,
`pirnt_type_11`  int(11) NULL DEFAULT 0 ,
`line_12`  varchar(100) NULL DEFAULT NULL ,
`pirnt_type_12`  int(11) NULL DEFAULT 0 ,
PRIMARY KEY (`descriptors_trailers_id`)
)
ENGINE=InnoDB

;

-- ----------------------------
-- Records of descriptors_trailers
-- ----------------------------
INSERT INTO descriptors_trailers VALUES ('1', null, '餐厅地址账单尾', '  谢谢光临！', '0', '地址：深圳市福田区车公庙安徽大厦', '0', '电话：0755-26631190', '0', '', '0', '', '0', '', '0', '', '0', '', '0', '', '0', '', '0', '', '0', '', '0');

-- ----------------------------
-- Table structure for `device_checkin`
-- ----------------------------
CREATE TABLE `device_checkin` (
`device_id`  varchar(100) NOT NULL DEFAULT '' ,
`last_checkin_time`  varchar(10) NULL DEFAULT NULL ,
PRIMARY KEY (`device_id`)
)
ENGINE=InnoDB

;

-- ----------------------------
-- Records of device_checkin
-- ----------------------------

-- ----------------------------
-- Table structure for `discount_service`
-- ----------------------------
CREATE TABLE `discount_service` (
`discount_service_id`  int(11) NOT NULL ,
`discount_service_number`  int(11) NULL DEFAULT NULL ,
`discount_service_name`  varchar(40) NULL DEFAULT NULL ,
`type`  int(11) NOT NULL DEFAULT 0 ,
`print_class`  int(11) NULL DEFAULT NULL ,
`menu_level_class`  int(11) NULL DEFAULT NULL ,
`privilege`  int(11) NULL DEFAULT NULL ,
`nlu`  int(11) NULL DEFAULT NULL ,
`amount`  decimal(11,2) NULL DEFAULT NULL ,
`date_from`  datetime NULL DEFAULT NULL ,
`date_to`  datetime NULL DEFAULT NULL ,
`category`  int(11) NULL DEFAULT NULL ,
`percent`  decimal(11,2) NULL DEFAULT NULL ,
`preset`  bit(1) NULL DEFAULT NULL ,
`reference_required`  bit(1) NULL DEFAULT NULL ,
`auto_sys_chg`  bit(1) NULL DEFAULT NULL ,
`seat_filter_exit`  bit(1) NULL DEFAULT NULL ,
`assume_entire_amount`  bit(1) NULL DEFAULT NULL ,
`not_with_seat`  bit(1) NULL DEFAULT NULL ,
`employee_meal`  bit(1) NULL DEFAULT b'0' ,
`discount_over_threshold`  bit(1) NULL DEFAULT NULL ,
`limit_discount`  bit(1) NULL DEFAULT NULL ,
`discount_last_item`  bit(1) NULL DEFAULT NULL ,
`single_seat`  bit(1) NULL DEFAULT NULL ,
`prorated_subtotal`  bit(1) NULL DEFAULT NULL ,
`select_discount`  bit(1) NULL DEFAULT NULL ,
`period_class_id`  int(11) NULL DEFAULT NULL ,
`rvc_class_id`  int(11) NULL DEFAULT NULL ,
`display_name`  char(60) NULL DEFAULT NULL ,
PRIMARY KEY (`discount_service_id`)
)
ENGINE=InnoDB

;

-- ----------------------------
-- Records of discount_service
-- ----------------------------
INSERT INTO discount_service VALUES ('2', null, '8.8折', '0', null, '6', '0', null, '0.00', null, null, '2', '12.00', '', null, null, null, '', null, '', null, null, null, null, null, '', null, null, ''), ('3', null, '8折', '0', null, '6', '0', null, '0.00', null, null, '2', '20.00', '', null, null, null, '', null, '', null, null, null, null, null, '', null, null, ''), ('4', null, '免单', '0', null, '0', '0', null, '0.00', null, null, '1', '100.00', '', null, null, null, '', null, '', null, null, null, null, null, '', null, null, ''), ('7', null, '自定折扣', '1', null, '1', '2', null, '0.00', null, null, '0', '0.00', '', null, null, null, '', null, '', null, null, null, null, null, '', null, null, ''), ('8', null, '抹零', '1', null, '6', '2', null, '0.00', null, null, '0', '0.00', '', null, null, null, '', null, '', null, null, null, null, null, '', null, null, ''), ('9', null, '员工折7折', '0', null, '1', '0', null, '0.00', null, null, '2', '30.00', '', null, null, null, '', null, '', null, null, null, null, null, '', null, null, '');

-- ----------------------------
-- Table structure for `employee`
-- ----------------------------
CREATE TABLE `employee` (
`employee_id`  int(11) NOT NULL ,
`employee_last_name`  varchar(40) NULL DEFAULT '' ,
`name_prefix`  varchar(20) NULL DEFAULT '' ,
`first_name`  varchar(20) NULL DEFAULT '' ,
`middle_name`  varchar(20) NULL DEFAULT '' ,
`name_suffix`  varchar(20) NULL DEFAULT '' ,
`previous_last_name`  varchar(20) NULL DEFAULT '' ,
`ssn_sin`  varchar(40) NULL DEFAULT '' ,
`password_id`  varchar(20) NULL DEFAULT '' ,
`pc_aps_id`  varchar(20) NULL DEFAULT '' ,
`payroll_id`  varchar(20) NULL DEFAULT '' ,
`employee_class`  int(11) NULL DEFAULT NULL ,
`back_office_class`  int(11) NULL DEFAULT NULL ,
`revenue_center`  int(11) NULL DEFAULT NULL ,
`is_in_traning`  bit(1) NULL DEFAULT b'0' ,
`is_minor`  bit(1) NULL DEFAULT b'0' ,
`cash_drawer`  int(11) NULL DEFAULT NULL ,
`late_clock`  int(11) NULL DEFAULT 0 ,
`lds_id`  int(11) NULL DEFAULT NULL ,
`cashier`  int(11) NULL DEFAULT NULL ,
`language_id`  int(11) NULL DEFAULT NULL ,
`start_date`  datetime NULL DEFAULT NULL ,
`end_date`  datetime NULL DEFAULT NULL ,
`job_rates`  int(11) NULL DEFAULT NULL ,
`check_name`  varchar(40) NULL DEFAULT '' ,
`image`  varchar(256) NULL DEFAULT '' ,
`front_password`  varchar(40) NULL DEFAULT '' ,
`back_password`  varchar(40) NULL DEFAULT '' ,
`period_class_id`  int(11) NULL DEFAULT NULL ,
`rvc_class_id`  int(11) NULL DEFAULT NULL ,
`commission`  float NULL DEFAULT 0 ,
PRIMARY KEY (`employee_id`)
)
ENGINE=InnoDB

;

-- ----------------------------
-- Records of employee
-- ----------------------------
INSERT INTO employee VALUES ('101', '员工1', '', '', '', '', '', '', '', '', '', '5', null, null, '', '', null, '0', null, null, null, null, '2016-12-13 15:46:46', null, '', '', '', '', null, null, '0'), ('102', '店长', '', '', '', '', '', '', '', '', '', '2', null, null, '', '', null, '0', null, null, null, null, '2016-12-13 15:46:46', null, '', '', '', '', null, null, '0'), ('105', '收银2', '', '', '', '', '', '', '', '', '', '4', null, null, '', '', null, '0', null, null, null, null, '2016-12-13 15:46:46', null, '', '', '', '', null, null, '0'), ('106', '收银1', '', '', '', '', '', '', '', '', '', '4', null, null, '', '', null, '0', null, null, null, null, '2016-12-13 15:46:46', null, '', '', '', '', null, null, '0'), ('777', '财务', '', '', '', '', '', '', '279', '00123', '', '1', null, null, '', '', null, '0', null, null, null, null, '2016-12-13 15:46:46', null, '', '', '', '', null, null, '0'), ('888', '测试帐号', '', '', '', '', '', '', '', '', '', '3', null, null, '', '', null, '0', null, null, null, null, '2016-12-13 15:46:46', null, '测试帐号', '', '', '', null, null, '0'), ('999', '999', '', '', '', '', '', '', '', '', '', '99', null, null, '', '', null, '0', null, null, null, null, '2016-12-13 15:46:46', null, '', '', '', '', null, null, '0');

-- ----------------------------
-- Table structure for `employee_class`
-- ----------------------------
CREATE TABLE `employee_class` (
`employee_class_id`  int(11) NOT NULL ,
`employee_class_number`  int(11) NULL DEFAULT NULL ,
`employee_class_name`  varchar(40) NULL DEFAULT NULL ,
`menu_item_privilege`  int(11) NULL DEFAULT NULL ,
`void_item`  bit(1) NULL DEFAULT NULL ,
`edit_check`  bit(1) NULL DEFAULT NULL ,
`trans_table`  bit(1) NULL DEFAULT NULL ,
`payment`  int(11) NULL DEFAULT NULL ,
`refund`  bit(1) NULL DEFAULT NULL ,
`report_edit`  bit(1) NULL DEFAULT NULL ,
`void_preorder`  bit(1) NULL DEFAULT b'0' ,
`manager_privilege`  int(11) NULL DEFAULT NULL ,
`move_check`  bit(1) NULL DEFAULT NULL ,
`split_check`  bit(1) NULL DEFAULT NULL ,
`send_order`  bit(1) NULL DEFAULT NULL ,
`print_prestatement`  bit(1) NULL DEFAULT NULL ,
`open_item`  bit(1) NULL DEFAULT NULL ,
`reprice`  bit(1) NULL DEFAULT NULL ,
`edit_checkname`  bit(1) NULL DEFAULT NULL ,
`print_bill`  bit(1) NULL DEFAULT NULL ,
`preorder`  int(1) NULL DEFAULT 0 ,
`open_drawer`  int(11) NULL DEFAULT NULL ,
`reprint_check`  bit(1) NULL DEFAULT NULL ,
`end_of_day`  bit(1) NULL DEFAULT NULL ,
`delete_check`  bit(1) NULL DEFAULT NULL ,
`shift`  bit(1) NULL DEFAULT NULL ,
`vip_card`  bit(1) NULL DEFAULT NULL ,
`report_view`  int(11) NULL DEFAULT NULL ,
`menu_item`  bit(1) NULL DEFAULT NULL ,
`is_order`  bit(1) NULL DEFAULT b'0' ,
`edit_customer`  bit(1) NULL DEFAULT b'0' ,
`change_setting`  bit(1) NULL DEFAULT NULL ,
`del_employee_pwd`  bit(1) NULL DEFAULT NULL ,
`open_menu_item`  bit(1) NULL DEFAULT NULL ,
`open_config`  bit(1) NULL DEFAULT NULL ,
`open_employee_info`  bit(1) NULL DEFAULT NULL ,
`open_employee_class`  bit(1) NULL DEFAULT NULL ,
`authority_1`  bit(1) NULL DEFAULT NULL ,
`authority_2`  bit(1) NULL DEFAULT NULL ,
`authority_3`  bit(1) NULL DEFAULT NULL ,
`authority_4`  bit(1) NULL DEFAULT NULL ,
`authority_5`  bit(1) NULL DEFAULT NULL ,
`authority_6`  bit(1) NULL DEFAULT NULL ,
`authority_7`  bit(1) NULL DEFAULT NULL ,
`authority_8`  bit(1) NULL DEFAULT NULL ,
`authority_9`  bit(1) NULL DEFAULT NULL ,
`authority_10`  bit(1) NULL DEFAULT NULL ,
`authority_11`  int(1) NULL DEFAULT NULL ,
`authority_12`  int(1) NULL DEFAULT NULL ,
`authority_13`  int(1) NULL DEFAULT NULL ,
`authority_14`  int(1) NULL DEFAULT NULL ,
`authority_15`  int(1) NULL DEFAULT NULL ,
PRIMARY KEY (`employee_class_id`)
)
ENGINE=InnoDB

;

-- ----------------------------
-- Records of employee_class
-- ----------------------------
INSERT INTO employee_class VALUES ('1', null, '管理员', null, '', '', '', '3', '', '', '', '3', '', '', '', '', '', '', '', '', '3', '1', '', '', '', '', null, '1', null, '', '', null, null, '', '', '', '', '', '', '', '', null, null, null, null, null, null, '2000', '100', null, null, null), ('2', null, '店长', '1', '', '', '', '3', '', '', '', '3', '', '', '', '', '', '', '', '', '3', '1', '', '', '', '', '', '1', null, '', '', '', '', '', '', '', '', '', '', '', '', null, null, null, null, null, null, '1000', '100', null, null, null), ('3', null, '经理', null, '', '', '', '2', '', '', '', '2', '', '', '', '', '', '', '', '', '3', '0', '', '', '', '', null, '1', null, '', '', null, null, '', '', '', '', '', '', '', '', null, null, null, null, null, null, '200', '100', null, null, null), ('4', null, '收银', null, '', '', '', '3', '', '', '', '2', '', '', '', '', '', '', '', '', '3', '1', '', '', '', '', null, '1', null, '', '', null, null, '', '', '', '', '', '', '', '', null, null, null, null, null, null, '200', '100', null, null, null), ('5', null, '普通员工', null, '', '', '', '0', '', '', '', '0', '', '', '', '', '', '', '', '', '0', '0', '', '', '', '', null, '0', null, '', '', null, null, '', '', '', '', '', '', '', '', null, null, null, null, null, null, '20', '100', null, null, null), ('99', '99', 'master', '3', '', '', '', '3', '', '', '', '3', '', '', '', '', '', '', '', '', '3', '1', '', '', '', '', '', '1', '', '', '', '', '', '', '', '', '', '', '', '', '', '', '', '', '', '', '', '99999', '100', '10', '10', '10');

-- ----------------------------
-- Table structure for `evaluation`
-- ----------------------------
CREATE TABLE `evaluation` (
`evaluation_id`  int(11) NOT NULL AUTO_INCREMENT ,
`menu_item_id`  int(11) NOT NULL ,
`menu_item_name`  varchar(40) NULL DEFAULT NULL ,
`evaluation_type`  int(11) NULL DEFAULT 0 ,
`evaluation_score`  float NULL DEFAULT 0 ,
`evaluation_content`  varchar(300) NULL DEFAULT '' ,
`customer_id`  varchar(40) NULL DEFAULT '0' ,
`customer_name`  varchar(40) NULL DEFAULT '' ,
`evaluation_time`  datetime NULL DEFAULT NULL ,
`extend_1`  varchar(40) NULL DEFAULT '' ,
`extend_2`  varchar(40) NULL DEFAULT '' ,
`extend_3`  varchar(40) NULL DEFAULT '' ,
`extend_4`  int(11) NULL DEFAULT NULL ,
`extend_5`  int(11) NULL DEFAULT NULL ,
PRIMARY KEY (`evaluation_id`)
)
ENGINE=InnoDB
AUTO_INCREMENT=1

;

-- ----------------------------
-- Records of evaluation
-- ----------------------------

-- ----------------------------
-- Table structure for `family_group`
-- ----------------------------
CREATE TABLE `family_group` (
`family_group_id`  int(11) NOT NULL DEFAULT 0 ,
`family_group_name`  varchar(40) NULL DEFAULT NULL ,
PRIMARY KEY (`family_group_id`)
)
ENGINE=InnoDB

;

-- ----------------------------
-- Records of family_group
-- ----------------------------
INSERT INTO family_group VALUES ('2', '果汁'), ('3', '奶茶'), ('4', '咖啡'), ('5', '花果中国茶'), ('6', '甜品'), ('7', '酒水'), ('8', '凉菜'), ('9', '川菜'), ('10', '粤菜'), ('11', '西餐'), ('12', '时蔬'), ('13', '调味品'), ('14', '粥品'), ('15', '饭面'), ('16', '套餐'), ('17', '靓汤'), ('18', '其他');

-- ----------------------------
-- Table structure for `history_card`
-- ----------------------------
CREATE TABLE `history_card` (
`id`  int(11) NOT NULL AUTO_INCREMENT ,
`old_card_id`  varchar(40) NULL DEFAULT NULL ,
`new_card_id`  varchar(40) NULL DEFAULT NULL ,
`employee_id`  int(11) NULL DEFAULT NULL ,
`employee_name`  varchar(60) NULL DEFAULT NULL ,
`time`  datetime NULL DEFAULT NULL ,
`extend_1`  varchar(40) NULL DEFAULT NULL ,
PRIMARY KEY (`id`)
)
ENGINE=InnoDB
AUTO_INCREMENT=1

;

-- ----------------------------
-- Records of history_card
-- ----------------------------

-- ----------------------------
-- Table structure for `history_day_end`
-- ----------------------------
CREATE TABLE `history_day_end` (
`history_day_end_id`  int(11) NOT NULL AUTO_INCREMENT ,
`day`  date NOT NULL ,
`rvc_center_id`  int(11) NOT NULL ,
`period_id`  int(11) NOT NULL ,
`eidt_time`  datetime NULL DEFAULT NULL ,
`sales_amount`  decimal(11,2) NULL DEFAULT NULL ,
`discount_amount`  decimal(11,2) NULL DEFAULT NULL ,
`service_amount`  decimal(11,2) NULL DEFAULT NULL ,
`return_amount`  decimal(11,2) NULL DEFAULT NULL ,
`should_amount`  decimal(11,2) NULL DEFAULT NULL ,
`actual_amount`  decimal(11,2) NULL DEFAULT NULL ,
`eatin_amount`  decimal(11,2) NULL DEFAULT NULL ,
`out_amount`  decimal(11,2) NULL DEFAULT NULL ,
`invoice_amount`  decimal(11,2) NULL DEFAULT NULL ,
`tax_amount`  decimal(11,2) NULL DEFAULT NULL ,
`customer_num`  int(11) NULL DEFAULT NULL ,
`chk_num`  int(11) NULL DEFAULT NULL ,
`table_num`  int(11) NULL DEFAULT NULL ,
PRIMARY KEY (`history_day_end_id`)
)
ENGINE=InnoDB
AUTO_INCREMENT=1

;

-- ----------------------------
-- Records of history_day_end
-- ----------------------------

-- ----------------------------
-- Table structure for `history_major_group`
-- ----------------------------
CREATE TABLE `history_major_group` (
`history_major_id`  int(11) NOT NULL AUTO_INCREMENT ,
`day`  date NOT NULL ,
`rvc_center_id`  int(11) NOT NULL ,
`period_id`  int(11) NOT NULL ,
`major_group_id`  int(11) NULL DEFAULT NULL ,
`amount`  decimal(11,2) NULL DEFAULT NULL ,
PRIMARY KEY (`history_major_id`)
)
ENGINE=InnoDB
AUTO_INCREMENT=1

;

-- ----------------------------
-- Records of history_major_group
-- ----------------------------

-- ----------------------------
-- Table structure for `history_messages`
-- ----------------------------
CREATE TABLE `history_messages` (
`history_message_id`  int(11) NOT NULL AUTO_INCREMENT ,
`tel`  varchar(50) NULL DEFAULT NULL ,
`message_content`  varchar(1000) NULL DEFAULT NULL ,
`send_time`  datetime NULL DEFAULT NULL ,
`actual_time`  datetime NULL DEFAULT NULL ,
`type`  int(11) NULL DEFAULT 0 ,
`status`  int(11) NULL DEFAULT 0 ,
`user_id`  int(11) NULL DEFAULT NULL ,
`sender`  int(11) NULL DEFAULT NULL ,
`extend_1`  int(11) NULL DEFAULT NULL ,
`extend_2`  varchar(300) NULL DEFAULT NULL ,
`extend_3`  varchar(300) NULL DEFAULT NULL ,
`extend_4`  varchar(300) NULL DEFAULT NULL ,
`extend_5`  varchar(300) NULL DEFAULT NULL ,
PRIMARY KEY (`history_message_id`)
)
ENGINE=InnoDB
AUTO_INCREMENT=1

;

-- ----------------------------
-- Records of history_messages
-- ----------------------------

-- ----------------------------
-- Table structure for `history_order_detail`
-- ----------------------------
CREATE TABLE `history_order_detail` (
`order_detail_id`  int(11) NOT NULL ,
`order_head_id`  int(11) NULL DEFAULT NULL ,
`check_id`  int(11) NULL DEFAULT 1 ,
`menu_item_id`  int(11) NULL DEFAULT 0 ,
`menu_item_name`  varchar(60) NULL DEFAULT '' ,
`product_price`  float NULL DEFAULT 0 ,
`is_discount`  bit(1) NULL DEFAULT b'0' ,
`original_price`  float NULL DEFAULT NULL ,
`discount_id`  int(11) NULL DEFAULT 0 ,
`actual_price`  float NULL DEFAULT 0 ,
`is_return_item`  bit(1) NULL DEFAULT b'0' ,
`order_employee_id`  int(11) NULL DEFAULT 0 ,
`order_employee_name`  varchar(30) NULL DEFAULT '' ,
`pos_device_id`  int(11) NULL DEFAULT 0 ,
`pos_name`  varchar(30) NULL DEFAULT '' ,
`order_time`  datetime NULL DEFAULT NULL ,
`return_time`  datetime NULL DEFAULT NULL ,
`return_reason`  varchar(200) NULL DEFAULT '' ,
`unit`  varchar(30) NULL DEFAULT '' ,
`is_send`  bit(1) NULL DEFAULT b'0' ,
`condiment_belong_item`  int(11) NULL DEFAULT 0 ,
`quantity`  float NULL DEFAULT 0 ,
`eat_type`  int(11) NULL DEFAULT 1 ,
`auth_id`  int(11) NULL DEFAULT NULL ,
`auth_name`  varchar(40) NULL DEFAULT '' ,
`weight_entry_required`  bit(1) NULL DEFAULT NULL ,
`description`  char(100) NULL DEFAULT NULL ,
`n_service_type`  int(11) NULL DEFAULT NULL ,
`not_print`  int(11) NULL DEFAULT NULL ,
`seat_num`  int(11) NULL DEFAULT NULL ,
`discount_price`  float NULL DEFAULT NULL ,
`sales_amount`  float NULL DEFAULT NULL ,
`is_make`  int(11) NULL DEFAULT NULL ,
`print_class`  int(11) NULL DEFAULT NULL ,
`rush`  int(11) NULL DEFAULT 0 
)
ENGINE=InnoDB

;

-- ----------------------------
-- Records of history_order_detail
-- ----------------------------

-- ----------------------------
-- Table structure for `history_order_head`
-- ----------------------------
CREATE TABLE `history_order_head` (
`order_head_id`  int(11) NOT NULL ,
`check_number`  int(11) NULL DEFAULT NULL ,
`rvc_center_id`  int(11) NULL DEFAULT NULL ,
`rvc_center_name`  varchar(30) NULL DEFAULT NULL ,
`table_id`  int(11) NULL DEFAULT NULL ,
`table_name`  varchar(30) NULL DEFAULT NULL ,
`check_id`  int(11) NOT NULL DEFAULT 0 ,
`open_employee_id`  int(11) NULL DEFAULT NULL ,
`open_employee_name`  varchar(30) NULL DEFAULT NULL ,
`customer_num`  int(11) NULL DEFAULT NULL ,
`customer_id`  int(11) NULL DEFAULT 0 ,
`customer_name`  varchar(30) NULL DEFAULT NULL ,
`pos_device_id`  int(11) NULL DEFAULT NULL ,
`pos_name`  varchar(30) NULL DEFAULT NULL ,
`order_start_time`  datetime NULL DEFAULT NULL ,
`order_end_time`  datetime NULL DEFAULT NULL ,
`should_amount`  decimal(11,2) NULL DEFAULT NULL ,
`return_amount`  decimal(11,2) NULL DEFAULT NULL ,
`discount_amount`  decimal(11,2) NULL DEFAULT NULL ,
`actual_amount`  decimal(11,2) NULL DEFAULT NULL ,
`print_count`  int(11) NULL DEFAULT NULL ,
`status`  int(11) NULL DEFAULT NULL ,
`eat_type`  int(11) NULL DEFAULT NULL ,
`check_name`  varchar(30) NULL DEFAULT NULL ,
`original_amount`  decimal(11,2) NULL DEFAULT 0.00 ,
`service_amount`  decimal(11,2) NULL DEFAULT 0.00 ,
`edit_time`  datetime NULL DEFAULT NULL ,
`party_id`  int(11) NULL DEFAULT NULL ,
`edit_employee_name`  varchar(30) NULL DEFAULT NULL ,
`remark`  varchar(50) NULL DEFAULT NULL ,
`is_make`  int(11) NULL DEFAULT NULL ,
`delivery_info`  varchar(100) NULL DEFAULT NULL ,
`kds_show`  int(11) NULL DEFAULT 0 ,
`kds_time`  datetime NULL DEFAULT NULL ,
`tax_amount`  decimal(11,2) NULL DEFAULT NULL ,
`raw_talbe`  int(11) NULL DEFAULT 0 ,
`tips_amount`  decimal(11,2) NULL DEFAULT NULL ,
`member_discount`  decimal(11,2) NULL DEFAULT NULL 
)
ENGINE=InnoDB

;

-- ----------------------------
-- Records of history_order_head
-- ----------------------------

-- ----------------------------
-- Table structure for `history_payment`
-- ----------------------------
CREATE TABLE `history_payment` (
`history_payment_id`  int(11) NOT NULL AUTO_INCREMENT ,
`day`  date NOT NULL ,
`rvc_center_id`  int(11) NOT NULL ,
`period_id`  int(11) NOT NULL ,
`payment_id`  int(11) NULL DEFAULT NULL ,
`amount`  decimal(11,2) NULL DEFAULT NULL ,
PRIMARY KEY (`history_payment_id`)
)
ENGINE=InnoDB
AUTO_INCREMENT=1

;

-- ----------------------------
-- Records of history_payment
-- ----------------------------

-- ----------------------------
-- Table structure for `history_time_clock`
-- ----------------------------
CREATE TABLE `history_time_clock` (
`time_clock_id`  int(11) UNSIGNED NOT NULL AUTO_INCREMENT ,
`employee_id`  int(11) NULL DEFAULT NULL ,
`job_id`  int(11) NULL DEFAULT NULL ,
`clock_in_time`  datetime NULL DEFAULT NULL ,
`clock_out_time`  datetime NULL DEFAULT NULL ,
`duration`  time NULL DEFAULT NULL ,
`override_in_early`  int(11) NULL DEFAULT NULL ,
`override_in_late`  int(11) NULL DEFAULT NULL ,
`override_out_early`  int(11) NULL DEFAULT NULL ,
`override_out_late`  int(11) NULL DEFAULT NULL ,
PRIMARY KEY (`time_clock_id`)
)
ENGINE=InnoDB
AUTO_INCREMENT=1

;

-- ----------------------------
-- Records of history_time_clock
-- ----------------------------

-- ----------------------------
-- Table structure for `information_screens`
-- ----------------------------
CREATE TABLE `information_screens` (
`info_id`  int(11) NOT NULL ,
`info_number`  int(11) NULL DEFAULT NULL ,
`info_name`  varchar(100) NULL DEFAULT NULL ,
`line1`  varchar(100) NULL DEFAULT NULL ,
`line2`  varchar(100) NULL DEFAULT NULL ,
`line3`  varchar(100) NULL DEFAULT NULL ,
`line4`  varchar(100) NULL DEFAULT NULL ,
`line5`  varchar(100) NULL DEFAULT NULL ,
`line6`  varchar(100) NULL DEFAULT NULL ,
`line7`  varchar(100) NULL DEFAULT NULL ,
`line8`  varchar(100) NULL DEFAULT NULL ,
`line9`  varchar(100) NULL DEFAULT NULL ,
`line10`  varchar(100) NULL DEFAULT NULL ,
PRIMARY KEY (`info_id`)
)
ENGINE=InnoDB

;

-- ----------------------------
-- Records of information_screens
-- ----------------------------
INSERT INTO information_screens VALUES ('1', null, '***帮助信息***', '1.如何登录进入系统', '2.输入用户名+密码, 默认输入999', '3.按‘确定’键或‘登录’键', null, null, null, null, null, null, null);

-- ----------------------------
-- Table structure for `inventory_setting`
-- ----------------------------
CREATE TABLE `inventory_setting` (
`setting_id`  int(11) NOT NULL AUTO_INCREMENT ,
`ip_addr`  varchar(60) NULL DEFAULT NULL ,
`port`  int(11) NULL DEFAULT 8000 ,
PRIMARY KEY (`setting_id`)
)
ENGINE=InnoDB
AUTO_INCREMENT=2

;

-- ----------------------------
-- Records of inventory_setting
-- ----------------------------
INSERT INTO inventory_setting VALUES ('1', 'stock.sandypos.com', '8000');

-- ----------------------------
-- Table structure for `invoices`
-- ----------------------------
CREATE TABLE `invoices` (
`invoice_id`  int(11) NOT NULL AUTO_INCREMENT ,
`order_head_id`  int(11) NULL DEFAULT NULL ,
`check_id`  int(11) NULL DEFAULT NULL ,
`invoice_number`  varchar(30) NULL DEFAULT NULL ,
`amount`  decimal(10,0) NULL DEFAULT NULL ,
`employee_id`  int(11) NULL DEFAULT NULL ,
`remark`  varchar(30) NULL DEFAULT NULL ,
`edit_time`  datetime NULL DEFAULT NULL ,
`pos_device_id`  int(11) NULL DEFAULT NULL ,
`rvc_center_id`  int(11) NULL DEFAULT NULL ,
PRIMARY KEY (`invoice_id`)
)
ENGINE=InnoDB
AUTO_INCREMENT=1

;

-- ----------------------------
-- Records of invoices
-- ----------------------------

-- ----------------------------
-- Table structure for `item_main_group`
-- ----------------------------
CREATE TABLE `item_main_group` (
`main_group_id`  int(11) NOT NULL ,
`main_group_name`  varchar(30) NULL DEFAULT NULL ,
`second_group_id`  int(11) NOT NULL ,
PRIMARY KEY (`main_group_id`, `second_group_id`)
)
ENGINE=InnoDB

;

-- ----------------------------
-- Records of item_main_group
-- ----------------------------
INSERT INTO item_main_group VALUES ('1', '饮品', '-1'), ('1', '饮品', '10'), ('1', '饮品', '12'), ('3', '西式风味', '-1'), ('3', '西式风味', '30'), ('9', '自定义菜', '-1'), ('9', '自定义菜', '91'), ('9999', '回收站', '-1'), ('9999', '回收站', '9999');

-- ----------------------------
-- Table structure for `item_unit`
-- ----------------------------
CREATE TABLE `item_unit` (
`unit_id`  int(11) NOT NULL AUTO_INCREMENT ,
`unit_name`  varchar(30) NULL DEFAULT NULL ,
PRIMARY KEY (`unit_id`)
)
ENGINE=InnoDB
AUTO_INCREMENT=32

;

-- ----------------------------
-- Records of item_unit
-- ----------------------------
INSERT INTO item_unit VALUES ('1', '例'), ('2', '位'), ('3', '碗'), ('4', '条'), ('5', '只'), ('6', '半只'), ('7', '斤'), ('8', '一打'), ('9', '半打'), ('10', '个'), ('11', '份'), ('12', '笼'), ('13', '件'), ('14', '听'), ('15', '瓶'), ('16', '杯'), ('17', '扎'), ('18', '大扎'), ('19', '小扎'), ('20', '盒'), ('21', '球'), ('22', '壶'), ('23', '大壶'), ('24', '中壶'), ('25', '小壶'), ('26', '套'), ('27', '热'), ('28', '冷'), ('29', '大'), ('30', '中'), ('31', '小');

-- ----------------------------
-- Table structure for `macros`
-- ----------------------------
CREATE TABLE `macros` (
`macros_id`  int(11) NOT NULL DEFAULT 0 ,
`macros_name`  varchar(40) NULL DEFAULT NULL ,
`macros_value`  varchar(200) NULL DEFAULT NULL ,
`remark`  varchar(600) NULL DEFAULT NULL ,
PRIMARY KEY (`macros_id`)
)
ENGINE=InnoDB

;

-- ----------------------------
-- Records of macros
-- ----------------------------
INSERT INTO macros VALUES ('1', 'MAX_TABLE_NUM', '200', '最大桌号'), ('2', 'MAX_ITEM_QUANTITY', '50', '最大数量'), ('3', 'MAX_ITEM_WEIGHT', '50', '最大重量'), ('4', 'MAX_GUEST_NUM', '20', '最大客人数'), ('5', 'PREORDER_WARNING_HOUR', '5', '当前桌子在该值小时内有其他预订时，提醒'), ('6', 'EXIT_AFTER_SEND', '1', '下单后的行为：0- 不跳转；1- 跳转到桌位；2- 跳转到登陆界面'), ('7', 'PRINT_TRANS', '1', '转台打印：0 -不打印 1 -打印'), ('8', 'EXIT_AFTER_PAY', '1', '付款后的行为：0- 不跳转；1- 跳转到桌位；2- 跳转到登陆界面'), ('9', 'HEAD_BEGIN_ID', '1000', '账单头order_head的起始ID'), ('10', 'COMBINE_ONE_CHECK', '1', '合台，合单时：  0 -合并到不同的单； 1 -合并到第一张单'), ('11', 'ROUND_ITEM_TTLPRICE', '0', '1 -计算单个菜品总价时四舍五入 ； 0 -不舍入'), ('13', 'NO_AUTO_COMBINE', '0', '0 -点菜时自动合并   1 -取消自动合并，一个菜一栏'), ('14', 'COMBINE_PAYITEM', '1', '0 -不合并   1 -结帐单自动合并菜品'), ('15', 'COMBINE_SENDITEM', '0', '0 -不合并   1 -厨房单自动合并菜品'), ('16', 'NOPRINT_VOID', '0', '0 -退菜打印   1 -退菜不打印'), ('18', 'FORCE_MINLIMIT', '1', '消费限制是否强制 0 -否   1 -是'), ('19', 'PAYMENT_ORDER', '0', '结账单菜品打印顺序 0 -点菜顺序   1 -按报表子类排序 2 -菜品价格排序 3-报表子类排序并打印分类小计'), ('20', 'SENDITEM_ORDER', '0', '送厨单菜品打印顺序 0 -点菜顺序   1 -按报表子类分类'), ('21', 'SYNC_PAD_PDA', '0', '在编辑菜单后是否同步到平板和PDA\r\n0：不同步\r\n1:同步'), ('22', 'USE_SALE_TIME', '1', '是否使用营业开始时间\r\n0：不使用，每天时间从0:00:00到23:59:59\r\n1:使用，每天时间从第一天的开始时间到第二天的开始时间'), ('23', 'PRINT_VIPINFO', '1', '0 -不打印   1 -结帐单打印会员信息'), ('24', 'PRINT_ALLMAKEITEM', '0', '划菜单是否打印整单菜品\n 0 -不打印   1 -打印'), ('25', 'PAYMENT_CHANGE_TIME', '8', '提示找零的时间(秒)，小于等于0则不倒计时'), ('27', 'SALES_REPORT_TYPE', '111', '前台销售总结报表内容,每一位为1表示开启报表\r\n个位: 分段销量\r\n十位: 大类销量\r\n百位: 部门销量'), ('29', 'SHOW_ITEM_ID', '0', '点菜界面显示菜品ID\r\n0 :不显示\r\n1 :显示\n '), ('30', 'DISCOUNT_TYPE', '2', '废弃'), ('32', 'NO_AUTO_CLOSECHK', '0', '是否自动关闭空白账单  0-自动关闭 1-不自动'), ('33', 'PRINTCHK_TWICE', '0', '收银小票打印次数：0 -1次；1 -2次；2 -提示是否打印'), ('34', 'NOPRINT_PDA', '0', 'PDA点菜配置为不送厨'), ('35', 'AUTO_PRINT_ORDER', '0', '送厨后自动打印划菜单'), ('36', 'TABLE_UPDATE_TIMER', '10', '桌台界面刷新间隔时间(秒)'), ('37', 'PRINT_SERVICE_DETAIL', '1', '收银小票是否打印服务费明细'), ('38', 'DZDP_ID', '0', '大众点评ID'), ('39', 'NO_AUTO_CUSTOMER', '0', '外卖单是否自动弹出常客：0-自动弹出  1-不自动'), ('40', 'PRINT_WEBVIPID', '0', '会员打折卡打印卡号：0-不打印  1-打印'), ('41', 'MAP_ENGINE', 'http://api.map.baidu.com/geocoder?output=html&src=coolroid&address=', '地图搜索URL'), ('42', 'NOT_CLEAN_TABLE', '0', '付款后是否自动清台：0-清台  1-不清台'), ('43', 'NOT_PRINT_FREEITEM', '0', '不打印单价为0菜品：0-  1-不打印'), ('44', 'NO_SOLDOUT_ITEM', '0', '沽清菜品不可点：0-提示  1-不可点'), ('45', 'COMBINE_CONDIMENT', '0', '带价格调味品打印时合并到菜品备注：0-不合并  1-合并'), ('46', 'FOOD_COURT', '0', ''), ('47', 'NO_SEND_HINT', '0', '未送厨时是否提示：0-提示  1-不提示'), ('48', 'SHOW_CONSUMPTION_LIMIT', '0', '开台时是否显示最低消费提示：0-不显示  1-显示'), ('49', 'SHIFT_MAJORSALES', '0', '在交班报表中显示大类销售统计，用于奶茶店'), ('50', 'SHOW_ITEM_NAME', '0', '菜名显示效果： 0-显示名称1+名称2；1-仅显示名称1；2-仅显示名称2'), ('51', 'REPRICE_TOTAL', '1', '菜品改价：0-改单价  1-直接改总价'), ('52', 'OPEN_TABLE_GUEST', '0', '开台输入人数效果: 0-默认 1-不显示人数输入框 2-人数强制输入，不能为零'), ('53', 'PRINT_VOID_PAY', '0', '结帐单打印退菜：0-不打印  1-打印'), ('54', 'PRINT_DISCOUNT_SEPARATE', '1', '收银小票是否打印折扣明细'), ('55', 'PRINT_SHIFT_TWICE', '0', '交班小票是否打印2次'), ('56', 'PRINT_MEMBER_TWICE', '0', '会员小票是否打印2次'), ('57', 'PRINT_COURSE_COMBINE', '0', '送厨单套餐在一张单打印'), ('58', 'EFT_NO_PRINT', '0', '取消EFT打印：1-不打印'), ('59', 'TIPS_SUGGEST', '15,18,20', '建议小费比例用,逗号分隔'), ('60', 'ITEM_ICON_STYLE', '0', '菜单图片显示风格:0- 菜名在图片底部 1- 菜名居中');

-- ----------------------------
-- Table structure for `major_group`
-- ----------------------------
CREATE TABLE `major_group` (
`major_group_id`  int(11) NOT NULL DEFAULT 0 ,
`major_group_name`  varchar(40) NULL DEFAULT NULL ,
PRIMARY KEY (`major_group_id`)
)
ENGINE=InnoDB

;

-- ----------------------------
-- Records of major_group
-- ----------------------------
INSERT INTO major_group VALUES ('1', '吧台'), ('2', '外场'), ('3', '厨房'), ('4', '其他');

-- ----------------------------
-- Table structure for `menu_item`
-- ----------------------------
CREATE TABLE `menu_item` (
`item_id`  int(11) NOT NULL ,
`item_name1`  varchar(60) NULL DEFAULT NULL ,
`item_name2`  varchar(60) NULL DEFAULT NULL ,
`icon`  varchar(512) NULL DEFAULT NULL ,
`slu_id`  int(11) NULL DEFAULT NULL ,
`nlu`  varchar(20) NULL DEFAULT NULL ,
`class_id`  int(11) NULL DEFAULT NULL ,
`print_class`  int(11) NULL DEFAULT NULL ,
`item_type`  int(11) NULL DEFAULT 0 ,
`allow_condiment`  int(11) NULL DEFAULT NULL ,
`required_condiment`  int(11) NULL DEFAULT 0 ,
`check_availability`  bit(1) NULL DEFAULT NULL ,
`no_access_mgr`  bit(1) NULL DEFAULT NULL ,
`major_group`  int(11) NULL DEFAULT NULL ,
`family_group`  int(11) NULL DEFAULT NULL ,
`price_1`  float NULL DEFAULT 0 ,
`cost_1`  float NULL DEFAULT 0 ,
`unit_1`  varchar(30) NULL DEFAULT '' ,
`date_from_1`  date NULL DEFAULT NULL ,
`date_to_1`  date NULL DEFAULT NULL ,
`surcharge_1`  float NULL DEFAULT 0 ,
`tare_weight_1`  float NULL DEFAULT 0 ,
`price_2`  float NULL DEFAULT 0 ,
`cost_2`  float NULL DEFAULT 0 ,
`unit_2`  varchar(30) NULL DEFAULT '' ,
`date_from_2`  date NULL DEFAULT NULL ,
`date_to_2`  date NULL DEFAULT NULL ,
`surcharge_2`  float NULL DEFAULT 0 ,
`tare_weight_2`  float NULL DEFAULT 0 ,
`price_3`  float NULL DEFAULT 0 ,
`cost_3`  float NULL DEFAULT 0 ,
`unit_3`  varchar(30) NULL DEFAULT '' ,
`date_from_3`  date NULL DEFAULT NULL ,
`date_to_3`  date NULL DEFAULT NULL ,
`surcharge_3`  float NULL DEFAULT 0 ,
`tare_weight_3`  float NULL DEFAULT 0 ,
`price_4`  float NULL DEFAULT 0 ,
`cost_4`  float NULL DEFAULT 0 ,
`unit_4`  varchar(30) NULL DEFAULT '' ,
`date_from_4`  date NULL DEFAULT NULL ,
`date_to_4`  date NULL DEFAULT NULL ,
`surcharge_4`  float NULL DEFAULT 0 ,
`tare_weight_4`  float NULL DEFAULT 0 ,
`price_5`  float NULL DEFAULT 0 ,
`cost_5`  float NULL DEFAULT 0 ,
`unit_5`  varchar(30) NULL DEFAULT '' ,
`date_from_5`  date NULL DEFAULT NULL ,
`date_to_5`  date NULL DEFAULT NULL ,
`surcharge_5`  float NULL DEFAULT 0 ,
`tare_weight_5`  float NULL DEFAULT NULL ,
`slu_priority`  int(11) NULL DEFAULT 0 ,
`period_class_id`  int(11) NULL DEFAULT 0 ,
`rvc_class_id`  int(11) NULL DEFAULT 0 ,
`commission_type`  int(11) NULL DEFAULT 0 ,
`commission_value`  float NULL DEFAULT 0 ,
`ticket_class`  int(11) NULL DEFAULT 1 ,
`tax_group`  int(11) NULL DEFAULT '-1' ,
`is_time_price`  tinyint(4) NULL DEFAULT 0 ,
`price_per_minute`  int(11) NULL DEFAULT 60 ,
PRIMARY KEY (`item_id`)
)
ENGINE=InnoDB

;

-- ----------------------------
-- Records of menu_item
-- ----------------------------
INSERT INTO menu_item VALUES ('1', '宴会', '', '', '91', 'YH', '6', '11', '4', null, '-1', '', '', '-1', '18', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, '2099-01-01', '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('2', '厨房自定义', '', null, '91', 'CFZDY', '6', '11', '4', null, '-1', null, null, '-1', '18', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, '2099-01-01', '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('3', '吧台自定义', '', null, '91', 'BTZDY', '6', '11', '4', null, '-1', null, null, '-1', '18', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, '2099-01-01', '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('1009', '皇家咖啡', '', null, '12', 'HJKF', '6', '11', '0', null, '-1', null, null, '1', '4', '32', '0', '热', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('1014', '爱尔兰咖啡', '', '', '12', 'AELKF', '6', '11', '0', null, '-1', '', '', '1', '4', '32', '0', '热', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('1015', '卡布基诺咖啡', '', '', '12', 'KBJNKF', '6', '11', '0', null, '-1', '', '', '1', '4', '32', '0', '热', null, null, '0', '0', '35', '0', '冷', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('1016', '拿铁咖啡', '', '', '12', 'NTKF', '6', '11', '0', null, '-1', '', '', '1', '4', '32', '0', '热', null, null, '0', '0', '35', '0', '冷', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('1017', '椰香咖啡', '', '', '12', 'YXKF', '6', '11', '0', null, '-1', '', '', '1', '4', '32', '0', '热', null, null, '0', '0', '35', '0', '冷', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('1029', '比利时极品蓝山', '', null, '10', 'BLSJPLS', '6', '11', '0', null, '-1', null, null, '1', '4', '128', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, '2099-01-01', '0', null, '0', '0', '0', '1', '2', '1', '-1', '0', '60'), ('1088', '比利时蓝山', '', null, '10', 'BLSLS', '6', '11', '0', null, '-1', null, null, '1', '4', '78', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, '2099-01-01', '0', null, '0', '0', '0', '1', '2', '1', '-1', '0', '60'), ('1089', '比利时风味', '', null, '10', 'BLSFW', '6', '11', '0', null, '-1', null, null, '1', '4', '78', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, '2099-01-01', '0', null, '0', '0', '0', '1', '2', '1', '-1', '0', '60'), ('1392', '扑克', '', null, '10', 'PK', '6', '11', '0', null, '-1', null, null, '1', '4', '15', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6000', '等叫', null, null, '-1', 'DJ', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6001', '剁椒', null, null, '-1', 'DJ', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6002', '榄角', null, null, '-1', 'LJ', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6003', '豆豉', null, null, '-1', 'DC', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6004', '加急', '', null, '-1', 'JJ', '-1', '-1', '1', null, '-1', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, '2099-01-01', '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6005', '回民忌口', '', null, '-1', 'HMJK', '-1', '-1', '1', null, '-1', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, '2099-01-01', '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6006', '芥末', null, null, '-1', 'JM', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6007', '糖', '', null, '-1', 'T', '-1', '-1', '1', null, '-1', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, '2099-01-01', '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6008', '少放味精', '', null, '-1', 'SFWJ', '-1', '-1', '1', null, '-1', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, '2099-01-01', '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6009', '豆瓣酱', null, null, '-1', 'DBJ', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6012', '桂林酱', null, null, '-1', 'GLJ', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6013', '虾酱', null, null, '-1', 'XJ', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6014', '花生酱', null, null, '-1', 'HSJ', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6015', '牛油', null, null, '-1', 'NY', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6016', '铁板出', null, null, '-1', 'TBC', '6', null, '1', null, '0', null, null, '4', '-1', '5', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6017', '冷盘出', null, null, '-1', 'LPC', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6018', '牛扒套餐出', null, null, '-1', 'NBTCC', '6', null, '1', null, '0', null, null, '4', '-1', '15', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6019', '摩卡', null, null, '-1', 'MK', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6020', '巴西', null, null, '-1', 'BX', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6021', '炭烧', null, null, '-1', 'TS', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6022', '曼特宁', null, null, '-1', 'MTN', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6023', '哥伦比亚', null, null, '-1', 'GLBY', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6024', '芝士', null, null, '-1', 'ZS', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6026', '咖哩汁', null, null, '-1', 'KLZ', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6027', '免葱', null, null, '-1', 'MC', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6028', '免姜', null, null, '-1', 'MJ', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6029', '免蒜', null, null, '-1', 'MS', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6030', '免芫茜', null, null, '-1', 'MYQ', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6031', '免味精', null, null, '-1', 'MWJ', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6032', '免油', null, null, '-1', 'MY', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6033', '免芝麻', null, null, '-1', 'MZM', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6034', '免胡椒', null, null, '-1', 'MHJ', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6035', '免牛肉', null, null, '-1', 'MNR', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6036', '免肉片', null, null, '-1', 'MRP', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6037', '免豉油', null, null, '-1', 'MCY', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6038', '免醋', null, null, '-1', 'MC', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6039', '免糖', null, null, '-1', 'MT', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6040', 'XO酱', null, null, '-1', 'XOJ', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6041', '蒜蓉炒', null, null, '-1', 'SRC', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6042', '蒜蓉蒸', null, null, '-1', 'SRZ', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6043', '白灼', null, null, '-1', 'BZ', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6044', '清炒', null, null, '-1', 'QC', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6045', '指天椒', null, null, '-1', 'ZTJ', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6046', '胡椒', null, null, '-1', 'HJ', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6047', '蚝油', null, null, '-1', 'HY', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6048', '虎皮', null, null, '-1', 'HP', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6049', '清水浸', null, null, '-1', 'QSJ', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6050', '盐水浸', null, null, '-1', 'YSJ', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6051', '原味', null, null, '-1', 'YW', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6052', '豆豉鲮鱼', null, null, '-1', 'DCLYC', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6053', '姜汁炒', null, null, '-1', 'JZC', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6054', '煲淋', null, null, '-1', 'BL', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6055', '蒸酿', null, null, '-1', 'ZN', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6056', '浓汤', null, null, '-1', 'NT', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6057', '椒丝腐乳', null, null, '-1', 'JSFRC', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6058', '盐', null, null, '-1', 'Y', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6059', '上汤', null, null, '-1', 'ST', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6060', '蒜蓉', null, null, '-1', 'SR', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6061', '腐乳', null, null, '-1', 'FR', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6062', '咸蛋', null, null, '-1', 'XD', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6063', '味精', null, null, '-1', 'WJ', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6064', '蚝油', null, null, '-1', 'HY', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6065', '咖喱', null, null, '-1', 'KL', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6066', '鲍贝扒', null, null, '-1', 'BBB', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6067', '豆瓣酱炒', null, null, '-1', 'DBJC', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6068', '红烧', null, null, '-1', 'HS', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6069', '豉汁', null, null, '-1', 'CZ', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6070', '砂锅', null, null, '-1', 'SG', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6071', '猪肝浸', null, null, '-1', 'ZGJ', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6072', '虾酱炒', null, null, '-1', 'XJC', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6073', '滚粥', null, null, '-1', 'GZ', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6074', '葱段炒', null, null, '-1', 'CDC', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6075', '芝士焗', null, null, '-1', 'ZSJ', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6076', '麻油', null, null, '-1', 'MY', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6077', '西芹', null, null, '-1', 'XQ', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6078', '兰豆', null, null, '-1', 'LD', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6079', '生炒', null, null, '-1', 'SC', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6080', '鸡油炒', null, null, '-1', 'JYC', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6081', '窝蛋上汤', null, null, '-1', 'WDST', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6082', '百合', null, null, '-1', 'BH', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6083', '猪油渣炒', null, null, '-1', 'ZYZC', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6084', '腐乳', null, null, '-1', 'FR', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6085', '老干妈', null, null, '-1', 'LGM', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6086', '卤水', null, null, '-1', 'LS', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6087', '1至3人用', null, null, '-1', '1Z3RY', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6088', '3至6人用', null, null, '-1', '3Z6RY', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6089', '6至9人用', null, null, '-1', '6Z9RY', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6090', '9至12人用', null, null, '-1', '9Z12RY', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6091', '9成熟', null, null, '-1', '9CS', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60');
INSERT INTO menu_item VALUES ('6092', '8成熟', null, null, '-1', '8CS', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6093', '7成熟', null, null, '-1', '7CS', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6094', '6成熟', null, null, '-1', '6CS', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6095', '5成熟', null, null, '-1', '5CS', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6096', '全熟', null, null, '-1', 'QS', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6351', '清真', null, null, '-1', 'QZ', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6361', '清淡', null, null, '-1', 'QD', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6362', '偏咸', null, null, '-1', 'PX', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6363', '麻辣', null, null, '-1', 'ML', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6364', '香辣', null, null, '-1', 'XL', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6365', '小辣', null, null, '-1', 'XL', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6366', '中辣', null, null, '-1', 'ZL', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6367', '劲辣', null, null, '-1', 'JL', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6368', '煎香', null, null, '-1', 'JX', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6369', '生', null, null, '-1', 'S', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6370', '熟', null, null, '-1', 'S', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6371', '甜', null, null, '-1', 'T', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6372', '酸甜', null, null, '-1', 'ST', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6373', '酸辣', null, null, '-1', 'SL', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6374', '生上', null, null, '-1', 'SS', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6375', '免芡汁', null, null, '-1', 'MQZ', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6376', '浓', null, null, '-1', 'N', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6377', '多汁', null, null, '-1', 'DZ', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6378', '多汤', null, null, '-1', 'DT', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6379', '小汁', null, null, '-1', 'XZ', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6380', '大芡', null, null, '-1', 'DQ', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6381', '多油', null, null, '-1', 'DY', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6382', '小油', null, null, '-1', 'XY', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6383', '捞', null, null, '-1', 'L', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6385', '湿', null, null, '-1', 'S', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6386', '干', null, null, '-1', 'G', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6670', '老板用', null, null, '-1', 'LBY', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6671', '贵宾用', null, null, '-1', 'GBY', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6672', '快上', null, null, '-1', 'KS', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6673', '打包', null, null, '-1', 'DB', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6674', '手撕', null, null, '-1', 'SS', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6675', '斩件', null, null, '-1', 'ZJ', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6676', '切碎', null, null, '-1', 'QS', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6677', '切丁', null, null, '-1', 'QD', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6678', '切片', null, null, '-1', 'QP', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6679', '切丝', null, null, '-1', 'QS', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6680', '片皮', null, null, '-1', 'PP', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6681', '肥', null, null, '-1', 'F', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6682', '瘦', null, null, '-1', 'S', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6683', '半肥瘦', null, null, '-1', 'BFS', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6684', '原只上', null, null, '-1', 'YZS', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6685', '一起上', null, null, '-1', 'YQS', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6686', '分开上', null, null, '-1', 'FKS', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6687', '湿炒', null, null, '-1', 'SC', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6688', '干炒', null, null, '-1', 'GC', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6689', '冰冻', null, null, '-1', 'BD', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6690', '不冰冻', null, null, '-1', 'BBD', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6691', '去壳', null, null, '-1', 'QK', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6692', '去胆', null, null, '-1', 'QD', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6693', '去皮', null, null, '-1', 'QP', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6694', '20分钟后上', null, null, '-1', '20FZHS', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('6695', '30分钟后上', null, null, '-1', '30FZHS', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('7236', '黑椒汁', '', '', '-1', 'HJZ', '6', '-1', '1', null, '-1', '', '', '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('7237', '蘑菇汁', '', '', '-1', 'MGZ', '6', '-1', '1', null, '-1', '', '', '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('7238', '洋葱汁', '', '', '-1', 'YCZ', '6', '-1', '1', null, '-1', '', '', '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('7272', '番茄汁', '', '', '-1', 'FQZ', '6', '-1', '1', null, '-1', '', '', '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('7277', '蒜蓉汁', '', '', '-1', 'SRZ', '6', '-1', '1', null, '-1', '', '', '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('7282', '米饭', '', '', '-1', 'MF', '6', '-1', '1', null, '-1', '', '', '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60'), ('7283', '意粉', '', '', '-1', 'YF', '6', '-1', '1', null, '-1', '', '', '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1', '0', '60');

-- ----------------------------
-- Table structure for `menu_item_class`
-- ----------------------------
CREATE TABLE `menu_item_class` (
`item_class_id`  int(11) NOT NULL ,
`item_class_number`  int(11) NULL DEFAULT NULL ,
`item_class_name`  varchar(40) NULL DEFAULT NULL ,
`sale_itemizer`  int(11) NULL DEFAULT NULL ,
`discount_itemizer`  int(11) NULL DEFAULT NULL ,
`print_group`  int(11) NULL DEFAULT '-1' ,
`halo`  int(11) NULL DEFAULT NULL ,
`service_itemizer`  int(11) NULL DEFAULT NULL ,
`privilege`  int(11) NULL DEFAULT NULL ,
`appetizers`  bit(1) NULL DEFAULT NULL ,
`reference_required`  bit(1) NULL DEFAULT NULL ,
`beverages`  bit(1) NULL DEFAULT NULL ,
`weight_entry_required`  bit(1) NULL DEFAULT b'0' ,
`condiments`  bit(1) NULL DEFAULT NULL ,
`increment_seat_number`  bit(1) NULL DEFAULT NULL ,
`condiment_seat_number`  bit(1) NULL DEFAULT NULL ,
`condiments_prefixes`  bit(1) NULL DEFAULT NULL ,
`match_condiments_quantity`  bit(1) NULL DEFAULT NULL ,
`shareable`  bit(1) NULL DEFAULT NULL ,
`count_menu_item`  bit(1) NULL DEFAULT NULL ,
`lds_items`  bit(1) NULL DEFAULT NULL ,
`retail_items`  bit(1) NULL DEFAULT NULL ,
`include_in_repeat_round`  bit(1) NULL DEFAULT NULL COMMENT ' ' ,
PRIMARY KEY (`item_class_id`)
)
ENGINE=InnoDB

;

-- ----------------------------
-- Records of menu_item_class
-- ----------------------------
INSERT INTO menu_item_class VALUES ('1', null, '称重不打折收服务费', null, '0', '-1', null, '9', null, null, null, null, '', null, null, null, null, null, null, null, null, null, null), ('2', null, '称重打折收服务费', null, '9', '-1', null, '9', null, null, null, null, '', null, null, null, null, null, null, null, null, null, null), ('3', null, '不打折收服务费', null, '0', '-1', null, '9', null, null, null, null, '', null, null, null, null, null, null, null, null, null, null), ('4', null, '不打折不收服务费', null, '0', '-1', null, '0', null, null, null, null, '', null, null, null, null, null, null, null, null, null, null), ('5', null, '打折不收服务费', null, '9', '-1', null, '0', null, null, null, null, '', null, null, null, null, null, null, null, null, null, null), ('6', null, '打折收服务费', null, '9', '-1', null, '9', null, null, null, null, '', null, null, null, null, null, null, null, null, null, null), ('11', null, '称重不打折不收服务费', null, '0', '-1', null, '0', null, null, null, null, '', null, null, null, null, null, null, null, null, null, null), ('12', null, '称重打折不收服务费', null, '9', '-1', null, '0', null, null, null, null, '', null, null, null, null, null, null, null, null, null, null);

-- ----------------------------
-- Table structure for `messages`
-- ----------------------------
CREATE TABLE `messages` (
`message_id`  int(11) NOT NULL AUTO_INCREMENT ,
`tel`  varchar(50) NULL DEFAULT NULL ,
`message_content`  varchar(1000) NULL DEFAULT NULL ,
`send_time`  datetime NULL DEFAULT NULL ,
`type`  int(11) NULL DEFAULT 0 ,
`user_id`  int(11) NULL DEFAULT '-1' ,
`sender`  int(11) NULL DEFAULT '-1' ,
`extend_1`  int(11) NULL DEFAULT 0 ,
`extend_2`  varchar(300) NULL DEFAULT NULL ,
`extend_3`  varchar(300) NULL DEFAULT NULL ,
`extend_4`  varchar(300) NULL DEFAULT NULL ,
`extend_5`  varchar(300) NULL DEFAULT NULL ,
PRIMARY KEY (`message_id`)
)
ENGINE=InnoDB
AUTO_INCREMENT=1

;

-- ----------------------------
-- Records of messages
-- ----------------------------

-- ----------------------------
-- Table structure for `messages_template_item`
-- ----------------------------
CREATE TABLE `messages_template_item` (
`message_tempitem_id`  int(11) NOT NULL DEFAULT 0 ,
`message_tempitem_name`  varchar(50) NULL DEFAULT '' ,
`message_tempitem_content`  varchar(50) NULL DEFAULT '' ,
`column_value`  varchar(100) NULL DEFAULT '' ,
`type`  int(11) NULL DEFAULT 0 ,
PRIMARY KEY (`message_tempitem_id`)
)
ENGINE=InnoDB

;

-- ----------------------------
-- Records of messages_template_item
-- ----------------------------
INSERT INTO messages_template_item VALUES ('1', '预订名称', '#OrderName#', '', '0'), ('2', '开席时间', '#ArriveTime#', '', '0'), ('3', '客户名称', '#CustomerName#', '', '0'), ('4', '客户电话', '#CustomerTel#', '', '0'), ('5', '预订房台', '#TblName#', '', '0'), ('6', '预订席数', '#TblNum#', '', '0'), ('7', '备用席数', '#BackTblNum#', '', '0'), ('8', '预付订金', '#Prepay#', '', '0'), ('9', '每桌价格', '#PricePerTbl#', '', '0'), ('10', '备注', '#Remark#', '', '0');

-- ----------------------------
-- Table structure for `miti`
-- ----------------------------
CREATE TABLE `miti` (
`order_employee_id`  int(11) NULL DEFAULT NULL ,
`order_employee_name`  varchar(50) NULL DEFAULT NULL ,
`actual_price`  float NULL DEFAULT NULL ,
`quantity`  float NULL DEFAULT NULL ,
`commission_value`  float NULL DEFAULT NULL ,
`commission_type`  int(11) NULL DEFAULT NULL 
)
ENGINE=MEMORY

;

-- ----------------------------
-- Records of miti
-- ----------------------------

-- ----------------------------
-- Table structure for `msg_setting`
-- ----------------------------
CREATE TABLE `msg_setting` (
`setting_id`  int(11) NOT NULL DEFAULT 0 ,
`type`  int(11) NULL DEFAULT 0 ,
`com_port`  int(11) NULL DEFAULT 1 ,
`ip_address`  varchar(50) NULL DEFAULT NULL ,
`ip_port`  int(11) NULL DEFAULT NULL ,
`user_id`  varchar(50) NULL DEFAULT NULL ,
`user_pwd`  varchar(50) NULL DEFAULT NULL ,
`net_server`  varchar(500) NULL DEFAULT NULL ,
`net_user`  varchar(50) NULL DEFAULT NULL ,
`net_user_pwd`  varchar(50) NULL DEFAULT NULL ,
`cr_ip`  varchar(50) NULL DEFAULT '' ,
`cr_url`  varchar(100) NULL DEFAULT '' ,
`cr_port`  int(11) NULL DEFAULT 2001 ,
`cr_user`  varchar(50) NULL DEFAULT '' ,
`cr_user_pwd`  varchar(50) NULL DEFAULT '' ,
PRIMARY KEY (`setting_id`)
)
ENGINE=InnoDB

;

-- ----------------------------
-- Records of msg_setting
-- ----------------------------
INSERT INTO msg_setting VALUES ('0', '0', '5', '192.168.1.113', '2001', 'super', '123', 'se1.china-sms.com:9900;se2.china-sms.com:9900;se3.china-sms.com:9900;se5.china-sms.com:9900', '', '', '127.0.0.1', 'www.gicater.com', '2001', 'super', '123');

-- ----------------------------
-- Table structure for `order_default_group`
-- ----------------------------
CREATE TABLE `order_default_group` (
`order_default_groupid`  int(11) NOT NULL ,
`order_default_groupname`  varchar(100) NULL DEFAULT NULL ,
`serving_period_class`  int(11) NULL DEFAULT '-1' ,
`serving_place_class`  int(11) NULL DEFAULT '-1' ,
`extend_1`  int(11) NULL DEFAULT NULL ,
`extend_2`  int(11) NULL DEFAULT NULL ,
`extend_3`  varchar(300) NULL DEFAULT NULL ,
`extend_4`  varchar(300) NULL DEFAULT NULL ,
`extend_5`  float NULL DEFAULT NULL ,
PRIMARY KEY (`order_default_groupid`)
)
ENGINE=InnoDB

;

-- ----------------------------
-- Records of order_default_group
-- ----------------------------
INSERT INTO order_default_group VALUES ('1', '默认开台消费组', '-1', '-1', null, null, null, null, null);

-- ----------------------------
-- Table structure for `order_detail`
-- ----------------------------
CREATE TABLE `order_detail` (
`order_detail_id`  int(11) UNSIGNED NOT NULL AUTO_INCREMENT ,
`order_head_id`  int(11) NULL DEFAULT NULL ,
`check_id`  int(11) NULL DEFAULT 1 ,
`menu_item_id`  int(11) NULL DEFAULT NULL ,
`menu_item_name`  varchar(60) NULL DEFAULT NULL ,
`product_price`  float NULL DEFAULT NULL ,
`is_discount`  bit(1) NULL DEFAULT NULL ,
`original_price`  float NULL DEFAULT NULL ,
`discount_id`  int(11) NULL DEFAULT NULL ,
`actual_price`  float NULL DEFAULT NULL ,
`is_return_item`  bit(1) NULL DEFAULT b'0' ,
`order_employee_id`  int(11) NULL DEFAULT NULL ,
`order_employee_name`  varchar(40) NULL DEFAULT NULL ,
`pos_device_id`  int(11) NULL DEFAULT NULL ,
`pos_name`  varchar(30) NULL DEFAULT NULL ,
`order_time`  datetime NULL DEFAULT NULL ,
`return_time`  datetime NULL DEFAULT NULL ,
`return_reason`  varchar(200) NULL DEFAULT NULL ,
`unit`  varchar(30) NULL DEFAULT NULL ,
`is_send`  bit(1) NULL DEFAULT NULL ,
`condiment_belong_item`  int(11) NULL DEFAULT NULL ,
`quantity`  float NULL DEFAULT 1 ,
`eat_type`  int(11) NULL DEFAULT NULL ,
`auth_id`  int(11) NULL DEFAULT NULL ,
`auth_name`  varchar(40) NULL DEFAULT '' ,
`weight_entry_required`  bit(1) NULL DEFAULT NULL ,
`description`  char(100) NULL DEFAULT NULL ,
`n_service_type`  int(11) NULL DEFAULT NULL ,
`not_print`  int(11) NULL DEFAULT NULL ,
`seat_num`  int(11) NULL DEFAULT NULL ,
`discount_price`  float NULL DEFAULT NULL ,
`sales_amount`  float NULL DEFAULT NULL ,
`is_make`  int(11) NULL DEFAULT NULL ,
`print_class`  int(11) NULL DEFAULT NULL ,
`rush`  int(11) NULL DEFAULT 0 ,
PRIMARY KEY (`order_detail_id`)
)
ENGINE=InnoDB
AUTO_INCREMENT=1

;

-- ----------------------------
-- Records of order_detail
-- ----------------------------

-- ----------------------------
-- Table structure for `order_detail_default`
-- ----------------------------
CREATE TABLE `order_detail_default` (
`order_detail_default_id`  int(11) NOT NULL AUTO_INCREMENT ,
`menu_item_id`  int(11) NOT NULL ,
`quantity`  float NULL DEFAULT NULL ,
`unit_id`  int(11) NULL DEFAULT NULL ,
`discount_service_id`  int(11) NULL DEFAULT NULL ,
`price`  float NULL DEFAULT NULL ,
`mark`  varchar(300) NULL DEFAULT NULL ,
`is_cus_num`  int(11) NULL DEFAULT 0 ,
`extend_1`  int(11) NULL DEFAULT 0 ,
`extend_2`  int(11) NULL DEFAULT 0 ,
`extend_3`  varchar(300) NULL DEFAULT NULL ,
`extend_4`  varchar(300) NULL DEFAULT NULL ,
`extend_5`  float NULL DEFAULT NULL ,
PRIMARY KEY (`order_detail_default_id`)
)
ENGINE=InnoDB
AUTO_INCREMENT=1

;

-- ----------------------------
-- Records of order_detail_default
-- ----------------------------

-- ----------------------------
-- Table structure for `order_head`
-- ----------------------------
CREATE TABLE `order_head` (
`order_head_id`  int(11) UNSIGNED NOT NULL AUTO_INCREMENT ,
`check_number`  int(11) NULL DEFAULT NULL ,
`rvc_center_id`  int(11) NULL DEFAULT NULL ,
`rvc_center_name`  varchar(30) NULL DEFAULT NULL ,
`table_id`  int(11) NULL DEFAULT NULL ,
`table_name`  varchar(30) NULL DEFAULT NULL ,
`check_id`  int(11) NOT NULL DEFAULT 0 ,
`open_employee_id`  int(11) NULL DEFAULT NULL ,
`open_employee_name`  varchar(30) NULL DEFAULT NULL ,
`customer_num`  int(11) NULL DEFAULT NULL ,
`customer_id`  int(11) NULL DEFAULT 0 ,
`customer_name`  varchar(30) NULL DEFAULT NULL ,
`pos_device_id`  int(11) NULL DEFAULT NULL ,
`pos_name`  varchar(30) NULL DEFAULT NULL ,
`order_start_time`  datetime NULL DEFAULT NULL ,
`order_end_time`  datetime NULL DEFAULT NULL ,
`should_amount`  decimal(11,2) NULL DEFAULT 0.00 ,
`return_amount`  decimal(11,2) NULL DEFAULT 0.00 ,
`discount_amount`  decimal(11,2) NULL DEFAULT 0.00 ,
`actual_amount`  decimal(11,2) NULL DEFAULT 0.00 ,
`print_count`  int(11) NULL DEFAULT 0 ,
`status`  int(11) NULL DEFAULT 0 ,
`eat_type`  int(11) NULL DEFAULT NULL ,
`check_name`  varchar(30) NULL DEFAULT NULL ,
`original_amount`  decimal(11,2) NULL DEFAULT 0.00 ,
`service_amount`  decimal(11,2) NULL DEFAULT 0.00 ,
`edit_time`  datetime NULL DEFAULT NULL ,
`party_id`  int(11) NULL DEFAULT NULL ,
`edit_employee_name`  varchar(30) NULL DEFAULT NULL ,
`remark`  varchar(50) NULL DEFAULT NULL ,
`is_make`  int(11) NULL DEFAULT NULL ,
`delivery_info`  varchar(100) NULL DEFAULT NULL ,
`kds_show`  int(11) NULL DEFAULT 0 ,
`kds_time`  datetime NULL DEFAULT NULL ,
`tax_amount`  decimal(11,2) NULL DEFAULT NULL ,
`raw_talbe`  int(11) NULL DEFAULT 0 ,
`tips_amount`  decimal(11,2) NULL DEFAULT NULL ,
`member_discount`  decimal(11,2) NULL DEFAULT NULL ,
PRIMARY KEY (`order_head_id`, `check_id`)
)
ENGINE=InnoDB
AUTO_INCREMENT=1

;

-- ----------------------------
-- Records of order_head
-- ----------------------------

-- ----------------------------
-- Table structure for `order_types`
-- ----------------------------
CREATE TABLE `order_types` (
`order_type_id`  int(11) NOT NULL ,
`order_type_number`  int(11) NULL DEFAULT NULL ,
`order_type_name`  varchar(30) NULL DEFAULT NULL ,
`is_enable`  bit(1) NULL DEFAULT NULL ,
`print_check_receipt`  bit(1) NULL DEFAULT NULL ,
`print_order_chit`  bit(1) NULL DEFAULT NULL ,
PRIMARY KEY (`order_type_id`)
)
ENGINE=InnoDB

;

-- ----------------------------
-- Records of order_types
-- ----------------------------
INSERT INTO order_types VALUES ('0', null, '堂吃', '', null, null), ('1', null, '带走', null, null, null);

-- ----------------------------
-- Table structure for `parties`
-- ----------------------------
CREATE TABLE `parties` (
`party_id`  int(11) NOT NULL AUTO_INCREMENT ,
`party_name`  varchar(200) NULL DEFAULT NULL ,
`status`  int(11) NULL DEFAULT 0 ,
`party_type`  int(11) NULL DEFAULT 0 ,
`table_num`  int(11) NULL DEFAULT 0 ,
`back_table_num`  int(11) NULL DEFAULT 0 ,
`table_price`  decimal(11,2) NULL DEFAULT NULL ,
`remark`  varchar(300) NULL DEFAULT NULL ,
`contract_id`  varchar(100) NULL DEFAULT NULL ,
`pre_amount`  decimal(11,2) NULL DEFAULT NULL ,
`amount`  decimal(11,2) NULL DEFAULT NULL ,
`sale_employee`  int(11) NULL DEFAULT '-1' ,
`customer_name`  varchar(100) NULL DEFAULT NULL ,
`customer_tel`  varchar(100) NULL DEFAULT NULL ,
`party_time`  datetime NULL DEFAULT NULL ,
`insert_time`  datetime NULL DEFAULT NULL ,
`update_time`  datetime NULL DEFAULT NULL ,
`insert_employee`  int(11) NULL DEFAULT '-1' ,
`update_employee`  int(11) NULL DEFAULT '-1' ,
`customer_id`  int(11) NULL DEFAULT NULL ,
`table_str`  varchar(500) NULL DEFAULT NULL ,
`cus_num`  int(11) NULL DEFAULT 1 ,
PRIMARY KEY (`party_id`)
)
ENGINE=InnoDB
AUTO_INCREMENT=1

;

-- ----------------------------
-- Records of parties
-- ----------------------------

-- ----------------------------
-- Table structure for `parties_type`
-- ----------------------------
CREATE TABLE `parties_type` (
`party_type_id`  int(11) NOT NULL DEFAULT 0 ,
`party_type_name`  varchar(200) NULL DEFAULT NULL ,
`msg_template`  varchar(500) NULL DEFAULT '' ,
PRIMARY KEY (`party_type_id`)
)
ENGINE=InnoDB

;

-- ----------------------------
-- Records of parties_type
-- ----------------------------
INSERT INTO parties_type VALUES ('0', '桌台预订', '您好，#CustomerName#,您已成功预订，预订房台为#TblName#,预订席数为#TblNum#,备用席数为安师大aaa#BackTblNum#,每桌价格：#PricePerTbl#,预付订金：#Prepay#,备注：#Remark#,客户电话：#CustomerTel#,开席时间#ArriveTime#,预订名称：#OrderName#。'), ('1', '婚宴', '您好，#CustomerName#，您已在深圳库瑞德餐厅成功预订婚宴，预订席数为#TblNum#，备用席数为#BackTblNum#，开席时间为#ArriveTime#，请您提前半小时抵达。'), ('2', '生日宴会', '您好，#CustomerName#,您已成功预订，预订房台为#TblName#,预订席数为#TblNum#,备用席数为aaa#BackTblNum#,每桌价格：#PricePerTbl#,预付订金：#Prepay#,备注：#Remark#,客户电话：#CustomerTel#,开席时间#ArriveTime#,预订名称：#OrderName#。'), ('3', '会议', '#CustomerName#您好，您已在深圳库瑞德餐厅成功预订婚宴，预订席数为#TblNum#，备用席数为#BackTblNum#，开席时间为#ArriveTime#，请您提前半小时抵达。'), ('4', '谢师宴', '您好，#CustomerName#,您已成功预订，预订房台为#TblName#,预订席数为#TblNum#,备用席数为#BackTblNum#,每桌价格：#PricePerTbl#,预付订金：#Prepay#,备注：#Remark#,客户电话：#CustomerTel#,开席时间#ArriveTime#,预订名称：#OrderName#。'), ('5', '年终宴会', '您好，#CustomerName#,您已成功预订，预订房台为#TblName#,预订席数为#TblNum#,备用席数为#BackTblNum#,每桌价格：#PricePerTbl#,预付订金：#Prepay#,备注：#Remark#,客户电话：#CustomerTel#,开席时间#ArriveTime#,预订名称：#OrderName#。'), ('10', '其他', '您好，#CustomerName#,您已成功预订，预订房台为#TblName#,预订席数为#TblNum#,备用席数为#BackTblNum#,每桌价格：#PricePerTbl#,预付订金：#Prepay#,备注：#Remark#,客户电话#CustomerTel#,开席时间#ArriveTime#,预订名称：#OrderName#。');

-- ----------------------------
-- Table structure for `party_default_remark`
-- ----------------------------
CREATE TABLE `party_default_remark` (
`remark_id`  int(11) NOT NULL AUTO_INCREMENT ,
`remark_title`  varchar(100) NULL DEFAULT NULL ,
`remark_content`  varchar(800) NULL DEFAULT NULL ,
PRIMARY KEY (`remark_id`)
)
ENGINE=InnoDB
AUTO_INCREMENT=4

;

-- ----------------------------
-- Records of party_default_remark
-- ----------------------------
INSERT INTO party_default_remark VALUES ('1', '备注：', '    1、请在大堂及宾馆门口放置指示牌。\r\n    2、宴会厅内提供签到台、签到本、签到笔，详细场地布置见婚宴细节确认表\r\n'), ('2', '出品部： ', '    1、菜单后附。\r\n    2、冷菜上菜时间: 待定 ,热菜上菜时间: 待定 。 \r\n'), ('3', '财务部： ', '    1、客人已交纳10000定金，婚宴结束后结清所有款项。\r\n');

-- ----------------------------
-- Table structure for `party_item`
-- ----------------------------
CREATE TABLE `party_item` (
`party_item_id`  int(11) NOT NULL AUTO_INCREMENT ,
`party_id`  int(11) NULL DEFAULT NULL ,
`menu_item_id`  int(11) NULL DEFAULT NULL ,
`item_course_name`  varchar(200) NULL DEFAULT NULL ,
`unit`  varchar(100) NULL DEFAULT NULL ,
`num`  decimal(11,2) NULL DEFAULT NULL ,
`price`  decimal(11,2) NULL DEFAULT NULL ,
`description`  varchar(200) NULL DEFAULT NULL ,
PRIMARY KEY (`party_item_id`)
)
ENGINE=InnoDB
AUTO_INCREMENT=1

;

-- ----------------------------
-- Records of party_item
-- ----------------------------

-- ----------------------------
-- Table structure for `party_remark`
-- ----------------------------
CREATE TABLE `party_remark` (
`remark_id`  int(11) NOT NULL AUTO_INCREMENT ,
`party_id`  int(11) NULL DEFAULT NULL ,
`remark_title`  varchar(100) NULL DEFAULT NULL ,
`remark_content`  varchar(800) NULL DEFAULT NULL ,
PRIMARY KEY (`remark_id`)
)
ENGINE=InnoDB
AUTO_INCREMENT=1

;

-- ----------------------------
-- Records of party_remark
-- ----------------------------

-- ----------------------------
-- Table structure for `party_table`
-- ----------------------------
CREATE TABLE `party_table` (
`party_id`  int(11) NOT NULL DEFAULT 0 ,
`table_id`  int(11) NOT NULL DEFAULT 0 ,
PRIMARY KEY (`party_id`, `table_id`)
)
ENGINE=InnoDB

;

-- ----------------------------
-- Records of party_table
-- ----------------------------

-- ----------------------------
-- Table structure for `payment`
-- ----------------------------
CREATE TABLE `payment` (
`payment_id`  int(11) UNSIGNED NOT NULL AUTO_INCREMENT ,
`order_head_id`  int(11) NULL DEFAULT NULL ,
`check_id`  int(11) NULL DEFAULT NULL ,
`tender_media_id`  int(11) NULL DEFAULT NULL ,
`total`  decimal(11,2) NULL DEFAULT NULL ,
`employee_id`  int(11) NULL DEFAULT NULL ,
`remark`  varchar(30) NULL DEFAULT NULL ,
`payment_time`  datetime NULL DEFAULT NULL ,
`pos_device_id`  int(11) NULL DEFAULT NULL ,
`rvc_center_id`  int(11) NULL DEFAULT NULL ,
`order_detail_id`  int(11) NULL DEFAULT NULL ,
`consume_id`  int(11) NULL DEFAULT NULL ,
`ticket_id`  int(11) NULL DEFAULT NULL ,
`wechat_id`  varchar(32) NULL DEFAULT NULL ,
PRIMARY KEY (`payment_id`)
)
ENGINE=InnoDB
AUTO_INCREMENT=1

;

-- ----------------------------
-- Records of payment
-- ----------------------------

-- ----------------------------
-- Table structure for `period_class`
-- ----------------------------
CREATE TABLE `period_class` (
`period_class_id`  int(11) NOT NULL DEFAULT 0 ,
`period_class_name`  varchar(40) NULL DEFAULT NULL ,
PRIMARY KEY (`period_class_id`)
)
ENGINE=InnoDB

;

-- ----------------------------
-- Records of period_class
-- ----------------------------
INSERT INTO period_class VALUES ('1', '默认营业时间组');

-- ----------------------------
-- Table structure for `periods`
-- ----------------------------
CREATE TABLE `periods` (
`period_id`  int(11) NOT NULL ,
`period_name`  varchar(30) NULL DEFAULT NULL ,
`start_time`  time NULL DEFAULT NULL ,
`end_time`  time NULL DEFAULT NULL ,
`is_serving_period`  bit(1) NULL DEFAULT NULL ,
`active_day`  int(11) NULL DEFAULT NULL ,
PRIMARY KEY (`period_id`)
)
ENGINE=InnoDB

;

-- ----------------------------
-- Records of periods
-- ----------------------------
INSERT INTO periods VALUES ('1', '午班', '02:00:00', '17:30:00', null, '0'), ('3', '晚班', '17:30:00', '02:00:00', null, '0');

-- ----------------------------
-- Table structure for `practice`
-- ----------------------------
CREATE TABLE `practice` (
`practice_id`  int(11) NOT NULL AUTO_INCREMENT ,
`practice_name`  varchar(300) NULL DEFAULT NULL ,
`practice_group`  int(11) NULL DEFAULT NULL ,
PRIMARY KEY (`practice_id`)
)
ENGINE=InnoDB
AUTO_INCREMENT=1

;

-- ----------------------------
-- Records of practice
-- ----------------------------

-- ----------------------------
-- Table structure for `practice_group`
-- ----------------------------
CREATE TABLE `practice_group` (
`practice_group_id`  int(11) NOT NULL DEFAULT 0 ,
`practice_group_name`  varchar(100) NULL DEFAULT NULL ,
PRIMARY KEY (`practice_group_id`)
)
ENGINE=InnoDB

;

-- ----------------------------
-- Records of practice_group
-- ----------------------------

-- ----------------------------
-- Table structure for `pre_order`
-- ----------------------------
CREATE TABLE `pre_order` (
`pre_order_id`  int(11) NOT NULL AUTO_INCREMENT ,
`pre_order_name`  varchar(40) NULL DEFAULT '' ,
`customer_id`  int(11) NULL DEFAULT 0 ,
`customer_name`  varchar(40) NULL DEFAULT '' ,
`telephone_1`  varchar(40) NULL DEFAULT '' ,
`telephone_2`  varchar(40) NULL DEFAULT '' ,
`company`  varchar(100) NULL DEFAULT '' ,
`pre_amount`  float NULL DEFAULT 0 ,
`order_type`  int(11) NULL DEFAULT 1 ,
`type`  int(11) NULL DEFAULT NULL ,
`rvc_center_id`  int(11) NULL DEFAULT 0 ,
`rvc_center_name`  varchar(40) NULL DEFAULT '' ,
`table_id`  int(11) NOT NULL DEFAULT 0 ,
`table_name`  varchar(40) NULL DEFAULT '' ,
`customer_num`  int(11) NULL DEFAULT 0 ,
`description`  varchar(200) NULL DEFAULT '' ,
`pre_order_status`  int(11) NULL DEFAULT 0 ,
`preorder_employee_id`  int(11) NULL DEFAULT 0 ,
`preorder_employee_name`  varchar(40) NULL DEFAULT '' ,
`preorder_time`  datetime NULL DEFAULT NULL ,
`disorder_employee_id`  int(11) NULL DEFAULT 0 ,
`disorder_employee_name`  varchar(40) NULL DEFAULT '' ,
`auth_employee_id`  int(11) NULL DEFAULT 0 ,
`auth_employee_name`  varchar(40) NULL DEFAULT '' ,
`sail_employee_id`  int(11) NULL DEFAULT 0 ,
`sail_employee_name`  varchar(40) NULL DEFAULT NULL ,
`disorder_time`  datetime NULL DEFAULT NULL ,
`disorder_reason`  varchar(255) NULL DEFAULT '' ,
`arrived_time`  datetime NULL DEFAULT NULL ,
`actual_arrived_time`  datetime NULL DEFAULT NULL ,
`amount`  float NULL DEFAULT 0 ,
PRIMARY KEY (`pre_order_id`, `table_id`)
)
ENGINE=InnoDB
AUTO_INCREMENT=1

;

-- ----------------------------
-- Records of pre_order
-- ----------------------------

-- ----------------------------
-- Table structure for `pre_order_detail`
-- ----------------------------
CREATE TABLE `pre_order_detail` (
`preorder_detail_id`  int(11) NOT NULL AUTO_INCREMENT ,
`pre_order_id`  int(11) NULL DEFAULT NULL ,
`menu_item_id`  int(11) NULL DEFAULT NULL ,
`menu_item_name`  varchar(40) NULL DEFAULT '' ,
`price`  float NULL DEFAULT NULL ,
`quantity`  float NULL DEFAULT NULL ,
`unit`  varchar(30) NULL DEFAULT NULL ,
`should_amount`  float NULL DEFAULT NULL ,
`condiment_belong_item`  int(11) NULL DEFAULT NULL ,
`description`  varchar(200) NULL DEFAULT NULL ,
PRIMARY KEY (`preorder_detail_id`)
)
ENGINE=InnoDB
AUTO_INCREMENT=1

;

-- ----------------------------
-- Records of pre_order_detail
-- ----------------------------

-- ----------------------------
-- Table structure for `price_scheme`
-- ----------------------------
CREATE TABLE `price_scheme` (
`menu_item_id`  int(11) NOT NULL DEFAULT 0 ,
`menu_item_name`  varchar(20) NULL DEFAULT NULL ,
`item_price`  double NULL DEFAULT NULL ,
`disable`  int(11) NULL DEFAULT 0 ,
`group_id`  int(11) NOT NULL DEFAULT '-1' ,
PRIMARY KEY (`menu_item_id`, `group_id`)
)
ENGINE=InnoDB

;

-- ----------------------------
-- Records of price_scheme
-- ----------------------------

-- ----------------------------
-- Table structure for `price_scheme_group`
-- ----------------------------
CREATE TABLE `price_scheme_group` (
`group_id`  int(11) NOT NULL ,
`group_name`  varchar(300) NULL DEFAULT NULL ,
`period_class`  int(11) NULL DEFAULT '-1' ,
`place_class`  int(11) NULL DEFAULT '-1' ,
`is_discount`  int(11) NULL DEFAULT 0 ,
`is_service`  int(11) NULL DEFAULT 0 ,
`from_time`  time NULL DEFAULT NULL ,
`to_time`  time NULL DEFAULT NULL ,
`week`  int(11) NULL DEFAULT 512 ,
`month`  int(11) NULL DEFAULT NULL ,
`begin`  date NULL DEFAULT NULL ,
`end`  date NULL DEFAULT NULL ,
`disable`  int(11) NULL DEFAULT 0 ,
PRIMARY KEY (`group_id`)
)
ENGINE=InnoDB

;

-- ----------------------------
-- Records of price_scheme_group
-- ----------------------------
INSERT INTO price_scheme_group VALUES ('1', '方案1', '-1', '-1', '0', '0', null, null, '127', null, null, null, '0'), ('2', '方案2', '-1', '-1', '0', '0', null, null, '127', null, null, null, '0'), ('3', '方案3', '-1', '-1', '0', '0', null, null, '127', null, null, null, '0'), ('4', '方案4', '-1', '-1', '0', '0', null, null, '127', null, null, null, '0'), ('5', '方案5', '-1', '-1', '0', '0', null, null, '127', null, null, null, '0'), ('6', '方案6', '-1', '-1', '0', '0', null, null, '127', null, null, null, '0'), ('7', '方案7', '-1', '-1', '0', '0', null, null, '127', null, null, null, '0');

-- ----------------------------
-- Table structure for `print_class`
-- ----------------------------
CREATE TABLE `print_class` (
`print_class_id`  int(11) NOT NULL ,
`print_class_number`  int(11) NULL DEFAULT NULL ,
`print_class_name`  varchar(30) NULL DEFAULT NULL ,
`customer_receipt`  bit(1) NULL DEFAULT b'0' ,
`local_order_receipt`  bit(1) NULL DEFAULT b'0' ,
`check`  bit(1) NULL DEFAULT b'0' ,
`journal`  bit(1) NULL DEFAULT b'0' ,
`fiscal_cash_register`  bit(1) NULL DEFAULT b'0' ,
`print_in_red`  bit(1) NULL DEFAULT b'0' ,
`remote_device`  int(11) NULL DEFAULT 0 ,
PRIMARY KEY (`print_class_id`)
)
ENGINE=InnoDB

;

-- ----------------------------
-- Records of print_class
-- ----------------------------
INSERT INTO print_class VALUES ('11', null, '热菜', '', '', '', '', '', '', '0');

-- ----------------------------
-- Table structure for `print_class_relation`
-- ----------------------------
CREATE TABLE `print_class_relation` (
`print_class_id`  int(11) NOT NULL DEFAULT 0 ,
`print_device_id`  int(11) NOT NULL DEFAULT 0 
)
ENGINE=InnoDB

;

-- ----------------------------
-- Records of print_class_relation
-- ----------------------------

-- ----------------------------
-- Table structure for `print_devices`
-- ----------------------------
CREATE TABLE `print_devices` (
`print_device_id`  int(11) NOT NULL ,
`print_device_name`  varchar(30) NULL DEFAULT NULL ,
`header`  int(11) NULL DEFAULT NULL ,
`trailer`  int(11) NULL DEFAULT NULL ,
`device_id`  int(11) NULL DEFAULT NULL ,
`backup_device_id`  int(11) NULL DEFAULT NULL ,
`redirection_device_id`  int(11) NULL DEFAULT NULL ,
`check_info_print`  int(11) NULL DEFAULT NULL ,
`print_table_number`  bit(1) NULL DEFAULT NULL ,
`com_port`  int(11) NULL DEFAULT 0 ,
`baud_rate`  int(11) NULL DEFAULT NULL ,
`parity_type`  int(11) NULL DEFAULT NULL ,
`num_data_bit`  int(11) NULL DEFAULT NULL ,
`num_stop_bits`  int(11) NULL DEFAULT NULL ,
`is_print_note`  int(11) NULL DEFAULT 1 ,
`printer_name`  varchar(300) NULL DEFAULT NULL ,
`flow_control`  int(11) NULL DEFAULT 1 ,
`paper_width`  int(11) NULL DEFAULT NULL ,
`beep`  int(11) NULL DEFAULT 0 ,
PRIMARY KEY (`print_device_id`)
)
ENGINE=InnoDB

;

-- ----------------------------
-- Records of print_devices
-- ----------------------------
INSERT INTO print_devices VALUES ('1', '收银', '1', '1', null, null, '0', '4', '', '0', '9600', '2', '8', '2', '1', 'myprinter', '1', '80', '0');

-- ----------------------------
-- Table structure for `print_task`
-- ----------------------------
CREATE TABLE `print_task` (
`id`  int(11) UNSIGNED NOT NULL AUTO_INCREMENT ,
`data`  varchar(21840) NULL DEFAULT NULL ,
`time`  timestamp NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP ,
PRIMARY KEY (`id`)
)
ENGINE=InnoDB
AUTO_INCREMENT=1

;

-- ----------------------------
-- Records of print_task
-- ----------------------------

-- ----------------------------
-- Table structure for `reasons`
-- ----------------------------
CREATE TABLE `reasons` (
`reason_id`  int(11) NOT NULL ,
`reason_number`  int(11) NULL DEFAULT NULL ,
`reason_name`  varchar(30) NULL DEFAULT NULL ,
`description`  varchar(200) NULL DEFAULT NULL ,
`is_voids`  bit(1) NULL DEFAULT NULL ,
`is_returns`  bit(1) NULL DEFAULT b'0' ,
`is_timecard`  bit(1) NULL DEFAULT b'0' ,
`is_requests`  bit(1) NULL DEFAULT NULL ,
`is_terminations`  bit(1) NULL DEFAULT NULL ,
`is_absence`  bit(1) NULL DEFAULT NULL ,
`is_playrate`  bit(1) NULL DEFAULT NULL ,
`is_other`  bit(1) NULL DEFAULT b'0' ,
PRIMARY KEY (`reason_id`)
)
ENGINE=InnoDB

;

-- ----------------------------
-- Records of reasons
-- ----------------------------
INSERT INTO reasons VALUES ('1', null, '错误输入', '', '', '', '', null, null, null, null, ''), ('2', null, '重复输入', '', '', '', '', null, null, null, null, ''), ('3', null, '菜没上', '', '', '', '', null, null, null, null, ''), ('4', null, '上菜慢', '', '', '', '', null, null, null, null, ''), ('5', null, '原料不足', '', '', '', '', null, null, null, null, ''), ('6', null, '客人取消', '', null, '', '', null, null, null, null, ''), ('7', null, '点多了', '', null, '', '', null, null, null, null, '');

-- ----------------------------
-- Table structure for `report`
-- ----------------------------
CREATE TABLE `report` (
`report_id`  int(11) NOT NULL AUTO_INCREMENT ,
`report_name`  varchar(40) NULL DEFAULT NULL ,
`report_class_id`  int(11) NULL DEFAULT NULL ,
`is_date_range`  bit(1) NULL DEFAULT b'0' ,
`is_rvc_range`  bit(1) NULL DEFAULT b'0' ,
`is_number_range`  bit(1) NULL DEFAULT b'0' ,
`number_range_type`  int(11) NULL DEFAULT '-1' ,
`template_filename`  varchar(256) NULL DEFAULT NULL ,
PRIMARY KEY (`report_id`)
)
ENGINE=InnoDB
AUTO_INCREMENT=142

;

-- ----------------------------
-- Records of report
-- ----------------------------
INSERT INTO report VALUES ('11', '报表主类销售统计', '4', '', '', '', '-1', 'report\\major_gourp.rpt'), ('12', '报表子类销售统计', '4', '', '', '', '-1', 'report\\family_group.rpt'), ('13', '时间段销售明细', '3', '', '', '', '-1', 'report\\systime_period.rpt'), ('15', '员工菜品销售明细', '6', '', '', '', '0', 'report\\employee_item_sales.rpt'), ('16', '各收银点收银统计', '4', '', '', '', '3', 'report\\cash_box_list.rpt'), ('17', '菜品销售统计', '5', '', '', '', '2', 'report\\item_sales.rpt'), ('18', '营业情况统计', '1', '', '', '', '-1', 'report\\sails.rpt'), ('19', '当日退菜明细', '5', '', '', '', '0', 'report\\return_item_list.rpt'), ('20', '未结账单明细', '1', '', '', '', '0', 'report\\unpay_check.rpt'), ('21', '员工营业销售明细', '6', '', '', '', '0', 'report\\employee_sale.rpt'), ('23', '账单流水报表', '1', '', '', '', '-1', 'report\\check_detail_common.rpt'), ('24', '当日送菜明细', '5', '', '', '', '-1', 'report\\send_items.rpt'), ('25', '送菜统计报表', '5', '', '', '', '-1', 'report\\send_items_sum.rpt'), ('26', '挂账统计报表', '6', '', '', '', '-1', 'report\\unpay_bills.rpt'), ('27', '会员卡消费统计报表', '6', '', '', '', '-1', 'report\\vipcard.rpt'), ('28', '菜品资料(横排)', '7', '', '', '', '-1', 'report\\items.rpt'), ('29', '菜品资料', '7', '', '', '', '-1', 'report\\items_1.rpt'), ('31', '菜品畅销销售统计', '4', '', '', '', '-1', 'report\\item_sales_desc.rpt'), ('41', '自定义菜销售明细', '5', '', '', '', '-1', 'report\\self_items.rpt'), ('42', '自定义菜销售统计', '5', '', '', '', '-1', 'report\\self_items_sum.rpt'), ('43', '菜品改价记录', '5', '', '', '', '-1', 'report\\change_price.rpt'), ('46', '收银员提成统计报表', '6', '', '', '', '-1', 'report\\cashier_sum.rpt'), ('47', '收银员收银明细报表', '6', '', '', '', '0', 'report\\cashier_detail.rpt'), ('48', '提成菜品', '7', '', '', '', '-1', 'report\\commission_item.rpt'), ('49', '点菜员提成统计报表', '6', '', '', '', '0', 'report\\employee_sommission.rpt'), ('50', '点菜员提成明细报表', '6', '', '', '', '0', 'report\\employee_sommission_detail.rpt'), ('51', '桌台资料', '2', '', '', '', '-1', 'report\\tables_detail.rpt'), ('52', '桌台消费排名', '2', '', '', '', '-1', 'report\\tables_sail.rpt'), ('53', '菜品类别', '7', '', '', '', '-1', 'report\\item_group.rpt'), ('54', '调味品', '7', '', '', '', '-1', 'report\\condiment_detail.rpt'), ('55', '时价菜', '7', '', '', '', '-1', 'report\\priceitem_detail.rpt'), ('56', '沽清菜品', '7', '', '', '', '-1', 'report\\soldoutitem_detail.rpt'), ('57', '套餐', '7', '', '', '', '-1', 'report\\course_detail.rpt'), ('58', '员工资料', '6', '', '', '', '-1', 'report\\employees_detail.rpt'), ('59', '折扣账单', '1', '', '', '', '-1', 'report\\discount_detail.rpt'), ('60', '服务费账单', '1', '', '', '', '-1', 'report\\service_detail.rpt'), ('61', '服务费统计', '1', '', '', '', '-1', 'report\\service_total.rpt'), ('70', '员工发票发放明细', '6', '', '', '', '-1', 'report\\invoice_detail.rpt'), ('71', '员工发票发放统计', '6', '', '', '', '-1', 'report\\invoice_total.rpt'), ('80', '代金券组使用统计', '4', '', '', '', '-1', 'report\\tickets_class_total.rpt'), ('81', '代金券使用统计', '4', '', '', '', '-1', 'report\\tickets_total.rpt'), ('100', '外卖菜品销售明细', '5', '', '', '', '-1', 'report\\take_out_details.rpt'), ('130', '套餐销售明细', '5', '', '', '', '-1', 'report\\course_sale_detail.rpt'), ('131', '小类菜品销售统计', '5', '', '', '', '4', 'report\\secondItem_sales.rpt'), ('132', '大类菜品销售统计', '5', '', '', '', '5', 'report\\mainItem_sales.rpt'), ('133', '报表主类数量畅销排行', '5', '', '', '', '-1', 'report\\major_items_num_desc.rpt'), ('134', '报表主类金额畅销排行', '5', '', '', '', '-1', 'report\\major_items_amount_desc.rpt'), ('135', '报表子类数量畅销排行', '5', '', '', '', '-1', 'report\\family_items_num_desc.rpt'), ('136', '报表子类金额畅销排行', '5', '', '', '', '-1', 'report\\family_items_amount_desc.rpt'), ('137', '报表主类数量滞销排行', '5', '', '', '', '-1', 'report\\major_items_num_asc.rpt'), ('138', '报表主类金额滞销排行', '5', '', '', '', '-1', 'report\\major_items_amount_asc.rpt'), ('139', '报表子类数量滞销排行', '5', '', '', '', '-1', 'report\\family_items_num_asc.rpt'), ('140', '报表子类金额滞销排行', '5', '', '', '', '-1', 'report\\family_items_amount_asc.rpt'), ('141', '员工考勤表', '6', '', '', '', '0', 'report\\employee_clock.rpt');

-- ----------------------------
-- Table structure for `report_class`
-- ----------------------------
CREATE TABLE `report_class` (
`report_class_id`  int(11) NOT NULL DEFAULT 0 ,
`report_class_name`  varchar(40) NULL DEFAULT '' ,
PRIMARY KEY (`report_class_id`)
)
ENGINE=InnoDB

;

-- ----------------------------
-- Records of report_class
-- ----------------------------
INSERT INTO report_class VALUES ('1', '账单统计'), ('2', '桌台统计'), ('3', '时间段统计'), ('4', '收入统计'), ('5', '菜品销售统计'), ('6', '员工统计'), ('7', '菜品资料');

-- ----------------------------
-- Table structure for `restaurant`
-- ----------------------------
CREATE TABLE `restaurant` (
`restaurant_id`  int(11) NOT NULL ,
`restaurant_name`  varchar(30) NULL DEFAULT NULL ,
`location_name_1`  varchar(30) NULL DEFAULT NULL ,
`location_name_2`  varchar(300) NULL DEFAULT NULL ,
`server_network_node`  int(11) NULL DEFAULT NULL ,
`backup_server_node`  int(11) NULL DEFAULT NULL ,
`default_printer_name`  varchar(30) NULL DEFAULT NULL ,
`start_time`  time NULL DEFAULT NULL ,
`start_day`  int(11) NULL DEFAULT NULL ,
`autoinc_business_date`  bit(1) NULL DEFAULT NULL ,
`fiscal_year_date`  datetime NULL DEFAULT NULL ,
`type`  int(11) NULL DEFAULT NULL ,
`fiscal_period_name`  varchar(300) NULL DEFAULT NULL ,
`floating_fical_date`  bit(1) NULL DEFAULT NULL ,
`fixed_period`  bit(1) NULL DEFAULT NULL ,
`number_of_days`  int(11) NULL DEFAULT NULL ,
`currency_name`  varchar(30) NULL DEFAULT NULL ,
`decimal_places`  int(11) NULL DEFAULT NULL ,
`decimal_char`  varchar(1) NULL DEFAULT NULL ,
`is_input_chk`  int(11) NULL DEFAULT 0 ,
`auto_send_type`  int(11) NULL DEFAULT 0 ,
`db_back_folder`  varchar(500) NULL DEFAULT NULL ,
`wechat_mchid`  varchar(32) NULL DEFAULT NULL ,
`wechat_appid`  varchar(32) NULL DEFAULT NULL ,
`ali_mchid`  varchar(32) NULL DEFAULT NULL ,
`ali_appid`  varchar(64) NULL DEFAULT NULL ,
PRIMARY KEY (`restaurant_id`)
)
ENGINE=InnoDB

;

-- ----------------------------
-- Records of restaurant
-- ----------------------------
INSERT INTO restaurant VALUES ('1', 'XX咖啡厅', '', '', '-1', '0', '', '04:00:00', null, null, null, '0', '', null, null, '4321', '￥', '1', null, '0', '2', null, '', null, '', '');

-- ----------------------------
-- Table structure for `rvc_center`
-- ----------------------------
CREATE TABLE `rvc_center` (
`rvc_center_id`  int(11) NOT NULL ,
`rvc_center_name`  varchar(30) NULL DEFAULT NULL ,
`cc_voucher_header`  int(11) NULL DEFAULT NULL ,
`consumption_limit`  int(11) NULL DEFAULT '-1' ,
`row_menu_printer`  int(11) NULL DEFAULT '-1' ,
PRIMARY KEY (`rvc_center_id`)
)
ENGINE=InnoDB

;

-- ----------------------------
-- Records of rvc_center
-- ----------------------------
INSERT INTO rvc_center VALUES ('1', '一楼', null, '-1', '-1'), ('2', '二楼', null, '-1', '-1');

-- ----------------------------
-- Table structure for `rvc_class`
-- ----------------------------
CREATE TABLE `rvc_class` (
`rvc_class_id`  int(11) NOT NULL DEFAULT 0 ,
`rvc_class_name`  varchar(40) NULL DEFAULT NULL ,
PRIMARY KEY (`rvc_class_id`)
)
ENGINE=InnoDB

;

-- ----------------------------
-- Records of rvc_class
-- ----------------------------
INSERT INTO rvc_class VALUES ('1', '一楼大厅'), ('2', '默认营业地点组');

-- ----------------------------
-- Table structure for `service_tip`
-- ----------------------------
CREATE TABLE `service_tip` (
`service_tip_id`  int(11) NOT NULL ,
`service_tip_name`  varchar(40) NULL DEFAULT NULL ,
`type`  int(11) NOT NULL DEFAULT 0 ,
`print_class`  int(11) NULL DEFAULT NULL ,
`menu_level_class`  int(11) NULL DEFAULT NULL ,
`privilege`  int(11) NULL DEFAULT NULL ,
`nlu`  int(11) NULL DEFAULT NULL ,
`amount`  decimal(11,2) NULL DEFAULT NULL ,
`date_from`  datetime NULL DEFAULT NULL ,
`date_to`  datetime NULL DEFAULT NULL ,
`category`  int(11) NULL DEFAULT NULL ,
`percent`  decimal(11,2) NULL DEFAULT NULL ,
`preset`  bit(1) NULL DEFAULT NULL ,
`reference_required`  bit(1) NULL DEFAULT NULL ,
`auto_sys_chg`  bit(1) NULL DEFAULT NULL ,
`seat_filter_exit`  bit(1) NULL DEFAULT NULL ,
`assume_entire_amount`  bit(1) NULL DEFAULT NULL ,
`not_with_seat`  bit(1) NULL DEFAULT NULL ,
`employee_meal`  bit(1) NULL DEFAULT b'0' ,
`discount_over_threshold`  bit(1) NULL DEFAULT NULL ,
`limit_discount`  bit(1) NULL DEFAULT NULL ,
`discount_last_item`  bit(1) NULL DEFAULT NULL ,
`single_seat`  bit(1) NULL DEFAULT NULL ,
`prorated_subtotal`  bit(1) NULL DEFAULT NULL ,
`select_discount`  bit(1) NULL DEFAULT NULL ,
`period_class_id`  int(11) NULL DEFAULT NULL ,
`rvc_class_id`  int(11) NULL DEFAULT NULL ,
`display_name`  char(60) NULL DEFAULT NULL ,
PRIMARY KEY (`service_tip_id`)
)
ENGINE=InnoDB

;

-- ----------------------------
-- Records of service_tip
-- ----------------------------
INSERT INTO service_tip VALUES ('1', '开瓶费', '0', null, '0', '0', null, '30.00', null, null, '1', '0.00', '', null, null, null, null, null, '', '', null, null, null, null, '', null, null, ''), ('2', '冲茶费', '0', null, '0', '0', null, '30.00', null, null, '1', '0.00', '', null, null, null, null, null, '', '', null, null, null, null, '', null, null, ''), ('3', '10%服务费', '0', null, '0', '0', null, '0.00', null, null, '1', '10.00', '', null, null, null, null, null, '', '', null, null, null, null, '', null, null, ''), ('4', '自定义服务费', '1', null, '0', '0', null, '0.00', null, null, '1', '0.00', '', null, null, null, null, null, '', '', null, null, null, null, '', null, null, '服务费');

-- ----------------------------
-- Table structure for `serving_period_class`
-- ----------------------------
CREATE TABLE `serving_period_class` (
`period_class_id`  int(11) NOT NULL DEFAULT 0 ,
`period`  int(11) NOT NULL DEFAULT 0 ,
PRIMARY KEY (`period_class_id`, `period`)
)
ENGINE=InnoDB

;

-- ----------------------------
-- Records of serving_period_class
-- ----------------------------
INSERT INTO serving_period_class VALUES ('1', '1'), ('1', '3');

-- ----------------------------
-- Table structure for `serving_rvc_class`
-- ----------------------------
CREATE TABLE `serving_rvc_class` (
`rvc_class_id`  int(11) NOT NULL DEFAULT 0 ,
`rvc_center_id`  int(11) NOT NULL DEFAULT 0 ,
PRIMARY KEY (`rvc_class_id`, `rvc_center_id`)
)
ENGINE=InnoDB

;

-- ----------------------------
-- Records of serving_rvc_class
-- ----------------------------
INSERT INTO serving_rvc_class VALUES ('1', '1'), ('2', '1'), ('2', '2');

-- ----------------------------
-- Table structure for `shift_info`
-- ----------------------------
CREATE TABLE `shift_info` (
`shift_id`  int(11) NOT NULL AUTO_INCREMENT ,
`type`  int(11) NULL DEFAULT NULL ,
`employee_id`  int(11) NOT NULL ,
`employee_name`  varchar(10) NULL DEFAULT NULL ,
`start_time`  datetime NULL DEFAULT NULL ,
`end_time`  datetime NULL DEFAULT NULL ,
`pos_device_id`  int(11) NULL DEFAULT NULL ,
`pos_name`  varchar(10) NULL DEFAULT NULL ,
`detail`  varchar(512) NULL DEFAULT NULL ,
PRIMARY KEY (`shift_id`)
)
ENGINE=InnoDB
AUTO_INCREMENT=1

;

-- ----------------------------
-- Records of shift_info
-- ----------------------------

-- ----------------------------
-- Table structure for `storage`
-- ----------------------------
CREATE TABLE `storage` (
`id`  int(11) NOT NULL AUTO_INCREMENT ,
`vip`  varchar(50) NULL DEFAULT NULL ,
`info`  varchar(500) NULL DEFAULT NULL ,
`employee`  int(11) NULL DEFAULT NULL ,
`start_date`  date NULL DEFAULT NULL ,
`end_date`  date NULL DEFAULT NULL ,
`del_date`  date NULL DEFAULT NULL ,
`del_employee`  int(11) NULL DEFAULT NULL ,
`is_use`  bit(1) NULL DEFAULT b'1' ,
`last_msg_date`  date NULL DEFAULT NULL COMMENT '上次发送短信通知时间' ,
PRIMARY KEY (`id`)
)
ENGINE=InnoDB
AUTO_INCREMENT=1

;

-- ----------------------------
-- Records of storage
-- ----------------------------

-- ----------------------------
-- Table structure for `table_status`
-- ----------------------------
CREATE TABLE `table_status` (
`table_stauts_id`  int(11) NOT NULL DEFAULT 0 ,
`table_status_name`  varchar(30) NULL DEFAULT NULL ,
`icon`  varchar(256) NULL DEFAULT NULL ,
`description`  varchar(200) NULL DEFAULT NULL ,
PRIMARY KEY (`table_stauts_id`)
)
ENGINE=InnoDB

;

-- ----------------------------
-- Records of table_status
-- ----------------------------
INSERT INTO table_status VALUES ('1', '空台', null, null), ('2', '开台', null, null), ('3', '送厨', null, null), ('4', '印单', null, '已印单，待付款'), ('5', '超时', null, '超过一定时间未付款'), ('6', '停用', null, '');

-- ----------------------------
-- Table structure for `tables`
-- ----------------------------
CREATE TABLE `tables` (
`table_id`  int(11) NOT NULL DEFAULT 0 ,
`table_name`  varchar(30) NULL DEFAULT NULL ,
`seat_num`  int(11) NULL DEFAULT NULL ,
`table_status`  int(11) NULL DEFAULT NULL ,
`description`  varchar(200) NULL DEFAULT NULL ,
`rvc_center_id`  int(11) NULL DEFAULT NULL ,
`floor`  int(11) NULL DEFAULT 1 ,
`icon`  varchar(256) NULL DEFAULT NULL ,
`consumption_limit`  int(11) NULL DEFAULT NULL ,
`row_menu_printer`  int(11) NULL DEFAULT '-1' ,
`party_table`  varchar(30) NULL DEFAULT NULL ,
PRIMARY KEY (`table_id`)
)
ENGINE=InnoDB

;

-- ----------------------------
-- Records of tables
-- ----------------------------
INSERT INTO tables VALUES ('-1', '快餐', null, '0', null, '1', '1', null, null, '-1', null), ('1', 'A1', '4', '1', '', '1', '0', '', '-1', '-1', null), ('2', 'A2', '4', '1', '', '1', '1', '', '-1', '-1', null), ('3', 'A3', '4', '0', '', '1', '1', '', '-1', '-1', null), ('5', 'A5', '6', '-1', '', '1', '1', '', '-1', '-1', null), ('21', 'B1', '8', '0', '', '2', '1', null, '-1', '-1', null), ('22', 'B2', '8', '0', '', '2', '1', null, '-1', '-1', null);

-- ----------------------------
-- Table structure for `tax`
-- ----------------------------
CREATE TABLE `tax` (
`tax_id`  int(11) NOT NULL DEFAULT 0 ,
`tax_name`  varchar(300) NULL DEFAULT NULL ,
`tax_group`  int(11) NULL DEFAULT NULL ,
`display_name`  varchar(300) NULL DEFAULT NULL ,
`tax_type`  int(11) NULL DEFAULT NULL ,
`amount`  decimal(11,2) NULL DEFAULT NULL ,
`start_amount`  decimal(11,2) NULL DEFAULT NULL ,
`end_amount`  decimal(11,2) NULL DEFAULT NULL ,
PRIMARY KEY (`tax_id`)
)
ENGINE=InnoDB

;

-- ----------------------------
-- Records of tax
-- ----------------------------

-- ----------------------------
-- Table structure for `tax_group`
-- ----------------------------
CREATE TABLE `tax_group` (
`tax_group_id`  int(11) NOT NULL DEFAULT 0 ,
`tax_group_name`  varchar(300) NULL DEFAULT NULL ,
PRIMARY KEY (`tax_group_id`)
)
ENGINE=InnoDB

;

-- ----------------------------
-- Records of tax_group
-- ----------------------------

-- ----------------------------
-- Table structure for `tax_primary`
-- ----------------------------
CREATE TABLE `tax_primary` (
`tax_id`  int(11) NOT NULL DEFAULT '-1' ,
`tax_name`  varchar(20) NULL DEFAULT NULL ,
`amount`  double NULL DEFAULT NULL ,
`include_service`  int(11) NULL DEFAULT 0 ,
`round`  int(11) NULL DEFAULT 0 ,
`tax_type`  int(11) NULL DEFAULT NULL ,
`start_amount`  decimal(11,2) NULL DEFAULT NULL ,
`end_amount`  decimal(11,2) NULL DEFAULT NULL ,
PRIMARY KEY (`tax_id`)
)
ENGINE=InnoDB

;

-- ----------------------------
-- Records of tax_primary
-- ----------------------------

-- ----------------------------
-- Table structure for `tender_media`
-- ----------------------------
CREATE TABLE `tender_media` (
`tender_media_id`  int(11) NOT NULL DEFAULT 0 ,
`tender_media_name`  varchar(30) NULL DEFAULT NULL ,
`type`  int(11) NULL DEFAULT NULL ,
`date_from`  datetime NULL DEFAULT NULL ,
`date_to`  datetime NULL DEFAULT NULL ,
`slu`  int(11) NULL DEFAULT NULL ,
`print_class`  int(11) NULL DEFAULT NULL ,
`menu_level_class`  int(11) NULL DEFAULT NULL ,
`privilege`  int(11) NULL DEFAULT NULL ,
`category`  int(11) NULL DEFAULT NULL ,
`nlu`  varchar(20) NULL DEFAULT NULL ,
`open_drawer`  bit(1) NULL DEFAULT NULL ,
`currency_conversion`  bit(1) NULL DEFAULT NULL ,
`reference_required`  bit(1) NULL DEFAULT NULL ,
`exempt_service`  bit(1) NULL DEFAULT NULL ,
`employee_meal`  bit(1) NULL DEFAULT NULL ,
`paid_full`  bit(1) NULL DEFAULT NULL ,
`require_amount_entry`  bit(1) NULL DEFAULT NULL ,
`declare_tips_paid`  bit(1) NULL DEFAULT NULL ,
`item_is_shareable`  bit(1) NULL DEFAULT NULL ,
`gross_receipts`  bit(1) NULL DEFAULT NULL ,
`charge_receipts`  bit(1) NULL DEFAULT NULL ,
`cash_register_credit`  bit(1) NULL DEFAULT NULL ,
`tax_exempt_coupon`  bit(1) NULL DEFAULT NULL ,
`charged_tip`  int(11) NULL DEFAULT NULL ,
`enable_halo`  bit(1) NULL DEFAULT NULL ,
`halo_limits_amount`  int(11) NULL DEFAULT 0 ,
`halo_limits_overtender`  int(11) NULL DEFAULT NULL ,
`halo`  int(11) NULL DEFAULT NULL ,
`print_summary_totals`  bit(1) NULL DEFAULT NULL ,
`print_vat_lines`  bit(1) NULL DEFAULT NULL ,
`print_sales_itemizer`  bit(1) NULL DEFAULT NULL ,
`print_check_trailer`  bit(1) NULL DEFAULT NULL ,
`print_on_receipt`  bit(1) NULL DEFAULT NULL ,
`print_with_lookup`  bit(1) NULL DEFAULT NULL ,
`print_validation`  bit(1) NULL DEFAULT NULL ,
`print_endorsement`  bit(1) NULL DEFAULT NULL ,
`suppress_trailer`  bit(1) NULL DEFAULT NULL ,
`print_fiscal_cash`  bit(1) NULL DEFAULT NULL ,
`print_check`  bit(1) NULL DEFAULT NULL ,
`print_memo_check`  bit(1) NULL DEFAULT NULL ,
`print_shared_check`  bit(1) NULL DEFAULT NULL ,
`print_check_active_seat`  bit(1) NULL DEFAULT NULL ,
`reprint_check`  bit(1) NULL DEFAULT NULL ,
`period_class_id`  int(11) NULL DEFAULT NULL ,
`rvc_class_id`  int(11) NULL DEFAULT NULL ,
`extra_amout`  float NULL DEFAULT 0 ,
PRIMARY KEY (`tender_media_id`)
)
ENGINE=InnoDB

;

-- ----------------------------
-- Records of tender_media
-- ----------------------------
INSERT INTO tender_media VALUES ('1', '现金', null, null, null, '-1', null, null, '1', null, null, '', null, '', null, '', '', '', '', null, null, null, null, null, null, null, '10000', null, '0', null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, '-1', '-1', '0'), ('2', '银行卡', null, null, null, '-1', null, null, '2', null, null, '', null, '', null, '', '', '', '', null, null, null, null, null, null, null, '0', null, '0', null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, '-1', '-1', '0'), ('3', '微信', null, null, null, null, null, null, '2', null, null, '', null, '', null, '', '', '', '', null, null, null, null, null, null, null, '0', null, '7', null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, '0'), ('4', '支付宝', null, null, null, null, null, null, '2', null, null, '', null, '', null, '', '', '', '', null, null, null, null, null, null, null, '0', null, '8', null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, '0'), ('5', '会员卡', null, null, null, null, null, null, '0', null, null, '', null, '', null, '', '', '', '', null, null, null, null, null, null, null, '0', null, '4', null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, '0'), ('6', '代金券', null, null, null, null, null, null, '0', null, null, '', null, '', null, '', '', '', '', null, null, null, null, null, null, null, '0', null, '0', null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, '0'), ('7', '美团', null, null, null, null, null, null, '2', null, null, '', null, '', null, '', '', '', '', null, null, null, null, null, null, null, '0', null, '0', null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, '0'), ('8', '大众点评', null, null, null, null, null, null, '0', null, null, '', null, '', null, '', '', '', '', null, null, null, null, null, null, null, '0', null, '0', null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, '0');

-- ----------------------------
-- Table structure for `ticket_class`
-- ----------------------------
CREATE TABLE `ticket_class` (
`ticket_class_id`  int(11) NOT NULL DEFAULT 0 ,
`ticket_class_name`  varchar(200) NULL DEFAULT NULL ,
PRIMARY KEY (`ticket_class_id`)
)
ENGINE=InnoDB

;

-- ----------------------------
-- Records of ticket_class
-- ----------------------------
INSERT INTO ticket_class VALUES ('1', '不使用'), ('2', '通用');

-- ----------------------------
-- Table structure for `ticket_relation`
-- ----------------------------
CREATE TABLE `ticket_relation` (
`ticket_class_id`  int(11) NOT NULL DEFAULT 0 ,
`ticket_id`  int(11) NOT NULL DEFAULT 0 ,
PRIMARY KEY (`ticket_class_id`, `ticket_id`)
)
ENGINE=InnoDB

;

-- ----------------------------
-- Records of ticket_relation
-- ----------------------------

-- ----------------------------
-- Table structure for `tickets`
-- ----------------------------
CREATE TABLE `tickets` (
`ticket_id`  int(11) NOT NULL ,
`ticket_name`  varchar(200) NULL DEFAULT NULL ,
`amount`  decimal(11,2) NULL DEFAULT NULL ,
`remark`  varchar(300) NULL DEFAULT NULL ,
`short_name`  varchar(30) NULL DEFAULT NULL ,
PRIMARY KEY (`ticket_id`)
)
ENGINE=InnoDB

;

-- ----------------------------
-- Records of tickets
-- ----------------------------

-- ----------------------------
-- Table structure for `total_statistics`
-- ----------------------------
CREATE TABLE `total_statistics` (
`id`  int(11) NOT NULL DEFAULT 0 ,
`total_checks`  int(11) NOT NULL DEFAULT 0 ,
`total_guests`  int(11) NOT NULL DEFAULT 0 ,
`install_date`  datetime NULL DEFAULT NULL ,
`db_version`  varchar(10) NULL DEFAULT NULL ,
`dayend_time`  datetime NULL DEFAULT NULL ,
PRIMARY KEY (`id`)
)
ENGINE=InnoDB

;

-- ----------------------------
-- Records of total_statistics
-- ----------------------------
INSERT INTO total_statistics VALUES ('0', '0', '0', '2013-06-19 09:18:01', '20161210', '2013-11-23 10:41:25');

-- ----------------------------
-- Table structure for `user_dcb`
-- ----------------------------
CREATE TABLE `user_dcb` (
`dcb_id`  int(11) NOT NULL AUTO_INCREMENT ,
`workstations_id`  int(11) NOT NULL ,
`dcb_name`  varchar(30) NULL DEFAULT NULL ,
PRIMARY KEY (`dcb_id`)
)
ENGINE=InnoDB
AUTO_INCREMENT=1

;

-- ----------------------------
-- Records of user_dcb
-- ----------------------------

-- ----------------------------
-- Table structure for `user_workstations`
-- ----------------------------
CREATE TABLE `user_workstations` (
`workstations_id`  int(11) NOT NULL ,
`pos_name`  varchar(30) NULL DEFAULT NULL ,
`revenue_center`  int(11) NULL DEFAULT NULL ,
`information_screen`  int(11) NULL DEFAULT NULL ,
`transaction_screen`  int(11) NULL DEFAULT NULL ,
`order_type`  int(11) NULL DEFAULT NULL ,
`auto_signout_delay`  int(11) NULL DEFAULT NULL ,
`check_start`  int(11) NULL DEFAULT 1000 ,
`check_end`  int(11) NULL DEFAULT 9999 ,
`check_num`  int(11) NULL DEFAULT 0 ,
`enable_auto_signout`  bit(1) NULL DEFAULT NULL ,
`cash_drawers`  int(11) NULL DEFAULT NULL ,
`order_devices`  int(11) NULL DEFAULT 0 ,
`customer_receipt_printer`  int(11) NULL DEFAULT NULL ,
`guest_check_printer`  int(11) NULL DEFAULT NULL ,
`journal_printer`  int(11) NULL DEFAULT NULL ,
`local_backup_printer`  int(11) NULL DEFAULT NULL ,
`report_printer`  int(11) NULL DEFAULT NULL ,
`peripheral_type`  int(11) NULL DEFAULT NULL ,
`connection_type`  int(11) NULL DEFAULT NULL ,
`opos_device_name`  varchar(30) NULL DEFAULT NULL ,
`opos_option`  int(11) NULL DEFAULT NULL ,
`com_port`  int(11) NULL DEFAULT NULL ,
`customer_display`  int(11) NULL DEFAULT 0 ,
`ip_address`  varchar(32) NULL DEFAULT '' ,
`subnet_mask`  varchar(32) NULL DEFAULT '' ,
`print_class`  int(11) NULL DEFAULT NULL ,
`is_quickservice`  bit(1) NULL DEFAULT NULL ,
PRIMARY KEY (`workstations_id`)
)
ENGINE=InnoDB

;

-- ----------------------------
-- Records of user_workstations
-- ----------------------------
INSERT INTO user_workstations VALUES ('1', '默认服务器', '1', null, null, null, null, '1', '999', '20', null, null, '0', '1', '1', null, null, null, null, null, null, null, '12', '-1', '127.0.0.1', null, null, '');

-- ----------------------------
-- Table structure for `vip_setting`
-- ----------------------------
CREATE TABLE `vip_setting` (
`setting_id`  int(11) NOT NULL AUTO_INCREMENT ,
`ip_addr`  varchar(60) NULL DEFAULT NULL ,
`port`  int(11) NULL DEFAULT 8000 ,
`res_id`  varchar(20) NULL DEFAULT NULL ,
`res_pwd`  varchar(20) NULL DEFAULT NULL ,
PRIMARY KEY (`setting_id`)
)
ENGINE=InnoDB
AUTO_INCREMENT=2

;

-- ----------------------------
-- Records of vip_setting
-- ----------------------------
INSERT INTO vip_setting VALUES ('1', 'vip.sandypos.com', '8000', '1', '');

-- ----------------------------
-- Table structure for `webreport_setting`
-- ----------------------------
CREATE TABLE `webreport_setting` (
`cr_url`  varchar(200) NULL DEFAULT NULL ,
`cr_port`  int(11) NOT NULL DEFAULT 2003 ,
`cr_res_id`  varchar(50) NULL DEFAULT NULL ,
`cr_res_pwd`  varchar(50) NULL DEFAULT NULL ,
`cr_last_endtime`  datetime NULL DEFAULT NULL ,
`cr_last_time`  datetime NULL DEFAULT NULL ,
`tender_media`  int(11) NULL DEFAULT 1 ,
`major_group`  int(11) NULL DEFAULT 1 ,
`family_group`  int(11) NULL DEFAULT 1 ,
`rvc_center`  int(11) NULL DEFAULT 1 ,
`periods`  int(11) NULL DEFAULT 1 ,
`employee`  int(11) NULL DEFAULT 1 ,
`menu_item`  int(11) NULL DEFAULT 1 ,
`tables`  int(11) NULL DEFAULT 1 ,
`res_info`  int(11) NULL DEFAULT 1 ,
`soldout`  int(11) NULL DEFAULT 0 ,
`soldoutp`  int(11) NULL DEFAULT 0 ,
`preorder_time`  datetime NULL DEFAULT NULL ,
`edit_mode`  int(11) NULL DEFAULT 0 ,
PRIMARY KEY (`cr_port`)
)
ENGINE=InnoDB

;

-- ----------------------------
-- Records of webreport_setting
-- ----------------------------
INSERT INTO webreport_setting VALUES ('sandypos.com', '2015', '{0000-DEFAULT-0000}', '123456', '2016-12-05 18:21:15', '2016-12-05 18:20:43', '1', '0', '0', '8', '0', '3', '0', '1', '1', '0', '0', null, '0');

-- ----------------------------
-- Table structure for `www_version`
-- ----------------------------
CREATE TABLE `www_version` (
`major_version`  int(11) NOT NULL ,
`menu_item`  int(11) NULL DEFAULT NULL ,
`condiment`  int(11) NULL DEFAULT NULL ,
`course`  int(11) NULL DEFAULT NULL ,
`res_info`  int(11) NULL DEFAULT NULL ,
`discount`  int(11) NULL DEFAULT NULL ,
`service`  int(11) NULL DEFAULT NULL ,
`tax`  int(11) NULL DEFAULT NULL ,
`payment`  int(11) NULL DEFAULT NULL ,
`tables`  int(11) NULL DEFAULT NULL ,
`employee`  int(11) NULL DEFAULT NULL ,
`employee_class`  int(11) NULL DEFAULT NULL ,
`order_default`  int(11) NULL DEFAULT NULL ,
`price_scheme`  int(11) NULL DEFAULT NULL ,
`consumption_limit`  int(11) NULL DEFAULT NULL ,
`reasons`  int(11) NULL DEFAULT NULL ,
`printer`  int(11) NULL DEFAULT NULL ,
`workstation`  int(11) NULL DEFAULT NULL ,
`major_group`  int(11) NULL DEFAULT NULL ,
`family_group`  int(11) NULL DEFAULT NULL ,
`periods`  int(11) NULL DEFAULT NULL ,
`rvc_center`  int(11) NULL DEFAULT NULL ,
`macros`  int(11) NULL DEFAULT NULL ,
`extend_1`  int(11) NULL DEFAULT NULL ,
`extend_2`  int(11) NULL DEFAULT NULL ,
`extend_3`  int(11) NULL DEFAULT NULL ,
PRIMARY KEY (`major_version`)
)
ENGINE=InnoDB

;

-- ----------------------------
-- Records of www_version
-- ----------------------------
INSERT INTO www_version VALUES ('0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0');

-- ----------------------------
-- Procedure structure for `c_department_sales`
-- ----------------------------
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `c_department_sales`(IN `s_time` datetime,IN `e_time` datetime)
BEGIN
  select print_class_id,print_class_name,round(sum(actual_price),2) from history_order_detail,menu_item,print_class 
	where history_order_detail.menu_item_id=menu_item.item_id AND menu_item.print_class=print_class.print_class_id 
	AND history_order_detail.menu_item_id>0 AND is_return_item=0 
	AND order_head_id in (select distinct order_head_id from history_order_head where order_end_time>=s_time and order_end_time<=e_time)
  GROUP BY print_class_id;
END
;;
DELIMITER ;

-- ----------------------------
-- Procedure structure for `c_item_sales`
-- ----------------------------
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `c_item_sales`(IN `s_time` datetime,IN `e_time` datetime,IN  `major_group` int)
BEGIN
	select menu_item_id ,item_name1,IFNULL(unit,'') as ut,round(sum(quantity),0),round(sum(actual_price),1)
	from history_order_detail,menu_item where menu_item_id>0 AND history_order_detail.menu_item_id=menu_item.item_id 
	AND menu_item.major_group=major_group AND is_return_item=0 AND order_head_id in (select distinct order_head_id
  from history_order_head where order_end_time>=s_time and order_end_time<=e_time)
	group by menu_item_id,ut;
END
;;
DELIMITER ;

-- ----------------------------
-- Procedure structure for `c_major_sales`
-- ----------------------------
DELIMITER ;;
CREATE DEFINER=`root`@`%` PROCEDURE `c_major_sales`(IN `s_time` datetime,IN `e_time` datetime)
BEGIN
	select major_group_id ,major_group_name ,round(sum(actual_price),2),round(sum(quantity)) from history_order_detail,menu_item,major_group
	where history_order_detail.menu_item_id=menu_item.item_id AND menu_item.major_group=major_group.major_group_id 
	AND history_order_detail.menu_item_id>0 AND is_return_item=0
	AND  order_head_id in (select distinct order_head_id from history_order_head where order_end_time>=s_time and order_end_time<=e_time)
	GROUP BY major_group_id;
END
;;
DELIMITER ;

-- ----------------------------
-- Procedure structure for `c_pay_style`
-- ----------------------------
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `c_pay_style`(IN `s_time` datetime,IN `e_time` datetime,IN `s_device_id` int,IN `e_device_id` int)
BEGIN
	select tender_media_name AS Tender,ifnull(total,0) AS total FROM
(select tender_media_id,round(sum(total),2) as total from payment  WHERE 
	pos_device_id>=s_device_id AND pos_device_id<=e_device_id AND payment_time>=s_time AND payment_time<e_time 
	group by tender_media_id) 
	as a right outer join tender_media on tender_media.tender_media_id=a.tender_media_id;
END
;;
DELIMITER ;

-- ----------------------------
-- Procedure structure for `c_pay_style_emp`
-- ----------------------------
DELIMITER ;;
CREATE DEFINER=`root`@`%` PROCEDURE `c_pay_style_emp`(IN `s_time` datetime,IN `e_time` datetime,IN `i_emp_id` int)
BEGIN
	select tender_media_name AS Tender,ifnull(total,0) AS total FROM
(select tender_media_id,round(sum(total),2) as total from payment  WHERE 
	employee_id=i_emp_id AND payment_time>=s_time AND payment_time<e_time 
	group by tender_media_id) 
	as a right outer join tender_media on tender_media.tender_media_id=a.tender_media_id;
END
;;
DELIMITER ;

-- ----------------------------
-- Procedure structure for `c_period_sales`
-- ----------------------------
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `c_period_sales`(IN `s_time` datetime,IN `e_time` datetime)
BEGIN
	DECLARE cur_state,line INT default 0;
	DECLARE pid INT;
	DECLARE pname varchar(30);
	DECLARE pstime,petime TIME;
	DECLARE sqlcmd,execsql varchar(5000);
	DECLARE sqlcond varchar(300);
	DECLARE cur CURSOR FOR SELECT period_id,period_name,start_time,end_time FROM periods;
	DECLARE CONTINUE HANDLER FOR NOT FOUND set cur_state=1 ;
	OPEN cur;
	REPEAT
		FETCH cur into pid,pname,pstime,petime;
			IF cur_state=0 THEN
				set line=line+1;
				IF pstime>petime THEN
					 set @sqlcond=concat('(time(order_end_time)>''',pstime,''' OR time(order_end_time)<''',petime,''')');
				ELSE
					 set @sqlcond=concat('(time(order_end_time) BETWEEN ''',pstime,''' AND ''',petime,''')');
				END IF;
				IF line=1 THEN
					set @sqlcmd=concat('select ',pid,' as period_id,''',pname,''' as period_name,sum(a.actual_amount) as total,sum(a.customer_num) as 
					customers_total from (select sum(actual_amount) as actual_amount,customer_num,order_head_id from history_order_head    
					where order_end_time>''',s_time,''' and order_end_time<=''',e_time,''' and ',@sqlcond,' group by order_head_id) as a ');
				ELSE
				  set @sqlcmd=concat(@sqlcmd,'\nunion select ',pid,' as period_id,''',pname,''' as period_name,sum(a.actual_amount) as total,sum(a.customer_num) as 
					customers_total from (select sum(actual_amount) as actual_amount,customer_num,order_head_id from history_order_head    
					where order_end_time>''',s_time,''' and order_end_time<=''',e_time,''' and ',@sqlcond,' group by order_head_id) as a ');
				END IF;
			END IF;
		UNTIL cur_state
	END REPEAT;
	CLOSE cur;
	prepare execsql from @sqlcmd;
  execute execsql;
END
;;
DELIMITER ;

-- ----------------------------
-- Procedure structure for `cash_box_list`
-- ----------------------------
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `cash_box_list`(IN `s_time` datetime,IN `e_time` datetime,IN `s_rvcid` int,IN `e_rvcid` int,IN `s_number` int,IN `e_number` int)
BEGIN
	declare sum_total FLOAT;
	select round(sum(total),2) into sum_total from payment 
where payment_time>=s_time and payment_time<=e_time 
and rvc_center_id>=s_rvcid and rvc_center_id<=e_rvcid 
and pos_device_id>=s_number and pos_device_id<=e_number;
	select dev_id,dev_name,item_total,
(round(item_total*100/sum_total,2)) as per 
from (select payment_id,user_workstations.workstations_id as dev_id,
 user_workstations.pos_name as dev_name,ifnull(round(sum(total),2),0) as item_total 
from payment right join user_workstations on pos_device_id=workstations_id 
where payment_time>=s_time and payment_time<=e_time 
and rvc_center_id>=s_rvcid and rvc_center_id<=e_rvcid 
and pos_device_id>=s_number and pos_device_id<=e_number 
or payment_time is null group by dev_id) as tableone;
END
;;
DELIMITER ;

-- ----------------------------
-- Procedure structure for `check_detail`
-- ----------------------------
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `check_detail`(IN `s_time` datetime,IN `e_time` datetime,IN `s_rvcid` int,IN `e_rvcid` int,IN `s_number` int,IN `e_number` int)
BEGIN
	select a.order_head_id,a.check_id,CONCAT(a.table_name,'/',CONVERT(a.check_id,CHAR))AS table_name,a.customer_num,a.actual_amount,a.should_amount,a.service_amount,a.discount_amount,  
ifnull(aa.major1,0) as major1 ,ifnull(bb.major2,0) as major2 ,ifnull(cc.major3,0) as major3,
ifnull(dd.major4,0) as major4  ,ifnull(b.shipin,0) as tender1,ifnull(c.shipin,0) as tender2,
ifnull(d.shipin,0) as tender3,ifnull(e.shipin,0) as tender4 ,ifnull(f.shipin,0) as tender5 ,ifnull(g.shipin,0) as tender6 
from history_order_head as a 
left join (select order_head_id,check_id,sum(total) as shipin 
from payment where tender_media_id=1 group by order_head_id,check_id) as b on a.order_head_id=b.order_head_id and a.check_id=b.check_id   
left join (select order_head_id,check_id,sum(total) as shipin 
from payment where tender_media_id=2 group by order_head_id,check_id) as c on a.order_head_id=c.order_head_id and a.check_id=c.check_id   
left join (select order_head_id,check_id,sum(total) as shipin 
from payment where tender_media_id=3 group by order_head_id,check_id) as d on a.order_head_id=d.order_head_id and a.check_id=d.check_id   
left join (select order_head_id,check_id,sum(total) as shipin 
from payment where tender_media_id=4 group by order_head_id,check_id) as e on a.order_head_id=e.order_head_id and a.check_id=e.check_id  
left join (select order_head_id,check_id,sum(total) as shipin 
from payment where tender_media_id=5 group by order_head_id,check_id) as f on a.order_head_id=f.order_head_id and a.check_id=f.check_id   
left join (select order_head_id,check_id,sum(total) as shipin 
from payment where tender_media_id=6 group by order_head_id,check_id) as g on a.order_head_id=g.order_head_id and a.check_id=g.check_id 
left join (select a1.order_head_id,a1.check_id,sum(a1.actual_price) 
as major1 from history_order_detail as a1  left join menu_item 
on menu_item.item_id=a1.menu_item_id  where a1.menu_item_id>0 and a1.is_return_item=0 
and menu_item.major_group=1 group by a1.order_head_id,a1.check_id) as aa 
on  a.order_head_id=aa.order_head_id and a.check_id=aa.check_id  
left join (select a1.order_head_id,a1.check_id,sum(a1.actual_price) 
as major2 from history_order_detail as a1  left join menu_item on menu_item.item_id=a1.menu_item_id  
where a1.menu_item_id>0 and a1.is_return_item=0 and menu_item.major_group=2 
group by a1.order_head_id,a1.check_id) as bb on  a.order_head_id=bb.order_head_id 
and a.check_id=bb.check_id  
left join (select a1.order_head_id,a1.check_id,sum(a1.actual_price) 
as major3 from history_order_detail as a1  left join menu_item on menu_item.item_id=a1.menu_item_id  
where a1.menu_item_id>0 and a1.is_return_item=0 and menu_item.major_group=3 
group by a1.order_head_id,a1.check_id) as cc on  a.order_head_id=cc.order_head_id 
and a.check_id=cc.check_id  
left join (select a1.order_head_id,a1.check_id,sum(a1.actual_price) 
as major4 from history_order_detail as a1  
left join menu_item on menu_item.item_id=a1.menu_item_id  
where a1.menu_item_id>0 and a1.is_return_item=0 and menu_item.major_group=4 
group by a1.order_head_id,a1.check_id) as dd on  a.order_head_id=dd.order_head_id 
and a.check_id=dd.check_id    
where a.order_end_time>s_time and order_end_time<e_time ORDER BY a.order_head_id;
END
;;
DELIMITER ;

-- ----------------------------
-- Procedure structure for `check_ticheng`
-- ----------------------------
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `check_ticheng`(IN s_time datetime,IN e_time datetime,IN s_rvcid INT,IN e_rvcid INT,IN s_number INT,IN e_number INT)
BEGIN
drop table if exists miti;
create table miti(
    order_employee_id integer,
    order_employee_name varchar(50),
    actual_price float,
    quantity float,
    commission_value float,
    commission_type int
) engine memory;
insert into miti select history_order_detail.order_employee_id,history_order_detail.order_employee_name,history_order_detail.actual_price,
history_order_detail.quantity,menu_item.commission_value,menu_item.commission_type from history_order_detail left join menu_item on  
history_order_detail.menu_item_id=menu_item.item_id 
where history_order_detail.actual_price>0 and menu_item.commission_type>0 and history_order_detail.is_return_item=0 and history_order_detail.menu_item_id>0 and  order_head_id in (select distinct order_head_id from history_order_head where order_end_time>=s_time and order_end_time<=e_time and rvc_center_id>=s_rvcid and rvc_center_id<=e_rvcid) and order_employee_id>=s_number and order_employee_id<=e_number;
select DISTINCT m.order_employee_id,employee.employee_last_name,a.quantity,a.jin1,b.actual_price,b.jin2,(ifnull(a.jin1,0)+ifnull(b.jin2,0)) as jin3 from 
(select distinct order_employee_id,order_employee_name from miti) as m left join 
((select order_employee_id,order_employee_name,sum(quantity) as quantity,sum(quantity*commission_value) as jin1 from miti where  commission_type=1 group by order_employee_id) as a)
on (m.order_employee_id=a.order_employee_id )  left join
((select order_employee_id,order_employee_name,sum(actual_price) as actual_price,sum(actual_price*commission_value) as jin2 from miti where  commission_type=2 group by order_employee_id) as b)
on (m.order_employee_id=b.order_employee_id )
LEFT JOIN employee ON employee.employee_id = m.order_employee_id
order by m.order_employee_id;
END
;;
DELIMITER ;

-- ----------------------------
-- Procedure structure for `check_ticheng_detail`
-- ----------------------------
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `check_ticheng_detail`(IN s_time datetime,IN e_time datetime,IN s_rvcid INT,IN e_rvcid INT,IN s_number INT,IN e_number INT)
BEGIN
drop table if exists miti;
create table miti(
    order_employee_id integer,
    order_employee_name varchar(50),
		menu_item_id int,
		menu_item_name VARCHAR(60),
    actual_price float,
    quantity float,
    commission_value float,
    commission_type int
) engine memory;
insert into miti select history_order_detail.order_employee_id,history_order_detail.order_employee_name,history_order_detail.menu_item_id,history_order_detail.menu_item_name,history_order_detail.actual_price,
history_order_detail.quantity,menu_item.commission_value,menu_item.commission_type from history_order_detail left join menu_item on  
history_order_detail.menu_item_id=menu_item.item_id 
where history_order_detail.actual_price>0 and menu_item.commission_type>0 and history_order_detail.is_return_item=0 and history_order_detail.menu_item_id>0 and  order_head_id in (select distinct order_head_id from history_order_head where order_end_time>=s_time and order_end_time<=e_time and rvc_center_id>=s_rvcid and rvc_center_id<=e_rvcid) and order_employee_id>=s_number and order_employee_id<=e_number;
select m.menu_item_id,m.menu_item_name,a.quantity,a.jin1,b.actual_price,b.jin2,(ifnull(a.jin1,0)+ifnull(b.jin2,0)) as jin3 from 
(select distinct menu_item_id,menu_item_name from miti GROUP BY menu_item_id) as m left join 
((select menu_item_id,sum(quantity) as quantity,sum(quantity*commission_value) as jin1 from miti where  commission_type=1 group by menu_item_id) as a)
on (m.menu_item_id=a.menu_item_id )  left join
((select menu_item_id,sum(actual_price) as actual_price,sum(actual_price*commission_value) as jin2 from miti where  commission_type=2 group by menu_item_id) as b)
on (m.menu_item_id=b.menu_item_id )
order by m.menu_item_id;
END
;;
DELIMITER ;

-- ----------------------------
-- Procedure structure for `cost_sum`
-- ----------------------------
DELIMITER ;;
CREATE DEFINER=`root`@`%` PROCEDURE `cost_sum`(IN `s_time` datetime,IN `e_time` datetime,IN `s_rvcid` int,IN `e_rvcid` int)
BEGIN


	DECLARE sum_q,sum_p float default 0;

	select sum(quantity),sum(actual_price) into sum_q,sum_p from history_order_detail 
where order_head_id in 
(select distinct order_head_id from history_order_head 
where order_end_time>=s_time and order_end_time<=e_time 

and rvc_center_id>=s_rvcid and rvc_center_id<=e_rvcid)  and is_return_item=0;

SELECT SUM(cost) from
(SELECT t1.*,
CASE
	WHEN t1.unit=menu_item.unit_2 THEN cost_2*sum_qq
	WHEN t1.unit=menu_item.unit_3 THEN cost_3*sum_qq
	WHEN t1.unit=menu_item.unit_4 THEN cost_4*sum_qq
	WHEN t1.unit=menu_item.unit_5 THEN cost_5*sum_qq
	ELSE cost_1*sum_qq END cost

 FROM menu_item,
	(select menu_item_id,menu_item.item_name1,unit,product_price,sum_qq,

(round(sum_qq/sum_q*100,2)) as sum_qq_avg,sum_pp,

(round(sum_pp/sum_p*100,2)) as sum_pp_avg from (select menu_item_id,menu_item_name,

unit,product_price,ifnull(sum(quantity),0) as sum_qq,ifnull(sum(actual_price),0) as sum_pp 

from history_order_detail where menu_item_id>0 and  order_head_id in (select distinct order_head_id 

from history_order_head where order_end_time>=s_time and order_end_time<=e_time 

and rvc_center_id>=s_rvcid and rvc_center_id<=e_rvcid and is_return_item=0) 
 group by menu_item_id,unit) as a 
LEFT JOIN menu_item ON menu_item.item_id = a.menu_item_id)t1
WHERE menu_item.item_id = t1.menu_item_id)t2
;

END
;;
DELIMITER ;

-- ----------------------------
-- Procedure structure for `customer_num`
-- ----------------------------
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `customer_num`(IN `s_time` datetime,IN `e_time` datetime,IN `s_rvcid` int,IN `e_rvcid` int,IN `s_number` int,IN `e_number` int)
BEGIN
SELECT SUM(customer_num)as cusNum 
FROM(SELECT DISTINCT order_head_id,customer_num FROM history_order_head
WHERE order_end_time>=s_time and order_end_time<=e_time 
and rvc_center_id>=s_rvcid and rvc_center_id<=e_rvcid
)t;
END
;;
DELIMITER ;

-- ----------------------------
-- Procedure structure for `cut_items`
-- ----------------------------
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `cut_items`(IN comp INT,IN tableid INT)
BEGIN
	DECLARE tmp_service,tmp_org,tmp_discount FLOAT DEFAULT 0;
	DECLARE cid,cur_state INT DEFAULT 0;
	DECLARE cur CURSOR FOR SELECT check_id FROM order_head where order_head_id=comp;
	DECLARE CONTINUE HANDLER FOR NOT FOUND set cur_state=1;
	OPEN cur;
	REPEAT
		FETCH cur INTO cid;
		IF cur_state=0 THEN
			SELECT COALESCE( SUM(actual_price),0) into tmp_service from order_detail where order_head_id=comp and check_id=cid and menu_item_id=-1 and is_return_item=0; 
			SELECT COALESCE( SUM(actual_price),0) into tmp_org from order_detail where order_head_id=comp and check_id=cid and menu_item_id>0 and is_return_item=0;
			SELECT COALESCE( SUM(actual_price),0) into tmp_discount from order_detail where order_head_id=comp and check_id=cid and menu_item_id=-2 and is_return_item=0; 
			UPDATE order_head SET service_amount=tmp_service,original_amount=tmp_org,discount_amount=tmp_discount,order_end_time=IF(order_end_time IS NULL, NOW(),order_end_time)
			,should_amount=original_amount+service_amount+discount_amount where order_head_id=comp and check_id=cid; 
		END IF;
		UNTIL cur_state
	END REPEAT;
	CLOSE cur;
	UPDATE order_head SET table_id=raw_talbe,raw_talbe=0 WHERE raw_talbe>0 AND order_head_id=comp;
	INSERT INTO history_order_head select * from order_head where order_head_id=comp;
	DELETE FROM order_head where order_head_id=comp;
	INSERT INTO history_order_detail select * from order_detail where order_head_id=comp;
	DELETE FROM order_detail where order_head_id=comp;
	UPDATE tables SET table_status=0 WHERE table_id= tableid;
END
;;
DELIMITER ;

-- ----------------------------
-- Procedure structure for `employee_item_sales`
-- ----------------------------
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `employee_item_sales`(IN `s_time` datetime,IN `e_time` datetime,IN `s_rvcid` int,IN `e_rvcid` int,IN `s_number` int,IN `e_number` int)
BEGIN
	select menu_item_id,menu_item_name,product_price,unit,ifnull(sum(quantity),0) as sum_qq,ifnull(sum(actual_price),0) as sum_pp from history_order_detail where menu_item_id>0 and is_return_item=0 and  order_head_id in (select distinct order_head_id from history_order_head where order_end_time>=s_time and order_end_time<=e_time and rvc_center_id>=s_rvcid and rvc_center_id<=e_rvcid) and order_employee_id>=s_number and order_employee_id<=e_number group by menu_item_id;
END
;;
DELIMITER ;

-- ----------------------------
-- Procedure structure for `employee_sales`
-- ----------------------------
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `employee_sales`(IN `s_time` datetime,IN `e_time` datetime,IN `s_rvcid` int,IN `e_rvcid` int,IN `s_number` int,IN `e_number` int)
BEGIN
select emp_id,emp_name,total,cus_total,round(total/cus_total,2) 
as cus_avg,checks,round(total/checks,2) as checks_avg,
tables,round(total/tables,2) as tables_avg 
from (select open_employee_id as emp_id,open_employee_name as emp_name,
sum(should_amount) as total,
count(order_head_id) as checks,count(distinct(order_head_id)) as tables 
from history_order_head where order_end_time>=s_time 
and order_end_time<=e_time and rvc_center_id>=s_rvcid 
and rvc_center_id<=e_rvcid and open_employee_id>=s_number 
and open_employee_id<=e_number group by open_employee_id)as tableone
LEFT JOIN(select open_employee_id as emp_id1,SUM(customer_num)as cus_total
FROM(SELECT open_employee_id,customer_num FROM history_order_head 
where order_end_time>=s_time 
and order_end_time<=e_time and rvc_center_id>=s_rvcid 
and rvc_center_id<=e_rvcid and open_employee_id>=s_number 
and open_employee_id<=e_number GROUP BY order_head_id)ttt1 GROUP BY emp_id1
)ttt2 ON ttt2.emp_id1=tableone.emp_id
 order by emp_id;
END
;;
DELIMITER ;

-- ----------------------------
-- Procedure structure for `family_group_analysis`
-- ----------------------------
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `family_group_analysis`(IN `s_time` datetime,IN `e_time` datetime,IN `s_rvcid` int,IN `e_rvcid` int)
BEGIN
	BEGIN
	declare sum_q,sum_p float;
	select sum(quantity),sum(actual_price) into sum_q,sum_p from history_order_detail where menu_item_id>0 and is_return_item=0 and  order_head_id in (select distinct order_head_id from history_order_head where order_end_time>=s_time and order_end_time<=e_time and rvc_center_id>=s_rvcid and rvc_center_id<=e_rvcid);
		select a.family_group_id as 'ID',`family_group_name` AS '名称',sum(count) AS '数量',sum(count_per) AS '数量百分比(%)',sum(total) AS '金额',sum(total_per) AS '金额百分比(%)' from ((select family_group_id,count,count_per,total,total_per from ((select family_group_id,0 as count,0 as count_per,0 as total,0 as total_per from family_group) union (select family_group,sum(quantity),(round(sum(quantity)/sum_q*100,2)),sum(actual_price),(round(sum(actual_price)/sum_p*100,2)) from history_order_detail left join menu_item on history_order_detail.menu_item_id=menu_item.item_id where menu_item_id>0 and is_return_item=0 and  order_head_id in (select distinct order_head_id from history_order_head where order_end_time>=s_time and order_end_time<=e_time and rvc_center_id>=s_rvcid and rvc_center_id<=e_rvcid) group by family_group)) as tableone order by family_group_id,count desc) as a left join (select family_group_id,`family_group_name` from family_group) as b on a.family_group_id=b.family_group_id) group by a.family_group_id;
END;
END
;;
DELIMITER ;

-- ----------------------------
-- Procedure structure for `flush_order`
-- ----------------------------
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `flush_order`(IN head_id INT,IN tableid INT)
BEGIN
	declare rows INT default -1;
	SELECT count(*) into rows FROM order_detail WHERE order_head_id=head_id;
	IF rows=0 THEN
    INSERT INTO history_order_detail select * from order_detail WHERE order_head_id=head_id AND is_return_item=1;
	  DELETE FROM order_detail WHERE order_head_id=head_id AND is_return_item=1;
		DELETE FROM order_head WHERE order_head_id=head_id;
		UPDATE tables SET table_status=1 WHERE table_id= tableid;
	END IF;
END
;;
DELIMITER ;

-- ----------------------------
-- Procedure structure for `group_item_sales`
-- ----------------------------
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `group_item_sales`(IN `s_time` datetime,IN `e_time` datetime,IN `s_rvcid` int,IN `e_rvcid` int,IN `s_number` int,IN `e_number` int)
BEGIN
	DECLARE sum_q,sum_p float default 0;
	select sum(quantity),sum(actual_price) into sum_q,sum_p from history_order_detail,menu_item where order_head_id in 
(select distinct order_head_id from history_order_head where order_end_time>=s_time and order_end_time<=e_time 
and rvc_center_id>=s_rvcid and rvc_center_id<=e_rvcid) and item_id=menu_item_id 
and slu_id>=s_number and slu_id<=e_number and is_return_item=0;
	select menu_item_id,menu_item_name,unit,product_price,sum_qq,
(round(sum_qq/sum_q*100,2)) as sum_qq_avg,sum_pp,
(round(sum_pp/sum_p*100,2)) as sum_pp_avg from (select menu_item_id,menu_item_name,
unit,product_price,round(ifnull(sum(quantity),0),2) as sum_qq,ifnull(sum(actual_price),0) as sum_pp 
from history_order_detail,menu_item where menu_item_id>0 and item_id = menu_item_id and  order_head_id in (select distinct order_head_id 
from history_order_head where order_end_time>=s_time and order_end_time<=e_time 
and rvc_center_id>=s_rvcid and rvc_center_id<=e_rvcid and is_return_item=0) and slu_id>=s_number 
and slu_id<=e_number group by menu_item_id) as a ;
END
;;
DELIMITER ;

-- ----------------------------
-- Procedure structure for `item_sales`
-- ----------------------------
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `item_sales`(IN `s_time` datetime,IN `e_time` datetime,IN `s_rvcid` int,IN `e_rvcid` int,IN `s_number` int,IN `e_number` int)
BEGIN


	DECLARE sum_q,sum_p float default 0;

	select sum(quantity),sum(actual_price) into sum_q,sum_p from history_order_detail 
where order_head_id in 
(select distinct order_head_id from history_order_head 
where order_end_time>=s_time and order_end_time<=e_time 

and rvc_center_id>=s_rvcid and rvc_center_id<=e_rvcid) and menu_item_id>=s_number 
and menu_item_id<=e_number and is_return_item=0;

SELECT t1.*,
CASE
	WHEN t1.unit=menu_item.unit_2 THEN cost_2*sum_qq
	WHEN t1.unit=menu_item.unit_3 THEN cost_3*sum_qq
	WHEN t1.unit=menu_item.unit_4 THEN cost_4*sum_qq
	WHEN t1.unit=menu_item.unit_5 THEN cost_5*sum_qq
	ELSE cost_1*sum_qq END cost

 FROM menu_item,
	(select menu_item_id,menu_item.item_name1,unit,product_price,sum_qq,

(round(sum_qq/sum_q*100,2)) as sum_qq_avg,sum_pp,

(round(sum_pp/sum_p*100,2)) as sum_pp_avg from (select menu_item_id,menu_item_name,

unit,product_price,ifnull(sum(quantity),0) as sum_qq,ifnull(sum(actual_price),0) as sum_pp 

from history_order_detail where menu_item_id>0 and  order_head_id in (select distinct order_head_id 

from history_order_head where order_end_time>=s_time and order_end_time<=e_time 

and rvc_center_id>=s_rvcid and rvc_center_id<=e_rvcid and is_return_item=0) 
and menu_item_id>=s_number 
and menu_item_id<=e_number group by menu_item_id,unit) as a 
LEFT JOIN menu_item ON menu_item.item_id = a.menu_item_id)t1
WHERE menu_item.item_id = t1.menu_item_id
;


END
;;
DELIMITER ;

-- ----------------------------
-- Procedure structure for `item_sales_desc`
-- ----------------------------
DELIMITER ;;
CREATE DEFINER=`root`@`%` PROCEDURE `item_sales_desc`(IN `s_time` datetime,IN `e_time` datetime,IN `s_rvcid` int,IN `e_rvcid` int,IN `s_number` int,IN `e_number` int)
BEGIN
	DECLARE sum_q,sum_p float default 0;
	select sum(quantity),sum(actual_price) into sum_q,sum_p from history_order_detail 
where order_head_id in 
(select distinct order_head_id from history_order_head 
where order_end_time>=s_time and order_end_time<=e_time 
and rvc_center_id>=s_rvcid and rvc_center_id<=e_rvcid) and menu_item_id>=s_number 
and menu_item_id<=e_number and is_return_item=0;
	select menu_item_id,menu_item.item_name1,unit,product_price,sum_qq,
(round(sum_qq/sum_q*100,2)) as sum_qq_avg,sum_pp,
(round(sum_pp/sum_p*100,2)) as sum_pp_avg from (select menu_item_id,menu_item_name,
unit,product_price,ifnull(sum(quantity),0) as sum_qq,ifnull(sum(actual_price),0) as sum_pp 
from history_order_detail where menu_item_id>0 and  order_head_id in (select distinct order_head_id 
from history_order_head where order_end_time>=s_time and order_end_time<=e_time 
and rvc_center_id>=s_rvcid and rvc_center_id<=e_rvcid and is_return_item=0) 
and menu_item_id>=s_number 
and menu_item_id<=e_number group by menu_item_id) as a 
LEFT JOIN menu_item ON menu_item.item_id = a.menu_item_id  ORDER BY sum_pp DESC;
END
;;
DELIMITER ;

-- ----------------------------
-- Procedure structure for `join_table`
-- ----------------------------
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `join_table`(IN table_from INT,IN table_dest INT,OUT rcode INT)
top:BEGIN
	declare from_rows,dest_rows,rows,lp,cur_state,check_itr,check_row,order_id,order_old,check_num,ismake1,ismake2 INT;
  declare des_table_name varchar(10);
	DECLARE cur CURSOR FOR SELECT check_id FROM order_head where table_id=table_from;
	DECLARE CONTINUE HANDLER FOR NOT FOUND set cur_state=-1 ;
	DECLARE CONTINUE HANDLER FOR SQLSTATE 'HY000' set rcode=-3;
	DECLARE EXIT HANDLER FOR SQLSTATE '23000' rollback;
	select count(*) into rows FROM order_head where table_id in(table_from,table_dest);
	IF rows>8 THEN
		set rcode=-1;
		leave top;
	END IF;
	select count(*) into dest_rows FROM order_head where table_id=table_dest;
	select count(*) into from_rows FROM order_head where table_id=table_from;
	if dest_rows*from_rows=0 THEN
		set rcode=-2;
		leave top;
	END IF;
START TRANSACTION;
	select sum(customer_num) into rows FROM (select distinct table_id,customer_num from order_head where table_id in(table_from,table_dest) order by table_id) AS tableone;
	set lp=0;
	set rcode=-4;
	select order_head_id,check_number,table_name,is_make into order_id,check_num,des_table_name,ismake1 from order_head where table_id=table_dest group by table_id;
	select order_head_id,is_make into order_old,ismake2 from order_head where table_id=table_from group by table_id;
	IF ISNULL(ismake1) OR ismake1=0 OR ISNULL(ismake2) OR ismake2=0 THEN
			SET ismake1=0;
	END IF;
	OPEN cur;
	REPEAT
		FETCH cur into check_itr;
		loop_label:LOOP
			set lp=lp+1;
			select count(*) into check_row FROM order_head where table_id=table_dest and check_id=lp;
			IF lp>8 THEN
				leave loop_label;
			END IF;
			IF check_row=0 THEN
				update order_head SET table_id=table_dest,check_id=lp,order_head_id=order_id,check_number=check_num,table_name=des_table_name where table_id=table_from and check_id=check_itr;
				update order_detail SET check_id=lp,order_head_id=order_id where check_id=check_itr and order_head_id=order_old;
				leave loop_label;
			END IF;
		END LOOP;
		UNTIL cur_state=-1
	END REPEAT;
	CLOSE cur;
	UPDATE payment SET order_head_id=order_id WHERE order_head_id=order_old;
	update order_head SET customer_num=rows,is_make=ismake1 where table_id=table_dest;
	UPDATE tables SET table_status=1 WHERE table_id=table_from;
	COMMIT;
	set rcode=0;
END
;;
DELIMITER ;

-- ----------------------------
-- Procedure structure for `join_table_1`
-- ----------------------------
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `join_table_1`(IN table_from INT,IN table_dest INT,OUT rcode INT)
top:BEGIN
	declare from_rows,dest_rows,rows,cur_state,check_itr,order_id,order_old,ismake1,ismake2 INT;
	declare payed_amount FLOAT;
	DECLARE cur CURSOR FOR SELECT check_id FROM order_head where table_id=table_from;
	DECLARE CONTINUE HANDLER FOR NOT FOUND set cur_state=-1 ;
	DECLARE CONTINUE HANDLER FOR SQLSTATE 'HY000' set rcode=-3;
	DECLARE EXIT HANDLER FOR SQLSTATE '23000' rollback;
	select count(*) into dest_rows FROM order_head where table_id=table_dest;
	select count(*) into from_rows FROM order_head where table_id=table_from;
	IF dest_rows*from_rows=0 THEN
		set rcode=-2;
		leave top;
	END IF;
START TRANSACTION;
	select sum(customer_num) into rows FROM (select distinct table_id,customer_num from order_head where table_id in(table_from,table_dest) order by table_id) AS tableone;
	set rcode=-4;
	select order_head_id,is_make into order_id,ismake1 from order_head where table_id=table_dest group by table_id;
	select order_head_id,is_make into order_old,ismake2 from order_head where table_id=table_from group by table_id;
  select sum(actual_amount) into payed_amount from order_head where table_id =table_from;
	IF ISNULL(ismake1) OR ismake1=0 OR ISNULL(ismake2) OR ismake2=0 THEN
			SET ismake1=0;
	END IF;
	OPEN cur;
	REPEAT
		FETCH cur into check_itr;
				update order_detail SET check_id=1,order_head_id=order_id where check_id=check_itr and order_head_id=order_old;
		UNTIL cur_state=-1
	END REPEAT;
	UPDATE payment SET order_head_id=order_id WHERE order_head_id=order_old;
	DELETE FROM order_head  where table_id=table_from;
	CLOSE cur;
	update order_head SET customer_num=rows,is_make=ismake1 where table_id=table_dest;
	update order_head SET actual_amount=actual_amount+payed_amount where table_id=table_dest AND check_id=1;
	UPDATE tables SET table_status=1 WHERE table_id=table_from;
	COMMIT;
	set rcode=0;
END
;;
DELIMITER ;

-- ----------------------------
-- Procedure structure for `maingroup_item_sales`
-- ----------------------------
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `maingroup_item_sales`(IN `s_time` datetime,IN `e_time` datetime,IN `s_rvcid` int,IN `e_rvcid` int,IN `s_number` int,IN `e_number` int)
BEGIN
	DECLARE sum_q,sum_p float default 0;
	select sum(quantity),sum(actual_price) into sum_q,sum_p from history_order_detail,menu_item,item_main_group where order_head_id in 
(select distinct order_head_id from history_order_head where order_end_time>=s_time and order_end_time<=e_time 
and rvc_center_id>=s_rvcid and rvc_center_id<=e_rvcid) and item_id=menu_item_id 
and main_group_id>=s_number and main_group_id<=e_number and is_return_item=0 and slu_id=second_group_id AND second_group_id != -1;
	select menu_item_id,menu_item_name,unit,product_price,sum_qq,
(round(sum_qq/sum_q*100,2)) as sum_qq_avg,sum_pp,
(round(sum_pp/sum_p*100,2)) as sum_pp_avg from (select menu_item_id,menu_item_name,
unit,product_price,round(ifnull(sum(quantity),0),2) as sum_qq,ifnull(sum(actual_price),0) as sum_pp 
from history_order_detail,menu_item,item_main_group where menu_item_id>0 and item_id = menu_item_id and  order_head_id in (select distinct order_head_id 
from history_order_head where order_end_time>=s_time and order_end_time<=e_time 
and rvc_center_id>=s_rvcid and rvc_center_id<=e_rvcid and is_return_item=0) and main_group_id>=s_number 
and main_group_id<=e_number and slu_id=second_group_id AND second_group_id != -1
 group by menu_item_id) as a ;
END
;;
DELIMITER ;

-- ----------------------------
-- Procedure structure for `major_group_analysis`
-- ----------------------------
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `major_group_analysis`(IN `s_time` datetime,IN `e_time` datetime,IN `s_rvcid` int,IN `e_rvcid` int)
BEGIN
	BEGIN
	declare sum_q,sum_p float;
	select sum(quantity),sum(actual_price) into sum_q,sum_p 
from history_order_detail where menu_item_id>0 and is_return_item=0 
and  order_head_id in (select distinct order_head_id from history_order_head where order_end_time>=s_time and order_end_time<=e_time and rvc_center_id>=s_rvcid and rvc_center_id<=e_rvcid);
		select a.major_group_id as 'ID',`major_group_name` AS '名称',sum(count) AS '数量',sum(count_per) AS '数量百分比(%)',sum(total) AS '金额',sum(total_per) AS '金额百分比(%)' from ((select major_group_id,count,count_per,total,total_per from ((select major_group_id,0 as count,0 as count_per,0 as total,0 as total_per from major_group) union (select major_group,sum(quantity),(round(sum(quantity)/sum_q*100,2)),sum(actual_price),(round(sum(actual_price)/sum_p*100,2)) from history_order_detail left join menu_item on history_order_detail.menu_item_id=menu_item.item_id where menu_item_id>0 and is_return_item=0 and  order_head_id in (select distinct order_head_id from history_order_head where order_end_time>=s_time and order_end_time<=e_time and rvc_center_id>=s_rvcid and rvc_center_id<=e_rvcid) group by major_group)) as tableone order by major_group_id,count desc) as a left join (select major_group_id,`major_group_name` from major_group) as b on a.major_group_id=b.major_group_id) group by a.major_group_id;
END;
END
;;
DELIMITER ;

-- ----------------------------
-- Procedure structure for `move_check`
-- ----------------------------
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `move_check`(IN table_from INT,IN check_from INT,IN table_dest INT,OUT rcode INT)
top:BEGIN
	declare dest_rows,from_rows,lp,check_row,customer_old,customer_dest,order_id,order_old,check_num,ismake1,ismake2 INT;
	declare des_table_name varchar(10);
	DECLARE CONTINUE HANDLER FOR SQLSTATE 'HY000' set rcode=-3;
	DECLARE EXIT HANDLER FOR SQLSTATE '23000' rollback;
	select count(*) into dest_rows FROM order_head where table_id=table_dest;
	IF dest_rows>7 THEN
		set rcode=-1;
		leave top;
	END IF;
	START TRANSACTION;
		set lp=0;
		set rcode=-4;
		select order_head_id,check_number,table_name,is_make into order_id,check_num,des_table_name,ismake1 from order_head where table_id=table_dest group by table_id;
		select order_head_id,is_make into order_old,ismake1 from order_head where table_id=table_from group by table_id;
		select count(*) into from_rows from order_head where table_id=table_from;
		select customer_num into customer_dest from order_head where table_id=table_dest limit 1;
		IF from_rows=1 THEN
			select customer_num into customer_old from order_head where table_id=table_from limit 1;
			set customer_dest=customer_dest+customer_old;
		END IF;
		IF ISNULL(ismake1) OR ismake1=0 OR ISNULL(ismake2) OR ismake2=0 THEN
			SET ismake1=0;
		END IF;
		loop_label:LOOP
			set lp=lp+1;
			select count(*) into check_row FROM order_head where table_id=table_dest and check_id=lp;
			IF lp>8 THEN
				leave loop_label;
			END IF;
			IF check_row=0 THEN
				update order_head SET table_id=table_dest,check_id=lp,order_head_id=order_id,check_number=check_num,table_name=des_table_name where table_id=table_from and check_id=check_from;
				update order_detail SET check_id=lp,order_head_id=order_id where check_id=check_from and order_head_id=order_old;
				leave loop_label;
			END IF;
		END LOOP;
	  UPDATE payment SET order_head_id=order_id WHERE order_head_id=order_old;
		update order_head set customer_num=customer_dest,is_make=ismake1 where table_id=table_dest;
		CALL flush_order(order_old,table_from);
	COMMIT;
	set rcode=0;
END
;;
DELIMITER ;

-- ----------------------------
-- Procedure structure for `move_check_1`
-- ----------------------------
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `move_check_1`(IN table_from INT,IN check_from INT,IN table_dest INT,OUT rcode INT)
top:BEGIN
	declare customer_old,customer_dest,order_id,order_old,ismake1,ismake2 INT;
	declare payed_old,payed_dest FLOAT;
	DECLARE CONTINUE HANDLER FOR SQLSTATE 'HY000' set rcode=-3;
	DECLARE EXIT HANDLER FOR SQLSTATE '23000' rollback;
	START TRANSACTION;
		set rcode=-4;
		select order_head_id,customer_num,is_make into order_id,customer_dest,ismake1 from order_head where table_id=table_dest group by table_id;
		select order_head_id,customer_num,is_make into order_old,customer_old,ismake2 from order_head where table_id=table_from group by table_id;

		IF ISNULL(ismake1) OR ismake1=0 OR ISNULL(ismake2) OR ismake2=0 THEN
			SET ismake1=0;
		END IF;
		set customer_dest=customer_dest+customer_old;
		select actual_amount into payed_old from order_head where table_id =table_from and check_id=check_from;
		DELETE FROM order_head  where table_id=table_from and check_id=check_from;
		update order_detail SET check_id=1,order_head_id=order_id where check_id=check_from and order_head_id=order_old;
		UPDATE payment SET order_head_id=order_id WHERE order_head_id=order_old;
		update order_head set customer_num=customer_dest,is_make=ismake1 where table_id=table_dest;
	  update order_head set actual_amount=actual_amount+payed_old where table_id=table_dest and check_id=1;
		CALL flush_order(order_old,table_from);
	COMMIT;
	set rcode=0;
END
;;
DELIMITER ;

-- ----------------------------
-- Procedure structure for `open_table`
-- ----------------------------
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `open_table`(IN in_table_id int)
BEGIN
	DECLARE tmp_price,tmp_quantity FLOAT DEFAULT 0;
	DECLARE tmp_actual_price FLOAT DEFAULT 0;
	DECLARE tmp_item_id,cur_state,cus_num,head_id,employee_id,device_id INT DEFAULT 0;
	DECLARE tmp_unit varchar(10);
	DECLARE tmp_name,employee_name varchar(30);
	DECLARE cur CURSOR FOR SELECT menu_item_id,menu_item_name,quantity,price,unit FROM order_detail_default;
	DECLARE CONTINUE HANDLER FOR NOT FOUND set cur_state=1;
	SELECT order_head_id,customer_num,open_employee_id,open_employee_name,pos_device_id INTO 
		head_id,cus_num,employee_id,employee_name,device_id FROM order_head WHERE table_id =in_table_id  limit 1;
	OPEN cur;
	REPEAT
		FETCH cur INTO tmp_item_id,tmp_name,tmp_quantity,tmp_price,tmp_unit;
		IF cur_state=0 THEN
			IF tmp_quantity<0 THEN
				SET tmp_quantity=cus_num;
			END IF;
			SET tmp_actual_price=tmp_quantity*tmp_price;
			INSERT INTO order_detail(order_head_id,menu_item_id,menu_item_name,product_price,unit,actual_price,quantity,order_time,check_id,order_employee_id,order_employee_name,pos_device_id)
			VALUES(head_id ,tmp_item_id,tmp_name,tmp_price,tmp_unit,tmp_actual_price,tmp_quantity,NOW(),1,employee_id,employee_name,device_id);
		END IF;
		UNTIL cur_state
	END REPEAT;
	CLOSE cur;
END
;;
DELIMITER ;

-- ----------------------------
-- Procedure structure for `order_type_sails`
-- ----------------------------
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `order_type_sails`(IN `s_time` datetime,IN `e_time` datetime,IN `s_rvcid` int,IN `e_rvcid` int)
BEGIN
	DECLARE should_total,customer_total,checks_total,tables_total FLOAT;
	select ifnull(sum(should_amount),0),count(*),
count(distinct(order_head_id)) into should_total,checks_total,tables_total 
from history_order_head where order_end_time>=s_time and order_end_time<=e_time and rvc_center_id>=s_rvcid 
and rvc_center_id<=e_rvcid;
  select ifnull(sum(customer_num),0) into customer_total FROM
(SELECT customer_num from history_order_head where order_end_time>=s_time 
and order_end_time<=e_time and rvc_center_id>=s_rvcid 
and rvc_center_id<=e_rvcid GROUP BY order_head_id)tttTmp;
select count(*),count(distinct(order_head_id)) into checks_total,tables_total 
from history_order_head where order_end_time>=s_time and order_end_time<=e_time 
and rvc_center_id>=s_rvcid and rvc_center_id<=e_rvcid ;
select order_type_id,order_type_name,ifnull(sales,0),
ifnull(concat(round(sales/should_total*100,2),'%'),'0.00%') as '% of Ttl',
ifnull(guests,0),ifnull(concat(round(guests/customer_total*100,2),'%'),'0.00%') as '% if Ttl',
ifnull(round(sales/guests,2),0.00) as 'Avg/Guest',ifnull(checks,0),
ifnull(concat(round(checks/checks_total*100,2),'%'),'0.00%') as '% of Ttl',
ifnull(round(sales/checks,2),0.00) as 'Avg/Chk',ifnull(tables,0),
ifnull(concat(round(tables/tables_total*100,2),'%'),'0.00%') as '% of Ttl',
ifnull(round(sales/tables,2),0.00) as 'Avg/Tbl',ifnull(time_total,0),
ifnull(round(time_total/tables,2),0.00) as 'Avg/Time' 
from (select eat_type,sum(should_amount) as sales,
count(*) as checks,
count(distinct(order_head_id)) as tables from history_order_head 
where order_end_time>=s_time and order_end_time<=e_time 
and rvc_center_id>=s_rvcid and rvc_center_id<=e_rvcid group by eat_type) 
as tableone 
LEFT JOIN(SELECT eat_type,SUM(customer_num)as guests FROM (SELECT eat_type,customer_num
FROM history_order_head where order_end_time>=s_time and order_end_time<=e_time 
and rvc_center_id>=s_rvcid and rvc_center_id<=e_rvcid GROUP BY order_head_id)tmpT1 GROUP BY eat_type)tmpT 
ON tableone.eat_type = tmpT.eat_type
right outer join order_types on tableone.eat_type=order_types.order_type_id 
left outer join (select eat_type,sum(eat_time) as time_total 
from (select order_head_id,eat_type,TimeStampDiff(MINUTE,min(order_end_time),max(order_end_time)) as eat_time 
from history_order_head where order_end_time>=s_time and order_end_time<=e_time 
and rvc_center_id>=s_rvcid and rvc_center_id<=e_rvcid group by order_head_id) as tablea group by eat_type) 
as timetable on order_types.order_type_id=timetable.eat_type;
END
;;
DELIMITER ;

-- ----------------------------
-- Procedure structure for `pay_style`
-- ----------------------------
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `pay_style`(IN `s_time` datetime,IN `e_time` datetime,IN `s_rvcid` int,IN `e_rvcid` int)
BEGIN
	DECLARE sum_total INT default 0;
	select sum(total) into sum_total from payment where order_head_id in (select distinct order_head_id from history_order_head where order_end_time>=s_time and order_end_time<=e_time and rvc_center_id>=s_rvcid and rvc_center_id<=e_rvcid);
	select tender_media.tender_media_id,tender_media_name,ifnull(total,0) AS total,
IFNULL(round(ifnull(total,0)/sum_total*100,2),0) as total_avg,round(total*extra_amout/100,2)  as sum_extra
from (select tender_media_id,round(sum(total),2) as total from payment  where order_head_id in (select distinct order_head_id from history_order_head where order_end_time>=s_time and order_end_time<=e_time and rvc_center_id>=s_rvcid and rvc_center_id<=e_rvcid) group by tender_media_id) as a right outer join tender_media on tender_media.tender_media_id=a.tender_media_id;
END
;;
DELIMITER ;

-- ----------------------------
-- Procedure structure for `return_item_list`
-- ----------------------------
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `return_item_list`(IN `s_time` datetime,IN `e_time` datetime,IN `s_rvcid` int,IN `e_rvcid` int,IN `s_number` int,IN `e_number` int)
BEGIN
	select rvc_center_id as rvc_id,
rvc_center_name as rvc_name,table_id as table_id,
table_name as table_name,
history_order_detail.order_head_id as order_head_id,
history_order_detail.check_id as check_id,
history_order_head.check_number as chk_num,
order_employee_id,order_employee_name,menu_item_id,menu_item_name,
return_time,abs(actual_price) as actual_price,abs(quantity) as quty,
return_reason,auth_id,auth_name from history_order_detail,history_order_head 
where history_order_detail.order_head_id=history_order_head.order_head_id AND history_order_detail.check_id=history_order_head.check_id
and (is_return_item=1 OR quantity<0) and  menu_item_id>0 
and history_order_detail.return_time >=s_time
and history_order_detail.return_time <=e_time
and history_order_head.rvc_center_id>=s_rvcid and history_order_head.rvc_center_id<=e_rvcid
and history_order_detail.order_employee_id>=s_number 
and history_order_detail.order_employee_id<=e_number 
order by history_order_detail.order_employee_id;
END
;;
DELIMITER ;

-- ----------------------------
-- Procedure structure for `revert_check`
-- ----------------------------
DELIMITER ;;
CREATE DEFINER=`root`@`%` PROCEDURE `revert_check`(IN headid INT,IN checkid INT)
BEGIN
	DECLARE tableid,cur_state INT DEFAULT 0;
	INSERT INTO order_head select * from history_order_head where order_head_id=headid AND check_id=checkid;
	DELETE FROM history_order_head where order_head_id=headid AND check_id=checkid;
	INSERT INTO order_detail select * from history_order_detail where order_head_id=headid AND check_id=checkid;
	DELETE FROM history_order_detail where order_head_id=headid AND check_id=checkid;
	UPDATE order_head SET status=0 WHERE order_head_id=headid AND check_id=checkid;
	SELECT table_id into tableid from order_head where order_head_id=headid;
	UPDATE tables SET table_status=2 WHERE table_id=tableid;
	UPDATE order_head SET edit_time=NOW() WHERE order_head_id=headid AND check_id=checkid;
END
;;
DELIMITER ;

-- ----------------------------
-- Procedure structure for `sail_pre_list`
-- ----------------------------
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `sail_pre_list`(IN `s_time` datetime,IN `e_time` datetime)
BEGIN
	select base.sail_employee_id,sail_employee_name,
(ifnull(sta4.ct,0)+ifnull(sta2.ct,0)+ifnull(sta3.ct,0)) as total,
ifnull(sta4.ct,0) as receive,ifnull(sta2.ct,0) as cancel,
ifnull(sta3.ct,0) as notre,base.amount 
from (((select sail_employee_id,sail_employee_name,sum(amount) as amount
 from pre_order where preorder_time>=s_time and preorder_time<=e_time 
group by sail_employee_id) as base left join 
(select sail_employee_id,count(*) as ct from pre_order 
where pre_order_status=2 group by sail_employee_id) as sta2 
on base.sail_employee_id=sta2.sail_employee_id) 
left join (select sail_employee_id,count(*) as ct from pre_order 
where pre_order_status=3 group by sail_employee_id) as sta3 
on base.sail_employee_id=sta3.sail_employee_id) 
left join (select sail_employee_id,count(*) as ct from pre_order 
where pre_order_status=4 group by sail_employee_id) as sta4 
on base.sail_employee_id=sta4.sail_employee_id;
END
;;
DELIMITER ;

-- ----------------------------
-- Procedure structure for `sales_analysis`
-- ----------------------------
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `sales_analysis`(IN `s_time` datetime,IN `e_time` datetime,IN `s_rvcid` int,IN `e_rvcid` int)
BEGIN
	DECLARE sales_detail_total,service_total,discount_total,return_item_total,should_total,actual_total,tax_total FLOAT;
	select ifnull(sum(actual_price),0) into sales_detail_total from history_order_detail where is_return_item=0 and menu_item_id>0 and  order_head_id in (select distinct order_head_id from history_order_head where order_end_time>=s_time and order_end_time<=e_time and rvc_center_id>=s_rvcid and rvc_center_id<=e_rvcid);
	select ifnull(sum(service_amount),0) into service_total from history_order_head where order_end_time>=s_time and order_end_time<=e_time and rvc_center_id>=s_rvcid and rvc_center_id<=e_rvcid;
	select sum(ifnull(discount_amount,0)) into discount_total from history_order_head where order_end_time>=s_time and order_end_time<=e_time and rvc_center_id>=s_rvcid and rvc_center_id<=e_rvcid ;
	select sum(abs(ifnull(actual_price,0))) into return_item_total from history_order_detail where (is_return_item=1 OR quantity<0) and menu_item_id>0 and return_time>=s_time and return_time<=e_time;
	select ifnull(sum(should_amount),0) into should_total from history_order_head where order_end_time>=s_time and order_end_time<=e_time and rvc_center_id>=s_rvcid and rvc_center_id<=e_rvcid;
	select ifnull(sum(actual_amount),0) into actual_total from history_order_head where order_end_time>=s_time and order_end_time<=e_time and rvc_center_id>=s_rvcid and rvc_center_id<=e_rvcid;
	select ifnull(sum(tax_amount),0) into tax_total from history_order_head where order_end_time>=s_time and order_end_time<=e_time and rvc_center_id>=s_rvcid and rvc_center_id<=e_rvcid;
  select round(sales_detail_total,2),round(service_total,2),round(discount_total,2),round(return_item_total,2),round(should_total,2),round(actual_total,2),round(tax_total,2); 

END
;;
DELIMITER ;

-- ----------------------------
-- Procedure structure for `sales_analysis_kaitailv`
-- ----------------------------
DELIMITER ;;
CREATE DEFINER=`root`@`%` PROCEDURE `sales_analysis_kaitailv`(IN `s_time` datetime,IN `e_time` datetime,IN `s_rvcid` int,IN `e_rvcid` int)
BEGIN
	DECLARE table_num ,actual_table_num,actual_cus_num,actual_seat_num INT;
	SELECT (SELECT COUNT(*) from `tables` WHERE table_status != 6) INTO table_num;
	SELECT (SELECT sum(seat_num) from `tables` WHERE table_status != 6) INTO actual_seat_num;
SELECT SUM(customer_num)as cusNum INTO actual_cus_num
FROM(SELECT DISTINCT order_head_id,customer_num FROM history_order_head
WHERE order_end_time>=s_time and order_end_time<=e_time 
and rvc_center_id>=s_rvcid and rvc_center_id<=e_rvcid)t;
select count(distinct(order_head_id)) into actual_table_num 
from history_order_head where order_end_time>=s_time and order_end_time<=e_time 
and rvc_center_id>=s_rvcid and rvc_center_id<=e_rvcid ;
	SELECT table_num ,actual_table_num,actual_cus_num,actual_seat_num,
actual_cus_num*1/actual_seat_num as shangzuolv,
actual_table_num*1/table_num as kaitailv;
END
;;
DELIMITER ;

-- ----------------------------
-- Procedure structure for `sales_periods`
-- ----------------------------
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `sales_periods`(IN `s_time` datetime,IN `e_time` datetime,IN `s_rvcid` int,IN `e_rvcid` int,IN `s_number` int,IN `e_number` int)
BEGIN
	DECLARE  cur_state,line INT default 0;
	DECLARE pid INT;
	DECLARE pname varchar(30);
	DECLARE pstime,petime TIME;
	DECLARE sqlcmd,execsql varchar(5000);
	DECLARE sqlcond varchar(300);
	DECLARE cur CURSOR FOR SELECT period_id,period_name,start_time,end_time FROM periods where period_id>=s_number and period_id<=e_number;
	DECLARE CONTINUE HANDLER FOR NOT FOUND set cur_state=1 ;
	OPEN cur;
	REPEAT
		FETCH cur into pid,pname,pstime,petime;
			IF cur_state=0 THEN
				set line=line+1;
				IF pstime>petime THEN
					 set @sqlcond=concat('(time(order_end_time)>''',pstime,''' OR time(order_end_time)<''',petime,''')');
				ELSE
					 set @sqlcond=concat('(time(order_end_time) BETWEEN ''',pstime,''' AND ''',petime,''')');
				END IF;
				IF LINE=1 THEN
					set @sqlcmd=concat('select ',pid,' as period_id,''',pname,''' as period_name,sum(a.should_amount) as total,sum(a.customer_num) as customers_total,round(sum(a.should_amount)/sum(a.customer_num),2) as customer_avg,sum(a.checks_total) as checks_total,round(sum(a.should_amount)/sum(a.checks_total),2) as table_avg,count(a.order_head_id) as tables_total,round(sum(a.should_amount)/count(a.order_head_id),2) as table_avg from (select        
																																				sum(should_amount) as should_amount,customer_num,count(order_head_id) as checks_total,order_head_id from history_order_head    
						where order_end_time>=''',s_time,''' and order_end_time<=''',e_time,''' and rvc_center_id>=',s_rvcid,' and rvc_center_id<=',e_rvcid,' and ',@sqlcond,' group by order_head_id) as a ');
				ELSE
					set @sqlcmd=concat(@sqlcmd,'union select ',pid,' as period_id,''',pname,''' as period_name,sum(a.should_amount) as total,sum(a.customer_num) as customers_total,round(sum(a.should_amount)/sum(a.customer_num),2) as customer_avg,sum(a.checks_total) as checks_total,round(sum(a.should_amount)/sum(a.checks_total),2) as table_avg,count(a.order_head_id) as tables_total,round(sum(a.should_amount)/count(a.order_head_id),2) as table_avg from (select        
																																				sum(should_amount) as should_amount,customer_num,count(order_head_id) as checks_total,order_head_id  from history_order_head    
						where order_end_time>=''',s_time,''' and order_end_time<=''',e_time,''' and rvc_center_id>=',s_rvcid,' and rvc_center_id<=',e_rvcid,' and ',@sqlcond,' group by order_head_id) as a ');
				END IF;
			END IF;
		UNTIL cur_state
	END REPEAT;
	CLOSE cur;
	prepare execsql from @sqlcmd;
  execute execsql;
END
;;
DELIMITER ;

-- ----------------------------
-- Procedure structure for `show_item_material`
-- ----------------------------
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `show_item_material`(IN `param_str` varchar(200))
BEGIN
SELECT item_material.item_id as '菜品ID',item_name1 AS '菜品名称',
GROUP_CONCAT(material_name,':',(round(item_material.num,2)+''),material.material_unit) as '物品'
from item_material,material,menu_item
where 1=1 and item_material.material_id = material.material_id
and menu_item.item_id = item_material.item_id
and (menu_item.item_name1 like CONCAT('%',param_str,'%')
or material_name like CONCAT('%',param_str,'%')
or item_material.material_id like CONCAT('%',param_str,'%')
or item_material.item_id like CONCAT('%',param_str,'%'))
GROUP BY item_material.item_id
ORDER BY item_material.item_id;
END
;;
DELIMITER ;

-- ----------------------------
-- Procedure structure for `show_item_material_2`
-- ----------------------------
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `show_item_material_2`()
BEGIN
SELECT item_material.item_id as '菜品ID',item_name1 AS '菜品名称',
GROUP_CONCAT(material_name,':',(round(item_material.num,2)+'')) as '物品'
from item_material,material,menu_item
where 1=1 and item_material.material_id = material.material_id
and menu_item.item_id = item_material.item_id
GROUP BY item_material.item_id
ORDER BY item_material.item_id;
END
;;
DELIMITER ;

-- ----------------------------
-- Procedure structure for `trans_table`
-- ----------------------------
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `trans_table`(IN table_from INT,IN table_dest INT)
BEGIN
	DECLARE tmp_status INT DEFAULT 0;
	declare tmp_name varchar(10);
	SELECT table_status INTO tmp_status FROM tables WHERE table_id=table_from;
	SELECT table_name INTO tmp_name FROM tables WHERE table_id=table_dest;
	UPDATE order_head SET table_id=table_dest ,table_name=tmp_name WHERE table_id=table_from;
	UPDATE tables SET table_status=tmp_status WHERE table_id=table_dest;
	UPDATE tables SET table_status=1 WHERE table_id=table_from;
END
;;
DELIMITER ;

-- ----------------------------
-- Procedure structure for `update_checknum`
-- ----------------------------
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `update_checknum`(IN device_id INT)
BEGIN
	DECLARE current_num,ncheck_end,ncheck_start INT;
	select check_start,check_end,check_num into ncheck_start,ncheck_end,current_num from user_workstations where workstations_id=device_id;
	IF current_num>=ncheck_end OR current_num<ncheck_start THEN
			UPDATE user_workstations SET check_num=check_start WHERE workstations_id=device_id;
	ELSE
			UPDATE user_workstations SET check_num=check_num+1 WHERE workstations_id=device_id;
	END IF;
END
;;
DELIMITER ;
DELIMITER ;;
CREATE TRIGGER `trigger_soldout_add` AFTER INSERT ON `bargain_price_item` FOR EACH ROW BEGIN
	UPDATE webreport_setting SET soldout = soldout | 2;
END
;;
DELIMITER ;
DELIMITER ;;
CREATE TRIGGER `trigger_soldout_update` AFTER UPDATE ON `bargain_price_item` FOR EACH ROW BEGIN
	UPDATE webreport_setting SET soldout = soldout | 1;
END
;;
DELIMITER ;
DELIMITER ;;
CREATE TRIGGER `trigger_soldout_del` AFTER DELETE ON `bargain_price_item` FOR EACH ROW BEGIN
	UPDATE webreport_setting SET soldout = soldout | 2;
END
;;
DELIMITER ;

-- ----------------------------
-- Auto increment value for `cashbox_in_out`
-- ----------------------------
ALTER TABLE `cashbox_in_out` AUTO_INCREMENT=1;
DELIMITER ;;
CREATE TRIGGER `trigger_condiment_membership_add` AFTER INSERT ON `condiment_membership` FOR EACH ROW BEGIN
	UPDATE webreport_setting SET menu_item = menu_item | 8;
END
;;
DELIMITER ;
DELIMITER ;;
CREATE TRIGGER `trigger_condiment_membership_update` AFTER UPDATE ON `condiment_membership` FOR EACH ROW BEGIN
	UPDATE webreport_setting SET menu_item = menu_item | 8;
END
;;
DELIMITER ;
DELIMITER ;;
CREATE TRIGGER `trigger_condiment_membership_del` AFTER DELETE ON `condiment_membership` FOR EACH ROW BEGIN
	UPDATE webreport_setting SET menu_item = menu_item | 8;
END
;;
DELIMITER ;
DELIMITER ;;
CREATE TRIGGER `trigger_consumption_limit_add` AFTER INSERT ON `consumption_limit` FOR EACH ROW BEGIN
	UPDATE webreport_setting SET tables = tables | 2;
END
;;
DELIMITER ;
DELIMITER ;;
CREATE TRIGGER `trigger_consumption_limit_update` AFTER UPDATE ON `consumption_limit` FOR EACH ROW BEGIN
	UPDATE webreport_setting SET tables = tables | 2;
END
;;
DELIMITER ;
DELIMITER ;;
CREATE TRIGGER `trigger_consumption_limit_del` AFTER DELETE ON `consumption_limit` FOR EACH ROW BEGIN
	UPDATE webreport_setting SET tables = tables | 2;
END
;;
DELIMITER ;
DELIMITER ;;
CREATE TRIGGER `trigger_course_detail_add` AFTER INSERT ON `course_detail` FOR EACH ROW BEGIN
	UPDATE webreport_setting SET menu_item = menu_item | 4;
END
;;
DELIMITER ;
DELIMITER ;;
CREATE TRIGGER `trigger_course_detail_update` AFTER UPDATE ON `course_detail` FOR EACH ROW BEGIN
	UPDATE webreport_setting SET menu_item = menu_item | 4;
END
;;
DELIMITER ;
DELIMITER ;;
CREATE TRIGGER `trigger_course_detail_del` AFTER DELETE ON `course_detail` FOR EACH ROW BEGIN
	UPDATE webreport_setting SET menu_item = menu_item | 4;
END
;;
DELIMITER ;

-- ----------------------------
-- Auto increment value for `course_detail`
-- ----------------------------
ALTER TABLE `course_detail` AUTO_INCREMENT=1;
DELIMITER ;;
CREATE TRIGGER `trigger_course_group_add` AFTER INSERT ON `course_group` FOR EACH ROW BEGIN
	UPDATE webreport_setting SET menu_item = menu_item | 4;
END
;;
DELIMITER ;
DELIMITER ;;
CREATE TRIGGER `trigger_course_group_update` AFTER UPDATE ON `course_group` FOR EACH ROW BEGIN
	UPDATE webreport_setting SET menu_item = menu_item | 4;
END
;;
DELIMITER ;
DELIMITER ;;
CREATE TRIGGER `trigger_course_group_del` AFTER DELETE ON `course_group` FOR EACH ROW BEGIN
	UPDATE webreport_setting SET menu_item = menu_item | 4;
END
;;
DELIMITER ;

-- ----------------------------
-- Auto increment value for `critical_operations`
-- ----------------------------
ALTER TABLE `critical_operations` AUTO_INCREMENT=1;

-- ----------------------------
-- Auto increment value for `customer`
-- ----------------------------
ALTER TABLE `customer` AUTO_INCREMENT=1;

-- ----------------------------
-- Auto increment value for `customer_consume`
-- ----------------------------
ALTER TABLE `customer_consume` AUTO_INCREMENT=1;
DELIMITER ;;
CREATE TRIGGER `trigger_header_update` AFTER UPDATE ON `descriptors_headers` FOR EACH ROW BEGIN
	UPDATE webreport_setting SET res_info = res_info | 8;
END
;;
DELIMITER ;
DELIMITER ;;
CREATE TRIGGER `trigger_menu_item_slu_add` AFTER INSERT ON `descriptors_menu_item_slu` FOR EACH ROW BEGIN
	UPDATE webreport_setting SET menu_item = menu_item | 2;
END
;;
DELIMITER ;
DELIMITER ;;
CREATE TRIGGER `trigger_menu_item_slu_update` AFTER UPDATE ON `descriptors_menu_item_slu` FOR EACH ROW BEGIN
	UPDATE webreport_setting SET menu_item = menu_item | 2;
END
;;
DELIMITER ;
DELIMITER ;;
CREATE TRIGGER `trigger_menu_item_slu_del` AFTER DELETE ON `descriptors_menu_item_slu` FOR EACH ROW BEGIN
	UPDATE webreport_setting SET menu_item = menu_item | 2;
END
;;
DELIMITER ;
DELIMITER ;;
CREATE TRIGGER `trigger_trailer_update` AFTER UPDATE ON `descriptors_trailers` FOR EACH ROW BEGIN
	UPDATE webreport_setting SET res_info = res_info | 8;
END
;;
DELIMITER ;
DELIMITER ;;
CREATE TRIGGER `trigger_discount_service_add` AFTER INSERT ON `discount_service` FOR EACH ROW BEGIN
	UPDATE webreport_setting SET tender_media = tender_media | 2;
END
;;
DELIMITER ;
DELIMITER ;;
CREATE TRIGGER `trigger_discount_service_update` AFTER UPDATE ON `discount_service` FOR EACH ROW BEGIN
	UPDATE webreport_setting SET tender_media = tender_media | 2;
END
;;
DELIMITER ;
DELIMITER ;;
CREATE TRIGGER `trigger_discount_service_del` AFTER DELETE ON `discount_service` FOR EACH ROW BEGIN
	UPDATE webreport_setting SET tender_media = tender_media | 2;
END
;;
DELIMITER ;
DELIMITER ;;
CREATE TRIGGER `trigger_employee_add` AFTER INSERT ON `employee` FOR EACH ROW BEGIN
	UPDATE webreport_setting SET employee = employee | 1;
END
;;
DELIMITER ;
DELIMITER ;;
CREATE TRIGGER `trigger_employee_update` AFTER UPDATE ON `employee` FOR EACH ROW BEGIN
	UPDATE webreport_setting SET employee = employee | 1;
END
;;
DELIMITER ;
DELIMITER ;;
CREATE TRIGGER `trigger_employee_del` AFTER DELETE ON `employee` FOR EACH ROW BEGIN
	UPDATE webreport_setting SET employee = employee | 1;
END
;;
DELIMITER ;
DELIMITER ;;
CREATE TRIGGER `trigger_employee_class_add` AFTER INSERT ON `employee_class` FOR EACH ROW BEGIN
	UPDATE webreport_setting SET employee = employee | 2;
END
;;
DELIMITER ;
DELIMITER ;;
CREATE TRIGGER `trigger_employee_class_update` AFTER UPDATE ON `employee_class` FOR EACH ROW BEGIN
	UPDATE webreport_setting SET employee = employee | 2;
END
;;
DELIMITER ;
DELIMITER ;;
CREATE TRIGGER `trigger_employee_class_del` AFTER DELETE ON `employee_class` FOR EACH ROW BEGIN
	UPDATE webreport_setting SET employee = employee | 2;
END
;;
DELIMITER ;

-- ----------------------------
-- Auto increment value for `evaluation`
-- ----------------------------
ALTER TABLE `evaluation` AUTO_INCREMENT=1;
DELIMITER ;;
CREATE TRIGGER `trigger_family_group_add` AFTER INSERT ON `family_group` FOR EACH ROW BEGIN
	UPDATE webreport_setting SET family_group = family_group | 1;
END
;;
DELIMITER ;
DELIMITER ;;
CREATE TRIGGER `trigger_family_group_update` AFTER UPDATE ON `family_group` FOR EACH ROW BEGIN
	UPDATE webreport_setting SET family_group = family_group | 1;
END
;;
DELIMITER ;
DELIMITER ;;
CREATE TRIGGER `trigger_family_group_del` AFTER DELETE ON `family_group` FOR EACH ROW BEGIN
	UPDATE webreport_setting SET family_group = family_group | 1;
END
;;
DELIMITER ;

-- ----------------------------
-- Auto increment value for `history_card`
-- ----------------------------
ALTER TABLE `history_card` AUTO_INCREMENT=1;

-- ----------------------------
-- Auto increment value for `history_day_end`
-- ----------------------------
ALTER TABLE `history_day_end` AUTO_INCREMENT=1;

-- ----------------------------
-- Auto increment value for `history_major_group`
-- ----------------------------
ALTER TABLE `history_major_group` AUTO_INCREMENT=1;

-- ----------------------------
-- Auto increment value for `history_messages`
-- ----------------------------
ALTER TABLE `history_messages` AUTO_INCREMENT=1;

-- ----------------------------
-- Indexes structure for table `history_order_detail`
-- ----------------------------
CREATE INDEX `idx_headcheck` ON `history_order_detail`(`order_head_id`, `check_id`) USING BTREE ;
CREATE INDEX `idx_detail` ON `history_order_detail`(`order_detail_id`) USING BTREE ;
CREATE INDEX `idx_condiment` ON `history_order_detail`(`condiment_belong_item`) USING BTREE ;
CREATE INDEX `idx_kds` ON `history_order_detail`(`is_make`, `order_time`) USING BTREE ;

-- ----------------------------
-- Indexes structure for table `history_order_head`
-- ----------------------------
CREATE INDEX `idx_headcheck` ON `history_order_head`(`order_head_id`, `check_id`) USING BTREE ;

-- ----------------------------
-- Auto increment value for `history_payment`
-- ----------------------------
ALTER TABLE `history_payment` AUTO_INCREMENT=1;

-- ----------------------------
-- Auto increment value for `history_time_clock`
-- ----------------------------
ALTER TABLE `history_time_clock` AUTO_INCREMENT=1;

-- ----------------------------
-- Auto increment value for `inventory_setting`
-- ----------------------------
ALTER TABLE `inventory_setting` AUTO_INCREMENT=2;

-- ----------------------------
-- Indexes structure for table `invoices`
-- ----------------------------
CREATE UNIQUE INDEX `order_head_id` ON `invoices`(`order_head_id`, `check_id`) USING BTREE ;

-- ----------------------------
-- Auto increment value for `invoices`
-- ----------------------------
ALTER TABLE `invoices` AUTO_INCREMENT=1;

-- ----------------------------
-- Auto increment value for `item_unit`
-- ----------------------------
ALTER TABLE `item_unit` AUTO_INCREMENT=32;

-- ----------------------------
-- Indexes structure for table `macros`
-- ----------------------------
CREATE INDEX `idx_macros_name` ON `macros`(`macros_name`) USING BTREE ;
DELIMITER ;;
CREATE TRIGGER `trigger_macros_update` AFTER UPDATE ON `macros` FOR EACH ROW BEGIN
	UPDATE webreport_setting SET rvc_center = rvc_center | 8;
END
;;
DELIMITER ;
DELIMITER ;;
CREATE TRIGGER `trigger_major_group_add` AFTER INSERT ON `major_group` FOR EACH ROW BEGIN
	UPDATE webreport_setting SET major_group = major_group | 1;
END
;;
DELIMITER ;
DELIMITER ;;
CREATE TRIGGER `trigger_major_group_update` AFTER UPDATE ON `major_group` FOR EACH ROW BEGIN
	UPDATE webreport_setting SET major_group = major_group | 1;
END
;;
DELIMITER ;
DELIMITER ;;
CREATE TRIGGER `trigger_major_group_del` AFTER DELETE ON `major_group` FOR EACH ROW BEGIN
	UPDATE webreport_setting SET major_group = major_group | 1;
END
;;
DELIMITER ;
DELIMITER ;;
CREATE TRIGGER `trigger_menu_item_add` AFTER INSERT ON `menu_item` FOR EACH ROW BEGIN
	UPDATE webreport_setting SET menu_item = menu_item | 1;
END
;;
DELIMITER ;
DELIMITER ;;
CREATE TRIGGER `trigger_menu_item_update` AFTER UPDATE ON `menu_item` FOR EACH ROW BEGIN
	UPDATE webreport_setting SET menu_item = menu_item | 1;
END
;;
DELIMITER ;
DELIMITER ;;
CREATE TRIGGER `trigger_menu_item_del` AFTER DELETE ON `menu_item` FOR EACH ROW BEGIN
	UPDATE webreport_setting SET menu_item = menu_item | 1;
END
;;
DELIMITER ;

-- ----------------------------
-- Auto increment value for `messages`
-- ----------------------------
ALTER TABLE `messages` AUTO_INCREMENT=1;
DELIMITER ;;
CREATE TRIGGER `trigger_order_default_group_add` AFTER INSERT ON `order_default_group` FOR EACH ROW BEGIN
	UPDATE webreport_setting SET res_info = res_info | 2;
END
;;
DELIMITER ;
DELIMITER ;;
CREATE TRIGGER `trigger_order_default_group_update` AFTER UPDATE ON `order_default_group` FOR EACH ROW BEGIN
	UPDATE webreport_setting SET res_info = res_info | 2;
END
;;
DELIMITER ;
DELIMITER ;;
CREATE TRIGGER `trigger_order_default_group_del` AFTER DELETE ON `order_default_group` FOR EACH ROW BEGIN
	UPDATE webreport_setting SET res_info = res_info | 2;
END
;;
DELIMITER ;
DELIMITER ;;
CREATE TRIGGER `trigger_order_detail_add` BEFORE INSERT ON `order_detail` FOR EACH ROW BEGIN 
if NEW.order_detail_id IS NULL then
	set NEW.order_time=now();
end if;
END
;;
DELIMITER ;

-- ----------------------------
-- Auto increment value for `order_detail`
-- ----------------------------
ALTER TABLE `order_detail` AUTO_INCREMENT=1;
DELIMITER ;;
CREATE TRIGGER `trigger_order_detail_default_add` AFTER INSERT ON `order_detail_default` FOR EACH ROW BEGIN
	UPDATE webreport_setting SET res_info = res_info | 2;
END
;;
DELIMITER ;
DELIMITER ;;
CREATE TRIGGER `trigger_order_detail_default_update` AFTER UPDATE ON `order_detail_default` FOR EACH ROW BEGIN
	UPDATE webreport_setting SET res_info = res_info | 2;
END
;;
DELIMITER ;
DELIMITER ;;
CREATE TRIGGER `trigger_order_detail_default_del` AFTER DELETE ON `order_detail_default` FOR EACH ROW BEGIN
	UPDATE webreport_setting SET res_info = res_info | 2;
END
;;
DELIMITER ;

-- ----------------------------
-- Auto increment value for `order_detail_default`
-- ----------------------------
ALTER TABLE `order_detail_default` AUTO_INCREMENT=1;

-- ----------------------------
-- Indexes structure for table `order_head`
-- ----------------------------
CREATE INDEX `table_id` ON `order_head`(`table_id`) USING BTREE ;

-- ----------------------------
-- Auto increment value for `order_head`
-- ----------------------------
ALTER TABLE `order_head` AUTO_INCREMENT=1;

-- ----------------------------
-- Auto increment value for `parties`
-- ----------------------------
ALTER TABLE `parties` AUTO_INCREMENT=1;

-- ----------------------------
-- Auto increment value for `party_default_remark`
-- ----------------------------
ALTER TABLE `party_default_remark` AUTO_INCREMENT=4;

-- ----------------------------
-- Auto increment value for `party_item`
-- ----------------------------
ALTER TABLE `party_item` AUTO_INCREMENT=1;

-- ----------------------------
-- Auto increment value for `party_remark`
-- ----------------------------
ALTER TABLE `party_remark` AUTO_INCREMENT=1;

-- ----------------------------
-- Auto increment value for `payment`
-- ----------------------------
ALTER TABLE `payment` AUTO_INCREMENT=1;
DELIMITER ;;
CREATE TRIGGER `trigger_periods_add` AFTER INSERT ON `periods` FOR EACH ROW BEGIN
	UPDATE webreport_setting SET periods = periods | 1;
END
;;
DELIMITER ;
DELIMITER ;;
CREATE TRIGGER `trigger_periods_update` AFTER UPDATE ON `periods` FOR EACH ROW BEGIN
	UPDATE webreport_setting SET periods = periods | 1;
END
;;
DELIMITER ;
DELIMITER ;;
CREATE TRIGGER `trigger_periods_del` AFTER DELETE ON `periods` FOR EACH ROW BEGIN
	UPDATE webreport_setting SET periods = periods | 1;
END
;;
DELIMITER ;

-- ----------------------------
-- Auto increment value for `practice`
-- ----------------------------
ALTER TABLE `practice` AUTO_INCREMENT=1;

-- ----------------------------
-- Auto increment value for `pre_order`
-- ----------------------------
ALTER TABLE `pre_order` AUTO_INCREMENT=1;

-- ----------------------------
-- Auto increment value for `pre_order_detail`
-- ----------------------------
ALTER TABLE `pre_order_detail` AUTO_INCREMENT=1;
DELIMITER ;;
CREATE TRIGGER `trigger_price_scheme_add` AFTER INSERT ON `price_scheme` FOR EACH ROW BEGIN
	UPDATE webreport_setting SET tables = tables | 4;
END
;;
DELIMITER ;
DELIMITER ;;
CREATE TRIGGER `trigger_price_scheme_update` AFTER UPDATE ON `price_scheme` FOR EACH ROW BEGIN
	UPDATE webreport_setting SET tables = tables | 4;
END
;;
DELIMITER ;
DELIMITER ;;
CREATE TRIGGER `trigger_price_scheme_del` AFTER DELETE ON `price_scheme` FOR EACH ROW BEGIN
	UPDATE webreport_setting SET tables = tables | 4;
END
;;
DELIMITER ;
DELIMITER ;;
CREATE TRIGGER `trigger_print_class_add` AFTER INSERT ON `print_class_relation` FOR EACH ROW BEGIN
	UPDATE webreport_setting SET major_group = major_group | 4;
END
;;
DELIMITER ;
DELIMITER ;;
CREATE TRIGGER `trigger_print_class_update` AFTER UPDATE ON `print_class_relation` FOR EACH ROW BEGIN
	UPDATE webreport_setting SET major_group = major_group | 4;
END
;;
DELIMITER ;
DELIMITER ;;
CREATE TRIGGER `trigger_print_class_del` AFTER DELETE ON `print_class_relation` FOR EACH ROW BEGIN
	UPDATE webreport_setting SET major_group = major_group | 4;
END
;;
DELIMITER ;
DELIMITER ;;
CREATE TRIGGER `trigger_print_devices_add` AFTER INSERT ON `print_devices` FOR EACH ROW BEGIN
	UPDATE webreport_setting SET major_group = major_group | 2;
END
;;
DELIMITER ;
DELIMITER ;;
CREATE TRIGGER `trigger_print_devices_update` AFTER UPDATE ON `print_devices` FOR EACH ROW BEGIN
	UPDATE webreport_setting SET major_group = major_group | 2;
END
;;
DELIMITER ;
DELIMITER ;;
CREATE TRIGGER `trigger_print_devices_del` AFTER DELETE ON `print_devices` FOR EACH ROW BEGIN
	UPDATE webreport_setting SET major_group = major_group | 2;
END
;;
DELIMITER ;

-- ----------------------------
-- Auto increment value for `print_task`
-- ----------------------------
ALTER TABLE `print_task` AUTO_INCREMENT=1;
DELIMITER ;;
CREATE TRIGGER `trigger_reasons_add` AFTER INSERT ON `reasons` FOR EACH ROW BEGIN
	UPDATE webreport_setting SET employee = employee | 4;
END
;;
DELIMITER ;
DELIMITER ;;
CREATE TRIGGER `trigger_reasons_update` AFTER UPDATE ON `reasons` FOR EACH ROW BEGIN
	UPDATE webreport_setting SET employee = employee | 4;
END
;;
DELIMITER ;
DELIMITER ;;
CREATE TRIGGER `trigger_reasons_del` AFTER DELETE ON `reasons` FOR EACH ROW BEGIN
	UPDATE webreport_setting SET employee = employee | 4;
END
;;
DELIMITER ;

-- ----------------------------
-- Auto increment value for `report`
-- ----------------------------
ALTER TABLE `report` AUTO_INCREMENT=142;
DELIMITER ;;
CREATE TRIGGER `trigger_restaurant_add` AFTER INSERT ON `restaurant` FOR EACH ROW BEGIN
	UPDATE webreport_setting SET res_info = res_info | 1;
END
;;
DELIMITER ;
DELIMITER ;;
CREATE TRIGGER `trigger_restaurant_update` AFTER UPDATE ON `restaurant` FOR EACH ROW BEGIN
	UPDATE webreport_setting SET res_info = res_info | 1;
END
;;
DELIMITER ;
DELIMITER ;;
CREATE TRIGGER `trigger_restaurant_del` AFTER DELETE ON `restaurant` FOR EACH ROW BEGIN
	UPDATE webreport_setting SET res_info = res_info | 1;
END
;;
DELIMITER ;
DELIMITER ;;
CREATE TRIGGER `trigger_rvc_center_add` AFTER INSERT ON `rvc_center` FOR EACH ROW BEGIN
	UPDATE webreport_setting SET rvc_center = rvc_center | 1;
END
;;
DELIMITER ;
DELIMITER ;;
CREATE TRIGGER `trigger_rvc_center_update` AFTER UPDATE ON `rvc_center` FOR EACH ROW BEGIN
	UPDATE webreport_setting SET rvc_center = rvc_center | 1;
END
;;
DELIMITER ;
DELIMITER ;;
CREATE TRIGGER `trigger_rvc_center_del` AFTER DELETE ON `rvc_center` FOR EACH ROW BEGIN
	UPDATE webreport_setting SET rvc_center = rvc_center | 1;
END
;;
DELIMITER ;
DELIMITER ;;
CREATE TRIGGER `trigger_service_tip_add` AFTER INSERT ON `service_tip` FOR EACH ROW BEGIN
	UPDATE webreport_setting SET tender_media = tender_media | 4;
END
;;
DELIMITER ;
DELIMITER ;;
CREATE TRIGGER `trigger_service_tip_update` AFTER UPDATE ON `service_tip` FOR EACH ROW BEGIN
	UPDATE webreport_setting SET tender_media = tender_media | 4;
END
;;
DELIMITER ;
DELIMITER ;;
CREATE TRIGGER `trigger_service_tip_del` AFTER DELETE ON `service_tip` FOR EACH ROW BEGIN
	UPDATE webreport_setting SET tender_media = tender_media | 4;
END
;;
DELIMITER ;
DELIMITER ;;
CREATE TRIGGER `trigger_serving_period_class_add` AFTER INSERT ON `serving_period_class` FOR EACH ROW BEGIN
	UPDATE webreport_setting SET periods = periods | 2;
END
;;
DELIMITER ;
DELIMITER ;;
CREATE TRIGGER `trigger_serving_rvc_class_add` AFTER INSERT ON `serving_rvc_class` FOR EACH ROW BEGIN
	UPDATE webreport_setting SET rvc_center = rvc_center | 2;
END
;;
DELIMITER ;

-- ----------------------------
-- Auto increment value for `shift_info`
-- ----------------------------
ALTER TABLE `shift_info` AUTO_INCREMENT=1;

-- ----------------------------
-- Auto increment value for `storage`
-- ----------------------------
ALTER TABLE `storage` AUTO_INCREMENT=1;

-- ----------------------------
-- Indexes structure for table `tables`
-- ----------------------------
CREATE INDEX `table_id` ON `tables`(`table_id`) USING BTREE ;
DELIMITER ;;
CREATE TRIGGER `trigger_tax_add` AFTER INSERT ON `tax` FOR EACH ROW BEGIN
	UPDATE webreport_setting SET res_info = res_info | 4;
END
;;
DELIMITER ;
DELIMITER ;;
CREATE TRIGGER `trigger_tax_update` AFTER UPDATE ON `tax` FOR EACH ROW BEGIN
	UPDATE webreport_setting SET res_info = res_info | 4;
END
;;
DELIMITER ;
DELIMITER ;;
CREATE TRIGGER `trigger_tax_del` AFTER DELETE ON `tax` FOR EACH ROW BEGIN
	UPDATE webreport_setting SET res_info = res_info | 4;
END
;;
DELIMITER ;
DELIMITER ;;
CREATE TRIGGER `trigger_tax_primary_add` AFTER INSERT ON `tax_primary` FOR EACH ROW BEGIN
	UPDATE webreport_setting SET res_info = res_info | 4;
END
;;
DELIMITER ;
DELIMITER ;;
CREATE TRIGGER `trigger_tax_primary_update` AFTER UPDATE ON `tax_primary` FOR EACH ROW BEGIN
	UPDATE webreport_setting SET res_info = res_info | 4;
END
;;
DELIMITER ;
DELIMITER ;;
CREATE TRIGGER `trigger_tax_primary_del` AFTER DELETE ON `tax_primary` FOR EACH ROW BEGIN
	UPDATE webreport_setting SET res_info = res_info | 4;
END
;;
DELIMITER ;
DELIMITER ;;
CREATE TRIGGER `trigger_tendermedia_add` AFTER INSERT ON `tender_media` FOR EACH ROW BEGIN
	UPDATE webreport_setting SET tender_media = tender_media | 1;
END
;;
DELIMITER ;
DELIMITER ;;
CREATE TRIGGER `trigger_tendermedia_update` AFTER UPDATE ON `tender_media` FOR EACH ROW BEGIN
	UPDATE webreport_setting SET tender_media = tender_media | 1;
END
;;
DELIMITER ;
DELIMITER ;;
CREATE TRIGGER `trigger_tendermedia_del` AFTER DELETE ON `tender_media` FOR EACH ROW BEGIN
	UPDATE webreport_setting SET tender_media = tender_media | 1;
END
;;
DELIMITER ;

-- ----------------------------
-- Auto increment value for `user_dcb`
-- ----------------------------
ALTER TABLE `user_dcb` AUTO_INCREMENT=1;
DELIMITER ;;
CREATE TRIGGER `trigger_workstation_add` AFTER INSERT ON `user_workstations` FOR EACH ROW BEGIN
	UPDATE webreport_setting SET rvc_center = rvc_center | 4;
END
;;
DELIMITER ;
DELIMITER ;;
CREATE TRIGGER `trigger_workstation_update` AFTER UPDATE ON `user_workstations` FOR EACH ROW BEGIN
	UPDATE webreport_setting SET rvc_center = rvc_center | 4;
END
;;
DELIMITER ;
DELIMITER ;;
CREATE TRIGGER `trigger_workstation_del` AFTER DELETE ON `user_workstations` FOR EACH ROW BEGIN
	UPDATE webreport_setting SET rvc_center = rvc_center | 4;
END
;;
DELIMITER ;

-- ----------------------------
-- Auto increment value for `vip_setting`
-- ----------------------------
ALTER TABLE `vip_setting` AUTO_INCREMENT=2;
