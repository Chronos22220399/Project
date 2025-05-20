--销售订单表 (Sales_Order)
CREATE TABLE Sales_Order (
    order_id INT PRIMARY KEY,
    sale_time DATETIME NOT NULL,
    cashier_id INT NOT NULL,
    member_id INT,
    total_amount DECIMAL(10, 2) NOT NULL,
    paid_amount DECIMAL(10, 2) NOT NULL,
    payment_method VARCHAR(50) NOT NULL,
    discount_info VARCHAR(255),
    remark TEXT
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
