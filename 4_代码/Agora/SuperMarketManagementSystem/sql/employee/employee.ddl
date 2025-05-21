员工信息
CREATE TABLE IF NOT EXISTS employee (
    employee_id INTEGER PRIMARY KEY AUTOINCREMENT,
    employee_name TEXT NOT NULL,
    gender TEXT NOT NULL,
    birth_date DATETIME NOT NULL,
    phone TEXT NOT NULL UNIQUE,
    id_number TEXT NOT NULL UNIQUE,
    hire_date DATETIME NOT NULL,
    position_id INTEGER NOT NULL,
    status TEXT NOT NULL CHECK(status IN ('在职', '离职', '休假')),
    address TEXT,
    FOREIGN KEY (position_id) REFERENCES position(position_id)
);
