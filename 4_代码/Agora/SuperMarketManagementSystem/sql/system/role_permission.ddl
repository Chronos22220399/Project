-- 角色权限关联表（role_permission）
CREATE TABLE IF NOT EXISTS role_permission (
  role_rk_id INTEGER NOT NULL, -- 角色内部ID，外键
  permission_rk_id INTEGER NOT NULL, -- 权限内部ID，外键
  PRIMARY KEY (role_rk_id, permission_rk_id),
  FOREIGN KEY (role_rk_id) REFERENCES role (id) ON DELETE CASCADE ON UPDATE CASCADE,
  FOREIGN KEY (permission_rk_id) REFERENCES permission (id) ON DELETE CASCADE ON UPDATE CASCADE
);
