-- 出库单表
-- destination_type：出库类型，包括：
--   - sale：销售出库
--   - transfer：调拨出库
--   - scrap：报废出库
--   - other：其他出库
-- status：出库状态，包括：
--   - pending：待出库
--   - completed：已完成
--   - cancelled：已取消
CREATE TABLE IF NOT EXISTS stock_out (
  id INTEGER PRIMARY KEY AUTOINCREMENT,
  stock_out_id TEXT NOT NULL UNIQUE,
  warehouse_rk_id INTEGER NOT NULL,
  created_at DATETIME DEFAULT CURRENT_TIMESTAMP,
  created_by INTEGER NOT NULL,
  destination_type TEXT NOT NULL CHECK (
    destination_type IN ('sale', 'transfer', 'scrap', 'other')
  ),
  destination_reference INTEGER,
  status TEXT NOT NULL CHECK (status IN ('pending', 'completed', 'cancelled')) DEFAULT 'pending',
  remark TEXT,
  FOREIGN KEY (warehouse_rk_id) REFERENCES warehouse (id) ON DELETE RESTRICT ON UPDATE CASCADE,
  FOREIGN KEY (created_by) REFERENCES employee (id) ON DELETE RESTRICT ON UPDATE CASCADE
);
