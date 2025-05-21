-- 仓库表
-- status: active（启用）, inactive（停用）, maintenance（维护中）, closed（已关闭）
CREATE TABLE IF NOT EXISTS warehouse (
  id INTEGER PRIMARY KEY AUTOINCREMENT,
  warehouse_id TEXT NOT NULL UNIQUE,
  warehouse_name TEXT NOT NULL,
  location TEXT,
  capacity REAL CHECK (capacity >= 0),
  available_capacity REAL,
  manager_rk_id INTEGER,
  phone TEXT,
  created_at DATETIME DEFAULT CURRENT_TIMESTAMP,
  status TEXT NOT NULL CHECK (
    status IN ('active', 'inactive', 'maintenance', 'closed')
  ) DEFAULT 'active',
  remark TEXT,
  FOREIGN KEY (manager_rk_id) REFERENCES employee (id) ON DELETE SET NULL ON UPDATE CASCADE
);
