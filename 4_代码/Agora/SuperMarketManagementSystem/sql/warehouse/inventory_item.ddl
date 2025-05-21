-- 对应商品管理模块的 inventory 表
-- 库存信息表（对应商品管理模块）
CREATE TABLE IF NOT EXISTS inventory_item (
  id INTEGER PRIMARY KEY AUTOINCREMENT, -- Auto-increment ID（自增主键）
  item_id TEXT NOT NULL UNIQUE, -- Item ID（库存项编号，唯一）
  inventory_rk_id INTEGER NOT NULL, -- Inventory FK（关联商品外键）
  min_threshold REAL CHECK (min_threshold >= 0), -- Minimum Threshold（最小库存阈值，非负）
  max_threshold REAL CHECK (max_threshold >= 0), -- Maximum Threshold（最大库存阈值，非负）
  last_updated DATETIME, -- Last Updated Time（最后更新时间）
  remark TEXT -- Remark（备注）
);
