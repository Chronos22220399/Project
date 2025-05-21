-- 商品成本记录表
CREATE TABLE IF NOT EXISTS goods_cost_record (
  id INTEGER PRIMARY KEY AUTOINCREMENT, -- Internal ID（自增主键，内部使用）
  cost_record_id TEXT NOT NULL UNIQUE, -- Cost Record ID（成本记录ID，外部使用，UUID）
  goods_rk_id INTEGER NOT NULL, -- Product ID（商品ID）
  stock_in_rk_id INTEGER NOT NULL, -- Inbound ID（入库单ID）
  supplier_rk_id INTEGER NOT NULL, -- Supplier ID（供应商ID）
  unit_cost REAL NOT NULL CHECK (unit_cost >= 0), -- Unit Cost（单位成本）
  quantity REAL NOT NULL CHECK (quantity >= 0), -- Quantity（数量）
  total_cost REAL NOT NULL CHECK (total_cost >= 0), -- Total Cost（总成本）
  stock_in_time DATETIME NOT NULL, -- Inbound Time（入库时间）
  recorded_at DATETIME DEFAULT CURRENT_TIMESTAMP, -- Recorded At（记录时间）
  FOREIGN KEY (goods_rk_id) REFERENCES product_information (id) ON DELETE RESTRICT ON UPDATE CASCADE,
  FOREIGN KEY (stock_in_rk_id) REFERENCES stock_in (id) ON DELETE RESTRICT ON UPDATE CASCADE,
  FOREIGN KEY (supplier_rk_id) REFERENCES supplier (id) ON DELETE RESTRICT ON UPDATE CASCADE
);
