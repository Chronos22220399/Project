-- 系统更新类型选项说明
-- patch: 补丁
-- upgrade: 版本升级
-- 系统更新记录表 (system_update_log)
CREATE TABLE IF NOT EXISTS system_update_log (
  id INTEGER PRIMARY KEY AUTOINCREMENT, -- 自增主键，内部ID
  external_id TEXT UNIQUE NOT NULL, -- 外部ID（UUID）
  version TEXT NOT NULL, -- 版本号
  user_rk_id INTEGER, -- 更新用户内部ID，外键
  update_type TEXT NOT NULL CHECK (update_type IN ('patch', 'upgrade')), -- 更新类型：补丁、版本升级
  updated_at DATETIME DEFAULT CURRENT_TIMESTAMP, -- 更新时间
  description TEXT, -- 描述
  change_summary TEXT, -- 变更摘要
  affected_modules TEXT, -- 受影响模块
  FOREIGN KEY (user_rk_id) REFERENCES user (id) ON DELETE SET NULL ON UPDATE CASCADE
);
