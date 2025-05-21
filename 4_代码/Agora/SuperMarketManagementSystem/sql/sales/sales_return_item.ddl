-- 退货明细表
CREATE TABLE IF NOT EXISTS sales_return_item (
  id INTEGER PRIMARY KEY AUTOINCREMENT,
  item_id TEXT NOT NULL UNIQUE,
  return_rk_id INTEGER NOT NULL,
  goods_rk_id INTEGER NOT NULL,
  original_quantity REAL NOT NULL CHECK (original_quantity >= 0),
  return_quantity REAL NOT NULL CHECK (return_quantity >= 0),
  refund_amount REAL NOT NULL CHECK (refund_amount >= 0),
  FOREIGN KEY (return_rk_id) REFERENCES sales_return (id) ON DELETE CASCADE,
  FOREIGN KEY (goods_rk_id) REFERENCES goods (id)
);
