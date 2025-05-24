-- 员工信息
CREATE TABLE IF NOT EXISTS employee (
  id INTEGER PRIMARY KEY AUTOINCREMENT,
  employee_id TEXT NOT NULL UNIQUE,
  user_rk_id INTEGER NOT NULL UNIQUE,
  employee_name TEXT NOT NULL,
  gender TEXT NOT NULL,
  birthday DATE NOT NULL,
  id_number TEXT NOT NULL UNIQUE,
  hire_date DATETIME NOT NULL,
  position_rk_id INTEGER NOT NULL,
  status TEXT NOT NULL CHECK (status IN ('active', 'inactive', 'on_leave')),
  address TEXT,
  FOREIGN KEY (position_rk_id) REFERENCES position(id) ON DELETE SET NULL,
  FOREIGN KEY (user_rk_id) REFERENCES user (id) ON DELETE CASCADE
);
