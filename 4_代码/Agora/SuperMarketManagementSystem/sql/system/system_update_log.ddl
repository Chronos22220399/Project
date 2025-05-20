--系统更新记录表 (System_Update_Log)
CREATE TABLE System_Update_Log (
    update_id INT AUTO_INCREMENT PRIMARY KEY,
    version VARCHAR(255) NOT NULL,
    user_id INT,
    update_type ENUM('补丁', '版本升级') NOT NULL,
    updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    description TEXT,
    change_summary TEXT,
    affected_modules TEXT,
    FOREIGN KEY (user_id) REFERENCES User(user_id)
);
