-- 工资管理
CREATE TABLE IF NOT EXISTS payroll_record (
  id INTEGER PRIMARY KEY AUTOINCREMENT,
  payroll_record_id TEXT NOT NULL UNIQUE,
  employee_rk_id INTEGER NOT NULL,
  pay_period TEXT NOT NULL, -- 用字符串存储，比如 "2023-04" 表示工资所属月份
  basic_salary REAL NOT NULL CHECK (basic_salary >= 0),
  bonus REAL DEFAULT 0 CHECK (bonus >= 0),
  deduction REAL DEFAULT 0 CHECK (deduction >= 0),
  net_salary REAL NOT NULL CHECK (net_salary >= 0),
  paid_at DATETIME NOT NULL,
  FOREIGN KEY (employee_rk_id) REFERENCES employee (id)
);
