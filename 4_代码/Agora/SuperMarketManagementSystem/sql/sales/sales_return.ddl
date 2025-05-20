--销售退货表 (Sales_Return)
CREATE TABLE Sales_Return (
    return_id INT PRIMARY KEY,
    order_id INT NOT NULL,
    return_time DATETIME NOT NULL,
    reason VARCHAR(255) NOT NULL,
    staff_id INT NOT NULL,
    total_refund DECIMAL(10, 2) NOT NULL,
    remark TEXT,
    status VARCHAR(20) CHECK (status IN ('未到', '已到', '取消')) NOT NULL,
    FOREIGN KEY (order_id) REFERENCES SalesOrder(order_id)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
