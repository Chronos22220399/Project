-- 促销活动表
CREATE TABLE IF NOT EXISTS promotion (
  id INTEGER PRIMARY KEY AUTOINCREMENT,
  promotion_id TEXT NOT NULL UNIQUE,
  promotion_name TEXT NOT NULL,
  description TEXT,
  type TEXT CHECK (type IN ('discount', 'full_reduction')),
  start_time DATETIME,
  end_time DATETIME,
  status TEXT CHECK (status IN ('active', 'expired', 'draft'))
);
