--用户信息表 (User)
CREATE TABLE User (
    user_id INT AUTO_INCREMENT PRIMARY KEY,
    username VARCHAR(255) NOT NULL,
    password_hash VARCHAR(255) NOT NULL,
    role_id INT,
    employee_id INT,
    status ENUM('启用', '停用', '锁定') DEFAULT '启用',
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    last_login_at TIMESTAMP,
    FOREIGN KEY (role_id) REFERENCES Role(role_id)
);
