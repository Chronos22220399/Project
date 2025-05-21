-- 预算计划表
-- Budget Type（预算类型）：
-- 'operating' : 经营预算
-- 'capital' : 资本预算
-- 'project' : 项目预算
-- 'marketing' : 市场预算
-- 'research' : 研发预算
-- 'personnel' : 人员预算
CREATE TABLE IF NOT EXISTS budget_plan (
  id INTEGER PRIMARY KEY AUTOINCREMENT, -- Internal ID（自增主键，内部使用）
  budget_id TEXT NOT NULL UNIQUE, -- Budget ID（预算ID，外部使用，UUID）
  budget_period TEXT NOT NULL, -- Budget Period（预算周期）
  department_name TEXT NOT NULL, -- Department Name（部门名称）
  budget_type TEXT NOT NULL CHECK (
    budget_type IN (
      'operating',
      'capital',
      'project',
      'marketing',
      'research',
      'personnel'
    )
  ), -- Budget Type（预算类型）：'operating'经营预算，'capital'资本预算，'project'项目预算，'marketing'市场预算，'research'研发预算，'personnel'人员预算
  budget_amount REAL NOT NULL CHECK (budget_amount >= 0), -- Budget Amount（预算金额）
  actual_expenditure REAL DEFAULT 0 CHECK (actual_expenditure >= 0), -- Actual Expenditure（实际支出金额）
  create_at DATETIME DEFAULT CURRENT_TIMESTAMP, -- Create Time（创建时间）
  responsible_person_id INTEGER NOT NULL, -- Responsible Person ID（负责人ID）
  status TEXT NOT NULL CHECK (
    status IN ('in_progress', 'completed', 'abandoned')
  ), -- Status（状态：进行中、已完成、已放弃）
  FOREIGN KEY (responsible_person_id) REFERENCES employee (id) ON DELETE RESTRICT ON UPDATE CASCADE
);
