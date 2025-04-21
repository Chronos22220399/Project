-- 库存表
CREATE TABLE inventory (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    goods_id INTEGER NOT NULL,
    warehouse_id INTEGER NOT NULL,
    quantity INTEGER NOT NULL,
    unit TEXT,
    FOREIGN KEY (goods_id) REFERENCES goods(id),
    FOREIGN KEY (warehouse_id) REFERENCES warehouse(id),
    UNIQUE (goods_id, warehouse_id)
);
