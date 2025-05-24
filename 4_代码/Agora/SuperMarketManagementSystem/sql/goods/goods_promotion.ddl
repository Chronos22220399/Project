-- 商品促销信息表
CREATE TABLE IF NOT EXISTS goods_promotion (
  goods_rk_id INTEGER NOT NULL,
  promotion_rk_id INTEGER NOT NULL,
  discount_rate REAL,
  full_threshold REAL,
  reduce_amount REAL,
  buy_quantity REAL,
  gift_product TEXT,
  PRIMARY KEY (goods_rk_id, promotion_rk_id),
  FOREIGN KEY (goods_rk_id) REFERENCES goods (id) ON DELETE CASCADE,
  FOREIGN KEY (promotion_rk_id) REFERENCES promotion (id) ON DELETE CASCADE,
  UNIQUE (goods_rk_id, promotion_rk_id)
);
