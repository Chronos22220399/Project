-- 供应商表
CREATE TABLE IF NOT EXISTS supplier (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    supplier_id TEXT UNIQUE, -- 逻辑ID
    supplier_name TEXT NOT NULL,
    contact_person TEXT,
    phone TEXT,  -- 可以加上长度限制 phone TEXT(15) 如果你希望限制长度
    address TEXT,
    rating_level TEXT DEFAULT 'C',
    CHECK(rating_level IN ('A', 'B', 'C', 'D', 'E'))
);
