-- 库存表
CREATE TABLE IF NOT EXISTS inventory (
  id INTEGER PRIMARY KEY AUTOINCREMENT,
  goods_rk_id INTEGER NOT NULL,
  warehouse_rk_id INTEGER NOT NULL,
  quantity REAL NOT NULL CHECK (quantity >= 0),
  min_threshold REAL NOT NULL CHECK (min_threshold >= 0),
  max_threshold REAL NOT NULL CHECK (max_threshold >= 0),
  last_updated DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP,
  FOREIGN KEY (goods_rk_id) REFERENCES goods (id) ON DELETE RESTRICT,
  FOREIGN KEY (warehouse_rk_id) REFERENCES warehouse (id) ON DELETE RESTRICT,
  UNIQUE (goods_rk_id, warehouse_rk_id)
);
