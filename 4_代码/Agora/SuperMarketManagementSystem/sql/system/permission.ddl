-- 权限表（permission）
-- id：内部自增主键
-- permission_id：外部ID，UUID格式，用于外部引用
CREATE TABLE IF NOT EXISTS permission (
  id INTEGER PRIMARY KEY AUTOINCREMENT, -- 内部ID，自增主键，内部使用
  permission_id TEXT NOT NULL UNIQUE, -- 权限外部ID，UUID，外部使用
  permission_name TEXT NOT NULL, -- 权限名称
  permission_code TEXT NOT NULL, -- 权限编码
  description TEXT, -- 权限描述
  created_at DATETIME DEFAULT CURRENT_TIMESTAMP -- 创建时间
);
