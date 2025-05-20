-- 创建供应商表
CREATE TABLE Supplier (
		supplier_id INT PRIMARY KEY AUTO_INCREMENT COMMENT '供应商ID（主键）',
    supplier_name VARCHAR(100) NOT NULL COMMENT '供应商名称',
    contact_person VARCHAR(50) COMMENT '联系人姓名',
    contact_phone VARCHAR(20) NOT NULL COMMENT '联系电话（必填）',
    email VARCHAR(100) COMMENT '邮箱（选填）',
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP COMMENT '注册时间（默认当前时间）',
    status ENUM('正常', '停用', '黑名单') DEFAULT '正常' COMMENT '状态（正常/停用/黑名单）',
    remark TEXT COMMENT '备注（长文本）'
)ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COMMENT='供应商信息表';
