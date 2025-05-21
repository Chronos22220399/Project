-- 角色表（role）
-- id：内部自增主键
-- role_id：外部ID，UUID格式，用于外部引用
CREATE TABLE role (
  id INTEGER PRIMARY KEY AUTOINCREMENT, -- 内部ID，自增主键，内部使用
  role_id TEXT NOT NULL UNIQUE, -- 角色外部ID，UUID，外部使用
  role_name TEXT NOT NULL, -- 角色名称
  description TEXT, -- 角色描述
  created_at DATETIME DEFAULT CURRENT_TIMESTAMP -- 创建时间
);
