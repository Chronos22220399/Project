岗位管理
CREATE TABLE IF NOT EXISTS position (
    position_id INT AUTO_INCREMENT PRIMARY KEY, 
    position_name VARCHAR(50) NOT NULL, 
    description TEXT, 
    level VARCHAR(20), 
    establishment INT, 
    create_time TIMESTAMP DEFAULT CURRENT_TIMESTAMP, 
    update_time TIMESTAMP DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP
) ENGINE = InnoDB DEFAULT CHARSET = utf8mb4 COLLATE = utf8mb4_unicode_ci;