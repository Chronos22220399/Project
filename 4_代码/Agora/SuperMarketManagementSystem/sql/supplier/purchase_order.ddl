-- 创建采购订单表
-- Purchase Order Table
-- status: 'pending_review'（待审）, 'ordered'（已下单）, 'received'（已入库）
CREATE TABLE IF NOT EXISTS purchase_order (
  id INTEGER PRIMARY KEY AUTOINCREMENT,
  purchase_order_id TEXT NOT NULL UNIQUE,
  supplier_rk_id INTEGER NOT NULL,
  created_at DATETIME DEFAULT CURRENT_TIMESTAMP,
  created_by INTEGER NOT NULL,
  expected_arrival_date DATETIME,
  actual_arrival_date DATETIME,
  status TEXT NOT NULL CHECK (
    status IN ('pending_review', 'ordered', 'received')
  ) DEFAULT 'pending_review',
  total_amount REAL CHECK (total_amount >= 0),
  remark TEXT,
  FOREIGN KEY (supplier_rk_id) REFERENCES supplier (id) ON DELETE RESTRICT ON UPDATE CASCADE,
  FOREIGN KEY (created_by) REFERENCES employee (id) ON DELETE RESTRICT ON UPDATE CASCADE
);
