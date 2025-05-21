-- 库存表
CREATE TABLE IF NOT EXISTS inventory (
  id INTEGER PRIMARY KEY AUTOINCREMENT,
  goods_rk_id INTEGER NOT NULL,
  warehouse_rk_id INTEGER NOT NULL,
  quantity REAL NOT NULL,
  FOREIGN KEY (goods_rk_id) REFERENCES goods (id) ON DELETE RESTRICT,
  FOREIGN KEY (warehouse_rk_id) REFERENCES warehouse (id) ON DELETE RESTRICT,
  UNIQUE (goods_rk_id, warehouse_rk_id)
);
