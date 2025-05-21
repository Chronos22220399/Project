-- 系统配置表（system_setting）
CREATE TABLE IF NOT EXISTS system_setting (
  setting_key TEXT PRIMARY KEY, -- 配置项键
  setting_value TEXT NOT NULL, -- 配置项值
  description TEXT, -- 描述
  updated_at DATETIME DEFAULT CURRENT_TIMESTAMP, -- 更新时间
  updater_rk_id INTEGER, -- 更新者内部ID，外键
  FOREIGN KEY (updater_rk_id) REFERENCES user (id) ON DELETE SET NULL ON UPDATE CASCADE
);
