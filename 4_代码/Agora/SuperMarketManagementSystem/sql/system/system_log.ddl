-- 系统操作日志表（system_log）
-- action_type 字段选项说明：
-- login：登录
-- add：添加
-- delete：删除
-- update：修改
CREATE TABLE IF NOT EXISTS system_log (
  id INTEGER PRIMARY KEY AUTOINCREMENT, -- 内部ID，自增主键，内部使用
  user_rk_id INTEGER, -- 用户内部ID，外键
  action_type TEXT NOT NULL CHECK (
    action_type IN ('login', 'add', 'delete', 'update')
  ), -- 操作类型
  actual_detail TEXT, -- 具体详情
  timestamp DATETIME DEFAULT CURRENT_TIMESTAMP, -- 时间戳
  ip_address TEXT, -- IP地址
  mac_address TEXT, -- MAC地址
  FOREIGN KEY (user_rk_id) REFERENCES user (id) ON DELETE SET NULL ON UPDATE CASCADE
);
