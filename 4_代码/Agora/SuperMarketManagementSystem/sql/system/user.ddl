-- status 状态字段取值说明：
-- active: 启用
-- inactive: 停用
-- locked: 锁定
CREATE TABLE user (
  user_id INTEGER PRIMARY KEY AUTOINCREMENT, -- 用户ID，自增主键
  username TEXT NOT NULL, -- 用户名
  password_hash TEXT NOT NULL, -- 密码哈希
  role_rk_id INTEGER, -- 角色外键ID，关联 role 表
  employee_rk_id INTEGER, -- 员工外键ID，关联 employee 表
  status TEXT CHECK (status IN ('active', 'inactive', 'locked')) DEFAULT 'active', -- 用户状态
  created_at DATETIME DEFAULT CURRENT_TIMESTAMP, -- 创建时间
  last_login_at DATETIME, -- 最后登录时间
  FOREIGN KEY (role_rk_id) REFERENCES role (role_id) ON DELETE SET NULL ON UPDATE CASCADE,
  FOREIGN KEY (employee_rk_id) REFERENCES employee (employee_id) ON DELETE SET NULL ON UPDATE CASCADE
);
