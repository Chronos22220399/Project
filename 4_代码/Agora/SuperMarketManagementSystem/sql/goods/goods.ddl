-- 商品表
CREATE TABLE IF NOT EXISTS goods (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    goods_id TEXT UNIQUE NOT NULL,
    category_id INTEGER,
    supplier_id INTEGER,
    unit_id INTEGER,
    goods_name TEXT NOT NULL,
    shelf_life_days INTEGER,
    barcode TEXT,
    image_url TEXT,
    description TEXT,
    FOREIGN KEY (category_id) REFERENCES category(id),
    FOREIGN KEY (unit_id) REFERENCES unit(id)
);
