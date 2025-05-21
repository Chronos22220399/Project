-- 收银记录表
CREATE TABLE IF NOT EXISTS cashier_record (
  id INTEGER PRIMARY KEY AUTOINCREMENT, -- Record ID（记录ID，自增主键）
  record_id TEXT NOT NULL UNIQUE,
  order_rk_id INTEGER NOT NULL, -- Order ID（销售订单ID）
  cashier_rk_id INTEGER NOT NULL, -- Cashier ID（收银员ID）
  payment_method TEXT NOT NULL CHECK (
    payment_method IN ('cash', 'bank_card', 'wechat', 'alipay', 'other')
  ), -- Payment Method（支付方式）
  receivable_amount REAL NOT NULL CHECK (receivable_amount >= 0), -- Receivable Amount（应收金额，非负）
  paid_amount REAL NOT NULL CHECK (paid_amount >= 0), -- Paid Amount（实收金额，非负）
  change_amount REAL NOT NULL CHECK (change_amount >= 0), -- Change Amount（找零金额，非负）
  cashier_time DATETIME DEFAULT CURRENT_TIMESTAMP, -- Cashier Time（收银时间）
  counter_number TEXT, -- Counter Number（收银台编号）
  -- 外键约束
  FOREIGN KEY (order_rk_id) REFERENCES sales_order (id) ON DELETE RESTRICT ON UPDATE CASCADE,
  FOREIGN KEY (cashier_rk_id) REFERENCES employee (id) ON DELETE RESTRICT ON UPDATE CASCADE
);
