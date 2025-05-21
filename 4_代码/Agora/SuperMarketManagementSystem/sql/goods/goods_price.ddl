-- 商品价格表
CREATE TABLE IF NOT EXISTS goods_price (
  id INTEGER PRIMARY KEY AUTOINCREMENT,
  goods_rk_id INTEGER NOT NULL,
  price REAL NOT NULL,
  start_time DATETIME NOT NULL,
  note TEXT,
  FOREIGN KEY (goods_rk_id) REFERENCES goods (id) ON DELETE CASCADE,
  UNIQUE (goods_rk_id, start_time)
);
