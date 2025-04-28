-- 商品促销信息表
CREATE TABLE IF NOT EXISTS goods_promotion (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    goods_rk_id INTEGER,
    promotion_rk_id INTEGER,
    discount_rate REAL,
    full_threshold REAL,
    reduce_amount REAL,
    buy_quantity INTEGER,
    gift_product TEXT,
    FOREIGN KEY (goods_rk_id) REFERENCES goods(id),
    FOREIGN KEY (promotion_rk_id) REFERENCES promotion(id),
    UNIQUE (goods_rk_id, promotion_rk_id)
);
