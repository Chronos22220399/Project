-- 商品盘点表，并没有和 inventory 表重复
-- inventory 侧重于描述当前有什么库存，inventory_check 侧重于描述库存的盘点历史
CREATE TABLE IF NOT EXISTS inventory_check (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    goods_rk_id INTEGER NOT NULL,
    warehouse_rk_id INTEGER NOT NULL,
    check_quantity INTEGER NOT NULL,
    actual_quantity INTEGER NOT NULL,
    difference INTEGER NOT NULL,
    check_time DATETIME NOT NULL,
    FOREIGN KEY (goods_rk_id) REFERENCES goods(id),
    FOREIGN KEY (warehouse_rk_id) REFERENCES warehouse(id)
);
