-- 仓库表
CREATE TABLE IF NOT EXISTS warehouse (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    warehouse_id TEXT UNIQUE,
    warehouse_name TEXT NOT NULL,
    location TEXT
);
