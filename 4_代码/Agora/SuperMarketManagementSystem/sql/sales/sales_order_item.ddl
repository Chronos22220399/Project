--销售订单明细表 (Sales_Order_Item)
CREATE TABLE Sales_Order_Item (
    item_id INT PRIMARY KEY,
    order_id INT NOT NULL,
    goods_id INT NOT NULL,
    product_name VARCHAR(100) NOT NULL,
    unit VARCHAR(20) NOT NULL,
    unit_price DECIMAL(10, 2) NOT NULL,
    quantity INT NOT NULL,
    subtotal DECIMAL(10, 2) NOT NULL,
    promotion_id INT,
    FOREIGN KEY (order_id) REFERENCES SalesOrder(order_id)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
