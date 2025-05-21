-- 岗位管理
CREATE TABLE IF NOT EXISTS position(
  id INTEGER AUTO_INCREMENT PRIMARY KEY,
  position_id TEXT NOT NULL UNIQUE,
  position_name TEXT NOT NULL,
  base_salary REAL NOT NULL,
  is_manager BOOLEAN NOT NULL DEFAULT FALSE,
  department_name TEXT NOT NULL,
  description TEXT
);
