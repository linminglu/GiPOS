/*
Navicat MySQL Data Transfer

Source Server         : pos
Source Server Version : 50525
Source Host           : localhost:3308
Source Database       : coolroid

Target Server Type    : MYSQL
Target Server Version : 50525
File Encoding         : 65001

Date: 2013-09-12 11:27:01
*/

SET FOREIGN_KEY_CHECKS=0;
-- ----------------------------
-- Table structure for `auto_menu_level`
-- ----------------------------
DROP TABLE IF EXISTS `auto_menu_level`;
CREATE TABLE `auto_menu_level` (
  `aml_id` int(11) NOT NULL,
  `aml_number` int(11) DEFAULT NULL,
  `aml_name` varchar(40) DEFAULT '' COMMENT 'auto_menu_level 的名称',
  `revenue_center` int(11) DEFAULT NULL,
  `period` int(11) DEFAULT NULL,
  `main_menu_level` int(11) DEFAULT NULL,
  `sub_menu_level` int(11) DEFAULT NULL,
  PRIMARY KEY (`aml_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of auto_menu_level
-- ----------------------------

-- ----------------------------
-- Table structure for `bargain_price_item`
-- ----------------------------
DROP TABLE IF EXISTS `bargain_price_item`;
CREATE TABLE `bargain_price_item` (
  `bargain_item_id` int(11) NOT NULL,
  `bargain_item_number` int(11) NOT NULL,
  `bargain_item_name` varchar(60) DEFAULT NULL,
  `bargain_status` int(11) DEFAULT NULL,
  `bargain_stype` int(11) DEFAULT NULL,
  `bargain_num_cur` float DEFAULT NULL,
  `bargain_num` float DEFAULT NULL,
  `bargain_price` float DEFAULT NULL,
  `bargain_vip` bit(1) DEFAULT NULL,
  `bargain_start_date` date DEFAULT NULL,
  `bargain_end_date` date DEFAULT NULL,
  `bargain_start_time` time DEFAULT NULL,
  `bargain_end_time` time DEFAULT NULL,
  `is_every_day` bit(1) DEFAULT NULL,
  `now_use_date` date DEFAULT NULL,
  PRIMARY KEY (`bargain_item_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of bargain_price_item
-- ----------------------------

-- ----------------------------
-- Table structure for `cashbox_in_out`
-- ----------------------------
DROP TABLE IF EXISTS `cashbox_in_out`;
CREATE TABLE `cashbox_in_out` (
  `in_out_id` int(11) NOT NULL AUTO_INCREMENT,
  `cashbox_id` int(11) DEFAULT NULL,
  `type` int(11) DEFAULT NULL,
  `cash_amount` decimal(11,2) DEFAULT NULL,
  `in_out_time` datetime DEFAULT NULL,
  `employee_id` int(11) DEFAULT NULL,
  `employee_name` varchar(30) DEFAULT NULL,
  PRIMARY KEY (`in_out_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of cashbox_in_out
-- ----------------------------

-- ----------------------------
-- Table structure for `cashbox_period_amout`
-- ----------------------------
DROP TABLE IF EXISTS `cashbox_period_amout`;
CREATE TABLE `cashbox_period_amout` (
  `employee_id` int(11) DEFAULT NULL,
  `cashbox_id` int(11) DEFAULT NULL,
  `date_from` datetime DEFAULT NULL,
  `cash_from` float DEFAULT NULL,
  `date_to` datetime DEFAULT NULL,
  `cash_to` float DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of cashbox_period_amout
-- ----------------------------

-- ----------------------------
-- Table structure for `condiment_groups`
-- ----------------------------
DROP TABLE IF EXISTS `condiment_groups`;
CREATE TABLE `condiment_groups` (
  `scomdiment_groups_id` int(11) NOT NULL,
  `comdiment_groups_name` varchar(30) DEFAULT NULL,
  `touchscreen_style` int(11) DEFAULT NULL,
  `price` float(11,0) NOT NULL,
  PRIMARY KEY (`scomdiment_groups_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of condiment_groups
-- ----------------------------
INSERT INTO condiment_groups VALUES ('1', 'Spice', null, '0');
INSERT INTO condiment_groups VALUES ('2', 'Sauce', null, '0');
INSERT INTO condiment_groups VALUES ('3', 'Sugar', null, '0');
INSERT INTO condiment_groups VALUES ('4', 'Edible oil', null, '0');
INSERT INTO condiment_groups VALUES ('5', 'Flavoring', null, '0');

-- ----------------------------
-- Table structure for `condiment_membership`
-- ----------------------------
DROP TABLE IF EXISTS `condiment_membership`;
CREATE TABLE `condiment_membership` (
  `condiment_groups_id` int(11) NOT NULL,
  `menu_item_id` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of condiment_membership
-- ----------------------------
INSERT INTO condiment_membership VALUES ('1', '6000');
INSERT INTO condiment_membership VALUES ('1', '6001');
INSERT INTO condiment_membership VALUES ('1', '6002');
INSERT INTO condiment_membership VALUES ('1', '6003');
INSERT INTO condiment_membership VALUES ('1', '6004');
INSERT INTO condiment_membership VALUES ('1', '6005');
INSERT INTO condiment_membership VALUES ('1', '6006');
INSERT INTO condiment_membership VALUES ('2', '6007');
INSERT INTO condiment_membership VALUES ('2', '6008');
INSERT INTO condiment_membership VALUES ('2', '6009');
INSERT INTO condiment_membership VALUES ('2', '6010');
INSERT INTO condiment_membership VALUES ('2', '6011');
INSERT INTO condiment_membership VALUES ('2', '6012');
INSERT INTO condiment_membership VALUES ('2', '6013');
INSERT INTO condiment_membership VALUES ('2', '6014');
INSERT INTO condiment_membership VALUES ('3', '6015');
INSERT INTO condiment_membership VALUES ('3', '6016');
INSERT INTO condiment_membership VALUES ('3', '6017');
INSERT INTO condiment_membership VALUES ('3', '6018');
INSERT INTO condiment_membership VALUES ('3', '6019');
INSERT INTO condiment_membership VALUES ('4', '6020');
INSERT INTO condiment_membership VALUES ('4', '6021');
INSERT INTO condiment_membership VALUES ('4', '6022');
INSERT INTO condiment_membership VALUES ('4', '6023');
INSERT INTO condiment_membership VALUES ('4', '6024');
INSERT INTO condiment_membership VALUES ('4', '6025');
INSERT INTO condiment_membership VALUES ('5', '6026');
INSERT INTO condiment_membership VALUES ('5', '6027');
INSERT INTO condiment_membership VALUES ('5', '6028');
INSERT INTO condiment_membership VALUES ('5', '6029');
INSERT INTO condiment_membership VALUES ('5', '6030');
INSERT INTO condiment_membership VALUES ('5', '6031');
INSERT INTO condiment_membership VALUES ('5', '6032');
INSERT INTO condiment_membership VALUES ('5', '6033');
INSERT INTO condiment_membership VALUES ('5', '6034');
INSERT INTO condiment_membership VALUES ('5', '6000');
INSERT INTO condiment_membership VALUES ('5', '6001');
INSERT INTO condiment_membership VALUES ('5', '6002');
INSERT INTO condiment_membership VALUES ('5', '6003');
INSERT INTO condiment_membership VALUES ('5', '6004');
INSERT INTO condiment_membership VALUES ('5', '6005');
INSERT INTO condiment_membership VALUES ('5', '6006');
INSERT INTO condiment_membership VALUES ('5', '6007');
INSERT INTO condiment_membership VALUES ('5', '6008');
INSERT INTO condiment_membership VALUES ('5', '6009');
INSERT INTO condiment_membership VALUES ('5', '6010');
INSERT INTO condiment_membership VALUES ('5', '6011');
INSERT INTO condiment_membership VALUES ('5', '6012');
INSERT INTO condiment_membership VALUES ('5', '6013');
INSERT INTO condiment_membership VALUES ('5', '6014');
INSERT INTO condiment_membership VALUES ('5', '6015');
INSERT INTO condiment_membership VALUES ('5', '6016');
INSERT INTO condiment_membership VALUES ('5', '6017');
INSERT INTO condiment_membership VALUES ('5', '6018');
INSERT INTO condiment_membership VALUES ('5', '6019');
INSERT INTO condiment_membership VALUES ('5', '6020');
INSERT INTO condiment_membership VALUES ('5', '6021');
INSERT INTO condiment_membership VALUES ('5', '6022');
INSERT INTO condiment_membership VALUES ('5', '6023');
INSERT INTO condiment_membership VALUES ('5', '6024');
INSERT INTO condiment_membership VALUES ('5', '6025');

-- ----------------------------
-- Table structure for `condiment_selection`
-- ----------------------------
DROP TABLE IF EXISTS `condiment_selection`;
CREATE TABLE `condiment_selection` (
  `condiment_selection_id` int(11) NOT NULL,
  `condiment_selection_number` int(11) NOT NULL,
  `condiment_selection_name` varchar(30) DEFAULT NULL,
  `own_condiment_group` int(11) DEFAULT NULL,
  `own_condiment_group_bak` int(11) DEFAULT NULL,
  PRIMARY KEY (`condiment_selection_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of condiment_selection
-- ----------------------------

-- ----------------------------
-- Table structure for `configurator_access`
-- ----------------------------
DROP TABLE IF EXISTS `configurator_access`;
CREATE TABLE `configurator_access` (
  `employee_class_id` int(11) NOT NULL,
  `employee_class_number` int(11) NOT NULL,
  `pos_cfg_form` int(11) DEFAULT NULL,
  `is_read` bit(1) DEFAULT NULL,
  `is_update` bit(1) DEFAULT NULL,
  `is_insert` bit(1) DEFAULT NULL,
  `is_delete` bit(1) DEFAULT NULL,
  PRIMARY KEY (`employee_class_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of configurator_access
-- ----------------------------

-- ----------------------------
-- Table structure for `consumption_limit`
-- ----------------------------
DROP TABLE IF EXISTS `consumption_limit`;
CREATE TABLE `consumption_limit` (
  `consumption_limit_id` int(11) NOT NULL DEFAULT '0',
  `consumption_limit_name` varchar(30) DEFAULT NULL,
  `limit_type` int(11) DEFAULT NULL,
  `limit_amount` float DEFAULT NULL,
  PRIMARY KEY (`consumption_limit_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of consumption_limit
-- ----------------------------
INSERT INTO consumption_limit VALUES ('1', '默认最低消费', '0', '0');

-- ----------------------------
-- Table structure for `course`
-- ----------------------------
DROP TABLE IF EXISTS `course`;
CREATE TABLE `course` (
  `course_id` int(11) NOT NULL,
  `course_name_1` varchar(40) DEFAULT '',
  `course_name_2` varchar(40) DEFAULT '',
  `course_description` varchar(200) DEFAULT NULL,
  `price` float DEFAULT NULL,
  `icon` varchar(256) DEFAULT NULL,
  `serving _period_class` int(11) DEFAULT NULL,
  `serving _rvc_class` int(11) DEFAULT NULL,
  `print_class` int(11) DEFAULT NULL,
  PRIMARY KEY (`course_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of course
-- ----------------------------

-- ----------------------------
-- Table structure for `course_detail`
-- ----------------------------
DROP TABLE IF EXISTS `course_detail`;
CREATE TABLE `course_detail` (
  `detail_id` int(11) NOT NULL AUTO_INCREMENT,
  `course_group_id` int(11) NOT NULL DEFAULT '0',
  `menu_item_id` int(11) NOT NULL DEFAULT '0',
  `item_course_name` varchar(200) DEFAULT NULL,
  `unit` varchar(100) DEFAULT NULL,
  `num` float DEFAULT '1',
  `price` float DEFAULT '0',
  `description` varchar(200) DEFAULT NULL,
  PRIMARY KEY (`detail_id`)
) ENGINE=InnoDB AUTO_INCREMENT=16 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of course_detail
-- ----------------------------
INSERT INTO course_detail VALUES ('1', '1', '1027', 'パスタ', '', '1', '10', '');
INSERT INTO course_detail VALUES ('2', '1', '1031', 'サラダ', '', '1', '10', '');
INSERT INTO course_detail VALUES ('3', '1', '1033', '前菜盛合せ', '', '1', '20', '');
INSERT INTO course_detail VALUES ('4', '3', '1027', 'パスタ', '', '1', '0', null);
INSERT INTO course_detail VALUES ('5', '3', '1029', 'デザート', '', '1', '0', null);
INSERT INTO course_detail VALUES ('6', '3', '1031', 'サラダ', '', '1', '0', null);
INSERT INTO course_detail VALUES ('7', '3', '1032', 'コーヒー', '', '1', '0', null);
INSERT INTO course_detail VALUES ('8', '3', '1033', '前菜盛合せ', '', '1', '0', null);
INSERT INTO course_detail VALUES ('9', '5', '1026', '前菜盛り合わせ', '', '1', '0', null);
INSERT INTO course_detail VALUES ('10', '5', '1027', 'パスタ', '', '1', '0', null);
INSERT INTO course_detail VALUES ('11', '5', '1028', 'メインディッシュ', '', '1', '0', null);
INSERT INTO course_detail VALUES ('12', '5', '1029', 'デザート', '', '1', '0', null);
INSERT INTO course_detail VALUES ('13', '5', '1030', 'コーヒー又は紅茶', '', '1', '0', null);
INSERT INTO course_detail VALUES ('14', '2', '1011', '生ビール：プレミアムモルツ', '', '1', '525', '');
INSERT INTO course_detail VALUES ('15', '2', '1012', 'オールフリー（ノンアルコールビール）', '', '1', '525', '');

-- ----------------------------
-- Table structure for `course_group`
-- ----------------------------
DROP TABLE IF EXISTS `course_group`;
CREATE TABLE `course_group` (
  `course_group_id` int(11) NOT NULL DEFAULT '0',
  `course_group_name` varchar(40) DEFAULT NULL,
  `menu_item_id` int(11) DEFAULT NULL,
  `is_must` int(11) DEFAULT NULL,
  `choose_num` int(11) DEFAULT NULL,
  `slu_id` int(11) DEFAULT '-1',
  PRIMARY KEY (`course_group_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of course_group
-- ----------------------------
INSERT INTO course_group VALUES ('1', '必选组', '1024', '1', '1', '-1');
INSERT INTO course_group VALUES ('2', '可选组', '1024', '0', '1', '-1');
INSERT INTO course_group VALUES ('3', '必选组', '1025', '1', '1', '-1');
INSERT INTO course_group VALUES ('4', '可选组', '1025', '0', '1', '-1');
INSERT INTO course_group VALUES ('5', '必选组', '1034', '1', '1', '-1');
INSERT INTO course_group VALUES ('6', '可选组', '1034', '0', '1', '-1');

-- ----------------------------
-- Table structure for `critical_operations`
-- ----------------------------
DROP TABLE IF EXISTS `critical_operations`;
CREATE TABLE `critical_operations` (
  `operation_id` int(11) NOT NULL AUTO_INCREMENT,
  `operation_type` int(11) DEFAULT NULL,
  `device_id` int(11) DEFAULT NULL,
  `order_head_id` int(11) DEFAULT NULL,
  `employee_id` int(11) DEFAULT NULL,
  `employee_name` varchar(30) DEFAULT NULL,
  `operation_time` datetime DEFAULT NULL,
  `operation_name` varchar(30) DEFAULT NULL,
  `operation_detail` varchar(300) DEFAULT NULL,
  PRIMARY KEY (`operation_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of critical_operations
-- ----------------------------

-- ----------------------------
-- Table structure for `critical_operation_type`
-- ----------------------------
DROP TABLE IF EXISTS `critical_operation_type`;
CREATE TABLE `critical_operation_type` (
  `operation_type_id` int(11) DEFAULT NULL,
  `operation_type_name` varchar(30) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of critical_operation_type
-- ----------------------------
INSERT INTO critical_operation_type VALUES ('0', '未知类型');
INSERT INTO critical_operation_type VALUES ('1', '赠送');
INSERT INTO critical_operation_type VALUES ('2', '改价');
INSERT INTO critical_operation_type VALUES ('3', '退菜');
INSERT INTO critical_operation_type VALUES ('4', '反结账');
INSERT INTO critical_operation_type VALUES ('5', '转台');
INSERT INTO critical_operation_type VALUES ('6', '合台\\合单');
INSERT INTO critical_operation_type VALUES ('7', '退款');
INSERT INTO critical_operation_type VALUES ('8', '交接班');
INSERT INTO critical_operation_type VALUES ('9', '日结');

-- ----------------------------
-- Table structure for `customer`
-- ----------------------------
DROP TABLE IF EXISTS `customer`;
CREATE TABLE `customer` (
  `customer_id` int(11) NOT NULL AUTO_INCREMENT,
  `card_id` varchar(40) DEFAULT '',
  `customer_name` varchar(40) DEFAULT NULL,
  `customer_class` int(11) DEFAULT '0',
  `times` int(11) DEFAULT '0',
  `amount` decimal(11,2) DEFAULT NULL,
  `telephone_1` varchar(40) DEFAULT NULL,
  `telephone_2` varchar(40) DEFAULT NULL,
  `company` varchar(100) DEFAULT NULL,
  `position` varchar(100) DEFAULT NULL,
  `address` varchar(200) DEFAULT NULL,
  `postcode` varchar(30) DEFAULT NULL,
  `email` varchar(200) DEFAULT NULL,
  `is_set_birthday` bit(1) DEFAULT b'0',
  `birthday` date DEFAULT NULL,
  `sex` bit(1) DEFAULT b'1',
  `description` varchar(200) DEFAULT '',
  `score` int(11) DEFAULT '0',
  `is_pre_comsume` int(11) DEFAULT NULL,
  `card_status` int(11) DEFAULT '0',
  `cid` varchar(40) DEFAULT NULL,
  `pwd` varchar(40) DEFAULT NULL,
  `open_date` datetime DEFAULT NULL,
  PRIMARY KEY (`customer_id`)
) ENGINE=InnoDB AUTO_INCREMENT=3 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of customer
-- ----------------------------
INSERT INTO customer VALUES ('1', '1', '贵宾1', '0', '0', '0.00', '', '', '', '', '', '', '', '', '2013-01-07', '', '', '361', '1', '0', '', null, null);
INSERT INTO customer VALUES ('2', '2', '贵宾2', '0', '0', '0.00', '', '', '', '', '', '', '', '', '2013-01-07', '', '', '289', '1', '0', '', null, null);

-- ----------------------------
-- Table structure for `customer_class`
-- ----------------------------
DROP TABLE IF EXISTS `customer_class`;
CREATE TABLE `customer_class` (
  `customer_class_id` int(11) NOT NULL,
  `customer_class_name` varchar(40) DEFAULT '',
  `tender_media_id` int(11) DEFAULT NULL,
  `is_preoder_free` bit(1) DEFAULT b'0',
  PRIMARY KEY (`customer_class_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of customer_class
-- ----------------------------
INSERT INTO customer_class VALUES ('0', '1星', null, '');
INSERT INTO customer_class VALUES ('1', '２星', null, '');
INSERT INTO customer_class VALUES ('2', '３星', null, '');
INSERT INTO customer_class VALUES ('3', 'VIP', null, '');

-- ----------------------------
-- Table structure for `customer_consume`
-- ----------------------------
DROP TABLE IF EXISTS `customer_consume`;
CREATE TABLE `customer_consume` (
  `card_id` varchar(40) NOT NULL,
  `amount` decimal(11,2) DEFAULT NULL,
  `employee_id` int(11) DEFAULT NULL,
  `employee_name` varchar(40) DEFAULT NULL,
  `time` datetime DEFAULT NULL,
  `extend_1` varchar(40) DEFAULT NULL,
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `type` int(11) DEFAULT '0',
  `order_head_id` int(11) DEFAULT NULL,
  `web_id` int(11) DEFAULT NULL,
  `device_id` int(11) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of customer_consume
-- ----------------------------

-- ----------------------------
-- Table structure for `customer_display`
-- ----------------------------
DROP TABLE IF EXISTS `customer_display`;
CREATE TABLE `customer_display` (
  `customer_display_id` int(11) NOT NULL DEFAULT '0',
  `customer_display_name` varchar(30) DEFAULT '',
  `com_port` int(11) NOT NULL DEFAULT '0',
  `baud_rate` int(11) DEFAULT NULL,
  `parity_type` int(11) DEFAULT NULL,
  `num_data_bit` int(11) DEFAULT NULL,
  `num_stop_bits` int(11) DEFAULT NULL,
  PRIMARY KEY (`customer_display_id`,`com_port`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of customer_display
-- ----------------------------
INSERT INTO customer_display VALUES ('1', '顾显1', '111', '2400', '0', '8', '0');

-- ----------------------------
-- Table structure for `dcb_order`
-- ----------------------------
DROP TABLE IF EXISTS `dcb_order`;
CREATE TABLE `dcb_order` (
  `order_head_id` int(11) NOT NULL,
  `time_diff` varchar(30) DEFAULT NULL,
  `dcb_id` varchar(10) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of dcb_order
-- ----------------------------

-- ----------------------------
-- Table structure for `descriptors_discount_service_slu`
-- ----------------------------
DROP TABLE IF EXISTS `descriptors_discount_service_slu`;
CREATE TABLE `descriptors_discount_service_slu` (
  `dds_slu_id` int(11) NOT NULL,
  `dds_slu_number` int(11) NOT NULL,
  `dds_slu_name` varchar(30) DEFAULT NULL,
  `touchscreen_style` int(11) DEFAULT NULL,
  PRIMARY KEY (`dds_slu_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of descriptors_discount_service_slu
-- ----------------------------

-- ----------------------------
-- Table structure for `descriptors_headers`
-- ----------------------------
DROP TABLE IF EXISTS `descriptors_headers`;
CREATE TABLE `descriptors_headers` (
  `descriptors_headers_id` int(11) NOT NULL,
  `descriptors_headers_number` int(11) DEFAULT NULL,
  `descriptors_headers_name` varchar(30) DEFAULT NULL,
  `line_1` varchar(100) DEFAULT NULL,
  `pirnt_type_1` int(11) DEFAULT '0',
  `line_2` varchar(100) DEFAULT NULL,
  `pirnt_type_2` int(11) DEFAULT '0',
  `line_3` varchar(100) DEFAULT NULL,
  `pirnt_type_3` int(11) DEFAULT '0',
  `line_4` varchar(100) DEFAULT NULL,
  `pirnt_type_4` int(11) DEFAULT '0',
  `line_5` varchar(100) DEFAULT NULL,
  `pirnt_type_5` int(11) DEFAULT '0',
  `line_6` varchar(100) DEFAULT NULL,
  `pirnt_type_6` int(11) DEFAULT '0',
  PRIMARY KEY (`descriptors_headers_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of descriptors_headers
-- ----------------------------
INSERT INTO descriptors_headers VALUES ('1', null, '餐厅名称账单头', '聚客ケータリング ソフトウェア', '0', '', '0', '', '0', '', '0', '', '0', '', '0');

-- ----------------------------
-- Table structure for `descriptors_menu_item_slu`
-- ----------------------------
DROP TABLE IF EXISTS `descriptors_menu_item_slu`;
CREATE TABLE `descriptors_menu_item_slu` (
  `dmi_slu_id` int(11) NOT NULL,
  `dmi_slu_number` int(11) DEFAULT NULL,
  `dmi_slu_name` varchar(30) DEFAULT NULL,
  `touchscreen_style` int(11) DEFAULT NULL,
  `class_id` int(11) DEFAULT '-1',
  `print_class` int(11) DEFAULT '-1',
  `allow_condimentint` int(11) DEFAULT '-1',
  `required_condiment` int(11) DEFAULT '-1',
  `item_type` int(11) DEFAULT '0',
  `major_group` int(11) DEFAULT '-1',
  `family_group` int(11) DEFAULT '-1',
  `period_class_id` int(11) DEFAULT '-1',
  `rvc_class_id` int(11) DEFAULT '-1',
  `ticket_class` int(11) DEFAULT '1',
  `tax_group` int(11) DEFAULT '-1',
  `commission_type` int(11) DEFAULT '0',
  `commission_value` float DEFAULT '0',
  PRIMARY KEY (`dmi_slu_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of descriptors_menu_item_slu
-- ----------------------------
INSERT INTO descriptors_menu_item_slu VALUES ('1', null, 'FOOD', null, '-1', '-1', '-1', '-1', '0', '-1', '-1', '-1', '-1', '1', '-1', '0', '0');
INSERT INTO descriptors_menu_item_slu VALUES ('2', null, 'WINE', null, '-1', '-1', '-1', '-1', '0', '-1', '-1', '-1', '-1', '1', '-1', '0', '0');
INSERT INTO descriptors_menu_item_slu VALUES ('3', null, 'BEER', null, '-1', '-1', '-1', '-1', '0', '-1', '-1', '-1', '-1', '1', '-1', '0', '0');
INSERT INTO descriptors_menu_item_slu VALUES ('4', null, 'DESSERT', null, '-1', '-1', '-1', '-1', '0', '-1', '-1', '-1', '-1', '1', '-1', '0', '0');
INSERT INTO descriptors_menu_item_slu VALUES ('5', null, 'COFFEE & TEA', null, '-1', '-1', '-1', '-1', '0', '-1', '-1', '-1', '-1', '1', '-1', '0', '0');
INSERT INTO descriptors_menu_item_slu VALUES ('6', null, 'DRINK', null, '-1', '-1', '-1', '-1', '0', '-1', '-1', '-1', '-1', '1', '-1', '0', '0');
INSERT INTO descriptors_menu_item_slu VALUES ('7', null, 'COURSE MENU', null, '-1', '-1', '-1', '-1', '0', '-1', '-1', '-1', '-1', '1', '-1', '0', '0');
INSERT INTO descriptors_menu_item_slu VALUES ('9999', null, '不显示', null, '6', '-1', '-1', '-1', '0', '-1', '-1', '-1', '-1', '1', '-1', '0', '0');

-- ----------------------------
-- Table structure for `descriptors_sales_itemizers`
-- ----------------------------
DROP TABLE IF EXISTS `descriptors_sales_itemizers`;
CREATE TABLE `descriptors_sales_itemizers` (
  `ds_itemizers_id` int(11) NOT NULL,
  `ds_itemizers_number` int(11) NOT NULL,
  `ds_itemizers_name` varchar(30) DEFAULT NULL,
  PRIMARY KEY (`ds_itemizers_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of descriptors_sales_itemizers
-- ----------------------------

-- ----------------------------
-- Table structure for `descriptors_tender_media_slu`
-- ----------------------------
DROP TABLE IF EXISTS `descriptors_tender_media_slu`;
CREATE TABLE `descriptors_tender_media_slu` (
  `dtm_slu_id` int(11) NOT NULL,
  `dtm_slu_number` int(11) NOT NULL,
  `dtm_slu_name` varchar(30) DEFAULT NULL,
  `touchscreen_style` int(11) DEFAULT NULL,
  PRIMARY KEY (`dtm_slu_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of descriptors_tender_media_slu
-- ----------------------------

-- ----------------------------
-- Table structure for `descriptors_trailers`
-- ----------------------------
DROP TABLE IF EXISTS `descriptors_trailers`;
CREATE TABLE `descriptors_trailers` (
  `descriptors_trailers_id` int(11) NOT NULL,
  `descriptors_trailers_number` int(11) DEFAULT NULL,
  `descriptors_trailers_name` varchar(30) DEFAULT NULL,
  `line_1` varchar(100) DEFAULT NULL,
  `pirnt_type_1` int(11) DEFAULT '0',
  `line_2` varchar(100) DEFAULT NULL,
  `pirnt_type_2` int(11) DEFAULT '0',
  `line_3` varchar(100) DEFAULT NULL,
  `pirnt_type_3` int(11) DEFAULT '0',
  `line_4` varchar(100) DEFAULT NULL,
  `pirnt_type_4` int(11) DEFAULT '0',
  `line_5` varchar(100) DEFAULT NULL,
  `pirnt_type_5` int(11) DEFAULT '0',
  `line_6` varchar(100) DEFAULT NULL,
  `pirnt_type_6` int(11) DEFAULT '0',
  `line_7` varchar(100) DEFAULT NULL,
  `pirnt_type_7` int(11) DEFAULT '0',
  `line_8` varchar(100) DEFAULT NULL,
  `pirnt_type_8` int(11) DEFAULT '0',
  `line_9` varchar(100) DEFAULT NULL,
  `pirnt_type_9` int(11) DEFAULT '0',
  `line_10` varchar(100) DEFAULT NULL,
  `pirnt_type_10` int(11) DEFAULT '0',
  `line_11` varchar(100) DEFAULT NULL,
  `pirnt_type_11` int(11) DEFAULT '0',
  `line_12` varchar(100) DEFAULT NULL,
  `pirnt_type_12` int(11) DEFAULT '0',
  PRIMARY KEY (`descriptors_trailers_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of descriptors_trailers
-- ----------------------------
INSERT INTO descriptors_trailers VALUES ('1', null, '餐厅地址账单尾', ' ', '0', ' 来ていただき、ありがとうございます！', '0', '住所： 深セン ポリ レストラン', '0', '電話：0755-26631190', '0', '', '0', '', '0', '', '0', '', '0', '', '0', '', '0', '', '0', '', '0');

-- ----------------------------
-- Table structure for `device_checkin`
-- ----------------------------
DROP TABLE IF EXISTS `device_checkin`;
CREATE TABLE `device_checkin` (
  `device_id` varchar(100) DEFAULT NULL,
  `last_checkin_time` varchar(10) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of device_checkin
-- ----------------------------
INSERT INTO device_checkin VALUES ('347AC46CB3BDF023AEA64F1D1E7A92A6D83ED98888CD417FA78548A7F364B24E9D988B5BE6BBE6E8', '2012020811');

-- ----------------------------
-- Table structure for `device_com_ports`
-- ----------------------------
DROP TABLE IF EXISTS `device_com_ports`;
CREATE TABLE `device_com_ports` (
  `network_node_id` int(11) NOT NULL,
  `com_port` int(11) NOT NULL DEFAULT '0',
  `baud_rate` int(11) DEFAULT NULL,
  `parity_type` int(11) DEFAULT NULL,
  `num_data_bit` int(11) DEFAULT NULL,
  `num_stop_bits` int(11) DEFAULT NULL,
  PRIMARY KEY (`network_node_id`,`com_port`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of device_com_ports
-- ----------------------------

-- ----------------------------
-- Table structure for `discount_service`
-- ----------------------------
DROP TABLE IF EXISTS `discount_service`;
CREATE TABLE `discount_service` (
  `discount_service_id` int(11) NOT NULL,
  `discount_service_number` int(11) DEFAULT NULL,
  `discount_service_name` varchar(40) DEFAULT NULL,
  `type` int(11) NOT NULL DEFAULT '0',
  `print_class` int(11) DEFAULT NULL,
  `menu_level_class` int(11) DEFAULT NULL,
  `privilege` int(11) DEFAULT NULL,
  `nlu` int(11) DEFAULT NULL,
  `amount` int(11) DEFAULT NULL,
  `date_from` datetime DEFAULT NULL,
  `date_to` datetime DEFAULT NULL,
  `category` int(11) DEFAULT NULL,
  `percent` int(11) DEFAULT NULL,
  `preset` bit(1) DEFAULT NULL,
  `reference_required` bit(1) DEFAULT NULL,
  `auto_sys_chg` bit(1) DEFAULT NULL,
  `seat_filter_exit` bit(1) DEFAULT NULL,
  `assume_entire_amount` bit(1) DEFAULT NULL,
  `not_with_seat` bit(1) DEFAULT NULL,
  `employee_meal` bit(1) DEFAULT b'0',
  `discount_over_threshold` bit(1) DEFAULT NULL,
  `limit_discount` bit(1) DEFAULT NULL,
  `discount_last_item` bit(1) DEFAULT NULL,
  `single_seat` bit(1) DEFAULT NULL,
  `prorated_subtotal` bit(1) DEFAULT NULL,
  `select_discount` bit(1) DEFAULT NULL,
  `period_class_id` int(11) DEFAULT NULL,
  `rvc_class_id` int(11) DEFAULT NULL,
  `display_name` char(60) DEFAULT NULL,
  PRIMARY KEY (`discount_service_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of discount_service
-- ----------------------------
INSERT INTO discount_service VALUES ('1', null, '贈る', '0', '2', '6', '2', null, '0', null, null, '0', '100', '', null, null, null, '', null, '', null, null, null, null, null, '', '-1', '-1', '');
INSERT INTO discount_service VALUES ('2', null, '88%', '0', null, '6', '0', null, '0', null, null, '2', '12', '', null, null, null, '', null, '', null, null, null, null, null, '', null, null, '-88%');
INSERT INTO discount_service VALUES ('3', null, '80%', '0', null, '6', '0', null, '0', null, null, '2', '20', '', null, null, null, '', null, '', null, null, null, null, null, '', null, null, '-80%');
INSERT INTO discount_service VALUES ('4', null, '70%', '0', null, '0', '0', null, '0', null, null, '1', '70', '', null, null, null, '', null, '', null, null, null, null, null, '', null, null, '-70%');
INSERT INTO discount_service VALUES ('5', null, '50%', '0', null, '0', '0', null, '0', null, null, '1', '50', '', null, null, null, '', null, '', null, null, null, null, null, '', null, null, '-50%');
INSERT INTO discount_service VALUES ('6', null, '1000円', '0', null, '0', '0', null, '1000', null, null, '1', '0', '', null, null, null, '', null, '', null, null, null, null, null, '', null, null, '-1000円');
INSERT INTO discount_service VALUES ('7', null, '800円', '0', null, '0', '0', null, '800', null, null, '1', '0', '', null, null, null, '', null, '', null, null, null, null, null, '', null, null, '-800円');
INSERT INTO discount_service VALUES ('8', null, 'Open Discount', '1', null, '1', '2', null, '0', null, null, '0', '0', '', null, null, null, '', null, '', null, null, null, null, null, '', null, null, '');

-- ----------------------------
-- Table structure for `employee`
-- ----------------------------
DROP TABLE IF EXISTS `employee`;
CREATE TABLE `employee` (
  `employee_id` int(11) NOT NULL,
  `employee_last_name` varchar(40) DEFAULT '',
  `name_prefix` varchar(20) DEFAULT '',
  `first_name` varchar(20) DEFAULT '',
  `middle_name` varchar(20) DEFAULT '',
  `name_suffix` varchar(20) DEFAULT '',
  `previous_last_name` varchar(20) DEFAULT '',
  `ssn_sin` varchar(40) DEFAULT '',
  `password_id` varchar(20) DEFAULT '',
  `pc_aps_id` varchar(20) DEFAULT '',
  `payroll_id` varchar(20) DEFAULT '',
  `employee_class` int(11) DEFAULT NULL,
  `back_office_class` int(11) DEFAULT NULL,
  `revenue_center` int(11) DEFAULT NULL,
  `is_in_traning` bit(1) DEFAULT b'0',
  `is_minor` bit(1) DEFAULT b'0',
  `cash_drawer` int(11) DEFAULT NULL,
  `late_clock` int(11) DEFAULT '0',
  `lds_id` int(11) DEFAULT NULL,
  `cashier` int(11) DEFAULT NULL,
  `language_id` int(11) DEFAULT NULL,
  `start_date` datetime DEFAULT NULL,
  `end_date` datetime DEFAULT NULL,
  `job_rates` int(11) DEFAULT NULL,
  `check_name` varchar(40) DEFAULT '',
  `image` varchar(256) DEFAULT '',
  `front_password` varchar(40) DEFAULT '',
  `back_password` varchar(40) DEFAULT '',
  `period_class_id` int(11) DEFAULT NULL,
  `rvc_class_id` int(11) DEFAULT NULL,
  `commission` float DEFAULT '0',
  PRIMARY KEY (`employee_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of employee
-- ----------------------------
INSERT INTO employee VALUES ('101', '员工1', '', '', '', '', '', '', '', '', '', '5', null, null, '', '', null, '0', null, null, null, null, null, null, '', '', '', '', null, null, '0');
INSERT INTO employee VALUES ('102', '店长', '', '', '', '', '', '', '', '0004485929', '', '2', null, null, '', '', null, '0', null, null, null, null, null, null, '', '', '', '', null, null, '0');
INSERT INTO employee VALUES ('105', '收银2', '', '', '', '', '', '', '', '', '', '4', null, null, '', '', null, '0', null, null, null, null, null, null, '', '', '', '', null, null, '0');
INSERT INTO employee VALUES ('106', '收银1', '', '', '', '', '', '', '', '', '', '4', null, null, '', '', null, '0', null, null, null, null, null, null, '', '', '', '', null, null, '0');
INSERT INTO employee VALUES ('777', '财务', '', '', '', '', '', '', '279', '00123', '', '1', null, null, '', '', null, '0', null, null, null, null, null, null, '', '', '', '', null, null, '0');
INSERT INTO employee VALUES ('888', '测试帐号', '', '', '', '', '', '', '', '', '', '3', null, null, '', '', null, '0', null, null, null, null, null, null, '测试帐号', '', '', '', null, null, '0');
INSERT INTO employee VALUES ('999', '999', '', '', '', '', '', '', '', '', '', '99', null, null, '', '', null, '0', null, null, null, null, null, null, '', '', '', '', null, null, '0');

-- ----------------------------
-- Table structure for `employee_class`
-- ----------------------------
DROP TABLE IF EXISTS `employee_class`;
CREATE TABLE `employee_class` (
  `employee_class_id` int(11) NOT NULL,
  `employee_class_number` int(11) DEFAULT NULL,
  `employee_class_name` varchar(40) DEFAULT NULL,
  `menu_item_privilege` int(11) DEFAULT NULL,
  `void_item` bit(1) DEFAULT NULL,
  `edit_check` bit(1) DEFAULT NULL,
  `trans_table` bit(1) DEFAULT NULL,
  `payment` int(11) DEFAULT NULL,
  `refund` bit(1) DEFAULT NULL,
  `report_edit` bit(1) DEFAULT NULL,
  `void_preorder` bit(1) DEFAULT b'0',
  `manager_privilege` int(11) DEFAULT NULL,
  `move_check` bit(1) DEFAULT NULL,
  `split_check` bit(1) DEFAULT NULL,
  `send_order` bit(1) DEFAULT NULL,
  `print_prestatement` bit(1) DEFAULT NULL,
  `open_item` bit(1) DEFAULT NULL,
  `reprice` bit(1) DEFAULT NULL,
  `edit_checkname` bit(1) DEFAULT NULL,
  `print_bill` bit(1) DEFAULT NULL,
  `preorder` int(1) DEFAULT '0',
  `open_drawer` int(11) DEFAULT NULL,
  `reprint_check` bit(1) DEFAULT NULL,
  `end_of_day` bit(1) DEFAULT NULL,
  `delete_check` bit(1) DEFAULT NULL,
  `shift` bit(1) DEFAULT NULL,
  `vip_card` bit(1) DEFAULT NULL,
  `report_view` int(11) DEFAULT NULL,
  `menu_item` bit(1) DEFAULT NULL,
  `is_order` bit(1) DEFAULT b'0',
  `edit_customer` bit(1) DEFAULT b'0',
  `change_setting` bit(1) DEFAULT NULL,
  `del_employee_pwd` bit(1) DEFAULT NULL,
  `open_menu_item` bit(1) DEFAULT NULL,
  `open_config` bit(1) DEFAULT NULL,
  `open_employee_info` bit(1) DEFAULT NULL,
  `open_employee_class` bit(1) DEFAULT NULL,
  `authority_1` bit(1) DEFAULT NULL,
  `authority_2` bit(1) DEFAULT NULL,
  `authority_3` bit(1) DEFAULT NULL,
  `authority_4` bit(1) DEFAULT NULL,
  `authority_5` bit(1) DEFAULT NULL,
  `authority_6` bit(1) DEFAULT NULL,
  `authority_7` bit(1) DEFAULT NULL,
  `authority_8` bit(1) DEFAULT NULL,
  `authority_9` bit(1) DEFAULT NULL,
  `authority_10` bit(1) DEFAULT NULL,
  `authority_11` int(1) DEFAULT NULL,
  `authority_12` int(1) DEFAULT NULL,
  `authority_13` int(1) DEFAULT NULL,
  `authority_14` int(1) DEFAULT NULL,
  `authority_15` int(1) DEFAULT NULL,
  PRIMARY KEY (`employee_class_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of employee_class
-- ----------------------------
INSERT INTO employee_class VALUES ('1', null, '管理员', null, '', '', '', '3', '', '', '', '3', '', '', '', '', '', '', '', '', '3', '1', '', '', '', '', null, '1', null, '', '', null, null, '', '', '', '', '', '', null, null, null, null, null, null, null, null, '2000', null, null, null, null);
INSERT INTO employee_class VALUES ('2', null, '店长', '1', '', '', '', '3', '', '', '', '3', '', '', '', '', '', '', '', '', '3', '1', '', '', '', '', '', '1', null, '', '', '', '', '', '', '', '', '', '', null, null, null, null, null, null, null, null, '1000', null, null, null, null);
INSERT INTO employee_class VALUES ('3', null, '经理', null, '', '', '', '2', '', '', '', '2', '', '', '', '', '', '', '', '', '3', '0', '', '', '', '', null, '1', null, '', '', null, null, '', '', '', '', '', '', null, null, null, null, null, null, null, null, '200', null, null, null, null);
INSERT INTO employee_class VALUES ('4', null, '收银', null, '', '', '', '3', '', '', '', '2', '', '', '', '', '', '', '', '', '3', '1', '', '', '', '', null, '1', null, '', '', null, null, '', '', '', '', '', '', null, null, null, null, null, null, null, null, '200', null, null, null, null);
INSERT INTO employee_class VALUES ('5', null, '普通员工', null, '', '', '', '0', '', '', '', '0', '', '', '', '', '', '', '', '', '0', '0', '', '', '', '', null, '0', null, '', '', null, null, '', '', '', '', '', '', null, null, null, null, null, null, null, null, '200', null, null, null, null);
INSERT INTO employee_class VALUES ('99', '99', 'master', '3', '', '', '', '9', '', '', '', '3', '', '', '', '', '', '', '', '', '3', '0', '', '', '', '', '', '1', '', '', '', '', '', '', '', '', '', '', '', '', '', '', '', '', '', '', '', '99999', '10', '10', '10', '10');

-- ----------------------------
-- Table structure for `evaluation`
-- ----------------------------
DROP TABLE IF EXISTS `evaluation`;
CREATE TABLE `evaluation` (
  `evaluation_id` int(11) NOT NULL AUTO_INCREMENT,
  `menu_item_id` int(11) NOT NULL,
  `menu_item_name` varchar(40) DEFAULT NULL,
  `evaluation_type` int(11) DEFAULT '0',
  `evaluation_score` float DEFAULT '0',
  `evaluation_content` varchar(300) DEFAULT '',
  `customer_id` varchar(40) DEFAULT '0',
  `customer_name` varchar(40) DEFAULT '',
  `evaluation_time` datetime DEFAULT NULL,
  `extend_1` varchar(40) DEFAULT '',
  `extend_2` varchar(40) DEFAULT '',
  `extend_3` varchar(40) DEFAULT '',
  `extend_4` int(11) DEFAULT NULL,
  `extend_5` int(11) DEFAULT NULL,
  PRIMARY KEY (`evaluation_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of evaluation
-- ----------------------------

-- ----------------------------
-- Table structure for `family_group`
-- ----------------------------
DROP TABLE IF EXISTS `family_group`;
CREATE TABLE `family_group` (
  `family_group_id` int(11) NOT NULL DEFAULT '0',
  `family_group_name` varchar(40) DEFAULT NULL,
  PRIMARY KEY (`family_group_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of family_group
-- ----------------------------
INSERT INTO family_group VALUES ('2', '果汁');
INSERT INTO family_group VALUES ('3', '奶茶');
INSERT INTO family_group VALUES ('4', '咖啡');
INSERT INTO family_group VALUES ('5', '花果中国茶');
INSERT INTO family_group VALUES ('6', '甜品');
INSERT INTO family_group VALUES ('7', '酒水');
INSERT INTO family_group VALUES ('8', '凉菜');
INSERT INTO family_group VALUES ('9', '川菜');
INSERT INTO family_group VALUES ('10', '粤菜');
INSERT INTO family_group VALUES ('11', '西餐');
INSERT INTO family_group VALUES ('12', '时蔬');
INSERT INTO family_group VALUES ('13', '调味品');
INSERT INTO family_group VALUES ('14', '粥品');
INSERT INTO family_group VALUES ('15', '饭面');
INSERT INTO family_group VALUES ('16', '套餐');
INSERT INTO family_group VALUES ('17', '靓汤');
INSERT INTO family_group VALUES ('18', '其他');

-- ----------------------------
-- Table structure for `history_card`
-- ----------------------------
DROP TABLE IF EXISTS `history_card`;
CREATE TABLE `history_card` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `old_card_id` varchar(40) DEFAULT NULL,
  `new_card_id` varchar(40) DEFAULT NULL,
  `employee_id` int(11) DEFAULT NULL,
  `employee_name` varchar(60) DEFAULT NULL,
  `time` datetime DEFAULT NULL,
  `extend_1` varchar(40) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of history_card
-- ----------------------------

-- ----------------------------
-- Table structure for `history_day_end`
-- ----------------------------
DROP TABLE IF EXISTS `history_day_end`;
CREATE TABLE `history_day_end` (
  `history_day_end_id` int(11) NOT NULL AUTO_INCREMENT,
  `day` date NOT NULL,
  `rvc_center_id` int(11) NOT NULL,
  `period_id` int(11) NOT NULL,
  `eidt_time` datetime DEFAULT NULL,
  `sales_amount` decimal(11,2) DEFAULT NULL,
  `discount_amount` decimal(11,2) DEFAULT NULL,
  `service_amount` decimal(11,2) DEFAULT NULL,
  `return_amount` decimal(11,2) DEFAULT NULL,
  `should_amount` decimal(11,2) DEFAULT NULL,
  `actual_amount` decimal(11,2) DEFAULT NULL,
  `eatin_amount` decimal(11,2) DEFAULT NULL,
  `out_amount` decimal(11,2) DEFAULT NULL,
  `invoice_amount` decimal(11,2) DEFAULT NULL,
  `tax_amount` decimal(11,2) DEFAULT NULL,
  `customer_num` int(11) DEFAULT NULL,
  `chk_num` int(11) DEFAULT NULL,
  `table_num` int(11) DEFAULT NULL,
  PRIMARY KEY (`history_day_end_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of history_day_end
-- ----------------------------

-- ----------------------------
-- Table structure for `history_major_group`
-- ----------------------------
DROP TABLE IF EXISTS `history_major_group`;
CREATE TABLE `history_major_group` (
  `history_major_id` int(11) NOT NULL AUTO_INCREMENT,
  `day` date NOT NULL,
  `rvc_center_id` int(11) NOT NULL,
  `period_id` int(11) NOT NULL,
  `major_group_id` int(11) DEFAULT NULL,
  `amount` decimal(11,2) DEFAULT NULL,
  PRIMARY KEY (`history_major_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of history_major_group
-- ----------------------------

-- ----------------------------
-- Table structure for `history_material_detail`
-- ----------------------------
DROP TABLE IF EXISTS `history_material_detail`;
CREATE TABLE `history_material_detail` (
  `hm_detail_id` int(11) NOT NULL AUTO_INCREMENT,
  `hm_head_id` int(11) DEFAULT NULL,
  `material_id` int(11) DEFAULT NULL,
  `material_name` varchar(60) DEFAULT '',
  `price` float DEFAULT '0',
  `num` float DEFAULT NULL,
  `total` float DEFAULT '0',
  `unit` varchar(60) DEFAULT '',
  `mark` text,
  `extend_1` varchar(40) DEFAULT '',
  `extend_2` varchar(40) DEFAULT '',
  `extend_3` varchar(40) DEFAULT '',
  `extend_4` int(11) DEFAULT '0',
  `extend_5` int(11) DEFAULT '0',
  PRIMARY KEY (`hm_detail_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of history_material_detail
-- ----------------------------

-- ----------------------------
-- Table structure for `history_material_head`
-- ----------------------------
DROP TABLE IF EXISTS `history_material_head`;
CREATE TABLE `history_material_head` (
  `hm_head_id` int(11) NOT NULL AUTO_INCREMENT,
  `type` int(11) DEFAULT '0',
  `type_name` varchar(60) DEFAULT '',
  `suppliers_id` int(11) DEFAULT '-1',
  `pick_id` int(11) DEFAULT NULL,
  `price` float DEFAULT NULL,
  `warehouse_id` int(11) DEFAULT NULL,
  `employee_id` int(11) DEFAULT NULL,
  `employee_name` varchar(60) DEFAULT '',
  `pick_time` datetime DEFAULT NULL,
  `mark` text,
  `print_times` int(11) DEFAULT '0',
  `modify_time` datetime DEFAULT NULL,
  `modify_id` int(11) DEFAULT NULL,
  `modify_name` varchar(60) DEFAULT NULL,
  `extend_1` varchar(40) DEFAULT '',
  `extend_2` varchar(40) DEFAULT '',
  `extend_3` varchar(40) DEFAULT '',
  `extend_4` int(11) DEFAULT '0',
  `extend_5` int(11) DEFAULT '0',
  PRIMARY KEY (`hm_head_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of history_material_head
-- ----------------------------

-- ----------------------------
-- Table structure for `history_messages`
-- ----------------------------
DROP TABLE IF EXISTS `history_messages`;
CREATE TABLE `history_messages` (
  `history_message_id` int(11) NOT NULL AUTO_INCREMENT,
  `tel` varchar(50) DEFAULT NULL,
  `message_content` varchar(1000) DEFAULT NULL,
  `send_time` datetime DEFAULT NULL,
  `actual_time` datetime DEFAULT NULL,
  `type` int(11) DEFAULT '0',
  `status` int(11) DEFAULT '0',
  `user_id` int(11) DEFAULT NULL,
  `sender` int(11) DEFAULT NULL,
  `extend_1` int(11) DEFAULT NULL,
  `extend_2` varchar(300) DEFAULT NULL,
  `extend_3` varchar(300) DEFAULT NULL,
  `extend_4` varchar(300) DEFAULT NULL,
  `extend_5` varchar(300) DEFAULT NULL,
  PRIMARY KEY (`history_message_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of history_messages
-- ----------------------------

-- ----------------------------
-- Table structure for `history_order_detail`
-- ----------------------------
DROP TABLE IF EXISTS `history_order_detail`;
CREATE TABLE `history_order_detail` (
  `order_detail_id` int(11) NOT NULL,
  `order_head_id` int(11) DEFAULT NULL,
  `check_id` int(11) DEFAULT '1',
  `menu_item_id` int(11) DEFAULT '0',
  `menu_item_name` varchar(60) DEFAULT '',
  `product_price` float DEFAULT '0',
  `is_discount` bit(1) DEFAULT b'0',
  `original_price` float DEFAULT NULL,
  `discount_id` int(11) DEFAULT '0',
  `actual_price` float DEFAULT '0',
  `is_return_item` bit(1) DEFAULT b'0',
  `order_employee_id` int(11) DEFAULT '0',
  `order_employee_name` varchar(30) DEFAULT '',
  `pos_device_id` int(11) DEFAULT '0',
  `pos_name` varchar(30) DEFAULT '',
  `order_time` datetime DEFAULT NULL,
  `return_time` datetime DEFAULT NULL,
  `return_reason` varchar(200) DEFAULT '',
  `unit` varchar(30) DEFAULT '',
  `is_send` bit(1) DEFAULT b'0',
  `condiment_belong_item` int(11) DEFAULT '0',
  `quantity` float DEFAULT '0',
  `eat_type` int(11) DEFAULT '1',
  `auth_id` int(11) DEFAULT NULL,
  `auth_name` varchar(40) DEFAULT '',
  `weight_entry_required` bit(1) DEFAULT NULL,
  `description` char(100) DEFAULT NULL,
  `n_service_type` int(11) DEFAULT NULL,
  `not_print` int(11) DEFAULT NULL,
  `seat_num` int(11) DEFAULT NULL,
  `discount_price` float DEFAULT NULL,
  `sales_amount` float DEFAULT NULL,
  KEY `idx_detailcheck` (`order_head_id`,`check_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of history_order_detail
-- ----------------------------

-- ----------------------------
-- Table structure for `history_order_head`
-- ----------------------------
DROP TABLE IF EXISTS `history_order_head`;
CREATE TABLE `history_order_head` (
  `order_head_id` int(11) NOT NULL,
  `check_number` int(11) DEFAULT NULL,
  `rvc_center_id` int(11) DEFAULT NULL,
  `rvc_center_name` varchar(30) DEFAULT NULL,
  `table_id` int(11) DEFAULT NULL,
  `table_name` varchar(30) DEFAULT NULL,
  `check_id` int(11) NOT NULL DEFAULT '0',
  `open_employee_id` int(11) DEFAULT NULL,
  `open_employee_name` varchar(30) DEFAULT NULL,
  `customer_num` int(11) DEFAULT NULL,
  `customer_id` int(11) DEFAULT '0',
  `customer_name` varchar(30) DEFAULT NULL,
  `pos_device_id` int(11) DEFAULT NULL,
  `pos_name` varchar(30) DEFAULT NULL,
  `order_start_time` datetime DEFAULT NULL,
  `order_end_time` datetime DEFAULT NULL,
  `should_amount` float DEFAULT NULL,
  `return_amount` float DEFAULT NULL,
  `discount_amount` float DEFAULT NULL,
  `actual_amount` float DEFAULT NULL,
  `print_count` int(11) DEFAULT NULL,
  `status` int(11) DEFAULT NULL,
  `eat_type` int(11) DEFAULT NULL,
  `check_name` varchar(30) DEFAULT NULL,
  `original_amount` float DEFAULT '0',
  `service_amount` float DEFAULT '0',
  `edit_time` datetime DEFAULT NULL,
  `party_id` int(11) DEFAULT NULL,
  `edit_employee_name` varchar(30) DEFAULT NULL,
  `remark` varchar(50) DEFAULT NULL,
  `is_make` int(11) DEFAULT NULL,
  KEY `idx_headcheck` (`order_head_id`,`check_id`) USING BTREE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of history_order_head
-- ----------------------------

-- ----------------------------
-- Table structure for `history_payment`
-- ----------------------------
DROP TABLE IF EXISTS `history_payment`;
CREATE TABLE `history_payment` (
  `history_payment_id` int(11) NOT NULL AUTO_INCREMENT,
  `day` date NOT NULL,
  `rvc_center_id` int(11) NOT NULL,
  `period_id` int(11) NOT NULL,
  `payment_id` int(11) DEFAULT NULL,
  `amount` decimal(11,2) DEFAULT NULL,
  PRIMARY KEY (`history_payment_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of history_payment
-- ----------------------------

-- ----------------------------
-- Table structure for `history_time_clock`
-- ----------------------------
DROP TABLE IF EXISTS `history_time_clock`;
CREATE TABLE `history_time_clock` (
  `employee_id` int(11) NOT NULL,
  `clock_date` datetime NOT NULL,
  `clock_1` time DEFAULT NULL,
  `clock_2` time DEFAULT NULL,
  `clock_3` time DEFAULT NULL,
  `clock_4` time DEFAULT NULL,
  `clock_5` time DEFAULT NULL,
  `clock_6` time DEFAULT NULL,
  `clock_7` time DEFAULT NULL,
  `clock_8` time DEFAULT NULL,
  `clock_9` time DEFAULT NULL,
  `clock_10` time DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of history_time_clock
-- ----------------------------

-- ----------------------------
-- Table structure for `information_screens`
-- ----------------------------
DROP TABLE IF EXISTS `information_screens`;
CREATE TABLE `information_screens` (
  `info_id` int(11) NOT NULL,
  `info_number` int(11) DEFAULT NULL,
  `info_name` varchar(100) DEFAULT NULL,
  `line1` varchar(100) DEFAULT NULL,
  `line2` varchar(100) DEFAULT NULL,
  `line3` varchar(100) DEFAULT NULL,
  `line4` varchar(100) DEFAULT NULL,
  `line5` varchar(100) DEFAULT NULL,
  `line6` varchar(100) DEFAULT NULL,
  `line7` varchar(100) DEFAULT NULL,
  `line8` varchar(100) DEFAULT NULL,
  `line9` varchar(100) DEFAULT NULL,
  `line10` varchar(100) DEFAULT NULL,
  PRIMARY KEY (`info_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of information_screens
-- ----------------------------
INSERT INTO information_screens VALUES ('1', null, '***帮助信息***', '1.如何登录进入系统', '2.输入用户名+密码, 默认输入999', '3.按‘确定’键或‘登录’键', null, null, null, null, null, null, null);

-- ----------------------------
-- Table structure for `inventory_setting`
-- ----------------------------
DROP TABLE IF EXISTS `inventory_setting`;
CREATE TABLE `inventory_setting` (
  `setting_id` int(11) NOT NULL AUTO_INCREMENT,
  `ip_addr` varchar(60) DEFAULT NULL,
  `port` int(11) DEFAULT '8000',
  PRIMARY KEY (`setting_id`)
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of inventory_setting
-- ----------------------------
INSERT INTO inventory_setting VALUES ('1', '127.0.0.1:83 ', '8000');

-- ----------------------------
-- Table structure for `inventory_type`
-- ----------------------------
DROP TABLE IF EXISTS `inventory_type`;
CREATE TABLE `inventory_type` (
  `inventory_type_id` int(11) NOT NULL,
  `inventory_type_name` varchar(60) DEFAULT NULL,
  PRIMARY KEY (`inventory_type_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of inventory_type
-- ----------------------------
INSERT INTO inventory_type VALUES ('0', '自动出货');
INSERT INTO inventory_type VALUES ('1', '进货');
INSERT INTO inventory_type VALUES ('2', '手动出货');
INSERT INTO inventory_type VALUES ('3', '退货给经销商');
INSERT INTO inventory_type VALUES ('4', '退货给仓库');

-- ----------------------------
-- Table structure for `invoices`
-- ----------------------------
DROP TABLE IF EXISTS `invoices`;
CREATE TABLE `invoices` (
  `invoice_id` int(11) NOT NULL AUTO_INCREMENT,
  `order_head_id` int(11) DEFAULT NULL,
  `check_id` int(11) DEFAULT NULL,
  `invoice_number` varchar(30) DEFAULT NULL,
  `amount` decimal(10,0) DEFAULT NULL,
  `employee_id` int(11) DEFAULT NULL,
  `remark` varchar(30) DEFAULT NULL,
  `edit_time` datetime DEFAULT NULL,
  `pos_device_id` int(11) DEFAULT NULL,
  `rvc_center_id` int(11) DEFAULT NULL,
  PRIMARY KEY (`invoice_id`),
  UNIQUE KEY `order_head_id` (`order_head_id`,`check_id`) USING BTREE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of invoices
-- ----------------------------

-- ----------------------------
-- Table structure for `item_main_group`
-- ----------------------------
DROP TABLE IF EXISTS `item_main_group`;
CREATE TABLE `item_main_group` (
  `main_group_id` int(11) NOT NULL,
  `main_group_name` varchar(30) DEFAULT NULL,
  `second_group_id` int(11) NOT NULL,
  PRIMARY KEY (`main_group_id`,`second_group_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of item_main_group
-- ----------------------------
INSERT INTO item_main_group VALUES ('1', 'FOOD', '-1');
INSERT INTO item_main_group VALUES ('1', 'FOOD', '1');
INSERT INTO item_main_group VALUES ('2', 'WINE', '-1');
INSERT INTO item_main_group VALUES ('2', 'WINE', '2');
INSERT INTO item_main_group VALUES ('3', 'BEER', '-1');
INSERT INTO item_main_group VALUES ('3', 'BEER', '3');
INSERT INTO item_main_group VALUES ('4', 'DESSERT', '-1');
INSERT INTO item_main_group VALUES ('4', 'DESSERT', '4');
INSERT INTO item_main_group VALUES ('5', 'COFFEE & TEA', '-1');
INSERT INTO item_main_group VALUES ('5', 'COFFEE & TEA', '5');
INSERT INTO item_main_group VALUES ('6', 'DRINK', '-1');
INSERT INTO item_main_group VALUES ('6', 'DRINK', '6');
INSERT INTO item_main_group VALUES ('7', 'COURSE MENU', '-1');
INSERT INTO item_main_group VALUES ('7', 'COURSE MENU', '7');
INSERT INTO item_main_group VALUES ('9999', '回收站', '-1');
INSERT INTO item_main_group VALUES ('9999', '回收站', '9999');

-- ----------------------------
-- Table structure for `item_material`
-- ----------------------------
DROP TABLE IF EXISTS `item_material`;
CREATE TABLE `item_material` (
  `item_id` int(11) NOT NULL,
  `material_id` int(11) NOT NULL,
  `num` float DEFAULT NULL,
  `unit` varchar(60) DEFAULT NULL,
  `unit_index` int(11) DEFAULT '1',
  PRIMARY KEY (`item_id`,`material_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of item_material
-- ----------------------------

-- ----------------------------
-- Table structure for `item_rvc_group`
-- ----------------------------
DROP TABLE IF EXISTS `item_rvc_group`;
CREATE TABLE `item_rvc_group` (
  `rvc_group_id` int(11) NOT NULL,
  `main_group_id` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of item_rvc_group
-- ----------------------------

-- ----------------------------
-- Table structure for `item_second_group`
-- ----------------------------
DROP TABLE IF EXISTS `item_second_group`;
CREATE TABLE `item_second_group` (
  `second_group_id` int(11) NOT NULL,
  `second_group_name` varchar(30) DEFAULT NULL,
  `menu_item_id` int(11) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of item_second_group
-- ----------------------------
INSERT INTO item_second_group VALUES ('1', ' ', '3');
INSERT INTO item_second_group VALUES ('1', ' ', '3');
INSERT INTO item_second_group VALUES ('1', null, '3');

-- ----------------------------
-- Table structure for `item_unit`
-- ----------------------------
DROP TABLE IF EXISTS `item_unit`;
CREATE TABLE `item_unit` (
  `unit_id` int(11) NOT NULL AUTO_INCREMENT,
  `unit_name` varchar(30) DEFAULT NULL,
  PRIMARY KEY (`unit_id`)
) ENGINE=InnoDB AUTO_INCREMENT=5 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of item_unit
-- ----------------------------
INSERT INTO item_unit VALUES ('1', '大盛り');
INSERT INTO item_unit VALUES ('2', '并盛り');
INSERT INTO item_unit VALUES ('3', '小ライス');
INSERT INTO item_unit VALUES ('4', '特盛り');

-- ----------------------------
-- Table structure for `job`
-- ----------------------------
DROP TABLE IF EXISTS `job`;
CREATE TABLE `job` (
  `job_id` int(11) NOT NULL,
  `job_number` int(11) DEFAULT NULL,
  `job_name` varchar(40) DEFAULT NULL,
  `overriding_employee_class` int(11) DEFAULT NULL,
  `revenue_center` int(11) DEFAULT NULL,
  `clock_in_privilege` int(11) DEFAULT NULL,
  `is_direct_tips` bit(1) DEFAULT NULL,
  `is_indirect_tips` bit(1) DEFAULT NULL,
  `allow_early_late` bit(1) DEFAULT NULL,
  `print_tips_declared` bit(1) DEFAULT NULL,
  PRIMARY KEY (`job_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of job
-- ----------------------------

-- ----------------------------
-- Table structure for `macros`
-- ----------------------------
DROP TABLE IF EXISTS `macros`;
CREATE TABLE `macros` (
  `macros_id` int(11) NOT NULL DEFAULT '0',
  `macros_name` varchar(40) DEFAULT NULL,
  `macros_value` varchar(200) DEFAULT NULL,
  `remark` varchar(600) DEFAULT NULL,
  PRIMARY KEY (`macros_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of macros
-- ----------------------------
INSERT INTO macros VALUES ('0', 'USER_NAME_LEN', '3', '用户名长度');
INSERT INTO macros VALUES ('1', 'MAX_TABLE_NUM', '200', '最大桌号');
INSERT INTO macros VALUES ('2', 'MAX_ITEM_QUANTITY', '50', '最大数量');
INSERT INTO macros VALUES ('3', 'MAX_ITEM_WEIGHT', '50', '最大重量');
INSERT INTO macros VALUES ('4', 'MAX_GUEST_NUM', '20', '最大客人数');
INSERT INTO macros VALUES ('5', 'PREORDER_WARNING_HOUR', '5', '当前桌子在该值小时内有其他预订时，提醒');
INSERT INTO macros VALUES ('6', 'EXIT_AFTER_SEND', '1', '下单后的行为：0- 不跳转；1- 跳转到桌位；2- 跳转到登陆界面');
INSERT INTO macros VALUES ('7', 'PRINT_TRANS', '1', '转台打印：0 -不打印 1 -打印');
INSERT INTO macros VALUES ('8', 'EXIT_AFTER_PAY', '1', '付款后的行为：0- 不跳转；1- 跳转到桌位；2- 跳转到登陆界面');
INSERT INTO macros VALUES ('9', 'HEAD_BEGIN_ID', '1000', '账单头order_head的起始ID');
INSERT INTO macros VALUES ('10', 'COMBINE_ONE_CHECK', '1', '合台，合单时：  0 -合并到不同的单； 1 -合并到第一张单');
INSERT INTO macros VALUES ('11', 'ROUND_ITEM_TTLPRICE', '0', '1 -计算单个菜品总价时四舍五入 ； 0 -不舍入');
INSERT INTO macros VALUES ('12', 'USE_SHOW_TEL', '0', '启动预订管理程序时，是否启动来电显示功能:\r\n1.启动\r\n0.不启动');
INSERT INTO macros VALUES ('13', 'NO_AUTO_COMBINE', '0', '0 -点菜时自动合并   1 -取消自动合并，一个菜一栏');
INSERT INTO macros VALUES ('14', 'COMBINE_PAYITEM', '1', '0 -不合并   1 -结帐单自动合并菜品');
INSERT INTO macros VALUES ('15', 'COMBINE_SENDITEM', '0', '0 -不合并   1 -厨房单自动合并菜品');
INSERT INTO macros VALUES ('16', 'NOPRINT_VOID', '0', '0 -退菜打印   1 -退菜不打印');
INSERT INTO macros VALUES ('17', 'PRINT_CONDIMENT', '0', '0 -结帐单不打印配料   1 -打印配料');
INSERT INTO macros VALUES ('18', 'FORCE_MINLIMIT', '1', '消费限制是否强制 0 -否   1 -是');
INSERT INTO macros VALUES ('19', 'PAYMENT_ORDER', '0', '结账单菜品打印顺序 0 -点菜顺序   1 -按大类排序 2 -菜品价格排序');
INSERT INTO macros VALUES ('20', 'SENDITEM_ORDER', '0', '送厨单菜品打印顺序 0 -点菜顺序   1 -按报表子类分类');
INSERT INTO macros VALUES ('21', 'SYNC_PAD_PDA', '0', '在编辑菜单后是否同步到平板和PDA\r\n0：不同步\r\n1:同步');
INSERT INTO macros VALUES ('22', 'USE_SALE_TIME', '0', '是否使用营业开始时间\r\n0：不使用，每天时间从0:00:00到23:59:59\r\n1:使用，每天时间从第一天的开始时间到第二天的开始时间');
INSERT INTO macros VALUES ('23', 'PRINT_VIPINFO', '1', '0 -不打印   1 -结帐单打印会员信息');
INSERT INTO macros VALUES ('24', 'PRINT_ALLMAKEITEM', '0', '划菜单是否打印整单菜品\n 0 -不打印   1 -打印');
INSERT INTO macros VALUES ('25', 'PAYMENT_CHANGE_TIME', '8', '提示找零的时间(秒)，小于等于0则不倒计时');
INSERT INTO macros VALUES ('26', 'CURRENCY', '￥', '货币符号');
INSERT INTO macros VALUES ('27', 'SALES_REPORT_TYPE', '111', '前台销售总结报表内容,每一位为1表示开启报表\r\n个位: 分段销量\r\n十位: 大类销量\r\n百位: 部门销量');
INSERT INTO macros VALUES ('28', 'CARD_REGEX', '0d+', '员工卡的识别正则表达式。请用户不要更改！');
INSERT INTO macros VALUES ('29', 'SHOW_ITEM_ID', '1', '点菜界面显示菜品ID');
INSERT INTO macros VALUES ('30', 'DISCOUNT_TYPE', '0', '折扣类型限制：\n0 :只能有一个整单折扣\n1 :只能有一个折扣\n 2：不限制折扣');
INSERT INTO macros VALUES ('31', 'DECIMAL_PLACES', '1', '精确到小数点后几位');
INSERT INTO macros VALUES ('32', 'NO_AUTO_CLOSECHK', '0', '取消自动关闭空白账单  0-自动 1-不自动');
INSERT INTO macros VALUES ('33', 'PRINTCHK_TWICE', '0', '收银小票是否打印2次');
INSERT INTO macros VALUES ('34', 'NOPRINT_PDA', '0', 'PDA点菜配置为不送厨');

-- ----------------------------
-- Table structure for `macros_key`
-- ----------------------------
DROP TABLE IF EXISTS `macros_key`;
CREATE TABLE `macros_key` (
  `key_str` varchar(200) DEFAULT NULL,
  `install_date` blob,
  `key_id` int(11) NOT NULL,
  `is_syc` bit(1) DEFAULT NULL,
  PRIMARY KEY (`key_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of macros_key
-- ----------------------------
INSERT INTO macros_key VALUES (null, 0x5D396CB592F5C8CF6974088E2E37C502, '0', null);

-- ----------------------------
-- Table structure for `major_group`
-- ----------------------------
DROP TABLE IF EXISTS `major_group`;
CREATE TABLE `major_group` (
  `major_group_id` int(11) NOT NULL DEFAULT '0',
  `major_group_name` varchar(40) DEFAULT NULL,
  PRIMARY KEY (`major_group_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of major_group
-- ----------------------------
INSERT INTO major_group VALUES ('1', '吧台');
INSERT INTO major_group VALUES ('2', '外场');
INSERT INTO major_group VALUES ('3', '厨房');
INSERT INTO major_group VALUES ('4', '其他');

-- ----------------------------
-- Table structure for `material`
-- ----------------------------
DROP TABLE IF EXISTS `material`;
CREATE TABLE `material` (
  `material_id` int(11) NOT NULL AUTO_INCREMENT,
  `material_name` varchar(60) DEFAULT '',
  `material_price` float DEFAULT '0',
  `material_unit` varchar(60) DEFAULT '',
  `nlu` varchar(20) DEFAULT '',
  `family_group` int(11) DEFAULT NULL,
  `num` float DEFAULT '0',
  `flag` bit(1) DEFAULT b'0',
  `extend_1` varchar(40) DEFAULT '',
  `extend_2` varchar(40) DEFAULT '',
  `extend_3` varchar(40) DEFAULT '',
  `extend_4` int(11) DEFAULT '0',
  `extend_5` int(11) DEFAULT '0',
  PRIMARY KEY (`material_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of material
-- ----------------------------

-- ----------------------------
-- Table structure for `menu_item`
-- ----------------------------
DROP TABLE IF EXISTS `menu_item`;
CREATE TABLE `menu_item` (
  `item_id` int(11) NOT NULL,
  `item_name1` varchar(60) DEFAULT NULL,
  `item_name2` varchar(60) DEFAULT NULL,
  `icon` varchar(512) DEFAULT NULL,
  `slu_id` int(11) DEFAULT NULL,
  `nlu` varchar(20) DEFAULT NULL,
  `class_id` int(11) DEFAULT NULL,
  `print_class` int(11) DEFAULT NULL,
  `item_type` int(11) DEFAULT '0',
  `allow_condiment` int(11) DEFAULT NULL,
  `required_condiment` int(11) DEFAULT '0',
  `check_availability` bit(1) DEFAULT NULL,
  `no_access_mgr` bit(1) DEFAULT NULL,
  `major_group` int(11) DEFAULT NULL,
  `family_group` int(11) DEFAULT NULL,
  `price_1` float DEFAULT '0',
  `cost_1` float DEFAULT '0',
  `unit_1` varchar(30) DEFAULT '',
  `date_from_1` date DEFAULT NULL,
  `date_to_1` date DEFAULT NULL,
  `surcharge_1` float DEFAULT '0',
  `tare_weight_1` float DEFAULT '0',
  `price_2` float DEFAULT '0',
  `cost_2` float DEFAULT '0',
  `unit_2` varchar(30) DEFAULT '',
  `date_from_2` date DEFAULT NULL,
  `date_to_2` date DEFAULT NULL,
  `surcharge_2` float DEFAULT '0',
  `tare_weight_2` float DEFAULT '0',
  `price_3` float DEFAULT '0',
  `cost_3` float DEFAULT '0',
  `unit_3` varchar(30) DEFAULT '',
  `date_from_3` date DEFAULT NULL,
  `date_to_3` date DEFAULT NULL,
  `surcharge_3` float DEFAULT '0',
  `tare_weight_3` float DEFAULT '0',
  `price_4` float DEFAULT '0',
  `cost_4` float DEFAULT '0',
  `unit_4` varchar(30) DEFAULT '',
  `date_from_4` date DEFAULT NULL,
  `date_to_4` date DEFAULT NULL,
  `surcharge_4` float DEFAULT '0',
  `tare_weight_4` float DEFAULT '0',
  `price_5` float DEFAULT '0',
  `cost_5` float DEFAULT '0',
  `unit_5` varchar(30) DEFAULT '',
  `date_from_5` date DEFAULT NULL,
  `date_to_5` date DEFAULT NULL,
  `surcharge_5` float DEFAULT '0',
  `tare_weight_5` float DEFAULT NULL,
  `slu_priority` int(11) DEFAULT '0',
  `period_class_id` int(11) DEFAULT '0',
  `rvc_class_id` int(11) DEFAULT '0',
  `commission_type` int(11) DEFAULT '0',
  `commission_value` float DEFAULT '0',
  `ticket_class` int(11) DEFAULT '1',
  `tax_group` int(11) DEFAULT '-1',
  PRIMARY KEY (`item_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of menu_item
-- ----------------------------
INSERT INTO menu_item VALUES ('1000', 'フォアグラのムース', '', null, '1', 'フォアグラのムース', '6', '1', '0', null, '5', null, null, '-1', '-1', '525', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1');
INSERT INTO menu_item VALUES ('1001', 'ホタルイカと空豆、カラスミのスパゲッティ', '', null, '1', 'ホタルイカとKD、カ', '6', '1', '0', null, '-1', null, null, '-1', '-1', '1260', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1');
INSERT INTO menu_item VALUES ('1002', '蝦夷鹿のカルパッチョ 胡桃、ゴルゴンゾーラと共に', '', null, '1', 'XYLのカルパッチョ', '6', '1', '0', null, '-1', null, null, '-1', '-1', '1100', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1');
INSERT INTO menu_item VALUES ('1003', '鮮魚のソテー　バーニャカウダ仕立て　', '', null, '1', 'XYのソテー　バーニ', '6', '1', '0', null, '-1', null, null, '-1', '-1', '1900', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1');
INSERT INTO menu_item VALUES ('1004', '仔羊のロースト　桜のソース', '', null, '1', 'ZYのロースト　Yの', '6', '1', '0', null, '-1', null, null, '-1', '-1', '2100', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1');
INSERT INTO menu_item VALUES ('1005', '富士金華豚肩ロースのロースト　焦がしバターとケッパーのソース', '', null, '9999', 'FSJKTJロースの', '6', '1', '0', null, '-1', null, null, '-1', '-1', '2400', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1');
INSERT INTO menu_item VALUES ('1006', 'トリッパのトマト煮とスカルモルツァチーズのグラタン仕立て', '', null, '9999', 'トリッパのトマトZと', '6', '1', '0', null, '-1', null, null, '-1', '-1', '1200', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1');
INSERT INTO menu_item VALUES ('1007', '桜海老と春野菜のアリオオーリオ', '', null, '1', 'YHLとCYCのアリ', '6', '1', '0', null, '-1', null, null, '-1', '-1', '1365', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1');
INSERT INTO menu_item VALUES ('1008', 'グラスワイン', '', null, '2', 'グラスワイン', '6', '1', '0', null, '-1', null, null, '-1', '-1', '630', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1');
INSERT INTO menu_item VALUES ('1009', 'ボトルワイン', '', null, '2', 'ボトルワイン', '6', '1', '0', null, '-1', null, null, '-1', '-1', '3150', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1');
INSERT INTO menu_item VALUES ('1010', 'バディア・ディ・モローナ　トスカーナ', '', null, '2', 'バディア・ディ・モロ', '6', '1', '0', null, '-1', null, null, '-1', '-1', '3150', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1');
INSERT INTO menu_item VALUES ('1011', '生ビール：プレミアムモルツ', '', null, '3', 'Sビール：プレミアム', '6', '1', '0', null, '-1', null, null, '-1', '-1', '525', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1');
INSERT INTO menu_item VALUES ('1012', 'オールフリー（ノンアルコールビール）', '', null, '3', 'オールフリー（ノンア', '6', '1', '0', null, '-1', null, null, '-1', '-1', '525', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1');
INSERT INTO menu_item VALUES ('1013', 'パンナコッタ　苺のスープ仕立て', '', null, '4', 'パンナコッタ　Mのス', '6', '1', '0', null, '-1', null, null, '-1', '-1', '630', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1');
INSERT INTO menu_item VALUES ('1014', 'テリーヌショコラと生姜のジェラート　オレンジソース', '', null, '9999', 'テリーヌショコラとS', '6', '1', '0', null, '-1', null, null, '-1', '-1', '735', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1');
INSERT INTO menu_item VALUES ('1015', 'ティラミス', '', null, '4', 'ティラミス', '6', '1', '0', null, '-1', null, null, '-1', '-1', '630', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1');
INSERT INTO menu_item VALUES ('1016', 'グレープフルーツのコンポート　サフラン風味', '', null, '4', 'グレープフルーツのコ', '6', '1', '0', null, '-1', null, null, '-1', '-1', '630', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1');
INSERT INTO menu_item VALUES ('1017', 'ノッチョーラ バニラジェラート添え', '', null, '4', 'ノッチョーラバニラジ', '6', '1', '0', null, '-1', null, null, '-1', '-1', '630', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1');
INSERT INTO menu_item VALUES ('1018', 'コーヒー', '', null, '5', 'コーヒー', '6', '1', '0', null, '-1', null, null, '-1', '-1', '420', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1');
INSERT INTO menu_item VALUES ('1019', '紅茶', '', null, '5', 'JC', '6', '1', '0', null, '-1', null, null, '-1', '-1', '420', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1');
INSERT INTO menu_item VALUES ('1020', 'エスプレッソ（ｓ）', '', null, '5', 'エスプレッソ（Ｓ）', '6', '1', '0', null, '-1', null, null, '-1', '-1', '420', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1');
INSERT INTO menu_item VALUES ('1021', 'エスプレッソ（ｗ）', '', null, '5', 'エスプレッソ（Ｗ）', '6', '1', '0', null, '-1', null, null, '-1', '-1', '525', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1');
INSERT INTO menu_item VALUES ('1022', 'スルジーヴァ', '', null, '6', 'スルジーヴァ', '6', '1', '0', null, '-1', null, null, '-1', '-1', '630', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1');
INSERT INTO menu_item VALUES ('1023', 'オレンジジュース', '', null, '6', 'オレンジジュース', '6', '1', '0', null, '-1', null, null, '-1', '-1', '420', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1');
INSERT INTO menu_item VALUES ('1024', '平日ランチ（火－金）', '', null, '7', 'PRランチ（H－J）', '6', '1', '3', null, '-1', null, null, '-1', '-1', '900', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1');
INSERT INTO menu_item VALUES ('1025', '週末ランチ（土・日）', '', null, '7', 'ZMランチ（T・R）', '6', '1', '3', null, '-1', null, null, '-1', '-1', '1600', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1');
INSERT INTO menu_item VALUES ('1026', '前菜盛り合わせ', '', null, '9999', 'QCSりHわせ', '6', '1', '0', null, '-1', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1');
INSERT INTO menu_item VALUES ('1027', 'パスタ', '', null, '9999', 'パスタ', '6', '1', '0', null, '-1', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1');
INSERT INTO menu_item VALUES ('1028', 'メインディッシュ', '', null, '9999', 'メインディッシュ', '6', '1', '0', null, '-1', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1');
INSERT INTO menu_item VALUES ('1029', 'デザート', '', null, '9999', 'デザート', '6', '1', '0', null, '-1', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1');
INSERT INTO menu_item VALUES ('1030', 'コーヒー又は紅茶', '', null, '9999', 'コーヒーYはJC', '6', '1', '0', null, '-1', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1');
INSERT INTO menu_item VALUES ('1031', 'サラダ', '', null, '9999', 'サラダ', '6', '1', '0', null, '-1', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1');
INSERT INTO menu_item VALUES ('1032', 'コーヒー', '', null, '9999', 'コーヒー', '6', '1', '0', null, '-1', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1');
INSERT INTO menu_item VALUES ('1033', '前菜盛合せ', '', null, '9999', 'QCSHせ', '6', '1', '0', null, '-1', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1');
INSERT INTO menu_item VALUES ('1034', 'コースメニュー', '', null, '7', 'コースメニュー', '6', '1', '3', null, '-1', null, null, '-1', '-1', '4200', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1');
INSERT INTO menu_item VALUES ('6000', 'こうしょう', null, null, '-1', 'こうしょう', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1');
INSERT INTO menu_item VALUES ('6001', 'ういきょう', null, null, '-1', 'ういきょう', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1');
INSERT INTO menu_item VALUES ('6002', 'はっかく', null, null, '-1', 'はっかく', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1');
INSERT INTO menu_item VALUES ('6003', 'ぢょうじ', null, null, '-1', 'ぢょうじ', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1');
INSERT INTO menu_item VALUES ('6004', 'ちんぴ', null, null, '-1', 'ちんぴ', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1');
INSERT INTO menu_item VALUES ('6005', 'さんしょう', null, null, '-1', 'さんしょう', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1');
INSERT INTO menu_item VALUES ('6006', 'しょうが', null, null, '-1', 'しょうが', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1');
INSERT INTO menu_item VALUES ('6007', 'わさび', null, null, '-1', 'わさび', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1');
INSERT INTO menu_item VALUES ('6008', 'マヨネーズ', null, null, '-1', 'マヨネーズ', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1');
INSERT INTO menu_item VALUES ('6009', 'ゴマ味噌', null, null, '-1', 'ゴマWC', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1');
INSERT INTO menu_item VALUES ('6010', 'しょうゆ', null, null, '-1', 'しょうゆ', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1');
INSERT INTO menu_item VALUES ('6011', 'ケジャップ', null, null, '-1', 'ケジャップ', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1');
INSERT INTO menu_item VALUES ('6012', 'トーバンジャン', null, null, '-1', 'トーバンジャン', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1');
INSERT INTO menu_item VALUES ('6013', 'チリソース', null, null, '-1', 'チリソース', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1');
INSERT INTO menu_item VALUES ('6014', 'あみのしおから', null, null, '-1', 'あみのしおから', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1');
INSERT INTO menu_item VALUES ('6015', 'さとう', null, null, '-1', 'さとう', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1');
INSERT INTO menu_item VALUES ('6016', 'ざらめ', null, null, '-1', 'ざらめ', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1');
INSERT INTO menu_item VALUES ('6017', 'くろざとう', null, null, '-1', 'くろざとう', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1');
INSERT INTO menu_item VALUES ('6018', '角砂糖', null, null, '-1', 'JST', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1');
INSERT INTO menu_item VALUES ('6019', '氷砂糖', null, null, '-1', 'BST', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1');
INSERT INTO menu_item VALUES ('6020', 'サラダオイル', null, null, '-1', 'サラダオイル', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1');
INSERT INTO menu_item VALUES ('6021', 'ごま油', null, null, '-1', 'ごまY', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1');
INSERT INTO menu_item VALUES ('6022', 'だいずあぶら', null, null, '-1', 'だいずあぶら', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1');
INSERT INTO menu_item VALUES ('6023', 'なたねあぶら', null, null, '-1', 'なたねあぶら', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1');
INSERT INTO menu_item VALUES ('6024', 'らっかせいあぶら', null, null, '-1', 'らっかせいあぶら', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1');
INSERT INTO menu_item VALUES ('6025', 'ラード', null, null, '-1', 'ラード', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1');
INSERT INTO menu_item VALUES ('6026', 'からし', null, null, '-1', 'からし', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1');
INSERT INTO menu_item VALUES ('6027', 'カレー', null, null, '-1', 'カレー', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1');
INSERT INTO menu_item VALUES ('6028', 'とうがらし', null, null, '-1', 'とうがらし', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1');
INSERT INTO menu_item VALUES ('6029', '塩', null, null, '-1', 'Y', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1');
INSERT INTO menu_item VALUES ('6030', '食塩', null, null, '-1', 'SY', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1');
INSERT INTO menu_item VALUES ('6031', 'しょうゆ', null, null, '-1', 'しょうゆ', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1');
INSERT INTO menu_item VALUES ('6032', '酢', null, null, '-1', 'Z', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1');
INSERT INTO menu_item VALUES ('6033', 'ソース', null, null, '-1', 'ソース', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1');
INSERT INTO menu_item VALUES ('6034', 'みりん', null, null, '-1', 'みりん', '6', null, '1', null, '0', null, null, '-1', '-1', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', '0', '0', '0', '', null, null, '0', null, '0', '0', '0', '0', '0', '1', '-1');

-- ----------------------------
-- Table structure for `menu_item_class`
-- ----------------------------
DROP TABLE IF EXISTS `menu_item_class`;
CREATE TABLE `menu_item_class` (
  `item_class_id` int(11) NOT NULL,
  `item_class_number` int(11) DEFAULT NULL,
  `item_class_name` varchar(40) DEFAULT NULL,
  `sale_itemizer` int(11) DEFAULT NULL,
  `discount_itemizer` int(11) DEFAULT NULL,
  `print_group` int(11) DEFAULT '-1',
  `halo` int(11) DEFAULT NULL,
  `service_itemizer` int(11) DEFAULT NULL,
  `privilege` int(11) DEFAULT NULL,
  `appetizers` bit(1) DEFAULT NULL,
  `reference_required` bit(1) DEFAULT NULL,
  `beverages` bit(1) DEFAULT NULL,
  `weight_entry_required` bit(1) DEFAULT b'0',
  `condiments` bit(1) DEFAULT NULL,
  `increment_seat_number` bit(1) DEFAULT NULL,
  `condiment_seat_number` bit(1) DEFAULT NULL,
  `condiments_prefixes` bit(1) DEFAULT NULL,
  `match_condiments_quantity` bit(1) DEFAULT NULL,
  `shareable` bit(1) DEFAULT NULL,
  `count_menu_item` bit(1) DEFAULT NULL,
  `lds_items` bit(1) DEFAULT NULL,
  `retail_items` bit(1) DEFAULT NULL,
  `include_in_repeat_round` bit(1) DEFAULT NULL COMMENT ' ',
  PRIMARY KEY (`item_class_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of menu_item_class
-- ----------------------------
INSERT INTO menu_item_class VALUES ('1', null, '称重不打折收服务费', null, '0', '-1', null, '9', null, null, null, null, '', null, null, null, null, null, null, null, null, null, null);
INSERT INTO menu_item_class VALUES ('2', null, '称重打折收服务费', null, '9', '-1', null, '9', null, null, null, null, '', null, null, null, null, null, null, null, null, null, null);
INSERT INTO menu_item_class VALUES ('3', null, '不打折收服务费', null, '0', '-1', null, '9', null, null, null, null, '', null, null, null, null, null, null, null, null, null, null);
INSERT INTO menu_item_class VALUES ('4', null, '不打折不收服务费', null, '0', '-1', null, '0', null, null, null, null, '', null, null, null, null, null, null, null, null, null, null);
INSERT INTO menu_item_class VALUES ('5', null, '打折不收服务费', null, '9', '-1', null, '0', null, null, null, null, '', null, null, null, null, null, null, null, null, null, null);
INSERT INTO menu_item_class VALUES ('6', null, '打折收服务费', null, '9', '-1', null, '9', null, null, null, null, '', null, null, null, null, null, null, null, null, null, null);
INSERT INTO menu_item_class VALUES ('11', null, '称重不打折不收服务费', null, '0', '-1', null, '0', null, null, null, null, '', null, null, null, null, null, null, null, null, null, null);
INSERT INTO menu_item_class VALUES ('12', null, '称重打折不收服务费', null, '9', '-1', null, '0', null, null, null, null, '', null, null, null, null, null, null, null, null, null, null);

-- ----------------------------
-- Table structure for `menu_level_class`
-- ----------------------------
DROP TABLE IF EXISTS `menu_level_class`;
CREATE TABLE `menu_level_class` (
  `mlc_id` int(11) NOT NULL,
  `mlc_number` int(11) DEFAULT NULL,
  `mlc_name` varchar(30) DEFAULT NULL,
  `main_level` int(11) DEFAULT NULL,
  `sub_level` int(11) DEFAULT NULL,
  `pop_main_level` int(11) DEFAULT NULL,
  `pop_sub_level` int(11) DEFAULT NULL,
  PRIMARY KEY (`mlc_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of menu_level_class
-- ----------------------------

-- ----------------------------
-- Table structure for `messages`
-- ----------------------------
DROP TABLE IF EXISTS `messages`;
CREATE TABLE `messages` (
  `message_id` int(11) NOT NULL AUTO_INCREMENT,
  `tel` varchar(50) DEFAULT NULL,
  `message_content` varchar(1000) DEFAULT NULL,
  `send_time` datetime DEFAULT NULL,
  `type` int(11) DEFAULT '0',
  `user_id` int(11) DEFAULT '-1',
  `sender` int(11) DEFAULT '-1',
  `extend_1` int(11) DEFAULT '0',
  `extend_2` varchar(300) DEFAULT NULL,
  `extend_3` varchar(300) DEFAULT NULL,
  `extend_4` varchar(300) DEFAULT NULL,
  `extend_5` varchar(300) DEFAULT NULL,
  PRIMARY KEY (`message_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of messages
-- ----------------------------

-- ----------------------------
-- Table structure for `messages_template_item`
-- ----------------------------
DROP TABLE IF EXISTS `messages_template_item`;
CREATE TABLE `messages_template_item` (
  `message_tempitem_id` int(11) NOT NULL DEFAULT '0',
  `message_tempitem_name` varchar(50) DEFAULT '',
  `message_tempitem_content` varchar(50) DEFAULT '',
  `column_value` varchar(100) DEFAULT '',
  `type` int(11) DEFAULT '0',
  PRIMARY KEY (`message_tempitem_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of messages_template_item
-- ----------------------------
INSERT INTO messages_template_item VALUES ('1', '预订名称', '#OrderName#', '', '0');
INSERT INTO messages_template_item VALUES ('2', '开席时间', '#ArriveTime#', '', '0');
INSERT INTO messages_template_item VALUES ('3', '客户名称', '#CustomerName#', '', '0');
INSERT INTO messages_template_item VALUES ('4', '客户电话', '#CustomerTel#', '', '0');
INSERT INTO messages_template_item VALUES ('5', '预订房台', '#TblName#', '', '0');
INSERT INTO messages_template_item VALUES ('6', '预订席数', '#TblNum#', '', '0');
INSERT INTO messages_template_item VALUES ('7', '备用席数', '#BackTblNum#', '', '0');
INSERT INTO messages_template_item VALUES ('8', '预付订金', '#Prepay#', '', '0');
INSERT INTO messages_template_item VALUES ('9', '每桌价格', '#PricePerTbl#', '', '0');
INSERT INTO messages_template_item VALUES ('10', '备注', '#Remark#', '', '0');

-- ----------------------------
-- Table structure for `miti`
-- ----------------------------
DROP TABLE IF EXISTS `miti`;
CREATE TABLE `miti` (
  `order_employee_id` int(11) DEFAULT NULL,
  `order_employee_name` varchar(50) DEFAULT NULL,
  `actual_price` float DEFAULT NULL,
  `quantity` float DEFAULT NULL,
  `commission_value` float DEFAULT NULL,
  `commission_type` int(11) DEFAULT NULL
) ENGINE=MEMORY DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of miti
-- ----------------------------

-- ----------------------------
-- Table structure for `msg_setting`
-- ----------------------------
DROP TABLE IF EXISTS `msg_setting`;
CREATE TABLE `msg_setting` (
  `setting_id` int(11) NOT NULL DEFAULT '0',
  `type` int(11) DEFAULT '0',
  `com_port` int(11) DEFAULT '1',
  `ip_address` varchar(50) DEFAULT NULL,
  `ip_port` int(11) DEFAULT NULL,
  `user_id` varchar(50) DEFAULT NULL,
  `user_pwd` varchar(50) DEFAULT NULL,
  `net_server` varchar(500) DEFAULT NULL,
  `net_user` varchar(50) DEFAULT NULL,
  `net_user_pwd` varchar(50) DEFAULT NULL,
  `cr_ip` varchar(50) DEFAULT '',
  `cr_url` varchar(100) DEFAULT '',
  `cr_port` int(11) DEFAULT '2001',
  `cr_user` varchar(50) DEFAULT '',
  `cr_user_pwd` varchar(50) DEFAULT '',
  PRIMARY KEY (`setting_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of msg_setting
-- ----------------------------
INSERT INTO msg_setting VALUES ('0', '0', '5', '192.168.1.113', '2001', 'super', '123', 'se1.china-sms.com:9900;se2.china-sms.com:9900;se3.china-sms.com:9900;se5.china-sms.com:9900', '', '', '127.0.0.1', 'www.gicater.com', '2001', 'super', '123');

-- ----------------------------
-- Table structure for `network_node`
-- ----------------------------
DROP TABLE IF EXISTS `network_node`;
CREATE TABLE `network_node` (
  `node_id` int(11) NOT NULL,
  `node_number` int(11) DEFAULT NULL,
  `node_name` varchar(30) DEFAULT NULL,
  `dns_domain_name` varchar(30) DEFAULT NULL,
  `ip_address` varchar(32) DEFAULT NULL,
  `subnet_mask` varchar(32) DEFAULT NULL,
  `is_diskless_pc` bit(1) DEFAULT NULL,
  `pc_type` int(11) DEFAULT NULL,
  `dns_server_ip` varchar(32) DEFAULT NULL,
  `boot_file` varchar(255) DEFAULT NULL,
  `gateway_ip` varchar(32) DEFAULT NULL,
  `mac_address` varchar(40) DEFAULT NULL,
  `resolution` int(11) DEFAULT NULL,
  PRIMARY KEY (`node_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of network_node
-- ----------------------------

-- ----------------------------
-- Table structure for `order_default_group`
-- ----------------------------
DROP TABLE IF EXISTS `order_default_group`;
CREATE TABLE `order_default_group` (
  `order_default_groupid` int(11) NOT NULL,
  `order_default_groupname` varchar(100) DEFAULT NULL,
  `serving_period_class` int(11) DEFAULT '-1',
  `serving_place_class` int(11) DEFAULT '-1',
  `extend_1` int(11) DEFAULT NULL,
  `extend_2` int(11) DEFAULT NULL,
  `extend_3` varchar(300) DEFAULT NULL,
  `extend_4` varchar(300) DEFAULT NULL,
  `extend_5` float DEFAULT NULL,
  PRIMARY KEY (`order_default_groupid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of order_default_group
-- ----------------------------
INSERT INTO order_default_group VALUES ('1', '默认开台消费组', '-1', '-1', null, null, null, null, null);

-- ----------------------------
-- Table structure for `order_detail`
-- ----------------------------
DROP TABLE IF EXISTS `order_detail`;
CREATE TABLE `order_detail` (
  `order_detail_id` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `order_head_id` int(11) DEFAULT NULL,
  `check_id` int(11) DEFAULT '1',
  `menu_item_id` int(11) DEFAULT NULL,
  `menu_item_name` varchar(60) DEFAULT NULL,
  `product_price` float DEFAULT NULL,
  `is_discount` bit(1) DEFAULT NULL,
  `original_price` float DEFAULT NULL,
  `discount_id` int(11) DEFAULT NULL,
  `actual_price` float DEFAULT NULL,
  `is_return_item` bit(1) DEFAULT b'0',
  `order_employee_id` int(11) DEFAULT NULL,
  `order_employee_name` varchar(40) DEFAULT NULL,
  `pos_device_id` int(11) DEFAULT NULL,
  `pos_name` varchar(30) DEFAULT NULL,
  `order_time` datetime DEFAULT NULL,
  `return_time` datetime DEFAULT NULL,
  `return_reason` varchar(200) DEFAULT NULL,
  `unit` varchar(30) DEFAULT NULL,
  `is_send` bit(1) DEFAULT NULL,
  `condiment_belong_item` int(11) DEFAULT NULL,
  `quantity` float DEFAULT '1',
  `eat_type` int(11) DEFAULT NULL,
  `auth_id` int(11) DEFAULT NULL,
  `auth_name` varchar(40) DEFAULT '',
  `weight_entry_required` bit(1) DEFAULT NULL,
  `description` char(100) DEFAULT NULL,
  `n_service_type` int(11) DEFAULT NULL,
  `not_print` int(11) DEFAULT NULL,
  `seat_num` int(11) DEFAULT NULL,
  `discount_price` float DEFAULT NULL,
  `sales_amount` float DEFAULT NULL,
  PRIMARY KEY (`order_detail_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of order_detail
-- ----------------------------

-- ----------------------------
-- Table structure for `order_detail_default`
-- ----------------------------
DROP TABLE IF EXISTS `order_detail_default`;
CREATE TABLE `order_detail_default` (
  `order_detail_default_id` int(11) NOT NULL AUTO_INCREMENT,
  `menu_item_id` int(11) NOT NULL,
  `quantity` float DEFAULT NULL,
  `unit_id` int(11) DEFAULT NULL,
  `discount_service_id` int(11) DEFAULT NULL,
  `price` float DEFAULT NULL,
  `mark` varchar(300) DEFAULT NULL,
  `is_cus_num` int(11) DEFAULT '0',
  `extend_1` int(11) DEFAULT '0',
  `extend_2` int(11) DEFAULT '0',
  `extend_3` varchar(300) DEFAULT NULL,
  `extend_4` varchar(300) DEFAULT NULL,
  `extend_5` float DEFAULT NULL,
  PRIMARY KEY (`order_detail_default_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of order_detail_default
-- ----------------------------

-- ----------------------------
-- Table structure for `order_head`
-- ----------------------------
DROP TABLE IF EXISTS `order_head`;
CREATE TABLE `order_head` (
  `order_head_id` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `check_number` int(11) DEFAULT NULL,
  `rvc_center_id` int(11) DEFAULT NULL,
  `rvc_center_name` varchar(30) DEFAULT NULL,
  `table_id` int(11) DEFAULT NULL,
  `table_name` varchar(30) DEFAULT NULL,
  `check_id` int(11) NOT NULL DEFAULT '0',
  `open_employee_id` int(11) DEFAULT NULL,
  `open_employee_name` varchar(30) DEFAULT NULL,
  `customer_num` int(11) DEFAULT NULL,
  `customer_id` int(11) DEFAULT '0',
  `customer_name` varchar(30) DEFAULT NULL,
  `pos_device_id` int(11) DEFAULT NULL,
  `pos_name` varchar(30) DEFAULT NULL,
  `order_start_time` datetime DEFAULT NULL,
  `order_end_time` datetime DEFAULT NULL,
  `should_amount` float DEFAULT '0',
  `return_amount` float DEFAULT '0',
  `discount_amount` float DEFAULT '0',
  `actual_amount` float DEFAULT '0',
  `print_count` int(11) DEFAULT '0',
  `status` int(11) DEFAULT '0',
  `eat_type` int(11) DEFAULT NULL,
  `check_name` varchar(30) DEFAULT NULL,
  `original_amount` float DEFAULT '0',
  `service_amount` float DEFAULT '0',
  `edit_time` datetime DEFAULT NULL,
  `party_id` int(11) DEFAULT NULL,
  `edit_employee_name` varchar(30) DEFAULT NULL,
  `remark` varchar(50) DEFAULT NULL,
  `is_make` int(11) DEFAULT NULL,
  PRIMARY KEY (`order_head_id`,`check_id`),
  KEY `table_id` (`table_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of order_head
-- ----------------------------

-- ----------------------------
-- Table structure for `order_types`
-- ----------------------------
DROP TABLE IF EXISTS `order_types`;
CREATE TABLE `order_types` (
  `order_type_id` int(11) NOT NULL,
  `order_type_number` int(11) DEFAULT NULL,
  `order_type_name` varchar(30) DEFAULT NULL,
  `is_enable` bit(1) DEFAULT NULL,
  `print_check_receipt` bit(1) DEFAULT NULL,
  `print_order_chit` bit(1) DEFAULT NULL,
  PRIMARY KEY (`order_type_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of order_types
-- ----------------------------
INSERT INTO order_types VALUES ('0', null, '堂吃', '', null, null);
INSERT INTO order_types VALUES ('1', null, '带走', null, null, null);

-- ----------------------------
-- Table structure for `parties`
-- ----------------------------
DROP TABLE IF EXISTS `parties`;
CREATE TABLE `parties` (
  `party_id` int(11) NOT NULL AUTO_INCREMENT,
  `party_name` varchar(200) DEFAULT NULL,
  `status` int(11) DEFAULT '0',
  `party_type` int(11) DEFAULT '0',
  `table_num` int(11) DEFAULT '0',
  `back_table_num` int(11) DEFAULT '0',
  `table_price` decimal(11,2) DEFAULT NULL,
  `remark` varchar(300) DEFAULT NULL,
  `contract_id` varchar(100) DEFAULT NULL,
  `pre_amount` decimal(11,2) DEFAULT NULL,
  `amount` decimal(11,2) DEFAULT NULL,
  `sale_employee` int(11) DEFAULT '-1',
  `customer_name` varchar(100) DEFAULT NULL,
  `customer_tel` varchar(100) DEFAULT NULL,
  `party_time` datetime DEFAULT NULL,
  `insert_time` datetime DEFAULT NULL,
  `update_time` datetime DEFAULT NULL,
  `insert_employee` int(11) DEFAULT '-1',
  `update_employee` int(11) DEFAULT '-1',
  `customer_id` int(11) DEFAULT NULL,
  `table_str` varchar(500) DEFAULT NULL,
  `cus_num` int(11) DEFAULT '1',
  PRIMARY KEY (`party_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of parties
-- ----------------------------

-- ----------------------------
-- Table structure for `parties_type`
-- ----------------------------
DROP TABLE IF EXISTS `parties_type`;
CREATE TABLE `parties_type` (
  `party_type_id` int(11) NOT NULL DEFAULT '0',
  `party_type_name` varchar(200) DEFAULT NULL,
  `msg_template` varchar(500) DEFAULT '',
  PRIMARY KEY (`party_type_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of parties_type
-- ----------------------------
INSERT INTO parties_type VALUES ('0', '桌台预订', '您好，#CustomerName#,您已成功预订，预订房台为#TblName#,预订席数为#TblNum#,备用席数为安师大aaa#BackTblNum#,每桌价格：#PricePerTbl#,预付订金：#Prepay#,备注：#Remark#,客户电话：#CustomerTel#,开席时间#ArriveTime#,预订名称：#OrderName#。');
INSERT INTO parties_type VALUES ('1', '婚宴', '您好，#CustomerName#，您已在深圳库瑞德餐厅成功预订婚宴，预订席数为#TblNum#，备用席数为#BackTblNum#，开席时间为#ArriveTime#，请您提前半小时抵达。');
INSERT INTO parties_type VALUES ('2', '生日宴会', '您好，#CustomerName#,您已成功预订，预订房台为#TblName#,预订席数为#TblNum#,备用席数为aaa#BackTblNum#,每桌价格：#PricePerTbl#,预付订金：#Prepay#,备注：#Remark#,客户电话：#CustomerTel#,开席时间#ArriveTime#,预订名称：#OrderName#。');
INSERT INTO parties_type VALUES ('3', '会议', '#CustomerName#您好，您已在深圳库瑞德餐厅成功预订婚宴，预订席数为#TblNum#，备用席数为#BackTblNum#，开席时间为#ArriveTime#，请您提前半小时抵达。');
INSERT INTO parties_type VALUES ('4', '谢师宴', '您好，#CustomerName#,您已成功预订，预订房台为#TblName#,预订席数为#TblNum#,备用席数为#BackTblNum#,每桌价格：#PricePerTbl#,预付订金：#Prepay#,备注：#Remark#,客户电话：#CustomerTel#,开席时间#ArriveTime#,预订名称：#OrderName#。');
INSERT INTO parties_type VALUES ('5', '年终宴会', '您好，#CustomerName#,您已成功预订，预订房台为#TblName#,预订席数为#TblNum#,备用席数为#BackTblNum#,每桌价格：#PricePerTbl#,预付订金：#Prepay#,备注：#Remark#,客户电话：#CustomerTel#,开席时间#ArriveTime#,预订名称：#OrderName#。');
INSERT INTO parties_type VALUES ('10', '其他', '您好，#CustomerName#,您已成功预订，预订房台为#TblName#,预订席数为#TblNum#,备用席数为#BackTblNum#,每桌价格：#PricePerTbl#,预付订金：#Prepay#,备注：#Remark#,客户电话#CustomerTel#,开席时间#ArriveTime#,预订名称：#OrderName#。');

-- ----------------------------
-- Table structure for `party_default_remark`
-- ----------------------------
DROP TABLE IF EXISTS `party_default_remark`;
CREATE TABLE `party_default_remark` (
  `remark_id` int(11) NOT NULL AUTO_INCREMENT,
  `remark_title` varchar(100) DEFAULT NULL,
  `remark_content` varchar(800) DEFAULT NULL,
  PRIMARY KEY (`remark_id`)
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of party_default_remark
-- ----------------------------
INSERT INTO party_default_remark VALUES ('1', '备注：', '    1、请在大堂及宾馆门口放置指示牌。\r\n    2、宴会厅内提供签到台、签到本、签到笔，详细场地布置见婚宴细节确认表\r\n');
INSERT INTO party_default_remark VALUES ('2', '出品部： ', '    1、菜单后附。\r\n    2、冷菜上菜时间: 待定 ,热菜上菜时间: 待定 。 \r\n');
INSERT INTO party_default_remark VALUES ('3', '财务部： ', '    1、客人已交纳10000定金，婚宴结束后结清所有款项。\r\n');

-- ----------------------------
-- Table structure for `party_item`
-- ----------------------------
DROP TABLE IF EXISTS `party_item`;
CREATE TABLE `party_item` (
  `party_item_id` int(11) NOT NULL AUTO_INCREMENT,
  `party_id` int(11) DEFAULT NULL,
  `menu_item_id` int(11) DEFAULT NULL,
  `item_course_name` varchar(200) DEFAULT NULL,
  `unit` varchar(100) DEFAULT NULL,
  `num` decimal(11,2) DEFAULT NULL,
  `price` decimal(11,2) DEFAULT NULL,
  `description` varchar(200) DEFAULT NULL,
  PRIMARY KEY (`party_item_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of party_item
-- ----------------------------

-- ----------------------------
-- Table structure for `party_remark`
-- ----------------------------
DROP TABLE IF EXISTS `party_remark`;
CREATE TABLE `party_remark` (
  `remark_id` int(11) NOT NULL AUTO_INCREMENT,
  `party_id` int(11) DEFAULT NULL,
  `remark_title` varchar(100) DEFAULT NULL,
  `remark_content` varchar(800) DEFAULT NULL,
  PRIMARY KEY (`remark_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of party_remark
-- ----------------------------

-- ----------------------------
-- Table structure for `party_table`
-- ----------------------------
DROP TABLE IF EXISTS `party_table`;
CREATE TABLE `party_table` (
  `party_id` int(11) NOT NULL DEFAULT '0',
  `table_id` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`party_id`,`table_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of party_table
-- ----------------------------

-- ----------------------------
-- Table structure for `payment`
-- ----------------------------
DROP TABLE IF EXISTS `payment`;
CREATE TABLE `payment` (
  `payment_id` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `order_head_id` int(11) DEFAULT NULL,
  `check_id` int(11) DEFAULT NULL,
  `tender_media_id` int(11) DEFAULT NULL,
  `total` float DEFAULT NULL,
  `employee_id` int(11) DEFAULT NULL,
  `remark` varchar(30) DEFAULT NULL,
  `payment_time` datetime DEFAULT NULL,
  `pos_device_id` int(11) DEFAULT NULL,
  `rvc_center_id` int(11) DEFAULT NULL,
  `order_detail_id` int(11) DEFAULT NULL,
  `consume_id` int(11) DEFAULT NULL,
  `ticket_id` int(11) DEFAULT NULL,
  PRIMARY KEY (`payment_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of payment
-- ----------------------------

-- ----------------------------
-- Table structure for `pc_devices`
-- ----------------------------
DROP TABLE IF EXISTS `pc_devices`;
CREATE TABLE `pc_devices` (
  `device_id` int(11) NOT NULL,
  `device_name` varchar(30) DEFAULT '',
  `ip_address` varchar(32) DEFAULT '',
  `subnet_mask` varchar(32) DEFAULT '',
  `dns_domain_name` varchar(30) DEFAULT '',
  `dns_server_ip` varchar(32) DEFAULT '',
  `print_class` int(11) DEFAULT NULL,
  PRIMARY KEY (`device_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of pc_devices
-- ----------------------------
INSERT INTO pc_devices VALUES ('1', 'pos_1', '', '', '', '', null);
INSERT INTO pc_devices VALUES ('2', 'pos_2', '', '', '', '', null);

-- ----------------------------
-- Table structure for `periods`
-- ----------------------------
DROP TABLE IF EXISTS `periods`;
CREATE TABLE `periods` (
  `period_id` int(11) NOT NULL,
  `period_name` varchar(30) DEFAULT NULL,
  `start_time` time DEFAULT NULL,
  `end_time` time DEFAULT NULL,
  `is_serving_period` bit(1) DEFAULT NULL,
  `active_day` int(11) DEFAULT NULL,
  PRIMARY KEY (`period_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of periods
-- ----------------------------
INSERT INTO periods VALUES ('1', 'Lunch', '02:00:00', '17:30:00', null, '0');
INSERT INTO periods VALUES ('3', 'Supper', '17:30:00', '02:00:00', null, '0');

-- ----------------------------
-- Table structure for `period_class`
-- ----------------------------
DROP TABLE IF EXISTS `period_class`;
CREATE TABLE `period_class` (
  `period_class_id` int(11) NOT NULL DEFAULT '0',
  `period_class_name` varchar(40) DEFAULT NULL,
  PRIMARY KEY (`period_class_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of period_class
-- ----------------------------
INSERT INTO period_class VALUES ('1', '默认营业时间组');

-- ----------------------------
-- Table structure for `practice`
-- ----------------------------
DROP TABLE IF EXISTS `practice`;
CREATE TABLE `practice` (
  `practice_id` int(11) NOT NULL AUTO_INCREMENT,
  `practice_name` varchar(300) DEFAULT NULL,
  `practice_group` int(11) DEFAULT NULL,
  PRIMARY KEY (`practice_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of practice
-- ----------------------------

-- ----------------------------
-- Table structure for `practice_group`
-- ----------------------------
DROP TABLE IF EXISTS `practice_group`;
CREATE TABLE `practice_group` (
  `practice_group_id` int(11) NOT NULL DEFAULT '0',
  `practice_group_name` varchar(100) DEFAULT NULL,
  PRIMARY KEY (`practice_group_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of practice_group
-- ----------------------------

-- ----------------------------
-- Table structure for `presets`
-- ----------------------------
DROP TABLE IF EXISTS `presets`;
CREATE TABLE `presets` (
  `presets_id` int(11) NOT NULL,
  `presets_name` varchar(40) DEFAULT NULL,
  `tender_media` int(11) DEFAULT '0',
  `amount` float DEFAULT NULL,
  `nlu` int(11) DEFAULT NULL,
  PRIMARY KEY (`presets_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of presets
-- ----------------------------

-- ----------------------------
-- Table structure for `pre_order`
-- ----------------------------
DROP TABLE IF EXISTS `pre_order`;
CREATE TABLE `pre_order` (
  `pre_order_id` int(11) NOT NULL AUTO_INCREMENT,
  `pre_order_name` varchar(40) DEFAULT '',
  `customer_id` int(11) DEFAULT '0',
  `customer_name` varchar(40) DEFAULT '',
  `telephone_1` varchar(40) DEFAULT '',
  `telephone_2` varchar(40) DEFAULT '',
  `company` varchar(100) DEFAULT '',
  `pre_amount` float DEFAULT '0',
  `order_type` int(11) DEFAULT '1',
  `type` int(11) DEFAULT NULL,
  `rvc_center_id` int(11) DEFAULT '0',
  `rvc_center_name` varchar(40) DEFAULT '',
  `table_id` int(11) NOT NULL DEFAULT '0',
  `table_name` varchar(40) DEFAULT '',
  `customer_num` int(11) DEFAULT '0',
  `description` varchar(200) DEFAULT '',
  `pre_order_status` int(11) DEFAULT '0',
  `preorder_employee_id` int(11) DEFAULT '0',
  `preorder_employee_name` varchar(40) DEFAULT '',
  `preorder_time` datetime DEFAULT NULL,
  `disorder_employee_id` int(11) DEFAULT '0',
  `disorder_employee_name` varchar(40) DEFAULT '',
  `auth_employee_id` int(11) DEFAULT '0',
  `auth_employee_name` varchar(40) DEFAULT '',
  `sail_employee_id` int(11) DEFAULT '0',
  `sail_employee_name` varchar(40) DEFAULT NULL,
  `disorder_time` datetime DEFAULT NULL,
  `disorder_reason` varchar(255) DEFAULT '',
  `arrived_time` datetime DEFAULT NULL,
  `actual_arrived_time` datetime DEFAULT NULL,
  `amount` float DEFAULT '0',
  PRIMARY KEY (`pre_order_id`,`table_id`),
  KEY `preorder_empid` (`sail_employee_id`) USING BTREE,
  KEY `preorder_status` (`pre_order_status`) USING BTREE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of pre_order
-- ----------------------------

-- ----------------------------
-- Table structure for `pre_order_detail`
-- ----------------------------
DROP TABLE IF EXISTS `pre_order_detail`;
CREATE TABLE `pre_order_detail` (
  `preorder_detail_id` int(11) NOT NULL AUTO_INCREMENT,
  `pre_order_id` int(11) DEFAULT NULL,
  `menu_item_id` int(11) DEFAULT NULL,
  `menu_item_name` varchar(40) DEFAULT '',
  `price` float DEFAULT NULL,
  `quantity` float DEFAULT NULL,
  `unit` varchar(30) DEFAULT NULL,
  `should_amount` float DEFAULT NULL,
  `condiment_belong_item` int(11) DEFAULT NULL,
  `description` varchar(200) DEFAULT NULL,
  PRIMARY KEY (`preorder_detail_id`),
  KEY `predetail` (`pre_order_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of pre_order_detail
-- ----------------------------

-- ----------------------------
-- Table structure for `print_class`
-- ----------------------------
DROP TABLE IF EXISTS `print_class`;
CREATE TABLE `print_class` (
  `print_class_id` int(11) NOT NULL,
  `print_class_number` int(11) DEFAULT NULL,
  `print_class_name` varchar(30) DEFAULT NULL,
  `customer_receipt` bit(1) DEFAULT b'0',
  `local_order_receipt` bit(1) DEFAULT b'0',
  `check` bit(1) DEFAULT b'0',
  `journal` bit(1) DEFAULT b'0',
  `fiscal_cash_register` bit(1) DEFAULT b'0',
  `print_in_red` bit(1) DEFAULT b'0',
  `remote_device` int(11) DEFAULT '0',
  PRIMARY KEY (`print_class_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of print_class
-- ----------------------------
INSERT INTO print_class VALUES ('1', null, '厨房', '', '', '', '', '', '', '0');

-- ----------------------------
-- Table structure for `print_class_relation`
-- ----------------------------
DROP TABLE IF EXISTS `print_class_relation`;
CREATE TABLE `print_class_relation` (
  `print_class_id` int(11) NOT NULL DEFAULT '0',
  `print_device_id` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`print_class_id`,`print_device_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of print_class_relation
-- ----------------------------
INSERT INTO print_class_relation VALUES ('1', '2');

-- ----------------------------
-- Table structure for `print_devices`
-- ----------------------------
DROP TABLE IF EXISTS `print_devices`;
CREATE TABLE `print_devices` (
  `print_device_id` int(11) NOT NULL,
  `print_device_name` varchar(30) DEFAULT NULL,
  `header` int(11) DEFAULT NULL,
  `trailer` int(11) DEFAULT NULL,
  `device_id` int(11) DEFAULT NULL,
  `backup_device_id` int(11) DEFAULT NULL,
  `redirection_device_id` int(11) DEFAULT NULL,
  `check_info_print` int(11) DEFAULT NULL,
  `print_table_number` bit(1) DEFAULT NULL,
  `com_port` int(11) DEFAULT '0',
  `baud_rate` int(11) DEFAULT NULL,
  `parity_type` int(11) DEFAULT NULL,
  `num_data_bit` int(11) DEFAULT NULL,
  `num_stop_bits` int(11) DEFAULT NULL,
  `is_print_note` int(11) DEFAULT '1',
  `printer_name` varchar(300) DEFAULT NULL,
  `flow_control` int(11) DEFAULT '1',
  `paper_width` int(11) DEFAULT NULL,
  PRIMARY KEY (`print_device_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of print_devices
-- ----------------------------
INSERT INTO print_devices VALUES ('1', '收银', '1', '1', null, null, '0', '4', '', '0', '9600', '2', '8', '2', '0', 'myprinter', '1', '80');
INSERT INTO print_devices VALUES ('2', 'キッチン', '-1', '-1', null, null, '0', '4', '', '0', '9600', '2', '8', '2', '1', 'myprinter', '1', '80');

-- ----------------------------
-- Table structure for `reasons`
-- ----------------------------
DROP TABLE IF EXISTS `reasons`;
CREATE TABLE `reasons` (
  `reason_id` int(11) NOT NULL,
  `reason_number` int(11) DEFAULT NULL,
  `reason_name` varchar(30) DEFAULT NULL,
  `description` varchar(200) DEFAULT NULL,
  `is_voids` bit(1) DEFAULT NULL,
  `is_returns` bit(1) DEFAULT b'0',
  `is_timecard` bit(1) DEFAULT b'0',
  `is_requests` bit(1) DEFAULT NULL,
  `is_terminations` bit(1) DEFAULT NULL,
  `is_absence` bit(1) DEFAULT NULL,
  `is_playrate` bit(1) DEFAULT NULL,
  `is_other` bit(1) DEFAULT b'0',
  PRIMARY KEY (`reason_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of reasons
-- ----------------------------
INSERT INTO reasons VALUES ('1', null, '错误输入', '', '', '', '', null, null, null, null, '');
INSERT INTO reasons VALUES ('2', null, '重复输入', '', '', '', '', null, null, null, null, '');
INSERT INTO reasons VALUES ('3', null, '菜没上', '', '', '', '', null, null, null, null, '');
INSERT INTO reasons VALUES ('4', null, '上菜慢', '', '', '', '', null, null, null, null, '');
INSERT INTO reasons VALUES ('5', null, '原料不足', '', '', '', '', null, null, null, null, '');
INSERT INTO reasons VALUES ('6', null, '客人忌口', '', null, '', '', null, null, null, null, '');
INSERT INTO reasons VALUES ('7', null, '点多了', '', null, '', '', null, null, null, null, '');

-- ----------------------------
-- Table structure for `report`
-- ----------------------------
DROP TABLE IF EXISTS `report`;
CREATE TABLE `report` (
  `report_id` int(11) NOT NULL AUTO_INCREMENT,
  `report_name` varchar(40) DEFAULT NULL,
  `report_class_id` int(11) DEFAULT NULL,
  `is_date_range` bit(1) DEFAULT b'0',
  `is_rvc_range` bit(1) DEFAULT b'0',
  `is_number_range` bit(1) DEFAULT b'0',
  `number_range_type` int(11) DEFAULT '-1',
  `template_filename` varchar(256) DEFAULT NULL,
  PRIMARY KEY (`report_id`)
) ENGINE=InnoDB AUTO_INCREMENT=141 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of report
-- ----------------------------
INSERT INTO report VALUES ('11', '菜品大类销售统计', '4', '', '', '', '-1', 'report\\major_gourp.rpt');
INSERT INTO report VALUES ('12', '菜品小类销售统计', '4', '', '', '', '-1', 'report\\family_group.rpt');
INSERT INTO report VALUES ('13', '时间段销售明细', '3', '', '', '', '-1', 'report\\systime_period.rpt');
INSERT INTO report VALUES ('15', '员工菜品销售明细', '6', '', '', '', '0', 'report\\employee_item_sales.rpt');
INSERT INTO report VALUES ('16', '各收银点收银统计', '4', '', '', '', '3', 'report\\cash_box_list.rpt');
INSERT INTO report VALUES ('17', '菜品销售统计', '5', '', '', '', '2', 'report\\item_sales.rpt');
INSERT INTO report VALUES ('18', '营业情况统计', '1', '', '', '', '-1', 'report\\sails.rpt');
INSERT INTO report VALUES ('19', '当日退菜明细', '5', '', '', '', '0', 'report\\return_item_list.rpt');
INSERT INTO report VALUES ('20', '未结账单明细', '1', '', '', '', '0', 'report\\unpay_check.rpt');
INSERT INTO report VALUES ('21', '员工营业销售明细', '6', '', '', '', '0', 'report\\employee_sale.rpt');
INSERT INTO report VALUES ('23', '账单流水报表', '1', '', '', '', '-1', 'report\\check_detail_common.rpt');
INSERT INTO report VALUES ('24', '当日送菜明细', '5', '', '', '', '-1', 'report\\send_items.rpt');
INSERT INTO report VALUES ('25', '送菜统计报表', '5', '', '', '', '-1', 'report\\send_items_sum.rpt');
INSERT INTO report VALUES ('26', '挂账统计报表', '6', '', '', '', '-1', 'report\\unpay_bills.rpt');
INSERT INTO report VALUES ('27', '会员卡消费统计报表', '6', '', '', '', '-1', 'report\\vipcard.rpt');
INSERT INTO report VALUES ('28', '菜品资料(横排)', '7', '', '', '', '-1', 'report\\items.rpt');
INSERT INTO report VALUES ('29', '菜品资料', '7', '', '', '', '-1', 'report\\items_1.rpt');
INSERT INTO report VALUES ('31', '菜品畅销销售统计', '4', '', '', '', '-1', 'report\\item_sales_desc.rpt');
INSERT INTO report VALUES ('41', '自定义菜销售明细', '5', '', '', '', '-1', 'report\\self_items.rpt');
INSERT INTO report VALUES ('42', '自定义菜销售统计', '5', '', '', '', '-1', 'report\\self_items_sum.rpt');
INSERT INTO report VALUES ('43', '菜品改价记录', '5', '', '', '', '-1', 'report\\change_price.rpt');
INSERT INTO report VALUES ('46', '收银员提成统计报表', '6', '', '', '', '-1', 'report\\cashier_sum.rpt');
INSERT INTO report VALUES ('47', '收银员收银明细报表', '6', '', '', '', '0', 'report\\cashier_detail.rpt');
INSERT INTO report VALUES ('48', '提成菜品', '7', '', '', '', '-1', 'report\\commission_item.rpt');
INSERT INTO report VALUES ('49', '点菜员提成统计报表', '6', '', '', '', '0', 'report\\employee_sommission.rpt');
INSERT INTO report VALUES ('50', '点菜员提成明细报表', '6', '', '', '', '0', 'report\\employee_sommission_detail.rpt');
INSERT INTO report VALUES ('51', '桌台资料', '2', '', '', '', '-1', 'report\\tables_detail.rpt');
INSERT INTO report VALUES ('52', '桌台消费排名', '2', '', '', '', '-1', 'report\\tables_sail.rpt');
INSERT INTO report VALUES ('53', '菜品类别', '7', '', '', '', '-1', 'report\\item_group.rpt');
INSERT INTO report VALUES ('54', '调味品', '7', '', '', '', '-1', 'report\\condiment_detail.rpt');
INSERT INTO report VALUES ('55', '时价菜', '7', '', '', '', '-1', 'report\\priceitem_detail.rpt');
INSERT INTO report VALUES ('56', '沽清菜品', '7', '', '', '', '-1', 'report\\soldoutitem_detail.rpt');
INSERT INTO report VALUES ('57', '套餐', '7', '', '', '', '-1', 'report\\course_detail.rpt');
INSERT INTO report VALUES ('58', '员工资料', '6', '', '', '', '-1', 'report\\employees_detail.rpt');
INSERT INTO report VALUES ('59', '折扣账单', '1', '', '', '', '-1', 'report\\discount_detail.rpt');
INSERT INTO report VALUES ('60', '服务费账单', '1', '', '', '', '-1', 'report\\service_detail.rpt');
INSERT INTO report VALUES ('70', '员工发票发放明细', '6', '', '', '', '-1', 'report\\invoice_detail.rpt');
INSERT INTO report VALUES ('71', '员工发票发放统计', '6', '', '', '', '-1', 'report\\invoice_total.rpt');
INSERT INTO report VALUES ('80', '代金券组使用统计', '4', '', '', '', '-1', 'report\\tickets_class_total.rpt');
INSERT INTO report VALUES ('81', '代金券使用统计', '4', '', '', '', '-1', 'report\\tickets_total.rpt');
INSERT INTO report VALUES ('130', '套餐销售明细', '5', '', '', '', '-1', 'report\\course_sale_detail.rpt');
INSERT INTO report VALUES ('131', '二级菜单菜品销售统计', '5', '', '', '', '4', 'report\\secondItem_sales.rpt');
INSERT INTO report VALUES ('132', '一级菜单菜品销售统计', '5', '', '', '', '5', 'report\\mainItem_sales.rpt');
INSERT INTO report VALUES ('133', '菜品大类数量畅销排行', '5', '', '', '', '-1', 'report\\major_items_num_desc.rpt');
INSERT INTO report VALUES ('134', '菜品大类金额畅销排行', '5', '', '', '', '-1', 'report\\major_items_amount_desc.rpt');
INSERT INTO report VALUES ('135', '菜品小类数量畅销排行', '5', '', '', '', '-1', 'report\\family_items_num_desc.rpt');
INSERT INTO report VALUES ('136', '菜品小类金额畅销排行', '5', '', '', '', '-1', 'report\\family_items_amount_desc.rpt');
INSERT INTO report VALUES ('137', '菜品大类数量滞销排行', '5', '', '', '', '-1', 'report\\major_items_num_asc.rpt');
INSERT INTO report VALUES ('138', '菜品大类金额滞销排行', '5', '', '', '', '-1', 'report\\major_items_amount_asc.rpt');
INSERT INTO report VALUES ('139', '菜品小类数量滞销排行', '5', '', '', '', '-1', 'report\\family_items_num_asc.rpt');
INSERT INTO report VALUES ('140', '菜品小类金额滞销排行', '5', '', '', '', '-1', 'report\\family_items_amount_asc.rpt');

-- ----------------------------
-- Table structure for `report_class`
-- ----------------------------
DROP TABLE IF EXISTS `report_class`;
CREATE TABLE `report_class` (
  `report_class_id` int(11) NOT NULL DEFAULT '0',
  `report_class_name` varchar(40) DEFAULT '',
  PRIMARY KEY (`report_class_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of report_class
-- ----------------------------
INSERT INTO report_class VALUES ('1', '账单统计');
INSERT INTO report_class VALUES ('2', '桌台统计');
INSERT INTO report_class VALUES ('3', '时间段统计');
INSERT INTO report_class VALUES ('4', '收入统计');
INSERT INTO report_class VALUES ('5', '菜品销售统计');
INSERT INTO report_class VALUES ('6', '员工统计');
INSERT INTO report_class VALUES ('7', '菜品资料');

-- ----------------------------
-- Table structure for `restaurant`
-- ----------------------------
DROP TABLE IF EXISTS `restaurant`;
CREATE TABLE `restaurant` (
  `restaurant_id` int(11) NOT NULL,
  `restaurant_name` varchar(30) DEFAULT NULL,
  `location_name_1` varchar(30) DEFAULT NULL,
  `location_name_2` varchar(300) DEFAULT NULL,
  `server_network_node` int(11) DEFAULT NULL,
  `backup_server_node` int(11) DEFAULT NULL,
  `default_printer_name` varchar(30) DEFAULT NULL,
  `start_time` time DEFAULT NULL,
  `start_day` int(11) DEFAULT NULL,
  `autoinc_business_date` bit(1) DEFAULT NULL,
  `fiscal_year_date` datetime DEFAULT NULL,
  `type` int(11) DEFAULT NULL,
  `fiscal_period_name` varchar(300) DEFAULT NULL,
  `floating_fical_date` bit(1) DEFAULT NULL,
  `fixed_period` bit(1) DEFAULT NULL,
  `number_of_days` int(11) DEFAULT NULL,
  `currency_name` varchar(30) DEFAULT NULL,
  `decimal_places` int(11) DEFAULT NULL,
  `decimal_char` varchar(1) DEFAULT NULL,
  `is_input_chk` int(11) DEFAULT '0',
  `auto_send_type` int(11) DEFAULT '0',
  `db_back_folder` varchar(500) DEFAULT NULL,
  PRIMARY KEY (`restaurant_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of restaurant
-- ----------------------------
INSERT INTO restaurant VALUES ('1', '聚客咖啡厅', '', '', '-1', '-1', '', '04:00:00', null, null, null, null, '', null, null, '4321', null, null, null, '0', '2', 'D:\\');

-- ----------------------------
-- Table structure for `rvc_center`
-- ----------------------------
DROP TABLE IF EXISTS `rvc_center`;
CREATE TABLE `rvc_center` (
  `rvc_center_id` int(11) NOT NULL,
  `rvc_center_name` varchar(30) DEFAULT NULL,
  `cc_voucher_header` int(11) DEFAULT NULL,
  `consumption_limit` int(11) DEFAULT '-1',
  `row_menu_printer` int(11) DEFAULT '-1',
  PRIMARY KEY (`rvc_center_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of rvc_center
-- ----------------------------
INSERT INTO rvc_center VALUES ('1', '1 階', null, '-1', '-1');
INSERT INTO rvc_center VALUES ('2', '2 階', null, '-1', '-1');

-- ----------------------------
-- Table structure for `rvc_class`
-- ----------------------------
DROP TABLE IF EXISTS `rvc_class`;
CREATE TABLE `rvc_class` (
  `rvc_class_id` int(11) NOT NULL DEFAULT '0',
  `rvc_class_name` varchar(40) DEFAULT NULL,
  PRIMARY KEY (`rvc_class_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of rvc_class
-- ----------------------------
INSERT INTO rvc_class VALUES ('1', '一楼大厅');
INSERT INTO rvc_class VALUES ('2', '默认营业地点组');

-- ----------------------------
-- Table structure for `service_tip`
-- ----------------------------
DROP TABLE IF EXISTS `service_tip`;
CREATE TABLE `service_tip` (
  `service_tip_id` int(11) NOT NULL,
  `service_tip_name` varchar(40) DEFAULT NULL,
  `type` int(11) NOT NULL DEFAULT '0',
  `print_class` int(11) DEFAULT NULL,
  `menu_level_class` int(11) DEFAULT NULL,
  `privilege` int(11) DEFAULT NULL,
  `nlu` int(11) DEFAULT NULL,
  `amount` int(11) DEFAULT NULL,
  `date_from` datetime DEFAULT NULL,
  `date_to` datetime DEFAULT NULL,
  `category` int(11) DEFAULT NULL,
  `percent` int(11) DEFAULT NULL,
  `preset` bit(1) DEFAULT NULL,
  `reference_required` bit(1) DEFAULT NULL,
  `auto_sys_chg` bit(1) DEFAULT NULL,
  `seat_filter_exit` bit(1) DEFAULT NULL,
  `assume_entire_amount` bit(1) DEFAULT NULL,
  `not_with_seat` bit(1) DEFAULT NULL,
  `employee_meal` bit(1) DEFAULT b'0',
  `discount_over_threshold` bit(1) DEFAULT NULL,
  `limit_discount` bit(1) DEFAULT NULL,
  `discount_last_item` bit(1) DEFAULT NULL,
  `single_seat` bit(1) DEFAULT NULL,
  `prorated_subtotal` bit(1) DEFAULT NULL,
  `select_discount` bit(1) DEFAULT NULL,
  `period_class_id` int(11) DEFAULT NULL,
  `rvc_class_id` int(11) DEFAULT NULL,
  `display_name` char(60) DEFAULT NULL,
  PRIMARY KEY (`service_tip_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of service_tip
-- ----------------------------
INSERT INTO service_tip VALUES ('1', '10%', '0', null, '0', '0', null, '30', null, null, '1', '10', '', null, null, null, null, null, '', null, null, null, null, null, '', null, null, '');
INSERT INTO service_tip VALUES ('2', '15%', '0', null, '0', '0', null, '30', null, null, '1', '15', '', null, null, null, null, null, '', null, null, null, null, null, '', null, null, '');
INSERT INTO service_tip VALUES ('3', '20%', '0', null, '0', '0', null, '30', null, null, '1', '20', '', null, null, null, null, null, '', null, null, null, null, null, '', null, null, '');
INSERT INTO service_tip VALUES ('4', '800円', '0', null, '0', '0', null, '800', null, null, '1', '0', '', null, null, null, null, null, '', null, null, null, null, null, '', null, null, '');
INSERT INTO service_tip VALUES ('5', '1000円', '0', null, '0', '0', null, '1000', null, null, '1', '0', '', null, null, null, null, null, '', null, null, null, null, null, '', null, null, '');
INSERT INTO service_tip VALUES ('6', 'Open Service', '1', null, '0', '0', null, '0', null, null, '1', '0', '', null, null, null, null, null, '', null, null, null, null, null, '', null, null, '服务费');

-- ----------------------------
-- Table structure for `serving_period_class`
-- ----------------------------
DROP TABLE IF EXISTS `serving_period_class`;
CREATE TABLE `serving_period_class` (
  `period_class_id` int(11) NOT NULL DEFAULT '0',
  `period` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`period_class_id`,`period`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of serving_period_class
-- ----------------------------
INSERT INTO serving_period_class VALUES ('1', '1');
INSERT INTO serving_period_class VALUES ('1', '3');

-- ----------------------------
-- Table structure for `serving_rvc_class`
-- ----------------------------
DROP TABLE IF EXISTS `serving_rvc_class`;
CREATE TABLE `serving_rvc_class` (
  `rvc_class_id` int(11) NOT NULL DEFAULT '0',
  `rvc_center_id` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`rvc_class_id`,`rvc_center_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of serving_rvc_class
-- ----------------------------
INSERT INTO serving_rvc_class VALUES ('1', '1');
INSERT INTO serving_rvc_class VALUES ('2', '1');
INSERT INTO serving_rvc_class VALUES ('2', '2');

-- ----------------------------
-- Table structure for `storage`
-- ----------------------------
DROP TABLE IF EXISTS `storage`;
CREATE TABLE `storage` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `vip` varchar(50) DEFAULT NULL,
  `info` varchar(500) DEFAULT NULL,
  `employee` int(11) DEFAULT NULL,
  `start_date` date DEFAULT NULL,
  `end_date` date DEFAULT NULL,
  `del_date` date DEFAULT NULL,
  `del_employee` int(11) DEFAULT NULL,
  `is_use` bit(1) DEFAULT b'1',
  `last_msg_date` date DEFAULT NULL COMMENT '上次发送短信通知时间',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of storage
-- ----------------------------

-- ----------------------------
-- Table structure for `suppliers`
-- ----------------------------
DROP TABLE IF EXISTS `suppliers`;
CREATE TABLE `suppliers` (
  `suppliers_id` int(11) NOT NULL AUTO_INCREMENT,
  `suppliers_name` varchar(300) DEFAULT '',
  `suppliers_addr` varchar(300) DEFAULT '',
  `suppliers_tel` varchar(60) DEFAULT '',
  `suppliers_contact` varchar(60) DEFAULT '',
  `extend_1` varchar(40) DEFAULT '',
  `extend_2` varchar(40) DEFAULT '',
  `extend_3` varchar(40) DEFAULT '',
  `extend_4` int(11) DEFAULT '0',
  `extend_5` int(11) DEFAULT '0',
  PRIMARY KEY (`suppliers_id`)
) ENGINE=InnoDB AUTO_INCREMENT=102 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of suppliers
-- ----------------------------
INSERT INTO suppliers VALUES ('101', 'coolroid', 'xxx', '123456789', 'xiao pang', '', '', '', '0', '0');

-- ----------------------------
-- Table structure for `tables`
-- ----------------------------
DROP TABLE IF EXISTS `tables`;
CREATE TABLE `tables` (
  `table_id` int(11) NOT NULL DEFAULT '0',
  `table_name` varchar(30) DEFAULT NULL,
  `seat_num` int(11) DEFAULT NULL,
  `table_status` int(11) DEFAULT NULL,
  `description` varchar(200) DEFAULT NULL,
  `rvc_center_id` int(11) DEFAULT NULL,
  `floor` int(11) DEFAULT '1',
  `icon` varchar(256) DEFAULT NULL,
  `consumption_limit` int(11) DEFAULT NULL,
  `row_menu_printer` int(11) DEFAULT '-1',
  `party_table` varchar(30) DEFAULT NULL,
  PRIMARY KEY (`table_id`),
  KEY `table_id` (`table_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of tables
-- ----------------------------
INSERT INTO tables VALUES ('-1', '快餐', null, '0', null, '1', '1', null, null, '-1', null);
INSERT INTO tables VALUES ('1', 'A1', '4', '0', '', '1', '0', '', '-1', '-1', null);
INSERT INTO tables VALUES ('2', 'A2', '4', '0', '', '1', '1', '', '-1', '-1', null);
INSERT INTO tables VALUES ('3', 'A3', '4', '0', '', '1', '1', '', '-1', '-1', null);
INSERT INTO tables VALUES ('5', 'A5', '6', '0', '', '1', '1', '', '-1', '-1', null);
INSERT INTO tables VALUES ('6', 'A6', '6', '0', '', '1', '1', '', '-1', '-1', null);
INSERT INTO tables VALUES ('7', 'A7', '8', '0', '', '1', '1', '', '-1', '-1', null);
INSERT INTO tables VALUES ('8', 'A8', '4', '0', '', '1', '1', '', '-1', '-1', null);
INSERT INTO tables VALUES ('9', 'A9', '8', '0', '', '1', '1', '', '-1', '-1', null);
INSERT INTO tables VALUES ('10', 'A10', '4', '0', '', '1', '1', '', '-1', '-1', null);
INSERT INTO tables VALUES ('11', 'A11', '8', '0', '', '1', '1', '', '-1', '-1', null);
INSERT INTO tables VALUES ('21', 'B1', '8', '0', '', '2', '1', null, '-1', '-1', null);
INSERT INTO tables VALUES ('22', 'B2', '8', '0', '', '2', '1', null, '-1', '-1', null);
INSERT INTO tables VALUES ('23', 'B3', '8', '0', '', '2', '1', null, '-1', '-1', null);
INSERT INTO tables VALUES ('25', 'B5', '8', '0', '', '2', '1', null, '-1', '-1', null);
INSERT INTO tables VALUES ('26', 'B6', '8', '0', '', '2', '1', null, '-1', '-1', null);
INSERT INTO tables VALUES ('27', 'B7', '8', '0', '', '2', '1', null, '-1', '-1', null);
INSERT INTO tables VALUES ('28', 'B8', '8', '0', '', '2', '1', null, '-1', '-1', null);
INSERT INTO tables VALUES ('29', 'B9', '8', '0', '', '2', '1', null, '-1', '-1', null);
INSERT INTO tables VALUES ('30', 'B10', '8', '0', '', '2', '1', null, '-1', '-1', null);
INSERT INTO tables VALUES ('31', 'B11', '8', '0', '', '2', '1', null, '-1', '-1', null);
INSERT INTO tables VALUES ('32', 'B12', '8', '0', '', '2', '1', null, '-1', '-1', null);
INSERT INTO tables VALUES ('33', 'B13', '8', '0', '', '2', '1', null, '-1', '-1', null);

-- ----------------------------
-- Table structure for `table_status`
-- ----------------------------
DROP TABLE IF EXISTS `table_status`;
CREATE TABLE `table_status` (
  `table_stauts_id` int(11) NOT NULL DEFAULT '0',
  `table_status_name` varchar(30) DEFAULT NULL,
  `icon` varchar(256) DEFAULT NULL,
  `description` varchar(200) DEFAULT NULL,
  PRIMARY KEY (`table_stauts_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of table_status
-- ----------------------------
INSERT INTO table_status VALUES ('1', '空台', null, null);
INSERT INTO table_status VALUES ('2', '开台', null, null);
INSERT INTO table_status VALUES ('3', '送厨', null, null);
INSERT INTO table_status VALUES ('4', '印单', null, '已印单，待付款');
INSERT INTO table_status VALUES ('5', '超时', null, '超过一定时间未付款');
INSERT INTO table_status VALUES ('6', '停用', null, '');

-- ----------------------------
-- Table structure for `tax`
-- ----------------------------
DROP TABLE IF EXISTS `tax`;
CREATE TABLE `tax` (
  `tax_id` int(11) NOT NULL DEFAULT '0',
  `tax_name` varchar(300) DEFAULT NULL,
  `tax_group` int(11) DEFAULT NULL,
  `display_name` varchar(300) DEFAULT NULL,
  `tax_type` int(11) DEFAULT NULL,
  `amount` decimal(11,2) DEFAULT NULL,
  `start_amount` decimal(11,2) DEFAULT NULL,
  `end_amount` decimal(11,2) DEFAULT NULL,
  PRIMARY KEY (`tax_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of tax
-- ----------------------------

-- ----------------------------
-- Table structure for `tax_group`
-- ----------------------------
DROP TABLE IF EXISTS `tax_group`;
CREATE TABLE `tax_group` (
  `tax_group_id` int(11) NOT NULL DEFAULT '0',
  `tax_group_name` varchar(300) DEFAULT NULL,
  PRIMARY KEY (`tax_group_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of tax_group
-- ----------------------------

-- ----------------------------
-- Table structure for `tax_type`
-- ----------------------------
DROP TABLE IF EXISTS `tax_type`;
CREATE TABLE `tax_type` (
  `tax_type_id` int(11) NOT NULL,
  `tax_type_name` varchar(300) DEFAULT NULL,
  PRIMARY KEY (`tax_type_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of tax_type
-- ----------------------------
INSERT INTO tax_type VALUES ('0', '比例');
INSERT INTO tax_type VALUES ('1', '金额');
INSERT INTO tax_type VALUES ('2', '已包含');

-- ----------------------------
-- Table structure for `tender_media`
-- ----------------------------
DROP TABLE IF EXISTS `tender_media`;
CREATE TABLE `tender_media` (
  `tender_media_id` int(11) NOT NULL DEFAULT '0',
  `tender_media_name` varchar(30) DEFAULT NULL,
  `type` int(11) DEFAULT NULL,
  `date_from` datetime DEFAULT NULL,
  `date_to` datetime DEFAULT NULL,
  `slu` int(11) DEFAULT NULL,
  `print_class` int(11) DEFAULT NULL,
  `menu_level_class` int(11) DEFAULT NULL,
  `privilege` int(11) DEFAULT NULL,
  `category` int(11) DEFAULT NULL,
  `nlu` varchar(20) DEFAULT NULL,
  `open_drawer` bit(1) DEFAULT NULL,
  `currency_conversion` bit(1) DEFAULT NULL,
  `reference_required` bit(1) DEFAULT NULL,
  `exempt_service` bit(1) DEFAULT NULL,
  `employee_meal` bit(1) DEFAULT NULL,
  `paid_full` bit(1) DEFAULT NULL,
  `require_amount_entry` bit(1) DEFAULT NULL,
  `declare_tips_paid` bit(1) DEFAULT NULL,
  `item_is_shareable` bit(1) DEFAULT NULL,
  `gross_receipts` bit(1) DEFAULT NULL,
  `charge_receipts` bit(1) DEFAULT NULL,
  `cash_register_credit` bit(1) DEFAULT NULL,
  `tax_exempt_coupon` bit(1) DEFAULT NULL,
  `charged_tip` int(11) DEFAULT NULL,
  `enable_halo` bit(1) DEFAULT NULL,
  `halo_limits_amount` int(11) DEFAULT '0',
  `halo_limits_overtender` int(11) DEFAULT NULL,
  `halo` int(11) DEFAULT NULL,
  `print_summary_totals` bit(1) DEFAULT NULL,
  `print_vat_lines` bit(1) DEFAULT NULL,
  `print_sales_itemizer` bit(1) DEFAULT NULL,
  `print_check_trailer` bit(1) DEFAULT NULL,
  `print_on_receipt` bit(1) DEFAULT NULL,
  `print_with_lookup` bit(1) DEFAULT NULL,
  `print_validation` bit(1) DEFAULT NULL,
  `print_endorsement` bit(1) DEFAULT NULL,
  `suppress_trailer` bit(1) DEFAULT NULL,
  `print_fiscal_cash` bit(1) DEFAULT NULL,
  `print_check` bit(1) DEFAULT NULL,
  `print_memo_check` bit(1) DEFAULT NULL,
  `print_shared_check` bit(1) DEFAULT NULL,
  `print_check_active_seat` bit(1) DEFAULT NULL,
  `reprint_check` bit(1) DEFAULT NULL,
  `period_class_id` int(11) DEFAULT NULL,
  `rvc_class_id` int(11) DEFAULT NULL,
  `extra_amout` float DEFAULT '0',
  PRIMARY KEY (`tender_media_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of tender_media
-- ----------------------------
INSERT INTO tender_media VALUES ('1', '現金', null, null, null, '-1', null, null, '1', null, null, '', null, '', null, '', '', '', null, null, null, null, null, null, null, null, '100000', null, '0', null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, '-1', '-1', '0');
INSERT INTO tender_media VALUES ('2', 'Master Card', null, null, null, '-1', null, null, '2', null, null, '', null, '', null, '', '', '', null, null, null, null, null, null, null, null, '0', null, '0', null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, '-1', '-1', '0');
INSERT INTO tender_media VALUES ('3', 'Visa Card', null, null, null, null, null, null, '2', null, null, '', null, '', null, '', '', '', null, null, null, null, null, null, null, null, '0', null, '0', null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, '0');
INSERT INTO tender_media VALUES ('4', '会員カード', null, null, null, null, null, null, '2', null, null, '', null, '', null, '', '', '', null, null, null, null, null, null, null, null, '0', null, '1', null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, '0');
INSERT INTO tender_media VALUES ('5', '従業員の食事', null, null, null, null, null, null, '0', null, null, '', null, '', null, '', '', '', null, null, null, null, null, null, null, null, '0', null, '0', null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, '0');
INSERT INTO tender_media VALUES ('6', 'クレジット カード', null, null, null, null, null, null, '0', null, null, '', null, '', null, '', '', '', null, null, null, null, null, null, null, null, '0', null, '0', null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, '0');

-- ----------------------------
-- Table structure for `test_db`
-- ----------------------------
DROP TABLE IF EXISTS `test_db`;
CREATE TABLE `test_db` (
  `datenow` datetime DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of test_db
-- ----------------------------
INSERT INTO test_db VALUES ('2013-03-15 10:58:40');

-- ----------------------------
-- Table structure for `tickets`
-- ----------------------------
DROP TABLE IF EXISTS `tickets`;
CREATE TABLE `tickets` (
  `ticket_id` int(11) NOT NULL,
  `ticket_name` varchar(200) DEFAULT NULL,
  `amount` decimal(11,2) DEFAULT NULL,
  `remark` varchar(300) DEFAULT NULL,
  `short_name` varchar(30) DEFAULT NULL,
  PRIMARY KEY (`ticket_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of tickets
-- ----------------------------

-- ----------------------------
-- Table structure for `ticket_class`
-- ----------------------------
DROP TABLE IF EXISTS `ticket_class`;
CREATE TABLE `ticket_class` (
  `ticket_class_id` int(11) NOT NULL DEFAULT '0',
  `ticket_class_name` varchar(200) DEFAULT NULL,
  PRIMARY KEY (`ticket_class_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of ticket_class
-- ----------------------------
INSERT INTO ticket_class VALUES ('1', '不使用');
INSERT INTO ticket_class VALUES ('2', '通用');

-- ----------------------------
-- Table structure for `ticket_relation`
-- ----------------------------
DROP TABLE IF EXISTS `ticket_relation`;
CREATE TABLE `ticket_relation` (
  `ticket_class_id` int(11) NOT NULL DEFAULT '0',
  `ticket_id` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`ticket_class_id`,`ticket_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of ticket_relation
-- ----------------------------

-- ----------------------------
-- Table structure for `time_clock_schedule`
-- ----------------------------
DROP TABLE IF EXISTS `time_clock_schedule`;
CREATE TABLE `time_clock_schedule` (
  `time_clock_id` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `time_clock_number` int(11) DEFAULT NULL,
  `employee_id` int(11) DEFAULT NULL,
  `job_id` int(11) DEFAULT NULL,
  `clock_in_time` time DEFAULT NULL,
  `clock_out_time` time DEFAULT NULL,
  `override_in_early` int(11) DEFAULT NULL,
  `override_in_late` int(11) DEFAULT NULL,
  `override_out_early` int(11) DEFAULT NULL,
  `override_out_late` int(11) DEFAULT NULL,
  PRIMARY KEY (`time_clock_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of time_clock_schedule
-- ----------------------------

-- ----------------------------
-- Table structure for `total_statistics`
-- ----------------------------
DROP TABLE IF EXISTS `total_statistics`;
CREATE TABLE `total_statistics` (
  `total_checks` int(11) NOT NULL DEFAULT '0',
  `total_guests` int(11) NOT NULL DEFAULT '0',
  `install_date` datetime DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of total_statistics
-- ----------------------------
INSERT INTO total_statistics VALUES ('0', '0', '2013-09-12 10:54:37');

-- ----------------------------
-- Table structure for `user_dcb`
-- ----------------------------
DROP TABLE IF EXISTS `user_dcb`;
CREATE TABLE `user_dcb` (
  `dcb_id` int(11) NOT NULL AUTO_INCREMENT,
  `workstations_id` int(11) NOT NULL,
  `dcb_name` varchar(30) DEFAULT NULL,
  PRIMARY KEY (`dcb_id`)
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of user_dcb
-- ----------------------------

-- ----------------------------
-- Table structure for `user_workstations`
-- ----------------------------
DROP TABLE IF EXISTS `user_workstations`;
CREATE TABLE `user_workstations` (
  `workstations_id` int(11) NOT NULL,
  `pos_name` varchar(30) DEFAULT NULL,
  `revenue_center` int(11) DEFAULT NULL,
  `information_screen` int(11) DEFAULT NULL,
  `transaction_screen` int(11) DEFAULT NULL,
  `order_type` int(11) DEFAULT NULL,
  `auto_signout_delay` int(11) DEFAULT NULL,
  `check_start` int(11) DEFAULT '1000',
  `check_end` int(11) DEFAULT '9999',
  `check_num` int(11) DEFAULT '0',
  `enable_auto_signout` bit(1) DEFAULT NULL,
  `cash_drawers` int(11) DEFAULT NULL,
  `order_devices` int(11) DEFAULT '0',
  `customer_receipt_printer` int(11) DEFAULT NULL,
  `guest_check_printer` int(11) DEFAULT NULL,
  `journal_printer` int(11) DEFAULT NULL,
  `local_backup_printer` int(11) DEFAULT NULL,
  `report_printer` int(11) DEFAULT NULL,
  `peripheral_type` int(11) DEFAULT NULL,
  `connection_type` int(11) DEFAULT NULL,
  `opos_device_name` varchar(30) DEFAULT NULL,
  `opos_option` int(11) DEFAULT NULL,
  `com_port` int(11) DEFAULT NULL,
  `customer_display` int(11) DEFAULT '0',
  `ip_address` varchar(32) DEFAULT '',
  `subnet_mask` varchar(32) DEFAULT '',
  `print_class` int(11) DEFAULT NULL,
  `is_quickservice` bit(1) DEFAULT NULL,
  PRIMARY KEY (`workstations_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of user_workstations
-- ----------------------------
INSERT INTO user_workstations VALUES ('1', '默认', '1', null, null, null, null, '1', '999', '174', null, null, '0', '1', '1', null, null, null, null, null, null, null, '12', '-1', '127.0.0.1', null, null, '');

-- ----------------------------
-- Table structure for `vip_setting`
-- ----------------------------
DROP TABLE IF EXISTS `vip_setting`;
CREATE TABLE `vip_setting` (
  `setting_id` int(11) NOT NULL AUTO_INCREMENT,
  `ip_addr` varchar(60) DEFAULT NULL,
  `port` int(11) DEFAULT '8000',
  `res_id` varchar(20) DEFAULT NULL,
  `res_pwd` varchar(20) DEFAULT NULL,
  PRIMARY KEY (`setting_id`)
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of vip_setting
-- ----------------------------
INSERT INTO vip_setting VALUES ('1', '127.0.0.1:81', '8000', '1', '');

-- ----------------------------
-- Table structure for `webreport_setting`
-- ----------------------------
DROP TABLE IF EXISTS `webreport_setting`;
CREATE TABLE `webreport_setting` (
  `cr_url` varchar(200) DEFAULT NULL,
  `cr_port` int(11) DEFAULT '2003',
  `cr_res_id` varchar(50) DEFAULT NULL,
  `cr_res_pwd` varchar(50) DEFAULT NULL,
  `cr_last_endtime` datetime DEFAULT NULL,
  `cr_last_time` datetime DEFAULT NULL,
  `tender_media` int(11) DEFAULT '1',
  `major_group` int(11) DEFAULT '1',
  `family_group` int(11) DEFAULT '1',
  `rvc_center` int(11) DEFAULT '1',
  `periods` int(11) DEFAULT '1',
  `employee` int(11) DEFAULT '1',
  `menu_item` int(11) DEFAULT '1',
  `tables` int(11) DEFAULT '1',
  `res_info` int(11) DEFAULT '1'
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of webreport_setting
-- ----------------------------
INSERT INTO webreport_setting VALUES ('www.coolroid.com', '2003', '{0000-DEFAULT-0000}', '123456', '0000-00-00 00:00:00', '0000-00-00 00:00:00', '1', '1', '1', '1', '1', '1', '1', '1', '1');

-- ----------------------------
-- View structure for `tt`
-- ----------------------------
DROP VIEW IF EXISTS `tt`;
CREATE ALGORITHM=UNDEFINED DEFINER=`root`@`localhost` SQL SECURITY DEFINER VIEW `tt` AS select `payment`.`order_head_id` AS `order_head_id`,`payment`.`check_id` AS `check_id`,`tender_media`.`tender_media_name` AS `tender_media_name`,sum(`payment`.`total`) AS `total` from (`payment` left join `tender_media` on((`payment`.`tender_media_id` = `tender_media`.`tender_media_id`))) group by `payment`.`order_head_id`,`payment`.`check_id`,`tender_media`.`tender_media_name`;

-- ----------------------------
-- Procedure structure for `cash_box_list`
-- ----------------------------
DROP PROCEDURE IF EXISTS `cash_box_list`;
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
DROP PROCEDURE IF EXISTS `check_detail`;
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
where a.order_start_time>s_time and order_start_time<e_time ORDER BY a.order_head_id;
END
;;
DELIMITER ;

-- ----------------------------
-- Procedure structure for `check_ticheng`
-- ----------------------------
DROP PROCEDURE IF EXISTS `check_ticheng`;
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
where menu_item.commission_type>0 and history_order_detail.is_return_item=0 and history_order_detail.menu_item_id>0 and  order_head_id in (select distinct order_head_id from history_order_head where order_start_time>=s_time and order_start_time<=e_time and rvc_center_id>=s_rvcid and rvc_center_id<=e_rvcid) and order_employee_id>=s_number and order_employee_id<=e_number;
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
DROP PROCEDURE IF EXISTS `check_ticheng_detail`;
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
where menu_item.commission_type>0 and history_order_detail.is_return_item=0 and history_order_detail.menu_item_id>0 and  order_head_id in (select distinct order_head_id from history_order_head where order_start_time>=s_time and order_start_time<=e_time and rvc_center_id>=s_rvcid and rvc_center_id<=e_rvcid) and order_employee_id>=s_number and order_employee_id<=e_number;
select m.menu_item_id,m.menu_item_name,a.quantity,a.jin1,b.actual_price,b.jin2,(ifnull(a.jin1,0)+ifnull(b.jin2,0)) as jin3 from 
(select distinct menu_item_id,menu_item_name from miti) as m left join 
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
DROP PROCEDURE IF EXISTS `cost_sum`;
DELIMITER ;;
CREATE DEFINER=`root`@`%` PROCEDURE `cost_sum`(IN `s_time` datetime,IN `e_time` datetime,IN `s_rvcid` int,IN `e_rvcid` int)
BEGIN


	DECLARE sum_q,sum_p float default 0;

	select sum(quantity),sum(actual_price) into sum_q,sum_p from history_order_detail 
where order_head_id in 
(select distinct order_head_id from history_order_head 
where order_start_time>=s_time and order_start_time<=e_time 

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

from history_order_head where order_start_time>=s_time and order_start_time<=e_time 

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
DROP PROCEDURE IF EXISTS `customer_num`;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `customer_num`(IN `s_time` datetime,IN `e_time` datetime,IN `s_rvcid` int,IN `e_rvcid` int,IN `s_number` int,IN `e_number` int)
BEGIN
SELECT SUM(customer_num)as cusNum 
FROM(SELECT DISTINCT order_head_id,customer_num FROM history_order_head
WHERE order_start_time>=s_time and order_start_time<=e_time 
and rvc_center_id>=s_rvcid and rvc_center_id<=e_rvcid
)t;
END
;;
DELIMITER ;

-- ----------------------------
-- Procedure structure for `cut_items`
-- ----------------------------
DROP PROCEDURE IF EXISTS `cut_items`;
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
	INSERT INTO history_order_head select * from order_head where order_head_id=comp;
	DELETE FROM order_head where order_head_id=comp;
	INSERT INTO history_order_detail select * from order_detail where order_head_id=comp;
	DELETE FROM order_detail where order_head_id=comp;
	UPDATE tables SET table_status=0 WHERE table_id= tableid;
END
;;
DELIMITER ;

-- ----------------------------
-- Procedure structure for `c_department_sales`
-- ----------------------------
DROP PROCEDURE IF EXISTS `c_department_sales`;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `c_department_sales`(IN `s_time` datetime,IN `e_time` datetime)
BEGIN
  select print_class_id,print_class_name,round(sum(actual_price),2) from history_order_detail,menu_item,print_class 
	where history_order_detail.menu_item_id=menu_item.item_id AND menu_item.print_class=print_class.print_class_id 
	AND history_order_detail.menu_item_id>0 AND is_return_item=0 
	AND order_head_id in (select distinct order_head_id from history_order_head where order_start_time>=s_time and order_start_time<=e_time)
  GROUP BY print_class_id;
END
;;
DELIMITER ;

-- ----------------------------
-- Procedure structure for `c_item_sales`
-- ----------------------------
DROP PROCEDURE IF EXISTS `c_item_sales`;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `c_item_sales`(IN `s_time` datetime,IN `e_time` datetime,IN  `major_group` int)
BEGIN
	select menu_item_id ,item_name1,unit,round(sum(quantity),0),round(sum(actual_price),1)
	from history_order_detail,menu_item where menu_item_id>0 AND history_order_detail.menu_item_id=menu_item.item_id 
	AND menu_item.major_group=major_group AND (order_time>=s_time AND order_time<e_time)AND is_return_item=0
	group by menu_item_id,unit;
END
;;
DELIMITER ;

-- ----------------------------
-- Procedure structure for `c_major_sales`
-- ----------------------------
DROP PROCEDURE IF EXISTS `c_major_sales`;
DELIMITER ;;
CREATE DEFINER=`root`@`%` PROCEDURE `c_major_sales`(IN `s_time` datetime,IN `e_time` datetime)
BEGIN
	select major_group_id ,major_group_name ,round(sum(actual_price),2) from history_order_detail,menu_item,major_group
	where history_order_detail.menu_item_id=menu_item.item_id AND menu_item.major_group=major_group.major_group_id 
	AND history_order_detail.menu_item_id>0 AND is_return_item=0
	AND  order_head_id in (select distinct order_head_id from history_order_head where order_start_time>=s_time and order_start_time<=e_time)
	GROUP BY major_group_id;
END
;;
DELIMITER ;

-- ----------------------------
-- Procedure structure for `c_pay_style`
-- ----------------------------
DROP PROCEDURE IF EXISTS `c_pay_style`;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `c_pay_style`(IN `s_time` datetime,IN `e_time` datetime,IN `s_device_id` int,IN `e_device_id` int)
BEGIN
	select tender_media_name AS 付款方式,ifnull(total,0) AS 总计 FROM
(select tender_media_id,round(sum(total),2) as total from payment  WHERE 
	pos_device_id>=s_device_id AND pos_device_id<=e_device_id AND payment_time>=s_time AND payment_time<e_time 
	group by tender_media_id) 
	as a right outer join tender_media on tender_media.tender_media_id=a.tender_media_id;
END
;;
DELIMITER ;

-- ----------------------------
-- Procedure structure for `c_period_sales`
-- ----------------------------
DROP PROCEDURE IF EXISTS `c_period_sales`;
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
					 set @sqlcond=concat('(time(order_start_time)>''',pstime,''' OR time(order_start_time)<''',petime,''')');
				ELSE
					 set @sqlcond=concat('(time(order_start_time) BETWEEN ''',pstime,''' AND ''',petime,''')');
				END IF;
				IF line=1 THEN
					set @sqlcmd=concat('select ',pid,' as period_id,''',pname,''' as period_name,sum(a.actual_amount) as total,sum(a.customer_num) as 
					customers_total from (select sum(actual_amount) as actual_amount,customer_num,order_head_id from history_order_head    
					where order_start_time>''',s_time,''' and order_start_time<=''',e_time,''' and ',@sqlcond,' group by order_head_id) as a ');
				ELSE
				  set @sqlcmd=concat(@sqlcmd,'\nunion select ',pid,' as period_id,''',pname,''' as period_name,sum(a.actual_amount) as total,sum(a.customer_num) as 
					customers_total from (select sum(actual_amount) as actual_amount,customer_num,order_head_id from history_order_head    
					where order_start_time>''',s_time,''' and order_start_time<=''',e_time,''' and ',@sqlcond,' group by order_head_id) as a ');
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
-- Procedure structure for `employee_item_sales`
-- ----------------------------
DROP PROCEDURE IF EXISTS `employee_item_sales`;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `employee_item_sales`(IN `s_time` datetime,IN `e_time` datetime,IN `s_rvcid` int,IN `e_rvcid` int,IN `s_number` int,IN `e_number` int)
BEGIN
	select menu_item_id,menu_item_name,product_price,unit,ifnull(sum(quantity),0) as sum_qq,ifnull(sum(actual_price),0) as sum_pp from history_order_detail where menu_item_id>0 and is_return_item=0 and  order_head_id in (select distinct order_head_id from history_order_head where order_start_time>=s_time and order_start_time<=e_time and rvc_center_id>=s_rvcid and rvc_center_id<=e_rvcid) and order_employee_id>=s_number and order_employee_id<=e_number group by menu_item_id;
END
;;
DELIMITER ;

-- ----------------------------
-- Procedure structure for `employee_sales`
-- ----------------------------
DROP PROCEDURE IF EXISTS `employee_sales`;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `employee_sales`(IN `s_time` datetime,IN `e_time` datetime,IN `s_rvcid` int,IN `e_rvcid` int,IN `s_number` int,IN `e_number` int)
BEGIN
select emp_id,emp_name,total,cus_total,round(total/cus_total,2) 
as cus_avg,checks,round(total/checks,2) as checks_avg,
tables,round(total/tables,2) as tables_avg 
from (select open_employee_id as emp_id,open_employee_name as emp_name,
sum(should_amount) as total,
count(order_head_id) as checks,count(distinct(order_head_id)) as tables 
from history_order_head where order_start_time>=s_time 
and order_start_time<=e_time and rvc_center_id>=s_rvcid 
and rvc_center_id<=e_rvcid and open_employee_id>=s_number 
and open_employee_id<=e_number group by open_employee_id)as tableone
LEFT JOIN(select open_employee_id as emp_id1,SUM(customer_num)as cus_total
FROM(SELECT open_employee_id,customer_num FROM history_order_head 
where order_start_time>=s_time 
and order_start_time<=e_time and rvc_center_id>=s_rvcid 
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
DROP PROCEDURE IF EXISTS `family_group_analysis`;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `family_group_analysis`(IN `s_time` datetime,IN `e_time` datetime,IN `s_rvcid` int,IN `e_rvcid` int)
BEGIN
	BEGIN
	declare sum_q,sum_p float;
	select sum(quantity),sum(actual_price) into sum_q,sum_p from history_order_detail where menu_item_id>0 and is_return_item=0 and  order_head_id in (select distinct order_head_id from history_order_head where order_start_time>=s_time and order_start_time<=e_time and rvc_center_id>=s_rvcid and rvc_center_id<=e_rvcid);
		select a.family_group_id as 'ID',`family_group_name` AS '名称',sum(count) AS '数量',sum(count_per) AS '数量百分比(%)',sum(total) AS '金额',sum(total_per) AS '金额百分比(%)' from ((select family_group_id,count,count_per,total,total_per from ((select family_group_id,0 as count,0 as count_per,0 as total,0 as total_per from family_group) union (select family_group,sum(quantity),(round(sum(quantity)/sum_q*100,2)),sum(actual_price),(round(sum(actual_price)/sum_p*100,2)) from history_order_detail left join menu_item on history_order_detail.menu_item_id=menu_item.item_id where menu_item_id>0 and is_return_item=0 and  order_head_id in (select distinct order_head_id from history_order_head where order_start_time>=s_time and order_start_time<=e_time and rvc_center_id>=s_rvcid and rvc_center_id<=e_rvcid) group by family_group)) as tableone order by family_group_id,count desc) as a left join (select family_group_id,`family_group_name` from family_group) as b on a.family_group_id=b.family_group_id) group by a.family_group_id;
END;
END
;;
DELIMITER ;

-- ----------------------------
-- Procedure structure for `flush_order`
-- ----------------------------
DROP PROCEDURE IF EXISTS `flush_order`;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `flush_order`(IN head_id INT,IN tableid INT)
BEGIN
	declare rows INT default -1;
	INSERT INTO history_order_detail select * from order_detail WHERE is_return_item=1;
	DELETE FROM order_detail WHERE is_return_item=1;
	SELECT count(*) into rows FROM order_detail WHERE order_head_id=head_id;
	IF rows=0 THEN
		DELETE FROM order_head WHERE order_head_id=head_id;
		UPDATE tables SET table_status=1 WHERE table_id= tableid;
	END IF;
END
;;
DELIMITER ;

-- ----------------------------
-- Procedure structure for `group_item_sales`
-- ----------------------------
DROP PROCEDURE IF EXISTS `group_item_sales`;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `group_item_sales`(IN `s_time` datetime,IN `e_time` datetime,IN `s_rvcid` int,IN `e_rvcid` int,IN `s_number` int,IN `e_number` int)
BEGIN
	DECLARE sum_q,sum_p float default 0;
	select sum(quantity),sum(actual_price) into sum_q,sum_p from history_order_detail,menu_item where order_head_id in 
(select distinct order_head_id from history_order_head where order_start_time>=s_time and order_start_time<=e_time 
and rvc_center_id>=s_rvcid and rvc_center_id<=e_rvcid) and item_id=menu_item_id 
and slu_id>=s_number and slu_id<=e_number and is_return_item=0;
	select menu_item_id,menu_item_name,unit,product_price,sum_qq,
(round(sum_qq/sum_q*100,2)) as sum_qq_avg,sum_pp,
(round(sum_pp/sum_p*100,2)) as sum_pp_avg from (select menu_item_id,menu_item_name,
unit,product_price,round(ifnull(sum(quantity),0),2) as sum_qq,ifnull(sum(actual_price),0) as sum_pp 
from history_order_detail,menu_item where menu_item_id>0 and item_id = menu_item_id and  order_head_id in (select distinct order_head_id 
from history_order_head where order_start_time>=s_time and order_start_time<=e_time 
and rvc_center_id>=s_rvcid and rvc_center_id<=e_rvcid and is_return_item=0) and slu_id>=s_number 
and slu_id<=e_number group by menu_item_id) as a ;
END
;;
DELIMITER ;

-- ----------------------------
-- Procedure structure for `item_sales`
-- ----------------------------
DROP PROCEDURE IF EXISTS `item_sales`;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `item_sales`(IN `s_time` datetime,IN `e_time` datetime,IN `s_rvcid` int,IN `e_rvcid` int,IN `s_number` int,IN `e_number` int)
BEGIN


	DECLARE sum_q,sum_p float default 0;

	select sum(quantity),sum(actual_price) into sum_q,sum_p from history_order_detail 
where order_head_id in 
(select distinct order_head_id from history_order_head 
where order_start_time>=s_time and order_start_time<=e_time 

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

from history_order_head where order_start_time>=s_time and order_start_time<=e_time 

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
DROP PROCEDURE IF EXISTS `item_sales_desc`;
DELIMITER ;;
CREATE DEFINER=`root`@`%` PROCEDURE `item_sales_desc`(IN `s_time` datetime,IN `e_time` datetime,IN `s_rvcid` int,IN `e_rvcid` int,IN `s_number` int,IN `e_number` int)
BEGIN
	DECLARE sum_q,sum_p float default 0;
	select sum(quantity),sum(actual_price) into sum_q,sum_p from history_order_detail 
where order_head_id in 
(select distinct order_head_id from history_order_head 
where order_start_time>=s_time and order_start_time<=e_time 
and rvc_center_id>=s_rvcid and rvc_center_id<=e_rvcid) and menu_item_id>=s_number 
and menu_item_id<=e_number and is_return_item=0;
	select menu_item_id,menu_item.item_name1,unit,product_price,sum_qq,
(round(sum_qq/sum_q*100,2)) as sum_qq_avg,sum_pp,
(round(sum_pp/sum_p*100,2)) as sum_pp_avg from (select menu_item_id,menu_item_name,
unit,product_price,ifnull(sum(quantity),0) as sum_qq,ifnull(sum(actual_price),0) as sum_pp 
from history_order_detail where menu_item_id>0 and  order_head_id in (select distinct order_head_id 
from history_order_head where order_start_time>=s_time and order_start_time<=e_time 
and rvc_center_id>=s_rvcid and rvc_center_id<=e_rvcid and is_return_item=0) 
and menu_item_id>=s_number 
and menu_item_id<=e_number group by menu_item_id) as a 
LEFT JOIN menu_item ON menu_item.item_id = a.menu_item_id  ORDER BY sum_pp DESC;
END
;;
DELIMITER ;

-- ----------------------------
-- Procedure structure for `i_consume_group`
-- ----------------------------
DROP PROCEDURE IF EXISTS `i_consume_group`;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `i_consume_group`(IN `s_time` datetime,IN `e_time` datetime)
BEGIN
	SELECT family_group_id AS 编号,family_group_name AS 名称,SUM(ttl1) AS 入库,SUM(ttl2) AS 领料,SUM(ttl3) AS 消耗
	,SUM(ttl4) AS 退货, SUM(ttl5) AS 结余
	FROM (SELECT  t1.family_group,ttl1,ttl2,ttl3,ttl4,ttl5 FROM
  (SELECT material.material_id,material.family_group,SUM(total) AS ttl1 FROM material LEFT JOIN history_material_detail 
		ON (history_material_detail.material_id=material.material_id AND hm_head_id IN 
	(SELECT hm_head_id FROM history_material_head WHERE type=1 AND pick_time>s_time AND pick_time<=e_time)) GROUP BY material_id)  AS t1,
	(SELECT material.material_id,SUM(total) AS ttl2 FROM material LEFT JOIN history_material_detail 
		ON (history_material_detail.material_id=material.material_id AND hm_head_id IN 
	(SELECT hm_head_id FROM history_material_head WHERE type=2 AND pick_time>s_time AND pick_time<=e_time)) GROUP BY material_id)  AS t2,
	(SELECT material.material_id,SUM(total) AS ttl3 FROM material LEFT JOIN history_material_detail 
		ON (history_material_detail.material_id=material.material_id AND hm_head_id IN 
	(SELECT hm_head_id FROM history_material_head WHERE type=0 AND pick_time>s_time AND pick_time<=e_time)) GROUP BY material_id)  AS t3,
	(SELECT material.material_id,SUM(total) AS ttl4 FROM material LEFT JOIN history_material_detail 
		ON (history_material_detail.material_id=material.material_id AND hm_head_id IN 
	(SELECT hm_head_id FROM history_material_head WHERE type=3 AND pick_time>s_time AND pick_time<=e_time)) GROUP BY material_id)  AS t4,
	(SELECT material.material_id,num*material_price AS ttl5 FROM material)  AS t5
	WHERE  t1.material_id=t2.material_id AND t1.material_id=t3.material_id AND t1.material_id=t4.material_id AND t1.material_id=t5.material_id)
	AS TT1,family_group
	WHERE  TT1.family_group=family_group.family_group_id
  GROUP BY family_group_id;
END
;;
DELIMITER ;

-- ----------------------------
-- Procedure structure for `i_consume_material`
-- ----------------------------
DROP PROCEDURE IF EXISTS `i_consume_material`;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `i_consume_material`(IN `s_time` datetime,IN `e_time` datetime,IN `s_id` int,IN `e_id` int)
BEGIN
	SELECT t1.material_id AS 编号,material_name AS 名称,ttl1 AS 入库,ttl2 AS 领料,ttl3 AS 消耗
	,ttl4 AS 退货, ttl5 AS 结余
	FROM
  (SELECT material.material_id,material.material_name,SUM(total) AS ttl1 FROM material LEFT JOIN history_material_detail 
		ON (history_material_detail.material_id=material.material_id AND hm_head_id IN 
	(SELECT hm_head_id FROM history_material_head WHERE type=1 AND pick_time>=s_time AND pick_time<=e_time)) WHERE family_group>=s_id 
		AND  family_group<=e_id GROUP BY material_id)  AS t1,
	(SELECT material.material_id,SUM(total) AS ttl2 FROM material LEFT JOIN history_material_detail 
		ON (history_material_detail.material_id=material.material_id AND hm_head_id IN 
	(SELECT hm_head_id FROM history_material_head WHERE type=2 AND pick_time>=s_time AND pick_time<=e_time)) WHERE family_group>=s_id 
		AND  family_group<=e_id GROUP BY material_id)  AS t2,
	(SELECT material.material_id,SUM(total) AS ttl3 FROM material LEFT JOIN history_material_detail 
		ON (history_material_detail.material_id=material.material_id AND hm_head_id IN 
	(SELECT hm_head_id FROM history_material_head WHERE type=0 AND pick_time>=s_time AND pick_time<=e_time)) WHERE family_group>=s_id 
		AND  family_group<=e_id GROUP BY material_id)  AS t3,
	(SELECT material.material_id,SUM(total) AS ttl4 FROM material LEFT JOIN history_material_detail 
		ON (history_material_detail.material_id=material.material_id AND hm_head_id IN 
	(SELECT hm_head_id FROM history_material_head WHERE type=3 AND pick_time>=s_time AND pick_time<=e_time)) WHERE family_group>=s_id 
		AND  family_group<=e_id GROUP BY material_id)  AS t4,
	(SELECT material.material_id,num*material_price AS ttl5 FROM material WHERE family_group>=s_id AND  family_group<=e_id )  AS t5
	WHERE  t1.material_id=t2.material_id AND t1.material_id=t3.material_id AND t1.material_id=t4.material_id AND t1.material_id=t5.material_id
  ;
END
;;
DELIMITER ;

-- ----------------------------
-- Procedure structure for `i_consume_material_new`
-- ----------------------------
DROP PROCEDURE IF EXISTS `i_consume_material_new`;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `i_consume_material_new`(IN `s_time` datetime,IN `e_time` datetime,IN `s_number` int,IN `e_number` int)
BEGIN
	SELECT t1.material_id ,t1.material_unit,material_name AS 名称,ttl2 AS 进货量,ttl1 AS 进货金额,ttl4 AS 销量,ttl3 AS 销售额, ttl6 AS 库存结余数量, ttl5 AS 库存结余金额
	FROM
  (SELECT material.material_id,material.material_unit,material.material_name,SUM(total) AS ttl1,SUM(history_material_detail.num) AS ttl2 FROM material LEFT JOIN history_material_detail 
		ON (history_material_detail.material_id=material.material_id AND hm_head_id IN 
	(SELECT hm_head_id FROM history_material_head WHERE type=1 AND pick_time>=s_time AND pick_time<=e_time)) WHERE family_group>=s_number 
		AND  family_group<=e_number GROUP BY material_id)  AS t1,
	(SELECT material.material_id,SUM(actual_price) AS ttl3,SUM(quantity) AS ttl4 FROM material LEFT JOIN 
		(SELECT material_id,actual_price,quantity FROM item_material,history_order_detail
		WHERE history_order_detail.menu_item_id=item_material.item_id AND is_return_item=0 AND order_time>=s_time AND order_time<=e_time) AS tmp
		ON tmp.material_id=material.material_id
		WHERE family_group>=s_number AND  family_group<=e_number GROUP BY material_id)  AS t3,
	(SELECT material.material_id,num AS ttl6,num*material_price AS ttl5 FROM material WHERE family_group>=s_number AND  family_group<=e_number )  AS t5
	WHERE  t1.material_id=t3.material_id AND  t1.material_id=t5.material_id
  ;
END
;;
DELIMITER ;

-- ----------------------------
-- Procedure structure for `i_consume_total`
-- ----------------------------
DROP PROCEDURE IF EXISTS `i_consume_total`;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `i_consume_total`(IN `s_time` datetime,IN `e_time` datetime,IN `s_id` int,IN `e_id` int)
BEGIN
	select hm_head_id as 'ID',type_name as '类型',
suppliers_name as '供应商',price AS '总金额',
employee_name AS '经办人' ,pick_time as '操作时间',mark AS '备注'
from history_material_head left JOIN 
suppliers
on (history_material_head.suppliers_id = suppliers.suppliers_id)
where 1=1 AND pick_time>=s_time AND pick_time<=e_time AND history_material_head.suppliers_id >= s_id AND history_material_head.suppliers_id <= e_id
order by pick_time desc;
END
;;
DELIMITER ;

-- ----------------------------
-- Procedure structure for `i_material_history`
-- ----------------------------
DROP PROCEDURE IF EXISTS `i_material_history`;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `i_material_history`(IN `sid` int,IN `sdate` datetime,IN `edate` datetime)
BEGIN
	SELECT history_material_detail.price,history_material_detail.num,
history_material_detail.unit,history_material_detail.total,
history_material_detail.mark,history_material_head.pick_time,
inventory_type_name,material_name
from history_material_head,history_material_detail,
inventory_type
WHERE history_material_detail.hm_head_id = history_material_head.hm_head_id
and history_material_head.pick_time >= sdate
and history_material_head.pick_time <= edate
and history_material_detail.material_id = sid
and inventory_type.inventory_type_id = history_material_head.type
;
END
;;
DELIMITER ;

-- ----------------------------
-- Procedure structure for `i_material_sail`
-- ----------------------------
DROP PROCEDURE IF EXISTS `i_material_sail`;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `i_material_sail`(IN `s_time` datetime,IN `e_time` datetime,IN `s_id` int)
BEGIN
	SELECT item_id,menu_item_name,product_price,sum(quantity) as num,sum(actual_price) as total
from item_material,history_order_detail
where material_id = s_id
and is_return_item = 0
and item_material.item_id = history_order_detail.menu_item_id
and order_time >= s_time and order_time <= e_time
GROUP BY item_id
;
END
;;
DELIMITER ;

-- ----------------------------
-- Procedure structure for `i_suppliers`
-- ----------------------------
DROP PROCEDURE IF EXISTS `i_suppliers`;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `i_suppliers`(IN `s_time` datetime,IN `e_time` datetime,IN `s_id` int)
BEGIN
	SELECT material.material_id AS 编号,material.material_name AS 名称,SUM(history_material_detail.num) AS 数量,SUM(total) AS 金额 
	FROM material,history_material_detail 
		WHERE hm_head_id IN
	(SELECT hm_head_id FROM history_material_head WHERE type=1 AND suppliers_id=s_id
		AND pick_time>=s_time AND pick_time<=e_time) AND history_material_detail.material_id=material.material_id
	GROUP BY material.material_id;
END
;;
DELIMITER ;

-- ----------------------------
-- Procedure structure for `i_suppliers_total`
-- ----------------------------
DROP PROCEDURE IF EXISTS `i_suppliers_total`;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `i_suppliers_total`(IN `s_time` datetime,IN `e_time` datetime)
BEGIN
	SELECT suppliers.suppliers_id AS 编号,suppliers.suppliers_name AS 名称,SUM(price) AS 供货金额 
	FROM history_material_head LEFT JOIN suppliers ON 
		history_material_head.suppliers_id=suppliers.suppliers_id
	WHERE type=1 AND pick_time>=s_time AND pick_time<=e_time
	GROUP BY suppliers.suppliers_id;
END
;;
DELIMITER ;

-- ----------------------------
-- Procedure structure for `join_table`
-- ----------------------------
DROP PROCEDURE IF EXISTS `join_table`;
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
DROP PROCEDURE IF EXISTS `join_table_1`;
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
DROP PROCEDURE IF EXISTS `maingroup_item_sales`;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `maingroup_item_sales`(IN `s_time` datetime,IN `e_time` datetime,IN `s_rvcid` int,IN `e_rvcid` int,IN `s_number` int,IN `e_number` int)
BEGIN
	DECLARE sum_q,sum_p float default 0;
	select sum(quantity),sum(actual_price) into sum_q,sum_p from history_order_detail,menu_item,item_main_group where order_head_id in 
(select distinct order_head_id from history_order_head where order_start_time>=s_time and order_start_time<=e_time 
and rvc_center_id>=s_rvcid and rvc_center_id<=e_rvcid) and item_id=menu_item_id 
and main_group_id>=s_number and main_group_id<=e_number and is_return_item=0 and slu_id=second_group_id;
	select menu_item_id,menu_item_name,unit,product_price,sum_qq,
(round(sum_qq/sum_q*100,2)) as sum_qq_avg,sum_pp,
(round(sum_pp/sum_p*100,2)) as sum_pp_avg from (select menu_item_id,menu_item_name,
unit,product_price,round(ifnull(sum(quantity),0),2) as sum_qq,ifnull(sum(actual_price),0) as sum_pp 
from history_order_detail,menu_item,item_main_group where menu_item_id>0 and item_id = menu_item_id and  order_head_id in (select distinct order_head_id 
from history_order_head where order_start_time>=s_time and order_start_time<=e_time 
and rvc_center_id>=s_rvcid and rvc_center_id<=e_rvcid and is_return_item=0) and main_group_id>=s_number 
and main_group_id<=e_number and slu_id=second_group_id
 group by menu_item_id) as a ;
END
;;
DELIMITER ;

-- ----------------------------
-- Procedure structure for `major_group_analysis`
-- ----------------------------
DROP PROCEDURE IF EXISTS `major_group_analysis`;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `major_group_analysis`(IN `s_time` datetime,IN `e_time` datetime,IN `s_rvcid` int,IN `e_rvcid` int)
BEGIN
	BEGIN
	declare sum_q,sum_p float;
	select sum(quantity),sum(actual_price) into sum_q,sum_p 
from history_order_detail where menu_item_id>0 and is_return_item=0 
and  order_head_id in (select distinct order_head_id from history_order_head where order_start_time>=s_time and order_start_time<=e_time and rvc_center_id>=s_rvcid and rvc_center_id<=e_rvcid);
		select a.major_group_id as 'ID',`major_group_name` AS '名称',sum(count) AS '数量',sum(count_per) AS '数量百分比(%)',sum(total) AS '金额',sum(total_per) AS '金额百分比(%)' from ((select major_group_id,count,count_per,total,total_per from ((select major_group_id,0 as count,0 as count_per,0 as total,0 as total_per from major_group) union (select major_group,sum(quantity),(round(sum(quantity)/sum_q*100,2)),sum(actual_price),(round(sum(actual_price)/sum_p*100,2)) from history_order_detail left join menu_item on history_order_detail.menu_item_id=menu_item.item_id where menu_item_id>0 and is_return_item=0 and  order_head_id in (select distinct order_head_id from history_order_head where order_start_time>=s_time and order_start_time<=e_time and rvc_center_id>=s_rvcid and rvc_center_id<=e_rvcid) group by major_group)) as tableone order by major_group_id,count desc) as a left join (select major_group_id,`major_group_name` from major_group) as b on a.major_group_id=b.major_group_id) group by a.major_group_id;
END;
END
;;
DELIMITER ;

-- ----------------------------
-- Procedure structure for `move_check`
-- ----------------------------
DROP PROCEDURE IF EXISTS `move_check`;
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
DROP PROCEDURE IF EXISTS `move_check_1`;
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
/*只有一张单*/
		IF ISNULL(ismake1) OR ismake1=0 OR ISNULL(ismake2) OR ismake2=0 THEN
			SET ismake1=0;
		END IF;
		set customer_dest=customer_dest+customer_old;
		select actual_amount into payed_old from order_head where table_id =table_from and check_id=check_from;
		DELETE FROM order_head  where table_id=table_from and check_id=check_from;
		update order_detail SET check_id=1,order_head_id=order_id where check_id=check_from and order_head_id=order_old;
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
DROP PROCEDURE IF EXISTS `open_table`;
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
DROP PROCEDURE IF EXISTS `order_type_sails`;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `order_type_sails`(IN `s_time` datetime,IN `e_time` datetime,IN `s_rvcid` int,IN `e_rvcid` int)
BEGIN
	DECLARE should_total,customer_total,checks_total,tables_total FLOAT;
	select ifnull(sum(should_amount),0),count(*),
count(distinct(order_head_id)) into should_total,checks_total,tables_total 
from history_order_head where order_start_time>=s_time and order_start_time<=e_time and rvc_center_id>=s_rvcid 
and rvc_center_id<=e_rvcid;
  select ifnull(sum(customer_num),0) into customer_total FROM
(SELECT customer_num from history_order_head where order_start_time>=s_time 
and order_start_time<=e_time and rvc_center_id>=s_rvcid 
and rvc_center_id<=e_rvcid GROUP BY order_head_id)tttTmp;
select count(*),count(distinct(order_head_id)) into checks_total,tables_total 
from history_order_head where order_start_time>=s_time and order_start_time<=e_time 
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
where order_start_time>=s_time and order_start_time<=e_time 
and rvc_center_id>=s_rvcid and rvc_center_id<=e_rvcid group by eat_type) 
as tableone 
LEFT JOIN(SELECT eat_type,SUM(customer_num)as guests FROM (SELECT eat_type,customer_num
FROM history_order_head where order_start_time>=s_time and order_start_time<=e_time 
and rvc_center_id>=s_rvcid and rvc_center_id<=e_rvcid GROUP BY order_head_id)tmpT1 GROUP BY eat_type)tmpT 
ON tableone.eat_type = tmpT.eat_type
right outer join order_types on tableone.eat_type=order_types.order_type_id 
left outer join (select eat_type,sum(eat_time) as time_total 
from (select order_head_id,eat_type,TimeStampDiff(MINUTE,min(order_start_time),max(order_end_time)) as eat_time 
from history_order_head where order_start_time>=s_time and order_start_time<=e_time 
and rvc_center_id>=s_rvcid and rvc_center_id<=e_rvcid group by order_head_id) as tablea group by eat_type) 
as timetable on order_types.order_type_id=timetable.eat_type;
END
;;
DELIMITER ;

-- ----------------------------
-- Procedure structure for `pay_style`
-- ----------------------------
DROP PROCEDURE IF EXISTS `pay_style`;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `pay_style`(IN `s_time` datetime,IN `e_time` datetime,IN `s_rvcid` int,IN `e_rvcid` int)
BEGIN
	DECLARE sum_total INT default 0;
	select sum(total) into sum_total from payment where order_head_id in (select distinct order_head_id from history_order_head where order_start_time>=s_time and order_start_time<=e_time and rvc_center_id>=s_rvcid and rvc_center_id<=e_rvcid);
	select tender_media.tender_media_id,tender_media_name,ifnull(total,0) AS total,
IFNULL(round(ifnull(total,0)/sum_total*100,2),0) as total_avg,round(total*extra_amout/100,2)  as sum_extra
from (select tender_media_id,round(sum(total),2) as total from payment  where order_head_id in (select distinct order_head_id from history_order_head where order_start_time>=s_time and order_start_time<=e_time and rvc_center_id>=s_rvcid and rvc_center_id<=e_rvcid) group by tender_media_id) as a right outer join tender_media on tender_media.tender_media_id=a.tender_media_id;
END
;;
DELIMITER ;

-- ----------------------------
-- Procedure structure for `return_item_list`
-- ----------------------------
DROP PROCEDURE IF EXISTS `return_item_list`;
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
where history_order_detail.order_head_id=history_order_head.order_head_id
and (is_return_item=1 OR quantity<0) 
and history_order_detail.order_head_id 
in (select distinct order_head_id from history_order_head 
where order_start_time>=s_time and order_start_time<=e_time 
and rvc_center_id>=s_rvcid and rvc_center_id<=e_rvcid)
and history_order_detail.order_employee_id>=s_number 
and history_order_detail.order_employee_id<=e_number 
order by history_order_detail.order_employee_id;
END
;;
DELIMITER ;

-- ----------------------------
-- Procedure structure for `revert_check`
-- ----------------------------
DROP PROCEDURE IF EXISTS `revert_check`;
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
DROP PROCEDURE IF EXISTS `sail_pre_list`;
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
DROP PROCEDURE IF EXISTS `sales_analysis`;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `sales_analysis`(IN `s_time` datetime,IN `e_time` datetime,IN `s_rvcid` int,IN `e_rvcid` int)
BEGIN
	DECLARE sales_detail_total,service_total,discount_total,return_item_total,should_total,actual_total FLOAT;
	select ifnull(sum(actual_price),0) into sales_detail_total from history_order_detail where is_return_item=0 and menu_item_id>0 and  order_head_id in (select distinct order_head_id from history_order_head where order_start_time>=s_time and order_start_time<=e_time and rvc_center_id>=s_rvcid and rvc_center_id<=e_rvcid);
	select ifnull(sum(service_amount),0) into service_total from history_order_head where order_start_time>=s_time and order_start_time<=e_time and rvc_center_id>=s_rvcid and rvc_center_id<=e_rvcid;
	select sum(ifnull(discount_amount,0)) into discount_total from history_order_head where order_start_time>=s_time and order_start_time<=e_time and rvc_center_id>=s_rvcid and rvc_center_id<=e_rvcid ;
	select sum(abs(ifnull(actual_price,0))) into return_item_total from history_order_detail where ((is_return_item=1 OR quantity<0) and menu_item_id>0) and order_head_id in (select distinct order_head_id from history_order_head where order_start_time>=s_time and order_start_time<=e_time and rvc_center_id>=s_rvcid and rvc_center_id<=e_rvcid) ;
	select ifnull(sum(should_amount),0) into should_total from history_order_head where order_start_time>=s_time and order_start_time<=e_time and rvc_center_id>=s_rvcid and rvc_center_id<=e_rvcid;
	select ifnull(sum(actual_amount),0) into actual_total from history_order_head where order_start_time>=s_time and order_start_time<=e_time and rvc_center_id>=s_rvcid and rvc_center_id<=e_rvcid;
select round(sales_detail_total,2),round(service_total,2),round(discount_total,2),round(return_item_total,2),round(should_total,2),round(actual_total,2); 
END
;;
DELIMITER ;

-- ----------------------------
-- Procedure structure for `sales_analysis_kaitailv`
-- ----------------------------
DROP PROCEDURE IF EXISTS `sales_analysis_kaitailv`;
DELIMITER ;;
CREATE DEFINER=`root`@`%` PROCEDURE `sales_analysis_kaitailv`(IN `s_time` datetime,IN `e_time` datetime,IN `s_rvcid` int,IN `e_rvcid` int)
BEGIN
	DECLARE table_num ,actual_table_num,actual_cus_num,actual_seat_num INT;
	SELECT (SELECT COUNT(*) from `tables` WHERE table_status != 6) INTO table_num;
	SELECT (SELECT sum(seat_num) from `tables` WHERE table_status != 6) INTO actual_seat_num;
SELECT SUM(customer_num)as cusNum INTO actual_cus_num
FROM(SELECT DISTINCT order_head_id,customer_num FROM history_order_head
WHERE order_start_time>=s_time and order_start_time<=e_time 
and rvc_center_id>=s_rvcid and rvc_center_id<=e_rvcid)t;
select count(distinct(order_head_id)) into actual_table_num 
from history_order_head where order_start_time>=s_time and order_start_time<=e_time 
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
DROP PROCEDURE IF EXISTS `sales_periods`;
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
					 set @sqlcond=concat('(time(order_start_time)>''',pstime,''' OR time(order_start_time)<''',petime,''')');
				ELSE
					 set @sqlcond=concat('(time(order_start_time) BETWEEN ''',pstime,''' AND ''',petime,''')');
				END IF;
				IF LINE=1 THEN
					set @sqlcmd=concat('select ',pid,' as period_id,''',pname,''' as period_name,sum(a.should_amount) as total,sum(a.customer_num) as customers_total,round(sum(a.should_amount)/sum(a.customer_num),2) as customer_avg,sum(a.checks_total) as checks_total,round(sum(a.should_amount)/sum(a.checks_total),2) as table_avg,count(a.order_head_id) as tables_total,round(sum(a.should_amount)/count(a.order_head_id),2) as table_avg from (select        
																																				sum(should_amount) as should_amount,customer_num,count(order_head_id) as checks_total,order_head_id from history_order_head    
						where order_start_time>=''',s_time,''' and order_start_time<=''',e_time,''' and rvc_center_id>=',s_rvcid,' and rvc_center_id<=',e_rvcid,' and ',@sqlcond,' group by order_head_id) as a ');
				ELSE
					set @sqlcmd=concat(@sqlcmd,'union select ',pid,' as period_id,''',pname,''' as period_name,sum(a.should_amount) as total,sum(a.customer_num) as customers_total,round(sum(a.should_amount)/sum(a.customer_num),2) as customer_avg,sum(a.checks_total) as checks_total,round(sum(a.should_amount)/sum(a.checks_total),2) as table_avg,count(a.order_head_id) as tables_total,round(sum(a.should_amount)/count(a.order_head_id),2) as table_avg from (select        
																																				sum(should_amount) as should_amount,customer_num,count(order_head_id) as checks_total,order_head_id  from history_order_head    
						where order_start_time>=''',s_time,''' and order_start_time<=''',e_time,''' and rvc_center_id>=',s_rvcid,' and rvc_center_id<=',e_rvcid,' and ',@sqlcond,' group by order_head_id) as a ');
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
DROP PROCEDURE IF EXISTS `show_item_material`;
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
DROP PROCEDURE IF EXISTS `show_item_material_2`;
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
-- Procedure structure for `test`
-- ----------------------------
DROP PROCEDURE IF EXISTS `test`;
DELIMITER ;;
CREATE DEFINER=`root`@`%` PROCEDURE `test`(IN `s_time` time,IN `e_time` time)
BEGIN
	select sum(should_amount) as should_amount,customer_num,order_head_id from history_order_head    
					where order_start_time>='2012-10-10 2:00' and order_start_time<='2012-10-11 2:00' 
		and case when e_time<s_time then (time(order_start_time)<e_time OR time(order_start_time)>s_time) else (time(order_start_time) BETWEEN e_time and e_time) end
group by order_head_id;

END
;;
DELIMITER ;

-- ----------------------------
-- Procedure structure for `test_rr`
-- ----------------------------
DROP PROCEDURE IF EXISTS `test_rr`;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `test_rr`(IN s_time DateTime,IN e_time DateTime)
BEGIN

	select a.order_head_id,a.check_id,a.actual_amount,a.should_amount,a.service_amount,a.discount_amount,  ifnull(aa.major1,0) as major1 ,ifnull(bb.major2,0) as major2 ,ifnull(cc.major3,0) as major3,ifnull(dd.major4,0) as major4  ,ifnull(b.shipin,0) as tender1,ifnull(c.shipin,0) as tender2,ifnull(d.shipin,0) as tender3,ifnull(e.shipin,0) as tender4 from history_order_head as a left join (select order_head_id,check_id,sum(total) as shipin from payment where tender_media_id=1 group by order_head_id,check_id) as b on a.order_head_id=b.order_head_id and a.check_id=b.check_id      left join (select order_head_id,check_id,sum(total) as shipin from payment where tender_media_id=2 group by order_head_id,check_id) as c on a.order_head_id=c.order_head_id and a.check_id=c.check_id   left join (select order_head_id,check_id,sum(total) as shipin from payment where tender_media_id=3 group by order_head_id,check_id) as d on a.order_head_id=d.order_head_id and a.check_id=d.check_id   left join (select order_head_id,check_id,sum(total) as shipin from payment where tender_media_id=4 group by order_head_id,check_id) as e on a.order_head_id=e.order_head_id and a.check_id=e.check_id  left join (select a1.order_head_id,a1.check_id,sum(a1.actual_price) as major1 from history_order_detail as a1  left join menu_item on menu_item.item_id=a1.menu_item_id  where a1.menu_item_id>0 and a1.is_return_item!=-1 and menu_item.major_group=1 group by a1.order_head_id,a1.check_id) as aa on  a.order_head_id=aa.order_head_id and a.check_id=aa.check_id  left join (select a1.order_head_id,a1.check_id,sum(a1.actual_price) as major2 from history_order_detail as a1  left join menu_item on menu_item.item_id=a1.menu_item_id  where a1.menu_item_id>0 and a1.is_return_item!=-1 and menu_item.major_group=2 group by a1.order_head_id,a1.check_id) as bb on  a.order_head_id=bb.order_head_id and a.check_id=bb.check_id  left join (select a1.order_head_id,a1.check_id,sum(a1.actual_price) as major3 from history_order_detail as a1  left join menu_item on menu_item.item_id=a1.menu_item_id  where a1.menu_item_id>0 and a1.is_return_item!=-1 and menu_item.major_group=3 group by a1.order_head_id,a1.check_id) as cc on  a.order_head_id=cc.order_head_id and a.check_id=cc.check_id  left join (select a1.order_head_id,a1.check_id,sum(a1.actual_price) as major4 from history_order_detail as a1  left join menu_item on menu_item.item_id=a1.menu_item_id  where a1.menu_item_id>0 and a1.is_return_item!=-1 and menu_item.major_group=4 group by a1.order_head_id,a1.check_id) as dd on  a.order_head_id=dd.order_head_id and a.check_id=dd.check_id    where a.order_start_time>s_time and order_start_time<e_time;

END
;;
DELIMITER ;

-- ----------------------------
-- Procedure structure for `trans_table`
-- ----------------------------
DROP PROCEDURE IF EXISTS `trans_table`;
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
DROP PROCEDURE IF EXISTS `update_checknum`;
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
CREATE TRIGGER `trigger_desheader_add` AFTER INSERT ON `descriptors_headers` FOR EACH ROW BEGIN
	UPDATE webreport_setting SET res_info = 1;
END
;;
DELIMITER ;
DELIMITER ;;
CREATE TRIGGER `trigger_desheader_update` AFTER UPDATE ON `descriptors_headers` FOR EACH ROW BEGIN
	UPDATE webreport_setting SET res_info = 1;
END
;;
DELIMITER ;
DELIMITER ;;
CREATE TRIGGER `trigger_desheader_del` AFTER DELETE ON `descriptors_headers` FOR EACH ROW BEGIN
	UPDATE webreport_setting SET res_info = 1;
END
;;
DELIMITER ;
DELIMITER ;;
CREATE TRIGGER `trigger_destrailer_add` AFTER INSERT ON `descriptors_trailers` FOR EACH ROW BEGIN
	UPDATE webreport_setting SET res_info = 1;
END
;;
DELIMITER ;
DELIMITER ;;
CREATE TRIGGER `trigger_destrailer_update` AFTER UPDATE ON `descriptors_trailers` FOR EACH ROW BEGIN
	UPDATE webreport_setting SET res_info = 1;
END
;;
DELIMITER ;
DELIMITER ;;
CREATE TRIGGER `trigger_destrailer_del` AFTER DELETE ON `descriptors_trailers` FOR EACH ROW BEGIN
	UPDATE webreport_setting SET res_info = 1;
END
;;
DELIMITER ;
DELIMITER ;;
CREATE TRIGGER `trigger_employee_add` AFTER INSERT ON `employee` FOR EACH ROW BEGIN
	UPDATE webreport_setting SET employee = 1;
END
;;
DELIMITER ;
DELIMITER ;;
CREATE TRIGGER `trigger_employee_update` AFTER UPDATE ON `employee` FOR EACH ROW BEGIN
	UPDATE webreport_setting SET employee = 1;
END
;;
DELIMITER ;
DELIMITER ;;
CREATE TRIGGER `trigger_employee_del` AFTER DELETE ON `employee` FOR EACH ROW BEGIN
	UPDATE webreport_setting SET employee = 1;
END
;;
DELIMITER ;
DELIMITER ;;
CREATE TRIGGER `trigger_family_group_add` AFTER INSERT ON `family_group` FOR EACH ROW BEGIN
	UPDATE webreport_setting SET family_group = 1;
END
;;
DELIMITER ;
DELIMITER ;;
CREATE TRIGGER `trigger_family_group_update` AFTER UPDATE ON `family_group` FOR EACH ROW BEGIN
	UPDATE webreport_setting SET family_group = 1;
END
;;
DELIMITER ;
DELIMITER ;;
CREATE TRIGGER `trigger_family_group_del` AFTER DELETE ON `family_group` FOR EACH ROW BEGIN
	UPDATE webreport_setting SET family_group = 1;
END
;;
DELIMITER ;
DELIMITER ;;
CREATE TRIGGER `trigger_major_group_add` AFTER INSERT ON `major_group` FOR EACH ROW BEGIN
	UPDATE webreport_setting SET major_group = 1;
END
;;
DELIMITER ;
DELIMITER ;;
CREATE TRIGGER `trigger_major_group_update` AFTER UPDATE ON `major_group` FOR EACH ROW BEGIN
	UPDATE webreport_setting SET major_group = 1;
END
;;
DELIMITER ;
DELIMITER ;;
CREATE TRIGGER `trigger_major_group_del` AFTER DELETE ON `major_group` FOR EACH ROW BEGIN
	UPDATE webreport_setting SET major_group = 1;
END
;;
DELIMITER ;
DELIMITER ;;
CREATE TRIGGER `trigger_menu_item_add` AFTER INSERT ON `menu_item` FOR EACH ROW BEGIN
	UPDATE webreport_setting SET menu_item = 1;
END
;;
DELIMITER ;
DELIMITER ;;
CREATE TRIGGER `trigger_menu_item_update` AFTER UPDATE ON `menu_item` FOR EACH ROW BEGIN
	UPDATE webreport_setting SET menu_item = 1;
END
;;
DELIMITER ;
DELIMITER ;;
CREATE TRIGGER `trigger_menu_item_del` AFTER DELETE ON `menu_item` FOR EACH ROW BEGIN
	UPDATE webreport_setting SET menu_item = 1;
END
;;
DELIMITER ;
DELIMITER ;;
CREATE TRIGGER `trigger_periods_add` AFTER INSERT ON `periods` FOR EACH ROW BEGIN
	UPDATE webreport_setting SET periods = 1;
END
;;
DELIMITER ;
DELIMITER ;;
CREATE TRIGGER `trigger_periods_update` AFTER UPDATE ON `periods` FOR EACH ROW BEGIN
	UPDATE webreport_setting SET periods = 1;
END
;;
DELIMITER ;
DELIMITER ;;
CREATE TRIGGER `trigger_periods_del` AFTER DELETE ON `periods` FOR EACH ROW BEGIN
	UPDATE webreport_setting SET periods = 1;
END
;;
DELIMITER ;
DELIMITER ;;
CREATE TRIGGER `trigger_rvc_center_add` AFTER INSERT ON `rvc_center` FOR EACH ROW BEGIN
	UPDATE webreport_setting SET rvc_center = 1;
END
;;
DELIMITER ;
DELIMITER ;;
CREATE TRIGGER `trigger_rvc_center_update` AFTER UPDATE ON `rvc_center` FOR EACH ROW BEGIN
	UPDATE webreport_setting SET rvc_center = 1;
END
;;
DELIMITER ;
DELIMITER ;;
CREATE TRIGGER `trigger_rvc_center_del` AFTER DELETE ON `rvc_center` FOR EACH ROW BEGIN
	UPDATE webreport_setting SET rvc_center = 1;
END
;;
DELIMITER ;
DELIMITER ;;
CREATE TRIGGER `trigger_tendermedia_add` AFTER INSERT ON `tender_media` FOR EACH ROW BEGIN
	UPDATE webreport_setting SET tender_media = 1;
END
;;
DELIMITER ;
DELIMITER ;;
CREATE TRIGGER `trigger_tendermedia_update` AFTER UPDATE ON `tender_media` FOR EACH ROW BEGIN
	UPDATE webreport_setting SET tender_media = 1;
END
;;
DELIMITER ;
DELIMITER ;;
CREATE TRIGGER `trigger_tendermedia_del` AFTER DELETE ON `tender_media` FOR EACH ROW BEGIN
	UPDATE webreport_setting SET tender_media = 1;
END
;;
DELIMITER ;
