-- 员工信息
CREATE TABLE IF NOT EXISTS employee (
  id INTEGER PRIMARY KEY AUTOINCREMENT,
  employee_id TEXT NOT NULL UNIQUE,
  employee_name TEXT NOT NULL,
  gender TEXT NOT NULL,
  birthday DATE NOT NULL,
  phone TEXT NOT NULL UNIQUE,
  id_number TEXT NOT NULL UNIQUE,
  hire_date DATETIME NOT NULL,
  position_rk_id INTEGER NOT NULL,
  status TEXT NOT NULL CHECK (status IN ('active', 'inactive', 'on_leave')),
  address TEXT,
  FOREIGN KEY (position_rk_id) REFERENCES position(id)
);
