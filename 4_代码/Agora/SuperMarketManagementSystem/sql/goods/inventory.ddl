-- 库存表
CREATE TABLE IF NOT EXISTS inventory (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    goods_rk_id INTEGER NOT NULL,
    warehouse_rk_id INTEGER NOT NULL,
    quantity INTEGER NOT NULL,
    FOREIGN KEY (goods_rk_id) REFERENCES goods(id),
    FOREIGN KEY (warehouse_rk_id) REFERENCES warehouse(id),
    UNIQUE (goods_rk_id, warehouse_rk_id)
);
