员工排班管理
CREATE TABLE shift (
    shift_id INT AUTO_INCREMENT PRIMARY KEY, 
    shift_name VARCHAR(20) NOT NULL, 
    start_time TIME,
    end_time TIME,
    break_time TIME
);

CREATE TABLE employee_schedule (
    schedule_id INT AUTO_INCREMENT PRIMARY KEY, 
    employee_id INT, 
    shift_id INT,
    schedule_date DATE,
    FOREIGN KEY (employee_id) REFERENCES employee(employee_id), 
    FOREIGN KEY (shift_id) REFERENCES shift(shift_id) 
);