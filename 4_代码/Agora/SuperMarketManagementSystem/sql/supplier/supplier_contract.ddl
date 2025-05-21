-- 供应商合同表
-- status:
--   active    : 生效中
--   expired   : 已过期
--   terminated: 已终止
CREATE TABLE IF NOT EXISTS supplier_contract (
  id INTEGER PRIMARY KEY AUTOINCREMENT,
  contract_id TEXT NOT NULL UNIQUE,
  supplier_rk_id INTEGER NOT NULL,
  start_date DATETIME DEFAULT CURRENT_TIMESTAMP,
  end_date DATETIME,
  contract_amount REAL NOT NULL,
  status TEXT CHECK (status IN ('active', 'expired', 'terminated')) DEFAULT 'active',
  file_path TEXT,
  FOREIGN KEY (supplier_rk_id) REFERENCES supplier (id) ON DELETE RESTRICT ON UPDATE CASCADE
);
