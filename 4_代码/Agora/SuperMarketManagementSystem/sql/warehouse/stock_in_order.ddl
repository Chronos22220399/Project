-- 入库单表
-- source_type: purchase（采购）, transfer（调拨）, return（退货）, other（其他）
CREATE TABLE IF NOT EXISTS stock_in (
  id INTEGER PRIMARY KEY AUTOINCREMENT,
  stock_in_id TEXT NOT NULL UNIQUE,
  warehouse_rk_id INTEGER NOT NULL,
  created_at DATETIME DEFAULT CURRENT_TIMESTAMP,
  created_by INTEGER NOT NULL,
  source_type TEXT NOT NULL CHECK (
    source_type IN ('purchase', 'transfer', 'return', 'other')
  ),
  source_reference INTEGER, -- 来源编号，可为采购订单ID等
  remark TEXT,
  FOREIGN KEY (warehouse_rk_id) REFERENCES warehouse (id) ON DELETE RESTRICT ON UPDATE CASCADE,
  FOREIGN KEY (created_by) REFERENCES employee (id) ON DELETE RESTRICT ON UPDATE CASCADE
);
