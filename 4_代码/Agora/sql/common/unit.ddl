-- 单位表
CREATE TABLE unit (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    unit_id TEXT UNIQUE,
    unit_name TEXT NOT NULL
);
