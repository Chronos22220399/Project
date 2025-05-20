-- 仓库表
CREATE TABLE IF NOT EXISTS warehouse (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    warehouse_id TEXT UNIQUE,
    warehouse_name TEXT NOT NULL,
    location TEXT,
    capacity INTEGER,
    manager_id INTEGER,
    phone TEXT,
    created_at DATETIME,
    status TEXT,
    remark TEXT,
    -- TODO: 待修改
    CHECK(status IN ('A', 'B', 'C', 'D', 'E'))
);
