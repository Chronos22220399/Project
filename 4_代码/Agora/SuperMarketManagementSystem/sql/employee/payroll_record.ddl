工资管理
CREATE TABLE IF NOT EXISTS payroll_record (
    payroll_id INTEGER PRIMARY KEY AUTOINCREMENT,
    employee_id INTEGER NOT NULL,
    pay_period TEXT NOT NULL,
    basic_salary DECIMAL(10, 2) NOT NULL CHECK(basic_salary >= 0),
    bonus DECIMAL(10, 2) DEFAULT 0 CHECK(bonus >= 0),
    deduction DECIMAL(10, 2) DEFAULT 0 CHECK(deduction >= 0),
    net_salary DECIMAL(10, 2) NOT NULL CHECK(net_salary >= 0),
    paid_at DATETIME NOT NULL,
    FOREIGN KEY (employee_id) REFERENCES employee(employee_id),
    UNIQUE (employee_id, pay_period)
);