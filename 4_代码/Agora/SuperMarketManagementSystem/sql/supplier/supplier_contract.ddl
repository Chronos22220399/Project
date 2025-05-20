-- 创建供应商合同表
CREATE TABLE SupplierContract (
    contract_id INT PRIMARY KEY AUTO_INCREMENT COMMENT '合同ID（主键）',
		supplier_id INT COMMENT '供应商ID（外键）',
		start_date DATE COMMENT '合同开始时间',
		end_date DATE COMMENT '合同结束时间',
		contract_amount INT COMMENT '合同金额',
		status ENUM('生效中', '已过期', '已终止') DEFAULT '生效中' COMMENT '状态（生效中/已过期/已终止）',
		file_path VARCHAR(255) COMMENT '附件路径：合同扫描件等文件路径',
		
		-- 外键约束：确保supplier_id引用Supplier表中的supplier_id
		FOREIGN KEY (supplier_id) REFERENCES Supplier(supplier_id) ON DELETE RESTRICT ON UPDATE CASCADE,
		
		-- 为supplier_id添加索引，提升按供应商ID查询或连接时的性能
		INDEX idx_supplier_id (supplier_id)
		
)ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COMMENT='供应商合同表';
