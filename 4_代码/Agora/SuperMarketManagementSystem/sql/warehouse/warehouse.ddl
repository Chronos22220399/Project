-- 仓库表
CREATE TABLE IF NOT EXISTS warehouse (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    warehouse_id TEXT UNIQUE,
    warehouse_name TEXT NOT NULL,
    location TEXT,
    total_slots INTEGER NOT NULL,
    available_slots INTEGER NOT NULL,
    manager TEXT,
    description TEXT
);
