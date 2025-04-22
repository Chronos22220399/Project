-- 商品类别表（支持层级结构）
CREATE TABLE IF NOT EXISTS category (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    category_id TEXT UNIQUE,
    category_name TEXT NOT NULL,
    category_description TEXT,
    parent_category_id INTEGER DEFAULT NULL,
    FOREIGN KEY (parent_category_id) REFERENCES category(id)
);
