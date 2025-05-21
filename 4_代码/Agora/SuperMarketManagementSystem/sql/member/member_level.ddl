-- 会员等级表
CREATE TABLE IF NOT EXISTS member_level (
  id INTEGER PRIMARY KEY AUTOINCREMENT,
  level_id TEXT NOT NULL UNIQUE,
  level_name TEXT NOT NULL UNIQUE,
  min_points REAL NOT NULL DEFAULT 0 CHECK (min_points >= 0),
  discount_rate REAL NOT NULL DEFAULT 1.0
);
