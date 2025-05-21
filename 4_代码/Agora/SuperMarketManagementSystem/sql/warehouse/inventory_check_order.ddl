-- 盘点单表
-- status values:
--   'draft'     - 草稿
--   'submitted' - 已提交
--   'audited'   - 已审核
CREATE TABLE IF NOT EXISTS inventory_check_order (
  id INTEGER PRIMARY KEY AUTOINCREMENT, -- Auto-increment ID（自增主键）
  check_id TEXT NOT NULL UNIQUE, -- Check Order ID（盘点单编号）
  warehouse_rk_id INTEGER NOT NULL, -- Warehouse FK（仓库外键）
  created_at DATETIME DEFAULT CURRENT_TIMESTAMP, -- Created Time（创建时间）
  created_by INTEGER NOT NULL, -- Created By（创建人）
  audited_by INTEGER NOT NULL, -- Audited By（审核人）
  audited_at DATETIME DEFAULT CURRENT_TIMESTAMP, -- Audited Time（审核时间）
  status TEXT NOT NULL CHECK (
    status IN ('draft', 'submitted', 'audited') -- Status（状态）
  ) DEFAULT 'draft',
  remark TEXT -- Remark（备注）
);
