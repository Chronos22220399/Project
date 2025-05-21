-- 出库明细表
CREATE TABLE IF NOT EXISTS stock_out_item (
  id INTEGER PRIMARY KEY AUTOINCREMENT,
  item_id TEXT NOT NULL UNIQUE,
  stock_out_rk_id INTEGER NOT NULL,
  goods_rk_id INTEGER NOT NULL,
  quantity REAL NOT NULL,
  unit_price REAL NOT NULL,
  remark TEXT,
  FOREIGN KEY (stock_out_rk_id) REFERENCES stock_out (id) ON DELETE CASCADE ON UPDATE CASCADE,
  FOREIGN KEY (goods_rk_id) REFERENCES product_information (id) ON DELETE RESTRICT ON UPDATE CASCADE
);
