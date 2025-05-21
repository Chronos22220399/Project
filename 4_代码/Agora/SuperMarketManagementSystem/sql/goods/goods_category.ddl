-- 商品类别表（支持层级结构）
CREATE TABLE IF NOT EXISTS goods_category (
  id INTEGER PRIMARY KEY AUTOINCREMENT,
  goods_category_id TEXT UNIQUE,
  goods_category_name TEXT NOT NULL,
  goods_category_description TEXT,
  parent_category_id INTEGER DEFAULT NULL,
  FOREIGN KEY (parent_category_id) REFERENCES goods_category (id)
);
