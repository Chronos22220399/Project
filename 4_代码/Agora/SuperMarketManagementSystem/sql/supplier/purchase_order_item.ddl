-- 创建采购订单明细表
CREATE TABLE IF NOT EXISTS purchase_order_item (
  id INTEGER PRIMARY KEY AUTOINCREMENT,
  item_id TEXT NOT NULL UNIQUE,
  purchase_order_rk_id INTEGER NOT NULL,
  goods_rk_id INTEGER NOT NULL,
  unit_rk_id INTEGER NOT NULL,
  unit_price REAL NOT NULL CHECK (unit_price >= 0),
  quantity REAL NOT NULL CHECK (quantity >= 0),
  subtotal REAL NOT NULL CHECK (subtotal >= 0),
  FOREIGN KEY (purchase_order_rk_id) REFERENCES purchase_order (id) ON DELETE CASCADE ON UPDATE CASCADE,
  FOREIGN KEY (goods_rk_id) REFERENCES goods (id) ON DELETE RESTRICT ON UPDATE CASCADE,
  FOREIGN KEY (unit_rk_id) REFERENCES unit (id) ON DELETE RESTRICT ON UPDATE CASCADE
);
