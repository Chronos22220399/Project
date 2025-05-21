-- 创建供应商评价表
-- Supplier Evaluation Table
-- service_score, qualify_score, timeliness_score: 评分范围 0.0 ~ 5.0（1 位小数）
-- total_score: 三项平均分，建议由程序自动计算存入
CREATE TABLE IF NOT EXISTS supplier_evaluation (
  id INTEGER PRIMARY KEY AUTOINCREMENT,
  evaluation_id TEXT NOT NULL UNIQUE,
  supplier_rk_id INTEGER NOT NULL,
  evaluation_date DATETIME DEFAULT CURRENT_TIMESTAMP,
  service_score REAL CHECK (
    service_score >= 0.0
    AND service_score <= 5.0
  ),
  qualify_score REAL CHECK (
    qualify_score >= 0.0
    AND qualify_score <= 5.0
  ),
  timeliness_score REAL CHECK (
    timeliness_score >= 0.0
    AND timeliness_score <= 5.0
  ),
  total_score REAL CHECK (
    total_score >= 0.0
    AND total_score <= 5.0
  ),
  comment TEXT,
  remark TEXT,
  FOREIGN KEY (supplier_rk_id) REFERENCES supplier (id) ON DELETE RESTRICT ON UPDATE CASCADE
);
