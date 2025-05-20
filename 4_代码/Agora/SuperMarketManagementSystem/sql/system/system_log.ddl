--系统操作日志表 (System_Log)
CREATE TABLE System_Log (
    log_id INT AUTO_INCREMENT PRIMARY KEY,
    user_id INT,
    action_type ENUM('登陆', '添加', '删除', '修改') NOT NULL,
    actual_detail TEXT,
    timestamp TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    ip_address VARCHAR(45),
    mac_address VARCHAR(17),
    FOREIGN KEY (user_id) REFERENCES User(user_id)
);
