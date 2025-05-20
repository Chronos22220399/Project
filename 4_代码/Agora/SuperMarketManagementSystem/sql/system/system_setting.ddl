--系统配置表 (System_Setting)
CREATE TABLE System_Setting (
    setting_key VARCHAR(255) PRIMARY KEY,
    setting_value TEXT NOT NULL,
    description TEXT,
    updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
    updater_id INT,
    FOREIGN KEY (updater_id) REFERENCES User(user_id)
);
