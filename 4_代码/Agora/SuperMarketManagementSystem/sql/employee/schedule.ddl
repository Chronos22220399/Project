-- 员工排班表
CREATE TABLE IF NOT EXISTS schedule (
  id INTEGER PRIMARY KEY AUTOINCREMENT,
  schedule_id TEXT NOT NULL UNIQUE,
  employee_rk_id INTEGER NOT NULL,
  schedule_date DATE NOT NULL,
  start_time TIME NOT NULL,
  end_time TIME NOT NULL,
  created_at DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP,
  created_by INTEGER,
  FOREIGN KEY (employee_rk_id) REFERENCES employee (id),
  FOREIGN KEY (created_by) REFERENCES employee (id)
);
