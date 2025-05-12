-- 商品预警表，当 inventory.quantity < inventory_alert.lower_bound 时发出预警
CREATE TABLE IF NOT EXISTS inventory_alert (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    goods_rk_id INTEGER NOT NULL,
    lower_bound INTEGER NOT NULL,
    FOREIGN KEY (goods_rk_id) REFERENCES goods(id),
    UNIQUE (goods_rk_id)
);
