-- 盘点单表
-- status values:
--   'draft'     - 草稿
--   'submitted' - 已提交
--   'audited'   - 已审核
CREATE TABLE IF NOT EXISTS inventory_check_order (
  id INTEGER PRIMARY KEY AUTOINCREMENT,
  order_id TEXT NOT NULL UNIQUE,
  warehouse_rk_id INTEGER NOT NULL,
  created_at DATETIME DEFAULT CURRENT_TIMESTAMP,
  created_by INTEGER NOT NULL,
  audited_by INTEGER NOT NULL,
  audited_at DATETIME DEFAULT CURRENT_TIMESTAMP,
  status TEXT NOT NULL DEFAULT 'draft',
  remark TEXT
);
