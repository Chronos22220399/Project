-- 积分政策表
CREATE TABLE IF NOT EXISTS points_policy (
  id INTEGER PRIMARY KEY AUTOINCREMENT,
  policy_id TEXT NOT NULL UNIQUE,
  policy_name TEXT NOT NULL UNIQUE,
  point_per_yuan REAL NOT NULL DEFAULT 0 CHECK (point_per_yuan >= 0),
  description TEXT,
  effective_from DATETIME NOT NULL,
  effective_to DATETIME,
  CHECK (
    effective_to IS NULL
    OR effective_to > effective_from
  )
);
