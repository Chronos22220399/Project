-- 销售订单明细表
CREATE TABLE IF NOT EXISTS sales_order_item (
  id INTEGER PRIMARY KEY AUTOINCREMENT,
  item_id TEXT NOT NULL UNIQUE,
  order_rk_id INTEGER NOT NULL,
  goods_rk_id INTEGER NOT NULL,
  product_name TEXT NOT NULL,
  unit_rk_id INTEGER NOT NULL,
  unit_price REAL NOT NULL CHECK (unit_price >= 0),
  quantity REAL NOT NULL CHECK (quantity > 0),
  subtotal REAL NOT NULL CHECK (subtotal >= 0),
  promotion_rk_id INTEGER,
  FOREIGN KEY (order_rk_id) REFERENCES sales_order (id) ON DELETE CASCADE,
  FOREIGN KEY (goods_rk_id) REFERENCES goods (id),
  FOREIGN KEY (unit_rk_id) REFERENCES unit (id),
  FOREIGN KEY (promotion_rk_id) REFERENCES promotion (id)
);
