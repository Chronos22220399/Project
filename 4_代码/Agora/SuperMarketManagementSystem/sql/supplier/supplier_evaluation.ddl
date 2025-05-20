-- 创建供应商评价表
CREATE TABLE SupplierEvaluation (
    -- 有Employee表之后需要添加的代码
	  -- evaluator_id INT COMMENT '评价人员（外键关联员工编号）',
		-- FOREIGN KEY (evaluator_id) REFERENCES Employee(employee_id) ON DELETE RESTRICT ON UPDATE CASCADE,
		-- INDEX idx_evaluator_id (evaluator_id)
			

	  evaluation_id INT PRIMARY KEY AUTO_INCREMENT COMMENT '评价ID（主键）',
		supplier_id INT COMMENT '供应商ID（外键）',
		evaluation_date TIMESTAMP DEFAULT CURRENT_TIMESTAMP COMMENT '评价时间',
		-- evaluator_id INT COMMENT '评价人员（外键关联员工编号）',
		service_score DECIMAL(2,1) COMMENT '服务评分（5分制 一位小数）',
		qualify_score DECIMAL(2,1) COMMENT '供货质量评分（5分制 一位小数）',
		timeliness_score DECIMAL(2,1) COMMENT '供货及时性评分（5分制 一位小数）',
		comment VARCHAR(255) COMMENT '综合评价（文字描述）',
		total_score DECIMAL(3,2) COMMENT '根据service score，qualify_score，timeliness_score的平均分来自动生成',
		remark VARCHAR(255) COMMENT '备注',
			
		-- 外键约束：确保supplier_id引用Supplier表中的supplier_id
		FOREIGN KEY (supplier_id) REFERENCES Supplier(supplier_id) ON DELETE RESTRICT ON UPDATE CASCADE,
			
		-- 外键约束：evaluator_id
		-- FOREIGN KEY (evaluator_id) REFERENCES Employee(employee_id) ON DELETE RESTRICT ON UPDATE CASCADE,
			
		-- 索引：supplier_id
		INDEX idx_supplier_id (supplier_id)
			
		-- 索引：evaluator_id
		-- INDEX idx_evaluator_id (evaluator_id)
    
			
)ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COMMENT='供应商评价表';
