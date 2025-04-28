-- 商品表
CREATE TABLE IF NOT EXISTS goods (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    goods_id TEXT UNIQUE NOT NULL,
    category_rk_id INTEGER,
    supplier_rk_id INTEGER,
    unit_rk_id INTEGER,
    goods_name TEXT NOT NULL,
    shelf_life_days INTEGER,
    barcode TEXT,
    image_url TEXT,
    description TEXT,
    FOREIGN KEY (category_rk_id) REFERENCES goods_category(id),
    FOREIGN KEY (supplier_rk_id) REFERENCES supplier(id),
    FOREIGN KEY (unit_rk_id) REFERENCES unit(id)
);
