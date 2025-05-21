-- 盘点明细表
CREATE TABLE IF NOT EXISTS inventory_check_item (
  id INTEGER PRIMARY KEY AUTOINCREMENT, -- Auto-increment ID（自增主键）
  item_id TEXT NOT NULL UNIQUE, -- Item ID（明细编号）
  check_rk_id INTEGER NOT NULL, -- Check Order FK（盘点单外键）
  goods_rk_id INTEGER NOT NULL, -- Goods FK（商品外键）
  system_quantity REAL NOT NULL, -- System Quantity（系统库存数量）
  actual_quantity REAL NOT NULL, -- Actual Quantity（实际盘点数量）
  difference REAL NOT NULL, -- Difference（盘盈盘亏）
  remark TEXT -- Remark（备注）
);
