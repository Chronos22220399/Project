-- 支付方式说明：
-- cash：现金
-- wechat：微信
-- alipay：支付宝
-- bank_card：银行卡
CREATE TABLE IF NOT EXISTS sales_order (
  id INTEGER PRIMARY KEY AUTOINCREMENT,
  order_id TEXT NOT NULL UNIQUE,
  sale_time DATETIME NOT NULL,
  cashier_rk_id INTEGER NOT NULL,
  member_rk_id INTEGER,
  total_amount REAL NOT NULL CHECK (total_amount >= 0),
  paid_amount REAL NOT NULL CHECK (paid_amount >= 0),
  payment_method TEXT NOT NULL CHECK (
    payment_method IN ('cash', 'wechat', 'alipay', 'bank_card')
  ),
  discount_info TEXT,
  remark TEXT,
  FOREIGN KEY (cashier_rk_id) REFERENCES employee (id),
  FOREIGN KEY (member_rk_id) REFERENCES member (id)
);
