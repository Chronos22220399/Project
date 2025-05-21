-- 创建供应商表
-- status:
--   active    : 正常
--   inactive  : 停用
--   blacklisted : 黑名单
CREATE TABLE IF NOT EXISTS supplier (
  id INTEGER PRIMARY KEY AUTOINCREMENT,
  supplier_id TEXT NOT NULL UNIQUE,
  supplier_name TEXT NOT NULL,
  contact_person TEXT NOT NULL,
  contact_phone TEXT NOT NULL,
  email TEXT,
  created_at DATETIME DEFAULT CURRENT_TIMESTAMP,
  status TEXT CHECK (status IN ('active', 'inactive', 'blacklisted')) DEFAULT 'active',
  remark TEXT
);
