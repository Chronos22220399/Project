-- 创建采购订单明细表
CREATE TABLE PurchaseOrderItem (
    item_id INT PRIMARY KEY AUTO_INCREMENT COMMENT '明细ID（主键）',
		purchase_order_id INT COMMENT '采购订单ID（外键）',
		-- goods_id INT COMMENT '商品ID（关联ProductInformation表中ID）',
		-- unit_id INT COMMENT '单位ID（关联ProductInformation表中unit_ID）',
		unit_price DECIMAL(10,2) COMMENT '单价 两位小数',
		quantity INT COMMENT '采购数量',
		subtotal DECIMAL(10,2) COMMENT '小计金额',
		
		-- 外键约束：purchase_order_id
		FOREIGN KEY (purchase_order_id) REFERENCES PurchaseOrder(purchase_order_id) ON DELETE RESTRICT ON UPDATE CASCADE,
		
		-- FOREIGN KEY (goods_id) REFERENCES ProductInformation(ID) ON DELETE RESTRICT ON UPDATE CASCADE,
		
		-- FOREIGN KEY (unit_id) REFERENCES ProductInformation(unit_ID) ON DELETE RESTRICT ON UPDATE CASCADE,
		
		
		-- 索引：purchase_order_id
		INDEX idx_purchase_order_id (purchase_order_id)
		
		-- INDEX idx_goods_id (goods_id),
		
		-- INDEX idx_unit_id (unit_id)
		
)ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COMMENT='采购订单明细表';

