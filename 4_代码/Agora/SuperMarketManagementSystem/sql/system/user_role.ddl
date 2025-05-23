CREATE TABLE user_role (
  user_rk_id INTEGER NOT NULL,
  role_rk_id INTEGER NOT NULL,
  PRIMARY KEY (user_rk_id, role_rk_id),
  FOREIGN KEY (user_rk_id) REFERENCES user (id) ON DELETE CASCADE,
  FOREIGN KEY (role_rk_id) REFERENCES role (role_id) ON DELETE CASCADE
);
