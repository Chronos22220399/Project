-- 商品出库表
CREATE TABLE IF NOT EXISTS inventory_out (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    inventory_out_id TEXT NOT NULL,
    goods_rk_id INTEGER NOT NULL,
    warehouse_rk_id INTEGER NOT NULL,
    unit_rk_id INTEGER NOT NULL,
    quantity INTEGER NOT NULL,
    out_time DATETIME NOT NULL,
    manager TEXT NOT NULL,
    reason TEXT,
    FOREIGN KEY (goods_rk_id) REFERENCES goods(id),
    FOREIGN KEY (warehouse_rk_id) REFERENCES warehouse(id),
    FOREIGN KEY (unit_rk_id) REFERENCES unit(id),
    UNIQUE (inventory_out_id, goods_rk_id, warehouse_rk_id, unit_rk_id)
);
