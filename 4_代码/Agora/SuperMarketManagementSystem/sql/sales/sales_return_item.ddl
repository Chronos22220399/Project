--退货明细表 (Sales_Return_Item)
CREATE TABLE Sales_Return_Item (
    item_id INT PRIMARY KEY,
    return_id INT NOT NULL,
    goods_id INT NOT NULL,
    original_quantity INT NOT NULL,
    return_quantity INT NOT NULL,
    refund_amount DECIMAL(10, 2) NOT NULL,
    FOREIGN KEY (return_id) REFERENCES SalesReturn(return_id)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
