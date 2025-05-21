-- 积分兑换记录表
CREATE TABLE IF NOT EXISTS points_exchange_record (
  id INTEGER PRIMARY KEY AUTOINCREMENT,
  record_id TEXT NOT NULL UNIQUE,
  member_rk_id INTEGER NOT NULL,
  item_rk_id INTEGER NOT NULL,
  operator_rk_id INTEGER,
  points_spent INTEGER NOT NULL,
  redemption_time DATETIME NOT NULL,
  FOREIGN KEY (member_rk_id) REFERENCES members (id) ON DELETE SET NULL,
  FOREIGN KEY (item_rk_id) REFERENCES items (id),
  FOREIGN KEY (operator_rk_id) REFERENCES employee (id)
);
