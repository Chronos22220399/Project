-- 供应商信息表
CREATE TABLE IF NOT EXISTS supplier (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    supplier_id TEXT UNIQUE, -- 逻辑ID
    supplier_name TEXT NOT NULL,
    contact_person TEXT,
    phone TEXT,
    address TEXT,
    rating_level TEXT CHECK(rating_level IN ('A', 'B', 'C', 'D', 'E')) DEFAULT 'C'
);
