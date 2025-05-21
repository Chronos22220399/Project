-- 积分兑换物品
CREATE TABLE IF NOT EXISTS points_reward_item (
  id INTEGER PRIMARY KEY AUTOINCREMENT,
  item_id TEXT NOT NULL UNIQUE,
  item_name TEXT NOT NULL,
  points_required REAL NOT NULL CHECK (points_required >= 0),
  item_quantity REAL NOT NULL CHECK (item_quantity >= 0),
  begin_time DATETIME NOT NULL,
  end_time DATETIME NOT NULL,
  CHECK (
    end_time IS NULL
    OR end_time > begin_time
  )
);
