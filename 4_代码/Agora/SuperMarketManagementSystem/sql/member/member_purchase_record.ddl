-- 会员消费记录表
CREATE TABLE IF NOT EXISTS member_purchase_record (
  id INTEGER PRIMARY KEY AUTOINCREMENT,
  record_id TEXT NOT NULL UNIQUE,
  member_rk_id INTEGER NOT NULL,
  transaction_date DATETIME NOT NULL,
  amount REAL NOT NULL CHECK (amount >= 0),
  earned_points INTEGER NOT NULL DEFAULT 0,
  FOREIGN KEY (member_rk_id) REFERENCES member (id) ON DELETE SET NULL
);
