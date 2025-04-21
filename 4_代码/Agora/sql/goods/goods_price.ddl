-- 商品价格表
CREATE TABLE goods_price (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    goods_id INTEGER NOT NULL,
    price REAL NOT NULL,
    start_time DATETIME NOT NULL,
    note TEXT,
    FOREIGN KEY (goods_id) REFERENCES goods(id),
    UNIQUE (goods_id, start_time)
);
