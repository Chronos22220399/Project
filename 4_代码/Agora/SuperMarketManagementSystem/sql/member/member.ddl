-- 会员信息表
-- 会员注销后状态标记为 inactive，删除会员只能从注销的会员中删除，且当前不写删除的功能
CREATE TABLE IF NOT EXISTS member (
  id INTEGER PRIMARY KEY AUTOINCREMENT,
  member_id TEXT NOT NULL UNIQUE,
  member_phone TEXT NOT NULL UNIQUE,
  registration_date DATETIME NOT NULL,
  level_rk_id INTEGER,
  points INTEGER DEFAULT 0,
  gender TEXT,
  birthday DATE,
  status TEXT CHECK (status IN ('active', 'inactive')) DEFAULT 'active',
  FOREIGN KEY (level_rk_id) REFERENCES member_levels (id) ON DELETE SET NULL
);
