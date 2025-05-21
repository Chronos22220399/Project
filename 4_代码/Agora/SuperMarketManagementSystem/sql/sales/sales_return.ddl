-- 销售退货表
-- status: 
--   pending    : 未到  
--   received   : 已到  
--   cancelled  : 取消  
CREATE TABLE IF NOT EXISTS sales_return (
  id INTEGER PRIMARY KEY AUTOINCREMENT,
  return_id TEXT NOT NULL UNIQUE,
  order_rk_id INTEGER NOT NULL,
  return_time DATETIME NOT NULL,
  reason TEXT NOT NULL,
  staff_rk_id INTEGER NOT NULL,
  total_refund REAL NOT NULL CHECK (total_refund >= 0),
  remark TEXT,
  status TEXT NOT NULL CHECK (status IN ('pending', 'received', 'cancelled')),
  FOREIGN KEY (order_rk_id) REFERENCES sales_order (id),
  FOREIGN KEY (staff_rk_id) REFERENCES employee (id)
);
