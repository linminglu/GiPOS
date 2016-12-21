/*
Navicat MySQL Data Transfer

Source Server         : coolroid
Source Server Version : 50537
Source Host           : localhost:3308
Source Database       : coolroid

Target Server Type    : MYSQL
Target Server Version : 50537
File Encoding         : 65001

Date: 2016-11-25 09:16:53
*/

SET FOREIGN_KEY_CHECKS=0;
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
	AND order_head_id in (select distinct order_head_id from history_order_head where order_end_time>=s_time and order_end_time<=e_time)
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
DROP PROCEDURE IF EXISTS `c_major_sales`;
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
DROP PROCEDURE IF EXISTS `c_pay_style`;
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
DROP PROCEDURE IF EXISTS `c_pay_style_emp`;
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
where a.order_end_time>s_time and order_end_time<e_time ORDER BY a.order_head_id;
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
DROP PROCEDURE IF EXISTS `cost_sum`;
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
DROP PROCEDURE IF EXISTS `customer_num`;
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
DROP PROCEDURE IF EXISTS `employee_item_sales`;
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
DROP PROCEDURE IF EXISTS `family_group_analysis`;
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
DROP PROCEDURE IF EXISTS `flush_order`;
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
DROP PROCEDURE IF EXISTS `group_item_sales`;
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
DROP PROCEDURE IF EXISTS `item_sales`;
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
DROP PROCEDURE IF EXISTS `item_sales_desc`;
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
DROP PROCEDURE IF EXISTS `maingroup_item_sales`;
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
DROP PROCEDURE IF EXISTS `major_group_analysis`;
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
DROP PROCEDURE IF EXISTS `pay_style`;
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
DROP PROCEDURE IF EXISTS `sales_analysis_kaitailv`;
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
