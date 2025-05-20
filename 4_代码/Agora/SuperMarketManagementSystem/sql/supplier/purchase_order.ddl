-- 创建采购订单表
CREATE TABLE PurchaseOrder (
    purchase_order_id INT PRIMARY KEY AUTO_INCREMENT COMMENT '采购订单ID（主键）',
		supplier_id INT COMMENT '供应商ID（外键）',
		created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP COMMENT '创建时间',
		created_by INT COMMENT '创建人ID（关联员工编号）',
		expected_arrival_date DATE COMMENT '预计到货日期',
		actual_arrival_date DATE COMMENT '实际到货日期',
		status ENUM('待审', '已下单', '已入库') DEFAULT '待审' COMMENT '订单状态：默认‘待审’状态',
		total_amount DECIMAL(10,2) COMMENT '总金额（两位小数）',
		remark VARCHAR(255) COMMENT '备注',
		
		
		-- 外键约束：确保supplier_id引用Supplier表中的supplier_id
		FOREIGN KEY (supplier_id) REFERENCES Supplier(supplier_id) ON DELETE RESTRICT ON UPDATE CASCADE,
		
		-- 外键约束：确保created_by引用Employee表中的employee_id
		-- FOREIGN KEY (created_by) REFERENCES Employee(employee_id) ON DELETE RESTRICT ON UPDATE CASCADE,
		
		-- 索引：supplier_id
		INDEX idx_supplier_id (supplier_id)
			
		-- 索引：created_by
		-- INDEX idx_created_by (created_by)
		
)ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COMMENT='采购订单表';
